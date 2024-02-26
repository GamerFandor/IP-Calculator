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
    // Name
    std::cout << "NAME" << "\n";
    std::cout << "\t" << "IP-Calculator - Calculates subnets and prints information about an IP address." << "\n";
    std::cout << "\n";

    // Synopsis
    std::cout << "SYNOPSIS" << "\n";
    std::cout << "\t" << "ip-calculator [OPTION] <IP ADDRESS> [NETMASK]" << "\n";
    std::cout << "\n";

    // Description
    std::cout << "DESCRIPTION" << "\n";
    std::cout << "\t" << "The IP Calculator offers a comprehensive solution for subnetting and obtaining information about" << "\n";
    std::cout << "\t" << "IP addresses. With its capability to divide a large network into smaller subnets, it makes" << "\n";
    std::cout << "\t" << "managing and organizing your network simple. The calculator also has a feature that can quickly" << "\n";
    std::cout << "\t" << "identify whether an IP address is classful or classless, providing a clear picture of your" << "\n";
    std::cout << "\t" << "network's structure. In addition to calculating the number of subnets and host addresses per subnet," << "\n";
    std::cout << "\t" << "it can also create custom subnet masks. The Command Line Interface (CLI) enables easy input of" << "\n";
    std::cout << "\t" << "IP addresses and provides concise and easily understandable outputs." << "\n";
    std::cout << "\n";

    // Options
    std::cout << "OPTIONS" << "\n";
    std::cout << "\t" << "-s <amount of required subnets>, --subnets <amount of required subnets>" << "\n";
    std::cout << "\t\t" << "Devide the network into equal size subnetworks." << "\n";
    std::cout << "\n";
    std::cout << "\t" << "-e <amount of required hosts>, --hosts <amount of required hosts>" << "\n";
    std::cout << "\t\t" << "Devide the network into equal size subnetworks considering the required hosts." << "\n";
    std::cout << "\n";
    std::cout << "\t" << "-d <amount of required subnets>..., --deviding <amount of required subnets>..." << "\n";
    std::cout << "\t\t" << "Devide the network into subnetworks, then do it and stop when it runs out of requests." << "\n";
    std::cout << "\n";
    std::cout << "\t" << "-c <required hosts in cronological order>..., --cronology <required hosts in cronological order>..." << "\n";
    std::cout << "\t\t" << "Devides the network into subnetwork considering the required hosts and the order or requests." << "\n";
    std::cout << "\n";
    std::cout << "\t" << "-h, --help" << "\n";
    std::cout << "\t\t" << "Display the help page" << "\n";
    std::cout << "\n";
    std::cout << "\t" << "-v, --version" << "\n";
    std::cout << "\t\t" << "Display the version" << "\n";
    std::cout << "\n";

    // Examples
    std::cout << "EXAMPLES" << "\n";
    std::cout << "\t" << "ip-calculator 169.254.0.0" << "\n";
    std::cout << "\t" << "ip-calculator 192.168.1.0 255.255.255.0" << "\n";
    std::cout << "\t" << "ip-calculator -s 3 192.168.1.0 255.255.255.0" << "\n";
    std::cout << "\t" << "ip-calculator -e 62 172.30.0.0 255.255.0.0" << "\n";
    std::cout << "\t" << "ip-calculator -d 4[2] 2 3[1] 4 10.0.0.0 255.0.0.0" << "\n";
    std::cout << "\t" << "ip-calculator -c 100 2000 50 30 20 92.128.0.0 255.128.0.0" << "\n";
    std::cout << "\t" << "ip-calculator -h" << "\n";
    std::cout << "\t" << "ip-calculator -v" << "\n";
    std::cout << "\n";

    // Reporting Bugs
    std::cout << "REPORTING BUGS" << "\n";
    std::cout << "\t" << "You can report bugs on the project's github page." << "\n";
    std::cout << "\t" << "<https://github.com/GamerFandor/IP-Calculator/issues>" << "\n";
    std::cout << "\n";
    
    // Licence
    std::cout << "LICENCE" << "\n";
    std::cout << "\t" << "IP-Calculator Copyright (C) 2022 Andor Zoltan Fulop" << "\n";
    std::cout << "\t" << "This program comes with ABSOLUTELY NO WARRANTY; for details visit <https://gnu.org/licenses/gpl.html>." << "\n";
    std::cout << "\t" << "This is free software, and you are welcome to redistribute it" << "\n";
    std::cout << "\t" << "under certain conditions; visit <https://gnu.org/licenses/gpl.html> for details." << "\n";
    std::cout << "\n";

    // Author
    std::cout << "AUTHOR" << "\n";
    std::cout << "\t" << "Written by Andor Zoltan Fulop." << "\n";
    std::cout << "\n";
}
