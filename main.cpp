#include "Display.h"
#include <string>

int main(int argc, char *argv[]){
    
    int dim = 800;
    if (argc >1) dim = std::stoi(argv[1], nullptr, 10);

    Display display;
    if(display.initialize(static_cast<double>(dim)))
        display.runLoop();
    display.shutdown();

    return 0;
}
