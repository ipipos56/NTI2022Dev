#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>


using namespace std;

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

double distanceBetweenPoints(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}



int main() {
    freopen("C:/NTI2022Dev/6Task/Task_6_only/1.txt", "r", stdin);
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
    //cout << minDistance << " " << minPoint[3] << " " << minPoint[4] << " " << minPoint[5] << endl;
    //cout<<minPoint<<endl;
    vector<Point*> brickPoints;
    //cout<<points.size()<<endl;
    double meanValueX = 0, meanValueY;
    for (int i = 0; i < points.size(); i++) {
        if (abs(points[i]->z - minPoint.z) <= 0.005) {
            //cout<<abs(points[i]->z - minPoint.z)<<endl;
            brickPoints.emplace_back(points[i]);
            meanValueX += points[i]->x;
            meanValueY += points[i]->y;
        }
    }
    meanValueX/=brickPoints.size();
    meanValueY/=brickPoints.size();
    Point tempPoint(vector<double>{meanValueX,meanValueY,minPoint.z,0,0,0});
    Point meanPoint;
    double meanDistance = 10000000;
    for (int i = 0; i < brickPoints.size(); i++) {
        if(distanceBetweenPoints(tempPoint,*brickPoints[i]) < meanDistance)
        {
            meanDistance = distanceBetweenPoints(tempPoint,*brickPoints[i]);
            meanPoint = *brickPoints[i];
        }
    }
    cout<<meanPoint<<endl;
    return 0;
}
