#include<mve/bits_dump.hpp>

std::string bits_dump(std::span<const uint8_t> bytes, std::size_t max) {
    std::ostringstream out;
    std::size_t limit = std::min(bytes.size(), max);

    for (std::size_t i = 0; i < limit; ++i) {
        out << std::bitset<8>(bytes[i]) << " ";
        if ((i + 1) % 8 == 0) {
            out << '\n';
        }
    }

    if (limit % 8 != 0) {
        out << '\n';
    }

    return out.str();
}
