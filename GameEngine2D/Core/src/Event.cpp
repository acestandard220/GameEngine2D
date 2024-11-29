#include "Application.h"
#include "Event.h"

EventCallbackFn EventManager::EventCallback = nullptr;


void EventManager::Init(GLFWwindow* window) {
	glfwSetKeyCallback(window, KeyBoardCallBack);
	glfwSetWindowCloseCallback(window, CloseWindowCallBack);
	glfwSetCursorPosCallback(window,MouseCallBack);
	glfwSetFramebufferSizeCallback(window, ResizeCalllback);
	glfwSetScrollCallback(window, ScrollCallBack);
}

void EventManager::KeyBoardCallBack(GLFWwindow* window,int key,int scancode,int action,int mods)
{
	KeyEvent keyevent;
	keyevent.type = EVENT_TYPE_KEY;
	keyevent.__key = key;
	keyevent.__action = action;
	keyevent.__mods = mods;
	keyevent.__scancode = scancode;

	keyevent.handled = false;

	EventCallback(keyevent);
}

void EventManager::CloseWindowCallBack(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, true);
}

void EventManager::MouseCallBack(GLFWwindow* window, double xPos, double yPos)
{
	MouseMoveEvent mouseevent;
	mouseevent.type = EVENT_TYPE_MOUSE;
	mouseevent.__xPos = xPos;
	mouseevent.__yPos = yPos;

	mouseevent.handled = false;

	EventCallback(mouseevent);
}



void EventManager::SetEventCallBackFn(EventCallbackFn callback)
{
    EventCallback = callback;
}

void EventManager::ResizeCalllback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	WindowResizeEvent windowresize;
	windowresize.__width = width;
	windowresize.__height = height;

	windowresize.type = EVENT_TYPE_RESIZE;
	windowresize.handled = false;

	EventCallback(windowresize);

}


void EventManager::ScrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
{
	MouseScrollEvent mousescroll;
	
	mousescroll.type = EVENT_TYPE_MOUSE_SCROLL;
	mousescroll.__xOffset = xOffset;
	mousescroll.__yOffset = yOffset;

	mousescroll.handled = false;

	EventCallback(mousescroll);
}


