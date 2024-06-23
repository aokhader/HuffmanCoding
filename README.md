# HuffmanCoding
## Description
Using the program and after you build the programs for compression and uncompression. you can compress and uncompress arbitrary input files using the Huffman Encoding compression technique.

## Assumptions
This program assumes you are running on a Linux machine or a virtual Linux machine such as Ubuntu's WSL. If you are running on a Windows then use a virtual Linux machine to run the program, or install a package that allows you to run a makefile if you want to use the ease of running it. To get Ubuntu, you follow the instructions in this [link](https://ubuntu.com/desktop/wsl).

To run the makefile without installing Ubuntu's WSL, install [GNU make](https://www.gnu.org/software/make/) with [chocolatey](https://chocolatey.org/install) to add ``make`` to the global path and runs on all Command Line Interfaces (powershell, git bash, cmd, etc…), then run the command ``choco install make``.

It also assumes that the characters in the input file comes from the 256 ASCII characters.

## Usage
After running the makefile using the command ``make``, you get two executables, one for each command you want to do: ``./compress`` and ``./uncompress``. The usage of the two executables are shown below:
```
./compress <original_file> <compressed_file_name>
./uncompress <compressed_file> <uncompressed_file_name>
```

