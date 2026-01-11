/*
 * Copyright (c) 2021 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 */

#include "utilities.h"
#include "eeprom-board.h"
#include "hardware/flash.h"
#include "hardware/sync.h"

#define EEPROM_READ_START (XIP_BASE + PICO_FLASH_SIZE_BYTES - 2*FLASH_BLOCK_SIZE)
#define EEPROM_WRITE_START (PICO_FLASH_SIZE_BYTES - 2*FLASH_BLOCK_SIZE)

uint8_t EepromMcuReadBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    
    uint8_t* flash = (uint8_t*) EEPROM_READ_START;
    memcpy1(buffer, flash, size);

    return SUCCESS;
}

uint8_t EepromMcuWriteBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    uint32_t ints = save_and_disable_interrupts();
    flash_range_program(EEPROM_WRITE_START + addr, buffer, size);
    restore_interrupts(ints);
    return SUCCESS;
}
