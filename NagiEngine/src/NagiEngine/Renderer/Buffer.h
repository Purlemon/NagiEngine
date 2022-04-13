#pragma once

#include <string>
#include "NagiEngine/Core/Core.h"
#include "NagiEngine/Core/Log.h"

#include <vector>

namespace Nagi {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static ng_uint32 ShaderDataTypeSize(ShaderDataType type) // ÿ��buffer��Ĵ�С
	{
		switch (type) {
			case Nagi::ShaderDataType::Float:		return 4;
			case Nagi::ShaderDataType::Float2:     return 4 * 2;
			case Nagi::ShaderDataType::Float3:     return 4 * 3;
			case Nagi::ShaderDataType::Float4:     return 4 * 4;
			case Nagi::ShaderDataType::Mat3:		return 4 * 3 * 3;
			case Nagi::ShaderDataType::Mat4:		return 4 * 4 * 4;
			case Nagi::ShaderDataType::Int:		return 4;
			case Nagi::ShaderDataType::Int2:		return 4 * 2;
			case Nagi::ShaderDataType::Int3:		return 4 * 3;
			case Nagi::ShaderDataType::Int4:		return 4 * 4;
			case Nagi::ShaderDataType::Bool:		return 1;
		}
		
		NAGI_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		ng_uint32 size;
		ng_uint32 offset;
		bool normalized;

		BufferElement(){ }

		BufferElement(ShaderDataType this_type, const std::string& this_name, bool this_normalized = false)
			:type(this_type), name(this_name), size(ShaderDataTypeSize(this_type)), offset(0),normalized(this_normalized)
		{
		}

		ng_uint32 GetComponentCount()const // ÿ��buffer�����Ԫ�ص�����
		{
			switch (type) {
				case Nagi::ShaderDataType::Float:		return 1;
				case Nagi::ShaderDataType::Float2:		return 2;
				case Nagi::ShaderDataType::Float3:		return 3;
				case Nagi::ShaderDataType::Float4:		return 3;
				case Nagi::ShaderDataType::Mat3:		return 3 * 3;
				case Nagi::ShaderDataType::Mat4:		return 4 * 4;
				case Nagi::ShaderDataType::Int:		return 1;
				case Nagi::ShaderDataType::Int2:		return 2;
				case Nagi::ShaderDataType::Int3:		return 3;
				case Nagi::ShaderDataType::Int4:		return 4;
				case Nagi::ShaderDataType::Bool:		return 1;
			}

			NAGI_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	}; 

	class BufferLayout
	{
	public:
		BufferLayout(){ }

		BufferLayout(const std::initializer_list<BufferElement>& element) // ����vector���������⹹��һ��
			:elements_(element), stride_(0)
		{
			CalculateOffsetsAndStride();
		}

		const std::vector<BufferElement>& GetElements()const { return elements_; }
		ng_uint32 GetStride()const { return stride_; }

		std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
		std::vector<BufferElement>::iterator end() { return elements_.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			ng_uint32 offset = 0;
			stride_ = 0;
			for (auto& element : elements_) {
				element.offset = offset;
				offset += element.size;
				stride_ += element.size;
			}
		}
	private:
		std::vector<BufferElement>elements_;
		ng_uint32 stride_;
	};

	// -----------------------------
	// -----------Buffer------------
	// -----------------------------

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const= 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, ng_uint32 size) = 0;

		virtual const BufferLayout& GetLayout()const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(float* vertices, ng_uint32 size); // �𵽹��캯��������
		static Ref<VertexBuffer> Create(ng_uint32 size); // �𵽹��캯��������
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual ng_uint32 GetCount()const = 0;

		static Ref<IndexBuffer> Create(ng_uint32* indices, ng_uint32 count);
	};

}