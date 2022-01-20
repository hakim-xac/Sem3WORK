#pragma once
#include <string>
#include <queue>
#include <iostream>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include "enums.h"

namespace WORK {
	/// <summary>
	/// ��������� ���������
	/// </summary>
	/// <typeparam name="TypeArray">��� �������, ������������� ��� �������� ��������� �����</typeparam>
	/// <typeparam name="TypeHashDirectBinding">��� �������, ������������� ��� �������� ����� � ��������
	///  ���-������� ��������� ����� ������� ����������</typeparam>
	/// <typeparam name="TypeHashOpenAdressing">��� �������, ������������� ��� �������� ����� � ��������
	///  ���-������� ��������� ����� �������� ����������</typeparam>
	template <class TypeArray>
	class CommonInterface
	{
		std::ostream&					out;						// ����� ������
		size_t							maxTableWidth;				// ������ ��������� ������
		int								maxTableColumnsInArray;		// ���������� ������� ��� ������ �������
		const size_t					maxSize;
		std::queue <std::string>		bufferForStatusBar;			// ������� ��� ������ ����
		Keys							activeKey;					// 
		std::vector <std::string>		bufferForMenu;				// ����� ����
		std::vector <TypeArray>			array;
		std::map<TypeSort, std::string> dataSortName;

	private:															
		CommonInterface(const CommonInterface&)					= delete;
		CommonInterface(const CommonInterface&&)				= delete;
		CommonInterface& operator = (const CommonInterface&)	= delete;
		CommonInterface& operator = (const CommonInterface&&)	= delete;

		void addToStatusBar(const std::string& str, StringFormat format = StringFormat::Off);
		void addToStatusBar(const std::string&& str, StringFormat format = StringFormat::Off);
		void generateMenu();					
		void setActiveKey(Keys key);	
		constexpr  std::string delimiter(char del = '=') const;		

		void nameToContainer();
		void printContainer(EnableMenuDisplay emd = EnableMenuDisplay::On);

		void test();

	public:
		
		CommonInterface();

		constexpr size_t getMaxTableWidth()			const;					// ������� ������ ������������ ����� ������������ ������ � ����������
		constexpr size_t getMaxTableColumns()		const;					// ������� ���������� ������� "�������", ��� ������ ������ ������� � ���-������
		constexpr size_t getMaxSize()				const;					// ������� ���������� ������� "�������", ��� ������ ������ ������� � ���-������

		constexpr void showHeader();										// ������� ���������
		constexpr void showMenu();											// ������� ����
		void showStatusBar();												// ������� ���������� �� ������ ����

		Keys getActiveKey()							const;					// ������� �������� ���� �������

		void readKey();


		///
		/// ���������� ������ �������� ������� ��������� � 1 ����������
		///
		constexpr const std::string generatingStrings(const std::string& str, char del = ' ') const;
		constexpr const std::string generatingStrings(const std::string&& str, char del = ' ') const;

		///
		/// ���������� ������ �������� ������� ��������� � 2 �����������
		///
		constexpr const std::string generatingStrings(const std::string& str, const std::string& str2, char del = ' ') const;
		constexpr const std::string generatingStrings(const std::string&& str, const std::string&& str2, char del = ' ') const;

		/////////////////////

		std::tuple<size_t, size_t> DirectSelectionSort();
		std::tuple<size_t, size_t> ShakerSort();

		void showSort(TypeSort tSort);
	};
}


/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
												/* ����������� ������� */



template <class TypeArray>
WORK::CommonInterface<TypeArray>
::CommonInterface()
	: out							{	std::cout		}
	, maxTableWidth					{	110				}
	, maxTableColumnsInArray		{	5				}
	, maxSize						{	12				}
	, bufferForStatusBar			{					}
	, activeKey						{	Keys::EmptyKey	}
	, bufferForMenu					{					}
	, array							(	maxSize			)
	, dataSortName					{
										{ TypeSort::DirectSelection, "���������� ������� ������� ������" },
										{ TypeSort::Shake, "����� ��������� ����������" },
									}
{
	generateMenu();
}


template <class TypeArray>
void WORK::CommonInterface<TypeArray>
::nameToContainer()
{
	auto begin	{	array.begin()	};
	auto end	{	array.end()		};

	srand(static_cast<TypeArray>(time(0)));

	std::string name{"�������������������������"};
	
	std::generate(begin, end, [&name]() {
		
		int item{ name[rand() % name.length()] - '�' };
		if (item > 32) item -= 32;
		return item;
		});
}


