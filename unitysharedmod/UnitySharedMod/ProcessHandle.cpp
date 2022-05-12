#include <windows.h>

//------------------------------------------------
// プロセスID ⇒ HWND への変換
// 引数:プロセスID
// 戻り値: HWND もしくは NULL
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
// 現在のウィンドウハンドルを得る
//------------------------------------------------
HWND GetCurrentWindowHandle() {
	// 実行中のプロセスIDを得る
	DWORD pID = GetCurrentProcessId();
	// プロセスID⇒ウィンドウハンドル
	HWND hWnd = GetWindowHandleFromProcessId(pID);
	return hWnd;
}






//------------------------------------------------
//getFileNameWithOutDirName
//フルパス名からファイル名を取得する
//------------------------------------------------
/*
引数：  char *lpszPath    ファイル名を含むパス名へのポインタ

戻り値：char * ファイル名へのポインタ
　　　　　　　ファイル名を含まないときは""へのポインタ
	   [\],[/],[:]が見つからなかった場合、引数をファイル名とみなしてそのまま返す
*/
char *GetFileNameWithOutDirName(char *lpszPath) {
	char    *lpszPtr=lpszPath;

	while(*lpszPtr != '\0') {
		//２バイト文字の先頭はスキップ
		if(IsDBCSLeadByte(*lpszPtr) == 0) {
			//[\],[/],[:]を見つけたら現在地+1のポインタを保存
			if((*lpszPtr == '\\') || (*lpszPtr == '/') || (*lpszPtr == ':')) {
				lpszPath=lpszPtr+1;
			}
		}
		//次の文字へ
		lpszPtr=CharNext(lpszPtr);
	}
	return lpszPath;
}