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

#include <stdlib.h>
#include "Address.h"
#include "Convert.h"
#include "Print/Print.h"

Address::Address(std::string addr, bool IsDecimal)
{
	if (IsDecimal)
	{
		if (!this->IsValidAddress(addr))
		{
			Print::Error("The given address is not valid!");
			Print::Information("You can use \"--help\" argument for more information.");
			exit(0);
		}

		std::string AddressInBin = "";
		std::string temp = "";
		for (int i = 0; i < addr.length(); i++)
		{
			if (addr[i] == '.')
			{
				if (std::stoi(temp) > 255 || std::stoi(temp) < 0)
				{
					Print::Error("The given address is not valid!");
					Print::Information("You can use \"--help\" argument for more information.");
					exit(0);
				}
				AddressInBin = AddressInBin + Convert::ExtendBinary(Convert::DecimalToBinary(std::stoi(temp)), 8);
				temp = "";
				continue;
			}

			temp = temp + addr[i];
		}

		if (std::stoi(temp) > 255 || std::stoi(temp) < 0)
		{
			Print::Error("The given address is not valid!");
			Print::Information("You can use \"--help\" argument for more information.");
			exit(0);
		}
		AddressInBin = AddressInBin + Convert::ExtendBinary(Convert::DecimalToBinary(std::stoi(temp)), 8);

		this->address[0] = Convert::BinaryToDecimal(AddressInBin.substr(0, 8));
		this->address[1] = Convert::BinaryToDecimal(AddressInBin.substr(8, 8));
		this->address[2] = Convert::BinaryToDecimal(AddressInBin.substr(16, 8));
		this->address[3] = Convert::BinaryToDecimal(AddressInBin.substr(24, 8));
	}
	else
	{
		if (addr.length() != 32)
		{
			Print::Error("The given address is not valid!");
			Print::Information("You can use \"--help\" argument for more information.");
			exit(0);
		}
		this->address[0] = Convert::BinaryToDecimal(addr.substr(0, 8));
		this->address[1] = Convert::BinaryToDecimal(addr.substr(8, 8));
		this->address[2] = Convert::BinaryToDecimal(addr.substr(16, 8));
		this->address[3] = Convert::BinaryToDecimal(addr.substr(24, 8));
	}
}

std::string Address::GetInDecimal() const
{
	return std::to_string(this->address[0]) + "." + std::to_string(this->address[1]) + "." + std::to_string(this->address[2]) + "." + std::to_string(this->address[3]);
}

std::string Address::GetInBinary() const
{
	return Convert::ExtendBinary(Convert::DecimalToBinary(this->address[0]), 8) + Convert::ExtendBinary(Convert::DecimalToBinary(this->address[1]), 8) + Convert::ExtendBinary(Convert::DecimalToBinary(this->address[2]), 8) + Convert::ExtendBinary(Convert::DecimalToBinary(this->address[3]), 8);
}

bool Address::Equal(const Address &Other) const
{
	for (int i = 0; i < this->GetInBinary().length(); i++)
	{
		if (int(this->GetInBinary()[i]) != int(Other.GetInBinary()[i]))
			return false;
	}

	return true;
}

bool Address::operator==(const Address &Other) const
{
	return this->Equal(Other);
}

bool Address::IsValidAddress(std::string addr)
{
	// Check is there dots next to each other
	if (addr.find("..") != std::string::npos)
		return false;

	// Check is there only 3 dots in the address
	int AmountOfDots = 0;
	for (int i = 0; i < addr.length(); i++)
		if (addr[i] == '.')
			AmountOfDots++;

	if (AmountOfDots != 3)
		return false;

	// Check the address not starts and not ends with dot
	if (!addr.find(".", 0) || !addr.find(".", addr.length() - 1))
		return false;

	return true;
}
