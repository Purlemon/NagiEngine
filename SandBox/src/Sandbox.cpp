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

// ʵ����ڷ���
PurlemonHazel::Application* PurlemonHazel::CreateApplication()
{
	return new Sandbox();
}