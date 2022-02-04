#include<PurlemonHazel.h>

class ExampleLayer : public PurlemonHazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		PH_INFO("ExampleLayer::Update");
	}

	void OnEvent(PurlemonHazel::Event& event) override
	{
		PH_TRACE("{0}", event);
	}

};

class Sandbox:public PurlemonHazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new PurlemonHazel::ImGuiLayer());
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