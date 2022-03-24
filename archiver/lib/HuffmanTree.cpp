#include "HuffmanTree.h"
#include <algorithm>
#include <queue>

HuffmanTree::HuffmanTree(FreqTable &frequencies) {
    std::priority_queue<Node> huff_order;
    for (auto &elem: frequencies) {
        Node temporary;
        temporary.frequency = elem.second;
        temporary.symbol = elem.first;
        huff_order.push(temporary);
    }
    while (huff_order.size() > 1) {
        Node first = huff_order.top();
        huff_order.pop();
        Node second = huff_order.top();
        huff_order.pop();
        Node final;
        final.frequency = first.frequency + second.frequency;
        final.left = std::make_shared<Node>(first);
        final.right = std::make_shared<Node>(second);
        huff_order.push(final);
    }
    root_ = huff_order.top();
}

void HuffmanTree::GetCodes(const std::shared_ptr<Node>& node, CodeTable &codes, std::string &code_word) {
    if (!node->left && !node->right) {
        codes[node->symbol] = code_word;
        return;
    }

    code_word.push_back('0');
    GetCodes(node->left, codes, code_word);
    code_word.pop_back();

    code_word.push_back('1');
    GetCodes(node->right, codes, code_word);
    code_word.pop_back();
}

std::vector<EncodedSymbol> HuffmanTree::GetCorrectCanonicalOrder(CodeTable& codes) {
    std::vector<EncodedSymbol> encoded_symbols;
    for (auto &elem: codes) {
        EncodedSymbol temp;
        temp.symbol = elem.first;
        temp.code = elem.second;
        encoded_symbols.push_back(temp);
    }
    std::stable_sort(encoded_symbols.begin(), encoded_symbols.end());
    return encoded_symbols;
}

CodeTable HuffmanTree::GetCanonical(std::vector<EncodedSymbol>& encoded_symbols) {
    CodeTable new_codes;
    size_t int_code = 0;
    size_t prev_size = -1;
    for (auto &elem: encoded_symbols) {
        if (prev_size == -1ul || elem.code.size() == prev_size) {
            new_codes[elem.symbol] = CodeFromIntToString(elem.code.size(), int_code);
            ++int_code;
        } else {
            new_codes[elem.symbol] = CodeFromIntToString(prev_size, int_code) + std::string(elem.code.size() - prev_size,'0');
            int_code = stoi(new_codes[elem.symbol], 0, 2);
            ++int_code;
        }
        prev_size = elem.code.size();
    }
    return new_codes;
}

std::string HuffmanTree::ToBinString(size_t number) {
    std::string bin_string;
    while (number != 0) {
        bin_string = std::to_string(number % 2) + bin_string;
        number /= 2;
    }
    return bin_string;
}

std::string HuffmanTree::CodeFromIntToString(size_t size, size_t int_code) {
    std::string new_code = ToBinString(int_code);
    std::string zeros(size - new_code.size(), '0');
    new_code = zeros + new_code;
    return new_code;
}




