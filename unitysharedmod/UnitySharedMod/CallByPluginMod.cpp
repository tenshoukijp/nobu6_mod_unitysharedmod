/*
 *
 * �V�ċL�����Ăяo�����\�b�h�S
 *
 */

#include <windows.h>

#include "SharedMemory.h"




// �J�n��
void WINAPI On_PluginMod_������(HANDLE �Ăяo�����n���h��) {

	// �r��Mutex�I�u�W�F�N�g���쐬�B�n���h���𓾂� 
	Mutex::hMutex = CreateMutex(NULL,FALSE, Mutex::GetMutexLabel()); 

	Mutex::BgnMutexLock();
	strcpy( SharedMemory::szFontName, "������" );
	Mutex::EndMutexLock();


}
 
// �I����
void WINAPI On_PluginMod_������() {

	// �r��Mutex�I�u�W�F�N�g��j���B�n���h������B
	CloseHandle(Mutex::hMutex);
}




