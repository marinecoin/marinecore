#ifndef MARINECORE_VERSION_H
#define MARINECORE_VERSION_H

#include <string>


#define CLIENT_VERSION_MAJOR       1
#define CLIENT_VERSION_MINOR       0
#define CLIENT_VERSION_REVISION    0
#define CLIENT_VERSION_BUILD       0

static const int CLIENT_VERSION =
                           1000000 * CLIENT_VERSION_MAJOR
                         +   10000 * CLIENT_VERSION_MINOR 
                         +     100 * CLIENT_VERSION_REVISION
                         +       1 * CLIENT_VERSION_BUILD;

extern const std::string CLIENT_NAME;
extern const std::string CLIENT_BUILD;
extern const std::string CLIENT_DATE;


static const int PROTOCOL_VERSION = 70001;


static const int MIN_PROTO_VERSION = 209;

static const int CADDR_TIME_VERSION = 31402;

static const int NOBLKS_VERSION_START = 32000;
static const int NOBLKS_VERSION_END = 32400;

static const int BIP0031_VERSION = 60000;

#endif
