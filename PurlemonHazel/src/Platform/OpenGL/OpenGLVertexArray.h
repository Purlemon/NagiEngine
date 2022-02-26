#pragma once

#include "PurlemonHazel/Renderer/VertexArray.h"

namespace PurlemonHazel {

	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) override;
	
		const inline std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers()const override { return vertex_buffers_; }
		const inline std::shared_ptr<IndexBuffer>& GetIndexBuffer()const override { return index_buffers_;  }
	private:
		unsigned int render_id_;
		std::vector<std::shared_ptr<VertexBuffer>>vertex_buffers_;
		std::shared_ptr<IndexBuffer>index_buffers_;
	};

}