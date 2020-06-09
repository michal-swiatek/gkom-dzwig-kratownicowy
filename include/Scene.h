/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef SCENE_H
#define SCENE_H

/*
*	Objects lengths and widths
*/
// Fence
#define NET_LENGTH 1.414f
#define NET_WIDTH 0.05f
#define FENCE_BAR_RADIUS 0.1f
#define FENCE_BAR_LENGTH_1 5.0f
#define FENCE_BAR_LENGTH_2 10.0f
#define FENCE_PARTS_IN_SQUARE_NUM 4
// Buildings
#define PILLAR_WIDTH 1.0f
#define ROD_WIDTH 0.05f
#define ROD_HEIGHT 1.0f
#define BUILDING_FLOOR_HEIGHT 1.0f
// Small building
#define SMALL_BUILDING_POS_X 25.0f
#define SMALL_BUILDING_POS_Z -25.0f
#define SMALL_BUILDING_PILLAR_HEIGHT 18.0f
#define SMALL_BUILDING_WIDTH 15.0f
// Medium building
#define MEDIUM_BUILDING_POS_X -25.0f
#define MEDIUM_BUILDING_POS_Z 30.0f
#define MEDIUM_BUILDING_PILLAR_HEIGHT_1 23.0f
#define MEDIUM_BUILDING_PILLAR_HEIGHT_2 18.0f
#define MEDIUM_BUILDING_WIDTH_1 25.0f
#define MEDIUM_BUILDING_LENGTH_1 15.0f
#define MEDIUM_BUILDING_WIDTH_2 15.0f
#define MEDIUM_BUILDING_LENGTH_2 10.0f
// Big building
#define BIG_BUILDING_POS_X -25.0f
#define BIG_BUILDING_POS_Z -25.0f
#define BIG_BUILDING_PILLAR_HEIGHT_1 28.0f
#define BIG_BUILDING_PILLAR_HEIGHT_2 18.0f
#define BIG_BUILDING_WIDTH_1 20.0f
#define BIG_BUILDING_LENGTH_1 25.0f
#define BIG_BUILDING_WIDTH_2 20.0f
#define BIG_BUILDING_LENGTH_2 15.0f
// Ground
#define GROUND_TILE_LENGTH 25.0f
#define GROUND_TILE_HEIGHT 0.01f
// Crane
#define CRANE_BASE_PARTS_NUM 16
#define CRANE_BASE_PART_HEIGHT 2.5f
#define CRANE_TOP_FORWARD_PARTS_NUM 10
#define CRANE_TOP_BACKWARD_PARTS_NUM 4
#define CRANE_TOP_PART_LENGTH 5.0f
#define CRANE_POS_X 15.0f
#define CRANE_POS_Z 15.0f
#define CRANE_TOP_HEIGHT_PLACEMENT 37.5f
#define CRANE_INITIAL_ANGLE 120.0f
// Stand
#define STAND_HEIGHT 1.0f
#define STAND_WIDTH 2.0f
#define STAND_LENGTH 2.0f
// Crane cylinders
#define CRANE_CYLINDER_LENGTH_1 2.5f
#define CRANE_CYLINDER_LENGTH_2 3.5f
#define CRANE_CYLINDER_LENGTH_3 5.0f
#define CRANE_CYLINDER_LENGTH_4 3.54f
#define CRANE_CYLINDER_LENGTH_5 10.16f
#define CRANE_CYLINDER_RADIUS_1 0.1f
#define CRANE_CYLINDER_RADIUS_2 0.25f
#define CRANE_CYLINDER_RADIUS_3 0.15f
// Weights
#define TOP_WEIGHTS_HEIGHT 4.8f
#define TOP_WEIGHTS_LENGTH 1.0f
#define TOP_WEIGHTS_WIDTH 2.3f
#define BOTTOM_WEIGHTS_HEIGHT 0.5f
#define BOTTOM_WEIGHTS_LENGTH 5.0f
#define BOTTOM_WEIGHTS_WIDTH 1.25f
// Crane station
#define STATION_HEIGHT_1 4.0f
#define STATION_WIDTH 2.5f
#define STATION_LENGTH_1 2.0f
#define STATION_HEIGHT_2 3.0f
#define STATION_LENGTH_2 1.0f
#define STATION_LENGTH_3 1.4142f
// Hoist holder
#define HOIST_HOLDER_LENGTH 3.0f
#define HOIST_HOLDER_WIDTH 2.0f
#define HOIST_HOLDER_HEIGHT 0.5f
// Wheels
#define WHEELS_RADIUS 0.25f
#define WHEELS_WIDTH 0.25f
// Line
#define LINE_PART_WIDTH 0.09f
#define LINE_PART_HEIGHT 0.4f
// Hook
#define HOOK_WIDTH 0.3f
#define HOOK_HEIGHT 1.0f
#define HOOK_HOOK_WIDTH 0.1f
#define HOOK_HOOK_LENGTH 0.71f
#define HOOK_HOOK_WIDTH_2 0.09f
#define HOOK_HOOK_LENGTH_2 0.5f

/*
*	Textures IDs
*/
#define BRUSHED_METAL 0
#define OLD_YELLOW_METAL_4 1
#define CONCRETE 2
#define DIRT 3
#define OLD_YELLOW_METAL 4
#define CONCRETE_2 5
#define DIRTY_BLUE_METAL_2 6
#define DIRTY_GREEN_METAL 7
#define CONCRETE_3 8
#define CONCRETE_4 9
#define CONCRETE_5 10
#define GLASS 11
#define STEEL_ROPE 12	
#define BLACK_METAL 13
#define OLD_YELLOW_METAL_2 14
#define RUST 15

