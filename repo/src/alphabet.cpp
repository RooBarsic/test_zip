# include <bits/stdc++.h>
# include <string>
# include <unordered_map>

# include "utills.h"
# include "structures.h"

bool contains_letter(Alphabet *alphabet, std::string letter) {
    return alphabet->letter_frequency.find(letter) != alphabet->letter_frequency.end();
}

bool add_letter_to_alphabet(Alphabet *alphabet, std::string letter) {
    if (alphabet->letter_frequency.find(letter) == alphabet->letter_frequency.end()) {
        alphabet->letters.push_back(letter);
        alphabet->alphabet_size++;
        alphabet->letter_frequency[letter] = 1;
        return true;
    }
    else {
        alphabet->letter_frequency[letter]++;
        return false;
    }
}

int init_alphabet_from_file(Alphabet *alphabet, std::string file_name) {
    std::ifstream in(file_name);
    if (!in.is_open()) {
        return 0;
    }
    std::string row;
    std::string buffer = "";
    while(getline(in, row)) {
        // if (in.peek() != EOF)
        //     row += "\n";
        for (int i = 0, row_sz = int(row.size()); i < row_sz; i++) {
            buffer += get_bits_str(row[i]);
        }
    }
    int n = int(buffer.size());
    /*
    n = 8000000
    1 - k = 1 - alphabet_num = 2   file size =    1000000
    2 - k = 2 - alphabet_num = 4   file size =     968237
    3 - k = 4 - alphabet_num = 16   file size =    801623
    4 - k = 5 - alphabet_num = 31   file size =    974983
    5 - k = 8 - alphabet_num = 26   file size =    598855
    6 - k = 10 - alphabet_num = 282   file size =  793187
    7 - k = 16 - alphabet_num = 676   file size =  594621
    8 - k = 12336 - alphabet_num = 2   file size = 645446
    9 - k =  - alphabet_num = 2   file size = 

    */
    int k = -9  ;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            k++;
        }
        if(k == 0) { 
            k = i;
            break;
        }
    }
    if ( k <= 0) {
        std:: cout << "------------------------------ still k < 0 --------------------- \n";
        k = 8;
    }
    k = 13;
    std:: cout << " total file size ----------------------- n = " << n << "   k = " << k << '\n';
    std::string alphabet_letter = "";
    for (int i = 0, sz = int(buffer.size()); i < sz; i++) {
        alphabet_letter += buffer[i];
        if (int(alphabet_letter.size()) % k == 0) {
            add_letter_to_alphabet(alphabet, alphabet_letter);
            alphabet_letter = "";
        }
    }
    if (int(alphabet_letter.size()) % k == 0 && (alphabet_letter.size()) != 0) {
        add_letter_to_alphabet(alphabet, alphabet_letter);
        alphabet_letter = "";
    }
    // std::string alphabet_letter = get_bits_str('\n');
    // add_letter_to_alphabet(alphabet, alphabet_letter);
#if DEBUG_MODE
    for (int i = 0; i < alphabet->alphabet_size; i++) {
        // std::cout << " e = " << char(get_int_from_bits(alphabet->letters[i]))
        //             << " letter = " << alphabet->letters[i]
        //             << "  num = " << alphabet->letter_frequency[alphabet->letters[i]] << '\n';
    }
    std::cout << " alphabet_size = " << alphabet->alphabet_size << '\n';
#endif
    in.close();
    return 1;
}

