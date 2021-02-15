#define LSPEED 10.f
#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Utility.h"
#include "LoadTGA.h"

#include "Application.h"


Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}


void Assignment2::Init() 
{
	camera_outHouse.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));
	camera_inHouse.Init(Vector3(22.5f, 17.5f, -62.7f), Vector3(21.7f, 17.2f, -63.1f), Vector3(0, 1, 0));
	camera_inHouse.setBoundary(Vector3(22.5f, 17.5f, -62.7f), Vector3(-28.7f, camera_inHouse.neg_bound.y, -87.f));

	Capoo_posBound.Set(90, Capoo.y, 90);
	Capoo_negBound.Set(-90, Capoo.y, -52);

	camera = camera_outHouse;

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	rotateAngle = 0;

	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	in_house = false;
	ate_meat = false;
	is_sleeping = false;

	x_value = y_value = z_value = 0;
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

	Capoo.Set(0, 2.7f, 0);

	black.Set(0, 0, 0);
	Capoo_color.Set(0.294f, 0.745f, 0.89f);
	Capoo_pattern.Set(0, .47f, .76f);

	capoo_blinking = false;
	capoo_running = false;

	rotateAngle = 0;
	angle_leg = 0;
	legDir = 0;
	eyeMove_capoo = -1;
	eye_capoo = .3f;

	moonshade.Set(0.93f, 0.93f, 0.88f);
	
	meshList[GEO_HOUSE] = MeshBuilder::GenerateOBJMTL("House", "OBJ//house_type04.obj", "OBJ//house_type04.mtl");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//treePine.obj", "OBJ//treePine.mtl");

	meshList[GEO_PLATE] = MeshBuilder::GenerateOBJMTL("Plate", "OBJ//plate.obj", "OBJ//plate.mtl");

	meshList[GEO_MEAT] = MeshBuilder::GenerateOBJMTL("Meat", "OBJ//meat.obj", "OBJ//plate.mtl");

	meshList[GEO_BED] = MeshBuilder::GenerateOBJMTL("Bed", "OBJ//bed.obj", "OBJ//bed.mtl");

	//meshList[GEO_BALL] = MeshBuilder::GenerateOBJMTL("Ball", "OBJ//ball.obj", "OBJ//ball.mtl");

	meshList[CAPOO_SPHERE] = MeshBuilder::GenerateSphere("Capoo", Capoo_color, 30, 30, 1);
	meshList[CAPOO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[CAPOO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[CAPOO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[CAPOO_SPHERE]->material.kShininess = .5f;

	meshList[CAPOO_PATTERN] = MeshBuilder::GenerateTorus("Capoo pattern", Capoo_pattern, 30, 30, 1, 1, 180.f);
	meshList[CAPOO_PATTERN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[CAPOO_PATTERN]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[CAPOO_PATTERN]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[CAPOO_PATTERN]->material.kShininess = .5f;

	meshList[EYE] = MeshBuilder::GenerateSphere("Eye", black, 30, 30, 1);
	meshList[EYE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[EYE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[EYE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[EYE]->material.kShininess = .7f;

	meshList[MOUTH] = MeshBuilder::GenerateTorus("mouth", black, 30, 30, 1, .3f, 180.f);
	meshList[MOUTH]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[MOUTH]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[MOUTH]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[MOUTH]->material.kShininess = 0;

	meshList[CAPOO_CYLINDER] = MeshBuilder::GenerateCylinder("Capoo", Capoo_color, 30, 30, 1, 1);
	meshList[CAPOO_CYLINDER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[CAPOO_CYLINDER]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[CAPOO_CYLINDER]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[CAPOO_CYLINDER]->material.kShininess = .5f;

	meshList[CAPOO_CONE] = MeshBuilder::GenerateCone("Capoo Tail", Capoo_color, 30, 20, 1, 2, 1.5);
	meshList[CAPOO_CONE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[CAPOO_CONE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[CAPOO_CONE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[CAPOO_CONE]->material.kShininess = .5f;

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Rsphere", red, 30, 30, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", lights[0].color, 30, 30, 1);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("ground", Color(.39f, .39f, .39f), 1.f, 1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[CAPOO_BLUSH] = MeshBuilder::GenerateQuad("Capoo Blush", Color(.39f, .39f, .39f), 1.f, 1.f);
	meshList[CAPOO_BLUSH]->textureID = LoadTGA("Image//blush.tga");
	meshList[CAPOO_BLUSH]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[CAPOO_BLUSH]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[CAPOO_BLUSH]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[CAPOO_BLUSH]->material.kShininess = 1.f;

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", blue, 1, 1, 1);
	meshList[GEO_CUBE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CUBE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_CUBE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_CUBE]->material.kShininess = 1.f;
	meshList[GEO_CUBE]->textureID = LoadTGA("Image//muscle_capoo.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//sans.tga");

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

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

	m_parameters[U_M_LIGHT_POSITION] = glGetUniformLocation(m_programID, "m_light.position_cameraspace");
	m_parameters[U_M_LIGHT_COLOR] = glGetUniformLocation(m_programID, "m_light.color");
	m_parameters[U_M_LIGHT_POWER] = glGetUniformLocation(m_programID, "m_light.power");
	m_parameters[U_M_LIGHT_KC] = glGetUniformLocation(m_programID, "m_light.kC");
	m_parameters[U_M_LIGHT_KL] = glGetUniformLocation(m_programID, "m_light.kL");
	m_parameters[U_M_LIGHT_KQ] = glGetUniformLocation(m_programID, "m_light.kQ");
	m_parameters[U_M_LIGHT_TYPE] = glGetUniformLocation(m_programID, "m_light.type");
	m_parameters[U_M_LIGHT_SPOTDIRECTION] = glGetUniformLocation(m_programID, "m_light.spotDirection");
	m_parameters[U_M_LIGHT_COSCUTOFF] = glGetUniformLocation(m_programID, "m_light.cosCutoff");
	m_parameters[U_M_LIGHT_COSINNER] = glGetUniformLocation(m_programID, "m_light.cosInner");
	m_parameters[U_M_LIGHT_EXPONENT] = glGetUniformLocation(m_programID, "m_light.exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);
	
	lights[0].isOn = true;
	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(3, 30, 8);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].isOn = false;
	lights[1].type = Light::LIGHT_DIRECTIONAL;
	lights[1].position.Set(0, 20, -75);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.1f, 0.1f, 0.1f);

	lights[M_LIGHT].type = Light::LIGHT_SPOT;
	lights[M_LIGHT].position.Set(-24, 20, -91);
	lights[M_LIGHT].color.Set(1, 1, 1);
	lights[M_LIGHT].power = 1;
	lights[M_LIGHT].kC = 1.f;
	lights[M_LIGHT].kL = 0.01f;
	lights[M_LIGHT].kQ = 0.001f;
	lights[M_LIGHT].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[M_LIGHT].cosInner = cos(Math::DegreeToRadian(30));
	lights[M_LIGHT].exponent = 3.f;
	lights[M_LIGHT].spotDirection.Set(0, 0.5f, 0);

										 //v Change this to set the total number of lights to set
	glUniform1i(m_parameters[U_NUMLIGHTS], 3);

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

	glUniform1i(m_parameters[U_M_LIGHT_TYPE], lights[M_LIGHT].type);
	glUniform3fv(m_parameters[U_M_LIGHT_COLOR], 1, &lights[M_LIGHT].color.r);

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
						 m_parameters[U_MATERIAL_DIFFUSE],
						 m_parameters[U_MATERIAL_SPECULAR],
						 m_parameters[U_MATERIAL_SHININESS]);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

}

void Assignment2::Update(double dt)
{
	camera.Update(dt);

	fps = 1.0f / dt;

	rotateAngle += (float)( 50 * dt);
	translateX += (float)(translateXDir * 10 * dt);
	translateY += (float)(translateYDir * 50 * dt);
	scaleAll += (float)(scaleDir * 2 * dt);

	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode


	if (Application::IsKeyPressed('O'))
		lights[2].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('U'))
		lights[2].position.y += (float)(LSPEED * dt);


	if (Application::IsKeyPressed('T'))
		lights[0].isOn = false;
	if (Application::IsKeyPressed('Y'))
		lights[0].isOn = true;

	if (lights[1].isOn)
	{
		glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
		glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
		glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
		glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
		glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
		glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
		glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

		glUniform1f(m_parameters[U_M_LIGHT_POWER], lights[M_LIGHT].power);
		glUniform1f(m_parameters[U_M_LIGHT_KC], lights[M_LIGHT].kC);
		glUniform1f(m_parameters[U_M_LIGHT_KL], lights[M_LIGHT].kL);
		glUniform1f(m_parameters[U_M_LIGHT_KQ], lights[M_LIGHT].kQ);
		glUniform1f(m_parameters[U_M_LIGHT_COSCUTOFF], lights[M_LIGHT].cosCutoff);
		glUniform1f(m_parameters[U_M_LIGHT_COSINNER], lights[M_LIGHT].cosInner);
		glUniform1f(m_parameters[U_M_LIGHT_EXPONENT], lights[M_LIGHT].exponent);
	}
	else
	{
		glUniform1f(m_parameters[U_LIGHT1_POWER], 0);
		glUniform1f(m_parameters[U_LIGHT1_KC], 0);
		glUniform1f(m_parameters[U_LIGHT1_KL], 0);
		glUniform1f(m_parameters[U_LIGHT1_KQ], 0);
		glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], 0);
		glUniform1f(m_parameters[U_LIGHT1_COSINNER], 0);
		glUniform1f(m_parameters[U_LIGHT1_EXPONENT], 0);

		glUniform1f(m_parameters[U_M_LIGHT_POWER], 0);
		glUniform1f(m_parameters[U_M_LIGHT_KC], 0);
		glUniform1f(m_parameters[U_M_LIGHT_KL], 0);
		glUniform1f(m_parameters[U_M_LIGHT_KQ], 0);
		glUniform1f(m_parameters[U_M_LIGHT_COSCUTOFF], 0);
		glUniform1f(m_parameters[U_M_LIGHT_COSINNER], 0);
		glUniform1f(m_parameters[U_M_LIGHT_EXPONENT], 0);
	}


	//Capoo Movement
	if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed(VK_RIGHT))
	{
		capoo_running = true;
		if (Application::IsKeyPressed(VK_DOWN))
		{
			Capoo.z += (float)(LSPEED * dt);
		}
		if (Application::IsKeyPressed(VK_UP))
		{
			Capoo.z -= (float)(LSPEED * dt);
		}
		if (Application::IsKeyPressed(VK_LEFT))
		{
			Capoo.x -= (float)(LSPEED * dt);
		}
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			Capoo.x += (float)(LSPEED * dt);
		}
	}
	else
	{
		legDir = 1;
		angle_leg = 0;
		capoo_running = false;
	}

	//Capoo Outside Boundary
	if (Capoo.x >= Capoo_posBound.x)
		Capoo.x = Capoo_posBound.x;
	if (Capoo.x <= Capoo_negBound.x)
		Capoo.x = Capoo_negBound.x;
	if (Capoo.z >= Capoo_posBound.z)
		Capoo.z = Capoo_posBound.z;
	if (Capoo.z <= Capoo_negBound.z)
		Capoo.z = Capoo_negBound.z;
		

	//	editor commands
	if (Application::IsKeyPressed(VK_DOWN))
		y_value -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed(VK_UP))
		y_value += (float)(LSPEED * dt);
	if (Application::IsKeyPressed(VK_LEFT))
		x_value -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed(VK_RIGHT))
		x_value += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('Z'))
		z_value -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('X'))
		z_value += (float)(LSPEED * dt);

	//Capoo Movements
	if (Application::IsKeyPressed('V'))
	{
		legDir = 1;
		angle_leg = 0;
		capoo_running = true;
	}
	if (Application::IsKeyPressed('B'))
	{
		eyeMove_capoo = -1;
		eye_capoo = .3f;
		capoo_blinking = true;
	}

	//Capoo run
	if (capoo_running)
	{
		angle_leg += (float)(legDir * 40 * dt);
		if ((angle_leg > 15) || (angle_leg < -15))
			legDir *= -1;
	}
	//Blinking
	if (capoo_blinking)
	{
		eye_capoo += (float)(eyeMove_capoo * .5f * dt);

		if ((eye_capoo <= 0.05f))
			eyeMove_capoo *= -1;
		if ((eye_capoo >= .3f))
			capoo_blinking = false;
	}
	if (Application::IsKeyPressed('F'))
	{
		Init();
	}

	//checks if Capoo in in the house
	if ((Capoo.x >= -5) && (Capoo.x <= 6) && (Capoo.z <= -47.5f) && (Capoo.z >= -63))
	{
		if (Application::IsKeyPressed('E'))
		{
			in_house = true;
			lights[1].isOn = true;
			camera = camera_inHouse;
			Capoo.Set(0, Capoo.y, -63);

			//boundary inside
			Capoo_posBound.Set(23, Capoo.y, -63);
			Capoo_negBound.Set(-22, Capoo.y, -83);
		}
		if (Application::IsKeyPressed('Q'))
		{
			in_house = false;
			lights[1].isOn = false;
			camera = camera_outHouse;
			Capoo.Set(0, Capoo.y, -52);

			//boundary outside
			Capoo_posBound.Set(90, Capoo.y, 90);
			Capoo_negBound.Set(-90, Capoo.y, -52);
		}
	}

	if ((Capoo.x >= 15) && (Capoo.x <= 23) &&(Capoo.z <= -77) && (Capoo.z >= -83))
		if (Application::IsKeyPressed('E'))
		{
			is_sleeping = true;
			Capoo.x = 23;
			Capoo.z = -83;
		}

	if (is_sleeping)
		if (Application::IsKeyPressed('Q'))
		{
			is_sleeping = false;
			Capoo.x = 15;
			Capoo.z = -77;
		}

	if ((Capoo.x == -22) && (Capoo.z == -83)) //checks if capoo is in the corner where the meat is placed
		if (Application::IsKeyPressed(VK_SPACE))
			ate_meat = true;

	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}

}

