#include "Compound.h"

void Compound::addModel(std::unique_ptr<Model> m) {
	models.push_back(std::move(m));
}

void Compound::translate(const glm::vec3& offset)
{
	for (auto& m : models) {
		m->translate(offset);
	}
}
void Compound::rotate(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& m : models) {
		m->rotate(angle, axis);
	}
}
void Compound::rotate2(const std::optional<glm::vec3>& axis)
{
	for (auto& m : models) {
		m->rotate2( axis);
	}
}
void Compound::scale(const glm::vec3& value)
{
	for (auto& m : models) {
		m->scale(value);
	}
}

Compound::Compound() : Model()
{
}

void Compound::draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const
{
	for (auto& m : models) {
		m->draw(camera, windowSettings, use_color);
	}
}
