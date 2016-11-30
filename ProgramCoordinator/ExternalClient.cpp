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
#include <thread>
#include <mutex>
#include <unordered_map>
#include <condition_variable>

char* TOURNAMENT_PASSWD;
char* USERNAME;
char* PASSWD;
int pid;
int portno;

std::thread ** threads;

gameMessage Msgs[2];
bool ready[2];
std::mutex msg_mutex;
std::condition_variable cvs[2];

std::unordered_map<std::string, int> socketMap;

int createSocket(std::string, int);
void authenticationProtocol(int);
void challengeProtocol(int);
void roundProtocol(int);
void matchProtocol(int);
void moveProtocol(int);
std::string strAtIndex(std::string,int);
struct gameMessage getMsg(int, bool=false);
void setMsg (int , struct gameMessage, bool=false);
int orientationFix(int);
void gameThread(int, int);


int main(int argc, char *argv[])
{
    TOURNAMENT_PASSWD = argv[3];
    USERNAME = argv[4];
    PASSWD = argv[5];

    std::string hostname (argv[1]);
    portno = atoi(argv[2]);

//SOCKET GOOD TO GO
int sockfd = createSocket(hostname,portno);
std::cout << sockfd <<std::endl;
authenticationProtocol(sockfd);
challengeProtocol(sockfd);

return 0;
}

int createSocket(std::string hostname, int portno)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(hostname.c_str());

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

    return sockfd;
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
    std::cout<<out.str()<<std::endl;
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
    std::cout<<out.str()<<std::endl;
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

   //Server: END OF CHALLENGES or PLEASE WAIT
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);

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

  //Server: END OF ROUND <rid> OF <rounds>
  bzero(buffer,256);
  read(sockfd,buffer,255);
  printf("%s\n",buffer);

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

    struct gameMessage * whoAmI = new struct gameMessage;


    //Server: STARTING TILE IS <tile> AT <x> <y> <orientation>
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    tile = strAtIndex(std::string(buffer),3);
    x = stoi(strAtIndex(std::string(buffer),5));
    y = stoi(strAtIndex(std::string(buffer),6));
    orientation = stoi(strAtIndex(std::string(buffer),7));

    //PASS STARTING TILE TO INTERNAL SERVER
\

    //Server: THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    number_tiles = stoi(strAtIndex(std::string(buffer),2));

    //CREATE TILE STACK OF INTERNAL SERVER
    std::string tileStack;
    out<<tile;
    for(int i = 0; i < number_tiles;i++)
        out<<strAtIndex(std::string(buffer),6+i);

    //Create Tile Stack Massage
    struct gameMessage* msg = new struct gameMessage;
    msg -> data.tile.lengthOfStack = 80;
    strcpy(msg -> data.tile.tileStack, tileStack.c_str());

    //add tileStack to message once thats operational
    std::cout<<"TILE STACK: "<<out.str()<<std::endl;
    out.str("");

    //Custom Move
    struct gameMessage * move = new struct gameMessage;
    move -> data.move.p1 = 3;
    strcpy(move -> data.move.tile, tile.c_str());
    move -> data.move.x = 76;
    move -> data.move.y = 76;
    move -> data.move.orientation = (unsigned int)orientationFix(orientation);

    //Server: MATCH BEGINS IN <timeplan> SECONDS
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    int timeplan = stoi(strAtIndex(std::string(buffer),3));

    int portNumberThread1 = portno + 1;
    int portNumberThread2 = portno + 2;

    int sockfd1 = createSocket("localhost", portNumberThread1);
    int sockfd2 = createSocket("localhost", portNumberThread2);

    /* Begin new threads here!! */
    threads = new std::thread*[2];
    threads[0] = new std::thread(gameThread, 0, sockfd1);
    threads[1] = new std::thread(gameThread, 1, sockfd2);

    setMsg(0, *msg, true);
    setMsg(1, *msg);
    setMsg(0, *move, true);
    setMsg(1, *move);

    for (int i = 0; i < number_tiles; i++)
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

