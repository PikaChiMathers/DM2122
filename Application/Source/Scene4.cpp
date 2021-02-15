#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"

#include "Application.h"


Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}


void Scene4::Init() 
{

	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Commented
	/*meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);*/


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

	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void Scene4::Update(double dt)
{
	camera.Update(dt);

	rotateAngle += (float)(rotateDir * 500 * dt);
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

void Scene4::Render() //My Own Pattern
{
	// Render VBO here


	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 model2;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;


	//projection.SetToOrtho(-40, +40, -30, +30, -10, +10); //Our world is a cube defined by these boundaries

	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	//view.SetToIdentity(); //no need camera for now, set it at World's origin
	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	/*meshList[GEO_AXES]->Render();
	meshList[GEO_QUAD]->Render();*/


	//Cube
	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	meshList[GEO_CUBE]->Render();

}

void Scene4::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}
