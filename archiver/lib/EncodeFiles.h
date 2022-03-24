#pragma once
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <unordered_map>
#include "HuffmanTree.h"
#include "BitsWriter.h"

using CodeTable = std::unordered_map<std::vector<bool>, std::string>;

CodeTable GetCanonicalHuffman(HuffmanTree &some_tree, std::vector<EncodedSymbol>& correct_canonical_order);

void EncodeFiles(std::string& archive_name, const std::vector<std::string>& file_names);

void WriteToArchive(std::istream& file, BitsWriter& writer, const std::string& file_name, CodeTable& codes_of_symbols, const bool last_file, std::vector<EncodedSymbol>& correct_canonical_order);