#include <string>
#include <iostream>
#include <string_view>
#include "Time.h"
#include "MyAir/MyAir.h"
#include <format>

void main()
{
	
	std::string address = "10.0.0.69";
	uint32_t port = 2025;
	std::string zone = "Deanne";
	std::string aircon = "ac1";
	Time t1("07:00"), t2("18:00"), now("now");
	uint32_t desiredTemp = 23;

	MyAir::Application app(address, port, aircon);

	std::cout << "Testing Connection: " << app.TestConnection().c_str() << std::endl;

	if (!app.IsSystemOn())
	{
		std::cout << "Status: System is currently off" << std::endl;
	}
	
	else
	{
		std::cout << "Status: System is currently on" << std::endl;

		if (now > t2 || now < t1)
		{
			auto& myzone = app.GetMyZone();
			if (myzone != zone)
			{
				std::cout << "MyZone: " << myzone << std::endl;
				std::cout << "MyZone set incorrectly, setting: MyZone = " << zone << std::endl;
				app.SetMyZone(zone);
			}

			uint32_t setTemp = app.GetZoneTemperature(zone);
			if (setTemp > desiredTemp)
			{
				std::cout << "Zone: " << zone << " SetTemp: " << setTemp << std::endl;
				std::cout << "Temperature is set too high, setting: " << desiredTemp << std::endl;
				app.SetZoneTemperature(zone, desiredTemp);
			}

		}

	}
	

	std::cin.get();
}