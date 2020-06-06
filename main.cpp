/*
 *  Created by michal-swiatek on 16.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#include "Configure.h"

#include "Core.h"

#include <memory>
#include <iostream>
#include <fstream>

#include "Shader.h"
#include "Camera.h"

#include "Cylinder.h"
#include "Cuboid.h"
#include "include/TexturesHandler.h"
#include "Object.h"
#include "include/Collection.h"
#include "include/Compound.h"
#include<iostream>

class DisplayCylinder : public Core
{
	using uint = unsigned int;

private:
	std::unique_ptr<Shader> shader;
	std::shared_ptr<Cylinder> cylinder;
	std::shared_ptr<Cuboid> cuboid;
	std::unique_ptr<Object> object;
	std::unique_ptr<Object> object2;
	std::unique_ptr<Object> object3;
	std::unique_ptr<Object> object4;
	std::unique_ptr<Object> object5;
	std::unique_ptr<Collection> duzaWskazowka;
	std::unique_ptr<Collection> malaWskazowka;
	std::unique_ptr<Collection> zegar;
	std::unique_ptr<Collection> podloga;

	TexturesHandler textH;

	uint VBO, VAO, EBO;

public:
	DisplayCylinder() : Core("Display cylinder"), VBO(0), VAO(0), EBO(0)
	{
		cylinder = std::make_shared<Cylinder>(1.0f, 1.0f, 1.0f, 8, 1);
		cuboid = std::make_shared<Cuboid>();
		shader = std::make_unique<Shader>("../shaders/texture.fs.glsl", "../shaders/texture.vs.glsl");
	}

	void init() override
	{
		std::string texture = "../textures/grass2.png";
		std::string texture2 = "../textures/awesomeface.png";

		textH.addTexture(texture);
		textH.addTexture(texture2);

		duzaWskazowka = std::unique_ptr<Collection>(new Collection());
		malaWskazowka = std::unique_ptr<Collection>(new Collection());
		podloga = std::unique_ptr<Collection>(new Collection());
		zegar = std::unique_ptr<Collection>(new Collection());

		object = std::unique_ptr<Object>(new Object(cylinder ,textH.useTexture(texture2)));
		object2 = std::unique_ptr<Object>(new Object(cuboid,textH.useTexture(texture2)));

		object3 = std::unique_ptr<Object>(new Object(cylinder, textH.useTexture(texture)));
		object4 = std::unique_ptr<Object>(new Object(cuboid, textH.useTexture(texture)));

		object5 = std::unique_ptr<Object>(new Object(cylinder, textH.useTexture(texture2)));

//		object->translateTo(glm::vec3(0.0f, 5.0f, 0.0f));
//		object2->translateTo(glm::vec3(0.0f, 2.0f, 0.0f));
//		object3->translateBySpecial(glm::vec3(0.0f, 3.0f, 0.0f));
//		object3->rotateBySpecial(glm::vec3(0.0f, 3.0f, 0.0f));
//		object3->scaleTo(glm::vec3(1.0f, 5.0f, 1.0f));
//		object->updateModel();
//		object2->updateModel();
//		object3->updateModel();
//		object4->updateModel();





		duzaWskazowka->addObject(move(object));
		duzaWskazowka->addObject(move(object2));

		duzaWskazowka->objects[0]->scaleBy(glm::vec3(0.3f, 8.0f, 0.3f));
		duzaWskazowka->objects[0]->translateBy(glm::vec3(0.0f, 4.0f, 0.0f));
		duzaWskazowka->objects[1]->translateBy(glm::vec3(0.0f, 8.0f, 0.0f));

		malaWskazowka->addObject(move(object3));
		malaWskazowka->addObject(move(object4));

		malaWskazowka->objects[0]->scaleBy(glm::vec3(0.3f, 4.0f, 0.3f));
		malaWskazowka->objects[0]->translateBy(glm::vec3(0.0f, 2.0f, 0.0f));
		malaWskazowka->objects[1]->translateBy(glm::vec3(0.0f, 4.0f, 0.0f));

		zegar->addObject(move(duzaWskazowka));
		zegar->addObject(move(malaWskazowka));

		zegar->updateModel();


		podloga->addObject(move(object5));
		podloga->objects[0]->scaleBy(glm::vec3(20.5f, 4.0f, 20.5f));
	//	collection->rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));


		mainCamera->getSettings().movementSpeed /= 2;

		shader->use();

		glViewport(0, 0, mainWindow->getWindowSettings().width, mainWindow->getWindowSettings().height);
		
	}
	void draw() override
	{
		zegar->objects[0]->rotateBySpecial2((float)glfwGetTime() * 0.1, glm::vec3(0.0, 0.0, 1.0));
		zegar->objects[1]->rotateBySpecial2((float)glfwGetTime() * 0.01, glm::vec3(0.0, 0.0, 1.0));

		zegar->translateBySpecial2(glm::vec3(0.0f, 3.0f, 0.0f));
;

		zegar->draw(mainCamera, shader->getProgramID());

		zegar->translateBySpecial2(glm::vec3(0.0f, -3.0f, 0.0f));


		podloga->draw(mainCamera, shader->getProgramID());


	}
};

int main() {
    try {
        initOpenGL();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
        return -1;
    }

	//Core app("Dzwig kratownicowy", int(PROJECT_VERSION_MAJOR), int(PROJECT_VERSION_MINOR), int(PROJECT_VERSION_PATCH));
	DisplayCylinder app;
    try {
        app.initApp();  //  Initialize subsystems and resources
    }
    catch (std::exception& e) {
        std::cout << e.what();
        return -2;
    }

    app.run();

    return 0;
}

