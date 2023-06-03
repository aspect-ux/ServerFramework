#include "../aspect/log.hpp"
#include <iostream>
#include <thread>


int main(int argc,char** argv)
{
	//logger日志器
	aspect::Logger::ptr logger(new aspect::Logger);
	/*
	//添加日志标准输出地appender
	logger->addAppender(aspect::LogAppender::ptr(new aspect::StdoutLogAppender));

	//添加文件日志输出地appender
	aspect::FileLogAppender::ptr file_appender(new aspect::FileLogAppender("./log.txt"));
	//添加日志格式器logFormatter
	aspect::LogFormatter::ptr fmt(new aspect::LogFormatter("%d%T%p%T%m%n"));
	file_appender->setFormatter(fmt);
	file_appender->setLevel(aspect::LogLevel::ERROR);
	//为日志器添加文件日志输出地
	logger->addAppender(file_appender);

	//__FILE__和__LINE__是宏，分别表示当前文件名和当前程序行数(十进制）
	//aspect::LogEvent::ptr event(new aspect::LogEvent(__FILE__, __LINE__, 0, std::this_thread()::get_id(), 2,time(0)));


	//ASPECT_LOG_INFO(logger) << "test macro";
	//ASPECT_LOG_ERROR(logger) << "test macro error";

	//SASPECT_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

	//auto l = aspect::LoggerMgr::GetInstance()->getLogger("xx");
	//ASPECT_LOG_INFO(l) << "xxx";
	*/
	std::cout << "hello aspect log" << std::endl;
	system("pause:");
	return 0;
}
