#include "HCTree.hpp"
#include "Helper.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

const string PARAMS_ERROR = "ERROR: Incorrect parameters";
const string NO_FILE_ERROR = "ERROR: File not found.";
const string USAGE_MESSAGE = "USAGE: ./uncompress <compressed_file> <uncompressed_file>"; 

int main(int argc, char* argv[]){
    if(argc != 3){
        cout << PARAMS_ERROR << endl << USAGE_MESSAGE << endl;
    }

    FancyInputStream compFile(argv[1]);
    //checking if the file is empty
    if(compFile.filesize() == 0){
        FancyOutputStream emptyFile(argv[2]);
        return 0;
    }
    if(!compFile.good()){
        return -1;
    }

    //Read the first 256 bytes as the frequencies for the Huffman Tree
    vector<int> uncompFreq(256, 0);
    //int numOfChars = 0;
    for(int i = 0; i < 256; i++){
        int letterFreq = compFile.read_int();
        if(letterFreq == -1){
            break;
        }
        uncompFreq[i] = letterFreq;
        //numOfChars += uncompFreq[i];
    }

    //Reconstruct the Huffman Tree using the frequencies
    HCTree reconHufTree;
    reconHufTree.build(uncompFreq);

    //Open output file and decode the bits.
    FancyOutputStream uncompFile(argv[2]);
    int numOfSymbolsToDecode = reconHufTree.getRoot()->count;

    for(int i = 0; i < numOfSymbolsToDecode; i++){
        unsigned char decodedSymbol = reconHufTree.decode(compFile);
        uncompFile.write_byte(decodedSymbol);
    }

    return 0;
}
