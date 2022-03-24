#pragma once
#include <unordered_map>
#include <vector>
#include "BitsReader.h"

using ReversedCodeTable = std::unordered_map<std::vector<bool>, std::vector<bool>>;

bool WriteToFile(BitsReader& reader, const ReversedCodeTable& map_codes_to_symbols);

void DecodeArchive(const std::string& archive_name);

