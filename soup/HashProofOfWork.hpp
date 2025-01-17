#pragma once

#include <cstdint>
#include <string>

#include "base.hpp"

NAMESPACE_SOUP
{
	// Appropriate difficulty for this method is around 5.

	// The id can be a random string but must be unique & generated by a trusted party for this to have any sort of security.
	// Even better if the id is bound to a particular client and time-limited so they can't be stockpiled.

	template <typename CryptoHashAlgo = sha1>
	class HashProofOfWork
	{
	public:
		[[nodiscard]] static std::string solve(uint8_t difficulty, const std::string& id)
		{
			std::string str = id;
			str.push_back('.');
			auto solution_offset = str.size();
			str.append(14, 'a');
			do
			{
				for (auto i = solution_offset; i != str.size(); ++i)
				{
					str[i] = rand.t<int8_t>(65, 122);
				}
			} while (!isGoodStr(str, difficulty));
			return str.substr(solution_offset);
		}

		[[nodiscard]] static bool verify(uint8_t difficulty, const std::string& id, const std::string& solution)
		{
			std::string str = id;
			str.push_back('.');
			str.append(solution);
			return solution.size() == 14
				&& isGoodStr(str, difficulty)
				;
		}

	private:
		[[nodiscard]] static bool isGoodStr(const std::string& str, uint8_t difficulty)
		{
			for (const auto& c : CryptoHashAlgo::hash(str))
			{
				if (c == 0)
				{
					if (difficulty <= 2)
					{
						return true;
					}
					difficulty -= 2;
					continue;
				}
				if ((c >> 4) == 0
					&& difficulty == 1
					)
				{
					return true;
				}
				break;
			}
			return false;
		}
	};
}
