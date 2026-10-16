#ifndef PLAT_H
#define PLAT_H
#include <stdint.h>
/* Platform interface: game code in game/ calls only this. */
/* --- system --- */
uint32_t plat_time_ms(void);
void plat_sleep_ms(uint32_t ms);
void plat_local_hms(int *h, int *m, int *s); /* GetLocalTime */
void plat_utc_hms(int *h, int *m, int *s);   /* GetSystemTime (UTC) */
int  plat_message_box(void *hwnd, const char *text, const char *title, unsigned flags); /* MessageBoxA: flags 0x10 ошибка, 0x30 предупреждение */
int  plat_cd_roots(char *buf, int size);      /* корни CD/DVD-приводов через \0, список завершён пустой строкой (GetLogicalDriveStrings + DRIVE_CDROM); возвращает число байт, 0 — нет */
void plat_wave_set_volume(uint32_t lr);      /* waveOutSetVolume(0, lr): (R<<16)|L; SDL: запоминает для микшера */
uint32_t plat_wave_volume(void);             /* последнее значение (тесты) */
int  plat_message_box_last(const char **text, const char **title); /* число вызовов и последний текст (тесты; hook: 0) */
void plat_exit(int code);                     /* выход из процесса (hook: CRT-выход Game.exe 0052e480; SDL: exit) */
void plat_exit_trap(int on);                  /* тесты: plat_exit только запоминает код и возвращается */
int  plat_exit_last(void);                    /* последний код plat_exit (тесты) */
int  plat_screensaver_get(void);              /* SystemParametersInfo(SPI_GETSCREENSAVEACTIVE) */
void plat_screensaver_set(int on);            /* SPI_SETSCREENSAVEACTIVE */
void plat_set_crash_handler(void (*fn)(void)); /* SetUnhandledExceptionFilter: fn вызывается при аварии, потом процесс завершается; NULL — снять */
void (*plat_crash_handler(void))(void);       /* текущий обработчик (тесты) */
int  plat_com_init(void);                     /* CoInitialize(NULL): число активных вызовов (SDL: счётчик, hook: WinAPI) */
void plat_com_uninit(void);                   /* CoUninitialize */
int  plat_com_count(void);                    /* init минус uninit (тесты; hook: 0) */
void plat_log(const char *fmt, ...);
void *plat_file_open(const char *path, const char *mode); /* case-insensitive lookup */
/* v2.00: fopen для путей игры: '\\' → '/', поиск каждого компонента без учёта регистра (native); hook — fopen как есть */
void *plat_fopen_game(const char *path, const char *mode);
void  plat_fs_mkdirs(int on);
int   plat_remove_game(const char *path);   /* v2.04: remove с переводом пути как в plat_fopen_game */
/* */   /* v2.04: plat_fopen_game создаёт недостающие каталоги пути при записи (игра) */
int plat_path_native(const char *path, char *out, int size);   /* 1 — все компоненты найдены */
/* v2.00: запуск игры — счётчик кадров (RE_MAX_FRAMES) и снимок (RE_SHOT_PNG); зовётся из plat_flip и цикла сообщений */
void plat_frame_tick(const char *where);
/* --- window & input --- */
int plat_window_open(const char *title, int w, int h, int fullscreen);
int plat_poll_events(void); /* returns 0 on quit request */
int plat_key_down(int scancode);
void plat_window_close(void);
/* --- render (declared; SDL/OpenGL impl in sdl/plat_render.c) --- */
typedef struct { float x, y, z, rhw; uint32_t color, specular; float u, v; } plat_vertex;
int plat_tex_create(int w, int h, const uint32_t *rgba);
void plat_tex_bind(int tex);
void plat_tex_update(int tex, int w, int h, const uint32_t *rgba);   /* v2.01: перезагрузка картинки текстуры (SDL) */
void plat_clear_rect(uint32_t rgb, int x, int y, int w, int h);       /* v2.01: заливка прямоугольника кадра (SDL) */
void plat_tex_free(int tex);
void plat_set_blend(int enable, int src, int dst);
void plat_set_zbuffer(int test, int write);
void plat_draw_tris(const plat_vertex *v, int count);
void plat_clear(uint32_t color, int clear_z);
void plat_draw_lines(const plat_vertex *v, int count);     /* список линий, count чётный */
void plat_set_current_viewport(void);                      /* D3D SetCurrentViewport (SDL: no-op) */
void plat_clear_depth(void *viewport, int x, int y, int w, int h, float z); /* очистка Z в прямоугольнике */
int plat_get_render_state(int state);                      /* последнее установленное значение (для тестов; hook: 0) */
void plat_flip(void);
void plat_blit2d(int tex, int sx, int sy, int sw, int sh, int dx, int dy);
/* Состояние устройства в терминах Direct3D 6/7 (номера D3DRENDERSTATETYPE / D3DTEXTURESTAGESTATETYPE и значения как в DX):
   state: 7 ZENABLE, 14 ZWRITEENABLE, 15 ALPHATESTENABLE, 19 SRCBLEND, 20 DESTBLEND, 22 CULLMODE, 23 ZFUNC (1..8 = D3DCMP), 24 ALPHAREF, 25 ALPHAFUNC, 27 ALPHABLENDENABLE.
   В SDL-варианте применяется к GL, в hook-варианте уходит в IDirect3DDevice3 игры. */
