/*
 *
 * Unity側が呼び出すメソッド郡
 *
 */

#include <windows.h>
#include "SharedMemory.h"
#include "ProcessHandle.h"

using namespace System;
using namespace System::Windows::Forms;


// Unityから呼んでもらう。
void WINAPI On_Unity_初期化() {

	// 現在実行中のウィンドウハンドルを得る。
	HWND hWnd = GetCurrentWindowHandle();
	if (!hWnd) { return; }

	// 排他Mutexオブジェクトを作成。ハンドルを得る 
	Mutex::hMutex = CreateMutex(NULL,FALSE, Mutex::GetMutexLabel()); 

	// 以下Unityアプリを真ん中に配置して、タイトルバーを消してみるテスト処理
    RECT rc1;        // デスクトップ領域
    RECT rc2;        // ウインドウ領域
    int  cx, cy;     // ウインドウ位置
    int  sx, sy;     // ウインドウサイズ

    // ディスプレイサイズの取得
    SystemParametersInfo(SPI_GETWORKAREA,0,&rc1,0);       // デスクトップのサイズ

	// 自分自身のウィンドウサイズを得る
    GetWindowRect( hWnd, &rc2 );  // ウインドウのサイズ

    // 位置と幅・高さの計算
    sx = (rc2.right - rc2.left);                            // ウインドウの横幅
    sy = (rc2.bottom - rc2.top);                            // ウインドウの高さ
    cx = (((rc1.right - rc1.left) - sx) / 2 + rc1.left);    // 中央に置いた場合のx位置
    cy = (((rc1.bottom - rc1.top) - sy) / 2 + rc1.top);     // 中央に置いた場合のy位置

	// ウィンドウのスタイルを変更する。ボーダーなくす
	SetWindowLong(hWnd, GWL_STYLE, WS_BORDER );

	// 移動して描画更新
	SetWindowPos( hWnd, NULL, cx, cy, sx, sy, SWP_SHOWWINDOW );


	Mutex::BgnMutexLock();
	strcat( SharedMemory::szFontName, "お");
	Mutex::EndMutexLock();

	// 以下、Unityアプリから呼び出したC++/CLI混成アプリが、Microsoft .NET FrameWorkを動かせることの実験
	Form^ form = gcnew Form();
	form->Text = gcnew String(SharedMemory::szFontName);
	form->Show();
}

// Unityから呼んでもらう。
void WINAPI On_Unity_末期化() {
	// 排他Mutexオブジェクトを破棄。ハンドル解放。
	CloseHandle(Mutex::hMutex); 
}
