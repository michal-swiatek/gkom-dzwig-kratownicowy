/*
 *  Created by michal-swiatek on 16.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#include "Configure.h"

#include "Core.h"

#include <memory>
#include <iostream>

#include "Shader.h"

#include "SkyBox.h"
#include "include/Scene.h"

class DisplayScene : public Core
{
	using uint = unsigned int;

private:
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Scene> scene;
    std::unique_ptr<SkyBox> skyBox;

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

        skyBox = std::make_unique<SkyBox>(glm::vec4(1.0,0.5,0.5,1.0));

		glViewport(0, 0, mainWindow->getWindowSettings().width, mainWindow->getWindowSettings().height);

	}
	void draw() override
	{
        shader->use();
		scene->draw(*mainCamera, shader->getProgramID());
		skyBox->draw(*mainCamera);

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

