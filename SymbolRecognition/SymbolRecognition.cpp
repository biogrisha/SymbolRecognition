#include <iostream> 
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include "Image.h"
#include "SuperInt.h"

using namespace std;
vector<float> coefs;

//vector<bool> img = { 11110000 };




float getSum()
{
   
    return 0;
}


float GetImgCode(std::string path)
{
    Image img(path);
    RGB rgb(0, 0, 0);
    int el = 0;
    for (int x = 0;x < 18;x++)
        for (int y = 0;y < 18;y++)
        {
            rgb = img.GetPixel(x, y);
            if (rgb.G == 0)
            {
                /*Vect vect;
                vect.x = x;
                vect.y = y;

                vec.push_back(vect);*/
            }
            else
            {
            }
        }

    //cout << getSum() << endl;
    return getSum();
}

float GetFuncRes(float x, float tolerance, int polDeg)
{

    float res = 1;
    int sz = coefs.size();
    int i2 = 0;
    for (int i = 1;i < sz; i++)
    {
        if (i2 < sz - polDeg * 2 && i > polDeg)
        {
            i2++;
        }

        if (x > coefs[i - 1] && x < coefs[i])
        {
            for (int j = 0; j < polDeg * 2;j++)
            {
                res *= (x - coefs[i2 + j]) * tolerance;
            }
            break;
        }
    }
    return res;
}


int main(int argc, char** argv)
{

}