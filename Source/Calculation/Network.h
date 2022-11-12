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

#include "Address.h"

enum AddressClass
{
	CLASS_A,
	CLASS_B,
	CLASS_C,
	CLASS_D,
	CLASS_E,
	CLASSLESS
};

class Network
{
private:
	Address NetworkIP = Address();
	Address Netmask = Address();
	AddressClass Class = AddressClass::CLASSLESS;

public:
	Network(Address IP = Address("169.254.0.0"), Address Mask = Address("255.255.0.0"), bool IsClasslessNetwork = true);
	
	void SetNetwork(Address NewIP, Address NewMask, bool IsClasslessNetwork = true);

	Address GetNetworkAddress() const;
	Address GetNetworkMask() const;
	Address GetFirstAddress() const;
	Address GetLastAddress() const;
	Address GetBroadcastAddress() const;
	std::string GetClass() const;
	AddressClass GetClassEnum() const;
	int GetAvailableHosts() const;

	bool Equal(const Network &Other) const;
	bool operator==(const Network &Other) const;

private:
	bool IsValidMask(Address Mask);
};
