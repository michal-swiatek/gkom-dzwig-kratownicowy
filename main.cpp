/*
 *  Created by michal-swiatek on 16.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#include <iostream>
#include "Core.h"

int main() {
    try {
        Core app("Dzwig kratownicowy");
        app.initApp();

        app.run();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }

    return 0;
}

