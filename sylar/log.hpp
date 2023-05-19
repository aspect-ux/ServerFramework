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
#include <functional>
#include <utility>

namespace aspect {

	class Logger;
	// ��־�¼�
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr; //��ֹͬһ��ַ�������������ָ�����գ������ͷ�ָ����Դ
		LogEvent();

		const char* getFile() const { return m_file; }
		int32_t getLine() const { return m_line; }
		uint32_t getElapse() const { return m_elapse; }
		uint32_t getThreadId() const { return m_threadId; }
		uint32_t getFiberId() const { return m_fiberId; }
		uint64_t getTime() const { return m_time; }
		std::string getConent() const { return m_content; }

	private:
		const char* m_file = nullptr; //�ļ���
		int32_t m_line = 0;			  //�к�
		uint32_t m_elapse = 0;		  //�������ڵĺ�����
		uint32_t m_threadId = 0;	  //�߳�id
		uint32_t m_fiberId = 0;		  //Э��id
		uint64_t m_time = 0;		  //ʱ���
		std::string m_content;        //��Ϣ
	};

	// ��־����
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
	

	// ��־��ʽ��
	class LogFormatter {
	public:
		typedef std::shared_ptr<LogFormatter> ptr;
		std::string format(LogLevel::Level level, std::shared_ptr<Logger> logger,LogEvent::ptr event);
		LogFormatter(const std::string& pattern);
	public:
		class FormatItem
		{
		public:
			FormatItem(const std::string fmt = "");
			typedef std::shared_ptr<FormatItem> ptr;
			virtual ~FormatItem() {}
			virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level,LogEvent::ptr event) = 0;
		};

		void init();
	private:
		std::string m_pattern;
		std::vector<FormatItem::ptr> m_items;
	};
	// ��־�����,��־�������
	class LogAppender
	{
	public:
		typedef std::shared_ptr<LogAppender> ptr;
		virtual ~LogAppender() {} //��������ͷ�

		virtual void Log(LogLevel::Level level, LogEvent::ptr event) = 0; //���麯��

		LogFormatter::ptr getLevel() const { return m_formatter; }
		void setLevel(LogFormatter::ptr val) { m_formatter = val; }
	protected:
		LogLevel::Level m_level;
		LogFormatter::ptr m_formatter;
	};

	// ��־��
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
		std::string getName()const { return m_name; }
	private:
		std::string m_name;						 //��־����
		LogLevel::Level m_level;				 //��־����
		std::list<LogAppender::ptr> m_appenders; //��־����
	};

	// ���������̨
	class StdoutLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<StdoutLogAppender> ptr;
		virtual void log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event);
	};
	// ������ļ�
	class FileLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<FileLogAppender> ptr;
		FileLogAppender(const std::string& filename);
		virtual void log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event);

		bool reopen(); //���´��ļ����ɹ��󷵻�true
	private:
		std::string m_filename;
		std::ofstream m_filestream;
	};

	// FormatItems
	class MessageFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getConent();
		}
	};

	class LevelFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << LogLevel::ToString(level);
		}
	};

	class ElapseFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getElapse();
		}
	};
	class ThreadIdFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getThreadId();
		}
	};
	class FiberIdFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getFiberId();
		}
	};
	class DateTimeFormatItem : public LogFormatter::FormatItem {
	public:
		DateTimeFormatItem(const std::string format = "%Y:%m:%d %H:%M:%S") :m_format(format) {}
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getTime();
		}
	private:
		std::string m_format;
	};
	class FileNameFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getFile();
		}
	};
	class NewLineFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << std::endl;
		}
	};
	class LineFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getLine();
		}
	};
	class StringFormatItem : public LogFormatter::FormatItem {
	public:
		StringFormatItem(const std::string str) :m_string(str) {}
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << m_string;
		}
	private:
		std::string m_string;
	};

}
#endif