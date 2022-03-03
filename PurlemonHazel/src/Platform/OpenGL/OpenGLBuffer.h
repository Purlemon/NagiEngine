#pragma once

#include "PurlemonHazel/Renderer/Buffer.h"

namespace PH {

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		inline const BufferLayout& GetLayout() const override { return layout_; }
		inline void SetLayout(const BufferLayout& layout) override { layout_ = layout; }
	private:
		unsigned int render_id_;
		BufferLayout layout_;
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