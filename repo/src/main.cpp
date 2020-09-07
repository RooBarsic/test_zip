# include <bits/stdc++.h>
# include <map>
# include <fstream>
# include <string>
# include <vector>
# include <unordered_map>
# include <algorithm>
# include <bitset>

# include "structures.h"
# include "alphabet.h"
# include "encoder.h"
# include "decoder.h"
# include "utills.h"

using namespace std;







/**

void print_map(Context *ctx) {
    for (int i = 0; i < ctx->uniq_characters.size(); i++) {
        string s = "";
        for (int j = 0; j < ctx->key_match[ ctx->uniq_characters[i] ].size(); j++) {
            if ( ctx->key_match[ ctx->uniq_characters[i] ][j] )
                s += "1";
            else 
                s += "0";
        }
        cout << ctx->uniq_characters[i] << " --> " << ctx->symbols_num[ ctx->uniq_characters[i] ]<< " --> " << s << "|" << '\n';
    }
}



void push_string_to_ctx(Context *ctx, string row) {
    for (int i = 0; i < row.size(); i++) {
        ctx->symbols_num[row[i]] ++;
        if (ctx->symbols_num[row[i]] == 1) {
            ctx->uniq_characters.push_back(row[i]);
        }
    }
}

void init_uniq_characters_order(Context *ctx) {
    sort(ctx->uniq_characters.begin(), ctx->uniq_characters.end(), 
        [ctx = ctx] (char a, char b) {
            return (ctx->symbols_num[a] > ctx->symbols_num[b]) ? 1 : 0; 
        }
    );
}

void fill_char_key_map(Context *ctx) {
    for (int i = 0; i < ctx->uniq_characters.size(); i++) {
        //cout << "e = |" << ctx->uniq_characters[i] << "|  bits = |";
        for (int j = 0; j < i; j++) {
            ctx->key_match[ctx->uniq_characters[i]].push_back(0);
            //cout << "0";
        }
        ctx->key_match[ctx->uniq_characters[i]].push_back(1);
        //cout << "1|   sz = " << ctx->key_match[ctx->uniq_characters[i]].size() << '\n';
    }
}

int parse_input(Context *context, string file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        return 0;
    }
    string row;
    while(getline(in, row)) {
        push_string_to_ctx(context, row);
    }
    in.close();
    init_uniq_characters_order(context);
    fill_char_key_map(context);
    return 1;
}

void put_key_val(Context *ctx, char e, string buff) {
    for (int i = 0; i < buff.size(); i++) {
        ctx->key_match[e].push_back(buff[i] == '1');
    }
}
















int encode_file(Context *ctx, OutputContext *out_ctx, string input_file_name, string output_file_name) {

    parse_input(ctx, input_file_name);

    print_map(ctx);

    ifstream in(input_file_name);
    ofstream out(output_file_name);

    if(!in.is_open() || !out.is_open()) {
        return 0;
    }
    
    out << ctx->uniq_characters.size() << '\n';
    for (int i = 0; i < ctx->uniq_characters.size(); i++) {
        out << ctx->uniq_characters[i] << '\n';

        reset_output_ctx(out_ctx);
        int f = write_bitstream(&out, out_ctx, ctx->key_match[ ctx->uniq_characters[i] ]);
        while (f == 0) {
            f = write_bit(&out, out_ctx, 0); 
        }
        out << '\n';
    }

    string row;
    while(getline(in, row)) {
        int f;
        reset_output_ctx(out_ctx);
        for (int i = 0; i < row.size(); i++) {
            f = write_bitstream(&out, out_ctx, ctx->key_match[ row[i] ]);
        }
        while(f == 0) {
            f = write_bit(&out, out_ctx, 0);
        }
        out << '\n';
    }
    in.close();
    out.close();
    return 1;
}

void decode_file(Context *ctx, OutputContext *out_ctx, string input_file_name, string output_file_name) {
    ifstream in(input_file_name);
    ofstream out(output_file_name);

    if(!in.is_open() || !out.is_open()) {
        return ;
    }
    
    int number_of_uniq_characters;
    in >> number_of_uniq_characters;
    string buff;
    getline(in, buff);
    cout << " num = " << number_of_uniq_characters << '\n';
    InputContext in_ctx;
    for (int i = 1; i <= number_of_uniq_characters; i++) {
        char e;
        getline(in, buff);
        e = buff[0];
        
        reset_input_ctx(&in_ctx);
        buff = "";
        buff += char(int('0') + read_bit(&in, &in_ctx));
        
        while(has_next_bit(&in_ctx) && (buff[int(buff.size()) - 1] != '1')) {
            buff += char(int('0') + read_bit(&in, &in_ctx));
        }

        cout << " e = |" << e << "|   buff = |" << buff << "|  \n";

        ctx->char_by_code[buff] = e;
        ctx->uniq_characters.push_back(e);
        put_key_val(ctx, e, buff);
    }

    print_map(ctx);

    reset_input_ctx(&in_ctx);
    buff = "";
    buff += char(int('0') + read_bit(&in, &in_ctx));
    int k = 0;
    while(1 == 1) {
        if (ctx->char_by_code[buff] != 0) {
            //cout << " got matche    buff = |" << buff << "|   val = |" << ctx->char_by_code[buff] << "|    k = " << k << " \n";
            out << ctx->char_by_code[buff];
            buff = "";
        }
        if(has_next_bit(&in_ctx)) {
            buff += char(int('0') + read_bit(&in, &in_ctx));
        }
        else if(in.peek() == EOF) {
            break;
        }
        else {
            out << '\n';
            buff = "";
            buff += char(int('0') + read_bit(&in, &in_ctx));
        }
    }
}

*/

void count_rows(std::string file_name) {
    std::ifstream in(file_name);

    int rows_num = 0;
    std::string str;
    while (getline(in, str)) {
        rows_num++;
    }
    std::cout << " rows_num = " << rows_num << '\n';
}

void create_test_data() {
    std::ofstream out("test_data_3.txt");

    for (int i = 0; i < 1000000; i++) {
        int x = (rand() ^ rand()) % 26;
        out << char(int('a') + x);
    }
}

void copy_file(std::string input_file_name, std::string output_file_name) {

}

int main(int argc, char *args[]) {
        create_test_data();
    //  ofstream out("test_out");
    //  OutputContext out_ctx;
    //  reset_output_ctx(&out_ctx);
    //  write_bit(&out, &out_ctx, 1);
    //  while(write_bit(&out, &out_ctx, 0) == 0){

    //  }

    // ifstream in("test_out");
    // InputContext in_ctx;
    // cout << read_bit(&in, &in_ctx);
    // while(has_next_bit(&in_ctx)){
    //     cout << read_bit(&in, &in_ctx);
    // }
    // return 0;
        
    if (argc < 4) {
        cout << "pleae give me the target file name!!";
        return 0;
    }
    Context context;
    OutputContext out_context;

    if (args[2][0] == 'e') {
        cout << " encoding \n";
        //parse_input(&context, args[1]);

        //print_map(&context);

        Alphabet alphabet;
        Context context1;
        init_alphabet_from_file(&alphabet, args[1]);
        init_encoder(&context1, &alphabet);
        encode_file(&context1, &alphabet, args[1], args[3]);

        decode_file(&context1, &alphabet, args[3], "decoded_file");
        count_rows(args[1]);
        count_rows(args[3]);
        count_rows("decoded_file");

        //encode_file(&context, &out_context, args[1], args[3]);
    }
    else {
        cout << " decoding \n";
       // decode_file(&context, &out_context, args[1], args[3]);
    }



    return 0;
}


