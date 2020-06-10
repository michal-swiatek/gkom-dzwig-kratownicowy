/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef TEXTURESHANDLER_H
#define TEXTURESHANDLER_H

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "Shader.h"

#include <vector>
#include <iostream>

class TexturesHandler
{
	const static int MAX_TEXTURES_NUM = 16;
	class TextureInfo {
	public:
		std::string filePath;
		int width;
		int height;
		int nrChannels;
		unsigned int textureID;
		TextureInfo(std::string name) {
			this->filePath = name;
		}
		~TextureInfo() = default;
	};
	std::vector<TextureInfo*> textures;
public:
	TexturesHandler(bool flipTextures = true);
	~TexturesHandler();

	void addTexture(std::string filePath);

	unsigned int getTextureID(const std::string& filePath);

	unsigned int useTexture(const std::string& filePath);

	unsigned int useTexture(int index);
};
#endif // !TEXTURESHANDLER_H