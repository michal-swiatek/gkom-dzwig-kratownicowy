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
	std::unique_ptr<Collection> goraDzwigu;
	std::unique_ptr<Collection> lina;
	std::unique_ptr<Collection> dzwig;


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

		dzwig = std::unique_ptr<Collection>(new Collection());

		object = std::unique_ptr<Object>(new Object(cuboid, textH.useTexture(texture2)));
		object2 = std::unique_ptr<Object>(new Object(cuboid, textH.useTexture(texture2)));

		object3 = std::unique_ptr<Object>(new Object(cuboid, textH.useTexture(texture)));
		object4 = std::unique_ptr<Object>(new Object(cylinder, textH.useTexture(texture)));

		object5 = std::unique_ptr<Object>(new Object(cylinder, textH.useTexture(texture2)));

		//		object->translateTo(glm::vec3(0.0f, 5.0f, 0.0f));
		//		object2->translateTo(glm::vec3(0.0f, 2.0f, 0.0f));
		//		object3->translateLocal(glm::vec3(0.0f, 3.0f, 0.0f));
		//		object3->rotateLocal(glm::vec3(0.0f, 3.0f, 0.0f));
		//		object3->scaleTo(glm::vec3(1.0f, 5.0f, 1.0f));
		//		object->updateModel();
		//		object2->updateModel();
		//		object3->updateModel();
		//		object4->updateModel();





		dzwig->addObject(move(object));
		dzwig->addObject(move(object2));

		dzwig->objects[0]->scaleWorld(glm::vec3(2.0f, 2.0f, 15.0f));
		dzwig->objects[0]->translateWorld(glm::vec3(0.0f, 0.0f, 4.0f));
		dzwig->objects[1]->scaleWorld(glm::vec3(0.0f, 0.0f, -4.0f));
		dzwig->objects[1]->translateWorld(glm::vec3(0.0f, 0.0f, -4.0f));

		dzwig->addObject(move(object3));
		dzwig->objects[2]->scaleWorld(glm::vec3(4.0f, 4.0f, 4.0f));
		dzwig->objects[2]->translateWorld(glm::vec3(0.0f, 0.0f, -4.0f));
		dzwig->addObject(move(object4));

		dzwig->objects[3]->scaleWorld(glm::vec3(0.3f, 0.3f, 0.3f));
		dzwig->objects[3]->translateWorld(glm::vec3(0.0f, 0.0f, 14.0f));







		mainCamera->getSettings().movementSpeed /= 2;

		shader->use();

		glViewport(0, 0, mainWindow->getWindowSettings().width, mainWindow->getWindowSettings().height);

	}
	void draw() override
	{
		dzwig->rotateWorld((float)glfwGetTime() * 0.1, glm::vec3(0.0, 1.0, 0.0));
		dzwig->objects[3]->scaleWorld(glm::vec3(1.0, 1.01, 1.0));

		dzwig->translateWorld(glm::vec3(0.0f, 3.0f, 0.0f));

		dzwig->draw(mainCamera, shader->getProgramID());

		dzwig->translateWorld(glm::vec3(0.0f, -3.0f, 0.0f));





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

