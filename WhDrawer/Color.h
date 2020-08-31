#pragma once
#include <iostream>
typedef unsigned long DWORD;
/// <summary>
/// 将RGBA四字节变量转换成BGRA四字节变量。
/// </summary>
/// <param name="rgba">RGBA四字节变量。</param>
/// <returns></returns>
constexpr DWORD BGRA(DWORD rgba) { return ((((rgba) & 0xFF) << 16) | ((rgba) & 0xFF00FF00) | (((rgba) & 0xFF0000) >> 16)); }
/// <summary>
/// 将BGRA四字节变量转换成RGBA四字节变量。
/// </summary>
/// <param name="rgba">BGRA四字节变量。</param>
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
	/// 空颜色值(0)。
	/// </summary>
	/// <returns></returns>
	inline Color() { ; }

	/// <summary>
	/// 构造颜色值。
	/// </summary>
	/// <param name="r">红色分量。</param>
	/// <param name="g">绿色分量。</param>
	/// <param name="b">蓝色分量。</param>
	/// <param name="a">透明度。</param>
	inline Color(BYTE r, BYTE g, BYTE b, BYTE a)
	{ 
		R() = r;
		G() = g;
		B() = b;
		A() = a;
	}

	/// <summary>
	/// 通过四字节变量构造颜色值，重设透明度。
	/// </summary>
	/// <param name="rgb">RGB值。</param>
	/// <param name="a">透明度。</param>
	inline Color(Color rgb, BYTE a) : Color(rgb) { A() = a; }

	/// <summary>
	/// 通过颜色枚举构造颜色值。
	/// </summary>
	/// <param name="color">颜色枚举。</param>
	inline Color(ColorEnum color) { FromBGRA((DWORD)color); }


	//Properties
	/// <summary>
	/// 获取或设置红色分量。
	/// </summary>
	/// <returns>无符号单字节(0-255)引用，表示红色分量值。</returns>
	inline BYTE& R() { return rgba.bytes[0]; }

	/// <summary>
	/// 获取或设置绿色分量。
	/// </summary>
	/// <returns>无符号单字节(0-255)引用，表示绿色分量值。</returns>
	inline BYTE& G() { return rgba.bytes[1]; }

	/// <summary>
	/// 获取或设置蓝色分量。
	/// </summary>
	/// <returns>无符号单字节(0-255)引用，表示蓝色分量值。</returns>
	inline BYTE& B() { return rgba.bytes[2]; }

	/// <summary>
	/// 获取或设置透明度。
	/// </summary>
	/// <returns>无符号单字节(0-255)引用，表示透明度。</returns>
	inline BYTE& A() { return rgba.bytes[3]; }

	/// <summary>
	/// 获取RGBA顺序四字节变量。
	/// </summary>
	/// <returns>无符号四字节变量，颜色顺序为RGBA。</returns>
	inline const DWORD ToRGBA() { return rgba.dword; }

	/// <summary>
	/// 获取BGRA顺序四字节变量。
	/// </summary>
	/// <returns>无符号四字节变量，颜色顺序为BGRA。</returns>
	inline const DWORD ToBGRA() { return BytesDword{ B(), G(), R(), A() }.dword; }

	//Methods
	/// <summary>
	/// 通过RGBA四字节变量设置颜色值。
	/// </summary>
	/// <param name="rgba">RGBA值。</param>
	/// <returns>自身引用</returns>
	inline Color& FromRGBA(DWORD rgba) 
	{ 
		this->rgba.dword = rgba;
		return *this;
	}

	/// <summary>
	/// 通过BGRA四字节变量设置颜色值。
	/// </summary>
	/// <param name="rgba">BGRA值。</param>
	/// <returns>自身引用</returns>
	inline Color& FromBGRA(DWORD bgra) { return FromRGBA(RGBA(bgra)); }

private:
	union BytesDword
	{
		BYTE bytes[4];
		DWORD dword = 0;
	};
	BytesDword rgba;
};

