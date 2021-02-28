#ifndef SCENE_SEARCH
#define SCENE_SEARCH

#include "Scene.h"
#include "Target.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"
#include "Light.h"

#include "Maps.h"
#include "Sound.h"

#include <sstream>
#include <stdlib.h>

class SceneSearch : public Scene
{
public:
	SceneSearch();
	~SceneSearch();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float translateX, translateY;
	float scaleAll;

	bool scene_change;

	int UI_height, UI_width;


	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_AXES = 0,

		GEO_TARGET,
		GEO_PROGRESS,

		GEO_CUBE,

		GEO_POPUP,

		GEO_MALL,
		GEO_BUILDING1,
		GEO_BUILDING2,
		GEO_BUILDING3,
		GEO_BUILDING4,
		GEO_BUILDING5,
		GEO_BUILDING6,
		GEO_BUILDING7,
		GEO_BUILDING8,
		GEO_BUSSTOP,
		GEO_TREE1,
		GEO_TREE2,

		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_CIRCLE,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_FLOOR,

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
		NUM_LIGHTS,
	};


private: //added (Step 2)
	Target* camera;

	bool game_start;
	bool game_pause;

	int current_target;
	// press_time (ensures that A or D key presses are only registered as 1 press each time)
	// spam_time (ensures that spacebar presses are only registered as 1 press each time)
	// esc_time (ensures that the esc button press is only registered as 1 press each time)
	//press_count (counts the number of spacebar presses the player has done)
	//passenger_count (stores the number of passengers found)
	int press_time, spam_time, esc_time, press_count, passenger_count;

	int timer;

	Target targets[16];

	Light lights[NUM_LIGHTS];
	Maps map;

	Sound sound;

	unsigned m_vertexArrayID;

	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;


	void RenderMesh(Mesh* mesh, bool enableLight);

	void RenderSkybox();

	void RenderCity();

	void RenderText(Mesh* mesh, std::string text, Color color);

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
		
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif