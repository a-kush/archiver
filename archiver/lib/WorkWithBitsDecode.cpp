#include "WorkWithBitsDecode.h"
#include "WorkWithBitsEncode.h"
#include <algorithm>


size_t IntFrom9Bits(BitsReader &reader) {
    size_t symbol = 0;
    std::vector<bool> data = reader.ReadByte(9);
    for (size_t i = 0; i < 9; ++i) {
        symbol += (static_cast<size_t>(data[i]) << i);
    }
    return symbol;
}

std::vector<std::vector<bool>> ReadSymbolsOrder(BitsReader &reader, size_t symbols_count) {
    std::vector<std::vector<bool>> symbols_order;

    for (size_t i = 0; i < symbols_count; ++i) {
        std::vector<bool> data = reader.ReadByte(9);
        symbols_order.push_back(data);
    }

    return symbols_order;
}

std::vector<size_t> ReadSymbolsCodeSize(BitsReader &reader, size_t symbols_count) {
    size_t count_values = 0;
    std::vector<size_t> symbols_code_size;
    while (count_values != symbols_count) {
        size_t temp = IntFrom9Bits(reader);
        symbols_code_size.push_back(temp);
        count_values += temp;
    }
    return symbols_code_size;
}

std::vector<EncodedSymbol> CreateVecOfEncodedSymbol(const std::vector<std::vector<bool>> &symbol_order, std::vector<size_t> &symbols_code_size) {
    std::vector<EncodedSymbol> final;

    size_t index = 0;
    for (auto &elem: symbol_order) {
        EncodedSymbol temp;
        temp.symbol = elem;
        while (symbols_code_size[index] == 0) {
            ++index;
        }
        temp.code = std::string(index + 1, '0');
        final.push_back(temp);
        --symbols_code_size[index];
    }

    return final;
}

std::vector<bool> GetVecBoolFromString(const std::string &s) {
    std::vector<bool> final;

    for (const auto& elem: s) {
        final.push_back(static_cast<bool>(elem - '0'));
    }
    return final;
}

ReversedCodeTable GetReversedCodeTable(const CodeTable &canonical_encoded_symbols) {
    ReversedCodeTable final;
    for (const auto &elem: canonical_encoded_symbols) {
        final[GetVecBoolFromString(elem.second)] = elem.first;
    }
    return final;
}


std::string DecodeFileName(BitsReader &reader, const ReversedCodeTable &map_codes_to_symbols) {
    bool is_file_name_end = false;
    std::string final;
    while (!is_file_name_end) {
        std::vector<bool> code;
        while (map_codes_to_symbols.find(code) == map_codes_to_symbols.end()) {
            std::vector<bool> data = reader.ReadByte(1);
            code.push_back(data[0]);
        }

        if (map_codes_to_symbols.at(code) == FILE_NAME_END) {
            is_file_name_end = true;
        } else {
            std::vector<bool> symbol = map_codes_to_symbols.at(code);
            final.push_back(WriteToChar(symbol, 0, 8));
        }
    }
    return final;
}

bool WriteFileData(BitsReader &reader, std::ostream &outfile, const ReversedCodeTable &map_codes_to_symbols) {
    bool is_file_data_end = false;
    bool is_there_another_file = true;
    BitsWriter writer(outfile);
    while (!is_file_data_end) {
        std::vector<bool> code;
        while (map_codes_to_symbols.find(code) == map_codes_to_symbols.end()) {
            std::vector<bool> data = reader.ReadByte(1);
            code.push_back(data[0]);
        }
        if (map_codes_to_symbols.at(code) == ONE_MORE_FILE || map_codes_to_symbols.at(code) == ARCHIVE_END) {
            is_file_data_end = true;
            if (map_codes_to_symbols.at(code) == ARCHIVE_END) {
                is_there_another_file = false;
            }
        } else {
            std::vector<bool> symbol = map_codes_to_symbols.at(code);
            symbol.pop_back();
            writer.WriteBit(symbol);
        }
    }
    writer.Close();
    return is_there_another_file;
}

char WriteToChar(const std::vector<bool> &data, size_t from, size_t to) {
    uint8_t symbol = 0;
    for (size_t i = 0; from + i < data.size() && from + i < to; ++i) {
        symbol += (static_cast<uint8_t>(data[from + i]) << (7 - i));
    }

    return static_cast<char>(symbol);
}




