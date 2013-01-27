#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include "GameManager.h"
#include "Objects.h"
#include "ObjectsFactory.h"
#include "WallObj.h"
#include "TargetObj.h"
#include "MissileObj.h"
#include "HelichopterObj.h"
#include "PlaneObj.h"
#include "PlaneManager.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

const int pauseTextLength = 27;
static string pauseText[] = 
{
    "Helicopter Side Scrolling Game",
    "Tutorial:",
    "Keys:", "Functionality:",
    "W", "Move Up",
    "S", "Move Down",
    "A", "Move Left",
    "D", "Move Right",
    "spacebar", "Shoot(downwards)",
    "M", "Shoot(forward)",
    "G", "Activate God Mode",
    "Left Arrow", "Decrease game speed",
    "Right Arrow", "Increase game speed",
    "Left Click/F", "Pause Game",
    "N", "Super Mega Snowflake bomb. Pressing N",
    "", "explodes the bomb up to 3 times."
};

// Function that puts out an error when it exits
void error(string str) 
{
    cerr << str << endl;
    exit(0);
}

unsigned long now() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

// TODO:: everything
GameManager::GameManager() : Border(5), MaxGC(3),
    BufferSize(10), FPS(30), mShouldDisplayPause(true), 
    mIsGameOver(false), mGameLoop(true), mMovement(0), 
    mGameSpeed(1), mForward(false), mBackward(false), 
    mUp(false), mDown(false)
{
    cout << "Game Manager was created." << endl;
}

GameManager::~GameManager()
{
    delete mMapManager;
    delete mHelichopterManager;
    delete mPlaneManager;

}

void GameManager::InitGame()
{

    // Create walls
    mMapManager = new MapManager(&xInfo);
    mHelichopterManager = new HelichopterManager(&xInfo);

    mPlaneManager = new PlaneManager(
        mHelichopterManager->GetHelichopter(),
        mHelichopterManager->GetTurretMissileObjs());

    // Create Objects then pass it to the Physics Manager
    mPhysicsManager = new PhysicsManager(
        mHelichopterManager->GetHelichopter(), 
        mMapManager->GetWallObjVector(), 
        mMapManager->GetTargetObjVector(), 
        mHelichopterManager->GetHeliMissileObjs(),
        mHelichopterManager->GetTurretMissileObjs(),
        mPlaneManager->GetPlaneObjs(),
        mHelichopterManager->GetExplosiveObjs());

    // Create Objects then pass it to the AI Manager
    mAIManager = new AIManager(
        mHelichopterManager->GetHelichopter(), 
        mMapManager->GetWallObjVector(), 
        mMapManager->GetTargetObjVector(), 
        mHelichopterManager->GetHeliMissileObjs(),
        mHelichopterManager->GetTurretMissileObjs());


    Repaint();

    cout << "Initialized Game!" << endl;
}

void GameManager::StartGame()
{
    XEvent event;
    unsigned long lastRepaint = 0;
    cout << "Starting Game" << endl;
    while (mGameLoop || mIsGameOver)
    {
        if(XPending(xInfo.display) > 0) 
        {
            XNextEvent(xInfo.display, &event);
            switch(event.type)
            {
                case ButtonPress:
                    HandleButtonPress(event);
                    break;
                case KeyPress:
                    HandleKeyPress(event);
                    break;
                case Expose:
                    ExposeUpdate();
                    Repaint();
                    break;
                case KeyRelease:
                    HandleKeyRelease(event);
                    break;
                default:
                    break;
            }
        }
        
        unsigned long end = now();
        if (end - lastRepaint > 1000000/FPS) {
            if(!ShouldDisplayPauseMenu())
            {
                mPhysicsManager->Update();
                mPlaneManager->Update(&xInfo, end - lastRepaint, mGameSpeed);
                mPlaneManager->AIFire(&xInfo, end - lastRepaint);
                mAIManager->AIFire(&xInfo, end - lastRepaint);
            }
            Update();
            Repaint();
            lastRepaint = now();
        }
        if (XPending(xInfo.display) == 0) {
            usleep(1000000/FPS - (end - lastRepaint));
        }
    }
    cout << "Exited the gameloop" << endl;
}

void GameManager::ExposeUpdate()
{          
    mMapManager->UpdateMap(&xInfo, mGameSpeed);

    mMapManager->ExposeUpdate(&xInfo);  
}

