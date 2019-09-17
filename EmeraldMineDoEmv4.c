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
#include <exec/types.h>
#include <dos/dos.h>


int main(void)
{
        return RETURN_OK;
}