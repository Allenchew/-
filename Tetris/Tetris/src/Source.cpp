#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "GameLoader.h"
#include "GameSystem.h"
#include "GameController.h"
#include "RefreshBuffer.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include "test\TestClearColor.h"

void GetInput(GLFWwindow * window, int key, int scancode, int action, int mods);

bool reset = false;
int moving = 0;

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

		RefreshBuffer refreshbuffer;

		GameLoader gameloader;
		GameSystem gs;
		gs.GenerataObj( gameloader.Map, gameloader.TmpMap);
		mapdata output = gameloader.BuildMap();
		VertexArray va;


		VertexBuffer vb((*output.position).data(), (*output.position).size() * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		IndexBuffer ib((*output.indices).data(), (*output.indices).size());
		glm::mat4 proj = glm::ortho(0.0f, 240.0f, 0.0f, 500.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		//shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);

		Texture texture("res/texture/PixelArt.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		glm::vec3 translation(10, -10, 0);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view* model;

		shader.Bind();
		shader.SetUniformMat4f("u_MVP", mvp);
		Renderer renderer;

	//	ImGui::CreateContext();
	//	ImGui_ImplGlfwGL3_Init(window, true);
	//	ImGui::StyleColorsDark();

		test::TestClearColor test;

		float timer = 1.f;

		float previous = glfwGetTime();
		while (!glfwWindowShouldClose(window))
		{

			test.OnUpdate(0.0f);
			test.OnRender();

	//		ImGui_ImplGlfwGL3_NewFrame();
		//	test.OnImGuiRender();
	//		ImGui::Render();
	//		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSetKeyCallback(window, GetInput);

			float now = glfwGetTime();
			float delta = now - previous;

			if (delta >= timer && !gs.gameReset) {
				if (timer > 0.4f)
					timer -= 0.001f;
				previous = now;
				moving = 2;
				reset = true;
			}

			if (reset) {
				if (gs.gameReset) {
					reset = false;
					if (moving == 10) {
						system("cls");
						gameloader = GameLoader();
						gs = GameSystem();
					}
				}
				else {
					reset = false;
					gs.ObjFall(moving);
					gs.GenerataObj(gameloader.Map, gameloader.TmpMap);
					output = gameloader.BuildMap();
					vb.Rebuff((*output.position).data(), (*output.position).size() * sizeof(float));
					ib.Rebuff((*output.indices).data(), (*output.indices).size());
					va.AddBuffer(vb, layout);
					va.Unbind();
					vb.Unbind();
					ib.Unbind();
				}
			}

			renderer.Clear();
			renderer.Draw(va, ib, shader);
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
		moving = 2;
		reset = true;
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