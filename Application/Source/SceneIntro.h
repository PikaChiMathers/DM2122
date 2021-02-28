#ifndef SCENE_INTRO
#define SCENE_INTRO

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"
#include "Light.h"
#include "Sound.h"
#include "Goose.h"
#include "GameObjectManager.h"
#include "TriggerCollider.h"
#include "Maps.h"
#include "Objects.h"


#include "Dialogue.h"

#include <sstream>

class SceneIntro : public Scene
{
public:
	SceneIntro();
	~SceneIntro();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	bool scene_change;

	int UI_height, UI_width;

	int colCount = 0;
	bool colEnter = false;

	int honk_count;
	bool honkerdonker = false;
	Sound sound;



	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_AXES = 0,

		GEO_QUAD,
		GEO_CUBE,
		GEO_GOOSE,
		GEO_BOSS,

		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_CIRCLE,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_SPLASH,
		GEO_ROOM,
		GEO_TEXT,
		GEO_UI,
		GEO_TEST,
		GEO_PINKLILY,

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
	Light lights[NUM_LIGHTS];
	Maps map;

	Dialogue* dialogue;

	//GameObject gameObject;
	Goose goose;
	GameObjectManager manager;
	Objects boss;
	unsigned m_vertexArrayID;
	/*unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];*/

	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	TriggerCollider bosscollider;

	bool IsSpacePressed;
	bool displayUI;
	void RenderMesh(Mesh* mesh, bool enableLight);

	void RenderSkybox();

	void RenderText(Mesh* mesh, std::string text, Color color);

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	int Space_Pressed;
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif