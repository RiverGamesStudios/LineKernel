#ifndef __IDE_H__
#define __IDE_H__
#include "bios_tools.h"

void ide_write(unsigned char channel, unsigned char reg, unsigned char data);
unsigned char ide_read(unsigned char channel, unsigned char reg);
void ide_read_buffer(unsigned char channel, unsigned char reg, unsigned int buffer,
                     unsigned int quads);
unsigned char ide_polling(unsigned char channel, unsigned int advanced_check);
unsigned char ide_print_error(unsigned int drive, unsigned char err);
void ide_initialize(unsigned int BAR0, unsigned int BAR1, unsigned int BAR2, unsigned int BAR3,
unsigned int BAR4);
unsigned char ide_ata_access(unsigned char direction, unsigned char drive, unsigned int lba, 
                             unsigned char numsects, unsigned short selector, unsigned int edi);
void ide_wait_irq();
void ide_irq();
unsigned char ide_atapi_read(unsigned char drive, unsigned int lba, unsigned char numsects,
          unsigned short selector, unsigned int edi);
void ide_read_sectors(unsigned char drive, unsigned char numsects, unsigned int lba,
                      unsigned short es, unsigned int edi);
void ide_write_sectors(unsigned char drive, unsigned char numsects, unsigned int lba,
                       unsigned short es, unsigned int edi);
void ide_atapi_eject(unsigned char drive);

/* Extra helper functions */
int ide_is_device(int device);
const char* ide_access_device_ata_pi(int device);
unsigned char* ide_access_device_model(int device);
char read_package0_error();

#endif
