#include "laPlutoFrontend.hpp"

#include "LangDesc.hpp"
#include "Lexeme.hpp"
#include "LexemeParser.hpp"

NAMESPACE_SOUP
{
	static constexpr const char* TK_LOCAL = "local";
	static constexpr const char* TK_FUNCTION = "function";
	static constexpr const char* TK_RETURN = "return";
	static constexpr const char* TK_IF = "if";
	static constexpr const char* TK_ELSE = "else";
	static constexpr const char* TK_WHILE = "while";
	static constexpr const char* TK_END = "end";
	static constexpr const char* TK_ADD = "+";
	static constexpr const char* TK_SUB = "-";
	static constexpr const char* TK_MUL = "*";
	static constexpr const char* TK_DIV = "/";
	static constexpr const char* TK_MOD = "%";
	static constexpr const char* TK_COMMA = ",";
	static constexpr const char* TK_LPAREN = "(";
	static constexpr const char* TK_RPAREN = ")";
	static constexpr const char* TK_ASSIGN = "=";
	static constexpr const char* TK_EQUALS = "==";
	static constexpr const char* TK_NOTEQUALS = "~=";

	irModule laPlutoFrontend::parse(const std::string& program)
	{
		LangDesc ld;
		ld.addToken(TK_LOCAL);
		ld.addToken(TK_FUNCTION);
		ld.addToken(TK_RETURN);
		ld.addToken(TK_IF);
		ld.addToken(TK_ELSE);
		ld.addToken(TK_WHILE);
		ld.addToken(TK_END);
		ld.addToken(TK_ADD);
		ld.addToken(TK_SUB);
		ld.addToken(TK_MUL);
		ld.addToken(TK_DIV);
		ld.addToken(TK_MOD);
		ld.addToken(TK_COMMA);
		ld.addToken(TK_LPAREN);
		ld.addToken(TK_RPAREN);
		ld.addToken(TK_ASSIGN);
		ld.addToken(TK_EQUALS);
		ld.addToken(TK_NOTEQUALS);

		auto ls = ld.tokenise(program);
		ld.eraseNlTerminatedComments(ls, "--");
		ld.eraseSpace(ls);
		LexemeParser lp(std::move(ls));

		irModule m;
		irFunction top_level_fn;
		locals.emplace();
		top_level_fn.insns = statlist(lp, m, top_level_fn);
		if (!top_level_fn.insns.empty())
		{
			//top_level_fn.name = "_start";
			m.func_exports.emplace_back(std::move(top_level_fn));
		}
		return m;
	}

	std::vector<UniquePtr<irExpression>> laPlutoFrontend::statlist(LexemeParser& lp, irModule& m, irFunction& fn)
	{
		std::vector<UniquePtr<irExpression>> insns{};
		while (lp.hasMore())
		{
			if (lp.i->token_keyword == TK_FUNCTION)
			{
				lp.advance();
				irFunction inner_fn;
				if (lp.i->isLiteral())
				{
					locals.emplace();
					inner_fn.name = lp.i->getLiteral();
					lp.advance(); // skip name
					if (lp.hasMore()) { lp.advance(); } // skip '('
					while (lp.hasMore() && lp.i->isLiteral())
					{
						locals.top().emplace_back(lp.i->getLiteral());
						inner_fn.parameters.emplace_back(IR_I64);
						lp.advance(); // skip name
						if (lp.getTokenKeyword() != TK_COMMA)
						{
							break;
						}
						lp.advance(); // skip ','
					}
					if (lp.hasMore()) { lp.advance(); } // skip ')'
					if (lp.hasMore())
					{
						inner_fn.insns = statlist(lp, m, inner_fn);
						if (lp.getTokenKeyword() == TK_END)
						{
							lp.advance();
						}
						m.func_exports.emplace_back(std::move(inner_fn));
					}
					locals.pop();
				}
			}
			else if (lp.i->token_keyword == TK_LOCAL)
			{
				lp.advance();
				if (lp.i->isLiteral())
				{
					fn.locals.emplace_back(IR_I64);
					locals.top().emplace_back(lp.i->getLiteral());
					lp.advance();
				}
			}
			else if (lp.i->token_keyword == TK_RETURN)
			{
				lp.advance();
				auto insn = soup::make_unique<irExpression>(IR_RET);
				do
				{
					auto val = expr(lp, m, fn);
					if (!val)
					{
						break;
					}
					if (val->type == IR_CALL)
					{
						if (lp.getTokenKeyword() == TK_COMMA) // Not the last return value?
						{
							// Prune to only a single return value.
							fn.returns.emplace_back(m.func_exports.at(val->call.index).returns.front());
							val = oneret(m, std::move(val));
						}
						else
						{
							for (const auto& type : m.func_exports.at(val->call.index).returns)
							{
								fn.returns.emplace_back(type);
							}
						}
					}
					else
					{
						fn.returns.emplace_back(val->getResultType(fn));
					}
					insn->children.emplace_back(std::move(val));
				} while (lp.getTokenKeyword() == TK_COMMA && (lp.advance(), true));
				insns.emplace_back(std::move(insn));
			}
			else if (lp.i->token_keyword == TK_IF)
			{
				lp.advance();
				auto insn = soup::make_unique<irExpression>(IR_IFELSE);
				if (auto cond = expr(lp, m, fn))
				{
					insn->children.emplace_back(std::move(cond));
					if (lp.hasMore()) { lp.advance(); } // skip 'then'
					for (auto& inner_stat : statlist(lp, m, fn))
					{
						insn->children.emplace_back(std::move(inner_stat));
					}
					insn->ifelse.ifinsns = insn->children.size() - 1;
					if (lp.getTokenKeyword() == TK_ELSE)
					{
						lp.advance();
						for (auto& inner_stat : statlist(lp, m, fn))
						{
							insn->children.emplace_back(std::move(inner_stat));
						}
					}
					if (lp.hasMore()) { lp.advance(); } // skip 'end'
					insns.emplace_back(std::move(insn));
				}
			}
			else if (lp.i->token_keyword == TK_WHILE)
			{
				lp.advance();
				auto insn = soup::make_unique<irExpression>(IR_WHILE);
				if (auto cond = expr(lp, m, fn))
				{
					insn->children.emplace_back(std::move(cond));
					if (lp.hasMore()) { lp.advance(); } // skip 'do'
					for (auto& inner_stat : statlist(lp, m, fn))
					{
						insn->children.emplace_back(std::move(inner_stat));
					}
					if (lp.hasMore()) { lp.advance(); } // skip 'end'
					insns.emplace_back(std::move(insn));
				}
			}
			else if (auto insn = exprstat(lp, m, fn))
			{
				insns.emplace_back(std::move(insn));
			}
			else
			{
				break;
			}
		}
		return insns;
	}

	[[nodiscard]] static uint8_t getbinopr(const char* token_keyword) noexcept
	{
		if (token_keyword == TK_ADD) { return IR_ADD_I64; }
		if (token_keyword == TK_SUB) { return IR_SUB_I64; }
		if (token_keyword == TK_MUL) { return IR_MUL_I64; }
		if (token_keyword == TK_DIV) { return IR_SDIV_I64; }
		if (token_keyword == TK_MOD) { return IR_SMOD_I64; }
		if (token_keyword == TK_EQUALS) { return IR_EQUALS_I64; }
		if (token_keyword == TK_NOTEQUALS) { return IR_NOTEQUALS_I64; }
		return 0xff;
	}

	[[nodiscard]] static uint8_t getpriority(uint8_t opr) noexcept
	{
		switch (opr)
		{
		case IR_MUL_I64: case IR_SDIV_I64: case IR_SMOD_I64: return 2;
		}
		return 1;
	}

	UniquePtr<irExpression> laPlutoFrontend::expr(LexemeParser& lp, irModule& m, irFunction& fn, uint8_t limit)
	{
		auto ret = simpleexp(lp, m, fn);
		if (ret)
		{
			auto opr = getbinopr(lp.getTokenKeyword());
			while (opr != 0xff && getpriority(opr) > limit)
			{
				lp.advance();
				auto rhs = expr(lp, m, fn, getpriority(opr));
				if (!rhs)
				{
					break;
				}
				ret = soup::make_unique<irExpression>(static_cast<irExpressionType>(opr), std::move(ret));
				ret->children.emplace_back(std::move(rhs));
				opr = getbinopr(lp.getTokenKeyword());
			}
		}
		return ret;
	}

	UniquePtr<irExpression> laPlutoFrontend::simpleexp(LexemeParser& lp, irModule& m, irFunction& fn)
	{
		UniquePtr<irExpression> ret;
		if (lp.hasMore())
		{
			if (lp.i->token_keyword == Lexeme::VAL)
			{
				if (lp.i->val.isInt())
				{
					ret = soup::make_unique<irExpression>(IR_CONST_I64);
					ret->const_i64.value = lp.i->val.getInt();
					lp.advance();
				}
				else if (lp.i->val.isString())
				{
					auto data = lp.i->val.getString();
					data.push_back('\0');
					ret = soup::make_unique<irExpression>(IR_CONST_I64);
					ret->const_i64.value = m.allocateConstData(std::move(data));
					lp.advance();
				}
			}
			else if (lp.i->token_keyword == Lexeme::LITERAL)
			{
				if (lp.i->getLiteral() == "true")
				{
					ret = soup::make_unique<irExpression>(IR_CONST_BOOL);
					ret->const_bool.value = true;
					lp.advance();
				}
				else if(lp.i->getLiteral() == "false")
				{
					ret = soup::make_unique<irExpression>(IR_CONST_BOOL);
					ret->const_bool.value = false;
					lp.advance();
				}
				else if ((lp.i + 1) != lp.tks.end()
					&& (lp.i + 1)->token_keyword == TK_LPAREN
					)
				{
					ret = suffixedexp(lp, m, fn);
				}
				else
				{
					const auto& locals_in_scope = locals.top();
					if (auto it = std::find(locals_in_scope.begin(), locals_in_scope.end(), lp.i->getLiteral()); it != locals_in_scope.end())
					{
						ret = soup::make_unique<irExpression>(IR_LOCAL_GET);
						ret->local_get.index = static_cast<uint32_t>(std::distance(locals_in_scope.begin(), it));
						lp.advance();
					}
				}
			}
		}
		return ret;
	}

	UniquePtr<irExpression> laPlutoFrontend::exprstat(LexemeParser& lp, irModule& m, irFunction& fn)
	{
		if (lp.getTokenKeyword() == Lexeme::LITERAL)
		{
			if ((lp.i + 1) != lp.tks.end()
				&& (lp.i + 1)->token_keyword == TK_ASSIGN
				)
			{
				const auto& locals_in_scope = locals.top();
				if (auto it = std::find(locals_in_scope.begin(), locals_in_scope.end(), lp.i->getLiteral()); it != locals_in_scope.end())
				{
					auto insn = soup::make_unique<irExpression>(IR_LOCAL_SET);
					insn->local_set.index = static_cast<uint32_t>(std::distance(locals_in_scope.begin(), it));
					lp.advance(); // skip name 
					lp.advance(); // skip '='
					if (auto val = expr(lp, m, fn))
					{
						insn->children.emplace_back(std::move(val));
						return insn;
					}
				}
			}
		}
		return suffixedexp(lp, m, fn);
	}

	UniquePtr<irExpression> laPlutoFrontend::suffixedexp(LexemeParser& lp, irModule& m, irFunction& fn)
	{
		UniquePtr<irExpression> ret;
		if (lp.getTokenKeyword() == Lexeme::LITERAL)
		{
			if ((lp.i + 1) != lp.tks.end()
				&& (lp.i + 1)->token_keyword == TK_LPAREN
				)
			{
				if (lp.i->getLiteral() == "__load_u8")
				{
					auto insn = soup::make_unique<irExpression>(IR_LOAD_I8);
					funcargs(lp, m, fn, *insn);
					auto ptrExpr = std::move(insn->children.at(0));
					insn->children.at(0) = soup::make_unique<irExpression>(IR_I64_TO_PTR);
					insn->children.at(0)->children.emplace_back(std::move(ptrExpr));
					ret = soup::make_unique<irExpression>(IR_I8_TO_I64_ZX);
					ret->children.emplace_back(std::move(insn));
				}
				else if (lp.i->getLiteral() == "__load_i8")
				{
					auto insn = soup::make_unique<irExpression>(IR_LOAD_I8);
					funcargs(lp, m, fn, *insn);
					auto ptrExpr = std::move(insn->children.at(0));
					insn->children.at(0) = soup::make_unique<irExpression>(IR_I64_TO_PTR);
					insn->children.at(0)->children.emplace_back(std::move(ptrExpr));
					ret = soup::make_unique<irExpression>(IR_I8_TO_I64_SX);
					ret->children.emplace_back(std::move(insn));
				}
				else if (lp.i->getLiteral() == "__store8")
				{
					ret = soup::make_unique<irExpression>(IR_STORE_I8);
					funcargs(lp, m, fn, *ret);
					auto ptrExpr = std::move(ret->children.at(0));
					ret->children.at(0) = soup::make_unique<irExpression>(IR_I64_TO_PTR);
					ret->children.at(0)->children.emplace_back(std::move(ptrExpr));
					auto valueExpr = std::move(ret->children.at(1));
					ret->children.at(1) = soup::make_unique<irExpression>(IR_I64_TO_I8);
					ret->children.at(1)->children.emplace_back(std::move(valueExpr));
				}
				else if (lp.i->getLiteral() == "print")
				{
					ret = soup::make_unique<irExpression>(IR_CALL);
					ret->call.index = m.getPrintFunctionIndex();
					funcargs(lp, m, fn, *ret);
					auto ptrExpr = oneret(m, std::move(ret->children.at(0)));
					ret->children.at(0) = soup::make_unique<irExpression>(IR_I64_TO_PTR);
					ret->children.at(0)->children.emplace_back(std::move(ptrExpr));
				}
				else
				{
					for (uint32_t i = 0; i != m.func_exports.size(); ++i)
					{
						if (m.func_exports[i].name == lp.i->getLiteral())
						{
							ret = soup::make_unique<irExpression>(IR_CALL);
							ret->call.index = i;
							funcargs(lp, m, fn, *ret);
							break;
						}
					}
				}
			}
		}
		return ret;
	}

	void laPlutoFrontend::funcargs(LexemeParser& lp, irModule& m, irFunction& fn, irExpression& insn)
	{
		lp.advance(); // skip name
		if (lp.hasMore()) { lp.advance(); } // skip '('
		while (lp.hasMore())
		{
			auto arg = expr(lp, m, fn);
			if (!arg)
			{
				break;
			}
			insn.children.emplace_back(std::move(arg));
			if (lp.getTokenKeyword() != TK_COMMA)
			{
				break;
			}
			lp.advance(); // skip ','
		}
		if (lp.hasMore()) { lp.advance(); } // skip ')'
	}

	UniquePtr<irExpression> laPlutoFrontend::oneret(irModule& m, UniquePtr<irExpression>&& insn)
	{
		if (insn->type == IR_CALL)
		{
			auto nret = m.getFunction(insn->call.index).returns.size();
			SOUP_ASSERT(nret != 0);
			auto discardInsn = soup::make_unique<irExpression>(IR_DISCARD);
			discardInsn->discard.count = nret - 1;
			discardInsn->children.emplace_back(std::move(insn));
			return discardInsn;
		}
		SOUP_MOVE_RETURN(insn);
	}
}
