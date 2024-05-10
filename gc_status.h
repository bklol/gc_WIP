/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * CS2Fixes
 * Written by xen and poggu
 * ======================================================
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from 
 * the use of this software.
 */

#pragma once

#include <ISmmPlugin.h>
#include <sh_vector.h>
#include <iserver.h>
#include <functional>

template <typename T, int index, typename ...Args>
constexpr T CallVFunc(void* pThis, Args... args) noexcept
{
    return reinterpret_cast<T(*)(void*, Args...)> (reinterpret_cast<void***>(pThis)[0][index])(pThis, args...);
}

#ifdef _WIN32
#define WIN_LINUX(win, linux) win
#else
#define WIN_LINUX(win, linux) linux
#endif

class gc_status : public ISmmPlugin, public IMetamodListener
{
public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	void Hook_StartupServer(const GameSessionConfiguration_t& config, ISource2WorldSession*, const char*);
	bool Pause(char *error, size_t maxlen);
	bool Unpause(char *error, size_t maxlen);
	void AllPluginsLoaded();
public:
	const char *GetAuthor();
	const char *GetName();
	const char *GetDescription();
	const char *GetURL();
	const char *GetLicense();
	const char *GetVersion();
	const char *GetDate();
	const char *GetLogTag();
};

extern gc_status g_gc_status;

PLUGIN_GLOBALVARS();
