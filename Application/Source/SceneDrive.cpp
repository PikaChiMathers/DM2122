#define LSPEED 10.f
#include "SceneDrive.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Utility.h"
#include "LoadTGA.h"

#include "Application.h"


SceneDrive::SceneDrive()
{
	honk_count = 1;
	coinRot = 0;
}

SceneDrive::~SceneDrive()
{
}

void SceneDrive::Init() 
{
	//camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0)); //init for camera3
	camera.Init(&bus, Vector3(0, 1, 0)); // init for cameraChase

	map.Set(Maps::SKYBOX_TYPE::SB_DAY);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	scene_change = true;

	UI_width = 160;
	UI_height = 90;

	red.Set(1, 0, 0);
	green.Set(0, 1, 0);
	blue.Set(0, 0, 1);
	pink.Set(1.0f, 0.55f, 0.6f);
	Lblue.Set(0.1f, 0.1f, 1.0f);
	purple.Set(0.6f, 0.5f, 1.0f);
	orange.Set(0.89f, 0.66f, 0.41f);
	yellow.Set(1, 1, 0);
	cyan.Set(0, 1, 1);
	magenta.Set(1, 0, 1);

	moonshade.Set(0.93f, 0.93f, 0.88f);

	meshList[GEO_TEST] = MeshBuilder::GenerateOBJ("test", "OBJ//bus.obj", Color(1, 0, 0));

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Rsphere", red, 30, 30, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", lights[0].color, 30, 30, 1);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("ground", Color(.39f, .39f, .39f), 1.f, 1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_TEMPLATE] = MeshBuilder::GenerateQuad("template", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TEMPLATE]->textureID = LoadTGA("Image//map_template.tga");
	
	meshList[GEO_BORDER] = MeshBuilder::GenerateQuad("border", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//border.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", blue, 1, 1, 1);
	meshList[GEO_CUBE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CUBE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_CUBE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_CUBE]->material.kShininess = 1.f;
	meshList[GEO_CUBE]->textureID = LoadTGA("Image//muscle_capoo.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//trebuchet.tga");

	meshList[GEO_COIN] = MeshBuilder::GenerateOBJMTL("coin", "OBJ//coin.obj", "OBJ//coin.mtl");
	meshList[GEO_COIN]->textureID = LoadTGA("Image//coin.tga");

	meshList[GEO_GOOSE] = MeshBuilder::GenerateOBJ("goose", "OBJ//goose.obj", Color(1 ,1, 1));
	meshList[GEO_PASSPORT] = MeshBuilder::GenerateOBJMTL("passport", "OBJ//passport.obj", "OBJ//passport.mtl");
	meshList[GEO_NPC] = MeshBuilder::GenerateOBJ("npc", "OBJ//among_us.obj", Color(.2, .9, .6));

	meshList[GEO_BUILDING1] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//short_apartment.obj", "OBJ//short_apartment.mtl");
	meshList[GEO_BUILDING1]->textureID = LoadTGA("Image//apartment.tga");
	meshList[GEO_BUILDING2] = MeshBuilder::GenerateOBJMTL("building2", "OBJ//med_apartment.obj", "OBJ//med_apartment.mtl");
	meshList[GEO_BUILDING2]->textureID = LoadTGA("Image//apartment.tga");
	meshList[GEO_BUILDING3] = MeshBuilder::GenerateOBJMTL("building3", "OBJ//tall_apartment.obj", "OBJ//tall_apartment.mtl");
	meshList[GEO_BUILDING3]->textureID = LoadTGA("Image//apartment.tga");
	meshList[GEO_BUILDING1B] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//short_apartment.obj", "OBJ//short_apartment.mtl");
	meshList[GEO_BUILDING1B]->textureID = LoadTGA("Image//house2.tga");
	meshList[GEO_BUILDING2B] = MeshBuilder::GenerateOBJMTL("building2", "OBJ//med_apartment.obj", "OBJ//med_apartment.mtl");
	meshList[GEO_BUILDING2B]->textureID = LoadTGA("Image//house2.tga");
	meshList[GEO_BUILDING3B] = MeshBuilder::GenerateOBJMTL("building3", "OBJ//tall_apartment.obj", "OBJ//tall_apartment.mtl");
	meshList[GEO_BUILDING3B]->textureID = LoadTGA("Image//house2.tga");

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	/*m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Blending.fragmentshader");*/

	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID,
		"MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] =
		glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] =
		glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] =
		glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] =
		glGetUniformLocation(m_programID, "material.kSpecular");
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

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);
	
	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(0, 1000, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 4500;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_SPOT;
	lights[1].position.Set(0, 20, 0);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f, 0.5f, 0.f);

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

	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	/**
	* scaling
	* type 1-3: 11.5,23
	* type 4-5: 23,34.5
	* type 6-8: 23,23
	*/
	bus.SetPosition(Position(63, 0, 40));
	manager.CreateGameObject(&bus);
	endpoint.SetPosition(Position(62.4, 0, 68.7));
	endpoint.SetRotateY(81);
	endpoint.SetScale(Scale(45, 1, 13));
	endpoint.SetPlayer(&bus);
	manager.CreateGameObject(&endpoint);
	cluster[0] = new ColliderObj;
	cluster[0]->SetPosition(Position(-46.2519, 0, -79.7891));
	cluster[0]->SetScale(Scale(23, 1, 34.5f));
	cluster[0]->SetTag("Type5");
	manager.CreateGameObject(cluster[0]);
	cluster[1] = new ColliderObj;
	cluster[1]->SetPosition(Position(-122.5, 0, -120.3));
	cluster[1]->SetScale(Scale(23, 1, 23));
	cluster[1]->SetTag("Type6");
	manager.CreateGameObject(cluster[1]);
	cluster[2] = new ColliderObj;
	cluster[2]->SetPosition(Position(-42.929, 0, -45.03));
	cluster[2]->SetRotateY(-90);
	cluster[2]->SetScale(Scale(11.5f, 1, 23));
	cluster[2]->SetTag("Type3");
	manager.CreateGameObject(cluster[2]);
	cluster[3] = new ColliderObj;
	cluster[3]->SetPosition(Position(-41.1, 0, -13.18));
	cluster[3]->SetScale(Scale(23, 1, 23));
	cluster[3]->SetTag("Type8");
	manager.CreateGameObject(cluster[3]);
	cluster[4] = new ColliderObj;
	cluster[4]->SetPosition(Position(-39.92, 0, 23.2));
	cluster[4]->SetRotateY(-90);
	cluster[4]->SetScale(Scale(23, 1, 34.5));
	cluster[4]->SetTag("Type5");
	manager.CreateGameObject(cluster[4]);
	cluster[5] = new ColliderObj;
	cluster[5]->SetPosition(Position(-123.15, 0, 22.24));
	cluster[5]->SetScale(Scale(23, 1, 23));
	cluster[5]->SetTag("Type6");
	manager.CreateGameObject(cluster[5]);
	cluster[6] = new ColliderObj;
	cluster[6]->SetPosition(Position(-122.87, 0, -13.5));
	cluster[6]->SetRotateY(180);
	cluster[6]->SetScale(Scale(23, 1, 23));
	cluster[6]->SetTag("Type7");
	manager.CreateGameObject(cluster[6]);
	cluster[7] = new ColliderObj;
	cluster[7]->SetPosition(Position(106.76, 0, 35.54));
	cluster[7]->SetRotateY(-23.5);
	cluster[7]->SetScale(Scale(23, 1, 23));
	cluster[7]->SetTag("Type8");
	manager.CreateGameObject(cluster[7]);
	cluster[8] = new ColliderObj;
	cluster[8]->SetPosition(Position(-47.537, 0, -121.438));
	cluster[8]->SetRotateY(180);
	cluster[8]->SetScale(Scale(23, 1, 23));
	cluster[8]->SetTag("Type8");
	manager.CreateGameObject(cluster[8]);
	cluster[9] = new ColliderObj;
	cluster[9]->SetPosition(Position(-83.786, 0, -12.705));
	cluster[9]->SetRotateY(90);
	cluster[9]->SetScale(Scale(23, 1, 34.5));
	cluster[9]->SetTag("Type4");
	manager.CreateGameObject(cluster[9]);
	cluster[10] = new ColliderObj;
	cluster[10]->SetPosition(Position(-123.421, 0, 135.403));
	cluster[10]->SetRotateY(90);
	cluster[10]->SetScale(Scale(11.5, 1, 23));
	cluster[10]->SetTag("Type3");
	manager.CreateGameObject(cluster[10]);
	cluster[11] = new ColliderObj;
	cluster[11]->SetPosition(Position(-122.97, 0, 111.517));
	cluster[11]->SetRotateY(180);
	cluster[11]->SetScale(Scale(23, 1, 34.5));
	cluster[11]->SetTag("Type4");
	manager.CreateGameObject(cluster[11]);
	cluster[12] = new ColliderObj;
	cluster[12]->SetPosition(Position(-124.252, 0, 71.04));
	cluster[12]->SetRotateY(180);
	cluster[12]->SetScale(Scale(23, 1, 23));
	cluster[12]->SetTag("Type7");
	manager.CreateGameObject(cluster[12]);
	cluster[13] = new ColliderObj;
	cluster[13]->SetPosition(Position(-124.233, 0, 53.178));
	cluster[13]->SetRotateY(90);
	cluster[13]->SetScale(Scale(11.5, 1, 23));
	cluster[13]->SetTag("Type3");
	manager.CreateGameObject(cluster[13]);
	cluster[14] = new ColliderObj;
	cluster[14]->SetPosition(Position(-123.803, 0, -45.587));
	cluster[14]->SetRotateY(-90);
	cluster[14]->SetScale(Scale(11.5, 1, 23));
	cluster[14]->SetTag("Type2");
	manager.CreateGameObject(cluster[14]);
	cluster[15] = new ColliderObj;
	cluster[15]->SetPosition(Position(-122.923, 0, -78.824));
	cluster[15]->SetRotateY(-90);
	cluster[15]->SetScale(Scale(23, 1, 23));
	cluster[15]->SetTag("Type7");
	manager.CreateGameObject(cluster[15]);
	cluster[16] = new ColliderObj;
	cluster[16]->SetPosition(Position(-84.1958, 0, -130.384));
	cluster[16]->SetRotateY(90);
	cluster[16]->SetScale(Scale(23, 1, 34.5));
	cluster[16]->SetTag("Type4");
	manager.CreateGameObject(cluster[16]);
	cluster[17] = new ColliderObj;
	cluster[17]->SetPosition(Position(-80.799, 0, -79.205));
	cluster[17]->SetRotateY(180);
	cluster[17]->SetScale(Scale(23, 1, 34.5));
	cluster[17]->SetTag("Type5");
	manager.CreateGameObject(cluster[17]);
	cluster[18] = new ColliderObj;
	cluster[18]->SetPosition(Position(-83.377, 0, -45.077));
	cluster[18]->SetRotateY(270);
	cluster[18]->SetScale(Scale(11.5, 1, 23));
	cluster[18]->SetTag("Type3");
	manager.CreateGameObject(cluster[18]);
	cluster[19] = new ColliderObj;
	cluster[19]->SetPosition(Position(-82.5234, 0, 22.9695));
	cluster[19]->SetRotateY(270);
	cluster[19]->SetScale(Scale(23, 1, 34.5));
	cluster[19]->SetTag("Type4");
	manager.CreateGameObject(cluster[19]);
	cluster[20] = new ColliderObj;
	cluster[20]->SetPosition(Position(-82.135, 0, 76.2388));
	cluster[20]->SetRotateY(270);
	cluster[20]->SetScale(Scale(11.5, 1, 23));
	cluster[20]->SetTag("Type1");
	manager.CreateGameObject(cluster[20]);
	cluster[21] = new ColliderObj;
	cluster[21]->SetPosition(Position(-79.5776, 0, 57.9134));
	cluster[21]->SetRotateY(90);
	cluster[21]->SetScale(Scale(23, 1, 23));
	cluster[21]->SetTag("Type7");
	manager.CreateGameObject(cluster[21]);
	cluster[22] = new ColliderObj;
	cluster[22]->SetPosition(Position(-86.833, 0, 107.758));
	cluster[22]->SetRotateY(90);
	cluster[22]->SetScale(Scale(23, 1, 23));
	cluster[22]->SetTag("Type7");
	manager.CreateGameObject(cluster[22]);
	cluster[23] = new ColliderObj;
	cluster[23]->SetPosition(Position(-83.01, 0, 130.354));
	cluster[23]->SetRotateY(90);
	cluster[23]->SetScale(Scale(11.5, 1, 23));
	cluster[23]->SetTag("Type3");
	manager.CreateGameObject(cluster[23]);
	cluster[24] = new ColliderObj;
	cluster[24]->SetPosition(Position(-47.9536, 0, 114.564));
	cluster[24]->SetRotateY(180);
	cluster[24]->SetScale(Scale(23, 1, 34.5));
	cluster[24]->SetTag("Type4");
	manager.CreateGameObject(cluster[24]);
	cluster[25] = new ColliderObj;
	cluster[25]->SetPosition(Position(-47.9536, 0, 136.763));
	cluster[25]->SetRotateY(-270);
	cluster[25]->SetScale(Scale(11.5, 1, 23));
	cluster[25]->SetTag("Type3");
	manager.CreateGameObject(cluster[25]);
	cluster[26] = new ColliderObj;
	cluster[26]->SetPosition(Position(-25.430, 0, 125.748));
	cluster[26]->SetRotateY(90);
	cluster[26]->SetScale(Scale(23, 1, 23));
	cluster[26]->SetTag("Type7");
	manager.CreateGameObject(cluster[26]);
	cluster[27] = new ColliderObj;
	cluster[27]->SetPosition(Position(-26.692, 0, 103.604));
	cluster[27]->SetRotateY(90);
	cluster[27]->SetScale(Scale(11.5, 1, 23));
	cluster[27]->SetTag("Type1");
	manager.CreateGameObject(cluster[27]);
	cluster[28] = new ColliderObj;
	cluster[28]->SetPosition(Position(-49.2745, 0, 69.097));
	cluster[28]->SetRotateY(0);
	cluster[28]->SetScale(Scale(11.5, 1, 23));
	cluster[28]->SetTag("Type1");
	manager.CreateGameObject(cluster[28]);
	cluster[29] = new ColliderObj;
	cluster[29]->SetPosition(Position(-27.1164, 0, 71.240));
	cluster[29]->SetRotateY(-90);
	cluster[29]->SetScale(Scale(23, 1, 34.5));
	cluster[29]->SetTag("Type5");
	manager.CreateGameObject(cluster[29]);
	cluster[30] = new ColliderObj;
	cluster[30]->SetPosition(Position(26.4525, 0, 44.7866));
	cluster[30]->SetRotateY(217.309);
	cluster[30]->SetScale(Scale(23, 1, 34.5));
	cluster[30]->SetTag("Type5");
	manager.CreateGameObject(cluster[30]);
	cluster[31] = new ColliderObj;
	cluster[31]->SetPosition(Position(2.1104, 0, 14.127));
	cluster[31]->SetRotateY(-78.8068);
	cluster[31]->SetScale(Scale(11.5, 1, 23));
	cluster[31]->SetTag("Type2");
	manager.CreateGameObject(cluster[31]);
	cluster[32] = new ColliderObj;
	cluster[32]->SetPosition(Position(-10.9397, 0, -125.9913));
	cluster[32]->SetRotateY(180);
	cluster[32]->SetScale(Scale(23, 1, 34.5));
	cluster[32]->SetTag("Type4");
	manager.CreateGameObject(cluster[32]);
	cluster[33] = new ColliderObj;
	cluster[33]->SetPosition(Position(-19.1237, 0, -76.1837));
	cluster[33]->SetRotateY(0);
	cluster[33]->SetScale(Scale(11.5, 1, 23));
	cluster[33]->SetTag("Type3");
	manager.CreateGameObject(cluster[33]);
	cluster[34] = new ColliderObj;
	cluster[34]->SetPosition(Position(21.4181, 0, 130.1077));
	cluster[34]->SetRotateY(-90);
	cluster[34]->SetScale(Scale(23, 1, 34.5));
	cluster[34]->SetTag("Type4");
	manager.CreateGameObject(cluster[34]);
	cluster[35] = new ColliderObj;
	cluster[35]->SetPosition(Position(21.41817, 0, 108.3904));
	cluster[35]->SetRotateY(90);
	cluster[35]->SetScale(Scale(23, 1, 34.5));
	cluster[35]->SetTag("Type4");
	manager.CreateGameObject(cluster[35]);
	cluster[36] = new ColliderObj;
	cluster[36]->SetPosition(Position(62.7545, 0, 124.217));
	cluster[36]->SetRotateY(90);
	cluster[36]->SetScale(Scale(23, 1, 23));
	cluster[36]->SetTag("Type7");
	manager.CreateGameObject(cluster[36]);
	cluster[37] = new ColliderObj;
	cluster[37]->SetPosition(Position(111.78678, 0, 129.3267));
	cluster[37]->SetRotateY(90);
	cluster[37]->SetScale(Scale(23, 1, 34.5));
	cluster[37]->SetTag("Type5");
	manager.CreateGameObject(cluster[37]);
	cluster[38] = new ColliderObj;
	cluster[38]->SetPosition(Position(62.82099, 0, 95.6409));
	cluster[38]->SetRotateY(262.404);
	cluster[38]->SetScale(Scale(11.5, 1, 23));
	cluster[38]->SetTag("Type3");
	manager.CreateGameObject(cluster[38]);
	cluster[39] = new ColliderObj;
	cluster[39]->SetPosition(Position(71.7895, 0, 80.32));
	cluster[39]->SetRotateY(352.404);
	cluster[39]->SetScale(Scale(11.5, 1, 23));
	cluster[39]->SetTag("Type3");
	manager.CreateGameObject(cluster[39]);
	cluster[40] = new ColliderObj;
	cluster[40]->SetPosition(Position(76.498299, 0, 58.5145));
	cluster[40]->SetRotateY(352.404);
	cluster[40]->SetScale(Scale(11.5, 1, 23));
	cluster[40]->SetTag("Type2");
	manager.CreateGameObject(cluster[40]);
	cluster[41] = new ColliderObj;
	cluster[41]->SetPosition(Position(117.82504, 0, -0.24954));
	cluster[41]->SetRotateY(274.70874);
	cluster[41]->SetScale(Scale(23, 1, 23));
	cluster[41]->SetTag("Type7");
	manager.CreateGameObject(cluster[41]);
	cluster[42] = new ColliderObj;
	cluster[42]->SetPosition(Position(26.7506, 0, -126.4129));
	cluster[42]->SetRotateY(180);
	cluster[42]->SetScale(Scale(23, 1, 34.5));
	cluster[42]->SetTag("Type4");
	manager.CreateGameObject(cluster[42]);
	cluster[43] = new ColliderObj;
	cluster[43]->SetPosition(Position(65.074, 0, -132.3670));
	cluster[43]->SetRotateY(-270);
	cluster[43]->SetScale(Scale(11.5, 1, 23));
	cluster[43]->SetTag("Type2");
	manager.CreateGameObject(cluster[43]);
	cluster[44] = new ColliderObj;
	cluster[44]->SetPosition(Position(105.1129, 0, -134.954));
	cluster[44]->SetRotateY(90);
	cluster[44]->SetScale(Scale(11.5, 1, 23));
	cluster[44]->SetTag("Type1");
	manager.CreateGameObject(cluster[44]);
	cluster[45] = new ColliderObj;
	cluster[45]->SetPosition(Position(125.6322, 0, -27.1762));
	cluster[45]->SetRotateY(97.209);
	cluster[45]->SetScale(Scale(11.5, 1, 23));
	cluster[45]->SetTag("Type1");
	manager.CreateGameObject(cluster[45]);
	cluster[46] = new ColliderObj;
	cluster[46]->SetPosition(Position(17.3438, 0, -58.9819));
	cluster[46]->SetRotateY(236.355);
	cluster[46]->SetScale(Scale(23, 1, 34.5));
	cluster[46]->SetTag("Type5");
	manager.CreateGameObject(cluster[46]);
	cluster[47] = new ColliderObj;
	cluster[47]->SetPosition(Position(60.851799, 0, -81.5723));
	cluster[47]->SetRotateY(211.29794);
	cluster[47]->SetScale(Scale(23, 1, 34.5));
	cluster[47]->SetTag("Type5");
	manager.CreateGameObject(cluster[47]);
	cluster[48] = new ColliderObj;
	cluster[48]->SetPosition(Position(77.3685, 0, -60.651939));
	cluster[48]->SetRotateY(211.29794);
	cluster[48]->SetScale(Scale(23, 1, 23));
	cluster[48]->SetTag("Type6");
	manager.CreateGameObject(cluster[48]);
	cluster[49] = new ColliderObj;
	cluster[49]->SetPosition(Position(104.776, 0, -61.1024));
	cluster[49]->SetRotateY(121.297);
	cluster[49]->SetScale(Scale(23, 1, 23));
	cluster[49]->SetTag("Type6");
	manager.CreateGameObject(cluster[49]);
	cluster[50] = new ColliderObj;
	cluster[50]->SetPosition(Position(87.690628, 0, -78.13084));
	cluster[50]->SetRotateY(45);
	cluster[50]->SetScale(Scale(11.5, 1, 23));
	cluster[50]->SetTag("Type2");
	manager.CreateGameObject(cluster[50]);
	border[0] = new Border;
	border[0]->SetPosition(Position(0, 5, -150));
	border[0]->SetScale(Scale(300, 20, 80));
	manager.CreateGameObject(border[0]);
	borderCol[0] = new ColliderObj;
	borderCol[0]->SetPosition(Position(0, 0, -160));
	borderCol[0]->SetScale(Scale(300, 20, 20));
	manager.CreateGameObject(borderCol[0]);
	border[1] = new Border;
	border[1]->SetPosition(Position(0, 5, 150));
	border[1]->SetRotateY(180);
	border[1]->SetScale(Scale(300, 20, 80));
	manager.CreateGameObject(border[1]);
	borderCol[1] = new ColliderObj;
	borderCol[1]->SetPosition(Position(0, 0, 160));
	borderCol[1]->SetScale(Scale(300, 20, 20));
	manager.CreateGameObject(borderCol[1]);
	border[2] = new Border;
	border[2]->SetPosition(Position(-150, 5, 0));
	border[2]->SetRotateY(90);
	border[2]->SetScale(Scale(300, 20, 80));
	manager.CreateGameObject(border[2]);
	borderCol[2] = new ColliderObj;
	borderCol[2]->SetPosition(Position(-160, 0, 0));
	borderCol[2]->SetRotateY(90);
	borderCol[2]->SetScale(Scale(300, 20, 20));
	manager.CreateGameObject(borderCol[2]);
	border[3] = new Border;
	border[3]->SetPosition(Position(150, 5, 0));
	border[3]->SetRotateY(-90);
	border[3]->SetScale(Scale(300, 20, 80));
	manager.CreateGameObject(border[3]);
	borderCol[3] = new ColliderObj;
	borderCol[3]->SetPosition(Position(160, 0, 0));
	borderCol[3]->SetRotateY(90);
	borderCol[3]->SetScale(Scale(300, 20, 20));
	manager.CreateGameObject(borderCol[3]);
	for (int i = 0; i < sizeof(coins)/sizeof(*coins); i++)
	{
		coins[i] = new Money;
		coins[i]->SetPlayer(&bus);
		coins[i]->SetValue(50);
		coins[i]->SetScale(Scale(3.5f, 3.5f, 3.5f));
		manager.CreateGameObject(coins[i]);
	}
	coins[0]->SetPosition(Position(61.7, 0, -6.2));
	//coins[1]->SetPosition(Position(50.8, 0, -39.3));
	coins[1]->SetPosition(Position(70.6, 0, -40.4));
	//coins[3]->SetPosition(Position(86.8, 0, -31.3));
	coins[2]->SetPosition(Position(94.6, 0, -9.5));
	//coins[5]->SetPosition(Position(93.3, 0, 5.87));
	coins[3]->SetPosition(Position(75.4, 0, 22.4));
	//coins[7]->SetPosition(Position(55.4, 0, 24));
	coins[4]->SetPosition(Position(35.5, 0, 13.8));
	//coins[9]->SetPosition(Position(30, 0, -2.8));
	coins[5]->SetPosition(Position(30.5, 0, -18.1));
	//coins[11]->SetPosition(Position(38, 0, -30.6));
	coins[6]->SetPosition(Position(84.6, 0, 100.6));
	coins[7]->SetPosition(Position(103, 0, 73.1));
	coins[8]->SetPosition(Position(124.8, 0, 53.8));
	coins[9]->SetPosition(Position(138.5, 0, 24.9));
	coins[10]->SetPosition(Position(145.8, 0, -12.1));
	coins[11]->SetPosition(Position(134.5, 0, -49.6));
	coins[12]->SetPosition(Position(114, 0, -75.1));
	coins[13]->SetPosition(Position(97.5, 0, -91.2));
	coins[14]->SetPosition(Position(80.7, 0, -110));
	//coins[21]->SetPosition(Position(136.1, 0, -146.2));
	//coins[22]->SetPosition(Position(86.6, 0, -146.2));
	//coins[23]->SetPosition(Position(46.4, 0, -146.2));
	//coins[24]->SetPosition(Position(7.9, 0, -146.2));
	//coins[25]->SetPosition(Position(-27.7, 0, -146.2));
	//coins[26]->SetPosition(Position(-60.9, 0, -146.2));
	//coins[27]->SetPosition(Position(-103.1, 0, -146.2));
	//coins[28]->SetPosition(Position(-139.4, 0, -146.2));
	coins[15]->SetPosition(Position(136.1, 0, -120));
	coins[16]->SetPosition(Position(46.4, 0, -108));
	coins[17]->SetPosition(Position(7.9, 0, -102.8));
	coins[18]->SetPosition(Position(-27.7, 0, -102.8));
	coins[19]->SetPosition(Position(-60.9, 0, -102.8));
	coins[20]->SetPosition(Position(-103.1, 0, -102.8));
	//coins[27]->SetPosition(Position(-139.4, 0, -102.8));
	coins[21]->SetPosition(Position(-60.9, 0, -58));
	coins[22]->SetPosition(Position(-103.1, 0, -58));
	//coins[30]->SetPosition(Position(-139.4, 0, -58));
	coins[23]->SetPosition(Position(-60.9, 0, -31));
	coins[24]->SetPosition(Position(-103.1, 0, -31));
	//coins[33]->SetPosition(Position(-139.4, 0, -31));
	coins[25]->SetPosition(Position(-60.9, 0, 5));
	coins[26]->SetPosition(Position(-103.1, 0, 5));
	//coins[36]->SetPosition(Position(-139.4, 0, 5));
	coins[27]->SetPosition(Position(-60.9, 0, 41));
	coins[28]->SetPosition(Position(-103.1, 0, 41));
	//coins[39]->SetPosition(Position(-139.4, 0, 41));
	coins[29]->SetPosition(Position(-60.9, 0, 89));
	coins[30]->SetPosition(Position(-103.1, 0, 89));
	//coins[42]->SetPosition(Position(-139.4, 0, 89));
	//coins[51]->SetPosition(Position(-60.9, 0, 147));
	//coins[52]->SetPosition(Position(-103.1, 0, 147));
	//coins[53]->SetPosition(Position(-139.4, 0, 147));
	//coins[54]->SetPosition(Position(-3, 0, 147));
	//coins[55]->SetPosition(Position(44.5, 0, 147));
	//coins[56]->SetPosition(Position(89, 0, 147));
	//coins[57]->SetPosition(Position(136, 0, 147));
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
		manager.CreateGameObject(npc[i]);
	}

	//temp.SetTag("Temp");
	//manager.CreateGameObject(&temp);
	TestRef = &bus;
}

