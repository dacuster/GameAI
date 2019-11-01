#include "InterfaceEvents.h"


MouseMoveEvent::MouseMoveEvent(const Vector2D& location, const MouseButtonState& state)
	:InterfaceEvent(MOUSE_MOVE_EVENT)
	,mLoc(location)
	,mState(state)
{
}

InterfaceEvent::PressState MouseMoveEvent::getPressedState(InterfaceEvent::MouseButton theButton)
{
	return (InterfaceEvent::PressState)mState.getPressedState((MouseButtonState::MouseButton)theButton);
}

MouseButtonEvent::MouseButtonEvent(const Vector2D& location, InterfaceEvent::MouseButton button, InterfaceEvent::PressState state)
	:InterfaceEvent(MOUSE_BUTTON_EVENT)
	,mLoc(location)
	,mButton(button)
	,mState(state)
{
}

KeyEvent::KeyEvent(InterfaceEvent::Key key, InterfaceEvent::PressState state)
	:InterfaceEvent(KEYBOARD_EVENT)
	,mKey(key)
	,mState(state)
{
}
