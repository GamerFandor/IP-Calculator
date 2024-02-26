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

#include "Convert.h"
#include <cmath>
#include <iostream>

std::string Convert::DecimalToBinary(int Decimal)
{
	std::string Temp = "";
	int Index = 0;

	while (Decimal > 0)
	{
		if (Decimal % 2 == 0)
		{
			Temp = Temp + "0";
			Decimal -= Decimal / 2;
		}
		else
		{
			Temp = Temp + "1";
			Decimal -= ceil((float)Decimal / 2);
		}
		Index++;
	}
	
	Index = Temp.length() - 1;
	std::string Output = "";

	for (int i = 0; i < Temp.length(); i++)
	{
		Output = Output + Temp[Index];
		Index--;
	}

	return Output;
}

int Convert::BinaryToDecimal(std::string Binary)
{
	int Sum = 0;

	for (int i = 0; i < Binary.length(); i++)
		if (Binary[i] == '1')
			Sum += pow(2, Binary.length() - 1 - i);
	
	return Sum;
}

std::string Convert::ExtendBinary(std::string Binary, int NewLength)
{
	std::string Output = "";

	for (int i = 0; i < NewLength - Binary.length(); i++)
		Output = Output + "0";

	Output += Binary;

	return Output;
}
