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
        /// <summary>
        ///                         Задает интерфейс и функции-члены необходимые для выполнения заданий по условию КР
        /// </summary>
        
        /*
        * создаем алиасы из базового класса
        */
        using CommonInterface<TypeContainer>::setActiveKey;                 
        using CommonInterface<TypeContainer>::getActiveKey;
        using CommonInterface<TypeContainer>::addToStatusBar;
        using CommonInterface<TypeContainer>::generatingStrings;
        using CommonInterface<TypeContainer>::delimiter;
        using CommonInterface<TypeContainer>::printErrorKey;
        using CommonInterface<TypeContainer>::header;

        /*
        * необходимые поля для решения
        */
        const size_t						  maxLengthString;  // длина строки, требуемая по условию КР
        std::string                           firstName;        // Имя
        std::string                           lastName;         // Фамилия
        std::string                           middleName;       // Имя
        std::string                           fullNameString;   // Полное ФИО для 8-го задания КР.
        std::string                           defaultString;    // Набор символов ФИО. Столько, сколько необходимо по условию (12 символов) 
        char                                  firstLetter;      // первый символ имени
        char                                  secondLetter;     // символ Я
        std::vector<TypeContainer>            array;            // Массив для реализации некоторых алгоритмов

    private:	
        
        ContainerInterface(const ContainerInterface&)               = delete;
        ContainerInterface(const ContainerInterface&&)              = delete;
        ContainerInterface& operator = (const ContainerInterface&)  = delete;
        ContainerInterface& operator = (const ContainerInterface&&) = delete;
        
        /// <summary>
        /// Распечатывает в поток контейнер.
        /// </summary>
        /// <typeparam name="Iter">Тип итератора</typeparam>
        /// <param name="begin">итератор на первый элемент</param>
        /// <param name="end">итератор на следующий после последнего элемента</param>
        /// <param name="emd">enum EnableMenuDisplay - вкл. заголовок на вывод</param>
        template <typename Iter>
        void        printContainer(Iter begin, Iter end, EnableMenuDisplay emd = EnableMenuDisplay::On);

        std::string getDefaultString();
        // Преобразует массив в строку
        template <typename TmpContainer>
        std::string arrayToString(const TmpContainer& array);
        template <typename Iter>
        std::string arrayToString(Iter begin, Iter end);
        std::string arrayToString();
        /// <summary>
        /// сбрасывает в дефолтное состояние
        /// </summary>
        void        resetArray();
        /// <summary>
        /// Преобразует массив с типами в массив size_t
        /// </summary>
        template<class Iter>
        std::vector<size_t> typeArrayToDecArray(Iter begin, Iter end);

        /// <summary>
        /// Преобразует массив с Type в массив типа TypeContainer
        /// </summary>
        template<class Type>
        void                decArrayToTypeArray(const Type& arr);
    public:
        
        ContainerInterface();

        void readKey();                 // бесконечный цикл, идет считывание клавиши и идет обработка команды
        void showSort(TypeSort tSort);  // общий интерфейс сортировки

        void directSelectionSort();        // сортировка методом прямого выбора
        void shakerSort();                 // шейкерная сортировка
        void shellSort();                  // сортировка методом шелла

        void makeHeap();                                     // вспомагательная функция для построения пирамиды

        void pushHeap(TypeContainer* arr, size_t curr, size_t size);// строит пирамиду
              

        void                        hoareSort();                                            // вспомагательная функция для сортировки методом Хоара
        void                        hoare(TypeContainer* data, size_t begin, size_t end, size_t cnt);   // сортировка методом Хоара

        void                        showMerge();                                            // интерфейс сортировки слиянием
        template <typename Iter>
        std::list<TypeContainer>    merge(Iter first, Iter last, Iter first2, Iter last2);  // сортировка слиянием
        template <typename Iter>
        std::vector<size_t>         fromToTernarySystem(Iter begin, Iter end, size_t from, size_t to);  // переводит контейнер из "from" СС в "to" СС 
        template <typename Type>
        Type                        digitalSort(Type& array);                               // цифровая сортировка
        void                        initDigitalSort();                                      // интерфейс цифровой сортировки
        void                        showQSearch(const TypeContainer& elem);                 // интерфейс быстрого поиска
        template <typename Iter>
        std::pair<bool, size_t>     quickSearch(Iter begin, Iter end, const TypeContainer& elem); // быстрый поиск
    };
}


