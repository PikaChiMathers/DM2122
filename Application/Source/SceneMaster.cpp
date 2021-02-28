#include "SceneMaster.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Utility.h"
#include "LoadTGA.h"

#include "Application.h"


SceneMaster::SceneMaster()
{
}

SceneMaster::~SceneMaster()
{
}

void SceneMaster::Init()
{
	map.Set(Maps::SKYBOX_TYPE::SB_SHOP); //to be changed

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	scene_change = true;

	rotateAngle = 0;

	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	UI_width = 160;
	UI_height = 90;

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", Color(.39f, .39f, .39f), 1.f, 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//carpet.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", lights[0].color, 30, 30, 1);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_FRONT_TRIVIA] = MeshBuilder::GenerateQuad("front", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM_TRIVIA] = MeshBuilder::GenerateQuad("bottom", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_BACK_TRIVIA] = MeshBuilder::GenerateQuad("back", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_TOP_TRIVIA] = MeshBuilder::GenerateQuad("top", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_LEFT_TRIVIA] = MeshBuilder::GenerateQuad("left", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_RIGHT_TRIVIA] = MeshBuilder::GenerateQuad("right", Color(.04f, .71f, 1), 1.f, 1.f);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//trebuchet.tga");

	meshList[GEO_UI] = MeshBuilder::GenerateRevQuad("UI", Color(1, 1, 1), 1.f, 1.f);

	//main menu meshes
	{
		meshList[GEO_UI]->textureID = LoadTGA("Assets//start.tga");
	}

	//pause menu meshes
	{
		meshList[GEO_OVERLAY] = MeshBuilder::GenerateRevQuad("overlay", Color(1, 1, 1), 1.f, 1.f);
		meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//overlay.tga");
	}

	//trivia meshes
	{
		meshList[GEO_GOOSE_TRIVIA] = MeshBuilder::GenerateOBJ("Goose", "OBJ//goose.obj", Color(.93f, .79f, 0));
		meshList[GEO_GOOSE_TRIVIA]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_GOOSE_TRIVIA]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
		meshList[GEO_GOOSE_TRIVIA]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
		meshList[GEO_GOOSE_TRIVIA]->material.kShininess = 1.f;

		meshList[GEO_PODIUM_A_TRIVIA] = MeshBuilder::GenerateOBJ("A", "OBJ//podium.obj", Color(1, 0, 0));
		meshList[GEO_PODIUM_B_TRIVIA] = MeshBuilder::GenerateOBJ("B", "OBJ//podium.obj", Color(0, 1, 0));
		meshList[GEO_PODIUM_C_TRIVIA] = MeshBuilder::GenerateOBJ("C", "OBJ//podium.obj", Color(0, 0, 1));

		meshList[GEO_TV_TRIVIA] = MeshBuilder::GenerateQuad("television", Color(1, 1, 1), 1, 1);
		meshList[GEO_TV_TRIVIA]->textureID = LoadTGA("Image//television.tga");
		meshList[GEO_TV_TRIVIA]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_TV_TRIVIA]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
		meshList[GEO_TV_TRIVIA]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
		meshList[GEO_TV_TRIVIA]->material.kShininess = 1.f;

		meshList[GEO_CONFETTI_TRIVIA] = MeshBuilder::GenerateRevQuad("confetti", Color(1, 1, 1), 160, 90);
		meshList[GEO_CONFETTI_TRIVIA]->textureID = LoadTGA("Image//confetti.tga");

		meshList[GEO_LOGO_TRIVIA] = MeshBuilder::GenerateQuad("logo", Color(1, 1, 1), 1, 1);
		meshList[GEO_LOGO_TRIVIA]->textureID = LoadTGA("Image//trivia_logo.tga");
		meshList[GEO_LOGO_TRIVIA]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_LOGO_TRIVIA]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
		meshList[GEO_LOGO_TRIVIA]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
		meshList[GEO_LOGO_TRIVIA]->material.kShininess = 1.f;
	}

	//search meshes
	{
		meshList[GEO_TARGET_SEARCH] = MeshBuilder::GenerateRevQuad("target", Color(1, 1, 1), 1.f, 1.f);
		meshList[GEO_TARGET_SEARCH]->textureID = LoadTGA("Image//target.tga");

		meshList[GEO_PROGRESS_SEARCH] = MeshBuilder::GenerateRevQuad("progress", Color(1, 1, 1), 1.f, 1.f);

		meshList[GEO_POPUP_SEARCH] = MeshBuilder::GenerateRevQuad("Instructions", Color(1, 1, 1), 1, 1);
		meshList[GEO_POPUP_SEARCH]->textureID = LoadTGA("Assets//search_instructions.tga");

		meshList[GEO_BUILDING1_SEARCH] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//short_apartment.obj", "OBJ//short_apartment.mtl");
		meshList[GEO_BUILDING1_SEARCH]->textureID = LoadTGA("Image//apartment.tga");
		meshList[GEO_BUILDING2_SEARCH] = MeshBuilder::GenerateOBJMTL("building2", "OBJ//med_apartment.obj", "OBJ//med_apartment.mtl");
		meshList[GEO_BUILDING2_SEARCH]->textureID = LoadTGA("Image//apartment.tga");
		meshList[GEO_BUILDING3_SEARCH] = MeshBuilder::GenerateOBJMTL("building3", "OBJ//tall_apartment.obj", "OBJ//tall_apartment.mtl");
		meshList[GEO_BUILDING3_SEARCH]->textureID = LoadTGA("Image//apartment.tga");
		meshList[GEO_BUILDING4_SEARCH] = MeshBuilder::GenerateOBJMTL("house2", "OBJ//smol_building.obj", "OBJ//smol_building.mtl");
		meshList[GEO_BUILDING4_SEARCH]->textureID = LoadTGA("Image//house2.tga");
		meshList[GEO_BUILDING5_SEARCH] = MeshBuilder::GenerateOBJMTL("building2", "OBJ//med_apartment.obj", "OBJ//med_apartment.mtl");
		meshList[GEO_BUILDING5_SEARCH]->textureID = LoadTGA("Image//house2.tga");
		meshList[GEO_BUSSTOP_SEARCH] = MeshBuilder::GenerateOBJ("busstop", "OBJ//bustop.obj", Color(1, 1, 1));
		meshList[GEO_MALL_SEARCH] = MeshBuilder::GenerateOBJMTL("mall", "OBJ//stadium.obj", "OBJ//stadium.mtl");
		meshList[GEO_MALL_SEARCH]->textureID = LoadTGA("Image//stadium.tga");
		meshList[GEO_TREE1_SEARCH] = MeshBuilder::GenerateOBJ("tree1", "OBJ//tree_large.obj", Color(0.184314, 0.309804, 0.184314));
		meshList[GEO_TREE2_SEARCH] = MeshBuilder::GenerateOBJ("tree2", "OBJ//tree_small.obj", Color(0.184314, 0.309804, 0.184314));
		meshList[GEO_FLOOR_SEARCH] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1), 1.f, 1.f);
		meshList[GEO_FLOOR_SEARCH]->textureID = LoadTGA("Image//HNS_map.tga");
	}

	//shop meshes
	{
		meshList[GEO_BUS_SHOP] = MeshBuilder::GenerateOBJ("bus", "OBJ//bus.obj", Color(0, 1, 1));
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL; //to be changed
	lights[0].position.Set(0, 10, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 3;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	glEnable(GL_DEPTH_TEST);

	//main menu init
	{
		buttonState = false;
		timer_main_menu = 0;
		timerTriggered = false;
	}

	//driving init
	{
		driving->Init();
	}

	//trivia init
	{
		camera_trivia.Init(Vector3(0, 9.2f, -23), Vector3(0, 9.15f, -22), Vector3(0, 1, 0.05f));

		manager_trivia.CreateGameObject(&goose);

		//Initializes the Podiums A, B & C
		manager_trivia.CreateGameObject(&P_A);
		manager_trivia.CreateGameObject(&P_B);
		manager_trivia.CreateGameObject(&P_C);

		//Initializes Wall Colliders front, back, left & right
		manager_trivia.CreateGameObject(&C_F);
		manager_trivia.CreateGameObject(&C_B);
		manager_trivia.CreateGameObject(&C_L);
		manager_trivia.CreateGameObject(&C_R);

		//Initializes Trigger (Checks whether the player presses spacebar in a cerrtain area) of each podium
		manager_trivia.CreateGameObject(&T_A);
		manager_trivia.CreateGameObject(&T_B);
		manager_trivia.CreateGameObject(&T_C);

		//Sets the position of each Object
		goose.SetRotateY(180);
		goose.SetPosition(Position(0, -.5f, -5));

		P_A.SetPosition(Position(5, 0, 0));
		P_B.SetPosition(Position(0, 0, 0));
		P_C.SetPosition(Position(-5, 0, 0));

		C_F.SetScale(Scale(50, 50, 50));
		C_B.SetScale(Scale(50, 50, 50));
		C_L.SetScale(Scale(50, 50, 50));
		C_R.SetScale(Scale(50, 50, 50));

		C_F.SetPosition(Position(0, 0, 46));
		C_B.SetPosition(Position(0, 0, -33));
		C_L.SetPosition(Position(-38, 0, 5));
		C_R.SetPosition(Position(38, 0, 5));

		T_A.SetPosition(Position(5, 0, 0));
		T_B.SetPosition(Position(0, 0, 0));
		T_C.SetPosition(Position(-5, 0, 0));

		press_time_trivia = qn_num = score = passengers = 0;
		play_once = false;
		dialogue = new Dialogue("Dialogue//Trivia.txt", Dialogue::TRIVIA); //Qn is a Dialogue ptr which will read the trivia txt file
		Qn_str = dialogue->Update(); //Qn_str will first be Updated to Show the Theme of Trivia

		answer = ""; //Initializes answer to be blank

		timer_minigame = 0;
		minigameTimerTriggered = false;
	}

	//search init
	{
		srand(time(NULL)); //to initialize random seed

		//keeps trach of the locations of the different buildings
		targets[0].Init(Vector3(0, 240, -330), Vector3(.73f, 239.7f, -329), Vector3(0.1f, 1, 0.2f));
		targets[1].Init(Vector3(0, 240, -330), Vector3(.59f, 239.7f, -329), Vector3(0.1f, 1, 0.2f));
		targets[2].Init(Vector3(0, 240, -330), Vector3(.48f, 239.73f, -329), Vector3(0.1f, 1, 0.2f));
		targets[3].Init(Vector3(0, 240, -330), Vector3(.4f, 239.6f, -329), Vector3(0.1f, 1, 0.2f));
		targets[4].Init(Vector3(0, 240, -330), Vector3(.38f, 239.8f, -329), Vector3(0.1f, 1, 0.2f));
		targets[5].Init(Vector3(0, 240, -330), Vector3(.25f, 239.95f, -329), Vector3(0.1f, 1, 0.2f));
		targets[6].Init(Vector3(0, 240, -330), Vector3(.11f, 239.7f, -329), Vector3(0.1f, 1, 0.2f));
		targets[7].Init(Vector3(0, 240, -330), Vector3(.08f, 239.95f, -329), Vector3(0.1f, 1, 0.2f));
		targets[8].Init(Vector3(0, 240, -330), Vector3(-.22f, 239.8f, -329), Vector3(0.1f, 1, 0.2f));
		targets[9].Init(Vector3(0, 240, -330), Vector3(-.25f, 239.69f, -329), Vector3(0.1f, 1, 0.2f));
		targets[10].Init(Vector3(0, 240, -330), Vector3(-.29f, 239.6f, -329), Vector3(0.1f, 1, 0.2f));
		targets[11].Init(Vector3(0, 240, -330), Vector3(-.41f, 239.8f, -329), Vector3(0.1f, 1, 0.2f));
		targets[12].Init(Vector3(0, 240, -330), Vector3(-.48f, 239.65f, -329), Vector3(0.1f, 1, 0.2f));
		targets[13].Init(Vector3(0, 240, -330), Vector3(-.58f, 239.7f, -329), Vector3(0.1f, 1, 0.2f));
		targets[14].Init(Vector3(0, 240, -330), Vector3(-.73f, 239.75f, -329), Vector3(0.1f, 1, 0.2f));
		targets[15].Init(Vector3(0, 240, -330), Vector3(-1.f, 239.4f, -329), Vector3(0.1f, 1, 0.2f));

		game_start = false;

		int min = 2; //min is how long this game will last in minutes
		timer_search = min * 60 * 60;

		for (int cam = 0; cam < 9; cam++) //Uses randomizer to set up to 9 random targets/buildings to have passengers
		{
			int target_num = rand() % 16;
			targets[target_num].num_passengers = rand() % 5 + 1; //each of the randomly selected buildings can have 1 to 5 passengers
		}

		current_target = press_count = passenger_count = press_time_search = spam_time = 0;
		camera_search = &targets[0];
	}

	//shop init
	{
		camera_shop.Init(Vector3(9.5f, 3, 6), Vector3(0, 3, 0), Vector3(0, 1, 0));
		camera_shop.setShopBound(Vector3(-18.85f, 2, -8.35f), Vector3(18.85f, 4, 8.35f));
		camera_shop.setBusBound(Vector3(-13.5f, 2, -4), Vector3(13.5f, 4, 4));

		displayShopUI0 = false;
		displayShopUI1 = false;
		displayShopUI2 = false;
		displayMessage = false;
	}

	scene = MAIN_MENU;
}

void SceneMaster::Update(double dt)
{
	if (game_pause == true)
	{
		scene = PAUSE_MENU;

		if (!pausePressed && Application::IsKeyPressed('P'))
		{
			game_pause = false;
			scene = prePausedScene;
			pausePressed = true;
		}

		if (pausePressed && !Application::IsKeyPressed('P'))
			pausePressed = false;

	}
	else
	{
		if (scene == TRIVIA)
			camera_trivia.Update(dt);
		if (scene == SHOP)
			camera_shop.Update(dt);

		fps = 1.0 / dt;

		rotateAngle += (float)(50 * dt);
		translateX += (float)(translateXDir * 10 * dt);
		translateY += (float)(translateYDir * 50 * dt);
		scaleAll += (float)(scaleDir * 2 * dt);

		if (Application::IsKeyPressed('1'))
			glEnable(GL_CULL_FACE);
		if (Application::IsKeyPressed('2'))
			glDisable(GL_CULL_FACE);
		if (Application::IsKeyPressed('3'))
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (Application::IsKeyPressed('4'))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		if (scene == MAIN_MENU)
		{
			if (timer_main_menu > 0)
				timer_main_menu -= dt;

			if (!buttonState && Application::IsMousePressed(0))
			{
				buttonState = true;
			}
			else if (buttonState && !Application::IsMousePressed(0))
			{
				buttonState = false;
				double x, y;
				Application::GetCursorPos(&x, &y);
				int w = Application::GetWindowWidth();
				int h = Application::GetWindowHeight();
				float posX = x / 10;
				float posY = 60 - (y / 10);
				if (posX > 44 && posX < 85 && posY > 1 && posY < 23)
				{
					meshList[GEO_UI]->textureID = LoadTGA("Assets//start_down.tga");

					if (timer_main_menu == 0)
						timer_main_menu = 0.5;

					timerTriggered = true;
				}
			}

			if (timer_main_menu <= 0 && timerTriggered == true)
			{
				scene_change = true;
				scene = DRIVING;
				map.Set(Maps::SKYBOX_TYPE::SB_DAY);
			}
		}
		else if (scene == INTRO)
		{

		}
		else if (scene == DRIVING)
		{
			driving->Update(dt);

			if (driving->getFinishScene() == true)
			{
				delete driving;

				if (rand() % 2 == 0)
				{
					scene = TRIVIA;
				}
				else
				{
					scene_change = true;
					scene = SEARCH;
					map.Set(Maps::SKYBOX_TYPE::SB_DAY);
				}
			}
		}
		else if (scene == TRIVIA)
		{
			manager_trivia.GameObjectManagerUpdate(dt);

			if (qn_num == 10) //To set the spotlight and drumroll for the final qn
			{
				if (!sound.Engine()->isCurrentlyPlaying(("media/drumroll.ogg"))) //loops drumroll until players answers qn
					sound.Engine()->play2D("media/drumroll.ogg");
				lights[0].type = Light::LIGHT_SPOT;
				glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
			}
			else if (qn_num > 10)
			{
				if (!play_once)
				{
					sound.Engine()->stopAllSounds();
					if (score >= 8)
					{
						sound.Engine()->play2D("media/hooray.ogg");
					}
					else if (score < 5)
						sound.Engine()->play2D("media/sad_trumbone.ogg");
					else
						sound.Engine()->play2D("media/slow_clap.ogg");

					play_once = true;
				}
			}

			if (Application::IsKeyPressed(VK_SPACE))
			{
				press_time_trivia++;
				if (press_time_trivia == 1) // To ensure that the Spacebar is only pressed once
				{
					sound.Engine()->play2D("media/honk_1.wav");

					if (qn_num <= 10)
					{
						//checks which answer was chosen
						if (T_A.IsTriggered())
							answer = dialogue->getChoice1();

						else if (T_B.IsTriggered())
							answer = dialogue->getChoice2();

						else if (T_C.IsTriggered())
							answer = dialogue->getChoice3();

						else
							answer = "";

						if (answer != "")
						{ //changes the qn and checks if the answer is correct
							qn_num++;
							if (qn_num != 0)
								Check_Answer();
						}

						if (qn_num == 0)
						{
							qn_num++;
							Qn_str = dialogue->Update();
						}
					}
				}
			}
			else press_time_trivia = 0;

			if (qn_num > 10) // to check if all 10 qns were answered
			{
				if (score < 5)
					passengers = -(5 - score); //loses passengers if wrong info was given
				if (score >= 8)
					passengers = score - 5; //gains passengers if tour is interesting

				if (timer_minigame <= 0)
				{
					scene_change = true;
					scene = SHOP;
					map.Set(Maps::SKYBOX_TYPE::SB_SHOP);
				}

				if (timer_minigame > 0)
					timer_minigame -= dt;

				if (minigameTimerTriggered == false)
				{
					timer_minigame = 3;
					minigameTimerTriggered = true;
				}
			}
		}
		else if (scene == SEARCH)
		{
			if (timer_search > 0)
			{
				if (game_start)
				{
					timer_search--;
					if (press_count == 0)
					{
						if (Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed(VK_RIGHT))
						{
							//changes location
							press_time_search++;
							if (press_time_search == 1)
							{
								if (Application::IsKeyPressed(VK_LEFT))
									current_target--;
								if (Application::IsKeyPressed(VK_RIGHT))
									current_target++;

								if (current_target < 0)
									current_target = 15;
								if (current_target >= 16)
									current_target = 0;
							}
						}
						else
							press_time_search = 0;

						camera_search = &targets[current_target];
					}

					//Updates the percentage of the building
					if (press_count >= 25)
						camera_search->progress = 25;
					if (press_count >= 50)
						camera_search->progress = 50;
					if (press_count >= 75)
						camera_search->progress = 75;
					if (press_count >= 100)
					{
						camera_search->progress = 100;
						press_count = 0;
						passenger_count += camera_search->num_passengers;
						camera_search->has_checked = true;
					}
				}

				if (Application::IsKeyPressed(VK_SPACE))
				{
					spam_time++;
					if (spam_time == 1)
					{
						if (game_start)
						{
							if (!camera_search->has_checked && press_count < 100)
							{
								//Randomizes Honk sounds
								std::string sound_file = "media/honk_" + std::to_string(rand() % 5 + 1) + ".wav";
								sound.Engine()->play2D(sound_file.std::string::c_str());

								press_count++;
							}
						}
						else
							game_start = true;
					}
				}
				else
					spam_time = 0;
			}
			else
			{
				if (timer_minigame <= 0)
				{
					scene_change = true;
					scene = SHOP;
					map.Set(Maps::SKYBOX_TYPE::SB_SHOP);
				}

				if (timer_minigame > 0)
					timer_minigame -= dt;

				if (minigameTimerTriggered == false)
				{
					timer_minigame = 3;
					minigameTimerTriggered = true;
				}
			}
		}
		else if (scene == SHOP)
		{
			bool canUpgrade0 = false;
			bool canUpgrade1 = false;
			bool canUpgrade2 = false;
			if (camera_shop.position.x > -13.5 && camera_shop.position.z > -8.35 && camera_shop.position.x < 13.5 && camera_shop.position.z < 8.35)
			{
				displayShopUI0 = true;

				if (shop.getUpgradeLevel(0) == 0)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max speed 0.tga");
				else if (shop.getUpgradeLevel(0) == 1)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max speed 1.tga");
				else if (shop.getUpgradeLevel(0) == 2)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max speed 2.tga");
				else if (shop.getUpgradeLevel(0) == 3)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max speed 3.tga");
				else if (shop.getUpgradeLevel(0) == 4)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max speed 4.tga");
				else if (shop.getUpgradeLevel(0) == 5)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max speed 5.tga");

				if (shop.getUpgradeLevel(0) < 5)
					canUpgrade0 = true;
			}
			else if (camera_shop.position.x > 13.5 && camera_shop.position.z > -4 && camera_shop.position.x < 18.85 && camera_shop.position.z < 4)
			{
				displayShopUI1 = true;

				if (shop.getUpgradeLevel(1) == 0)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max capacity 0.tga");
				else if (shop.getUpgradeLevel(1) == 1)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max capacity 1.tga");
				else if (shop.getUpgradeLevel(1) == 2)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max capacity 2.tga");
				else if (shop.getUpgradeLevel(1) == 3)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max capacity 3.tga");
				else if (shop.getUpgradeLevel(1) == 4)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max capacity 4.tga");
				else if (shop.getUpgradeLevel(1) == 5)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//max capacity 5.tga");

				if (shop.getUpgradeLevel(1) != 5)
					canUpgrade1 = true;
			}
			else if (camera_shop.position.x > -18.85 && camera_shop.position.z > -8.35 && camera_shop.position.x < -13.5 && camera_shop.position.z < 4)
			{
				displayShopUI2 = true;

				if (shop.getUpgradeLevel(2) == 0)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//item spawn 0.tga");
				else if (shop.getUpgradeLevel(2) == 1)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//item spawn 1.tga");
				else if (shop.getUpgradeLevel(2) == 2)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//item spawn 2.tga");
				else if (shop.getUpgradeLevel(2) == 3)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//item spawn 3.tga");
				else if (shop.getUpgradeLevel(2) == 4)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//item spawn 4.tga");
				else if (shop.getUpgradeLevel(2) == 5)
					meshList[GEO_UI]->textureID = LoadTGA("Assets//item spawn 5.tga");

				if (shop.getUpgradeLevel(2) != 5)
					canUpgrade2 = true;
			}
			else
			{
				displayShopUI0 = false;
				displayShopUI1 = false;
				displayShopUI2 = false;
			}

			if (timer_shop > 0)
				timer_shop -= dt;
			else
				displayMessage = false;

			if (spacePressed == false && Application::IsKeyPressed(VK_SPACE))
			{
				spacePressed = true;

				if (canUpgrade0 == true && Bus::GetMoney() >= shop.getUpgradeCost(0))
				{
					Bus::ReduceMoney(shop.getUpgradeCost(0));
					shop.upgrade(0);
				}
				else if (canUpgrade1 == true && Bus::GetMoney() >= shop.getUpgradeCost(1))
				{
					Bus::ReduceMoney(shop.getUpgradeCost(1));
					shop.upgrade(1);
				}
				else if (canUpgrade2 == true && Bus::GetMoney() >= shop.getUpgradeCost(2))
				{
					Bus::ReduceMoney(shop.getUpgradeCost(2));
					shop.upgrade(2);
				}
				else
				{
					displayMessage = true;
					timer_shop = 1;
				}
			}

			if (spacePressed == true && !Application::IsKeyPressed(VK_SPACE))
				spacePressed = false;

			if (enterPressed == false && Application::IsKeyPressed(VK_LSHIFT))
				enterPressed == true;

			if (enterPressed == true && !Application::IsKeyPressed(VK_LSHIFT))
			{
				enterPressed == false;

				driving = new SceneDrive();
				scene_change = true;
				scene = DRIVING;
				map.Set(Maps::SKYBOX_TYPE::SB_DAY);
			}
		}

		if (scene_change) //skybox changes when scene changes
		{
			if (scene != TRIVIA)
			{
				meshList[GEO_FRONT]->textureID = LoadTGA((map.skybox_loc[0]).std::string::c_str());
				meshList[GEO_BACK]->textureID = LoadTGA((map.skybox_loc[1]).std::string::c_str());
				meshList[GEO_LEFT]->textureID = LoadTGA((map.skybox_loc[2]).std::string::c_str());
				meshList[GEO_RIGHT]->textureID = LoadTGA((map.skybox_loc[3]).std::string::c_str());
				meshList[GEO_TOP]->textureID = LoadTGA((map.skybox_loc[4]).std::string::c_str());
				meshList[GEO_BOTTOM]->textureID = LoadTGA((map.skybox_loc[5]).std::string::c_str());
			}

			scene_change = false;
		}

		if (!Application::IsKeyPressed('P') && pausePressed == true)
			pausePressed = false;

		if (Application::IsKeyPressed('P') && pausePressed == false && scene != MAIN_MENU)
		{
			game_pause = true;
			pausePressed = true;
			prePausedScene = scene;
		}
	}
}

void SceneMaster::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();

	if (scene == DRIVING)
		viewStack.LookAt(camera_driving.position.x, camera_driving.position.y, camera_driving.position.z, camera_driving.target.x, camera_driving.target.y, camera_driving.target.z, camera_driving.up.x, camera_driving.up.y, camera_driving.up.z);
	if (scene == TRIVIA)
		viewStack.LookAt(camera_trivia.position.x, camera_trivia.position.y, camera_trivia.position.z, camera_trivia.target.x, camera_trivia.target.y, camera_trivia.target.z, camera_trivia.up.x, camera_trivia.up.y, camera_trivia.up.z);
	if (scene == SEARCH)
		viewStack.LookAt(camera_search->position.x, camera_search->position.y, camera_search->position.z, camera_search->target.x, camera_search->target.y, camera_search->target.z, camera_search->up.x, camera_search->up.y, camera_search->up.z);
	if (scene == SHOP)
		viewStack.LookAt(camera_shop.position.x, camera_shop.position.y, camera_shop.position.z, camera_shop.target.x, camera_shop.target.y, camera_shop.target.z, camera_shop.up.x, camera_shop.up.y, camera_shop.up.z);
	
	modelStack.LoadIdentity();

	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP

	if (scene != MAIN_MENU && scene != PAUSE_MENU)
	{
		RenderSkybox();
	}

	if (scene == MAIN_MENU)
	{
		RenderMeshOnScreen(meshList[GEO_UI], 80, 45, 160, 90);
	}
	else if (scene == PAUSE_MENU)
	{
		RenderMeshOnScreen(meshList[GEO_OVERLAY], 80, 45, 1000, 1000);
		RenderTextOnScreen(meshList[GEO_TEXT], "Paused", Color(1, 0, 0), 8, 53, 82);
	}
	else if (scene == INTRO)
	{

	}
	else if (scene == DRIVING)
	{
		driving->Render();
	}
	else if (scene == TRIVIA)
	{
		RenderRoom();

		modelStack.PushMatrix();
		modelStack.Rotate(180, 0, 1, 0);
		if (qn_num == 0) //Renders the start of trivia mini game menu
		{
			RenderTextOnScreen(meshList[GEO_TEXT], Qn_str + " Trivia", Color(0, 1, 0), 10, 46, 64);
			RenderTextOnScreen(meshList[GEO_TEXT], "Instructions:", Color(.3f, 1, .3f), 5, 58, 55);
			RenderTextOnScreen(meshList[GEO_TEXT], "Use WASD to move to Podium A, B or C", Color(.3f, 1, .3f), 2.5f, 51, 50);
			RenderTextOnScreen(meshList[GEO_TEXT], "Spacebar to select & start", Color(.3f, 1, .3f), 2.5f, 57, 43);
		}
		else if (qn_num <= 10) //Renders the different questions
		{
			RenderTextOnScreen(meshList[GEO_TEXT], (std::to_string(score)) + "/10", Color(0, 1, 0), 6, 110, 76);
			RenderTextOnScreen(meshList[GEO_TEXT], ("Q" + std::to_string(qn_num) + ":" + Qn_str), Color(0, 1, 0), 2.44f, 37, 65);
			RenderTextOnScreen(meshList[GEO_TEXT], ("A:" + dialogue->getChoice1()), Color(0, 1, 0), 4, 40, 57);
			RenderTextOnScreen(meshList[GEO_TEXT], ("B:" + dialogue->getChoice2()), Color(0, 1, 0), 4, 40, 51);
			RenderTextOnScreen(meshList[GEO_TEXT], ("C:" + dialogue->getChoice3()), Color(0, 1, 0), 4, 40, 45);
		}
		else //Renders the final score and outcome of the trivia minigame
		{
			RenderTextOnScreen(meshList[GEO_TEXT], (std::to_string(score) + "/10"), Color(0, 1, 0), 10, 72, 53);
			if (score < 5)
				RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(passengers * -1) + " passengers were unimpressed and left the tour", Color(.3f, 1, .3f), 2.5f, 40, 50);
			else if (score >= 8)
				RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(passengers) + " people were impressed and joined the tour", Color(.3f, 1, .3f), 2.5f, 40, 50);
			else
				RenderTextOnScreen(meshList[GEO_TEXT], "Your passengers slow clap your efforts", Color(.3f, 1, .3f), 2.5f, 40, 50);
		}

		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(goose.GetPositionX(), goose.GetPositionY(), goose.GetPositionZ());
		modelStack.Rotate(goose.GetRotateX(), 1, 0, 0);
		modelStack.Rotate(goose.GetRotateY(), 0, 1, 0);
		modelStack.Rotate(goose.GetRotateZ(), 0, 0, 1);
		RenderMesh(meshList[GEO_GOOSE_TRIVIA], true);
		modelStack.PopMatrix();

		if ((qn_num > 10) && (score >= 8))
			RenderMeshOnScreen(meshList[GEO_CONFETTI_TRIVIA], 80, 45, 1, 1);
	}
	else if (scene == SEARCH)
	{
		RenderCity();

		if (game_start)
		{
			RenderMeshOnScreen(meshList[GEO_TARGET_SEARCH], 80, 45, 10, 10);

			//bar_type (sets up the progress bar depending on the player's progress percentage)
			std::string bar_type = "Assets//progress_" + std::to_string(camera_search->progress) + ".tga";
			meshList[GEO_PROGRESS_SEARCH]->textureID = LoadTGA(bar_type.std::string::c_str());
			RenderMeshOnScreen(meshList[GEO_PROGRESS_SEARCH], 80, 35, 20, 5);

			std::ostringstream ss;
			ss.precision(3);
			ss << "Time left:" << (timer_search / 3600) << "m " << (timer_search % 3600) / 60 << "s";
			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0), 3, 5, 85);
			RenderTextOnScreen(meshList[GEO_TEXT], "Passengers found:" + std::to_string(passenger_count), Color(0, 0, 0), 3, 5, 80);
		}
		else
		{ //Renders the Intructions
			RenderMeshOnScreen(meshList[GEO_POPUP_SEARCH], 80, 45, 120, 60);
		}

		if (timer_search <= 0)
		{//Renders the final results of the Search Minigame
			meshList[GEO_POPUP_SEARCH]->textureID = LoadTGA("Assets//search_results.tga");
			RenderMeshOnScreen(meshList[GEO_POPUP_SEARCH], 80, 45, 120, 60);
			if (passenger_count > 0)
				RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(passenger_count) + " passenger(s) joined the rest of the tour!", Color(0, 0, 0), 4, 30, 45);
			else
				RenderTextOnScreen(meshList[GEO_TEXT], "You could not find anyone to join the tour.", Color(0, 0, 0), 4, 30, 45);
		}
	}
	else if (scene == SHOP)
	{
		//render model
		modelStack.PushMatrix();
		modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.07f, 0.07f, 0.07f);
		RenderMesh(meshList[GEO_BUS_SHOP], true);
		modelStack.PopMatrix();

		//render UI
		if (displayShopUI0)
		{
			RenderMeshOnScreen(meshList[GEO_UI], 80, 15, 130, 30);
			if (shop.getUpgradeLevel(0) < 5)
				RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(shop.getUpgradeCost(0)), Color(0, 0, 0), 3, 68, 15.2f);

			if (displayMessage)
			{
				if (shop.getUpgradeLevel(0) == 5)
					RenderTextOnScreen(meshList[GEO_TEXT], "Max upgrades reached!", Color(1, 1, 1), 3, 55, 50);
				else
					RenderTextOnScreen(meshList[GEO_TEXT], "Not enough money!", Color(1, 1, 1), 3, 55, 50);
			}
		}
		if (displayShopUI1)
		{
			RenderMeshOnScreen(meshList[GEO_UI], 80, 15, 130, 30);
			if (shop.getUpgradeLevel(1) < 5)
				RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(shop.getUpgradeCost(1)), Color(0, 0, 0), 3, 68, 15.2f);

			if (displayMessage)
			{
				if (shop.getUpgradeLevel(1) == 5)
					RenderTextOnScreen(meshList[GEO_TEXT], "Max upgrades reached!", Color(1, 1, 1), 3, 55, 50);
				else
					RenderTextOnScreen(meshList[GEO_TEXT], "Not enough money!", Color(1, 1, 1), 3, 55, 50);
			}
		}
		if (displayShopUI2)
		{
			RenderMeshOnScreen(meshList[GEO_UI], 80, 15, 130, 30);
			if (shop.getUpgradeLevel(2) < 5)
				RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(shop.getUpgradeCost(2)), Color(0, 0, 0), 3, 68, 15.2f);

			if (displayMessage)
			{
				if (shop.getUpgradeLevel(2) == 5)
					RenderTextOnScreen(meshList[GEO_TEXT], "Max upgrades reached!", Color(1, 1, 1), 3, 55, 50);
				else
					RenderTextOnScreen(meshList[GEO_TEXT], "Not enough money!", Color(1, 1, 1), 3, 55, 50);
			}
		}
	}
}

