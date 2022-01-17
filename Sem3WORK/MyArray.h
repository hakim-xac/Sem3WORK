#pragma once
#include <vector>

namespace WORK {

	template <typename Type>
	class MyArray
	{
		std::vector <Type> array;
	private:
		MyArray() = delete;
	public:
		MyArray(size_t size) : array(size) {}

	};
}
