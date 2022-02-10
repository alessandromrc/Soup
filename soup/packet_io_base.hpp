#pragma once

#include <bit>
#include <cstdint>

namespace soup
{
	template <typename T>
	struct packet_io_base
	{
		[[nodiscard]] bool b(bool& v)
		{
			return reinterpret_cast<T*>(this)->u8(*(uint8_t*)&v);
		}

		[[nodiscard]] bool u16(uint16_t& v)
		{
			if constexpr (std::endian::native == std::endian::little)
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0]);
			}
			else
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1]);
			}
		}

		[[nodiscard]] bool u24(uint32_t& v)
		{
			if constexpr (std::endian::native == std::endian::little)
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0]);
			}
			else
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2]);
			}
		}
		
		[[nodiscard]] bool u32(uint32_t& v)
		{
			if constexpr (std::endian::native == std::endian::little)
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0]);
			}
			else
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3]);
			}
		}

		[[nodiscard]] bool u40(uint64_t& v)
		{
			if constexpr (std::endian::native == std::endian::little)
				{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[4])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0]);
			}
			else
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[4]);
			}
		}
		
		[[nodiscard]] bool u48(uint64_t& v)
		{
			if constexpr (std::endian::native == std::endian::little)
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[5])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[4])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0]);
			}
			else
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[4])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[5]);
			}
		}

		[[nodiscard]] bool u56(uint64_t& v)
		{
			if constexpr (std::endian::native == std::endian::little)
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[6])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[5])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[4])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0]);
			}
			else
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[4])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[5])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[6]);
			}
		}

		[[nodiscard]] bool u64(uint64_t& v)
		{
			if constexpr (std::endian::native == std::endian::little)
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[7])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[6])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[5])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[4])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0]);
			}
			else
			{
				return reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[0])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[1])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[2])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[3])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[4])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[5])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[6])
					&& reinterpret_cast<T*>(this)->u8(((uint8_t*)&v)[7]);
			}
		}

		[[nodiscard]] bool i8(int8_t& v)
		{
			return reinterpret_cast<T*>(this)->u8(*(uint8_t*)&v);
		}

		[[nodiscard]] bool i16(int16_t& v)
		{
			return u16(*(uint16_t*)&v);
		}

		[[nodiscard]] bool i32(int32_t& v)
		{
			return u32(*(uint32_t*)&v);
		}

		[[nodiscard]] bool i64(int64_t& v)
		{
			return u64(*(uint64_t*)&v);
		}
	};
}
