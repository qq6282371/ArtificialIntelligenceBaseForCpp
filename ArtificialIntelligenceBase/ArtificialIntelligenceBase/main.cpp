#include "gtest\gtest.h"
#include "AIString.h"
#include "Parameter.h"


int main(int argc, char**argv, char**env)
{
	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	getchar();
	return ret;
}

TEST(testAIBase, testParam)
{//���������࣬���ɸ��ֲ���
	CParameter param;
	param << 1 << 1.3f << 9.3 << 'c'<<AIString("abc");
	EXPECT_EQ(1, param[0]);
	EXPECT_EQ(1.3f, param[1]);
	EXPECT_EQ(9.3, param[2]);
	EXPECT_EQ('c', param[3]);
	EXPECT_EQ(std::string("abc"), param[4]);
	EXPECT_STREQ("abc", _CV(char*,param[4]));
	EXPECT_EQ(5, param.size());
	
}

TEST(testAIBase, testString)
{//֧�ָ��ơ���ֵ�����졢���ַ����ַ�����ƥ�䡢��������
	AIString str,str1,str2("cdef");
	str = "abc";
	str1 = str;
	EXPECT_STREQ("abc", str.c_str());
	EXPECT_STREQ("abc", str1.c_str());
	EXPECT_STREQ("cdef", str2.c_str());
	str1.format("%d", str.size());
	EXPECT_STREQ("3", str1.c_str());
	str2 = "abc" + str;
	EXPECT_STREQ("abcabc", str2.c_str());
	str2 += "abc";
	EXPECT_STREQ("abcabcabc", str2.c_str());
	str2 = std::string("abc");
	str2 += std::string("def");
	EXPECT_STREQ("abcdef", str2.c_str());
	std::wstring wstr(L"abc"), wstr1(L"def");
	EXPECT_TRUE((std::wstring)str == wstr);
	str1 = wstr1;
	EXPECT_TRUE((std::wstring)str1 == wstr1);
	str1 += wstr1;
	EXPECT_STREQ("defdef", str1.c_str());
}