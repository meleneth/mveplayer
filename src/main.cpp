#include "log/log.hpp"

int main(int argc, char** argv) {
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "MVE Player starting up";
    return 0;
}
