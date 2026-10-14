/* Прокси DINPUT.dll: Game.exe импортирует только DirectInputCreateA.
   Загружается раньше WinMain игры — здесь ставим перехваты. */
#include "hook.h"
typedef HRESULT (WINAPI *PFN_DICreateA)(HINSTANCE, DWORD, void **, void *);
static PFN_DICreateA real_create;
static void load_real(void) {
    char path[MAX_PATH]; GetSystemDirectoryA(path, MAX_PATH); lstrcatA(path, "\\dinput.dll");
    HMODULE h = LoadLibraryA(path);
    real_create = h ? (PFN_DICreateA)GetProcAddress(h, "DirectInputCreateA") : 0;
    if (!real_create) re_log("ERROR: system dinput.dll not found");
}
__declspec(dllexport) HRESULT WINAPI DirectInputCreateA(HINSTANCE hi, DWORD ver, void **out, void *outer) {
    if (!real_create) load_real();
    return real_create ? real_create(hi, ver, out, outer) : E_FAIL;
}
BOOL WINAPI DllMain(HINSTANCE h, DWORD reason, LPVOID r) {
    (void)h; (void)r;
    if (reason == DLL_PROCESS_ATTACH) {
        if ((uintptr_t)GetModuleHandleA(NULL) != GAME_BASE) { re_log("ERROR: Game.exe not at 0x400000"); return TRUE; }
        re_log("re_driver: Driver (PC, 1999) reconstruction layer");
        re_install_all();
    }
    return TRUE;
}
