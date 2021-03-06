#include "BlueBell.h"

#include "Events/EventManager.h"

class SandBox : public BlueBell::Application
{
public: 

	SandBox();
	~SandBox();

	void CreateEntities() override;

	void TestFunction(BlueBell::RefPtr<int>& rRefPtr);

	void OnImGuiRender(BlueBell::OnImGuiRenderArgs& args);

	void OnInput(BlueBell::OnInputArgs& args);

private:
	BlueBell::Overlay m_overlay;
	BlueBell::Vector2D m_relativePosition;
	BlueBell::Vector2D m_absolutePosition;
};