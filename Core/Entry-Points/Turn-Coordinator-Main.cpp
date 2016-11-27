#include "../ExternalPlayers/TurnCoordinator/TurnCoordinator.h"

int main(int argc, char * argv[]) {
    if (argc < 1) throw invalid_argument("Not enough parameters specified.");
    int port = atoi(argv[0]);
    TurnCoordinator coordinator(port);
    coordinator.startCoordinator();
}
