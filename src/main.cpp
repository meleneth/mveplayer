#include "log/log.hpp"

int main() {
    Log::init();
    spdlog::info("Starting .mve player");
    return 0;
}