template <class TypeArray>
void WORK::CommonInterface<TypeArray>
::generateMenu()
{
	bufferForMenu.emplace_back(delimiter());
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("������� �� ������� � ������� ����"));
	bufferForMenu.emplace_back(delimiter('_'));
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("������ �� ������� �������"));
	bufferForMenu.emplace_back(delimiter('_'));
	bufferForMenu.emplace_back(generatingStrings("( 1 )", "��������� ������� ���������� ������� ������� ������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 2 )", "��������� ������� ��������� ����������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 3 )", "��������� ������� ���������� ������� �����", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 4 )", "��������� ��������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 5 )", "����� ������� ����������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 6 )", "������� ���� �������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 7 )", "��������� ������� ���������� ������� �������� ����������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 8 )", "��������� ������� ������� ����� ����� �", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 9 )", "��������� ������� ������� ����� ����� �", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 0 )", "�����", '.'));
	bufferForMenu.emplace_back(delimiter());
}


template <class TypeArray>
constexpr void WORK::CommonInterface<TypeArray>
::showMenu()
{
	for (auto&& it : bufferForMenu)
	{
		out << it;
	}
}


template <class TypeArray>
constexpr size_t WORK::CommonInterface<TypeArray>
::getMaxTableWidth() const
{
	return maxTableWidth;
}


template <class TypeArray>
constexpr size_t WORK::CommonInterface<TypeArray>
::getMaxTableColumns() const
{
	return maxTableColumnsInArray;
}


template <class TypeArray>
constexpr size_t WORK::CommonInterface<TypeArray>
::getMaxSize() const
{
	return maxSize;
}


template <class TypeArray>
WORK::Keys WORK::CommonInterface<TypeArray>
::getActiveKey() const
{
	return activeKey;
}


template <class TypeArray>
void WORK::CommonInterface<TypeArray>
::setActiveKey(Keys key)
{
	activeKey = key;
}


template <class TypeArray>
void WORK::CommonInterface<TypeArray>
::addToStatusBar(const std::string& str, StringFormat format)
{
	addToStatusBar(std::move(str), format);
}

