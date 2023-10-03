#include <stdio.h>
#include <pthread.h>
#include <getopt.h>
#include <stdlib.h>

#include "sockets.h"
#include "server.h"
#include "OVESP.h"

void show_help_menu (void);

void show_help_menu(void)
{
    printf("Usage : server [OPTION]\n");
    printf("Example : server -p 4444 -t 10\n\n");
    printf("Options available :\n");
    printf("-p, --port\t PORT to use when the server is listening.\n");
    printf("-t, --threads\t THREADS Pool the server will create for the clients.\n");
    printf("-h, --help\t show this help menu.\n\n");
}

int main(int argc, char **argv)
{
    const char *optstring = ":hp:t:";
    const struct option lopts[] = {
        {"help", no_argument, NULL, 'h'}, /* Print the help menu */
        {"port", required_argument, NULL, 'p'}, /* Required the port number to listen to */
        {"threads", required_argument, NULL, 't'}, /* Number of threads to create */
        {NULL, no_argument, NULL, 0}, /* If no arguments, read the config file */
    };

    int val;
    int index;

    index = -1;

    while (EOF !=(val = getopt_long(argc, argv, optstring, lopts, &index))) {
        
        switch(val) {
            case 'h' :
                show_help_menu();
                break;
            case 'p' :

                break;
            
            case 't' :
                break;
            case ':':
                printf("Missing argument for '%c' option.\n", optopt);
                break;
            case '?':
                printf("Unknown option: '%c'. Ignoring it.\n", optopt);
                break;
        }
        index = -1;

        
    }

    int server_socket;
    int client_socket;
    Message *msg;

    msg = NULL;
    server_socket = Server_init();

    while (1) {
        client_socket = Accept_connexion(server_socket);
        Receive_msg(client_socket, &msg);
        OVESP_server((char*)msg->data, client_socket);
        
    }

    return 0;
}