#pragma once

#ifdef PH_PLATFORM_WINDOWS // 在windows生效
	#ifdef PH_BUILD_DLL // 在PurlemonHazel中定义
		#define PH_API __declspec(dllexport) // 在PurlemonHazel中导出dll
	#else 
		#define PH_API __declspec(dllimport) // 在其他项目中导入dll
	#endif 
#else
	#error PurlemonHazel only support windows!
#endif 

#define BIT(x) (1 << x)
