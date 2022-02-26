#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"
#include "Input.h"

#include <glad/glad.h>

namespace PurlemonHazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::instance_ = nullptr;

	Application::Application()
	{
		PH_CORE_ASSERT(!instance_, "Application已经存在！");
		instance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_FN(OnEvent));
	
		imgui_layer_ = new ImGuiLayer();
		PushOverlay(imgui_layer_);

		// ----------------------------
		// OpenGL Render
		// ----------------------------

		// 三角形
		vertex_array_.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};
		std::shared_ptr<VertexBuffer>vertex_buffer_;
		vertex_buffer_.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertex_buffer_->SetLayout(layout);
		vertex_array_->AddVertexBuffer(vertex_buffer_);

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<IndexBuffer>index_buffer_;
		index_buffer_.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		vertex_array_->SetIndexBuffer(index_buffer_);

		std::string vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		shader_.reset(new Shader(vertex_src, fragment_src));
	
		// 正方形
		square_va_.reset(VertexArray::Create());

		float square_vertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f, 
			 0.75f, -0.75f, 0.0f, 
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};
		
		std::shared_ptr<VertexBuffer>square_vb;
		square_vb.reset(VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_vb->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		square_va_->AddVertexBuffer(square_vb);

		unsigned int square_indices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<IndexBuffer>square_ib;
		square_ib.reset(IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(unsigned int)));
		square_va_->SetIndexBuffer(square_ib);

		std::string blue_vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string blue_fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
			}
		)";
		blue_shader_.reset(new Shader(blue_vertex_src, blue_fragment_src));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		layer_stack_.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		layer_stack_.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		// 接收到WindowCloseEvent事件关闭窗口
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// 对所有层进行OnEvent调用
		for (auto it = layer_stack_.end(); it != layer_stack_.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.handled_)
				break;
		}
	}

	void Application::Run()
	{
		while (running_) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			blue_shader_->Bind();
			square_va_->Bind();
			glDrawElements(GL_TRIANGLES, square_va_->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			shader_->Bind();
			vertex_array_->Bind();
			glDrawElements(GL_TRIANGLES, vertex_array_->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layer_stack_)
				layer->OnUpdate();

			imgui_layer_->Begin();
			for (Layer* layer : layer_stack_)
				layer->OnImGuiRender();
			imgui_layer_->End();

			window_->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}
}