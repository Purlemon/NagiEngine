#pragma once

#include <memory>

#include "Buffer.h"

namespace Nagi {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Nagi::Ref<VertexBuffer>& vertex_buffer) = 0;
		virtual void SetIndexBuffer(const Nagi::Ref<IndexBuffer>& index_buffer) = 0;

		virtual const std::vector<Nagi::Ref<VertexBuffer>>& GetVertexBuffers()const = 0;
		virtual const Nagi::Ref<IndexBuffer>& GetIndexBuffer()const = 0;

		static Ref<VertexArray> Create();
	};

}