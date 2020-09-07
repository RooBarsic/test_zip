# include <bits/stdc++.h>
# include <map>
# include <fstream>
# include <string>
# include <vector>
# include <unordered_map>
# include <algorithm>
# include <bitset>

# include "structures.h"

#ifndef SMART_ZIP_DECODER_H

void init_decoder(Context *context, Alphabet *alphabet);

void decode_file(Context *context, Alphabet *alphabet, std::string input_file_name, std::string output_file_name);

#define SMART_ZIP_ENCODER_H

#endif //SMART_ZIP_DECODER_H