void plat_scene_begin(void);
void plat_scene_end(void);
void plat_set_render_state(int state, uint32_t value);
void plat_set_tex_stage(int stage, int type, uint32_t value);   /* type 1 COLOROP, 16 MAGFILTER, 17 MINFILTER */
void plat_set_viewport(int x, int y, int w, int h);
uint32_t plat_get_tex_stage(int stage, int type);              /* GetTextureStageState (SDL: последнее установленное, 0 если нет) */
void plat_draw_prim(int ptype, const plat_vertex *v, int count); /* DrawPrimitive(D3DPRIMITIVETYPE: 2 линии, 4 треугольники; FVF XYZRHW|DIFFUSE|SPECULAR|TEX1), count вершин */
int  plat_draw_prim_last(int *ptype, int *count);               /* SDL (тесты): число вызовов и параметры последнего; hook: 0 */
/* Константы смешивания = значения D3DBLEND (1 ZERO, 2 ONE, 3 SRCCOLOR, 4 INVSRCCOLOR, 5 SRCALPHA, 6 INVSRCALPHA, 7 DESTALPHA, 8 INVDESTALPHA, 9 DESTCOLOR, 10 INVDESTCOLOR).
   color/specular вершины = 0xAARRGGBB; x,y в пикселях окна, z 0..1, rhw = 1/w (0 → 1). */
/* Подключение GL-контекста (SDL-окно или OSMesa); swap может быть NULL (offscreen). */
int plat_render_attach(void *(*get_proc)(const char *), void (*swap)(void), int w, int h);
int plat_render_offscreen(int w, int h);                 /* OSMesa; <0 если нет в сборке */
int plat_render_readback(uint32_t *rgba_topdown);        /* w*h пикселей 0xAABBGGRR (байты R,G,B,A) */
void plat_render_shutdown(void);
/* Звук и CD-аудио */
int  plat_snd_create(const void *pcm, int bytes, int rate, int channels, int bits);
void plat_snd_destroy(int h);
void plat_snd_play(int h, int loop);
void plat_snd_stop(int h);
void plat_snd_set(int h, int volume, int pitch_hz, int pan);
void plat_snd_pos3d(int h, float x, float y, float z);
/* volume/pan как в DirectSound (сотые дБ). Микшер: 44100 Гц, стерео S16; plat_snd_mix пригоден для тестов без устройства. */
void plat_snd_mix(int16_t *out_stereo, int frames);
int  plat_snd_open(void);                                /* SDL_audio, 1 = ок */
void plat_snd_close(void);
int  plat_cd_play(int track);
void plat_cd_stop(void);
int  plat_cd_current(void);
/* --- CD-аудио (MCI cdaudio, формат времени TMSF) и aux-громкость; таймеры (timeSetEvent). Время/позиции — упакованные TMSF как у MCI.
   SDL: учётная заглушка (plat_cd_stub_*), hook: winmm. --- */
