#include "Regex.hpp"

#include <sstream>
#include <unordered_set>

#include "base.hpp"
#include "RegexConstraint.hpp"
#include "RegexMatcher.hpp"
#include "string.hpp"

#define REGEX_DEBUG_MATCH false

#if REGEX_DEBUG_MATCH
#include <iostream>
#endif

namespace soup
{
	Regex Regex::fromFullString(const std::string& str)
	{
		if (str.length() >= 2)
		{
			const char c = str.at(0);
			const auto i = str.find_last_of(c);
			if (i > 0)
			{
				return Regex(str.c_str() + 1, str.c_str() + i, parseFlags(str.c_str() + i + 1));
			}
		}
		return {};
	}

	bool Regex::matches(const std::string& str) const noexcept
	{
		return matches(str.data(), &str.data()[str.size()]);
	}

	bool Regex::matches(const char* it, const char* end) const noexcept
	{
		return match(it, end).isSuccess();
	}

	bool Regex::matchesFully(const std::string& str) const noexcept
	{
		return matchesFully(str.data(), &str.data()[str.size()]);
	}

	bool Regex::matchesFully(const char* it, const char* end) const noexcept
	{
		auto res = match(it, end);
		if (res.isSuccess())
		{
			return res.groups.at(0)->end == end;
		}
		return false;
	}

	RegexMatchResult Regex::match(const std::string& str) const noexcept
	{
		return match(str.data(), &str.data()[str.size()]);
	}

	RegexMatchResult Regex::match(const char* it, const char* end) const noexcept
	{
		return match(it, it, end);
	}

	RegexMatchResult Regex::match(const char* it, const char* begin, const char* end) const noexcept
	{
		RegexMatcher m(*this, begin, end);
		return match(m, it);
	}

	RegexMatchResult Regex::match(RegexMatcher& m, const char* it) const noexcept
	{
		const auto match_begin = it;
		m.it = it;
		SOUP_IF_UNLIKELY (m.shouldSaveCheckpoint())
		{
			m.saveCheckpoint();
		}
		while (m.c != nullptr)
		{
#if REGEX_DEBUG_MATCH
			std::cout << m.c->toString() << ": ";
#endif

			if (m.c->rollback_transition)
			{
#if REGEX_DEBUG_MATCH
				std::cout << "saved rollback; ";
#endif
				m.saveRollback(m.c->rollback_transition);
			}

			// Matches?
			auto _it = m.it;
			if (m.c->matches(m))
			{
				for (auto g = m.c->group.getPointer(); g; g = g->parent)
				{
					if (g->lookahead_or_lookbehind)
					{
						break;
					}
					if (g->isNonCapturing())
					{
						continue;
					}
					//std::cout << "group " << g->index << "; ";
					while (g->index >= m.result.groups.size())
					{
						m.result.groups.emplace_back(std::nullopt);
					}
					if (m.result.groups.at(g->index).has_value())
					{
						m.result.groups.at(g->index)->end = m.it;
					}
					else
					{
						m.result.groups.at(g->index) = RegexMatchedGroup{ g->name, _it, m.it };
					}
				}
				if (m.c->group.getBool())
				{
					m.result.groups.at(m.c->group->index)->begin = _it;
				}

				m.c = m.c->success_transition;
				if (m.shouldSaveCheckpoint())
				{
#if REGEX_DEBUG_MATCH
					std::cout << "saved checkpoint; ";
#endif
					m.saveCheckpoint();
				}
				if (reinterpret_cast<uintptr_t>(m.c) == 0b10)
				{
#if REGEX_DEBUG_MATCH
					std::cout << "matched into a snafu\n";
#endif
					return {};
				}
#if REGEX_DEBUG_MATCH
				std::cout << "matched\n";
#endif
				continue;
			}

			// Rollback?
			if (!m.rollback_points.empty())
			{
#if REGEX_DEBUG_MATCH
				std::cout << "did not match, rolling back\n";
#endif
				m.restoreRollback();
				if (reinterpret_cast<uintptr_t>(m.c) == 1)
				{
#if REGEX_DEBUG_MATCH
					std::cout << "rollback says we should succeed now\n";
#endif
					break;
				}
				continue;
			}

			// Oh well
#if REGEX_DEBUG_MATCH
			std::cout << "no matchy\n";
#endif
			return {};
		}

		// Handle match of regex without capturing groups
		SOUP_IF_UNLIKELY (!m.result.isSuccess())
		{
			m.result.groups.emplace_back(RegexMatchedGroup{ {}, match_begin, m.it });
		}

		SOUP_ASSERT(m.checkpoints.empty()); // if we made a checkpoint for a lookahead group, it should have been restored.

		SOUP_MOVE_RETURN(m.result);
	}

	RegexMatchResult Regex::search(const std::string& str) const noexcept
	{
		return search(str.data(), &str.data()[str.size()]);
	}

	RegexMatchResult Regex::search(const char* it, const char* end) const noexcept
	{
		RegexMatcher m(*this, it, end);
		for (; it != end; ++it)
		{
#if REGEX_DEBUG_MATCH
			std::cout << "--- Attempting match with " << std::distance(m.begin, it) << " byte offset ---\r\n";
#endif
			auto res = match(m, it);
			if (res.isSuccess())
			{
				return res;
			}
			m.reset(*this);
		}
		return {};
	}

