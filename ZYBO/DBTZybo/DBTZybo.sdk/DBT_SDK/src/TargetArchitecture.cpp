#include <stdio.h>
#include <stddef.h>

#include "TargetArchitecture.h"

CTargetArchitecture::CTargetArchitecture(int Tcache_size)
      :transCache(Tcache_size)
{
  eoExec = false;
}


CTargetArchitecture::~CTargetArchitecture()
{
}