#ifndef HEADER_MP3
#define HEADER_MP3

#include <stdio.h>
#include <string.h>

typedef enum
{
    e_success,
    e_failure,
}Status;

Status read_tags(FILE *Fptr);
Status edit_tags(FILE *org,FILE *dup,char *usr_str,char *tag);
void copy_remaining(FILE* src,FILE* dest);

#endif
