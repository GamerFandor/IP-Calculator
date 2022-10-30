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

#include "Print/Print.h"
#include "Arguments/Arguments.h"

bool Contains(char* sentence, const char* findable);

Arguments::Arguments(int argc, char **argv)
{
    this->argc = argc;
    this->argv = argv;
}

Task Arguments::GetTask() const
{
    return Task::TASK_PRINTVERSION;
}

std::string Arguments::GetIP() const
{
    return "";
}

std::string Arguments::GetMask() const
{
    return "";
}

int Arguments::GetRequiredSubnets() const
{
    return 0;
}

int Arguments::GetRequiredHosts() const
{
    return 0;
}

std::vector<int> Arguments::GetRequiredHostsList() const
{
    std::vector<int> Output;
    return Output;
}

std::vector<int> Arguments::GetRequiredHostsListForCronology() const
{
    std::vector<int> Output;
    return Output;
}
