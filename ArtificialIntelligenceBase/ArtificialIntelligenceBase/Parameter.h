#pragma once
#include <vector>
#include <stdint.h>
#include "DataBuf.h"
#include "Result.h"

template <class T>
class Convert{
public:
	Convert(const DataBuf& right):m_data(*(const T*)right.get())
	{
	}
	Convert(const Result& ret):
	m_data(*(const T*)ret.getResult().get())
	{
	}
	operator T(){
		return m_data;
	}
private:
	T m_data;
};
#ifndef _CV
#define _CV(tp,x) (tp)Convert<tp>(x)
#endif
#ifndef _D
#define _D(tp,x) declare<tp>(x)
#endif


class CParameter
{
public:
	CParameter(){}
	CParameter(const CParameter& param){
		size_t len = param.size();
		if (len > 0){
			for (size_t i = 0; i < len;i++)
			{
				m_Params.push_back(param[i]);
			}
		}
	}
	~CParameter(){}
public:
	void AddParam(const DataBuf& param){
		m_Params.push_back(param);
	}
	size_t size() const{
		return m_Params.size();
	}
	std::vector<DataBuf>::iterator begin(){
		return m_Params.begin();
	}
	std::vector<DataBuf>::iterator end(){
		return m_Params.end();
	}
	DataBuf& operator[](unsigned nIndex){
		return m_Params[nIndex];
	}
	const DataBuf& operator[](unsigned nIndex) const{
		return m_Params[nIndex];
	}
	CParameter& operator<<(const DataBuf& param)
	{
		m_Params.push_back(param);
		return *this;
	}
	CParameter& operator=(const CParameter& param){
		if (this != &param){
			size_t len = param.size();
			if (len > 0){
				for (size_t i = 0; i < len; i++)
				{
					m_Params.push_back(param[i]);
				}
			}
		}
		return *this;
	}
public:
	std::vector<DataBuf> m_Params;
};

template <class T>
void* copy(void* src,size_t& len){
	len = sizeof(T);
	return (void*)new T(*(T*)src);
}

template <class T>
void del(void* data){
	delete (T*)data;
}

template <class T>
DataBuf declare(const T& data){
	T tmp(data);
	return DataBuf(&tmp,copy<T>,del<T>);
}

template <class T>
CParameter& operator<<(CParameter& paramlst,T param)
{
	paramlst.AddParam(DataBuf(&param,copy<T>,del<T>));
	return paramlst;
}

template <class T>
DataBuf& operator<<(DataBuf& buf,T data)
{
	T* pData = new T(data);
}

template <class T>
bool operator==(const DataBuf& left,const T& right)
{
	return _CV(T, left) == right;
}

template <class T>
bool operator==(const T& left, const DataBuf& right)
{
	return _CV(T, right) == left;
}