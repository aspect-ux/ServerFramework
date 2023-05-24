#ifndef __ASPECT_UTIL_H__
#define __ASPECT_UTIL_H__

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
namespace aspect {
	pid_t GetThreadId();
	uint32_t GetFiberId();
}
#endif