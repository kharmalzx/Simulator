#pragma once

#ifndef CLERKSTATES_H
#define CLERKSTATES_H

#include <qstate.h>
#include <qsignaltransition.h>
#include "Clerk.h"
#include "ClerkMachine.h"
#include "StateClerkMove.h"
#include "StateClerkLoad.h"
#include "StateClerkReplenish.h"
#include "StateClerkService.h"
#include "StateClerkSlack.h"
#include "StateClerkSolicit.h"
#include "StateClerkIdle.h"
#include "StateClerkEnd.h"
#include "StateClerkRest.h"
#include "StateClerkInit.h"
#include "StateClerkWorking.h"
#include "StateClerkClean.h"


enum ClerkAction
{
	MOVE,
	LOAD,
	REPLENISH,
	SERVICE,
	SLACK,
	SOLICIT,
	IDLE,
	REST,
	END,
	INIT,
	WORKING,
	CLEAN
};

#endif // CLERKSTATES_H