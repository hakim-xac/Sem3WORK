#ifndef MAIN_WORK
#define MAIN_WORK

#include <iostream>
#include "ContainerInterface.h"
#include <windows.h>
namespace WORK {
    void setWindow(short width, short height)
    {
        _SMALL_RECT Rect{ 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(width - 1) };
        HANDLE Handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
        SetConsoleScreenBufferSize(Handle, _COORD{ width , height });
        SetConsoleWindowInfo(Handle, TRUE, &Rect);
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
    using namespace WORK;                           // Подключаем пространство имен нашей программы

    setWindow(111, 300);
    setlocale(LC_ALL, "Russian");                   // Задаем локаль


    ContainerInterface<char> window{};

    /* Запускаем бесконечный цикл ожидая ввод команды от пользователя  */
    while (true)
    {
        //if (window.getFlagClearArrayAndHash()) window.showGeneratedRandom();

        system("cls");                        // Очистка экрана
        window.showHeader();                // Вывод заголовка
        window.showStatusBar();             // Вывод "всплывающих сообщений"
        window.showMenu();                  // Вывод меню
        window.readKey();
    }
}
#pragma clang diagnostic pop


#endif