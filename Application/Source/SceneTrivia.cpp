#define LSPEED 10.f
#include "SceneTrivia.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Utility.h"
#include "LoadTGA.h"

#include "Application.h"


SceneTrivia::SceneTrivia()
{
}

SceneTrivia::~SceneTrivia()
{
}


void SceneTrivia::Init()
{
	camera.Init(Vector3(0, 9.2f, -23), Vector3(0, 9.15f, -22), Vector3(0, 1, 0.05f));

	manager.CreateGameObject(&goose);

	//Initializes the Podiums A, B & C
	manager.CreateGameObject(&P_A);
	manager.CreateGameObject(&P_B);
	manager.CreateGameObject(&P_C);

	//Initializes Trigger (Checks whether the player presses spacebar in a cerrtain area) of each podium
	manager.CreateGameObject(&T_A);
	manager.CreateGameObject(&T_B);
	manager.CreateGameObject(&T_C);

	//Sets the position of each Object
	goose.SetRotateY(180);
	goose.SetPosition(Position(0, -.5f, -5));

	P_A.SetPosition(Position(5, 0, 0));
	P_B.SetPosition(Position(0, 0, 0));
	P_C.SetPosition(Position(-5, 0, 0));

	T_A.SetPosition(Position(5, 0, 0));
	T_B.SetPosition(Position(0, 0, 0));
	T_C.SetPosition(Position(-5, 0, 0));

	is_correct = false;
	press_time = qn_num = score = 0;
	Qn = new Dialogue("Dialogue//Trivia.txt", Dialogue::TRIVIA);
	Qn_str = "";

	answer = ANS_TYPE::Blank;

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	rotateAngle = 0;

	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	UI_width = 160;
	UI_height = 90;

	x_value = y_value = z_value = 0;

	meshList[GEO_GOOSE] = MeshBuilder::GenerateOBJMTL("Goose", "OBJ//goose.obj", "OBJ//goose.mtl");

	meshList[GEO_PODIUM_A] = MeshBuilder::GenerateOBJ("A", "OBJ//podium.obj", Color(1, 0, 0));
	meshList[GEO_PODIUM_B] = MeshBuilder::GenerateOBJ("B", "OBJ//podium.obj", Color(0, 1, 0));
	meshList[GEO_PODIUM_C] = MeshBuilder::GenerateOBJ("C", "OBJ//podium.obj", Color(0, 0, 1));

	meshList[GEO_TV] = MeshBuilder::GenerateQuad("television", Color(1, 1, 1), 1, 1);
	meshList[GEO_TV]->textureID = LoadTGA("Image//television.tga");
	meshList[GEO_TV]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TV]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_TV]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_TV]->material.kShininess = 1.f;

	meshList[GEO_LOGO] = MeshBuilder::GenerateQuad("logo", Color(1, 1, 1), 1, 1);
	meshList[GEO_LOGO]->textureID = LoadTGA("Image//trivia_logo.tga");
	meshList[GEO_LOGO]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LOGO]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_LOGO]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LOGO]->material.kShininess = 1.f;

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", lights[0].color, 30, 30, 1);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(.04f, .71f, 1), 1.f, 1.f);
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(.04f, .71f, 1), 1.f, 1.f);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", Color(.39f, .39f, .39f), 1.f, 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//carpet.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 1, 1, 1);
	meshList[GEO_CUBE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CUBE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_CUBE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_CUBE]->material.kShininess = 1.f;
	meshList[GEO_CUBE]->textureID = LoadTGA("Image//muscle_capoo.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//trebuchet.tga");

	glDisable(GL_CULL_FACE);
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

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);


	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 10;
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

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void SceneTrivia::Update(double dt)
{
	manager.GameObjectManagerUpdate(dt);

	//editor controls
	{
		if (Application::IsKeyPressed('I'))
			z_value -= (float)(LSPEED * dt);
		if (Application::IsKeyPressed('K'))
			z_value += (float)(LSPEED * dt);
		if (Application::IsKeyPressed('J'))
			x_value -= (float)(LSPEED * dt);
		if (Application::IsKeyPressed('L'))
			x_value += (float)(LSPEED * dt);
		if (Application::IsKeyPressed('O'))
			y_value -= (float)(LSPEED * dt);
		if (Application::IsKeyPressed('U'))
			y_value += (float)(LSPEED * dt);
		if (Application::IsKeyPressed('T'))
			lights[0].isOn = false;
		if (Application::IsKeyPressed('Y'))
			lights[0].isOn = true;
	}

	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

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

	if (Application::IsKeyPressed(VK_SPACE))
	{
		press_time++;
		if (press_time == 1) // To ensure that the Spacebar is only pressed once
		{
			if (T_A.IsTriggered())
			{
				answer = ANS_TYPE::A;
			}
			else if (T_B.IsTriggered())
			{
				answer = ANS_TYPE::B;
			}
			else if (T_C.IsTriggered())
			{
				answer = ANS_TYPE::C;
			}

			if (answer != ANS_TYPE::Blank && qn_num != 0) Check_Answer();

			if (qn_num == 0)
			{
				qn_num++;
				Qn_str = Qn->Update();
			}
			else
				qn_num++;
		}
	}
	else press_time = 0;
}

