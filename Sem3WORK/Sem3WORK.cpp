#pragma once

#include <iostream>
#include "enums.h"
#include "CommonInterface.h"



int main()
{
    using namespace WORK;                           // Подключаем пространство имен нашей программы

    setlocale(LC_ALL, "Russian");                   // Задаем локаль


    CommonInterface<int> window{};


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
