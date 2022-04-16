#include <NagiEngine.h>
#include "NagiEngine/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Nagi {

	class NagiEditor : public Application
	{
	public:
		NagiEditor()
			: Application("Nagi Editor", 1920, 1280)
		{
			PushLayer(new EditorLayer());
		}

		~NagiEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new NagiEditor();
	}

}