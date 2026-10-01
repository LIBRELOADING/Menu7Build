#pragma once
#include <cstdint>

namespace Anogs {
    constexpr uintptr_t AnoSDKInit            = 0xE6E05;
    constexpr uintptr_t AnoSDKGetReportData   = 0xE8B4B;
    constexpr uintptr_t AnoSDKOnRecvData      = 0xE9C43;
    constexpr uintptr_t AnoSDKIoctl           = 0xEA945;
}

namespace Anort {
    constexpr uintptr_t unwind_xx_info_query  = 0x970AB;
    constexpr uintptr_t unwind_xx_ioctl       = 0x97337;
    constexpr uintptr_t tp_syscall_imp        = 0x108AF0;
}