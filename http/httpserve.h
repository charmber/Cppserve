#ifdef _WIN32

#include "win.h"

#elif _WIN64

#include "win64.h"

#elif __APPLE__

#include "mac_linuxserve.h"

#elif __linux

#include "linux_httpserve.h"

#elif __unix

#include "unix.h"

#elif __posix

#include "posix.h"

#endif
