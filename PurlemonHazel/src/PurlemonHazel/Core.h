#pragma once

#ifdef PH_PLATFORM_WINDOWS // ��windows��Ч
	#ifdef PH_BUILD_DLL // ��PurlemonHazel�ж���
		#define PH_API __declspec(dllexport) // ��PurlemonHazel�е���dll
	#else 
		#define PH_API __declspec(dllimport) // ��������Ŀ�е���dll
	#endif 
#else
	#error PurlemonHazel only support windows!
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