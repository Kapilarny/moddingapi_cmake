//
// Created by user on 23.05.2024.
//

#ifndef HOOK_HELPER_H
#define HOOK_HELPER_H

#include <iostream>

#include "MinHook.h"

static __int64 moduleBase = (__int64) GetModuleHandle(nullptr);

bool init_minhook() {
    if(MH_Initialize() != MH_OK) {
        // SetConsoleTextAttribute(hConsole, 64);
        std::cout << "MinHook Failed to initialize!\n";

        return false;
    }

    return true;
}

void shutdown_minhook() {
    MH_Uninitialize();
}

template<typename T>
bool register_hook(uint64_t addr, T* func, void* orig) {
    if(MH_CreateHook((LPVOID)addr, (void*)func, (void**)orig) != MH_OK) {
        // SetConsoleTextAttribute(hConsole, 64);
        std::cout << "Failed to apply hooks!\n";
        // SetConsoleTextAttribute(hConsole, 0);

        return false;
    }

    if(MH_EnableHook((LPVOID)addr) != MH_OK) {
        // SetConsoleTextAttribute(hConsole, 64);
        std::cout << "Failed to apply hooks!\n";
        // SetConsoleTextAttribute(hConsole, 0);

        return false;
    }

    return true;
}

template<typename T>
bool register_game_hook(uint64_t addr, T* func, void* orig) {
    return register_hook(moduleBase + addr, func, orig);
}

#endif //HOOK_HELPER_H
