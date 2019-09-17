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
#include <string.h>
#include <exec/types.h>
#include <dos/dos.h>

typedef struct 
{
    char* name;
    long size;

} EngineEntry;

#define ENTRIES_AMOUNT 10

static EngineEntry entries[ENTRIES_AMOUNT] = 
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

static UBYTE* memoryEmv4;

static UBYTE* GetEmv4Memory(void);
static long CopyFilesToEmv4Memory(UBYTE* memory);
static void FreeEmv4Memory(void);
static BOOL WriteEmv4ToFile(UBYTE* memory, long size);
static long CopyEntry(const EngineEntry* entry, UBYTE* memory);
static BOOL ShouldSkipHeader(const EngineEntry* entry);
static FILE* GetFile(const EngineEntry* entry);
//----------------------------------------------------------------------------

int main(void)
{
        UBYTE* memory = GetEmv4Memory();

        if (NULL == memory)
        {
                return RETURN_ERROR;
        }

        long size = CopyFilesToEmv4Memory(memory);

        if (0 == size)
        {
                FreeEmv4Memory();
                return RETURN_ERROR;
        }

        if (FALSE == WriteEmv4ToFile(memory, size))
        {
                FreeEmv4Memory();
                return RETURN_ERROR;
        }

        FreeEmv4Memory();

        return RETURN_OK;
}

//----------------------------------------------------------------------------

static BOOL WriteEmv4ToFile(UBYTE* memory, long size)
{
	FILE* f = fopen("emv4", "wb");

        if (NULL == f)
        {
                printf("Cannot open file 'emv4' to writting.\n");
                return FALSE;
        }

        fwrite(memory, 1, size, f);
        fclose(f);

        return TRUE;
}

//----------------------------------------------------------------------------

static long CopyFilesToEmv4Memory(UBYTE* memory)
{
        for (int i = 0; i < ENTRIES_AMOUNT; ++i)
        {
		long size = CopyEntry(&entries[i], memory);

		if (0 == size)
		{
			return 0;
		}

		if (size & 1)
		{
			size++;
		}

		memory += size;
        }

        return (memory - memoryEmv4);
}

//----------------------------------------------------------------------------

static long CopyEntry(const EngineEntry* entry, UBYTE* memory)
{
	FILE* f = GetFile(entry);

	if (NULL == f)
	{
		return 0;
	}

	long size = entry->size;

	if (TRUE == ShouldSkipHeader(entry))
	{
		fseek(f, 16, SEEK_SET);
		size -= 16;
	}
	
	fread(memory, 1, size, f);
	fclose(f);

	return size;
}

//----------------------------------------------------------------------------

static BOOL ShouldSkipHeader(const EngineEntry* entry)
{
	if (0 == strcmp(entry->name, "em"))
	{
		return FALSE;
	}

	if (0 == strcmp(entry->name, "ems"))
	{
		return FALSE;
	}

	if (0 == strcmp(entry->name, "magic.sh"))
	{
		return FALSE;
	}


	return TRUE;
}

//----------------------------------------------------------------------------

static FILE* GetFile(const EngineEntry* entry)
{
	FILE* f = fopen(entry->name, "rb");

	if (NULL == f)
	{
		printf("Cannot open file: %s\n", entry->name);
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	long size = ftell(f);

	if (entry->size != size)
	{
		printf("Wrong size of file. ");
		printf("Expected %ld bytes but found %ld bytes\n", entry->size, size);
		fclose(f);
		return NULL;
	}

	fseek(f,0, SEEK_SET);
	return f;
}

//----------------------------------------------------------------------------

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
