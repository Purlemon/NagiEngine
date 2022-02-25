#pragma once

namespace PurlemonHazel {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const= 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, unsigned int size); // 起到构造函数的作用
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount()const = 0;

		static IndexBuffer* Create(unsigned int* indices, unsigned int count);
	};

}