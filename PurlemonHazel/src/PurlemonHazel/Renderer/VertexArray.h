#pragma once

#include <memory>

#include "Buffer.h"

namespace PH {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const PH::Ref<VertexBuffer>& vertex_buffer) = 0;
		virtual void SetIndexBuffer(const PH::Ref<IndexBuffer>& index_buffer) = 0;

		virtual const std::vector<PH::Ref<VertexBuffer>>& GetVertexBuffers()const = 0;
		virtual const PH::Ref<IndexBuffer>& GetIndexBuffer()const = 0;

		static VertexArray* Create();
	};

}