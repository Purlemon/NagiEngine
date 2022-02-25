#pragma once

#include <string>

namespace PurlemonHazel {

	class Shader
	{
	public:
		Shader(const std::string& vertex_src, const std::string& fragment_src);
		~Shader();

		void Bind()const;
		void Unbind()const;
	private:
		uint32_t render_id_;
	};

}