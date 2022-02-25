#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace PurlemonHazel {

	// ------------------------------------------
	// OpenGLVertexBuffer
	// ------------------------------------------

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
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

	// ------------------------------------------
	// OpenGLIndexBuffer
	// ------------------------------------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
		:count_(count)
	{
		glCreateBuffers(1, &render_id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
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