int      plat_cd_open(void *hwnd);                    /* 1 = ок, 0 = не открылся, -1 = формат времени не принят (устройство закрыто) */
void     plat_cd_close(void);
int      plat_cd_track_count(void);                   /* <0 — ошибка запроса */
int      plat_cd_track_info(int track, uint32_t *pos, uint32_t *len); /* 0 ок, 1 — позиция не получена, 2 — длина не получена */
int      plat_cd_play_range(void *hwnd, uint32_t from, uint32_t to);  /* 1 = ок */
int      plat_cd_play_to(uint32_t to);                /* продолжить с текущей позиции до to; 1 = ок */
void     plat_cd_pause(void);                         /* MCI_STOP */
int      plat_aux_find_cd(void);                      /* индекс aux-устройства CD или -1 */
void     plat_aux_set_volume(int dev, uint32_t lr);   /* (R<<16)|L, 0..0xffff */
int      plat_timer_period_begin(unsigned ms);        /* 0 = ок */
void     plat_timer_period_end(unsigned ms);
unsigned plat_timer_start(unsigned delay_ms, unsigned flags, void (*cb)(unsigned id)); /* flags: 0 разово, 1 периодически; 0 = ошибка */
void     plat_timer_kill(unsigned id);
void     plat_cd_stub_set(int ntracks, int aux_dev);  /* только SDL (тесты): сколько дорожек «в приводе» */
int      plat_cd_stub_state(uint32_t *from, uint32_t *to, uint32_t *vol); /* только SDL: 1 — играет */
/* --- DirectDraw/Direct3D-объекты (непрозрачные дескрипторы; NULL = ошибка). Возврат int32 — HRESULT (0 = успех).
   SDL: объекты-заглушки без устройства (поверхности существуют только как учётные записи); hook: вызовы vtable объектов Game.exe. --- */
