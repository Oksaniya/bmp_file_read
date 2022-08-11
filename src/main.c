#include "../inc/common.h"

t_buff buff;

int main(int argc, char **argv)
{
  //t_buff buff;
  t_header header;
  FILE *file_pointer;

 // _Static_assert(15 == sizeof(header), "Struct 'header' size doesn't match");
  file_pointer = fopen(argv[1], "r+");
  if (file_pointer == NULL)
  {
    exit(EXIT_FAILURE);
  }
  printf("size_f struct %lu \n", sizeof(header));
  argc_check(argc);
  header_decoder(file_pointer, &header);
  fclose(file_pointer);


  int fd = 0;
  fd = open(argv[1], FULL_HEADER);
  ssize_t res = 0;
  uint8_t buffer[14];

  res = read(fd, (void *)buffer, 14);

  for (int n = 0; n < FULL_HEADER; n++)
  {
    printf("%x ", buffer[n]);
  }
  printf("\n\n");

  fclose(file_pointer);
  return 0;
}

void header_decoder(FILE *file_pointer, t_header *header)
{
  //header->identifyer[2] = 0;
  /*
  fread((void*)header->identifyer, IDENTIFYER, 1, file_pointer);
  fread((void*)&header->file_in_bytes, FILE_IN_BYTES, 1, file_pointer);
  fread((void*)&header->reserved, RESERVED, 1, file_pointer);
  fread((void*)&header->DataOffset, DATA_OFFSET, 1, file_pointer);
*/
memset((void*)header, 0, FULL_HEADER);
printf("sizeof header = %zu\n", sizeof(*header));
fread((void*)header, sizeof(*header), 1, file_pointer);

  printf("BPM Ident = 0x%04X \n", header->identifyer);
  printf("File size = %u \n", header->file_in_bytes);
  printf("Reserved = %u \n", header->reserved);
  printf("DataOffset = %u \n", header->DataOffset);
}

/*
char *ft_strnew(size_t size)
{
    char *str;
    str = (char *)malloc(size);

    if (str == NULL)
    {
        return NULL;
    }

    ft_bzero((void *)str, size);
    return str;
}

void ft_bzero(void *ptr, size_t size)
{
	size_t	iterator;
	char	*p;
	
	p = (char *)ptr;
	iterator = 0;
	while (iterator < size)
	{
		p[iterator] = 0;
        iterator++;
	}
}*/

void argc_check(int argc)
{
    if (argc != 2)
    {
        printf("You shpuld enter 2 arguments. Than the program will work properly)\n");
        exit(1);
    }
}