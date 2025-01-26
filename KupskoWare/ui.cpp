#include <iostream>
#include "ui.hpp"

MenuVars settings;
Screen screen;

void handle_keys()
{
	auto GetKeyInput = [](unsigned int key) -> bool
		{
			bool SendInput = false;

			while (GetAsyncKeyState(key))
			{
				SendInput = true;
			}

			return SendInput;
		};

	if (GetKeyInput(VK_INSERT))
		settings.bMenuOpen = !settings.bMenuOpen;
}

void imgui_menu(GLFWwindow* window)
{
	ImGui::SetNextWindowSize(ImVec2(385, 420), ImGuiCond_Once);

	if (settings.bMenuOpen)
	{
		ImGui::Begin(MENU_NAME, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

		ImGui::Text("Game: %s", memory.szProcessName);
		ImGui::Spacing();

		if (GTAstatus)
		{
			gta::Ui();
		}

		ImGui::End();
	}
}

void ui::run()
{
	if (!glfwInit()) //initialize glfw
	{
		std::printf("glfwInit failed\n");
		exit(EXIT_FAILURE);
	}

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); //get this bullshit

	//get screen res
	screen.width = mode->width;
	screen.height = mode->height;

	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate); //set refreshrate

	//set opengl bs
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true); //transparent window
	glfwWindowHint(GLFW_DECORATED, false); //title bar n shit
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_FLOATING, true);

	GLFWwindow* window = glfwCreateWindow(screen.width, screen.height + 1, WINDOW_NAME, NULL, NULL); //add + 1 cuz otherwise black screen

	if (!window)
	{
		std::printf("failed to create a window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glad_glViewport(0, 0, screen.width, screen.height); //set viewport ig?

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& IO = ImGui::GetIO(); (void)IO;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	IO.IniFilename = NULL; //disable imgui.ini cfg
	ImGui::StyleColorsDark();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, !settings.bMenuOpen);

		glad_glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImDrawList* DrawList = ImGui::GetForegroundDrawList();

		imgui_menu(window);
		handle_keys();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		Sleep(10);
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}