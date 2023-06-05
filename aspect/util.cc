#include "util.h"
#include "log.h"
#include <sys/types.h>
#include <unistd.h>
#include <syscall.h>

namespace aspect {

	static aspect::Logger::ptr g_logger = ASPECT_LOG_NAME("system");

	pid_t GetThreadId() {
		return syscall(SYS_gettid);
	}
	uint32_t GetFiberId() {
		return 0;
	}
	
}