void SceneDrive::Update(double dt)
{
	manager.GameObjectManagerUpdate(dt);
	camera.Update(dt);
	camera.SetChase(&bus); // use only for cameraChase

	fps = 1.0f / dt;

	coinRot += coinRot > 360 ? (180 * dt) - 360 : 180 * dt;

	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

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

	//for testing purposes
	/*if (Application::IsKeyPressed('V'))
	{
		scene_change = true;
		map.Set(Maps::SKYBOX_TYPE::SB_DAY);
	}
	if (Application::IsKeyPressed('B'))
	{
		scene_change = true;
		map.Set(Maps::SKYBOX_TYPE::SB_NIGHT);
	}*/

	/*if (Application::IsKeyPressed('T'))
	{
		TestRef->SetPositionZ(TestRef->GetPositionZ() - 5 * multiplier * dt);
	}
	if (Application::IsKeyPressed('G'))
	{
		TestRef->SetPositionZ(TestRef->GetPositionZ() + 5 * multiplier * dt);
	}
	if (Application::IsKeyPressed('F'))
	{
		TestRef->SetPositionX(TestRef->GetPositionX() - 5 * multiplier * dt);
	}
	if (Application::IsKeyPressed('H'))
	{
		TestRef->SetPositionX(TestRef->GetPositionX() + 5 * multiplier * dt);
	}
	if (Application::IsMousePressed(1))
	{
		multiplier = 10;
	}
	else if (Application::IsMousePressed(0))
	{
		multiplier = 1;
	}
	else multiplier = 5;

	if (Application::IsKeyPressed('C'))
	{
		TestRef->SetRotateY(TestRef->GetRotateY() + 90 * dt);
	}
	if (Application::IsKeyPressed('V'))
	{
		TestRef->SetRotateY(TestRef->GetRotateY() - 90 * dt);
	}
	if (Application::IsKeyPressed('Z') && toggleTime <= 0)
	{
		TestRef->SetRotateY(TestRef->GetRotateY() + 45);
		toggleTime = .3;
	}
	else if (Application::IsKeyPressed('X') && toggleTime <= 0)
	{
		TestRef->SetRotateY(TestRef->GetRotateY() - 45);
		toggleTime = .3;
	}*/
	/*else if (Application::IsMousePressed(2) && toggleTime <= 0)
	{
		clusterType++;
		switch (clusterType)
		{
		case 1:
			TestRef->SetTag("Type1");
			break;
		case 2:
			TestRef->SetTag("Type2");
			break;
		case 3:
			TestRef->SetTag("Type3");
			break;
		case 4:
			TestRef->SetTag("Type4");
			break;
		case 5:
			TestRef->SetTag("Type5");
			break;
		case 6:
			TestRef->SetTag("Type6");
			break;
		case 7:
			TestRef->SetTag("Type7");
			break;
		case 8:
			TestRef->SetTag("Type8");
			break;
		default:
			clusterType = 1;
			TestRef->SetTag("Type1");
			break;
		}
		toggleTime = .3;
	}*/
	else if (Application::IsKeyPressed('B') && toggleTime <= 0)
	{
		toggleHitBox = !toggleHitBox;
		toggleTime = .3;

	}
	else if (toggleTime > 0) toggleTime -= dt;

	if (scene_change) //to ensure that the skybox only updates when the scene changes
	{
		meshList[GEO_FRONT]->textureID = LoadTGA((map.skybox_loc[0]).std::string::c_str());
		meshList[GEO_BACK]->textureID = LoadTGA((map.skybox_loc[1]).std::string::c_str());
		meshList[GEO_LEFT]->textureID = LoadTGA((map.skybox_loc[2]).std::string::c_str());
		meshList[GEO_RIGHT]->textureID = LoadTGA((map.skybox_loc[3]).std::string::c_str());
		meshList[GEO_TOP]->textureID = LoadTGA((map.skybox_loc[4]).std::string::c_str());
		meshList[GEO_BOTTOM]->textureID = LoadTGA((map.skybox_loc[5]).std::string::c_str());

		scene_change = false;
	}

	/*if (Application::IsKeyPressed('5'))
	{
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('8'))
	{
		lights[0].type = Light::LIGHT_MULTIPLE;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}

	if (Application::IsKeyPressed('5'))
	{
		lights[1].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		lights[1].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		lights[1].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}
	else if (Application::IsKeyPressed('8'))
	{
		lights[1].type = Light::LIGHT_MULTIPLE;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}*/
}

