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


        std::string                           fullNameString;
        std::string                           defaultString;
        std::vector<TypeContainer>            array;

    private:	
        
        ContainerInterface(const ContainerInterface&)               = delete;
        ContainerInterface(const ContainerInterface&&)              = delete;
        ContainerInterface& operator = (const ContainerInterface&)  = delete;
        ContainerInterface& operator = (const ContainerInterface&&) = delete;
        
        std::vector<TypeContainer> nameToContainer();
        template <typename Iter>
        void        printContainer(Iter begin, Iter end, EnableMenuDisplay emd = EnableMenuDisplay::On);
        std::string getDefaultString();
        template <typename TmpContainer>
        std::string arrayToString(const TmpContainer& array);
        std::string arrayToString();
        void        resetArray();

        template<class Iter>
        std::vector<size_t> typeArrayToDecArray(Iter begin, Iter end);
        template<class Type>
        void                decArrayToTypeArray(const Type& arr);
    public:
        
        ContainerInterface();

        void readKey();
        void showSort(TypeSort tSort);

        std::tuple<bool, size_t, size_t, std::string> selectAction(TypeSort tSort);

        std::tuple<bool, size_t, size_t, std::string> directSelectionSort();
        std::tuple<bool, size_t, size_t, std::string> shakerSort();
        std::tuple<bool, size_t, size_t, std::string> shellSort();

        std::string                 makeHeap();

        template <typename Iter>
        void                        pushHeap(Iter begin, Iter end);

        std::string                 hoareSort();
        void                        hoare(TypeContainer* data, size_t begin, size_t end);

        void                        showMerge();
        template <typename Iter>
        std::list<TypeContainer>    merge(Iter first, Iter last, Iter first2, Iter last2);
        template <typename Iter>
        std::vector<size_t>         fromToTernarySystem(Iter begin, Iter end, size_t from, size_t to);
        template <typename Type>
        Type                        digitalSort(Type& array);
        std::string                 initDigitalSort();
        void                        showQSort(const TypeContainer& elem);
        std::pair<bool, size_t>     isQuickSearch(const TypeContainer& elem);
        template <typename Iter>
        std::pair<bool, size_t>     quickSearch(Iter begin, Iter end, const TypeContainer& elem);
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
    , fullNameString("ХАКИМОВАНДРЕЙСАМИГУЛЛОВИЧ")
    , defaultString("ХАКИМОВАНДРЕ")
    , array() {
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
    case Keys::Exit:                            exit(0);								            // Выход из цикла	
        break;
    case Keys::DirectSelectionSort:             showSort(TypeSort::DirectSelection);                // 1
        break;
    case Keys::ShakerSort:                      showSort(TypeSort::Shake);                          // 2
        break;
    case Keys::ShellSorting:                    showSort(TypeSort::Shell);                          // 3
        break;
    case Keys::Heap:                            showSort(TypeSort::Heap);                           // 4
        break;
    case Keys::HoareSorting:                    showSort(TypeSort::Hoare);                          // 5
        break;
    case Keys::Merger:                          showMerge();                                        // 6
        break;
    case Keys::DigitalSorting:                  showSort(TypeSort::Digital);                        // 7
        break;
    case Keys::QuickSearchBegin:                showQSort('А');                                     // 8
        break;
    case Keys::QuickSearchEnd:                  showQSort('Я');	                                    // 9
        break;
    default:
        printErrorKey();								// любая клавиша отсутствующая в перечислении Keys
        break;
    }
    setActiveKey(Keys::EmptyKey);
}


template <class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::resetArray()
{
    array.clear();
    std::copy(defaultString.begin(), defaultString.end(), std::back_inserter(array));
}


template <class TypeContainer>
std::string WORK::ContainerInterface<TypeContainer>
::getDefaultString()
{
    return defaultString;
}


template <class TypeContainer>
std::string WORK::ContainerInterface<TypeContainer>
::arrayToString()
{
    std::string result;
    std::copy(array.begin(), array.end(), std::back_inserter(result));
    return result;
}


