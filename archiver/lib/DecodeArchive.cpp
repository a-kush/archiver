#include "DecodeArchive.h"
#include "WorkWithBitsDecode.h"
#include "WorkWithBitsEncode.h"
#include <iostream>

bool WriteToFile(BitsReader &reader, const ReversedCodeTable &map_codes_to_symbols) {
    std::string file_name = DecodeFileName(reader, map_codes_to_symbols);

    std::ofstream outfile(file_name, std::ios::binary);

    bool is_there_one_more_file = WriteFileData(reader, outfile, map_codes_to_symbols);

    outfile.close();

    return is_there_one_more_file;
}


void DecodeArchive(const std::string& archive_name) {
    std::ifstream archive(archive_name, std::ios::binary);

    BitsReader reader(archive);

    bool is_there_one_more_file = true;
    while (is_there_one_more_file) {
        size_t symbols_count = IntFrom9Bits(reader);
        std::vector<std::vector<bool>> symbol_order = ReadSymbolsOrder(reader, symbols_count);

        std::vector<size_t> symbols_code_size = ReadSymbolsCodeSize(reader, symbols_count);
        std::vector<EncodedSymbol> encoded_symbols = CreateVecOfEncodedSymbol(symbol_order, symbols_code_size);

        CodeTable canonical_encoded_symbols = HuffmanTree::GetCanonical(encoded_symbols);

        ReversedCodeTable map_codes_to_symbols = GetReversedCodeTable(canonical_encoded_symbols);

        is_there_one_more_file = WriteToFile(reader, map_codes_to_symbols);
    }
    archive.close();
}


