#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <iostream>
#include <cstdlib>
#include <vector>

#include "Objects.h"
#include "WallObj.h"
#include "TargetObj.h"
#include "XInfo.h"

class MapManager 
{
public:
    MapManager(XInfo* xInfo);
    ~MapManager();

    void Update(XInfo* xInfo);
    void Repaint(XInfo* xInfo);
    void UpdateMap(XInfo* xInfo, int velX);
    void GenerateWall(XInfo* xInfo);
    int GetScore();
    void ExposeUpdate(XInfo* xInfo);

    std::vector<WallObj*>* GetWallObjVector();
    std::vector<TargetObj*>* GetTargetObjVector();

private:
    std::vector<WallObj*> mWallObjs;
    std::vector<TargetObj*> mTargetObjs;

    int mMapCounter;
    int mWallHeight;
    int mScore;

    int mWallGenHeight;
    int mWallGenWidth;
    int mTargetGenHeight;
    int mTargetGenWidth;
};

#endif