#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main() {
    uint32_t data = 0x12345678;
    printf("Content in data: %x\n", data);
    printf("Address of data: %p\n", (void *)&(data));
    bool flag = true;
    while (flag) {
        if (data == 0x11944040) {
            printf("Content in data: %x\n", data);
            flag = false;
        }
    }
    return 0;
}
