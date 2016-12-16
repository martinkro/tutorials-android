#include "unpacker.h"
#include "log.h"
#include "test.h"

#include <stdlib.h>

extern void _init(uint32_t base)
{
    DEBUG_LOG("unpacker init xxxx...");
    typedef void(*pfn_test_close)();
    pfn_test_close pfn = (pfn_test_close)g_func_array.test_fclose;
    if (pfn != NULL)
    {
        pfn();
    }
}
