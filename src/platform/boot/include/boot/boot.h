/*******************************************************************************
 *                   * The copyright to the programs herein is  the property   *
 *                   * of ABB STOTZ KONTAKT GmbH. The programs  may be  used   *
 *   A    BBB   BBB  * or copied  only with  the written  permission of  ABB   *
 *  A A   B  B  B  B * STOTZ KONTAKT GmbH  or in  accordance  with the terms   *
 * A   A  B  B  B  B * of the agreement under which the program(s) have been   *
 * AAAAA  BBB   BBB  * supplied.                                               *
 * A   A  B  B  B  B * In no event shall  ABB STOTZ KONTAKT GmbH   be liable   *
 * A   A  B  B  B  B * for incidental or consequential damages  arising from   *
 * A   A  BBB   BBB  * use of this program.                                    *
 *                   *                                                         *
 * Asea Brown Boveri *        COPYRIGHT ABB STOTZ KONTAKT GmbH 2020            *
 *******************************************************************************
 * FILE DESCRIPTION                                                            *
 *---------------------------------------------------------------------------- *
 * DESCRIPTION:                                                                *
 *                                                                             *
 *-----                                                                        *
 * File: system.h                                                              *
 * Project: src                                                                *
 * Created: Tuesday April 7th 2020                                             *
 * Author: Diego Asanza <diego.asanza@de.abb.com>                              *
 ******************************************************************************/

#ifndef SRC_BOOTLOADER_BOOT_SRC_BOOT_H
#define SRC_BOOTLOADER_BOOT_SRC_BOOT_H

#include <stdbool.h>
#include <stdint.h>

#define IMAGE_MAGIC      0x96f3b83c
#define IMAGE_MAGIC_NONE 0xffffffff

struct image_version {
    uint8_t  iv_major;
    uint8_t  iv_minor;
    uint16_t iv_revision;
    uint32_t iv_build_num;
};

/** Image header.  All fields are in little endian byte order. */
struct image_header {
    uint32_t ih_magic;
    uint32_t ih_load_addr;
    uint16_t ih_hdr_size;           /* Size of image header (bytes). */
    uint16_t reserved_1;   
    uint32_t ih_img_size;           /* Does not include header. */
    uint32_t reserved_2;              
    struct image_version ih_ver;
    uint32_t ih_crc32;    /* includes image header, without ih_crc32 */
};

/**
 * @brief Returns true if a valid application is present. False otherwise.
 * 
 * @return true 
 * @return false 
 */
bool boot_check_app( void );

/**
 * @brief Starts the application.
 *        This function never returns.
 */
void boot_start_app( void );

/**
 * @brief gets the application version.
 * 
 * @return pointer to the image version struct
 */
const struct image_version* 
boot_get_app_version(void);

/**
 * @brief Get the image header.
 * 
 * @return pointer to the image header struct.
 */
const struct image_header*
boot_get_app_header(void);

/**
 * @brief Initialize the bootloader module
 * 
 * @return int 0 if ok
 */
int
boot_init( void );

/**
 * @brief Erase the application 
 * 
 * @return int -1 if error
 */
int
boot_erase_app(void);

/**
 * @brief Program len bytes into the application space.
 * 
 * @param addr 
 * @param data 
 * @param len 
 * @return int 
 */
int
boot_program_app(uint32_t addr, uint8_t* data, int len);

/**
 * @brief Start bootloader from application.
 *        This function will clear the image header, so the bootloader will
 *        start after next reset.
 *        @warning This function *must* only be called from application.
 * @return int 0 if successfull.
 */
int
boot_start_from_app(void);

void
boot_reset_counter( void );

#endif /* SRC_BOOTLOADER_BOOT_SRC_SYSTEM */
