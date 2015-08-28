// Copyright 2015-2015 the openage authors. See copying.md for legal info.

#include "../log/log.h"
#include "toplevel.h"

namespace openage {
namespace gui {

bool TopLevel::handle_mouse(const input::action_arg_t &arg) {
	for (auto &control : this->get_controls()) {
		log::log(MSG(info) << "toplevel");
		if (control->handle_mouse(arg)) {
			return true;
		}
	}
	return false;
}

} // namespace gui
} // namespace openage
