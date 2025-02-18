#pragma once

#ifdef PHV_PLATFORM_WINDOWS

extern phv::Application* phv::CreateApplication();

int main(int argc, char** argv)
{
	phv::Log::Init();

	auto app = phv::CreateApplication();
	app->init();
	app->loop();
	delete app;
}

#endif