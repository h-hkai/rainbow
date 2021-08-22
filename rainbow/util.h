#ifndef __RAINBOW_UTIL_H_
#define __RAINBOW_UTIL_H_

#include <pthread.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>

#include <sys/syscall.h>

namespace rainbow {

pid_t GetThreadId();
uint32_t GetFiberId();


std::string BacktraceToString(const std::string& prefix = "", int size = 64, int skip = 2);

void Backtrace(std::vector<std::string>& bt, int size = 64, int skip = 1);

uint64_t GetCurrentMS();
uint64_t GetCurrentUS();

} // namespace rainbow


#endif
