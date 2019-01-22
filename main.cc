#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "controller.h"


int main(int arghs, char *argv[]) { 
    bool fileInit = false;
    bool testing = false;
    bool graphics = false;
    std::string filename;
    std::string deck1File = "default.deck";
    std::string deck2File = "default.deck";
    
    // read from command line args
    for(int i = 0; i < arghs; i++) {
        std::string arg = argv[i];

        if (arg == "-init") {
            // read commands that the game will begin with
            fileInit = true;
            filename = argv[i+1];
        }

        else if (arg == "-testing") {
            //use testing mode
            testing = true;
        }

        else if (arg == "-graphics") {
            //use graphical view
            graphics = true;
        }

        else if (arg == "-deck1") {
            // get deck from argv[i+1]
            deck1File = argv[i+1];
        }

        else if (arg == "deck2") {
            // get deck from argv[i+1]
            deck2File = argv[i+1];
        }

    }

    std::fstream f{filename};

    Controller c{deck1File, deck2File, testing,  graphics, fileInit, f, std::cin};


    c.playGame();
}
