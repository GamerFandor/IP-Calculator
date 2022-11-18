#! /bin/bash

######################## Informations about the pakcage and the app #########################

AppName="IP-Calculator"
AppVersion="1.0.0"
PackageVersion="1"
Architecture="amd64"
Maintainer="Andor Zoltán Fülöp <https://github.com/GamerFandor/>"
Description="Calculates subnets and prints information about an IP address."

AppBinaryPath="./Binary/ip-calculator"
ManpagePath="./Miscellaneous/Manpage.1"
PackageOutputPath="./Binary/"

#############################################################################################

# Collect every source file
Source=$(find ./Source -name *.cpp)

# Make 'Binary' folder if it does not exist
mkdir -p Binary

# Compile the files
clang++ $Source -o ./Binary/ip-calculator -ISource

# If there are errors then print it to the screen and exit the program
Error=$?
if [ $Error -ne 0 ]; then
	echo -e "[ \033[1;31mx\033[0m ] Failed to build the project. Errorcode: "$Error && exit
fi

# Print a success text
echo -e "[ \033[1;32m+\033[0m ] Binary files successfully created!"

# Generate the full file name
FullPackageName=$AppName"_"$AppVersion"-"$PackageVersion"_"$Architecture

# Place the executable inside the package folder
mkdir -p ./$FullPackageName/usr/local/bin
cp $AppBinaryPath ./$FullPackageName/usr/local/bin

# Place the manpage inside the package folder
mkdir -p ./$FullPackageName/usr/share/man/man1
cp $ManpagePath ./$FullPackageName/usr/share/man/man1/$AppName.1

# Compress manpage
gzip ./$FullPackageName/usr/share/man/man1/$AppName.1 ./$FullPackageName/usr/share/man/man1/$AppName.1.gz

# Create control file
mkdir ./$FullPackageName/DEBIAN
cat << EOF > ./$FullPackageName/DEBIAN/control
Package: $AppName
Version: $AppVersion
Architecture: $Architecture
Maintainer: $Maintainer
Description: $Description
EOF

# Make the package
dpkg-deb --build --root-owner-group $FullPackageName
mv $FullPackageName.deb $PackageOutputPath

# Clean up
rm -r $FullPackageName
