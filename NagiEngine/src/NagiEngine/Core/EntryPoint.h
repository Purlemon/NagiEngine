#pragma once
// �����ƽ̨����ڵ�

#ifdef NAGI_PLATFORM_WINDOWS // ��windows��Ч

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