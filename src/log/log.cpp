#include "log.hpp"

namespace Log {
void init() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto logger = std::make_shared<spdlog::logger>("mve", console_sink);
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug); // or info for less noise
    spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
}
}
