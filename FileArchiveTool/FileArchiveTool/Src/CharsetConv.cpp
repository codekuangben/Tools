#ifdef WIN32
#include <windows.h>		// 暂时先用 windows 自己的转换函数
#endif

#include "CharsetConv.h"
//#include "iconv.h"
#include "FileArchiveToolSys.h"
#include "LogSys.h"
#include "LogStr.h"

#include <string.h>

#include <unicode/ucnv.h> 

BEGIN_NAMESPACE_FILEARCHIVETOOL

// 字节缓冲区大小
#define BYTE_BUFFER_SIZE 2 * 1024 * 1024

CharsetConv::CharsetConv()
{
	m_bytes = new char[BYTE_BUFFER_SIZE];
}

CharsetConv::~CharsetConv()
{
	delete[]m_bytes;
}

//int CharsetConv::convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen)
//{
	// Iconv Begin
	//iconv_t cd;
	//const char **pin = (const char **)&inbuf;
	//char **pout = &outbuf;

	//cd = iconv_open(to_charset, from_charset);
	//if (cd == 0) return -1;
	//memset(outbuf, 0, outlen);
	//if (iconv(cd, pin, (size_t*)&inlen, pout, (size_t*)&outlen) == -1) return -1;
	//iconv_close(cd);
	//return 0;
	// Iconv End
//}

//返回0为成功，错误代码定义见后面  
int CharsetConv::convert(const char* toConverterName, const char* fromConverterName, char* target, int32 targetCapacity, const char* source, int32 sourceLength)
{
	if (sourceLength > targetCapacity)
	{
		FileArchiveToolSysDef->getLogSysPtr()->log(LS_CODE_BUFFER_OVERFLOW);
	}

	UErrorCode error = U_ZERO_ERROR;
	ucnv_convert(toConverterName, fromConverterName, target, targetCapacity, source, sourceLength, &error);

	if (error != U_ZERO_ERROR)		// 编码出错
	{
		FileArchiveToolSysDef->getLogSysPtr()->log(LS_CODE_ERROR);
	}

	return error;
}

// 全局函数，使用 windows 编码解码
// GBK 编码转换到UTF8编码
int CharsetConv::LocalToUtf8(char * lpGBKStr, char * lpUTF8Str, int nUTF8StrLen)
{
#if 0
	wchar_t * lpUnicodeStr = NULL;
	int nRetLen = 0;

	if (!lpGBKStr)  //如果GBK字符串为NULL则出错退出
		return 0;

	nRetLen = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char *)lpGBKStr, -1, NULL, NULL);  //获取转换到Unicode编码后所需要的字符空间长度
	lpUnicodeStr = new WCHAR[nRetLen + 1];  //为Unicode字符串空间
	nRetLen = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char *)lpGBKStr, -1, lpUnicodeStr, nRetLen);  //转换到Unicode编码
	if (!nRetLen)  //转换失败则出错退出
		return 0;

	nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, NULL, 0, NULL, NULL);  //获取转换到UTF8编码后所需要的字符空间长度

	if (!lpUTF8Str)  //输出缓冲区为空则返回转换后需要的空间大小
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return nRetLen;
	}

	if (nUTF8StrLen < nRetLen)  //如果输出缓冲区长度不够则退出
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return 0;
	}

	nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, (char *)lpUTF8Str, nUTF8StrLen, NULL, NULL);  //转换到UTF8编码

	if (lpUnicodeStr)
		delete[]lpUnicodeStr;

	return nRetLen - 1;
#else
	convert("utf-8", "gb2312", lpUTF8Str, nUTF8StrLen, lpGBKStr, strlen(lpGBKStr));
	return strlen(lpUTF8Str);
#endif
}

// UTF8编码转换到GBK编码
int CharsetConv::Utf8ToLocal(char * lpUTF8Str, char * lpGBKStr, int nGBKStrLen)
{
#if 0
	wchar_t * lpUnicodeStr = NULL;
	int nRetLen = 0;

	if (!lpUTF8Str)  //如果UTF8字符串为NULL则出错退出
		return 0;

	nRetLen = ::MultiByteToWideChar(CP_UTF8, 0, lpUTF8Str, -1, NULL, NULL);  //获取转换到Unicode编码后所需要的字符空间长度
	lpUnicodeStr = new WCHAR[nRetLen + 1];  //为Unicode字符串空间
	nRetLen = ::MultiByteToWideChar(CP_UTF8, 0, lpUTF8Str, -1, lpUnicodeStr, nRetLen);  //转换到Unicode编码
	if (!nRetLen)  //转换失败则出错退出
		return 0;

	nRetLen = ::WideCharToMultiByte(CP_ACP, 0, lpUnicodeStr, -1, NULL, NULL, NULL, NULL);  //获取转换到GBK编码后所需要的字符空间长度

	if (!lpGBKStr)  //输出缓冲区为空则返回转换后需要的空间大小
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return nRetLen;
	}

	if (nGBKStrLen < nRetLen)  //如果输出缓冲区长度不够则退出
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return 0;
	}

	nRetLen = ::WideCharToMultiByte(CP_ACP, 0, lpUnicodeStr, -1, lpGBKStr, nRetLen, NULL, NULL);  //转换到GBK编码

	if (lpUnicodeStr)
		delete[]lpUnicodeStr;

	return nRetLen - 1;		// 如果使用 WideCharToMultiByte 函数，返回的长度需要 - 1，如果使用 ICU ，就不用
#else
	convert("gb2312", "utf-8", lpGBKStr, nGBKStrLen, lpUTF8Str, strlen(lpUTF8Str));
	return strlen(lpGBKStr);
#endif
}

char* CharsetConv::Utf8ToLocalStr(char * lpUTF8Str)
{
	memset(m_bytes, 0, BYTE_BUFFER_SIZE);
	Utf8ToLocal(lpUTF8Str, m_bytes, BYTE_BUFFER_SIZE);

	return m_bytes;
}

char* CharsetConv::LocalToUtf8Str(char * lpGBKStr)
{
	memset(m_bytes, 0, BYTE_BUFFER_SIZE);
	LocalToUtf8(lpGBKStr, m_bytes, BYTE_BUFFER_SIZE);

	return m_bytes;
}

int CharsetConv::Utf8ToLocalStrLen(char * lpUTF8Str)
{
	memset(m_bytes, 0, BYTE_BUFFER_SIZE);
	return Utf8ToLocal(lpUTF8Str, m_bytes, BYTE_BUFFER_SIZE);
}

int CharsetConv::LocalToUtf8StrLen(char * lpGBKStr)
{
	memset(m_bytes, 0, BYTE_BUFFER_SIZE);
	return LocalToUtf8(lpGBKStr, m_bytes, BYTE_BUFFER_SIZE);
}

END_NAMESPACE_FILEARCHIVETOOL