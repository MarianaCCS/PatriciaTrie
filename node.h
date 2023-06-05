#include <iostream>

struct Node{
    Node* children[256];
    std::string prefix;
    bool endWord;

    Node():endWord(false){
        for (int i=0; i<256; i++) children[i] = nullptr;
    }
};