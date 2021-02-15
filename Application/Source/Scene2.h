#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float translateX, translateY;
	float scaleAll;
	float box_TY, hearts_TX[5], hearts_TY[5];

	int translateXDir, translateYDir, rotateDir, scaleDir;
	int box_TYDir,num_hearts, hearts_Yorigin[5], hearts_TXDir[5], hearts_TYDir[5];

	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_TRIANGLE_2_INNER,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MVP2,
		U_TOTAL,
	};


private: //added (Step 2)
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif