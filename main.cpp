#include "Display.h"

int main(int argc, char *argv[]){
    int dim = 800;
    if (argc) dim = stoi(argv[1], nullptr, 10);
    Display display;
    if(display.initialize(dim))
        display.runLoop();
    display.shutdown();
    return 0;
}
