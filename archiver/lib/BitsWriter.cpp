#include "BitsWriter.h"
#include "ConstForWriterAndReader.h"

BitsWriter::BitsWriter(std::ostream& stream)
        : output_stream_(stream){
}

void BitsWriter::WriteBit(const std::vector<bool> &data) {
    for (const auto& elem : data) {
        symbol_ += (static_cast<uint8_t>(elem) << (NORMAL_BYTE - 1 - current_index_));
        ++current_index_;
        if (current_index_ == NORMAL_BYTE) {
            output_stream_.put(static_cast<char>(symbol_));
            output_stream_.flush();
            symbol_ = 0;
            current_index_ = 0;
        }
    }
}

void BitsWriter::Close() {
    if (current_index_ != 0) {
        output_stream_.put(static_cast<char>(symbol_));
        output_stream_.flush();
    }
}
