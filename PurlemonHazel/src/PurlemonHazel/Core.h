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

#define BIT(x) (1 << x)