/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
                                                /* Определение функций-членов класса */



template <class TypeContainer>
WORK::ContainerInterface<TypeContainer>
::ContainerInterface()
    : CommonInterface<TypeContainer>()
    , maxLengthString{ 12 }                 /*********----- НЕ БОЛЬШЕ ДЛИНЫ ФИО и НЕ МЕНЬШЕ 2, ИНАЧЕ UB ---***************/ // на данный момент это 12
    , firstName("АНДРЕЙ")                   // ЗАПОЛНИТЬ --- ИМЯ
    , lastName("ХАКИМОВ")                   // ЗАПОЛНИТЬ --- ФАМИЛИЯ
    , middleName("САМИГУЛЛОВИЧ")            // ЗАПОЛНИТЬ --- ОТЧЕСТВО
    , fullNameString(lastName + firstName + middleName)
    , defaultString(fullNameString.substr(0, maxLengthString))
    , firstLetter(firstName[0])
    , secondLetter('Я')
    , array() {
    std::copy(defaultString.begin(), defaultString.begin() + maxLengthString, std::back_inserter(array));
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
    case Keys::Exit:                            exit(0);                                            // Выход из цикла	
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
    case Keys::QuickSearchBegin:                showQSearch(firstLetter);                           // 8
        break;
    case Keys::QuickSearchEnd:                  showQSearch(secondLetter);	                        // 9
        break;
    default:
        printErrorKey();                        // любая клавиша отсутствующая в перечислении Keys
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
template <class Iter>
std::string WORK::ContainerInterface<TypeContainer>
::arrayToString(Iter begin, Iter end)
{
    std::string result;
    std::copy(begin, end, std::back_inserter(result));
    return result;
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
    resetArray();

    switch (tSort) {
        case TypeSort::DirectSelection:     directSelectionSort();  break;
        case TypeSort::Shake:               shakerSort();           break;
        case TypeSort::Shell:               shellSort();            break;
        case TypeSort::Heap:                makeHeap();             break;
        case TypeSort::Hoare:               hoareSort();            break;
        case TypeSort::Digital:             initDigitalSort();      break;
        default:
            addToStatusBar(header("Метод сортировки не выбран!"));
    }
}


template <class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::directSelectionSort()
{

    auto begin{ array.begin() };
    auto end{ array.end() };
    using Iter = decltype(array)::iterator;

    size_t countOfComparisons{};
    size_t countOfShipments{};
    Iter min{ array.begin() };
    addToStatusBar(header("Сортировка методом Прямого выбора"));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Строка до сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));
    for (auto it{ begin }, ite{ std::prev(end) }; it != ite; ++it) {
        min = it;
        for (auto it_j{ std::next(it) }, ite_j{ end }; it_j != ite_j; ++it_j) {
            ++countOfComparisons;
            if (*it_j < *min) min = it_j;			
        }
        countOfShipments += 3;
        std::iter_swap(it, min);
        auto distance{ std::distance(begin, it) + 1 };
        addToStatusBar(generatingStrings(std::to_string(distance), arrayToString()));
        addToStatusBar(delimiter('-'));
    }
    addToStatusBar(generatingStrings("Строка после сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));
    addToStatusBar(delimiter(' '));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Количество сравнений", std::to_string(countOfComparisons)));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Количество перестановок", std::to_string(countOfShipments)));
    addToStatusBar(delimiter('-'));
}


