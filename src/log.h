//
// Created by user on 28.05.2024.
//

#ifndef LOG_H
#define LOG_H

#include <string>
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void log_info(std::string str) {
    // Set color to green
    SetConsoleTextAttribute(hConsole, 10);
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), str.c_str(), (DWORD)str.size(), NULL, 0);
    // SetConsoleTextAttribute(hConsole, 0);
}

#endif //LOG_H
