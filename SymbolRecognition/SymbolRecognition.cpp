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



SuperInt EvalNestedSeriesSumm(int value, int nestLevel)
{
    SuperInt unit(2, 1);
    SuperInt factor(2, 1);

    SuperInt dividend(20, value);
    SuperInt dividendRes(20, value);
    SuperInt divisor(2, 1);

    if (nestLevel <1)
    {
        dividendRes = unit;
    }

    for (int i = 1; i < nestLevel; i++)
    {
        dividend = dividend.Sum(unit);
        dividendRes = dividendRes.Mult(dividend);

        factor = factor.Sum(unit);
        divisor = divisor.Mult(factor);

    }

    dividendRes = dividendRes.Div(divisor);

    return dividendRes;
}


vector<bool> img = { 1,1,0,0,0,0,0,0};

SuperInt GetImageNum(const vector<bool>& img)
{
    SuperInt res(2, 1);
    int unitsNum = 0;
    int imgSize = img.size();
    for (bool unit : img)
    {
        unitsNum += unit;
    }

    if (unitsNum < img.size() / 2)
    {
        int nestLev = 0;

        for (int i = 1; i < unitsNum; i++)
        {
            res = res.Sum(EvalNestedSeriesSumm((imgSize + 1) - i, i));
            nestLev = i;
        }


        int PrevElPos = -1;
        int distFromPrev = 0;
        int maxNum = imgSize - (unitsNum - 1);
        for (int i = 0; i < imgSize; i++)
        {
            if (img[i])
            {

                if ((i - PrevElPos) > 1)
                {
                    for (int j = PrevElPos + 1; j < i; j++)
                    {
                        res = res.Sum(EvalNestedSeriesSumm(maxNum, nestLev));

                        maxNum--;
                    }
                }

                nestLev--;
                PrevElPos = i;
            }

        }
        res.PrintDecimal();
        cout << endl;
    }
    return res;
}

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
    GetImageNum(img);
}