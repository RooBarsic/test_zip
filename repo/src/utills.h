# include "string"
# include "vector"
#include "structures.h"
#ifndef SMART_ZIP_UTILLS_H

void reset_output_ctx(OutputContext *out_ctx);

/** write single bit to output
 */
int write_bit(std::ofstream *out, OutputContext *out_ctx, bool bit);

int write_bitstream(std::ofstream *out, OutputContext *out_ctx, std::vector<bool> bits);

int read_bit(std::ifstream *in, InputContext *in_ctx);

void reset_input_ctx(InputContext *in_ctx);

bool has_next_bit(InputContext *in_ctx);

std::string get_bits_str(char e);

void fill_bitstream(std::vector<bool> *bits, std::string bits_str);

int get_int_from_bits(std::string bits);

#define SMART_ZIP_UTILLS_H

#endif //SMART_ZIP_UTILLS_H
