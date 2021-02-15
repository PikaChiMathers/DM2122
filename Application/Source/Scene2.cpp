#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

//void Scene2::Init()
//{
//	// Init VBO here
//
//	//Set background color to dark blue (Step 3a)
//	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//
//	//Generate a default VAO (Step 4a)
//	glGenVertexArrays(1, &m_vertexArrayID);
//	glBindVertexArray(m_vertexArrayID);
//
//	//Generate buffers (Step 4b)
//	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
//	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
//
//	//An array of 3 vectors which represent 3 vertices (Step 4c)
//	static const GLfloat vertex_buffer_data[] = {
//
//		//0.0f, 1.0f, 0.5f, //vertex 0 of triangle
//		//-1.0f, 0.0f, 0.5f, //vertex 1 of triangle
//		//1.0f, 0.0f, 0.5f, //vertex 2 of triangle
//
//		-0.5f, 0.5f, 0.0f,
//		-0.5f, 0.0f, 0.0f,
//		0.0f, 0.5f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//		0.5f, 0.5f, 0.0f,
//		0.5f, 0.0f, 0.0f,
//
//	};
//
//	//Set the current active buffer (Step 4d)
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
//
//	//Transfer vertices to OpenGL (Step 4e)
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
//
//	//An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
//	static const GLfloat color_buffer_data[] = {
//		//0.0f, 1.0f, 0.0f, //color of vertex 0
//		//0.0f, 0.0f, 1.0f, //color of vertex 1
//		//1.0, 0.0f, 0.0f, //color of vertex 2
//
//		1.0f, 0.0f, 0.0f,
//		1.0f, 0.0f, 0.0f,
//		1.0f, 0.0f, 0.0f,
//		1.0f, 0.0f, 0.0f,
//		1.0f, 0.0f, 0.0f,
//		1.0f, 0.0f, 0.0f,
//	};
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), 
//		color_buffer_data, GL_STATIC_DRAW);
//
//
//
//
//	//Attempt at second triangle
//
//
//	//Generate buffers (Step 4b)
//	//glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[1]);
//	//glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[1]);
//
//	//An array of 3 vectors which represent 3 vertices (Step 4c)
//	static const GLfloat vertex_buffer_data_2[] = {
//
//		1.0f, 1.0f, 0.0f, //vertex 0 of triangle
//		0.0f, 0.0f, 0.0f, //vertex 1 of triangle
//		1.0f, -1.0f, 0.0f, //vertex 2 of triangle
//	};
//
//	//Set the current active buffer (Step 4d)
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
//
//	//Transfer vertices to OpenGL (Step 4e)
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2), vertex_buffer_data_2, GL_STATIC_DRAW);
//
//
//	//An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
//	static const GLfloat color_buffer_data_2[] = {
//		1.0f, 1.0f, 0.0f, //color of vertex 0
//		1.0f, 1.0f, 0.0f, //color of vertex 1
//		1.0, 1.0f, 0.0f, //color of vertex 2
//	};
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2),
//		color_buffer_data_2, GL_STATIC_DRAW);
//
//
//
//
//	//Load vertex and fragment shaders (Step 6a)
//	m_programID = LoadShaders
//	(
//		"Shader//SimpleVertexShader.vertexshader",
//		"Shader//SimpleFragmentShader.fragmentshader"
//	);
//
//	//Use our shader (Step 6b)
//	glUseProgram(m_programID);
//
//	// Enable depth test
//	glEnable(GL_DEPTH_TEST);
//
//
//}


