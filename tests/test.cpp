#include "../aspect/log.hpp"
#include <iostream>
#include <thread>


int main(int argc,char** argv)
{
	aspect::Logger::ptr logger(new aspect::Logger);
	logger->addAppender(aspect::LogAppender::ptr(new aspect::StdoutLogAppender));

	aspect::LogEvent::ptr event(new aspect::LogEvent(__FILE__, __LINE__, 0, std::this_thread().get, 2,time(0)));

	logger->Log(aspect::LogLevel::DEBUG, event);

	std::cout << "hello aspect log" << std::endl;
	system("pause:");
	return 0;
}
