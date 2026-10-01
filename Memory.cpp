#include "memory.h"
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/mman.h>
#include <android/log.h>

#define LOG_TAG "Menu7Bypass"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

uintptr_t Memory::GetModuleBase(const char* name) {
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return 0;
    char line[512];
    uintptr_t base = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, name)) {
            sscanf(line, "%lx-", &base);
            break;
        }
    }
    fclose(fp);
    return base;
}

size_t Memory::GetModuleSize(const char* name) {
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return 0;
    char line[512];
    uintptr_t start = 0, end = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, name)) {
            uintptr_t s, e;
            sscanf(line, "%lx-%lx", &s, &e);
            if (start == 0 || s < start) start = s;
            if (e > end) end = e;
        }
    }
    fclose(fp);
    return end - start;
}

bool Memory::PatchBytes(uintptr_t addr, const uint8_t* data, size_t len) {
    uintptr_t page = addr & ~(uintptr_t)(4095);
    size_t total = (addr - page) + len;
    size_t pages = (total + 4095) & ~((size_t)4095);

    if (mprotect((void*)page, pages, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
        LOGE("mprotect falhou em 0x%lx", addr);
        return false;
    }
    memcpy((void*)addr, data, len);
    __builtin___clear_cache((char*)addr, (char*)(addr + len));
    mprotect((void*)page, pages, PROT_READ | PROT_EXEC);
    LOGI("Patch OK em 0x%lx (%zu bytes)", addr, len);
    return true;
}

bool Memory::ReadBytes(uintptr_t addr, uint8_t* out, size_t len) {
    memcpy(out, (void*)addr, len);
    return true;
}

bool Memory::Nop(uintptr_t addr, size_t count) {
    uint8_t nop[4] = {0x1F, 0x20, 0x03, 0xD5};  // ARM64 NOP
    for (size_t i = 0; i < count; i++) {
        if (!PatchBytes(addr + (i * 4), nop, 4)) return false;
    }
    return true;
}