
// PW.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "PW.h"
#include "PWDlg.h"
#include <string>
#include "Settings.h"
#include "Registry.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPWApp

BEGIN_MESSAGE_MAP(CPWApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


bool MCP(std::wstring& name);

bool ECP(int pid);

// CPWApp construction

CPWApp::CPWApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPWApp object

CPWApp theApp;


// CPWApp initialization
//CPWDlg* dlg = nullptr;
BOOL CPWApp::InitInstance()
{	

	Registry r;
	r.CreateStartUpKey();
	unsigned int sec = 0;
	unsigned unsigned tick = 0;
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, L"PW");

	if (!hMutex)
		// Mutex doesn’t exist. This is
		// the first instance so create
		// the mutex.
		hMutex = CreateMutex(0, 0, L"PW");
	else
	{
		MessageBox(0, L"This App is running now.", L"PW", MB_OK | MB_ICONEXCLAMATION);
		// The mutex exists so this is the
		// the second instance so return.
		CloseHandle(hMutex);
		exit(0);
		return 0;
	}
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("PW"));

	Param p;
	while (p.ErrorNo()!= 0)
	{	
		CPWDlg dlg;
		dlg.DoModal();
		p = Param();
	}
	
	sec = p.Second();
	std::vector<std::wstring> name = p.Processes();

	while (true)
	{

		if ((GetTickCount64() - tick) > (1000 * sec))
		{
			for (int i = 0; i < name.size(); i++)
			{
				std::wstring n = name[i];	
				MCP(n);
			}

			tick = GetTickCount64();
		}

		if (((GetAsyncKeyState(VK_F2) & 1)) && (((GetAsyncKeyState(VK_F7) & 1))))
		//if ((GetKeyState(0xA0) > 0) && ((GetKeyState(0xA2)>0)))
		{

			CPWDlg dlg;
			dlg.DoModal();
			
			Param p;
			sec = p.Second();
			name = p.Processes();
		}

		Sleep(100);
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}










//
//HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, "PW");
//unsigned unsigned tick = 0;
//
//if (!hMutex)
//// Mutex doesn’t exist. This is
//// the first instance so create
//// the mutex.
//hMutex = CreateMutex(0, 0, "PW");
//else
//{
//	MessageBox(0, "This App is running now.", "PW", MB_OK | MB_ICONEXCLAMATION);
//	// The mutex exists so this is the
//	// the second instance so return.
//	CloseHandle(hMutex);
//	exit(0);
//	return 0;
//}
//
//std::string path[255];
//memset(path, 0, 255);
//
//GetCurrentDirectory(255, (LPSTR)path);
//std::string filePath((char*)&path[0]);
//
//filePath += "\\config.ini" + NULL;
////MessageBox(0,(LPCSTR)(&filePath[0]),"", MB_OK | MB_ICONEXCLAMATION);
////memcpy((fp+res),fn,8); 
////const char *file = fp;
//
//HANDLE hFile = INVALID_HANDLE_VALUE;
//hFile = CreateFile((LPCSTR)&filePath[0],               // file name 
//	GENERIC_READ,          // open for reading 
//	0,                     // do not share 
//	NULL,                  // default security 
//	OPEN_EXISTING,         // existing file only 
//	FILE_ATTRIBUTE_NORMAL, // normal file 
//	NULL);                 // no template 
//if (hFile == INVALID_HANDLE_VALUE)
//{
//	MessageBox(0, "OOPS, CAN'T OPEN CONFIG FILE 00 :(.", "PW", MB_OK | MB_ICONEXCLAMATION);
//	CloseHandle(hMutex);
//	exit(0);
//}
//
//char data[1024] = { 0 };
//unsigned long byte_to_read = 0;
//
//if (!(ReadFile(hFile, &data[0], 1024, &byte_to_read, 0)))
//{
//	MessageBox(0, "OOPS, CAN'T OPEN CONFIG FILE :(.", "PW", MB_OK | MB_ICONEXCLAMATION);
//	CloseHandle(hFile);
//	CloseHandle(hMutex);
//	exit(0);
//}
//
//CloseHandle(hFile);
//
//int size = 0;
//int sec = 0;
//int index = 0;
//
//sec = *(int*)data;
//index += 4;
//
//size = *(int*)(data + 4);
//index += 4;
//
//char* process = new char[size + 1];
//memset(process, 0, size + 1);
//memcpy(process, (data + index), size);
//
//tick = GetTickCount64();
//while (true)
//{
//	if ((GetTickCount64() - tick) > (1000 * sec))
//	{
//		std::string name("notepad.exe");
//		//const char *name = "notepad.exe";
//		MCP(name);
//		//MessageBox(0,"HELLO WORLD","PW", MB_OK | MB_ICONEXCLAMATION);
//		tick = GetTickCount64();
//	}
//
//	/*if ((GetKeyState(0xA0)) && ((GetKeyState(0xA2)))  && ((GetKeyState(0x74))))
//	{
//		MessageBox(0,"Byte","PW", MB_OK | MB_ICONEXCLAMATION);
//		CloseHandle(hMutex);
//		exit(0);
//	}*/
//	Sleep(100);
//}
//
//CloseHandle(hMutex);
//return 0;
//
//}
//


#include <tlhelp32.h>


bool MCP(std::wstring& name)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			
			std::wstring nm(entry.szExeFile);
			if ((nm == name))
			{
				ECP(entry.th32ProcessID);
				CloseHandle(snapshot);
				return true;
			}

		}
	}

	CloseHandle(snapshot);
	return false;
}


bool ECP(int pid)
{
	HANDLE hProcess = NULL;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	return TerminateProcess(hProcess, 0);
}