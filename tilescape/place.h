#pragma once
#include <stdint.h>
#include <string.h>

#ifndef offset
#define offset(of, by) ((void *)((char *)of + by))
#endif

/* Lo/hi may be in different spots, depending on endianness. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define ts_place_blob(ptr) ((uint16_t *)offset(ptr, 2))
#define ts_place_tile(ptr) ((uint8_t *)offset(ptr, 1))
#define ts_place_mini(ptr) ((uint8_t *)ptr)
#else
#define ts_place_mini(ptr) ((uint8_t *)offset(ptr, 3))
#define ts_place_tile(ptr) ((uint8_t *)offset(ptr, 2))
#define ts_place_blob(ptr) ((uint16_t *)ptr)
#endif
#define ts_place_totl(ptr) (&(ptr)->int_32)


typedef union {
    uint8_t int_8;
    uint16_t int_16;
    uint32_t int_32;
} TSPlace;