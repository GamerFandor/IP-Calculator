#! /bin/bash

# Collect every source file
Source=$(find ./Source -name *.cpp)
if [[ $1 == "-v" || $1 == "--verbose" ]]; then
	echo -e "[ \033[1;34mi\033[0m ] Every \"*.cpp\" file collected from \"Source\" folder."
fi

# Make 'Binary' folder if it does not exist
if [[ $1 == "-v" || $1 == "--verbose" ]]; then
	if [ -d "./Binary/" ]; then
		echo -e "[ \033[1;34mi\033[0m ] Binary folder already exists."
	else
		echo -e "[ \033[1;34mi\033[0m ] Binary folder has been created"
	fi
fi
mkdir -p Binary

# Compile the files
if [[ $1 == "-v" || $1 == "--verbose" ]]; then
	echo -e "[ \033[1;34mi\033[0m ] Staring the building process."
	clang++ $Source -g -o Binary/ip-calculator -ISource
else
	clang++ $Source -o Binary/ip-calculator -ISource
fi

# If there are errors then print it to the screen and exit the program
Error=$?
if [ $Error -ne 0 ]; then
	echo -e "[ \033[1;31mx\033[0m ] Failed to build the project. Errorcode: "$Error && exit
fi

# Print a success text
echo -e "[ \033[1;32m+\033[0m ] Binary files successfully created!"
