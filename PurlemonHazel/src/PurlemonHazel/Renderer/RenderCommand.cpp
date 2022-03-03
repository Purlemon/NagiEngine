#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace PH {

	// TODO: —°‘Ò‰÷»æ∑Ω Ω
	RendererAPI* RenderCommand::renderer_api_ = new OpenGLRendererAPI();

}