#pragma once
#include <unordered_map>
#include <vector>
#include "BitsWriter.h"
#include "StructEncodedSymbol.h"


const std::vector<bool> FILE_NAME_END = {false, false, false, false, false, false, false, false, true};
const std::vector<bool> ONE_MORE_FILE = {true, false, false, false, false, false, false, false, true};
const std::vector<bool> ARCHIVE_END = {false, true, false, false, false, false, false, false, true};


using FreqTable = std::unordered_map<std::vector<bool>, size_t>;
using CodeTable = std::unordered_map<std::vector<bool>, std::string>;

std::vector<std::vector<bool>> FileNameTo9Bits(const std::string& name);

void AddFileNameToFreq(FreqTable& frequencies, const std::string& file_name);

FreqTable CountFrequency(std::istream& file);

void WriteInteger(size_t code_table_size, BitsWriter& writer);

void WriteCodeTable(const std::vector<EncodedSymbol> &symbols_with_canonical_codes, BitsWriter& writer);

void WriteCodeSizes(const std::vector<EncodedSymbol>& symbols_with_canonical_codes, BitsWriter& writer);

void WriteFileName(CodeTable& codes_of_symbols, const std::vector<std::vector<bool>>& file_name, BitsWriter& writer);

void WriteFileData(CodeTable &codes_of_symbols, BitsWriter& writer, std::istream& file);

void WriteOneMoreFile(CodeTable &codes_of_symbols, BitsWriter& writer);

void WriteArchiveEnd(CodeTable &codes_of_symbols, BitsWriter& writer);

