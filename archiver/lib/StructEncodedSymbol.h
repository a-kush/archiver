#pragma once


struct EncodedSymbol {
    std::vector<bool> symbol;
    std::string code;

    bool operator<(const EncodedSymbol &other) const {
        return code.size() < other.code.size();
    }
};


