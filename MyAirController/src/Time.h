#pragma once
#include <string>
#include <vector>
#include <iostream>

class Time
{
	public:
		Time(const std::string& time);
		bool operator==(const Time& other);
		bool operator!=(const Time& other);

		bool operator<(const Time& other);
		bool operator>(const Time& other);
	private:
		std::vector<int> GetTokens(std::string str, const std::string& delim = ":");
	private:
		int m_Hours;
		int m_Minutes;
		int m_Seconds;
};