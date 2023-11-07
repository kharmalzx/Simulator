#include "StateCheckout.h"

StateCheckout::StateCheckout(QObject *parent) :AbstractCustomerState(parent)
{}

StateCheckout::~StateCheckout()
{}

void StateCheckout::onEntry(QEvent * e)
{
}


void StateCheckout::onInterruption() {


}

void StateCheckout::toMove()
{
}