void GameManager::Update()
{
    if(mHelichopterManager->IsHelichopterDestroyed())
    {
        mShouldDisplayPause = true;
        mIsGameOver = true;
        mGameLoop = false;
    }
    else if(ShouldDisplayPauseMenu())
    {
        // Should do nothing
    }
    else 
    {
        if(mHelichopterManager->ShouldHeliMove(xInfo.width, xInfo.height))
        {
            mHelichopterManager->UpdateHeli(&xInfo);
        }
        mMapManager->UpdateMap(&xInfo, mGameSpeed);
        
        mHelichopterManager->Update(&xInfo, mGameSpeed);
        mMapManager->Update(&xInfo);
    }
}

void GameManager::Repaint()
{
    //XClearWindow( xInfo.display, xInfo.window );
    
    XWindowAttributes windowInfo;
    XGetWindowAttributes(xInfo.display, xInfo.window, &windowInfo);
    unsigned int height = windowInfo.height;
    unsigned int width = windowInfo.width;

    //XFillRectangle(xInfo.display, xInfo.window, xInfo.gc[1], 300, 200, 50, 50);
    XFreePixmap(xInfo.display, xInfo.pixmap);
    int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
    xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, width, height, depth);
    xInfo.width = width;
    xInfo.height = height;

    XFillRectangle(xInfo.display, xInfo.pixmap, xInfo.gc[1], 0, 0, width, height);
    if(ShouldDisplayPauseMenu())
    {
        DisplayPauseMenu();
    }
    else
    {
        stringstream sscore;
        sscore << "Score: " << mMapManager->GetScore() + mPlaneManager->GetScore();
        XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[1],
            10, 10, sscore.str().c_str(), sscore.str().size());

        if(mPhysicsManager->IsInGodMode())
        {
            stringstream sGodMode;
            sGodMode << "GOD MODE";
            XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[1],
                xInfo.width/2 - 20, 50, sGodMode.str().c_str(), sGodMode.str().size());
        }
        mHelichopterManager->Repaint(&xInfo);
        mMapManager->Repaint(&xInfo);
        mPlaneManager->Repaint(&xInfo); 
    }

    XCopyArea(xInfo.display, xInfo.pixmap, xInfo.window, xInfo.gc[1],
        0,0, width, height, 0, 0);
    //XFillRectangle(xInfo.display, xInfo.window, xInfo.gc[1], width-80, height-80, 80, 80);

    XFlush( xInfo.display );
}

