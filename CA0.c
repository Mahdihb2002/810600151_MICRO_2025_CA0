#include "stm32f10x.h"

int main(void) {
    RCC->APB2ENR |= (1 << 2) | (1 << 3);

    GPIOA->CRL &= ~((0xF << 0) | (0xF << 4) | (0xF << 8));
    GPIOA->CRL |=  ((0x2 << 0) | (0x2 << 4) | (0x2 << 8));

    GPIOB->CRL &= ~((0xF << 4) | (0xF << 12) | (0xF << 16));
    GPIOB->CRL |=  ((0x8 << 4) | (0x8 << 12) | (0x8 << 16));

    uint8_t last1 = 1, last3 = 1, last4 = 1;
    uint8_t now1, now3, now4;

    while (1) {
        now1 = (GPIOB->IDR & (1 << 1)) ? 1 : 0;
        now3 = (GPIOB->IDR & (1 << 3)) ? 1 : 0;
        now4 = (GPIOB->IDR & (1 << 4)) ? 1 : 0;

        if (last1 == 1 && now1 == 0) {
            GPIOA->ODR ^= (1 << 0);
            for (volatile int i = 0; i < 50000; i++);
        }
        if (last3 == 1 && now3 == 0) {
            GPIOA->ODR ^= (1 << 1);
            for (volatile int i = 0; i < 50000; i++);
        }
        if (last4 == 1 && now4 == 0) {
            GPIOA->ODR ^= (1 << 2);
            for (volatile int i = 0; i < 50000; i++);
        }

        last1 = now1;
        last3 = now3;
        last4 = now4;
    }
}
