/*********************************
/ Christian Sumido
/ gcbsumid@uwaterloo.ca
/ 20374863
/ Side-scrolling X-lib game
**********************************/

/*** Includes ***/
#include <iostream>
#include <list>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "GameManager.h"

using namespace std;

// Main program
int main(int argc, char *argv[])
{
    GameManager gameManager;


    gameManager.InitX(argc, argv);
    gameManager.InitGame();

    // This is where the gameloop is.
    gameManager.StartGame();
    
    // Close program
    gameManager.CloseDisplay();
    return 0;
}