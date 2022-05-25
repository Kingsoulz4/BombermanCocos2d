#include "AIHigh.h"

AIHigh::AIHigh()
{
}

AIHigh::AIHigh(BattleScene* battleScene)
{
    this->battleScene = battleScene;
}

AIHigh::~AIHigh()
{
}

//std::vector<Point> AIHigh::findpath(Point src, Point dest)
//{
//    
//    std::queue<Point> q;
//    q.push(src);
//    std::vector<Point> res;
//    const int dx[4] = { -1, 0, 1, 0 };
//    const int dy[4] = { 0, 1, 0, -1 };
//    std::map<Point, bool> trace;
//    Size size = battleScene->getTileMap()->getMapSize();
//    for (int i = 0; i < size.height; i++)
//    {
//        for (int j = 0; j < size.width; j++)
//        {
//            trace.insert(std::make_pair(Point(j, i), false));
//        }
//    }
//    while (!q.empty())
//    {
//        auto pnt = q.front();
//        q.pop();
//        
//        res.push_back(pnt);
//        if (pnt == dest)
//        {
//            return res;
//        }
//        for (size_t i = 0; i < 4; i++)
//        {
//            Point p = Point(pnt.x + dx[i], pnt.y + dy[i]);
//            if (p.x < 0 || p.x >= size.width || p.y < 0 || p.y >= size.height || trace.at(p) 
//                || battleScene->getLayerFrame()->tileGIDAt(p) != 0 
//                || battleScene->getLayerContainer()->tileGIDAt(p) != 0
//                || battleScene->getLayerObstacle()->tileGIDAt(p) != 0)
//            {
//                continue;
//            }
//            q.push(p);
//            trace.at(p) = true;
//        }
//
//    }
//    return std::vector<Point>();
//}

std::vector<Point> AIHigh::findpath(Point src, Point dest)
{

    std::queue<Point> q;
    q.push(src);
    std::vector<Point> res;
    const int dx[4] = { -1, 0, 1, 0 };
    const int dy[4] = { 0, 1, 0, -1 };
    std::map<Point, bool> trace;
    std::map<Point, Point> step;
    Size size = battleScene->getTileMap()->getMapSize();
    for (int i = 0; i < size.height; i++)
    {
        for (int j = 0; j < size.width; j++)
        {
            trace.insert(std::make_pair(Point(j, i), false));
        }
    }
    for (int i = 0; i < size.height; i++)
    {
        for (int j = 0; j < size.width; j++)
        {
            step.insert(std::make_pair(Point(j, i), Point(-1, -1)));
        }
    }
    step.at(src) = Point(-2, -2);
    while (!q.empty())
    {
        auto pnt = q.front();
        q.pop();

        //res.push_back(pnt);
        if (pnt == dest)
        {
            if (step.at(dest) != Point(-1, -1))
            {
                Point p = dest;
                while (p != src)
                {
                    res.push_back(p);
                    p = step.at(p);
                }
                return res;

            }
            return res;
        }
        for (size_t i = 0; i < 4; i++)
        {
            Point p = Point(pnt.x + dx[i], pnt.y + dy[i]);
            if (p.x < 0 || p.x >= size.width || p.y < 0 || p.y >= size.height || trace.at(p)
                || battleScene->getLayerFrame()->tileGIDAt(p) != 0
                || battleScene->getLayerContainer()->tileGIDAt(p) != 0
                || battleScene->getLayerObstacle()->tileGIDAt(p) != 0)
            {
                continue;
            }
            q.push(p);
            trace.at(p) = true;
            step.at(p) = pnt;
        }

    }
    return std::vector<Point>();
}

