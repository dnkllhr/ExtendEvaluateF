#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

#define TOURNAMENT_PASSWD 1234
#define USERNAME "LAMPSHADE"
#define PASSWD "ILOVECAKE123"

void authenticationProtocol(int);
void challengeProtocol(int);
void roundProtocol(int);
void matchProtocol(int);
//void moveProtocol(int);


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);


    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);


    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

//SOCKET GOOD TO GO
authenticationProtocol(sockfd);
challengeProtocol(sockfd);

return 0;
}


//AUTHENTICATION PROTOCOL
void authenticationProtocol(int sockfd)
{
    int pid;
    char buffer[256];

    read(sockfd,buffer,255);    //Server: THIS IS SPARTA!
    printf("%s\n",buffer);

    bzero(buffer,256);
    sprintf(buffer,"JOIN %d",TOURNAMENT_PASSWD);
    printf("%s\n",buffer);
    write(sockfd,buffer,strlen(buffer)); //Client: JOIN <tournament password>

    bzero(buffer,256);
    read(sockfd,buffer,255); //Server: HELLO!
    printf("%s\n",buffer);


    bzero(buffer,256);
    sprintf(buffer,"I AM %s %s",USERNAME,PASSWD);
    printf("%s\n",buffer);
    write(sockfd,buffer,strlen(buffer));  //Client: I AM <username> <password>

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE
    sscanf(buffer,"WELCOME %d PLEASE WAIT FOR THE NEXT CHALLENGE", &pid);
    printf("%s\n",buffer);
}


//CHALLENGE PROTOCOL
void challengeProtocol(int sockfd)
{
int cid, rounds;
char buffer[256];

bzero(buffer,256);
read(sockfd,buffer,255);  //Server: NEW CHALLENGE <cid> YOU WILL PLAY <rounds> MATCH
sscanf(buffer,"NEW CHALLENGE %d YOU WILL PLAY %d MATCH", &cid, &rounds);
printf("%s\n",buffer);

for(int i = 0; i < rounds; i++)
  {
    roundProtocol(sockfd);
  }
}

//ROUND PROTOCOL
void roundProtocol(int sockfd)
{
  int rid,rounds;
  char buffer[256];

  bzero(buffer,256);
  read(sockfd,buffer,255);  //Server: BEGIN ROUND <rid> OF <rounds>
  sscanf(buffer,"BEGIN ROUND %d OF %d", &rid, &rounds);
  printf("%s\n",buffer);

  matchProtocol(sockfd);

  bzero(buffer,256);
  read(sockfd,buffer,255);  //Server: END OF ROUND <rid> OF <rounds>
  printf("%s\n",buffer);
}


void matchProtocol(int sockfd) {
    int oppPid, tile, x, y, orientation, number_tiles, time_plan;
    char buffer[256];

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: YOUR OPPONENT IS PLAYER <pid>
    sscanf(buffer,"YOUR OPPONENT IS PLAYER %d", &oppPid);
    printf("%s\n",buffer);

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: STARTING TILE IS <tile> AT <x> <y> <orientation>
    sscanf(buffer,"STARTING TILE IS %d AT %d %d %d", &tile,&x, &y, &orientation);
    printf("%s\n",buffer);

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
    sscanf(buffer,"THE REMAINING %d TILES ARE [ <tiles> ]", &number_tiles);   //need to decide how to handle tile queue
    printf("%s\n",buffer);

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: MATCH BEGINS IN <timeplan> SECONDS
    sscanf(buffer,"MATCH BEGINS IN %d SECONDS", &time_plan);
    printf("%s\n",buffer);

    //moveProtocol(int sockfd);

}
