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

class Address
{
private:
	int address[4];

public:
	Address(std::string addr = "0.0.0.0", bool IsDecimal = true);

	std::string GetInDecimal() const;
	std::string GetInBinary() const;

	bool Equal(const Address &Other) const;
	bool operator==(const Address &Other) const;

private:
	bool IsValidAddress(std::string addr);
};
