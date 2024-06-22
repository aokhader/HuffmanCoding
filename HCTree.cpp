#include "HCTree.hpp"
#include "Helper.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack> 

void postOrderTraversal(HCNode* current){
    if(current == nullptr){
        return;
    }
    postOrderTraversal(current->c0);
    postOrderTraversal(current->c1);
    delete current;
}

HCTree::~HCTree(){
    postOrderTraversal(root);
    leaves.clear();
}

/**
 * Use the Huffman algorithm to build a Huffman coding tree.
 * PRECONDITION: freqs is a vector of ints, such that freqs[i] is the frequency of occurrence of byte i in the input file.
 * POSTCONDITION: root points to the root of the trie, and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
    //Creating nodes for frequencies > 0
    for(int i = 0; i < 256; i++){
        if(freqs[i] > 0){
            unsigned char letter = i;
            HCNode* node = new HCNode(freqs[i], letter);
            HufTree.push(node);
            leaves[i] = node;
        }
    }

    //left child = lower freq = 0 child
    while(HufTree.size() > 1){
        HCNode* leftChild = HufTree.top();
        HufTree.pop();
        HCNode* rightChild = HufTree.top();
        HufTree.pop();

        unsigned char newSymbol = leftChild->symbol;
        int newFreq = leftChild->count + rightChild->count;
        HCNode* newNode = new HCNode(newFreq, newSymbol);
        newNode->c0 = leftChild;
        newNode->c1 = rightChild;

        leftChild->p = newNode;
        rightChild->p = newNode;

        HufTree.push(newNode);
    }

    //If queue is empty, then there was nothing to begin with i.e. a empty file
    if(HufTree.size() == 0){
        return;
    }

    //now only the root remains
    root = HufTree.top();  
    HufTree.pop();  
}


/**
 * Write to the given FancyOutputStream the sequence of bits coding the given symbol.
 * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const{
    //We have the tree, so traverse the tree STARTING from the leaf to the root
    HCNode* path = leaves[symbol];
    if(path == nullptr){
        return;
    }
    stack<HCNode*> reverseEncoding;
    reverseEncoding.push(path);

    while(path->p != nullptr){
        reverseEncoding.push(path->p);
        path = path->p;
    }

    //now all the nodes are in the stack, starting from the root
    while(reverseEncoding.size() > 1){
        HCNode* parent = reverseEncoding.top();
        reverseEncoding.pop();
        HCNode* child = reverseEncoding.top();

        if(parent->c0 == child){
            //put 0 into the bitwise buffer
            out.write_bit(0);
        }
        if(parent->c1 == child){
            //put 1 into the bitwise buffer
            out.write_bit(1);
        }
    }
}


/**
 * Return symbol coded in the next sequence of bits from the stream.
 * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
 */
unsigned char HCTree::decode(FancyInputStream & in) const{
    HCNode* current = root;
    /*
    char bit = 0;
    while((bit = in.read_bit()) != -1){
        if(bit == 0){
            current = current->c0;
        }
        else if(bit == 1){
            current = current->c1;
        }
        if(current->c0 == nullptr && current->c1 == nullptr){
            return current->symbol;
        }
    }
    */
    
    while(!(current->c0 == nullptr) && !(current->c1 == nullptr)){
        int bit = in.read_bit();
        if(bit == 0){current = current->c0;}
        else if(bit == -1){
            break;
        }
        else if(bit == 1){current = current->c1;}
    }
    
    return current->symbol;
}

/**
 * Print out the Huffman Tree nodes in level-order traversal
 */
void HCTree::printHuffmanTreeNodeInfo(){
    queue<HCNode*> output;
    output.push(root);


    while(!output.empty()){
        //putting the children in the queue in order
        HCNode* current = output.front();
        output.pop();
        cout << "(" << current->symbol << ", " << current->count << ")" << endl;

        if(current->c0 != nullptr){
            output.push(current->c0);
        }
        if(current->c1 != nullptr){
            output.push(current->c1);
        }

        //check if there is a left child in the next level first
        if(current->c0 != nullptr){
            current = current->c0;
        }
        else if(current->c1 != nullptr){
            current = current->c1;
        }
    }

    while(!output.empty()){
        HCNode* inOrderNode = output.front();
        output.pop();
        cout << "(" << inOrderNode->symbol << ", " << inOrderNode->count << ")" << endl;
    }
}
HCNode* HCTree::getRoot(){
    return root;
}
