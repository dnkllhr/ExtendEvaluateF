#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include "ProgramCoordinator.h"
#include <vector>

char* TOURNAMENT_PASSWD;
char* USERNAME;
char* PASSWD;

void authenticationProtocol(int);
void challengeProtocol(int);
void roundProtocol(int);
void matchProtocol(int);
void moveProtocol(int);


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    TOURNAMENT_PASSWD = argv[3];
    USERNAME = argv[4];
    PASSWD = argv[5];

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
    sprintf(buffer,"JOIN %s",TOURNAMENT_PASSWD);
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

  bzero(buffer,256);
  read(sockfd,buffer,255);  //Server: END OF CHALLENGES or PLEASE WAIT
  printf("%s\n",buffer);

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
    sscanf(buffer,"STARTING TILE IS %d AT %d %d %d", &tile, &x, &y, &orientation);
    printf("%s\n",buffer);

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
    sscanf(buffer,"THE REMAINING %d TILES ARE [ <tiles> ]", &number_tiles);   //need to decide how to handle tile queue
    printf("%s\n",buffer);

    std::istringstream brett (buffer);
    std::vector<std::string> strings;
    std::string s;
    while(getline(brett, s, ' '))
      strings.push_back(s);



    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: MATCH BEGINS IN <timeplan> SECONDS
    sscanf(buffer,"MATCH BEGINS IN %d SECONDS", &time_plan);
    printf("%s\n",buffer);

    //Pre Match AI Grind

    for(int i = 1; i <= number_tiles; i++)
    moveProtocol(sockfd);

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
    printf("%s\n",buffer);

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
    printf("%s\n",buffer);
}

void moveProtocol(int sockfd)
{
    char buffer[256];
    int timeMove, gid, moveNum;
    int gamesActive = 2;

    const char* tile = new char[6];

    bzero(buffer,256);
    read(sockfd,buffer,255);  //Server: MAKE YOUR MOVE IN GAME <gid> WITHIN <timemove> SECOND: MOVE <#> PLACE <tile>
    std::istringstream iss1 (buffer);
    std::vector<std::string> moveMsgStrings;
    std::string tempString;
    while(getline(iss1, tempString, ' ')){
      moveMsgStrings.push_back(tempString);
    }
    //std::cout<<moveMsgStrings[5]<<"\t"<<moveMsgStrings[7]<<"\t"<<moveMsgStrings[10];
    //gid = moveMsgStrings[5];
    timeMove = stoi(moveMsgStrings[7]);
    moveNum = stoi(moveMsgStrings[10]);
    tile = moveMsgStrings[12].c_str();
    std::cout << moveMsgStrings[12]<<std::endl;

//    sscanf(buffer,"MAKE YOUR MOVE IN GAME %d WITHIN %d %[SECOND]: MOVE %d PLACE %s", &gid, &timeMove, __null, &moveNum, (char *)tile);
    printf("%s\n",buffer);
    /*Decide Move with given Tile and Time

    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

    moveMessage r;
    strcpy(r.tile, tile);
    r.gid = gid;

    //Pass r to the game server
    r.placeable = 0;
    //Wait for response from game server

    //delete[] tile;
    if(!r.placeable) // missing retrieve and add tiger for nonplacable tiger
    {
      bzero(buffer,256);
      sprintf(buffer,"GAME %d MOVE %d TILE %s UNPLACEABLE PASS", gid, moveNum, tile);
      printf("%s\n",buffer);
      write(sockfd,buffer,strlen(buffer));  //Client: "GAME %d TILE %s UNPLACEABLE PASS"
    }
    else // Tile is place able
    {
      switch (r.meepleType)
      {
        case 0: //NONE
          bzero(buffer,256);
          sprintf(buffer,"GAME %d MOVE %d PLACE %s AT %d %d %d NONE", gid, moveNum, tile, r.x, r.y, r.orientation);
          printf("%s\n",buffer);
          write(sockfd,buffer,strlen(buffer));  //Client: GAME <gid> PLACE <tile> AT <x> <y> <orientation> NONE
          break;
        case 1: //TIGER
          bzero(buffer,256);
          sprintf(buffer,"GAME %d MOVE %d PLACE %s AT %d %d %d TIGER %d", gid, moveNum, tile, r.x, r.y, r.orientation, r.zone);
          printf("%s\n",buffer);
          write(sockfd,buffer,strlen(buffer));  //Client: GAME <gid> PLACE <tile> AT <x> <y> <orientation> TIGER <zone>
          break;
        case 2://CROC
          bzero(buffer,256);
          sprintf(buffer,"GAME %d MOVE %d PLACE %s AT %d %d %d CROCODILE", gid, moveNum, tile, r.x, r.y, r.orientation);
          printf("%s\n",buffer);
          write(sockfd,buffer,strlen(buffer));  //Client: GAME <gid> PLACE <tile> AT <x> <y> <orientation> CROCODILE
          break;

      }
    }

    //tournament server returns result of moves, Pass info to Game Server.

    int currentlyActive = gamesActive;
    for(int i = 0; i < currentlyActive; i++){
      int movePid, x, y, orientation, zone;

      //Server: GAME <gid> MOVE <#> PLAYER <pid> <move>
      bzero(buffer,256);
      read(sockfd,buffer,255);

      if(!forfeit)
      {
        std::istringstream brett (buffer);
        std::vector<std::string> strings;
        std::string s;
        while(getline(brett, s, ' ')){
          strings.push_back(s);
        }

        if(strings[6]=="PLACED")
        {
          if(strings[12]=="TIGER")
          {
            sscanf(buffer,"GAME %d MOVE %d PLAYER %d PLACED %s AT %d %d %d TIGER %d", &gid, &moveNum, &movePid, (char *)tile, &x, &y, &orientation, &zone );
            printf("%s\n",buffer);
          }
          else
          {
            sscanf(buffer,"GAME %d MOVE %d PLAYER %d PLACED %s AT %d %d %d", &gid, &moveNum, &movePid, (char *)tile, &x, &y, &orientation);
            printf("%s\n",buffer);
          }
        }
        else
        {
          tile = strings[7].c_str();
          if(strings[9]!="PASSED") // TILE <tile> UNPLACEABLE RETRIEVED TIGER AT <x> <y>
          {
            x = stoi(strings[strings.size()-2]);
            y = stoi(strings[strings.size()-1]);
            printf("%s\n",buffer);
          }
          else //TILE <tile> UNPLACEABLE PASSED
          {
            //do nothing
          }

        }

      }

      else  //FORFEITED
      {
        sscanf(buffer,"GAME %d MOVE %d PLAYER %d FORFEITED:", &gid, &moveNum, &movePid);
        printf("%s\n",buffer);

      }

    }

}
