#include "UnitHex.h"
#include "Shapes.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

UnitHex::UnitHex(Shader* shader, Texture* texture, const fVec3& position) {
	this->shader   = shader;
	this->texture  = texture;
	this->position = position;
}

fVec3 UnitHex::GetWorldCoordinates() {
	fVec3 ret = fVec3();
	ret.x = this->position.x * this->size.x * 0.75;
	ret.z = this->position.z * this->size.z;
	if (int(this->position.x) % 2) 
		ret.z += this->size.z * 0.5;
	ret.y = this->position.y * this->size.y;
	return ret;
}

void UnitHex::Draw() {
	fVec3 worldPos = GetWorldCoordinates();
	
	glm::mat4 model = glm::mat4(1.0);
	
	model = glm::translate(model, glm::vec3(worldPos.x, worldPos.y, worldPos.z));
	model = glm::scale    (model, glm::vec3(this->size.x, this->size.y, this->size.z));

	this->shader->Use();
	this->texture->Bind();

	this->shader->SetUniform(GLSLDataType::Mat4f, "uVP",    { &Camera::activeCam->VP[0][0] });
	this->shader->SetUniform(GLSLDataType::Mat4f, "uModel", { &model[0][0] });

	HexaPrism::instance.Draw();

}