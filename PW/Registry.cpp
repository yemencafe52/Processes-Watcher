#include "pch.h"
#include "Registry.h"

bool Registry::CreateStartUpKey()
{
	bool res = false;

	try
	{
		CSettingsStore reg(TRUE, FALSE);
		
		LPCTSTR path =L"Software\\Microsoft\\Windows\\CurrentVersion\\Run\\";
		LPCTSTR p = L"WP";
		LPCTSTR v = L"1";

		if (!(reg.Open(p)))
		{
			if (reg.CreateKey(p))
			{
				if (reg.Write(p, v))
				{
					res = true;
				}
			}
		}
		

	}
	catch (int e)
	{
	}

	return res;
}

bool Registry::DeleteStartUpKey()
{
	bool res = false;
	try
	{
	}
	catch (int e)
	{
	}
	return res;

}