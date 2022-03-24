#pragma once
#include <istream>
#include <vector>
#include "ConstForWriterAndReader.h"

class BitsReader {
public:
    explicit BitsReader(std::istream& input_stream);
    std::vector<bool> ReadByte(const size_t byte_size);
private:
    std::istream& input_stream_;
    uint8_t symbol_ = 0;
    uint8_t current_index_ = NORMAL_BYTE;
};
