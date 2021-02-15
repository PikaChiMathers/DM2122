#ifndef SCENE_5_H
#define SCENE_5_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"

class Scene5 : public Scene
{
public:
	Scene5();
	~Scene5();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float translateX, translateY;
	float scaleAll;

	int translateXDir, translateYDir, rotateDir, scaleDir;

	Color red, blue, green, pink, Lblue, purple, moonshade;

	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_AXES,

		GEO_QUAD,

		GEO_CUBE,

		GEO_SPHERE,
		MOON,

		GEO_CIRCLE,

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

	MS modelStack, viewStack, projectionStack;


		
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif