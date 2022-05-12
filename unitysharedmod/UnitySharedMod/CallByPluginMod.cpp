/*
 *
 * 天翔記側が呼び出すメソッド郡
 *
 */

#include <windows.h>

#include "SharedMemory.h"




// 開始時
void WINAPI On_PluginMod_初期化(HANDLE 呼び出し元ハンドル) {

	// 排他Mutexオブジェクトを作成。ハンドルを得る 
	Mutex::hMutex = CreateMutex(NULL,FALSE, Mutex::GetMutexLabel()); 

	Mutex::BgnMutexLock();
	strcpy( SharedMemory::szFontName, "あいう" );
	Mutex::EndMutexLock();


}
 
// 終了時
void WINAPI On_PluginMod_末期化() {

	// 排他Mutexオブジェクトを破棄。ハンドル解放。
	CloseHandle(Mutex::hMutex);
}