// pass msg and move to threads
void moveProtocol(int sockfd)
{
    char buffer[256];
    int timeMove, moveNum;
    int gamesActive = 2;
    std::string tile, gid;

    //Prepare Output and msg
    std::stringstream out;
    struct gameMessage* msg = new struct gameMessage;

    //Server: MAKE YOUR MOVE IN GAME <gid> WITHIN <timemove> SECOND: MOVE <#> PLACE <tile>
    bzero(buffer,256);
    read(sockfd,buffer,255);
    printf("%s\n",buffer);
    gid = strAtIndex(std::string(buffer),5);
    timeMove = stoi(strAtIndex(std::string(buffer),7));
    moveNum = stoi(strAtIndex(std::string(buffer),10));
    tile = strAtIndex(std::string(buffer),12);

    //Create Move Message and Pass to INTERNAL Server
    strcpy(msg -> data.move.tile, tile.c_str());

    setMsg(socketMap[gid], *msg);
    //Await response
    struct gameMessage newMsg = getMsg(socketMap[gid]);
    newMsg.data.move.x -= 76;
    newMsg.data.move.y -= 76;
    int orient = orientationFix(newMsg.data.move.orientation);
    int zone = newMsg.data.move.zone;
    //Respond to Tournament Server With Move
    int response;
    bzero(buffer,256);

    if(!newMsg.data.move.placeable)
        response = 0;
    else
        response = newMsg.data.move.meepleType;

    switch (response) {
        case 3:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" TILE "<< tile <<" UNPLACEABLE PASS";
            break;
        case 0:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" PLACE "<< tile <<" AT "<<newMsg.data.move.x <<" "<<newMsg.data.move.y<<" "<<orient<<" NONE";
            break;
        case 1:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" PLACE <tile> AT "<<newMsg.data.move.x <<" "<<newMsg.data.move.y<<" "<<orient<<" TIGER "<<zone;
            break;
        case 2:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" PLACE "<< tile <<" AT "<<newMsg.data.move.x <<" "<<newMsg.data.move.y<<" "<<orient<<" CROCODILE";
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
          // stop forfeited match
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

gameMessage getMsg (int thread_num, bool mainThread) {
    std::unique_lock<std::mutex> guard(msg_mutex);
    cvs[thread_num].wait(guard, [thread_num, mainThread](){return (ready[thread_num] || mainThread);});

    if (mainThread && !ready[thread_num - 1]) {
        gameMessage notValid;
        notValid.messageType = -1;
        return notValid;
    }

    return Msgs[thread_num-1];
}

void setMsg (int thread_num, struct gameMessage message, bool mainThread){
    std::unique_lock<std::mutex> guard(msg_mutex);
        Msgs[thread_num] = message;
        ready[thread_num] = true;
    cvs[thread_num].wait(guard, [thread_num, mainThread](){return (ready[thread_num] || mainThread);});
}

void gameThread(int thread_num, int socketfd){
    //Instaniate game
    fork();
    execl(PATH_TO_GAME, std::itoa(thread_num == 0 ? portno+1 : portno+2));

    //process tile and place

    struct gameMessage tileStack = getMsg(thread_num);
    socketfd.send((char*)(&tileStack));

    //wait for starting tile
    struct gameMessage start = getMsg(thread_num);
    socketfd.send((char*)(&start));

    //process tile stack

    while(true)
    {
        struct gameMessage tileForMove = getMsg(thread_num);
        socketfd.send((char*)(&tileForMove));
        struct gameMessage gameMove = (char*)socketfd.read();
        setMsg(thread_num, gameMove);
    }
}

int orientationFix(int orientation)
{
    switch (orientation) {
        case 1:
            return 270; break;
        case 2:
            return 180; break;
        case 3:
            return 90; break;
        case 90:
            return 3; break;
        case 180:
            return 2; break;
        case 270:
            return 1; break;
        default:
            return orientation;
    }
}
