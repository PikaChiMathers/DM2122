#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

//void Scene1::Init()
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

void Scene1::Init() //My Own Pattern
{
	// Init VBO here

	//Set background color to dark blue (Step 3a)
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

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


	//An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
	static const GLfloat color_buffer_data[] = {
		0.55f, 0.55f, 0.8f,
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
		0.55f, 0.55f, 0.8f,
		0.3f, 0.5f, 1.0f,
		0.3f, 0.5f, 1.0f,
		0.3f, 0.5f, 1.0f,
		0.55f, 0.55f, 0.8f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
		color_buffer_data, GL_STATIC_DRAW);




	//Load vertex and fragment shaders (Step 6a)
	m_programID = LoadShaders
	(
		"Shader//SimpleVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader"
	);

	//Use our shader (Step 6b)
	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);


}

void Scene1::Update(double dt)
{
}

//void Scene1::Render()
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

void Scene1::Render() //My Own Pattern
{
	// Render VBO here

	//Clear color buffer every frame (Step 3b)
	/*glClear(GL_COLOR_BUFFER_BIT);*/

	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Step 4f
	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	//Step 5b
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

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

void Scene1::Exit()
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
