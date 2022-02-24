#pragma once

namespace MyAir {

	class Http
	{
		public:
			static const std::string Get(const std::string& url);

		private:
			static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param);
		
	};
}
