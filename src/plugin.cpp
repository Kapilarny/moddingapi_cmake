#include "plugin.h"

#include <iostream>
#include "MinHook.h"
#include <windows.h>
#include <unordered_map>
#include <fstream>

#include "hook_helper.h"
#include "log.h"
#include "mem.h"

// 122C310
typedef __int64(__fastcall *sub_122C310)(const char* a1);
sub_122C310 orig_sub_122C310;

std::unordered_map<__int64, std::string> hash_map;

__int64 sub_122C310_Hook(const char* a1) {
    auto result = orig_sub_122C310(a1);

    // std::cout << "Hashing -> " << a1 << "\n";
    hash_map[result] = a1;

    return result;
}

struct cc2_hashed_str {
    int hash;
    bool unk;
};

std::unordered_map<__int64, std::string> xfbin_map;

// __int64 __fastcall sub_12447E0(__int64 a1, const char *a2)
// sub_12447E0
typedef __int64(__fastcall *sub_12447E0)(__int64 a1, const char* a2);
sub_12447E0 orig_sub_12447E0;

__int64 sub_12447E0_Hook(__int64 a1, const char* a2) {
    auto result = orig_sub_12447E0(a1, a2);

    // std::cout << "Hashing XFBIN -> " << a2 << "\n";

    if(!result || *(DWORD*)(result + 104) != 2) {
        return result;
    }

    // xfbin_map[result] = a2;

    // std::cout << "Hashing: " << a2 << " -> " << *(__int64*)(result + 80) << "\n";
    xfbin_map[*(__int64*)(result + 80)] = a2;

    return result;
}

// 1237F90
typedef __int64(__fastcall *sub_1237F90)(__int64 a1, const char** chunkType, cc2_hashed_str* resource);
sub_1237F90 orig_sub_1237F90;
__int64 __fastcall NSUNS_GetXFBINResource(__int64 xfbinHandle, const char **chunkType, cc2_hashed_str* resource) {
    std::string str = xfbin_map[xfbinHandle] + " -> " + hash_map[resource->hash] + " (" + *chunkType + ")\n";

    log_info(str);

    return orig_sub_1237F90(xfbinHandle, chunkType, resource);
}

void __stdcall InitializePlugin(__int64 moduleBase, std::vector<__int64> fuckin_function_list) {
    std::cout << "All my fucking homies hate VS\n";

    if(!init_minhook()) return;

    uint64_t hash_str_addr = GAME_SCAN("4C 8B C1 48 85 C9 75 03 33 C0 C3 B8 FF FF FF FF 48 C7 C1 FF FF FF FF 66 0F 1F 84 00 00 00 00 00 48 FF C1 41 80 3C 08 00 75 F6 4C 63 D1 85 C9 7E 2A 45 33 C9 4C 8D 1D ?? ?? ?? ?? 0F 1F 44 00 00 43 0F B6 14 01 8B C8 C1 E9 18 49 FF C1 33 D1 C1 E0 08 41 33 04 93 4D 3B CA 7C E5 F7 D0 C3");
    uint64_t get_xfbin_handle = GAME_SCAN("48 89 5C 24 18 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 70 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 60 48 8B DA 48");
    uint64_t get_xfbin_resource = GAME_SCAN("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 50 49 8B D8 48 8B FA 48 8B F1 E8 ?? ?? ?? ?? 0F 10 03 48 8B AE 90 00 00 00 33 D2 0F B7 7F 0A 4C 8B CD 0F 11 44 24 20 44 0F B6 54 24 24 0F 10 00 48 8B 45 08 44 8B 5C 24 20 0F 11 44 24 38 0F B6 5C 24 3C 8B 74 24 38 38 50 19 75 62 90 0F B6 48 24 84 C9 74 18 41 3A CA 75 06 44 39 58 20 74 0D 8B CA 45 84 D2 74 32 44 39 58 20 EB 29 66 39 78 30 75 21 38 50 3C 74 2B 84 DB 74 27 0F B6 48 3C 84 C9 74 1F 44 8B 40 38 3A CB 75 05 44 3B C6 74 12 44 3B C6 8B CA 0F 92 C1 85 C9 74 06 48 8B 40 10 EB 06 4C 8B C8 48 8B 00 38 50 19 74 9F 41 38 51 19 75 5F 45 84 D2 74 1A 41 0F B6 41 24 44 3A D0 75 06 45 3B 59 20 74 0A 84 C0 74 31 45 3B 59 20 EB 28 66 41 3B 79 30 75 21 84 DB 74 24 41 38 51 3C 74 1E 41 0F B6 41 3C 3A D8 75 06 41 3B 71 38 74 0F 84 C0 74 07 41 3B 71 38 0F 92 C2 85 D2 75 11 4C 3B CD 74 0C 49 8B 49 48 48 8B 01 FF 50 ?? EB 02 33 C0 48 8B 5C 24 60 48 8B 6C 24 68 48 8B 74 24 70 48 83 C4 50 5F C3");

    if(!register_hook(get_xfbin_resource, &NSUNS_GetXFBINResource, &orig_sub_1237F90)) {
        std::cout << "HOOK FAILED\n";
    }

    if(!register_hook(hash_str_addr, &sub_122C310_Hook, &orig_sub_122C310)) {
        std::cout << "HOOK FAILED\n";
    }

    if(!register_hook(get_xfbin_handle, &sub_12447E0_Hook, &orig_sub_12447E0)) {
        std::cout << "HOOK FAILED\n";
    }

    std::cout << "Hooks applied motherfucker!\n";
}

void __stdcall InitializeCommands(__int64 a, AddCmd addCmdFuncPtr) {}
void __stdcall InitializeHooks(__int64 a, HookFunct hookFuncPtr) {}
void __stdcall InitializeLuaCommands(__int64 a, LuaAddFc luaAddFuncPtr) {}
void __stdcall GameLoop(__int64 fuckin_god_knows_what_this_var_is) {}

// This function is called when the API is loading a mod's files. Return true if the file was read by this plugin, otherwise return false for the API to manage the file.
bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes) {
    return true;
}
