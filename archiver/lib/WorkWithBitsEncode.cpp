#include "WorkWithBitsEncode.h"
#include <algorithm>
#include <iostream>
#include "BitsReader.h"

std::vector<std::vector<bool>> FileNameTo9Bits(const std::string& name) {
    std::vector<std::vector<bool>> file_name_in_bits;
    for (const auto& elem : name) {
        auto symbol = static_cast<uint8_t>(elem);

        std::vector<bool> symbol_bin;
        for (size_t i = 8; i > 0; --i) {
            auto temp = symbol >> (i - 1);
            symbol_bin.push_back(static_cast<bool>(temp & 1));
        }
        symbol_bin.push_back(false);
        file_name_in_bits.push_back(symbol_bin);
    }
    std::vector<bool> filename_end(9);
    filename_end[8] = true;
    file_name_in_bits.push_back(filename_end);
    return file_name_in_bits;
}

void AddFileNameToFreq(FreqTable& frequencies, const std::string& file_name) {
    std::vector<std::vector<bool>> file_name_bits = FileNameTo9Bits(file_name);
    for (const auto& elem : file_name_bits) {
        ++frequencies[elem];
    }
}

FreqTable CountFrequency(std::istream& file) {
    BitsReader reader(file);

    FreqTable frequencies;
    while (!file.fail()) {
        std::vector<bool> elem = reader.ReadByte(8);
        ++frequencies[elem];
    }

    frequencies[FILE_NAME_END] = 1;
    frequencies[ONE_MORE_FILE] = 1;
    frequencies[ARCHIVE_END] = 1;
    return frequencies;
}

std::vector<bool> GetVecBoolFromInt (size_t integer) {
    size_t this_size = 0;
    std::vector<bool> final;
    while (integer != 0) {
        final.push_back(static_cast<bool>(integer & 1));
        integer = integer >> 1;
        ++this_size;
    }
    while (this_size != 9) {
        final.push_back(false);
        ++this_size;
    }
    return final;
}

void WriteInteger(size_t code_table_size, BitsWriter& writer) {
    std::vector<bool> data = GetVecBoolFromInt(code_table_size);
    writer.WriteBit(data);
}

void WriteCodeTable(const std::vector<EncodedSymbol> &symbols_with_canonical_codes, BitsWriter& writer) {
    for (auto &elem: symbols_with_canonical_codes) {
            writer.WriteBit(elem.symbol);
    }
}

void WriteCodeSizes(const std::vector<EncodedSymbol> &symbols_with_canonical_codes, BitsWriter& writer) {

    size_t vector_size = symbols_with_canonical_codes[symbols_with_canonical_codes.size() - 1].code.size();
    std::vector<size_t> count_symbols_with_this_size(vector_size);

    for (const auto &elem: symbols_with_canonical_codes) {
        ++count_symbols_with_this_size[elem.code.size() - 1];
    }

    for (auto elem : count_symbols_with_this_size) {
        WriteInteger(elem, writer);
    }
}


void WriteFileName(CodeTable& codes_of_symbols, const std::vector<std::vector<bool>>& file_name, BitsWriter& writer) {
    for (const auto &elem: file_name) {
        std::vector<bool> code;
        for (auto &bit: codes_of_symbols[elem]) {
            code.push_back(static_cast<bool>(bit - '0'));
        }
        writer.WriteBit(code);
    }
}

void WriteFileData(CodeTable &codes_of_symbols, BitsWriter& writer, std::istream& file) {
    BitsReader reader(file);

    while (!file.fail()) {
        std::vector<bool> elem = reader.ReadByte(8);
        std::vector<bool> code;
        for (auto &bit: codes_of_symbols[elem]) {
            code.push_back(static_cast<bool>(bit - '0'));
        }
        writer.WriteBit(code);
    }
}

void WriteOneMoreFile(CodeTable &codes_of_symbols, BitsWriter& writer) {
    std::vector<bool> code;
    for (auto& bit : codes_of_symbols[ONE_MORE_FILE]) {
        code.push_back(static_cast<bool>(bit - '0'));
    }
    writer.WriteBit(code);
}

void WriteArchiveEnd(CodeTable &codes_of_symbols, BitsWriter& writer) {
    std::vector<bool> code;
    for (auto& bit : codes_of_symbols[ARCHIVE_END]) {
        code.push_back(static_cast<bool>(bit - '0'));
    }
    writer.WriteBit(code);
}
