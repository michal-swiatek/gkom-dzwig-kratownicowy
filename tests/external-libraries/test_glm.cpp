/*
 *  Created by michal-swiatek on 11.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy
 */

#include <cassert>

#include <glm/glm.hpp>

int main() {
    glm::vec3 v1(1.0f);
    glm::vec3 v2(1.0f, 2.0f, 3.0f);
    glm::vec3 v3 = v1 + v2;

    assert(v3.x == 2.0f);
    assert(v3.y == 3.0f);
    assert(v3.z == 4.0f);

    assert(v3.r == 2.0f);
    assert(v3.g == 3.0f);
    assert(v3.b == 4.0f);

    assert(v3.s == 2.0f);
    assert(v3.t == 3.0f);

    return 0;
}
