#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace PurlemonHazel {

	// TODO: ѡ����Ⱦ��ʽ
	RendererAPI* RenderCommand::renderer_api_ = new OpenGLRendererAPI();

}