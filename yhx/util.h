#pragma once

#include <cxxabi.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <boost/lexical_cast.hpp>

namespace yhx
{

    /**
     * @brief 返回当前线程的ID
     */
    pid_t GetThreadId();

    /**
     * @brief 返回当前协程的ID
     */
    uint32_t GetFiberId();
}