#ifndef DEF_H
#define DEF_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <signal.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <linux/if_ether.h>
#include <malloc.h>
#include <fcntl.h>
#include <termios.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <sched.h>
#include <easylogging++.h>

// el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %func[%fbase] %level: %msg");
#define def_msleep(M) usleep(1000*(M))
#define def_min(a,b) ((a) < (b) ? (a):(b))
#define def_max(a,b) ((a) > (b) ? (a):(b))

#if 0
#ifdef DEBUG
    #define LOGD(...) do{char tmp[1024]={0x00};snprintf(tmp, 1023, __VA_ARGS__) printf("%s (%4d) DEBUG: %s\n", __FILE__, __LINE__, tmp);}while(0)
    #define LOGI(...) do{printf("%s (%4d) INFO: ", __FILE__, __LINE__);printf(__VA_ARGS__);printf("\n");}while(0)
    #define LOGW(...) do{printf("%s (%4d) WARN: ", __FILE__, __LINE__);printf(__VA_ARGS__);printf("\n");}while(0)
    #define LOGE(...) do{printf("%s (%4d) ERROR: ", __FILE__, __LINE__);printf(__VA_ARGS__);printf("\n");}while(0)
#else
    #define LOGI(...)
	#define LOGD(...) 
	#define LOGW(...) 
    #define LOGE(...) do{char tmp[1024]={0x00};snprintf(tmp, 1023, __VA_ARGS__) printf("%s (%4d) ERROR: %s\n", __FILE__, __LINE__, tmp);}while(0)
#endif
#else
#if 1 //def DEBUG
// Use default logger
    #define LOGI(...) el::Loggers::getLogger("default")->info(__VA_ARGS__)
    #define LOGD(...) el::Loggers::getLogger("default")->debug(__VA_ARGS__)
	#define LOGW(...) el::Loggers::getLogger("default")->warn(__VA_ARGS__)
    #define LOGE(...) el::Loggers::getLogger("default")->error(__VA_ARGS__)
#else
	#define LOGI(...) 
    #define LOGD(...) (void)
	#define LOGW(...) 
    #define LOGE(...) el::Loggers::getLogger("default")->error(__VA_ARGS__)
#endif
#endif

#endif

