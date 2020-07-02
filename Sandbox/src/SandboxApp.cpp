#include <LittleWooden.hpp>

class Sandbox : public LittleWooden::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

LittleWooden::Application* LittleWooden::CreateApplication()
{
	return new Sandbox();
}
