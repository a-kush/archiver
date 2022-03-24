#include "BitsReader.h"

BitsReader::BitsReader(std::istream &stream)
        : input_stream_(stream) {
}

std::vector<bool> BitsReader::ReadByte(const size_t byte_size) {
    std::vector<bool> final;

    for (size_t i = 0; i < byte_size; ++i) {
        if (current_index_ == NORMAL_BYTE) {
            char temp;
            input_stream_.get(temp);
            symbol_ = temp;
            current_index_ = 0;
        }
        auto temp1 = symbol_ >> (NORMAL_BYTE - 1 - current_index_);
        final.push_back(static_cast<bool>(temp1 & 1));
        ++current_index_;
    }
    if (byte_size == NORMAL_BYTE) {
        final.push_back(false);
    }

    return final;
}
