/*
 *
 * Unity�����Ăяo�����\�b�h�S
 *
 */

#include <windows.h>
#include "SharedMemory.h"
#include "ProcessHandle.h"

using namespace System;
using namespace System::Windows::Forms;


// Unity����Ă�ł��炤�B
void WINAPI On_Unity_������() {

	// ���ݎ��s���̃E�B���h�E�n���h���𓾂�B
	HWND hWnd = GetCurrentWindowHandle();
	if (!hWnd) { return; }

	// �r��Mutex�I�u�W�F�N�g���쐬�B�n���h���𓾂� 
	Mutex::hMutex = CreateMutex(NULL,FALSE, Mutex::GetMutexLabel()); 

	// �ȉ�Unity�A�v����^�񒆂ɔz�u���āA�^�C�g���o�[�������Ă݂�e�X�g����
    RECT rc1;        // �f�X�N�g�b�v�̈�
    RECT rc2;        // �E�C���h�E�̈�
    int  cx, cy;     // �E�C���h�E�ʒu
    int  sx, sy;     // �E�C���h�E�T�C�Y

    // �f�B�X�v���C�T�C�Y�̎擾
    SystemParametersInfo(SPI_GETWORKAREA,0,&rc1,0);       // �f�X�N�g�b�v�̃T�C�Y

	// �������g�̃E�B���h�E�T�C�Y�𓾂�
    GetWindowRect( hWnd, &rc2 );  // �E�C���h�E�̃T�C�Y

    // �ʒu�ƕ��E�����̌v�Z
    sx = (rc2.right - rc2.left);                            // �E�C���h�E�̉���
    sy = (rc2.bottom - rc2.top);                            // �E�C���h�E�̍���
    cx = (((rc1.right - rc1.left) - sx) / 2 + rc1.left);    // �����ɒu�����ꍇ��x�ʒu
    cy = (((rc1.bottom - rc1.top) - sy) / 2 + rc1.top);     // �����ɒu�����ꍇ��y�ʒu

	// �E�B���h�E�̃X�^�C����ύX����B�{�[�_�[�Ȃ���
	SetWindowLong(hWnd, GWL_STYLE, WS_BORDER );

	// �ړ����ĕ`��X�V
	SetWindowPos( hWnd, NULL, cx, cy, sx, sy, SWP_SHOWWINDOW );


	Mutex::BgnMutexLock();
	strcat( SharedMemory::szFontName, "��");
	Mutex::EndMutexLock();

	// �ȉ��AUnity�A�v������Ăяo����C++/CLI�����A�v�����AMicrosoft .NET FrameWork�𓮂����邱�Ƃ̎���
	Form^ form = gcnew Form();
	form->Text = gcnew String(SharedMemory::szFontName);
	form->Show();
}

// Unity����Ă�ł��炤�B
void WINAPI On_Unity_������() {
	// �r��Mutex�I�u�W�F�N�g��j���B�n���h������B
	CloseHandle(Mutex::hMutex); 
}
