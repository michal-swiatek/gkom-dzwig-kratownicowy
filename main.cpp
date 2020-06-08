/*
 *  Created by michal-swiatek on 16.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#include "Configure.h"

#include "Core.h"

#include <memory>
#include <iostream>

#include "Shader.h"
#include "LightHandler.h"
#include "SkyBox.h"
#include "include/Scene.h"
#include "Shadows.h"

class DisplayScene : public Core
{
	using uint = unsigned int;

private:
	std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> shadowShader;
	std::unique_ptr<Scene> scene;
    std::unique_ptr<SkyBox> skyBox;
    std::unique_ptr<LightHandler> light;
    std::shared_ptr<PointLight> pointLight;
    std::shared_ptr<PointLight> pointLight2;
    std::shared_ptr<Model> cuboid;
    std::shared_ptr<LightSource> source;
    std::shared_ptr<LightSource> source2;
    glm::mat4 lightSpaceMatrix;

	uint VBO, VAO, EBO;

public:
	DisplayScene() : Core("Display cylinder"), VBO(0), VAO(0), EBO(0)
	{
		shader = std::make_unique<Shader>("../shaders/phong_model.vs.glsl", "../shaders/phong_model.fs.glsl");
        shadowShader = std::make_unique<Shader>("../shaders/shadow_map.vs.glsl", "../shaders/shadow_map.fs.glsl");
		scene = std::make_unique<Scene>();
        light = std::make_unique<LightHandler>();
        PointLightInfo pointLightInfo;
        pointLightInfo.ambient = glm::vec3(1.0f);
        pointLightInfo.diffuse = glm::vec3(1.0f);
        pointLightInfo.specular = glm::vec3(1.0f);
        pointLightInfo.constant = 1.0;
        pointLightInfo.linear = 0.03;
        pointLightInfo.quadratic = 0.01;
        cuboid = std::make_shared<Cuboid>();
        source = std::make_shared<LightSource>(cuboid);
        source->translateWorld(glm::vec3(10.0f, 0.5f, 0.0f));
        source2 = std::make_shared<LightSource>(cuboid);
        source2->translateWorld(glm::vec3(-10.0f, 0.5f, 0.0f));
        pointLight = std::make_unique<PointLight>(pointLightInfo,source);
        pointLight2 = std::make_unique<PointLight>(pointLightInfo,source2);
	}


	void init() override
	{

		mainCamera->getSettings().movementSpeed /= 2;
        DirectionalLight dirLight;
        dirLight.direction = glm::vec3(0.1f, 1.0f, 0.1f);
        dirLight.ambient = glm::vec3(0.1f);
        dirLight.specular = glm::vec3(0.6f);
        dirLight.diffuse = glm::vec3(0.9f);

        light->setDirLight(dirLight);
        light->addPointLight(pointLight);
        light->addPointLight(pointLight2);

        skyBox = std::make_unique<SkyBox>();
        shader->use();
        glViewport(0, 0, mainWindow->getWindowSettings().width, mainWindow->getWindowSettings().height);

	}
	void draw() override
	{
        shader->use();
        light->applyLightToShader(*shader);
		scene->draw(*mainCamera, shader->getProgramID());
		light->drawPointLights(*mainCamera);
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

