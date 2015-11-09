#pragma once
#include <string>
#include <stdarg.h>

class AIString:
	public std::string
{
public:
	AIString() :std::string(){}
	AIString(const char* str) :std::string(){ assign(str); }
	AIString(const wchar_t* str) :std::string(){
		char* tmp = new char[wcslen(str) + 1];
		if (tmp){
			memset(tmp, 0, (size() + 1)*sizeof(wchar_t));
			wcstombs(tmp, str, wcslen(str));
		}
		assign(tmp);
		delete[]tmp;
	}
	AIString(const std::wstring& str){
		char* tmp = new char[str.size() * 3];
		if (tmp != NULL){
			memset(tmp, 0, str.size() * 3);
			wcstombs(tmp, str.c_str(), str.size());
			assign(tmp);
			delete[]tmp;
		}
	}
	~AIString(){}
public:
	AIString& operator=(const std::string& str){
		if (this != &str)
			assign(str);
		return *this;
	}
	AIString& operator=(const char* str){
		assign(str);
		return *this;
	}
	AIString& operator=(const std::wstring& str){
		char* tmp = new char[str.size() * 3];
		if (tmp != NULL){
			memset(tmp, 0,str.size() * 3);
			wcstombs(tmp, str.c_str(), str.size());
			assign(tmp);
			delete[]tmp;
		}
		return *this;
	}
	AIString& operator=(const wchar_t* str){
		char* tmp = new char[wcslen(str) * 3];
		if (tmp != NULL){
			memset(tmp, 0, wcslen(str) * 3);
			wcstombs(tmp, str, wcslen(str));
			assign(tmp);
			delete[]tmp;
		}
		return *this;
	}
	operator std::wstring()
	{
		wchar_t* tmp = new wchar_t[size() + 1];
		if (tmp){
			memset(tmp, 0, (size()+1)*sizeof(wchar_t));
			mbstowcs(tmp, c_str(), size());

		}
		std::wstring ret(tmp);
		delete[]tmp;
		return ret;
	}
	AIString& operator+=(const std::wstring& str){
		char* tmp = new char[str.size() * 3];
		if (tmp != NULL){
			memset(tmp, 0, str.size() * 3);
			wcstombs(tmp, str.c_str(), str.size());
			append(tmp);
			delete[]tmp;
		}
		return *this;
	}
	AIString& operator+=(const wchar_t* str){
		char* tmp = new char[wcslen(str) * 3];
		if (tmp != NULL){
			memset(tmp, 0, wcslen(str) * 3);
			wcstombs(tmp, str, wcslen(str));
			append(tmp);
			delete[]tmp;
		}
		return *this;
	}
	AIString& operator+=(const char* str){
		append(str);
		return *this;
	}
	AIString& operator+=(const std::string& str){
		append(str);
		return *this;
	}
	AIString& operator+=(const AIString& str){
		append(str.c_str());
		return *this;
	}
	bool operator==(const AIString& str){
		if (this == &str)return true;
		return (compare(str) == 0);
	}
	bool operator==(const std::string& str){
		return (compare(str) == 0);
	}
	bool operator==(const char* str){
		return (compare(str) == 0);
	}
	bool operator==(const std::wstring& str){
		bool ret = false;
		char* tmp = new char[str.size() * 3];
		if (tmp != NULL){
			memset(tmp, 0, str.size() * 3);
			wcstombs(tmp, str.c_str(), str.size());
			ret = (compare(tmp)==0);
			delete[]tmp;
		}
		return ret;
	}
public:
	//格式化输入
	//返回0 成功 其他失败
	int format(const char* fmt, ...)
	{
		int ret = 0, len = 1024;
		va_list ap;
		va_start(ap, fmt);
		char* sBuf = NULL;
		do
		{
			sBuf = new char[len];
			if (sBuf == NULL) return -1;
			ret = vsnprintf_s(sBuf, len,len, fmt, ap);
			if (ret >= len){
				len *= 2;
				delete[]sBuf;
				sBuf = NULL;
				va_end(ap);
				continue;
			}
			else if (ret < 0){
				delete[]sBuf;
				sBuf = NULL;
				va_end(ap);
				return -2;
			}
			break;
		} while (ret >= len);
		assign(sBuf);
		delete[]sBuf;
		sBuf = NULL;
		va_end(ap);
		return 0;
	}
	//格式化输出
	//返回转换的个数
	int tovalue(const char* fmt, ...)
	{
		int ret = 0;
		va_list ap;
		va_start(ap, fmt);
		ret = vsscanf(c_str(), fmt, ap);
		va_end(ap);
		return ret;
	}
};

bool operator==(const char* left, const AIString& right)
{
	return (right == left);
}

bool operator==(const std::string& left, const AIString& right)
{
	return (right == left);
}

bool operator==(const std::wstring& left, const AIString& right)
{
	return (right == left);
}