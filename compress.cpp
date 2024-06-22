#include "HCTree.hpp"
#include "Helper.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

const char* PARAMS_ERROR = "Incorrect parameters. \nUSAGE: ./uncompress <compressed_file> <uncompressed_file>";
const char* NO_FILE_ERROR = "File not found.";
const char* DEST_FILE_ERROR = "Unable to write to destination file.";

int main(int argc, char* argv[]){
    if(argc != 3){
        error(PARAMS_ERROR);    
    }

    FancyInputStream encodeFile(argv[1]);
    if(!encodeFile.good()){
        error(NO_FILE_ERROR);
    }
    FancyOutputStream destFile(argv[2]);
    if(!destFile.good()){
        error(DEST_FILE_ERROR);
    }

    int fileSize = encodeFile.filesize();
    vector<int> frequencies(256,0);
    int symbolFreq;
    while((symbolFreq = encodeFile.read_byte()) != -1){
        frequencies[symbolFreq]++;
    }
    
    //Now that we have the frequencies, we can create the Huffman Tree
    HCTree HuffmanTree;
    HuffmanTree.build(frequencies);

    //If the Huffman Tree is empty then the file is empty
    if(HuffmanTree.getRoot() == nullptr){
        return 0;
    }

    /**
     * Now write the file header.
     * Consists of the frequencies we need to make the Huffman Tree
     */ 
    for(int i = 0; i < 256; i++){
        destFile.write_int(frequencies[i]);
    }

    //Now that we have the tree, encode the file
    //Resetting the input stream to be able to encode the characters
    encodeFile.reset();
    if(!encodeFile.good()){
        error("File is not good. Check flags.");
    }

    for(int i = 0; i < fileSize; i++){
        char letterToEncode = encodeFile.read_byte();
        HuffmanTree.encode(letterToEncode, destFile);
    }
  
    return 0;
}
