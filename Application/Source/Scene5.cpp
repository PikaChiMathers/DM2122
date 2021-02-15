#include "Scene5.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"

#include "Application.h"


Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}


void Scene5::Init() 
{
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

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

	moonshade.Set(0.93f, 0.93f, 0.88f);
	
	meshList[MOON] = MeshBuilder::GenerateSphere("Moon", moonshade, 30, 30, 1);
	
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad",red, 1, 1);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", red, 1, 1, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", pink, 30, 30, 1);
	meshList[MOON] = MeshBuilder::GenerateSphere("moon", moonshade, 30, 30, 1);
	
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Lblue, 30, 1);

	glEnable(GL_CULL_FACE);

	//Load vertex and fragment shaders (Step 6a)
	m_programID = LoadShaders
	(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader"); //New Shaders

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");

	//Use our shader (Step 6b)
	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

}

void Scene5::Update(double dt)
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

}

void Scene5::Render() //My Own Pattern
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


	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP
	meshList[GEO_AXES]->Render();

	modelStack.PushMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(2, 2, 2);
	modelStack.Rotate((-1 * rotateAngle), 1, 0, 1);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP
	meshList[GEO_CIRCLE]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(1.4f, 1.4f, 1.4f);
	modelStack.Rotate((2 * rotateAngle), 1, 1, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP
	Mesh* purpCircle = MeshBuilder::GenerateCircle("purple circle", purple, 30, 1);
	purpCircle->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP
	meshList[GEO_SPHERE]->Render();

	modelStack.PushMatrix();
	modelStack.PushMatrix();
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(10, 10, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP
	meshList[MOON]->Render();
	modelStack.PopMatrix();



}

void Scene5::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}
