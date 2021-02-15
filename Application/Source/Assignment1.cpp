#define LSPEED 10.f
#include "Assignment1.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Utility.h"

#include "Application.h"


Assignment1::Assignment1()
{
}

Assignment1::~Assignment1()
{
}


void Assignment1::Init() 
{
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	angle_capoo = 0;
	capooDir = 0;
	angle_chick = 0;
	chickDir = 0;
	chickJumpDirX = 0;
	chickJumpDirY = 0;
	jump_chickX = 0;
	jump_chickY = 0;
	jump_capooZ = 0;
	jump_capooY = 0;
	capooJumpDirZ = 0;
	capooJumpDirY = 0;
	rotateAngle = 0;


	angle_leg = 0;
	legDir = 1;
	eyeMove_capoo = -1;
	eyeMove_chick = -1;
	eye_capoo = .3f;
	eye_chick = .2f;


	////Set background color to dark blue (Step 3a)
	//glClearColor(0.0f, 0.0f, 0.4f, );

	//Set background to white
	glClearColor(.961f, .961f, .961f, 1);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	animation1 = false;
	x_value = y_value = z_value = 0.001f; //Used this to help me set the coordinates of my meshes

	black.Set(0, 0, 0);
	red.Set(1, 0, 0);
	green.Set(0, 1, 0);
	blue.Set(0, 0, 1);
	pink.Set(1.0f, 0.55f, 0.6f);
	Lblue.Set(0.1f, 0.1f, 1.0f);
	Dblue.Set(0, 0, .545f);
	purple.Set(0.6f, 0.5f, 1.0f);
	orange.Set(0.89f, 0.66f, 0.41f);
	yellow.Set(1, 1, 0);
	cyan.Set(0, 1, 1);
	magenta.Set(1, 0, 1);
	brown.Set(.75f, .56f, .31f);
	moonshade.Set(0.93f, 0.93f, 0.88f);
	

	Capoo_color.Set(0.294f, 0.745f, 0.89f);
	Capoo_pattern.Set(0, .47f, .76f);

	Chick_color.Set(1.f, .91f, .51f);
	Chick_beak.Set(.89f, .60f, .01f);


	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", lights[0].color, 30, 30, 1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Dblue, 1, 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = .6f;

	meshList[QUAD_BOX] = MeshBuilder::GenerateQuad("Box_side", brown, 1, 1);
	meshList[QUAD_BOX]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[QUAD_BOX]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[QUAD_BOX]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[QUAD_BOX]->material.kShininess = 1.f;


	meshList[CHICK_BODY] = MeshBuilder::GenerateSphere("Chick", Chick_color, 30, 30, 1);
	meshList[CHICK_BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[CHICK_BODY]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[CHICK_BODY]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[CHICK_BODY]->material.kShininess = .5f;

	meshList[CHICK_BEAK] = MeshBuilder::GenerateCone("Chick beak", Chick_beak, 30, 4, 1, 1);
	meshList[CHICK_BEAK]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[CHICK_BEAK]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[CHICK_BEAK]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[CHICK_BEAK]->material.kShininess = .6f;

	meshList[CHICK_WING] = MeshBuilder::GenerateCircle("Chick wing", Chick_color, 30, 1);
	meshList[CHICK_WING]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[CHICK_WING]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[CHICK_WING]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[CHICK_WING]->material.kShininess = .5f;

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

	glEnable(GL_CULL_FACE);

	m_programID = LoadShaders( "Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader" );
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


	glUseProgram(m_programID);
	

	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
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


	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
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

}

void Assignment1::Update(double dt)
{
	camera.Update(dt);

	rotateAngle += (float)(50 * dt);
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

	if (Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('U'))
		lights[0].position.y += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('T'))
		lights[0].isOn = false;
	if (Application::IsKeyPressed('Y'))
		lights[0].isOn = true;

	if (Application::IsKeyPressed(VK_DOWN))
		lights[1].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed(VK_UP))
		lights[1].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed(VK_LEFT))
		lights[1].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed(VK_RIGHT))
		lights[1].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		lights[1].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('U'))
		lights[1].position.y += (float)(LSPEED * dt);


	//editor commands
	//if (Application::IsKeyPressed(VK_DOWN))
	//	y_value -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed(VK_UP))
	//	y_value += (float)(LSPEED * dt);
	//if (Application::IsKeyPressed(VK_LEFT))
	//	x_value -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed(VK_RIGHT))
	//	x_value += (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('Z'))
	//	z_value -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('X'))
	//	z_value += (float)(LSPEED * dt);

	if (Application::IsKeyPressed('G'))
	{
		camera.Reset();
	}

	if (Application::IsKeyPressed('F'))
	{
		chick_flap = false;
		capoo_running = false;
		capoo_blinking = false;
		chick_blinking = false;

		animation1 = false;
		angle_chick = 0;
		angle_capoo = 0;
		chickDir = 0;
		jump_chickX = 0;
		jump_chickY = 0;
		chickJumpDirX = 0;
		chickJumpDirY = 0;
		jump_capooZ = 0;
		jump_capooY = 0;
		capooJumpDirZ = 0;
		capooJumpDirY = 0;
		rotateAngle = 0;
	}


	if (Application::IsKeyPressed('X'))
	{
		animation1 = true;
		capooDir = 1;
		chickDir = -1;
		angle_capoo = 1;
		angle_chick = 1;
		jump_chickX = -17.68f;
		jump_chickY = 13.1f;
		chickJumpDirX = 1;
		chickJumpDirY = 1;
		jump_capooZ = 0;
		jump_capooY = 0;
		capooJumpDirZ = 0;
		capooJumpDirY = 0;
		rotateAngle = 0;
	}

	if (Application::IsKeyPressed('C'))
	{
		wingDir = 1;
		angle_wing = 0;
		chick_flap = true;
	}
	if (Application::IsKeyPressed('V'))
	{
		legDir = 1;
		angle_leg = 0;
		capoo_running = true;
	}
	if (Application::IsKeyPressed('B'))
	{
		eyeMove_capoo = -1;
		eyeMove_chick = -1;
		eye_capoo = .3f;
		eye_chick = .2f;
		capoo_blinking = true;
		chick_blinking = true;
	}

	if (Application::IsKeyPressed('5'))
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
	}

	//animation1
	if (animation1)
	{

		//Capoo movement
		angle_capoo += (float)(capooDir * 40 * dt);
		if (angle_capoo >= 100)
			capooDir = 0;

		jump_capooZ += (float)(capooJumpDirZ * 40 * dt);
		jump_capooY += (float)(capooJumpDirY * 40 * dt);

		if ((jump_chickY <= -2) && (jump_capooZ == 0))
		{
			capooJumpDirZ = -1;
			capooJumpDirY = 1;
		}

		if (jump_capooY >= 18.f)
			capooJumpDirY = -1;
		if (jump_capooY <= -2)
			capooJumpDirY = 0;
		if (jump_capooZ < -26)
			capooJumpDirZ = 0;

		//chick movement
		angle_chick += (float)(chickDir * 40 * dt);
		if (angle_chick < -85)
			chickDir *= -1;
		
		if (jump_chickY >= 15)
			chickJumpDirY = -1;
		if (jump_chickY <= -2)
			chickJumpDirY = 0;
		if (jump_chickX > -7)
			chickJumpDirX = 0;

		if (angle_chick >= .5f)
		{
			chickDir = 0;
			jump_chickX += (float)(chickJumpDirX * 40 * dt);
			jump_chickY += (float)(chickJumpDirY * 40 * dt);
		}
	}
	//Capoo run
	if (capoo_running)
	{
		angle_leg += (float)(legDir * 40 * dt);
		if ((angle_leg > 15) || (angle_leg < -15))
			legDir *= -1;
	}

	//Chick flapping wings
	if (chick_flap)
	{
		angle_wing += (float)(wingDir * 40 * dt);
		if ((angle_wing > 15) || (angle_wing < -15))
			wingDir *= -1;

		angle_wing += (float)(wingDir * 40 * dt);
		if ((angle_wing > 15) || (angle_wing < -15))
			wingDir = -1;
	}

	//Blinking
	if (capoo_blinking)
	{
		eye_capoo += (float)(eyeMove_capoo * .5f * dt);

		if ((eye_capoo <= 0.05f) || (eye_capoo >= .3f))
			eyeMove_capoo *= -1;
	}
	if (chick_blinking)
	{
		eye_chick += (float)(eyeMove_chick * .2f * dt);
		if ((eye_chick <= 0.05f) || (eye_chick >= .2f))
			eyeMove_chick *= -1;
	}

}

