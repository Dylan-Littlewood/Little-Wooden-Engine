#pragma once

#include "lwpch.hpp"

#include "LittleWooden/Core/Base.hpp"
#include "LittleWooden/Events/Event.hpp"

namespace LittleWooden {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool Borders;

		WindowProps(const std::string& title = "Little Wooden Engine", unsigned int width = 1280, unsigned int height = 720, bool borders = true)
			:Title(title), Width(width), Height(height), Borders(borders)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void CallEvent(Event& event) = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}