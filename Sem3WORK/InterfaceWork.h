#pragma once
#include "Interface.h"

namespace WORK {

	template <class TypeArray>
	class InterfaceWork : public Interface<TypeArray>
	{

	private:
		InterfaceWork() = delete;
	public:
		InterfaceWork(TypeArray&& array);


		void readKey();
	};

}


/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
												/* Определение методов */



template <typename TypeArray>
WORK::InterfaceWork<TypeArray>::InterfaceWork(TypeArray&& array)
	: Interface<TypeArray>(std::move(array)) {}

template<class TypeArray>
void WORK::InterfaceWork<TypeArray>::readKey()
{
	
	if (this->getActiveKey() == Keys::EmptyKey)
	{
		this->setActiveKey(static_cast<Keys>(std::cin.get()));	// Принимаем один символ
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем остальной буфер
	}
	switch (this->getActiveKey())
	{
	case Keys::Exit:                                    // 0
		exit(0);                                        // Выход из цикла
		break;
	case Keys::DirectSelectionSort:                     // 1
		break;
	case Keys::ShakerSort:								// 2
		break;
	case Keys::ShellSorting:							// 3
		break;
	case Keys::Pyramid:									// 4
		break;
	case Keys::HoareSorting:							// 5
		break;
	case Keys::Merger:									// 6
		break;
	case Keys::DigitalSorting:							// 7
		break;
	case Keys::QuickSearchBegin:						// 8
		break;
	case Keys::QuickSearchEnd:							// 9
		break;
	default:
		this->addToStatusBar("Введена не верная команда!");            // любая клавиша отсутствующая в перечислении Keys
		break;
	}
	this->setActiveKey(Keys::EmptyKey);
}
