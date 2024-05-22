#ifndef MODDINGAPI_CMAKE_LIBRARY_H
#define MODDINGAPI_CMAKE_LIBRARY_H

#include <vector>
#include <string>

#define API extern "C" __declspec(dllexport)

typedef void(__stdcall *AddCmd)(std::string command, __int64 function, int paramcount);
typedef void(__stdcall *HookFunct)(void* toHook, void* ourFunct, int len);
typedef void(__stdcall *LuaAddFc)(std::string command, __int64 function);

// Those "a" variables fucking suck since im completely clueless on what they do haha
// No explanation in plugin template too :P

API void __stdcall InitializePlugin(__int64 moduleBase, std::vector<__int64> fuckin_function_list); // god i hate this wtf
API void __stdcall InitializeCommands(__int64 a, AddCmd addCmdFuncPtr);
API void __stdcall InitializeHooks(__int64 a, HookFunct hookFuncPtr);
API void __stdcall InitializeLuaCommands(__int64 a, LuaAddFc luaAddFuncPtr);
API void __stdcall GameLoop(__int64 a);
API bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes);

#endif //MODDINGAPI_CMAKE_LIBRARY_H
