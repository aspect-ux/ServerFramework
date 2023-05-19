#include "log.hpp"

namespace sylar {
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
		// 另一种写法，用宏直接替换
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
		return "UNKNOWN"
	}
	// logger
	Logger::Logger(const std::string& name = "root")
		:m_name(name) 
	{};

	void Logger::addAppender(LogAppender::ptr appender) {
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

	void Logger::Log(LogLevel::Level level, const LogEvent& event){
	if (level > m_level)
		for (auto i : m_appenders)
		{
			i->Log(level, event);
		}
	}

	void Logger::debug(LogEvent::ptr event) {
		debug(LogLevel::DEBUG, event);
	}
	void Logger::info(LogEvent::ptr event) {
		debug(LogLevel::INFO, event);
	}
	void Logger::warn(LogEvent::ptr event) {
		debug(LogLevel::WARN, event);
	}
	void Logger::error(LogEvent::ptr event) {
		debug(LogLevel::EFFOR, event);
	}
	void Logger::fatal(LogEvent::ptr event) {
		debug(LogLevel::FATAL, event);
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
		return !!m_filestream; // !!操作后，0依旧是0，其他都为1
	}
	void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
		m_filestream << m_formatter->format(event);
	}


	void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
		std::cout << m_formatter->format(event);
	}
	
	//formatter
	LogFormatter::LogFormatter(const std::string& pattern) :m_pattern(pattern){}

	std::string LogFormatter::format(LogEvent::ptr event) {

	}

	void LogFormatter::init(){
		std::vector<std::tuple<std::string, std::string, int>> vec;
		std::string nstr;
		for (size_t i = 0; i < m_pattern.size(); ++i) //size_t适应不同系统，无符整形，并且表示范围最大的类型
		{
			if (m_pattern[i] != '%')
			{
				nstr.append(1, m_pattern[i]);
				continue;
			}
			size_t n = i + 1;
			int fmt_status = 0;
			size_t fmt_begin = 0;

			std::string str;
			std::string fmt;
			while (n < m_pattern.size())
			{
				if (isspace(m_pattern[n])) {
					break;
				}
				if (fmt_status == 0) {
					if (m_pattern[n] == '(') {
						str = m_pattern.substr(i + 1, n - i - 1);
						fmt_status = 1; //解析格式
						++n;
						fmt_begin = n;
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
			}


			if (fmt_status == 0)
			{
				if (!nstr.empty()) {
					vec.push_back(std::make_pair(nstr, "", 0));
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
					vec.push_back(std::make_pair(nstr, "", 0));
				}
				vec.push_back(std::make_tuple(str, fmt, 1));
				i = n;
			}
		}
		if (!nstr.empty()) {
			vec.push_back(std::make_pair(nstr, "", 0));
		}
	}

	std::string LogFormatter::format(LogLevel::Level level,LogEvent::ptr event)
	{
		std::stringstream ss;
		for (auto& i : m_item)
		{
			i->format(ss,level, event);
		}
		return ss.str();
	}

	class MessageFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, LogLevel::Level level, LogEvent::ptr event)override {
			os << event->getConent();
		}
	};
	class LevelFormatItem : public LogFormatter::FormatItem {
	public:
		void format(std::ostream& os, LogLevel::Level level,LogEvent::ptr event)override {
			os << LogLevel::ToString(level);
		}
	};

}