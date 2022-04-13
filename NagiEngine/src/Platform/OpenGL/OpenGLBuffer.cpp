#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Nagi {

	// ------------------------------------------
	// OpenGLVertexBuffer
	// ------------------------------------------

	OpenGLVertexBuffer::OpenGLVertexBuffer(ng_uint32 size)
	{
		glCreateBuffers(1, &render_id_);
		glBindBuffer(GL_ARRAY_BUFFER, render_id_);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, ng_uint32 size)
	{
		glCreateBuffers(1, &render_id_);
		glBindBuffer(GL_ARRAY_BUFFER, render_id_);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &render_id_);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, render_id_);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, ng_uint32 size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, render_id_);
		// 将数据data填充进render_id_的[0, size]
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	// ------------------------------------------
	// OpenGLIndexBuffer
	// ------------------------------------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(ng_uint32* indices, ng_uint32 count)
		:count_(count)
	{
		glCreateBuffers(1, &render_id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(ng_uint32), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &render_id_);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id_);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}