void Scene2::Init() //My Own Pattern
{
	// Init VBO here

	rotateAngle = 0;
	translateX = -35;
	translateY = -30;
	translateXDir = 1;
	translateYDir = 0;
	rotateDir = 0;
	scaleDir = 1;
	scaleAll = 4;
	box_TY = -18;
	box_TYDir = 0;

	num_hearts = 5;
	
	for (int h = 0; h < num_hearts; h++)
	{
		hearts_TXDir[h] = 0;
		hearts_TYDir[h] = 0;
	}

	hearts_TX[0] = -15;
	hearts_TX[1] = -13;
	hearts_TX[2] = 0;
	hearts_TX[3] = 18;
	hearts_TX[4] = 20;

	hearts_Yorigin[0] = hearts_TY[0] = -15;
	hearts_Yorigin[1] = hearts_TY[1] = -13;
	hearts_Yorigin[2] = hearts_TY[2] = -18;
	hearts_Yorigin[3] = hearts_TY[3] = -13;
	hearts_Yorigin[4] = hearts_TY[4] = -15;


	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers (Step 4b)
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);


	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f, // Coordinates of points(x, y, z)
		-0.1f, 0.6f, 0.0f,
		-0.5f, 0.75f, 0.0f,
		-0.8f, 0.4f, 0.0f,
		0.0, -0.9f, 0.0f,
		0.8f, 0.4f, 0.0f,
		0.5f, 0.75f, 0.0f,
		0.1f, 0.6f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};

	//Set the current active buffer (Step 4d)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);


	////An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
	//static const GLfloat color_buffer_data[] = {
	//	1.0f, 0.55f, 0.6f,
	//	1.0f, 0.55f, 0.6f,
	//	1.0f, 0.55f, 0.6f,
	//	1.0f, 0.55f, 0.6f,
	//	1.0f, 0.55f, 0.6f,
	//	1.0f, 0.55f, 0.6f,
	//	1.0f, 0.55f, 0.6f,
	//	1.0f, 0.55f, 0.6f,
	//	1.0f, 0.55f, 0.6f,
	//};

	//An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
	static const GLfloat color_buffer_data[] = {
		1.0f, 0.55f, 0.6f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
		color_buffer_data, GL_STATIC_DRAW);


	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data_2[] = {
		1.0f, 1.0f, 0.0f, // Coordinates of points(x, y, z)
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};

	//Set the current active buffer (Step 4d)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2), vertex_buffer_data_2, GL_STATIC_DRAW);


	////An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
	//static const GLfloat color_buffer_data_2[] = {
	//	0.2f, 0.55f, 0.2f,
	//	0.2f, 0.55f, 0.2f,
	//	0.2f, 0.55f, 0.2f,
	//	0.2f, 0.55f, 0.2f,
	//	0.2f, 0.55f, 0.2f,
	//	0.2f, 0.55f, 0.2f,
	//};

	//An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
	static const GLfloat color_buffer_data_2[] = {
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2),
		color_buffer_data_2, GL_STATIC_DRAW);

	//Inner box
	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data_2_inner[] = {
		1.0f, 1.0f, 0.0f, // Coordinates of points(x, y, z)
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};

	//Set the current active buffer (Step 4d)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2_INNER]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2_inner), vertex_buffer_data_2_inner, GL_STATIC_DRAW);

	//An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
	static const GLfloat color_buffer_data_2_inner[] = {
		0.63f, 0.63f, 0.63f,
		0.63f, 0.63f, 0.63f,
		0.63f, 0.63f, 0.63f,
		0.63f, 0.63f, 0.63f,
		0.63f, 0.63f, 0.63f,
		0.63f, 0.63f, 0.63f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2_INNER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2_inner),
		color_buffer_data_2_inner, GL_STATIC_DRAW);

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

