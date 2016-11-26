#include "module.h"
#include "log.h"
#include <stdio.h>
#include <string.h>

uintptr_t get_image_base(const char* module_name)
{
    uintptr_t base = 0;

    if (module_name == NULL)
    {
        return base;
    }

    FILE* fp = fopen("/proc/self/maps", "r");
    if (fp != NULL)
    {
        char line[1024] = {0};
        while(fgets(line, sizeof(line), fp)){
            unsigned long start, end;
            int offset, dev_major, dev_minor, inode;
            char read, write, exec, cow;
            char filename[512] = { 0 };
            if(sscanf(line, "%lx-%lx %c%c%c%c %x %x:%x %d %s",
                            &start, &end,
                            &read, &write, &exec, &cow, &offset,
                            &dev_major, &dev_minor, &inode, filename) >= 11){

                if (strstr(filename, module_name) != NULL){
                    base = start;
                    break;
                }
            }
        }

        fclose(fp);
    }

    return base;
}
