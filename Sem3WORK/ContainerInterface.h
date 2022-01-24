#pragma once

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <iterator>
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
        std::map<TypeSort, std::string>		dataSortName;

    private:	
        
        ContainerInterface(const ContainerInterface&)				= delete;
        ContainerInterface(const ContainerInterface&&)				= delete;
        ContainerInterface& operator = (const ContainerInterface&)	= delete;
        ContainerInterface& operator = (const ContainerInterface&&)	= delete;

        
        void nameToContainer();
        template <typename Iter>
        void printContainer(Iter begin, Iter end, EnableMenuDisplay emd = EnableMenuDisplay::On);

    public:
        
        ContainerInterface();

        void readKey();
        void showSort(TypeSort tSort);

        std::tuple<bool, size_t, size_t> directSelectionSort();
        std::tuple<bool, size_t, size_t> shakerSort();
        std::tuple<bool, size_t, size_t> shellSort();

        void makeHeap();
        template <typename Iter>
        void pushHeap(Iter begin, Iter end);

        void hoareSort();
        void hoare(TypeContainer* data, size_t begin, size_t end);

        void showMerge();
        template <typename Iter>
        std::list<TypeContainer> merge(Iter first, Iter last, Iter first2, Iter last2);
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
    , array							(	this->getMaxSize()			            )
    , dataSortName
    {
        { TypeSort::DirectSelection,	"Сортировка методом ПРЯМОГО ВЫБОРА"		},
        { TypeSort::Shake,				"Метод Шейкерной Сортировки"			},
        { TypeSort::Shell,				"Сортировка методом Шелла"		    	},
        { TypeSort::Heap,				"Построение Пирамиды"    	            },
        { TypeSort::Hoare,				"Сортировка методом Хоара"    	        },
        { TypeSort::Merge,				"Слияние двух списков"    	            },
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
    case Keys::Exit:							exit(0);								            // Выход из цикла	
        break;
    case Keys::DirectSelectionSort:				showSort(TypeSort::DirectSelection);	            // 1
        break;
    case Keys::ShakerSort:						showSort(TypeSort::Shake);				            // 2
        break;
    case Keys::ShellSorting:					showSort(TypeSort::Shell);	                        // 3
        break;
    case Keys::Heap:						    showSort(TypeSort::Heap);                           // 4
        break;
    case Keys::HoareSorting:					showSort(TypeSort::Hoare);  	                    // 5
        break;
    case Keys::Merger:							showMerge();                                    	// 6
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
template <class Iter>
void WORK::ContainerInterface<TypeContainer>
::printContainer(Iter begin, Iter end, EnableMenuDisplay emd)
{
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


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::showSort(TypeSort tSort)
{
    nameToContainer();
    addToStatusBar("Вывод массива перед сортировкой", StringFormat::On);
    printContainer(array.begin(), array.end(), EnableMenuDisplay::Off);
    
    size_t countOfComparisons{};
    size_t countOfShipments{};
    bool isVisibleCounts{};
    switch (tSort) {
    case TypeSort::DirectSelection:		std::tie(isVisibleCounts, countOfComparisons, countOfShipments) = directSelectionSort();	break;
    case TypeSort::Shake:				std::tie(isVisibleCounts, countOfComparisons, countOfShipments) = shakerSort();				break;
    case TypeSort::Shell:				std::tie(isVisibleCounts, countOfComparisons, countOfShipments) = shellSort();				break;
    case TypeSort::Heap:				                                                                  makeHeap();				break;
    case TypeSort::Hoare:				                                                                  hoareSort();				break;
    default:
        addToStatusBar("Метод сортировки не выбран!", StringFormat::On);
        return;
    }

    addToStatusBar(delimiter());
    addToStatusBar("Вывод массива после сортировки", StringFormat::On);
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings(dataSortName.at(tSort)));
    addToStatusBar(delimiter('-'));
    printContainer(array.begin(), array.end(), EnableMenuDisplay::Off);

    if (isVisibleCounts)
    {
        addToStatusBar(delimiter('-'));
        addToStatusBar(generatingStrings("Количество сравнений", std::to_string(countOfComparisons)));
        addToStatusBar(delimiter('-'));
        addToStatusBar(generatingStrings("Количество перестановок", std::to_string(countOfShipments)));
        addToStatusBar(delimiter('-'));
    }    
}


template <class TypeContainer>
std::tuple<bool, size_t, size_t> WORK::ContainerInterface<TypeContainer>
::directSelectionSort()
{

    auto begin{ array.begin() };
    auto end{ array.end() };
    using Iter = decltype(array)::iterator;

    size_t countOfComparisons{};
    size_t countOfShipments{};
    Iter min;
    for (auto it{ begin }, ite{ end }; it != ite; ++it) {
        min = it;
        countOfShipments += 3;
        for (auto it_j{ std::next(it) }, ite_j{ end }; it_j != ite_j; ++it_j) {
            ++countOfComparisons;
            if (*it_j < *min) min = it_j;			
        }
        std::iter_swap(it, min);
    }
    return { true, countOfComparisons, countOfShipments };
}


template <class TypeContainer>
std::tuple<bool, size_t, size_t> WORK::ContainerInterface<TypeContainer>
::shakerSort()
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
        
    return { true, countOfComparisons, countOfShipments };
}


