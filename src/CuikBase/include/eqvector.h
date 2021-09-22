#ifndef EQVECTORH
#define EQVECTORH

#include "interval.h"
#include "equation.h"
#include "geom.h"  

#include <stdio.h>

/** 
    \file eqvector.h

    \brief Definition of the TEqVEctor type and the associated functions.

    Interface of the module to manage symbolic vectors in R^3.

    \sa eqvector.c, TEqVector.
*/

/**
   \brief An array with three equations.

   An array with three equations.
*/
typedef Tequation TEqVector[3];

/**
   \brief Initializes a vector of equations.

   Initializes a 3-d vector of equations.

   \param ev The equation vector to initilize.
*/
void InitEqVector(TEqVector *ev);

/**
   \brief Copies a vector of equations.

   Initializes a vector of equations from another vector.

   \param ev_dst The vector to initialize.
   \param ev_src The vector from where to copy.
*/ 
void CopyEqVector(TEqVector *ev_dst,TEqVector *ev_src);

/**
   \brief Initializes a vector of equations from a constant vector.

   Initializes a vector of equations from a constant vector.

   \param v The constant vector.
   \param ev The equation vector to initialize.
*/
void EqVectorFromVector(double *v,TEqVector *ev);

/**
   \brief Gets an alement from a equation vector.

   Gets an equation from a equation vector.

   \param i The index of the element to get (0, 1, or 2).
   \param ev The equation vector.
*/
Tequation *GetEqVectorElement(unsigned int i,TEqVector *ev);

/**
   \brief Scales a equation vector with a constant.

   Multiplies all the equations in an equation vector by a constant.

   \param ct The constant scale factor.
   \param ev The equation vector to scale.
*/
void ScaleEqVector(double ct,TEqVector *ev);

/**
   \brief Scales an equation vector by a variable.

   Multiplies all the equations in an equation vector by a variable.

   \param v The identifier of the variable.
   \param ev The equation vector to scale.
*/   
void VarScaleEqVector(unsigned int v,TEqVector *ev);

/**
   \brief Accumulates two vectors of equations.

   Adds two vectors of equations where vector to accumulate is
   scaled by a constant factor.
   
   \param ev The equation vector to add.
   \param ct The scale factor.
   \param evOut The equation vector where to accumulate. 
*/
void AccumulateEqVectors(TEqVector *ev,double ct,TEqVector *evOut);

/**
   \brief Accumulates two vectors of equations.

   Adds two vectors of equations where vector to accumulate is
   scaled by a variable factor.
   
   \param ev The equation vector to add.
   \param v The variable scale factor.
   \param evOut The equation vector where to accumulate. 
*/
void VarAccumulateEqVectors(TEqVector *ev,unsigned int v,TEqVector *evOut);

/**
   \brief Accumulates a constant vector to a equation vector.

   Accumulates a constant vector scaled by a variable to a equation vector.
   
   \param c The constant vector to add.
   \param v The varible to scale.
   \param evOut The equation vector where to accumulate the scaled constant
                vector.
*/
void VarAccumulateVector2EqVector(double *c,unsigned int v,TEqVector *evOut);

/**
   \brief Accumulates a constant vector to a equation vector.

   Accumulates a constant vector scaled by a couple of variables 
   to a equation vector.
   
   \param c The constant vector to add.
   \param v1 The first variable to scale.
   \param v2 The second variable to scale.
   \param evOut The equation vector where to accumulate the scaled constant
                vector.
*/
void Var2AccumulateVector2EqVector(double *c,unsigned int v1,
				   unsigned int v2,TEqVector *evOut);
/**
   \brief Accumulates a constant vector to an equation vector.

    Accumulates a constant vector to an equation vector.
    
    \param v The constant vector.
    \param ev The output equation vector.
*/
void AccumulateVector2EqVector(double *v,TEqVector *ev);

/**
   \brief Cross product of two equation vectors.

   Generats an equation vector as the cross product of two equation vectors.

   \param ev1 The first vector to operate.
   \param ev2 The second vector to operate.
   \param evOut The result.
*/
void CrossProductEqVectors(TEqVector *ev1,TEqVector *ev2,TEqVector *evOut);

/**
   \brief Cross product of a constant vector and an equation vector.

   Generats an equation vector as the cross product a constant vector
   and an equation vector.

   Note that v x ev = -ev x v. Thus, this can not be directly used
   to comptue ev x v.

   \param v The constant vector to operate.
   \param ev The equation vector to operate.
   \param evOut The result.
*/
void CrossProductVectorEqVector(double *v,TEqVector *ev,TEqVector *evOut);

/**
   \brief Dot product of two equation vectors.

   Generats an equation as the dot product of two equation vectors.

   \param ev1 The first vector to operate.
   \param ev2 The second vector to operate.
   \param eqOut The resulting equation.
*/
void DotProductEqVectors(TEqVector *ev1,TEqVector *ev2,Tequation *eqOut);

/**
   \brief Dot product of a constant vector and an equation vector.

   Generats an equation as the dot product of a constant vector and an
   equation vector.

   \param v The constant vector to operate.
   \param ev The equation vector to operate.
   \param eqOut The resulting equation.
*/
void DotProductVectorEqVector(double *v,TEqVector *ev,Tequation *eqOut);

/**
   \brief Evaluates a vector of equations.

   Evaluates a vector of equations on a given point.

   \param v The array with the values for the variables.
   \param o The output constant vector. Space for the output must be
            allocated externally.
   \param ev The equation vector to evaluate.
*/
void EvaluateEqVector(double *v,double *o,TEqVector *ev);

/**
   \brief Evaluates a vector of equations on intervals.

   Evaluates a vector of equations on a given interval range.

   \param v The array with the intervals for the variables.
   \param o The output interval vector. Space for the output must be
            allocated externally.
   \param ev The equation vector to evaluate.
*/
void EvaluateEqVectorInt(Tinterval *v,Tinterval *o,TEqVector *ev);

/**
   \brief Deletes an equation vector.

   Deallocates the memory used by an equation vector.

   \param ev The equation vector to release.
*/
void DeleteEqVector(TEqVector *ev);

#endif
