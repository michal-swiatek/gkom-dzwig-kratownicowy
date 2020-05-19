/*
 *  Created by michal-swiatek on 16.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#include <Configure.h>
#include <iostream>

#include "Core.h"

int main() {
    Core app("Dzwig kratownicowy", int(PROJECT_VERSION_MAJOR), int(PROJECT_VERSION_MINOR), int(PROJECT_VERSION_PATCH));

    try {
        initOpenGL();   //  Create context and window
        app.initApp();  //  Initialize subsystems and resources
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
        return -1;
    }

    app.run();

    return 0;
}

