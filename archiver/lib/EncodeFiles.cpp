#include "EncodeFiles.h"
#include "WorkWithBitsEncode.h"
#include "HuffmanTree.h"
#include <iostream>

CodeTable GetCanonicalHuffman(HuffmanTree &some_tree, std::vector<EncodedSymbol> &correct_canonical_order) {
    std::string s;
    CodeTable codes_of_symbols;
    some_tree.GetCodes(std::make_shared<Node>(some_tree.GetRoot()), codes_of_symbols, s);

    correct_canonical_order = HuffmanTree::GetCorrectCanonicalOrder(codes_of_symbols);
    CodeTable canonical_codes_of_symbols = HuffmanTree::GetCanonical(correct_canonical_order);
    return canonical_codes_of_symbols;
}

void WriteToArchive(std::istream &file, BitsWriter &writer, const std::string& file_name,
                    CodeTable &codes_of_symbols, const bool last_file,
                    std::vector<EncodedSymbol> &correct_canonical_order) {
    WriteInteger(codes_of_symbols.size(), writer);

    WriteCodeTable(correct_canonical_order, writer);

    WriteCodeSizes(correct_canonical_order, writer);

    std::vector<std::vector<bool>> file_name_in_bits = FileNameTo9Bits(file_name);
    WriteFileName(codes_of_symbols, file_name_in_bits, writer);

    WriteFileData(codes_of_symbols, writer, file);

    if (!last_file) {
        WriteOneMoreFile(codes_of_symbols, writer);
    } else {
        WriteArchiveEnd(codes_of_symbols, writer);
    }
}


void EncodeFiles(std::string& archive_name, const std::vector<std::string>& file_names) {
    std::ofstream outfile(archive_name, std::ios::binary);
    BitsWriter writer(outfile);

    for (size_t index = 0; index < file_names.size(); ++index) {
        std::ifstream file(file_names[index], std::ios::binary);

        FreqTable frequencies = CountFrequency(file);
        std::string file_name(file_names[index]);
        AddFileNameToFreq(frequencies, file_name);

        HuffmanTree some_tree(frequencies);
        std::vector<EncodedSymbol> correct_canonical_order;
        CodeTable codes_of_symbols = GetCanonicalHuffman(some_tree, correct_canonical_order);

        bool last_file = false;
        if (index == file_names.size() - 1) {
            last_file = true;
        }

        file.clear();
        file.seekg(0);

        WriteToArchive(file, writer, std::string(file_names[index]), codes_of_symbols, last_file,
                       correct_canonical_order);

        file.close();
    }
    writer.Close();
    outfile.close();
}
