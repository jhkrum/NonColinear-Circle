/****************************************************************

 <br>
 <br> Subject:            Calculation of a Circle Using NonCollinear Points
 <br> Project:            Challenge001
 <br> Author:             Justin H. Krum
 <br> Creation Date:      October 6, 2017
 <br> Last Modification:  October 6, 2017

 ****************************************************************/

/****************************************************************
 VAR NAME           TYPE        PURPOSE

 p1                 float[]     To store both x1 and y1 within indexes 0 and 1, respectively -- AKA point A
 p2                 float[]     To store both x2 and y2 within indexes 0 and 1, respectively -- AKA point B
 p3                 float[]     To store both x3 and y3 within indexes 0 and 1, respectively -- AKA point C
 pCircle            float[]     To store both xCircle and yCircle within indexes 0 and 1, respectively
 midpointAB         float[]     To store the x and y value of the midpoint between p1 and p2
 midpointBC         float[]     To store the x and y value of the midpoint between p2 and p3
 slopeAB            float       To store the value of slope between p1 and p2
 slopeBC            float       To store the value of slope between p2 and p3
 equationAB         float[]     To setup for standard form of an equation for the perpendicular bisector to AB
 equationBC         float[]     To setup for standard form of an equation for the perpendicular bisector to BC
 a1,a2,b1,b2,c1,c2  float       To apply equationAB and equationBC to Cramer's Rule to solve the system of equations
 deltaX             float       To calculate slopeAB
 deltaY             float       To calculate slopeBC
 distance           float       To calculate radius
 radius             float       To calculate the equation of the circle




 FUNCTION NAME      ARGUMENTS               RETURN TYPE     PURPOSE
 getSlope           float[], float[]        float           To calculate slope of a line
 getIntersection    float[], float[], int   float           To apply Cramer's Rule to solve for a systems of linear equations
 getDistance        float[], float[]        float           To calculate the radius of a circle
 getMidpoint        float[], float[]. int   float           To calculate the midpoint between to points
 getCoefA           float, float[]          float           To return the standard form of a linear equation coefficient A
 getCoefB           float, float[]          float           To return the standard form of a linear equation coefficient B
 getCoefC           float, float[]          float           To return the standard form of a linear equation coefficient C
 main                                       int             To execute the program

 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0


float getSlope(float p1[], float p2[]){

    float deltaX = p2[0] - p1[0];   //Calculates change in X values
    float deltaY = p2[1] - p1[0];   //Calculates change in Y values

    return deltaY/deltaX;
}

float getIntersection(float equation1[], float equation2[], int boolean){

    float solution, a1, a2, b1, b2, c1, c2;
    a1 = equation1[0], b1 = equation1[1], c1 = equation1[2];    //Sets up a1, b1, c1
    a2 = equation2[0], b1 = equation2[1], c2 = equation2[2];    //Sets up a2, b2, c2

    /*******************************************************************************************
    Must follow standard form of a linear equation Ax + By = C to apply Cramer's Rule

    a1*x + b1*y = c1
    a2*x + b2*y = c2
    *******************************************************************************************/

   if(boolean == true) solution = (c1 * b2 - b1 * c2) / (a1 * b2 - b1 * a2);                //Returns solution X value
   else if(boolean == false) solution = (a1 * c2 - c1 * a2) / (a1 * b2 - b1 * a2);          //Returns solution Y value

   return solution;
}

float getDistance(float p1[], float p2[]){

    float distance = sqrt( pow((p2[0] - p1[0]), 2) + pow((p2[1] - p1[1]), 2));              //Uses distance formula to calculate dist

    return distance;
}

float getMidpoint(float p1[], float p2[], int boolean){

    if(boolean==true) return ((p2[0] + p1[0]) / 2);         //Return X value of midpoint
    else if(boolean==false) return ((p2[1] + p1[1]) / 2);   //Return Y value of midpoint

}

float getCoefA(float slope, float pointVal[]){
    return -1*slope;                                                //A coefficient will always equal negative perpendicular slope
}

float getCoefB(float slope, float pointVal[]){
    return 1;                                                       //B coefficient in standard form will always solve to 1
}

float getCoefC(float slope, float pointVal[]){
    float coefC = ((-1 * slope) * pointVal[0]) + pointVal[1];       //Solves point-slope to C value in Ax + By = C
    return coefC;
}

int main()
{
    float p1[2], p2[2], p3[2];              //Points A, B, and C respectively

    p1[0] = 50.0, p1[1] = 70.0,
    p2[0] = -30.0, p2[1] = 10.0,
    p3[0] = 40.0, p3[1] = -40.0;      //Index 0 holds X, Index 1 holds Y

    printf("Point 1\tx = %.2f\ty=%.2f", p1[0], p1[1]);
    printf("\nPoint 2\tx = %.2f\ty=%.2f", p2[0], p2[1]);
    printf("\nPoint 3\tx = %.2f\ty=%.2f", p3[0], p3[1]);


    printf("\n\nSlope p1-p2 = %.2f", getSlope(p1, p2));
    printf("\nSlope p2-p3 = %.2f", getSlope(p2, p3));

    float slopeAB = getSlope(p1, p2);       //Sets slopes of AB and BC
    float slopeBC = getSlope(p2, p3);

    slopeAB = -1 * 1/slopeAB,               /* Sets slopeAB and slopeBC to perpendicular slope */
    slopeBC = -1 * 1/slopeBC;

    float midpointAB[2], midpointBC[2];     //Holds midpoints between AB and BC
    midpointAB[0] = getMidpoint(p1, p2, true), midpointAB[1] = getMidpoint(p1, p2, false);
    midpointBC[0] = getMidpoint(p1, p2, true), midpointBC[1] = getMidpoint(p1, p2, false);

    float equationAB[3], equationBC[3];
    equationAB[0] = getCoefA(slopeAB, midpointAB),
    equationAB[1] = getCoefB(slopeAB, midpointAB),
    equationAB[2] = getCoefC(slopeAB, midpointAB);  //Sets up the equation of the perpendicular bisector AB


    equationBC[0] = getCoefA(slopeBC, midpointBC),
    equationBC[1] = getCoefB(slopeBC, midpointBC),
    equationBC[2] = getCoefC(slopeBC, midpointBC);  //Sets up the equation of the perpendicular bisector BC

    float pCircle[2];
    pCircle[0] = getIntersection(equationAB, equationBC, true),
    pCircle[1] = getIntersection(equationAB, equationBC, false);    //Finds X and Y value for Circle Center

    printf("\n\nCircle X = %.3f", pCircle[0]);
    printf("\nCircle Y = %.3f", pCircle[1]);

    float radius = getDistance(p1, pCircle);    //Calculates radius by equidistant property of circumcenters

    printf("\nRadius = %.3f", radius);
    printf("\n(x-%.3f)^2 + (y-%.3f)^2 = %.3f\n\n", pCircle[0], pCircle[1], pow(radius, 2));




    return 0;
}
