#ifndef __ASPECT_LOG_H__
#define __ASPECT_LOG_H__

#include <iostream>
#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "singleton.h"
#include "util.h"

//宏不要放在命名空间中
/**
 * @brief 使用流式方式将日志级别level的日志写入到logger
 */
#define ASPECT_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        aspect::LogEventWrap(aspect::LogEvent::ptr(new aspect::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, aspect::GetThreadId(),\
                aspect::GetFiberId(), time(0), aspect::Thread::GetName()))).getSS()

	 /**
	  * @brief 使用流式方式将日志级别debug的日志写入到logger
	  */
#define ASPECT_LOG_DEBUG(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::DEBUG)

	  /**
	   * @brief 使用流式方式将日志级别info的日志写入到logger
	   */
#define ASPECT_LOG_INFO(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::INFO)

	   /**
		* @brief 使用流式方式将日志级别warn的日志写入到logger
		*/
#define ASPECT_LOG_WARN(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::WARN)

		/**
		 * @brief 使用流式方式将日志级别error的日志写入到logger
		 */
#define ASPECT_LOG_ERROR(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::ERROR)

		 /**
		  * @brief 使用流式方式将日志级别fatal的日志写入到logger
		  */
#define ASPECT_LOG_FATAL(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::FATAL)

/**
 * @brief 使用格式化方式将日志级别level的日志写入到logger
 */
#define ASPECT_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        aspect::LogEventWrap(aspect::LogEvent::ptr(new aspect::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, aspect::GetThreadId(),\
                aspect::GetFiberId(), time(0), aspect::Thread::GetName()))).getEvent()->format(fmt, __VA_ARGS__)

/**
* @brief 使用格式化方式将日志级别debug的日志写入到logger
*/
#define ASPECT_LOG_FMT_DEBUG(logger, fmt, ...) ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::DEBUG, fmt, __VA_ARGS__)

			/**
			 * @brief 使用格式化方式将日志级别info的日志写入到logger
			 */
#define ASPECT_LOG_FMT_INFO(logger, fmt, ...)  ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::INFO, fmt, __VA_ARGS__)

			 /**
			  * @brief 使用格式化方式将日志级别warn的日志写入到logger
			  */
#define ASPECT_LOG_FMT_WARN(logger, fmt, ...)  ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::WARN, fmt, __VA_ARGS__)

			  /**
			   * @brief 使用格式化方式将日志级别error的日志写入到logger
			   */
#define ASPECT_LOG_FMT_ERROR(logger, fmt, ...) ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::ERROR, fmt, __VA_ARGS__)

			   /**
				* @brief 使用格式化方式将日志级别fatal的日志写入到logger
				*/
#define ASPECT_LOG_FMT_FATAL(logger, fmt, ...) ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::FATAL, fmt, __VA_ARGS__)

				/**
				 * @brief 获取主日志器
				 */
				
#define ASPECT_LOG_ROOT() aspect::LoggerMgr::GetInstance()->getRoot()

				 /**
				  * @brief 获取name的日志器
				  */
#define ASPECT_LOG_NAME(name) aspect::LoggerMgr::GetInstance()->getLogger(name)


namespace aspect {

