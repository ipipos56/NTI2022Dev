#include <iostream>
#include <vector>
#include <string>


using namespace std;

vector<double> spaceSplitter(string inp)
{
    vector<double> outputVector;
    int n;
    n = inp.find(" ");
    while(n != -1)
    {
        outputVector.emplace_back(atof(inp.substr(0,n).c_str()));
        inp.erase(0,n+1);
        n = inp.find(' ');
    }
    outputVector.emplace_back(atof(inp.c_str()));
    return outputVector;
}

int main() {
    freopen("C:/NTI2022Dev/3Task/Task_3_only/1.txt", "r", stdin);
    string inputLine;
    getline(cin,inputLine);
    double minDistance = -1000000;
    vector<double> minPoint;
    while(getline(cin,inputLine))
    {
        vector<double> curInput;
        curInput = spaceSplitter(inputLine);
        if(curInput[2] > minDistance && curInput[2] < -0.11)
        {
            minDistance = curInput[2];
            minPoint = curInput;
        }
    }
    cout<<minDistance<<" "<<minPoint[3]<<" "<<minPoint[4]<<" "<<minPoint[5]<<endl;
    //cout<<minPoint[0]<<" "<<minPoint[1]<<" "<<minPoint[2]<<endl;
    return 0;
}
