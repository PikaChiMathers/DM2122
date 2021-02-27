#define LSPEED 10.f
#include "SceneSearch.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Utility.h"
#include "LoadTGA.h"

#include "Application.h"


SceneSearch::SceneSearch()
{
}

SceneSearch::~SceneSearch()
{
}


void SceneSearch::Init()
{
	srand(time(NULL)); //to initialize random seed

	targets[0].Init(Vector3(0, 240, -330), Vector3(.73f, 239.7f, -329), Vector3(0.1f, 1, 0.2f));
	targets[1].Init(Vector3(0, 240, -330), Vector3(.59f, 239.7f, -329), Vector3(0.1f, 1, 0.2f));
	targets[2].Init(Vector3(0, 240, -330), Vector3(.48f, 239.73f, -329), Vector3(0.1f, 1, 0.2f));
	targets[3].Init(Vector3(0, 240, -330), Vector3(.4f, 239.6f, -329), Vector3(0.1f, 1, 0.2f));
	targets[4].Init(Vector3(0, 240, -330), Vector3(.38f, 239.8f, -329), Vector3(0.1f, 1, 0.2f));
	targets[5].Init(Vector3(0, 240, -330), Vector3(.25f, 239.95f, -329), Vector3(0.1f, 1, 0.2f));
	targets[6].Init(Vector3(0, 240, -330), Vector3(.11f, 239.7f, -329), Vector3(0.1f, 1, 0.2f));
	targets[7].Init(Vector3(0, 240, -330), Vector3(.08f, 239.95f, -329), Vector3(0.1f, 1, 0.2f));
	targets[8].Init(Vector3(0, 240, -330), Vector3(-.22f, 239.8f, -329), Vector3(0.1f, 1, 0.2f));
	targets[9].Init(Vector3(0, 240, -330), Vector3(-.25f, 239.69f, -329), Vector3(0.1f, 1, 0.2f));
	targets[10].Init(Vector3(0, 240, -330), Vector3(-.29f, 239.6f, -329), Vector3(0.1f, 1, 0.2f));
	targets[11].Init(Vector3(0, 240, -330), Vector3(-.41f, 239.8f, -329), Vector3(0.1f, 1, 0.2f));
	targets[12].Init(Vector3(0, 240, -330), Vector3(-.48f, 239.65f, -329), Vector3(0.1f, 1, 0.2f));
	targets[13].Init(Vector3(0, 240, -330), Vector3(-.58f, 239.7f, -329), Vector3(0.1f, 1, 0.2f));
	targets[14].Init(Vector3(0, 240, -330), Vector3(-.73f, 239.75f, -329), Vector3(0.1f, 1, 0.2f));
	targets[15].Init(Vector3(0, 240, -330), Vector3(-1.f, 239.4f, -329), Vector3(0.1f, 1, 0.2f));

	game_start = false;

	int min = 2; //min is how long this game will last in minutes
	timer = min * 60 * 60;

	for (int cam = 0; cam < 9; cam++) //Uses randomizer to set up to 9 random targets/buildings to have passengers
	{
		int target_num = rand() % 16;
		targets[target_num].num_passengers = rand() % 5 + 1; //each of the randomly selected buildings can have 1 to 5 passengers
	}

	current_target = press_count = passenger_count = press_time = spam_time = 0;
	camera = &targets[0];

	map.Set(Maps::SKYBOX_TYPE::SB_DAY);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	rotateAngle = 0;

	//Set background color to dark blue (Step 3a)
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO (Step 4a)
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	scene_change = true;

	UI_width = 160;
	UI_height = 90;

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Rsphere", Color(1, 0, 0), 30, 30, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", lights[0].color, 30, 30, 1);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP] = MeshBuilder::GenerateRevQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//HNS_map.tga");

	meshList[GEO_TARGET] = MeshBuilder::GenerateRevQuad("target", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TARGET]->textureID = LoadTGA("Image//target.tga");

	meshList[GEO_PROGRESS] = MeshBuilder::GenerateRevQuad("progress", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_INSTRUCTIONS] = MeshBuilder::GenerateRevQuad("Instructions", Color(1, 1, 1), 1, 1);
	meshList[GEO_INSTRUCTIONS]->textureID = LoadTGA("Assets//search_instructions.tga");


	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0, 0, 1), 1, 1, 1);
	meshList[GEO_CUBE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CUBE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_CUBE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_CUBE]->material.kShininess = 1.f;

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//trebuchet.tga");

	meshList[GEO_BUILDING1] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//short_apartment.obj", "OBJ//short_apartment.mtl");
	meshList[GEO_BUILDING1]->textureID = LoadTGA("Image//apartment.tga");
	meshList[GEO_BUILDING2] = MeshBuilder::GenerateOBJMTL("building2", "OBJ//med_apartment.obj", "OBJ//med_apartment.mtl");
	meshList[GEO_BUILDING2]->textureID = LoadTGA("Image//apartment.tga");
	meshList[GEO_BUILDING3] = MeshBuilder::GenerateOBJMTL("building3", "OBJ//tall_apartment.obj", "OBJ//tall_apartment.mtl");
	meshList[GEO_BUILDING3]->textureID = LoadTGA("Image//apartment.tga");
	meshList[GEO_BUILDING4] = MeshBuilder::GenerateOBJMTL("house2", "OBJ//smol_building.obj", "OBJ//smol_building.mtl");
	meshList[GEO_BUILDING4]->textureID = LoadTGA("Image//house2.tga");
	meshList[GEO_BUILDING5] = MeshBuilder::GenerateOBJMTL("building2", "OBJ//med_apartment.obj", "OBJ//med_apartment.mtl");
	meshList[GEO_BUILDING5]->textureID = LoadTGA("Image//house2.tga");
	meshList[GEO_BUSSTOP] = MeshBuilder::GenerateOBJ("busstop", "OBJ//bustop.obj", Color(1, 1, 1));
	meshList[GEO_MALL] = MeshBuilder::GenerateOBJMTL("mall", "OBJ//stadium.obj", "OBJ//stadium.mtl");
	meshList[GEO_MALL]->textureID = LoadTGA("Image//stadium.tga");
	meshList[GEO_TREE1] = MeshBuilder::GenerateOBJ("tree1", "OBJ//tree_large.obj", Color(0.184314, 0.309804, 0.184314));
	meshList[GEO_TREE2] = MeshBuilder::GenerateOBJ("tree2", "OBJ//tree_small.obj", Color(0.184314, 0.309804, 0.184314));

	glEnable(GL_CULL_FACE);
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
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_targetspace");
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
	lights[0].position.Set(0, 1000, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1800;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(-1.f, 1.f, 0.f);

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

void SceneSearch::Update(double dt)
{
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

	if (timer > 0)
	{
		if (game_start)
		{
			timer--;
			if (press_count == 0)
			{
				if (Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed(VK_RIGHT))
				{
					press_time++;
					if (press_time == 1)
					{
						if (Application::IsKeyPressed(VK_LEFT))
							current_target--;
						if (Application::IsKeyPressed(VK_RIGHT))
							current_target++;

						if (current_target < 0)
							current_target = 15;
						if (current_target >= 16)
							current_target = 0;
					}
				}
				else
					press_time = 0;

				camera = &targets[current_target];
			}

			if (press_count >= 25)
				camera->progress = 25;
			if (press_count >= 50)
				camera->progress = 50;
			if (press_count >= 75)
				camera->progress = 75;
			if (press_count >= 100)
			{
				camera->progress = 100;
				press_count = 0;
				passenger_count += camera->num_passengers;
				camera->has_checked = true;
			}
		}

		if (Application::IsKeyPressed(VK_SPACE))
		{
			spam_time++;
			if (spam_time == 1)
			{
				if (game_start)
				{
					if (!camera->has_checked && press_count < 100)
					{
						std::string sound_file = "media/honk_" + std::to_string(rand() % 5 + 1) + ".wav";
							sound.Engine()->play2D(sound_file.std::string::c_str());

						press_count++;
					}
				}
				else
					game_start = true;
			}
		}
		else
			spam_time = 0;
	}

}

void SceneSearch::Render() //My Own Pattern
{
	// Render VBO here

	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera->position.x, camera->position.y,
		camera->position.z, camera->target.x, camera->target.y,
		camera->target.z, camera->up.x, camera->up.y, camera->up.z);
	modelStack.LoadIdentity();

	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_targetspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_targetspace.x);
	}
	else if (lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_targetspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_targetspace.x);
		Vector3 spotDirection_targetspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_targetspace.x);
	}
	else
	{
		Position lightPosition_targetspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_targetspace.x);
	}

	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with new MVP

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();
	RenderSkybox();

	RenderCity();

	if (game_start)
	{
		RenderMeshOnScreen(meshList[GEO_TARGET], 80, 45, 10, 10);

		//bar_type (sets up the progress bar depending on the player's progress percentage)
		std::string bar_type = "Assets//progress_" + std::to_string(camera->progress) + ".tga";
		meshList[GEO_PROGRESS]->textureID = LoadTGA(bar_type.std::string::c_str());
		RenderMeshOnScreen(meshList[GEO_PROGRESS], 80, 35, 20, 5);

		std::ostringstream ss;
		ss.precision(3);
		ss << "Timer left:" << (timer/3600) <<"m " << (timer%3600)/60 << "s";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 1), 3, 5, 85);
		RenderTextOnScreen(meshList[GEO_TEXT], "Passengers found:" + std::to_string(passenger_count), Color(0, 0, 1), 3, 5, 80);
	}
	else
	{
		RenderMeshOnScreen(meshList[GEO_INSTRUCTIONS], 80, 45, 120, 60);
	}
}

