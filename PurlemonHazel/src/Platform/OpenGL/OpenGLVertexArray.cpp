#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace PH {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type) {
		case PH::ShaderDataType::Float:		return GL_FLOAT;
		case PH::ShaderDataType::Float2:		return GL_FLOAT;
		case PH::ShaderDataType::Float3:		return GL_FLOAT;
		case PH::ShaderDataType::Float4:		return GL_FLOAT;
		case PH::ShaderDataType::Mat3:		return GL_FLOAT;
		case PH::ShaderDataType::Mat4:		return GL_FLOAT;
		case PH::ShaderDataType::Int:		return GL_INT;
		case PH::ShaderDataType::Int2:		return GL_INT;
		case PH::ShaderDataType::Int3:		return GL_INT;
		case PH::ShaderDataType::Int4:		return GL_INT;
		case PH::ShaderDataType::Bool:		return GL_BOOL;
		}

		PH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &render_id_);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &render_id_);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(render_id_);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const PH::Ref<VertexBuffer>& vertex_buffer)
	{
		PH_CORE_ASSERT(vertex_buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(render_id_);
		vertex_buffer->Bind();
		
		unsigned int index = 0;
		const auto& layout = vertex_buffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset);
			++index;
		}
		
		vertex_buffers_.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const PH::Ref<IndexBuffer>& index_buffer)
	{
		glBindVertexArray(render_id_);
		index_buffer->Bind();

		index_buffers_ = index_buffer;
	}

}