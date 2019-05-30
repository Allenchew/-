#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<ft2build.h>
#include FT_FREETYPE_H

#include "VertexBufferLayout.h"
#include "BlockEffect.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

struct Character {
	unsigned int     TextureID; 
	glm::ivec2 Size;   
	glm::ivec2 Bearing;    
	unsigned int     Advance;   
};

//背景の点座標
float tmpdata[32] = 
{0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.5f,
240.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,0.5f,
240.0f,500.0f,1.0f,1.0f,1.0f,1.0f,1.0f,0.5f,
0.0f,500.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.5f };

//点座標の接続順
unsigned int tmpindices[6] = {
	0,1,2,
	2,3,0
};

void GetInput(GLFWwindow * window, int key, int scancode, int action, int mods);

bool fading = false;
bool reset = false;
int moving = 0;

void updateData(const mapdata& output,VertexBufferLayout& layout,VertexBuffer& vb,IndexBuffer& ib,VertexArray& va ) {
	vb.Rebuff((*output.position).data(), (*output.position).size() * sizeof(float));
	ib.Rebuff((*output.indices).data(), (*output.indices).size());
	va.AddBuffer(vb, layout);
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
}

int main(void)
{
	GLFWwindow* window;
	FT_Library library;
	FT_Face face;

	int error;
	error = FT_Init_FreeType(&library);
	if (error) {
		std::cout << "freetype error!!" << std::endl;
	}
	error = FT_New_Face(library,
		"/usr/share/fonts/truetype/arial.ttf",
		0,
		&face);
	if (error == FT_Err_Unknown_File_Format)
	{
		std::cout << "font error!!" << std::endl;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	if(FT_Load_Char(face,'X',FT_LOAD_RENDER))
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//setting window size
	window = glfwCreateWindow(240, 500, "Tetris", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		//get texture address
		std::vector<std::string> imgaddress;
		imgaddress.push_back("res/texture/PixelArtWhite.png");
		imgaddress.push_back("res/texture/rem.jpg");

		GameLoader gameloader;
		GameSystem gs;
		//マップの更新、当たり判定
		gs.GenerateObj( gameloader.Map, gameloader.TmpMap);
		mapdata output = gameloader.BuildMap();
		
		//背景の設定
		VertexArray vatmp;

		VertexBuffer vbtmp(tmpdata, 32 * sizeof(float));
		VertexBufferLayout layouttmp;
		layouttmp.Push<float>(2);
		layouttmp.Push<float>(2);
		layouttmp.Push<float>(4);
		vatmp.AddBuffer(vbtmp, layouttmp);
		IndexBuffer ibtmp(tmpindices, 6);
		glm::mat4 projtmp = glm::ortho(0.0f, 240.0f, 0.0f, 500.0f, -1.0f, 1.0f);
		glm::mat4 viewtmp = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		Shader shadertmp("res/shaders/Basic.shader");
		shadertmp.Bind();
		//shadertmp.SetUniform4f("u_Color",0.0f,0.0f,0.0f,0.0f);
		Texture texturetmp(imgaddress);
		texturetmp.Bind(0);
		shadertmp.SetUniform1i("u_Texture", 0);

		vatmp.Unbind();
		vbtmp.Unbind();
		ibtmp.Unbind();
		shadertmp.Unbind();

		glm::vec3 translationtmp(0, 0, 0);
		glm::mat4 modeltmp = glm::translate(glm::mat4(1.0f), translationtmp);
		glm::mat4 mvptmp = projtmp * viewtmp* modeltmp;

		shadertmp.Bind();
		shadertmp.SetUniformMat4f("u_MVP", mvptmp);
		
		//ブロックの初期化
		VertexArray va;
		VertexBuffer vb((*output.position).data(), (*output.position).size() * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		layout.Push<float>(4);
		va.AddBuffer(vb, layout);
		IndexBuffer ib((*output.indices).data(), (*output.indices).size());
		glm::mat4 proj = glm::ortho(0.0f, 240.0f, 0.0f, 500.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		//shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);

		//Texture texturetmp(imgaddress);
		//texturetmp.Bind(0);
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		glm::vec3 translation(0, 0, 0);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view* model;

		shader.Bind();
		shader.SetUniformMat4f("u_MVP", mvp);
		Renderer renderer;

		BlockEffect blockeffect;
	
	//	ImGui::CreateContext();
	//	ImGui_ImplGlfwGL3_Init(window, true);
	//	ImGui::StyleColorsDark();

		//test::TestClearColor test;

		float timer = 1.f;//更新する時間

		float previous = glfwGetTime();
		while (!glfwWindowShouldClose(window))
		{

		//	test.OnUpdate(0.0f);
		//	test.OnRender();

	//		ImGui_ImplGlfwGL3_NewFrame();
		//	test.OnImGuiRender();
	//		ImGui::Render();
	//		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			//get input
			
			glfwSetKeyCallback(window, GetInput);
			

			float now = glfwGetTime();
			float delta = now - previous;

			if (delta >= timer && !gs.GameReset) {
				if (timer > 0.4f)
					timer -= 0.001f;
				previous = now;
				moving = 2;
				reset = true;
			}

			if (reset) {
				if (gs.GameReset) { //Game Over
					reset = false;  // initialize
					if (moving == 10) {
						system("cls");
						gameloader = GameLoader();
						gs = GameSystem();
					}
				}
				else {
					reset = false;
					gs.ObjFall(moving);
					gs.GenerateObj(gameloader.Map, gameloader.TmpMap);
					output = gameloader.BuildMap();
					updateData(output,layout,vb,ib,va);
				}
			}
			if (gs.ClearEffect) {
				fading = true;
				blockeffect.BlockTrans(*output.position,gs.outputindex);
				updateData(output, layout, vb, ib, va);
				if (blockeffect.EndEffect) {
					blockeffect.EndEffect = false;
					gs.ClearEffect = false;
					gs.CLearStroke(gameloader.TmpMap);
					gs.MoveLine(gameloader.Map,gameloader.TmpMap);
					updateData(output, layout, vb, ib, va);
					fading = false;
				}
			}
			renderer.Clear();
			renderer.Draw(vatmp, ibtmp, shadertmp,texturetmp,1);
			renderer.Draw(va, ib, shader,texturetmp,0);
			

			glfwPollEvents();

			glfwSwapBuffers(window);
		}
	}
	//ImGui_ImplGlfwGL3_Shutdown();
	//ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

void GetInput(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		moving = 8;
		reset = true;
	}
	else if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action== GLFW_PRESS)) {
		if (!fading) {
			moving = 2;
			reset = true;
		}
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		moving = 4;
		reset = true;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		moving = 6;
		reset = true;
	}
	else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		moving = 10;
		reset = true;
	}
}