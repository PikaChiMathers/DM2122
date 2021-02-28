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

	//driving meshes
	{
		meshList[GEO_TEST_DRIVING] = MeshBuilder::GenerateOBJ("test", "OBJ//bus.obj", Color(1, 0, 0));

		meshList[GEO_TEMPLATE_DRIVING] = MeshBuilder::GenerateQuad("template", Color(1, 1, 1), 1.f, 1.f);
		meshList[GEO_TEMPLATE_DRIVING]->textureID = LoadTGA("Image//map_template.tga");

		meshList[GEO_BORDER_DRIVING] = MeshBuilder::GenerateQuad("border", Color(1, 1, 1), 1.f, 1.f);
		meshList[GEO_BORDER_DRIVING]->textureID = LoadTGA("Image//border.tga");

		meshList[GEO_OVERLAY_DRIVING] = MeshBuilder::GenerateRevQuad("overlay", Color(1, 1, 1), 1.f, 1.f);
		meshList[GEO_OVERLAY_DRIVING]->textureID = LoadTGA("Image//overlay.tga");

		meshList[GEO_CUBE_DRIVING] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 1, 1, 1);
		meshList[GEO_CUBE_DRIVING]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_CUBE_DRIVING]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
		meshList[GEO_CUBE_DRIVING]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
		meshList[GEO_CUBE_DRIVING]->material.kShininess = 1.f;

		meshList[GEO_COIN_DRIVING] = MeshBuilder::GenerateOBJMTL("coin", "OBJ//coin.obj", "OBJ//coin.mtl");
		meshList[GEO_COIN_DRIVING]->textureID = LoadTGA("Image//coin.tga");

		meshList[GEO_NPC_DRIVING] = MeshBuilder::GenerateOBJ("npc", "OBJ//among_us.obj", Color(.2, .9, .6));

		meshList[GEO_BUILDING1_DRIVING] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//short_apartment.obj", "OBJ//short_apartment.mtl");
		meshList[GEO_BUILDING1_DRIVING]->textureID = LoadTGA("Image//apartment.tga");
		meshList[GEO_BUILDING2_DRIVING] = MeshBuilder::GenerateOBJMTL("building2", "OBJ//med_apartment.obj", "OBJ//med_apartment.mtl");
		meshList[GEO_BUILDING2_DRIVING]->textureID = LoadTGA("Image//apartment.tga");
		meshList[GEO_BUILDING3_DRIVING] = MeshBuilder::GenerateOBJMTL("building3", "OBJ//tall_apartment.obj", "OBJ//tall_apartment.mtl");
		meshList[GEO_BUILDING3_DRIVING]->textureID = LoadTGA("Image//apartment.tga");
		meshList[GEO_BUILDING1B_DRIVING] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//short_apartment.obj", "OBJ//short_apartment.mtl");
		meshList[GEO_BUILDING1B_DRIVING]->textureID = LoadTGA("Image//house2.tga");
		meshList[GEO_BUILDING2B_DRIVING] = MeshBuilder::GenerateOBJMTL("building2", "OBJ//med_apartment.obj", "OBJ//med_apartment.mtl");
		meshList[GEO_BUILDING2B_DRIVING]->textureID = LoadTGA("Image//house2.tga");
		meshList[GEO_BUILDING3B_DRIVING] = MeshBuilder::GenerateOBJMTL("building3", "OBJ//tall_apartment.obj", "OBJ//tall_apartment.mtl");
		meshList[GEO_BUILDING3B_DRIVING]->textureID = LoadTGA("Image//house2.tga");
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
		camera_driving.Init(&bus, Vector3(0, 1, 0));

		bus.SetPosition(Position(63, 0, 40));
		manager_driving.CreateGameObject(&bus);
		endpoint.SetPosition(Position(62.4, 0, 68.7));
		endpoint.SetRotateY(81);
		endpoint.SetScale(Scale(45, 1, 13));
		endpoint.SetPlayer(&bus);
		manager_driving.CreateGameObject(&endpoint);
		cluster[0] = new ColliderObj;
		cluster[0]->SetPosition(Position(-46.2519, 0, -79.7891));
		cluster[0]->SetScale(Scale(23, 1, 34.5f));
		cluster[0]->SetTag("Type5");
		manager_driving.CreateGameObject(cluster[0]);
		cluster[1] = new ColliderObj;
		cluster[1]->SetPosition(Position(-122.5, 0, -120.3));
		cluster[1]->SetScale(Scale(23, 1, 23));
		cluster[1]->SetTag("Type6");
		manager_driving.CreateGameObject(cluster[1]);
		cluster[2] = new ColliderObj;
		cluster[2]->SetPosition(Position(-42.929, 0, -45.03));
		cluster[2]->SetRotateY(-90);
		cluster[2]->SetScale(Scale(11.5f, 1, 23));
		cluster[2]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[2]);
		cluster[3] = new ColliderObj;
		cluster[3]->SetPosition(Position(-41.1, 0, -13.18));
		cluster[3]->SetScale(Scale(23, 1, 23));
		cluster[3]->SetTag("Type8");
		manager_driving.CreateGameObject(cluster[3]);
		cluster[4] = new ColliderObj;
		cluster[4]->SetPosition(Position(-39.92, 0, 23.2));
		cluster[4]->SetRotateY(-90);
		cluster[4]->SetScale(Scale(23, 1, 34.5));
		cluster[4]->SetTag("Type5");
		manager_driving.CreateGameObject(cluster[4]);
		cluster[5] = new ColliderObj;
		cluster[5]->SetPosition(Position(-123.15, 0, 22.24));
		cluster[5]->SetScale(Scale(23, 1, 23));
		cluster[5]->SetTag("Type6");
		manager_driving.CreateGameObject(cluster[5]);
		cluster[6] = new ColliderObj;
		cluster[6]->SetPosition(Position(-122.87, 0, -13.5));
		cluster[6]->SetRotateY(180);
		cluster[6]->SetScale(Scale(23, 1, 23));
		cluster[6]->SetTag("Type7");
		manager_driving.CreateGameObject(cluster[6]);
		cluster[7] = new ColliderObj;
		cluster[7]->SetPosition(Position(106.76, 0, 35.54));
		cluster[7]->SetRotateY(-23.5);
		cluster[7]->SetScale(Scale(23, 1, 23));
		cluster[7]->SetTag("Type8");
		manager_driving.CreateGameObject(cluster[7]);
		cluster[8] = new ColliderObj;
		cluster[8]->SetPosition(Position(-47.537, 0, -121.438));
		cluster[8]->SetRotateY(180);
		cluster[8]->SetScale(Scale(23, 1, 23));
		cluster[8]->SetTag("Type8");
		manager_driving.CreateGameObject(cluster[8]);
		cluster[9] = new ColliderObj;
		cluster[9]->SetPosition(Position(-83.786, 0, -12.705));
		cluster[9]->SetRotateY(90);
		cluster[9]->SetScale(Scale(23, 1, 34.5));
		cluster[9]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[9]);
		cluster[10] = new ColliderObj;
		cluster[10]->SetPosition(Position(-123.421, 0, 135.403));
		cluster[10]->SetRotateY(90);
		cluster[10]->SetScale(Scale(11.5, 1, 23));
		cluster[10]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[10]);
		cluster[11] = new ColliderObj;
		cluster[11]->SetPosition(Position(-122.97, 0, 111.517));
		cluster[11]->SetRotateY(180);
		cluster[11]->SetScale(Scale(23, 1, 34.5));
		cluster[11]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[11]);
		cluster[12] = new ColliderObj;
		cluster[12]->SetPosition(Position(-124.252, 0, 71.04));
		cluster[12]->SetRotateY(180);
		cluster[12]->SetScale(Scale(23, 1, 23));
		cluster[12]->SetTag("Type7");
		manager_driving.CreateGameObject(cluster[12]);
		cluster[13] = new ColliderObj;
		cluster[13]->SetPosition(Position(-124.233, 0, 53.178));
		cluster[13]->SetRotateY(90);
		cluster[13]->SetScale(Scale(11.5, 1, 23));
		cluster[13]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[13]);
		cluster[14] = new ColliderObj;
		cluster[14]->SetPosition(Position(-123.803, 0, -45.587));
		cluster[14]->SetRotateY(-90);
		cluster[14]->SetScale(Scale(11.5, 1, 23));
		cluster[14]->SetTag("Type2");
		manager_driving.CreateGameObject(cluster[14]);
		cluster[15] = new ColliderObj;
		cluster[15]->SetPosition(Position(-122.923, 0, -78.824));
		cluster[15]->SetRotateY(-90);
		cluster[15]->SetScale(Scale(23, 1, 23));
		cluster[15]->SetTag("Type7");
		manager_driving.CreateGameObject(cluster[15]);
		cluster[16] = new ColliderObj;
		cluster[16]->SetPosition(Position(-84.1958, 0, -130.384));
		cluster[16]->SetRotateY(90);
		cluster[16]->SetScale(Scale(23, 1, 34.5));
		cluster[16]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[16]);
		cluster[17] = new ColliderObj;
		cluster[17]->SetPosition(Position(-80.799, 0, -79.205));
		cluster[17]->SetRotateY(180);
		cluster[17]->SetScale(Scale(23, 1, 34.5));
		cluster[17]->SetTag("Type5");
		manager_driving.CreateGameObject(cluster[17]);
		cluster[18] = new ColliderObj;
		cluster[18]->SetPosition(Position(-83.377, 0, -45.077));
		cluster[18]->SetRotateY(270);
		cluster[18]->SetScale(Scale(11.5, 1, 23));
		cluster[18]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[18]);
		cluster[19] = new ColliderObj;
		cluster[19]->SetPosition(Position(-82.5234, 0, 22.9695));
		cluster[19]->SetRotateY(270);
		cluster[19]->SetScale(Scale(23, 1, 34.5));
		cluster[19]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[19]);
		cluster[20] = new ColliderObj;
		cluster[20]->SetPosition(Position(-82.135, 0, 76.2388));
		cluster[20]->SetRotateY(270);
		cluster[20]->SetScale(Scale(11.5, 1, 23));
		cluster[20]->SetTag("Type1");
		manager_driving.CreateGameObject(cluster[20]);
		cluster[21] = new ColliderObj;
		cluster[21]->SetPosition(Position(-79.5776, 0, 57.9134));
		cluster[21]->SetRotateY(90);
		cluster[21]->SetScale(Scale(23, 1, 23));
		cluster[21]->SetTag("Type7");
		manager_driving.CreateGameObject(cluster[21]);
		cluster[22] = new ColliderObj;
		cluster[22]->SetPosition(Position(-86.833, 0, 107.758));
		cluster[22]->SetRotateY(90);
		cluster[22]->SetScale(Scale(23, 1, 23));
		cluster[22]->SetTag("Type7");
		manager_driving.CreateGameObject(cluster[22]);
		cluster[23] = new ColliderObj;
		cluster[23]->SetPosition(Position(-83.01, 0, 130.354));
		cluster[23]->SetRotateY(90);
		cluster[23]->SetScale(Scale(11.5, 1, 23));
		cluster[23]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[23]);
		cluster[24] = new ColliderObj;
		cluster[24]->SetPosition(Position(-47.9536, 0, 114.564));
		cluster[24]->SetRotateY(180);
		cluster[24]->SetScale(Scale(23, 1, 34.5));
		cluster[24]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[24]);
		cluster[25] = new ColliderObj;
		cluster[25]->SetPosition(Position(-47.9536, 0, 136.763));
		cluster[25]->SetRotateY(-270);
		cluster[25]->SetScale(Scale(11.5, 1, 23));
		cluster[25]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[25]);
		cluster[26] = new ColliderObj;
		cluster[26]->SetPosition(Position(-25.430, 0, 125.748));
		cluster[26]->SetRotateY(90);
		cluster[26]->SetScale(Scale(23, 1, 23));
		cluster[26]->SetTag("Type7");
		manager_driving.CreateGameObject(cluster[26]);
		cluster[27] = new ColliderObj;
		cluster[27]->SetPosition(Position(-26.692, 0, 103.604));
		cluster[27]->SetRotateY(90);
		cluster[27]->SetScale(Scale(11.5, 1, 23));
		cluster[27]->SetTag("Type1");
		manager_driving.CreateGameObject(cluster[27]);
		cluster[28] = new ColliderObj;
		cluster[28]->SetPosition(Position(-49.2745, 0, 69.097));
		cluster[28]->SetRotateY(0);
		cluster[28]->SetScale(Scale(11.5, 1, 23));
		cluster[28]->SetTag("Type1");
		manager_driving.CreateGameObject(cluster[28]);
		cluster[29] = new ColliderObj;
		cluster[29]->SetPosition(Position(-27.1164, 0, 71.240));
		cluster[29]->SetRotateY(-90);
		cluster[29]->SetScale(Scale(23, 1, 34.5));
		cluster[29]->SetTag("Type5");
		manager_driving.CreateGameObject(cluster[29]);
		cluster[30] = new ColliderObj;
		cluster[30]->SetPosition(Position(26.4525, 0, 44.7866));
		cluster[30]->SetRotateY(217.309);
		cluster[30]->SetScale(Scale(23, 1, 34.5));
		cluster[30]->SetTag("Type5");
		manager_driving.CreateGameObject(cluster[30]);
		cluster[31] = new ColliderObj;
		cluster[31]->SetPosition(Position(2.1104, 0, 14.127));
		cluster[31]->SetRotateY(-78.8068);
		cluster[31]->SetScale(Scale(11.5, 1, 23));
		cluster[31]->SetTag("Type2");
		manager_driving.CreateGameObject(cluster[31]);
		cluster[32] = new ColliderObj;
		cluster[32]->SetPosition(Position(-10.9397, 0, -125.9913));
		cluster[32]->SetRotateY(180);
		cluster[32]->SetScale(Scale(23, 1, 34.5));
		cluster[32]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[32]);
		cluster[33] = new ColliderObj;
		cluster[33]->SetPosition(Position(-19.1237, 0, -76.1837));
		cluster[33]->SetRotateY(0);
		cluster[33]->SetScale(Scale(11.5, 1, 23));
		cluster[33]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[33]);
		cluster[34] = new ColliderObj;
		cluster[34]->SetPosition(Position(21.4181, 0, 130.1077));
		cluster[34]->SetRotateY(-90);
		cluster[34]->SetScale(Scale(23, 1, 34.5));
		cluster[34]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[34]);
		cluster[35] = new ColliderObj;
		cluster[35]->SetPosition(Position(21.41817, 0, 108.3904));
		cluster[35]->SetRotateY(90);
		cluster[35]->SetScale(Scale(23, 1, 34.5));
		cluster[35]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[35]);
		cluster[36] = new ColliderObj;
		cluster[36]->SetPosition(Position(62.7545, 0, 124.217));
		cluster[36]->SetRotateY(90);
		cluster[36]->SetScale(Scale(23, 1, 23));
		cluster[36]->SetTag("Type7");
		manager_driving.CreateGameObject(cluster[36]);
		cluster[37] = new ColliderObj;
		cluster[37]->SetPosition(Position(111.78678, 0, 129.3267));
		cluster[37]->SetRotateY(90);
		cluster[37]->SetScale(Scale(23, 1, 34.5));
		cluster[37]->SetTag("Type5");
		manager_driving.CreateGameObject(cluster[37]);
		cluster[38] = new ColliderObj;
		cluster[38]->SetPosition(Position(62.82099, 0, 95.6409));
		cluster[38]->SetRotateY(262.404);
		cluster[38]->SetScale(Scale(11.5, 1, 23));
		cluster[38]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[38]);
		cluster[39] = new ColliderObj;
		cluster[39]->SetPosition(Position(71.7895, 0, 80.32));
		cluster[39]->SetRotateY(352.404);
		cluster[39]->SetScale(Scale(11.5, 1, 23));
		cluster[39]->SetTag("Type3");
		manager_driving.CreateGameObject(cluster[39]);
		cluster[40] = new ColliderObj;
		cluster[40]->SetPosition(Position(76.498299, 0, 58.5145));
		cluster[40]->SetRotateY(352.404);
		cluster[40]->SetScale(Scale(11.5, 1, 23));
		cluster[40]->SetTag("Type2");
		manager_driving.CreateGameObject(cluster[40]);
		cluster[41] = new ColliderObj;
		cluster[41]->SetPosition(Position(117.82504, 0, -0.24954));
		cluster[41]->SetRotateY(274.70874);
		cluster[41]->SetScale(Scale(23, 1, 23));
		cluster[41]->SetTag("Type7");
		manager_driving.CreateGameObject(cluster[41]);
		cluster[42] = new ColliderObj;
		cluster[42]->SetPosition(Position(26.7506, 0, -126.4129));
		cluster[42]->SetRotateY(180);
		cluster[42]->SetScale(Scale(23, 1, 34.5));
		cluster[42]->SetTag("Type4");
		manager_driving.CreateGameObject(cluster[42]);
		cluster[43] = new ColliderObj;
		cluster[43]->SetPosition(Position(65.074, 0, -132.3670));
		cluster[43]->SetRotateY(-270);
		cluster[43]->SetScale(Scale(11.5, 1, 23));
		cluster[43]->SetTag("Type2");
		manager_driving.CreateGameObject(cluster[43]);
		cluster[44] = new ColliderObj;
		cluster[44]->SetPosition(Position(105.1129, 0, -134.954));
		cluster[44]->SetRotateY(90);
		cluster[44]->SetScale(Scale(11.5, 1, 23));
		cluster[44]->SetTag("Type1");
		manager_driving.CreateGameObject(cluster[44]);
		cluster[45] = new ColliderObj;
		cluster[45]->SetPosition(Position(125.6322, 0, -27.1762));
		cluster[45]->SetRotateY(97.209);
		cluster[45]->SetScale(Scale(11.5, 1, 23));
		cluster[45]->SetTag("Type1");
		manager_driving.CreateGameObject(cluster[45]);
		cluster[46] = new ColliderObj;
		cluster[46]->SetPosition(Position(17.3438, 0, -58.9819));
		cluster[46]->SetRotateY(236.355);
		cluster[46]->SetScale(Scale(23, 1, 34.5));
		cluster[46]->SetTag("Type5");
		manager_driving.CreateGameObject(cluster[46]);
		cluster[47] = new ColliderObj;
		cluster[47]->SetPosition(Position(60.851799, 0, -81.5723));
		cluster[47]->SetRotateY(211.29794);
		cluster[47]->SetScale(Scale(23, 1, 34.5));
		cluster[47]->SetTag("Type5");
		manager_driving.CreateGameObject(cluster[47]);
		cluster[48] = new ColliderObj;
		cluster[48]->SetPosition(Position(77.3685, 0, -60.651939));
		cluster[48]->SetRotateY(211.29794);
		cluster[48]->SetScale(Scale(23, 1, 23));
		cluster[48]->SetTag("Type6");
		manager_driving.CreateGameObject(cluster[48]);
		cluster[49] = new ColliderObj;
		cluster[49]->SetPosition(Position(104.776, 0, -61.1024));
		cluster[49]->SetRotateY(121.297);
		cluster[49]->SetScale(Scale(23, 1, 23));
		cluster[49]->SetTag("Type6");
		manager_driving.CreateGameObject(cluster[49]);
		cluster[50] = new ColliderObj;
		cluster[50]->SetPosition(Position(87.690628, 0, -78.13084));
		cluster[50]->SetRotateY(45);
		cluster[50]->SetScale(Scale(11.5, 1, 23));
		cluster[50]->SetTag("Type2");
		manager_driving.CreateGameObject(cluster[50]);
		border[0] = new Border;
		border[0]->SetPosition(Position(0, 5, -150));
		border[0]->SetScale(Scale(300, 20, 80));
		manager_driving.CreateGameObject(border[0]);
		borderCol[0] = new ColliderObj;
		borderCol[0]->SetPosition(Position(0, 0, -160));
		borderCol[0]->SetScale(Scale(300, 20, 20));
		manager_driving.CreateGameObject(borderCol[0]);
		border[1] = new Border;
		border[1]->SetPosition(Position(0, 5, 150));
		border[1]->SetRotateY(180);
		border[1]->SetScale(Scale(300, 20, 80));
		manager_driving.CreateGameObject(border[1]);
		borderCol[1] = new ColliderObj;
		borderCol[1]->SetPosition(Position(0, 0, 160));
		borderCol[1]->SetScale(Scale(300, 20, 20));
		manager_driving.CreateGameObject(borderCol[1]);
		border[2] = new Border;
		border[2]->SetPosition(Position(-150, 5, 0));
		border[2]->SetRotateY(90);
		border[2]->SetScale(Scale(300, 20, 80));
		manager_driving.CreateGameObject(border[2]);
		borderCol[2] = new ColliderObj;
		borderCol[2]->SetPosition(Position(-160, 0, 0));
		borderCol[2]->SetRotateY(90);
		borderCol[2]->SetScale(Scale(300, 20, 20));
		manager_driving.CreateGameObject(borderCol[2]);
		border[3] = new Border;
		border[3]->SetPosition(Position(150, 5, 0));
		border[3]->SetRotateY(-90);
		border[3]->SetScale(Scale(300, 20, 80));
		manager_driving.CreateGameObject(border[3]);
		borderCol[3] = new ColliderObj;
		borderCol[3]->SetPosition(Position(160, 0, 0));
		borderCol[3]->SetRotateY(90);
		borderCol[3]->SetScale(Scale(300, 20, 20));
		manager_driving.CreateGameObject(borderCol[3]);
		for (int i = 0; i < sizeof(coins) / sizeof(*coins); i++)
		{
			coins[i] = new Money;
			coins[i]->SetPlayer(&bus);
			coins[i]->SetValue(50);
			coins[i]->SetScale(Scale(3.5f, 3.5f, 3.5f));
			manager_driving.CreateGameObject(coins[i]);
		}
		coins[0]->SetPosition(Position(61.7, 0, -6.2));
		coins[1]->SetPosition(Position(70.6, 0, -40.4));
		coins[2]->SetPosition(Position(94.6, 0, -9.5));
		coins[3]->SetPosition(Position(75.4, 0, 22.4));
		coins[4]->SetPosition(Position(35.5, 0, 13.8));
		coins[5]->SetPosition(Position(30.5, 0, -18.1));
		coins[6]->SetPosition(Position(84.6, 0, 100.6));
		coins[7]->SetPosition(Position(103, 0, 73.1));
		coins[8]->SetPosition(Position(124.8, 0, 53.8));
		coins[9]->SetPosition(Position(138.5, 0, 24.9));
		coins[10]->SetPosition(Position(145.8, 0, -12.1));
		coins[11]->SetPosition(Position(134.5, 0, -49.6));
		coins[12]->SetPosition(Position(114, 0, -75.1));
		coins[13]->SetPosition(Position(97.5, 0, -91.2));
		coins[14]->SetPosition(Position(80.7, 0, -110));
		coins[15]->SetPosition(Position(136.1, 0, -120));
		coins[16]->SetPosition(Position(46.4, 0, -108));
		coins[17]->SetPosition(Position(7.9, 0, -102.8));
		coins[18]->SetPosition(Position(-27.7, 0, -102.8));
		coins[19]->SetPosition(Position(-60.9, 0, -102.8));
		coins[20]->SetPosition(Position(-103.1, 0, -102.8));
		coins[21]->SetPosition(Position(-60.9, 0, -58));
		coins[22]->SetPosition(Position(-103.1, 0, -58));
		coins[23]->SetPosition(Position(-60.9, 0, -31));
		coins[24]->SetPosition(Position(-103.1, 0, -31));
		coins[25]->SetPosition(Position(-60.9, 0, 5));
		coins[26]->SetPosition(Position(-103.1, 0, 5));
		coins[27]->SetPosition(Position(-60.9, 0, 41));
		coins[28]->SetPosition(Position(-103.1, 0, 41));
		coins[29]->SetPosition(Position(-60.9, 0, 89));
		coins[30]->SetPosition(Position(-103.1, 0, 89));
		coins[31]->SetPosition(Position(44.5, 0, 106.5));
		coins[32]->SetPosition(Position(136, 0, 106.5));
		coins[33]->SetPosition(Position(-9.3, 0, -58.5));
		coins[34]->SetPosition(Position(-18.6, 0, -28.5));
		coins[35]->SetPosition(Position(-19.4, 0, 4));
		coins[36]->SetPosition(Position(-11.7, 0, 37.2));
		coins[37]->SetPosition(Position(-0.5, 0, 90));

		npcSpawn[0] = Position(-64, 0, 123);
		npcSpawn[1] = Position(-64, 0, 63);
		npcSpawn[2] = Position(-64, 0, 19);
		npcSpawn[3] = Position(-64, 0, -15);
		npcSpawn[4] = Position(-64, 0, -80);
		npcSpawn[5] = Position(-64, 0, -126);
		npcSpawn[6] = Position(-121, 0, 89);
		npcSpawn[7] = Position(-85, 0, 39);
		npcSpawn[8] = Position(-85, 0, -57);
		npcSpawn[9] = Position(-7, 0, -88);
		npcSpawn[10] = Position(103, 0, 52);
		npcSpawn[11] = Position(106, 0, 100);
		npcSpawn[12] = Position(-10, 0, 103);
		npcSpawn[13] = Position(39, 0, 32);
		npcSpawn[14] = Position(-26, 0, -43);
		for (int i = 0; i < sizeof(npc) / sizeof(*npc); i++)
		{
			npc[i] = new Person;
			npc[i]->SetPosition(npcSpawn[i]);
			npc[i]->SetPlayer(&bus);
			npc[i]->SetScale(Scale(3.5f, 3.5f, 3.5f));
			manager_driving.CreateGameObject(npc[i]);
		}

		TestRef = &bus;

		startGame = endGame = paused = false;
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
		if (scene == DRIVING)
		{
			camera_driving.Update(dt);
			camera_driving.SetChase(&bus);
		}
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
			manager_driving.GameObjectManagerUpdate(dt);

			coinRot += coinRot > 360 ? (180 * dt) - 360 : 180 * dt;

			if (!startGame) // not yet started. show how to play
			{
				if (Application::IsKeyPressed(VK_SPACE))
				{
					// starts the game
					startGame = true;
					endpoint.SetTimer(30);
					endpoint.StartTimer();
				}
			}

			if (endGame)
			{
				// if game ended
				if (Application::IsKeyPressed(VK_SPACE))
				{
					//go to next scene
				}
			}
			else
			{
				// ongoing game
				endGame = (endpoint.GetTime() <= 0); // end game if timer ends
				if (toggleTime > 0) toggleTime -= dt;
			}

			if (Application::IsKeyPressed(VK_SPACE) && honk_count == 1 && !honkerdonker)
			{
				honkerdonker = true;
				sound.Engine()->play2D("media/honk_1.wav");
				honk_count++;
			}

			else if (Application::IsKeyPressed(VK_SPACE) && honk_count == 2 && !honkerdonker)
			{
				honkerdonker = true;
				sound.Engine()->play2D("media/honk_2.wav");
				honk_count++;
			}

			else if (Application::IsKeyPressed(VK_SPACE) && honk_count == 3 && !honkerdonker)
			{
				honkerdonker = true;
				sound.Engine()->play2D("media/honk_3.wav");
				honk_count++;
			}

			else if (Application::IsKeyPressed(VK_SPACE) && honk_count == 4 && !honkerdonker)
			{
				honkerdonker = true;
				sound.Engine()->play2D("media/honk_4.wav");
				honk_count++;
			}

			else if (Application::IsKeyPressed(VK_SPACE) && honk_count == 5 && !honkerdonker)
			{
				honkerdonker = true;
				sound.Engine()->play2D("media/honk_5.wav");
				honk_count = 1;
			}
			else if (!Application::IsKeyPressed(VK_SPACE) && honkerdonker)
			{
				honkerdonker = false;
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

				if (canUpgrade0 == true && money >= shop.getUpgradeCost(0))
				{
					money -= shop.getUpgradeCost(0);
					shop.upgrade(0);
				}
				else if (canUpgrade1 == true && money >= shop.getUpgradeCost(1))
				{
					money -= shop.getUpgradeCost(1);
					shop.upgrade(1);
				}
				else if (canUpgrade2 == true && money >= shop.getUpgradeCost(2))
				{
					money -= shop.getUpgradeCost(2);
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
		modelStack.PushMatrix();
		modelStack.Rotate(270, 1, 0, 0);
		modelStack.Scale(300, 300, 1);
		RenderMesh(meshList[GEO_TEMPLATE_DRIVING], true);
		modelStack.PopMatrix();

		std::vector<GameObject*>GOList = manager_driving.GetGameObjectList();
		for (std::vector<GameObject*>::iterator it = GOList.begin(); it != GOList.end(); it++)
		{
			GameObject* gameObject = (*it);
			modelStack.PushMatrix();
			modelStack.Translate(gameObject->GetPositionX(), gameObject->GetPositionY(), gameObject->GetPositionZ());
			modelStack.Rotate(gameObject->GetRotateX(), 1, 0, 0);
			modelStack.Rotate(gameObject->GetRotateY(), 0, 1, 0);
			modelStack.Rotate(gameObject->GetRotateZ(), 0, 0, 1);
			modelStack.PushMatrix();
			if (gameObject->Type() == "Bus")
			{
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Scale(.03f, .03f, .03f);
				RenderMesh(meshList[GEO_TEST_DRIVING], true);
			}
			else if (gameObject->Type() == "ColliderObj")
			{
				if (abs((Vector3(gameObject->GetPositionX(), gameObject->GetPositionY(), gameObject->GetPositionZ()) - Vector3(bus.GetPositionX(), bus.GetPositionY(), bus.GetPositionZ())).Length()) > 100)
				{
					// dont render if GO is aprox. out of view
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					continue;
				}
				if (gameObject->GetTag() == "Temp")
				{
					modelStack.PushMatrix();
					RenderMesh(meshList[GEO_CUBE_DRIVING], false);
					modelStack.PopMatrix();
				}
				if (gameObject->GetTag() == "Type1")
				{
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING1_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
				}
				if (gameObject->GetTag() == "Type2")
				{
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING2_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
				}
				if (gameObject->GetTag() == "Type3")
				{
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING3_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
				}
				if (gameObject->GetTag() == "Type4")
				{
					modelStack.PushMatrix();
					modelStack.Translate(0, 0, 11.5f);
					modelStack.Rotate(90, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING3_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					modelStack.PushMatrix();
					modelStack.Translate(5.75, 0, -5.75f);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING3_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					modelStack.PushMatrix();
					modelStack.Translate(-5.75, 0, -5.75f);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING2_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
				}
				if (gameObject->GetTag() == "Type5")
				{
					modelStack.PushMatrix();
					modelStack.Translate(0, 0, 11.5f);
					modelStack.Rotate(90, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING3_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					modelStack.PushMatrix();
					modelStack.Translate(5.75, 0, -5.75f);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING2_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					modelStack.PushMatrix();
					modelStack.Translate(-5.75, 0, -5.75f);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING2_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
				}
				if (gameObject->GetTag() == "Type6")
				{
					modelStack.PushMatrix();
					modelStack.Translate(5.75, 0, 0);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING1_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					modelStack.PushMatrix();
					modelStack.Translate(-5.75, 0, 0);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING1_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
				}
				if (gameObject->GetTag() == "Type7")
				{
					modelStack.PushMatrix();
					modelStack.Translate(5.75, 0, 0);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING1_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					modelStack.PushMatrix();
					modelStack.Translate(-5.75, 0, 0);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING2_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
				}
				if (gameObject->GetTag() == "Type8")
				{
					modelStack.PushMatrix();
					modelStack.Translate(5.75, 0, 0);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING2_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					modelStack.PushMatrix();
					modelStack.Translate(-5.75, 0, 0);
					modelStack.Rotate(0, 0, 1, 0);
					modelStack.PushMatrix();
					modelStack.Translate(.85f, 0, .6f);
					RenderMesh(meshList[GEO_BUILDING3_DRIVING], lights[0].isOn);
					modelStack.PopMatrix();
					modelStack.PopMatrix();
				}
			}
			else if (gameObject->Type() == "Border")
			{
				if (gameObject->GetTag() == "Render")
				{
					for (int i = -150; i <= 150; i += 10)
					{
						modelStack.PushMatrix();
						modelStack.Translate(i, 0, 0);
						modelStack.Scale(10, 10, 10);
						RenderMesh(meshList[GEO_BORDER_DRIVING], false);
						modelStack.PopMatrix();
					}
				}
			}
			else if (gameObject->Type() == "Money")
			{
				if (abs((Vector3(gameObject->GetPositionX(), gameObject->GetPositionY(), gameObject->GetPositionZ()) - Vector3(bus.GetPositionX(), bus.GetPositionY(), bus.GetPositionZ())).Length()) > 100)
				{
					// dont render if GO is aprox. out of view
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					continue;
				}
				modelStack.Scale(10, 10, 10);
				modelStack.Rotate(coinRot, 0, 1, 0);
				RenderMesh(meshList[GEO_COIN_DRIVING], true);
			}
			else if (gameObject->Type() == "Person")
			{
				if (abs((Vector3(gameObject->GetPositionX(), gameObject->GetPositionY(), gameObject->GetPositionZ()) - Vector3(bus.GetPositionX(), bus.GetPositionY(), bus.GetPositionZ())).Length()) > 100)
				{
					// dont render if GO is aprox. out of view
					modelStack.PopMatrix();
					modelStack.PopMatrix();
					continue;
				}
				modelStack.Scale(.03f, .03f, .03f);
				RenderMesh(meshList[GEO_NPC_DRIVING], true);
			}
			modelStack.PopMatrix();
			modelStack.Scale(gameObject->GetScaleX(), gameObject->GetScaleY(), gameObject->GetScaleZ());
			if (toggleHitBox) RenderMesh(meshList[GEO_CUBE_DRIVING], false); // hitbox
			modelStack.PopMatrix();
		}

		std::ostringstream ss;
		ss.precision(5);
		ss << "FPS: " << fps;

		if (endGame)
		{
			RenderMeshOnScreen(meshList[GEO_OVERLAY_DRIVING], 80, 45, 1000, 1000);
			RenderTextOnScreen(meshList[GEO_TEXT], "Times Up", Color(1, 0, 0), 8, 50, 82);
			RenderTextOnScreen(meshList[GEO_TEXT], "Passengers:" + std::to_string(bus.GetPassengerCount()), Color(0, 0, 1), 4, 50, 50);
			RenderTextOnScreen(meshList[GEO_TEXT], "Money Collected:" + std::to_string(bus.GetMoneyCurrent()), Color(1, 0, 0), 4, 40, 46);
			RenderTextOnScreen(meshList[GEO_TEXT], "Total Money:" + std::to_string(Bus::GetMoney()), Color(1, 1, 0), 4, 45, 42);

			RenderTextOnScreen(meshList[GEO_TEXT], "Press Space to Continue", Color(1, 0, 0), 7, 0, 0);
		}
		else if (!startGame)
		{
			RenderMeshOnScreen(meshList[GEO_OVERLAY_DRIVING], 80, 45, 1000, 1000);
			RenderTextOnScreen(meshList[GEO_TEXT], "Insert Title", Color(1, 0, 0), 8, 50, 82);
			RenderTextOnScreen(meshList[GEO_TEXT], "Objective: pick up as many passengers", Color(0, 1, 0), 4, 5, 54);
			RenderTextOnScreen(meshList[GEO_TEXT], "as you can before time runs out", Color(0, 1, 0), 4, 20, 50);
			RenderTextOnScreen(meshList[GEO_TEXT], "pick up coins while you're at it", Color(0, 1, 0), 4, 15, 46);
			RenderTextOnScreen(meshList[GEO_TEXT], "W - S: move Foward/Backward", Color(0, 1, .5), 3, 55, 30);
			RenderTextOnScreen(meshList[GEO_TEXT], "A - D: steer", Color(0, 1, .5), 3, 55, 27);
			RenderTextOnScreen(meshList[GEO_TEXT], "Shift: drift", Color(0, 1, .5), 3, 55, 24);

			RenderTextOnScreen(meshList[GEO_TEXT], "Press Space to Begin", Color(1, 0, 0), 8, 0, 0);
		}
		else if (paused)
		{
			RenderMeshOnScreen(meshList[GEO_OVERLAY_DRIVING], 80, 45, 1000, 1000);
			RenderTextOnScreen(meshList[GEO_TEXT], "Paused", Color(1, 0, 0), 8, 53, 82);
			RenderTextOnScreen(meshList[GEO_TEXT], "W - S: move Foward/Backward", Color(0, 1, .5), 3, 55, 30);
			RenderTextOnScreen(meshList[GEO_TEXT], "A - D: steer", Color(0, 1, .5), 3, 55, 27);
			RenderTextOnScreen(meshList[GEO_TEXT], "Shift: drift", Color(0, 1, .5), 3, 55, 24);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, Application::GetWindowHeight() * .1f);
			RenderTextOnScreen(meshList[GEO_TEXT], "Passengers:" + std::to_string(bus.GetPassengerCount()), Color(0, 0, 1), 3, 0, 87);
			RenderTextOnScreen(meshList[GEO_TEXT], "Money Collected:" + std::to_string(bus.GetMoneyCurrent()), Color(1, 0, 0), 3, 0, 84);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(static_cast<int>(endpoint.GetTime())), Color(1, 0, 0), 8, 74, 82);
		}
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
		RenderMesh(meshList[GEO_FRONT], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-24, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_BACK], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 24);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_LEFT], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -24);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_RIGHT], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -24, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_BOTTOM], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 24, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_TOP], true);
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