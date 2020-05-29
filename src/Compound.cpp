#include "Compound.h"

void Compound::addObject(std::unique_ptr<Object> object) {
	objects.push_back(std::move(object));
}

void Compound::translate(const glm::vec3& offset)
{
	for (auto& o : objects) {
		o->translate(offset);
	}
}
void Compound::rotate(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& o : objects) {
		o->rotate(angle, axis);
	}
}
void Compound::rotate2(const std::optional<glm::vec3>& axis)
{
	for (auto& o : objects) {
		o->rotate2( axis);
	}
}
void Compound::scale(const glm::vec3& value)
{
	for (auto& o : objects) {
		o->scale(value);
	}
}

void Compound::draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const
{
	for (auto& o : objects) {
		o->draw(camera, windowSettings, use_color);
	}
}
