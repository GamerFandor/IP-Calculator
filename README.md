# IP Calculator #

The IP Calculator offers a comprehensive solution for subnetting and obtaining information about IP addresses. With its capability to divide a large network into smaller subnets, it makes managing and organizing your network simple. The calculator also has a feature that can quickly identify whether an IP address is classful or classless, providing a clear picture of your network's structure. In addition to calculating the number of subnets and host addresses per subnet, it can also create custom subnet masks. The Command Line Interface (CLI) enables easy input of IP addresses and provides concise and easily understandable outputs.

If you have any feedback or suggestions, please let me know by opening an [issue](https://github.com/GamerFandor/IP-Calculator/issues) on GitHub.

# How to use #

You can use the `-h` or `--help` arguments or the `man` command if you installed the .deb package for printing the manual.
```ip-calculator -h```
```ip-calculator --help```
```man ip-calculator``` 

# Installation #

#### Install the .deb package ####
    
```
# Download the package
wget https://github.com/GamerFandor/IP-Calculator/releases/download/v1.0.0/IP-Calculator_1.0.0-1_amd64.deb

# Install the .deb package
sudo dpkg -i IP-Calculator_1.0.0-1_amd64.deb

# Remove the .deb file 
rm IP-Calculator_1.0.0-1_amd64.deb

# Check whether the installation was successful
ip-calculator
```

#### Download and use on Linux ####
    
```
# Download the compiled program
wget https://github.com/GamerFandor/IP-Calculator/releases/download/v1.0.0/ip-calculator

# Check whether the program downloaded successfully
ip-calculator
```

#### Build yourself on Linux ####

```
# Install clang 
sudo apt-get update && sudo apt-get install clang -y

# Download the Source files
wget https://github.com/GamerFandor/IP-Calculator/archive/refs/tags/v1.0.0.tar.gz

# Extract the .tar.gz file
tar -xf v1.0.0.tar.gz

# Enter the directory
cd IP-Calculator-1.0.0

# Run the build script
./Build.sh -v

# Check whether the program compiled successfully
./Binary/ip-calculator
```

#### Build yourself on Windows ####

1. Download clang from [here](https://prereleases.llvm.org/win-snapshots/LLVM-12.0.0-6923b0a7-win64.exe) and install it
2. Download the Source files from [here](https://github.com/GamerFandor/IP-Calculator/archive/refs/tags/v1.0.0.zip)
3. UnZip the downloaded file
4. Open a Command Prompt
5. Navigate to the UnZiped directory
6. Run the build script:
```.\Build.bat```
7. Check whether the program compiled successfully
```.\Binary\ip-calculator.exe```