/*
*	Models IDs
*/
#define CUBE 0
#define CYLINDER 1

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

	float lineDistance = 0.0f;
	float hoistDistance = 0.0f;
	int lineParts = 0;

public:
	Scene() {

		this->addTextures();
		this->createModels();
		this->createScene();

		scene->translateWorld(glm::vec3(-CRANE_POS_X, 0.0f, -CRANE_POS_Z));

	}

	void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) {

		scene->draw(camera, shaderID);

	}

	void rotateCraneTop(float angle) {
		// 7 : CraneTop
		objectsToMove[7]->rotateWorld(angle, glm::vec3(0.0, 1.0, 0.0));
	}

	void moveCraneHoist(float distance) {

		this->hoistDistance += distance;
		if (this->hoistDistance >= 20.0f) {
			this->hoistDistance = 20.0f;
		}
		else if (this->hoistDistance <= -10.0f) {
			this->hoistDistance = -10.0f;
		}
		else {
			// 0 - 3 : wheels
			for (int i = 0; i < 4; ++i) {
				//objectsToMove[i]->rotateLocal(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				objectsToMove[i]->translateLocal(glm::vec3(distance * 4, 0.0f, 0.0f));
			}

			// 6 : Hoist
			objectsToMove[6]->objects[0]->translateLocal(glm::vec3(distance / 3, 0.0f, 0.0f)); // wozek
			objectsToMove[6]->objects[5]->translateLocal(glm::vec3(distance * 100 / 9, 0.0f, 0.0f)); //lina
			objectsToMove[5]->objects[0]->translateLocal(glm::vec3(distance * 10 / 3, 0.0f, 0.0f));//czesc hak
			objectsToMove[5]->objects[1]->translateLocal(glm::vec3(distance * 10, 0.0f, 0.0f));//czesc hak
			objectsToMove[5]->objects[2]->translateLocal(glm::vec3(distance * 100 / 9, 0.0f, 0.0f));//czesc hak
			objectsToMove[5]->objects[3]->translateLocal(glm::vec3(distance * 10, 0.0f, 0.0f));//czesc hak
			objectsToMove[5]->objects[4]->translateLocal(glm::vec3(distance * 100 / 9, 0.0f, 0.0f));//czesc hak
		}
	}

	void moveCraneHook(float distance) {
		this->lineDistance += distance;
		if (this->lineDistance >= 0.4f) {
			this->lineDistance = 0.0f;
			this->lineParts -= 1;
			if (this->lineParts < -50) {
				this->lineParts = -50;
			}
		}
		else if (this->lineDistance <= -0.4f) {
			this->lineDistance = 0.0f;
			this->lineParts += 1;
			if (this->lineParts > 25) {
				this->lineParts = 25;
			}
		}

		if (this->lineParts >= -49 and this->lineParts < 25) {
			// 5 : Hook
			objectsToMove[5]->translateWorld(glm::vec3(0.0f, distance, 0.0f));
			// 4 : Line
			for (int i = 0; i < 50 + this->lineParts; ++i) {
				objectsToMove[4]->objects[i]->translateWorld(glm::vec3(0.0f, distance, 0.0f));
			}
		}
	}

	void move() {
		// objectsToMove:
		// 0 - 3 : wheels
		// 4 : Line
		// 5 : Hook
		// 6 : Hoist
		// 7 : CraneTop

		//this->moveCraneHook(0.001f);

		//this->moveCraneHoist(0.01f);

		//this->rotateCraneTop(0.1f);
	}
