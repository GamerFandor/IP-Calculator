/**
 * IP-Calculator - Calculates subnets and prints information about an IP address.
 * Copyright (C) 2022  Andor Zoltán Fülöp
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
**/

#include "Defines.h"
#include "Print/Print.h"
#include <iostream>

#ifdef PLATFORM_WINDOWS

#include <windows.h>


void Print::Success(std::string Message)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "[ ";
    SetConsoleTextAttribute(h, 10);
    std::cout << "+";
    SetConsoleTextAttribute(h, 7);
    std::cout << " ] " << Message << "\n";
}

void Print::Information(std::string Message)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "[ ";
    SetConsoleTextAttribute(h, 9);
    std::cout << "i";
    SetConsoleTextAttribute(h, 7);
    std::cout << " ] " << Message << "\n";
}

void Print::Warning(std::string Message)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "[ ";
    SetConsoleTextAttribute(h, 14);
    std::cout << "!";
    SetConsoleTextAttribute(h, 7);
    std::cout << " ] " << Message << "\n";
}

void Print::Error(std::string Message)
{
    HANDLE h = GetStdHandle(STD_ERROR_HANDLE);
    std::cout << "[ ";
    SetConsoleTextAttribute(h, 12);
    std::cout << "x";
    SetConsoleTextAttribute(h, 7);
    std::cout << " ] " << Message << "\n";
}

#endif