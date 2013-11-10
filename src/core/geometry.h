#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include "graphics.h"

enum PrimitiveType { 
	TRIANGLE = GL_TRIANGLES, 
	QUADS = GL_QUADS, 
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
};

class Geometry {
	public:
		Geometry();
		Geometry(glm::vec3* vertices, glm::vec4* colours, int verticesCount);
        Geometry(glm::vec3* vertices, unsigned int* indices, int verticesCount, int indicesCount);
        Geometry(glm::vec3* vertices, unsigned int* indices, glm::vec3* normals, int verticesCount, int indicesCount);
		~Geometry();

		glm::vec3* GetVertices();
		glm::vec2* GetUVs();
		glm::vec4* GetColours();
        glm::vec3* GetNormals();
        unsigned int* GetIndices();
		
		int GetVerticesCount(); 
		int GetUVsCount();
        int GetIndicesCount();
        int GetNormalsCount();
		PrimitiveType GetType();

        void SetPrimitive(PrimitiveType primitiveType);

        void SetColours(glm::vec4* colours);
        void SetUVs(glm::vec2* uvs);

		static Geometry* Triangle();

		bool HasColors();
		bool HasTexCoords();
        bool HasIndices();
        bool HasNormals();
        
	private:
		glm::vec3* vertices;
		glm::vec2* uvs;
        glm::vec3* normals;
		glm::vec4* colours;
        unsigned int* indices;

        int indicesCount;
		int verticesCount;
		int uvsCount;
        int normalsCount;

		PrimitiveType primitiveType;
};

#endif
