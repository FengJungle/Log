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

// ������־�ļ����洢
#define MAX_SIZE 2*1024*1024  // 2M

class LOG
{
public:

	// ��ʼ��
	void init(LOGLEVEL loglevel, LOGTARGET logtarget);

	// 
	void uninit();

	// file
	int createFile();

	static LOG* getInstance();

	// Log����
	LOGLEVEL getLogLevel();
	void setLogLevel(LOGLEVEL loglevel);

	// Log���λ��
	LOGTARGET getLogTarget();
	void setLogTarget(LOGTARGET logtarget);

	// ��log
	static int writeLog(
		LOGLEVEL loglevel,         // Log����
		unsigned char* fileName,   // ���������ļ���
		unsigned char* function,   // ������
		int lineNumber,            // �к�
		char* format,              // ��ʽ��
		...);                      // ����

	// ���log
	static void outputToTarget();

private:
	LOG();
	~LOG();
	static LOG* Log;

	// ������
	static mutex log_mutex;
	// �ٽ���
	static CRITICAL_SECTION criticalSection;

	// �洢log��buffer
	static string logBuffer;
	// ��д��log����
	static int writtenSize;

	// Log����
	LOGLEVEL logLevel;

	// Log���λ��
	LOGTARGET logTarget;

	// Handle
	static HANDLE mFileHandle;
};



#endif // __LOG_H__