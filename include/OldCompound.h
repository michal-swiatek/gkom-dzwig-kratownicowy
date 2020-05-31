#ifndef OLDCOMPOUND_H
#define OLDCOMPOUND_H

#include "OldModel.h"

class OldCompound : public OldModel
{
protected:
	std::vector<std::unique_ptr<OldModel>> models;

public:
	void addModel(std::unique_ptr<OldModel> models);

    void translate(const glm::vec3& offset) override;
    void rotate(float angle, const std::optional<glm::vec3>& axis) override;
    void scale(const glm::vec3& value) override;

    OldCompound();


    void rotate2(const std::optional<glm::vec3>& axis);


    void draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const override;


};



#endif // !OLDCOMPOUND_H