template <class TypeArray>
void WORK::CommonInterface<TypeArray>
::addToStatusBar(const std::string&& str, StringFormat format)
{	
	if (format == StringFormat::Off) {
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
constexpr void WORK::CommonInterface<TypeArray>
::showHeader()
{
	std::string hr{ delimiter() };

	out << hr;
	out << generatingStrings("����������� ������");
	out << delimiter('-');
	out << generatingStrings("������ ��-11", "������� �.C.");
	out << hr;
}


template <class TypeArray>
void WORK::CommonInterface<TypeArray>
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
constexpr std::string WORK::CommonInterface<TypeArray>
::delimiter(char del) const
{
	std::string result(maxTableWidth, del);
	result.at(0) = '#';
	result[result.size() - 2] = '#';
	result.back() = '\n';
	return result;
}


template <class TypeArray>
constexpr const std::string WORK::CommonInterface<TypeArray>
::generatingStrings(const std::string& inStr, char del) const
{
	return generatingStrings(std::move(inStr), del);
}


template <class TypeArray>
constexpr const std::string WORK::CommonInterface<TypeArray>
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
constexpr const std::string WORK::CommonInterface<TypeArray>
::generatingStrings(const std::string& inStr, const std::string& inStr2, char del) const
{
	return generatingStrings(std::move(inStr), std::move(inStr2), del);
}


template <class TypeArray>
constexpr const std::string WORK::CommonInterface<TypeArray>
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


template <class TypeArray>
void WORK::CommonInterface<TypeArray>
::printContainer(EnableMenuDisplay emd)
{

	auto begin{ array.begin() };
	auto end{ array.end() };

	if (emd == EnableMenuDisplay::On)	addToStatusBar("����� ����������", StringFormat::On);

	std::string result{};
	auto lengthColumn{ (getMaxTableWidth() - 10) / getMaxTableColumns() };

	for (auto it{ begin }, ite{ end }; it != ite; ++it) {

		std::string tmp(lengthColumn, ' ');
		std::string num{ std::to_string(*it) };

		size_t len{ static_cast<size_t>(std::distance(begin, it)) };
		if ((len + 1) % getMaxTableColumns() != 0 && it != std::prev(ite)) {
			tmp.replace(tmp.size() - 1, 1, "|");
		}
		tmp.replace((tmp.length() - num.length()) / 2, num.length(), num);
		result += tmp;

		if ((len + 1) % getMaxTableColumns() == 0) {
			addToStatusBar(generatingStrings(result));
			addToStatusBar(delimiter('-'));
			result.clear();
		}
	}

	if (!result.empty()) addToStatusBar(generatingStrings(" ", result));

}



template<class TypeArray>
void WORK::CommonInterface<TypeArray>
::readKey()
{

	if (this->getActiveKey() == Keys::EmptyKey)
	{
		this->setActiveKey(static_cast<Keys>(std::cin.get()));	// ��������� ���� ������
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ��������� �����
	}
	switch (this->getActiveKey())
	{
	case Keys::Exit:                                    // 0
		exit(0);                                        // ����� �� �����
		break;
	case Keys::DirectSelectionSort:                     // 1
		showSort(TypeSort::DirectSelection);
		break;
	case Keys::ShakerSort:								// 2
		showSort(TypeSort::Shake);
		break;
	case Keys::ShellSorting:							// 3
		showSort(TypeSort::DirectSelection);
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
		this->addToStatusBar("������� �� ������ �������!", StringFormat::On);            // ����� ������� ������������� � ������������ Keys
		break;
	}
	this->setActiveKey(Keys::EmptyKey);
}


template <class TypeArray>
std::tuple<size_t, size_t> WORK::CommonInterface<TypeArray>
::DirectSelectionSort()
{

	auto begin{ array.begin() };
	auto end{ array.end() };
	using Iter = decltype(array)::iterator;

	size_t countOfComparisons{};
	size_t countOfShipments{};
	Iter min;
	for (auto it{ begin }, ite{ end }; it != ite; ++it) {
		min = it;
		++countOfShipments;
		for (auto it_j{ std::next(it) }, ite_j{ end }; it_j != ite_j; ++it_j) {
			++countOfComparisons;
			if (*it_j < *min) min = it_j;			
		}
		std::iter_swap(it, min);
	}
	countOfShipments *= 3;
	return { countOfComparisons, countOfShipments };
}


template <class TypeArray>
std::tuple<size_t, size_t> WORK::CommonInterface<TypeArray>
::ShakerSort()
{
	auto begin{ array.begin() };
	auto end{ array.end() };
	using Iter = decltype(array)::iterator;

	size_t countOfComparisons{};
	size_t countOfShipments{};

	Iter left				{ begin };
	Iter right				{ end };

	while (left != right)
	{
		for (auto it{ std::prev(right) }, ite{ left }; it != ite; --it)
		{
			++countOfComparisons;
			if (*std::prev(it) > *it) {
				std::iter_swap(std::prev(it), it);
				++countOfShipments;
			}
		}
		++left;
		for (auto it{ left }; it != right; ++it)
		{
			++countOfComparisons;
			if (*std::prev(it) > *it)
			{
				std::iter_swap(std::prev(it), it);
				++countOfShipments;
			}
		}
		--right;
	}
		
	return { countOfComparisons, countOfShipments };
}


template<class TypeArray>
void WORK::CommonInterface<TypeArray>
::showSort(TypeSort tSort)
{
	nameToContainer();
	addToStatusBar("����� ������� ����� �����������", StringFormat::On);
	printContainer(EnableMenuDisplay::Off);

	size_t countOfComparisons{};
	size_t countOfShipments{};

	switch(tSort) {
	case TypeSort::DirectSelection:		std::tie(countOfComparisons, countOfShipments) = DirectSelectionSort();		break;
	case TypeSort::Shake:				std::tie(countOfComparisons, countOfShipments) = ShakerSort();				break;
	default: 
		addToStatusBar("����� ���������� �� ������!", StringFormat::On);
		return;
	}

	addToStatusBar(delimiter());
	addToStatusBar("����� ������� ����� ����������", StringFormat::On);
	addToStatusBar(delimiter('-'));
	addToStatusBar(generatingStrings(dataSortName.at(tSort)));
	addToStatusBar(delimiter('-'));
	printContainer(EnableMenuDisplay::Off);

	addToStatusBar(delimiter('-'));
	addToStatusBar(generatingStrings("���������� ���������", std::to_string(countOfComparisons)));
	addToStatusBar(delimiter('-'));
	addToStatusBar(generatingStrings("���������� ������������", std::to_string(countOfShipments)));
	addToStatusBar(delimiter('-'));

}





template<class TypeArray>
void WORK::CommonInterface<TypeArray>
::test()
{
	nameToContainer(array.begin(), array.end());
	printContainer(array.begin(), array.end());
	
}