void   *plat_dd_create_surface(void *dd, const void *desc124);   /* DDSURFACEDESC 124 байта */
int32_t plat_dd_set_display_mode(void *dd, int w, int h, int bpp);
void   *plat_dd_create_clipper(void *dd);
int32_t plat_dd_set_clipper(void *surf, void *clipper);
int32_t plat_dd_attach_surface(void *surf, void *attached);
void   *plat_dd_get_attached(void *surf, uint32_t caps);         /* backbuffer: caps = 4 */
void    plat_dd_release(void *obj);
int32_t plat_dd_set_cooperative(void *dd, void *hwnd, uint32_t flags); /* IDirectDraw::SetCooperativeLevel */
int32_t plat_dd_is_lost(void *surf);                             /* != 0 — поверхность потеряна */
int32_t plat_dd_restore(void *surf);
int32_t plat_dd_fill_rect(void *surf, int x0, int y0, int x1, int y1, uint32_t pixel); /* цветовая заливка (Blt COLORFILL) */
void   *plat_d3d_create_device(void *d3d, const void *iid, void *surf);
void   *plat_d3d_create_viewport(void *d3d);
int32_t plat_d3d_add_viewport(void *dev, void *vp);
int32_t plat_d3d_set_viewport_rect(void *vp, int w, int h);
void    plat_window_maximize(void *wnd);                         /* ShowWindow(SW_MAXIMIZE) */
int     plat_dd_last_coop(void);                                 /* SDL: флаги последнего SetCooperativeLevel (тесты); hook: 0 */
int     plat_dd_stub_count(void);                                /* SDL: число живых заглушек (тесты); hook: 0 */
int     plat_dd_stub_last_fill(int32_t *rect4, uint32_t *pixel); /* SDL: последняя заливка (тесты); hook: 0 */
/* --- палитры и размер поверхности, текстура устройства (Render.c) --- */
int32_t plat_dd_get_surface_size(void *surf, int32_t *w, int32_t *h);  /* GetSurfaceDesc: ширина/высота; HRESULT */
void   *plat_dd_create_palette(void *dd, uint32_t flags, const void *entries256); /* CreatePalette; NULL — ошибка */
int32_t plat_dd_surface_set_palette(void *surf, void *pal);             /* IDirectDrawSurface::SetPalette */
int32_t plat_dd_palette_set_entries(void *pal, uint32_t flags, uint32_t first, uint32_t count, const void *entries); /* SetEntries */
void    plat_tex_palette_changed(void *tex, uint32_t first, uint32_t count); /* IDirect3DTexture2::PaletteChanged */
void    plat_set_texture(int stage, void *tex);                         /* IDirect3DDevice3::SetTexture (SDL: запоминает) */
void   *plat_stub_last_texture(int *stage);                             /* SDL (тесты): последний plat_set_texture; hook: NULL */
int     plat_stub_pal_stats(int *entries_calls, int *changed_calls);    /* SDL (тесты): счётчики; hook: 0 */
int     plat_dd_stub_last_desc(uint32_t *desc31);                       /* SDL (тесты): последний CreateSurface; hook: 0 */
/* --- окно игры, цикл сообщений (WinMain.c) --- */
typedef int32_t (*plat_wndproc)(void *hwnd, uint32_t msg, uint32_t wparam, int32_t lparam);
void   *plat_game_window_create(void *hinst, int32_t show, const char *title, int w, int h, plat_wndproc proc); /* RegisterClass+CreateWindowEx+ShowWindow; NULL — не удалось */
void    plat_pump_messages(void);                                /* PeekMessage/GetMessage/Dispatch до опустошения очереди */
void    plat_set_priority(int level);                            /* 0 — обычный, 1 — высокий (0x80), 2 — реального времени (0x100) */
void    plat_post_quit(int code);                                /* PostQuitMessage */
void    plat_post_close(void *hwnd);                             /* PostMessage(WM_CLOSE) */
void    plat_set_cursor(int visible);                            /* SetCursor(стрелка / NULL) */
int32_t plat_def_window_proc(void *hwnd, uint32_t msg, uint32_t wparam, int32_t lparam); /* DefWindowProc */
void   *plat_dll_proc(void *mod, const char *name);              /* GetProcAddress; SDL: NULL */
void   *plat_lock_resource(void *res);                           /* LockResource (v1.45, 0048c43c); SDL: res — уже указатель на данные */
void    plat_dll_unload(void *mod);                              /* FreeLibrary; SDL: ничего */
void   *plat_dll_load(const char *name);                         /* LoadLibrary; SDL: NULL (Glide на macOS нет) */
void    plat_win_trap(int on);                                   /* тесты (SDL): окно не создаётся, вызовы только запоминаются */
int     plat_win_state(int *cursor, int *prio, int *quit, int *closes, int *w, int *h, const char **title, plat_wndproc *proc); /* тесты: SDL — состояние; hook — 0 */
/* DirectInput (клавиатура/мышь/джойстик). Устройство — непрозрачный указатель; kind формата данных: 0 клавиатура, 1 мышь, 2 джойстик */
void    plat_di_release(void *obj);                    /* IUnknown::Release */
void    plat_di_unacquire(void *dev);                  /* IDirectInputDevice::Unacquire */
int32_t plat_di_set_format(void *dev, int kind);       /* SetDataFormat; 0 — успех */
int32_t plat_di_acquire(void *dev);                    /* Acquire; 0 — успех */
int32_t plat_di_get_state(void *dev, uint32_t size, void *buf); /* GetDeviceState; 0 — успех */
void    plat_input_enable(int on);                 /* v2.03 (SDL): GetDeviceState клавиатуры — SDL/геймпад/RE_KEYS (только игра) */
void    plat_input_fill_keys(uint8_t *keys256);    /* v2.03 (SDL): добавить нажатые клавиши (DIK, 0x80) */
int     plat_key_dik(const char *name);            /* v2.03 (SDL): имя клавиши/номер → DIK, -1 — неизвестно */
int     plat_frame_no(void);                       /* v2.03 (SDL): номер последнего показанного кадра (plat_flip) */
int32_t plat_di_poll(void *dev);                       /* IDirectInputDevice2::Poll; 0 или 1 (DI_NOEFFECT) — успех */
void    plat_di_stub_joy(int32_t x, int32_t y, int32_t poll_rc); /* тест (SDL): что вернёт джойстик (lX, lY) и Poll */
void    plat_event_close(void *h);                     /* CloseHandle события */
int     plat_di_stub_counts(int *releases, int *unacquires, int *events_closed, int *last_kind); /* для тестов (SDL: счётчики, hook: нули) */
void    plat_di_stub_fail_state(int on);               /* тест: GetDeviceState возвращает ошибку */
/* DirectInput Force Feedback: эффект постоянной силы. kind 0 — «удар» (250000 мкс, gain 10000, 2 оси), kind 1 — «двигатель» (15000 мкс, gain 7500, 1 ось) */
int32_t plat_di_enum_effect(void *dev, uint8_t guid[16]);                     /* EnumEffects(DIEFT_CONSTANTFORCE): GUID первого эффекта; 0 — успех */
int32_t plat_di_create_effect(void *dev, int kind, const uint8_t *guid, void **out); /* CreateEffect; 0 — успех */
int32_t plat_di_set_effect(void *eff, int kind, int32_t dx, int32_t dy, int32_t magnitude); /* SetParameters(START|...): kind 0 — направление (dx,dy)+сила, kind 1 — только сила */
int     plat_di_stub_effects(int *created, int *created_kind, int *sets, int *set_kind, int32_t *dx, int32_t *dy, int32_t *mag); /* тесты (SDL) */
void    plat_di_stub_fail_enum(int on);                /* тест: EnumEffects ошибка */
/* DirectInput: создание и настройка (InitInput 004e2ee0, колбэк джойстиков 004e3cdf) */
typedef int32_t (*plat_di_joy_cb)(const void *inst, void *di);   /* inst: DIDEVICEINSTANCE (guidInstance +4, dwDevType +0x24); 1 — продолжить, 0 — стоп */
void   *plat_di_create(void *hinst, uint32_t version);           /* DirectInputCreateA(hinst, version); NULL — ошибка */
void   *plat_di_create_sys_device(void *di, int kind);           /* CreateDevice(GUID_SysKeyboard (0) / GUID_SysMouse (1)); NULL — ошибка */
void   *plat_di_create_device(void *di, const void *guid);       /* CreateDevice(guid); NULL — ошибка */
void   *plat_di_query_device2(void *dev);                        /* QueryInterface(IDirectInputDevice2A), исходный объект остаётся у вызывающего; NULL — ошибка */
int32_t plat_di_set_coop(void *dev, void *hwnd, uint32_t flags); /* SetCooperativeLevel; 0 — успех */
int32_t plat_di_set_event(void *dev, void *ev);                  /* SetEventNotification; 0 — успех */
int32_t plat_di_set_prop(void *dev, int prop, uint32_t obj, uint32_t how, int32_t a, int32_t b); /* SetProperty: prop 1 буфер (a — размер), 4 диапазон (a..b), 5 мёртвая зона (a); 0 — успех */
int32_t plat_di_get_caps_flags(void *dev, uint32_t *flags);      /* GetCapabilities → DIDEVCAPS.dwFlags (0x100 — Force Feedback); 0 — успех */
int32_t plat_di_enum_joysticks(void *di, plat_di_joy_cb cb);     /* EnumDevices(DIDEVTYPE_JOYSTICK, ATTACHEDONLY); колбэк получает di; 0 — успех */
void   *plat_event_create(void);                                 /* CreateEvent (авто-сброс); NULL — ошибка */
/* тесты (SDL): сколько джойстиков «подключено», флаги устройства, маска отказов (бит: 0 create, 1 sys_device, 2 device, 3 query, 4 coop, 5 event, 6 prop, 7 caps, 8 acquire, 9 event_create) */
void    plat_di_stub_setup(int joysticks, uint32_t caps_flags, uint32_t fail_mask);
int     plat_di_stub_init_stats(int *devices, int *coops, int *props, int *queries); /* SDL: счётчики вызовов */
/* DirectDraw: создание объекта и режим экрана */
void   *plat_dd_create(const void *guid);              /* DirectDrawCreate(guid, &dd, NULL); NULL — ошибка */
int32_t plat_dd_get_display_flags(void *dd, uint32_t *pixfmt_flags); /* GetDisplayMode → ddpfPixelFormat.dwFlags; HRESULT */
void    plat_dd_stub_display(uint32_t pixfmt_flags, int fail_create, int fail_mode);  /* тесты (SDL) */
/* FMV (DirectShow MultiMedia Stream) и DirectSound: 0048ae12, 0048b2fd, 0048b32b, 0048b34c, 0048b65d, 0048bdcc, 0048be68 */
int32_t plat_mms_set_state(void *mms, int state);                         /* IMultiMediaStream::SetState (1 — идти, 0 — стоп); 0 — успех */
int32_t plat_sample_update(void *sample);                                 /* IStreamSample::Update(0,0,0,0); 0 — успех */
int32_t plat_dd_blt_from(void *dst, const int32_t *rect4, void *src);     /* dst->Blt(rect, src, NULL, DDBLT_WAIT, NULL); 0 — успех */
int32_t plat_dd_fill_all(void *surf, uint32_t pixel);                     /* Blt на всю поверхность: DDBLT_COLORFILL */
int32_t plat_ds_set_format(void *primary, const void *wfx18);             /* IDirectSoundBuffer::SetFormat(WAVEFORMATEX, 18 байт) */
int32_t plat_ds_set_speaker_config(void *ds, uint32_t cfg);               /* IDirectSound::SetSpeakerConfig */
/* DirectSound 3D (0048bd40, 0048c74b…0048cba4): слушатель IDirectSound3DListener, буфер IDirectSoundBuffer, 3D-буфер IDirectSound3DBuffer; 0 — успех */
int32_t plat_ds_listener_set_position(void *l, float x, float y, float z);       /* SetPosition(x,y,z,DS3D_IMMEDIATE=1) */
int32_t plat_ds_listener_set_orientation(void *l, const float *six);             /* SetOrientation(front xyz, top xyz, 1) */
int32_t plat_ds_listener_set_velocity(void *l, float x, float y, float z);       /* SetVelocity(x,y,z,1) */
int32_t plat_ds_listener_commit(void *l);                                        /* CommitDeferredSettings */
int32_t plat_ds_buf_play(void *b, uint32_t flags);                               /* Play(0,0,flags) */
int32_t plat_ds_buf_set_volume(void *b, int32_t vol);                            /* SetVolume (сотые дБ) */
int32_t plat_ds_buf_set_frequency(void *b, uint32_t hz);                         /* SetFrequency */
int32_t plat_ds_buf_get_status(void *b, uint32_t *status);                       /* GetStatus */
int32_t plat_ds3d_set_mode(void *b3d, uint32_t mode);                            /* SetMode(mode, DS3D_IMMEDIATE=0) */
int32_t plat_ds3d_set_position(void *b3d, float x, float y, float z);            /* SetPosition(x,y,z,1) */
int32_t plat_ds3d_set_velocity(void *b3d, float x, float y, float z);            /* SetVelocity(x,y,z,1) */
int     plat_ds3d_stub_last(int *op, float *v6, uint32_t *u);                    /* тесты (SDL): последний вызов (op 1..11), числа, целое */
int32_t plat_ds_buf_stop(void *b);                                               /* IDirectSoundBuffer::Stop */
int32_t plat_ds_buf_set_position(void *b, uint32_t pos);                         /* SetCurrentPosition */
int32_t plat_ds3d_set_velocity_ex(void *b3d, float x, float y, float z, uint32_t apply);   /* SetVelocity с явным режимом применения */
int32_t plat_ds_create_buffer(void *ds, uint32_t flags, uint32_t bytes, const void *wfx18, void **out);   /* CreateSoundBuffer(DSBUFFERDESC 20 байт); 0 — успех */
int32_t plat_com_query_interface(void *obj, const void *iid16, void **out);      /* IUnknown::QueryInterface; 0 — успех */
int32_t plat_ds_prop_set(void *ps, const void *guid16, uint32_t id, const void *data, uint32_t len);   /* IKsPropertySet::Set */
int32_t plat_ds_prop_support(void *ps, const void *guid16, uint32_t id, uint32_t *support);            /* IKsPropertySet::QuerySupport */
/* v1.93: DirectSound — создание, перечисление драйверов, кооперативный уровень, дубликат, Lock/Unlock/Restore (0048ba20..0048cdab); 0 — успех */
typedef int32_t (*plat_ds_enum_cb)(const void *guid16, const char *desc, const char *module, void *ctx);   /* 1 — продолжить, 0 — стоп */
int32_t plat_ds_enumerate(plat_ds_enum_cb cb, void *ctx);                        /* DirectSoundEnumerateA */
int32_t plat_ds_create(const void *guid16, void **out);                          /* DirectSoundCreate(guid, &ds, NULL) */
int32_t plat_ds_set_coop(void *ds, void *hwnd, uint32_t level);                  /* IDirectSound::SetCooperativeLevel */
int32_t plat_ds_get_caps_flags(void *ds, uint32_t *flags);                       /* IDirectSound::GetCaps → DSCAPS.dwFlags (0x20 — эмуляция) */
int32_t plat_ds_duplicate(void *ds, void *src, void **out);                      /* IDirectSound::DuplicateSoundBuffer */
int32_t plat_ds_buf_lock(void *b, uint32_t bytes, void **p1, uint32_t *n1, void **p2, uint32_t *n2);   /* Lock(0, bytes, …, 0) */
int32_t plat_ds_buf_unlock(void *b, void *p1, uint32_t n1, void *p2, uint32_t n2);                     /* Unlock */
int32_t plat_ds_buf_restore(void *b);                                            /* Restore */
/* тесты (SDL): драйверы для перечисления (guid NULL — основной), маска отказов (бит 0 Create, 1 GetCaps, 2 Coop, 3 Duplicate, 4 Lock, 5 Restore, 6 — Duplicate один раз даёт DSERR_BUFFERLOST), caps, разрез Lock */
void    plat_ds_stub_drivers(int n, const uint8_t (*guids)[16], const char *const *names, uint32_t caps);
void    plat_ds_stub_dsfail(uint32_t mask, uint32_t split);
int     plat_ds_stub_dsstats(int *creates, int *coop_level, int *dups, int *locks, int *unlocks, int *restores, uint8_t *last_lock64);
void    plat_ds_stub_ctl(uint32_t fail_mask, uint32_t support);                  /* тесты (SDL): bit0 — CreateBuffer падает, bit1 — QI падает, bit2 — QuerySupport падает */
int     plat_ds_stub_prop(uint8_t *guid16, uint32_t *id, uint32_t *len, uint32_t *data0, int *count);   /* тесты (SDL): последний Set */
void    plat_fmv_stub_fail(uint32_t mask);                                /* тесты (SDL): бит 0 SetState, 1 Update, 2 Blt — отказ */
int     plat_fmv_stub_stats(int *state, int *updates, int32_t *rect4, int *blts, uint32_t *fill_px, int *fills, uint8_t *fmt18, uint32_t *spk); /* тесты (SDL) */
/* Поверхности: блокировка, формат пикселей, показ кадра (0041eb8c, 0041ec82, 0041d3ed, 0041dec8, 00420c5a, 00420cac, 00421149) */
int32_t plat_dd_lock(void *surf, void *desc124);                          /* Lock(NULL, desc, DDLOCK_WAIT, NULL); desc[0]=0x7c; lpSurface — desc[9], pitch — desc[4]; HRESULT */
int32_t plat_dd_unlock(void *surf);                                       /* Unlock(NULL) */
int32_t plat_dd_get_pixel_format(void *surf, uint32_t *pf8);              /* GetPixelFormat: DDPIXELFORMAT 32 байта (pf8[0]=0x20 на входе); HRESULT */
void   *plat_dd_query_dd4(void *dd);                                      /* QueryInterface(IID_IDirectDraw4); NULL — ошибка */
void   *plat_dd_query_d3d(void *dd);                                      /* QueryInterface(IID_IDirect3D3); NULL — ошибка */
void    plat_window_client_rect(void *hwnd, int32_t *rc4);                /* GetClientRect: left, top, right, bottom */
void    plat_client_to_screen(void *hwnd, int32_t *pt2);                  /* ClientToScreen: x, y */
int32_t plat_dd_clipper_set_hwnd(void *clipper, void *hwnd);              /* IDirectDrawClipper::SetHWnd(0, hwnd) */
int32_t plat_dd_blt_rect(void *dst, const int32_t *drc4, void *src, const int32_t *src_rc4); /* dst->Blt(drc, src, src_rc, 0, NULL); 0 — успех */
int32_t plat_dd_flip(void *surf, uint32_t flags);                         /* Flip(NULL, flags); HRESULT */
/* тесты (SDL): lock_fail — отказ Lock; pf: bitcount, маски R,G,B для GetPixelFormat (pf_fail — отказ) */
void    plat_dd_stub_surface(int lock_fail, int pf_fail, uint32_t bits, uint32_t rmask, uint32_t gmask, uint32_t bmask, int32_t flip_hr);
int     plat_dd_stub_surface_stats(int *locks, int *unlocks, int *flips, uint32_t *flip_flags, int *blts, int32_t *drc4, int32_t *src_rc4, int *clip_sets);
/* v1.94: перечисление DirectDraw/Direct3D (блок 0041ce90..0042d384) */
typedef int32_t (*plat_dd_enum_cb)(const void *guid16, const char *desc, const char *name, void *ctx);   /* 1 — продолжить, 0 — стоп */
int32_t plat_dd_enumerate(plat_dd_enum_cb cb, void *ctx);                 /* DirectDrawEnumerateA; HRESULT */
typedef int32_t (*plat_d3d_dev_cb)(const void *guid16, const char *desc, const char *name, const void *hw_desc, const void *hel_desc, void *ctx);
int32_t plat_d3d_enum_devices(void *d3d, plat_d3d_dev_cb cb, void *ctx);  /* IDirect3D3::EnumDevices (D3DDEVICEDESC 0xfc байт); HRESULT */
void    plat_dd_stub_enum(int n_dd, int n_dev, uint32_t fail_mask);       /* тесты (SDL): bit0 — отказ DirectDrawEnumerate, bit1 — отказ EnumDevices */
/* v1.95: FMV через DirectShow (0048a940, 0048ac1c, 0048af23, 0048b3e8), окно (005224a8); HRESULT, 0 — успех */
int32_t plat_com_create(const void *clsid16, const void *iid16, void **out);   /* CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, iid, out) */
int32_t plat_mms_initialize(void *amms, uint32_t type, uint32_t flags, void *graph);   /* IAMMultiMediaStream::Initialize (vtable 0x30) */
int32_t plat_mms_add_stream(void *amms, void *src, const void *purpose16, uint32_t flags);   /* AddMediaStream(src, purpose, flags, NULL) (0x3c) */
int32_t plat_mms_open_file(void *amms, const char *path, uint32_t flags);     /* MultiByteToWideChar(CP_ACP, 0x104) + OpenFile (0x40) */
int32_t plat_mms_get_stream(void *mms, const void *purpose16, void **out);     /* IMultiMediaStream::GetMediaStream (0x10) */
int32_t plat_ddms_get_format(void *ddms, void *desc108);                       /* IDirectDrawMediaStream::GetFormat(desc, NULL, NULL, NULL) (0x24) */
int32_t plat_ddms_create_sample(void *ddms, void *surf, const int32_t *rect4, uint32_t flags, void **out);   /* CreateSample (0x34) */
int32_t plat_dd_get_surface_desc(void *surf, void *desc108);                   /* IDirectDrawSurface::GetSurfaceDesc (0x58), desc[0] = размер */
int32_t plat_media_get_duration(void *mpos, double *sec);                      /* IMediaPosition::get_Duration (0x1c) */
void    plat_window_update(void *hwnd);                                        /* UpdateWindow */
void    plat_window_foreground(void *hwnd);                                    /* SetForegroundWindow */
int32_t plat_wm_create_hinst(int32_t lparam);                                  /* WM_CREATE: CREATESTRUCTA.hInstance (+4); SDL — lparam как есть */
/* тесты (SDL): FMV — mask отказов (бит 0 CoCreate, 1 QI, 2 Initialize, 3 AddStream видео, 4 AddStream звук, 5 OpenFile,
   6 GetMediaStream, 7 GetFormat, 8 GetSurfaceDesc, 9 CreateSample, 10 get_Duration), w×h формата, длительность; ok — 0 = все отказы */
