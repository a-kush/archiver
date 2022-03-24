#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "StructEncodedSymbol.h"


using CodeTable = std::unordered_map<std::vector<bool>, std::string>;
using FreqTable = std::unordered_map<std::vector<bool>, size_t>;

struct Node {
    size_t frequency = 0;
    std::vector<bool> symbol;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    bool operator<(const Node &other) const {
        return frequency > other.frequency;
    }
};



class HuffmanTree {
public:
    explicit HuffmanTree(FreqTable &frequencies);

    void GetCodes(const std::shared_ptr<Node>& node, CodeTable &codes, std::string& code_word);

    static CodeTable GetCanonical(std::vector<EncodedSymbol>& encoded_symbols);

    static std::vector<EncodedSymbol> GetCorrectCanonicalOrder(CodeTable& codes);

    const Node& GetRoot() const {
        return root_;
    }

private:
    Node root_;
    static std::string ToBinString(size_t number);
    static std::string CodeFromIntToString(size_t size, size_t int_code);

};