void Scene2::Update(double dt)
{
	rotateAngle += (float)(rotateDir * 500 * dt);
	translateX += (float)(translateXDir * 10 * dt);
	translateY += (float)(translateYDir * 50 * dt);
	box_TY += (float)(box_TYDir * 10 * dt);
	scaleAll += (float)(scaleDir * 2 * dt);

	/*if ((rotateAngle > 360) || (rotateAngle < 0))
		rotateDir *= -1;*/
	if ((translateX > 40) || (translateX < -40))
		translateXDir *= -1;
	if ((translateY > 10))
		translateYDir = -1;
	if (translateY < -18)
	{
		translateYDir = 0;
		//rotateDir = 0;
	}
	if ((scaleAll > 5) || (rotateAngle < 1))
		scaleDir *= -1;

	if (box_TY > -11)
	{
		box_TYDir = -1;
	}
	if (box_TY < -18)
	{
		box_TYDir = 0;
	}

	for (int h = 0; h < num_hearts; h++)
	{
		hearts_TX[h] += (float)(hearts_TXDir[h] * 10 * dt);
		hearts_TY[h] += (float)(hearts_TYDir[h] * 40 * dt);

		if (hearts_TY[h] > (hearts_Yorigin[h] + 50))
			hearts_TYDir[h] = -1;
		if ((hearts_TX[h] > 40) || (hearts_TX[h] < -40))
			hearts_TXDir[h] *= -1;

		if (hearts_TY[h] < -16)
			hearts_TYDir[h] = 0;
	}

	/*if (Application::IsKeyPressed(VK_SPACE))*/
	if (Application::IsKeyPressed(VK_UP))
	{
		translateYDir = 1;
		box_TYDir = 1;
		rotateDir = 1;
		for (int h = 0; h < num_hearts; h++)
		{
			if (h % 2 == 0)
				hearts_TXDir[h] = 1;
			else
				hearts_TXDir[h] = -1;
			hearts_TYDir[h] = 1;
		}

	}


}

//void Scene2::Render()
//{
//	// Render VBO here
//
//	//Clear color buffer every frame (Step 3b)
//	/*glClear(GL_COLOR_BUFFER_BIT);*/
//
//	//Clear color & depth buffer every frame
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//	//Step 4f
//	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
//	//Step 5b
//	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
//
//	//Attempt at second triangle
//	//Step 4f
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
//	glVertexAttribPointer(
//		0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
//		3,         //size
//		GL_FLOAT,  //type
//		GL_FALSE,  //normalized?
//		0,         //stride
//		0          //array buffer offset
//	);
//
//	//Step 5b
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//
//	//Draw the triangle (Step 4g)
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); //Starting from vertex 0; 3 vertices  = 1 triangle
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
//	glVertexAttribPointer(
//		0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
//		3,         //size
//		GL_FLOAT,  //type
//		GL_FALSE,  //normalized?
//		0,         //stride
//		0          //array buffer offset
//	);
//
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//
//	//Draw the triangle (Step 4g)
//	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle
//
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
//
//
//
//
//	////Attempt at second triangle
//	////Step 4f
//	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
//	//glVertexAttribPointer(
//	//	0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
//	//	3,         //size
//	//	GL_FLOAT,  //type
//	//	GL_FALSE,  //normalized?
//	//	0,         //stride
//	//	0          //array buffer offset
//	//);
//
//	////Step 5b
//
//	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//
//	////Draw the triangle (Step 4g)
//	//glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices  = 1 triangle
//
//	glDisableVertexAttribArray(0);
//
//	//Step 5c
//	glDisableVertexAttribArray(1);
//}