template <class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::shakerSort()
{
    using Iter = decltype(array)::iterator;

    size_t countOfComparisons   {               };
    size_t countOfShipments     {               };

    Iter begin				    { array.begin() };
    Iter left				    { array.begin() };
    Iter right				    { array.end()   };

    addToStatusBar(header("Шейкерная сортировка"));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Строка до сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));

    size_t distance{};
    while (left != right)
    {
        for (auto it{ std::prev(right) }, ite{ left }; it != ite; --it)
        {
            ++countOfComparisons;
            if (*std::prev(it) > *it) {
                std::iter_swap(std::prev(it), it);
                ++countOfShipments;
            }
            addToStatusBar(generatingStrings(std::string(1, *std::prev(it)) + std::string(1, *it)));
            addToStatusBar(generatingStrings(std::to_string(++distance), arrayToString()));
            addToStatusBar(delimiter('-'));
        }
        ++left;

        addToStatusBar(delimiter('_'));
        for (auto it{ left }; it != right; ++it)
        {
            ++countOfComparisons;
            if (*std::prev(it) > *it)
            {
                std::iter_swap(std::prev(it), it);
                ++countOfShipments;
                
            }
            addToStatusBar(generatingStrings(std::string(1, *std::prev(it)) + std::string(1, *it)));
            addToStatusBar(generatingStrings(std::to_string(++distance), arrayToString()));
            addToStatusBar(delimiter('-'));
        }
        if (left == right) break;
        --right;

        addToStatusBar(generatingStrings(std::to_string(++distance), arrayToString()));
        addToStatusBar(delimiter('-'));
        addToStatusBar(delimiter());
    }

    addToStatusBar(generatingStrings("Строка после сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));
    addToStatusBar(delimiter(' '));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Количество сравнений", std::to_string(countOfComparisons)));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Количество перестановок", std::to_string(countOfShipments)));
    addToStatusBar(delimiter('-'));
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::shellSort()                                                   //////////////////////////////                
{

    addToStatusBar(header("Сортировка методом Шелла"));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Строка до сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));

    size_t countOfComparisons{};
    size_t countOfShipments{};

    auto first{ array.begin() };
    auto last{ array.end() };
    auto distance{ last - first };
    for (auto d{ 3 }; d > 0 ; d -= 2)
    {
        for (auto i{ first + d }; i != last; ++i)
        {
            for (auto j = i; j - first >= d; j -= d)
            {
                ++countOfComparisons;
                addToStatusBar(generatingStrings(std::string(1, *j) + std::string(1, *(j - d))));
                if (*j < *(j - d))
                {
                    ++countOfShipments;
                    addToStatusBar(generatingStrings(std::string(1, *j) + std::string(1, *(j - d))));
                    std::iter_swap(j, j - d);
                }
                else break;
                addToStatusBar(generatingStrings(arrayToString()));
            }
        }

        addToStatusBar(delimiter('-'));
    }

    addToStatusBar(generatingStrings("Строка после сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));
    addToStatusBar(delimiter(' '));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Количество сравнений", std::to_string(countOfComparisons)));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Количество перестановок", std::to_string(countOfShipments)));
    addToStatusBar(delimiter('-'));
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::pushHeap(TypeContainer *data, size_t curr, size_t size)
{

    if (data == nullptr)
    {
        addToStatusBar(generatingStrings("In void WORK::ContainerInterface<TypeContainer>"));
        addToStatusBar(generatingStrings("::hoare(TypeContainer * data, size_t begin, size_t end)"));
        addToStatusBar(generatingStrings("data == nullptr"));
        return;
    }

    TypeContainer elem{ data[curr] };
    size_t child{};
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("0_start"));
    addToStatusBar(generatingStrings(arrayToString()));
    while (curr <= size / 2)
    {
        child = curr + curr;
        if (child < size && data[child] < data[child + 1]) ++child;
        if (elem >= data[child])
        {
            addToStatusBar(generatingStrings("SR " + std::string(1, data[child]) + "_" + std::string(1, data[child + 1])));
            break;
        }
        data[curr] = data[child];
        curr = child;

        addToStatusBar(generatingStrings(std::string(1, data[child]) + " " + std::string(1, elem)));
    }
    data[curr] = elem;

    addToStatusBar(generatingStrings(arrayToString()));
    addToStatusBar(generatingStrings("1_end"));
    addToStatusBar(delimiter('-'));
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::makeHeap()
{    
    addToStatusBar(header("Построить пирамиду"));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Изначальная строка", arrayToString()));
    addToStatusBar(delimiter('-'));

    auto begin{ array.begin() + (array.end() - array.begin()) / 2 };

    for (auto i{ array.size() / 2 }; i > 0; --i)
    {
        pushHeap(array.data(), i, array.size() - 1);
    }

    addToStatusBar(generatingStrings("результат построения пирамиды", arrayToString()));
    addToStatusBar(delimiter('-'));
}


