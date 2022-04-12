#pragma once

#include "PurlemonHazel/Renderer/VertexArray.h"

namespace PH {

	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const PH::Ref<VertexBuffer>& vertex_buffer) override;
		void SetIndexBuffer(const PH::Ref<IndexBuffer>& index_buffer) override;
	
		const std::vector<PH::Ref<VertexBuffer>>& GetVertexBuffers()const override { return vertex_buffers_; }
		const PH::Ref<IndexBuffer>& GetIndexBuffer()const override { return index_buffers_;  }
	private:
		ph_uint32 render_id_;
		std::vector<PH::Ref<VertexBuffer>>vertex_buffers_;
		PH::Ref<IndexBuffer>index_buffers_;
	};

}