void SceneSearch::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Step 6c
	glDeleteProgram(m_programID);

}

void SceneSearch::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneSearch::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(499, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-499, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 499);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -499);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -499, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 499, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
}

void SceneSearch::RenderCity()
{

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FLOOR], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 0, 425);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(200, 0, 252);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 0, 260);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(175, 0, 425);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING3], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 0, 425);
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING3], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 0, 150);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(200, 0, 150);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(55, 0, 200);
	//modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-160, 0, 410);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING5], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 410);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING5], lights[0].isOn);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-440, 0, 410);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING4], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-160, 0, 280);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING4], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 280);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING4], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-440, 0, 280);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING5], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-140, 0, 170);
	/*modelStack.Rotate(-180, 0, 1, 0);*/
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BUILDING4], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-30, 0, 400);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BUSSTOP], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-390, -44, 5);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(.15, .15, .15);
	RenderMesh(meshList[GEO_MALL], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 230);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 100);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 50);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, -50);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, -100);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, -150);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 300);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-220, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-345, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-50, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(55, 0, 300);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BUSSTOP], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(75, 0, 375);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(75, 0, 255);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE2], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100, 0, 170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(275, 0, 170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, 0, 170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_TREE1], lights[0].isOn);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20, 0, -175);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(65, 10, 10);
	RenderMesh(meshList[GEO_BUSSTOP], lights[0].isOn);
	modelStack.PopMatrix();
}

void SceneSearch::RenderText(Mesh* mesh, std::string text, Color color)
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


void SceneSearch::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
		characterSpacing.SetToTranslation(i * .6f, 0.5f, 0);
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

void SceneSearch::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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