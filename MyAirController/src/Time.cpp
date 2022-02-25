#include "Time.h"
#include <ctime>
#include <iostream>

Time::Time(const std::string& time)
{
	char buffer[32];
	errno_t errNum;
	struct tm newtime;
	__time64_t aclock;
	_time64(&aclock);
	_localtime64_s(&newtime, &aclock);
	
	if (!strcmp(time.c_str(), "now"))
	{
		m_Hours = newtime.tm_hour;
		m_Minutes = newtime.tm_min;
		m_Seconds = newtime.tm_sec;
	}
	else
	{
		auto tokens = GetTokens(time);
		
		switch (tokens.size())
		{
		case 3:
			m_Hours = tokens[0];
			m_Minutes = tokens[1];
			m_Seconds = tokens[2];
			break;
		case 2:
			m_Hours = tokens[0];
			m_Minutes = tokens[1];
			m_Seconds = 0;
			break;
		case 1:
			m_Hours = tokens[0];
			m_Minutes = 0;
			m_Seconds = 0;
			break;
		default:		
			m_Hours = 0;
			m_Minutes = 0;
			m_Seconds = 0;
			break;
		}
		
	}
	
}

bool Time::operator==(const Time& other)
{
	return this->m_Hours == other.m_Hours &&
		this->m_Minutes == other.m_Minutes &&
		this->m_Seconds == other.m_Seconds;
}

Time::operator std::string() const
{
	if (m_Hours == 0 && m_Minutes == 0 && m_Seconds == 0)
		return std::string();

	if (m_Seconds == 0)
		return std::format("{:02d}:{:02d}", m_Hours, m_Minutes);
	
	
	return std::format("{:02d}:{:02d}:{:02d}", m_Hours, m_Minutes, m_Seconds);
}

bool Time::operator!=(const Time& other)
{
	return !(*this == other);
}

bool Time::operator<(const Time& other)
{
	if (this->m_Hours < other.m_Hours ||
		(this->m_Hours == other.m_Hours) && (this->m_Minutes < other.m_Minutes) ||
		(this->m_Hours == other.m_Hours) && (this->m_Minutes == other.m_Minutes) && (this->m_Seconds < other.m_Seconds))
		return true;
	return false;
}

bool Time::operator>(const Time& other)
{
	return !(*this < other);
}

std::ostream& Time::operator<<(std::ostream& stream)
{
	stream << std::format("{:02d}:{:02d}:{:02d}", this->m_Hours, this->m_Minutes, this->m_Seconds);
	
	return stream;
}

std::vector<int> Time::GetTokens(std::string str, const std::string& delim)
{
	std::vector<int> tokens;
	
	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delim)) != std::string::npos) {
		token = str.substr(0, pos);
		tokens.push_back(std::stoi(token));
		str.erase(0, pos + delim.length());
	}	
	tokens.push_back(std::stoi(str));
	
	return tokens;
}
