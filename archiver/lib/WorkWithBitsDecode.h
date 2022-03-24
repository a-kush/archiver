#pragma once
#include "EncodeFiles.h"
#include "BitsReader.h"

using ReversedCodeTable = std::unordered_map<std::vector<bool>, std::vector<bool>>;

size_t IntFrom9Bits (BitsReader& reader);

std::vector<std::vector<bool>> ReadSymbolsOrder(BitsReader& reader, size_t symbols_count);

std::vector<size_t> ReadSymbolsCodeSize(BitsReader& reader, size_t symbols_count);

std::vector<EncodedSymbol> CreateVecOfEncodedSymbol(const std::vector<std::vector<bool>> &symbol_order, std::vector<size_t> &symbols_code_size);

std::vector<bool> GetVecBoolFromString(const std::string& s);

ReversedCodeTable GetReversedCodeTable(const CodeTable& canonical_encoded_symbols);

std::string DecodeFileName(BitsReader& reader, const ReversedCodeTable& map_codes_to_symbols);

bool WriteFileData(BitsReader& reader, std::ostream& outfile, const ReversedCodeTable& map_codes_to_symbols);


char WriteToChar(const std::vector<bool> &data, size_t from, size_t to);


