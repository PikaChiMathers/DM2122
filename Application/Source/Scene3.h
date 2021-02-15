#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"

class Scene3 : public Scene
{
public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle, rotateBG;
	float translateX, translateY;
	float scaleAll;
	float box_TY, hearts_TX[8], hearts_TY[8], hearts_RX[8];

	int translateXDir, translateYDir, rotateDir, scaleDir;
	int box_TYDir,num_hearts, hearts_Yorigin[8], hearts_Xorigin[8], hearts_TXDir[5], hearts_TYDir[5];

	enum GEOMETRY_TYPE //added (Step 1)
	{
		SQUARE = 0,
		SQUARE_2,
		HEART,
		CIRCLE,
		CIRCLE_2, //like a prototype to allow me to make different colors for the circle without having to copy paste the same circle vertices
		CIRCLE_3,
		TRIANGLE,
		STAR,
		STICK,
		NUM_GEOMETRY,
	};

	enum COLOUR_TYPE
	{
		TREE_TRUNK,
		WATER,
		PETAL,
		CHERRY_BLOSSOM,
		DAY_NIGHT,
		HILL,
		BLANK,
		STAR_SHADE,
		NUM_COLOURS,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

	enum PLACING
	{
		PLACE_BACKGROUND = 0,
		PLACE_STARS,
		PLACE_WATER,
		PLACE_TREE_BASE,
		PLACE_HILL,
		PLACE_FALLING_LEAVES,
		PLACE_TREE_LEAVES
	};


private: //added (Step 2)
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_COLOURS];
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif