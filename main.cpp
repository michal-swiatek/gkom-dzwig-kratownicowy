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
    std::shared_ptr<Model> cuboid;
    glm::mat4 lightSpaceMatrix;

	const float LIGHT_STEP = 0.01f;
	const float MAX_LIGHT = 1.3f;
	const float MIN_LIGHT = 0.9f;

	float lightY = MAX_LIGHT;

    void createTopCraneLight(std::shared_ptr<Model> cuboid) {
        PointLightInfo pointLightInfo;
        pointLightInfo.ambient = glm::vec3(1.0f);
        pointLightInfo.diffuse = glm::vec3(1.0f);
        pointLightInfo.specular = glm::vec3(1.0f);
        pointLightInfo.constant = 1.0;
        pointLightInfo.linear = 0.22;
        pointLightInfo.quadratic = 0.2;
        pointLightInfo.color = glm::vec3(0.5,0.0,0.0);

        auto source = std::make_shared<LightSource>(cuboid);
        source->scaleLocal(glm::vec3(0.3));
        source->translateWorld(glm::vec3(0.0f, 50.1f, 0.0f));

        auto pointLight = std::make_shared<PointLight>(pointLightInfo,source);


        light->addPointLight(pointLight);

    }

    void createBottomCraneLights(std::shared_ptr<Model> cuboid) {
        PointLightInfo pointLightInfo;
		pointLightInfo.ambient = glm::vec3(0.8f);
		pointLightInfo.diffuse = glm::vec3(0.8f);
		pointLightInfo.specular = glm::vec3(0.8f);

        pointLightInfo.constant = 1.0;
		pointLightInfo.linear = 0.22;
		pointLightInfo.quadratic = 0.20;
		pointLightInfo.color = glm::vec3(1.0);

        auto source = std::make_shared<LightSource>(cuboid);
        source->scaleLocal(glm::vec3(0.3));
        source->translateWorld(glm::vec3(2.0f, 2.6f, 1.9f));
        auto pointLight = std::make_shared<PointLight>(pointLightInfo,source);
        auto source2 = std::make_shared<LightSource>(cuboid);
        source2->scaleLocal(glm::vec3(0.3));
        source2->translateWorld(glm::vec3(-2.0f, 2.6f, -1.9f));
        auto pointLight2 = std::make_shared<PointLight>(pointLightInfo,source2);
        auto source3 = std::make_shared<LightSource>(cuboid);
        source3->scaleLocal(glm::vec3(0.3));
        source3->translateWorld(glm::vec3(2.0f, 2.6f, -1.9f));
        auto pointLight3 = std::make_shared<PointLight>(pointLightInfo,source3);
        auto source4 = std::make_shared<LightSource>(cuboid);
        source4->scaleLocal(glm::vec3(0.3));
        source4->translateWorld(glm::vec3(-2.0f, 2.6f, 1.9f));
        auto pointLight4 = std::make_shared<PointLight>(pointLightInfo,source4);
        light->addPointLight(pointLight);
        light->addPointLight(pointLight2);
        light->addPointLight(pointLight3);
        light->addPointLight(pointLight4);
    }

    void createPointLights() {
        cuboid = std::make_shared<Cuboid>();
        createTopCraneLight(cuboid);
        createBottomCraneLights(cuboid);
    }
    void createDirLight() {
        DirectionalLight dirLight;
        dirLight.direction = glm::vec3(0.4f, 1.0f, 0.2f);
        dirLight.ambient = glm::vec3(0.1f);
        dirLight.specular = glm::vec3(0.4f);
        dirLight.diffuse = glm::vec3(0.6f);
        light->setDirLight(dirLight);
    }
    void initializeLight() {
        light = std::make_unique<LightHandler>();
        createPointLights();
        createDirLight();
    }
	uint VBO, VAO, EBO;

public:
	DisplayScene() : Core("Dzwig kratownicowy"), VBO(0), VAO(0), EBO(0)
	{
		shader = std::make_unique<Shader>("../shaders/phong_model.vs.glsl", "../shaders/phong_model.fs.glsl");
        shadowShader = std::make_unique<Shader>("../shaders/shadow_map.vs.glsl", "../shaders/shadow_map.fs.glsl");
		scene = std::make_unique<Scene>();
		initializeLight();
	}


	void init() override
	{
		mainCamera->getSettings().movementSpeed /= 2;
        skyBox = std::make_unique<SkyBox>();
        shader->use();
        prepareShadows();
        lightSpaceMatrix = calcLightSpaceMatrix(light->getDirection());
        glViewport(0, 0, mainWindow->getWindowSettings().width, mainWindow->getWindowSettings().height);

	}

    void draw() override
    {
        applyLightViewToShaders({ shadowShader.get(), shader.get() }, lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        shadowShader->use();
		
		glCullFace(GL_FRONT);
        scene->draw(*mainCamera, shadowShader->getProgramID());
		glCullFace(GL_BACK);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, mainWindow->getWindowSettings().width, mainWindow->getWindowSettings().height);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader->use();
        glActiveTexture(GL_TEXTURE15);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        shader->setInt("shadowMap", 15);
        light->applyLightToShader(*shader);
        scene->draw(*mainCamera, shader->getProgramID());
        light->drawPointLights(*mainCamera);

        skyBox->draw(*mainCamera);

    }

	void updateLogic() override
	{
		// Light
		if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_EQUAL) == GLFW_PRESS) {
			this->lightY += LIGHT_STEP;
			if (this->lightY >= MAX_LIGHT) {
				this->lightY = MAX_LIGHT;
			}
		}
		if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_MINUS) == GLFW_PRESS) {
			this->lightY -= LIGHT_STEP;
			if (this->lightY <= MIN_LIGHT) {
				this->lightY = MIN_LIGHT;
			}
		}

		light->setDirection(glm::vec3(1.0f, this->lightY, 1.0f));
		
		// Light intensity
		float intensity = glm::sin(glm::radians(90.0f*(1.0f-glm::abs(1.5f-lightY))));
		light->getDirLight().diffuse = glm::vec3(intensity);


		// Crane movement
		if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_R) == GLFW_PRESS)
			scene->rotateCraneTop(0.5f);
		if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_F) == GLFW_PRESS)
			scene->rotateCraneTop(-0.5f);
		if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_T) == GLFW_PRESS)
			scene->moveCraneHoist(0.1f);
		if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_G) == GLFW_PRESS)
			scene->moveCraneHoist(-0.1f);
		if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_Y) == GLFW_PRESS)
			scene->moveCraneHook(0.1f);
		if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_H) == GLFW_PRESS)
			scene->moveCraneHook(-0.1f);

        lightSpaceMatrix = calcLightSpaceMatrix(light->getDirection());
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

