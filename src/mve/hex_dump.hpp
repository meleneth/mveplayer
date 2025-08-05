#pragma once

#include <string>
#include <span>
#include <cstdint>
#include <sstream>
#include <iomanip>


std::string hex_dump(std::span<const uint8_t> bytes, std::size_t max = 16);

