#pragma once
#include <iostream>
#include <vector>

class BitsWriter {
public:
    explicit BitsWriter(std::ostream& stream);
    void WriteBit(const std::vector<bool>& data);
    void Close();
private:

    std::ostream& output_stream_;
    uint8_t symbol_ = 0;
    uint8_t current_index_ = 0;
};
