#pragma once

#include <windows.h>

// ���ݎ��s���̎����̃v���Z�X�̃E�B���h�E�n���h���𓾂�B
HWND GetCurrentWindowHandle();

// �t���p�X������t�@�C���������𓾂�B
// (��������̃|�C���^�����Ă邾���Ȃ̂ŁA���̕�����̑��݂��K�{�Ȃ̂ŋC��t���邱��)
char *GetFileNameWithOutDirName(char *lpszPath);