#include "myairpch.h"

#include "Application.h"
#include "Http.h"
#include <json.hpp>
using json = nlohmann::json;

namespace MyAir {
	Application::Application(const std::string& address, uint32_t port, const std::string& aircon)
		: m_Aircon(aircon)
	{
		m_BaseUrl = std::format("http://{}:{}/", address, std::to_string(port));
	}
	std::string Application::TestConnection()
	{
		return Http::Get(m_BaseUrl);
	}
	bool Application::IsSystemOn()
	{
		json jsonResult = json::parse(GetSystemData());
		std::string status = jsonResult["aircons"][m_Aircon]["info"]["state"];

		return !strcmp(status.c_str(), "on");
	}

	bool Application::IsTempOutOfRange(const std::string& zone, uint32_t desiredTemperature)
	{
		uint32_t currentSetTemp = GetZoneTemperature(zone);		
		return (currentSetTemp > desiredTemperature);
	}
	

	bool Application::IsMyZone(const std::string& zone)
	{
		return !strcmp(this->GetMyZone().c_str(), zone.c_str());		
	}

	const std::string Application::GetMyZone()
	{
		json jsonResult = json::parse(GetSystemData());
		auto aircon = jsonResult["aircons"][m_Aircon];

		int myZone = aircon["info"]["myZone"];
		std::string zoneKey = std::format("z{:02d}", myZone);
		
		return aircon["zones"][zoneKey]["name"];
	}
	void Application::SetMyZone(const std::string& zone)
	{
		std::cout << "SetMyZone: Not Yet Implemented." << std::endl;
	}
	uint32_t Application::GetZoneTemperature(const std::string& zone)
	{
		json jsonResult = json::parse(GetSystemData());
		auto zones = jsonResult["aircons"][m_Aircon]["zones"];
		for (auto& el : zones.items())
		{
			if (!strcmp(zone.c_str(), ((std::string)el.value()["name"]).c_str()))
				return el.value()["setTemp"];
		}

		return -1;
	}
	void Application::SetZoneTemperature(const std::string& zone, uint32_t temperature)
	{
		std::cout << "SetZoneTemperature: Not Yet Implemented." << std::endl;
	}
	std::string Application::GetSystemData()
	{
		return Http::Get(std::format("{}getSystemData", m_BaseUrl));
	}
}
