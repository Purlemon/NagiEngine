#pragma once

#include "NagiEngine/Renderer/Buffer.h"

namespace Nagi {

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(ng_uint32 size);
		OpenGLVertexBuffer(float* vertices, ng_uint32 size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetData(const void* data, ng_uint32 size);

		const BufferLayout& GetLayout() const override { return layout_; }
		void SetLayout(const BufferLayout& layout) override { layout_ = layout; }
	private:
		ng_uint32 render_id_;
		BufferLayout layout_;
	};
	
	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(ng_uint32* indices, ng_uint32 count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		
		ng_uint32 GetCount() const override{ return count_; }
	private:
		ng_uint32 render_id_;
		ng_uint32 count_;
	};

}