#ifndef SCENE_DRIVE
#define SCENE_DRIVE

#include "Scene.h"
#include "Camera2.h"
#include "Camera3.h"
#include "CameraChase.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"
#include "Light.h"

#include "GameObjectManager.h"
#include "Bus.h"
#include "ColliderObj.h"
#include "Border.h"
#include "Test.h"
#include "Person.h"
#include "Money.h"
#include "Maps.h"
#include "Score.h"

#include "Dialogue.h"

#include <sstream>

class SceneDrive : public Scene
{
public:
	SceneDrive();
	~SceneDrive();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float fps;

	Color red, blue, green, pink, Lblue, purple, orange, yellow, cyan, magenta, moonshade;

	bool scene_change;

	int UI_height, UI_width;


	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_AXES = 0,

		GEO_QUAD,
		GEO_TEMPLATE,
		GEO_BORDER,

		GEO_CUBE,

		GEO_COIN,
		GEO_PASSPORT,
		GEO_GOOSE,

		GEO_BUILDING1,
		GEO_BUILDING2,
		GEO_BUILDING3,
		GEO_BUILDING1B,
		GEO_BUILDING2B,
		GEO_BUILDING3B,

		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_CIRCLE,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_TEXT,

		GEO_TEST,

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

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};

	enum LIGHT_TYPES
	{
		LIGHT1 = 0,
		LIGHT2,
		NUM_LIGHTS,
	};


private: //added (Step 2)
	Camera3 camera;
	//CameraChase camera;

	Maps map;

	GameObjectManager manager;
	ColliderObj* cluster[51];
	ColliderObj* borderCol[4];
	Border* border[4];

	GameObject* TestRef;
	double toggleTime = 0;
	bool toggleHitBox = false;
	float multiplier = 4;
	int clusterType = 1;

	Money money;
	Score score;

	Bus bus;

	Light lights[NUM_LIGHTS];
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	MS modelStack, viewStack, projectionStack;

	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
		
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif