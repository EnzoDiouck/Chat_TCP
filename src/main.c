#include "if_error.h"
#include "strlen.h"
#include "atoi.h"
#include "memset.h"
#include <sys/socket.h>
#include <poll.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "realloc.h"
#include "printbase10.h"

#define MAX 256



static void write_fd(struct pollfd *tfd, char *msg, int i, int nbr_client)
{
  int comp;

  comp = 1;
  while (comp <= nbr_client)
    {
      if (comp != i)
	{
	  write (tfd[comp].fd, "Client ", 7);
	  write(tfd[comp].fd, std_print_base10(i), std_strlen(std_print_base10(i)));
	  write(tfd[comp].fd, " : ", 3);
	  if (write(tfd[comp].fd, msg, std_strlen(msg)) == -1)
	    write(tfd[comp].fd, "error writing\n", 15);
	}
      comp++;
    }
}





static int socket_server(int port)
{
  int sockfd;
  struct sockaddr_in addrsock;

  std_memset(&addrsock, 0, sizeof(addrsock));
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
    if_error("sockfd");
  addrsock.sin_family = AF_INET;
  addrsock.sin_addr.s_addr = INADDR_ANY;
  addrsock.sin_port = htons(port);
  if (bind(sockfd, (const struct sockaddr *)&addrsock, sizeof(addrsock)) == -1)
    if_error("bind");
  return sockfd;
}





int main(int argc, char *argv[])
{
  int i;
  int comp;
  struct pollfd tfd[MAX];
  nfds_t size_tfd;
  int timeout;
  char msg[MAX];
  struct sockaddr_in clientaddr;
  socklen_t clientaddr_len;
  int nbr_client;

  if (argc != 2)
    text_exit("./echo_server port\n");
  i = 0;
  nbr_client = 0;
  clientaddr_len = sizeof(clientaddr);
  size_tfd = 1;
  timeout = 3 * 60 * 1000;
  tfd[0].fd = socket_server(std_atoi(argv[1]));
  tfd[0].events = POLLIN;
  tfd[0].revents = 0;
  if (listen(tfd[0].fd, 0) == -1)
    if_error("listen");

  while (1)
    {
      if (poll(tfd, size_tfd, timeout) <= 0)
	{
	  write(1,"no action done\n", 16);
	  close(tfd[0].fd);
	  return 89;
	}
      while (i <= nbr_client)
	{
	  if (tfd[i].revents & POLLIN)
	    {
	      if (i == 0)//demande de connection
		{
		  nbr_client++;
		  tfd[nbr_client].fd = accept(tfd[0].fd, (struct sockaddr *)&clientaddr, &clientaddr_len);
		  if (tfd[nbr_client].fd == -1)
		    if_error("accept");
		  write(1, "Hi client ", 10);
		  write(1, std_print_base10(nbr_client), std_strlen(std_print_base10(nbr_client)));
		  write(1, "\n", 1);
		  tfd[nbr_client].events = POLLIN;
		  size_tfd++;
		}
	      else//chat
		{
		  comp = read(tfd[i].fd, msg, MAX);
		  if (comp == 0)//déconection
		    {
		      close(tfd[i].fd);
		      write(1, "Bye client ", 11);
		      write(1, std_print_base10(i), std_strlen(std_print_base10(i)));
		      write(1, "\n", 1);
		    }
		  else
		    {
		      msg[comp] = '\0';
		      write_fd(tfd, msg, i, nbr_client);
		    }
		}
	    }
	  i++;
	}
      i = 0;
    }
  close(tfd[0].fd);
}
