#include "gc_status.h"
#include "iserver.h"

#include "appframework/IAppSystem.h"
#include "common.h"
#include "icvar.h"
#include "interface.h"
#include "tier0/dbg.h"
#include "plat.h"
#include "igamesystemfactory.h"
#include "tier0/memdbgon.h"
#include "addresses.h"

CBaseGameSystemFactory **CBaseGameSystemFactory::sm_pFirst = nullptr;
ICvar *icvar = NULL;

void Message(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);

	char buf[1024] = {};
	V_vsnprintf(buf, sizeof(buf) - 1, msg, args);

	ConColorMsg(Color(255, 0, 255, 255), "[gc_status] %s", buf);

	va_end(args);
}

class GameSessionConfiguration_t { };

SH_DECL_HOOK3_void(INetworkServerService, StartupServer, SH_NOATTRIB, 0, const GameSessionConfiguration_t&, ISource2WorldSession*, const char*);
gc_status g_gc_status;
PLUGIN_EXPOSE(gc_status, g_gc_status);

bool gc_status::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	GET_V_IFACE_ANY(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
	SH_ADD_HOOK_MEMFUNC(INetworkServerService, StartupServer, g_pNetworkServerService, this, &gc_status::Hook_StartupServer, true);
	GET_V_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
	ConVar_Register( FCVAR_RELEASE | FCVAR_CLIENT_CAN_EXECUTE | FCVAR_GAMEDLL );
	addresses::Initialize();
	return true;
}

bool IsConnectedToGC(void *pGameSystem)
{
	return *(int *)((uint8*)pGameSystem + WIN_LINUX(0x52c, 0x5b4)) == 0;
}

bool gc_status::Unload(char *error, size_t maxlen)
{
	SH_REMOVE_HOOK_MEMFUNC(INetworkServerService, StartupServer, g_pNetworkServerService, this, &gc_status::Hook_StartupServer, true);
	return true;
}

void gc_status::Hook_StartupServer(const GameSessionConfiguration_t& config, ISource2WorldSession*, const char*)
{
	uint8 *ptr = (uint8*)modules::server->FindSignature((uint8*)sigs::IGameSystem_InitAllSystems_pFirst) + 3;
	CBaseGameSystemFactory::sm_pFirst = (CBaseGameSystemFactory **)(ptr + *(uint32*)ptr + 4);
	void *pGameSystem = CBaseGameSystemFactory::GetGlobalPtrByName("CCSGCServerSystem");
	if(pGameSystem)
	{
		Message("Is connect to gc? %s\n",IsConnectedToGC(pGameSystem) ? "yes" : "no");
		if(!IsConnectedToGC(pGameSystem))
		{
			Message("trying  to reconnect gc....\n");
			//addresses::Hello_SERVER_GC((uint8*)pGameSystem + WIN_LINUX(0xb8, 0xb0));
			addresses::Init_CCSGCServerSystem();
			addresses::Init_Steam_GC(pGameSystem);
		}
	}
	else
		Message("cant find CGCClientSystem aka CCSGCServerSystem\n");
}

void gc_status::AllPluginsLoaded()
{

}


bool gc_status::Pause(char *error, size_t maxlen)
{
	return true;
}

bool gc_status::Unpause(char *error, size_t maxlen)
{
	return true;
}

const char *gc_status::GetLicense()
{
	return "";
}

const char *gc_status::GetVersion()
{
	return "0.1";
}

const char *gc_status::GetDate()
{
	return __DATE__;
}

const char *gc_status::GetLogTag()
{
	return "gc_status[WIP]";
}

const char *gc_status::GetAuthor()
{
	return "bklol";
}

const char *gc_status::GetDescription()
{
	return "should reconnect gc when gc fked";
}

const char *gc_status::GetName()
{
	return "gc_status";
}

const char *gc_status::GetURL()
{
	return "https://github.com/bklol";
}
