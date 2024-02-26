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
#include <string>
#include <stdlib.h>
#include "Network.h"
#include "Print/Print.h"

Network::Network(Address IP, Address Mask, bool IsClasslessNetwork)
{
	this->NetworkIP = IP;
	if (IsClasslessNetwork)
	{
		this->Class = AddressClass::CLASSLESS;

		if (this->IsValidMask(Mask))
		{
			this->Netmask = Mask;
		}
		else
		{
			Print::Error("The given mask is not valid!");
			Print::Information("You can use \"--help\" argument for more information.");
			exit(0);
		}
	}
	else
	{
		if (IP.GetInBinary().substr(0, 1) == "0")
		{
			this->Class = AddressClass::CLASS_A;
			this->Netmask = Address("255.0.0.0");
		}
		else if (IP.GetInBinary().substr(0, 2) == "10")
		{
			this->Class = AddressClass::CLASS_B;
			this->Netmask = Address("255.255.0.0");
		}
		else if (IP.GetInBinary().substr(0, 3) == "110")
		{
			this->Class = AddressClass::CLASS_C;
			this->Netmask = Address("255.255.255.0");
		}
		else if (IP.GetInBinary().substr(0, 4) == "1110")
		{
			this->Class = AddressClass::CLASS_D;
			this->Netmask = Address("255.255.255.255");
		}
		else if (IP.GetInBinary().substr(0, 5) == "1111")
		{
			this->Class = AddressClass::CLASS_E;
			this->Netmask = Address("255.255.255.255");
		}
	}
}

void Network::SetNetwork(Address NewIP, Address NewMask, bool IsClasslessNetwork)
{
	this->NetworkIP = NewIP;
	if (IsClasslessNetwork)
	{
		this->Class = AddressClass::CLASSLESS;

		if (this->IsValidMask(NewMask))
		{
			this->Netmask = NewMask;
		}
		else
		{
			Print::Error("The given mask is not valid!");
			Print::Information("You can use \"--help\" argument for more information.");
			exit(0);
		}
	}
	else
	{
		if (NewIP.GetInBinary().substr(0, 1) == "0")
		{
			this->Class = AddressClass::CLASS_A;
			this->Netmask = Address("255.0.0.0");
		}
		else if (NewIP.GetInBinary().substr(0, 2) == "10")
		{
			this->Class = AddressClass::CLASS_B;
			this->Netmask = Address("255.255.0.0");
		}
		else if (NewIP.GetInBinary().substr(0, 3) == "110")
		{
			this->Class = AddressClass::CLASS_C;
			this->Netmask = Address("255.255.255.0");
		}
		else if (NewIP.GetInBinary().substr(0, 4) == "1110")
		{
			this->Class = AddressClass::CLASS_D;
			this->Netmask = Address("255.255.255.255");
		}
		else if (NewIP.GetInBinary().substr(0, 4) == "1111")
		{
			this->Class = AddressClass::CLASS_E;
			this->Netmask = Address("255.255.255.255");
		}
	}
}

Address Network::GetNetworkAddress() const
{	
	std::string ip = this->NetworkIP.GetInBinary().substr(0, this->Netmask.GetInBinary().find("0"));

	for (int i = 0; i < this->Netmask.GetInBinary().length(); i++)
		if (this->Netmask.GetInBinary()[i] == '0')
			ip = ip + "0";

	return Address(ip, false);
}

Address Network::GetNetworkMask() const
{
	return this->Netmask;
}

Address Network::GetFirstAddress() const
{
	std::string ip = this->NetworkIP.GetInBinary().substr(0, this->Netmask.GetInBinary().find("0"));

	for (int i = 0; i < this->Netmask.GetInBinary().length(); i++)
		if (this->Netmask.GetInBinary()[i] == '0')
			ip = ip + "0";

	ip[ip.length() - 1] = '1';

	return Address(ip, false);
}

Address Network::GetLastAddress() const
{
	std::string ip = this->NetworkIP.GetInBinary().substr(0, this->Netmask.GetInBinary().find("0"));

	for (int i = 0; i < this->Netmask.GetInBinary().length(); i++)
		if (this->Netmask.GetInBinary()[i] == '0')
			ip = ip + "1";

	ip[ip.length() - 1] = '0';

	return Address(ip, false);
}

Address Network::GetBroadcastAddress() const
{
	std::string ip = this->NetworkIP.GetInBinary().substr(0, this->Netmask.GetInBinary().find("0"));

	for (int i = 0; i < this->Netmask.GetInBinary().length(); i++)
		if (this->Netmask.GetInBinary()[i] == '0')
			ip = ip + "1";

	return Address(ip, false);
}

int Network::GetAvailableHosts() const
{
	int HostBits = 0;
	for (int i = 0; i < this->Netmask.GetInBinary().length(); i++)
		if (this->Netmask.GetInBinary()[i] == '0')
			HostBits++;

	return pow(2, HostBits) - 2;
}

std::string Network::GetClass() const
{
	switch (this->Class)
	{
	case AddressClass::CLASS_A:
		return "Class A";

	case AddressClass::CLASS_B:
		return "Class B";

	case AddressClass::CLASS_C:
		return "Class C";
	
	case AddressClass::CLASS_D:
		return "Class D";

	case AddressClass::CLASS_E:
		return "Class E";

	case AddressClass::CLASSLESS:
		return "Classless";

	default:
		return "Classless";
	}

	return "Classless";
}

AddressClass Network::GetClassEnum() const
{
	return this->Class;
}

bool Network::Equal(const Network &Other) const
{
	return this->GetNetworkAddress() == Other.GetNetworkAddress() && this->GetNetworkMask() == Other.GetNetworkMask();
}

bool Network::operator==(const Network &Other) const
{
	return this->Equal(Other);
}

bool Network::IsValidMask(Address Mask)
{
	for (int i = 1; i < Mask.GetInBinary().length(); i++)
	{
		if (Mask.GetInBinary()[i - 1] == '1' && Mask.GetInBinary()[i] == '1')
			continue;

		if (Mask.GetInBinary()[i - 1] == '1' && Mask.GetInBinary()[i] == '0')
			continue;

		if (Mask.GetInBinary()[i - 1] == '0' && Mask.GetInBinary()[i] == '0')
			continue;
		
		if (Mask.GetInBinary()[i - 1] == '0' && Mask.GetInBinary()[i] == '1')
			return false;
	}

	return true;
}
