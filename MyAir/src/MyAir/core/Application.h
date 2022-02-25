#pragma once
#include <string>

namespace MyAir {

	class Application {
		public:
			Application(const std::string& address, uint32_t port, const std::string& aircon);

			std::string TestConnection();
			bool IsSystemOn();
			bool IsMyZone(const std::string& zone);
			bool IsTempOutOfRange(const std::string& zone, uint32_t desiredTemperature);			
			const std::string GetMyZone();
			void SetMyZone(const std::string& zone);
			uint32_t GetZoneTemperature(const std::string& zone);
			void SetZoneTemperature(const std::string& zone, uint32_t temperature);

		private:
			std::string GetSystemData();

		private:
			std::string m_BaseUrl;
			std::string m_Aircon;
	};
}