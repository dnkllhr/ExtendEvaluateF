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
std::string strAtIndex(std::string,int);


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
std::cout << sockfd <<std::endl;
authenticationProtocol(sockfd);
challengeProtocol(sockfd);

return 0;
}

//AUTHENTICATION PROTOCOL
void authenticationProtocol(int sockfd)
{
    std::string pid;
    char buffer[256];

    //Prepare Output Stream
    std::stringstream out;

    //Server: THIS IS SPARTA!
    read(sockfd,buffer,255);
    printf("%s\n",buffer);

    //Client: JOIN <tournament password>
    bzero(buffer,256);
    out<<"JOIN ";
    out<<TOURNAMENT_PASSWD;
    std::cout<<"\t"<<out.str()<<std::endl;
    write(sockfd,out.str().c_str(),out.gcount()+1);
    out.str("");

    //Server: HELLO!
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);

   //Client: I AM <username> <password>
    bzero(buffer,256);
    out<<"I AM ";
    out<<USERNAME<<" "<<PASSWD;
    std::cout<<"\t"<<out.str()<<std::endl;
    write(sockfd,out.str().c_str(),out.gcount()+1);
    out.str("");

    //Server: WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
     pid = strAtIndex(std::string(buffer),1);
}

void challengeProtocol(int sockfd)
{
    std::string cid;
    int rounds;
    char buffer[256];

    //Server: NEW CHALLENGE <cid> YOU WILL PLAY <rounds> MATCH
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    cid = strAtIndex(std::string(buffer),1);
    rounds = stoi(strAtIndex(std::string(buffer),6));

    //roundProtocol
    for(int i = 0; i < rounds; i++)
        roundProtocol(sockfd);

/*    //Server: END OF CHALLENGES or PLEASE WAIT
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
*/
}

void roundProtocol(int sockfd)
{
  int rid,rounds;
  char buffer[256];

  //Server: BEGIN ROUND <rid> OF <rounds>
  bzero(buffer,256);
  read(sockfd,buffer,255);
  printf("%s\n",buffer);
    rid = stoi(strAtIndex(std::string(buffer),2));
    rounds = stoi(strAtIndex(std::string(buffer),4));

  //matchProtocol
  matchProtocol(sockfd);
/*
  //Server: END OF ROUND <rid> OF <rounds>
  bzero(buffer,256);
  read(sockfd,buffer,255);
  printf("%s\n",buffer);
 */
}

void matchProtocol(int sockfd)
{
    std::string oppPid, tile;
    int x, y, orientation, number_tiles, time_plan;
    char buffer[256];
    //Prepare Output and Input Stream
    std::stringstream out;

    //Server: YOUR OPPONENT IS PLAYER <pid>
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
      oppPid = strAtIndex(buffer,4);


    //Server: STARTING TILE IS <tile> AT <x> <y> <orientation>
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    x = stoi(strAtIndex(std::string(buffer),5));
    y = stoi(strAtIndex(std::string(buffer),6));
    orientation = stoi(strAtIndex(std::string(buffer),7));

    //PASS STARTING TILE TO INTERNAL SERVER

    //Server: THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    number_tiles = stoi(strAtIndex(std::string(buffer),2));

    //CREATE TILE STACK OF INTERNAL SERVER
    std::string tileStack;
    for(int i = 0; i < number_tiles;i++)
        out<<strAtIndex(std::string(buffer),6+i);

    //add tileStack to message once thats operational
    std::cout<<"TILE STACK: "<<out.str()<<std::endl;
    out.str("");


    //Server: MATCH BEGINS IN <timeplan> SECONDS
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    x = stoi(strAtIndex(std::string(buffer),3));


//    moveProtocol
    for(int i = 1; i <= number_tiles; i++)
    moveProtocol(sockfd);

    //Server: GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);

    //Server: GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
}

void moveProtocol(int sockfd)
{
    char buffer[256];
    int timeMove, moveNum;
    int gamesActive = 2;
    std::string tile, gid;

    //Prepare Output and Input Stream
    std::stringstream out;

    //Server: MAKE YOUR MOVE IN GAME <gid> WITHIN <timemove> SECOND: MOVE <#> PLACE <tile>
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    gid = strAtIndex(std::string(buffer),5);
    timeMove = stoi(strAtIndex(std::string(buffer),7));
    moveNum = stoi(strAtIndex(std::string(buffer),10));
    tile = strAtIndex(std::string(buffer),12);

    //Create Move Message and Pass to INTERNAL Server

    //Await response

    //Respond to Tournament Server With Move
    int response = 1;
    bzero(buffer,256);

    switch (response) {
        case 0:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" TILE "<< tile <<" UNPLACEABLE PASS";
            break;
        case 1:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" PLACE "<< tile <<" AT <x> <y> <orientation> NONE";
            break;
        case 2:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" PLACE <tile> AT <x> <y> <orientation> TIGER";
            break;
        case 3:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" PLACE "<< tile <<" AT <x> <y> <orientation> CROCODILE";
            break;
    }

    std::cout<<"\t"<<out.str()<<std::endl;
    write(sockfd,out.str().c_str(),out.gcount()+1);
    out.str("");

    //Recieve Results of Turn
    int currentlyActive = gamesActive;
    for(int i = 0; i < currentlyActive; i++){
      int movePid, x, y, orientation, zone;

      //Server: GAME <gid> MOVE <#> PLAYER <pid> <move>
      bzero(buffer,256);
      read(sockfd,buffer,255);
      printf("%s\n",buffer);
      if(strAtIndex(std::string(buffer),6).compare("FORFEITED") == 0) //Game FORFEITED
      {
          gamesActive--;
          //Let Game Know of Forfeit
      }
      else
      {
        if(gid.compare(strAtIndex(std::string(buffer),1)) != 0);    //Game You Care About
        else
        {
            //Let Game Know of the opponents move (not a Forfeit)


        }

      }
  }

}

std::string strAtIndex(std::string buffer, int index)
{
    std::vector<std::string> strings;
    std::string s;
    std::istringstream in (buffer);
    while(getline(in, s, ' '))
      strings.push_back(s);
     return strings[index];
}
