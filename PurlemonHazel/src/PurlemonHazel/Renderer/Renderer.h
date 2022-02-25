#pragma once

namespace PurlemonHazel {

	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return renderer_api_; }
	private:
		static RendererAPI renderer_api_;
	};

}