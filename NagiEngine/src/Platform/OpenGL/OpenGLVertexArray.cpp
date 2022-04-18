#include "ngpch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Nagi {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type) {
		case Nagi::ShaderDataType::Float:		return GL_FLOAT;
		case Nagi::ShaderDataType::Float2:		return GL_FLOAT;
		case Nagi::ShaderDataType::Float3:		return GL_FLOAT;
		case Nagi::ShaderDataType::Float4:		return GL_FLOAT;
		case Nagi::ShaderDataType::Mat3:		return GL_FLOAT;
		case Nagi::ShaderDataType::Mat4:		return GL_FLOAT;
		case Nagi::ShaderDataType::Int:		return GL_INT;
		case Nagi::ShaderDataType::Int2:		return GL_INT;
		case Nagi::ShaderDataType::Int3:		return GL_INT;
		case Nagi::ShaderDataType::Int4:		return GL_INT;
		case Nagi::ShaderDataType::Bool:		return GL_BOOL;
		}

		NAGI_CORE_ASSERT(false, "Unknown ShaderDataType!");
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

	void OpenGLVertexArray::AddVertexBuffer(const Nagi::Ref<VertexBuffer>& vertex_buffer)
	{
		NAGI_CORE_ASSERT(vertex_buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(render_id_);
		vertex_buffer->Bind();
		
		ng_uint32 index = 0;
		const auto& layout = vertex_buffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			// 传入int用glVertexAttribIPointer，否则会被转换为float
			if (ShaderDataTypeToOpenGLBaseType(element.type) == GL_INT) {
				glVertexAttribIPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					layout.GetStride(),
					(const void*)element.offset);
			}
			else {
				glVertexAttribPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset);
			}
			++index;
		}
		
		vertex_buffers_.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Nagi::Ref<IndexBuffer>& index_buffer)
	{
		glBindVertexArray(render_id_);
		index_buffer->Bind();

		index_buffers_ = index_buffer;
	}

}