#include "UnitHex.h"
#include "Shapes.h"
#include "Camera.h"
#include "CoordinateSystem.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Batch.h"
#include "Log.h"
#include "ResourcesManager.h"
#include "Shader.h"
#include "Texture.h"


std::unordered_map<std::string, UnitHex> UnitHex::blockTypes;


UnitHex::UnitHex(Shader* shader, Texture* texture, const fVec3& position) {
	this->shader   = shader;
	this->texture  = texture;
	this->position = position;
}

Shader* UnitHex::GetShader() {
	return this->shader;
}

Texture* UnitHex::GetTexture() {
	return this->texture;
}

void UnitHex::Draw(const fVec3& worldPos) {
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(worldPos.x, worldPos.y, worldPos.z));
	model = glm::scale(model, glm::vec3(this->size.x, this->size.y, this->size.z));

	if (!isBatched) {
		this->texture->Bind();
		this->shader->Use();
		this->shader->SetUniform(GLSLDataType::Mat4f, "uVP", { &Camera::activeCam->VP[0][0] });
		this->shader->SetUniform(GLSLDataType::Mat4f, "uModel", { &model[0][0] });
		HexaPrism::instance.Draw();
		return;
	}
	Batch::Add(this, VertexData((float*)HexaPrism::vertices, 24 * 9), IndexData(HexaPrism::indices, 60), (void*)&model);
}


void UnitHex::Draw() {
	fVec3 worldPos = CoordinateSystem::HexToWorld(this->position, this->size);
	this->Draw(worldPos);
}


UnitHex* UnitHex::GetBlockType(std::string blockName) {
	auto temp = UnitHex::blockTypes.find(blockName);
	if (temp == UnitHex::blockTypes.end()) 
		return nullptr;
	return &temp->second;
}

void UnitHex::Init() {
	UnitHex::blockTypes["Grass"] = UnitHex(ResourceManager<Shader>::Load(RES_SHADER_DIR "PrismBatched.glsl"),
										   ResourceManager<Texture>::Load(RES_IMAGE_DIR "GrassHex.png"));

	UnitHex::blockTypes["Dirt"] = UnitHex(ResourceManager<Shader>::Load(RES_SHADER_DIR "PrismBatched.glsl"),
										   ResourceManager<Texture>::Load(RES_IMAGE_DIR "DirtHex.png"));


	UnitHex::blockTypes["Sand"] = UnitHex(ResourceManager<Shader>::Load(RES_SHADER_DIR "PrismBatched.glsl"),
											ResourceManager<Texture>::Load(RES_IMAGE_DIR "SandHex.png"));

	UnitHex::blockTypes["Stone"] = UnitHex(ResourceManager<Shader>::Load(RES_SHADER_DIR "PrismBatched.glsl"),
											ResourceManager<Texture>::Load(RES_IMAGE_DIR "StoneHex.png"));

	UnitHex::blockTypes["Snow"] = UnitHex(ResourceManager<Shader>::Load(RES_SHADER_DIR "PrismBatched.glsl"),
											ResourceManager<Texture>::Load(RES_IMAGE_DIR "SnowHex.png"));

}