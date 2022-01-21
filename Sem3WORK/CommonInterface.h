#pragma once

#include <string>
#include <queue>
#include <iostream>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <map>
#include "enums.h"


namespace WORK {
	template <typename TypeContainer>
	class CommonInterface
	{
		std::ostream&						out;						// ����� ������
		size_t								maxTableWidth;				// ������ ��������� ������
		int									maxTableColumnsInArray;		// ���������� ������� ��� ������ �������
		const size_t						maxSize;
		std::queue <std::string>			bufferForStatusBar;			// ������� ��� ������ ����
		Keys								activeKey;					// 
		std::vector <std::string>			bufferForMenu;				// ����� ����
		std::map<HeaderValue, std::string>	headerValue;
	private:
		CommonInterface(const CommonInterface&)					= delete;
		CommonInterface(const CommonInterface&&)				= delete;
		CommonInterface& operator = (const CommonInterface&)	= delete;
		CommonInterface& operator = (const CommonInterface&&)	= delete;


		void generateMenu();

	public:

		CommonInterface();
		constexpr void printErrorKey();
		void addToStatusBar(const std::string& str, StringFormat format = StringFormat::Off);
		void addToStatusBar(const std::string&& str, StringFormat format = StringFormat::Off);
		constexpr  std::string delimiter(char del = '=') const;
		constexpr const std::string generatingStrings(const std::string& str, const std::string& str2 = "", char del = ' ') const;
		constexpr const std::string generatingStrings(const std::string&& str, const std::string&& str2 = "", char del = ' ') const;


		constexpr void showHeader();										// ������� ���������
		constexpr void showMenu();											// ������� ����
		void showStatusBar();												// ������� ���������� �� ������ ����


		void setActiveKey(Keys key);

		constexpr size_t getMaxTableWidth()			const;					// ������� ������ ������������ ����� ������������ ������ � ����������
		constexpr size_t getMaxTableColumns()		const;					// ������� ���������� ������� "�������", ��� ������ ������ ������� � ���-������
		constexpr size_t getMaxSize()				const;					// ������� ���������� ������� "�������", ��� ������ ������ ������� � ���-������

		Keys getActiveKey()							const;					// ������� �������� ���� �������

	};
}


/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
												/* ����������� ������� */



template <class TypeContainer>
WORK::CommonInterface<TypeContainer>
::CommonInterface()
	: out							{ std::cout			}
	, maxTableWidth					{ 110				}
	, maxTableColumnsInArray		{ 5					}
	, maxSize						{ 12				}
	, bufferForStatusBar			{					}
	, activeKey						{ Keys::EmptyKey	}
	, bufferForMenu					{					}
	, headerValue{
		{	HeaderValue::groupName,				"������ ��-11"						},
		{	HeaderValue::WorkName,				"����������� ������"				},
		{	HeaderValue::LastNameStudent,		"������� �.�."						},
		{	HeaderValue::FooterName,			"������� �� ������� � ������� ����"	},
		{	HeaderValue::KeyZeroName,			"�����"														},
		{	HeaderValue::KeyOneName,			"��������� ������� ���������� ������� ������� ������"		},
		{	HeaderValue::KeyTwoName,			"��������� ������� ��������� ����������"					},
		{	HeaderValue::KeyThreeName,			"��������� ������� ���������� ������� �����"				},
		{	HeaderValue::KeyFourName,			"��������� ��������"										},
		{	HeaderValue::KeyFiveName,			"����� ������� ����������"									},
		{	HeaderValue::KeySixName,			"������� ���� �������"										},
		{	HeaderValue::KeySevenName,			"��������� ������� ���������� ������� �������� ����������"	},
		{	HeaderValue::KeyEightName,			"��������� ������� ������� ����� ����� �"					},
		{	HeaderValue::KeyNineName,			"��������� ������� ������� ����� ����� �"					},
		{	HeaderValue::KeyErrorName,			"������� �� ������ �������!"								}
	}
{
	generateMenu();
}


