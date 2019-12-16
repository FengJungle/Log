#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <TCHAR.H>
#include <mutex>

using namespace std;

enum LOGLEVEL
{
	LOG_LEVEL_NONE,
	LOG_LEVEL_ERROR,     // error
	LOG_LEVEL_WARNING,   // warning
	LOG_LEVEL_DEBUG,     // debug
	LOG_LEVEL_INFO,      // info	
};

enum LOGTARGET
{
	LOG_TARGET_NONE      = 0x00,
	LOG_TARGET_CONSOLE   = 0x01,
	LOG_TARGET_FILE      = 0x10
};

#define FILENAME(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#define LOG_DEBUG(...)    LOG::writeLog(LOG_LEVEL_DEBUG, (unsigned char*)(FILENAME(__FILE__)), (unsigned char*)(__FUNCTION__), (int)(__LINE__), __VA_ARGS__)
#define LOG_INFO(...)     LOG::writeLog(LOG_LEVEL_INFO, (unsigned char*)(FILENAME(__FILE__)), (unsigned char*)(__FUNCTION__), (int)(__LINE__), __VA_ARGS__)
#define LOG_WARNING(...)  LOG::writeLog(LOG_LEVEL_WARNING, (unsigned char*)(FILENAME(__FILE__)), (unsigned char*)(__FUNCTION__), (int)(__LINE__), __VA_ARGS__)
#define LOG_ERROR(...)    LOG::writeLog(LOG_LEVEL_ERROR, (unsigned char*)(FILENAME(__FILE__)), (unsigned char*)(__FUNCTION__), (int)(__LINE__), __VA_ARGS__)

#define ENTER() LOG_INFO("enter")
#define EXIT()  LOG_INFO("exit")
#define FAIL()  LOG_ERROR("fail")

// 单个日志文件最大存储
#define MAX_SIZE 2*1024*1024  // 2M

class LOG
{
public:

	// 初始化
	void init(LOGLEVEL loglevel, LOGTARGET logtarget);

	// 
	void uninit();

	// file
	int createFile();

	static LOG* getInstance();

	// Log级别
	LOGLEVEL getLogLevel();
	void setLogLevel(LOGLEVEL loglevel);

	// Log输出位置
	LOGTARGET getLogTarget();
	void setLogTarget(LOGTARGET logtarget);

	// 打log
	static int writeLog(
		LOGLEVEL loglevel,         // Log级别
		unsigned char* fileName,   // 函数所在文件名
		unsigned char* function,   // 函数名
		int lineNumber,            // 行号
		char* format,              // 格式化
		...);                      // 变量

	// 输出log
	static void outputToTarget();

private:
	LOG();
	~LOG();
	static LOG* Log;

	// 互斥锁
	static mutex log_mutex;
	// 临界区
	static CRITICAL_SECTION criticalSection;

	// 存储log的buffer
	static string logBuffer;
	// 已写的log长度
	static int writtenSize;

	// Log级别
	LOGLEVEL logLevel;

	// Log输出位置
	LOGTARGET logTarget;

	// Handle
	static HANDLE mFileHandle;
};



#endif // __LOG_H__