//----------------------------------------------------------------------------
//  Emerald Mine Do EM V4 - tiny tool to join following files
//  from Amiga game Emerald Mine (release 4):
//  1.  em (main file) (size 30628 bytes). executable
//  2.  ems (soprol file) (size  5872 bytes). executable
//  3.  bassdrum.sh (size 5161 bytes with 16 bytes header)
//  4.  claps.sh (size 2679 bytes with 16 bytes header)
//  5.  lead.sh (size 7662 bytes with 16 bytes header)
//  6.  magic.sh (size 5432 bytes )
//  7.  slapbass.sh (size 7280 bytes with 16 bytes header)
//  8.  snaredrum.sh (size 4969 bytes with 16 bytes header)
//  9.  voice.sh (size 9375 bytes with 16 bytes header)
//  10. whistle.sh (size 11094 bytes with 16 bytes header)
//
//  sample files (from points 3-10) will be stored without header
//  and with even size of bytes
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <exec/types.h>
#include <dos/dos.h>

typedef struct 
{
    char* name;
    long size;

} EngineEntry;

static EngineEntry entries[10] = 
{
    { "em", 30628},
    { "ems", 5872},
    { "bassdrum.sh", 5161},
    { "claps.sh", 2679},
    { "lead.sh", 7662},
    { "magic.sh", 5432},
    { "slapbass.sh", 7280},
    { "snaredrum.sh", 4969},
    { "voice.sh", 9375},
    { "whistle.sh", 11094},
};

//----------------------------------------------------------------------------

int main(void)
{
        //1. allocate engine emv4 memory and clear it

        //2. copy file content into emv4 memory

        //3. write emv4 memory to file emv4

        return RETURN_OK;
}

//----------------------------------------------------------------------------
static UBYTE* memoryEmv4;

static UBYTE* GetEmv4Memory(void)
{
        const size_t size = 100*1024;

        memoryEmv4 = malloc(size);

        if (NULL == memoryEmv4)
        {
                printf("Cannot allocate memory for emv4.\n");
                return NULL;
        }

        UBYTE* memory = memoryEmv4;

        for (int i = 0; i < size; ++i)
        {
                *memory++ = 0;
        }

        return memoryEmv4;
}

static void FreeEmv4Memory(void)
{
        free(memoryEmv4);
}

//----------------------------------------------------------------------------