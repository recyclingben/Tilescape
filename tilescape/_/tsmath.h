#pragma once


static inline int8_t max8(int8_t a, int8_t b) {
    return a - ((a - b) & (a - b) >> 31);
}

static inline uint8_t umax8(uint8_t a, uint8_t b) {
    return (uint8_t)max8((int8_t)a, (int8_t)b);
}