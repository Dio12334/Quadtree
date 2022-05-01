#include "Display.h"

int main(int argc, char **argv){
    Display display;
    if(display.initialize())
        display.runLoop();
    display.shutdown();
    return 0;
}
