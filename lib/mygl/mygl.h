#ifndef _MYGL_H_
#define _MYGL_H_

#include <tuple>
#include <cmath>
#include "definitions.h"

using namespace std;

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
class CGDraw
{
  private:
    void swap(int &x1, int &y1, int &x2, int &y2);

    tuple<int, int, int, int> InterpolarCor(tuple<int, int, int, int> RGBAi,
                                            tuple<int, int, int, int> RGBAf,
                                            float D);

    float getLength(int xi, int yi, int xf, int yf);

    tuple<int, int> InterpolarPixel(tuple<int, int> XYi,
                                    tuple<int, int> XYf,
                                    float D);

  public:
    void PutPixel(tuple<int, int> XY,
                  tuple<int, int, int, int> RGBA);

    void DrawLine(tuple<int, int> XYi,
                  tuple<int, int> XYf,
                  tuple<int, int, int, int> RGBAi,
                  tuple<int, int, int, int> RGBAf);

    void DrawTriangle(tuple<int, int> XY1,
                      tuple<int, int> XY2,
                      tuple<int, int> XY3,
                      tuple<int, int, int, int> RGBA1,
                      tuple<int, int, int, int> RGBA2,
                      tuple<int, int, int, int> RGBA3);
};

void CGDraw::swap(int &x1, int &y1, int &x2, int &y2)
{
    int aux = x1;
    x1 = x2;
    x2 = aux;
    aux = y1;
    y1 = y2;
    y2 = aux;
}

float CGDraw::getLength(int xi, int yi, int xf, int yf)
{
    int dx = abs(xf - xi);
    int dy = abs(yf - yi);

    return (sqrt((dx * dx) + (dy * dx)));
}

tuple<int, int, int, int> CGDraw::InterpolarCor(tuple<int, int, int, int> RGBAi, tuple<int, int, int, int> RGBAf, float D)
{
    return make_tuple(get<0>(RGBAf) * D + (1 - D) * get<0>(RGBAi),
                      get<1>(RGBAf) * D + (1 - D) * get<1>(RGBAi),
                      get<2>(RGBAf) * D + (1 - D) * get<2>(RGBAi),
                      get<3>(RGBAf) * D + (1 - D) * get<3>(RGBAi));
}

tuple<int, int> CGDraw::InterpolarPixel(tuple<int, int> XYi, tuple<int, int> XYf, float D)
{
    return make_tuple(get<0>(XYf) * D + (1 - D) * get<0>(XYi),
                      get<1>(XYf) * D + (1 - D) * get<1>(XYi));
}

void CGDraw::PutPixel(tuple<int, int> XY, tuple<int, int, int, int> RGBA)
{
    int R, G, B, A;
    int x, y;

    tie(R, G, B, A) = RGBA;
    tie(x, y) = XY;

    if (x > IMAGE_WIDTH || x < 0 || y > IMAGE_HEIGHT || y < 0) //verifica se ta desenhando fora
        return;

    FBptr[(4 * x) + (4 * y * IMAGE_HEIGHT) + 0] = R; // componente R
    FBptr[(4 * x) + (4 * y * IMAGE_HEIGHT) + 1] = G; // componente G
    FBptr[(4 * x) + (4 * y * IMAGE_HEIGHT) + 2] = B; // componente B
    FBptr[(4 * x) + (4 * y * IMAGE_HEIGHT) + 3] = A; // componente A
}

void CGDraw::DrawLine(tuple<int, int> XYi, tuple<int, int> XYf,
                      tuple<int, int, int, int> RGBAi, tuple<int, int, int, int> RGBAf)
{
    int x1, y1, x2, y2,
        R, G, B, A, R2, G2, B2, A2,
        Dx, Dy,
        y, x,
        c;
    float cAng, mx, my, D, distance, TotalDistance;
    bool flag[3]; //lowHigh,X1,Y1

    tie(x1, y1) = XYi;
    tie(x2, y2) = XYf;
    tie(R, G, B, A) = RGBAi;
    tie(R2, G2, B2, A2) = RGBAf;
    tie(x1, y1) = XYi;
    tie(x2, y2) = XYf;

    flag[0] = (abs(y2 - y1) < abs(x2 - x1));
    flag[1] = (x1 > x2);
    flag[2] = (y1 > y2);

    if (flag[1]) //faz a troca se um dos pontos iniciai for maior que o final
    {
        swap(x1, y1, x2, y2);
    }

    Dx = (x2 - x1);
    Dy = (y2 - y1);

    //termo independente
    c = -x1 * y2 + x2 * y1;
    //coeficiente angular
    cAng = (float)Dy / Dx;
    //coeficientes angulares
    mx = x1 + 1.0;
    my = y1 + (cAng >= 0 ? 0.5 : -0.5);
    D = -Dx * my + Dy * mx + c;

    y = y1;
    x = x1;

    TotalDistance = getLength(x1, y1, x2, y2);
    for (x = x1; x < x2; x++)
    {
        distance = getLength(x, y, x2, y2) / TotalDistance;
        PutPixel(make_tuple(x, y), InterpolarCor(RGBAi, RGBAf, distance));
        if (D > 0)
        {
            //SE escolhido se cAng>=0, E escolhido se cAng<0
            if (cAng >= 0)
            {
                y++;
                D -= Dx;
            }
        }
        else
        { //E escolhido se cAng>=0, NE escolhido se cAng<0
            if (cAng < 0)
            {
                y--;
                D += Dx;
            }
        }
        D += Dy;
    }
}

void CGDraw::DrawTriangle(tuple<int, int> XY1, tuple<int, int> XY2, tuple<int, int> XY3,
                          tuple<int, int, int, int> RGBA1,
                          tuple<int, int, int, int> RGBA2,
                          tuple<int, int, int, int> RGBA3)
{
    DrawLine(XY1, XY2, RGBA2, RGBA1);
    DrawLine(XY2, XY3, RGBA2, RGBA3);
    DrawLine(XY3, XY1, RGBA3, RGBA1);
}

#endif // _MYGL_H_