//std::vector<Point> AIHigh::findpath(Point src, Point dest)
//{
//
//    std::queue<Point> q;
//    q.push(src);
//    std::vector<Point> res;
//    const int dx[4] = { -1, 0, 1, 0 };
//    const int dy[4] = { 0, 1, 0, -1 };
//    std::map<Point, Point> trace;
//    Size size = battleScene->getTileMap()->getMapSize();
//    for (int i = 0; i < size.height; i++)
//    {
//        for (int j = 0; j < size.width; j++)
//        {
//            trace.insert(std::make_pair(Point(j, i), Point(-1,-1)));
//        }
//    }
//    trace.at(dest) = Point(-2, -2);
//    while (!q.empty())
//    {
//        auto pnt = q.front();
//        q.pop();
//
//        res.push_back(pnt);
//        if (pnt == dest)
//        {
//            if (trace.at(src) != Point( - 1,-1))
//            {
//                Point p = src;
//                while (p != Point(-2, -2))
//                {
//                    res.push_back(p);
//                    p = trace.at(p);
//                }
//                return res;
//
//             }
//            return res;
//        }
//        for (size_t i = 0; i < 4; i++)
//        {
//            Point p = Point(pnt.x + dx[i], pnt.y + dy[i]);
//            if (p.x < 13 || p.x >= 45 || p.y < 3 || p.y >= 23 || trace.at(p) != Point(-1, -1)
//                || battleScene->getLayerFrame()->tileGIDAt(p) != 0
//                || battleScene->getLayerContainer()->tileGIDAt(p) != 0
//                || battleScene->getLayerObstacle()->tileGIDAt(p) != 0)
//            {
//                continue;
//            }
//            q.push(p);
//            trace.at(p) = pnt;
//        }
//
//    }
//    return std::vector<Point>();
//}

//std::vector<Point> AIHigh::findpath(Point src, Point dest)
//{
//
//    std::queue<std::pair<int, int>> q;
//    q.push(std::make_pair(src.x,src.y));
//    std::vector<Point> res;
//    const int dx[4] = { -1, 0, 1, 0 };
//    const int dy[4] = { 0, 1, 0, -1 };
//    std::map<std::pair<int, int>, std::pair<int, int>> trace;
//    Size size = battleScene->getTileMap()->getMapSize();
//    for (int i = 0; i < size.height; i++)
//    {
//        for (int j = 0; j < size.width; j++)
//        {
//            trace.insert(std::make_pair(std::make_pair(j,i), std::make_pair(-1, -1)));
//        }
//    }
//    trace.at(std::make_pair((int)dest.x, (int)dest.y)) = std::make_pair(-2, -2);
//    while (!q.empty())
//    {
//        auto pnt = q.front();
//        q.pop();
//        
//        if (pnt == std::make_pair((int)dest.x, (int)dest.y))
//        {
//            break;
//        }
//        
//        for (size_t i = 0; i < 4; i++)
//        {
//            auto p = std::make_pair(pnt.first + dx[i], pnt.second + dy[i]);
//            while (!(p.first < 13 || p.first >= 45|| p.second < 3 || p.second >= 23))
//            {
//                if(!( trace.at(p) != std::make_pair(-1, -1)
//                    || battleScene->getLayerFrame()->tileGIDAt(Point(p.first, p.second)) != 0
//                    || battleScene->getLayerContainer()->tileGIDAt(Point(p.first, p.second)) != 0
//                    || battleScene->getLayerObstacle()->tileGIDAt(Point(p.first, p.second)) != 0))
//
//                {
//                    q.push(p);
//                    trace.at(p) = pnt;
//                }
//                p.first += dx[i];
//                p.second += dy[i];
//               
//            }
//            
//        }
//
//    }
//    if (trace.at(std::make_pair(src.x, src.y)).first != -1)
//    {
//        std::pair<int, int> p = std::make_pair(src.x, src.y);
//        while (p != std::make_pair(-2, -2))
//        {
//            res.push_back(Point(p.first, p.second));
//            p = trace.at(p);
//        }
//        return res;
//
//    }
//
//    return std::vector<Point>();
//}


