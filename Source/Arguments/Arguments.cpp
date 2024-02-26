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

#include <iostream>
#include "Print/Print.h"
#include "Arguments/Arguments.h"

bool Contains(char* sentence, const char* findable);

Arguments::Arguments(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        std::string temp(argv[i]);
        if (temp.find("ip-calculator") != std::string::npos) continue;
        this->argv.push_back(temp);
    }
}

int Arguments::GetArgCount() const
{
    return argv.size();
}

Task Arguments::GetTask() const
{
    if (Contains("--version") || Contains("-v"))
        return Task::TASK_PRINTVERSION;
    else if (Contains("--help") || Contains("-h"))
        return Task::TASK_PRINTHELP;
    
    if (FlagCount() == 0 && this->argv.size() == 1)
        return Task::TASK_PRINTDETAILS;

    if (FlagCount() == 0 && this->argv.size() == 2)
        return Task::TASK_PRINTCLASSLESSDETAILS;

    if (FlagCount() == 1 && this->argv.size() == 4 && this->argv[0] == "-s" || this->argv[0] == "--subnet")
        return Task::TASK_CALCULATEBYSUBNET;

    if (FlagCount() == 1 && this->argv.size() == 4 && this->argv[0] == "-e" || this->argv[0] == "--hosts")
        return Task::TASK_CALCULATEBYHOST;

    if (FlagCount() == 1 && this->argv.size() >= 4 && this->argv[0] == "-d" || this->argv[0] == "--deviding")
        return Task::TASK_CALCULATEBYMULTIPLESUBNETS;

    if (FlagCount() == 1 && this->argv.size() >= 4 && this->argv[0] == "-c" || this->argv[0] == "--cronology")
        return Task::TASK_CALCULATEBYCRONOLOGICAL;

    return Task::TASK_PRINTVERSION;
}

std::string Arguments::GetIP() const
{
    if (this->argv.size() == 1) return this->argv[0];
    return this->argv[this->argv.size() - 2];
}

std::string Arguments::GetMask() const
{
    return this->argv[this->argv.size() - 1];
}

int Arguments::GetRequiredSubnets() const
{
    return stoi(this->argv[1]);
}

int Arguments::GetRequiredHosts() const
{
    return stoi(this->argv[1]);
}

std::vector<int> Arguments::GetRequiredHostsList() const
{
    std::vector<int> Output;
    std::vector<std::string> temp = this->argv;
    temp.pop_back();
    temp.pop_back();
    temp.erase(temp.begin());
    for (int i = 0; i < temp.size(); i++)
        Output.push_back(stoi(temp[i]));
    return Output;
}

std::vector<int> Arguments::GetSubnetIndexToBeDevided() const
{
    std::vector<int> Output;
    std::vector<std::string> temp = this->argv;
    temp.pop_back();
    temp.pop_back();
    temp.erase(temp.begin());
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i].find("[") != std::string::npos) 
        {
            int start = temp[i].find("[");
            int end = temp[i].find("]");
            if (start != std::string::npos && end != std::string::npos) 
            {
                std::string number_str = temp[i].substr(start + 1, end - start - 1);
                int number = 0;
                for (char c : number_str) 
                {
                    if (c >= '0' && c <= '9') 
                    {
                        number = number * 10 + (c - '0');
                    }
                }
                Output.push_back(number);
            }
        } 
        else 
        {
            Output.push_back(stoi(temp[i]));
        }
    }
    
    return Output;
}

std::vector<int> Arguments::GetRequiredHostsListForCronology() const
{
    std::vector<int> Output;
    std::vector<std::string> temp = this->argv;
    temp.pop_back();
    temp.pop_back();
    temp.erase(temp.begin());
    for (int i = 0; i < temp.size(); i++)
        Output.push_back(stoi(temp[i]));
    return Output;
}

bool Arguments::Contains(std::string Searched) const
{   
    for (int i = 0; i < this->argv.size(); i++)
        if (this->argv[i] == Searched)
            return true;

    return false;
}

int Arguments::FlagCount() const
{
    int FlagCount = 0;
    for (auto arg : this->argv)
        if (arg.substr(0, 1) == "-")
            FlagCount++;

    return FlagCount;
}
