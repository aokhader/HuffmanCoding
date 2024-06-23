# HuffmanCoding
## Description
Using the program and after you build the programs for compression and uncompression. you can compress and uncompress arbitrary input files using the Huffman Encoding compression. 

## Assumptions
This program assumes you are running on a Linux machine or a virtual Linux machine such as WSL. If you are running on a Windows then use a virtual Linux machine to run the program, or install a package that allows you to run a makefile if you want to use the ease of running it. 

It also assumes that the characters in the input file comes from the 256 ASCII characters.

## Usage
After running the makefile using the command ``make``, you get two executables, one for each command you want to do: ``./compress`` and ``./uncompress``. The usage of the two executables are shown below:
```
./compress <original_file> <compressed_file_name>
./uncompress <compressed_file> <uncompressed_file_name>
```

