#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <cmath> //sqrt

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
typedef struct cor 
{
	int R;
	int G;
	int B;
	int A;
}COR;

typedef struct vertices 
{
	int x;
	int y;
}VERTICES;

//Pixel 
struct Pixel
{
    int pos_x;
    int pos_y;
};

//Create Pixel
Pixel createPixel(int pos_x, int pos_y, Pixel pixel){

    pixel.pos_x = pos_x;
    pixel.pos_y = pos_y;

    return pixel;
}

//Draw Pixel
int PutPixel(VERTICES v, COR p){

	int valor = 4*v.x + 4*v.y*IMAGE_WIDTH;

	FBptr[valor + 0] = p.R;
	FBptr[valor + 1] = p.G;
	FBptr[valor + 2] = p.B;
	FBptr[valor + 3] = p.A;

}
void DrawLine(int x1,int y1, int x2, int y2){
		COR p = {255,255,255,0};
		COR p1 = {255,255,255,0}; 
		VERTICES v1 = {x1,y1};
		VERTICES v2 = {x2,y2};  
        int slope;
        int dx, dy, incE, incNE, d, x, y;
        float m;
        float Rf, Gf, Bf;
        float R,G,B,A;
        
        int dist;
        
        if(v1.x == v2.x){
        	m = -1;
        }else{
			m = (float(v2.y)-float(v1.y))/(float(v2.x) - float(v1.x)); // calculo do coeficiente angular
		}

        dx = v2.x - v1.x;
        
        dy = v2.y - v1.y;


       	if(-0.5 < m < 0 || m > 1 || m < -2 || m < -1 || dx == 0){
       		        if (v1.y > v2.y){
			            DrawLine(x2,y2,x1,y1); // inverte recursivamente
			             return;
			        }   

	        if (dx < 0){            
	            slope = -1;
	            dx = -dx;
	        }
	        else{            
	           slope = 1;
	        }

	        incE = 2 * dx;
	        incNE = 2 * dx - 2 * dy;
	        d = 2 * dx - dy;
	        VERTICES tempV;

	        tempV.x = v1.x;

	        Rf = (float(p1.R) - float(p.R))/(float(dy)); // calculo do incremento das cores
	    	Gf = (float(p1.G) - float(p.G))/(float(dy));
	    	Bf = (float(p1.B) - float(p.B))/(float(dy));

	        
	        COR tempP = {p.R, p.G, p.B, p.A};

	    	R = p.R;
	    	G = p.G;
	    	B = p.B;
	    	A = p.A;

	        for (tempV.y = v1.y; tempV.y <= v2.y; tempV.y++){
	        	R += Rf;		// incrementa aos componentes
	        	G += Gf;
	        	B += Bf;
	        	tempP.R = R;
	        	tempP.G = G;
	        	tempP.B = B;

	            PutPixel(tempV, tempP);

	            if (d <= 0){
	              d += incE;
	            }
	            else{
	              d += incNE;
	              tempV.x += slope;
	            }
	        }
        }else{
       		        if (v1.x > v2.x){
			            DrawLine(x2,y2,x1,y1); // inverte recursivamente
			             return;
			        } 

	        if (dy < 0){            
	            slope = -1;
	            dy = -dy;
	        }
	        else{            
	           slope = 1;
	        }
	        // Constante de Bresenham
	        incE = 2 * dy;
	        incNE = 2 * dy - 2 * dx;
	        d = 2 * dy - dx;
	        VERTICES tempV;
	        tempV.y = v1.y;

	        COR tempP = {p.R, p.G, p.B, p.A};

	       
	        Rf = (float(p1.R) - float(p.R))/(float(dx)); // calculo do incremento das cores
	    	Gf = (float(p1.G) - float(p.G))/(float(dx));
	    	Bf = (float(p1.B) - float(p.B))/(float(dx));


			R = p.R;
	    	G = p.G;
	    	B = p.B;
	    	A = p.A;


	        for (tempV.x = v1.x; tempV.x <= v2.x; tempV.x++){
	        	R += Rf;			// incrementa aos componentes
	        	G += Gf;
	        	B += Bf;
	        	tempP.R = R;
	        	tempP.G = G;
	        	tempP.B = B;

	            PutPixel(tempV, tempP);

	            if (d <= 0){
	              d += incE;
	            }
	            else{
	              d += incNE;
	              tempV.y += slope;
	            }
	        }
	    }
	  }



//Draw Triangle
void drawTriangle(Pixel p1, Pixel p2, Pixel p3)
{
    DrawLine(p1.pos_x, p1.pos_y, p2.pos_x, p2.pos_y);
    DrawLine(p2.pos_x, p2.pos_y, p3.pos_x, p3.pos_y);
    DrawLine(p3.pos_x, p3.pos_y, p1.pos_x, p1.pos_y);
}

#endif // _MYGL_H_