void GameManager::InitX(int argc, char *argv[])
{
    XSizeHints hints;
    unsigned long white, black;

    // Display opening uses the DISPLAY environment variable
    // It can go wrong if DISPLAY isn't set, or you don't have permission.
    xInfo.display = XOpenDisplay("");
    if(!xInfo.display)
    {
        error("Can't open display.");
    }

    // Determine the screen's info
    xInfo.screen = DefaultScreen(xInfo.display);
    white = XWhitePixel(xInfo.display, xInfo.screen);
    black = XBlackPixel(xInfo.display, xInfo.screen);

    hints.x = 100;
    hints.y = 100;  
    hints.width = 800;
    hints.height = 600;
    hints.flags = PPosition | PSize;

    xInfo.width = 800;
    xInfo.height = 600;
    xInfo.prevWidth = 800;
    xInfo.prevHeight = 600;

    xInfo.window = XCreateSimpleWindow(
        xInfo.display,              // Display where window appears
        DefaultRootWindow(xInfo.display), //window's parent in window tree
        hints.x, hints.y,           // upper left hand corner location
        hints.width, hints.height,  // size of window
        Border,                    // width of window's border
        black,                      // window border colour
        white                       // window background colour
        );

    XSetStandardProperties(
        xInfo.display,              // display containing the window
        xInfo.window,               // window whose properties are set
        "A1 - Helicopter Side-scrolling game", // windwo's title
        "A1",                       // icon's title
        None,                       // pixmap for the icon
        argv, argc,                 // applications command line args
        &hints                      // size hints for the iwndow
        );

    xInfo.gc[0] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
    XSetForeground(xInfo.display, xInfo.gc[0], BlackPixel(xInfo.display, xInfo.screen));
    XSetBackground(xInfo.display, xInfo.gc[0], WhitePixel(xInfo.display, xInfo.screen));
    XSetFillStyle(xInfo.display, xInfo.gc[0], FillSolid);
    XSetLineAttributes(xInfo.display, xInfo.gc[0],
                     1, LineSolid, CapButt, JoinRound);

    xInfo.gc[1] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
    XSetForeground(xInfo.display, xInfo.gc[1], WhitePixel(xInfo.display, xInfo.screen));
    XSetBackground(xInfo.display, xInfo.gc[1], BlackPixel(xInfo.display, xInfo.screen));
    XSetFillStyle(xInfo.display, xInfo.gc[1], FillSolid);
    XSetLineAttributes(xInfo.display, xInfo.gc[1],
                     1, LineSolid, CapButt, JoinRound);

    xInfo.gc[2] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
    XSetForeground(xInfo.display, xInfo.gc[2], BlackPixel(xInfo.display, xInfo.screen));
    XSetBackground(xInfo.display, xInfo.gc[2], WhitePixel(xInfo.display, xInfo.screen));
    XSetFillStyle(xInfo.display, xInfo.gc[2], FillSolid);
    XSetLineAttributes(xInfo.display, xInfo.gc[2],
                     1, LineSolid, CapButt, JoinRound);

    xInfo.gc[3] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
    XSetForeground(xInfo.display, xInfo.gc[3], BlackPixel(xInfo.display, xInfo.screen));
    XSetBackground(xInfo.display, xInfo.gc[3], WhitePixel(xInfo.display, xInfo.screen));
    XSetFillStyle(xInfo.display, xInfo.gc[3], FillSolid);
    XSetLineAttributes(xInfo.display, xInfo.gc[3],
                     1, LineSolid, CapButt, JoinRound);


    int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
    xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, hints.width, hints.height, depth);
    xInfo.width = hints.width;
    xInfo.height = hints.height;

    XSelectInput(xInfo.display, xInfo.window, 
        ButtonPressMask | KeyPressMask | KeyReleaseMask | ExposureMask);

    XAutoRepeatOff(xInfo.display);
    // Put the window on the screen
    XMapRaised(xInfo.display, xInfo.window);
    XFlush(xInfo.display);
    sleep(2); // let server get set up before sending drawing commands
}

void GameManager::CloseDisplay()
{
    XCloseDisplay(xInfo.display);
    XAutoRepeatOn(xInfo.display);
}

void GameManager::HandleButtonPress(XEvent &event)
{
    // TODO:: Pause the game / Unpause the game
    cout << "Pressed the mouse! Pause/Unpause function." << endl;
    if(mShouldDisplayPause)
    {
        mShouldDisplayPause = false;
    } 
    else
    {
        mShouldDisplayPause = true;
    }

    if(mIsGameOver)
    {
        mIsGameOver = false;
    }
}

void GameManager::HandleKeyPress(XEvent &event)
{
    KeySym key;
    char text[BufferSize];

    int i = XLookupString(
        (XKeyEvent *)&event,    // the keyboard event
        text,                   // buffer when text will be written
        BufferSize,             // size of the text buffer
        &key,                   // workstation-independent key symbol
        NULL                    // pointer to a composeStatus structure (unused)
        );

    
    cout << "This key is pressed:" << text[0] << endl;
    if(text[0] == 'q') 
    {
        cout << "Terminate Normally." << endl;
        mGameLoop = false;
    }
    if(text[0] == 'a')
    {
        mHelichopterManager->AddAcceleration(-1, 0);
        mMovement++;
        mBackward = true;
    }
    else if(text[0] == 'w')
    {
        mHelichopterManager->AddAcceleration(0, -1);
        mMovement++;
        mUp = true;
    }
    else if(text[0] == 's')
    {
        mHelichopterManager->AddAcceleration(0, 1);
        mMovement++;
        mDown = true;
    }
    else if(text[0] == 'd')
    {
        mHelichopterManager->AddAcceleration(1, 0);
        mMovement++;
        mForward = true;
    } 
    if(key == XK_g)
    {
        mPhysicsManager->GodMode();
    }
    if(key == XK_Left)
    {
        cout << "Pressed Left!" << endl;
        if(mGameSpeed > 0)
        {
            mGameSpeed--;
            cout << "Gamespeed: " << mGameSpeed << endl;
        }
    }
    if(key == XK_Right)
    {
        cout << "Pressed Right!" << endl;
        if(mGameSpeed < 10)
        {
            mGameSpeed++;
            cout << "Gamespeed: " << mGameSpeed << endl;
        }
    }
    if(key == XK_m)
    {
        HandleFireMissile(false);
    }
    if(key == XK_f)
    {
        HandleButtonPress(event);
    }
    if(key == XK_n)
    {
        HandleExplosion(event);
    }
    if(text[0] == ' ')
    {
        HandleFireMissile(true);
    }
}  

