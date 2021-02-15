#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}


void Scene3::Init() //My Own Pattern
{
	// Init VBO here

	rotateAngle = 0;
	rotateBG = 0;
	translateX = -35;
	translateY = -30;
	translateXDir = 1;
	translateYDir = 0;
	rotateDir = 0;
	scaleDir = 1;
	scaleAll = 0;
	box_TY = -18;
	box_TYDir = 0;

	num_hearts = 8;
	
	for (int h = 0; h < num_hearts; h++)
	{
		hearts_TXDir[h] = 0;
		hearts_TYDir[h] = 0;
	}

	hearts_Xorigin[0] = hearts_TX[0] = 20;
	hearts_Xorigin[1] = hearts_TX[1] = 40;
	hearts_Xorigin[2] = hearts_TX[2] = 35;
	hearts_Xorigin[3] = hearts_TX[3] = 25;
	hearts_Xorigin[4] = hearts_TX[4] = 17;
	hearts_Xorigin[5] = hearts_TX[5] = 19;
	hearts_Xorigin[6] = hearts_TX[6] = 35;
	hearts_Xorigin[7] = hearts_TX[7] = 14;

	hearts_RX[0] = -15;
	hearts_RX[1] = -13;
	hearts_RX[2] = 40;
	hearts_RX[3] = 18;
	hearts_RX[4] = 20;
	hearts_RX[5] = -15;
	hearts_RX[6] = -13;
	hearts_RX[7] = 180;

	hearts_Yorigin[0] = hearts_TY[0] = 20;
	hearts_Yorigin[1] = hearts_TY[1] = 15;
	hearts_Yorigin[2] = hearts_TY[2] = 13;
	hearts_Yorigin[3] = hearts_TY[3] = 30;
	hearts_Yorigin[4] = hearts_TY[4] = 16;
	hearts_Yorigin[5] = hearts_TY[2] = 18;
	hearts_Yorigin[6] = hearts_TY[3] = 35;
	hearts_Yorigin[7] = hearts_TY[4] = 14;

	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers (Step 4b)
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_COLOURS, &m_colorBuffer[0]);


	//Heart
	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data_heart[] = {
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
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[HEART]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_heart), vertex_buffer_data_heart, GL_STATIC_DRAW);



	//An array of 3 vectors which represents the colors of the 3 vertices (Step 5a)
	static const GLfloat color_buffer_data_petal[] = {
		1.0f, 0.53f, 0.4f,
		1.0f, 0.53f, 0.4f,
		1.0f, 0.53f, 0.4f,
		1.0f, 0.53f, 0.4f,
		1.0f, 0.53f, 0.4f,
		1.0f, 0.53f, 0.4f,
		1.0f, 0.53f, 0.4f,
		1.0f, 0.53f, 0.4f,
		1.0f, 0.53f, 0.4f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[PETAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_petal), color_buffer_data_petal, GL_STATIC_DRAW);


	//Square
	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data_square[] = {
		1.0f, 1.0f, 0.0f, // Coordinates of points(x, y, z)
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};

	//Set the current active buffer (Step 4d)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_square), vertex_buffer_data_square, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data_tree[] = {
		0.38f, 0.2f, 0.07f,
		0.38f, 0.2f, 0.07f,
		0.38f, 0.2f, 0.07f,
		0.38f, 0.2f, 0.07f,
		0.38f, 0.2f, 0.07f,
		0.38f, 0.2f, 0.07f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_TRUNK]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_tree),
		color_buffer_data_tree, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data_water[] = {
		0.38f, 0.69f, 1.0f,
		0.38f, 0.69f, 1.0f,
		0.38f, 0.69f, 1.0f,
		0.38f, 0.69f, 1.0f,
		0.38f, 0.69f, 1.0f,
		0.38f, 0.69f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WATER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_water),
		color_buffer_data_water, GL_STATIC_DRAW);

	//Circle
	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data_circle[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.5f, 0.87f, 0.0f,
		0.71f, 0.71f, 0.0f,
		0.87f, 0.5f, 0.0f,

		1.0f, 0.0f, 0.0f,

		0.87f, -0.5f, 0.0f,
		0.71f, -0.71f, 0.0f,
		0.5f, -0.87f, 0.0f,

		0.0f, -1.0f, 0.0f,

		-0.5f, -0.87f, 0.0f,
		-0.71f, -0.71f, 0.0f,
		-0.87f, -0.5f, 0.0f,

		-1.0f, 0.0f, 0.0f,

		-0.87f, 0.5f, 0.0f,
		-0.71f, 0.71f, 0.0f,
		-0.5f, 0.87f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};

	//Set the current active buffer (Step 4d)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_circle), vertex_buffer_data_circle, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data_blossom[] = {
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,

		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,

		1.0f, 0.55f, 0.6f,

		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,

		1.0f, 0.55f, 0.6f,

		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,

		1.0f, 0.55f, 0.6f,

		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,

		1.0f, 0.55f, 0.6f,
		1.0f, 0.55f, 0.6f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_blossom),
		color_buffer_data_blossom, GL_STATIC_DRAW);


	static const GLfloat color_buffer_data_time[] = {
		0.0f, 0.0f, 0.2f,
		0.98f, 0.95f, 0.36f,

		//Day

		0.98f, 0.93f, 0.36f,
		0.98f, 0.93f, 0.36f,
		0.98f, 0.93f, 0.36f,

		0.98f, 0.93f, 0.36f,

		0.98f, 0.93f, 0.36f,
		0.98f, 0.93f, 0.36f,
		0.98f, 0.93f, 0.36f,

		0.98f, 0.93f, 0.36f,

		//Night

		0.0f, 0.0f, 0.2f,
		0.0f, 0.0f, 0.2f,
		0.0f, 0.0f, 0.2f,

		0.0f, 0.0f, 0.2f,

		0.0f, 0.0f, 0.2f,
		0.0f, 0.0f, 0.2f,
		0.98f, 0.95f, 0.36f,

		0.98f, 0.95f, 0.36f,
		0.98f, 0.95f, 0.36f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[DAY_NIGHT]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_time),
		color_buffer_data_time, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data_hill[] = {
		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,

		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,

		0.0f, 0.55f, 0.27f,

		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,

		0.0f, 0.55f, 0.27f,

		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,

		0.0f, 0.55f, 0.27f,

		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,

		0.0f, 0.55f, 0.27f,
		0.0f, 0.55f, 0.27f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[HILL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_hill),
		color_buffer_data_hill, GL_STATIC_DRAW);



	//Triangle
	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data_triangle[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};

	//Set the current active buffer (Step 4d)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_triangle), vertex_buffer_data_triangle, GL_STATIC_DRAW);


	//Star
	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data_star[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.25f, 0.2f, 0.0f,
		1.0f, 0.2f, 0.0f,
		0.37f, -0.27f, 0.0f,
		0.6f, -1.0f, 0.0f,
		0.0f, -0.55f, 0.0f,
		-0.6f, -1.0f, 0.0f,
		-0.37f, -0.27f, 0.0f,
		-1.0f, 0.2f, 0.0f,
		-0.25f, 0.2f, 0.0f,
		0.0f, 1.0f, 0.0f,

	};

	//Set the current active buffer (Step 4d)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_star), vertex_buffer_data_star, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data_star[] = {
		0.98f, 0.86f, 0.05f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
		0.99f, 0.71f, 0.08f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_SHADE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_star),
		color_buffer_data_star, GL_STATIC_DRAW);



	//Square
	//An array of 3 vectors which represent 3 vertices (Step 4c)
	static const GLfloat vertex_buffer_data_stick[] = {
		1.0f, 1.0f, 0.0f, // Coordinates of points(x, y, z)
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};

	//Set the current active buffer (Step 4d)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STICK]);

	//Transfer vertices to OpenGL (Step 4e)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_stick), vertex_buffer_data_stick, GL_STATIC_DRAW);


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

