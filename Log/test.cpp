#include "log.h"

/*���̰߳�ȫ ����ģʽ*/
#include <process.h>
#include <Windows.h>
#define THREAD_NUM 5

// ȫ����Դ����
int g_num = 0;

unsigned int __stdcall func(void *pPM)
{
	LOG_INFO("enter");
	//int nThreadNum = *(int *)pPM;
	Sleep(50);
	g_num++;
	LOG_INFO("g_num = %d", g_num);

	LOG_INFO("exit");
	return 0;
}

int main()
{
	LOG *logger = LOG::getInstance();
	HANDLE  handle[THREAD_NUM];

	//�̱߳��
	int threadNum = 0;
	while (threadNum < THREAD_NUM)
	{
		handle[threadNum] = (HANDLE)_beginthreadex(NULL, 0, func, NULL, 0, NULL);
		//�����߳̽��յ�����ʱ���߳̿��ܸı������i��ֵ
		threadNum++;
	}
	//��֤���߳���ȫ�����н���
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	//system("pause");
	return 0;
}