private:
	void addTextures() {

		textures.push_back("./textures/brushedMetal.png");
		textures.push_back("./textures/oldYellowMetal4.png");
		textures.push_back("./textures/concrete.png");
		textures.push_back("./textures/dirt.png");
		textures.push_back("./textures/oldYellowMetal.png");
		textures.push_back("./textures/concrete2.png");
		textures.push_back("./textures/dirtyBlueMetal2.png");
		textures.push_back("./textures/dirtyGreenMetal.png");
		textures.push_back("./textures/concrete3.png");
		textures.push_back("./textures/concrete4.png");
		textures.push_back("./textures/concrete5.png");
		textures.push_back("./textures/glass.png");
		textures.push_back("./textures/steelRope.png");
		textures.push_back("./textures/blackMetal.png");
		textures.push_back("./textures/oldYellowMetal2.png");
		textures.push_back("./textures/rust.png");



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

	// Creating fence around crane
	
	void createFence() {
		std::shared_ptr<Collection> fence = std::make_shared<Collection>();

		std::shared_ptr<Collection> fencePart;

		for (int i = 0; i < FENCE_PARTS_IN_SQUARE_NUM; ++i) {
			fencePart = this->createFencePart();

			fencePart->translateWorld(glm::vec3(-FENCE_BAR_LENGTH_2 * FENCE_PARTS_IN_SQUARE_NUM / 2, 0.0f, -FENCE_BAR_LENGTH_2 * FENCE_PARTS_IN_SQUARE_NUM / 2 + i * FENCE_BAR_LENGTH_2));

			fence->addObject(fencePart);
		}
		for (int i = 0; i < FENCE_PARTS_IN_SQUARE_NUM; ++i) {
			fencePart = this->createFencePart();

			fencePart->translateWorld(glm::vec3(-FENCE_BAR_LENGTH_2 * FENCE_PARTS_IN_SQUARE_NUM / 2, 0.0f, -FENCE_BAR_LENGTH_2 * FENCE_PARTS_IN_SQUARE_NUM / 2 + i * FENCE_BAR_LENGTH_2));
			fencePart->rotateWorld(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

			fence->addObject(fencePart);
		}
		for (int i = 0; i < FENCE_PARTS_IN_SQUARE_NUM; ++i) {
			fencePart = this->createFencePart();

			fencePart->translateWorld(glm::vec3(-FENCE_BAR_LENGTH_2 * FENCE_PARTS_IN_SQUARE_NUM / 2, 0.0f, -FENCE_BAR_LENGTH_2 * FENCE_PARTS_IN_SQUARE_NUM / 2 + i * FENCE_BAR_LENGTH_2));
			fencePart->rotateWorld(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

			fence->addObject(fencePart);
		}
		for (int i = 0; i < FENCE_PARTS_IN_SQUARE_NUM; ++i) {
			fencePart = this->createFencePart();

			fencePart->translateWorld(glm::vec3(-FENCE_BAR_LENGTH_2 * FENCE_PARTS_IN_SQUARE_NUM / 2, 0.0f, -FENCE_BAR_LENGTH_2 * FENCE_PARTS_IN_SQUARE_NUM / 2 + i * FENCE_BAR_LENGTH_2));
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
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(FENCE_BAR_RADIUS, FENCE_BAR_LENGTH_1, FENCE_BAR_RADIUS));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		fencePart->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(FENCE_BAR_RADIUS, FENCE_BAR_LENGTH_2, FENCE_BAR_RADIUS));
		part->translateWorld(glm::vec3(0.0f, 5.0f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 5.0f, 0.0f));
		fencePart->addObject(part);

		// Net

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

		// Net
		//1
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH, NET_WIDTH));
		part->translateWorld(glm::vec3(0.0f, NET_LENGTH/2, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 9.0f));
		net->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH*2, NET_WIDTH));
		part->translateWorld(glm::vec3(0.0f, NET_LENGTH, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 8.0f));
		net->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH*3, NET_WIDTH));
		part->translateWorld(glm::vec3(0.0f, NET_LENGTH*3/2, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 7.0f));
		net->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH*4, NET_WIDTH));
		part->translateWorld(glm::vec3(0.0f, NET_LENGTH*2, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 6.0f));
		net->addObject(part);
		//5-10
		for (int i = 0; i < 6; ++i) {
			part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
			part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH*5, NET_WIDTH));
			part->translateWorld(glm::vec3(0.0f, NET_LENGTH*5/2, 0.0f));
			part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			part->translateWorld(glm::vec3(0.0f, 0.0f, 5.0 - i * 1.0f));
			net->addObject(part);
		}
		//11
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH, NET_WIDTH));
		part->translateWorld(glm::vec3(0.0f, NET_LENGTH/2, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 4.0f, 0.0f));
		net->addObject(part);
		//12
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH*2, NET_WIDTH));
		part->translateWorld(glm::vec3(0.0f, NET_LENGTH, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 3.0f, 0.0f));
		net->addObject(part);
		//13
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH*3, NET_WIDTH));
		part->translateWorld(glm::vec3(0.0f, NET_LENGTH*3/2, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 2.0f, 0.0f));
		net->addObject(part);
		//14
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(NET_WIDTH, NET_LENGTH*4, NET_WIDTH));
		part->translateWorld(glm::vec3(0.0f, NET_LENGTH*2, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 1.0f, 0.0f));
		net->addObject(part);


		return net;
	}

	// Creating buildings

	void createConstructionSite() {
		std::shared_ptr<Collection> constructionSite = std::make_shared<Collection>();

		std::shared_ptr<Collection> building;
		// Add 
		// Small building
		building = this->createSmallBuilding();

		building->translateWorld(glm::vec3(SMALL_BUILDING_POS_X, 0.0f, SMALL_BUILDING_POS_Z));

		constructionSite->addObject(building);

		// Medium building

		building = this->createMediumBuilding();

		building->translateWorld(glm::vec3(MEDIUM_BUILDING_POS_X, 0.0f, MEDIUM_BUILDING_POS_Z));

		constructionSite->addObject(building);
		// Big building

		building = this->createBigBuilding();

		building->translateWorld(glm::vec3(BIG_BUILDING_POS_X, 0.0f, BIG_BUILDING_POS_Z));

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
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(BIG_BUILDING_WIDTH_1, BUILDING_FLOOR_HEIGHT, BIG_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 5.5f, 0.0f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(BIG_BUILDING_WIDTH_1, BUILDING_FLOOR_HEIGHT, BIG_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 10.5f, 0.0f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(BIG_BUILDING_WIDTH_1, BUILDING_FLOOR_HEIGHT, BIG_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 15.5f, 0.0f));
		building->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(BIG_BUILDING_WIDTH_1, BUILDING_FLOOR_HEIGHT, BIG_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 20.5f, 0.0f));
		building->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(BIG_BUILDING_WIDTH_1, BUILDING_FLOOR_HEIGHT, BIG_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 25.5f, 0.0f));
		building->addObject(part);

		std::shared_ptr<Collection> pillar;

		// Pillars
		//1
		pillar = createBuildingPillar(BIG_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(9.0f, 0.0f, 11.0f));
		building->addObject(pillar);
		//2
		pillar = createBuildingPillar(BIG_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, 11.0f));
		building->addObject(pillar);
		//3
		pillar = createBuildingPillar(BIG_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(9.0f, 0.0f, -11.0f));
		building->addObject(pillar);
		//4
		pillar = createBuildingPillar(BIG_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, -11.0f));
		building->addObject(pillar);


		// Second floors
		//1
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(BIG_BUILDING_WIDTH_2, BUILDING_FLOOR_HEIGHT, BIG_BUILDING_LENGTH_2));
		part->translateWorld(glm::vec3(0.0f, 5.5f, 20.0f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(BIG_BUILDING_WIDTH_2, BUILDING_FLOOR_HEIGHT, BIG_BUILDING_LENGTH_2));
		part->translateWorld(glm::vec3(-0.0f, 10.5f, 20.0f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(BIG_BUILDING_WIDTH_2, BUILDING_FLOOR_HEIGHT, BIG_BUILDING_LENGTH_2));
		part->translateWorld(glm::vec3(-0.0f, 15.5f, 20.0f));
		building->addObject(part);

		// Second floors pillars
		//1
		pillar = createBuildingPillar(BIG_BUILDING_PILLAR_HEIGHT_2);
		pillar->translateWorld(glm::vec3(8.0f, 0.0f, 26.0f));
		building->addObject(pillar);
		//2
		pillar = createBuildingPillar(BIG_BUILDING_PILLAR_HEIGHT_2);
		pillar->translateWorld(glm::vec3(-8.0f, 0.0f, 26.0f));
		building->addObject(pillar);

		return building;
	}

	std::shared_ptr<Collection> createMediumBuilding() {
		std::shared_ptr<Collection> building = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_4];

		// Floors
		//1
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(MEDIUM_BUILDING_WIDTH_1, BUILDING_FLOOR_HEIGHT, MEDIUM_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 5.5f, 0.0f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(MEDIUM_BUILDING_WIDTH_1, BUILDING_FLOOR_HEIGHT, MEDIUM_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 10.5f, 0.0f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(MEDIUM_BUILDING_WIDTH_1, BUILDING_FLOOR_HEIGHT, MEDIUM_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 15.5f, 0.0f));
		building->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(MEDIUM_BUILDING_WIDTH_1, 1.0f, MEDIUM_BUILDING_LENGTH_1));
		part->translateWorld(glm::vec3(0.0f, 20.05f, 0.0f));
		building->addObject(part);

		std::shared_ptr<Collection> pillar;

		// Pillars
		//1
		pillar = createBuildingPillar(MEDIUM_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(9.0f, 0.0f, 6.0f));
		building->addObject(pillar);
		//2
		pillar = createBuildingPillar(MEDIUM_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, 6.0f));
		building->addObject(pillar);
		//3
		pillar = createBuildingPillar(MEDIUM_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(9.0f, 0.0f, -6.0f));
		building->addObject(pillar);
		//4
		pillar = createBuildingPillar(MEDIUM_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, -6.0f));
		building->addObject(pillar);
		//5
		pillar = createBuildingPillar(MEDIUM_BUILDING_PILLAR_HEIGHT_1);
		pillar->translateWorld(glm::vec3(0.0f, 0.0f, -6.0f));
		building->addObject(pillar);


		// Second floors
		//1
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(MEDIUM_BUILDING_WIDTH_2, BUILDING_FLOOR_HEIGHT, MEDIUM_BUILDING_LENGTH_2));
		part->translateWorld(glm::vec3(-5.0f, 5.5f, -12.5f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(MEDIUM_BUILDING_WIDTH_2, BUILDING_FLOOR_HEIGHT, MEDIUM_BUILDING_LENGTH_2));
		part->translateWorld(glm::vec3(-5.0f, 10.5f, -12.5f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(MEDIUM_BUILDING_WIDTH_2, BUILDING_FLOOR_HEIGHT, MEDIUM_BUILDING_LENGTH_2));
		part->translateWorld(glm::vec3(-5.0f, 15.5f, -12.5f));
		building->addObject(part);

		// Second floors pillars
		//1
		pillar = createBuildingPillar(MEDIUM_BUILDING_PILLAR_HEIGHT_2);
		pillar->translateWorld(glm::vec3(0.0f, 0.0f, -14.0f));
		building->addObject(pillar);
		//2
		pillar = createBuildingPillar(MEDIUM_BUILDING_PILLAR_HEIGHT_2);
		pillar->translateWorld(glm::vec3(-9.0f, 0.0f, -14.0f));
		building->addObject(pillar);

		return building;
	}

	std::shared_ptr<Collection> createSmallBuilding() {
		std::shared_ptr<Collection> building = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_4];

		// Floors
		//1
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(SMALL_BUILDING_WIDTH, BUILDING_FLOOR_HEIGHT, SMALL_BUILDING_WIDTH));
		part->translateWorld(glm::vec3(0.0f, 5.5f, 0.0f));
		building->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(SMALL_BUILDING_WIDTH, BUILDING_FLOOR_HEIGHT, SMALL_BUILDING_WIDTH));
		part->translateWorld(glm::vec3(0.0f, 10.5f, 0.0f));
		building->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(SMALL_BUILDING_WIDTH, BUILDING_FLOOR_HEIGHT, SMALL_BUILDING_WIDTH));
		part->translateWorld(glm::vec3(0.0f, 15.5f, 0.0f));
		building->addObject(part);

		std::shared_ptr<Collection> pillar;

		// Pillars
		//1
		pillar = createBuildingPillar(SMALL_BUILDING_PILLAR_HEIGHT);
		pillar->translateWorld(glm::vec3(6.0f, 0.0f, 6.0f));
		building->addObject(pillar);
		//2
		pillar = createBuildingPillar(SMALL_BUILDING_PILLAR_HEIGHT);
		pillar->translateWorld(glm::vec3(-6.0f, 0.0f, 6.0f));
		building->addObject(pillar);
		//3
		pillar = createBuildingPillar(SMALL_BUILDING_PILLAR_HEIGHT);
		pillar->translateWorld(glm::vec3(6.0f, 0.0f, -6.0f));
		building->addObject(pillar);
		//4
		pillar = createBuildingPillar(SMALL_BUILDING_PILLAR_HEIGHT);
		pillar->translateWorld(glm::vec3(-6.0f, 0.0f, -6.0f));
		building->addObject(pillar);

		return building;
	}

	std::shared_ptr<Collection> createBuildingPillar( float height ) {
		std::shared_ptr<Collection> pillar = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[CONCRETE_2];
		std::string partTexture2 = textures[RUST];

		//1
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(PILLAR_WIDTH, height, PILLAR_WIDTH));
		part->translateWorld(glm::vec3(0.0f, height/2 , 0.0f));
		pillar->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture2)));
		part->scaleLocal(glm::vec3(ROD_WIDTH, ROD_HEIGHT, ROD_WIDTH));
		part->translateWorld(glm::vec3(-0.4f, height + ROD_HEIGHT/2, -0.4f));
		pillar->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture2)));
		part->scaleLocal(glm::vec3(ROD_WIDTH, ROD_HEIGHT, ROD_WIDTH));
		part->translateWorld(glm::vec3(0.4f, height + ROD_HEIGHT/2, -0.4f));
		pillar->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture2)));
		part->scaleLocal(glm::vec3(ROD_WIDTH, ROD_HEIGHT, ROD_WIDTH));
		part->translateWorld(glm::vec3(-0.4f, height + ROD_HEIGHT/2, 0.4f));
		pillar->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture2)));
		part->scaleLocal(glm::vec3(ROD_WIDTH, ROD_HEIGHT, ROD_WIDTH));
		part->translateWorld(glm::vec3(0.4f, height + ROD_HEIGHT/2, 0.4f));
		pillar->addObject(part);

		return pillar;
	}
	
	// Creating groung

	void createGround() {
		std::shared_ptr<Collection> tiles = std::make_shared<Collection>();

		std::string tileTexture = textures[DIRT];
		// 0 0
		tiles->addObject(createTile(-GROUND_TILE_LENGTH, -GROUND_TILE_LENGTH, tileTexture));
		// 1 0
		tiles->addObject(createTile(0.0f, -GROUND_TILE_LENGTH, tileTexture));
		// 2 0
		tiles->addObject(createTile(GROUND_TILE_LENGTH, -GROUND_TILE_LENGTH, tileTexture));
		// 0 1
		tiles->addObject(createTile(-GROUND_TILE_LENGTH, 0.0f, tileTexture));
		// 1 1
		tiles->addObject(createTile(0.0f, 0.0f, tileTexture));
		// 2 1
		tiles->addObject(createTile(GROUND_TILE_LENGTH, 0.0f, tileTexture));
		// 0 2
		tiles->addObject(createTile(-GROUND_TILE_LENGTH, GROUND_TILE_LENGTH, tileTexture));
		// 1 2
		tiles->addObject(createTile(0.0f, GROUND_TILE_LENGTH, tileTexture));
		// 2 2
		tiles->addObject(createTile(GROUND_TILE_LENGTH, GROUND_TILE_LENGTH, tileTexture));

		// Add to scene
		scene->addObject(tiles);
	}

	std::shared_ptr<Object> createTile(float x, float z, std::string texture) {
		std::shared_ptr<Object> tile = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(texture)));
		tile->scaleLocal(glm::vec3(GROUND_TILE_LENGTH, GROUND_TILE_HEIGHT, GROUND_TILE_LENGTH));
		tile->translateWorld(glm::vec3(x, -GROUND_TILE_HEIGHT/2, z));
		return tile;
	}

	// CREATING CRANE :D

	void createCrane() {
		std::shared_ptr<Collection> crane = std::make_shared<Collection>();

		crane->addObject(this->createCraneBase());

		std::shared_ptr<Collection> craneTop = this->createCraneTop();

		craneTop->translateWorld(glm::vec3(0.0f, CRANE_TOP_HEIGHT_PLACEMENT, 0.0f));

		objectsToMove.push_back(craneTop);

		crane->addObject(craneTop);

		crane->rotateWorld(CRANE_INITIAL_ANGLE, glm::vec3(0.0f, 1.0f, 0.0f));

		crane->translateWorld(glm::vec3(CRANE_POS_X, 0.0f, CRANE_POS_Z));

		scene->addObject(crane);
	}

	std::shared_ptr<Collection> createCraneBase() {
		std::shared_ptr<Collection> base = std::make_shared<Collection>();

		base->addObject(this->createCraneBaseBottom());
		for (int i = 0; i < CRANE_BASE_PARTS_NUM; ++i) {
			std::shared_ptr<Collection> part = createCraneBasePart();
			part->translateWorld(glm::vec3(0.0f, i*CRANE_BASE_PART_HEIGHT, 0.0f));
			base->addObject(part);
		}

		std::shared_ptr<Collection> top = createCraneBaseTop();
		top->translateWorld(glm::vec3(0.0f, CRANE_BASE_PARTS_NUM*CRANE_BASE_PART_HEIGHT - 0.1f, 0.0f));

		base->addObject(top);
		

		return base;
	}

	std::shared_ptr<Collection> createCraneBaseTop() {
		std::shared_ptr<Collection> topParts = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[OLD_YELLOW_METAL_4];

		//1
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_5, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_5/2, 0.0f));
		part->rotateWorld(9.97f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(-1.25f, 0.0f, -1.25f));
		topParts->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_5, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_5/2, 0.0f));
		part->rotateWorld(9.97f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->rotateWorld(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(1.25f, 0.0f, -1.25f));
		topParts->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_5, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_5/2, 0.0f));
		part->rotateWorld(-9.97f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->rotateWorld(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(-1.25f, 0.0f, 1.25f));
		topParts->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_5, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_5/2, 0.0f));
		part->rotateWorld(-9.97f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(1.25f, 0.0f, 1.25f));
		topParts->addObject(part);

		return topParts;
	}

	std::shared_ptr<Collection> createCraneBasePart() {
		std::shared_ptr<Collection> parts = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[OLD_YELLOW_METAL_4];

		//1
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(-1.25, CRANE_CYLINDER_LENGTH_1/2, -1.25f));
		parts->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(1.25, CRANE_CYLINDER_LENGTH_1/2, -1.25f));
		parts->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(-1.25, CRANE_CYLINDER_LENGTH_1/2, 1.25f));
		parts->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(1.25, CRANE_CYLINDER_LENGTH_1/2, 1.25f));
		parts->addObject(part);
		//5
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_3, CRANE_CYLINDER_LENGTH_4, CRANE_CYLINDER_RADIUS_3));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(1.25, 1.25f, 0.0f));
		parts->addObject(part);
		//6
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_3, CRANE_CYLINDER_LENGTH_4, CRANE_CYLINDER_RADIUS_3));
		part->rotateWorld(-45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(1.25f, 1.25f, 0.0f));
		parts->addObject(part);
		//7
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_3, CRANE_CYLINDER_LENGTH_4, CRANE_CYLINDER_RADIUS_3));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(-1.25f, 1.25f, 0.0f));
		parts->addObject(part);
		//8
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_3, CRANE_CYLINDER_LENGTH_4, CRANE_CYLINDER_RADIUS_3));
		part->rotateWorld(-45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(-1.25f, 1.25f, 0.0f));
		parts->addObject(part);
		//9
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_3, CRANE_CYLINDER_LENGTH_4, CRANE_CYLINDER_RADIUS_3));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 1.25f));
		parts->addObject(part);
		//10
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_3, CRANE_CYLINDER_LENGTH_4, CRANE_CYLINDER_RADIUS_3));
		part->rotateWorld(-45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, 1.25f));
		parts->addObject(part);
		//11
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_3, CRANE_CYLINDER_LENGTH_4, CRANE_CYLINDER_RADIUS_3));
		part->rotateWorld(-45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 1.25f, -1.25f));
		parts->addObject(part);
		//12
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_3, CRANE_CYLINDER_LENGTH_4, CRANE_CYLINDER_RADIUS_3));
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
		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(BOTTOM_WEIGHTS_LENGTH, BOTTOM_WEIGHTS_HEIGHT, BOTTOM_WEIGHTS_WIDTH));
		cube->translateWorld(glm::vec3(0.0f, 1.25f, -1.875f));
		weights->addObject(cube);
		//2
		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(BOTTOM_WEIGHTS_LENGTH, BOTTOM_WEIGHTS_HEIGHT, BOTTOM_WEIGHTS_WIDTH));
		cube->translateWorld(glm::vec3(0.0f, 1.25f, 1.875f));
		weights->addObject(cube);
		//3
		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(BOTTOM_WEIGHTS_WIDTH, BOTTOM_WEIGHTS_HEIGHT, BOTTOM_WEIGHTS_LENGTH));
		cube->translateWorld(glm::vec3(-1.875f, 1.75f, 0.0f));
		weights->addObject(cube);
		//4
		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(BOTTOM_WEIGHTS_WIDTH, BOTTOM_WEIGHTS_HEIGHT, BOTTOM_WEIGHTS_LENGTH));
		cube->translateWorld(glm::vec3(1.875f, 1.75f, 0.0f));
		weights->addObject(cube);
		//5
		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(BOTTOM_WEIGHTS_LENGTH, BOTTOM_WEIGHTS_HEIGHT, BOTTOM_WEIGHTS_WIDTH));
		cube->translateWorld(glm::vec3(0.0f, 2.25f, -1.875f));
		weights->addObject(cube);
		//6
		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(weightsTexture)));
		cube->scaleLocal(glm::vec3(BOTTOM_WEIGHTS_LENGTH, BOTTOM_WEIGHTS_HEIGHT, BOTTOM_WEIGHTS_WIDTH));
		cube->translateWorld(glm::vec3(0.0f, 2.25f, 1.875f));
		weights->addObject(cube);


		return weights;
	}

	std::shared_ptr<Collection> createCraneBaseBottomStand() {
		std::shared_ptr<Collection> stand = std::make_shared<Collection>();

		std::string standTexture = textures[OLD_YELLOW_METAL_4];

		std::shared_ptr<Object> cube;

		// Add base holders
		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(standTexture)));
		cube->scaleLocal(glm::vec3(STAND_WIDTH, STAND_HEIGHT, STAND_LENGTH));
		cube->translateWorld(glm::vec3(-1.5f, STAND_HEIGHT/2, -1.5f));
		stand->addObject(cube);

		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(standTexture)));
		cube->scaleLocal(glm::vec3(STAND_WIDTH, STAND_HEIGHT, STAND_LENGTH));
		cube->translateWorld(glm::vec3(1.5f, STAND_HEIGHT/2, -1.5f));
		stand->addObject(cube);

		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(standTexture)));
		cube->scaleLocal(glm::vec3(STAND_WIDTH, STAND_HEIGHT, STAND_LENGTH));
		cube->translateWorld(glm::vec3(-1.5f, STAND_HEIGHT/2, 1.5f));
		stand->addObject(cube);

		cube = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(standTexture)));
		cube->scaleWorld(glm::vec3(STAND_WIDTH, STAND_HEIGHT, STAND_LENGTH));
		cube->translateWorld(glm::vec3(1.5f, STAND_HEIGHT/2, 1.5f));
		stand->addObject(cube);

		return stand;
	}
	
	std::shared_ptr<Collection> createCraneTop() {
		std::shared_ptr<Collection> top = std::make_shared<Collection>();

		std::shared_ptr<Collection> part;

		for (int i = 1; i < CRANE_TOP_FORWARD_PARTS_NUM; ++i) {
			part = createCraneTopPart();
			part->translateWorld(glm::vec3(i*CRANE_TOP_PART_LENGTH, 0.0f, 0.0f));
			top->addObject(part);
		}
		for (int i = 0; i < CRANE_TOP_BACKWARD_PARTS_NUM; ++i) {
			part = createCraneTopPart();
			part->translateWorld(glm::vec3(-i* CRANE_TOP_PART_LENGTH, 0.0f, 0.0f));
			top->addObject(part);
		}

		part = createCraneTopConeEnd();
		part->translateWorld(glm::vec3(9* CRANE_TOP_PART_LENGTH, 0.0f, 0.0f));
		top->addObject(part);

		part = createCraneTopTriangleEnd();
		part->translateWorld(glm::vec3(-4* CRANE_TOP_PART_LENGTH +0.125f, 0.0f, 0.0f));
		top->addObject(part);

		part = createCraneTopWeights();
		part->translateWorld(glm::vec3(-4 * CRANE_TOP_PART_LENGTH + 1.0f, 0.0f, 0.0f));
		top->addObject(part);

		part = createCraneStation();
		part->translateWorld(glm::vec3(4.0f, -3.5f, 2.0f));
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

		std::string partTexture = textures[OLD_YELLOW_METAL_4];

		std::shared_ptr<Collection> wall = std::make_shared<Collection>();

		//1.1
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_3, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_3/2, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		wall->addObject(part);
		//1.2
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_3, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_3/2, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		wall->addObject(part);
		//1.3
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, 4.72f, CRANE_CYLINDER_RADIUS_1));
		part->translateWorld(glm::vec3(0.0f, 2.36f, 0.0f));
		part->rotateWorld(58.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		wall->addObject(part);
		//1.4
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, 2.69f, CRANE_CYLINDER_RADIUS_1));
		part->translateWorld(glm::vec3(0.0f, 1.345f, 0.0f));
		part->rotateWorld(-32.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(-5.0f, 0.0f, 0.0f));
		wall->addObject(part);

		wall->rotateWorld(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		wall->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));

		top->addObject(wall);

		wall = std::make_shared<Collection>();
		//2.1
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_3, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_3/2, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		wall->addObject(part);
		//2.2
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_3, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_3/2, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(0.0f, 2.5f, 0.0f));
		wall->addObject(part);
		//2.3
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, 4.72f, CRANE_CYLINDER_RADIUS_1));
		part->translateWorld(glm::vec3(0.0f, 2.36f, 0.0f));
		part->rotateWorld(58.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		wall->addObject(part);
		//2.4
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, 2.69f, CRANE_CYLINDER_RADIUS_1));
		part->translateWorld(glm::vec3(0.0f, 1.345f, 0.0f));
		part->rotateWorld(-32.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(-5.0f, 0.0f, 0.0f));
		wall->addObject(part);

		wall->rotateWorld(-30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		wall->translateWorld(glm::vec3(0.0f, 0.0f, 1.25f));

		top->addObject(wall);

		//3.1
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, 5.59f, CRANE_CYLINDER_RADIUS_1));
		part->translateWorld(glm::vec3(0.0f, 2.8f, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->rotateWorld(26.56f, glm::vec3(0.0f, 1.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));
		top->addObject(part);
		//3.2
		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, 5.59f, CRANE_CYLINDER_RADIUS_1));
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

		std::string partTexture = textures[OLD_YELLOW_METAL_4];

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->rotateWorld(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_1/2, 0.0f));
		part->rotateWorld(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_1/2, 0.0f));
		part->rotateWorld(-30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 1.25f));
		top->addObject(part);

		return top;
	}

	std::shared_ptr<Collection> createCraneTopConeEnd() {
		std::shared_ptr<Collection> top = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[OLD_YELLOW_METAL_4];

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_1));
		part->rotateWorld(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_1));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_1/2, 0.0f));
		part->rotateWorld(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_1, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_1));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_1/2, 0.0f));
		part->rotateWorld(-30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, 1.25f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_2, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_2/2 - 0.22f, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		part->translateWorld(glm::vec3(2.165f, 0.0f, 0.0f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_1/2, 0.0f));
		part->rotateWorld(30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, 0.0f, -1.25f));
		part->rotateWorld(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		top->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(CRANE_CYLINDER_RADIUS_2, CRANE_CYLINDER_LENGTH_1, CRANE_CYLINDER_RADIUS_2));
		part->translateWorld(glm::vec3(0.0f, CRANE_CYLINDER_LENGTH_1/2, 0.0f));
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

		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(TOP_WEIGHTS_LENGTH, TOP_WEIGHTS_HEIGHT, TOP_WEIGHTS_WIDTH));
		part->translateWorld(glm::vec3(0.0f, 1.08f, 0.0f));
		weights->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(TOP_WEIGHTS_LENGTH, TOP_WEIGHTS_HEIGHT, TOP_WEIGHTS_WIDTH));
		part->translateWorld(glm::vec3(1.1f, 1.08f, 0.0f));
		weights->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(TOP_WEIGHTS_LENGTH, TOP_WEIGHTS_HEIGHT, TOP_WEIGHTS_WIDTH));
		part->translateWorld(glm::vec3(2.2f, 1.08f, 0.0f));
		weights->addObject(part);

		return weights;
	}

	std::shared_ptr<Collection> createCraneStation() {
		std::shared_ptr<Collection> station = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[OLD_YELLOW_METAL_2];
		std::string partTexture2 = textures[GLASS];

		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(STATION_LENGTH_1, STATION_HEIGHT_1, STATION_WIDTH));
		part->translateWorld(glm::vec3(0.0f, 2.0f, 0.0f));
		station->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture2)));
		part->scaleLocal(glm::vec3(STATION_LENGTH_2, STATION_HEIGHT_2, STATION_WIDTH));
		part->translateWorld(glm::vec3(1.5f, 1.5f, 0.0f));
		station->addObject(part);

		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(STATION_LENGTH_3, STATION_LENGTH_3, STATION_WIDTH-0.01f));
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
		part->translateWorld(glm::vec3(0.0f, 0.6f, 0.0f));
		hoist->addObject(part);

		part = createCraneTopHoistHook();
		part->translateWorld(glm::vec3(0.0f, -19.4f, 0.0f));
		hoist->addObject(part);

		objectsToMove.push_back(hoist);
		return hoist;
	}

	std::shared_ptr<Collection> createCraneTopHoistHolder() {
		std::shared_ptr<Collection> hoistHolder = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[DIRTY_GREEN_METAL];

		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(HOIST_HOLDER_LENGTH, HOIST_HOLDER_HEIGHT, HOIST_HOLDER_WIDTH));
		part->translateWorld(glm::vec3(0.0f, 0.5f, 0.0f));
		hoistHolder->addObject(part);

		return hoistHolder;
	}

	std::shared_ptr<Collection> createCraneTopHoistHolderWheel() {
		std::shared_ptr<Collection> wheel = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[BLACK_METAL];

		part = std::shared_ptr<Object>(new Object(models[CYLINDER], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(WHEELS_RADIUS, WHEELS_WIDTH, WHEELS_RADIUS));
		part->translateWorld(glm::vec3(0.0f, WHEELS_WIDTH/2, 0.0f));
		part->rotateWorld(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		wheel->addObject(part);

		return wheel;
	}

	std::shared_ptr<Collection> createCraneTopHoistLine() {
		std::shared_ptr<Collection> line = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[STEEL_ROPE];

		for (int i = 0; i < 50; ++i) {
			part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
			part->scaleLocal(glm::vec3(LINE_PART_WIDTH, LINE_PART_HEIGHT, LINE_PART_WIDTH));
			part->translateWorld(glm::vec3(0.0f, -20.0f+i*0.4f, 0.0f));
			line->addObject(part);
		}
		for (int i = 0; i < 25; ++i) {
			part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
			part->scaleLocal(glm::vec3(LINE_PART_WIDTH, LINE_PART_HEIGHT, LINE_PART_WIDTH));
			part->translateWorld(glm::vec3(0.0f, -0.4f, 0.0f));
			line->addObject(part);
		}

		objectsToMove.push_back(line);

		return line;
	}

	std::shared_ptr<Collection> createCraneTopHoistHook() {
		std::shared_ptr<Collection> hook = std::make_shared<Collection>();

		std::shared_ptr<Object> part;

		std::string partTexture = textures[OLD_YELLOW_METAL_2];

		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(HOOK_WIDTH, HOOK_HEIGHT, HOOK_WIDTH));
		part->translateWorld(glm::vec3(0.0f, -HOOK_HEIGHT/2, 0.0f));
		hook->addObject(part);

		//1
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(HOOK_HOOK_WIDTH, HOOK_HOOK_LENGTH, HOOK_HOOK_WIDTH));
		part->translateWorld(glm::vec3(0.0f, -HOOK_HOOK_LENGTH/2, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, -0.8f, 0.0f));
		hook->addObject(part);
		//2
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(HOOK_HOOK_WIDTH_2, HOOK_HOOK_LENGTH_2, HOOK_HOOK_WIDTH_2));
		part->translateWorld(glm::vec3(0.0f, -1.52f, -0.49f));
		hook->addObject(part);
		//3
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(HOOK_HOOK_WIDTH, HOOK_HOOK_LENGTH, HOOK_HOOK_WIDTH));
		part->translateWorld(glm::vec3(0.0f, -HOOK_HOOK_LENGTH/2, 0.0f));
		part->rotateWorld(-45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, -1.74f, -0.505f));
		hook->addObject(part);
		//4
		part = std::shared_ptr<Object>(new Object(models[CUBE], texturesHandler.useTexture(partTexture)));
		part->scaleLocal(glm::vec3(HOOK_HOOK_WIDTH_2, HOOK_HOOK_LENGTH, HOOK_HOOK_WIDTH_2));
		part->translateWorld(glm::vec3(0.0f, -HOOK_HOOK_LENGTH/2, 0.0f));
		part->rotateWorld(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		part->translateWorld(glm::vec3(0.0f, -1.74f, 0.49f));
		hook->addObject(part);

		objectsToMove.push_back(hook);

		return hook;
	}

};
#endif // !SCENE_H