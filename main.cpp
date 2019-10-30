#include <iostream>
#include <list>
#include <bits/stdc++.h>
using namespace std;

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize) {

    int mapSize = nMapWidth * nMapHeight;
    //The index for our starting position and target position
    int startIdx = nStartX + nStartY * nMapWidth;
    int targetIdx = nTargetX + nTargetY * nMapWidth;

    //In case our goal destination is non traversable
    if(pMap[startIdx] == 0) return -1;
    //In case start destination is non traversable
    if(pMap[targetIdx] == 0) return -1;
    //If our starting position is the same as our target position
    if(startIdx == targetIdx) {
        if(nOutBufferSize == 0)
            return -1;
        else
            return 0;
    }

    //Assume we can only move vertically or horizontally
    //North, south, east and west
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    //Two queues with x/y coordinates to avoid one queue of objects
    list <int> x, y;
    bool visited[mapSize];
    //Keeps track of every vertex's predecessor
    int pred[mapSize];

    //Initialise the visited array
    for(int i = 0; i < nMapWidth*nMapHeight; ++i) {
        visited[i] = false;
    }

    //add starting positions x and y to the list queues
    x.push_back(nStartX);
    y.push_back(nStartY);

    //Set starting position to visited
    visited[startIdx] = true;

    bool reachedGoal = false;

    //BFS algorithm
    //We don't have to keep track of the distance as the shortest distance to any vertex will always be
    //the first on reaching the vertex in an unweighted graph
    while(!x.empty() && !y.empty()) {

        int c = x.front();
        int r = y.front();
        x.pop_front();
        y.pop_front();
        int currentIdx = c + r * nMapWidth;

        //Try moving in all four directions
        for(int i = 0; i < 4; ++i) {
            int cc = c + dc[i];
            int rr = r + dr[i];
            int nextIdx = cc + rr * nMapWidth;

            //Avoid invalid cells
            if(cc < 0 || rr < 0 || cc >= nMapWidth || rr >= nMapHeight) continue;
            if(pMap[nextIdx] == 0) continue;
            if(visited[nextIdx]) continue;

            //We know that cc and rr is a neighbouring cell, traversable, non-visited
            visited[nextIdx] = true;
            pred[nextIdx] = currentIdx;

            if(nextIdx == targetIdx) {
                reachedGoal = true;
                break;
            }

            x.push_back(cc);
            y.push_back(rr);
        }
    }
    //There is no path between starting position and target position
    if(!reachedGoal) {
        return -1;
    }

    //Go through the shortest path recursively from target to start position
    vector<int> path;
    int currentIdx = targetIdx;
    path.push_back(currentIdx);

    while(pred[currentIdx] != startIdx) {
        path.push_back(pred[currentIdx]);
        currentIdx = pred[currentIdx];
    }
    int returnVal = path.size();

    //If our found path is bigger than the requirement, just return the distance
    if(path.size() > nOutBufferSize) return returnVal;

    int j = 0;
    //Copy to output buffer in the reverse order
    for(int i = path.size() - 1; i >= 0; --i) {
        pOutBuffer[j] = path[i];
        j++;
    }

    return returnVal;
}
