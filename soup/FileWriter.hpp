#pragma once

#include "Writer.hpp"

#include <filesystem>
#include <fstream>

#include "type_traits.hpp"

NAMESPACE_SOUP
{
	class FileWriter final : public Writer
	{
	public:
		std::ofstream s;

		FileWriter(const std::string& path, bool little_endian = true)
			: Writer(little_endian), s(path, std::ios::binary)
		{
		}

#if SOUP_WINDOWS && !SOUP_CROSS_COMPILE
		FileWriter(const std::wstring& path, bool little_endian = true)
			: Writer(little_endian), s(path, std::ios::binary)
		{
		}
#endif

		template <class T, SOUP_RESTRICT(std::is_same_v<T, std::filesystem::path>)>
		FileWriter(const T& path, bool little_endian = true)
			: Writer(little_endian), s(path, std::ios::binary)
		{
		}

		~FileWriter() final = default;

		bool raw(void* data, size_t size) noexcept final
		{
#if SOUP_EXCEPTIONS
			try
#endif
			{
				s.write(reinterpret_cast<char*>(data), size);
			}
#if SOUP_EXCEPTIONS
			catch (...)
			{
				return false;
			}
#endif
			return true;
		}
	};
}
