#include <string>

#include "version.h"


const std::string CLIENT_NAME("Marinecoin-Core");

#define CLIENT_VERSION_SUFFIX   "-mtc"


#ifdef HAVE_BUILD_INFO
#    include "build.h"
#endif

#ifdef GIT_ARCHIVE
#    define GIT_COMMIT_ID "$Format:%h$"
#    define GIT_COMMIT_DATE "$Format:%cD"
#endif

#define STRINGIFY(s) #s

#define BUILD_DESC_FROM_COMMIT(maj,min,rev,build,commit) \
    "v" STRINGIFY(maj) "." STRINGIFY(min) "." STRINGIFY(rev) "." STRINGIFY(build) "-g" commit

#define BUILD_DESC_FROM_UNKNOWN(maj,min,rev,build) \
    "v" STRINGIFY(maj) "." STRINGIFY(min) "." STRINGIFY(rev) "." STRINGIFY(build) "-unk"

#ifndef BUILD_DESC
#    ifdef GIT_COMMIT_ID
#        define BUILD_DESC BUILD_DESC_FROM_COMMIT(CLIENT_VERSION_MAJOR, CLIENT_VERSION_MINOR, CLIENT_VERSION_REVISION, CLIENT_VERSION_BUILD, GIT_COMMIT_ID)
#    else
#        define BUILD_DESC BUILD_DESC_FROM_UNKNOWN(CLIENT_VERSION_MAJOR, CLIENT_VERSION_MINOR, CLIENT_VERSION_REVISION, CLIENT_VERSION_BUILD)
#    endif
#endif

#ifndef BUILD_DATE
#    ifdef GIT_COMMIT_DATE
#        define BUILD_DATE GIT_COMMIT_DATE
#    else
#        define BUILD_DATE __DATE__ ", " __TIME__
#    endif
#endif

const std::string CLIENT_BUILD(BUILD_DESC CLIENT_VERSION_SUFFIX);
const std::string CLIENT_DATE(BUILD_DATE);
