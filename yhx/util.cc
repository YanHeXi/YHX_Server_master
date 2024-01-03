#include "util.h"
#include "log.h"

// static yhx::Logger::ptr g_logger = YHX_LOG_DEBUG("system");

namespace yhx
{
    pid_t GetThreadId()
    {
        // return syscall(SYS_gettid);
        return 0;
    }

    uint32_t GetFiberId()
    {
        // return yhx::Fiber::GetFiberId();
        return 0;
    }
} // namespace yhx
