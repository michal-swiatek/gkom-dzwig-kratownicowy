#ifndef COMPOUND_H
#define COMPOUND_H

#include "Model.h"

class Compound : public Model
{
protected:
	std::vector<std::unique_ptr<Model>> models;

public:
	void addModel(std::unique_ptr<Model> models);

    void translate(const glm::vec3& offset) override;
    void rotate(float angle, const std::optional<glm::vec3>& axis) override;
    void scale(const glm::vec3& value) override;

    Compound();


    void rotate2(const std::optional<glm::vec3>& axis);


    void draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const override;


};



#endif // !COMPOUND_H