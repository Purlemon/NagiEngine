#pragma once
// 定义跨平台的入口点

#ifdef PH_PLATFORM_WINDOWS // 在windows生效

extern PH::Application* PH::CreateApplication();

int main(int argc, char** argv)
{
	PH::Log::Init();
	PH_CORE_WARN("Initialized Log!");
	int a = 5;
	PH_INFO("Hello!Var={0}",a);

	std::cout << "Hello PH!\n";
	auto app = PH::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error PH only support windows!
#endif 