template <class TypeContainer>
template <class TmpContainer>
std::string WORK::ContainerInterface<TypeContainer>
::arrayToString(const TmpContainer& array)
{
    std::string result;
    std::move(array.begin(), array.end(), std::back_inserter(result));
    return result;
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
std::tuple<bool, size_t, size_t, std::string> WORK::ContainerInterface<TypeContainer>
::selectAction(TypeSort tSort)
{

    size_t countOfComparisons{};
    size_t countOfShipments{};
    bool isVisibleCounts{};
    std::string stringResult{};
    resetArray();
    switch (tSort) {
    case TypeSort::DirectSelection:		std::tie(isVisibleCounts, countOfComparisons, countOfShipments, stringResult) = directSelectionSort();  break;
    case TypeSort::Shake:				std::tie(isVisibleCounts, countOfComparisons, countOfShipments, stringResult) = shakerSort();           break;
    case TypeSort::Shell:				std::tie(isVisibleCounts, countOfComparisons, countOfShipments, stringResult) = shellSort();            break;
    case TypeSort::Heap:				                                                                 stringResult = makeHeap();             break;
    case TypeSort::Hoare:				                                                                 stringResult = hoareSort();            break;
    case TypeSort::Digital:				                                                                 stringResult = initDigitalSort();      break;
    default:
        addToStatusBar("Метод сортировки не выбран!", StringFormat::On);
    }
    return { isVisibleCounts, countOfComparisons, countOfShipments, stringResult };
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::showSort(TypeSort tSort)
{
    auto [isVisibleCounts, countOfComparisons, countOfShipments, headerSort] = selectAction(tSort);

    addToStatusBar(headerSort, StringFormat::On);
    addToStatusBar(delimiter('-'));
    addToStatusBar(delimiter(' '));
    addToStatusBar(generatingStrings("Строка до операции", getDefaultString()));
    addToStatusBar(delimiter(' '));
    addToStatusBar(delimiter('-'));
    addToStatusBar(delimiter(' '));
    addToStatusBar(generatingStrings("Строка после операции", arrayToString()));
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
std::tuple<bool, size_t, size_t, std::string> WORK::ContainerInterface<TypeContainer>
::directSelectionSort()
{

    auto begin{ array.begin() };
    auto end{ array.end() };
    using Iter = decltype(array)::iterator;

    size_t countOfComparisons{};
    size_t countOfShipments{};
    Iter min{ array.begin() };
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
std::tuple<bool, size_t, size_t, std::string> WORK::ContainerInterface<TypeContainer>
::shakerSort()
{
    using Iter = decltype(array)::iterator;

    size_t countOfComparisons   {               };
    size_t countOfShipments     {               };

    Iter left				    { array.begin() };
    Iter right				    { array.end()   };

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
std::tuple<bool, size_t, size_t, std::string> WORK::ContainerInterface<TypeContainer>
::shellSort()                                                   //////////////////////////////                
{
    size_t countOfComparisons{};
    size_t countOfShipments{};

    for (size_t step{ array.size() >> 1}; step; step >>= 1)
    {
        for (size_t i{ step }, j{}; i < array.size(); ++i)
        {
            TypeContainer tmp{ array[i] };
            for (j = i; j >= step; j -= step)
            {
                ++countOfComparisons;
                if (tmp < array[j - step]) array[j] = array[j - step];                
                else break;
            }
            array[j] = tmp;
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
std::string WORK::ContainerInterface<TypeContainer>
::makeHeap()
{    
    auto begin{ array.begin() };
    auto end{ array.begin() };

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
    int x{ data[(begin + end - 1) / 2] };

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
std::string WORK::ContainerInterface<TypeContainer>
::hoareSort()
{
    hoare(array.data(), 0, array.size() - 1);
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
template<class Iter>
inline std::vector<size_t> WORK::ContainerInterface<TypeContainer>
::fromToTernarySystem(Iter begin, Iter end, size_t from, size_t to)
{
    
    std::vector<size_t> result;
    for (auto it{ begin }, ite{ end }; it != ite; ++it)
    {
        size_t tmp{};
        for (size_t pow{ 1 }; *it; pow *= from, *it /= to)
        {
            tmp += (*it % to) * pow;
        }
        result.emplace_back(tmp);
    }
    return result;
}


template<class TypeContainer>
template<class Type>
Type WORK::ContainerInterface<TypeContainer>
::digitalSort(Type& array)
{
    auto begin{ array.begin() };
    auto end{ array.end() };
    std::vector<std::list<size_t>> base(3);    

    for (auto maxElem{ *std::max_element(begin, end) }; maxElem; maxElem /= 10)
    {
        for (int i{}, step{ 1 }; i < base.size(); ++i, step *= 10)
        {
            for (auto&& it: array)
            {
                size_t tmp_it{ it };
                tmp_it /= step;
                auto n{ tmp_it % 10 };
                if (n > 2)
                {
                    addToStatusBar("Формат массива не задан!", StringFormat::On);
                    addToStatusBar("Числа должны быть в троичной системе счисления!", StringFormat::On);
                    array.clear();
                    return Type();
                }
                base.at(n).push_back(it);
            }
            array.clear();
            std::copy(base.at(0).begin(), base.at(0).end(), std::back_inserter(array));
            std::copy(base.at(1).begin(), base.at(1).end(), std::back_inserter(array));
            std::copy(base.at(2).begin(), base.at(2).end(), std::back_inserter(array));
            base.at(0).clear();
            base.at(1).clear();
            base.at(2).clear();
        }
    }
    Type result;
    std::move(array.begin(), array.end(), std::back_inserter(result));
    return result;
}


template<class TypeContainer>
template<class Iter>
std::vector<size_t> WORK::ContainerInterface<TypeContainer>
::typeArrayToDecArray(Iter begin, Iter end)
{
    std::vector<size_t> result;
    std::transform(begin, end, std::back_inserter(result), [](TypeContainer& elem) -> size_t {
        return elem - 'А' + 1;
        });
    return result;
}


template<class TypeContainer>
template<class Type>
void WORK::ContainerInterface<TypeContainer>
::decArrayToTypeArray(const Type& arr)
{
    std::transform(arr.begin(), arr.end(), std::back_inserter(array), [](size_t elem) -> TypeContainer {
        return static_cast<int>(elem) + 'А' - 1;
        });

}


template<class TypeContainer>
std::string WORK::ContainerInterface<TypeContainer>
::initDigitalSort()
{
    auto arr{ typeArrayToDecArray(array.begin(), array.end()) };
    auto arrayInTernary{ std::move(fromToTernarySystem(arr.begin(), arr.end(), 10, 3)) };
    auto arraySorted{ std::move(digitalSort(arrayInTernary)) };
    auto arrayInDec{ fromToTernarySystem(arraySorted.begin(), arraySorted.end(), 3, 10) };

    printContainer(arrayInDec.begin(), arrayInDec.end());
    array.clear();

    decArrayToTypeArray(arrayInDec);
    return "Метод цифровой сортировки";
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::showQSort(const TypeContainer& elem)
{
    addToStatusBar("Быстрый поиск", StringFormat::On);
    addToStatusBar(generatingStrings("Поиск в строке", fullNameString));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Поисковый запрос", std::string() + elem));
    auto [isFind, countOfComparisons] = isQuickSearch(elem);
    std::string find{ isFind ? "Найдено" : "НЕ найдено" };
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Результат поиска", find));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Количество сравнений", std::to_string(countOfComparisons)));
    addToStatusBar(delimiter('-'));
}


template<class TypeContainer>
std::pair<bool, size_t> WORK::ContainerInterface<TypeContainer>
::isQuickSearch(const TypeContainer& elem)
{
    std::string copyFullName{ fullNameString };
    hoare(copyFullName.data(), 0, copyFullName.size() - 1);
    return quickSearch(copyFullName.begin(), copyFullName.end(), elem);
}


template<class TypeContainer>
template<class Iter>
std::pair<bool, size_t> WORK::ContainerInterface<TypeContainer>
::quickSearch(Iter begin, Iter end, const TypeContainer& elem)
{
    Iter left{ begin };
    Iter right{ end };
    size_t countOfComparisons{};
    while (std::distance(left, right) > 0)
    {
        auto distance = std::distance(left, right);
        Iter middle{ left + (distance / 2) };
        if (*middle == elem) return { true, countOfComparisons };
        if (*middle < elem) left = middle + 1;
        else right = middle - 1;
        ++countOfComparisons;
    }
    return { false, countOfComparisons };
}

