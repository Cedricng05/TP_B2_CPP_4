#include <iostream>
#include <filesystem>
#include <string>
#include "Drive.h"
#include "notif.h"
#include <fstream>
#include "Config.h"

#include <tchar.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <strsafe.h>
#include "resource.h"
#define UNICODE
#include <windows.h>


using namespace std;

// tray icon data
NOTIFYICONDATA m_NID;

BOOL CreateTrayIcon()
{
    memset(&m_NID, 0, sizeof(m_NID));
    m_NID.cbSize = sizeof(m_NID);

    m_NID.uID = IDI_USER_IMAGE;

    // set handle to the window that receives tray icon notifications
    m_NID.hWnd = GetForegroundWindow();

    // fields that are being set when adding tray icon
    m_NID.uFlags = NIF_MESSAGE | NIF_ICON;

    // set image
    m_NID.hIcon = LoadIcon(NULL,MAKEINTRESOURCE(IDI_USER_IMAGE));

    if (!m_NID.hIcon)
        return FALSE;

    m_NID.uVersion = NOTIFYICON_VERSION_4;

    if (!Shell_NotifyIcon(NIM_ADD, &m_NID))
        return FALSE;

    return Shell_NotifyIcon(NIM_SETVERSION, &m_NID);
}

BOOL ShowTrayIconBalloon(LPCTSTR pszTitle, LPCTSTR pszText, UINT unTimeout, DWORD dwInfoFlags)
{
    m_NID.uFlags |= NIF_INFO;
    m_NID.uFlags |= NIF_ICON;
    //m_NID.uFlags |= NIF_ICON | NIF_TIP | NIF_GUID | NIF_MESSAGE;
    m_NID.uTimeout = unTimeout;
    m_NID.dwInfoFlags = dwInfoFlags;

    if (StringCchCopy(m_NID.szInfoTitle, sizeof(m_NID.szInfoTitle), pszTitle) != S_OK)
        return FALSE;

    if (StringCchCopy(m_NID.szInfo, sizeof(m_NID.szInfo), pszText) != S_OK)
        return FALSE;

    return Shell_NotifyIcon(NIM_MODIFY, &m_NID);
}

void notif(){
    CreateTrayIcon();
    ShowTrayIconBalloon("Keyce drive", "Nouvelle cle detecte", 10000, NULL);
}

using namespace std;

filesystem::path source;
filesystem::path targetParent;
void instruction(){

    auto target = targetParent / source.filename();
                 try
                 {
                    create_directories(target);
                    copy(source, target, filesystem::copy_options::recursive);
                 }
                 catch(std::exception& e){
                     std::cout << e.what();
                 }
}

void copyFile(){
    WCHAR myDrives[105];
    WCHAR volumeName[MAX_PATH];
    WCHAR fileSystemName[MAX_PATH];
    DWORD serialNumber, maxComponentLen, fileSystemFlags;
    UINT driveType;

    if (!GetLogicalDriveStringsW(ARRAYSIZE(myDrives) - 1, myDrives))
    {
        wprintf(L"GetLogicalDrives() failed with error code: %lu\n", GetLastError());
    }
    else
    {
        for (LPWSTR drive = myDrives; *drive != 0; drive += 4)
        {
            driveType = GetDriveTypeW(drive);
            if(driveType == DRIVE_REMOVABLE) {
                wprintf(L"\nUSB Drive detected in drive %s\n", drive);
            }
        }
        if(driveType != DRIVE_REMOVABLE) {
             wprintf(L"\nAucun support USB detecte\n");
            }
    }

    /*if(source == "F:\\keyce_drive" && targetParent == "C:\\Users\\Hans Louis\\Desktop\\keyce_drive"){
        instruction();
    }
    else if(source == "C:\\Users\\Hans Louis\\Desktop\\keyce_drive\\" && targetParent == "F:\\"){
        instruction();
    }*/

    // Copy to the USB from Desktop

    //filesystem::path targetParent = "F:\\";
    //filesystem::path source = "C:\\Users\\Hans Louis\\Desktop\\keyce_drive";

    // Copy to Desktop from USB
    filesystem::path source = "F:\\keyce_drive\\EPREUVED_examen.docx";
    filesystem::path targetParent = "C:\\Users\\Hans Louis\\Desktop\\keyce_drive";
     auto target = targetParent / source.filename();
                 try
                 {
                    create_directories(target);
                    copy(source, target, filesystem::copy_options::recursive);
                 }
                 catch(std::exception& e){
                     std::cout << e.what();
                 }

    ifstream src ("F:\\keyce_drive", ios::binary);
    ofstream dst ("C:\\Users\\Desktop\\keyce_drive\\", ios::binary);
    dst << src.rdbuf();
}

void onlyThat(){

    // Path to the file
    char* filepath = "F:\\keyce_drive\\";

    // Passing the path as argument to the function
    filesystem::path p(filepath);
    cout <<p.filename();
    p.extension() = ".pdf", ".mp4", ".mp3", ".pptx", ".jpg", ".png", ".gif";

    if (p.extension() != ".pdf" || p.extension() !=".mp4" || p.extension() !=".mp3" || p.extension() !=".pptx" || p.extension() !=".jpg" || p.extension() !=".png" || p.extension() !=".gif") {
         cout << "Error to copy, cause extension form" << endl;
    }
    else{
        copyFile();
    }
}
/*void modTime(){

    FILETIME ft;
    SYSTEMTIME st;
    if(!ft){
        copyFile();
    }
}*/
int compareFile(FILE* f1, FILE* f2){
    int N = 10000;
    char buf1[N], buf2[N];

    do {
        size_t r1 = fread(buf1, 1,  N, f1);
        size_t r2 = fread(buf2, 1,  N, f2);

        if (r1 != r2 || memcmp(buf1, buf2, r1)){
            copyFile();
            return 0;
        }

    } while (!feof(f1) || !feof(f2));

  return 1;
}
using namespace std;

int main()
{
    Drive d;
    d.detect();
//    d.sync('G');
//    notif();
    copyFile();
    onlyThat();
    Config c;
    c.create();
    //c.readRecord();
    return 0;
}
