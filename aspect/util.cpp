#include "util.hpp"

namespace aspect {
	pid_t GetTreadId() {
		return syscall(SYS_gettid);
	}
	uint32_t GetFiberId() {
		return 0;
	}
}