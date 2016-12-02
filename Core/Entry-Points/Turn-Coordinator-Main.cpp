#include "../../ExternalPlayers/TurnCoordinator/TurnCoordinator.h"
#include <stdexcept>

int main(int argc, char * argv[]) {
    if (argc < 1) throw std::invalid_argument("Not enough parameters specified.");
    int port = atoi(argv[1]);
    TurnCoordinator coordinator(port);
    coordinator.startCoordinator();
}
