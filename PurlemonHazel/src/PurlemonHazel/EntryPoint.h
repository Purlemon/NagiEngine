#pragma once
// �����ƽ̨����ڵ�

#ifdef PH_PLATFORM_WINDOWS // ��windows��Ч

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