#pragma once
#include <string>
#include <queue>
#include <iostream>
#include <type_traits>
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
		std::ostream& out										{ std::cout };			// буфер вывода
		size_t maxTableWidth									{ 110 };				// ширина выводимой строки
		int maxTableColumnsInArray								{ 5 };					// количество колонов при выводе массива
		std::queue <std::string> bufferForStatusBar				{};						// очередь для статус бара
		Keys activeKey											{ Keys::EmptyKey };		// 
		std::vector <std::string> bufferForMenu{};										// буфер меню


	private:
		Interface() = delete;															// запрещаем создавать пустой класс

		void generateMenu();															// генеригует меню
	protected:


		TypeArray myTypeArray;
			
		void addToStatusBar(const std::string&& str, bool isFormated = true);			// добавляет в очередь статус бара, строку для вывода

		bool flagClearArrayAndHash								{ true };				// флаг пустого массива и, следовательно, хеш-таблиц


	public:
		
		Interface(TypeArray&& myTypeArray);

		constexpr size_t getMaxTableWidth()			const;					// возврат ширины максимальной длины используемой строки в приложении
		constexpr size_t getMaxTableColumns()		const;					// возврат количества колонок "таблицы", при выводе данных массива и хеш-таблиц

		Keys getActiveKey()							const;					// возврат текущего кода клавиши
		void setActiveKey(Keys key);										// задает код клавиши

		constexpr void showHeader();										// выводит заголовок
		constexpr void showMenu();											// выводит меню
		void showStatusBar();												// выводит информацию из статус бара

		constexpr  std::string delimiter(char del = '=') const;				// возврат разделителя


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
::Interface(TypeArray&& myTypeArray) : myTypeArray(myTypeArray) {
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