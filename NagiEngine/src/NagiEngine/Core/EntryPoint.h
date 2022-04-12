#pragma once
// 定义跨平台的入口点

#ifdef NAGI_PLATFORM_WINDOWS // 在windows生效

extern Nagi::Application* Nagi::CreateApplication();

int main(int argc, char** argv)
{
	Nagi::Log::Init();
	NAGI_CORE_WARN("Initialized Log!");

	std::cout << "Hello NagiEngine!\n";
	auto app = Nagi::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Nagi only support windows!
#endif 