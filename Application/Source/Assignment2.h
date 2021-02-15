#ifndef SCENE_A2
#define SCENE_A2

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"
#include "Light.h"

#include <sstream>

class Assignment2 : public Scene
{
public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float translateX, translateY;
	float scaleAll;

	float fps;

	Position Capoo;
	Position Capoo_posBound, Capoo_negBound;

	float angle_leg, legDir, eyeMove_capoo, eye_capoo;
	float x_value, y_value, z_value;

	int translateXDir, translateYDir, rotateDir, scaleDir;

	Color red, blue, green, pink, Lblue, purple, orange, yellow, cyan, magenta, moonshade;

	Color black, Capoo_color, Capoo_pattern;

	bool in_house, ate_meat, is_sleeping, capoo_blinking, capoo_running;

	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_AXES = 0,

		GEO_QUAD,

		GEO_CUBE,

		EYE,
		MOUTH,

		CAPOO_SPHERE,
		CAPOO_PATTERN,
		CAPOO_CYLINDER,
		CAPOO_CONE,
		CAPOO_BLUSH,

		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_CIRCLE,

		//Skybox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_TEXT,

		//OBJs
		GEO_HOUSE,
		GEO_TREE,
		GEO_BALL,
		GEO_BED,
		GEO_MEAT,
		GEO_PLATE,

		GEO_MODEL7,
		GEO_MODEL8,

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

		U_M_LIGHT_POSITION,
		U_M_LIGHT_COLOR,
		U_M_LIGHT_POWER,
		U_M_LIGHT_KC,
		U_M_LIGHT_KL,
		U_M_LIGHT_KQ,
		U_M_LIGHT_TYPE,
		U_M_LIGHT_SPOTDIRECTION,
		U_M_LIGHT_COSCUTOFF,
		U_M_LIGHT_COSINNER,
		U_M_LIGHT_EXPONENT,

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
		M_LIGHT, //Light to highlight the meat in the house
		NUM_LIGHTS,
	};


private: //added (Step 2)
	Camera3 camera, camera_inHouse, camera_outHouse;
	Light lights[NUM_LIGHTS];

	unsigned m_vertexArrayID;

	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;


	void RenderMesh(Mesh* mesh, bool enableLight);

	void RenderSkybox();

	void RenderCapoo();

	void RenderText(Mesh* mesh, std::string text, Color color);

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
		
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif