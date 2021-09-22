#include "color.h"
#include "error.h" 

#include <math.h>

/** 
    \file color.c

    \brief Implementation of the functions operating on Tcolor.

    Implementation of the functions working on colors as red/green/blue components.

    \sa Tcolor, color.h.
*/

void NewColor(double r,double g,double b,Tcolor *c)
{
  c->r=r;
  c->g=g;
  c->b=b;
}

void NewColorWithID(unsigned int id,Tcolor *c)
{
  switch(id)
    {
    case RED:
      NewColor(1,0,0,c);
      break;
    case GREEN:
      NewColor(0,1,0,c);
      break;
    case BLUE:
      NewColor(0,0,1,c);
      break;
    case BLACK:
      NewColor(0,0,0,c);
      break;
    case GREY:
      NewColor(0.7,0.7,0.7,c);
      break;
    case WHITE:
      NewColor(1,1,1,c);
      break;
    case YELLOW:
      NewColor(1,1,0,c);
      break;
    case PURPLE:
      NewColor(1,0,1,c);
      break;
    case CYAN:
      NewColor(0,1,1,c);
      break;
    default:
      Error("Undefined color in NewColorWithID");
    }
}

void CopyColor(Tcolor *c_dst,Tcolor *c_src)
{
  c_dst->r=c_src->r;
  c_dst->g=c_src->g;
  c_dst->b=c_src->b;
}

boolean NullColor(Tcolor *c)
{
  return((c->r<0)||(c->g<0)||(c->b<0));
}

boolean SameColor(Tcolor *c1,Tcolor *c2)
{
  return((fabs(c1->r-c2->r)<1e-3)&&
	 (fabs(c1->g-c2->g)<1e-3)&&
	 (fabs(c1->b-c2->b)<1e-3));
}

void Add2Color(double s,Tcolor *c)
{
  c->r+=s;
  c->g+=s;
  c->b+=s;
}

void ScaleColor(double s,Tcolor *c)
{
  c->r*=s;
  c->g*=s;
  c->b*=s;
}

void AccumulateColor(Tcolor *c1,Tcolor *c)
{
  c->r+=c1->r;
  c->g+=c1->g;
  c->b+=c1->b;
}

void CostColor(double cost,double minCost,Tcolor *c)
{
  if (cost<minCost)
    {
      /* Black */
      c->r=0;
      c->g=0;
      c->b=0;
    }
  else
    {
      /* Gradient for the rest (0=green, 1=red) */
      c->r=cost;
      c->g=1.0-cost;
      c->b=0;
    }
}

void SetRed(double r,Tcolor *c)
{
  c->r=r;
}

void SetGreen(double g,Tcolor *c)
{
  c->g=g;
}

void SetBlue(double b,Tcolor *c)
{
  c->b=b;
}

double GetRed(Tcolor *c)
{
  return(c->r);
}

double GetGreen(Tcolor *c)
{
  return(c->g);
}

double GetBlue(Tcolor *c)
{
  return(c->b);
}

void PrintColor(FILE *f,Tcolor *c)
{
  fprintf(f,"%f %f %f",c->r,c->g,c->b);
}

void DeleteColor(Tcolor *c)
{
}
