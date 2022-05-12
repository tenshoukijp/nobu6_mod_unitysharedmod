/*
 *
 * 天翔記側とUnity側で共用される変数。
 *
 */

#include <windows.h>

// 共有メモリ
#pragma data_seg(".UnitySharedMemory")

namespace SharedMemory {

	char szFontName[64] = ""; // 天翔記で使ってるフォント名。
}

#pragma data_seg()

