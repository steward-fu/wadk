#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
  
int main(int argc, char const* argv[])
{
    ssize_t r = 0;
    int opt = 1;
    int fd = -1;
    int new_socket = 0;
    char buf[255] = { 0 };
    struct sockaddr_in addr = { 0 };
    const char *hello = "hello from server !";
  
    if (argc != 3) {
        printf("Usage: %s IP Port\n", argv[0]);
        return 0;
    }
  
    socklen_t addrlen = sizeof(addr);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
  
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
  
    bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(fd, 3);
    new_socket = accept(fd, (struct sockaddr *)&addr, &addrlen);
    printf("new_socket %d\n", new_socket);
  
    r = read(new_socket, buf, sizeof(buf));
    printf("%s (r=%d)\n", buf, r);
    send(new_socket, hello, strlen(hello), 0);
    close(new_socket);
    close(fd);
 
    return 0;
}
