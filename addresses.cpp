#include "addresses.h"
#include "utils/module.h"

#include "tier0/memdbgon.h"
#define RESOLVE_SIG(module, sig, variable) variable = (decltype(variable))module->FindSignature((uint8*)sig)

void addresses::Initialize()
{
	modules::server = new CModule(GAMEBIN, "server");
	RESOLVE_SIG(modules::server, sigs::Hello_SERVER_GC, addresses::Hello_SERVER_GC);
	RESOLVE_SIG(modules::server, sigs::Init_Steam_GC, addresses::Init_Steam_GC);
	RESOLVE_SIG(modules::server, sigs::Init_CCSGCServerSystem, addresses::Init_CCSGCServerSystem);
	RESOLVE_SIG(modules::server, sigs::Active_GC_session, addresses::Active_GC_session);
}