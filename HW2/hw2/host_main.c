#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/kvm.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#define KVM_ARM_WRITE_GPA _IOWR(KVMIO, 0x0b, struct kvm_arm_write_gpa_args)

struct kvm_arm_write_gpa_args {
    uint32_t vmid;
    uint64_t gpa;
    uint64_t data;
    uint64_t size;
};

int main(int argc, char *argv[]) {
    int kvm_fd = open("/dev/kvm", O_RDWR);
    if (kvm_fd < 0) {
	fprintf(stderr, "cannot open kvm device!\n");
	return 1;
    }
    uint64_t vmid = strtoul(argv[1], NULL, 0);
    uint64_t gpa = strtoull(argv[2], NULL, 16);

    uint32_t data = 0x11944040;
    uint64_t size = sizeof(data);
    
    struct kvm_arm_write_gpa_args args = {vmid, gpa, (uint64_t)&data, size};

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <vmid> <gpa>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int ret = ioctl(kvm_fd, KVM_ARM_WRITE_GPA, &args);
    if (ret < 0) {
        printf("Test case failed: %d\n", ret);
    } else {
        printf("Test case succeeded\n");
    }

    close(kvm_fd);
    
    return 0;
}
