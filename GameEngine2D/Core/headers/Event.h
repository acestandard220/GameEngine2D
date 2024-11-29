#pragma once
#include "pch.h"

enum EventType 
{
    EVENT_TYPE_KEY,
    EVENT_TYPE_MOUSE,
    EVENT_TYPE_MOUSE_SCROLL,
    EVENT_TYPE_RESIZE,

    EVENT_TYPE_UNKNOWN
};

struct Event
{
    EventType type;
    bool handled;
 
    virtual EventType Get() = 0;
};

struct KeyEvent : Event
{
    int __key;
    int __action;
    int __mods;
    int __scancode;
    static EventType GetStaticType()
    {
        return EVENT_TYPE_KEY;
    }
    virtual EventType Get() override {
       return  GetStaticType();
    }
};

struct MouseMoveEvent :Event
{
    double __xPos;
    double __yPos;
    static EventType GetStaticType()
    {
        return EVENT_TYPE_MOUSE;
    }
    virtual EventType Get() override {
        return  GetStaticType();
    }
};

struct MouseScrollEvent : Event
{
    double __xOffset;
    double __yOffset;

    static EventType GetStaticType()
    {
        return EVENT_TYPE_MOUSE_SCROLL;
    }
    virtual EventType Get() override {
        return  GetStaticType();
    }
};

struct WindowResizeEvent : Event
{
    int __width;
    int __height;

    static EventType GetStaticType()
    {
        return EVENT_TYPE_RESIZE;
    }
    virtual EventType Get() override {
        return GetStaticType();
    }
};


using EventCallbackFn = std::function<void(Event& _event)>;


class EventManager
{   
    public:
        EventManager() = default;
        
        void Init(GLFWwindow* window);
    
        void SetEventCallBackFn(EventCallbackFn callback);
        
      
    private:
        static void KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void CloseWindowCallBack(GLFWwindow* window);
        static void MouseCallBack(GLFWwindow* window, double xPos, double yPos);
        static void ResizeCalllback(GLFWwindow* window, int width, int height);
        static void ScrollCallBack(GLFWwindow* window, double xOffset, double yOffset);
    private:
        static EventCallbackFn EventCallback;
    
};

class EventDispatcher
{
    public:
         EventDispatcher(Event& e) : _event(e){}
        
        template <typename T,typename F>
        bool Dispatch(const F& callback)
        {
            if(T::GetStaticType() == _event.type)
            {
                callback((T&)_event);
                return true;
            }
            return false;
        }
    private:
        Event& _event;
};
