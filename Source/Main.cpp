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

#include <iostream>
#include "Print/Print.h"
#include "Calculation/Subnet.h"
#include "Arguments/Arguments.h"
#include "Calculation/Convert.h"
#include "Calculation/Address.h"

int main(int argc, char **argv)
{
	// Read arguments
	Arguments args = Arguments(argc, argv);

	if (args.GetArgCount() == 0)
	{
		Print::Version();
		return 0;
	}

	// Declare necessary variable
	Network MainNetwork;
	Subnet Sub;
	std::vector<Network> Output;

	// Decide what the program has to do
	switch (args.GetTask())
	{
	// Printing version
	case Task::TASK_PRINTVERSION:
		Print::Version();
		break;

	// Printing help
	case Task::TASK_PRINTHELP:
		Print::Help();
		break;
	
	// Printing details about an IP address
	case Task::TASK_PRINTDETAILS:
		MainNetwork.SetNetwork(Address(args.GetIP()), Address("0.0.0.0"), false);
		Print::DetailsTable(MainNetwork);
		break;

	// Printing details about a classless IP address
	case Task::TASK_PRINTCLASSLESSDETAILS:
		MainNetwork.SetNetwork(Address(args.GetIP()), Address(args.GetMask()));
		Print::DetailsTable(MainNetwork);
		break;

	// Devide the netwrok into given parts
	case Task::TASK_CALCULATEBYSUBNET:
		MainNetwork.SetNetwork(Address(args.GetIP()), Address(args.GetMask()));
		Sub.SetNetwork(MainNetwork);
		Output = Sub.DevideBySubnetCount(args.GetRequiredSubnets());

		Print::Table(Output);
		break;
	
	// Devide the network by the given host amount
	case Task::TASK_CALCULATEBYHOST:
		MainNetwork.SetNetwork(Address(args.GetIP()), Address(args.GetMask()));
		Sub.SetNetwork(MainNetwork);
		Output = Sub.DevideByEqualHostCount(args.GetRequiredHosts());

		Print::Table(Output);
		break;
	
	// Devide the network by the given hosts per network
	case Task::TASK_CALCULATEBYMULTIPLESUBNETS:
		MainNetwork.SetNetwork(Address(args.GetIP()), Address(args.GetMask()));
		Sub.SetNetwork(MainNetwork);
		Output = Sub.DevideByMultipleSubnetCount(args.GetRequiredHostsList(), args.GetSubnetIndexToBeDevided());

		Print::Table(Output);
		break;

	// Devide the network by cronological subnetwork request
	case Task::TASK_CALCULATEBYCRONOLOGICAL:
		MainNetwork.SetNetwork(Address(args.GetIP()), Address(args.GetMask()));
		Sub.SetNetwork(MainNetwork);
		Output = Sub.DevideByCronologicalHostRequests(args.GetRequiredHostsListForCronology());

		Print::Table(Output);
		break;

	// Any case of detecting task wrongly the program will print the version
	default:
		Print::Version();
		break;
	}

	// Return 0 if the program successfully complited its job
	return 0;
}
