#include "Application.h"
#include "../Logging/Logger.h"
#include "../Core/BlueBerry.h"
#include "../Platform/GraphicsAPI.h"

extern BlueBell::Application* BlueBell::CreateApplication();

int main()
{
	BlueBell::Logger::Init();

	BB_LOG_INFO("BlueBell starting up...");

	BlueBell::InitBlueBerry();
	BlueBell::Application* app = BlueBell::CreateApplication();

	app->Run();
	delete app;
	BlueBell::DeleteBlueBerry();
}