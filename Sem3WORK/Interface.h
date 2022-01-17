#pragma once
#include <string>
#include <queue>
#include <iostream>
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

		void addToStatusBar(const std::string& str, bool isFormated = true);			// ��������� � ������� ������ ����, ������ ��� ������
		void addToStatusBar(const std::string&& str, bool isFormated = true);

		bool flagClearArrayAndHash								{ true };				// ���� ������� ������� �, �������������, ���-������


	public:
		
		Interface(TypeArray& myTypeArray);

		Interface(TypeArray&& myTypeArray);

		constexpr size_t getMaxTableWidth()			const;					// ������� ������ ������������ ����� ������������ ������ � ����������
		constexpr size_t getMaxTableColumns()		const;					// ������� ���������� ������� "�������", ��� ������ ������ ������� � ���-������
		constexpr bool getFlagClearArrayAndHash()	const;					// ���� ������� ������� � ���-������
		Keys getActiveKey()							const;					// ������� �������� ���� �������
		void setActiveKey(Keys key);										// ������ ��� �������

		void setFlagClearArray(bool flag);									// ������ ����, ��������������� �������

		constexpr void showHeader();										// ������� ���������
		constexpr void showMenu();											// ������� ����
		void showStatusBar();												// ������� ���������� �� ������ ����
		void showStatusType();												// ������� ���������� � ������� � ���-�������

		constexpr  std::string delimiter(char del = '=') const;				// ������� �����������


		///
		/// ���������� ������ �������� ������� ��������� � 1 ����������
		///
		constexpr const std::string generatingStrings(const std::string& str, char del = ' ') const;
		constexpr const std::string generatingStrings(const std::string&& str, char del = ' ') const;

		///
		/// ���������� ������ �������� ������� ��������� � 2 �����������
		///
		constexpr const std::string generatingStrings(const std::string& str, const std::string& str2, char del = ' ') const;
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
::Interface(
	TypeArray& myTypeArray)
	: myTypeArray(myTypeArray) {
	generateMenu();
}


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
	bufferForMenu.emplace_back(generatingStrings("�����"));
	bufferForMenu.emplace_back(generatingStrings("( 1 )", "�������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 2 )", "���-������� (����� ������� ����������)", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 3 )", "���-������� (����� �������� ����������, ������������ �������� �����)", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 4 )", "���-������� (����� �������� ����������, ������������ ������������ �����)", '.'));

	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("����� � ���-�������"));

	bufferForMenu.emplace_back(generatingStrings("( 5 )", "����� ������� ����������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 6 )", "����� �������� ����������, ������������ �������� �����", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 7 )", "����� �������� ����������, ������������ ������������ �����", '.'));

	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("������"));
	bufferForMenu.emplace_back(generatingStrings("( 8 )", "�������� ������ � ���-������� ������ �������", '.'));
	bufferForMenu.emplace_back(generatingStrings("( 9 )", "������ ����� ������ ������� � ���-������", '.'));
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
constexpr bool WORK::Interface<TypeArray>
::getFlagClearArrayAndHash() const 
{
	return flagClearArrayAndHash;
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
::setFlagClearArray(bool flag)
{
	flagClearArrayAndHash = flag;
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::addToStatusBar(const std::string& str, bool isFormated)
{
	return addToStatusBar(std::move(str), isFormated);
}


template <class TypeArray>
void WORK::Interface<TypeArray>
::addToStatusBar(const std::string&& str, bool isFormated)
{	
	if (!isFormated) {
		bufferForStatusBar.emplace(str);
		return;
	}

	bufferForStatusBar.emplace(delimiter());
	bufferForStatusBar.emplace(delimiter(' '));
	bufferForStatusBar.emplace(generatingStrings(str));
	bufferForStatusBar.emplace(delimiter(' '));
	bufferForStatusBar.emplace(delimiter());
}


template <class TypeArray>
constexpr void WORK::Interface<TypeArray>
::showHeader()
{

	std::string header{ generatingStrings("������������ ������ � 3", "�������� ����������� ����������� ������ ��� ����������� ������. ") };
	std::string header2{ generatingStrings("������ ��-11", "������� �.C.") };

	std::string hr{ delimiter() };

	out << hr;
	out << header;
	out << delimiter('-');
	out << header2;
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
void WORK::Interface<TypeArray>
::showStatusType()
{
	out << generatingStrings("������ ������� � ���-�������:", getFlagClearArrayAndHash() ? "�����" : "���������");
	out << delimiter('-');
	out << generatingStrings("���������� ��������� �������:", std::to_string(myTypeArray.getSize()));
	out << delimiter('-');
	//out << generatingStrings("���������� ��������� ���-�������:", std::to_string(myTypeHashTableDirectBinding.getSize()));
	out << delimiter();
}


template <class TypeArray>
constexpr std::string WORK::Interface<TypeArray>
::delimiter(char del) const
{

	std::string result(maxTableWidth, del);
	result.at(0) = '#';	result[result.size() - 2] = '#'; result.back() = '\n';
	return result;
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string& str, char del) const
{
	return generatingStrings(std::move(str), del);
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string&& str, char del) const
{
	try {
		if (str.empty()) throw std::exception("Dont empty string! -> LAB2::MyList::generatingStrings(const std::string& str)");
		int parity{ str.length() % 2 == 0 };
		size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

		std::string middle(middleSize - parity, del);
		std::string result{ "#" + middle + str + (parity ? " " : "") + middle + "#\n" };

		return result;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return std::string();
	}
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string& str, const std::string& str2, char del) const
{
	return generatingStrings(std::move(str), std::move(str2), std::move(del));
}


template <class TypeArray>
constexpr const std::string WORK::Interface<TypeArray>
::generatingStrings(const std::string&& str, const std::string&& str2, char del) const
{
	try {
		size_t len{ str.length() + str2.length() + 11 };
		size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };

		std::string middle(middleSize, del);
		std::string result{ "#    " + str + middle + str2 + "    #\n" };

		return result;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return std::string();
	}
}