#pragma once

#include <cstddef>

using ComponentTypeID = std::size_t;
template <typename T> inline auto GetComponentTypeID() -> ComponentTypeID {
	static int component_type_id = []() {
		static int id_counter = 0;
		return id_counter++;
	}();

	return component_type_id;
};

