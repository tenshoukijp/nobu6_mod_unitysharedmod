#pragma once

#include <windows.h>

// 現在実行中の自分のプロセスのウィンドウハンドルを得る。
HWND GetCurrentWindowHandle();

// フルパス名からファイル名だけを得る。
// (元文字列のポインタ示してるだけなので、元の文字列の存在が必須なので気を付けること)
char *GetFileNameWithOutDirName(char *lpszPath);