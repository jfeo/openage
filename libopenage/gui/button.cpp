// Copyright 2015-2015 the openage authors. See copying.md for legal info.

#include "button.h"

#include <SDL2/SDL_mouse.h>
#include "../log/log.h"

namespace openage {
namespace gui {

bool Button::handle_mouse(const input::action_arg_t &arg) {
	if (arg.e.cc.code != 1)
	{
		return false;
	}
	if (!this->contains(arg.mouse.x, arg.mouse.y)) {
		return false;
	}
	switch (arg.e.cc.eclass) {
		case input::event_class::MOUSE_DOWN:
			this->set_state(State::DOWN);
			break;
		case input::event_class::MOUSE_UP:
			this->set_state(State::NORMAL);
			break;
		case input::event_class::MOUSE_BUTTON:
			if (this->click_func.get() != nullptr) {
				(*this->click_func.get())();
			}
			break;
		default:
			return false;
	}
	return true;
}

void Button::set_click(const std::function<void(void)> func) {
	this->click_func = std::make_unique<std::function<void(void)>>(func);
}

void Button::set_state(State new_state) {
	state = new_state;
	sig_state_change.emit(new_state);
}

} // namespace gui
} // namespace openage
