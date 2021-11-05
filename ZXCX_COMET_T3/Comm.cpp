#include "pch.h"
#include "Comm.h"

LPCTSTR Strcpy(CString& dBuffc, void* sBuffc)
{
	dBuffc.Format("%s", sBuffc);
	return dBuffc;
}

LPCTSTR Strcpy(CString& dBuffc, void* sBuffc, int slen)
{
	char	buf[256];

	sprintf(buf, "%d", slen);
	dBuffc.Format(buf, sBuffc);
	return dBuffc;
}

int Strlen(void* sBuffc)
{
	return strlen((char*)sBuffc);
}

int MakePack(void* Src, void* Dest, int Slen, char OperMode, int LowNibbleFlg)
{
	BYTE	*bSrc = (BYTE *)Src;
	BYTE	*bDest = (BYTE *)Dest;
	BYTE	Value = 0;
	int		i = 0, j = 0;

	for (i = 0; i < Slen; i++)
	{
		if ((bSrc[i] >= 'a') && (bSrc[i] <= 'f'))
			Value = ((bSrc[i] - 0x57) & 0x0f);
		else
			if ((bSrc[i] >= 'A') && (bSrc[i] <= 'F'))
				Value = ((bSrc[i] - 0x37) & 0x0f);
			else Value = (bSrc[i] & 0x0f);

		if (!LowNibbleFlg)
		{
			if (!(i & 1))
			{
				if (OperMode == '|')
					bDest[j] |= (Value << 4);
				else
					if (OperMode == '^')
						bDest[j] ^= (Value << 4);
					else
						bDest[j] = (bDest[j] & 0x0f) | (Value << 4);
			}
			else
			{
				if (OperMode == '|')
					bDest[j] |= (Value);
				else
					if (OperMode == '^')
						bDest[j] ^= (Value);
					else
						bDest[j] = (bDest[j] & 0xf0) | (Value);
				j++;
			}
		}
		else
		{
			if (i & 1)
			{
				if (OperMode == '|')
					bDest[j] |= (Value << 4);
				else
					if (OperMode == '^')
						bDest[j] ^= (Value << 4);
					else
						bDest[j] = (bDest[j] & 0x0f) | (Value << 4);
			}
			else
			{
				if (OperMode == '|')
					bDest[j] |= (Value);
				else
					if (OperMode == '^')
						bDest[j] ^= (Value);
					else
						bDest[j] = (bDest[j] & 0xf0) | (Value);
				j++;
			}
		}
	}
	return j;
}

int MakeUnPack(void* Src, void* Dest, int Slen, int AscFlg)
{
	BYTE	*bSrc = (BYTE *)Src;
	BYTE	*bDest = (BYTE *)Dest;
	int		i = 0, j = 0;

	for (i = 0; i < Slen; i++)
	{
		if (!AscFlg)											// 0x30 - 0x3f
		{
			bDest[j++] = ((bSrc[i] & 0xf0) >> 4) | '0';
			bDest[j++] = (bSrc[i] & 0x0f) | '0';
		}
		else													// 0x30 - 0x39, 0x41 - 0x46
		{
			bDest[j] = ((bSrc[i] & 0xf0) >> 4) | '0';
			if (bDest[j] >= 0x3a)
				bDest[j] += 0x07;
			j++;

			bDest[j] = (bSrc[i] & 0x0f) | '0';
			if (bDest[j] >= 0x3a)
				bDest[j] += 0x07;
			j++;
		}
	}
	return j;
}

int MakeUnPack(void* Src, CString& Dest, int Slen, int AscFlg)
{
	char str[STRBUFFSIZE];

	memset(str, 0, sizeof(str));
	int i = MakeUnPack(Src, str, Slen, AscFlg);
	Strcpy(Dest, str);
	return i;
}

CString MakeUnPack(void* Src, int Slen, int AscFlg)
{
	CString	cstrstr("");

	MakeUnPack(Src, cstrstr, Slen, AscFlg);
	return cstrstr;
}