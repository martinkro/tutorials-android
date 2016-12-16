#include "test.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static void test_fclose()
{
    FILE* fp = NULL;
    DEBUG_LOG("test_fclose ...");
    fp = fopen("/data/data/com.personal.testn9/lib/libTestN9.so","rb");
    if (fp != NULL)
    {
        DEBUG_LOG("fopen success!");
        uint8_t buf[4096] = {0};
        size_t read_count = fread(buf, 1, sizeof(buf), fp);
        fclose(fp);
    }
    else
    {
        ERROR_LOG("fopen fail:%s", strerror(errno));
    }

}

TEST_FUNC_ARRAY g_func_array = {
        (void*)test_fclose
};
