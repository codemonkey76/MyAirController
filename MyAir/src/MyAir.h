#pragma once
#include <string>

namespace MyAir {

	class Application {
		public:
			Application(const std::string& address, uint32_t port, const std::string& aircon)
				: m_Address(address), m_Port(port), m_Aircon(aircon) {}

			std::string TestConnection();

		private:
			std::string m_Address;
			uint32_t m_Port;
			std::string m_Aircon;
	};
}