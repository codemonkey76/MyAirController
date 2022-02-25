#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <format>

class Time
{
	public:
		Time() = default;
		Time(const std::string& time);
		bool operator==(const Time& other);
		bool operator!=(const Time& other);

		bool operator<(const Time& other);
		bool operator>(const Time& other);
		std::ostream& operator<< (std::ostream& stream);
		operator std::string() const;

		const int GetHours() const { return m_Hours; }
		const int GetMinutes() const { return m_Minutes; }
		const int GetSeconds() const { return m_Seconds; }
		void SetHours(int hours) { m_Hours = hours; }
		void SetMinutes(int minutes) { m_Minutes = minutes; }
		void SetSeconds(int seconds) { m_Seconds = seconds; }

		
	private:
		std::vector<int> GetTokens(std::string str, const std::string& delim = ":");
	private:
		int m_Hours = 0;
		int m_Minutes = 0;
		int m_Seconds = 0;
};