#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string& meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateRevQuad(const std::string& meshName, Color color, float lengthX, float lengthY); //Reverse Quad is for UI that require the other side of the quad that may not be seen due to culling
	static Mesh* GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, unsigned numSlice, float radius);
	static Mesh* GenerateCone(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius, float height);
	static Mesh* GenerateCone(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius, float height, float apex_posX);
	static Mesh* GenerateCylinder(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius, float height);
	static Mesh* GenerateTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR, float anglePiece);
	static Mesh* GenerateOBJ(const std::string& meshName, const std::string& file_path);
	static Mesh* GenerateOBJ(const std::string& meshName, const std::string& file_path, Color color);
	static Mesh* GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path);
	static Mesh* GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol);
};

#endif