#include <sys/sysctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <linux/unistd.h>       /* for _syscallX macros/related stuff */
#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>
#include <time.h>
#include <unistd.h>

#include <string.h> /* for strncpy */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <termios.h>
#include <ifaddrs.h>
#include <sys/vfs.h>
#include <mntent.h> /* for getmntent(), et al. */

#define DEFAULT_DELAY 300
#define DEFAULT_PORT 7
#define MAX_CPU_NUM 16

typedef struct{
    uint32_t total;
    uint32_t cached;
    uint32_t buffered;
    uint32_t free;
    uint32_t used;
}ram_t;

typedef struct{
    char cpuid;
    uint32_t idle;
    uint32_t full;
    uint32_t last_idle;
    uint32_t last_full;
    float pcnt;
}cpu_t;

typedef struct{
    long long now_tx;
    long long now_rx;
    long long last_tx;
    long long last_rx;
    long tx;
    long rx;    
}txrx_t;

typedef struct{
uint32_t total;
uint32_t used;
}swap_t;

typedef struct{
    uint8_t ip[4];

    uint16_t load[3];
    float cpu[4];
    
    uint32_t temp;
    
    ram_t ram;
    swap_t swap;
    swap_t storage; 
    
}udp_pkt;    //64 bytes

typedef struct{
    char proc1[32];
    char proc2[32];
    char proc3[32];
}proc_t;


uint8_t * addr2arr(struct in_addr ipadrr);
void print_help();

uint32_t get_cpu(cpu_t *cpuarray);
float get_temp();
float get_h3temp();
void gettxrx(char *dev, txrx_t *if1);
struct in_addr get_addr(char *dev);
ram_t get_ram();
swap_t get_swap();
int get_ifname(char *iface,int index);
swap_t get_disk_byname(char *mntpoint);
swap_t get_disk_bymnt(char *mntpoint);
proc_t get_procs();
