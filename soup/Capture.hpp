#pragma once

#include <type_traits>
#include <utility> // move

#include "deleter_impl.hpp"

namespace soup
{
	class Capture
	{
	protected:
		void* data = nullptr;
		deleter_t deleter = nullptr;

	public:
		Capture() noexcept = default;

		Capture(const Capture&) = delete;

		Capture(Capture&& b) noexcept
			: data(b.data), deleter(b.deleter)
		{
			b.data = nullptr;
		}

		template <typename T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, int> = 0>
		Capture(const T& v)
			: data(new std::remove_reference_t<T>(v)), deleter(&deleter_impl<std::remove_reference_t<T>>)
		{
		}

		template <typename T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, int> = 0>
		Capture(T&& v)
			: data(new std::remove_reference_t<T>(std::move(v))), deleter(&deleter_impl<std::remove_reference_t<T>>)
		{
		}

		template <typename T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, int> = 0>
		Capture(T v)
			: data(const_cast<void*>(static_cast<const void*>(v)))
		{
		}

		~Capture()
		{
			reset();
		}

		void reset() noexcept
		{
			if (deleter != nullptr)
			{
				deleter(data);
			}
			data = nullptr;
			deleter = nullptr;
		}

		void operator =(const Capture&) = delete;

		void operator =(Capture&& b) noexcept
		{
			reset();
			data = b.data;
			deleter = b.deleter;
			b.data = nullptr;
		}

		template <typename T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, int> = 0>
		void operator =(const T& v)
		{
			reset();
			data = new std::remove_reference_t<T>(v);
			deleter = &deleter_impl<std::remove_reference_t<T>>;
		}

		template <typename T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, int> = 0>
		void operator =(T&& v)
		{
			reset();
			data = new std::remove_reference_t<T>(std::move(v));
			deleter = &deleter_impl<std::remove_reference_t<T>>;
		}

		template <typename T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, int> = 0>
		void operator =(T v)
		{
			reset();
			data = v;
			deleter = nullptr;
		}

		[[nodiscard]] operator bool() const noexcept
		{
			return data != nullptr;
		}

		template <typename T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, int> = 0>
		[[nodiscard]] T& get() const noexcept
		{
			return *reinterpret_cast<T*>(data);
		}

		template <typename T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, int> = 0>
		[[nodiscard]] T get() const noexcept
		{
			return reinterpret_cast<T>(data);
		}
	};
}
