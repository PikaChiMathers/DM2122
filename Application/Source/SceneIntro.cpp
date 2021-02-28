#define LSPEED 10.f
#include "SceneIntro.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Sound.h"
#include "irrKlang.h"

#include "Application.h"


SceneIntro::SceneIntro()
{
	honk_count = 1;
}

SceneIntro::~SceneIntro()
{
}


void SceneIntro::Init()
{
	manager.CreateGameObject(&goose);
	goose.SetPosition(Position (-15, -3, 0));
	manager.CreateGameObject(&boss);
	boss.SetPosition(Position(0, -4, 0));
	boss.SetScale(Scale(2, 4, 2));
	manager.CreateGameObject(&bosscollider);
	bosscollider.SetPosition(Position(0, -4, 0));
	bosscollider.SetScale(Scale(7, 9, 7));

	camera.Init(Vector3(-0.7, 39, -68), Vector3(-0.67, 38.65, -67), Vector3(0, 1, 0));
	map.Set(Maps::SKYBOX_TYPE::SB_INTRO);

	//map.Set(Maps::MAP_TYPE::M_CITY, Maps::SKYBOX_TYPE::SB_DAY);

	dialogue = new Dialogue("Dialogue//D1.txt", Dialogue::DIALOGUE);

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



	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", lights[0].color, 30, 30, 1);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("ground", Color(.39f, 0.72f, 1.f), 1.f, 1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//trebuchet.tga");

	meshList[GEO_UI] = MeshBuilder::GenerateQuad("UI", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_BOSS] = MeshBuilder::GenerateOBJ("Boss", "OBJ//goose.obj", Color(.42f, .26f, .15f));
	meshList[GEO_BOSS]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOSS]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_BOSS]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BOSS]->material.kShininess = 1.f;

	meshList[GEO_GOOSE] = MeshBuilder::GenerateOBJ("Goose", "OBJ//goose.obj", Color(.93f, .79f, 0));
	meshList[GEO_GOOSE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_GOOSE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_GOOSE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_GOOSE]->material.kShininess = 1.f;

	meshList[GEO_PINKLILY] = MeshBuilder::GenerateOBJ("PinkLily", "OBJ//pink_water_lily.obj", Color(0 , .79f, 0));

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
	lights[0].position.Set(0, 48, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 4;
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

}

void SceneIntro::Update(double dt)
{
	
	manager.GameObjectManagerUpdate(dt);
	//camera.Update(dt);

	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	//for testing purposes
	if (Application::IsKeyPressed('V'))
	{
		scene_change = true;
		map.Set(Maps::SKYBOX_TYPE::SB_DAY);
	}
	if (Application::IsKeyPressed('B'))
	{
		scene_change = true;
		map.Set(Maps::SKYBOX_TYPE::SB_NIGHT);
	}


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

	if (Application::IsKeyPressed(VK_SPACE))
		if (dialogue->getCurrentLine() < dialogue->getTotalLines())
			std::cout << dialogue->Update() << std::endl;

	if (Application::IsKeyPressed(VK_SPACE))
	{
		dialogue->Update();
			if (dialogue->getPersonTalking() == "Boss Goose")
			{
				meshList[GEO_UI]->textureID = LoadTGA("Assets//Boss Dialogue Box.tga");
			}
			else if (dialogue->getPersonTalking() == "Boss Duck")
			{
				meshList[GEO_UI]->textureID = LoadTGA("Assets//Duck Dialogue Box.tga");
			}
	}

	if (bosscollider.IsTriggered())
	{
		std::cout << "boss triggered" ;
	}

	//if (dialogue->getPersonTalking() = 2)
	//{
	//}
}

void SceneIntro::Render() //My Own Pattern
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


	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();
	RenderSkybox();

	modelStack.PushMatrix();
	modelStack.Translate(0, -.1f, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(200, 200, 200);
	RenderMesh(meshList[GEO_QUAD], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(boss.GetPositionX(), boss.GetPositionY(), boss.GetPositionZ());
	modelStack.Scale(2, 2, 2);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOSS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(goose.GetPositionX()*2, goose.GetPositionY(), goose.GetPositionZ()*2);
	modelStack.Rotate(goose.GetRotateX(), 1, 0, 0);
	modelStack.Rotate(goose.GetRotateY(), 0, 1, 0);
	modelStack.Rotate(goose.GetRotateZ(), 0, 0, 1);
	modelStack.Scale(1.5f, 1.5f, 1.5f);
	RenderMesh(meshList[GEO_GOOSE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(36, 0, 23);
	/*modelStack.Rotate(-90, 0, 0, 0);*/
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_PINKLILY], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 0, -18);
	/*modelStack.Rotate(-90, 0, 0, 0);*/
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_PINKLILY], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-22, 0, -10);
	/*modelStack.Rotate(-90, 0, 0, 0);*/
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_PINKLILY], true);
	modelStack.PopMatrix();


	/*RenderMeshOnScreen(meshList[GEO_SPLASH], 1, 1, 10, 10);*/
}

void SceneIntro::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}

void SceneIntro::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneIntro::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(50, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-50, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 50);
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -50);
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 50, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
}

void SceneIntro::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneIntro::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneIntro::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}