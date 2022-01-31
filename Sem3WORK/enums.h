#pragma once
namespace WORK {
    enum class Keys {
        Exit = 48										// Key 0, ¬ыход
        , DirectSelectionSort = 49						// Key 1, выполнить вручную сортировку методом пр€мого выбора
        , ShakerSort = 50								// Key 2, выполнить вручную шейкерную сортировку
        , ShellSorting = 51								// Key 3, выполнить сортировку методом Ўелла
        , Heap = 52									    // Key 4, построить пирамиду
        , HoareSorting = 53								// Key 5, выполнить вручную сортировку методом ’оара
        , Merger = 54									// Key 6, ѕровести сли€ние двух упор€доченных списков
        , DigitalSorting = 55							// Key 7, выполнить вручную сортировку методом цифровой сортировки
        , QuickSearchBegin = 56							// Key 8, выполнить вручную быстрый поиск первой буквы имени
        , QuickSearchEnd = 57							// Key 9, выполнить вручную быстрый поиск буквы Ђяї
        , EmptyKey = -1
    };

    enum class StringFormat {                           // ‘лаг форматировани€ строки
        On
        , Off
    };

    enum class EnableMenuDisplay {                      // ‘лаг отображени€ заголовка
        On
        , Off
    };

    enum class TypeSort {                               // ѕеречислени€ используемых сортировок
        DirectSelection
        , Shake
        , Shell
        , Heap
        , Hoare
        , Merge
        , Digital
    };

    enum class HeaderValue {                            // вспомогательное перечисление, дл€ хранени€ std::string в std::map
        WorkName
        , groupName
        , LastNameStudent
        , FooterName
        , KeyErrorName
        , KeyZeroName
        , KeyOneName
        , KeyTwoName
        , KeyThreeName
        , KeyFourName
        , KeyFiveName
        , KeySixName
        , KeySevenName
        , KeyEightName
        , KeyNineName
    };
}




