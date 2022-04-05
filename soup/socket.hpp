#pragma once

#include "worker.hpp"

#include "base.hpp"
#include "fwd.hpp"

#if SOUP_WINDOWS
#pragma comment(lib, "Ws2_32.lib")
#include <Winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include "addr_socket.hpp"
#include "capture.hpp"
#include "socket_tls_encrypter.hpp"
#include "unique_ptr.hpp"

namespace soup
{
#pragma pack(push, 1)
	class socket : public worker
	{
	public:
#if SOUP_WINDOWS
		inline static size_t wsa_consumers = 0;
#endif

#if SOUP_WINDOWS
		using fd_t = ::SOCKET;
#else
		using fd_t = int;
#endif
		fd_t fd = -1;
		addr_socket peer;
		capture user_data;
		bool remote_closed = false;

		std::string tls_record_buf_data{};
		tls_content_type_t tls_record_buf_content_type;

		socket_tls_encrypter tls_encrypter_send;
		socket_tls_encrypter tls_encrypter_recv;

		socket() noexcept;

		socket(const socket&) = delete;

		socket(socket&& b) noexcept
		{
			onConstruct();
			operator =(std::move(b));
		}

	protected:
		void onConstruct() noexcept;

	public:
		~socket() noexcept;

		void operator =(const socket&) = delete;

		void operator =(socket&& b) noexcept;

		[[nodiscard]] constexpr bool hasConnection() const noexcept
		{
			return fd != -1;
		}

		bool init(int af);

		bool connect(const std::string& host, uint16_t port) noexcept; // blocking
		bool connect(const char* host, uint16_t port) noexcept; // blocking
		bool connect(const addr_socket& addr) noexcept; // blocking
		bool connect(const addr_ip& ip, uint16_t port) noexcept; // blocking

		template <typename T = int>
		bool setOpt(int name, T&& val) noexcept
		{
#if SOUP_WINDOWS
			return setsockopt(fd, SOL_SOCKET, name, (const char*)&val, sizeof(T)) != -1;
#else
			return setsockopt(fd, SOL_SOCKET, name, &val, sizeof(T)) != -1;
#endif
		}

		bool bind6(uint16_t port) noexcept;
		bool bind4(uint16_t port) noexcept;

		[[nodiscard]] socket accept6() noexcept;
		[[nodiscard]] socket accept4() noexcept;

		bool setBlocking(bool blocking = true) noexcept;
		bool setNonBlocking() noexcept;

		static bool trustAllCertchainsWithNoChecksWhatsoever_ThisIsNotAJoke_IfYouCareYouShouldLookIntoThis(const certchain&);

		void enableCryptoClient(std::string server_name, void(*callback)(socket&, capture&&), capture&& cap = {}, bool(*certchain_validator)(const certchain&) = &trustAllCertchainsWithNoChecksWhatsoever_ThisIsNotAJoke_IfYouCareYouShouldLookIntoThis);
	protected:
		void enableCryptoClientRecvServerHelloDone(unique_ptr<socket_tls_handshaker>&& handshaker);

	public:
		void enableCryptoServer(void(*cert_selector)(socket_tls_server_rsa_data& out, const std::string& server_name), void(*callback)(socket&, capture&&), capture&& cap = {}, void(*on_client_hello)(socket&, tls_client_hello&&) = nullptr);
	
		// Application Layer

		[[nodiscard]] bool isEncrypted() const noexcept;

		template <typename T>
		[[nodiscard]] T& getUserData() // Allows you to associate custom data with a socket. Note that all calls to getUserData on the same socket must use the same T.
		{
			if (!user_data)
			{
				user_data = T{};
			}
			return user_data.get<T>();
		}

		bool send(const std::string& data);

		void recv(void(*callback)(socket&, std::string&&, capture&&), capture&& cap = {});

		/*[[nodiscard]] std::string recvExact(int bytes) noexcept
		{
			std::string buf(bytes, 0);
			char* dp = buf.data();
			while (bytes != 0)
			{
				int read = bytes;
				if (!transport_recv(dp, read))
				{
					return {};
				}
				bytes -= read;
				dp += read;
			}
			return buf;
		}*/

		void close();

		// TLS - Crypto Layer

		bool tls_sendHandshake(const unique_ptr<socket_tls_handshaker>& handshaker, tls_handshake_type_t handshake_type, const std::string& content);
		bool tls_sendRecord(tls_content_type_t content_type, std::string content);

		void tls_recvHandshake(unique_ptr<socket_tls_handshaker>&& handshaker, tls_handshake_type_t expected_handshake_type, void(*callback)(socket&, unique_ptr<socket_tls_handshaker>&&, std::string&&), std::string&& pre = {});
		void tls_recvRecord(tls_content_type_t expected_content_type, void(*callback)(socket&, std::string&&, capture&&), capture&& cap = {});
		void tls_recvRecord(void(*callback)(socket&, tls_content_type_t, std::string&&, capture&&), capture&& cap = {});

		void tls_unrecv(tls_content_type_t content_type, std::string&& content) noexcept;

		void tls_close(tls_alert_description_t desc);

		// Transport Layer

		bool transport_send(const std::string& data) const noexcept;
		bool transport_send(const void* data, int size) const noexcept;

		using transport_recv_callback_t = void(*)(socket&, std::string&&, capture&&);

		[[nodiscard]] bool transport_hasData() const;

	protected:
		[[nodiscard]] std::string transport_recvCommon(int max_bytes);
	public:
		void transport_recv(int max_bytes, transport_recv_callback_t callback, capture&& cap = {});
		void transport_recvExact(int bytes, transport_recv_callback_t callback, capture&& cap = {}, std::string&& pre = {});

		void transport_close() noexcept;
	};
#pragma pack(pop)
}
