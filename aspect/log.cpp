#include "log.hpp"
#include <map>
#include <tuple>
#include <functional>
#include <utility>

namespace aspect {
	const char* LogLevel::ToString(LogLevel::Level level)
	{
		/*
		switch (level)
		{
		case sylar::LogLevel::DEBUG:
			break;
		case sylar::LogLevel::INFO:
			break;
		case sylar::LogLevel::WARN:
			break;
		case sylar::LogLevel::ERROR:
			break;
		case sylar::LogLevel::FATAL:
			break;
		default:
			break;
		}*/
		// ��һ��д�����ú�ֱ���滻
		switch (level)
		{
#define XX(name) \
			case LogLevel::name: \
				return #name; \
				break;

			XX(DEBUG);
			XX(INFO);
			XX(WARN);
			XX(ERROR);
			XX(FATAL);
#undef XX
		default:
			return "UNKNOWN";
		}
		return "UNKNOWN";
	}



	// FormatItems
	class MessageFormatItem : public LogFormatter::FormatItem {
	public:
		MessageFormatItem(const std::string str = "") {}
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getConent();
		}
	};

	class LevelFormatItem : public LogFormatter::FormatItem {
	public:
		LevelFormatItem(const std::string str = "") {}
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << LogLevel::ToString(level);
		}
	};

	class ElapseFormatItem : public LogFormatter::FormatItem {
	public:
		ElapseFormatItem(const std::string str = "") {}
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getElapse();
		}
	};
	class ThreadIdFormatItem : public LogFormatter::FormatItem {
	public:
		ThreadIdFormatItem(const std::string str = "") {}
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getThreadId();
		}
	};
	class FiberIdFormatItem : public LogFormatter::FormatItem {
	public:
		FiberIdFormatItem(const std::string str = "") {}
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
		FileNameFormatItem(const std::string str = "") {}
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getFile();
		}
	};
	class NewLineFormatItem : public LogFormatter::FormatItem {
	public:
		NewLineFormatItem(const std::string str = "") {}
		void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)override {
			os << std::endl;
		}
	};
	class LineFormatItem : public LogFormatter::FormatItem {
	public:
		LineFormatItem(const std::string str = "") {}
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
	class NameFormatItem : public LogFormatter::FormatItem {
	public:
		NameFormatItem(const std::string& str = "") {}
		void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
			os << event->getLogger()->getName();
		}
	};
	class TabFormatItem : public LogFormatter::FormatItem {
	public:
		TabFormatItem(const std::string& str = "") {}
		void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
			os << "\t";
		}
	private:
		std::string m_string;
	};
	class ThreadNameFormatItem : public LogFormatter::FormatItem {
	public:
		ThreadNameFormatItem(const std::string& str = "") {}
		void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
			os << event->getThreadName();
		}
	};


	//logEvent
	LogEventWrap::LogEventWrap(LogEvent::ptr e)
		:m_event(e) {
	}

	LogEventWrap::~LogEventWrap() {
		m_event->getLogger()->log(m_event->getLevel(), m_event);
	}
	LogEvent::LogEvent(const char* file, int32_t line, uint32_t elapse,
		uint32_t thread_id, uint32_t fiber_id, uint64_t time) :m_file(file),
		m_line(line), m_elapse(elapse), m_threadId(thread_id), m_fiberId(fiber_id), m_time(time)
	{}



	// logger
	Logger::Logger(const std::string& name)
		:m_name(name)
		, m_level(LogLevel::DEBUG) {
		m_formatter.reset(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));
	}

	void Logger::addAppender(LogAppender::ptr appender) {
		if (!appender->getFormatter())
		{
			appender->setFormatter(m_formatter);
		}
		m_appenders.push_back(appender);
	}
	void Logger::delAppender(LogAppender::ptr appender) {
		for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it)
		{
			if (*it != appender)
			{
				m_appenders.erase(it);
				break;
			}
		}
	}

	void Logger::Log(LogLevel::Level level, LogEvent::ptr event){
		if (level > m_level)
		{
			auto self = shared_from_this();
			for (auto i : m_appenders)
			{
				i->log(level,self, event);
			}
		}
	}

	void Logger::debug(LogEvent::ptr event) {
		Log(LogLevel::DEBUG, event);
	}
	void Logger::info(LogEvent::ptr event) {
		Log(LogLevel::INFO, event);
	}
	void Logger::warn(LogEvent::ptr event) {
		Log(LogLevel::WARN, event);
	}
	void Logger::error(LogEvent::ptr event) {
		Log(LogLevel::ERROR, event);
	}
	void Logger::fatal(LogEvent::ptr event) {
		Log(LogLevel::FATAL, event);
	}

	// appender
	FileLogAppender::FileLogAppender(const std::string& filename)
		:m_filename(filename)
	{

	}
	bool FileLogAppender::reopen()
	{
		if (m_filestream)
		{
			m_filestream.close();
		}
		m_filestream.open(m_filename);
		return !!m_filestream; // !!������0������0��������Ϊ1
	}
	void FileLogAppender::log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event) {
		m_filestream << m_formatter->format(level,logger,event);
	}
	void LogAppender::log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event) {
		std::cout << "std";
	}
	void StdoutLogAppender::log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event) {
		
		if (level >= m_level) {
			//MutexType::Lock lock(m_mutex);
			m_formatter->format(std::cout, logger, level, event);
		}
	}
	


	//formatter
	LogFormatter::LogFormatter(const std::string& pattern) :m_pattern(pattern){}

	std::string LogFormatter::format(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event) {
		std::stringstream ss;
		for (auto& i : m_items) {
			i->format(ss, logger, level, event);
		}
		return ss.str();
	}
	std::ostream& LogFormatter::format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
		for (auto& i : m_items) {
			i->format(ofs, logger, level, event);
		}
		return ofs;
	}

	void LogFormatter::init(){
		std::vector<std::tuple<std::string, std::string, int>> vec;
		std::string nstr;
		for (size_t i = 0; i < m_pattern.size(); ++i) //size_t��Ӧ��ͬϵͳ���޷����Σ����ұ�ʾ��Χ��������
		{
			if (m_pattern[i] != '%')
			{
				nstr.append(1, m_pattern[i]);
				continue;
			}

			if ((i + 1) < m_pattern.size()) {
				if (m_pattern[i + 1] == '%')
				{
					nstr.append(1, '%');
					continue;
				}
			}
			size_t n = i + 1;
			int fmt_status = 0;
			size_t fmt_begin = 0;

			std::string str;
			std::string fmt;
			while (n < m_pattern.size())
			{
				if (isalpha(m_pattern[n]) && m_pattern[n] != '{' && m_pattern[n] != '}') {
					break;
				}
				if (fmt_status == 0) {
					if (m_pattern[n] == '(') {
						str = m_pattern.substr(i + 1, n - i - 1);
						fmt_status = 1; //������ʽ
						fmt_begin = n;
						++n;
						continue;
					}
				}
				if (fmt_status == 1) {
					if (m_pattern[n] == '}') {
						fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
						fmt_status = 2;
						break;
					}
				}
				++n;
			}


			if (fmt_status == 0)
			{
				if (!nstr.empty()) {
					vec.push_back(std::make_tuple(nstr, "", 0));
					nstr.clear();
				}
				str = m_pattern.substr(i + 1, n - i - 1);
				vec.push_back(std::make_tuple(str, fmt, i));
				i = n;
			}
			else if (fmt_status == 1) {
				std::cout << "pattern parse error:" << m_pattern << " - " << m_pattern.substr(i) << std::endl;
				vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
			}
			else if (fmt_status == 2)
			{
				if (!nstr.empty()) {
					vec.push_back(std::make_tuple(nstr, "", 0));
					nstr.clear();
				}
				vec.push_back(std::make_tuple(str, fmt, 1));
				i = n;
			}
		}
		if (!nstr.empty()) {
			vec.push_back(std::make_tuple(nstr, "",0));
		}
		static std::map<std::string, std::function<FormatItem::ptr(const std::string str)>> s_format_items = {
#define XX(str,C) {#str, [](const std::string& fmt) { return FormatItem::ptr(new C(fmt)); } }

		XX(m, MessageFormatItem),           //m:��Ϣ
		XX(p, LevelFormatItem),             //p:��־����
		XX(r, ElapseFormatItem),            //r:�ۼƺ�����
		XX(c, NameFormatItem),              //c:��־����
		XX(t, ThreadIdFormatItem),          //t:�߳�id
		XX(n, NewLineFormatItem),           //n:����
		XX(d, DateTimeFormatItem),          //d:ʱ��
		XX(f, FileNameFormatItem),          //f:�ļ���
		XX(l, LineFormatItem),              //l:�к�
		XX(T, TabFormatItem),               //T:Tab
		XX(F, FiberIdFormatItem),           //F:Э��id
		XX(N, ThreadNameFormatItem),        //N:�߳�����
#undef XX
		};

		for (auto& i : vec) {
			if (std::get<2>(i) == 0)
			{
				m_items.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
			}
			else {
				auto it = s_format_items.find(std::get<0>(i));
				if (it == s_format_items.end()) {
					m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
				}
				else {
					m_items.push_back(it->second(std::get<1>(i)));
				}
			}
			std::cout << std::get<0>(i) << " - " << std::get<1>(i) << " - " << std::get<2>(i) << std::endl;
		}
			
		}

}