#pragma once
/*
 *	��������ֵ�� ��װ�˷���ֵ �������쳣 �������� �����û��Զ�������
 *	ע�⣬������������û��Զ������ͣ������ͱ���ʵ���˸��ƹ��캯����
 *	���������������ֻ�ǽ���ǳ����
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
	bool m_bIsException;//true��ʾ���ؽ�������쳣��Ϣ false��ʾ���ؽ��û���쳣
	AIString m_strMsg;//���صĽ����Ϣ
	int m_nStatus;//״̬ ִ��״̬
	DataBuf m_clsResult;//���ؽ����ŵĵط�
};

