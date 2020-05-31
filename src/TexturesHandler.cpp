/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#include "TexturesHandler.h"

TexturesHandler::TexturesHandler(bool flipTextures) {
	stbi_set_flip_vertically_on_load(flipTextures);
}
TexturesHandler::~TexturesHandler() {
	for (int i = 0; i < textures.size(); ++i) {
		delete textures[i];
	}
}

void TexturesHandler::addTexture(std::string filePath) {

	if (textures.size() < MAX_TEXTURES_NUM) {
		TextureInfo* textureInfo = new TextureInfo(filePath);
		glGenTextures(1, &textureInfo->textureID);
		glBindTexture(GL_TEXTURE_2D, textureInfo->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		unsigned char *data = stbi_load(filePath.c_str(), &textureInfo->width, &textureInfo->height, &textureInfo->nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureInfo->width, textureInfo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			textures.push_back(textureInfo);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		//std::cout << "TEXTURE:"<< textureInfo->filePath<< " "<< textureInfo->width<<" "<<textureInfo->height << std::endl;
		stbi_image_free(data);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
}

unsigned int TexturesHandler::getTextureID(std::string filePath) {
	for (auto texture : this->textures) {
		if (texture->filePath == filePath) {
			return texture->textureID;
		}
	}
	return 0;
}

unsigned int TexturesHandler::useTexture(std::string filePath) {
	for (int i = 0; i < this->textures.size(); ++i) {
		if (this->textures[i]->filePath == filePath) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, this->textures[i]->textureID);
			return i;
		}
	}
	return 0;
}

unsigned int TexturesHandler::useTexture(int index) {
	if (index < this->textures.size() && index >= 0) {
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, this->textures[index]->textureID);
		return index;
	}
	return 0;
}