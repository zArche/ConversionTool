#pragma once
#include <string>
using namespace std;

class Tool
{
public:
	Tool();
	~Tool();

	static unsigned char toHex(char x);
	static unsigned char fromHex(char x);
	static CString urlEncode(CString str);
	static CString urlDecode(CString str);
	static CString sqlEncode(CString str);
	static CString sqlDecode(CString str);
	static CString hexEncode(CString str);
	static CString hexDecode(CString str);
	static CString asciiEncode(CString str);
	static CString asciiDecode(CString str);
	static CString md5Encode(CString str);
	static CString base64Encode(CString str);
	static CString base64Decode(CString str);
};

