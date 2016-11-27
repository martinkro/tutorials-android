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
        char line[2048] = {0};
        while(fgets(line, sizeof(line), fp)){
            unsigned long start, end;
            int offset, dev_major, dev_minor, inode;

            char read, write, exec, cow;
            char filename[1024] = { 0 };
            if(sscanf(line, "%lx-%lx %c%c%c%c %x %x:%x %d %s",
                            &start, &end,
                            &read, &write, &exec, &cow, &offset,
                            &dev_major, &dev_minor, &inode, filename) >= 11){


                if (strstr(filename, module_name) != NULL){
                    DEBUG_LOG("%x-%x %c%c%c%c %08x %d:%d %d %s",
                                                                start,
                                                                end,
                                                                read,
                                                                write,
                                                                exec,
                                                                cow,
                                                                offset,
                                                                dev_major,
                                                                dev_minor,
                                                                inode,
                                                                filename
                                                        );
                    DEBUG_LOG("line:%s", line);
                    DEBUG_LOG("[++++++++++++++++++]");
                    char out_name[512];
                    snprintf(out_name, sizeof(out_name), "/data/local/tmp/%08x-%08x.dat", start,end);
                    FILE* f = fopen(out_name, "wb");
                    fwrite((void*)start, 1, end-start, f);
                    fclose(f);
                    if (base == 0)
                    {
                        base = start;
                    }

                    //break;
                }
            }
        }

        fclose(fp);
    }

    return base;
}
