# IP Calculator #

## Installation ##
### Build it yourself ###
1. Install git and clang
```bash
$ sudo apt update && sudo apt install git && sudo apt install clang
```
2. Clone the repository
```bash
$ git clone https://github.com/...
```
3. Run `Build.sh`
```bash
$ ./IP-Calculator/Build.sh
```
If you do everything correctly then there will be the executable in the `./IP-Calculator/Binary` directory.

### Download the precompiled `.deb` package  ###
1. Download the `.deb` package which you can find under the releases tab on Github
2. Install the package
```bash
$ dpkg -i IP-Calculator.deb
```
If you do everything correctly then there will be the executable in the `/bin` directory. So you can use it anywhere.
