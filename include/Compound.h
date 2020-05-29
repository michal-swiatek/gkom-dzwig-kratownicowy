#ifndef COMPOUND_H
#define COMPOUND_H

#include "Object.h"
#include <vector>

class Compound{
protected:
	std::vector<std::unique_ptr<Object>> objects;

public:
	void addObject(std::unique_ptr<Object> object);

    void translate(const glm::vec3& offset);
    void rotate(float angle, const std::optional<glm::vec3>& axis);
    void scale(const glm::vec3& value);




    void rotate2(const std::optional<glm::vec3>& axis);


    void draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const;


};



#endif // !COMPOUND_H