#include "Instance.hpp"
#include <stdio.h>
// #include "test.cpp"

int main(int argc, char** argv) {
    try {
        Instance instance;
        instance.initVulkan();
        instance.cleanup();
    } catch(const std::exception& e) {
        fprintf(stderr,"%s", e.what());
    }
}