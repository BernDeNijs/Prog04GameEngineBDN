#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"


#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "GameTime.h"

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

bdnE::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming_4_assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		450,
		600,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(dataPath);

}

bdnE::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void bdnE::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = GameTime::GetInstance();


	//Set MaxFps with screen refreshRate
	DEVMODE dm;
	memset(&dm, 0, sizeof(dm));
	dm.dmSize = sizeof(dm);
	if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm) != 0)
	{
		time.SetMaxFPS(static_cast<float>(dm.dmDisplayFrequency));
	}

	float lag = 0.f;

	bool doContinue = true;
	while (doContinue)
	{

		//Update GameTime
		time.Update();

		//Check for exit + process input
		doContinue = input.ProcessInput();

		//Update game
		sceneManager.Update();					//Basic update
		lag += time.GetFixedTimeStep();
		while (lag >= time.GetFixedTimeStep())	//Fixed update every xx- ms
		{
			sceneManager.FixedUpdate();
			lag -= time.GetFixedTimeStep();
		}
		renderer.Render();							//Render after all updates are completed
		sceneManager.DeleteDeadGameObjects();		//Don't delete Gameobjects until after everything has been updated & rendered, otherwise we can cause undefined behavior
		sceneManager.UpdateCurrentActiveScene();	//Don't switch our current scene around for the same reason
		sceneManager.DeleteDeadScenes();			//Don't delete our scenes for the same reason too

		//Limit FPS
		time.FPSDelay();


	}
}
