#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nagi {

	// TODO: ѡ����Ⱦ��ʽ
	RendererAPI* RenderCommand::renderer_api_ = new OpenGLRendererAPI();

}