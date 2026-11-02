
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SOCKET_ENABLED (&(int) {1})
#define SOCKET_DISABLED (&(int) {0})
#define MAX_ALLOWED_CLIENTS (3)
#define SOCKET_SUCCESS 0

#define MAX_MSG_SIZE 512


int error_callback(const char *msg) {

  perror(msg);
  exit(EXIT_FAILURE);
}





int main() {

  /* netværk servers kør på sockets,
   * man har en server der lytter på en specifik netværks IP og port, som man binder til
   * derefter accepterer vi hver klient i sekvential raekke,
   * sockets er laesbar som filer er.
   */

  int server_fd, ESPClient;
  int server_PORT = 8090;
  
  struct sockaddr_in address;
  socklen_t addrlength = sizeof(address);

  char msg[MAX_MSG_SIZE] = {0};
 

  
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < SOCKET_SUCCESS) {
    error_callback("SOCKINIT FAILED\n");
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                  SOCKET_ENABLED, sizeof(int))) {
    error_callback("SOCKETOPT FAILED\n");

  }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // det her betyder bind til alle netvaerks porter! lidt farligt hvis man har flere interfaces paa en server. ikke for os.
    address.sin_port = htons(server_PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < SOCKET_SUCCESS) {

      error_callback("SOCKBIND FAILED\n");
    }

    if (listen(server_fd, MAX_ALLOWED_CLIENTS) < 0) {

      error_callback("ERROR LISTENING...\n");
    }

    if ((ESPClient = accept(server_fd, (struct sockaddr *)&address,
                            &addrlength)) < SOCKET_SUCCESS) {
      error_callback("SOCKET ACCEPT FAILED");
    }

    // stadig udefineret hvornaar vi vil stoppe programmet.
    int stopsignal = 0;

    while (!stopsignal) {

      ssize_t valread = read(ESPClient, msg, MAX_MSG_SIZE - 1);
      printf("%s, msgsize: %zd", msg, valread);

     

    }
    
}

