#pragma once

#include <map>
#include <functional>
#include "CommonInterface.h"
#include "enums.h"

namespace WORK {

	template <class TypeContainer>
	class ContainerInterface : public CommonInterface<TypeContainer>
	{
		using CommonInterface<TypeContainer>::addToStatusBar;
		using CommonInterface<TypeContainer>::generatingStrings;
		using CommonInterface<TypeContainer>::delimiter;

		std::vector <TypeContainer>			array;
		std::map<TypeSort, std::string> dataSortName;

	private:	
		
		ContainerInterface(const ContainerInterface&)				= delete;
		ContainerInterface(const ContainerInterface&&)				= delete;
		ContainerInterface& operator = (const ContainerInterface&)	= delete;
		ContainerInterface& operator = (const ContainerInterface&&)	= delete;

		
		void nameToContainer();
		void printContainer(EnableMenuDisplay emd = EnableMenuDisplay::On);

		void test();

	public:
		
		ContainerInterface();

		

		void readKey();


		///
		/// ���������� ������ �������� ������� ��������� � 1 ����������
		///
		

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



template <class TypeContainer>
WORK::ContainerInterface<TypeContainer>
::ContainerInterface()
	: CommonInterface<TypeContainer>()
	, array							(	this->getMaxSize()			)
	, dataSortName					{
										{ TypeSort::DirectSelection, "���������� ������� ������� ������" },
										{ TypeSort::Shake, "����� ��������� ����������" },
									} {}


template <class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::nameToContainer()
{
	auto begin	{	array.begin()	};
	auto end	{	array.end()		};

	srand(static_cast<TypeContainer>(time(0)));

	std::string name{"�������������������������"};
	
	std::generate(begin, end, [&name]() {
		
		int item{ name[rand() % name.length()] - '�' };
		if (item > 32) item -= 32;
		return item;
		});
}


template <class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::printContainer(EnableMenuDisplay emd)
{

	auto begin{ array.begin() };
	auto end{ array.end() };

	if (emd == EnableMenuDisplay::On)	addToStatusBar("����� ����������", StringFormat::On);

	std::string result{};
	auto lengthColumn{ (this->getMaxTableWidth() - 10) / this->getMaxTableColumns() };

	for (auto it{ begin }, ite{ end }; it != ite; ++it) {

		std::string tmp(lengthColumn, ' ');
		std::string num{ std::to_string(*it) };

		size_t len{ static_cast<size_t>(std::distance(begin, it)) };
		if ((len + 1) % this->getMaxTableColumns() != 0 && it != std::prev(ite)) {
			tmp.replace(tmp.size() - 1, 1, "|");
		}
		tmp.replace((tmp.length() - num.length()) / 2, num.length(), num);
		result += tmp;

		if ((len + 1) % this->getMaxTableColumns() == 0) {
			addToStatusBar(generatingStrings(result));
			addToStatusBar(delimiter('-'));
			result.clear();
		}
	}

	if (!result.empty()) addToStatusBar(generatingStrings(" ", result));

}



template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
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


template <class TypeContainer>
std::tuple<size_t, size_t> WORK::ContainerInterface<TypeContainer>
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


template <class TypeContainer>
std::tuple<size_t, size_t> WORK::ContainerInterface<TypeContainer>
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


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
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





template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::test()
{
	nameToContainer(array.begin(), array.end());
	printContainer(array.begin(), array.end());
	
}