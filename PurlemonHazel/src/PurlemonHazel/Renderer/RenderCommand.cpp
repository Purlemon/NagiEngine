#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace PurlemonHazel {

	// TODO: —°‘Ò‰÷»æ∑Ω Ω
	RendererAPI* RenderCommand::renderer_api_ = new OpenGLRendererAPI();

}