#pragma once
#include <iostream>
#include <sstream>
#include<string>

class DebugString
{
public:
	operator std::string() { return str; }

	DebugString(std::string str = std::string()) : str(str) { ; }

	DebugString(const char* str) : str(str) { ; }

	/// <summary>
	/// ׷�����ݵ�DebugString��
	/// <para>ע���ɱ�κ������ɴ��������������</para>
	/// </summary>
	/// <typeparam name="DataTy">�������͡�</typeparam>
	/// <typeparam name="...ArgsT">�������Ͱ���</typeparam>
	/// <param name="data">���ݡ�</param>
	/// <param name="...args">��������</param>
	/// <returns></returns>
	template <typename DataTy, typename... ArgsT>
	DebugString& Append(DataTy data, ArgsT ...args)
	{
		std::stringstream ss;
		ss << str;
		ss << data;
		str = ss.str();
		return Append(args...);
	}

	DebugString& Append() { return *this; }

	template<typename DataTy>
	DebugString& operator+(DataTy data) { return Append(data); }

	friend inline std::ostream& operator<<(std::ostream& o, DebugString d_str) { return o << (std::string)d_str; }


private:
	std::string str;
};

#define _BRACE(...) ((DebugString("{ ")).Append(##__VA_ARGS__) + " }")
#define _COLON_(st, x) #x, ":", st.x, ", "
#define _COLON(st, x) #x, ":", st.x

#define DEBUG_STR_STRUCT_1(st, m1) _BRACE(_COLON(st, m1))
#define DEBUG_STR_STRUCT_2(st, m1, m2) _BRACE(_COLON_(st, m1), _COLON(st, m2))
#define DEBUG_STR_STRUCT_3(st, m1, m2, m3) _BRACE(_COLON_(st, m1), _COLON_(st, m2), _COLON(st, m3))
#define DEBUG_STR_STRUCT_4(st, m1, m2, m3, m4) _BRACE(_COLON_(st, m1), _COLON_(st, m2), _COLON_(st, m3), _COLON(st, m4))
#define DEBUG_STR_STRUCT_5(st, m1, m2, m3, m4, m5) _BRACE(_COLON_(st, m1), _COLON_(st, m2), _COLON_(st, m3), _COLON_(st, m4), _COLON(st, m5))


