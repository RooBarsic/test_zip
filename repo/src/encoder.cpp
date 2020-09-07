#include <iostream>
# include <algorithm>

# include "utills.h"
# include "alphabet.h"
# include "structures.h"


Node* build_huffman_tree(std::vector<Node*> *nodes) {
    while (nodes->size() > 1) {
        Node *a = (*nodes)[nodes->size() - 1];
        Node *b = (*nodes)[nodes->size() - 2];
        nodes->pop_back();
        nodes->pop_back();

        Node *c = new Node();
        c->letter = a->letter + b->letter;
        c->frequency = a->frequency + b->frequency;
        c->left = a;
        c->right = b;
        nodes->push_back(c);
        int idx = nodes->size() - 1;
        while(0 < idx && (*nodes)[idx - 1]->frequency < (*nodes)[idx]->frequency) {
            std::swap((*nodes)[idx - 1], (*nodes)[idx]);
            idx--;
        }
    }

    return (*nodes)[0];
}

void fill_context(Node *node, Context *context, std::string key) {
    if (node != NULL) {
        if (node->left == NULL && node->right == NULL) { // it's a leaf
            context->letter_by_key[key] = node->letter;
            context->key_by_letter[node->letter] = key;
        }
        else {
            fill_context(node->left, context, key + "1");
            fill_context(node->right, context, key + "0");
        }
    }
}

void init_encoder(Context *context, Alphabet *alphabet) {
    std::sort(alphabet->letters.begin(), alphabet->letters.end(),
              [alphabet = alphabet] (std::string a, std::string b) {
                  return alphabet->letter_frequency[a] > alphabet->letter_frequency[b];
    });

    std::vector<Node*> base_nodes;
    for (int i = 0; i < alphabet->alphabet_size; i++) {
        Node *node = new Node();
        node->letter = alphabet->letters[i];
        node->frequency = alphabet->letter_frequency[alphabet->letters[i]];
        node->left = node->right = NULL;
        base_nodes.push_back(node);
    }

    Node *root = build_huffman_tree(&base_nodes);

    fill_context(root, context, "");

#if DEBUG_MODE
    int total_bits_len = 0;
    for (int i = 0; i < alphabet->alphabet_size; i++) {
        std::string letter = alphabet->letters[i];
        // std::cout << "letter = " << letter
        //             << " char=" << char(get_int_from_bits(letter))
        //             << " -> encoded = " << context->key_by_letter[letter] << '\n';
        total_bits_len += alphabet->letter_frequency[letter] * int(context->key_by_letter[letter].size());
    }
    std::cout << "total bits len = " << total_bits_len << '\n';
#endif
}

void encode_file(Context *context, Alphabet *alphabet, std::string input_file_name, std::string output_file_name) {

    std::ifstream in(input_file_name);
    std::ofstream out(output_file_name);

    if(!in.is_open() || !out.is_open()) {
        return ;
    }

    std::vector<bool> bitstream;
    OutputContext outputContext;
    reset_output_ctx(&outputContext);
//    out << alphabet->alphabet_size << '\n';
//    reset_output_ctx(&outputContext);
//    for (int i = 0; i < alphabet->alphabet_size; i++) {
//        int f;
//        fill_bitstream(&bitstream, alphabet->letters[i]);
//        out << alphabet->letters[i].size() << '\n'; // write letter length
//        reset_output_ctx(&outputContext);
//        f = write_bitstream(&out, &outputContext, bitstream);  // write letter
//        while (f == 0) {
//            f = write_bit(&out, &outputContext, 0);
//        }
//        out << '\n';
//
//        fill_bitstream(&bitstream, context->key_by_letter[alphabet->letters[i]]);
//        out << context->key_by_letter[alphabet->letters[i]].size() << '\n'; // write key length
//        reset_output_ctx(&outputContext);
//        f = write_bitstream(&out, &outputContext, bitstream);  // write key
//        while (f == 0) {
//            f = write_bit(&out, &outputContext, 0);
//        }
//        out << '\n';
//    }

    InputContext inputContext;
    reset_input_ctx(&inputContext);
    std::string bit_buffer = "";
    int f;
#if 0 //DEBUG_MODE
    std::string prev_match = "";
    int match_sequence_counter = 0;
#endif
    while (has_next_bit(&inputContext) || in.peek() !=  EOF) {
        if (read_bit(&in, &inputContext))
            bit_buffer += "1";
        else
            bit_buffer += "0";

        if (contains_letter(alphabet, bit_buffer)) {
#if 0 //DEBUG_MODE
            if (prev_match == bit_buffer)
                match_sequence_counter++;
            else 
                match_sequence_counter = 1;
            prev_match = bit_buffer;
            std::cout << " encoder ::::: got_match.  bits = " << bit_buffer << "   char = " << char(get_int_from_bits(bit_buffer)) << "   sequence = " << match_sequence_counter << '\n';
#endif
            std::string key = context->key_by_letter[bit_buffer];
            fill_bitstream(&bitstream, key);
            f = write_bitstream(&out, &outputContext, bitstream);
            bit_buffer = "";
        }
    }
    while (f == 0) {
        f = write_bit(&out, &outputContext, 0);
    }

}



