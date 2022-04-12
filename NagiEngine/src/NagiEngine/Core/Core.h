#pragma once

#include <memory>

#ifdef NAGI_PLATFORM_WINDOWS // ��windows��Ч
	#if NAGI_DYNAMIC_LINK
		#ifdef NAGI_BUILD_DLL // ��Nagi�ж���
			#define NAGI_API __declspec(dllexport) // ��Nagi�е���dll
		#else 
			#define NAGI_API __declspec(dllimport) // ��������Ŀ�е���dll
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

	// ����֮�����ʵ��
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