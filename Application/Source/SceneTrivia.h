#ifndef SCENE_TRIVIA
#define SCENE_TRIVIA

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"
#include "Light.h"

#include "GameObjectManager.h"
#include "TriggerCollider.h"
#include "Objects.h"
#include "Goose.h"
#include "Sound.h"

#include "Dialogue.h"

#include <sstream>

class SceneTrivia : public Scene
{
public:
	SceneTrivia();
	~SceneTrivia();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float translateX, translateY;
	float scaleAll;

	int UI_height, UI_width;


	enum GEOMETRY_TYPE //added (Step 1)
	{
		GEO_AXES = 0,
		GEO_QUAD,

		GEO_GOOSE,
		GEO_CONFETTI,

		GEO_TV,
		GEO_LOGO,
		GEO_PODIUM_A,
		GEO_PODIUM_B,
		GEO_PODIUM_C,

		GEO_LIGHTBALL,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_TEXT,

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
	Camera3 camera;
	Light lights[NUM_LIGHTS];
	Sound sound;

	Dialogue* Qn;
	std::string Qn_str;

	int press_time, qn_num, score;
	//press_time (number of times press spacebar is registered) (helps to prevent multiple registered keypresses)
	//qn_num (current question number)
	//score (player's score)
	std::string answer;
	bool play_once; //ensures hooray/aww sound is played only once

	GameObjectManager manager;
	Goose goose;
	Objects P_A, P_B, P_C; //Podium A, B & C
	Objects C_F, C_B, C_L, C_R; //Collider front, back, left & right
	TriggerCollider T_A, T_B, T_C;//Trigger A, B & C

	unsigned m_vertexArrayID;
	/*unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];*/

	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;

	void Check_Answer(); //To check player's trivia answer

	void RenderRoom();

	void RenderMesh(Mesh* mesh, bool enableLight);

	void RenderSkybox();

	void RenderText(Mesh* mesh, std::string text, Color color);

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);

	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
};

#endif