#include "SandBox.h"

#include "imgui.h"
#include "Tests/HLSLParserTest.h"

SandBox::SandBox()
	: m_overlay("Test")
	, m_relativePosition(BlueBell::Vector2D::Zero)
	, m_absolutePosition(BlueBell::Vector2D::Zero)
{
	BB_LOG_INFO("Sandbox loading up...");

	CreateEntities();

	BlueBell::StackPtr<int> stackPtr = BlueBell::MakeStackPtr<int>(22);

	BlueBell::RefPtr<int> refPtr = BlueBell::MakeRefPtr<int>(222);

	BlueBell::StackPtr<int> stackPtr2 = stackPtr;

	BlueBell::EventManager::GetInstance()->AddReceiverToEvent<BlueBell::OnImGuiRenderArgs>(BB_BIND_FUNC(OnImGuiRender, this));

	BlueBell::GameObject gameObject;

	BlueBell::CameraComponent* pCameraComponent = gameObject.CreateComponent<BlueBell::CameraComponent>(0, 0, 2564, 990, -1, 1000);
	gameObject.CreateComponent<BlueBell::CameraControllerComponent>();
	
	float aspectRatio = 2564.0f / 990.0f;
	float fov = 45;
	pCameraComponent->ApplyPerspective(aspectRatio, fov);

	m_overlay.AddVariable(&m_relativePosition, "Relative position", BlueBell::Overlay::VariableType::Vector2D);
	m_overlay.AddVariable(&m_absolutePosition, "Absolute position", BlueBell::Overlay::VariableType::Vector2D);

	BlueBell::EventManager::GetInstance()->AddReceiverToEvent<BlueBell::OnInputArgs>(BB_BIND_FUNC(OnInput, this));

	HLSLParser parser;
	parser.Parse();
}

SandBox::~SandBox()
{
}

void SandBox::CreateEntities()
{
	// Create entities here

}

void SandBox::TestFunction(BlueBell::RefPtr<int>& rRefPtr)
{
	
}

void SandBox::OnImGuiRender(BlueBell::OnImGuiRenderArgs& args)
{
	m_overlay.Render();
}

void SandBox::OnInput(BlueBell::OnInputArgs& args)
{
	if (args.device == BlueBell::InputDevice::Mouse)
	{
		if (args.mouse.mouseType == BlueBell::InputMouseType::Position)
		{
			m_relativePosition = args.mouse.mousePosition.relative;
			m_absolutePosition = args.mouse.mousePosition.absolute;
		}
		else if (args.mouse.mouseType == BlueBell::InputMouseType::Button)
		{
			int i = 0;
		}
	}
}

BlueBell::Application* BlueBell::CreateApplication()
{
	return new SandBox();
}


