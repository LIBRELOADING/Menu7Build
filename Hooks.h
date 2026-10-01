#pragma once

namespace Hooks {
    void Init();
    void InstallAnogsBypass();
    void InstallAnortBypass();
    void HookAnoSDKIoctl();
    void HookAnoSDKOnRecvData();
    void HookUnwindQuery();
    void HookTpSyscall();
}