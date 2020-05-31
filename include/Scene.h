/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef SCENE_H
#define SCENE_H

#include "TexturesHandler.h"
#include "Shader.h"
#include "Object.h"

#include <vector>

class Scene
{
	TexturesHandler texturesHandler;
	std::vector<std::unique_ptr<Shader>> shaders;
	std::vector<Object> objects;
public:
	Scene() {

	}
};
#endif // !SCENE_H