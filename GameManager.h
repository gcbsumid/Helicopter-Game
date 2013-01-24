#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <math.h>

#include "XInfo.h"
#include "Objects.h"
#include "PhysicsManager.h"
#include "MapManager.h"
#include "HelichopterObj.h"
#include "HelichopterManager.h"
#include "AIManager.h"
#include "PlaneManager.h"

class GameManager 
{
public:
    GameManager();
    ~GameManager();

    void InitGame();      // initialize start of game
    void StartGame();
    void Update();          // update moving parts 
    void Repaint();         // updates the animations?
    void InitX(int argc, char *argv[]);
    void CloseDisplay();

    enum eState 
    {
        E_STATE_STARTMENU,
        E_STATE_GAMEMODE,

        E_STATE_INVALID
    };

private:

    bool ShouldDisplayPauseMenu();
    void DisplayPauseMenu();
    void HandleButtonPress(XEvent &event);
    void HandleKeyPress(XEvent &event);
    void HandleKeyRelease(XEvent &event);
    void HandleFireMissile(bool isBomb);
    void ExposeUpdate();

    const int Border; // Define
    const int MaxGC;    
    const int BufferSize;
    const int FPS;

    XInfo xInfo;
    eState mState;
    PhysicsManager* mPhysicsManager;
    MapManager* mMapManager;
    HelichopterManager* mHelichopterManager;
    AIManager* mAIManager;
    PlaneManager* mPlaneManager;

    bool mShouldDisplayPause;
    bool mIsGameOver;
    bool mGameLoop;
    int mMovement;
    int mAccelerationTuning;
    int mTime;
    int mGameSpeed;

    bool mForward;
    bool mBackward;
    bool mUp;
    bool mDown;

};

#endif