#include "Core/FLApp.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {
    FLCore::FLApp app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

    return 0;
}
