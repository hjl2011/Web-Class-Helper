/*
Web-Class-Helper Commands Module Header File 1.1.2
This source code file is under MIT License.
Copyright (c) 2022 Class Tools Develop Team
Contributors: jsh-jsh ren-yc
*/
#ifndef VARIABLES_H
#define VARIABLES_H
#include <bits/stdc++.h>
#include <windows.h>
#include <wininet.h>
#include <tlhelp32.h>
#include <conio.h>
#include <direct.h>
#include "commands.h"
#include "functions.h"
#include "file-process.h"
#include "apis.h"
using namespace std;

#define WCH_ERRNO_OUT_OF_RANGE "OOR"
#define WCH_ERRNO_NETWORK_FAILURE "NF"
#define WCH_ERRNO_CLOCK_OPERATION "CO"
#define WCH_ERRNO_TASK_OPERATION "TO"
#define WCH_ERRNO_WORK_OPERATION "WO"
#define WCH_LOG_MODE_ST -1
#define WCH_LOG_MODE_ERROR 0
#define WCH_LOG_MODE_RC 1
#define WCH_LOG_MODE_RW 2
#define WCH_LOG_MODE_KT 3
#define WCH_LOG_MODE_WD 4
#define WCH_LOG_MODE_UPD 5
#define WCH_LOG_STATUS_INFO "[INFO]"
#define WCH_LOG_STATUS_ERROR "[ERROR]"

struct WCH_Time {
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;
	int WeekDay;
	string Name;
};
struct WCH_Data_Body {
	int H;
	int M;
};
const string WCH_WDName[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
multimap <int, pair <int, string>> WCH_clock_list;
set <string> WCH_task_list;
set <string> WCH_work_list;
HWND WCH_hWnd;
int WCH_clock_num;
int WCH_task_num;
int WCH_work_num;
int WCH_ProgressBarCount;
int WCH_ProgressBarTot;
bool WCH_cmd_line = true;
bool WCH_anti_idle;
bool WCH_program_end;
bool WCH_wait_cmd;
string WCH_command;
ifstream fin;
ofstream fout;
wifstream wfin;
wofstream wfout;
WCH_Time WCH_GetTime();
void WCH_Sleep(int _ms);
void WCH_Error(string INFO);
void WCH_printlog(int w, initializer_list <string> other);
void WCH_read();
void WCH_save();
int WCH_GetNumDigits(int n);

#endif