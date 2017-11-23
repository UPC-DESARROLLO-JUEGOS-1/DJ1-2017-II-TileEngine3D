#pragma once

#include "VertexData.h"
#include <glm\glm.hpp>

struct dtPositionNormalUVVertex
{
	V3 Position;
	V3 Normal;
	V2 UV;

	void SetPosition(float x, float y, float z) {
		Position.x = x;
		Position.y = y;
		Position.z = z;
	}

	void SetUV(float u, float v) {
		UV.x = u;
		UV.y = v;
	}

	void SetNormal(float x, float y, float z) {
		Normal.x = x;
		Normal.y = y;
		Normal.z = z;
	}

	void SetPositionAndUV(float x, float y, float z, float u, float v) {
		Position.x = x;
		Position.y = y;
		Position.z = z;
		UV.x = u;
		UV.y = v;
	}

	void static ProcessNormal(dtPositionNormalUVVertex* v1, dtPositionNormalUVVertex* v2, dtPositionNormalUVVertex* v3) {
		glm::vec3 vertex1 = glm::vec3(v1->Position.x, v1->Position.y, v1->Position.z);
		glm::vec3 vertex2 = glm::vec3(v2->Position.x, v2->Position.y, v2->Position.z);
		glm::vec3 vertex3 = glm::vec3(v3->Position.x, v3->Position.y, v3->Position.z);

		glm::vec3 edge1 = vertex2 - vertex1;
		glm::vec3 edge2 = vertex3 - vertex1;
		glm::vec3 cross = glm::cross(edge1, edge2);
		glm::vec3 normal = glm::normalize(cross);

		v1->SetNormal(normal.x, normal.y, normal.z);
		v2->SetNormal(normal.x, normal.y, normal.z);
		v3->SetNormal(normal.x, normal.y, normal.z);
	}

	void static ProcessNormal(dtPositionNormalUVVertex* v1, dtPositionNormalUVVertex* v2, dtPositionNormalUVVertex* v3, glm::vec3 offset) {
		glm::vec3 vertex1 = glm::vec3(v1->Position.x, v1->Position.y, v1->Position.z);
		glm::vec3 vertex2 = glm::vec3(v2->Position.x, v2->Position.y, v2->Position.z);
		glm::vec3 vertex3 = glm::vec3(v3->Position.x, v3->Position.y, v3->Position.z);

		glm::vec3 edge1 = vertex2 - vertex1;
		glm::vec3 edge2 = vertex3 - vertex1;
		glm::vec3 cross = glm::cross(edge1, edge2);
		glm::vec3 normal = glm::normalize(cross);

		normal = normal * offset;

		v1->SetNormal(normal.x, normal.y, normal.z);
		v2->SetNormal(normal.x, normal.y, normal.z);
		v3->SetNormal(normal.x, normal.y, normal.z);
	}
};