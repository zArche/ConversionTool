#include "stdafx.h"
#include "Tool.h"
#include "md5.h"

Tool::Tool()
{
}


Tool::~Tool()
{
}

CString Tool::urlEncode(CString str) {
	CString strTemp;
	int length = str.GetLength();
	for (int i = 0; i < length; i++)
	{
		strTemp += '%';
		strTemp += toHex((unsigned char)str[i] >> 4);
		strTemp += toHex((unsigned char)str[i] % 16);
	
	}
	return strTemp;
}

CString Tool::urlDecode(CString str)
{
	CString strTemp;
	for (int i = 0; i < str.GetLength(); i++)
	{
		char ch = 0;
		if (str[i] == '%')
		{
			ch = (fromHex(str[++i]) << 4);
			ch |= fromHex(str[++i]);
		}
		else
			ch = str[i];
		strTemp += (char)ch;
	}
	return strTemp;
}

unsigned char Tool::toHex(char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

unsigned char Tool::fromHex(char x)
{
	return isdigit(x) ? x - '0' : x - 'A' + 10;
}


CString Tool::sqlEncode(CString str) {
	if (str.GetLength()<=0)
	{
		return str;
	}
	CString strTemp;
	int length = str.GetLength();
	strTemp += "0x";
	for (int i = 0; i < length; i++)
	{
		strTemp += toHex((unsigned char)str[i] >> 4);
		strTemp += toHex((unsigned char)str[i] % 16);
		strTemp += "00";

	}
	return strTemp;
}

CString Tool::sqlDecode(CString str)
{
	CString strTemp;
	for (int i = 0; i < str.GetLength(); i++)
	{
		char ch = 0;
		if (str[i] == '0') //00 0x开头
		{
			if (str[i+1] == 'x' || str[i+1] == '0')
			{	
				i++;
				if (i+2 < str.GetLength())
				{
					ch = (fromHex(str[++i]) << 4);
					ch |= fromHex(str[++i]);

				}

			}

		}
		else
			ch = str[i];
		strTemp += (char)ch;
	}
	return strTemp;
}

CString Tool::hexEncode(CString str) {
	if (str.GetLength() <= 0)
	{
		return str;
	}
	CString strTemp;
	int length = str.GetLength();
	strTemp += "0x";
	for (int i = 0; i < length; i++)
	{
		strTemp += toHex((unsigned char)str[i] >> 4);
		strTemp += toHex((unsigned char)str[i] % 16);

	}
	return strTemp;
}

CString Tool::hexDecode(CString str)
{
	CString strTemp;
	bool flag = false;
	for (int i = 0; i < str.GetLength(); i++)
	{
		char ch = 0;
		if (str[i] == '0' && str[i + 1] == 'x') //0x
		{
			i++;
			flag = true;
			continue;
		}
		else if(flag){
			ch = (fromHex(str[i]) << 4);
			ch |= fromHex(str[++i]);
		}
		strTemp += (char)ch;
	}
	return flag?strTemp:str;
}

CString Tool::asciiEncode(CString str) {
	CString strTemp;
	int length = str.GetLength();
	char c[255] = { 0 };
	for (int i = 0; i < length; i++)
	{
		int asc = str[i];
		CString c;
		c.Format(L"%d",asc);
		strTemp += c;
		strTemp += ' ';

	}
	return strTemp;
}

static void StringSplit(CString source, CStringArray& dest, char division)
{
	dest.RemoveAll();
	for (int i = 0;i< source.GetLength();i++)
	{
		if (source.GetAt(i) == division)
		{
			dest.Add(source.Left(i));
			for (int j = 0;j<(dest.GetSize() - 1);j++)
			{
				dest[dest.GetSize() - 1] = dest[dest.GetSize() - 1].Right(dest[dest.GetSize() - 1].GetLength() - dest[j].GetLength() - 1);  //去掉左边   
			}
		}
	}
}

CString Tool::asciiDecode(CString str)
{
	CString strTemp;
	CStringArray strArray;
	StringSplit(str, strArray,' ');
	if (strArray.GetSize()<=0)
	{
		int asc = _ttoi(str);
		if (asc!=0)
			return strTemp+(char)asc;
		else
			return str;
	}
	for (int i = 0; i < strArray.GetSize(); i++)
	{
		CString cstr = strArray.GetAt(i);
		int asc = _ttoi(cstr);
		strTemp += (char)asc;

	}
	return strTemp;
}

CString Tool::md5Encode(CString str) {
	CString strTemp;

	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, str, -1, ptxtTemp, len, NULL, NULL);
	string md5 = MD5(ptxtTemp).toString();
	strTemp += md5.c_str();
	delete[] ptxtTemp;
	return strTemp;
}

CString Tool::base64Encode(CString str) {
	if (str.GetLength() <= 0)
	{
		return str;
	}
	CString strTemp;

	//编码表
	const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//返回值
	string strEncode;
	unsigned char Tmp[4] = { 0 };
	int LineLength = 0;
	int index = 0;
	for (int i = 0;i<=str.GetLength()-3;)
	{
		Tmp[1] = str[i++];
		Tmp[2] = str[i++];
		Tmp[3] = str[i++];
		strEncode += EncodeTable[Tmp[1] >> 2];
		strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode += EncodeTable[Tmp[3] & 0x3F];
		if (LineLength += 4, LineLength == 76) { strEncode += "\r\n";LineLength = 0; }
		index = i;
	}
	//对剩余数据进行编码
	int Mod = str.GetLength() % 3;
	if (Mod == 1)
	{
		Tmp[1] = str[str.GetLength()-1];
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode += "==";
	}
	else if (Mod == 2)
	{
		Tmp[1] = str[str.GetLength()-2];
		Tmp[2] = str[str.GetLength()-1];
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode += EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode += "=";
	}

	return strTemp + strEncode.c_str();

}

CString Tool::base64Decode(CString str)
{
	if (str.GetLength() <= 0)
	{
		return str;
	}
	CString strTemp;
	//解码表
	const char DecodeTable[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62, // '+'
		0, 0, 0,
		63, // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
	};
	//返回值
	string strDecode;
	int nValue;
	int i = 0;
	while (i <= str.GetLength()-4)
	{
		if (str[i] != '\r' && str[i] != '\n')
		{
			nValue = DecodeTable[str[i++]] << 18;
			nValue += DecodeTable[str[i++]] << 12;
			strDecode += (nValue & 0x00FF0000) >> 16;
			if (str[i] != '=')
			{
				nValue += DecodeTable[str[i++]] << 6;
				strDecode += (nValue & 0x0000FF00) >> 8;
				if (str[i] != '=')
				{
					nValue += DecodeTable[str[i++]];
					strDecode += nValue & 0x000000FF;

				}
			}
		}
		else// 回车换行,跳过
		{
			i++;
		}
	}
	return strTemp + strDecode.c_str();
}
