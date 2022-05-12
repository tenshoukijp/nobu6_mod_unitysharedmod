#include <windows.h>

#include "ProcessHandle.h"

extern HANDLE hDllModule;

namespace Mutex {

	// Mutex�p�̃n���h��
	HANDLE hMutex = NULL;


	// ����DLL�̎������g�̖��O
	static char szBufMutexLabel[1024] = "";

	// dll���������g�̖��O�𓾂�BMutex�p�̎��ʖ�������ɂ��邱�ƂŁA��Ӑ���ۂB
	char* GetMutexLabel() {

		// ���߂̎���������B
		if (szBufMutexLabel[0] == NULL ) {
			// ���W���[���n���h�������W���[���̃t���p�X��(����ŕԂ��Ă��镶����́A�ďo�����v���Z�X��Win�o�[�W�����╶���R�[�h��Ԃő啶���������̈������ς��̂Œ���)
			GetModuleFileName((HMODULE)hDllModule, szBufMutexLabel, MAX_PATH);
			// �t���p�X�����t�@�C������
			char szBuf[MAX_PATH] = "";
			strcpy( szBuf, GetFileNameWithOutDirName( szBufMutexLabel ) );
			// ��������
			::_strlwr( szBuf );
			// �o�b�t�@�Ɋi�[���Ă���
			strcpy( szBufMutexLabel, szBuf );
		}
		return szBufMutexLabel;
	}



	static HANDLE hMutexLock = NULL;

	// Mutex���b�N�J�n�B�N��������Ă����疳���ɑ҂B
	void BgnMutexLock() {
		// �r���J�n
		hMutexLock = OpenMutex(MUTEX_ALL_ACCESS, FALSE, GetMutexLabel());
		// ���̏��Ń��b�N����Ă���҂�
		WaitForSingleObject(hMutexLock,INFINITE);
	}

	// Mutex���b�N���
	void EndMutexLock() {
		ReleaseMutex(hMutexLock);
	}

}


