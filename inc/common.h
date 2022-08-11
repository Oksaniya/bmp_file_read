#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define FULL_HEADER 14
#define IDENTIFYER 2
#define FILE_IN_BYTES 4
#define RESERVED 4
#define DATA_OFFSET 4

typedef struct __attribute__((packed))           s_header
{
    uint16_t            identifyer; //2 bytes: BM * BA * CI * CP * IC * PT
    uint32_t            file_in_bytes; // 4 bytes	The size of the BMP file in bytes
    uint32_t            reserved; //4 bytes: unused (=0)
    uint32_t            DataOffset; //4 bytes: Offset from beginning of file to the beginning of the bitmap data
}                                               t_header;
//struct s_header = {0};


typedef struct          s_buff
{
    int                 i;
}                       t_buff;

void read_f(FILE *fp, t_buff *buff);
char *ft_strnew(size_t size);
void ft_bzero(void *ptr, size_t size);
void argc_check(int argc);
void read_header(FILE *file_pointer, t_header *header);
void header_decoder(FILE *file_pointer, t_header *header);


#endif