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

#pragma once

#include <string>
#include <vector>
#include "Calculation/Network.h"

class Print
{
public:
    static void Success(std::string Message);
    static void Information(std::string Message);
    static void Warning(std::string Message);
    static void Error(std::string Message);

    static void Table(std::vector<Network> nets);
    static void Line();
    static void Header();
    static void DataRow(Network net, int id);

    static void DetailsTable(Network net);

    static std::string AlignLeft(std::string Text, unsigned int Length);
    static std::string AlignRight(std::string Text, unsigned int Length);
    static std::string AlignCenter(std::string Text, unsigned int Length); 
    static std::string FormatNumber(int Num);   

    static void Version();
    static void Help();
};