	class Logger;
	class LoggerManager;

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
		static LogLevel::Level FromString(const std::string& str);
	};

	// 日志事件
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr; //防止同一地址多次析构，导致指针悬空，更好释放指针资源
		LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
            ,const char* file, int32_t line, uint32_t elapse
            ,uint32_t thread_id, uint32_t fiber_id, uint64_t time
            ,const std::string& thread_name);

		const char* getFile() const { return m_file; }
		int32_t getLine() const { return m_line; }
		uint32_t getElapse() const { return m_elapse; }
		uint32_t getThreadId() const { return m_threadId; }
		uint32_t getFiberId() const { return m_fiberId; }
		uint64_t getTime() const { return m_time; }
		std::string getThreadName() const{ return m_threadName; }
		std::string getConent() const { return m_ss.str(); }

		std::shared_ptr<Logger> getLogger() const { return m_logger; } //返回日志器
		std::stringstream& getSS() { return m_ss; }
		LogLevel::Level getLevel() const { return m_level; }

	private:
		const char* m_file = nullptr; //文件名
		int32_t m_line = 0;			  //行号
		uint32_t m_elapse = 0;		  //程序到现在的毫秒数
		uint32_t m_threadId = 0;	  //线程id
		uint32_t m_fiberId = 0;		  //协程id
		uint64_t m_time = 0;		  //时间戳
		std::string m_threadName;     //线程名字
		std::stringstream m_ss;       //日志内容流

		std::shared_ptr<Logger> m_logger; //日志器
		LogLevel::Level m_level;          //日志等级
	};

	/**
	 * @brief 日志事件包装器
	 */
	class LogEventWrap {
	public:

		/**
		 * @brief 构造函数
		 * @param[in] e 日志事件
		 */
		LogEventWrap(LogEvent::ptr e);

		~LogEventWrap();
		/**
		 * @brief 获取日志事件
		 */
		LogEvent::ptr getEvent() const { return m_event; }
		/**
		 * @brief 获取日志内容流
		 */
		std::stringstream& getSS();
	private:
		/**
		 * @brief 日志事件
		 */
		LogEvent::ptr m_event;
	};
	

	// 日志格式器
	class LogFormatter {
	public:
		typedef std::shared_ptr<LogFormatter> ptr;
		std::string format(LogLevel::Level level, std::shared_ptr<Logger> logger,LogEvent::ptr event);
		std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
		LogFormatter(const std::string& pattern);
	public:
		class FormatItem
		{
		public:
			FormatItem(const std::string fmt = ""){}
			typedef std::shared_ptr<FormatItem> ptr;
			virtual ~FormatItem() {}
			virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level,LogEvent::ptr event) = 0;
		};

		void init();

		bool isError() const {return m_error;}

		/**
		 * @brief 返回日志模板
		 */
		const std::string getPattern() const { return m_pattern;}
	private:
		std::string m_pattern;
		std::vector<FormatItem::ptr> m_items;

		bool m_error = false;
	};
	// 日志输出地,日志输出集合
	class LogAppender
	{
	friend class Logger;
	public:
		typedef std::shared_ptr<LogAppender> ptr;
		//typedef Spinlock MutexType;

		virtual ~LogAppender() {} //子类更好释放
		virtual void log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event) = 0; //纯虚函数

		LogFormatter::ptr getFormatter() const { return m_formatter; }
		
		/**
		 * @brief 更改日志格式器
		 */
		void setFormatter(LogFormatter::ptr val);

		/**
		 * @brief 获取日志级别
		 */
		LogLevel::Level getLevel() const { return m_level; }

		/**
		 * @brief 设置日志级别
		 */
		void setLevel(LogLevel::Level val) { m_level = val; }

		virtual std::string toYamlString() = 0;
	protected:
		LogLevel::Level m_level = LogLevel::DEBUG;
		
		//是否有格式器
		bool m_hasFormatter = false;
		// Mutex
		//MutexType m_mutex;
		LogFormatter::ptr m_formatter;
	};

	// 日志器
	class Logger : public std:: enable_shared_from_this<Logger>
	{
	friend class LoggerManager;
	public:
		typedef std::shared_ptr<Logger> ptr;
		
		Logger(const std::string& name = "root");
		void Log(LogLevel::Level level, LogEvent::ptr event);

		void debug(LogEvent::ptr event);
		void info(LogEvent::ptr event);
		void warn(LogEvent::ptr event);
		void error(LogEvent::ptr event);
		void fatal(LogEvent::ptr event);


		/**
		 * @brief 添加日志目标
		 * @param[in] appender 日志目标
		 */
		void addAppender(LogAppender::ptr appender);

		/**
		 * @brief 删除日志目标
		 * @param[in] appender 日志目标
		 */
		void delAppender(LogAppender::ptr appender);

		/**
		 * @brief 清空日志目标
		 */
		void clearAppenders();

		LogLevel::Level getLevel() const { return m_level; }
		void setLevel(LogLevel::Level val) { m_level = val; }
		std::string getName()const { return m_name; }

		void setFormatter(LogFormatter::ptr val);
		void setFormatter(const std::string& val);
		LogFormatter::ptr getFormatter();

		/**
		 * @brief 将日志器的配置转成YAML String
		 */
		std::string toYamlString();
	private:
		std::string m_name;						 //日志名称
		LogLevel::Level m_level;				 //日志级别
		std::list<LogAppender::ptr> m_appenders; //日志集合
		LogFormatter::ptr m_formatter;
		Logger::ptr m_root;              //主日志器
	};

	// 输出到控制台
	class StdoutLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<StdoutLogAppender> ptr;
		void log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event) override;
		std::string toYamlString() override;
	};

	// 输出到文件
	class FileLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<FileLogAppender> ptr;
		FileLogAppender(const std::string& filename);
		virtual void log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event);

		bool reopen(); //重新打开文件，成功后返回true

		std::string toYamlString() override;
	private:
		std::string m_filename;
		std::ofstream m_filestream;
	};

	/**
	 * @brief 日志器管理类
	 */
	class LoggerManager {
	public:
		//typedef Spinlock MutexType;
		/**
		 * @brief 构造函数
		 */
		LoggerManager();

		/**
		 * @brief 获取日志器
		 * @param[in] name 日志器名称
		 */
		Logger::ptr getLogger(const std::string& name);

		/**
		 * @brief 初始化
		 */
		void init();

		/**
		 * @brief 返回主日志器
		 */
		Logger::ptr getRoot() const { return m_root; }

		/**
		 * @brief 将所有的日志器配置转成YAML String
		 */
		std::string toYamlString();
	private:
		// Mutex
		//MutexType m_mutex;
		// 日志器容器
		std::map<std::string, Logger::ptr> m_loggers;
		// 主日志器
		Logger::ptr m_root;
	};

	// 日志器管理类单例模式
	typedef aspect::Singleton<LoggerManager> LoggerMgr;
	

}
#endif