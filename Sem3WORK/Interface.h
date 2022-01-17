#pragma once
#include <string>
#include <queue>
#include <iostream>
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

		void addToStatusBar(const std::string& str, bool isFormated = true);			// добавляет в очередь статус бара, строку для вывода
		void addToStatusBar(const std::string&& str, bool isFormated = true);

		bool flagClearArrayAndHash								{ true };				// флаг пустого массива и, следовательно, хеш-таблиц


	public:
		
		Interface(TypeArray& myTypeArray);

		Interface(TypeArray&& myTypeArray);

		constexpr size_t getMaxTableWidth()			const;					// возврат ширины максимальной длины используемой строки в приложении
		constexpr size_t getMaxTableColumns()		const;					// возврат количества колонок "таблицы", при выводе данных массива и хеш-таблиц
		constexpr bool getFlagClearArrayAndHash()	const;					// флаг пустого массива и хеш-таблиц
		Keys getActiveKey()							const;					// возврат текущего кода клавиши
		void setActiveKey(Keys key);										// задает код клавиши

		void setFlagClearArray(bool flag);									// задает флаг, сигнализирующий очистку

		constexpr void showHeader();										// выводит заголовок
		constexpr void showMenu();											// выводит меню
		void showStatusBar();												// выводит информацию из статцс бара
		void showStatusType();												// выводит информацию о массиве и хеш-таблице

		constexpr  std::string delimiter(char del = '=') const;				// выводит разделитель


		///
		/// генерирует строку согласно формату программы с 1 параметром
		///
		constexpr const std::string generatingStrings(const std::string& str, char del = ' ') const;
		constexpr const std::string generatingStrings(const std::string&& str, char del = ' ') const;

		///
		/// генерирует строку согласно формату программы с 2 параметрами
		///
		constexpr const std::string generatingStrings(const std::string& str, const std::string& str2, char del = ' ') const;
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
::Interface(
	TypeArray& myTypeArray)
	: myTypeArray(myTypeArray) {
	generateMenu();
}


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
	bufferForMenu.emplace_back(generatingStrings("Вывод"));
	bufferForMenu.emplace_back(generatingStrings("( 1 )", "Массива", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 2 )", "Хеш-таблицы (метод прямого связывания)", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 3 )", "хеш-таблицы (метод открытой адрессации, использованы линейные пробы)", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 4 )", "хеш-таблицы (метод открытой адрессации, использованы квадратичные пробы)", '.'));

	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("Поиск в хеш-таблице"));

	bufferForMenu.emplace_back(generatingStrings("( 5 )", "метод прямого связывания", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 6 )", "метод открытой адрессации, использованы линейные пробы", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 7 )", "метод открытой адрессации, использованы квадратичные пробы", '.'));

	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("Прочее"));
	bufferForMenu.emplace_back(generatingStrings("( 8 )", "Обновить массив и хеш-таблицы новыми данными", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 9 )", "Задать новый размер массива и хеш-таблиц", '.'));
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
constexpr bool WORK::Interface<TypeArray>
::getFlagClearArrayAndHash() const 
{
	return flagClearArrayAndHash;
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
::setFlagClearArray(bool flag)
{
	flagClearArrayAndHash = flag;
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::addToStatusBar(const std::string& str, bool isFormated)
{
	return addToStatusBar(std::move(str), isFormated);
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::addToStatusBar(const std::string&& str, bool isFormated)
{	
	if (!isFormated) {
		bufferForStatusBar.emplace(str);
		return;
	}

	bufferForStatusBar.emplace(delimiter());
	bufferForStatusBar.emplace(delimiter(' '));
	bufferForStatusBar.emplace(generatingStrings(str));
	bufferForStatusBar.emplace(delimiter(' '));
	bufferForStatusBar.emplace(delimiter());
}


template <class TypeArray>
constexpr void WORK::Interface<TypeArray>
::showHeader()
{

	std::string header{ generatingStrings("Лабораторная работа № 3", "Изучение возможности хэширования данных для организации поиска. ") };
	std::string header2{ generatingStrings("Группа ПБ-11", "Хакимов А.C.") };

	std::string hr{ delimiter() };

	out << hr;
	out << header;
	out << delimiter('-');
	out << header2;
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
void WORK::Interface<TypeArray>
::showStatusType()
{
	out << generatingStrings("Статус Массива и Хеш-таблицы:", getFlagClearArrayAndHash() ? "ПУСТО" : "ЗАПОЛНЕНЫ");
	out << delimiter('-');
	out << generatingStrings("количество элементов массива:", std::to_string(myTypeArray.getSize()));
	out << delimiter('-');
	//out << generatingStrings("количество элементов хеш-таблицы:", std::to_string(myTypeHashTableDirectBinding.getSize()));
	out << delimiter();
}


template <class TypeArray>
constexpr std::string WORK::Interface<TypeArray>
::delimiter(char del) const
{

	std::string result(maxTableWidth, del);
	result.at(0) = '#';	result[result.size() - 2] = '#'; result.back() = '\n';
	return result;
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string& str, char del) const
{
	return generatingStrings(std::move(str), del);
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string&& str, char del) const
{
	try {
		if (str.empty()) throw std::exception("Dont empty string! -> LAB2::MyList::generatingStrings(const std::string& str)");
		int parity{ str.length() % 2 == 0 };
		size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

		std::string middle(middleSize - parity, del);
		std::string result{ "#" + middle + str + (parity ? " " : "") + middle + "#\n" };

		return result;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return std::string();
	}
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string& str, const std::string& str2, char del) const
{
	return generatingStrings(std::move(str), std::move(str2), std::move(del));
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string&& str, const std::string&& str2, char del) const
{
	try {
		size_t len{ str.length() + str2.length() + 11 };
		size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };

		std::string middle(middleSize, del);
		std::string result{ "#    " + str + middle + str2 + "    #\n" };

		return result;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return std::string();
	}
}