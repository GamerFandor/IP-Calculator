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

#include <cmath>
#include <iostream>
#include "Defines.h"
#include <algorithm>
#include "Print/Print.h"

void Print::Table(std::vector<Network> nets)
{
    Print::Line();
    Print::Header();
    Print::Line();
    for (int i = 0; i < nets.size(); i++)
        Print::DataRow(nets[i], i + 1);
    Print::Line();
}

void Print::Line()
{
    std::cout << "+-------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+" << "\n";
}

void Print::Header()
{
    std::cout << "| " << Print::AlignCenter("ID", 5) << " | " << Print::AlignCenter("Network Address", 15) << " | " << Print::AlignCenter("Netmask", 15) << " | " << Print::AlignCenter("First Address", 15) << " | " << Print::AlignCenter("Last Address", 15) << " | " << Print::AlignCenter("Broadcast", 15) << " | " << Print::AlignCenter("Available hosts", 15) << " |" << "\n";
}

void Print::DataRow(Network net, int id)
{
    std::string SerNum = Print::AlignRight(std::to_string(id) + ".", 5);
    std::string NetAdd = Print::AlignLeft(net.GetNetworkAddress().GetInDecimal(), 15);
    std::string Mask = Print::AlignLeft(net.GetNetworkMask().GetInDecimal(), 15);
    std::string FirstAdd = Print::AlignLeft(net.GetFirstAddress().GetInDecimal(), 15);
    std::string LastAdd = Print::AlignLeft(net.GetLastAddress().GetInDecimal(), 15);
    std::string BroadcastAdd = Print::AlignLeft(net.GetBroadcastAddress().GetInDecimal(), 15);
    std::string Hosts = Print::AlignRight(Print::FormatNumber(net.GetAvailableHosts()), 15);

    std::cout << "| " << SerNum << " | " << NetAdd << " | " << Mask << " | " << FirstAdd << " | " << LastAdd << " | " << BroadcastAdd << " | " << Hosts << " |" << "\n";
}

void Print::DetailsTable(Network net)
{
    if (net.GetClassEnum() == AddressClass::CLASSLESS)
    {
        std::cout << "+-----------------+-----------------+" << "\n";
        std::cout << "| " << Print::AlignRight("Class", 15) << " | " << Print::AlignLeft("Classless", 15) << " |" << "\n";
        std::cout << "| " << Print::AlignRight("Network Address", 15) << " | " << Print::AlignLeft(net.GetNetworkAddress().GetInDecimal(), 15) << " |" << "\n";
        std::cout << "| " << Print::AlignRight("Netmask", 15) << " | " << Print::AlignLeft(net.GetNetworkMask().GetInDecimal(), 15) << " |" << "\n";
        std::cout << "| " << Print::AlignRight("First Address", 15) << " | " << Print::AlignLeft(net.GetFirstAddress().GetInDecimal(), 15) << " |" << "\n";
        std::cout << "| " << Print::AlignRight("Last Address", 15) << " | " << Print::AlignLeft(net.GetLastAddress().GetInDecimal(), 15) << " |" << "\n";
        std::cout << "| " << Print::AlignRight("Broadcast", 15) << " | " << Print::AlignLeft(net.GetBroadcastAddress().GetInDecimal(), 15) << " |" << "\n";
        std::cout << "| " << Print::AlignRight("Available Hosts", 15) << " | " << Print::AlignLeft(Print::FormatNumber(net.GetAvailableHosts()), 15) << " |" << "\n";
        std::cout << "+-----------------+-----------------+" << "\n";
    }
    else
    {
        std::cout << "+-----------------+-----------------+" << "\n";
        std::cout << "| " << Print::AlignRight("Class", 15) << " | " << Print::AlignLeft(net.GetClass(), 15) << " |" << "\n";
        std::cout << "| " << Print::AlignRight("Network Address", 15) << " | " << Print::AlignLeft(net.GetNetworkAddress().GetInDecimal(), 15) << " |" << "\n";
        switch (net.GetClassEnum())
        {
        case AddressClass::CLASS_D:
            std::cout << "| " << Print::AlignRight("Netmask", 15) << " | " << Print::AlignLeft("Not defined", 15) << " |" << "\n";
            break;

        case AddressClass::CLASS_E:
            std::cout << "| " << Print::AlignRight("Netmask", 15) << " | " << Print::AlignLeft("Not defined", 15) << " |" << "\n";
            break;

        default:
            std::cout << "| " << Print::AlignRight("Netmask", 15) << " | " << Print::AlignLeft(net.GetNetworkMask().GetInDecimal(), 15) << " |" << "\n";
            break;
        }

        switch (net.GetClassEnum())
        {
        case AddressClass::CLASS_D:
            std::cout << "| " << Print::AlignRight("Address", 15) << " | " << Print::AlignLeft("Multicast", 15) << " |" << "\n";
            break;

        case AddressClass::CLASS_E:
            std::cout << "| " << Print::AlignRight("Address", 15) << " | " << Print::AlignLeft("Reserved", 15) << " |" << "\n";
            break;

        default:
            std::cout << "| " << Print::AlignRight("First Address", 15) << " | " << Print::AlignLeft(net.GetFirstAddress().GetInDecimal(), 15) << " |" << "\n";
            std::cout << "| " << Print::AlignRight("Last Address", 15) << " | " << Print::AlignLeft(net.GetLastAddress().GetInDecimal(), 15) << " |" << "\n";
            std::cout << "| " << Print::AlignRight("Broadcast", 15) << " | " << Print::AlignLeft(net.GetBroadcastAddress().GetInDecimal(), 15) << " |" << "\n";
            std::cout << "| " << Print::AlignRight("Available Hosts", 15) << " | " << Print::AlignLeft(Print::FormatNumber(net.GetAvailableHosts()), 15) << " |" << "\n";
            break;
        }
        
        std::cout << "+-----------------+-----------------+" << "\n";
    }
}

