#ifndef __ASPECT_LOG_H
#define __ASPECT_LOG_H

#include <iostream>
#include <string >
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>


namespace aspect {

	/**
	 * @brief ʹ����ʽ��ʽ����־����level����־д�뵽logger
	 */
#define ASPECT_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        aspect::LogEventWrap(aspect::LogEvent::ptr(new aspect::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, aspect::GetThreadId(),\
                aspect::GetFiberId(), time(0), aspect::Thread::GetName()))).getSS()

	 /**
	  * @brief ʹ����ʽ��ʽ����־����debug����־д�뵽logger
	  */
#define ASPECT_LOG_DEBUG(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::DEBUG)

	  /**
	   * @brief ʹ����ʽ��ʽ����־����info����־д�뵽logger
	   */
#define ASPECT_LOG_INFO(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::INFO)

	   /**
		* @brief ʹ����ʽ��ʽ����־����warn����־д�뵽logger
		*/
#define ASPECT_LOG_WARN(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::WARN)

		/**
		 * @brief ʹ����ʽ��ʽ����־����error����־д�뵽logger
		 */
#define ASPECT_LOG_ERROR(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::ERROR)

		 /**
		  * @brief ʹ����ʽ��ʽ����־����fatal����־д�뵽logger
		  */
#define ASPECT_LOG_FATAL(logger) ASPECT_LOG_LEVEL(logger, aspect::LogLevel::FATAL)

		  /**
		   * @brief ʹ�ø�ʽ����ʽ����־����level����־д�뵽logger
		   */
#define ASPECT_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        aspect::LogEventWrap(aspect::LogEvent::ptr(new aspect::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, aspect::GetThreadId(),\
                aspect::GetFiberId(), time(0), aspect::Thread::GetName()))).getEvent()->format(fmt, __VA_ARGS__)

		   /**
			* @brief ʹ�ø�ʽ����ʽ����־����debug����־д�뵽logger
			*/
#define ASPECT_LOG_FMT_DEBUG(logger, fmt, ...) ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::DEBUG, fmt, __VA_ARGS__)

			/**
			 * @brief ʹ�ø�ʽ����ʽ����־����info����־д�뵽logger
			 */
#define ASPECT_LOG_FMT_INFO(logger, fmt, ...)  ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::INFO, fmt, __VA_ARGS__)

			 /**
			  * @brief ʹ�ø�ʽ����ʽ����־����warn����־д�뵽logger
			  */
#define ASPECT_LOG_FMT_WARN(logger, fmt, ...)  ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::WARN, fmt, __VA_ARGS__)

			  /**
			   * @brief ʹ�ø�ʽ����ʽ����־����error����־д�뵽logger
			   */
#define ASPECT_LOG_FMT_ERROR(logger, fmt, ...) ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::ERROR, fmt, __VA_ARGS__)

			   /**
				* @brief ʹ�ø�ʽ����ʽ����־����fatal����־д�뵽logger
				*/
#define ASPECT_LOG_FMT_FATAL(logger, fmt, ...) ASPECT_LOG_FMT_LEVEL(logger, aspect::LogLevel::FATAL, fmt, __VA_ARGS__)

				/**
				 * @brief ��ȡ����־��
				 */
#define ASPECT_LOG_ROOT() aspect::LoggerMgr::GetInstance()->getRoot()

				 /**
				  * @brief ��ȡname����־��
				  */
#define ASPECT_LOG_NAME(name) aspect::LoggerMgr::GetInstance()->getLogger(name)

	class Logger;
	class LoggerManager;

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

	// ��־�¼�
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr; //��ֹͬһ��ַ�������������ָ�����գ������ͷ�ָ����Դ
		LogEvent(const char* file, int32_t line, uint32_t elapse,
			uint32_t thread_id, uint32_t fiber_id, uint64_t time);

		const char* getFile() const { return m_file; }
		int32_t getLine() const { return m_line; }
		uint32_t getElapse() const { return m_elapse; }
		uint32_t getThreadId() const { return m_threadId; }
		uint32_t getFiberId() const { return m_fiberId; }
		uint64_t getTime() const { return m_time; }
		std::string getThreadName() const{ return m_threadName; }
		std::string getConent() const { return m_ss.str(); }

		std::shared_ptr<Logger> getLogger() const { return m_logger; } //������־��
		std::stringstream& getSS() { return m_ss; }

	private:
		const char* m_file = nullptr; //�ļ���
		int32_t m_line = 0;			  //�к�
		uint32_t m_elapse = 0;		  //�������ڵĺ�����
		uint32_t m_threadId = 0;	  //�߳�id
		uint32_t m_fiberId = 0;		  //Э��id
		uint64_t m_time = 0;		  //ʱ���
		std::string m_threadName;     //�߳�����
		std::stringstream m_ss;       //��־������

		std::shared_ptr<Logger> m_logger; //��־��
		LogLevel::Level m_level;          //��־�ȼ�
	};

	/**
	 * @brief ��־�¼���װ��
	 */
	class LogEventWrap {
	public:

		/**
		 * @brief ���캯��
		 * @param[in] e ��־�¼�
		 */
		LogEventWrap(LogEvent::ptr e);

		~LogEventWrap();
		/**
		 * @brief ��ȡ��־�¼�
		 */
		LogEvent::ptr getEvent() const { return m_event; }
		/**
		 * @brief ��ȡ��־������
		 */
		std::stringstream& getSS();
	private:
		/**
		 * @brief ��־�¼�
		 */
		LogEvent::ptr m_event;
	};
	

	// ��־��ʽ��
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
	private:
		std::string m_pattern;
		std::vector<FormatItem::ptr> m_items;
	};
	// ��־�����,��־�������
	class LogAppender
	{
	public:
		typedef std::shared_ptr<LogAppender> ptr;
		//typedef Spinlock MutexType;

		virtual ~LogAppender() {} //��������ͷ�
		virtual void log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event) = 0; //���麯��

		LogFormatter::ptr getFormatter() const { return m_formatter; }
		void setFormatter(LogFormatter::ptr val) { m_formatter = val; }
	protected:
		LogLevel::Level m_level;
		// Mutex
		//MutexType m_mutex;
		LogFormatter::ptr m_formatter;
	};

	// ��־��
	class Logger : public std:: enable_shared_from_this<Logger>
	{
	public:
		typedef std::shared_ptr<Logger> ptr;
		
		Logger(const std::string& name = "root");
		void Log(LogLevel::Level level, LogEvent::ptr event);

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
		LogFormatter::ptr m_formatter;
	};

	// ���������̨
	class StdoutLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<StdoutLogAppender> ptr;
		void log(LogLevel::Level level, std::shared_ptr<Logger> logger, LogEvent::ptr event) override;
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

	/**
	 * @brief ��־��������
	 */
	class LoggerManager {
	public:
		//typedef Spinlock MutexType;
		/**
		 * @brief ���캯��
		 */
		LoggerManager();

		/**
		 * @brief ��ȡ��־��
		 * @param[in] name ��־������
		 */
		Logger::ptr getLogger(const std::string& name);

		/**
		 * @brief ��ʼ��
		 */
		void init();

		/**
		 * @brief ��������־��
		 */
		Logger::ptr getRoot() const { return m_root; }

		/**
		 * @brief �����е���־������ת��YAML String
		 */
		std::string toYamlString();
	private:
		// Mutex
		//MutexType m_mutex;
		// ��־������
		//std::map<std::string, Logger::ptr> m_loggers;
		// ����־��
		Logger::ptr m_root;
	};

	

}
#endif