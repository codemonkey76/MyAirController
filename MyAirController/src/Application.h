#pragma once
#include "Config.h"
#include <string>
#include "Time.h"
namespace MyAirController
{
	class Application
	{
		public:
			void Run();
			void LoadConfig(const std::string& filepath);
			void SaveConfig(const std::string& filepath);

			Config GetConfig() { return m_Config; }
			void SetConfig(Config config) { m_Config = config; };

		private:
			bool IsOperatingHours() { return Time("now") < m_Config.StartTime || Time("now") > m_Config.EndTime; }
		private:
			Config m_Config;

	};

}