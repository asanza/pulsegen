#ifndef EA525B5E_D3AF_4246_A15F_F9AD018BEE71
#define EA525B5E_D3AF_4246_A15F_F9AD018BEE71

#include <stdint.h>

#define HAL_FLASH_SECTOR_SIZE   (2048)
#define HAL_FLASH_SECTOR_COUNT  (262144/2048)

int
hal_flash_init( void );

int
hal_flash_write(uint32_t address, const void *src, uint32_t len);

int
hal_flash_erase_sector(uint32_t sector_address);

int
hal_flash_write_word(uint32_t address, uint32_t val);


#endif /* EA525B5E_D3AF_4246_A15F_F9AD018BEE71 */
