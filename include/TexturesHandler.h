/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef TEXTURESHANDLER_H
#define TEXTURESHANDLER_H

#include "../external-libraries/include/STB/stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	unsigned int getTextureID(std::string filePath);

	unsigned int useTexture(std::string filePath);

	unsigned int useTexture(int index);
};
#endif // !TEXTURESHANDLER_H