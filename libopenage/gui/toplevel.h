// Copyright 2015-2015 the openage authors. See copying.md for legal info.

#ifndef OPENAGE_GUI_TOPLEVEL_H_
#define OPENAGE_GUI_TOPLEVEL_H_

#include <memory>

#include "../input/input_context.h"
#include "../input/action.h"

#include "absolutelayout.h"
#include "container.h"
#include "layout.h"

namespace openage {
namespace gui {

class TopLevel : public Container {
public:
	TopLevel(input::InputContext &mode) : mode(mode) {
		set_layout_data(AbsoluteLayoutData{});
		this->mode.bind(input::event_class::MOUSE_BUTTON, [this](const input::action_arg_t &arg) {
			return this->handle_mouse(arg);
		});
	}

	void resize(int w, int h) {
		dynamic_cast<AbsoluteLayoutData &>(*layout_data).set_position(0, 0, w, h);
		needs_layout = true;
		layout->layout(*this);
	}

	virtual std::tuple<int, int> get_best_size() const override {
		return std::make_tuple(0, 0);
	}

protected:
	std::unique_ptr<Control> control;
	bool handle_mouse(const input::action_arg_t &arg) override;

private:
	input::InputContext &mode;
};

} // namespace gui
} // namespace openage

#endif