template<class TypeContainer>
std::tuple<bool, size_t, size_t> WORK::ContainerInterface<TypeContainer>
::shellSort()
{
    
    size_t countOfComparisons{};
    size_t countOfShipments{};

    for (size_t step{ array.size() >> 1}; step; step >>= 1)
    {
        for (size_t i{ step }, j{}; i < array.size(); ++i)
        {
            TypeContainer* tmp{ &array[i] };
            for (j = i; j >= step; j -= step)
            {
                ++countOfComparisons;
                if (*tmp < array[j - step]) array[j] = array[j - step];                
                else break;
            }
            array[j] = *tmp;
            ++countOfShipments;
        }
    }
    
    return { true, countOfComparisons , countOfShipments  };

}


template<class TypeContainer>
template<class Iter>
void WORK::ContainerInterface<TypeContainer>
::pushHeap(Iter begin, Iter end)
{
    auto child{ (end - 1) - begin };
    while (child != 0)
    {
        auto parent{ (child - 1) / 2 };
        if (begin[child] < begin[parent]) return;
        std::iter_swap(begin+child, begin+parent);
        child = parent;
    }
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::makeHeap()
{
    auto begin{ array.begin() };
    auto end{ array.end() };
    
    for (auto it{ begin }; it != end; )
    {
        pushHeap(begin, ++it);
    }   
}


template<typename TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::hoare(TypeContainer* data, size_t begin, size_t end)
{
   
    if (data == nullptr)
    {
        addToStatusBar(generatingStrings("In void WORK::ContainerInterface<TypeContainer>"));
        addToStatusBar(generatingStrings("::hoare(TypeContainer * data, size_t begin, size_t end)"));        
        addToStatusBar(generatingStrings("data == nullptr"));
        return;
    }

    auto i{ begin }, j{ end };
    int x{ data[(begin + end) / 2] };

    while (i <= j)
    {        
        while (data[i] < x) ++i;
        while (data[j] > x) --j;  
        if (i <= j) {
            if (i < j)  std::swap(data[i], data[j]);            
            ++i;
            --j;
        }
    }
    if (i < end) hoare(data, i, end);
    if (begin < j) hoare(data, begin, j);
}


template<typename TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::hoareSort()
{
    hoare(array.data(), 0, array.size() - 1);
}


template<typename TypeContainer>
template<typename Iter>
std::list<TypeContainer> WORK::ContainerInterface<TypeContainer>
::merge(Iter first, Iter last, Iter first2, Iter last2 )
{
    std::list<TypeContainer> result;
    auto it_r{ std::back_inserter(result) };

    for (; first != last; ++it_r) {
        if (first2 == last2) {
            std::copy(first, last, it_r);
            return result;
        }
        if (*first2 < *first) {
            *it_r = *first2;
            ++first2;
        }
        else {
            *it_r = *first;
            ++first;
        }
    }
    std::copy(first2, last2, it_r);
    return result;
}


template<typename TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::showMerge()
{
    std::list<TypeContainer> lastName;
    std::list<TypeContainer> name;
    std::string patternLastName{ "хакимов" };
    std::string patternName{ "андрей" };
    std::transform(patternLastName.begin(), patternLastName.end(), std::back_inserter(lastName), [](char c) -> TypeContainer {
        return c - 'а';
        });
    std::transform(patternName.begin(), patternName.end(), std::back_inserter(name), [](char c) -> TypeContainer {
        return c - 'а';
        });


    std::list<TypeContainer> lst{ merge(lastName.begin(), lastName.end(), name.begin(), name.end()) };
    addToStatusBar(dataSortName.at(TypeSort::Merge), StringFormat::On);
    addToStatusBar(generatingStrings("первый список", "\"" + patternLastName + "\""));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("второй список", "\"" + patternName + "\""));

    printContainer(lst.begin(), lst.end());
}