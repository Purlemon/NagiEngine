#pragma once

#include "PurlemonHazel/Renderer/Buffer.h"

namespace PurlemonHazel {

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
	private:
		unsigned int render_id_;
	};
	
	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		
		inline unsigned int GetCount() const override{ return count_; }
	private:
		unsigned int render_id_;
		unsigned int count_;
	};

}