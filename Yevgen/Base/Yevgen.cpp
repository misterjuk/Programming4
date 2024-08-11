#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Yevgen.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "GameTime.h"
#include "ResourceManager.h"


#include <chrono>
#include <thread>


SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

yev::Yevgen::Yevgen(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

yev::Yevgen::~Yevgen()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void yev::Yevgen::Run(const std::function<void()>& load)
{

	load();

	auto& input = InputManager::GetInstance();
	GameTime::GetInstance().Start();

	bool doContinue = true;

	while (doContinue)
	{
		GameTime::GetInstance().Update();

		GameTime::GetInstance().GetDeltaTime();

		doContinue = input.ProcessInput();

		Update();
		Render();

		const auto sleep_time = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(1000/165) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleep_time);
	}
}
void yev::Yevgen::FixedUpdate()
{

}

void yev::Yevgen::Update()
{
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.Update();
}

void yev::Yevgen::Render()
{
	const auto& renderer = Renderer::GetInstance();
	renderer.Render();
}
