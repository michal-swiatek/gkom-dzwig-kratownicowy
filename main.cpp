/*
 *  Created by michal-swiatek on 16.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#include <Configure.h>
#include <iostream>

#include "Core.h"

int main() {
    Core app("Dzwig kratownicowy", int(PROJECT_VERSION_MAJOR), int(PROJECT_VERSION_MINOR));
    try {
        app.initApp();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }

    app.run();

    return 0;
}

