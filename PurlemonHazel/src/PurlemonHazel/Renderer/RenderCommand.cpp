#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace PH {

	// TODO: ѡ����Ⱦ��ʽ
	RendererAPI* RenderCommand::renderer_api_ = new OpenGLRendererAPI();

}