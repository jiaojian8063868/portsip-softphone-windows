/*
    PortSIP
    Copyright (C) 2007 PortSIP Solutions, Inc.
   
    support@portsip.com

    Visit us at http://www.portsip.com
*/


#ifndef PORTSIP_UTILITY_hxx
#define PORTSIP_UTILITY_hxx
#include <locale>
#include <algorithm>
#include "CommonDef.h"
#include "ICUC4/unicode/unistr.h"
#include "ICUC4/unicode/calendar.h"
#include "ICUC4/unicode/datefmt.h"
#include "ICUC4/unicode/smpdtfmt.h"
#include <string>
#include "System/MimeType.h"
#include "atltime.h"
#include "db/DBParam.h"
#include "ShlObj_core.h "
#include <chrono>
#include <cstdint>
using namespace std;
using namespace icu;
template<typename charT>
struct charEqual {
	charEqual(const std::locale& loc) : loc_(loc) {}
	bool operator()(charT ch1, charT ch2) {
		return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
	}
private:
	const std::locale& loc_;
};
template<typename T>
int ci_find_substr(const T& str1, const T& str2, const std::locale& loc = std::locale())
{
	typename T::const_iterator it = std::search(str1.begin(), str1.end(),
		str2.begin(), str2.end(), charEqual<typename T::value_type>(loc));
	if (it != str1.end()) return it - str1.begin();
	else return -1; // not found
}
#define TIMER_START(_X) auto _X##_start =GetTickCount(), _X##_stop = _X##_start
#define TIMER_STOP(_X) _X##_stop = GetTickCount()
#define TIMER_MSEC(_X) (_X##_stop - _X##_start)
class PortUtility
{
public:
	PortUtility();
	virtual ~PortUtility();

public:
	bool getLocalIP(string & ip);
	static void getCurrentlyPath(string & path, bool withSplit = true);
	bool initWinsock();

	string getSelfFullFilePathName();
//	string base64Encode(const string & text);
//	string base64Decode(const string & text);
	static string removePath(const char * filePathName);
	static bool initializeWinsock();
	static bool getPortSIPVpnIp(string & ip);

	static std::string hexEncode(unsigned char * data, int length) ;

	static bool fromHex(const string & str, char * outBuf, int & outBufSize);

	static wchar_t*				 char2Wchar(const char *str);
	static void					 freeWchar(wchar_t* wstr);
	static char*				 wchar2Char(const wchar_t *wstr);
	static	void				 freeChar(char* str);
	static std::wstring			 string2WString(const std::string& s);
	static std::string			 wstring2String(const std::wstring &s);
	static int					 compareStringNoCase(const std::string & s1, const std::string & s2);
	static bool					 IsContainsStr(string strSrc, string strContain);
	
	static TagScreenMetrics		 transVideoResolution(int nVideoResolution);
	static  int                  transVideoBitrate(int nBitrateType);

	static AUDIOCODEC_TYPE getAudioCodecByName(const string & codecName);
	static VIDEOCODEC_TYPE getVideoCodecByName(const string & codecName);

	static void  supersplit(const std::string& s, std::vector<std::string>& v, const std::string& c);
	static bool  isPortAvailable(int nPort);
	static int   findStringLike(std::string strSrc, std::string strKeyString);
	//@PARAM 1+@PARAM2 Format: 2019-08-06 12:22:01 PM
	static void FormatDateTime(std::string strDateTime, std::string &strOutString,ENUM_LANGUAGE enumLanguage);
	//@PARAM 1+@PARAM2 Format: 2019-08-06 12:22:01 GMT+8:00
	static void FormatDateTimeGMT(std::string strDateTime, std::string &strOutString, ENUM_LANGUAGE enumLanguage);
	//sender Format like 77777@sipdomain
	static std::string GetSipNumberBySenderFormatNoSip(std::string strSender);
	//caller Format like sip:102@sipdomian
	//sender Format like sip:77777@sipdomain
	static std::string GetSipNumberBySenderFormat(std::string strSender);
	static ENUM_MSG_TYPE GetMsgTypeByString(std::string strMsgType);
	static CString ansi2Unicode(const char * ansi);
	static void UnicodeToUtf8(CString strUnicode, string strUTF8);
	static std::wstring Utf82Unicode_ND(const std::string& utf8string);
	static string WideByte2Acsi_ND(wstring& wstrcode);
	static string UTF_82ASCII_ND(string& strUtf8Code);
	static wstring Acsi2WideByte_ND(string& strascii);
	static std::string Unicode2Utf8_ND(const std::wstring& widestring);
	static string ASCII2UTF_8_ND(string& strAsciiCode);
	static time_t StringToDatetime(const char *str);
	static std::string UnixTimeToDateTime(time_t time);
	LPCTSTR PortUtility::FileSizeToFormat(DWORD dwSize);
	int GetLocalTimeZone();
	static int gcd2(int w, int h);
	static void CheckFilePath(std::string  strFilePath);
	static std::string  CheckFileExist(std::string strFilePath,std::string strFileName);
	static bool StrIsAllNum(std::string strSearch);

	static vector<string> split2(string str, char del); //��::192:168:ABC::416��->��192 168 ABC 416��
	static std::string getFileExtension(string strFileName);
	static std::string getMimeType(std::string & strEXtension);
	static CIUIString FormatPlayTime(std::string strPlayTime);
	static bool  CheckEmailAddress(CIUIString csEmailAddress);
	static bool CheckExtersionNumber(CIUIString csExtersionNumber);
	static void deleteAllMark(string &s, const string &mark);
	static HRESULT GetShellThumbnailImage(LPCWSTR pszPath, HBITMAP* pThumbnail); 
	static bool stringToLL(const std::string &str, long long &val);
	static bool removeFile(const std::string strFilePath);
	static ENUM_LANGUAGE GetSystemDefaultLang();
};
//





#endif

