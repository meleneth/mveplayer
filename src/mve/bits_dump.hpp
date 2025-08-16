#pragma once
#include <span>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <cstdint>

std::string bits_dump(std::span<const uint8_t> bytes, std::size_t max = 16);
