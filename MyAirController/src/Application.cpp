#include "Application.h"

#include <iostream>
#include "Time.h"
#include "MyAir/MyAir.h"

namespace YAML {

	template<>
	struct convert<Time>
	{
		static Node encode(const Time& rhs)
		{
			Node node;
			node.push_back(rhs.GetHours());
			node.push_back(rhs.GetMinutes());
			node.push_back(rhs.GetSeconds());
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Time& rhs)
		{
			if (!node.IsSequence() || node.size() < 2 )
				return false;

			rhs.SetHours(node[0].as<int>());
			rhs.SetMinutes(node[1].as<int>());
			if (node.size() == 3)
				rhs.SetSeconds(node[2].as<float>());
			else
				rhs.SetSeconds(0);
			
			return true;
		}
	};

}



namespace MyAirController {


	void Application::Run()
	{

		MyAir::Application app(m_Config.Address, m_Config.Port, m_Config.Aircon);
		
		if (app.IsSystemOn() && IsOperatingHours())
		{
			if (!app.IsMyZone(m_Config.Zone))
				app.SetMyZone(m_Config.Zone);

			if (app.IsTempOutOfRange(m_Config.Zone, m_Config.DesiredTemperature))
				app.SetZoneTemperature(m_Config.Zone, m_Config.DesiredTemperature);

		}
	}

	void Application::LoadConfig(const std::string& filepath)
	{
		YAML::Node data;		

		try
		{
			data = YAML::LoadFile(filepath);
		}
		catch(...)
		{
			std::cout << "ERROR: " << filepath << " not found, or invalid" << std::endl;			
		}

		try
		{
			m_Config.Address = data["Address"].as<std::string>();
			m_Config.Aircon = data["Aircon"].as<std::string>();
			m_Config.Zone = data["Zone"].as<std::string>();
			m_Config.Port = data["Port"].as<int>();
			m_Config.DesiredTemperature = data["DesiredTemp"].as<int>();
			m_Config.StartTime = { data["StartTime"].as<Time>() };
			m_Config.EndTime = { data["EndTime"].as<Time>() };
		}
		catch (...)
		{
			std::cout << "ERROR: Something is invalid in your " << filepath << " file" << std::endl;			
		}
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Time& t)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << t.GetHours() << t.GetMinutes() << t.GetSeconds() << YAML::EndSeq;
		return out;
	}

	void Application::SaveConfig(const std::string& filepath)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Address" << YAML::Value << m_Config.Address;
		out << YAML::Key << "Aircon" << YAML::Value << m_Config.Aircon;
		out << YAML::Key << "Zone" << YAML::Value << m_Config.Zone;
		out << YAML::Key << "Port" << YAML::Value << m_Config.Port;
		out << YAML::Key << "DesiredTemp" << YAML::Value << m_Config.DesiredTemperature;
		out << YAML::Key << "StartTime" << YAML::Value << m_Config.StartTime;
		out << YAML::Key << "EndTime" << YAML::Value << m_Config.EndTime;
		out << YAML::EndMap;

		try
		{
			std::ofstream fout(filepath);
			fout << out.c_str();
		}
		catch (...)
		{
			std::cout << "ERROR: Error saving config file " << filepath << std::endl;
		}
	}

}
