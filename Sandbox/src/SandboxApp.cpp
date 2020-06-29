#include <LittleWoodenEngine.h>

class Sandbox : public LWE::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

LWE::Application* LWE::CreateApplication()
{
	return new Sandbox();
}
