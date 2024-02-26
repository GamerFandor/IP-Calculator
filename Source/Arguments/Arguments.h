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

enum Task
{
    TASK_PRINTHELP,
    TASK_PRINTVERSION,
    TASK_PRINTDETAILS,
    TASK_PRINTCLASSLESSDETAILS,
    TASK_CALCULATEBYSUBNET,
    TASK_CALCULATEBYHOST,
    TASK_CALCULATEBYMULTIPLESUBNETS,
    TASK_CALCULATEBYCRONOLOGICAL
};

class Arguments
{
private:
    std::vector<std::string> argv;

public:
    Arguments(int argc, char **argv);

    int GetArgCount() const;
    Task GetTask() const;
    std::string GetIP() const;
    std::string GetMask() const;
    int GetRequiredSubnets() const;
    int GetRequiredHosts() const;
    std::vector<int> GetRequiredHostsList() const;
    std::vector<int> GetSubnetIndexToBeDevided() const;
    std::vector<int> GetRequiredHostsListForCronology() const;

private:
    bool Contains(std::string Searched) const;
    int FlagCount() const;
};