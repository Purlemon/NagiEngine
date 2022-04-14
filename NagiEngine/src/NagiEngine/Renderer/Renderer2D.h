#pragma once

#include "OrthographicCamera.h"

#include "Texture.h"

namespace Nagi {

	// �����ı�����Ϣ
	struct QuadProps
	{
		glm::vec3 position;
		glm::vec2 size;
		float rotation;

		QuadProps(const glm::vec3& this_position, const glm::vec2& this_size, float this_rotation = 0.0f)
			:position(this_position), size(this_size), rotation(this_rotation) {}
		QuadProps(const glm::vec2& this_position, const glm::vec2& this_size, float this_rotation = 0.0f)
			:position(glm::vec3(this_position.x, this_position.y, 0.0f)), size(this_size), rotation(this_rotation) {}
	};

	// ����2D������Ϣ
	struct Texture2DPorps
	{
		Ref<Texture2D> texture;
		float tiling_factor;	// �������ظ���ϵ��
		glm::vec4 tint_color;	// ��ɫ�˾�

		Texture2DPorps()
			:Texture2DPorps(nullptr) { }

		Texture2DPorps(const Ref<Texture2D>& this_texture, const glm::vec4& this_tint_color)
			:Texture2DPorps(this_texture, 1.0f, this_tint_color){ }

		Texture2DPorps(const Ref<Texture2D>& this_texture, 
			float this_tiling_factor = 1.0f, 
			const glm::vec4& this_tint_color = glm::vec4(1.0f))
			:texture(this_texture), tiling_factor(this_tiling_factor), tint_color(this_tint_color) { }
		
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const QuadProps& quad_props, const glm::vec4& color);
		static void DrawQuad(const QuadProps& quad_props, const Texture2DPorps& tex2d_porps);

		// ֡״̬ͳ��
		struct FrameStatistics
		{
			ng_sizei quad_count;
			ng_sizei batch_count;

			ng_sizei GetTriangleCount() { return quad_count * 2; }
		};
		static void ResetStatistics();
		static FrameStatistics GetStatistics();

	private:
		static void FlushAndReset();	// ����һ��DrawCall���quad��ʱ�ٴ�DrawCall
		static void ResetBatchParams();	// ��������ɻ��ƺ�, ��Ҫ�����µ�DrawCall���ò���
	};

}