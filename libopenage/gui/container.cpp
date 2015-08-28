// Copyright 2015-2015 the openage authors. See copying.md for legal info.

#include "container.h"
#include "drawer.h"
#include "layout.h"

namespace openage {
namespace gui {

ContainerBase::ContainerBase() = default;

ContainerBase::~ContainerBase() = default;

void ContainerBase::draw(const Drawer &drawer) const {
	Drawer dr = drawer;
	dr.translate(left(), top());
	for (auto &c : controls) {
		c->draw(dr);
	}
}

bool ContainerBase::contains(int x, int y) const {
	if (!Control::contains(x, y)) return false;
	x -= left(); y -= top();
	for (auto &c : controls) {
		if (c->contains(x, y)) {
			return true;
		}
	}
	return false;
}

std::tuple<int, int> ContainerBase::get_best_size() const {
	return layout->get_best_size(controls);
}

Control *ContainerBase::control_at(int x, int y) const {
	for (auto &c : controls) {
		if (c->contains(x, y)) {
			return c.get();
		}
	}
	return nullptr;
}
	
void ContainerBase::set_layout(std::unique_ptr<Layout> &&layout) {
	this->layout = std::move(layout);
	needs_layout = true;
}

} // namespace gui
} // namespace openage
