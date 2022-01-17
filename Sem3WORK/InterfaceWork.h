#pragma once
#include "Interface.h"

namespace WORK {

	template <class TypeArray>
	class InterfaceWork : public Interface<TypeArray>
	{

	private:
		InterfaceWork() = delete;
	public:
		InterfaceWork(TypeArray array) : Interface<TypeArray>(array) {}
	};

}