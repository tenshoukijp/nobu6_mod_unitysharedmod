#include <windows.h>

//------------------------------------------------
// �v���Z�XID �� HWND �ւ̕ϊ�
// ����:�v���Z�XID
// �߂�l: HWND �������� NULL
//------------------------------------------------
HWND GetWindowHandleFromProcessId( const DWORD TargetID) {
	HWND hWnd = GetTopWindow(NULL);
	do {
		if(GetWindowLong( hWnd, GWL_HWNDPARENT) != 0 || !IsWindowVisible(hWnd)) {
			continue;
		}
		DWORD ProcessID;
		GetWindowThreadProcessId( hWnd, &ProcessID);
		if(TargetID == ProcessID) {
			return hWnd;
		}
	} while((hWnd = GetNextWindow( hWnd, GW_HWNDNEXT)) != NULL);

	return NULL;
}


//------------------------------------------------
// ���݂̃E�B���h�E�n���h���𓾂�
//------------------------------------------------
HWND GetCurrentWindowHandle() {
	// ���s���̃v���Z�XID�𓾂�
	DWORD pID = GetCurrentProcessId();
	// �v���Z�XID�˃E�B���h�E�n���h��
	HWND hWnd = GetWindowHandleFromProcessId(pID);
	return hWnd;
}






//------------------------------------------------
//getFileNameWithOutDirName
//�t���p�X������t�@�C�������擾����
//------------------------------------------------
/*
�����F  char *lpszPath    �t�@�C�������܂ރp�X���ւ̃|�C���^

�߂�l�Fchar * �t�@�C�����ւ̃|�C���^
�@�@�@�@�@�@�@�t�@�C�������܂܂Ȃ��Ƃ���""�ւ̃|�C���^
	   [\],[/],[:]��������Ȃ������ꍇ�A�������t�@�C�����Ƃ݂Ȃ��Ă��̂܂ܕԂ�
*/
char *GetFileNameWithOutDirName(char *lpszPath) {
	char    *lpszPtr=lpszPath;

	while(*lpszPtr != '\0') {
		//�Q�o�C�g�����̐擪�̓X�L�b�v
		if(IsDBCSLeadByte(*lpszPtr) == 0) {
			//[\],[/],[:]���������猻�ݒn+1�̃|�C���^��ۑ�
			if((*lpszPtr == '\\') || (*lpszPtr == '/') || (*lpszPtr == ':')) {
				lpszPath=lpszPtr+1;
			}
		}
		//���̕�����
		lpszPtr=CharNext(lpszPtr);
	}
	return lpszPath;
}