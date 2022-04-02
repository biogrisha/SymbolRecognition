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
vector<SuperInt> coefs;



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


vector<bool> imgVec;

SuperInt GetImageNum(const vector<bool>& img)
{
    SuperInt res(2, 1);
    int unitsNum = 0;
    int imgSize = img.size();
    for (bool unit : img)
    {
        unitsNum += unit;
    }

    if (unitsNum <= img.size() / 2)
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
    }
    return res;
}




SuperInt GetImgCode(std::string path)
{
    imgVec.clear();
    Image img(path);
    RGB rgb(0, 0, 0);
    int el = 0;
    for (int x = 0;x < 10;x++)
        for (int y = 0;y < 10;y++)
        {
            rgb = img.GetPixel(x, y);
            if (rgb.G == 0)
            {
                imgVec.push_back(1);
            }
            else
            {
                imgVec.push_back(0);
            }
        }

    //cout << getSum() << endl;
    return GetImageNum(imgVec);
}

SuperInt GetFuncRes(SuperInt x, SuperInt tolerance, int polDeg)
{
    bool isModified = false;
    SuperInt res(2,1);
    int sz = coefs.size();
    int i2 = 0;
    int leftComp = 0;
    int rightComp = 0;
    for (int i = 1;i < sz; i++)
    {
        if (i2 < sz - polDeg * 2 && i > polDeg)
        {
            i2++;
        }

        leftComp = x.Compare(coefs[i - 1]);
        rightComp = x.Compare(coefs[i]);
        if (leftComp <=0 && rightComp >=0)
        {
            for (int j = 0; j < polDeg * 2;j++)
            {
                res =  res.Mult(x.Diff( coefs[i2 + j]));
                isModified = true;
            }
            break;
        }
    }

    if (isModified)
    {
        res = res.Div(tolerance);
    }
    else
    {
        res = tolerance;
    }
    return res;
}

void InitCoefs()
{
    coefs.push_back(SuperInt({ 0,0,1,1,0,1,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,1,0,0,0,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1,0,0,0,0,0,1,0,1,1,0,1,1,1,0 }));
    coefs.push_back(SuperInt({ 0,0,1,1,1,0,1,0,0,0,0,0,1,0,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,0,1,0,1,1,1,0,0,1,0,1,1,0,1,0,0,1,1,0,1,0,0,0,0,1,0,0,1,0,1,1,0,1,1,1,0,1,1,0,0,1,0 }));
    coefs.push_back(SuperInt({ 0,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,1,0,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,1,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,1,1,0,1,0,1,0,1,0,0,1,0,0,0,0,1,1,0 }));
    coefs.push_back(SuperInt({ 1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,0 }));
    coefs.push_back(SuperInt({ 0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,0,1,0,1,1,0,0,1,1,0,0,0,1,0,0,1,0,1,1,1,1,0,0,0,1,1,0,0,1,0 }));
    coefs.push_back(SuperInt({ 0,1,1,1,1,1,0,0,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1,0,0,1,0,0,1,0,1,1,1,1,0,0,0,1,1,0,1,0,0,1,1,0,1,0,0,1,0,0,1,1,0,1,1,1,0 }));
    coefs.push_back(SuperInt({ 0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1,0 }));
    coefs.push_back(SuperInt({ 0,1,0,1,1,0,0,1,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,1,1,0,1,0,0,1,0,1,0,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,1,1,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,0,1,0 }));
    coefs.push_back(SuperInt({ 0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,1,0,0,1,0,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,0 }));
    coefs.push_back(SuperInt({ 0,0,0,1,1,1,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1,0,1,0,1,0,0,1,1,0,0,1,0 }));
    coefs.push_back(SuperInt({ 0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,1,1,0,1,0,1,0,0,1,1,0,0,0,1,0,0,1,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1,0,1,0,0,1,0,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0 }));
    coefs.push_back(SuperInt({ 0,1,0,1,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,0,1,1,0,0,1,0,1,0,0,1,0,0,1,1,1,0 }));
    coefs.push_back(SuperInt({ 1,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,0,1,0,1,0,1,1,1,1,0,0,1,0,1,0,1,0,0,0,0,0,0,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,1,0,0,0,1,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,0 }));
    coefs.push_back(SuperInt({ 0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,1,1,1,0,0,1,0,1,1,1,0,0,0,1,0,1,1,0,0,1,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,1,0,1,1,0 }));
    coefs.push_back(SuperInt({ 0,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0,0,1,0,1,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,0,1,0,1,1,1,0,0,1,0 }));
    coefs.push_back(SuperInt({ 0,0,1,0,0,0,0,0,1,0,1,0,0,1,1,1,1,0,0,0,0,1,1,1,0,1,0,1,0,0,1,0,1,1,1,1,0,1,1,0,1,1,0,1,0,0,1,1,1,0,1,1,1,1,0,0,1,1,1,0,0,0,1,0,1,0,1,0,0,1,0 }));

    std::sort(coefs.begin(), coefs.end());
}
int main(int argc, char** argv)
{
    SuperInt threshold(vector<bool>(60,1));

    SuperInt toCheck1 = GetImgCode("C:/CPPDEV/Projects/SymbolRecognition/SymbolRecognition/fim1.bmp");
    //SuperInt toCheck2 = GetImgCode("C:/CPPDEV/Projects/SymbolRecognition/SymbolRecognition/fim2.bmp");
    SuperInt tol(vector<bool>(350, 1));

    InitCoefs();

    
    SuperInt res1 = GetFuncRes(toCheck1,tol,3);
    //SuperInt res2 = GetFuncRes(toCheck2, tol, 2);


    if (threshold > res1)
    {
        cout << "res1 is 2";
        cout << endl;
    }

    res1.PrintBinary();
    cout << endl;
    //toCheck1.PrintBinaryEx();

}