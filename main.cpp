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
	std::unique_ptr<Collection> collection;
	std::unique_ptr<Collection> collection2;
	std::unique_ptr<Collection> wszystko;

	TexturesHandler textH;

	uint VBO, VAO, EBO;

public:
	DisplayCylinder() : Core("Display cylinder"), VBO(0), VAO(0), EBO(0)
	{
		cylinder = std::make_shared<Cylinder>(1.0f, 1.0f, 1.0f, 3, 1);
		cuboid = std::make_shared<Cuboid>();
		shader = std::make_unique<Shader>("../shaders/texture.fs.glsl", "../shaders/texture.vs.glsl");
	}

	void init() override
	{
		
		std::string texture = "../textures/grass2.png";
		std::string texture2 = "../textures/awesomeface.png";

		textH.addTexture(texture);
		textH.addTexture(texture2);

		collection = std::unique_ptr<Collection>(new Collection());
		collection2 = std::unique_ptr<Collection>(new Collection());
		wszystko = std::unique_ptr<Collection>(new Collection());

		object = std::unique_ptr<Object>(new Object(cylinder ,textH.useTexture(texture)));
		object2 = std::unique_ptr<Object>(new Object(cuboid,textH.useTexture(texture2)));

	//	object2->translate(glm::vec3(0.0f, 5.0f, 0.0f));
		object2->translateTo(glm::vec3(0.0f, 5.0f, 0.0f));
	//	object2->rotate(20.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		object3 = std::unique_ptr<Object>(new Object(cuboid, textH.useTexture(texture)));
		
		object3->translateTo(glm::vec3(0.0f, 2.0f, 0.0f));
	//	object3->rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		object4 = std::unique_ptr<Object>(new Object(cuboid, textH.useTexture(texture2)));

		object4->translateTo(glm::vec3(0.0f, -3.0f, 1.0f));
		object4->scaleTo(glm::vec3(2.0f, 5.0f, 2.0f));


		object->updateModel();
		object2->updateModel();
		object3->updateModel();
		object4->updateModel();
		collection2->addObject(move(object3));
		collection2->addObject(move(object4));

		collection->addObject(move(object));
		collection->addObject(move(object2));

		wszystko->addObject(move(collection));
		wszystko->addObject(move(collection2));


	//	collection->rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));


		mainCamera->getSettings().movementSpeed /= 2;

		shader->use();

		glViewport(0, 0, mainWindow->getWindowSettings().width, mainWindow->getWindowSettings().height);
		
	}
	void draw() override
	{
		//shader->setMatrix4f("mvp", mainCamera->getViewProjectionMatrix());

		//auto width = mainWindow->getWindowSettings().width;
		//auto height = mainWindow->getWindowSettings().height;

		//glViewport(0, 0, width / 2, height);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		////glDrawElements(GL_TRIANGLES, cylinder->getIndices().size(), GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, cuboid->getIndices().size(), GL_UNSIGNED_INT, 0);

		//glViewport(width / 2, 0, width / 2, height);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		////glDrawElements(GL_TRIANGLES, cylinder->getIndices().size(), GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, cuboid->getIndices().size(), GL_UNSIGNED_INT, 0);


		//compound->rotate(sin(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
//		std::cout << "ajidfiajfiaw\n";
		


//		compound->rotateBy(1 , glm::vec3(0.0f, 0.0f, 1.0f));
//		compound->translateBy(glm::vec3(cos(glfwGetTime()) * 0.01, sin(glfwGetTime())*0.01, 0.0f));
		

//		angle += 1;

		wszystko->translateBySpecial(glm::vec3(0.5, 0.0, 0.0));
		wszystko->draw(mainCamera, shader->getProgramID());
		wszystko->translateBySpecial(glm::vec3(-0.5, 0.0, 0.0));
		wszystko->rotateBySpecial((float)glfwGetTime() * 0.1, glm::vec3(0.0, 0.0, 1.0));
//		collection2->draw(mainCamera, shader->getProgramID());
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

