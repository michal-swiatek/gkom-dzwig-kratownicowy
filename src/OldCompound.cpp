#include "OldCompound.h"

void OldCompound::addModel(std::unique_ptr<OldModel> m) {
	models.push_back(std::move(m));
}

void OldCompound::translate(const glm::vec3& offset)
{
	for (auto& m : models) {
		m->translate(offset);
	}
}
void OldCompound::rotate(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& m : models) {
		m->rotate(angle, axis);
	}
}
void OldCompound::rotate2(const std::optional<glm::vec3>& axis)
{
	for (auto& m : models) {
		m->rotate2( axis);
	}
}
void OldCompound::scale(const glm::vec3& value)
{
	for (auto& m : models) {
		m->scale(value);
	}
}

OldCompound::OldCompound() : OldModel()
{
}

void OldCompound::draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const
{
	for (auto& m : models) {
		m->draw(camera, windowSettings, use_color);
	}
}
