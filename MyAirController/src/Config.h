#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Time.h"
#include <yaml-cpp/yaml.h>



namespace MyAirController {

	struct Config
	{	
		Config()
			: Address(""), Port(0), Aircon(""), Zone(""), DesiredTemperature(0) {}

		std::string Address;
		uint32_t Port;
		std::string Aircon;
		std::string Zone;
		Time StartTime;
		Time EndTime;
		uint32_t DesiredTemperature;
	};

	void Serialize(Config c, const std::string& filepath);
	Config Deserialize(const std::string& filepath);
}