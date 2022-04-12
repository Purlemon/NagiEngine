#pragma once

#include <memory>

#ifdef NAGI_PLATFORM_WINDOWS // 在windows生效
	#if NAGI_DYNAMIC_LINK
		#ifdef NAGI_BUILD_DLL // 在Nagi中定义
			#define NAGI_API __declspec(dllexport) // 在Nagi中导出dll
		#else 
			#define NAGI_API __declspec(dllimport) // 在其他项目中导入dll
		#endif 
	#else
		#define NAGI_API
	#endif
#else
	#error NagiEngine only support windows!
#endif 

#ifdef NAGI_ENABLE_ASSERTS 
	#define NAGI_ASSERT(x, ...) { if(!(x)) { NAGI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NAGI_CORE_ASSERT(x, ...) { if(!(x)) { NAGI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NAGI_ASSERT(x, ...)
	#define NAGI_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NAGI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

typedef unsigned int ph_uint32;
typedef char ph_uint8;

namespace Nagi {

	// 便于之后更改实现
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}