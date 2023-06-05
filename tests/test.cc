#include "../aspect/log.h"
#include <iostream>
#include <thread>
#include <pthread.h>

int main(int argc,char** argv)
{
	
	//logger��־��
	aspect::Logger::ptr logger(new aspect::Logger);
	
	//�����־��׼�����appender
	logger->addAppender(aspect::LogAppender::ptr(new aspect::StdoutLogAppender));
	//����ļ���־�����appender
	aspect::FileLogAppender::ptr file_appender(new aspect::FileLogAppender("./log.txt"));

	//�����־��ʽ��logFormatter
	aspect::LogFormatter::ptr fmt(new aspect::LogFormatter("%d%T%p%T%m%n"));

	file_appender->setFormatter(fmt);
	file_appender->setLevel(aspect::LogLevel::UNKNOWN);

	//Ϊ��־������ļ���־�����
	logger->addAppender(file_appender);

	//__FILE__��__LINE__�Ǻ꣬�ֱ��ʾ��ǰ�ļ����͵�ǰ��������(ʮ���ƣ�

	ASPECT_LOG_ERROR(logger) << "test macro error";

	//ASPECT_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

	auto l = aspect::LoggerMgr::GetInstance()->getLogger("xx");
	ASPECT_LOG_INFO(l) << "xxx";
	
	std::cout << "hello aspect log" << std::endl;

	return 0;
}