template <class TypeContainer>
void WORK::CommonInterface<TypeContainer>
::generateMenu()
{
	bufferForMenu.emplace_back(delimiter());
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings(headerValue.at(HeaderValue::FooterName)));
	bufferForMenu.emplace_back(delimiter('_'));
	bufferForMenu.emplace_back(delimiter('_'));
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(generatingStrings("( 1 )", headerValue.at(HeaderValue::KeyOneName),		'.'));
	bufferForMenu.emplace_back(generatingStrings("( 2 )", headerValue.at(HeaderValue::KeyTwoName),		'.'));
	bufferForMenu.emplace_back(generatingStrings("( 3 )", headerValue.at(HeaderValue::KeyThreeName),	'.'));
	bufferForMenu.emplace_back(generatingStrings("( 4 )", headerValue.at(HeaderValue::KeyFourName),		'.'));
	bufferForMenu.emplace_back(generatingStrings("( 5 )", headerValue.at(HeaderValue::KeyFiveName),		'.'));
	bufferForMenu.emplace_back(generatingStrings("( 6 )", headerValue.at(HeaderValue::KeySixName),		'.'));
	bufferForMenu.emplace_back(generatingStrings("( 7 )", headerValue.at(HeaderValue::KeySevenName),	'.'));
	bufferForMenu.emplace_back(generatingStrings("( 8 )", headerValue.at(HeaderValue::KeyEightName),	'.'));
	bufferForMenu.emplace_back(generatingStrings("( 9 )", headerValue.at(HeaderValue::KeyNineName),		'.'));
	bufferForMenu.emplace_back(generatingStrings("( 0 )", headerValue.at(HeaderValue::KeyZeroName),		'.'));
	bufferForMenu.emplace_back(delimiter(' '));
	bufferForMenu.emplace_back(delimiter());
}


template <class TypeContainer>
constexpr void WORK::CommonInterface<TypeContainer>
::showMenu()
{
	for (auto&& it : bufferForMenu) out << it;
}


template <class TypeContainer>
constexpr size_t WORK::CommonInterface<TypeContainer>
::getMaxTableWidth() const
{
	return maxTableWidth;
}


template <class TypeContainer>
constexpr size_t WORK::CommonInterface<TypeContainer>
::getMaxTableColumns() const
{
	return maxTableColumnsInArray;
}


template <class TypeContainer>
constexpr size_t WORK::CommonInterface<TypeContainer>
::getMaxSize() const
{
	return maxSize;
}


template <class TypeContainer>
WORK::Keys WORK::CommonInterface<TypeContainer>
::getActiveKey() const
{
	return activeKey;
}


template <class TypeContainer>
void WORK::CommonInterface<TypeContainer>
::setActiveKey(Keys key)
{
	activeKey = key;
}


template <class TypeContainer>
void WORK::CommonInterface<TypeContainer>
::addToStatusBar(const std::string& str, StringFormat format)
{
	addToStatusBar(std::move(str), format);
}


template <class TypeContainer>
void WORK::CommonInterface<TypeContainer>
::addToStatusBar(const std::string&& str, StringFormat format)
{
	if (format == StringFormat::Off) {
		bufferForStatusBar.emplace(std::move(str));
		return;
	}
	std::string hr	{ delimiter()		};
	std::string hr2	{ delimiter(' ')	};

	bufferForStatusBar.emplace(hr);
	bufferForStatusBar.emplace(hr2);
	bufferForStatusBar.emplace(generatingStrings(std::move(str)));
	bufferForStatusBar.emplace(hr2);
	bufferForStatusBar.emplace(hr);
}


template <class TypeContainer>
constexpr void WORK::CommonInterface<TypeContainer>
::showHeader()
{
	std::string hr{ delimiter() };

	out << hr;
	out << generatingStrings(headerValue.at(HeaderValue::WorkName));
	out << delimiter('-');
	out << generatingStrings(headerValue.at(HeaderValue::groupName), headerValue.at(HeaderValue::LastNameStudent));
	out << hr;
}


template <class TypeContainer>
void WORK::CommonInterface<TypeContainer>
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


template <class TypeContainer>
constexpr std::string WORK::CommonInterface<TypeContainer>
::delimiter(char del) const
{
	std::string result(maxTableWidth, del);
	result.at(0) = '#';
	result[result.size() - 2] = '#';
	result.back() = '\n';
	return result;
}


template <class TypeContainer>
constexpr const std::string WORK::CommonInterface<TypeContainer>
::generatingStrings(const std::string& str, const std::string& str2, char del) const
{
	return generatingStrings(std::move(str), std::move(str2), del);
}


template <class TypeContainer>
constexpr const std::string WORK::CommonInterface<TypeContainer>
::generatingStrings(const std::string&& str, const std::string&& str2, char del) const
{
	if (str.empty()) return {};

	try {
		if (str2.empty())		
		{
			int parity{ str.length() % 2 == 0 };
			size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

			std::string middle(middleSize - parity, del);

			return { "#" + middle + str + (parity ? " " : "") + middle + "#\n" };
		}
		else
		{
			size_t len{ str.length() + str2.length() + 11 };
			size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };
			std::string middle(middleSize, del);

			return { "#    " + str + middle + str2 + "    #\n" };
		}
	}
	catch (const std::exception& ex) {
		return ex.what();
	}
}


template <class TypeContainer>
constexpr void WORK::CommonInterface<TypeContainer>
::printErrorKey()
{
	addToStatusBar(headerValue.at(HeaderValue::KeyErrorName), StringFormat::On);
}


