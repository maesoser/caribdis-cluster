#include "sm-agent.h"


uint8_t * addr2arr(struct in_addr ipadrr){
        static uint8_t iparr[4] = {0};
        char *ipstr = inet_ntoa(ipadrr);
        sscanf(ipstr, "%hhu.%hhu.%hhu.%hhu", &iparr[0], &iparr[1], &iparr[2], &iparr[3]);
        return iparr;
}

void print_help(){
        printf("\n sm-agent: System monitorization agent.\n");
                printf("\n OPTIONS:\n");
                printf("\t -h \tPrint this help\n");
                printf("\t -p [port]\tSend data using udp to the specified port.\n");
        exit(1);
}


int main(int argc, char *argv[]){
        unsigned int laptime = DEFAULT_DELAY;
        uint32_t port = DEFAULT_PORT;
        char* toaddr;
        
        int opt;
        char dev[32];
        
        cpu_t cpuinfo[MAX_CPU_NUM];

        txrx_t if1stats;
        bzero(&if1stats,sizeof(txrx_t));

        int cores = 0;

        ram_t ram;

        double load[3];

        struct in_addr addr = { 0 };

        swap_t swap;
        swap_t mem;
        
        bzero(&cpuinfo,sizeof(cpu_t)*MAX_CPU_NUM);

        while ((opt = getopt(argc, argv, "t:p:h:a")) != -1) {
                switch(opt) {
                        case 't':
                                laptime = atoi(optarg);
                                break;
                        case 'h':
                                print_help();
                                break;
                        case 'p':
                                port = atoi(optarg);
                        case 'a':
                                toaddr = optarg;
                }
        }
        printf("Started SM-AGENT\n");
        while(1){
                ram = get_ram();
                printf("RAM: %d/%d\n",ram.used/1024,ram.total/1024);
                
                
                if (getloadavg(load, 3) == -1){
                        load[0] = 0;
                        load[1] = 0;
                        load[2] = 0;
                }
                
                get_ifname(dev,1);
                addr = get_addr(dev);
                gettxrx(dev,&if1stats);
                printf("%s: %s\tDown:%Lu\tUp:%Lu\tKbytes\n",dev,inet_ntoa(addr),if1stats.rx,if1stats.tx);

                mem = get_disk_bymnt("/");
                printf("DISK: %d/%d\tMbytes\t",mem.used/1024,mem.total/1024);
                
                swap = get_swap();
                printf("SWAP: %d/%d\tMbytes\n",swap.used/1024,swap.total/1024);
                
                cores = get_cpu(&cpuinfo);
                
                for(int n=1; n < cores; n++){
                        printf("CPU [%d/%d]: %0.1f %%\t",n,cores-1,cpuinfo[n].pcnt);
                }
                printf("\n");
                                
                sleep(laptime);
        }
        return 0;

}
