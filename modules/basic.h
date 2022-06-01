/*
Web Class Helper Basic Module Header File 2.0.1
This source code file is under MIT License.
Copyright (c) 2022 Class Tools Develop Team
Contributors: jsh-jsh ren-yc
*/
#ifndef BASIC_H
#define BASIC_H
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cuchar>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <shared_mutex>
#include <any>
#include <charconv>
#include <filesystem>
#include <optional>
#include <memory_resource>
#include <string_view>
#include <variant>
#include <bit>
#include <compare>
#include <concepts>
#include <coroutine>
#include <numbers>
#include <ranges>
#include <span>
#include <stop_token>
#include <version>
#include <io.h>
#include <windows.h>
#include <wininet.h>
#include <tlhelp32.h>
#include <conio.h>
#include <direct.h>
#include <VersionHelpers.h>
#include <gdiplus.h>
#include "file-process.h"
#include "init.h"
#include "commands.h"
#include "functions.h"
#include "apis.h"

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "gdiplus.lib")
#pragma comment (lib, "urlmon.lib")

using std::cin;
using std::cout;
using std::endl;
using std::format;
using std::getline;
using std::to_string;
using std::to_wstring;
using std::string;
using std::wstring;
using std::ifstream;
using std::ofstream;
using std::map;
using std::set;
using std::vector;
using std::multimap;
using std::function;
using std::pair;
using std::stringstream;
using std::thread;
using std::runtime_error;
using std::ios;
using std::make_pair;
using std::equal_range;

#define WCH_IDM_SHOWHIDE 11461
#define WCH_IDM_EXIT 11462
#define WCH_IDM_OPENPIC 11463
#define WCH_ERRNO_UNCORRECT 0
#define WCH_ERRNO_NETWORK_FAILURE 1
#define WCH_ERRNO_FILE_NOT_FOUND 2
#define WCH_ERRNO_CLOCK_OPERATION 3
#define WCH_ERRNO_TASK_OPERATION 4
#define WCH_ERRNO_WORK_OPERATION 5
#define WCH_ERROR_DPI_GET_FAILED 6
#define WCH_LOG_STATUS_INFO "[INFO]"
#define WCH_LOG_STATUS_DEBUG "[DEBUG]"
#define WCH_LOG_STATUS_WARN "[WARN]"
#define WCH_LOG_STATUS_ERROR "[ERROR]"

class GdiplusWrapper {
public:
	GdiplusWrapper() {
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
	~GdiplusWrapper() {
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
		UINT num = 0;
		UINT size = 0;
		Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;
		Gdiplus::GetImageEncodersSize(&num, &size);
		if (size == 0) {
			return -1;
		}
		pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
		if (pImageCodecInfo == NULL) {
			return -1;
		}
		Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
		for (UINT j = 0; j < num; j++) {
			if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;
			}
		}
		free(pImageCodecInfo);
		return -1;
	}
	void SaveImage(HBITMAP hBitmap, const WCHAR* filename, const WCHAR* format) {
		CLSID pngClsid;
		Gdiplus::Bitmap bitmap(hBitmap, NULL);
		GetEncoderClsid(format, &pngClsid);
		bitmap.Save(filename, &pngClsid);
	}
private:
	ULONG_PTR gdiplusToken;
};

class CTrayIcon {
public:
	CTrayIcon() {};
	~CTrayIcon() {};
	BOOL CreateTray(HWND, HICON, UINT, LPCTSTR = L"Web Class Helper");
	BOOL ChangeTray(LPCTSTR, LPCTSTR = L"Web Class Helper", UINT = 3000);
	BOOL DeleteTray();
private:
	NOTIFYICONDATAW m_Notify;
};

struct WCH_Time {
	int Year {};
	int Month {};
	int Day {};
	int Hour {};
	int Minute {};
	int Second {};
	int WeekDay {};
	string Name {};
};

struct WCH_Data_Body {
	int H {};
	int M {};
};

struct WCH_Version {
	int X {};
	int Y {};
	int Z {};
};

struct MyNotify {
	MyNotify(HWND hWND, WCHAR* Path = (WCHAR*)L"WCH.ico", WCHAR* Title = (WCHAR*)L"Web Class Helper", UINT uID = 1) {
		NOTIFYICONDATAW nID = {};
		nID.hIcon = (HICON)LoadImageW(NULL, Path, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
		wcscpy_s(nID.szTip, Title);
		nID.hWnd = hWND;
		nID.uID = uID;
		nID.uFlags = NIF_GUID | NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nID.uCallbackMessage = 1025;
		Shell_NotifyIconW(NIM_ADD, &nID);
	}
};

const string WCH_WDName[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
map <string, function <void ()>> WCH_command_support;
vector <string> WCH_command_list;
multimap <int, pair <int, string>> WCH_clock_list;
set <string> WCH_task_list;
set <string> WCH_work_list;
HWND WCH_hWnd;
MyNotify *Myn;
CTrayIcon *MyC;
int WCH_clock_num;
int WCH_task_num;
int WCH_work_num;
int WCH_clock_change;
int WCH_task_change;
int WCH_work_change;
int WCH_ProgressBarCount;
int WCH_ProgressBarTot;
int WCH_InputTimes;
bool WCH_cmd_line = true;
bool WCH_anti_idle;
bool WCH_program_end;
string WCH_command;
string WCH_ProgressBarStr;
ifstream fin;
ofstream fout;
WCH_Time WCH_GetTime();
void WCH_Sleep(int _ms);
void WCH_Error(int _in);
void WCH_printlog(string _mode, string _info);
void WCH_read();
bool WCH_save_func();
int WCH_GetNumDigits(int _n);

#endif