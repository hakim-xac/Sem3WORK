#pragma once
#include <string>
#include <queue>
#include <iostream>
#include <type_traits>
#include "enums.h"

namespace WORK {
	/// <summary>
	/// ��������� ���������
	/// </summary>
	/// <typeparam name="TypeArray">��� �������, ������������� ��� �������� ��������� �����</typeparam>
	/// <typeparam name="TypeHashDirectBinding">��� �������, ������������� ��� �������� ����� � ��������
	///  ���-������� ��������� ����� ������� ����������</typeparam>
	/// <typeparam name="TypeHashOpenAdressing">��� �������, ������������� ��� �������� ����� � ��������
	///  ���-������� ��������� ����� �������� ����������</typeparam>
	template <class TypeArray>
	class Interface
	{
		std::ostream& out										{ std::cout };			// ����� ������
		size_t maxTableWidth									{ 110 };				// ������ ��������� ������
		int maxTableColumnsInArray								{ 5 };					// ���������� ������� ��� ������ �������
		std::queue <std::string> bufferForStatusBar				{};						// ������� ��� ������ ����
		Keys activeKey											{ Keys::EmptyKey };		// 
		std::vector <std::string> bufferForMenu{};										// ����� ����


	private:
		Interface() = delete;															// ��������� ��������� ������ �����

		void generateMenu();															// ���������� ����
	protected:


		TypeArray myTypeArray;
			
		void addToStatusBar(const std::string&& str, bool isFormated = true);			// ��������� � ������� ������ ����, ������ ��� ������

		bool flagClearArrayAndHash								{ true };				// ���� ������� ������� �, �������������, ���-������


	public:
		
		Interface(TypeArray&& myTypeArray);

		constexpr size_t getMaxTableWidth()			const;					// ������� ������ ������������ ����� ������������ ������ � ����������
		constexpr size_t getMaxTableColumns()		const;					// ������� ���������� ������� "�������", ��� ������ ������ ������� � ���-������

		Keys getActiveKey()							const;					// ������� �������� ���� �������
		void setActiveKey(Keys key);										// ������ ��� �������

		constexpr void showHeader();										// ������� ���������
		constexpr void showMenu();											// ������� ����
		void showStatusBar();												// ������� ���������� �� ������ ����

		constexpr  std::string delimiter(char del = '=') const;				// ������� �����������


		///
		/// ���������� ������ �������� ������� ��������� � 1 ����������
		///
		constexpr const std::string generatingStrings(const std::string&& str, char del = ' ') const;

		///
		/// ���������� ������ �������� ������� ��������� � 2 �����������
		///
		constexpr const std::string generatingStrings(const std::string&& str, const std::string&& str2, char del = ' ') const;

	};
}


/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
												/* ����������� ������� */


template <class TypeArray>
WORK::Interface<TypeArray>
::Interface(TypeArray&& myTypeArray) : myTypeArray(myTypeArray) {
	generateMenu();
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::generateMenu()
{
	bufferForMenu.emplace_back(delimiter());
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("������� �� ������� � ������� ����"));
	bufferForMenu.emplace_back(delimiter('_'));
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("������ �� ������� �������"));
	bufferForMenu.emplace_back(delimiter('_'));
	bufferForMenu.emplace_back(generatingStrings("( 1 )", "��������� ������� ���������� ������� ������� ������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 2 )", "��������� ������� ��������� ����������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 3 )", "��������� ������� ���������� ������� �����", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 4 )", "��������� ��������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 5 )", "����� ������� ����������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 6 )", "������� ���� �������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 7 )", "��������� ������� ���������� ������� �������� ����������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 8 )", "��������� ������� ������� ����� ����� �", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 9 )", "��������� ������� ������� ����� ����� �", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 0 )", "�����", '.'));
	bufferForMenu.emplace_back(delimiter());
}


template <class TypeArray>
constexpr void WORK::Interface<TypeArray>
::showMenu()
{
	for (auto&& it : bufferForMenu)
	{
		out << it;
	}
}


template <class TypeArray>
constexpr size_t WORK::Interface<TypeArray>
::getMaxTableWidth() const
{
	return maxTableWidth;
}


template <class TypeArray>
constexpr size_t WORK::Interface<TypeArray>
::getMaxTableColumns() const
{
	return maxTableColumnsInArray;
}


template <class TypeArray>
WORK::Keys WORK::Interface<TypeArray>
::getActiveKey() const
{
	return activeKey;
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::setActiveKey(Keys key)
{
	activeKey = key;
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::addToStatusBar(const std::string&& str, bool isFormated)
{	
	if (!isFormated) {
		bufferForStatusBar.emplace(std::move(str));
		return;
	}
	std::string hr{ delimiter() };
	std::string hr2{ delimiter(' ')};

	bufferForStatusBar.emplace(hr);
	bufferForStatusBar.emplace(hr2);
	bufferForStatusBar.emplace(generatingStrings(std::move(str)));
	bufferForStatusBar.emplace(hr2);
	bufferForStatusBar.emplace(hr);
}


template <class TypeArray>
constexpr void WORK::Interface<TypeArray>
::showHeader()
{
	std::string hr{ delimiter() };

	out << hr;
	out << generatingStrings("����������� ������");
	out << delimiter('-');
	out << generatingStrings("������ ��-11", "������� �.C.");
	out << hr;
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::showStatusBar()
{
	std::string hr{ delimiter(' ') };

	out << hr;

	while (!bufferForStatusBar.empty())
	{
		out << bufferForStatusBar.front();
		bufferForStatusBar.pop();
	}

	out << hr;
}


template <class TypeArray>
constexpr std::string WORK::Interface<TypeArray>
::delimiter(char del) const
{
	std::string result(maxTableWidth, del);
	result.at(0) = '#';
	result[result.size() - 2] = '#';
	result.back() = '\n';
	return result;
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string&& inStr, char del) const
{
	if (inStr.empty()) return {};

	std::string str;
	if constexpr (std::is_lvalue_reference_v<std::string>) str = inStr;
	else str = std::move(inStr);

	try {		
		int parity{ str.length() % 2 == 0 };
		size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

		std::string middle(middleSize - parity, del);

		return { "#" + middle + str + (parity ? " " : "") + middle + "#\n" };
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return {};
	}
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string&& inStr, const std::string&& inStr2, char del) const
{
	if (inStr.empty() || inStr2.empty()) return {};

	std::string str;
	std::string str2;
	if constexpr (std::is_lvalue_reference_v<std::string>)
	{
		str = inStr;
		str2 = inStr2;
	}
	else
	{
		str = std::move(inStr);
		str2 = std::move(inStr2);
	}

	try {
		size_t len{ str.length() + str2.length() + 11 };
		size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };
		std::string middle(middleSize, del);

		return { "#    " + str + middle + str2 + "    #\n" };
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return {};
	}
}