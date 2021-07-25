#ifndef __RAINBOW_UTIL_H_
#define __RAINBOW_UTIL_H_

#include <pthread.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include <sys/syscall.h>

namespace rainbow {

pid_t GetThreadId();
uint32_t GetFiberId();

} // namespace rainbow


#endif
