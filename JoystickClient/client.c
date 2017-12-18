#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../JoystickServer/joystickconvert.h"

#define SUCCESS 1
#define IPLEN 16
#define DEFAULT_IP_LEN 11
static int client_id =0;

static int client_connect(char IP_address[]) {
    int rtnValue;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    client_id =  socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr(IP_address);
    printf("%s ip address: %s\n", __func__, IP_address);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;

    rtnValue = connect(client_id, (struct sockaddr *) &serverAddr, addr_size);
    if (rtnValue == -1) {
        printf("%s: error connecting errno: %s\n", __func__, strerror(errno));
    }
    printf("%s: client id: %d", __func__, client_id);
    return SUCCESS;
}

static int incoming_message(){
    long incoming_value = 0;
    uint32_t translated_value =0;
    recv(client_id, &incoming_value, sizeof(long), 0);
    translated_value = ntohl(incoming_value);

    printf("%s: incoming value: %d\n", __func__, translated_value);
    print_robot_value(translated_value);
}

int main(int argc, char *argv[]){
    char incomingIP[IPLEN];
    if (argc != 2) {
        printf("%s: argc no value setting default to 127.0.0.1\n", __func__);
        strncpy(incomingIP,"127.0.0.1\0", DEFAULT_IP_LEN);
    } else {
        strncpy(incomingIP, argv[1], IPLEN);
        printf("%s: incoming IP %s\n", __func__, incomingIP);
    }
    client_connect(incomingIP);
    for (;;) {
        incoming_message();
    } return 1;
}