void SceneMaster::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);

	glDeleteProgram(m_programID);
}

void SceneMaster::Check_Answer()
{
	goose.SetRotateY(180);
	goose.SetPosition(Position(0, 0, -5));

	if (answer == dialogue->getAnswer())
	{
		sound.Engine()->play2D("media/correctAns.ogg");
		score++;
	}
	else
		sound.Engine()->play2D("media/wrongAns.ogg");

	Qn_str = dialogue->Update();
}

void SceneMaster::RenderRoom()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -.1f, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(50, 50, 50);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 12.6f, 23.8f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(50, 25, 25);
	RenderMesh(meshList[GEO_TV_TRIVIA], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(P_A.GetPositionX(), P_A.GetPositionY(), P_A.GetPositionZ());
	modelStack.Scale(1, 1.5f, 1);
	RenderMesh(meshList[GEO_PODIUM_A_TRIVIA], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5.44f, 2.55f, 3.4f);
	modelStack.Rotate(180, 0, 1, 0);
	RenderText(meshList[GEO_TEXT], "A", Color(1, 1, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(P_B.GetPositionX(), P_B.GetPositionY(), P_B.GetPositionZ());
	modelStack.Scale(1, 1.5f, 1);
	RenderMesh(meshList[GEO_PODIUM_B_TRIVIA], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-.30f, 2.55f, 3.4f);
	modelStack.Rotate(180, 0, 1, 0);
	RenderText(meshList[GEO_TEXT], "B", Color(1, 1, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(P_C.GetPositionX(), P_C.GetPositionY(), P_C.GetPositionZ());
	modelStack.Scale(1, 1.5f, 1);
	RenderMesh(meshList[GEO_PODIUM_C_TRIVIA], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5.72f, 2.55f, 3.4f);
	modelStack.Rotate(180, 0, 1, 0);
	RenderText(meshList[GEO_TEXT], "C", Color(1, 1, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-19, 13.4f, 23.3f);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[GEO_LOGO_TRIVIA], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(19, 13.4f, 23.3f);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[GEO_LOGO_TRIVIA], true);
	modelStack.PopMatrix();
}

void SceneMaster::RenderCity()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FLOOR_SEARCH], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 0, 425);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(200, 0, 252);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 0, 260);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(175, 0, 425);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING3_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 0, 425);
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING3_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 0, 150);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(200, 0, 150);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(55, 0, 200);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-160, 0, 410);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING5_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 410);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING5_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-440, 0, 410);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING4_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-160, 0, 280);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING4_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 280);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING4_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-440, 0, 280);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING5_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-140, 0, 170);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING4_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-30, 0, 400);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BUSSTOP_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-390, -44, 5);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(.15, .15, .15);
	RenderMesh(meshList[GEO_MALL_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 230);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 100);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 50);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, -50);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, -100);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, -150);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 300);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-220, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-345, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-50, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(55, 0, 300);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BUSSTOP_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(75, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(75, 0, 255);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100, 0, 170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(275, 0, 170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, 0, 170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1_SEARCH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20, 0, -175);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(65, 10, 10);
	RenderMesh(meshList[GEO_BUSSTOP_SEARCH], true);
	modelStack.PopMatrix();
}

