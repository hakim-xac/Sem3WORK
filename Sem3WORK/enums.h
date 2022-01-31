#pragma once
namespace WORK {
    enum class Keys {
        Exit = 48										// Key 0, �����
        , DirectSelectionSort = 49						// Key 1, ��������� ������� ���������� ������� ������� ������
        , ShakerSort = 50								// Key 2, ��������� ������� ��������� ����������
        , ShellSorting = 51								// Key 3, ��������� ���������� ������� �����
        , Heap = 52									    // Key 4, ��������� ��������
        , HoareSorting = 53								// Key 5, ��������� ������� ���������� ������� �����
        , Merger = 54									// Key 6, �������� ������� ���� ������������� �������
        , DigitalSorting = 55							// Key 7, ��������� ������� ���������� ������� �������� ����������
        , QuickSearchBegin = 56							// Key 8, ��������� ������� ������� ����� ������ ����� �����
        , QuickSearchEnd = 57							// Key 9, ��������� ������� ������� ����� ����� �߻
        , EmptyKey = -1
    };

    enum class StringFormat {                           // ���� �������������� ������
        On
        , Off
    };

    enum class EnableMenuDisplay {                      // ���� ����������� ���������
        On
        , Off
    };

    enum class TypeSort {                               // ������������ ������������ ����������
        DirectSelection
        , Shake
        , Shell
        , Heap
        , Hoare
        , Merge
        , Digital
    };

    enum class HeaderValue {                            // ��������������� ������������, ��� �������� std::string � std::map
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




