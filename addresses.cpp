#include "addresses.h"
#include "utils/module.h"

#include "tier0/memdbgon.h"
#define RESOLVE_SIG(module, sig, variable) variable = (decltype(variable))module->FindSignature((uint8*)sig)

void addresses::Initialize()
{
	modules::server = new CModule(GAMEBIN, "server");
	RESOLVE_SIG(modules::server, sigs::Hello_SERVER_GC, addresses::Hello_SERVER_GC);
}