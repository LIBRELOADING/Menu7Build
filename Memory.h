#pragma once
#include <cstdint>
#include <cstddef>

namespace Memory {
    uintptr_t GetModuleBase(const char* name);
    size_t    GetModuleSize(const char* name);
    bool      PatchBytes(uintptr_t addr, const uint8_t* data, size_t len);
    bool      ReadBytes(uintptr_t addr, uint8_t* out, size_t len);
    bool      Nop(uintptr_t addr, size_t count);
}
