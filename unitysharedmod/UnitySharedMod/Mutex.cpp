#include <windows.h>

#include "ProcessHandle.h"

extern HANDLE hDllModule;

namespace Mutex {

	// Mutex用のハンドル
	HANDLE hMutex = NULL;


	// このDLLの自分自身の名前
	static char szBufMutexLabel[1024] = "";

	// dllが自分自身の名前を得る。Mutex用の識別名をこれにすることで、一意性を保つ。
	char* GetMutexLabel() {

		// 初めの時だけ代入。
		if (szBufMutexLabel[0] == NULL ) {
			// モジュールハンドル→モジュールのフルパス名(これで返ってくる文字列は、呼出し元プロセスのWinバージョンや文字コード空間で大文字小文字の扱いか変わるので注意)
			GetModuleFileName((HMODULE)hDllModule, szBufMutexLabel, MAX_PATH);
			// フルパス名→ファイル名へ
			char szBuf[MAX_PATH] = "";
			strcpy( szBuf, GetFileNameWithOutDirName( szBufMutexLabel ) );
			// 小文字へ
			::_strlwr( szBuf );
			// バッファに格納しておく
			strcpy( szBufMutexLabel, szBuf );
		}
		return szBufMutexLabel;
	}



	static HANDLE hMutexLock = NULL;

	// Mutexロック開始。誰かが取っていたら無限に待つ。
	void BgnMutexLock() {
		// 排他開始
		hMutexLock = OpenMutex(MUTEX_ALL_ACCESS, FALSE, GetMutexLabel());
		// 他の所でロックされてたら待つ
		WaitForSingleObject(hMutexLock,INFINITE);
	}

	// Mutexロック解放
	void EndMutexLock() {
		ReleaseMutex(hMutexLock);
	}

}


