// bytes.hpp
#pragma once
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <cctype>
#include <cstdint>
#include <string_view>
#include <vector>
#include <stdexcept>

inline std::vector<uint8_t> vhex(std::string_view s) {
    auto nibb = [](char c)->int{
        if ('0'<=c && c<='9') return c-'0';
        c = std::tolower(static_cast<unsigned char>(c));
        if ('a'<=c && c<='f') return 10 + (c-'a');
        return -1;
    };

    std::vector<uint8_t> out;
    int hi = -1;
    for (char c : s) {
        if (std::isspace(static_cast<unsigned char>(c)) || c==',' || c=='_' ) continue;
        if (c=='x' || c=='X') continue;                // tolerate 0x??
        int v = nibb(c);
        if (v < 0) throw std::runtime_error("hex(): bad char");
        if (hi < 0) hi = v;
        else { out.push_back(uint8_t((hi<<4) | v)); hi = -1; }
    }
    if (hi >= 0) throw std::runtime_error("hex(): odd number of nibbles");
    return out;
}

// Nice for constructing expected data from ints too:
template <typename... T>
inline std::vector<uint8_t> bytes(T... xs) {
    static_assert((std::is_integral_v<T> && ...), "bytes(): integers only");
    static_assert((... && (std::is_signed_v<T> ? (xs >= 0 && xs <= 0xFF) : (xs <= 0xFF))),
                  "bytes(): values must be 0..255 at compile time if constexpr");
    return { static_cast<uint8_t>(xs)... };
}

struct BytesEqual : Catch::Matchers::MatcherBase<std::vector<uint8_t>> {
    const std::vector<uint8_t>& expected;
    explicit BytesEqual(const std::vector<uint8_t>& e) : expected(e) {}

    bool match(const std::vector<uint8_t>& actual) const override {
        return actual == expected;
    }

    std::string describe() const override {
        std::ostringstream os;
        os << "expected bytes:\n" << hex_dump(expected);
        return os.str();
    }
};

inline BytesEqual BytesEq(const std::vector<uint8_t>& e) {
    return BytesEqual(e);
}

inline std::string render_window(const std::vector<uint8_t>& v,
                                 const std::vector<uint8_t>& other,
                                 size_t start, size_t end)
{
    std::ostringstream os;
    os << std::hex << std::setfill('0');
    os << "@0x" << std::setw(6) << start << ": ";
    for (size_t i = start; i <= end; ++i) {
        bool diff_here = (i >= other.size()) || (v[i] != other[i]);
        if (diff_here) os << '[';
        os << "0x" << std::setw(2) << int(v[i]);
        if (diff_here) os << ']';
        os << ' ';
    }
    return os.str();
}

struct BytesEqualWindow : Catch::Matchers::MatcherBase<std::vector<uint8_t>> {
    const std::vector<uint8_t>& expected;
    mutable std::optional<std::string> last_description;

    explicit BytesEqualWindow(const std::vector<uint8_t>& e) : expected(e) {}

    bool match(const std::vector<uint8_t>& actual) const override {
        last_description.reset();

        // find the first differing index
        size_t diff = std::min(expected.size(), actual.size());
        for (size_t i = 0; i < diff; ++i) {
            if (expected[i] != actual[i]) {
                diff = i;
                break;
            }
        }
        bool equal = (expected.size() == actual.size() &&
                      std::equal(expected.begin(), expected.end(), actual.begin()));
        if (equal) return true;

        size_t before = (diff == 0) ? 0 : diff - 1;
        size_t after = 8;
        size_t exp_end = expected.empty() ? 0 : std::min(expected.size() - 1, diff + after);
        size_t act_end = actual.empty() ? 0 : std::min(actual.size() - 1, diff + after);

        std::ostringstream msg;
        msg << "-> \n";
        msg << std::hex << std::setw(2) << std::setfill('0');
        if(actual.size() == 192) {
          for(int y = 0; y < 8; ++y) {
            for(int x=0; x < 8; ++x) {
              msg << std::setw(2) << (uint16_t)actual[(y*8*3) + x*3];
              msg << std::setw(2) << (uint16_t)actual[(y*8*3) + x*3 + 1];
              msg << std::setw(2) << (uint16_t)actual[(y*8*3) + x*3 + 2];
              msg << " ";
            }
            msg << "\n";
          }
        }
        msg << " <-\n";
        msg << "bytes differ starting at index " << diff
            << " (expected size " << expected.size()
            << ", actual size " << actual.size() << ")\n";

        if (!expected.empty())
            msg << "EXPECTED " << render_window(expected, actual, before, exp_end) << "\n";
        else
            msg << "EXPECTED is empty\n";

        if (!actual.empty())
            msg << "ACTUAL   " << render_window(actual, expected, before, act_end) << "\n";
        else
            msg << "ACTUAL is empty\n";

        last_description = msg.str();
        return false;
    }

    std::string describe() const override {
        return last_description.value_or("bytes are equal");
    }
};

inline BytesEqualWindow BytesEqWindow(const std::vector<uint8_t>& e) {
    return BytesEqualWindow(e);
}


