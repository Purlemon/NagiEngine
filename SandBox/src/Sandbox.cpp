#include<PurlemonHazel.h>

class Sandbox:public PurlemonHazel::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

};

// 实现入口方法
PurlemonHazel::Application* PurlemonHazel::CreateApplication()
{
	return new Sandbox();
}