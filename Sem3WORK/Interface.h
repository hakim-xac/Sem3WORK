#pragma once
#include <string>
#include <queue>
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include "enums.h"

namespace WORK {
	/// <summary>
	/// Обобщеный интерфейс
	/// </summary>
	/// <typeparam name="TypeArray">Тип массива, используемого для хранения случайных чисел</typeparam>
	/// <typeparam name="TypeHashDirectBinding">Тип массива, используемого для хранения чисел в качестве
	///  хеш-таблицы используя мктод прямого связывания</typeparam>
	/// <typeparam name="TypeHashOpenAdressing">Тип массива, используемого для хранения чисел в качестве
	///  хеш-таблицы используя метод открытой адрессации</typeparam>
	template <class TypeArray>
	class Interface
	{
		std::ostream& out;										// буфер вывода
		size_t						maxTableWidth;				// ширина выводимой строки
		int							maxTableColumnsInArray;		// количество колонов при выводе массива
		const size_t				maxSize;
		std::queue <std::string>	bufferForStatusBar;			// очередь для статус бара
		Keys						activeKey;					// 
		std::vector <std::string>	bufferForMenu;				// буфер меню
		std::vector <TypeArray>		array;
		std::list <TypeArray>		list;

	private:															
		Interface(const Interface&)					= delete;
		Interface(const Interface&&)				= delete;
		Interface& operator = (const Interface&)	= delete;
		Interface& operator = (const Interface&&)	= delete;
		void addToStatusBar(const std::string&& str, bool isFormated = true);
		void generateMenu();					
		void setActiveKey(Keys key);	
		constexpr  std::string delimiter(char del = '=') const;				

	public:
		
		Interface();

		constexpr size_t getMaxTableWidth()			const;					// возврат ширины максимальной длины используемой строки в приложении
		constexpr size_t getMaxTableColumns()		const;					// возврат количества колонок "таблицы", при выводе данных массива и хеш-таблиц
		constexpr size_t getMaxSize()				const;					// возврат количества колонок "таблицы", при выводе данных массива и хеш-таблиц

		constexpr void showHeader();										// выводит заголовок
		constexpr void showMenu();											// выводит меню
		void showStatusBar();												// выводит информацию из статус бара

		Keys getActiveKey()							const;					// возврат текущего кода клавиши

		void readKey();


		///
		/// генерирует строку согласно формату программы с 1 параметром
		///
		constexpr const std::string generatingStrings(const std::string&& str, char del = ' ') const;

		///
		/// генерирует строку согласно формату программы с 2 параметрами
		///
		constexpr const std::string generatingStrings(const std::string&& str, const std::string&& str2, char del = ' ') const;


	};
}


/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
												/* Определение методов */


template <class TypeArray>
WORK::Interface<TypeArray>
::Interface() 
	: out						{	std::cout		}
	, maxTableWidth				{	110				}
	, maxTableColumnsInArray	{	5				}
	, maxSize					{	12				}
	, bufferForStatusBar		{					}
	, activeKey					{ Keys::EmptyKey	}
	, bufferForMenu				{					}
{
	generateMenu();
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::generateMenu()
{
	bufferForMenu.emplace_back(delimiter());
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("Нажмите на клавишу и нажмите ВВОД"));
	bufferForMenu.emplace_back(delimiter('_'));
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("Ответы на решение заданий"));
	bufferForMenu.emplace_back(delimiter('_'));
	bufferForMenu.emplace_back(generatingStrings("( 1 )", "Выполнить вручную сортировку методом прямого выбора", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 2 )", "Выполнить вручную шейкерную сортировку", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 3 )", "Выполнить вручную сортировку методом Шелла", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 4 )", "Построить пирамиду", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 5 )", "метод прямого связывания", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 6 )", "Слияние двух списков", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 7 )", "Выполнить вручную сортировку методом цифровой сортировки", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 8 )", "Выполнить вручную быстрый поиск Буквы А", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 9 )", "Выполнить вручную быстрый поиск Буквы Я", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 0 )", "Выход", '.'));
	bufferForMenu.emplace_back(delimiter());
}


template <class TypeArray>
constexpr void WORK::Interface<TypeArray>
::showMenu()
{
	for (auto&& it : bufferForMenu)
	{
		out << it;
	}
}


template <class TypeArray>
constexpr size_t WORK::Interface<TypeArray>
::getMaxTableWidth() const
{
	return maxTableWidth;
}


template <class TypeArray>
constexpr size_t WORK::Interface<TypeArray>
::getMaxTableColumns() const
{
	return maxTableColumnsInArray;
}


template <class TypeArray>
constexpr size_t WORK::Interface<TypeArray>
::getMaxSize() const
{
	return maxSize;
}


template <class TypeArray>
WORK::Keys WORK::Interface<TypeArray>
::getActiveKey() const
{
	return activeKey;
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::setActiveKey(Keys key)
{
	activeKey = key;
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::addToStatusBar(const std::string&& str, bool isFormated)
{	
	if (!isFormated) {
		bufferForStatusBar.emplace(std::move(str));
		return;
	}
	std::string hr{ delimiter() };
	std::string hr2{ delimiter(' ')};

	bufferForStatusBar.emplace(hr);
	bufferForStatusBar.emplace(hr2);
	bufferForStatusBar.emplace(generatingStrings(std::move(str)));
	bufferForStatusBar.emplace(hr2);
	bufferForStatusBar.emplace(hr);
}


template <class TypeArray>
constexpr void WORK::Interface<TypeArray>
::showHeader()
{
	std::string hr{ delimiter() };

	out << hr;
	out << generatingStrings("Контрольная работа");
	out << delimiter('-');
	out << generatingStrings("Группа ПБ-11", "Хакимов А.C.");
	out << hr;
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::showStatusBar()
{
	std::string hr{ delimiter(' ') };

	out << hr;

	while (!bufferForStatusBar.empty())
	{
		out << bufferForStatusBar.front();
		bufferForStatusBar.pop();
	}

	out << hr;
}


template <class TypeArray>
constexpr std::string WORK::Interface<TypeArray>
::delimiter(char del) const
{
	std::string result(maxTableWidth, del);
	result.at(0) = '#';
	result[result.size() - 2] = '#';
	result.back() = '\n';
	return result;
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string&& inStr, char del) const
{
	if (inStr.empty()) return {};

	std::string str;
	if constexpr (std::is_lvalue_reference_v<std::string>) str = inStr;
	else str = std::move(inStr);

	try {		
		int parity{ str.length() % 2 == 0 };
		size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

		std::string middle(middleSize - parity, del);

		return { "#" + middle + str + (parity ? " " : "") + middle + "#\n" };
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return {};
	}
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string&& inStr, const std::string&& inStr2, char del) const
{
	if (inStr.empty() || inStr2.empty()) return {};

	std::string str;
	std::string str2;
	if constexpr (std::is_lvalue_reference_v<std::string>)
	{
		str = inStr;
		str2 = inStr2;
	}
	else
	{
		str = std::move(inStr);
		str2 = std::move(inStr2);
	}

	try {
		size_t len{ str.length() + str2.length() + 11 };
		size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };
		std::string middle(middleSize, del);

		return { "#    " + str + middle + str2 + "    #\n" };
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return {};
	}
}



template<class TypeArray>
void WORK::Interface<TypeArray>
::readKey()
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