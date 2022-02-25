#include <string>
#include <iostream>
#include <string_view>
#include "Time.h"
#include "MyAir/MyAir.h"
#include <format>
#include <yaml-cpp/yaml.h>
#include "Config.h"
#include "Application.h"
#include "include/CommandLine.hpp"

std::string getInput(const std::string& message, const std::string& prompt)
{
	char word[100];
	std::cout << message << std::endl;
	std::cout << prompt;
	std::cin.getline(word, 100);
	return std::string(word);	
}

int main(int argc, char** argv)
{
	// This variables can be set via the command line.
	std::string hostAddress = "";	
	std::string airCon = "";
	int32_t port = 0;
	std::string zone = "";
	std::string startTime = "";
	std::string endTime = "";
	bool overrides = false;
	bool printHelp = false;


	// First configure all possible command line options.
	CommandLine args("MyAirController remote control program.");
	args.addArgument({ "-h", "--host" }, &hostAddress, "Host address");
	args.addArgument({ "-p", "--port" }, &port, "Port to connect to");
	args.addArgument({ "-a", "--aircon" }, &airCon, "Aircon name (e.g. ac1)");
	args.addArgument({ "-z", "--zone" }, &zone, "Zone to control");
	args.addArgument({ "-s", "--start" }, &startTime, "Start Time");
	args.addArgument({ "-e", "--end" }, &endTime, "End Time");
	args.addArgument({ "-h", "--help" }, &printHelp,
		"If no arguments are provided, they are loaded from the config.yaml file. If options are not set you will be prompted.");
	
	
	// Then do the actual parsing.
	try {
		args.parse(argc, argv);
	}
	catch (std::runtime_error const& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}


	// Load file

	using namespace MyAirController;
	Application app;

	app.LoadConfig("config.yaml");
	Config c = app.GetConfig();
	
	// Set any overrides
	if (!hostAddress.empty())
	{
		c.Address = hostAddress;
		overrides = true;
	}

	if (!zone.empty())
	{
		c.Zone = zone;
		overrides = true;
	}

	if (!airCon.empty())
	{
		c.Aircon = airCon;
		overrides = true;
	}

	if (port != 0)
	{
		c.Port = port;
		overrides = true;
	}

	if (!startTime.empty())
	{
		c.StartTime = { startTime };
		overrides = true;
	}

	if (!endTime.empty())
	{
		c.EndTime = { endTime };
		overrides = true;
	}

	
	if (c.Address.empty())	
	{
		c.Address = getInput("ERROR: Host address not provided", "Address: ");
		overrides = true;
	}

	if (c.Zone.empty())
	{
		c.Zone = getInput("ERROR: Zone name not provided", "Zone: ");
		overrides = true;
	}

	if (c.Aircon.empty())
	{
		c.Aircon = getInput("ERROR: Aircon name not provided", "Aircon: ");
		overrides = true;
	}

	if (c.Port == 0)
	{
		c.Port = std::stoi(getInput("ERROR: Port not provided", "Port: "));
		overrides = true;
	}

	if (c.DesiredTemperature == 0)
	{
		c.DesiredTemperature = std::stoi(getInput("ERROR: Desired Temperature is invalid", "SetTemp: "));
		overrides = true;
	}

	if (((std::string)c.StartTime).empty())
	{
		c.StartTime = { getInput("ERROR: Start time", "StartTime: ") };
		overrides = true;
	}

	if (((std::string)c.EndTime).empty())
	{
		c.EndTime = { getInput("ERROR: End time", "EndTime: ") };
		overrides = true;
	}
		
	if (overrides)
	{
		std::cout << "Settings have been changed, saving in config.yaml" << std::endl;
		app.SetConfig(c);
		app.SaveConfig("config.yaml");
	}


	if (printHelp) {
		args.printHelp();
		return 0;
	}

	// Print the resulting values.	
	app.Run();


	return 0;
}