std::string Print::AlignLeft(std::string Text, unsigned int Length)
{
    std::string Output = "";
    Output += Text;
    for (int i = 0; i < Length - Text.length(); i++)
        Output += " ";
    return Output;
}

std::string Print::AlignRight(std::string Text, unsigned int Length)
{
    std::string Output = "";
    for (int i = 0; i < Length - Text.length(); i++)
        Output += " ";
    Output += Text;
    return Output;
}

std::string Print::AlignCenter(std::string Text, unsigned int Length)
{
    std::string Output = "";

    int SpacesOnLeft = floor((Length - Text.length()) / 2.0f);
    int SpacesOnRight = ceil((Length - Text.length()) / 2.0f);
    bool IsTextInserted = false;

    for (int i = 0; i < Length - Text.length() + 1; i++)
    {
        if (SpacesOnLeft > 0)
        {
            Output += " ";
            SpacesOnLeft--;
            continue;
        }

        if (!IsTextInserted)
        {
            Output += Text;
            IsTextInserted = true;
        }
        
        if (SpacesOnRight > 0)
        {
            Output += " ";
            SpacesOnRight--;
        }
    }

    return Output;
}

std::string Print::FormatNumber(int Num)
{
    std::string Output = "";
    int FinalLength = (int)(floor(std::to_string(Num).length() / 3) + std::to_string(Num).length());
    int CountdownToSpace = std::to_string(Num).length() % 3;

    for (int i = 0; i < std::to_string(Num).length(); i++)
    {
        if (CountdownToSpace == 0)
        {
            Output += " ";
            CountdownToSpace = 3;
        }

        Output += std::to_string(Num)[i];
        CountdownToSpace--;
    }
    if (Output[0] == ' ')
    {
        return Output.substr(1, Output.length() - 1);
    }
    return Output;
}

void Print::Version()
{
    std::cout << "IP-Calculator v1.0.0\n\nIP-Calculator Copyright (C) 2022 Andor Zoltan Fulop\nThis program comes with ABSOLUTELY NO WARRANTY; for details visit <https://gnu.org/licenses/gpl.html>.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; visit <https://gnu.org/licenses/gpl.html> for details.\n\nWritten by Andor Zoltan Fulop.\n";
}

void Print::Help()
{
    // Usage
    std::cout << "[USAGE / EXAMPLES]\n";
    std::cout << "   ip-calculator IP_Address\n";
    std::cout << "   ip-calculator IP_Address Netmask\n";
    std::cout << "   ip-calculator -s 4 IP_Address Netmask\n";
    std::cout << "   ip-calculator -h 20 IP_Address Netmask\n";
    std::cout << "   ip-calculator -d 2[2] 4[3] 3[1] 2 IP_Address Netmask\n";
    std::cout << "   ip-calculator -c 100 20 30 20 IP_Address Netmask\n";
    std::cout << "   ip-calculator -h\n";
    std::cout << "   ip-calculator -v\n\n";

    // Description
    std::cout << "[DESCRIPTION]\n";
    std::cout << "   Calculates IPv4 addresses (subneting, superneting and details). (Version 1.0.0)\n\n";

    // Positional arguments
    std::cout << "[POSITIONAL ARGUMENTS]\n";
    std::cout << "   IP_address\n";
    std::cout << "         IP address of a network which you want details about.\n\n";
    std::cout << "   Netmask\n";
    std::cout << "         Netmask of your network.\n\n";

    // Optional arguments
    std::cout << "[OPTIONAL ARGUMENTS]\n";
    std::cout << "   -s <amount of required subnets>, --subnets <amount of required subnets>\n";
    std::cout << "         Devides the given network into the given subnets if it possible.\n\n";
    std::cout << "   -h <amount of required hosts>, --hosts <amount of required hosts>\n";
    std::cout << "         Devides the given network to have enough hosts in the given subnetwork.\n\n";
    std::cout << "   -d <amount of required subnets>, --deviding <amount of required subnets>\n";
    std::cout << "         Devides the given network to subnetworks and subnetworks are devided into more subnetworks.\n\n";
    std::cout << "   -c <required hosts in cronological order>, --cronology <required hosts in cronological order>\n";
    std::cout << "         Devides the given network in cronological order.\n\n";
    std::cout << "   -h, --help\n";
    std::cout << "         Prints the help page.\n\n";
    std::cout << "   -v, --version\n";
    std::cout << "         Prints the current version of the software.\n\n";
    
    // Author
    std::cout << "[AUTHOR]\n";
    std::cout << "   Written by Andor Zoltan Fulop.\n\n";

    // Licence
    std::cout << "[LICENCE]\n";
    std::cout << "   IP-Calculator Copyright (C) 2022 Andor Zoltan Fulop\n   This program comes with ABSOLUTELY NO WARRANTY; for details visit <https://gnu.org/licenses/gpl.html>.\n   This is free software, and you are welcome to redistribute it\n   under certain conditions; visit <https://gnu.org/licenses/gpl.html> for details.\n";
}