template<typename TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::hoare(TypeContainer* data, size_t begin, size_t end, size_t cnt)
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
            if (i < j)
            {
                addToStatusBar(generatingStrings(std::to_string(i) + "\t"+ std::string(1, data[i]) + std::string(1, data[j]) + "\t" + std::to_string(j)));
                std::swap(data[i], data[j]);
            }
            ++i;
            --j;
        }
        addToStatusBar(generatingStrings("i " + std::to_string(i) + " j " + std::to_string(j)));
        addToStatusBar(generatingStrings(std::to_string(++cnt), arrayToString()));
        addToStatusBar(delimiter('-'));
    }
    addToStatusBar(generatingStrings("i " + std::to_string(i) + " end"));
    if (i < end) hoare(data, i, end, cnt);
    if (begin < j) hoare(data, begin, j, cnt);


}


template<typename TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::hoareSort()
{
    addToStatusBar(header("Сортировка методом Хоара"));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Строка до сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));
    hoare(array.data(), 0, array.size() - 1, 0);
    addToStatusBar(generatingStrings("Строка после сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));
}


template<typename TypeContainer>
template<typename Iter>
std::list<TypeContainer> WORK::ContainerInterface<TypeContainer>
::merge(Iter first, Iter last, Iter first2, Iter last2 )
{
    std::list<TypeContainer> result;
    auto it_r{ std::back_inserter(result) };
    std::sort(first, last);
    std::sort(first2, last2);
    addToStatusBar(generatingStrings("Фамилия: " + arrayToString(first, last)));
    addToStatusBar(generatingStrings("Имя: " + arrayToString(first2, last2)));
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
        addToStatusBar(generatingStrings(arrayToString(result.begin(), result.end())));
    }
    std::copy(first2, last2, it_r);
    return result;
}


template<typename TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::showMerge()
{
    auto copy_firstName{ firstName };
    auto copy_lastName{ lastName };
    std::list<TypeContainer> lst{ merge(lastName.begin(), lastName.end(), firstName.begin(), firstName.end()) };

    std::string result;
    std::copy(lst.begin(), lst.end(), std::back_inserter(result));
    addToStatusBar("Сортировка слиянием", StringFormat::On);
    addToStatusBar(generatingStrings("первый список", "\"" + copy_lastName + "\""));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("второй список", "\"" + copy_firstName + "\""));

    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("результатирующий список", "\"" + result + "\""));
    addToStatusBar(delimiter('-'));



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

    addToStatusBar(header("Метод цифровой сортировки"));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Строка до сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));
    //for (auto maxElem{ *std::max_element(begin, end) }; maxElem; maxElem /= 10)
    {
        for (int i{}, step{ 1 }; i < base.size(); ++i, step *= 10)
        {

            addToStatusBar(delimiter(' '));
            addToStatusBar(generatingStrings("____" + std::to_string(i) + "____"));
            addToStatusBar(delimiter(' '));
            addToStatusBar(delimiter('-'));
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
            printContainer(array.begin(), array.end(), EnableMenuDisplay::Off);
            addToStatusBar(delimiter());
        }

        
    }
    this->array.clear();
    decArrayToTypeArray( fromToTernarySystem(array.begin(), array.end(), 3, 10) );
    addToStatusBar(generatingStrings("Строка после сортировки", arrayToString()));
    addToStatusBar(delimiter('-'));
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
void WORK::ContainerInterface<TypeContainer>
::initDigitalSort()
{
    auto arr{ typeArrayToDecArray(array.begin(), array.end()) };
    auto arrayInTernary{ std::move(fromToTernarySystem(arr.begin(), arr.end(), 10, 3)) };
    auto arraySorted{ std::move(digitalSort(arrayInTernary)) };
    auto arrayInDec{ fromToTernarySystem(arraySorted.begin(), arraySorted.end(), 3, 10) };

    //printContainer(arrayInDec.begin(), arrayInDec.end(), EnableMenuDisplay::Off);
    array.clear();

    decArrayToTypeArray(arrayInDec);
}


