#include <string>
#include <iostream>
#include "Time.h"
#include "MyAir.h"

void main()
{
	std::string address = "10.0.0.69";
	uint32_t port = 2025;
	std::string zone = "Deanne";
	std::string aircon = "ac1";
	Time t1("07:00"), t2("21:00"), now("now");
	uint32_t desiredTemp = 23;

	MyAir::Application app(address, port, aircon);

	std::cout << "Testing Connection: " << app.TestConnection().c_str() << std::endl;
}