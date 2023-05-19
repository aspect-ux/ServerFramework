#ifndef __SYLAR_LOG_H
#define __SYLAR_LOG_H

#include <iostream>
#include <string >
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>

namespace sylar {

	// 日志事件
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr; //防止同一地址多次析构，导致指针悬空，更好释放指针资源
		LogEvent();

		const char* getFile() const { return m_file; }
		int32_t getLine() const { return m_line; }
		uint32_t getElapse() const { return m_elapse; }
		uint32_t getFiberId() const { return m_fiberId; }
		uint64_t getTime() const { return m_time; }
		std::string getConent() const { return m_content; }
	private:
		const char* m_file = nullptr; //文件名
		int32_t m_line = 0;			  //行号
		uint32_t m_elapse = 0;		  //程序到现在的毫秒数
		uint32_t m_threadId = 0;	  //线程id
		uint32_t m_fiberId = 0;		  //协程id
		uint64_t m_time = 0;		  //时间戳
		std::string m_content;        //消息
	};

	// 日志级别
	class LogLevel {
	public:
		enum Level {
			UNKNOWN = 0,
			DEBUG = 1,
			INFO = 2,
			WARN = 3,
			ERROR = 4,
			FATAL = 5
		};

		static const char* ToString(LogLevel::Level level);
	};


	//
	//
	

	// 日志格式器
	class LogFormatter {
	public:
		typedef std::shared_ptr<LogFormatter> ptr;
		std::string format(LogLevel::Level level,LogEvent::ptr event);
		LogFormatter(const std::string& pattern);
	public:
		class FormatItem
		{
		public:
			typedef std::shared_ptr<FormatItem> ptr;
			virtual ~FormatItem() {}
			virtual std::string format(std::ostream& os, LogLevel::Level level,LogEvent::ptr event) = 0;
		};

		void init();
	private:
		std::string m_pattern;
		std::vector<FormatItem::ptr> m_item;
	};
	// 日志输出地,日志输出集合
	class LogAppender
	{
	public:
		typedef std::shared_ptr<LogAppender> ptr;
		virtual ~LogAppender() {} //子类更好释放

		virtual void Log(LogLevel::Level level, LogEvent::ptr event) = 0; //纯虚函数

		LogFormatter::ptr getLevel() const { return m_formatter; }
		void setLevel(LogFormatter::ptr val) { m_formatter = val; }
	protected:
		LogLevel::Level m_level;
		LogFormatter::ptr m_formatter;
	};

	// 日志器
	class Logger {
	public:
		typedef std::shared_ptr<Logger> ptr;
		
		Logger(const std::string& name = "root");
		void Log(LogLevel::Level level, const LogEvent& event);

		void debug(LogEvent::ptr event);
		void info(LogEvent::ptr event);
		void warn(LogEvent::ptr event);
		void error(LogEvent::ptr event);
		void fatal(LogEvent::ptr event);

		void addAppender(LogAppender::ptr appender);
		void delAppender(LogAppender::ptr appender);
		LogLevel::Level getLevel() const { return m_level; }
		void setLevel(LogLevel::Level val) { m_level = val; }
	private:
		std::string m_name;						 //日志名称
		LogLevel::Level m_level;				 //日志级别
		std::list<LogAppender::ptr> m_appenders; //日志集合
	};

	// 输出到控制台
	class StdoutLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<StdoutLogAppender> ptr;
		virtual void log(LogLevel::Level level, LogEvent::ptr event);
	};
	// 输出到文件
	class FileLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<FileLogAppender> ptr;
		FileLogAppender(const std::string& filename);
		virtual void log(LogLevel::Level level, LogEvent::ptr event);

		bool reopen(); //重新打开文件，成功后返回true
	private:
		std::string m_filename;
		std::ofstream m_filestream;
	};
}
#endif