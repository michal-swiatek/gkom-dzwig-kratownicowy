/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef SCENE_H
#define SCENE_H

#include "TexturesHandler.h"
#include "Shader.h"
#include "Object.h"
#include "Model.h"
#include "Cuboid.h"
#include "Cylinder.h"
#include "Collection.h"

#include <vector>

class Scene
{
	TexturesHandler texturesHandler;
	std::vector<std::shared_ptr<Model>> models;
	std::vector<std::string> textures;
	std::vector<std::shared_ptr<Collection>> objectsToMove;
	std::unique_ptr<Collection> scene;
public:
	Scene() {
		this->addTextures();
		this->createModels();
		this->createScene();

		scene->translateWorld(glm::vec3(-15.0f, 0.0f, -15.0f));
	}

	void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) {
		scene->draw(camera, shaderID);
	}

	void move() {
		/*objectsToMove[0]->rotateWorld((float)glfwGetTime() * 0.1, glm::vec3(0.0, 1.0, 0.0));
		objectsToMove[0]->objects[3]->scaleWorld(glm::vec3(1.0, 1.01, 1.0));

		objectsToMove[0]->translateWorld(glm::vec3(0.0f, 3.0f, 0.0f));

		objectsToMove[0]->translateWorld(glm::vec3(0.0f, -3.0f, 0.0f));*/

		for (int i = 0; i < 4; ++i) {
			objectsToMove[i]->rotateLocal(0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		objectsToMove[5]->rotateWorld(0.1f, glm::vec3(0.0, 1.0, 0.0));
		//objectsToMove[4]->translateLocal(glm::vec3(0.01f, 0.0f, 0.0f));

		//for (auto& object : objectsToMove) {
		//	object->rotateWorld(sin((float)glfwGetTime()) * 0.1, glm::vec3(0.0, 1.0, 0.0));
		//}
	}
private:
	void addTextures() {
		textures.push_back("./textures/grass2.png");
		textures.push_back("./textures/awesomeface.png");

		for (auto texture : textures) {
			texturesHandler.addTexture(texture);
		}
	}
	void createModels() {
		models.push_back(std::make_shared<Cuboid>());
		models.push_back(std::make_shared<Cylinder>(1.0f, 1.0f, 1.0f, 8, 1));
	}
	void createScene() {
		scene = std::make_unique<Collection>();
		

		this->createGround();
		this->createCrane();

	}

	void createGround() {
		std::shared_ptr<Collection> tiles = std::make_shared<Collection>();

		// Add ground tiles.
		// 0 0
		tiles->addObject(createTile(-25.0f, -25.0f, textures[0]));
		// 1 0
		tiles->addObject(createTile(0.0f, -25.0f, textures[0]));
		// 2 0
		tiles->addObject(createTile(25.0f, -25.0f, textures[0]));
		// 0 1
		tiles->addObject(createTile(-25.0f, 0.0f, textures[0]));
		// 1 1
		tiles->addObject(createTile(0.0f, 0.0f, textures[0]));
		// 2 1
		tiles->addObject(createTile(25.0f, 0.0f, textures[0]));
		// 0 2
		tiles->addObject(createTile(-25.0f, 25.0f, textures[0]));
		// 1 2
		tiles->addObject(createTile(0.0f, 25.0f, textures[0]));
		// 2 2
		tiles->addObject(createTile(25.0f, 25.0f, textures[0]));

		// Add to scene
		scene->addObject(tiles);
	}
	std::shared_ptr<Object> createTile(float x, float z, std::string texture) {
		std::shared_ptr<Object> tile = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(texture)));
		tile->scaleLocal(glm::vec3(25.0f, 0.01f, 25.0f));
		tile->translateWorld(glm::vec3(x, -0.005f, z));
		return tile;
	}

	void createCrane() {
		std::shared_ptr<Collection> crane = std::make_shared<Collection>();

		crane->addObject(this->createCraneBase());

		std::shared_ptr<Collection> craneTop = this->createCraneTop();

		craneTop->translateWorld(glm::vec3(0.0f, 37.5f, 0.0f));

		objectsToMove.push_back(craneTop);

		crane->addObject(craneTop);

		crane->rotateWorld(120.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		crane->translateWorld(glm::vec3(15.0f, 0.0f, 15.0f));

		scene->addObject(crane);
	}

	std::shared_ptr<Collection> createCraneBase() {
		std::shared_ptr<Collection> base = std::make_shared<Collection>();

		base->addObject(this->createCraneBaseBottom());
		float nextHeight = 2.5f;
		for (int i = 0; i < 16; ++i) {
			std::shared_ptr<Collection> part = createCraneBasePart();
			part->translateWorld(glm::vec3(0.0f, i*2.5f, 0.0f));
			base->addObject(part);
		}

		std::shared_ptr<Collection> top = createCraneBaseTop();
		top->translateWorld(glm::vec3(0.0f, 40.0f, 0.0f));

		base->addObject(top);
		

		return base;
	}

	std::shared_ptr<Collection> createCraneBaseTop() {
		std::shared_ptr<Collection> topParts = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		//1
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 10.16f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 5.08f, 0.0f));
		part->rotateWorld(9.97f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(-1.25f, 0.0f, -1.25f));
		topParts->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 10.16f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 5.08f, 0.0f));
		part->rotateWorld(9.97f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->rotateWorld(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(1.25f, 0.0f, -1.25f));
		topParts->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 10.16f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 5.08f, 0.0f));
		part->rotateWorld(-9.97f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->rotateWorld(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(-1.25f, 0.0f, 1.25f));
		topParts->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 10.16f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 5.08f, 0.0f));
		part->rotateWorld(-9.97f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(1.25f, 0.0f, 1.25f));
		topParts->addObject(part);

		return topParts;
	}

	std::shared_ptr<Collection> createCraneBasePart() {
		std::shared_ptr<Collection> parts = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		// Add cube sceleton
		//1
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->translateWorld(glm::vec3(-1.25, 1.25f, -1.25f));
		parts->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->translateWorld(glm::vec3(1.25, 1.25f, -1.25f));
		parts->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->translateWorld(glm::vec3(-1.25, 1.25f, 1.25f));
		parts->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->translateWorld(glm::vec3(1.25, 1.25f, 1.25f));
		parts->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.15f, 3.54f, 0.15f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(1.25, 1.25f, 0.0f));
		parts->addObject(part);
		//6
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.15f, 3.54f, 0.15f));
		part->rotateWorld(-45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(1.25f, 1.25f, 0.0f));
		parts->addObject(part);
		//7
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.15f, 3.54f, 0.15f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(-1.25f, 1.25f, 0.0f));
		parts->addObject(part);
		//8
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.15f, 3.54f, 0.15f));
		part->rotateWorld(-45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(-1.25f, 1.25f, 0.0f));
		parts->addObject(part);
		//9
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.15f, 3.54f, 0.15f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 1.25f));
		parts->addObject(part);
		//10
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.15f, 3.54f, 0.15f));
		part->rotateWorld(-45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 1.25f));
		parts->addObject(part);
		//11
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.15f, 3.54f, 0.15f));
		part->rotateWorld(-45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, -1.25f));
		parts->addObject(part);
		//12
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.15f, 3.54f, 0.15f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, -1.25f));
		parts->addObject(part);


		return parts;
	}

	std::shared_ptr<Collection> createCraneBaseBottom() {
		std::shared_ptr<Collection> baseBottom = std::make_shared<Collection>();

		baseBottom->addObject(this->createCraneBaseBottomWeights());
		baseBottom->addObject(this->createCraneBaseBottomStand());

		return baseBottom;
	}

	std::shared_ptr<Collection> createCraneBaseBottomWeights() {
		std::shared_ptr<Collection> weights = std::make_shared<Collection>();

		std::shared_ptr<Object> cube;

		std::string weightsTexture = textures[0];

		// Add weights
		//1
		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(5.0f, 0.5f, 1.25f));
		cube->translateWorld(glm::vec3(0.0f, 1.25f, -1.875f));
		weights->addObject(cube);
		//2
		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(5.0f, 0.5f, 1.25f));
		cube->translateWorld(glm::vec3(0.0f, 1.25f, 1.875f));
		weights->addObject(cube);
		//3
		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(1.25f, 0.5f, 5.0f));
		cube->translateWorld(glm::vec3(-1.875f, 1.75f, 0.0f));
		weights->addObject(cube);
		//4
		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(1.25f, 0.5f, 5.0f));
		cube->translateWorld(glm::vec3(1.875f, 1.75f, 0.0f));
		weights->addObject(cube);
		//5
		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(5.0f, 0.5f, 1.25f));
		cube->translateWorld(glm::vec3(0.0f, 2.25f, -1.875f));
		weights->addObject(cube);
		//6
		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(5.0f, 0.5f, 1.25f));
		cube->translateWorld(glm::vec3(0.0f, 2.25f, 1.875f));
		weights->addObject(cube);


		return weights;
	}

	std::shared_ptr<Collection> createCraneBaseBottomStand() {
		std::shared_ptr<Collection> stand = std::make_shared<Collection>();

		std::string standTexture = textures[0];

		std::shared_ptr<Object> cube;

		// Add base holders
		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(standTexture)));
		cube->scaleLocal(glm::vec3(2.0f, 1.0f, 2.0f));
		cube->translateWorld(glm::vec3(-1.5f, 0.5f, -1.5f));
		stand->addObject(cube);

		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(standTexture)));
		cube->scaleLocal(glm::vec3(2.0f, 1.0f, 2.0f));
		cube->translateWorld(glm::vec3(1.5f, 0.5f, -1.5f));
		stand->addObject(cube);

		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(standTexture)));
		cube->scaleLocal(glm::vec3(2.0f, 1.0f, 2.0f));
		cube->translateWorld(glm::vec3(-1.5f, 0.5f, 1.5f));
		stand->addObject(cube);

		cube = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(standTexture)));
		cube->scaleWorld(glm::vec3(2.0f, 1.0f, 2.0f));
		cube->translateWorld(glm::vec3(1.5f, 0.5f, 1.5f));
		stand->addObject(cube);

		return stand;
	}
	
	std::shared_ptr<Collection> createCraneTop() {
		std::shared_ptr<Collection> top = std::make_shared<Collection>();
		float nextLength = 5.0f;
		std::shared_ptr<Collection> part;
		for (int i = 1; i < 10; ++i) {
			part = createCraneTopPart();
			part->translateWorld(glm::vec3(i*nextLength, 0.0f, 0.0f));
			top->addObject(part);
		}
		for (int i = 0; i < 4; ++i) {
			part = createCraneTopPart();
			part->translateWorld(glm::vec3(-i*nextLength, 0.0f, 0.0f));
			top->addObject(part);
		}

		part = createCraneTopConeEnd();
		part->translateWorld(glm::vec3(9*nextLength, 0.0f, 0.0f));
		top->addObject(part);

		part = createCraneTopTriangleEnd();
		part->translateWorld(glm::vec3(-4*nextLength+0.125f, 0.0f, 0.0f));
		top->addObject(part);

		part = createCraneTopWeights();
		part->translateWorld(glm::vec3(-4 * nextLength + 1.0f, 0.0f, 0.0f));
		top->addObject(part);

		part = createCraneStation();
		part->translateWorld(glm::vec3(4.0f, -2.5f, 2.0f));
		top->addObject(part);

		part = createCraneTopHoist();
		part->translateWorld(glm::vec3(20.0f, 0.0f, 0.0f));
		top->addObject(part);

		objectsToMove.push_back(top);

		return top;
	}

	std::shared_ptr<Collection> createCraneTopPart() {
		std::shared_ptr<Collection> top = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		std::shared_ptr<Collection> wall = std::make_shared<Collection>();

		//1.1
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 5.0f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		wall->addObject(part);
		//1.2
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 5.0f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		wall->addObject(part);
		//1.3
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 4.72f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 2.36f, 0.0f));
		part->rotateWorld(58.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		wall->addObject(part);
		//1.4
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 2.69f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 1.345f, 0.0f));
		part->rotateWorld(-32.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(-5.0f, 0.0f, 0.0f));
		wall->addObject(part);

		wall->rotateWorld(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		wall->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));

		top->addObject(wall);

		wall = std::make_shared<Collection>();
		//2.1
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 5.0f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		wall->addObject(part);
		//2.2
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 5.0f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		wall->addObject(part);
		//2.3
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 4.72f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 2.36f, 0.0f));
		part->rotateWorld(58.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		wall->addObject(part);
		//2.4
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 2.69f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 1.345f, 0.0f));
		part->rotateWorld(-32.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(-5.0f, 0.0f, 0.0f));
		wall->addObject(part);

		wall->rotateWorld(-30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		wall->translateWorld(glm::vec3(0.0f, 0.0f, 1.25f));

		top->addObject(wall);

		//3.1
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 5.59f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 2.8f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->rotateWorld(26.56f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));
		top->addObject(part);
		//3.2
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 5.59f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 2.8f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->rotateWorld(-26.56f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 1.25f));
		top->addObject(part);

		return top;
	}

	std::shared_ptr<Collection> createCraneTopTriangleEnd() {
		std::shared_ptr<Collection> top = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->rotateWorld(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 0.0f));
		part->rotateWorld(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 0.0f));
		part->rotateWorld(-30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 1.25f));
		top->addObject(part);

		return top;
	}

	std::shared_ptr<Collection> createCraneTopConeEnd() {
		std::shared_ptr<Collection> top = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 2.5f, 0.1f));
		part->rotateWorld(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 2.5f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 0.0f));
		part->rotateWorld(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 2.5f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 0.0f));
		part->rotateWorld(-30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 1.25f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.3f, 3.5f, 0.3f));
		part->translateWorld(glm::vec3(0.0f, 1.53f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(2.165f, 0.0f, 0.0f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 0.0f));
		part->rotateWorld(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));
		part->rotateWorld(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 2.5f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 0.0f));
		part->rotateWorld(-30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 1.25f));
		part->rotateWorld(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		top->addObject(part);

		return top;
	}

	std::shared_ptr<Collection> createCraneTopWeights() {
		std::shared_ptr<Collection> weights = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 4.8f, 2.3f));
		part->translateWorld(glm::vec3(0.0f, 1.08f, 0.0f));
		weights->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 4.8f, 2.3f));
		part->translateWorld(glm::vec3(1.1f, 1.08f, 0.0f));
		weights->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 4.8f, 2.3f));
		part->translateWorld(glm::vec3(2.2f, 1.08f, 0.0f));
		weights->addObject(part);

		return weights;
	}

	std::shared_ptr<Collection> createCraneStation() {
		std::shared_ptr<Collection> station = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(2.0f, 4.0f, 2.5f));
		part->translateWorld(glm::vec3(0.0f, 2.0f, 0.0f));
		station->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 3.0f, 2.5f));
		part->translateWorld(glm::vec3(1.5f, 1.5f, 0.0f));
		station->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.4142f, 1.4142f, 2.49f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(1.0f, 3.0f, 0.0f));
		station->addObject(part);

		return station;
	}

	std::shared_ptr<Collection> createCraneTopHoist() {
		std::shared_ptr<Collection> hoist = std::make_shared<Collection>();

		std::shared_ptr<Collection> part;

		part = createCraneTopHoistHolder();
		part->translateWorld(glm::vec3(0.0f, 0.0f, 0.0f));
		hoist->addObject(part);


		//1
		part = createCraneTopHoistHolderWheel();
		part->translateWorld(glm::vec3(1.0f, 0.5f, 1.0f));
		hoist->addObject(part);
		objectsToMove.push_back(part);
		//2
		part = createCraneTopHoistHolderWheel();
		part->translateWorld(glm::vec3(1.0f, 0.5f, -1.25f));
		hoist->addObject(part);
		objectsToMove.push_back(part);
		//3
		part = createCraneTopHoistHolderWheel();
		part->translateWorld(glm::vec3(-1.0f, 0.5f, 1.0f));
		hoist->addObject(part);
		objectsToMove.push_back(part);
		//4
		part = createCraneTopHoistHolderWheel();
		part->translateWorld(glm::vec3(-1.0f, 0.5f, -1.25f));
		hoist->addObject(part);
		objectsToMove.push_back(part);



		part = createCraneTopHoistLine();
		part->translateWorld(glm::vec3(0.0f, 0.0f, 0.0f));
		hoist->addObject(part);

		part = createCraneTopHoistHook();
		part->translateWorld(glm::vec3(0.0f, -20.0f, 0.0f));
		hoist->addObject(part);

		objectsToMove.push_back(hoist);
		return hoist;
	}

	std::shared_ptr<Collection> createCraneTopHoistHolder() {
		std::shared_ptr<Collection> hoistHolder = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(3.0f, 0.5, 2.0f));
		part->translateWorld(glm::vec3(0.0f, 0.5f, 0.0f));
		hoistHolder->addObject(part);

		return hoistHolder;
	}

	std::shared_ptr<Collection> createCraneTopHoistHolderWheel() {
		std::shared_ptr<Collection> wheel = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.25f, 0.25f, 0.25f));
		part->translateWorld(glm::vec3(0.0f, 0.125f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		wheel->addObject(part);

		return wheel;
	}

	std::shared_ptr<Collection> createCraneTopHoistLine() {
		std::shared_ptr<Collection> line = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.09f, 20.0f, 0.09f));
		part->translateWorld(glm::vec3(0.0f, -10.0f, 0.0f));
		line->addObject(part);


		return line;
	}

	std::shared_ptr<Collection> createCraneTopHoistHook() {
		std::shared_ptr<Collection> hook = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[0];

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.3f, 1.0f, 0.3f));
		part->translateWorld(glm::vec3(0.0f, -0.5f, 0.0f));
		hook->addObject(part);

		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 0.71f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, -0.355f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, -0.8f, 0.0f));
		hook->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.09f, 0.5f, 0.09f));
		part->translateWorld(glm::vec3(0.0f, -1.52f, -0.49f));
		hook->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 0.71f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, -0.355f, 0.0f));
		part->rotateWorld(-45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, -1.74f, -0.505f));
		hook->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.09f, 0.71f, 0.09f));
		part->translateWorld(glm::vec3(0.0f, -0.355f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, -1.74f, 0.49f));
		hook->addObject(part);

		return hook;
	}

};
#endif // !SCENE_H