void GameManager::HandleFireMissile(bool isBomb)
{
    mHelichopterManager->HandleFireMissiles(isBomb);
}

void GameManager::HandleExplosion(XEvent &event)
{
    mHelichopterManager->HandleExplosion();
}

void GameManager::HandleKeyRelease(XEvent &event)
{
    if(mMovement > 0)
    {
        KeySym key;
        char text[BufferSize];

        int i = XLookupString(
            (XKeyEvent *)&event,    // the keyboard event
            text,                   // buffer when text will be written
            BufferSize,             // size of the text buffer
            &key,                   // workstation-independent key symbol
            NULL                    // pointer to a composeStatus structure (unused)
        );

        if(i == 1)
        {
            cout << "This key is released:" << text[0] << endl;
            if(text[0] == 'a')
            {
                if(mForward)
                {
                    mHelichopterManager->AddAcceleration(1, 0);
                }
                else 
                {
                    mHelichopterManager->ResetXAcceleration();
                }
                mBackward = false;
                mMovement--;
            }
            else if(text[0] == 'w')
            {
                if(mDown)
                {
                    mHelichopterManager->AddAcceleration(0, 1);
                }
                else 
                {
                    mHelichopterManager->ResetYAcceleration();
                }
                mUp = false;
                mMovement--;
            }
            else if(text[0] == 's')
            {
                if(mUp)
                {
                    mHelichopterManager->AddAcceleration(0, -1);
                }
                else 
                {
                    mHelichopterManager->ResetYAcceleration();
                }
                mDown = false;
                mMovement--;
            }
            else if(text[0] == 'd')
            {
                if(mBackward)
                {
                    mHelichopterManager->AddAcceleration(-1, 0);
                }
                else 
                {
                    mHelichopterManager->ResetXAcceleration();
                }
                mForward = false;
                mMovement--;
            } 
        }
    }

}

bool GameManager::ShouldDisplayPauseMenu()
{
    return mShouldDisplayPause;
}

void GameManager::DisplayPauseMenu()
{
    stringstream ss;
    stringstream text;
    XFontStruct *font;
    XCharStruct cstruct;
    //char * text = "Hi!";

    cstruct.ascent += 10;

    ss << "-*-fixed-*-*-*-*-20-*-*-*-*-*-*-*";
    font = XLoadQueryFont(xInfo.display, ss.str().c_str());
    if (!font) {
        cout << "Unable to load preferred font: " << ss.str().c_str() << " using fixed instead." << endl;
        font = XLoadQueryFont(xInfo.display, "fixed");
    }
    if(mIsGameOver)
    {
        text << "GAME OVER. Your Score is: " << mMapManager->GetScore() + mPlaneManager->GetScore();
        
        XDrawImageString( xInfo.display, xInfo.pixmap, xInfo.gc[0],
            xInfo.width/2 - 50,  xInfo.height/2, text.str().c_str(), text.str().size());
    }
    else
    {
        int counter = 0;
        text << pauseText[counter++];
        XDrawImageString( xInfo.display, xInfo.pixmap, xInfo.gc[0],
            xInfo.width/2 - 80,  xInfo.height/4 - 50, text.str().c_str(), text.str().size());
        text.str("");


        text << pauseText[counter++];
        XDrawImageString( xInfo.display, xInfo.pixmap, xInfo.gc[0],
            xInfo.width/2 - 25,  xInfo.height/4, text.str().c_str(), text.str().size());
        text.str("");
        
        int textX = xInfo.width/2 - 50;
        int textY = xInfo.height/4 + 25;
        while(counter < pauseTextLength)
        {
            text << pauseText[counter++];
            XDrawImageString( xInfo.display, xInfo.pixmap, xInfo.gc[0],
                textX - 50,  textY, text.str().c_str(), text.str().size());
            text.str("");

            text << pauseText[counter++];
            XDrawImageString( xInfo.display, xInfo.pixmap, xInfo.gc[0],
                textX + 80,  textY, text.str().c_str(), text.str().size());
            text.str("");
            textY += 30;
        }
    } 

}