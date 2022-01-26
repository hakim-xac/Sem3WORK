#pragma once

#include <vector>
#include <list>
#include <tuple>
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
        using CommonInterface<TypeContainer>::getMaxSize;
        std::string                           defaultString;
        std::vector<TypeContainer>            array;

    private:	
        
        ContainerInterface(const ContainerInterface&)				= delete;
        ContainerInterface(const ContainerInterface&&)				= delete;
        ContainerInterface& operator = (const ContainerInterface&)	= delete;
        ContainerInterface& operator = (const ContainerInterface&&)	= delete;
        
        std::vector<TypeContainer> nameToContainer();
        template <typename Iter>
        void printContainer(Iter begin, Iter end, EnableMenuDisplay emd = EnableMenuDisplay::On);
        std::string getDefaultString();
    public:
        
        ContainerInterface();

        void readKey();
        void showSort(TypeSort tSort);

        template <typename Iter>
        std::tuple<bool, size_t, size_t, std::string> selectAction(Iter begin, Iter end, TypeSort tSort);

        template <typename Iter>
        std::tuple<bool, size_t, size_t, std::string> directSelectionSort(Iter begin, Iter end);
        template <typename Iter>
        std::tuple<bool, size_t, size_t, std::string> shakerSort(Iter begin, Iter end);
        template <typename Iter>
        std::tuple<bool, size_t, size_t, std::string> shellSort(Iter begin, Iter end);

        template <typename Iter>
        std::string makeHeap(Iter begin, Iter end);
        template <typename Iter>
        void pushHeap(Iter begin, Iter end);

        template <typename Iter>
        std::string hoareSort(Iter begin, Iter end);
        void hoare(TypeContainer* data, size_t begin, size_t end);

        void showMerge();
        template <typename Iter>
        std::list<TypeContainer> merge(Iter first, Iter last, Iter first2, Iter last2);


        void arrayEncodeToTernarySystem();
        void arrayDecodeToTernarySystem();
        void digitalSort();
        template <typename Iter>
        void initDigitalSort(Iter begin, Iter end);
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
    , defaultString("ХАКИМОВАНДРЕ")
    , array(getMaxSize()) {
    std::copy(defaultString.begin(), defaultString.end(), std::back_inserter(array));
}


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
    case Keys::Merger:							showMerge();                                        // 6
        break;
    case Keys::DigitalSorting:					showSort(TypeSort::Digital);                        // 7
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
std::string WORK::ContainerInterface<TypeContainer>
::getDefaultString()
{
    return defaultString;
}


    template <class TypeContainer>
    std::vector<TypeContainer> WORK::ContainerInterface<TypeContainer>
        ::nameToContainer()
    {
    std::vector<TypeContainer> result(getMaxSize());
    auto begin	{ result.begin()	};
    auto end	{ result.end()		};
    const std::string name{ defaultString };
    size_t count{};
    std::generate(begin, end, [&name, &count]() {
        int item{};
        item = name[count++] - 'А';        
        if (item > 32) item -= 32;
        return ++item;
        });
    return result;
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
template<class Iter>
std::tuple<bool, size_t, size_t, std::string> WORK::ContainerInterface<TypeContainer>
::selectAction(Iter begin, Iter end, TypeSort tSort)
{

    size_t countOfComparisons{};
    size_t countOfShipments{};
    bool isVisibleCounts{};
    std::string stringResult{};
    switch (tSort) {
    case TypeSort::DirectSelection:		std::tie(isVisibleCounts, countOfComparisons, countOfShipments, stringResult) = directSelectionSort(begin, end);	break;
    case TypeSort::Shake:				std::tie(isVisibleCounts, countOfComparisons, countOfShipments, stringResult) = shakerSort(begin, end);				break;
    case TypeSort::Shell:				std::tie(isVisibleCounts, countOfComparisons, countOfShipments, stringResult) = shellSort(begin, end);				break;
    case TypeSort::Heap:				                                                                 stringResult = makeHeap(begin, end);				break;
    case TypeSort::Hoare:				                                                                 stringResult = hoareSort(begin, end);				break;
    case TypeSort::Digital:				                                                                  initDigitalSort(begin, end);		break;
    default:
        addToStatusBar("Метод сортировки не выбран!", StringFormat::On);
    }
    return { isVisibleCounts, countOfComparisons, countOfShipments, std::move(stringResult) };
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::showSort(TypeSort tSort)
{
    std::string str{ getDefaultString() };
    auto [isVisibleCounts, countOfComparisons, countOfShipments, headerSort] = selectAction(str.begin(), str.end(), tSort);

    addToStatusBar(headerSort, StringFormat::On);
    addToStatusBar(delimiter('-'));
    addToStatusBar(delimiter(' '));
    addToStatusBar(generatingStrings("Строка до операции", getDefaultString()));
    addToStatusBar(delimiter(' '));
    addToStatusBar(delimiter('-'));
    addToStatusBar(delimiter(' '));

    addToStatusBar(generatingStrings("Строка после операции", str));
    addToStatusBar(delimiter(' '));
    addToStatusBar(delimiter('-'));
  
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
template <class Iter>
std::tuple<bool, size_t, size_t, std::string> WORK::ContainerInterface<TypeContainer>
::directSelectionSort(Iter begin, Iter end)
{

    size_t countOfComparisons{};
    size_t countOfShipments{};
    Iter min{ begin  };
    for (auto it{ begin }, ite{ end }; it != ite; ++it) {
        min = it;
        countOfShipments += 3;
        for (auto it_j{ std::next(it) }, ite_j{ end }; it_j != ite_j; ++it_j) {
            ++countOfComparisons;
            if (*it_j < *min) min = it_j;			
        }
        std::iter_swap(it, min);
    }
    std::move(begin, end, begin);
    return { true, countOfComparisons, countOfShipments, {"Сортировка методом Прямого выбора"} };
}


template <class TypeContainer>
template <class Iter>
std::tuple<bool, size_t, size_t, std::string> WORK::ContainerInterface<TypeContainer>
::shakerSort(Iter begin, Iter end)
{

    size_t countOfComparisons   {       };
    size_t countOfShipments     {       };

    Iter left				    { begin };
    Iter right				    { end   };

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
        
    return { true, countOfComparisons, countOfShipments, {"Шейкерная сортировка"} };
}


template<class TypeContainer>
template<class Iter>
std::tuple<bool, size_t, size_t, std::string> WORK::ContainerInterface<TypeContainer>
::shellSort(Iter begin, Iter end)                                                   //////////////////////////////                
{
    printContainer(array.begin(), array.end());
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
    
    return { true, countOfComparisons , countOfShipments, {"Сортировка методом Шелла"} };

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
template<class Iter>
std::string WORK::ContainerInterface<TypeContainer>
::makeHeap(Iter begin, Iter end)
{    
    for (auto it{ begin }; it != end; )
    {
        pushHeap(begin, ++it);
    }   
    return "Построить пирамиду";
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
template<typename Iter>
std::string WORK::ContainerInterface<TypeContainer>
::hoareSort(Iter begin, Iter end)
{
    auto length{ std::distance(begin, end) };
    hoare(&*begin, 0, length);   
    return "Сортировка методом Хоара";
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
    std::string lastName{"хакимов"};
    std::string name{"андрей"};


    std::list<TypeContainer> lst{ merge(lastName.begin(), lastName.end(), name.begin(), name.end()) };

    std::string result;
    std::copy(lst.begin(), lst.end(), std::back_inserter(result));
    addToStatusBar("Сортировка слиянием", StringFormat::On);
    addToStatusBar(generatingStrings("первый список", "\"" + lastName + "\""));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("второй список", "\"" + name + "\""));

    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("результатирующий список", "\"" + result + "\""));



}


template<class TypeContainer>
inline void WORK::ContainerInterface<TypeContainer>
::arrayEncodeToTernarySystem()
{
    auto array{ nameToContainer() };
    std::vector<TypeContainer> buf;
    for (auto&& it : array)
    {
        TypeContainer tmp{};
        for (auto pow{ 1 }; it; pow *= 10, it /= 3)
        {
            tmp += (it % 3) * pow;
        }
        buf.emplace_back(tmp);
    }
    array.clear();
    std::move(buf.begin(), buf.end(), std::back_inserter(array));
}


template<class TypeContainer>
inline void WORK::ContainerInterface<TypeContainer>
::arrayDecodeToTernarySystem()
{
    auto array{ nameToContainer() };
    std::vector<TypeContainer> buf;
    for (auto&& it : array)
    {
        TypeContainer tmp{};
        for (auto pow{ 1 }; it; pow *= 3, it /= 10)
        {
            tmp += (it % 10) * pow;
        }
        buf.emplace_back(tmp);
    }
    array.clear();
    std::move(buf.begin(), buf.end(), std::back_inserter(array));
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::digitalSort()
{
    auto array{ nameToContainer() };
    std::vector<std::list<TypeContainer>> base(3);    

    for (auto maxElem{ *std::max_element(array.begin(), array.end()) }; maxElem; maxElem /= 10)
    {
        for (int i{}, step{ 1 }; i < base.size(); ++i, step *= 10)
        {
            for (auto&& it : array)
            {
                auto tmp_it{ it };
                tmp_it /= step;
                auto n{ tmp_it % 10 };
                if (n > 2)
                {
                    addToStatusBar("Формат массива не задан!", StringFormat::On);
                    addToStatusBar("Числа должны быть в троичной системе счисления!", StringFormat::On);
                    array.clear();
                    return;
                }
                base.at(n).push_back(it);
            }
            array.clear();
            std::move(base.at(0).begin(), base.at(0).end(), std::back_inserter(array));
            std::move(base.at(1).begin(), base.at(1).end(), std::back_inserter(array));
            std::move(base.at(2).begin(), base.at(2).end(), std::back_inserter(array));
            base.at(0).clear();
            base.at(1).clear();
            base.at(2).clear();
        }
    }
}


template<class TypeContainer>
template<class Iter>
void WORK::ContainerInterface<TypeContainer>
::initDigitalSort(Iter begin, Iter end)
{
    auto array{ nameToContainer() };
    //nameToContainer();
    decltype(array) tmp( array.size() );
    std::copy(array.begin(), array.end(), std::back_inserter(tmp));
    //std::string oldName{ arrayToString () };
    //std::cout << "\n\narrayToString : " << oldName << " \n\n";
    std::cout << "\narray before digitalSort: \n";
    for (auto&& it : array)
    {
        std::cout << "n:" << it << "\n";
    }
    arrayEncodeToTernarySystem();
    digitalSort();
    arrayDecodeToTernarySystem();
    //std::cout << "\n\narrayToString : " << arrayToString() << " \n\n";
    std::cout << "array after digitalSort: \n";
    for (auto&& it : array)
    {
        std::cout << "n:" << it << "\n";
    }
/*******************************************************************************************************************/
    array.clear();
    std::copy(tmp.begin(), tmp.end(), std::back_inserter(array));
    //std::string newName{ arrayToString() };
    std::cout << ("\n*************************************************************\n");
    std::cout << ("\n*************************************************************\n");
    std::cout << ("\n*************************************************************\n");

    //std::cout << "\n\narrayToString : " << newName << " \n\n";
    std::cout << "\narray before digitalSort: \n";
    for (auto&& it : array)
    {
        std::cout << "n:" << it << "\n";
    }

    std::sort(array.begin(), array.end());

   // std::cout << "\n\narrayToString : " << arrayToString() << " \n\n";
    std::cout << "array after sort: \n";
    for (auto&& it : array)
    {
        std::cout << "n:" << it << "\n";
    }

    //std::cout << "\nbool string:" << ( oldName == newName) << "\n";
    system("pause");
    
}

