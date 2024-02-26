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

#include <vector>
#include "Calculation/Network.h"

class Subnet
{
private:
    Network MainNetwork = Network(Address("169.254.0.0"), Address("255.255.0.0"));

public:
    Subnet(Network MainNetwork = Network(Address("169.254.0.0"), Address("255.255.0.0")));

    void SetNetwork(Network NewNetwork);

    std::vector<Network> DevideBySubnetCount(int RequiredSubnets);
    std::vector<Network> DevideByEqualHostCount(int RequiredHosts);
    std::vector<Network> DevideByMultipleSubnetCount(std::vector<int> RequiredHosts, std::vector<int> SubnetToBeDevided);
    std::vector<Network> DevideByCronologicalHostRequests(std::vector<int> RequiredHosts);

private:
    std::string GetFixNetworkAddressPart();
    int GetRequiredBits(int RequiredNetworks);
    bool IsCollide(std::vector<std::string> PreviouslyCalculated);
};
