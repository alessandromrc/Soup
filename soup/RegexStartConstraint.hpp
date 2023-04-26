#pragma once

#include "RegexConstraintTransitionable.hpp"

#include "RegexMatcher.hpp"

namespace soup
{
	template <bool multi_line>
	struct RegexStartConstraint : public RegexConstraintTransitionable
	{
		[[nodiscard]] bool matches(RegexMatcher& m) const noexcept final
		{
			if (m.it == m.begin)
			{
				return true;
			}
			if constexpr (multi_line)
			{
				if (*(m.it - 1) == '\n')
				{
					return true;
				}
			}
			return false;
		}

		[[nodiscard]] std::string toString() const noexcept final
		{
			return "^";
		}
	};
}