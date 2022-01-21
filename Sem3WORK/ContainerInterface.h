#pragma once

#include <map>
#include "CommonInterface.h"
#include "enums.h"

namespace WORK {

	template <class TypeContainer>
	class ContainerInterface : public CommonInterface<TypeContainer>
	{
		using CommonInterface<TypeContainer>::setActiveKey;
		using CommonInterface<TypeContainer>::getActiveKey;
		using CommonInterface<TypeContainer>::addToStatusBar;
		using CommonInterface<TypeContainer>::generatingStrings;
		using CommonInterface<TypeContainer>::delimiter;
		using CommonInterface<TypeContainer>::printErrorKey;

		std::vector <TypeContainer>			array;
		std::map<TypeSort, std::string> dataSortName;

	private:	
		
		ContainerInterface(const ContainerInterface&)				= delete;
		ContainerInterface(const ContainerInterface&&)				= delete;
		ContainerInterface& operator = (const ContainerInterface&)	= delete;
		ContainerInterface& operator = (const ContainerInterface&&)	= delete;

		
		void nameToContainer();
		void printContainer(EnableMenuDisplay emd = EnableMenuDisplay::On);

	public:
		
		ContainerInterface();

		void readKey();

		std::pair<size_t, size_t> DirectSelectionSort();
		std::pair<size_t, size_t> ShakerSort();

		void showSort(TypeSort tSort);
	};
}


/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
												/* Определение методов */



template <class TypeContainer>
WORK::ContainerInterface<TypeContainer>
::ContainerInterface()
	: CommonInterface<TypeContainer>()
	, array							(	this->getMaxSize()			)
	, dataSortName
	{
		{ TypeSort::DirectSelection,	"Сортировка методом ПРЯМОГО ВЫБОРА"		},
		{ TypeSort::Shake,				"Метод Шейкерной Сортировки"			},
	} {}



template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::readKey()
{

	if (getActiveKey() == Keys::EmptyKey)
	{
		setActiveKey(static_cast<Keys>(std::cin.get()));	// Принимаем один символ
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем остальной буфер
	}
	switch (this->getActiveKey())
	{
	case Keys::Exit:							exit(0);								// Выход из цикла	
		break;
	case Keys::DirectSelectionSort:				showSort(TypeSort::DirectSelection);	// 1
		break;
	case Keys::ShakerSort:						showSort(TypeSort::Shake);				// 2
		break;
	case Keys::ShellSorting:					showSort(TypeSort::DirectSelection);	// 3
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
		printErrorKey();								// любая клавиша отсутствующая в перечислении Keys
		break;
	}
	setActiveKey(Keys::EmptyKey);
}


template <class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::nameToContainer()
{
	auto begin	{	array.begin()	};
	auto end	{	array.end()		};

	srand(static_cast<TypeContainer>(time(0)));

	std::string name{"ХакимовАндрейСамигуллович"};
	
	std::generate(begin, end, [&name]() {
		
		int item{ name[rand() % name.length()] - 'А' };
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

	if (emd == EnableMenuDisplay::On)	addToStatusBar("Вывод контейнера", StringFormat::On);

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


template <class TypeContainer>
std::pair<size_t, size_t> WORK::ContainerInterface<TypeContainer>
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
std::pair<size_t, size_t> WORK::ContainerInterface<TypeContainer>
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
	addToStatusBar("Вывод массива перед сортировкой", StringFormat::On);
	printContainer(EnableMenuDisplay::Off);

	size_t countOfComparisons{};
	size_t countOfShipments{};

	switch(tSort) {
	case TypeSort::DirectSelection:		std::tie(countOfComparisons, countOfShipments) = DirectSelectionSort();		break;
	case TypeSort::Shake:				std::tie(countOfComparisons, countOfShipments) = ShakerSort();				break;
	default: 
		addToStatusBar("Метод сортировки не выбран!", StringFormat::On);
		return;
	}

	addToStatusBar(delimiter());
	addToStatusBar("Вывод массива после сортировки", StringFormat::On);
	addToStatusBar(delimiter('-'));
	addToStatusBar(generatingStrings(dataSortName.at(tSort)));
	addToStatusBar(delimiter('-'));
	printContainer(EnableMenuDisplay::Off);

	addToStatusBar(delimiter('-'));
	addToStatusBar(generatingStrings("Количество сравнений", std::to_string(countOfComparisons)));
	addToStatusBar(delimiter('-'));
	addToStatusBar(generatingStrings("Количество перестановок", std::to_string(countOfShipments)));
	addToStatusBar(delimiter('-'));

}



