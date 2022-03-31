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
vector<float> coefs1;


struct Vect
{
    float x = 0;
    float y = 0;
};


vector<int> vec;

float oper(float a, float b)
{
    float res = 0;
    if (a > b)
    {
        res = a + (b * a);
    }
    else
    {
        res = b + (b * a);
    }
    return res;
}

void PutCoefs()
{
    float startVal = 0.00217;
    float sum = startVal;
    float temp = startVal;
    for (int i = 0; i < 324; i++)
    {
        temp = oper(sum, startVal);
        sum = oper(temp, sum);
        coefs1.push_back(temp);
    }
    auto rng = std::default_random_engine(4);
    std::shuffle(coefs1.begin(), coefs1.end(), rng);
}

float getSum()
{
    float sum = 0.00217;
    for (int i = 0; i < 324; i++)
    {
        if (vec[i] == 0)
        {
            sum = oper(sum, coefs1[i]);
        }
    }
    return sum;
}


//float getSum1()
//{
//    float dist = 0;
//    float distTemp = 0;
//    float sum = 0;
//    Vect meanV;
//    Vect distant1;
//    Vect distant2;
//
//    for (Vect el : vec)
//    {
//        meanV.x += el.x;
//        meanV.y += el.y;
//    }
//
//    meanV.x /= vec.size();
//    meanV.y /= vec.size();
//
//    for (Vect el : vec)
//    {
//        distTemp = sqrt(pow(el.x - meanV.x, 2) + pow(el.y - meanV.y, 2));
//        if (dist < distTemp)
//        {
//            dist = distTemp;
//            distant1 = el;
//        }
//
//    }
//    dist = 0;
//    for (Vect el : vec)
//    {
//        
//        distTemp = sqrt(pow(el.x - distant1.x, 2) + pow(el.y - distant1.y, 2));
//        if (dist < distTemp)
//        {
//            dist = distTemp;
//            distant2 = el;
//        }
//
//    }
//
//
//    for (Vect el : vec)
//    {
//
//        sum += (sqrt(pow(el.x - distant1.x, 2) + pow(el.y - distant1.y, 2)) / dist);
//        sum += (sqrt(pow(el.x - distant2.x, 2) + pow(el.y - distant2.y, 2)) / dist);
//        sum -= (sqrt(pow(el.x - meanV.x, 2) + pow(el.y - meanV.y, 2)) / dist);
//
//    }
//    //sum /= vec.size();
//    return sum;
//
//}
float GetImgCode(std::string path)
{
    PutCoefs();
    Image img(path);
    vec.clear();
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
                vec.push_back(0);
            }
            else
            {
                vec.push_back(1);
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

void init()
{
    coefs.push_back(2.74516);
    coefs.push_back(0.202901);
    coefs.push_back(0.326133);
    coefs.push_back(0.247653);
    coefs.push_back(0.116014);
    coefs.push_back(0.971055);
    coefs.push_back(0.105421);
    coefs.push_back(0.105464);
    coefs.push_back(1.08206);
    coefs.push_back(0.42194);
    coefs.push_back(1.42704);
    coefs.push_back(0.354507);
    coefs.push_back(0.85929);
    coefs.push_back(1.74937);
    coefs.push_back(0.0796379);
    coefs.push_back(0.252362);
    coefs.push_back(1.13218);
    coefs.push_back(0.657803);
    coefs.push_back(0.559644);
    coefs.push_back(0.0855772);
    coefs.push_back(0.115039);
    coefs.push_back(0.33337);
    coefs.push_back(0.366657);
    coefs.push_back(0.196804);
    coefs.push_back(0.25897);
    coefs.push_back(0.129121);
    coefs.push_back(0.47371);
    coefs.push_back(0.234778);
    coefs.push_back(0.308576);
    coefs.push_back(0.228317);
    coefs.push_back(0.0380453);
    coefs.push_back(1.36545);
    coefs.push_back(0.134692);
    coefs.push_back(0.172951);
    coefs.push_back(0.114426);
    coefs.push_back(0.135917);
    coefs.push_back(0.524709);
    coefs.push_back(0.292219);
    coefs.push_back(1.93524);
    coefs.push_back(0.546157);
    coefs.push_back(0.414247);
    coefs.push_back(0.624098);
    coefs.push_back(0.0364047);
    coefs.push_back(0.175312);
    coefs.push_back(0.212383);
    coefs.push_back(0.173366);
    coefs.push_back(1.72796);
    coefs.push_back(1.74115);
    coefs.push_back(0.358875);
    coefs.push_back(0.559701);



    sort(coefs.begin(), coefs.end());

}
int main(int argc, char** argv)
{
    SuperInt s_1(234, 15);
    s_1.PrintDecimal();
    cout << endl;
    SuperInt s_2(100, 15);
    s_2.PrintDecimal();
    cout << endl;
    SuperInt s_3 = s_1.Mult(s_2);
    s_3.PrintDecimal();
    cout << endl;
    cout << (s_2 > s_1);

}