#include <boot/boot.h>
#include <crc/crc32.h>
#include <hal/hal_flash.h>
#include <stdint.h>

#define COUNTER_KEY 0xD15EA5E
#define MAX_REBOOTS 10

/* following symbols are provided by the linker script */
extern uint32_t __boot_start__;
extern uint32_t __boot_size__;
extern uint32_t __app_start__;
extern uint32_t __app_size__;

/* place the reboot counter into the .noinit section */
struct reboot_counter {
    uint32_t key;
    uint32_t counter;
    uint32_t boot_start;
};

static struct reboot_counter reboot_counter __attribute__((section(".noinit")));

/**
 * @brief Starts the application at given program counter with a given
 *        stack pointer.
 *
 */
__attribute__((naked, noreturn)) static void
start_app(uint32_t pc, uint32_t sp)
{
    (void)pc;
    (void)sp;

    asm("msr msp, r1\n" /* load r1 into MSP */
        "bx r0\n"       /* branch to the address at r0 */
    );
}

/**
 * @brief Starts the application.
 *        This function never returns.
 */
__attribute__((noreturn)) void
boot_start_app(void)
{
    struct image_header *hdr;
    uint32_t *           app;

    /* 
     * increase the reboot counter. This checks how frequently the application
     * boots. After running for some time, the application will reset this
     * reboot counter. If the bootloader detects that the reboot counter rises
     * too high, it knows that the application is not running how it should.
     */
    reboot_counter.key = COUNTER_KEY;
    reboot_counter.counter++;

    hdr = (struct image_header *)&__app_start__;

    app = (uint32_t *)hdr->ih_load_addr;

    start_app(app[1], app[0]);
}

void
boot_reset_counter(void)
{
    reboot_counter.counter = 0;
    /* also clear the start request, if pending */
    reboot_counter.boot_start = 0;
}

/**
 * @brief Returns true if a valid application is present. False otherwise.
 *
 * @return true
 * @return false
 */
bool
boot_check_app(void)
{
    struct image_header *hdr;

    uint32_t crc;
    uint32_t len;

    /* first we check the reboot counter. It indicates an unstable app */
    if ((reboot_counter.key == COUNTER_KEY) &&
        (reboot_counter.counter == MAX_REBOOTS)) {
        /* app failed to reset the reboot counter */
        return false;
    }

    /* second we check if the app has requested a bootloader start */
    if ((reboot_counter.key == COUNTER_KEY) &&
        reboot_counter.boot_start == (IMAGE_MAGIC)) {
        return false;
    }

    /* now check if there is a valid image */
    hdr = (struct image_header *)&__app_start__;

    if (hdr->ih_magic != IMAGE_MAGIC) {
        /* no header */
        return false;
    }

    len = hdr->ih_hdr_size + hdr->ih_img_size;

    if (len > (uint32_t)&__app_size__) {
        /*
         * the length reported by header is greather that the available space
         * in flash. This is not possible so we abort.
         */
        return false;
    }

    if (hdr->ih_load_addr < hdr->ih_hdr_size + (uint32_t)&__app_start__) {
        /* the reported load address is not in the allowed region */
        return 0;
    }

    /* it seems that there is a header present. Proceed to check the app. */
    crc = crc32(0xFFFFFFFF, (uint8_t *)hdr->ih_load_addr, hdr->ih_img_size);

    /* append the crc of the header */
    crc = crc32(crc, (uint8_t *)hdr,
                sizeof(struct image_header) - sizeof(uint32_t));

    /* if checksum does not match, then no valid application is present */
    if (crc != hdr->ih_crc32) {
        return false;
    }

    /* application valid. */
    return true;
}

/**
 * @brief gets the application version.
 *
 * @return pointer to the image version struct
 */
const struct image_version *
boot_get_app_version(void)
{
    struct image_header *hdr;
    hdr = (struct image_header *)&__app_start__;

    if (hdr->ih_magic != IMAGE_MAGIC) {
        return NULL;
    }

    return &hdr->ih_ver;
}

/**
 * @brief Get the image header.
 *
 * @return pointer to the image header struct.
 */

const struct image_header *
boot_get_app_header(void)
{
    struct image_header *hdr;
    hdr = (struct image_header *)&__app_start__;

    if (hdr->ih_magic != IMAGE_MAGIC) {
        return NULL;
    }

    return hdr;
}

int
boot_init(void)
{
    return hal_flash_init();
}

int
boot_erase_app(void)
{
    int rval;

    uint32_t start_addr = (uint32_t)&__app_start__;
    uint32_t end_addr   = (uint32_t)&__app_start__ + (uint32_t)&__app_size__;

    /* delete all sectors occupied by the application */
    for (uint32_t i = start_addr; i < end_addr; i += HAL_FLASH_SECTOR_SIZE) {
        rval = hal_flash_erase_sector(i);
        if (rval != 0) {
            return rval;
        }
    }

    return 0;
}

int
boot_program_app(uint32_t addr, uint8_t *data, int len)
{
    uint32_t start_addr = (uint32_t)&__app_start__;

    return hal_flash_write(addr + start_addr, data, len);
}

int
boot_start_from_app(void)
{
    reboot_counter.key = COUNTER_KEY;
    reboot_counter.boot_start = IMAGE_MAGIC;
    return 0;
}
