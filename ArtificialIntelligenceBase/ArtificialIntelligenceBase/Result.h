#pragma once
/*
 *	函数返回值类 封装了返回值 允许返回异常 常规类型 或者用户自定义类型
 *	注意，如果包含的是用户自定义类型，该类型必须实现了复制构造函数，
 *	否则会产生错误或者只是进行浅拷贝
 */
#include "AIString.h"
#include "DataBuf.h"


class Result
{
public:
	Result(void)
	{
		m_bIsException = false;
	}
	Result(AIString msg){}
	Result(const Result& ret)
	{
		m_bIsException = ret.m_bIsException;
	}
	~Result(void)
	{
	}
public:
	Result& operator<<(const char* msg)
	{
		m_strMsg = msg;
		return *this;
	}
	Result& operator<<(const AIString& msg)
	{
		m_strMsg = msg;
		return *this;
	}
	Result& operator<<(const DataBuf& data)
	{
		m_clsResult = data;
		return *this;
	}
	Result& operator<<(const int& status)
	{
		m_nStatus = status;
		return *this;
	}
	Result& operator<<(const bool& isException)
	{
		m_bIsException = isException;
		return *this;
	}
	Result& operator=(const Result& ret)
	{
		if(this!=&ret)
		{
			m_bIsException = ret.m_bIsException;
			m_strMsg = ret.m_strMsg;
		}
		return *this;
	}
	Result& operator=(const DataBuf& ret)
	{
		m_clsResult = ret;
		return *this;
	}
public:
	DataBuf& getResult(){
		return m_clsResult;
	}
	const DataBuf& getResult() const{
		return m_clsResult;
	}
	int getStatus(){
		return m_nStatus;
	}
	bool hasException(){
		return m_bIsException;
	}
private:
	bool m_bIsException;//true表示返回结果包含异常信息 false表示返回结果没有异常
	AIString m_strMsg;//返回的结果信息
	int m_nStatus;//状态 执行状态
	DataBuf m_clsResult;//返回结果存放的地方
};

