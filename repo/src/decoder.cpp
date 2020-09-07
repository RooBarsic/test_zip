#include <iostream>
# include <algorithm>

# include "utills.h"
# include "alphabet.h"
# include "structures.h"


void init_decoder(Context *context, Alphabet *alphabet) {
}

void decode_file(Context *context, Alphabet *alphabet, std::string input_file_name, std::string output_file_name) {

    std::ifstream in(input_file_name);
    std::ofstream out(output_file_name);

    if(!in.is_open() || !out.is_open()) {
        return ;
    }

    std::vector<bool> bitstream;
    OutputContext outputContext;
    reset_output_ctx(&outputContext);

    InputContext inputContext;
    reset_input_ctx(&inputContext);
    std::string bit_buffer = "";
    int f;
#if DEBUG_MODE
    std::string prev_match = "";
    int match_sequence_counter = 0;
#endif
    while (has_next_bit(&inputContext) || in.peek() !=  EOF) {
        if (read_bit(&in, &inputContext))
            bit_buffer += "1";
        else
            bit_buffer += "0";

        if (context->letter_by_key.find(bit_buffer) != context->letter_by_key.end() ) {
            std::string letter = context->letter_by_key[bit_buffer];
#if 0 //DEBUG_MODE
            if (prev_match == bit_buffer)
                match_sequence_counter++;
            else 
                match_sequence_counter = 1;
            prev_match = bit_buffer;
            std::cout << " decoder ::::: got_match.  bits = " << bit_buffer << "   char = " << char(get_int_from_bits(letter)) << "   sequence = " << match_sequence_counter << '\n';
#endif
            fill_bitstream(&bitstream, letter);
            f = write_bitstream(&out, &outputContext, bitstream);
            bit_buffer = "";
        }
    }
#if DEBUG_MODE
    std::cout << " final f = " << f << '\n';
#endif
    while (f == 0) {
        f = write_bit(&out, &outputContext, 0);
    }

}



