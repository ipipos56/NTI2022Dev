#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>


using namespace std;

//#define COEFF 0.000334
#define COEFF 0.002

struct Point{
public:
    double x;
    double y;
    double z;

    double r;
    double g;
    double b;

    void setValues(vector<double> input)
    {
        this->x = input[0];
        this->y = input[1];
        this->z = input[2];
        this->r = input[3];
        this->g = input[4];
        this->b = input[5];
    }

    Point()
    {
        this->x = -1;
        this->y = -1;
        this->z = -1;
        this->r = -1;
        this->g = -1;
        this->b = -1;
    }

    Point(vector<double> input)
    {
        this->x = input[0];
        this->y = input[1];
        this->z = input[2];
        this->r = input[3];
        this->g = input[4];
        this->b = input[5];
    }

    friend ostream& operator<<(ostream& os, const Point& obj1)
    {
        os << obj1.x << ',' << obj1.y  << ',' << obj1.z ;
        return os;
    }

};

vector<double> spaceSplitter(string inp) {
    vector<double> outputVector;
    int n,nOld=0;
    n = inp.find(" ");
    while (n != -1) {
        outputVector.emplace_back(atof(inp.substr(0, n).c_str()));
        inp.erase(0,n+1);
        n = inp.find(" ");
        //nOld = n+1;
    }
    outputVector.emplace_back(atof(inp.c_str()));
    return outputVector;
}

int brickPoints = 0;

void brickSpaceDeleter(int x, int y, vector<vector<int>> &map)
{
    map[x][y] = 0;
    brickPoints++;
    if(map[x-1][y] == 1)
        brickSpaceDeleter(x-1,y,map);
    if(map[x-1][y-1] == 1)
        brickSpaceDeleter(x-1,y-1,map);
    if(map[x][y-1] == 1)
        brickSpaceDeleter(x,y-1,map);
    if(map[x+1][y-1] == 1)
        brickSpaceDeleter(x+1,y-1,map);
    if(map[x+1][y] == 1)
        brickSpaceDeleter(x+1,y,map);
    if(map[x+1][y+1] == 1)
        brickSpaceDeleter(x+1,y+1,map);
    if(map[x][y+1] == 1)
        brickSpaceDeleter(x,y+1,map);
    if(map[x-1][y+1] == 1)
        brickSpaceDeleter(x-1,y+1,map);
}


int main() {
    freopen("C:/NTI2022Dev/4Task/Task_4_only/3.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    string inputLine;
    getline(cin, inputLine);
    double minDistance = -1000000;
    Point minPoint;
    vector<Point*> points;
    while (getline(cin, inputLine)) {
        Point *curInput = new Point();
        curInput->setValues(spaceSplitter(inputLine));
        points.emplace_back(curInput);
        if (curInput->z > minDistance && curInput->z < -0.11) {
            minDistance = curInput->z;
            minPoint = *curInput;
        }
    }
    //cout<<minPoint<<endl;
    //cout<<minPoint.r<<","<<minPoint.g<<","<<minPoint.b<<endl;
    double minX = points[0]->x, minY = points[0]->y, maxX=points[0]->x, maxY=points[0]->y;
    for (int i = 1; i < points.size(); i++) {
       if(points[i]->x < minX)
           minX = points[i]->x;
        if(points[i]->x > maxX)
            maxX = points[i]->x;
        if(points[i]->y < minY)
            minY = points[i]->y;
        if(points[i]->y > maxY)
            maxY = points[i]->y;
    }

    int width = (maxX - minX) / COEFF;
    int height = (maxY - minY) / COEFF;

    //cout<<width<<","<<height<<endl;
    vector<vector<int>> map(height+1, vector<int>(width+1, 0));
    for(int i = 0;i<points.size();i++)
    {
        int x,y;
        x = (points[i]->x + abs(minX)) / COEFF;
        y = (points[i]->y + abs(minY)) / COEFF;
        if(points[i]->r > 0.35 && points[i]->g < 0.3 && points[i]->b < 0.3)
            map[y][x] = 1;
        else if(points[i]->b > 0.35 && points[i]->r < 0.3 && points[i]->g < 0.3)
            map[y][x] = 2;
    }

    int brickCount = 0;
    for(int i = 1;i<map.size()-1;i++)
    {
        for(int j = 1;j<map[i].size()-1;j++)
        {
            if(map[i][j] == 1) {
                brickPoints = 0;
                brickSpaceDeleter(i, j, map);
                if(brickPoints > 60)
                    brickCount++;
            }
        }
    }
    cout<<brickCount<<endl;
    return 0;
}