void SceneMaster::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneMaster::RenderSkybox()
{
	if (scene == DRIVING)
	{
		modelStack.PushMatrix();
		modelStack.Translate(499, 0, 0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_FRONT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-499, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_BACK], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 499);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_LEFT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -499);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_RIGHT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -499, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_BOTTOM], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 499, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_TOP], false);
		modelStack.PopMatrix();
	}
	else if (scene == TRIVIA)
	{
		modelStack.PushMatrix();
		modelStack.Translate(24, 0, 0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_FRONT_TRIVIA], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-24, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_BACK_TRIVIA], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 24);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_LEFT_TRIVIA], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -24);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_RIGHT_TRIVIA], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -24, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_BOTTOM_TRIVIA], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 24, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_TOP_TRIVIA], true);
		modelStack.PopMatrix();
	}
	else if (scene == SEARCH)
	{
		modelStack.PushMatrix();
		modelStack.Translate(499, 0, 0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_FRONT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-499, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_BACK], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 499);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_LEFT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -499);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_RIGHT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -499, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_BOTTOM], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 499, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_TOP], false);
		modelStack.PopMatrix();
	}
	else if (scene == SHOP)
	{
		modelStack.PushMatrix();
		modelStack.Translate(18.99f, 4.99f, 0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(17, 10, 20);
		RenderMesh(meshList[GEO_FRONT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-18.99f, 4.99f, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(17, 10, 38);
		RenderMesh(meshList[GEO_BACK], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 4.99f, 8.49f);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(38, 10, 17);
		RenderMesh(meshList[GEO_LEFT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 4.99f, -8.49f);
		modelStack.Scale(38, 10, 17);
		RenderMesh(meshList[GEO_RIGHT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(38, 17, 38);
		RenderMesh(meshList[GEO_BOTTOM], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 10, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(38, 17, 38);
		RenderMesh(meshList[GEO_TOP], false);
		modelStack.PopMatrix();
	}
}

void SceneMaster::RenderText(Mesh* mesh, std::string text, Color color)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneMaster::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, UI_width, 0, UI_height, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i * 1.0f, 0.5f, 0);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneMaster::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, UI_width, 0, UI_height, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}