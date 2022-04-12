#pragma once

#include "NagiEngine/Renderer/VertexArray.h"

namespace Nagi {

	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const Nagi::Ref<VertexBuffer>& vertex_buffer) override;
		void SetIndexBuffer(const Nagi::Ref<IndexBuffer>& index_buffer) override;
	
		const std::vector<Nagi::Ref<VertexBuffer>>& GetVertexBuffers()const override { return vertex_buffers_; }
		const Nagi::Ref<IndexBuffer>& GetIndexBuffer()const override { return index_buffers_;  }
	private:
		ph_uint32 render_id_;
		std::vector<Nagi::Ref<VertexBuffer>>vertex_buffers_;
		Nagi::Ref<IndexBuffer>index_buffers_;
	};

}