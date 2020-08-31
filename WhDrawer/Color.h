#pragma once
#include <iostream>
typedef unsigned long DWORD;
/// <summary>
/// ��RGBA���ֽڱ���ת����BGRA���ֽڱ�����
/// </summary>
/// <param name="rgba">RGBA���ֽڱ�����</param>
/// <returns></returns>
constexpr DWORD BGRA(DWORD rgba) { return ((((rgba) & 0xFF) << 16) | ((rgba) & 0xFF00FF00) | (((rgba) & 0xFF0000) >> 16)); }
/// <summary>
/// ��BGRA���ֽڱ���ת����RGBA���ֽڱ�����
/// </summary>
/// <param name="rgba">BGRA���ֽڱ�����</param>
/// <returns></returns>
constexpr DWORD RGBA(DWORD bgra) { return BGRA(bgra); }

enum class ColorEnum : DWORD
{
	BLACK			= 0		   ,
	BLUE			= 0xAA0000 ,
	GREEN			= 0x00AA00 ,
	CYAN			= 0xAAAA00 ,
	RED				= 0x0000AA ,
	MAGENTA			= 0xAA00AA ,
	BROWN			= 0x0055AA ,
	LIGHTGRAY		= 0xAAAAAA ,
	DARKGRAY		= 0x555555 ,
	LIGHTBLUE		= 0xFF5555 ,
	LIGHTGREEN		= 0x55FF55 ,
	LIGHTCYAN		= 0xFFFF55 ,
	LIGHTRED		= 0x5555FF ,
	LIGHTMAGENTA	= 0xFF55FF ,
	YELLOW			= 0x55FFFF ,
	WHITE			= 0xFFFFFF ,
};


struct Color
{
public:
	using BYTE = unsigned char;
	using DWORD = unsigned long;

	//Constructor
	/// <summary>
	/// ����ɫֵ(0)��
	/// </summary>
	/// <returns></returns>
	inline Color() { ; }

	/// <summary>
	/// ������ɫֵ��
	/// </summary>
	/// <param name="r">��ɫ������</param>
	/// <param name="g">��ɫ������</param>
	/// <param name="b">��ɫ������</param>
	/// <param name="a">͸���ȡ�</param>
	inline Color(BYTE r, BYTE g, BYTE b, BYTE a)
	{ 
		R() = r;
		G() = g;
		B() = b;
		A() = a;
	}

	/// <summary>
	/// ͨ�����ֽڱ���������ɫֵ������͸���ȡ�
	/// </summary>
	/// <param name="rgb">RGBֵ��</param>
	/// <param name="a">͸���ȡ�</param>
	inline Color(Color rgb, BYTE a) : Color(rgb) { A() = a; }

	/// <summary>
	/// ͨ����ɫö�ٹ�����ɫֵ��
	/// </summary>
	/// <param name="color">��ɫö�١�</param>
	inline Color(ColorEnum color) { FromBGRA((DWORD)color); }


	//Properties
	/// <summary>
	/// ��ȡ�����ú�ɫ������
	/// </summary>
	/// <returns>�޷��ŵ��ֽ�(0-255)���ã���ʾ��ɫ����ֵ��</returns>
	inline BYTE& R() { return rgba.bytes[0]; }

	/// <summary>
	/// ��ȡ��������ɫ������
	/// </summary>
	/// <returns>�޷��ŵ��ֽ�(0-255)���ã���ʾ��ɫ����ֵ��</returns>
	inline BYTE& G() { return rgba.bytes[1]; }

	/// <summary>
	/// ��ȡ��������ɫ������
	/// </summary>
	/// <returns>�޷��ŵ��ֽ�(0-255)���ã���ʾ��ɫ����ֵ��</returns>
	inline BYTE& B() { return rgba.bytes[2]; }

	/// <summary>
	/// ��ȡ������͸���ȡ�
	/// </summary>
	/// <returns>�޷��ŵ��ֽ�(0-255)���ã���ʾ͸���ȡ�</returns>
	inline BYTE& A() { return rgba.bytes[3]; }

	/// <summary>
	/// ��ȡRGBA˳�����ֽڱ�����
	/// </summary>
	/// <returns>�޷������ֽڱ�������ɫ˳��ΪRGBA��</returns>
	inline const DWORD ToRGBA() { return rgba.dword; }

	/// <summary>
	/// ��ȡBGRA˳�����ֽڱ�����
	/// </summary>
	/// <returns>�޷������ֽڱ�������ɫ˳��ΪBGRA��</returns>
	inline const DWORD ToBGRA() { return BytesDword{ B(), G(), R(), A() }.dword; }

	//Methods
	/// <summary>
	/// ͨ��RGBA���ֽڱ���������ɫֵ��
	/// </summary>
	/// <param name="rgba">RGBAֵ��</param>
	/// <returns>��������</returns>
	inline Color& FromRGBA(DWORD rgba) 
	{ 
		this->rgba.dword = rgba;
		return *this;
	}

	/// <summary>
	/// ͨ��BGRA���ֽڱ���������ɫֵ��
	/// </summary>
	/// <param name="rgba">BGRAֵ��</param>
	/// <returns>��������</returns>
	inline Color& FromBGRA(DWORD bgra) { return FromRGBA(RGBA(bgra)); }

private:
	union BytesDword
	{
		BYTE bytes[4];
		DWORD dword = 0;
	};
	BytesDword rgba;
};

