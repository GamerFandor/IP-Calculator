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
#include "Print/Print.h"
#include "Calculation/Subnet.h"
#include "Calculation/Convert.h"

Subnet::Subnet(Network MainNetwork)
{
    this->MainNetwork = MainNetwork;
}

void Subnet::SetNetwork(Network NewNetwork)
{
    this->MainNetwork = NewNetwork;
}

std::vector<Network> Subnet::DevideBySubnetCount(int RequiredSubnets)
{
    int RequiredBits = this->GetRequiredBits(RequiredSubnets);

    // Generate the new netmask
    std::string NewMaskString = this->MainNetwork.GetNetworkMask().GetInBinary().substr(0, this->MainNetwork.GetNetworkMask().GetInBinary().find("0"));
    for (int i = 0; i < RequiredBits; i++)
        NewMaskString = NewMaskString + '1';
    int temp = 32 - NewMaskString.length();
    for (int i = 0; i < temp; i++)
        NewMaskString = NewMaskString + '0';

    // Generate subnet network addresses
    std::vector<Network> nets;

    for (int i = 0; i < pow(2, RequiredBits); i++)
    {
        std::string ip = this->GetFixNetworkAddressPart();

        ip = ip + Convert::ExtendBinary(Convert::DecimalToBinary(i), RequiredBits);

        temp = 32 - ip.length();
        for (int j = 0; j < temp; j++)
            ip = ip + '0';

        nets.push_back(Network(Address(ip, false), Address(NewMaskString, false)));
    }
    
    return nets;
}

std::vector<Network> Subnet::DevideByEqualHostCount(int RequiredHosts)
{
    int HostBits = GetRequiredBits(RequiredHosts + 2);

    // Generate the new netmask
    std::string NewMaskString = this->MainNetwork.GetNetworkMask().GetInBinary().substr(0, this->MainNetwork.GetNetworkMask().GetInBinary().find("0"));
    int SubnetIdBits = 32 - (NewMaskString.length() + HostBits);
    for (int i = 0; i < SubnetIdBits; i++)
        NewMaskString += "1";
    int temp = 32 - NewMaskString.length();
    for (int i = 0; i < temp; i++)
        NewMaskString = NewMaskString + '0';

    // Generate subnet network addresses
    std::vector<Network> nets;

    for (int i = 0; i < pow(2, SubnetIdBits); i++)
    {
        std::string ip = this->GetFixNetworkAddressPart();

        ip = ip + Convert::ExtendBinary(Convert::DecimalToBinary(i), SubnetIdBits);

        temp = 32 - ip.length();
        for (int j = 0; j < temp; j++)
            ip = ip + '0';

        nets.push_back(Network(Address(ip, false), Address(NewMaskString, false)));
    }
    
    return nets;
}

std::vector<Network> Subnet::DevideByMultipleSubnetCount(std::vector<int> RequiredHosts, std::vector<int> SubnetToBeDevided)
{   
    std::vector<Network> Output;
    
    Network NetowrkToBeDevided = this->MainNetwork;

    for (int i = 0; i < RequiredHosts.size(); i++)
    {        
        auto temp = Subnet(NetowrkToBeDevided).DevideBySubnetCount(RequiredHosts[i]);


        if (RequiredHosts.size() - 1 == i)
        {       
            Output.insert(Output.end(), temp.begin(), temp.end());
        }
        else
        {
            NetowrkToBeDevided = temp[SubnetToBeDevided[i] - 1];
            for (int j = 0; j < temp.size(); j++)
            {  
                if (temp[j] == NetowrkToBeDevided) continue;
                Output.push_back(temp[j]);
            }
        }
    }

    return Output;
}

std::vector<Network> Subnet::DevideByCronologicalHostRequests(std::vector<int> RequiredHosts)
{
    std::vector<Network> nets;

    std::vector<std::string> PreviouslyCalculated; 
    
    do
    {
        for (int i = 0; i < RequiredHosts.size(); i++)
        {
            std::string GivenNetwork = GetFixNetworkAddressPart();
            std::string HostID(GetRequiredBits(RequiredHosts[i] + 2), '0');
            std::string Calculateable(32 - GivenNetwork.length() - HostID.length(), '0');

            for (auto Previous : PreviouslyCalculated)
            {
                std::string TempCalc;
                std::string TempPrev;

                if (Calculateable.length() > Previous.length())
                {
                    TempCalc = Calculateable.substr(0, Previous.length());
                    TempPrev = Previous;
                }
                else
                {
                    TempCalc = Calculateable;
                    TempPrev = Previous.substr(0, Calculateable.length());
                }
                
                while (Convert::BinaryToDecimal(TempCalc) == Convert::BinaryToDecimal(TempPrev))
                {   
                    TempCalc = Convert::ExtendBinary(Convert::DecimalToBinary(Convert::BinaryToDecimal(TempCalc) + 1), TempPrev.length());
                }

                for (int i = 0; i < TempCalc.length(); i++)
                    Calculateable[i] = TempCalc[i];
            }
            
            PreviouslyCalculated.push_back(Calculateable);
            
            for (int i = 0; i < PreviouslyCalculated.size(); i++)
            {    
                for (int j = 0; j < PreviouslyCalculated.size() - 1; j++)
                {
                    if (PreviouslyCalculated[j].length() > PreviouslyCalculated[j + 1].length())
                    {
                        auto Temp = PreviouslyCalculated[j];
                        PreviouslyCalculated[j] = PreviouslyCalculated[j + 1];
                        PreviouslyCalculated[j + 1] = Temp;
                    }
                }
            }
            
            std::string Mask(32 - HostID.length(), '1');
            //std::cout << "\033[1;34m" << GivenNetwork << "\033[0m" << Calculateable << "\033[1;32m" << HostID << "\033[0m\n";
            nets.push_back(Network(Address(GivenNetwork + Calculateable + HostID, false), Address(Mask + HostID, false)));
        }
    } while (IsCollide(PreviouslyCalculated));

    return nets;
}

std::string Subnet::GetFixNetworkAddressPart()
{
    return this->MainNetwork.GetNetworkAddress().GetInBinary().substr(0, this->MainNetwork.GetNetworkMask().GetInBinary().find("0"));
}

int Subnet::GetRequiredBits(int RequiredNetworks)
{
    int i = 1;

    while (!(pow(2, i) >= RequiredNetworks))
        i++;

    return i;    
}

bool Subnet::IsCollide(std::vector<std::string> PreviouslyCalculated)
{
    for (int i = 0; i < PreviouslyCalculated.size(); i++)
    {
        for (int j = 0; j < PreviouslyCalculated.size(); j++)
        {
            if (i == j) continue;
            
            std::string TempCalc;
            std::string TempPrev;

            if (PreviouslyCalculated[i].length() > PreviouslyCalculated[j].length())
            {
                TempCalc = PreviouslyCalculated[i].substr(0, PreviouslyCalculated[j].length());
                TempPrev = PreviouslyCalculated[j];
            }
            else
            {
                TempCalc = PreviouslyCalculated[i];
                TempPrev = PreviouslyCalculated[j].substr(0, PreviouslyCalculated[i].length());
            }

            if (Convert::BinaryToDecimal(TempCalc) == Convert::BinaryToDecimal(TempPrev))
            {
                return true;
            }
        }
    }
    return false;
}