#ifndef SCENE_MASTER
#define SCENE_MASTER

#include "Border.h"
#include "Camera3.h"
#include "Camera4.h"
#include "CameraChase.h"
#include "ColliderObj.h"
#include "Dialogue.h"
#include "DriveObjective.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Goose.h"
#include "Light.h"
#include "MatrixStack.h"
#include "Mesh.h"
#include "Maps.h"
#include "Money.h"
#include "Objects.h"
#include "Scene.h"
#include "Shop.h"
#include "Sound.h"
#include "Target.h"
#include "TriggerCollider.h"
#include "Person.h"
#include "Vertex.h"

#include <sstream>
#include <stdlib.h>

class SceneMaster : public Scene
{
public:
	SceneMaster();
	~SceneMaster();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float translateX, translateY;
	float scaleAll;

	float fps;

	int translateXDir, translateYDir, rotateDir, scaleDir;

	int UI_height, UI_width;

	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,

		GEO_QUAD,

		GEO_TEMPLATE_DRIVING,
		GEO_BORDER_DRIVING,
		GEO_OVERLAY_DRIVING,
		GEO_CUBE_DRIVING,
		GEO_COIN_DRIVING,
		GEO_NPC_DRIVING,
		GEO_BUILDING1_DRIVING,
		GEO_BUILDING2_DRIVING,
		GEO_BUILDING3_DRIVING,
		GEO_BUILDING1B_DRIVING,
		GEO_BUILDING2B_DRIVING,
		GEO_BUILDING3B_DRIVING,
		GEO_TEST_DRIVING,

		GEO_GOOSE_TRIVIA,
		GEO_CONFETTI_TRIVIA,
		GEO_TV_TRIVIA,
		GEO_LOGO_TRIVIA,
		GEO_PODIUM_A_TRIVIA,
		GEO_PODIUM_B_TRIVIA,
		GEO_PODIUM_C_TRIVIA,

		GEO_TARGET_SEARCH,
		GEO_PROGRESS_SEARCH,
		GEO_POPUP_SEARCH,
		GEO_MALL_SEARCH,
		GEO_BUILDING1_SEARCH,
		GEO_BUILDING2_SEARCH,
		GEO_BUILDING3_SEARCH,
		GEO_BUILDING4_SEARCH,
		GEO_BUILDING5_SEARCH,
		GEO_BUSSTOP_SEARCH,
		GEO_TREE1_SEARCH,
		GEO_TREE2_SEARCH,

		GEO_BUS_SHOP,

		GEO_LIGHTBALL,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_TEXT,
		GEO_UI,

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

	enum SCENE
	{
		MAIN_MENU = 0,
		PAUSE_MENU,
		INTRO,
		DRIVING,
		TRIVIA,
		SEARCH,
		SHOP,
	};

private:
	//shared
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	MS modelStack, viewStack, projectionStack;
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
	Light lights[1];

	//scene change variables
	Maps map;
	bool scene_change;

	//scene type
	unsigned scene;

	//driving camera
	CameraChase camera_driving;

	//trivia camera
	Camera3 camera_trivia;

	//search camera
	Target* camera_search;

	//shop camera
	Camera4 camera_shop;

	//general variables
	Dialogue* dialogue;

	Sound sound;

	int passengers;

	//main menu variables
	bool buttonState;
	double timer_main_menu;
	bool timerTriggered;

	//pause menu variables
	bool game_pause;

	//driving variables
	int honk_count;
	bool honkerdonker = false;

	GameObjectManager manager_driving;
	ColliderObj* cluster[51];
	ColliderObj* borderCol[4];
	Border* border[4];
	Money* coins[38];

	Person* npc[15];
	Position npcSpawn[15];

	Bus bus;
	DriveObjective endpoint;

	ColliderObj temp;

	GameObject* TestRef;
	double toggleTime = 0;
	bool toggleHitBox = false;
	float multiplier = 4;
	int clusterType = 1;

	float coinRot;

	bool startGame, endGame, paused;

	//trivia variables
	std::string Qn_str;
	int press_time_trivia; //number of times press spacebar is registered (helps to prevent multiple registered keypresses)
	int qn_num; //current question number

	int score;
	std::string answer;
	bool play_once; //ensures sound is played only once

	GameObjectManager manager_trivia;
	Goose goose;
	Objects P_A, P_B, P_C; //Podium A, B & C
	Objects C_F, C_B, C_L, C_R; //Collider front, back, left & right
	TriggerCollider T_A, T_B, T_C;//Trigger A, B & C

	void Check_Answer(); //To check player's trivia answer

	void RenderRoom();

	//search variables
	int colCount = 0;
	bool colEnter = false;

	bool game_start;

	int current_target;
	int press_time_search; //ensures that A or D key presses are only registered as 1 press each time
	int spam_time; //ensures that spacebar presses are only registered as 1 press each time
	int press_count; //counts the number of spacebar presses the player has done
	int passenger_count; //number of passengers found

	int timer_search;

	Target targets[16];

	void RenderCity();

	//shop variables
	Shop shop;

	bool displayShopUI0;
	bool displayShopUI1;
	bool displayShopUI2;
	bool displayMessage;

	int money;
	double timer_shop;
	bool spacePressed;

	//shared
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
};

#endif