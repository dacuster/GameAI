#pragma once

#include <Vector2D.h>
#include <SDL.h>
#include "Event.h"
#include "InputSystem.h"

class InterfaceEvent: public Event
{
public:
	enum MouseButton
	{
		LEFT=InputSystem::LEFT,
		RIGHT= InputSystem::RIGHT,
		CENTER= InputSystem::CENTER
	};

	enum Key
	{
		F_KEY = InputSystem::F_KEY,
		S_KEY = InputSystem::S_KEY,
		L_KEY = InputSystem::L_KEY,
		ENTER_KEY = InputSystem::ENTER_KEY,
		RETURN_KEY = InputSystem::RETURN_KEY,
		SPACE_KEY = InputSystem::SPACE_KEY,
		ESCAPE_KEY = InputSystem::ESCAPE_KEY
	};

	enum PressState
	{
		PRESSED = InputSystem::PRESSED,
		RELEASED = InputSystem::RELEASED
	};


	InterfaceEvent(EventType type) :Event(type) {};
	~InterfaceEvent() {};
};

class MouseMoveEvent : public InterfaceEvent
{
public:
	MouseMoveEvent(const Vector2D& location, const MouseButtonState& state);
	~MouseMoveEvent() {};

	const Vector2D& getLocation() const { return mLoc; };
	InterfaceEvent::PressState getPressedState(InterfaceEvent::MouseButton theButton);

private:
	Vector2D mLoc;
	MouseButtonState mState;
};

class MouseButtonEvent : public InterfaceEvent
{
public:
	MouseButtonEvent(const Vector2D& location, InterfaceEvent::MouseButton button, InterfaceEvent::PressState state);
	~MouseButtonEvent() {};

	const Vector2D& getLocation() const { return mLoc; };
	InterfaceEvent::MouseButton getButton() const { return mButton; };
	InterfaceEvent::PressState getPressedState() const { return mState; };
private:
	Vector2D mLoc;
	InterfaceEvent::MouseButton mButton;
	InterfaceEvent::PressState mState;
};

class KeyEvent : public InterfaceEvent
{
public:
	KeyEvent(InterfaceEvent::Key key, InterfaceEvent::PressState state);
	~KeyEvent() {};

	InterfaceEvent::Key getKey() const { return mKey; };
	InterfaceEvent::PressState getPressedState() const { return mState; };
private:
	InterfaceEvent::Key mKey;
	InterfaceEvent::PressState mState;
};

