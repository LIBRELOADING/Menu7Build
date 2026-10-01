#include "hooks.h"
#include "memory.h"
#include "offsets.h"
#include <android/log.h>

#define LOG_TAG "Menu7Bypass"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static uintptr_t g_anogs_base = 0;
static uintptr_t g_anort_base = 0;

// ARM64: MOV W0, #0 ; RET
static const uint8_t RET0[] = {0x00, 0x00, 0x80, 0x52, 0xC0, 0x03, 0x5F, 0xD6};

void Hooks::Init() {
    g_anogs_base = Memory::GetModuleBase("libanogs.so");
    g_anort_base = Memory::GetModuleBase("libanort.so");
    LOGI("libanogs base: 0x%lx", g_anogs_base);
    LOGI("libanort base: 0x%lx", g_anort_base);
}

void Hooks::InstallAnogsBypass() {
    if (!g_anogs_base) { LOGI("libanogs nao carregada"); return; }
    Memory::PatchBytes(g_anogs_base + Anogs::AnoSDKGetReportData, RET0, sizeof(RET0));
    Memory::PatchBytes(g_anogs_base + Anogs::AnoSDKOnRecvData,    RET0, sizeof(RET0));
    Memory::PatchBytes(g_anogs_base + Anogs::AnoSDKIoctl,         RET0, sizeof(RET0));
    LOGI("Bypass Anogs instalado");
}

void Hooks::InstallAnortBypass() {
    if (!g_anort_base) { LOGI("libanort nao carregada"); return; }
    Memory::PatchBytes(g_anort_base + Anort::unwind_xx_info_query, RET0, sizeof(RET0));
    Memory::PatchBytes(g_anort_base + Anort::unwind_xx_ioctl,      RET0, sizeof(RET0));
    LOGI("Bypass Anort instalado");
}

void Hooks::HookAnoSDKIoctl() {
    if (!g_anogs_base) return;
    Memory::PatchBytes(g_anogs_base + Anogs::AnoSDKIoctl, RET0, sizeof(RET0));
}

void Hooks::HookAnoSDKOnRecvData() {
    if (!g_anogs_base) return;
    Memory::PatchBytes(g_anogs_base + Anogs::AnoSDKOnRecvData, RET0, sizeof(RET0));
}

void Hooks::HookUnwindQuery() {
    if (!g_anort_base) return;
    Memory::PatchBytes(g_anort_base + Anort::unwind_xx_info_query, RET0, sizeof(RET0));
}

void Hooks::HookTpSyscall() {
    if (!g_anort_base) return;
    Memory::Nop(g_anort_base + Anort::tp_syscall_imp, 4);
}