#pragma once
// �����ƽ̨����ڵ�

#ifdef PH_PLATFORM_WINDOWS // ��windows��Ч

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