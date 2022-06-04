/*
Web Class Helper File Process Module Header File 2.0.1
This source code file is under MIT License.
Copyright (c) 2022 Class Tools Develop Team
Contributors: jsh-jsh ren-yc
*/
#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H
#include "init.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include "apis.hpp"
#include "basic.hpp"

extern const wstring WCH_WDName[7];
extern map <wstring, function <void ()>> WCH_command_support;
extern vector <wstring> WCH_command_list;
extern multimap <int, pair <int, wstring>> WCH_clock_list;
extern set <wstring> WCH_task_list;
extern set <wstring> WCH_work_list;
extern wstring WCH_window_title;
extern HWND WCH_hWnd;
extern HMENU WCH_hMenu;
extern int WCH_clock_num;
extern int WCH_task_num;
extern int WCH_work_num;
extern int WCH_clock_change;
extern int WCH_task_change;
extern int WCH_work_change;
extern int WCH_ProgressBarCount;
extern int WCH_ProgressBarTot;
extern int WCH_InputTimes;
extern bool WCH_cmd_line;
extern bool WCH_anti_idle;
extern bool WCH_program_end;
extern wstring WCH_command;
extern wstring WCH_ProgressBarStr;
extern ifstream fin;
extern wifstream wfin;
extern ofstream fout;
extern wofstream wfout;
WCH_Time WCH_GetTime();
void WCH_Sleep(int _ms);
void WCH_printlog(wstring _mode, wstring _info);
void WCH_read();
bool WCH_save_func();
int WCH_GetNumDigits(int _n);

void WCH_printlog(wstring _mode, wstring _info) {
	// Print log.
	WCH_Time now = WCH_GetTime();
	wfout.open(L"logs/latest.log", ios::app);
	wfout << format(L"[{:02}:{:02}:{:02}] {}: {}.", now.Hour, now.Minute, now.Second, _mode, _info) << endl;
	wfout.close();
}

void WCH_read_clock() {
	// Read clock data.
	WCH_Time q = WCH_GetTime();
	wstring NowWeekDay = WCH_WDName[(q.Day + 2 * q.Month + 3 * (q.Month + 1) / 5 + q.Year + q.Year / 4 - q.Year / 100 + q.Year / 400 + 1) % 7];
	wstring FilePath = L"data/" + NowWeekDay + L".dat";
	wfin.open(FilePath);
	if (!wfin.is_open()) {
		return;
	}
	WCH_printlog(WCH_LOG_STATUS_INFO, L"Reading file \"" + FilePath + L"\"");
	wfin >> WCH_clock_num;
	wfin.ignore();
	for (int i = 1; i <= WCH_clock_num; i++) {
		wstring tmp1;
		getline(wfin, tmp1);
		vector <wstring> tmp2 = WCH_split(tmp1);
		int H = stoi(tmp2[0]);
		int M = stoi(tmp2[1]);
		wstring Tname = tmp1.substr((int)tmp2[0].size() + (int)tmp2[1].size() + 2, tmp1.size() - 1);
		WCH_clock_list.emplace(make_pair(H, make_pair(M, Tname)));
	}
	wfin.close();
}

void WCH_read_task() {
	// Read task data.
	wstring FilePath = L"data/task.dat";
	wfin.open(FilePath);
	if (!wfin.is_open()) {
		return;
	}
	WCH_printlog(WCH_LOG_STATUS_INFO, L"Reading file \"" + FilePath + L"\"");
	wfin >> WCH_task_num;
	wfin.ignore();
	for (int i = 1; i <= WCH_task_num; i++) {
		wstring TaskName;
		getline(wfin, TaskName);
		WCH_task_list.insert(TaskName);
	}
	wfin.close();
}

void WCH_read_work() {
	// Read work data.
	wstring FilePath = L"data/work.dat";
	wfin.open(FilePath);
	if (!wfin.is_open()) {
		return;
	}
	WCH_printlog(WCH_LOG_STATUS_INFO, L"Reading file \"" + FilePath + L"\"");
	wfin >> WCH_work_num;
	wfin.ignore();
	for (int i = 1; i <= WCH_work_num; i++) {
		wstring WorkName;
		getline(wfin, WorkName);
		WCH_work_list.insert(WorkName);
	}
	wfin.close();
}

