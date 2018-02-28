#pragma once

#include "ModuleManager.h"

class MultiInteractionPluginImpl : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	void StartupModule();
	void ShutdownModule();
};