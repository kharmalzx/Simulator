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


enum ClerkState
{
	STATE_MOVE,
	STATE_LOAD,
	STATE_REPLENISH,
	STATE_SERVICE,
	STATE_SLACK,
	STATE_SOLICIT,
	STATE_IDLE,
	STATE_REST,
	STATE_END,
	STATE_INIT
};

#endif // CLERKSTATES_H