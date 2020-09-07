# include <bits/stdc++.h>
# include <map>
# include <fstream>
# include <string>
# include <vector>
# include <unordered_map>
# include <algorithm>
# include <bitset>

# include "structures.h"

#ifndef SMART_ZIP_ENCODER_H

Node* build_huffman_tree(std::vector<Node> *nodes);

void fill_context(Node *node, Context *context, std::string key);

void init_encoder(Context *context, Alphabet *alphabet);

void encode_file(Context *context, Alphabet *alphabet, std::string input_file_name, std::string output_file_name);

#define SMART_ZIP_ENCODER_H

#endif //SMART_ZIP_ENCODER_H