void    plat_fmv_stub_open(int ok, uint32_t fail_mask, int32_t w, int32_t h, double dur);
int     plat_fmv_stub_open_stats(int *creates, int *opens, char *last_path64, int *samples, int32_t *rect4, int *fg, int *upd);
/* --- v1.96: окно/DirectDraw (0041ed98, 00420038, 00425f7b) и WinMain (00521f10) --- */
void    plat_window_move(void *hwnd, int x, int y, int w, int h, int repaint);  /* MoveWindow */
void   *plat_window_active(void);                                             /* GetActiveWindow; SDL — окно игры или NULL */
int32_t plat_dd_get_caps(void *dd, void *hal380, void *hel380);              /* IDirectDraw4::GetCaps (0x2c), DDCAPS 0x17c (dwSize заполнен); HRESULT */
typedef int32_t (*plat_pf_enum_cb)(const uint32_t *pixfmt8, uint8_t *ctx);    /* DDPIXELFORMAT 32 байта; 1 — продолжить */
int32_t plat_d3d_enum_tex_formats(void *dev, plat_pf_enum_cb cb, void *ctx); /* IDirect3DDevice3::EnumTextureFormats (0x20); HRESULT */
int32_t plat_d3d_enum_zbuffer(void *d3d, const void *dev_guid, plat_pf_enum_cb cb, void *ctx); /* IDirect3D3::EnumZBufferFormats (0x28); HRESULT */
void   *plat_cursor_set(void *cursor);                                        /* SetCursor: возвращает прежний; SDL — NULL прячет, иное показывает */
void   *plat_current_process(void);                                           /* GetCurrentProcess (псевдо-дескриптор −1) */
void   *plat_load_accelerators(void *hinst, const char *name);                /* LoadAcceleratorsA; SDL — NULL (таблиц ускорителей нет) */
void    plat_dd_stub_caps(uint32_t fail_mask, uint32_t caps2);                /* тесты (SDL): bit0 GetCaps, bit1 EnumTextureFormats, bit2 EnumZBuffer; dwCaps2 HAL */
int     plat_win_moves(int32_t *last5);                                       /* тесты (SDL): число MoveWindow и последний x,y,w,h,repaint; hook — 0 */
#endif
