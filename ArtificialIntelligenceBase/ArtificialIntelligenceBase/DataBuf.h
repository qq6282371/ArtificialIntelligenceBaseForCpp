#pragma once

typedef void* (*COPYFUNC)(void*,size_t&);
typedef void (*DELFUNC)(void*);

class DataBuf{
public:
	DataBuf(){
		m_buf = NULL;
		m_len = 0;
		m_copy = NULL;
	}
	DataBuf(const DataBuf& buf){
		if (buf.m_buf != NULL && (buf.m_len != 0) && (buf.m_copy != NULL))
		{
			m_buf = buf.getCopy(m_len);
			if (m_buf != NULL){
				m_copy = buf.m_copy;
				m_free = buf.m_free;
			}
		}
		else{
			m_buf = NULL;
			m_len = 0;
			m_copy = NULL;
			m_free = NULL;
		}
	}
	DataBuf(void* buf,COPYFUNC copyFunc,DELFUNC freeFunc){
		m_buf = NULL;
		m_len = 0;
		m_copy = NULL;
		m_free = freeFunc;
		if(copyFunc!=NULL){
			m_buf = copyFunc(buf,m_len);
			if (m_buf != NULL){
				m_copy = copyFunc;
			}
		}
	}
	~DataBuf(){
		if (m_buf != NULL && m_free != NULL){
			m_free(m_buf);
			m_buf = NULL;
		}
		if (m_len != 0)m_len = 0;
	}
	void* get(){
		return m_buf;
	}
	const void* get()const {
		return m_buf;
	}
public:
	DataBuf& operator=(const DataBuf& buf){
		if (this != &buf){
			if (m_buf != NULL){
				m_free(m_buf);
				m_buf = NULL;
				m_free = NULL;
			}
			if (m_len != 0)m_len = 0;
			if (buf.m_buf != NULL && (buf.m_len != 0) && (buf.m_copy != NULL))
			{
				m_buf = buf.getCopy(m_len);
				if (m_buf != NULL){
					m_copy = buf.m_copy;
					m_free = buf.m_free;
				}
			}
		}
		return *this;
	}
protected:
	void* getCopy(size_t& len) const{
		return m_copy(m_buf,len);
	}
private:
	void* m_buf;
	size_t m_len;
	COPYFUNC m_copy;
	DELFUNC m_free;
};