#pragma once

#include "PurlemonHazel/Renderer/Buffer.h"

namespace PH {

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(ph_uint32 size);
		OpenGLVertexBuffer(float* vertices, ph_uint32 size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetData(const void* data, ph_uint32 size);

		const BufferLayout& GetLayout() const override { return layout_; }
		void SetLayout(const BufferLayout& layout) override { layout_ = layout; }
	private:
		ph_uint32 render_id_;
		BufferLayout layout_;
	};
	
	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(ph_uint32* indices, ph_uint32 count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		
		ph_uint32 GetCount() const override{ return count_; }
	private:
		ph_uint32 render_id_;
		ph_uint32 count_;
	};

}