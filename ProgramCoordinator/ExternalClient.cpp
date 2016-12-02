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
#include <string>
#include <algorithm>
#include <exception>

char* TOURNAMENT_PASSWD;
char* USERNAME;
char* PASSWD;
int pid;
int portno;

std::thread ** threads;

gameMessage Msgs[2];
bool ready[2];
std::mutex msg_mutexes[2];
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
void gameThread(int);


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
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) > 0)
        perror("ERROR connecting socket");

    return sockfd;
}

int createServerSocket(int portno)
{
    std::stringstream toRun;
    toRun << PATH_TO_GAME << " " << portno;

    int sockfd, newsockfd, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        perror("ERROR on binding");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    std::cout << "Server listening on " << portno << std::endl;
    std::cout << toRun.str() << std::endl;

    system(toRun.str().c_str());

    std::cout << "Accept connection" << std::endl;
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) perror("ERROR on accept.");
    
    std::cout << "Connection accepted!!!" << std::endl;
    return newsockfd; /* we never get here */
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

    ready[0] = false;
    ready[1] = false;
    /* Begin new threads here!! */
    threads = new std::thread*[2];
    threads[0] = new std::thread(gameThread, 0);
    threads[1] = new std::thread(gameThread, 1);

    std::cout << "Send tile stack for thread 0." << std::endl;
    setMsg(0, *msg, true);
    std::cout << "Send tile stack for thread 1." << std::endl;
    setMsg(1, *msg, true);
    std::cout << "Send start tile for thread 0." << std::endl;
    setMsg(0, *move, true);
    std::cout << "Send start tile for thread 1." << std::endl;
    setMsg(1, *move, true);

    for (int i = 0; i < 2*number_tiles; i++)
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

    setMsg(socketMap[gid], *msg, true);
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
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" PLACE " << tile << " AT "<<newMsg.data.move.x <<" "<<newMsg.data.move.y<<" "<<orient<<" TIGER "<<zone;
            break;
        case 2:
            out<<"GAME "<<gid<<" MOVE "<<moveNum<<" PLACE "<< tile <<" AT "<<newMsg.data.move.x <<" "<<newMsg.data.move.y<<" "<<orient<<" CROCODILE";
            break;
    }

    std::cout<<"Response: " << out.str()<<std::endl;
    write(sockfd,out.str().c_str(),out.tellp());
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
          std::cout << buffer << std::endl;
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
    while(getline(in, s, ' ')) {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        strings.push_back(s);
    }

    return strings[index];
}

struct gameMessage getMsg (int thread_num, bool noWait) {
    std::unique_lock<std::mutex> guard(msg_mutexes[thread_num]);
    auto timeout = std::chrono::milliseconds(50);
    while(!ready[thread_num] && !noWait)
        cvs[thread_num].wait_for(guard, timeout, [thread_num, noWait](){return (ready[thread_num] || noWait);});

    if (noWait && !ready[thread_num]) {
        gameMessage notValid;
        notValid.messageType = -1;
        return notValid;
    }

    ready[thread_num] = false;
    struct gameMessage newMsg = Msgs[thread_num];
    guard.unlock();
    cvs[thread_num].notify_all();
    return newMsg;
}

void setMsg (int thread_num, struct gameMessage message, bool noWait){
    std::unique_lock<std::mutex> guard(msg_mutexes[thread_num]);
    auto timeout = std::chrono::milliseconds(50);
    while (ready[thread_num]) {
        cvs[thread_num].wait_for(guard, timeout, [thread_num](){return !ready[thread_num];});
    }

    Msgs[thread_num] = message;
    ready[thread_num] = true;
    guard.unlock();
    cvs[thread_num].notify_all();
    while (ready[thread_num] && !noWait)
        cvs[thread_num].wait_for(guard, timeout, [thread_num, noWait](){return (!ready[thread_num] || noWait);});
}

void gameThread(int thread_num){
    int socketfd = createServerSocket(portno + 1 + thread_num);

    //Instaniate game
    //if (fork() == 0) {
    //    std::cout << "Execute Game!" << std::endl;
    //    execl(PATH_TO_GAME, std::to_string(thread_num == 0 ? portno+1 : portno+2).c_str());
    //}
    //process tile and place

    std::cout << "Get TileStack! " << thread_num << std::endl;
    struct gameMessage tileStack = getMsg(thread_num);
    std::cout << "Send TileStack! " << thread_num << std::endl;
    send(socketfd, (char*)(&tileStack), sizeof(tileStack), 0);

    //wait for starting tile
    std::cout << "Get starting tile! " << thread_num << std::endl;
    struct gameMessage start = getMsg(thread_num);
    std::cout << "Send starting tile! " << thread_num << std::endl;
    send(socketfd, (char*)(&start), sizeof(start), 0);
    //process tile stack

    while(true)
    {
        struct gameMessage tileForMove = getMsg(thread_num);
        send(socketfd, (char*)(&tileForMove), sizeof(tileForMove), 0);
        struct gameMessage gameMove;
        read(socketfd, (char*)(&gameMove), sizeof(gameMove));
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