void Scene2::Render() //My Own Pattern
{
	// Render VBO here

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 model2;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); //no need camera for now, set it at World's origin

		projection.SetToOrtho(-40, +40, -30, +30, -10, +10); //Our world is a cube defined by these boundaries


		//Clear color & depth buffer every frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Step 4f
		glEnableVertexAttribArray(0); //1st attribute buffer : vertices
		//Step 5b
		glEnableVertexAttribArray(1); //2nd attribute buffer: colors

		//Heart 1
		scale.SetToScale(8, 8, 8);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(hearts_TX[0], hearts_TY[0], -1);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]); //update the shader with new MVP

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(
			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
			3,         //size
			GL_FLOAT,  //type
			GL_FALSE,  //normalized?
			0,         //stride
			0          //array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Draw the triangle (Step 4g)
/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);


		//Heart 2
		scale.SetToScale(8, 8, 8);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(hearts_TX[1], hearts_TY[1], -1);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]); //update the shader with new MVP

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(
			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
			3,         //size
			GL_FLOAT,  //type
			GL_FALSE,  //normalized?
			0,         //stride
			0          //array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Draw the triangle (Step 4g)
/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);



		//Heart 3
		scale.SetToScale(8, 8, 8);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(hearts_TX[2], hearts_TY[2], -1);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]); //update the shader with new MVP

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(
			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
			3,         //size
			GL_FLOAT,  //type
			GL_FALSE,  //normalized?
			0,         //stride
			0          //array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Draw the triangle (Step 4g)
/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);


		//Heart 4
		scale.SetToScale(8, 8, 8);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(hearts_TX[3], hearts_TY[3], -1);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]); //update the shader with new MVP

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(
			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
			3,         //size
			GL_FLOAT,  //type
			GL_FALSE,  //normalized?
			0,         //stride
			0          //array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Draw the triangle (Step 4g)
/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);


		//Heart 5
		scale.SetToScale(8, 8, 8);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(hearts_TX[4], hearts_TY[4], -1);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]); //update the shader with new MVP

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(
			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
			3,         //size
			GL_FLOAT,  //type
			GL_FALSE,  //normalized?
			0,         //stride
			0          //array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Draw the triangle (Step 4g)
/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);




//		// inner box
//		scale.SetToScale(36, 10, 1);
//		rotate.SetToRotation(0, 0, 0, 1);
//		translate.SetToTranslation(0, -16, -2);
//		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
//		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
//			&MVP.a[0]); //update the shader with new MVP
//
//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2_INNER]);
//		glVertexAttribPointer(
//			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
//			3,         //size
//			GL_FLOAT,  //type
//			GL_FALSE,  //normalized?
//			0,         //stride
//			0          //array buffer offset
//		);
//
//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2_INNER]);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//		//Draw the triangle (Step 4g)
///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle
//
//		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);

		//Box
		scale.SetToScale(80, 12, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(0, box_TY , 0);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 9);


		//		//Inner Box
		//		scale.SetToScale(80, 12, 1);
		//		rotate.SetToRotation(0, 0, 0, 1);
		//		translate.SetToTranslation(0, -18, 0);
		//		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		//		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
		//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		//			&MVP.a[0]); //update the shader with new MVP

		//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2_INNER]);
		//		glVertexAttribPointer(
		//			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		//			3,         //size
		//			GL_FLOAT,  //type
		//			GL_FALSE,  //normalized?
		//			0,         //stride
		//			0          //array buffer offset
		//		);

		//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2_INNER]);
		//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//		//Draw the triangle (Step 4g)
		///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

		//		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);


	//			//Third Object 3
	//			scale.SetToScale(scaleAll, scaleAll, scaleAll);
	//			rotate.SetToRotation(0, 0, 0, 1);
	//			translate.SetToTranslation(-2, -4, 0);
	//			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	//			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//				&MVP.a[0]); //update the shader with new MVP

	//			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	//			glVertexAttribPointer(
	//				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
	//				3,         //size
	//				GL_FLOAT,  //type
	//				GL_FALSE,  //normalized?
	//				0,         //stride
	//				0          //array buffer offset
	//			);

	//			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//			//Draw the triangle (Step 4g)
	///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

	//			glDrawArrays(GL_TRIANGLE_FAN, 0, 9);


	//Clear color buffer every frame (Step 3b)
	/*glClear(GL_COLOR_BUFFER_BIT);*/






	////Attempt at second triangle
	////Step 4f
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	//glVertexAttribPointer(
	//	0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
	//	3,         //size
	//	GL_FLOAT,  //type
	//	GL_FALSE,  //normalized?
	//	0,         //stride
	//	0          //array buffer offset
	//);

	////Step 5b

	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


	////Draw the triangle (Step 4g)
	//glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices  = 1 triangle

	glDisableVertexAttribArray(0);

	//Step 5c
	glDisableVertexAttribArray(1);
}

void Scene2::Exit()
{
	// Cleanup VBO here

	//Step 4h
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[1]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[1]);
	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}
