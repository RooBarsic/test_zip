# include <iostream>
# include <fstream>
# include <algorithm>

# include "structures.h"

std::string get_bits_str(char e) {
    std::string bits_str = "";
    long long mask = int(e);
    for (int i = 7; i >= 0; i--) {
        if (mask & (1 << i))
            bits_str += "1";
        else
            bits_str += "0";
    }
    return bits_str;
}

int get_int_from_bits(std::string bits) {
    long long mask = 0;
    for (int i = 0, sz = int(bits.size()); i < sz; i++) {
        mask <<= 1;
        if (bits[i] == '1')
            mask |= 1;
    }
    return mask;
}

void reset_output_ctx(OutputContext *out_ctx) {
    out_ctx->bit_buffer = 0;
    out_ctx->cur_bit = 8;
}

/** write single bit to output
 */
int write_bit(std::ofstream *out, OutputContext *out_ctx, bool bit) {
    // cout << bit;
    out_ctx->cur_bit--;
    if (bit)
        out_ctx->bit_buffer |= (1 << out_ctx->cur_bit);
    if (out_ctx->cur_bit == 0) {
        *out << char(out_ctx->bit_buffer);
        out_ctx->bit_buffer = 0;
        out_ctx->cur_bit = 8;
        return 1;
    }
    return 0;
}

int write_bitstream(std::ofstream *out, OutputContext *out_ctx, std::vector<bool> bits) {
    int last = 1;
    for (int i = 0; i < bits.size(); i++) {
        last = write_bit(out, out_ctx, bits[i]);
    }
    return last;
}

std::string print_bits(std::string buff) {
    std::string res = "";
    for (int i = 0; i < buff.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            if(int(buff[i]) & (1 << j))
                res += "1";
            else
                res += "0";
        }
    }
    return res;
}

int read_bit(std::ifstream *in, InputContext *in_ctx) {
    if (in_ctx->bit_id == 0) {
        if (in_ctx->char_id >= in_ctx->row.size()) {
            //std::getline(*in, in_ctx->row);
            char e;
            (*in).get(e);
            in_ctx->row = "";
            in_ctx->row += e;
            // if (in->peek() != EOF) {
            //     in_ctx->row += "\n";
            // }
#if 0 //DEBUG_MODE
            std::cout << "\n I readed row = |" << in_ctx->row << "|   bits = |" << print_bits(in_ctx->row) << "| \n";
#endif
            in_ctx->char_id = 0;
        }
        in_ctx->buff = (int) in_ctx->row[ in_ctx->char_id ];
        in_ctx->bit_id = 8;
        in_ctx->char_id++;
    }
    in_ctx->bit_id--;
    if (in_ctx->buff & (1 << in_ctx->bit_id))
        return 1;
    return 0;
}

void reset_input_ctx(InputContext *in_ctx) {
    in_ctx->bit_id = 0;
    in_ctx->char_id = 0;
    in_ctx->row = "";
}

bool has_next_bit(InputContext *in_ctx) {
    if (in_ctx->char_id < in_ctx->row.size() || in_ctx->bit_id > 0 )
        return true;
    return false;
}

void fill_bitstream(std::vector<bool> *bits, std::string bits_str) {
    bits->clear();
    for (int i = 0, sz = int(bits_str.size()); i < sz; i++) {
        bits->push_back((bits_str[i] == '1'));
    }
}
