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

#include <spdlog/spdlog.h>

// el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %func[%fbase] %level: %msg");
#define def_msleep(M) usleep(1000*(M))
#define def_min(a,b) ((a) < (b) ? (a):(b))
#define def_max(a,b) ((a) > (b) ? (a):(b))

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define XLOG_BUFFER_DEPTH (32)
#define XLOG_BUFFER_SIZE (2048)
#define XLOG_BUFFER_CACHE (1024)

#if 1 //def DEBUG
#define LOGV(...) do{char xlog_tmp_buf__[XLOG_BUFFER_SIZE]={0x00};snprintf(xlog_tmp_buf__, sizeof(xlog_tmp_buf__), __VA_ARGS__); fprintf(stderr, "%s (%4d)[V]: %s\n", __FILENAME__, __LINE__, xlog_tmp_buf__);}while(0)
#define LOGD(...) do{char xlog_tmp_buf__[XLOG_BUFFER_SIZE]={0x00};snprintf(xlog_tmp_buf__, sizeof(xlog_tmp_buf__), __VA_ARGS__); fprintf(stderr, "%s (%4d)[D]: %s\n", __FILENAME__, __LINE__, xlog_tmp_buf__);}while(0)
#define LOGI(...) do{char xlog_tmp_buf__[XLOG_BUFFER_SIZE]={0x00};snprintf(xlog_tmp_buf__, sizeof(xlog_tmp_buf__), __VA_ARGS__); fprintf(stderr, "%s (%4d)[I]: %s\n", __FILENAME__, __LINE__, xlog_tmp_buf__);}while(0)
#define LOGW(...) do{char xlog_tmp_buf__[XLOG_BUFFER_SIZE]={0x00};snprintf(xlog_tmp_buf__, sizeof(xlog_tmp_buf__), __VA_ARGS__); fprintf(stderr, "%s (%4d)[W]: %s\n", __FILENAME__, __LINE__, xlog_tmp_buf__);}while(0)
#define LOGE(...) do{char xlog_tmp_buf__[XLOG_BUFFER_SIZE]={0x00};snprintf(xlog_tmp_buf__, sizeof(xlog_tmp_buf__), __VA_ARGS__); fprintf(stderr, "%s (%4d)[E]: %s\n", __FILENAME__, __LINE__, xlog_tmp_buf__);}while(0)
#define LOGF(...) do{char xlog_tmp_buf__[XLOG_BUFFER_SIZE]={0x00};snprintf(xlog_tmp_buf__, sizeof(xlog_tmp_buf__), __VA_ARGS__); fprintf(stderr, "%s (%4d)[F]: %s\n", __FILENAME__, __LINE__, xlog_tmp_buf__);}while(0)
#else
#define LOGV(...)
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...) do{char xlog_tmp_buf__[XLOG_BUFFER_SIZE]={0x00};snprintf(xlog_tmp_buf__, sizeof(xlog_tmp_buf__), __VA_ARGS__); fprintf(stderr, "%s (%4d)[E]: %s\n", __FILENAME__, __LINE__, xlog_tmp_buf__);}while(0)
#define LOGF(...) do{char xlog_tmp_buf__[XLOG_BUFFER_SIZE]={0x00};snprintf(xlog_tmp_buf__, sizeof(xlog_tmp_buf__), __VA_ARGS__); fprintf(stderr, "%s (%4d)[F]: %s\n", __FILENAME__, __LINE__, xlog_tmp_buf__);}while(0)
#endif

#endif

