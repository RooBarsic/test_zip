# include <bits/stdc++.h>

#ifndef SMART_ZIP_STRUCTURES_H
#define SMART_ZIP_STRUCTURES_H

#define DEBUG_MODE 1

struct Context {
    std::unordered_map<std::string, std::string> key_by_letter;
    std::unordered_map<std::string, std::string> letter_by_key;

    Context() {key_by_letter, letter_by_key; }
};

struct Node {
    std::string letter;
    int frequency;
    Node *left;
    Node *right;
    Node() {left=NULL, right=NULL, letter="", frequency=0;}
};

struct Alphabet {
    int alphabet_size;
    std::unordered_map<std::string, int> letter_frequency;
    std::vector<std::string> letters;

    Alphabet() {letters, letter_frequency, alphabet_size=0;}
};


struct OutputContext {
    char bit_buffer;
    int cur_bit = 8;

    OutputContext() {bit_buffer, cur_bit;}
};

struct InputContext {
    int buff;
    int bit_id = 0;
    int char_id = 0;
    std::string row;

    InputContext() {buff, bit_id, char_id, row;}
};



#endif //SMART_ZIP_STRUCTURES_H
