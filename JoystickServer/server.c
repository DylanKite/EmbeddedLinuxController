#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "joystickconvert.h"

#define SUCCESS 1
#define FAILURE 0

static int connected_socket = 0;

static int socket_init(){
    int sock_id;
    struct sockaddr_in addr;
    struct sockaddr_storage addr_storage;
    socklen_t sock_size;

    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_id  == -1) {
        printf("%s: error creating new socket", __func__);
        return FAILURE;
    }
    printf("%s: socket_id: %d\n", __func__, sock_id);

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(7891);
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);

    bind(sock_id, (struct sockaddr *) &addr, sizeof(addr));

    if(listen(sock_id,1)==0) {
        printf("Listening\n");
    }
      else {
        printf("Error\n");
    }

    sock_size = sizeof(addr_storage);
    printf("%s: done listening", __func__);
    connected_socket = accept(sock_id,(struct sockaddr *) &addr_storage, &sock_size);
    printf("%s: connection successful\n", __func__);
    return SUCCESS;
}

static void send_message() {
    uint32_t robot_value = 0;
    long network_value = 0;
    for(;;) {
        robot_value= joystickToRobot();
        network_value = htonl(robot_value);

        send(connected_socket, &network_value, sizeof(long), 0);
    }

}

int main(){
    socket_init();
    send_message();
}
