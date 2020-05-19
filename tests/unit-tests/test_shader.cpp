/*
 *   Created by michal-swiatek on 11.05.2020.
 *   Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy
 *
 *  TODO: integrate unit test library
 */

#include <cassert>

#include "Core.h"
#include "Shader.h"

class TestShader : public Core
{
public:
    TestShader() : Core("Test shader") { }

    void init() override
    {
        //  Performing tests
        Shader shader("shaders/flat.vs.glsl", "shaders/flat.fs.glsl");

        assert(shader.getProgramID() != 0);
    }
};

int main() {
    TestShader test;
    try {
        initOpenGL();
        test.initApp();
    }
    catch (std::exception& e) {
        e.what();
    }

    return 0;
}
