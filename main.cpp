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

#include "include/Scene.h"

class DisplayScene : public Core
{
	using uint = unsigned int;

private:
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Scene> scene;

	uint VBO, VAO, EBO;

public:
	DisplayScene() : Core("Display cylinder"), VBO(0), VAO(0), EBO(0)
	{
		shader = std::make_unique<Shader>("../shaders/texture.vs.glsl", "../shaders/texture.fs.glsl");
		scene = std::make_unique<Scene>();
	}

	void init() override
	{

		mainCamera->getSettings().movementSpeed /= 2;

		shader->use();

		glViewport(0, 0, mainWindow->getWindowSettings().width, mainWindow->getWindowSettings().height);

	}
	void draw() override
	{

		scene->draw(mainCamera, shader->getProgramID());

	}
	void updateLogic() override
	{

		scene->move();

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

	DisplayScene app;
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