void Assignment2::Render() //My Own Pattern
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

	if (lights[M_LIGHT].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[M_LIGHT].position.x, lights[M_LIGHT].position.y, lights[M_LIGHT].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[M_LIGHT].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[M_LIGHT].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[M_LIGHT].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[M_LIGHT].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(lights[1].position.x, lights[1].position.y, lights[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	RenderSkybox();

	modelStack.PushMatrix();
	modelStack.Translate(0, -.1f, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(200, 200, 200);
	RenderMesh(meshList[GEO_QUAD], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(32.5f, 0, -100);
	modelStack.Scale(50, 50, 50);
	RenderMesh(meshList[GEO_HOUSE], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(62, 0, -70);
	modelStack.Scale(50, 50, 50);
	RenderMesh(meshList[GEO_TREE], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-24, 0, -91);
	modelStack.Scale(7.5f, 7.5f, 7.5f);
	RenderMesh(meshList[GEO_PLATE], lights[0].isOn);
	modelStack.PopMatrix();

	if (!ate_meat)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-24, .5f, -91);
		modelStack.Scale(7.5f, 7.5f, 7.5f);
		RenderMesh(meshList[GEO_MEAT], lights[0].isOn);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(15.3f, 0, -86);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10.7f, 10.7f, 10.7f);
	RenderMesh(meshList[GEO_BED], lights[0].isOn);
	modelStack.PopMatrix();

	RenderCapoo();

	if ((Capoo.x >= -5) && (Capoo.x <= 6) && (Capoo.z <= -47.5f) && (Capoo.z >= -63.5))
	{
		if (!in_house)
			RenderTextOnScreen(meshList[GEO_TEXT], "Press E to get inside", Color(0, 1, 0), 3, 7, 30);
		else
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to get outside", Color(0, 1, 0), 3, 7, 30);
	}

	if ((Capoo.x == -22) && (Capoo.z == -83))
	{
		if (!ate_meat)
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Spacebar to eat meat", Color(0, 1, 0), 3, 7, 30);
	} 
	if ((Capoo.x >= 15) && (Capoo.x <= 23) && (Capoo.z <= -77) && (Capoo.z >= -83))
	{
		if (!is_sleeping)
			RenderTextOnScreen(meshList[GEO_TEXT], "Press E to sleep", Color(0, 1, 0), 3, 7, 30);
		else
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to leave bed", Color(0, 1, 0), 3, 7, 30);
	}

	std::ostringstream ss;
	ss.precision(5);

	//to check pos of cam and capoo
	/*ss << "CAPOO: x:" << (Capoo.x) << " y:" << (Capoo.y) << "z:" << (Capoo.z);
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 2, 0, 0);
	ss.str("");

	ss.precision(5);
	ss << "CAM: x:" << (camera.position.x) << " y:" << (camera.position.y) << "z:" << (camera.position.z);
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 2, 0, 2);
	ss.str("");*/

	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 2, 58, 58);

	RenderTextOnScreen(meshList[GEO_TEXT], "Use WASD to move", Color(0, 1, 0), 3, 0, 0);
}

void Assignment2::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}

void Assignment2::RenderMesh(Mesh* mesh, bool enableLight)
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

void Assignment2::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -500);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 1);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_BACK], false);

	modelStack.PushMatrix();
	modelStack.Translate(-.5f, 0, .5f);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_LEFT], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 1);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_RIGHT], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, .5f, .5f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(270, 0, 0, 1);
	RenderMesh(meshList[GEO_BOTTOM], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);
	RenderMesh(meshList[GEO_TOP], false);

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment2::RenderCapoo()
{
	//CAPOO
	modelStack.PushMatrix();
	modelStack.Translate(Capoo.x, Capoo.y, Capoo.z);

	if(is_sleeping)
		modelStack.Rotate(180, 0, 1, 0);
	else
		modelStack.Rotate(90, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Scale(.2f, .2f, .2f);

	modelStack.PushMatrix();
	modelStack.Scale(14, 14, 14);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(meshList[CAPOO_CYLINDER], lights[0].isOn);

	//Pattern on back
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(-.53f, .2f, -.4f);
	modelStack.Translate(0, 1.08f, 0);
	RenderMesh(meshList[CAPOO_PATTERN], lights[0].isOn);


	modelStack.PushMatrix();

	modelStack.Translate(0, -1.7f, 0);
	RenderMesh(meshList[CAPOO_PATTERN], lights[0].isOn);


	modelStack.PushMatrix();
	modelStack.Translate(0, -1.7f, 0);
	RenderMesh(meshList[CAPOO_PATTERN], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//head
	modelStack.PushMatrix();
	modelStack.Translate(0, -.5f, 0);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);

	//ears
	modelStack.PushMatrix();
	modelStack.Scale(.7f, .3f, .5f);
	modelStack.Rotate(45, 1, 0, 0);
	modelStack.Translate(0.5f, .15f, 1.2f);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Translate(.0f, -1.4f, -1.45f);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//eyes

	modelStack.PushMatrix();
	modelStack.Translate(.2f, -.61f, -.44f);

	if (is_sleeping)
	{
		modelStack.Scale(.05f, .3f, .3f);
	}
	else if (capoo_blinking)
	{
		modelStack.Scale(eye_capoo, .3f, .3f);
	}
	else
		modelStack.Scale(.3f, .3f, .3f);
	RenderMesh(meshList[EYE], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 3);
	RenderMesh(meshList[EYE], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//mouth
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(-10, 0, 0, 1);
	modelStack.Scale(.1f, .1f, .1f);
	modelStack.Translate(0, -10.f, .69f);
	RenderMesh(meshList[MOUTH], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -1.85f);
	RenderMesh(meshList[MOUTH], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Translate(-.47f, 0, 0);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);

	modelStack.Rotate(90, 0, 0, 1);
	modelStack.PushMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(.5f, .2f, .6f);
	modelStack.Translate(.3f, 4.2f, 0);
	RenderMesh(meshList[CAPOO_CONE], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	if (capoo_running)
	{
		modelStack.PushMatrix();
		modelStack.Rotate(angle_leg, 0, 0, 1);
	}

	//1st pair of legs
	modelStack.PushMatrix();
	modelStack.Scale(3.7f, 6.25f, 3.7f);
	modelStack.Translate(0, -1.2f, -2.5f);
	modelStack.Rotate(136, 0, 0, 1);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);


	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(-136, 0, 0, 1);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();


	if (capoo_running)
	{
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(angle_leg, 0, 0, 1);
	}

	//2nd pair of legs
	modelStack.PushMatrix();
	modelStack.Scale(3.7f, 6.25f, 3.7f);
	modelStack.Translate(-2.7f, -1.2f, -2.5f);
	modelStack.Rotate(136, 0, 0, 1);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);


	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(-136, 0, 0, 1);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	if (capoo_running)
	{
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(-angle_leg, 0, 0, 1);
	}

	//3rd pair of legs
	modelStack.PushMatrix();
	modelStack.Scale(3.7f, 6.25f, 3.7f);
	modelStack.Translate(2.7f, -1.2f, -2.5f);
	modelStack.Rotate(136, 0, 0, 1);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);


	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(-136, 0, 0, 1);
	RenderMesh(meshList[CAPOO_SPHERE], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	if (capoo_running)
	{
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(4.2f, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(-4.9f, -4.9f, -4.9f);
	RenderMesh(meshList[CAPOO_BLUSH], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void Assignment2::RenderText(Mesh* mesh, std::string text, Color color)
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

void Assignment2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
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

void Assignment2::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
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