void Assignment1::Render() //My Own Pattern
{
	// Render VBO here

	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 model2;*/
	//Mtx44 view;
	//Mtx44 projection;
	//Mtx44 MVP;

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

	/*meshList[GEO_AXES]->Render();
	modelStack.PopMatrix();*/

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(lights[1].position.x, lights[1].position.y, lights[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0, .0056f);
	RenderMesh(meshList[GEO_QUAD], lights[0].isOn);
	modelStack.PopMatrix();

	//Box

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -43.6f);
	modelStack.Scale(1, 1, 1.5f);

	modelStack.PushMatrix();
	modelStack.Scale(35, 17, 1);
	modelStack.Translate(0, 0.17f, 0);
	RenderMesh(meshList[QUAD_BOX], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 17);
	RenderMesh(meshList[QUAD_BOX], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Scale(.05882f, 1, 1);
	modelStack.Translate(8.5f, 0, -8.5f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(17, 1, 1);
	RenderMesh(meshList[QUAD_BOX], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -17.f);
	RenderMesh(meshList[QUAD_BOX], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Translate(0, -.45f, 8.5);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1, 17, 1);
	RenderMesh(meshList[QUAD_BOX], lights[0].isOn);

	
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//CAPOO
	modelStack.PushMatrix();
	//Capoo - Animation (Whole Body)
	if (animation1 && chickJumpDirY == 0)
		modelStack.Translate(0, jump_capooY, jump_capooZ);

	modelStack.Rotate(angle_capoo, 0, 1, 0);
	modelStack.Scale(.4f, .4f, .4f);


	modelStack.PushMatrix();
	modelStack.Scale(14, 14, 14);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(meshList[CAPOO_CYLINDER], lights[0].isOn);

	//Pattern on back
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(-.53f, .2f, -.4f);
	modelStack.Translate(0,1.08f, 0);
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
	if (capoo_blinking)
	{
		modelStack.Scale(eye_capoo, .3f, .3f);
	}
	else
		modelStack.Scale(.3f,.3f,.3f);
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
	modelStack.Translate(0,0,5);
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

	//Item - Chick
	modelStack.PushMatrix();
	if (animation1)
	{
		modelStack.Translate(jump_chickX, jump_chickY, -34.f);
	}
	else
		modelStack.Translate(-17.68f, 13.1f, -34.f);
	modelStack.Rotate(angle_chick, 0, 1, 0);
	modelStack.Scale(2, 2, 2);

	modelStack.PushMatrix();
	RenderMesh(meshList[CHICK_BODY], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Scale(.3f, .3f, .3f);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(.75f, 1.f, 1.f);
	modelStack.Translate(-1.1f,3.57f, 0);
	RenderMesh(meshList[CHICK_BEAK], lights->isOn);
	modelStack.PopMatrix();

	//eyes
	modelStack.PushMatrix(); 
	modelStack.Translate(.68f, .51f, -.51f);
	if (chick_blinking)
	{
		modelStack.Scale(.2f, eye_chick, .2f);
	}
	else
		modelStack.Scale(.2f, .2f, .2f);
	RenderMesh(meshList[EYE], lights[0].isOn);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 4.2f);
	RenderMesh(meshList[EYE], lights[0].isOn);

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//wings
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, .68f);
	if (chick_flap)
	{
		modelStack.Rotate(angle_wing, 1, 0, 0);
	}
	modelStack.Scale(.5f, .7f, .7f);
	RenderMesh(meshList[CHICK_WING], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -.68f);
	if (chick_flap)
	{
		modelStack.Rotate(-angle_wing, 1, 0, 0);
	}
	modelStack.Scale(.5f, .7f, .7f);
	RenderMesh(meshList[CHICK_WING], lights[0].isOn);
	modelStack.PopMatrix();
	
	modelStack.PopMatrix();
	modelStack.PopMatrix();

}



void Assignment1::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}

void Assignment1::RenderMesh(Mesh* mesh, bool enableLight)
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
	mesh->Render();
}