	void Regex::replaceAll(std::string& str, const std::string& replacement) const
	{
		RegexMatchResult match;
		while (match = search(str), match.isSuccess())
		{
			const size_t offset = (match.groups.at(0).value().begin - str.data());
			str.erase(offset, match.length());
			str.insert(offset, replacement);
		}
	}

	std::string Regex::unparseFlags(uint16_t flags)
	{
		std::string str{};
		if (flags & RE_MULTILINE)
		{
			str.push_back('m');
		}
		if (flags & RE_DOTALL)
		{
			str.push_back('s');
		}
		if (flags & RE_INSENSITIVE)
		{
			str.push_back('i');
		}
		if (flags & RE_UNICODE)
		{
			str.push_back('u');
		}
		if (flags & RE_UNGREEDY)
		{
			str.push_back('U');
		}
		if (flags & RE_DOLLAR_ENDONLY)
		{
			str.push_back('D');
		}
		if (flags & RE_EXPLICIT_CAPTURE)
		{
			str.push_back('n');
		}
		return str;
	}

	[[nodiscard]] static std::string node_to_graphviz_dot_string(const RegexConstraint* node)
	{
		std::stringstream ss;
		if (auto str = node->toString(); !str.empty())
		{
			ss << std::move(str);
		}
		else
		{
			ss << "dummy";
		}
		ss << " (";
		ss << (void*)node;
		ss << ')';

		return string::escape(ss.str());
	}

	static void add_success_node(std::stringstream& ss, std::unordered_set<const RegexConstraint*>& mapped_nodes)
	{
		if (mapped_nodes.count(reinterpret_cast<const RegexConstraint*>(1)) == 0)
		{
			mapped_nodes.emplace(reinterpret_cast<const RegexConstraint*>(1));
			ss << R"("success" [shape="diamond"];)" << '\n';
		}
	}

	static void add_fail_node(std::stringstream& ss, std::unordered_set<const RegexConstraint*>& mapped_nodes)
	{
		if (mapped_nodes.count(reinterpret_cast<const RegexConstraint*>(2)) == 0)
		{
			mapped_nodes.emplace(reinterpret_cast<const RegexConstraint*>(2));
			ss << R"("fail" [shape="diamond"];)" << '\n';
		}
	}

	static void node_to_graphviz_dot(std::stringstream& ss, std::unordered_set<const RegexConstraint*>& mapped_nodes, const RegexConstraint* node)
	{
		if (mapped_nodes.count(node) != 0)
		{
			return;
		}
		mapped_nodes.emplace(node);

		ss << node_to_graphviz_dot_string(node);
		ss << R"( [shape="rect"];)";
		ss << '\n';

		if (reinterpret_cast<uintptr_t>(node->success_transition) > 0b10)
		{
			const auto success_transition = reinterpret_cast<const RegexConstraint*>(reinterpret_cast<uintptr_t>(node->success_transition) & ~1);

			node_to_graphviz_dot(ss, mapped_nodes, success_transition);

			ss << node_to_graphviz_dot_string(node);
			ss << " -> ";
			ss << node_to_graphviz_dot_string(success_transition);
			ss << R"( [label="success"];)";
			ss << '\n';
		}
		else if (reinterpret_cast<uintptr_t>(node->success_transition) == 0b10)
		{
			add_fail_node(ss, mapped_nodes);

			ss << node_to_graphviz_dot_string(node);
			ss << " -> ";
			ss << R"("fail")";
			ss << R"( [label="success"];)";
			ss << '\n';
		}
		else
		{
			add_success_node(ss, mapped_nodes);

			ss << node_to_graphviz_dot_string(node);
			ss << " -> ";
			ss << R"("success")";
			ss << R"( [label="success"];)";
			ss << '\n';
		}

		if (node->rollback_transition)
		{
			if (reinterpret_cast<uintptr_t>(node->rollback_transition) > 1)
			{
				node_to_graphviz_dot(ss, mapped_nodes, node->rollback_transition);

				ss << node_to_graphviz_dot_string(node);
				ss << " -> ";
				ss << node_to_graphviz_dot_string(node->rollback_transition);
				ss << R"( [label="rollback"];)";
				ss << '\n';
			}
			else
			{
				add_success_node(ss, mapped_nodes);

				ss << node_to_graphviz_dot_string(node);
				ss << " -> ";
				ss << R"("success")";
				ss << R"( [label="rollback"];)";
				ss << '\n';
			}
		}
	}

	std::string Regex::toGraphvizDot() const SOUP_EXCAL
	{
		std::stringstream ss;
		std::unordered_set<const RegexConstraint*> mapped_nodes{};

		ss << "digraph {\n";
		ss << "label=" << string::escape(toFullString()) << ";\n";
		node_to_graphviz_dot(ss, mapped_nodes, reinterpret_cast<const RegexConstraint*>(reinterpret_cast<uintptr_t>(group.initial) & ~1));
		ss << '}';

		return ss.str();
	}
}
