#ifndef MUSE_H
#define MUSE_H

#include "network.h"
#include "main_memory.h"
#include <commons/log.h>
#include <commons/config.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

//#define MUSE_CONFIG_PATH "/home/utnso/git/tp-2019-2c-Los-Trapitos/configs/memoria.config"
//#define MUSE_LOG_PATH "/home/utnso/git/tp-2019-2c-Los-Trapitos/logs/muse.log"

#define MUSE_CONFIG_PATH "/home/utnso/workspace/tp-2019-2c-Los-Trapitos/configs/memoria.config"
#define MUSE_LOG_PATH "/home/utnso/workspace/tp-2019-2c-Los-Trapitos/logs/muse.log"

/*
	#define MUSE_CONFIG_PATH "../configs/memoria.config"
	#define MUSE_LOG_PATH "../logs/muse.log"
 */

typedef struct muse_configuration_s
{
	int listen_port;
	int memory_size;
	int page_size;
	int swap_size;
}muse_configuration;

uint32_t memory_close(uint32_t pid);

void* muse_invoke_function(Function *function,uint32_t pid);

/* 
Starts server,logger and loads configuration. 
[LOG_LEVEL_TRACE] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
*/
void muse_start_service(ConnectionHandler ch);

/* Stops the server and frees resources */
void muse_stop_service();

/* helpers */
muse_configuration *load_configuration(char *config_path);

/* Connection handler. */
void* handler(void *args);

/* Decides wich message has arrived
 * and depending on the message 
 * does an action */
void message_handler(Message *m,int sock);

#endif 
