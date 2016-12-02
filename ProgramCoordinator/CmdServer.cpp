/* A simple server in the internet domain using TCP
   The port number is passed as an argument
   This version runs forever, forking off a separate
   process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <exception>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <sstream>

void Tournament_Protocol(int);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, pid;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     while (1) {
         newsockfd = accept(sockfd,
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0)
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             Tournament_Protocol(newsockfd);
             exit(0);
         }
         else close(newsockfd);
     } /* end of while */

     close(sockfd);
     return 0; /* we never get here */
}


void Tournament_Protocol (int sock)
{
   char buffer[256];
   std::string S_pid, C_pid;
   std::cout<<"Server pid: ";
   std::cin >> S_pid;
   std::cout<<"Client pid: ";
   std::cin >> C_pid;

   write(sock,"THIS IS SPARTA!\r\n",225);

   bzero(buffer,256);
   read(sock,buffer,255);
   write(sock,"HELLO!",6);

   bzero(buffer,256);
   read(sock,buffer,255);
   sprintf(buffer,"WELCOME %s PLEASE WAIT FOR THE NEXT CHALLENGE\r\n",C_pid.c_str());
   write(sock,buffer,255);

//CHALLENGE PROTOCOL
   int totalRounds;
   std::cout<<"Starting Challenge Protocol\n Number of Rounds: ";
   std::cin>>totalRounds;

   bzero(buffer,256);
   sprintf(buffer,"NEW CHALLENGE 123 YOU WILL PLAY %d MATCHES\r\n", totalRounds);
   write(sock,buffer,255);

   for(int round = 1; round <= totalRounds; round++) //ROUND PROTOCOL
    {
      bzero(buffer,256);
      sprintf(buffer,"BEGIN ROUND %d of %d\r\n",round ,totalRounds);
      write(sock,buffer,255);

      bzero(buffer,256);
      sprintf(buffer,"YOUR OPPONENT IS PLAYER %s\r\n",S_pid.c_str());
      write(sock,buffer,255);

      std::string tile;
      int x,y,orientation;
      std::cout << "STARTING TILE : ";
      std::cin >> tile;
      std::cout << "at X : ";
      std::cin >> x;
      std::cout << "and Y : ";
      std::cin >> y;
      std::cout << "Orientation (Counter Clock Wise) : ";
      std::cin >> orientation;

      bzero(buffer,256);
      sprintf(buffer,"STARTING TILE IS %s AT %d %d %d\r\n",tile.c_str(),x,y,orientation);
      write(sock,buffer,255);

      int remainingTiles;
      std::string tileStack = "";
      std::vector<std::string> tiles;
      std::cout<<"Number of Remaining Tiles: ";
      std::cin>>remainingTiles;

      for (int i = 1; i <= remainingTiles; i++)
      {
          std::cout << "Tile " << i <<" : ";
          std::string s;
          std::cin>>s;
          tiles.push_back(s);
          s += " ";
          tileStack += s;
      }


      bzero(buffer,256);
      sprintf(buffer,"THE REMAINING %d TILES ARE [ %s]\r\n",remainingTiles,tileStack.c_str() );
      write(sock,buffer,255);

      int timeTill;
      std::string GID1, GID2;
      std::cout << "Time til Match: ";
      std::cin >> timeTill;
      std::cout << "Assign Game 1 ID: ";
      std::cin >> GID1;
      std::cout << "Assign Game 2 ID: ";
      std::cin >> GID2;

      //Delay here if we care later

      bzero(buffer,256);
      sprintf(buffer,"MATCH BEGINS IN %d SECONDS\r\n",timeTill);
      write(sock,buffer,255);

      int activeGames = 2;
      std::string games[2] = {GID1,GID2};
      int gameIndex = 0;
      for(int i = 1; i <= remainingTiles && activeGames > 0 ; i++){

          if(activeGames > 1)
            gameIndex = (gameIndex + 1)%2;

          bzero(buffer,256);
          sprintf(buffer,"MAKE YOUR MOVE IN GAME %s WITHIN 1 SECOND: MOVE %d PLACE %s\r\n", games[gameIndex].c_str(), i, tiles[i-1].c_str());
          write(sock,buffer,255);

          int moveType;
          int x_move, y_move;
          std::cout<<"\nMOVE "+ std::to_string(i)+"_________________________";
          std::cout<<"\nTile is: "<<tiles[i-1]<<"\nMove Type ? \n(1)Place\n(2)Unplacable\n";
          std::cin >> moveType;

          std::string serverMove = "GAME "+games[gameIndex]+" MOVE "+std::to_string(i)+" PLAYER "+S_pid+" ";
          if (moveType == 1)
          {
              int meeple;
              std::cout<<"X :";
              std::cin >>x_move;
              std::cout<<"Y :";
              std::cin >> y_move;
              std::cout<<"Meeple?\n(1) NONE\n(2) TIGER\n(3) Croc\n";
              std::cin >> meeple;
              switch (meeple) {
                  case 1:
                    serverMove += "PLACED "+tiles[i-1]+" AT "+std::to_string(x_move)+" "+std::to_string(y_move)+" "+std::to_string(orientation)+" NONE\r\n";
                    break;
                  case 2:
                    int zone;
                    std::cout<<"Zone :";
                    std::cin>>zone;
                    serverMove += "PLACED "+tiles[i-1]+" AT "+std::to_string(x_move)+" "+std::to_string(y_move)+" "+std::to_string(orientation)+" TIGER "+std::to_string(zone)+"\r\n";
                    break;
                  case 3:
                    serverMove += "PLACED "+tiles[i-1]+" AT "+std::to_string(x_move)+" "+std::to_string(y_move)+" "+std::to_string(orientation)+" CROCODILE\r\n";
                    break;
              }

          }
          else
              serverMove = "TILE "+ tiles[i-1] +" UNPLACEABLE PASSED\r\n";



          bzero(buffer,256);
          read(sock,buffer,255);    //Client Move


          //print our move
          write(sock,serverMove.c_str(),255);

          //print clientMove
          //all this bologna to convert client move into the way the server says it
          std::string clientMove = "";
          std::vector<std::string> strings;
          std::string r;
          std::istringstream in (buffer);
          while(getline(in, r, ' ')) {
              r.erase(std::remove(r.begin(), r.end(), '\n'), r.end());
              r.erase(std::remove(r.begin(), r.end(), '\r'), r.end());
              strings.push_back(r);
          }
          for (int j = 0; j < 4; j++)
              clientMove += strings[j] + " ";
          clientMove += "PLAYER "+ C_pid + " ";
          for(int j = 4; j < strings.size()-1;j++)
            clientMove += strings[j] + " ";
          clientMove += strings[strings.size()-1]+"\r\n";

          write(sock,clientMove.c_str(),255);

      }

      bzero(buffer,256);
      sprintf(buffer,"GAME A OVER PLAYER 0 100 PLAYER 1 50\r\n");
      write(sock,buffer,255);

      bzero(buffer,256);
      sprintf(buffer,"GAME B OVER PLAYER 1 50 PLAYER 0 100\r\n");
      write(sock,buffer,255);

      bzero(buffer,256);
      sprintf(buffer,"END OF ROUND %d OF %d\r\n", round, totalRounds);
      write(sock,buffer,255);
    }
    bzero(buffer,256);
    sprintf(buffer,"END OF CHALLENGES\r\n");
    write(sock,buffer,255);

}
