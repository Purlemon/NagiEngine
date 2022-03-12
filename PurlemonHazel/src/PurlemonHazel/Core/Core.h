#pragma once

#include <memory>

#ifdef PH_PLATFORM_WINDOWS // 在windows生效
	#if PH_DYNAMIC_LINK
		#ifdef PH_BUILD_DLL // 在PH中定义
			#define PH_API __declspec(dllexport) // 在PH中导出dll
		#else 
			#define PH_API __declspec(dllimport) // 在其他项目中导入dll
		#endif 
	#else
		#define PH_API
	#endif
#else
	#error PH only support windows!
#endif 

#ifdef PH_ENABLE_ASSERTS 
	#define PH_ASSERT(x, ...) { if(!(x)) { PH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PH_CORE_ASSERT(x, ...) { if(!(x)) { PH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PH_ASSERT(x, ...)
	#define PH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define PH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace PH {

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