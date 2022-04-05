#pragma once

#include <vector>

#include "base.hpp"

#if SOUP_WINDOWS
#include <WinSock2.h>
#else
#include <poll.h>
#endif

#include "unique_ptr.hpp"
#include "worker.hpp"

namespace soup
{
	class scheduler
	{
	public:
		std::vector<unique_ptr<worker>> workers{};

		using on_work_done_t = void(*)(worker&);
		using on_connection_lost_t = void(*)(socket&);
		using on_exception_t = void(*)(worker&, const std::exception&);

		on_work_done_t on_work_done = nullptr;
		on_connection_lost_t on_connection_lost = nullptr;
		on_exception_t on_exception = nullptr;

		socket& addSocket(unique_ptr<socket>&& sock) noexcept;
		socket& addSocket(socket&& sock) noexcept;

		void run();
	protected:
		int poll(std::vector<pollfd>& pollfds, int timeout = -1);
		void processPollResults(std::vector<pollfd>& pollfds);
		void fireHoldupCallback(worker& w);
	};
}
