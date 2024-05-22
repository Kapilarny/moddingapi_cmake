#include "plugin.h"

#include <iostream>
#include <windows.h>

void __stdcall InitializePlugin(__int64 moduleBase, std::vector<__int64> fuckin_function_list) {
    // Print red bold message to log
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 64);
    std::cout << "All my fucking homies hate VS\n";
    SetConsoleTextAttribute(hConsole, 0);
}

void __stdcall InitializeCommands(__int64 a, __int64 addCommandFunctionAddress) {

}

void __stdcall InitializeHooks(__int64 a, __int64 hookFunctionAddress) {

}

void __stdcall InitializeLuaCommands(__int64 a, __int64 addCommandFunction) {

}

void __stdcall GameLoop(__int64 fuckin_god_knows_what_this_var_is) {

}

// This function is called when the API is loading a mod's files. Return true if the file was read by this plugin, otherwise return false for the API to manage the file.
bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes) {
    return true;
}
