/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef SCENE_H
#define SCENE_H

// Textures ID
#define BRUSHED_METAL 0
#define DIRTY_BLUE_METAL 1
#define CONCRETE 2
#define DIRT 3
#define OLD_YELLOW_METAL 4
#define CONCRETE_2 5
#define DIRTY_BLUE_METAL_2 6
#define DIRTY_GREEN_METAL 7
#define CONCRETE_3 8
#define CONCRETE_4 9
#define CONCRETE_5 10
#define DIRT2 11
#define STEEL_ROPE 12
#define BLACK_METAL 13
#define OLD_YELLOW_METAL_2 14













#include <GL/glew.h>
#include <TexturesHandler.h>
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

	void draw(cam::Camera &camera, int shaderID) {

		scene->draw(camera, shaderID);
//        skyBox->draw(camera);
	}

	void rotateCraneTop(float angle) {
		// 7 : CraneTop
		objectsToMove[7]->rotateWorld(angle, glm::vec3(0.0, 1.0, 0.0));
	}

	void moveCraneHoist(float distance) {
		// 0 - 3 : wheels
		for (int i = 0; i < 4; ++i) {
			objectsToMove[i]->rotateLocal(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		// 6 : Hoist
		// TUTAJ TRZEBA ZROBIC PORUSZANIE HAKIEM

	}

	void moveCraneHook(float distance) {
		// 5 : Hook
		objectsToMove[5]->translateWorld(glm::vec3(0.0f, distance, 0.0f));
		// 4 : Line
		objectsToMove[4]->scaleWorld(glm::vec3(0.0f, 1.0f-distance/2.0f, 0.0f));
		objectsToMove[4]->translateWorld(glm::vec3(0.0f, distance, 0.0f));
	}

	void move() {
		// objectsToMove:
		// 0 - 3 : wheels
		// 4 : Line
		// 5 : Hook
		// 6 : Hoist
		// 7 : CraneTop

		//this->moveCraneHoist(1.0f);

		//this->moveCraneHook(0.1f);

		this->rotateCraneTop(0.1f);
	}
private:
	void addTextures() {

		textures.push_back("../textures/brushedMetal.png");
		textures.push_back("../textures/dirtyBlueMetal.png");
		textures.push_back("../textures/concrete.png");
		textures.push_back("../textures/dirt.png");
		textures.push_back("../textures/oldYellowMetal.png");
		textures.push_back("../textures/concrete2.png");
		textures.push_back("../textures/dirtyBlueMetal2.png");
		textures.push_back("../textures/dirtyGreenMetal.png");
		textures.push_back("../textures/concrete3.png");
		textures.push_back("../textures/concrete4.png");
		textures.push_back("../textures/concrete5.png");
		textures.push_back("../textures/dirt2.png");
		textures.push_back("../textures/steelRope.png");
		textures.push_back("../textures/blackMetal.png");
		textures.push_back("../textures/oldYellowMetal2.png");


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
		this->createConstructionSite();
		this->createFence();

	}
	
	void createFence() {
		std::shared_ptr<Collection> fence = std::make_shared<Collection>();

		std::shared_ptr<Collection> fencePart;

		for (int i = 0; i < 4; ++i) {
			fencePart = this->createFencePart();

			fencePart->translateWorld(glm::vec3(-20.0f, 0.0f, -20.0f+i*10.0f));

			fence->addObject(fencePart);
		}
		for (int i = 0; i < 4; ++i) {
			fencePart = this->createFencePart();

			fencePart->translateWorld(glm::vec3(-20.0f, 0.0f, -20.0f + i * 10.0f));
			fencePart->rotateWorld(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

			fence->addObject(fencePart);
		}
		for (int i = 0; i < 4; ++i) {
			fencePart = this->createFencePart();

			fencePart->translateWorld(glm::vec3(-20.0f, 0.0f, -20.0f + i * 10.0f));
			fencePart->rotateWorld(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

			fence->addObject(fencePart);
		}
		for (int i = 0; i < 4; ++i) {
			fencePart = this->createFencePart();

			fencePart->translateWorld(glm::vec3(-20.0f, 0.0f, -20.0f + i * 10.0f));
			fencePart->rotateWorld(270.0f, glm::vec3(0.0f, 1.0f, 0.0f));

			fence->addObject(fencePart);
		}

		fence->translateWorld(glm::vec3(17.5f, 0.0f, 17.5f));

		// Add to scene
		scene->addObject(fence);
	}

	std::shared_ptr<Collection> createFencePart() {
		std::shared_ptr<Collection> fencePart = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[OLD_YELLOW_METAL];

		// Vertical and horizontal 
		//1
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 5.0f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		fencePart->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[1], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.1f, 10.0f, 0.1f));
		part->translateWorld(glm::vec3(0.0f, 5.0f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 5.0f, 0.0f));
		fencePart->addObject(part);

		// Net :(

		std::shared_ptr<Collection> netPart;
		//1
		netPart = createFencePartNet();
		fencePart->addObject(netPart);
		//2
		netPart = createFencePartNet();
		netPart->rotateWorld(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		netPart->translateWorld(glm::vec3(0.0f, 0.0f, 10.0f));
		fencePart->addObject(netPart);
		

		return fencePart;
	}

	std::shared_ptr<Collection> createFencePartNet() {
		std::shared_ptr<Collection> net = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[BRUSHED_METAL];

		// Net :(
		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.414f, 0.05f));
		part->translateWorld(glm::vec3(0.0f, 0.707f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 9.0f));
		net->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 2.828f, 0.05f));
		part->translateWorld(glm::vec3(0.0f, 1.414f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 8.0f));
		net->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 4.243f, 0.05f));
		part->translateWorld(glm::vec3(0.0f, 2.121f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 7.0f));
		net->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 5.657f, 0.05f));
		part->translateWorld(glm::vec3(0.0f, 2.828f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 6.0f));
		net->addObject(part);
		//5-10
		for (int i = 0; i < 6; ++i) {
			part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
			part->scaleLocal(glm::vec3(0.05f, 7.071f, 0.05f));
			part->translateWorld(glm::vec3(0.0f, 3.536f, 0.0f));
			part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			part->translateWorld(glm::vec3(0.0f, 0.0f, 5.0 - i * 1.0f));
			net->addObject(part);
		}
		//11
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.414f, 0.05f));
		part->translateWorld(glm::vec3(0.0f, 0.707f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 4.0f, 0.0f));
		net->addObject(part);
		//12
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 2.828f, 0.05f));
		part->translateWorld(glm::vec3(0.0f, 1.414f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 3.0f, 0.0f));
		net->addObject(part);
		//13
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 4.243f, 0.05f));
		part->translateWorld(glm::vec3(0.0f, 2.121f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 2.0f, 0.0f));
		net->addObject(part);
		//14
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 5.657f, 0.05f));
		part->translateWorld(glm::vec3(0.0f, 2.828f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 1.0f, 0.0f));
		net->addObject(part);


		return net;
	}

	void createConstructionSite() {
		std::shared_ptr<Collection> constructionSite = std::make_shared<Collection>();

		std::shared_ptr<Collection> building;
		// Add 
		// Small building
		building = this->createSmallBuilding();

		building->translateWorld(glm::vec3(25.0f, 0.0f, -25.0f));

		constructionSite->addObject(building);

		// Medium building

		building = this->createMediumBuilding();

		building->translateWorld(glm::vec3(-25.0f, 0.0f, 30.0f));

		constructionSite->addObject(building);
		// Big building

		building = this->createBigBuilding();

		building->translateWorld(glm::vec3(-25.0f, 0.0f, -25.0f));

		constructionSite->addObject(building);

		// Add to scene
		scene->addObject(constructionSite);
	}

	std::shared_ptr<Collection> createBigBuilding() {
		std::shared_ptr<Collection> building = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_4];

		// Floors
		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(20.0f, 1.0f, 25.0f));
		part->translateWorld(glm::vec3(0.0f, 5.5f, 0.0f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(20.0f, 1.0f, 25.0f));
		part->translateWorld(glm::vec3(0.0f, 10.5f, 0.0f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(20.0f, 1.0f, 25.0f));
		part->translateWorld(glm::vec3(0.0f, 15.5f, 0.0f));
		building->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(20.0f, 1.0f, 25.0f));
		part->translateWorld(glm::vec3(0.0f, 20.5f, 0.0f));
		building->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(20.0f, 1.0f, 25.0f));
		part->translateWorld(glm::vec3(0.0f, 25.5f, 0.0f));
		building->addObject(part);

		std::shared_ptr<Collection> pillar;

		// Pillars
		//1
		pillar = createBigBuildingBigPillar();
		pillar->translateWorld(glm::vec3(9.0f, 0.0f, 11.0f));
		building->addObject(pillar);
		//2
		pillar = createBigBuildingBigPillar();
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, 11.0f));
		building->addObject(pillar);
		//3
		pillar = createBigBuildingBigPillar();
		pillar->translateWorld(glm::vec3(9.0f, 0.0f, -11.0f));
		building->addObject(pillar);
		//4
		pillar = createBigBuildingBigPillar();
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, -11.0f));
		building->addObject(pillar);


		// Second floors
		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(20.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(0.0f, 5.5f, 20.0f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(20.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(-0.0f, 10.5f, 20.0f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(20.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(-0.0f, 15.5f, 20.0f));
		building->addObject(part);

		// Second floors pillars
		//1
		pillar = createBigBuildingSmallPillar();
		pillar->translateWorld(glm::vec3(8.0f, 0.0f, 27.0f));
		building->addObject(pillar);
		//2
		pillar = createBigBuildingSmallPillar();
		pillar->translateWorld(glm::vec3(-8.0f, 0.0f, 27.0f));
		building->addObject(pillar);

		return building;
	}

	std::shared_ptr<Collection> createBigBuildingBigPillar() {
		std::shared_ptr<Collection> pillar = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_2];

		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 28.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 14.0f, 0.0f));
		pillar->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 28.5f, -0.4f));
		pillar->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 28.5f, -0.4f));
		pillar->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 28.5f, 0.4f));
		pillar->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 28.5f, 0.4f));
		pillar->addObject(part);

		return pillar;
	}

	std::shared_ptr<Collection> createBigBuildingSmallPillar() {
		std::shared_ptr<Collection> pillar = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_2];

		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 18.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 9.0f, 0.0f));
		pillar->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 18.5f, -0.4f));
		pillar->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 18.5f, -0.4f));
		pillar->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 18.5f, 0.4f));
		pillar->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 18.5f, 0.4f));
		pillar->addObject(part);

		return pillar;
	}

	std::shared_ptr<Collection> createMediumBuilding() {
		std::shared_ptr<Collection> building = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_4];

		// Floors
		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(25.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(0.0f, 5.5f, 0.0f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(25.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(0.0f, 10.5f, 0.0f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(25.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(0.0f, 15.5f, 0.0f));
		building->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(25.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(0.0f, 20.05f, 0.0f));
		building->addObject(part);

		std::shared_ptr<Collection> pillar;

		// Pillars
		//1
		pillar = createMediumBuildingBigPillar();
		pillar->translateWorld(glm::vec3(9.0f, 0.0f, 6.0f));
		building->addObject(pillar);
		//2
		pillar = createMediumBuildingBigPillar();
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, 6.0f));
		building->addObject(pillar);
		//3
		pillar = createMediumBuildingBigPillar();
		pillar->translateWorld(glm::vec3(9.0f, 0.0f, -6.0f));
		building->addObject(pillar);
		//4
		pillar = createMediumBuildingBigPillar();
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, -6.0f));
		building->addObject(pillar);
		//5
		pillar = createMediumBuildingBigPillar();
		pillar->translateWorld(glm::vec3(0.0f, 0.0f, -6.0f));
		building->addObject(pillar);


		// Second floors
		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(15.0f, 1.0f, 10.0f));
		part->translateWorld(glm::vec3(-5.0f, 5.5f, -12.5f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(15.0f, 1.0f, 10.0f));
		part->translateWorld(glm::vec3(-5.0f, 10.5f, -12.5f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(15.0f, 1.0f, 10.0f));
		part->translateWorld(glm::vec3(-5.0f, 15.5f, -12.5f));
		building->addObject(part);

		// Second floors pillars
		//1
		pillar = createMediumBuildingSmallPillar();
		pillar->translateWorld(glm::vec3(0.0f, 0.0f, -14.0f));
		building->addObject(pillar);
		//2
		pillar = createMediumBuildingSmallPillar();
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, -14.0f));
		building->addObject(pillar);

		return building;
	}

	std::shared_ptr<Collection> createMediumBuildingBigPillar() {
		std::shared_ptr<Collection> pillar = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_2];

		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 23.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 11.5f, 0.0f));
		pillar->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 23.5f, -0.4f));
		pillar->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 23.5f, -0.4f));
		pillar->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 23.5f, 0.4f));
		pillar->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 23.5f, 0.4f));
		pillar->addObject(part);

		return pillar;
	}

	std::shared_ptr<Collection> createMediumBuildingSmallPillar() {
		std::shared_ptr<Collection> pillar = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_2];

		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 18.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 9.0f, 0.0f));
		pillar->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 18.5f, -0.4f));
		pillar->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 18.5f, -0.4f));
		pillar->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 18.5f, 0.4f));
		pillar->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 18.5f, 0.4f));
		pillar->addObject(part);

		return pillar;
	}


	std::shared_ptr<Collection> createSmallBuilding() {
		std::shared_ptr<Collection> building = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_4];

		// Floors
		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(15.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(0.0f, 5.5f, 0.0f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(15.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(0.0f, 10.5f, 0.0f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(15.0f, 1.0f, 15.0f));
		part->translateWorld(glm::vec3(0.0f, 15.5f, 0.0f));
		building->addObject(part);

		std::shared_ptr<Collection> pillar;

		// Pillars
		//1
		pillar = createSmallBuildingPillar();
		pillar->translateWorld(glm::vec3(6.0f, 0.0f, 6.0f));
		building->addObject(pillar);
		//2
		pillar = createSmallBuildingPillar();
		pillar->translateWorld(glm::vec3(-6.0f, 0.0f, 6.0f));
		building->addObject(pillar);
		//3
		pillar = createSmallBuildingPillar();
		pillar->translateWorld(glm::vec3(6.0f, 0.0f, -6.0f));
		building->addObject(pillar);
		//4
		pillar = createSmallBuildingPillar();
		pillar->translateWorld(glm::vec3(-6.0f, 0.0f, -6.0f));
		building->addObject(pillar);

		return building;
	}

	std::shared_ptr<Collection> createSmallBuildingPillar() {
		std::shared_ptr<Collection> pillar = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_2];

		//1
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(1.0f, 18.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 9.0f, 0.0f));
		pillar->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 18.5f, -0.4f));
		pillar->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 18.5f, -0.4f));
		pillar->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(-0.4f, 18.5f, 0.4f));
		pillar->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.05f, 1.0f, 0.05f));
		part->translateWorld(glm::vec3(0.4f, 18.5f, 0.4f));
		pillar->addObject(part);

		return pillar;
	}

	void createGround() {
		std::shared_ptr<Collection> tiles = std::make_shared<Collection>();

		std::string tileTexture = textures[DIRT];
		// 0 0
		tiles->addObject(createTile(-25.0f, -25.0f, tileTexture));
		// 1 0
		tiles->addObject(createTile(0.0f, -25.0f, tileTexture));
		// 2 0
		tiles->addObject(createTile(25.0f, -25.0f, tileTexture));
		// 0 1
		tiles->addObject(createTile(-25.0f, 0.0f, tileTexture));
		// 1 1
		tiles->addObject(createTile(0.0f, 0.0f, tileTexture));
		// 2 1
		tiles->addObject(createTile(25.0f, 0.0f, tileTexture));
		// 0 2
		tiles->addObject(createTile(-25.0f, 25.0f, tileTexture));
		// 1 2
		tiles->addObject(createTile(0.0f, 25.0f, tileTexture));
		// 2 2
		tiles->addObject(createTile(25.0f, 25.0f, tileTexture));

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
		top->translateWorld(glm::vec3(0.0f, 39.9f, 0.0f));

		base->addObject(top);
		

		return base;
	}

	std::shared_ptr<Collection> createCraneBaseTop() {
		std::shared_ptr<Collection> topParts = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[DIRTY_BLUE_METAL];

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

		std::string partTexture = textures[DIRTY_BLUE_METAL];

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

		std::string weightsTexture = textures[CONCRETE_3];

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

		std::string standTexture = textures[DIRTY_BLUE_METAL];

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

		std::string partTexture = textures[DIRTY_BLUE_METAL];

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

		std::string partTexture = textures[DIRTY_BLUE_METAL];

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

		std::string partTexture = textures[DIRTY_BLUE_METAL];

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
		part->scaleLocal(glm::vec3(0.25f, 3.5f, 0.25f));
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

		std::string partTexture = textures[CONCRETE_2];

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

		std::string partTexture = textures[DIRTY_BLUE_METAL_2];

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

		std::string partTexture = textures[DIRTY_GREEN_METAL];

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(3.0f, 0.5, 2.0f));
		part->translateWorld(glm::vec3(0.0f, 0.5f, 0.0f));
		hoistHolder->addObject(part);

		return hoistHolder;
	}

	std::shared_ptr<Collection> createCraneTopHoistHolderWheel() {
		std::shared_ptr<Collection> wheel = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[BLACK_METAL];

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

		std::string partTexture = textures[STEEL_ROPE];

		part = std::shared_ptr<Object>(new Object(models[0], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(0.09f, 20.0f, 0.09f));
		part->translateWorld(glm::vec3(0.0f, -10.0f, 0.0f));
		line->addObject(part);

		objectsToMove.push_back(line);

		return line;
	}

	std::shared_ptr<Collection> createCraneTopHoistHook() {
		std::shared_ptr<Collection> hook = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[OLD_YELLOW_METAL_2];

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

		objectsToMove.push_back(hook);

		return hook;
	}

};
#endif // !SCENE_H