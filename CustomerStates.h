#pragma once

#ifndef CUSTOMERSTATES_H
#define CUSTOMERSTATES_H

#include <qstate.h>
#include <qsignaltransition.h>
#include "Customer.h"
#include "CustomerMachine.h"
#include "StateMove.h"
#include "StateEnter.h"
#include "StateQueue.h"
#include "StateFetch.h"
#include "StateCheckout.h"

enum CustomerState
{
	STATE_PURCHASE,
	STATE_MOVE,
	STATE_QUEUE,
	STATE_ENTER,
	STATE_EXIT,
	STATE_CHECKOUT,
	STATE_SERVICE
};

#endif // CUSTOMERSTATES_H