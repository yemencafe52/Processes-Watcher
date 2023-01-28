#include "pch.h"
#include "Settings.h"

Param::Param(unsigned int sec, std::vector<std::wstring>& processes):sec(sec), processes(processes)
{
}

Param::Param()
{
	CString config = L"";
	CString tmp = 0;
	wchar_t buffer[512] = { 0 };
	DWORD fz;

	unsigned int sec = 0;
	unsigned int index = 0;
	unsigned int count = 0;

	try
	{
		GetCurrentDirectoryW(512, (LPWSTR)(&buffer[0]));
		config = buffer;
		config += "\\pwdb";

		if (PathFileExistsW(config))
		{
			HANDLE hFile = INVALID_HANDLE_VALUE;
			hFile = CreateFile((LPCWSTR)config,               // file name 
				GENERIC_READ,          // open for reading 
				0,                     // do not share 
				NULL,                  // default security 
				OPEN_EXISTING,         // existing file only 
				FILE_ATTRIBUTE_NORMAL, // normal file 
				NULL);
			// no template 
			if (hFile == INVALID_HANDLE_VALUE)
			{
				throw 1;
			}


			fz = GetFileSize(hFile, 0);
			char* data = new char[fz];
			unsigned long byte_to_read = 0;

			if (!(ReadFile(hFile, &data[0], 1024, &byte_to_read, 0)))
			{
				CloseHandle(hFile);
				throw 1;

			}

			CloseHandle(hFile);

			sec = *(int*)data + index;
			index += 4;

			this->sec = sec;

			count = 0;
			count = *(int*)(data + index);
			index += 4;

			for (int i = 0; i < count; i++)
			{
				unsigned int len = 0;
				len = (((*(int*)(data + index))) + 2);

				index += 4;
				wchar_t* buff = new wchar_t[len];
				memset(buff, 0, ((len)));

				memcpy(buff, (data + index), ((len)-2));
				index += (len - 2);

				std::wstring p(buff);
				processes.push_back(p);

			}

			delete data;
			return;
		}

		throw 1;
	}
	catch (int e)
	{
		this->error_no = e;
	}
}

unsigned int Param::Second()
{
	return this->sec;
}

std::vector<std::wstring>& Param::Processes()
{
	return this->processes;
}

bool Param::SaveToDisk()
{
	bool res = false;

	try
	{

		std::wstring tmp;
		//unsigned sec = 0;
		unsigned int count = 0;
		char* data = 0;
		std::wstring config = L"";
		wchar_t buffer[512] = { 0 };
		HANDLE hFile = INVALID_HANDLE_VALUE;
		std::vector<char> ar;
		DWORD rtb = 0;
		unsigned long byte_to_read = 0;
		///////////////////////////////

		if (!(sec > 0))
		{
			throw 1;
		}

		if ((sec > 99999))
		{
			throw 1;
		}

		data = (char*)(&sec);

		ar.clear();
		ar.insert(ar.begin(), data, data + 4);

		count = processes.size();
		data = (char*)&count;

		ar.insert(ar.end(), data, data + 4);

		for (int i = 0; i < processes.size(); i++)
		{
			tmp = processes[i];

			unsigned int txt_count = processes[i].length() * 2;
			data = (char*)&txt_count;

			ar.insert(ar.end(), data, data + 4);

			data = (char*)tmp.data();

			ar.insert(ar.end(), data, data + txt_count);
		}


		GetCurrentDirectoryW(512, (LPWSTR)(&buffer[0]));
		config = buffer;

		config += std::wstring(L"\\pwdb");

		if (PathFileExistsW((LPCTSTR)&config[0]))
		{
			DeleteFileW((LPCTSTR)&config[0]);
		}

		hFile = CreateFile((LPCWSTR)&config[0],               // file name 
			GENERIC_WRITE,          // open for reading 
			0,                     // do not share 
			NULL,                  // default security 
			CREATE_NEW,         // existing file only 
			FILE_ATTRIBUTE_NORMAL, // normal file 
			NULL);
		// no template 
		if (hFile == INVALID_HANDLE_VALUE)
		{
			throw 1;
		}

	    byte_to_read = 0;
		count = ar.size();
		data = ar.data();
	    rtb = 0;

		if (!(WriteFile(hFile, data, count, &rtb, 0)))
		{
			CloseHandle(hFile);
			throw 1;
		}

		CloseHandle(hFile);
		res = true;

	}
	catch(int e)
	{
		this->error_no = 1;
		res = false;
	}

	return res;
}

Param::~Param() {
	//SaveToDisk();
}

int Param::ErrorNo()
{
	return this->error_no;
}