void WCH_read() {
	// Read data.
	WCH_cmd_line = false;
	wcout << L"Reading data..." << endl;
	WCH_read_clock();
	WCH_read_task();
	WCH_read_work();
	WCH_ProgressBarTot = 3;
	thread T(WCH_ProgressBar);
	T.detach();
	WCH_Sleep(4000);
	WCH_cmd_line = true;
	_wsystem(L"cls");
}

void WCH_save_clock() {
	// Save clock data.
	WCH_Time q = WCH_GetTime();
	wstring NowWeekDay = WCH_WDName[(q.Day + 2 * q.Month + 3 * (q.Month + 1) / 5 + q.Year + q.Year / 4 - q.Year / 100 + q.Year / 400 + 1) % 7];
	wstring FilePath = L"data/" + NowWeekDay + L".dat";
	if (WCH_clock_num == 0) {
		if (_waccess(FilePath.c_str(), 0) != -1) {
			WCH_printlog(WCH_LOG_STATUS_INFO, L"Deleting file \"" + FilePath + L"\"");
			DeleteFileW(FilePath.c_str());
		}
		return;
	}
	WCH_printlog(WCH_LOG_STATUS_INFO, L"Writing file \"" + FilePath + L"\"");
	wfout.open(FilePath);
	wfout << WCH_clock_num << endl;
	for (int i = 0; i <= 24; i++) {
		for (auto it = WCH_clock_list.equal_range(i).first; it != WCH_clock_list.equal_range(i).second; it++) {
			wfout << i << L" " << (it -> second).first << L" " << (it -> second).second << endl;
		}
	}
	wfout.close();
}

void WCH_save_task() {
	// Save task list data.
	wstring FilePath = L"data/task.dat";
	if (WCH_task_num == 0) {
		if (_waccess(FilePath.c_str(), 0) != -1) {
			WCH_printlog(WCH_LOG_STATUS_INFO, L"Deleting file \"" + FilePath + L"\"");
			DeleteFileW(FilePath.c_str());
		}
		return;
	}
	WCH_printlog(WCH_LOG_STATUS_INFO, L"Writing file \"" + FilePath + L"\"");
	wfout.open(FilePath);
	wfout << WCH_task_num << endl;
	for (auto it = WCH_task_list.begin(); it != WCH_task_list.end(); it++) {
		wfout << *it << endl;
	}
	wfout.close();
}

void WCH_save_work() {
	// Save task list data.
	wstring FilePath = L"data/work.dat";
	if (WCH_work_num == 0) {
		if (_waccess(FilePath.c_str(), 0) != -1) {
			WCH_printlog(WCH_LOG_STATUS_INFO, L"Deleting file \"" + FilePath + L"\"");
			DeleteFileW(FilePath.c_str());
		}
		return;
	}
	WCH_printlog(WCH_LOG_STATUS_INFO, L"Writing file \"" + FilePath + L"\"");
	wfout.open(FilePath);
	wfout << WCH_work_num << endl;
	for (auto it = WCH_work_list.begin(); it != WCH_work_list.end(); it++) {
		wfout << *it << endl;
	}
	wfout.close();
}

bool WCH_save_func() {
	// Save data. (Function)
	bool NeedSave = (WCH_clock_change != 0 || WCH_task_change != 0 || WCH_work_change != 0);
	if (NeedSave) {
		wcout << L"Saving data..." << endl;
		WCH_ProgressBarTot = WCH_clock_change + WCH_task_change + WCH_work_change;
	}
	WCH_save_clock();
	WCH_save_task();
	WCH_save_work();
	if (NeedSave) {
		thread T(WCH_ProgressBar);
		T.detach();
		WCH_Sleep(WCH_ProgressBarTot * 1000);
		WCH_Sleep(1000);
	}
	return NeedSave;
}

#endif