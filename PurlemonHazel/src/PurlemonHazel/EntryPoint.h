#pragma once
// 定义跨平台的入口点

#ifdef PH_PLATFORM_WINDOWS // 在windows生效

extern PH::Application* PH::CreateApplication();

int main(int argc, char** argv)
{
	PH::Log::Init();
	PH_CORE_WARN("Initialized Log!");

	std::cout << "Hello PurlemonHazel!\n";
	auto app = PH::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error PH only support windows!
#endif 