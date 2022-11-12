#! /bin/bash

### Informations about the pakcage and the app ##############################################

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

FullPackageName=$AppName"_"$AppVersion"-"$PackageVersion"_"$Architecture

mkdir -p ./$FullPackageName/usr/local/bin
cp $AppBinaryPath ./$FullPackageName/usr/local/bin

mkdir -p ./$FullPackageName/usr/share/man/man1
cp $ManpagePath ./$FullPackageName/usr/share/man/man1/$AppName.1

gzip ./$FullPackageName/usr/share/man/man1/$AppName.1 ./$FullPackageName/usr/share/man/man1/$AppName.1.gz
rm ./$FullPackageName/usr/share/man/man1/$AppName.1

mkdir ./$FullPackageName/DEBIAN
cat << EOF > ./$FullPackageName/DEBIAN/control
Package: $AppName
Version: $AppVersion
Architecture: $Architecture
Maintainer: $Maintainer
Description: $Description
EOF

dpkg-deb --build --root-owner-group $FullPackageName
mv $FullPackageName.deb $PackageOutputPath
rm -r $FullPackageName
