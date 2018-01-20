#ifndef MARINECORE_INIT_H
#define MARINECORE_INIT_H

#include "wallet.h"

extern CWallet* pwalletMain;

void StartShutdown();
void Shutdown(void* parg);
bool AppInit2();
std::string HelpMessage();

#endif
