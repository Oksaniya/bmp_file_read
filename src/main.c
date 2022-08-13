#include "../inc/common.h"

int main(int argc, char **argv)
{
  t_header header;
  t_InfoHeader InfoHeader;
  t_ColorTable ColorTable;
  FILE *file_pointer;

  _Static_assert(14 == sizeof(header), "Struct 'header' size doesn't match");
  _Static_assert(40 == sizeof(InfoHeader), "Struct 'InfoHeader' size doesn't match");
  _Static_assert(4 == sizeof(ColorTable), "Struct 'ColorTable' size doesn't match");
  
  file_pointer = fopen(argv[1], "r+");
  if (file_pointer == NULL)
  {
    exit(EXIT_FAILURE);
  }

  argc_check(argc);
  header_decoder(file_pointer, &header);
  InfoHeader_decoder(file_pointer, &InfoHeader);
  ColorTable_decoder(file_pointer, &ColorTable);
  Bits_Per_Pixel_Field_Check(&InfoHeader);

  fclose(file_pointer);
  return 0;
}

void header_decoder(FILE *file_pointer, t_header *header)
{
  memset((void*)header, 0, FULL_HEADER);
  fread((void*)header, sizeof(*header), 1, file_pointer);

  printf("\nFULL_HEADER has %d bytes.\n", FULL_HEADER);
  printf("BPM Ident = 0x%04X \n", header->identifyer);
  printf("File size = %u \n", header->file_in_bytes);
  printf("Reserved = %u \n", header->reserved);
  printf("DataOffset = %u \n\n", header->DataOffset);
}

void InfoHeader_decoder(FILE *file_pointer, t_InfoHeader *InfoHeader)
{
  memset((void*)InfoHeader, 0, INFO_HEADER);
  fread((void*)InfoHeader, INFO_HEADER, 1, file_pointer);

  printf("\nINFO_HEADER has %d bytes.\n", INFO_HEADER);
  printf("Size_ = %u \n", InfoHeader->Size_);
  printf("Width = %u \n", InfoHeader->Width);
  printf("Height = %u \n", InfoHeader->Height);
  printf("Planes = %u \n", InfoHeader->Planes);
  printf("Bits_Per_Pixel = %u \n", InfoHeader->Bits_Per_Pixel);
  printf("Compression = %u \n", InfoHeader->Compression);
  printf("ImageSize = %u \n", InfoHeader->ImageSize);
  printf("XpixelsPerM = %u \n", InfoHeader->XpixelsPerM);
  printf("YpixelsPerM = %u \n", InfoHeader->YpixelsPerM);
  printf("Colors_Used = %u \n", InfoHeader->Colors_Used);
  printf("Important_Colors = %u \n\n", InfoHeader->Important_Colors);
}

void ColorTable_decoder(FILE *file_pointer, t_ColorTable *ColorTable)
{
  memset((void*)ColorTable, 0, COLOR_TABLE);
  fread((void*)ColorTable, COLOR_TABLE, 1, file_pointer);

  printf("\nCOLOR_TABLE has %d bytes.\n", COLOR_TABLE);
  printf("Red = %u \n", ColorTable->Red);
  printf("Green = %u \n", ColorTable->Green);
  printf("Blue = %u \n", ColorTable->Blue);
  printf("Reserved = %u \n\n", ColorTable->Reserved);
}

void Bits_Per_Pixel_Field_Check(t_InfoHeader *InfoHeader)
{
  switch (InfoHeader->Bits_Per_Pixel)
  {
  case 1:
    printf("The bitmap is monochrome, and the palette contains two entries.\n\n");
    break;

  case 4:
    printf("The bitmap has a maximum of 16 colors, and the palette contains up to 16 entries.\n\n");
    break;
  
  case 8:
    printf("The bitmap has a maximum of 256 colors, and the palette contains up to 256 entries.\n\n");
    break;

  case 16:
    printf("The bitmap has a maximum of 2^16 colors.\n\n");
    break;

  case 32:
    printf("The bitmap has a maximum of 2^24 colors, and the Palette field does not contain any entries.\n\n");
    break;

  default:
    break;
  }
}

void argc_check(int argc)
{
    if (argc != 2)
    {
        printf("You shpuld enter 2 arguments. Than the program will work properly)\n");
        exit(1);
    }
}