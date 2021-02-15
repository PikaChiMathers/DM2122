#define LSPEED 10.f
#include "SceneLight2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Utility.h"

#include "Application.h"


SceneLight2::SceneLight2()
{
}

SceneLight2::~SceneLight2()
{
}


void SceneLight2::Init() 
{
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	rotateAngle = 0;

	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);


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
	

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Rsphere", red, 30, 30, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_SPHERE1] = MeshBuilder::GenerateSphere("Bsphere", blue, 30, 30, 1);
	meshList[GEO_SPHERE1]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE1]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE1]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE1]->material.kShininess = 1.f;

	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("Gsphere", green, 30, 30, 1);
	meshList[GEO_SPHERE2]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE2]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE2]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE2]->material.kShininess = 1.f;

	meshList[GEO_SPHERE3] = MeshBuilder::GenerateSphere("Psphere", pink, 30, 30, 1);
	meshList[GEO_SPHERE3]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE3]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE3]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE3]->material.kShininess = 1.f;

	meshList[GEO_SPHERE4] = MeshBuilder::GenerateSphere("LBsphere", Lblue, 30, 30, 1);
	meshList[GEO_SPHERE4]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE4]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE4]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE4]->material.kShininess = 1.f;

	meshList[GEO_SPHERE5] = MeshBuilder::GenerateSphere("PRsphere", purple, 30, 30, 1);
	meshList[GEO_SPHERE5]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE5]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE5]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE5]->material.kShininess = 1.f;

	meshList[GEO_SPHERE6] = MeshBuilder::GenerateSphere("Ysphere", yellow, 30, 30, 1);
	meshList[GEO_SPHERE6]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE6]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE6]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE6]->material.kShininess = 1.f;

	meshList[GEO_SPHERE7] = MeshBuilder::GenerateSphere("Csphere", cyan, 30, 30, 1);
	meshList[GEO_SPHERE7]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE7]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE7]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE7]->material.kShininess = 1.f;

	meshList[GEO_SPHERE8] = MeshBuilder::GenerateSphere("Msphere", magenta, 30, 30, 1);
	meshList[GEO_SPHERE8]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE8]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE8]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE8]->material.kShininess = 1.f;

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", lights[0].color, 30, 30, 1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", blue, 1, 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

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

void SceneLight2::Update(double dt)
{
	camera.Update(dt);

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

}

void SceneLight2::Render() //My Own Pattern
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
	modelStack.Scale(50, 50, 50);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(2, 2, 2);
	modelStack.Translate(0, 1, 0);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Scale(2, 2, 2);
	//modelStack.Translate(-2, 1, 2);
	//RenderMesh(meshList[GEO_SPHERE1], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Scale(2, 2, 2);
	//modelStack.Translate(-2, 1, -2);
	//RenderMesh(meshList[GEO_SPHERE2], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Scale(2, 2, 2);
	//modelStack.Translate(2, 1, 2);
	//RenderMesh(meshList[GEO_SPHERE3], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Scale(2, 2, 2);
	//modelStack.Translate(2, 1, -2);
	//RenderMesh(meshList[GEO_SPHERE4], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Scale(2, 2, 2);
	//modelStack.Translate(2, 1, 0);
	//RenderMesh(meshList[GEO_SPHERE5], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Scale(2, 2, 2);
	//modelStack.Translate(-2, 1, 0);
	//RenderMesh(meshList[GEO_SPHERE6], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Scale(2, 2, 2);
	//modelStack.Translate(0, 1, 2);
	//RenderMesh(meshList[GEO_SPHERE7], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Scale(2, 2, 2);
	//modelStack.Translate(0, 1, -2);
	//RenderMesh(meshList[GEO_SPHERE8], true);
	//modelStack.PopMatrix();
}



void SceneLight2::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}

void SceneLight2::RenderMesh(Mesh* mesh, bool enableLight)
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
