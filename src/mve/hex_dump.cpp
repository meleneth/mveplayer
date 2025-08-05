#include<mve/hex_dump.hpp>

std::string hex_dump(std::span<const uint8_t> bytes, std::size_t max) {
    std::ostringstream out;
    for (std::size_t i = 0; i < std::min(bytes.size(), max); ++i) {
        out << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]) << " ";
    }
    return out.str();
}

