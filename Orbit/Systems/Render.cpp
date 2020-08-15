#include "Render.h"

namespace Orbit
{
	void Orbit::Render::Init()
	{
        for (auto it : entities)
        {
            Renderable* renderable = (Renderable*) ecsInstance->GetComponent<Renderable>(it);

            renderable->material.shader.Use();
            renderable->material.shader.SetInt("material.diffuse", 0);
            renderable->material.shader.SetInt("material.specular", 1);

            glGenVertexArrays(1, &(renderable->VAO));
            glGenBuffers(1, &(renderable->VBO));

            glBindBuffer(GL_ARRAY_BUFFER, renderable->VBO);
            glBufferData(GL_ARRAY_BUFFER, renderable->vertices.size() * sizeof(float), &(renderable->vertices)[0], GL_STATIC_DRAW);

            glBindVertexArray(renderable->VAO);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
	}

	void Orbit::Render::Update(float dt)
	{

        for (auto it : entities)
        {
            Renderable* renderable = (Renderable*)ecsInstance->GetComponent<Renderable>(it);
            Transform* transform = (Transform*)ecsInstance->GetComponent<Transform>(it);

            renderable->material.shader.Use();

            glm::mat4 projection = glm::perspective(glm::radians(45.0f), renderable->persWidth / renderable->persHeight, 0.1f, 100.0f);

            glm::mat4 view = (*(renderable->camera)).GetViewMatrix();

            renderable->material.shader.SetMat4("projection", projection);
            renderable->material.shader.SetMat4("view", view);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform->position);
            model = glm::rotate(model, glm::radians(transform->angle), transform->rotation);
            renderable->material.shader.SetMat4("model", model);

            renderable->material.shader.SetVec3("viewPos", (*(renderable->camera)).position);
            renderable->material.shader.SetFloat("material.shininess", renderable->material.shininess);

            renderable->material.shader.SetVec3("dirLight.direction", renderable->material.dirLight.direction);
            renderable->material.shader.SetVec3("dirLight.ambient", renderable->material.dirLight.ambient);
            renderable->material.shader.SetVec3("dirLight.diffuse", renderable->material.dirLight.diffuse);
            renderable->material.shader.SetVec3("dirLight.specular", renderable->material.dirLight.specular);

            renderable->material.shader.SetInt("nr_active_point_lights", renderable->material.pointLights.size());

            for (int i = 0; i < renderable->material.pointLights.size(); i++)
            {
                std::string lightname = "pointLights[" + std::to_string(i) + "].";
                renderable->material.shader.SetVec3(lightname + "position", renderable->material.pointLights[i].position);
                renderable->material.shader.SetVec3(lightname + "ambient", renderable->material.pointLights[i].ambient);
                renderable->material.shader.SetVec3(lightname + "diffuse", renderable->material.pointLights[i].diffuse);
                renderable->material.shader.SetVec3(lightname + "specular", renderable->material.pointLights[i].specular);
                renderable->material.shader.SetFloat(lightname + "constant", renderable->material.pointLights[i].constant);
                renderable->material.shader.SetFloat(lightname + "linear", renderable->material.pointLights[i].linear);
                renderable->material.shader.SetFloat(lightname + "quadratic", renderable->material.pointLights[i].quadratic);
            }

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, renderable->material.diffuseMap.ID);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, renderable->material.specularMap.ID);

            glBindVertexArray(renderable->VAO);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

	}
}