void Scene3::Update(double dt)
{
	scaleAll += (float)(scaleDir * 0.9 * dt);
	rotateAngle += (float)(30 * dt);
	rotateBG += (float)(27 * dt);

	if ((scaleAll > 0.5) || (scaleAll < 0))
		scaleDir *= -1;

	for (int h = 0; h < num_hearts; h++)
	{
		hearts_TX[h] -= (float)(20 * dt);
		hearts_RX[h] += (float)(90 * dt);

		if ((hearts_TY[h] < -25) || (hearts_TX[h] < -40))
		{
			hearts_TY[h] = hearts_Yorigin[h];
			hearts_TX[h] = hearts_Xorigin[h];
		}
		else
			hearts_TY[h] -= (float)(10 * dt);
	}

}

void Scene3::Render() //My Own Pattern
{
	// Render VBO here


	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Step 4f
	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	//Step 5b
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

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

		projection.SetToOrtho(-40, 40, -30, 30, -10, 10); //Our world is a cube defined by these boundaries

		//Background
		scale.SetToScale(201, 201, 201);
		rotate.SetToRotation(rotateBG, 0, 0, 1);
		translate.SetToTranslation(0, -160, PLACE_BACKGROUND);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[DAY_NIGHT]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);



			//Hill
			scale.SetToScale(50, 50, 50);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(30, -60, PLACE_HILL);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[HILL]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);


			//Tree Roots
			scale.SetToScale(20, 7, 5);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(30, -11, PLACE_TREE_BASE);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_TRUNK]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLES, 0, 3);


			//Tree Trunk
			scale.SetToScale(3, 40, 5);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(30, -11, PLACE_TREE_BASE);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STICK]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_TRUNK]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLES, 0, 6);



			//Tree Branch 1
			scale.SetToScale(1, 10, 5);
			rotate.SetToRotation(45, 0, 0, 1);
			translate.SetToTranslation(25, 18, PLACE_TREE_BASE);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STICK]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_TRUNK]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLES, 0, 6);


			//Tree Branch 2
			scale.SetToScale(1, 10, 5);
			rotate.SetToRotation(-45, 0, 0, 2);
			translate.SetToTranslation(39, 17, PLACE_TREE_BASE);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STICK]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_TRUNK]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLES, 0, 6);


			//Tree Leaves
			scale.SetToScale(8, 8, 8);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(10, 25, PLACE_TREE_LEAVES);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);

			//Tree Leaves
			scale.SetToScale(8, 8, 8);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(20, 25, PLACE_TREE_LEAVES);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);


			//Tree Leaves
			scale.SetToScale(9, 9, 9);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(30, 25, PLACE_TREE_LEAVES);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);

			//Tree Leaves
			scale.SetToScale(9, 9, 9);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(35, 25, PLACE_TREE_LEAVES);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);


			//Tree Leaves
			scale.SetToScale(4, 4, 4);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(3, 25, PLACE_TREE_LEAVES);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);


			//Tree Leaves
			scale.SetToScale(9, 9, 9);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(35, 25, PLACE_TREE_LEAVES);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);



			//Tree Leaves
			scale.SetToScale(9, 9, 9);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(35, 25, PLACE_TREE_LEAVES);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[HEART]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);




			//Tree Leaves
			scale.SetToScale(9, 9, 9);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(35, 25, PLACE_TREE_LEAVES);
			model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
				&MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[HEART]);
			glVertexAttribPointer(
				0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
				3,         //size
				GL_FLOAT,  //type
				GL_FALSE,  //normalized?
				0,         //stride
				0          //array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CHERRY_BLOSSOM]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Draw the triangle (Step 4g)
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

			glDrawArrays(GL_TRIANGLE_FAN, 0, 19);




	//		//Star
	//		scale.SetToScale(scaleAll, scaleAll, scaleAll);
	//		rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//		translate.SetToTranslation(0, -45, PLACE_STARS);
	//		model = rotate * translate * scale; //scale, followed by rotate, then lastly translate
	//		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//			&MVP.a[0]); //update the shader with new MVP

	//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	//		glVertexAttribPointer(
	//			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
	//			3,         //size
	//			GL_FLOAT,  //type
	//			GL_FALSE,  //normalized?
	//			0,         //stride
	//			0          //array buffer offset
	//		);

	//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_SHADE]);
	//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//		//Draw the triangle (Step 4g)
	///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

	//		glDrawArrays(GL_TRIANGLE_FAN, 0, 12);


	//		//Star
	//		scale.SetToScale(scaleAll, scaleAll, scaleAll);
	//		rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//		translate.SetToTranslation(0, -45, PLACE_STARS);
	//		model = rotate * translate * scale; //scale, followed by rotate, then lastly translate
	//		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//			&MVP.a[0]); //update the shader with new MVP

	//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	//		glVertexAttribPointer(
	//			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
	//			3,         //size
	//			GL_FLOAT,  //type
	//			GL_FALSE,  //normalized?
	//			0,         //stride
	//			0          //array buffer offset
	//		);

	//		//Draw the triangle (Step 4g)
	///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

	//		glDrawArrays(GL_TRIANGLE_FAN, 0, 12);

	//		//Star
	//		scale.SetToScale(scaleAll, scaleAll, scaleAll);
	//		rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//		translate.SetToTranslation(-10, -35, PLACE_STARS);
	//		model = rotate * translate * scale; //scale, followed by rotate, then lastly translate
	//		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//			&MVP.a[0]); //update the shader with new MVP

	//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	//		glVertexAttribPointer(
	//			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
	//			3,         //size
	//			GL_FLOAT,  //type
	//			GL_FALSE,  //normalized?
	//			0,         //stride
	//			0          //array buffer offset
	//		);

	//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_SHADE]);
	//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//		//Draw the triangle (Step 4g)
	///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

	//		glDrawArrays(GL_TRIANGLE_FAN, 0, 12);


	//		//Star
	//		scale.SetToScale(scaleAll, scaleAll, scaleAll);
	//		rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//		translate.SetToTranslation(-19, -10, PLACE_STARS);
	//		model = rotate * translate * scale; //scale, followed by rotate, then lastly translate
	//		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//			&MVP.a[0]); //update the shader with new MVP

	//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	//		glVertexAttribPointer(
	//			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
	//			3,         //size
	//			GL_FLOAT,  //type
	//			GL_FALSE,  //normalized?
	//			0,         //stride
	//			0          //array buffer offset
	//		);

	//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_SHADE]);
	//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//		//Draw the triangle (Step 4g)
	///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

	//		glDrawArrays(GL_TRIANGLE_FAN, 0, 12);

	//		//Star
	//		scale.SetToScale(scaleAll, scaleAll, scaleAll);
	//		rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//		translate.SetToTranslation(-20, -30, PLACE_STARS);
	//		model = rotate * translate * scale; //scale, followed by rotate, then lastly translate
	//		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//			&MVP.a[0]); //update the shader with new MVP

	//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	//		glVertexAttribPointer(
	//			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
	//			3,         //size
	//			GL_FLOAT,  //type
	//			GL_FALSE,  //normalized?
	//			0,         //stride
	//			0          //array buffer offset
	//		);

	//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_SHADE]);
	//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//		//Draw the triangle (Step 4g)
	///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

	//		glDrawArrays(GL_TRIANGLE_FAN, 0, 12);



	//		//Star
	//		scale.SetToScale(scaleAll, scaleAll, scaleAll);
	//		rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//		translate.SetToTranslation(-20, -20, PLACE_STARS);
	//		model = rotate * translate * scale; //scale, followed by rotate, then lastly translate
	//		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//			&MVP.a[0]); //update the shader with new MVP

	//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	//		glVertexAttribPointer(
	//			0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
	//			3,         //size
	//			GL_FLOAT,  //type
	//			GL_FALSE,  //normalized?
	//			0,         //stride
	//			0          //array buffer offset
	//		);

	//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_SHADE]);
	//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//		//Draw the triangle (Step 4g)
	///*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

	//		glDrawArrays(GL_TRIANGLE_FAN, 0, 12);





			for (int h = 0; h < num_hearts; h++)
			{
				scale.SetToScale(1, 2, 2);
				rotate.SetToRotation(hearts_RX[h], 0, 1, 1);
				translate.SetToTranslation(hearts_TX[h], hearts_TY[h], 1);
				model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
				MVP = projection * view * model; // Remember, matrix multiplication is the other way around
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
					&MVP.a[0]); //update the shader with new MVP

				glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[HEART]);
				glVertexAttribPointer(
					0,         //attribute 0. Must match the layout in the shader. Usually 0 is for vertex
					3,         //size
					GL_FLOAT,  //type
					GL_FALSE,  //normalized?
					0,         //stride
					0          //array buffer offset
				);


				glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[PETAL]);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

				//Draw the triangle (Step 4g)
		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/ //Starting from vertex 0; 3 vertices  = 1 triangle

				glDrawArrays(GL_TRIANGLE_FAN, 0, 9);
			}

	glDisableVertexAttribArray(0);

	//Step 5c
	glDisableVertexAttribArray(1);
}

void Scene3::Exit()
{
	// Cleanup VBO here

	//Step 4h
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_COLOURS, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}
