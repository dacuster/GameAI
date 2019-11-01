#include "InputSystem.h"
#include "InterfaceEvents.h"
#include "EventSystem.h"

#include <iostream>
#include <cassert>
#include <SDL.h>

using namespace std;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	cleanup();
}

bool InputSystem::init()
{
	return true;
}

void InputSystem::cleanup()
{
}

void InputSystem::update(double dt)
{
	SDL_PumpEvents();

	SDL_Event theEvent;

	while (SDL_PollEvent(&theEvent))
	{
		switch (theEvent.type)
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			processKeyEvent(theEvent.key);
			break;
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			processMouseEvent(theEvent);
			break;
		case SDL_WINDOWEVENT:
			processWindowEvent(theEvent.window);
			break;
		}
	}
}

Vector2D InputSystem::getCurrentMousePos()
{
	int x,y;

	SDL_GetMouseState(&x, &y);

	return Vector2D(x, y);
}

bool InputSystem::isMouseButtonPressed(MouseButton button)
{
	int x, y;

	Uint32 state = SDL_GetMouseState(&x, &y);
	return (state & SDL_BUTTON(button));
}

bool InputSystem::isKeyPressed(Key theKey)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	return state[SDL_GetScancodeFromKey(theKey)];
}

void InputSystem::processKeyEvent(const SDL_KeyboardEvent& theEvent)
{
	InterfaceEvent::PressState pressed = InterfaceEvent::RELEASED;
	if (theEvent.type == SDL_KEYDOWN)
	{
		pressed = InterfaceEvent::PRESSED;
	}
	SDL_Keysym theKey = theEvent.keysym;

	EventSystem::getInstance()->fireEvent(KeyEvent((InterfaceEvent::Key)theKey.sym, pressed));
}

void InputSystem::processMouseEvent(const SDL_Event& theEvent)
{
	if (theEvent.type == SDL_MOUSEMOTION)
	{
		SDL_MouseMotionEvent motionEvent = theEvent.motion;
		MouseMoveEvent mouseEvent(Vector2D(motionEvent.x, motionEvent.y), motionEvent.state);
		EventSystem::getInstance()->fireEvent(mouseEvent);
	}
	else if (theEvent.type == SDL_MOUSEBUTTONUP || theEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_MouseButtonEvent buttonEvent = theEvent.button;
		
		InterfaceEvent::MouseButton whichButton = (InterfaceEvent::MouseButton)buttonEvent.button;
		
		InterfaceEvent::PressState pressed;
		if (buttonEvent.type == SDL_MOUSEBUTTONUP)
			pressed = InterfaceEvent::RELEASED;
		else
			pressed = InterfaceEvent::PRESSED;

		MouseButtonEvent mouseEvent(Vector2D(buttonEvent.x, buttonEvent.y), whichButton, pressed);
		EventSystem::getInstance()->fireEvent(mouseEvent);
	}
}

void InputSystem::processWindowEvent(const SDL_WindowEvent& theEvent)
{
	//nothing for now
}

/*

void InputSystem::processAllegroMouseEvent(const ALLEGRO_EVENT& theEvent)
{
	Vector2D loc(theEvent.mouse.x, theEvent.mouse.y);

	EventSystem::getInstance()->fireEvent(MouseMoveEvent(loc));
}

void InputSystem::processAllegroMouseButtonEvent(const ALLEGRO_EVENT& theEvent)
{
	InterfaceEvent::PressState pressed = InterfaceEvent::RELEASED;
	if (theEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		pressed = InterfaceEvent::PRESSED;
	}

	InterfaceEvent::MouseButton button = InterfaceEvent::LEFT;
	if (theEvent.mouse.button & 2)
	{
		button = InterfaceEvent::RIGHT;
	}
	else if(theEvent.mouse.button & 4)
	{
		button = InterfaceEvent::CENTER;
	}

	Vector2D loc(theEvent.mouse.x, theEvent.mouse.y);

	EventSystem::getInstance()->fireEvent(MouseButtonEvent(loc, button, pressed));
}
*/

MouseButtonState::MouseButtonState(Uint32 state)
	:mState(state)
{
}

MouseButtonState::PressState MouseButtonState::getPressedState(MouseButton theButton)
{
	if (mState & SDL_BUTTON(theButton))
		return PRESSED;
	else
		return RELEASED;
}