void SceneDrive::Render() //My Own Pattern
{
	// Render VBO here

	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y,
		camera.position.z, camera.target.x, camera.target.y,
		camera.target.z, camera.up.x, camera.up.y, camera.up.z);
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

	if (lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP

	RenderSkybox();
	//modelStack.Scale(3, 3, 3);
	//RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
		modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();
	

	modelStack.PushMatrix();
		modelStack.Rotate(270, 1, 0, 0);
		modelStack.Scale(300, 300, 1);
		RenderMesh(meshList[GEO_TEMPLATE], true);
	modelStack.PopMatrix();

	std::vector<GameObject*>GOList = manager.GetGameObjectList();
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
					RenderMesh(meshList[GEO_TEST], true);
				}
				else if (gameObject->Type() == "ColliderObj")
				{
					if (abs((Vector3(gameObject->GetPositionX(), gameObject->GetPositionY(), gameObject->GetPositionZ()) - Vector3(bus.GetPositionX(), bus.GetPositionY(), bus.GetPositionZ())).Length()) > 100)
					{ // dont render if GO is aprox. out of view
						modelStack.PopMatrix();
						modelStack.PopMatrix();
						continue;
					}
					if (gameObject->GetTag() == "Temp")
					{
						modelStack.PushMatrix();
							RenderMesh(meshList[GEO_CUBE], false);
						modelStack.PopMatrix();
					}
					if (gameObject->GetTag() == "Type1")
					{
						modelStack.PushMatrix();
							modelStack.Translate(.85f, 0, .6f);
							RenderMesh(meshList[GEO_BUILDING1], lights[0].isOn);
						modelStack.PopMatrix();
					}
					if (gameObject->GetTag() == "Type2")
					{
						modelStack.PushMatrix();
							modelStack.Translate(.85f, 0, .6f);
							RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
						modelStack.PopMatrix();
					}
					if (gameObject->GetTag() == "Type3")
					{
						modelStack.PushMatrix();
							modelStack.Translate(.85f, 0, .6f);
							RenderMesh(meshList[GEO_BUILDING3], lights[0].isOn);
						modelStack.PopMatrix();
					}
					if (gameObject->GetTag() == "Type4")
					{
						modelStack.PushMatrix();
							modelStack.Translate(0, 0, 11.5f);
							modelStack.Rotate(90, 0, 1, 0);
							modelStack.PushMatrix();
								modelStack.Translate(.85f, 0, .6f);
								RenderMesh(meshList[GEO_BUILDING3], lights[0].isOn);
							modelStack.PopMatrix();
						modelStack.PopMatrix();
						modelStack.PushMatrix();
							modelStack.Translate(5.75, 0, -5.75f);
							modelStack.Rotate(0, 0, 1, 0);
							modelStack.PushMatrix();
								modelStack.Translate(.85f, 0, .6f);
								RenderMesh(meshList[GEO_BUILDING3], lights[0].isOn);
							modelStack.PopMatrix();
						modelStack.PopMatrix();
						modelStack.PushMatrix();
							modelStack.Translate(-5.75, 0, -5.75f);
							modelStack.Rotate(0, 0, 1, 0);
							modelStack.PushMatrix();
								modelStack.Translate(.85f, 0, .6f);
								RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
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
								RenderMesh(meshList[GEO_BUILDING3], lights[0].isOn);
							modelStack.PopMatrix();
						modelStack.PopMatrix();
						modelStack.PushMatrix();
							modelStack.Translate(5.75, 0, -5.75f);
							modelStack.Rotate(0, 0, 1, 0);
							modelStack.PushMatrix();
								modelStack.Translate(.85f, 0, .6f);
								RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
							modelStack.PopMatrix();
						modelStack.PopMatrix();
						modelStack.PushMatrix();
							modelStack.Translate(-5.75, 0, -5.75f);
							modelStack.Rotate(0, 0, 1, 0);
							modelStack.PushMatrix();
								modelStack.Translate(.85f, 0, .6f);
								RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
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
								RenderMesh(meshList[GEO_BUILDING1], lights[0].isOn);
							modelStack.PopMatrix();
						modelStack.PopMatrix();
						modelStack.PushMatrix();
							modelStack.Translate(-5.75, 0, 0);
							modelStack.Rotate(0, 0, 1, 0);
							modelStack.PushMatrix();
								modelStack.Translate(.85f, 0, .6f);
								RenderMesh(meshList[GEO_BUILDING1], lights[0].isOn);
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
								RenderMesh(meshList[GEO_BUILDING1], lights[0].isOn);
							modelStack.PopMatrix();
						modelStack.PopMatrix();
						modelStack.PushMatrix();
							modelStack.Translate(-5.75, 0, 0);
							modelStack.Rotate(0, 0, 1, 0);
							modelStack.PushMatrix();
								modelStack.Translate(.85f, 0, .6f);
								RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
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
								RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
							modelStack.PopMatrix();
						modelStack.PopMatrix();
						modelStack.PushMatrix();
							modelStack.Translate(-5.75, 0, 0);
							modelStack.Rotate(0, 0, 1, 0);
							modelStack.PushMatrix();
								modelStack.Translate(.85f, 0, .6f);
								RenderMesh(meshList[GEO_BUILDING3], lights[0].isOn);
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
								RenderMesh(meshList[GEO_BORDER], false);
							modelStack.PopMatrix();
						}
					}
				}
				else if (gameObject->Type() == "DriveObjective")
				{
					//modelStack.Scale(gameObject->GetScaleX(), gameObject->GetScaleY(), gameObject->GetScaleZ());
					//RenderMesh(meshList[GEO_CUBE], false); // hitbox
				}
				else if (gameObject->Type() == "Money")
				{
					if (abs((Vector3(gameObject->GetPositionX(), gameObject->GetPositionY(), gameObject->GetPositionZ()) - Vector3(bus.GetPositionX(), bus.GetPositionY(), bus.GetPositionZ())).Length()) > 100)
					{ // dont render if GO is aprox. out of view
						modelStack.PopMatrix();
						modelStack.PopMatrix();
						continue;
					}
					modelStack.Scale(10, 10, 10);
					modelStack.Rotate(coinRot, 0, 1, 0);
					RenderMesh(meshList[GEO_COIN], true);
				}
				else if (gameObject->Type() == "Person")
				{
					if (abs((Vector3(gameObject->GetPositionX(), gameObject->GetPositionY(), gameObject->GetPositionZ()) - Vector3(bus.GetPositionX(), bus.GetPositionY(), bus.GetPositionZ())).Length()) > 100)
					{ // dont render if GO is aprox. out of view
						modelStack.PopMatrix();
						modelStack.PopMatrix();
						continue;
					}					
					modelStack.Scale(.03f, .03f, .03f);
					RenderMesh(meshList[GEO_NPC], true);
				}
			modelStack.PopMatrix();
			modelStack.Scale(gameObject->GetScaleX(), gameObject->GetScaleY(), gameObject->GetScaleZ());
			if (toggleHitBox) RenderMesh(meshList[GEO_CUBE], false); // hitbox
		modelStack.PopMatrix();
	}

	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, Application::GetWindowHeight() * .1f);

	RenderTextOnScreen(meshList[GEO_TEXT], "Passengers:" + std::to_string(bus.GetPassengerCount()) + "/" + std::to_string(endpoint.GetRequiredPassengerCount()), Color(0, 0, 1), 3, 0, 81);

	RenderTextOnScreen(meshList[GEO_TEXT], "Total Money:" + std::to_string(Bus::GetMoney()), Color(1, 1, 0), 3, 0, 87);

	RenderTextOnScreen(meshList[GEO_TEXT], "Money Collected:" + std::to_string(bus.GetMoneyCurrent()), Color(1, 0, 0), 3, 0, 84);

	RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(TestRef->GetPositionX()) + ", " + std::to_string(TestRef->GetPositionZ()) + ", " + std::to_string(TestRef->GetRotateY()) + ", " + TestRef->GetTag(), Color(1, 0, 1), 3, 0, 0);

	//RenderMeshOnScreen(meshList[GEO_QUAD], 80, 45, 10, 10);
}

void SceneDrive::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}

void SceneDrive::RenderMesh(Mesh* mesh, bool enableLight)
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

		//load material
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

void SceneDrive::RenderSkybox()
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

void SceneDrive::RenderText(Mesh* mesh, std::string text, Color color)
{
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!mesh || mesh->textureID <= 0) //Proper error check
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
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneDrive::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, UI_width, 0, UI_height, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
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

void SceneDrive::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, UI_width, 0, UI_height, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0); 
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}