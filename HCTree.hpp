#ifndef HCTREE_HPP
#define HCTREE_HPP
#include <queue>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "Helper.hpp"
using namespace std;

/**
 * A Huffman Code Tree class
 */
class HCTree {
    private:
        HCNode* root;
        vector<HCNode*> leaves;
        priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> HufTree;

    public:
        /**
         * Constructor, which initializes everything to null pointers
         */
        HCTree() : root(nullptr) {
            leaves = vector<HCNode*>(256, nullptr);
        }

        ~HCTree();

        /**
         * Use the Huffman algorithm to build a Huffman coding tree.
         * PRECONDITION: freqs is a vector of ints, such that freqs[i] is the frequency of occurrence of byte i in the input file.
         * POSTCONDITION: root points to the root of the trie, and leaves[i] points to the leaf node containing byte i.
         */
        void build(const vector<int>& freqs);

        /**
         * Write to the given FancyOutputStream the sequence of bits coding the given symbol.
         * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
         */
        void encode(unsigned char symbol, FancyOutputStream & out) const;

        /**
         * Return symbol coded in the next sequence of bits from the stream.
         * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
         */
        unsigned char decode(FancyInputStream & in) const;

        /**
         * Print out the Huffman Tree nodes in level-order traversal
         */
        void printHuffmanTreeNodeInfo();

        /**
         * Return a pointer to the root, used for serializing the tree 
         */
        HCNode* getRoot();
};
#endif // HCTREE_HPP
