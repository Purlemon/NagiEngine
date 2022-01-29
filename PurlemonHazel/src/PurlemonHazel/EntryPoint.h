#pragma once
// 定义跨平台的入口点

#ifdef PH_PLATFORM_WINDOWS // 在windows生效

extern PurlemonHazel::Application* PurlemonHazel::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Hello PurlemonHazel!\n";
	auto app = PurlemonHazel::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error PurlemonHazel only support windows!
#endif 