template<class TypeContainer>
void WORK::ContainerInterface<TypeContainer>
::showQSearch(const TypeContainer& elem)
{
    std::string copyFullName{ fullNameString };
    std::sort(copyFullName.begin(), copyFullName.end());
    addToStatusBar("Быстрый поиск", StringFormat::On);
    addToStatusBar(generatingStrings("Поиск в строке", fullNameString));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Строка в отсортированном виде", arrayToString(copyFullName.begin(), copyFullName.end())));
    addToStatusBar(delimiter('-'));
    auto elem_t{ elem - 'А' + 1 };
    addToStatusBar(generatingStrings("Поисковый запрос", std::string() + elem + "(" + std::to_string(elem_t) + ")"));
    addToStatusBar(delimiter('-'));
    auto vec{ typeArrayToDecArray(copyFullName.begin(), copyFullName.end()) };
    auto [isFind, countOfComparisons] = quickSearch(vec.begin(), vec.end(), elem);

    std::string find{ isFind ? "Найдено" : "НЕ найдено" };
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Результат поиска", find));
    addToStatusBar(delimiter('-'));
    addToStatusBar(generatingStrings("Количество сравнений", std::to_string(countOfComparisons)));
    addToStatusBar(delimiter('-'));
}


template<class TypeContainer>
template<class Iter>
std::pair<bool, size_t> WORK::ContainerInterface<TypeContainer>
::quickSearch(Iter begin, Iter end, const TypeContainer& elem)
{
    Iter left{ begin };
    Iter right{ end };
    auto elem_t{ elem - 'А' + 1 };
    size_t countOfComparisons{};
    addToStatusBar(header(""));
    printContainer(begin, end, EnableMenuDisplay::Off);
    while (std::distance(left, right) > 0)
    {
        auto distance = std::distance(left, right);
        Iter middle{ left + (distance / 2) };
        if (*middle == elem_t)
        {
            auto length{ std::distance(left, middle) };
            addToStatusBar(generatingStrings(std::to_string(length) + " " 
                + std::string(1, *middle + 'А' - 1) + " == " + std::string(1, elem_t + 'А' - 1)));
            return { true, countOfComparisons };
        }
        if (*middle < elem_t)
        {
            auto length{ std::distance(left, middle) };
            addToStatusBar(generatingStrings(std::to_string(length) + " " 
                + std::string(1, *middle + 'А' - 1) + " < " + std::string(1, elem_t + 'А' - 1)));
            left = middle + 1;
        }
        else
        {
            auto length{ std::distance(left, middle) };
            addToStatusBar(generatingStrings(std::to_string(length) + " " 
                + std::string(1, *middle + 'А' - 1) + " > " + std::string(1, elem_t + 'А' - 1)));
            right = middle - 1;
        }
        ++countOfComparisons;
    }
    return { false, countOfComparisons };
}

