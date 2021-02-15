#ifndef SCENE_LIGHT2_H
#define SCENE_LIGHT2_H

#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"
#include "Light.h"

class SceneLight2 : public Scene
{
public:
	SceneLight2();
	~SceneLight2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float translateX, translateY;
	float scaleAll;

	int translateXDir, translateYDir, rotateDir, scaleDir;

	Color red, blue, green, pink, Lblue, purple, orange, yellow, cyan, magenta, moonshade;

	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_AXES = 0,

		GEO_QUAD,

		GEO_CUBE,

		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_SPHERE1,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		GEO_SPHERE5,
		GEO_SPHERE6,
		GEO_SPHERE7,
		GEO_SPHERE8,
		MOON,

		GEO_CIRCLE,

		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,


		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,


		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_TOTAL,
	};

	enum LIGHT_TYPES
	{
		LIGHT1 = 0,
		LIGHT2,
		NUM_LIGHTS,
	};


private: //added (Step 2)
	Camera2 camera;
	Light lights[NUM_LIGHTS];

	unsigned m_vertexArrayID;
	/*unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];*/

	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;


	void RenderMesh(Mesh* mesh, bool enableLight);


		
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif