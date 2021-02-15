#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"

class Scene4 : public Scene
{
public:
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float translateX, translateY;
	float scaleAll;

	int translateXDir, translateYDir, rotateDir, scaleDir;

	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MVP2,
		U_TOTAL,
	};


private: //added (Step 2)
	Camera camera;

	unsigned m_vertexArrayID;
	/*unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];*/

	Mesh* meshList[NUM_GEOMETRY];

		
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif