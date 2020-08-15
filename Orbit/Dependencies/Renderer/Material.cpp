#include "Material.h"

namespace Orbit
{
	Material::Material()
	{
	}
	Material::Material(const Shader& shader, const Texture& diffuseMap, const Texture& specularMap, const DirectionalLight& dirLight,
		std::vector<PointLight> pointLights, float shininess)
	{
		this->shader = shader;
		this->diffuseMap = diffuseMap;
		this->specularMap = specularMap;
		this->dirLight = dirLight;
		this->pointLights = pointLights;
		this->shininess = shininess;
	}
}