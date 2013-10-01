#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include "graphics.h"

enum PrimitiveType { TRIANGLE = GL_TRIANGLES, QUADS = GL_QUADS };


class Geometry {
	public:
		Geometry();
		Geometry(glm::vec3* vertices, glm::vec4* colours, int verticesCount);
        Geometry(glm::vec3* vertices, unsigned int* indices, int verticesCount, int indicesCount);
		~Geometry();

		glm::vec3* GetVertices();
		glm::vec2* GetUVs();
		glm::vec4* GetColours();
        unsigned int* GetIndices();
		
		int GetVerticesCount(); 
		int GetUVsCount();
        int GetIndicesCount();
		PrimitiveType GetType();

        void SetPrimitive(PrimitiveType primitiveType);

        void SetColours(glm::vec4* colours);
        void SetUVs(glm::vec2* uvs);

		static Geometry* Triangle();

		bool HasColors();
		bool HasTexCoords();
        bool HasIndices();
	private:
		glm::vec3* vertices;
		glm::vec2* uvs;
		glm::vec4* colours;
        unsigned int* indices;

        int indicesCount;
		int verticesCount;
		int uvsCount;

		PrimitiveType primitiveType;
};

#endif
