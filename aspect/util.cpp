#include "util.hpp"
#include "log.hpp"
#include <sys/types.h>
//#include <unistd.h>

namespace aspect {

	static aspect::Logger::ptr g_logger = ASPECT_LOG_NAME("system");

	pid_t GetThreadId() {
		return 0;
		//return syscall(SYS_gettid);
	}
	uint32_t GetFiberId() {
		return 0;
	}
	
}