void SceneTrivia::Render() //My Own Pattern
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
	modelStack.Scale(50, 50, 50);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 12.6f, 23.8f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(50, 25, 25);
	RenderMesh(meshList[GEO_TV], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(P_A.GetPositionX(), P_A.GetPositionY(), P_A.GetPositionZ());
	modelStack.Scale(1, 1.5f, 1);
	RenderMesh(meshList[GEO_PODIUM_A], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5.44f, 2.55f, 3.4f);
	modelStack.Rotate(180, 0, 1, 0);
	RenderText(meshList[GEO_TEXT], "A", Color(1, 1, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(P_B.GetPositionX(), P_B.GetPositionY(), P_B.GetPositionZ());
	modelStack.Scale(1, 1.5f, 1);
	RenderMesh(meshList[GEO_PODIUM_B], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-.30f, 2.55f, 3.4f);
	modelStack.Rotate(180, 0, 1, 0);
	RenderText(meshList[GEO_TEXT], "B", Color(1, 1, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(P_C.GetPositionX(), P_C.GetPositionY(), P_C.GetPositionZ());
	modelStack.Scale(1, 1.5f, 1);
	RenderMesh(meshList[GEO_PODIUM_C], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5.72f, 2.55f, 3.4f);
	modelStack.Rotate(180, 0, 1, 0);
	RenderText(meshList[GEO_TEXT], "C", Color(1, 1, 1));
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	if (qn_num == 0)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Trivia", Color(0, 1, 0), 10, 63, 67);
		RenderTextOnScreen(meshList[GEO_TEXT], "Use WASD to move to A, B or C", Color(0, 1, 0), 2.5f, 57, 59);
		RenderTextOnScreen(meshList[GEO_TEXT], "Spacebar to select & start", Color(0, 1, 0), 2.5f, 59, 52);
	}
	else if (qn_num <= 10)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], (std::to_string(score)) + "/10", Color(0, 1, 0), 6, 110, 76);
		RenderTextOnScreen(meshList[GEO_TEXT], ("Q" + std::to_string(qn_num) + ":" + Qn_str), Color(0, 1, 0), 2.44f, 37, 65);
		RenderTextOnScreen(meshList[GEO_TEXT], ("A:" + Qn->getChoice1()), Color(0, 1, 0), 4, 40, 57);
		RenderTextOnScreen(meshList[GEO_TEXT], ("B:" + Qn->getChoice2()), Color(0, 1, 0), 4, 40, 51);
		RenderTextOnScreen(meshList[GEO_TEXT], ("C:" + Qn->getChoice3()), Color(0, 1, 0), 4, 40,45);
	}
	else
	{
		RenderTextOnScreen(meshList[GEO_TEXT], (std::to_string(score) + "/10"), Color(0, 1, 0), 10, 72, 53);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-19, 13.4f, 23.3f);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[GEO_LOGO], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(19, 13.4f, 23.3f);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[GEO_LOGO], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(goose.GetPositionX(), goose.GetPositionY(), goose.GetPositionZ());
	modelStack.Rotate(goose.GetRotateX(), 1, 0, 0);
	modelStack.Rotate(goose.GetRotateY(), 0, 1, 0);
	modelStack.Rotate(goose.GetRotateZ(), 0, 0, 1);
	RenderMesh(meshList[GEO_GOOSE], true);
	modelStack.PopMatrix();
}

void SceneTrivia::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}

void SceneTrivia::Check_Answer()//Checks the player's answer input and adds points respectfully
{
	is_correct = false;

	goose.SetRotateY(180);
	goose.SetPosition(Position(0, 0, -5));

	if (qn_num == 1)
	{
		if (answer == ANS_TYPE::C)
			is_correct = true;
	}
		
	else if (qn_num == 2)
	{
		if (answer == ANS_TYPE::A)
			is_correct = true;
	}
		
	else if (qn_num == 3)
	{
		if (answer == ANS_TYPE::B)
			is_correct = true;
	}
		
	else if (qn_num == 4)
	{
		if (answer == ANS_TYPE::B)
			is_correct = true;
	}
		
	else if (qn_num == 5)
	{
		if (answer == ANS_TYPE::A)
			is_correct = true;
	}
		
	else if (qn_num == 6)
	{
		if (answer == ANS_TYPE::C)
			is_correct = true;
	}
		
	else if (qn_num == 7)
	{
		if (answer == ANS_TYPE::A)
			is_correct = true;
	}
		
	else if (qn_num == 8)
	{
		if (answer == ANS_TYPE::C)
			is_correct = true;
	}
		
	else if (qn_num == 9)
	{
		if (answer == ANS_TYPE::B)
			is_correct = true;
	}
		
	else if (qn_num == 10)
	{
		if (answer == ANS_TYPE::C)
			is_correct = true;
	}

	answer = ANS_TYPE::Blank;
	Qn_str = Qn->Update();
	if (is_correct)
		score++;
}

void SceneTrivia::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneTrivia::RenderSkybox()
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
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(50, 50, 50);
	RenderMesh(meshList[GEO_TOP], true);
	modelStack.PopMatrix();
}

void SceneTrivia::RenderText(Mesh* mesh, std::string text, Color color)
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
		characterSpacing.SetToTranslation(i * 0.7f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneTrivia::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
		characterSpacing.SetToTranslation(i * .7f, 0.5f, 0);
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

void SceneTrivia::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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