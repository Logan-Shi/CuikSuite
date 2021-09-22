#include "link.h"
#include "polyhedron.h"
#include "varnames.h"
#include "basic_algebra.h"
#include "geom.h"

#include <math.h>
#include <string.h>

/** \file link.c

    \brief Implementaton of the function operating on Tlink.
    
    Implementaton of the function operating on Tlink.

    \sa Tlink, link.h.
*/

/** 
    \brief Maximum number of variables used to represent a link rotation.

    Maximum number of variables used to represent a link rotation. Used to allocate
    space for the \ref GetRotVarID functions.
*/
#define MAX_ROT_VARS 14

/** 
    \brief Identifies trivial inertia matrices.
    
    Identifies trivial (i.e., null) inertia matrices.

    \param m The inertia matrix to check.

    \return TRUE if the matrix is the identity.
*/
boolean TrivialInertiaMatrix(double **m);

/** 
    \brief Adjust the range of the force-related parameters of the link.

    Adjust the range of the stiffness, length, rest, and maxForce variables
    associated with the link. These variables are related by the
    equations force=stiffness*(length-rest) which can be used to
    crop the ranges given by the user.

    \param l The link to adjust.
*/
void AdjustLinkForceParameters(Tlink *l);

/** 
   \brief Obtains information about the variables used to codify the rotation of the link.

   Defines the \e csvID, \e vID, and \e nvID fields for
   the link. If the values are already cached nothing is done.
   If the cuiksystem is diferent from that for which the identified
   where computed before they are re-computed.

   Note that in general there are not translation variables associated with a link
   but that translations are computed accumulating displacements on links from
   the ground link to the current one.
   In global cuiksystems, though, those accumulations are identified with given
   variables and they can be directly retrieved (see \ref SetTransVars).

   \param r The type of representation to use (i.e., the \ref CT_REPRESENTATION
            parameter). 
   \param cs The cuiksystem from where to get the variable identifiers.
   \param vID Buffer where to store the variable identifiers. 
   \param l The link.
*/
void GetRotVarID(unsigned int r,TCuikSystem *cs,unsigned int *vID,Tlink *l);

/** 
   \brief Obtains information about the variables used to codify the rotation of the link.

   This function is specific for LINK_AxisX links. For this links only one axis
   is represented.

   It is also used for LINK_DeforX and for LINK_PrismaticX.

   Don't use this function directly. Instead call always \ref GetRotVarID.

   \param cs The cuiksystem from where to get the variable identifiers.
   \param l The link.
*/
void GetRotVarIDAxisX(TCuikSystem *cs,Tlink *l);

/** 
   \brief Obtains information about the variables used to codify the rotation of the link.
   
   Version of \ref GetRotVarID for \ref REP_FLINKS representations.

   Don't use this function directly. Instead call always \ref GetRotVarID.
   
   \param cs The cuiksystem from where to get the variable identifiers.
   \param l The link.
*/
void GetRotVarIDFLinks(TCuikSystem *cs,Tlink *l);

/** 
   \brief Obtains information about the variables used to codify the rotation of the link.
   
   Version of \ref GetRotVarID for \ref REP_LINKS representations.

   Don't use this function directly. Instead call always \ref GetRotVarID.
   
   \param cs The cuiksystem from where to get the variable identifiers.
   \param l The link.
*/
void GetRotVarIDLinks(TCuikSystem *cs,Tlink *l);

/** 
   \brief Obtains information about the variables used to codify the rotation of the link.
   
   Version of \ref GetRotVarID for \ref REP_QLINKS representations.

   Don't use this function directly. Instead call always \ref GetRotVarID.
   
   \param cs The cuiksystem from where to get the variable identifiers.
   \param l The link.
*/
void GetRotVarIDQLinks(TCuikSystem *cs,Tlink *l);

/** 
    \brief Adds the link configuration variables to the system.

    Adds the configuration variables to the system of equations.
    These parameters will be later used in the equations (i.e.,
    in the force equilibrium equations for tensegrities).

    \param p The set of parameters.
    \param cs The cuiksystem where to add the variables and equations.	
    \param l The link from where to generate the variables and equation.
*/
void GenerateLinkConf(Tparameters *p,TCuikSystem *cs,Tlink *l);

/** 
    \brief Version of \ref GenerateLinkRot for axis X links.

    Version of \ref GenerateLinkRot for links where only the X axis is represented.

    \param p A set of parameters. They include, for instance the dummification
             level.
    \param lID The identifier of the link in the mechanism. Used to generate
               unique names for the new variables.
    \param cs The cuiksystem where to add the variables and equations.	
    \param l The link from where to generate the variables and equation.
*/
void GenerateLinkRotAxisX(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l);

/** 
    \brief Version of \ref GenerateLinkRot for partial matrix representation.

    Version of \ref GenerateLinkRot for partial matrix representation.

    \param p A set of parameters. They include, for instance the dummification
             level.
    \param lID The identifier of the link in the mechanism. Used to generate
               unique names for the new variables.
    \param cs The cuiksystem where to add the variables and equations.	
    \param l The link from where to generate the variables and equation.
*/
void GenerateLinkRotLinks(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l);

/** 
    \brief Version of \ref GenerateLinkRot for full matrix representation.

    Version of \ref GenerateLinkRot for full matrix representation.

    \param p A set of parameters. They include, for instance the dummification
             level.
    \param lID The identifier of the link in the mechanism. Used to generate
               unique names for the new variables.
    \param cs The cuiksystem where to add the variables and equations.	
    \param l The link from where to generate the variables and equation.
*/
void GenerateLinkRotFLinks(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l);

/** 
    \brief Version of \ref GenerateLinkRot for quaternions representation.

    Version of \ref GenerateLinkRot for quaternion representation.

    \param p A set of parameters. They include, for instance the dummification
             level.
    \param lID The identifier of the link in the mechanism. Used to generate
               unique names for the new variables.
    \param cs The cuiksystem where to add the variables and equations.	
    \param l The link from where to generate the variables and equation.
*/
void GenerateLinkRotQLinks(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l);

/** 
    \brief  Version of \ref ApplyLinkRot for axis X links.

    Version of \ref ApplyLinkRot for links for which only the axis X
    is relevant.

    \param sf Constant scale factor to apply to the input vector.
    \param sv Variable scale factor given as the identifier of the
              range in the given \e box whose center have to be used as scale factor.
	      If no variable scale factor is to be used this parameter should be
	      NO_UINT.
    \param p The 3D vector in the link reference frame that we want to transform to
             the global one and to add to \e trans.
    \param eq Set of 3 equations where to add the 3 expressions resulting from this
              function (one for the X component of the vector in the globla frame,
	      another for the Y expression and, finally the expression for the Z
	      component). 
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers. The numerical identifier
	      of the variable is used to generate a unique name for it.
    \param groundLink TRUE if the given link is the ground link.
    \param l The link to use to rotate the given input vector \e p.
*/
void ApplyLinkRotAxisX(double sf,unsigned int sv,double *p,Tequation *eq,
		       TCuikSystem *cs,boolean groundLink,Tlink *l);

/** 
    \brief  Version of \ref ApplyLinkRot for deform X links.

    Version of \ref ApplyLinkRot for links for which only the axis X
    is relevant and where there is an elongation along this axis.

    \param pr The set of parameters.
    \param sf Constant scale factor to apply to the input vector.
    \param sv Variable scale factor given as the identifier of the
              range in the given \e box whose center have to be used as scale factor.
	      If no variable scale factor is to be used this parameter should be
	      NO_UINT.
    \param p The 3D vector in the link reference frame that we want to transform to
             the global one and to add to \e trans.
    \param eq Set of 3 equations where to add the 3 expressions resulting from this
              function (one for the X component of the vector in the globla frame,
	      another for the Y expression and, finally the expression for the Z
	      component). 
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers. The numerical identifier
	      of the variable is used to generate a unique name for it.
    \param groundLink TRUE if the given link is the ground link.
    \param l The link to use to rotate the given input vector \e p.
*/
void ApplyLinkRotDeformX(Tparameters *pr,double sf,unsigned int sv,double *p,Tequation *eq,
			 TCuikSystem *cs,boolean groundLink,Tlink *l);
/** 
    \brief  Version of \ref ApplyLinkRot  for partial matrix representation.

    Version of \ref ApplyLinkRot  for partial matrix representation.

    \param sf Constant scale factor to apply to the input vector.
    \param sv Variable scale factor given as the identifier of the
              range in the given \e box whose center have to be used as scale factor.
	      If no variable scale factor is to be used this parameter should be
	      NO_UINT.
    \param p The 3D vector in the link reference frame that we want to transform to
             the global one and to add to \e trans.
    \param eq Set of 3 equations where to add the 3 expressions resulting from this
              function (one for the X component of the vector in the globla frame,
	      another for the Y expression and, finally the expression for the Z
	      component). 
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers. The numerical identifier
	      of the variable is used to generate a unique name for it.
    \param groundLink TRUE if the given link is the ground link.
    \param l The link to use to rotate the given input vector \e p.
*/
void ApplyLinkRotLinks(double sf,unsigned int sv,double *p,Tequation *eq,
		       TCuikSystem *cs,boolean groundLink,Tlink *l);

/** 
    \brief  Version of \ref ApplyLinkRot for full matrix representation.

    Version of \ref ApplyLinkRot for full matrix representation.

    \param sf Constant scale factor to apply to the input vector.
    \param sv Variable scale factor given as the identifier of the
              range in the given \e box whose center have to be used as scale factor.
	      If no variable scale factor is to be used this parameter should be
	      NO_UINT.
    \param p The 3D vector in the link reference frame that we want to transform to
             the global one and to add to \e trans.
    \param eq Set of 3 equations where to add the 3 expressions resulting from this
              function (one for the X component of the vector in the globla frame,
	      another for the Y expression and, finally the expression for the Z
	      component). 
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers. The numerical identifier
	      of the variable is used to generate a unique name for it.
    \param groundLink TRUE if the given link is the ground link.
    \param l The link to use to rotate the given input vector \e p.
*/
void ApplyLinkRotFLinks(double sf,unsigned int sv,double *p,Tequation *eq,
			TCuikSystem *cs,boolean groundLink,Tlink *l);

/** 
    \brief  Version of \ref ApplyLinkRot for quaternion representation.

    Version of \ref ApplyLinkRot for quaternion representation.

    \param sf Constant scale factor to apply to the input vector.
    \param sv Variable scale factor given as the identifier of the
              range in the given \e box whose center have to be used as scale factor.
	      If no variable scale factor is to be used this parameter should be
	      NO_UINT.
    \param p The 3D vector in the link reference frame that we want to transform to
             the global one and to add to \e trans.
    \param eq Set of 3 equations where to add the 3 expressions resulting from this
              function (one for the X component of the vector in the globla frame,
	      another for the Y expression and, finally the expression for the Z
	      component). 
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers. The numerical identifier
	      of the variable is used to generate a unique name for it.
    \param groundLink TRUE if the given link is the ground link.
    \param l The link to use to rotate the given input vector \e p.
*/
void ApplyLinkRotQLinks(double sf,unsigned int sv,double *p,Tequation *eq,
			TCuikSystem *cs,boolean groundLink,Tlink *l);

/** 
    \brief Computes the force-related dummy variables from the system ones.

    Computes the force-related dummy variables from the system ones.
    Actually nothing is computed since all force variables are system variables.

    This is an auxiliary function of \ref RegenerateLinkSolution.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point with the values for the system variables.
               At the end of the function, this vector also has values for
	       the link-related dummy variables.
    \param l The link.
*/
void RegenerateLinkSolutionConf(unsigned int r,TCuikSystem *cs,double *sol,Tlink *l);

/** 
    \brief  Version of \ref RegenerateLinkSolution  for partial matrix representation.

    Version of \ref RegenerateLinkSolution for partial matrix representation.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point with the values for the system variables.
               At the end of the function, this vector also has values for
	       the link-related dummy variables.
    \param groundLink TRUE if the given link is the ground link. The rotation matrix
                      for the ground link is fixed (the identity) and, its rotation
		      matrix generates no variables (nor system nor dummy).
    \param l The link.
*/
void RegenerateLinkSolutionLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,Tlink *l);

/** 
    \brief  Version of \ref RegenerateLinkSolution  for quaternion representation.

    Version of \ref RegenerateLinkSolution for quaternion representation.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point with the values for the system variables.
               At the end of the function, this vector also has values for
	       the link-related dummy variables.
    \param groundLink TRUE if the given link is the ground link. The rotation matrix
                      for the ground link is fixed (the identity) and, its rotation
		      matrix generates no variables (nor system nor dummy).
    \param l The link.
*/
void RegenerateLinkSolutionQLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,Tlink *l);

/** 
    \brief Computes the force-related dummy variables from the system ones.
    
    Computes the force-related dummy variables from the system ones.
    Actually nothing is computed since all force variables are system variables.


    This is an auxiliary function of \ref RegenerateLinkBox and is the same
    as \ref RegenerateLinkSolutionConf but working on a box instead than
    on a point.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param b The solution box with the values for the system variables.
             At the end of the function, this box also has values for
	     the link-related dummy variables.
    \param l The link.
*/
void RegenerateLinkBoxConf(unsigned int r,TCuikSystem *cs,Tbox *b,Tlink *l);

/** 
    \brief  Version of \ref RegenerateLinkBox for partial matrix representation.

    Version of \ref RegenerateLinkBox for partial matrix representation.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param b The solution box with the values for the system variables.
             At the end of the function, this box also has values for
	     the link-related dummy variables.
    \param groundLink TRUE if the given link is the ground link. The rotation matrix
                      for the ground link is fixed (the identity) and, its rotation
		      matrix generates no variables (nor system nor dummy).
    \param l The link.
*/
void RegenerateLinkBoxLinks(unsigned int r,TCuikSystem *cs,Tbox *b,boolean groundLink,Tlink *l);

/** 
    \brief  Version of \ref RegenerateLinkBox  for quaternion representation.

    Version of \ref RegenerateLinkBox for quaternion representation.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param b The solution box with the values for the system variables.
             At the end of the function, this box also has values for
	     the link-related dummy variables.
    \param groundLink TRUE if the given link is the ground link. The rotation matrix
                      for the ground link is fixed (the identity) and, its rotation
		      matrix generates no variables (nor system nor dummy).
    \param l The link.
*/
void RegenerateLinkBoxQLinks(unsigned int r,TCuikSystem *cs,Tbox *b,boolean groundLink,Tlink *l);

/** 
    \brief  Version of \ref GetTransform2Link for axis X links.

    Version of \ref GetTransform2Link for links where only the X axis is
    relevant.

    Also used for LINK_DeformX links.
 
    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defined. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point including values for all variables (i.e., already regenerated
               using \ref RegenerateLinkSolution before calling this function). 
    \param groundLink TRUE if the given link is the ground link.
    \param trans 3d vector with the translation from the ground link to this link.
                 The variables for these translations are removed from the cuiksystems
		 and computed from rotations and fixed vectors. Consequently they can
		 only be computed at the level where we have cuiksystems and links
		 (i.e. in \ref world.h).
    \param t The returned homogeneous transform.
    \param l The link whose reference frame we want to retrive.
    
*/
void GetTransform2LinkAxisX(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,
			    double *trans,THTransform *t,Tlink *l);

/** 
    \brief  Version of \ref GetTransform2Link  for partial matrix representation.

    Version of \ref GetTransform2Link for full partial representation.
 
    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defined. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point including values for all variables (i.e., already regenerated
               using \ref RegenerateLinkSolution before calling this function). 
    \param groundLink TRUE if the given link is the ground link.
    \param trans 3d vector with the translation from the ground link to this link.
                 The variables for these translations are removed from the cuiksystems
		 and computed from rotations and fixed vectors. Consequently they can
		 only be computed at the level where we have cuiksystems and links
		 (i.e. in \ref world.h).
    \param t The returned homogeneous transform.
    \param l The link whose reference frame we want to retrive.
    
*/
void GetTransform2LinkLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,
			    double *trans,THTransform *t,Tlink *l);

/** 
    \brief  Version of \ref GetTransform2Link  for full matrix representation.

    Version of \ref GetTransform2Link for full matrix representation.
 
    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defined. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point including values for all variables (i.e., already regenerated
               using \ref RegenerateLinkSolution before calling this function). 
    \param groundLink TRUE if the given link is the ground link.
    \param trans 3d vector with the translation from the ground link to this link.
                 The variables for these translations are removed from the cuiksystems
		 and computed from rotations and fixed vectors. Consequently they can
		 only be computed at the level where we have cuiksystems and links
		 (i.e. in \ref world.h).
    \param t The returned homogeneous transform.
    \param l The link whose reference frame we want to retrive.
*/
void GetTransform2LinkFLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,
			     double *trans,THTransform *t,Tlink *l);

/** 
    \brief  Version of \ref GetTransform2Link  for quaternion representation.

    Version of \ref GetTransform2Link for quaternion representation.
 
    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param cs The cuik system on which the boxes are defined. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point including values for all variables (i.e., already regenerated
               using \ref RegenerateLinkSolution before calling this function). 
    \param groundLink TRUE if the given link is the ground link.
    \param trans 3d vector with the translation from the ground link to this link.
                 The variables for these translations are removed from the cuiksystems
		 and computed from rotations and fixed vectors. Consequently they can
		 only be computed at the level where we have cuiksystems and links
		 (i.e. in \ref world.h).
    \param t The returned homogeneous transform.
    \param l The link whose reference frame we want to retrive.
    
*/
void GetTransform2LinkQLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,
			     double *trans,THTransform *t,Tlink *l);

/** 
    \brief  Version of \ref GenerateLinkSolution for axis X links.

    Version of \ref GenerateLinkSolution for links where only the
    axis X is relevant.

    Also used for LINK_DeformX links.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param t The transform giving the link pose.
    \param cs The cuik system on which the variables are defined.
    \param sol The solution point where to store the generated values.
    \param groundLink TRUE for the ground link.
    \param l The link.
*/
void GenerateLinkSolutionAxisX(unsigned int r,THTransform *t,TCuikSystem *cs,
			       double *sol,boolean groundLink,Tlink *l);


/** 
    \brief  Version of \ref GenerateLinkSolution  for partial matrix representation.

    Version of \ref GenerateLinkSolution for partial matrix representation.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param t The transform giving the link pose.
    \param cs The cuik system on which the variables are defined.
    \param sol The solution point where to store the generated values.
    \param groundLink TRUE for the ground link.
    \param l The link.
*/
void GenerateLinkSolutionLinks(unsigned int r,THTransform *t,TCuikSystem *cs,
			       double *sol,boolean groundLink,Tlink *l);

/** 
    \brief  Version of \ref GenerateLinkSolution  for full matrix representation.

    Version of \ref GenerateLinkSolution for full matrix representation.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param t The transform giving the link pose.
    \param cs The cuik system on which the variables are defined.
    \param sol The solution point where to store the generated values.
    \param groundLink TRUE for the ground link.
    \param l The link.
*/
void GenerateLinkSolutionFLinks(unsigned int r,THTransform *t,TCuikSystem *cs,
				double *sol,boolean groundLink,Tlink *l);

/** 
    \brief  Version of \ref GenerateLinkSolution  for quaternion representation.

    Version of \ref GenerateLinkSolution for quaternion representation.

    \param r The type of representation used (REP_JOINTS, REP_LINKS...)
    \param t The transform giving the link pose.
    \param cs The cuik system on which the variables are defined.
    \param sol The solution point where to store the generated values.
    \param groundLink TRUE for the ground link.
    \param l The link.
*/
void GenerateLinkSolutionQLinks(unsigned int r,THTransform *t,TCuikSystem *cs,
				double *sol,boolean groundLink,Tlink *l);

/** 
    \brief Identifies the variables giving the translation of the link.

    Sets to TRUE the translations variables for the
    given link in the given array of variables.
    In general the tranlation variables are not in the cuiksystems since
    translations are computed accumulating displacements over links.
    The translation variables are only present in very particular 
    cuiksystems and for links that are at the end of a open sequence
    of links.

    \param vars The array of booleans to set.
    \param cs The cuiksystem where the link variables are included.
    \param l The link.
*/
void SetTransVars(boolean *vars,TCuikSystem *cs,Tlink *l);

/** 
    \brief Identifies the variables giving the rotation of the link.

    Sets to TRUE the rotation variables for the
    given link in the given array of variables.

    Note that the rotation variables depends on the 
    \ref CT_REPRESENTATION  setting.

    \param r The type of representation (REP_JOINTS, REP_LINKS,...)
    \param vars The array of booleans to set.
    \param cs The cuiksystem where the link variables are included.
    \param l The link.   
*/
void SetRotVars(unsigned int r,boolean *vars,TCuikSystem *cs,Tlink *l);

/**********************************************************************/


boolean EmptyLinkConf(TLinkConf *ld)
{
  return(!IsVariableLengthLink(ld->l)); 
}

double GetLinkConfExtension(TLinkConf *ld)
{
  if (EmptyLinkConf(ld))
    Error("Using GetLinkConfExtension on an empty link configuration");
  
  if (GetLinkType(ld->l)==LINK_PrismaticX)
    Error("GetLinkConfExtension is only defined on prismatic links");
  
  return(ld->p[0]);
}

void GetLinkConfTransform(unsigned int bID,THTransform *t,TLinkConf *ld)
{
  if (EmptyLinkConf(ld))
    HTransformIdentity(t);
  else
    {
      if (GetLinkType(ld->l)==LINK_DeformX)
	HTransformScaleX(ld->p[0],t);
      else
	{
	  /* Prismatic link: only the upper bodies are displaced */
	  if (bID>=(LinkNBodies(ld->l)/2))
	    HTransformTx(ld->p[0],t);
	  else
	    HTransformIdentity(t);
	}
    }
}

void DeleteLinkConf(TLinkConf *ld)
{
  if (ld->p!=NULL)
    free(ld->p);
}
/**********************************************************************/

boolean TrivialInertiaMatrix(double **m)
{
  return((fabs(m[0][0])<ZERO)&&(fabs(m[0][1])<ZERO)&&(fabs(m[0][2])<ZERO)&&
	                       (fabs(m[1][1])<ZERO)&&(fabs(m[1][2])<ZERO)&&
	                                             (fabs(m[2][2])<ZERO));
}
  
/**********************************************************************/


void InitLink(char *name,double mass,double **iMatrix,THTransform *iFrame,Tlink *l)
{
  unsigned int namel,i,j;

  namel=strlen(name);
  if (namel==0)
    l->name=NULL;
  else
    {
      NEW(l->name,namel+1,char);
      strcpy(l->name,name);
    }

  l->type=LINK_FullRot; /* by default we encode the full rotation of the links. */

  InitVector(sizeof(double *),CopyVoidPtr,DeleteVoidPtr,INIT_NUM_SHAPES,&(l->bodies));

  l->s=1;
  l->c=0;
  HTransformIdentity(&(l->R));
  HTransformIdentity(&(l->iR));
  
  l->allSpheres=TRUE;

  for(i=0;i<3;i++)
    l->axisID[i]=NO_UINT;

  /*sum of the maximum coordinate value for all bodies in the link*/
  l->maxCoord=0.0;

  l->csvID=NULL;
  l->nvID=0;
  l->vID=NULL;

  /* In general links do not have to be in force equilibrium */
  l->forceEquilibrium=FALSE;
  
  /* force and fixedDim is only used in tensegrity structures */
  l->extForce[0]=l->extForce[1]=l->extForce[2]=0.0;
  l->fixedDim[0]=l->fixedDim[1]=l->fixedDim[2]=INF;

  /* Force-related information. Only used for some AxisX of DeformX links */
  NewInterval(0,0,&(l->length));
  l->varLength=FALSE;

  l->stiffness=0.0;
  NewInterval(0,0,&(l->rest));
  NewInterval(0,0,&(l->force));
  l->forceModel=NO_FORCE;

  if (mass<0)
    Error("Negative mass in InitLink");
  
  l->mass=mass;

  NEW(l->iMatrix,3,double*);
  for(i=0;i<3;i++)
    {
      NEW(l->iMatrix[i],3,double); 
      for(j=i;j<3;j++)
	l->iMatrix[i][j]=(((mass==0)||(iMatrix==NULL))?0.0:iMatrix[i][j]);
    }
  l->iMatrix[1][0]=l->iMatrix[0][1];
  l->iMatrix[2][0]=l->iMatrix[0][2];
  l->iMatrix[2][1]=l->iMatrix[1][2];

  if ((mass==0)||(iFrame==NULL))
    HTransformIdentity(&(l->iFrame));
  else
    HTransformCopy(&(l->iFrame),iFrame);

  l->l1=NO_UINT;
  l->l2=NO_UINT;
  for(i=0;i<3;i++)
    {
      l->p1[i]=0.0;
      l->p2[i]=0.0;
    }
}

void InitNoRotLink(char *name,Tlink *l)
{
  /* Initialize as a normal link, even if some structures will not be
     actually used */
  InitLink(name,0.0,NULL,NULL,l);
  l->type=LINK_NoRot;
  l->forceEquilibrium=TRUE;
}

void AdjustLinkForceParameters(Tlink *l)
{
  if (l->forceModel==LINEAR_FORCE)
    {
      Tinterval r;
      boolean reduction;

      do {
	reduction=FALSE;
    
	/* f=k*(l-r) */
	IntervalSubstract(&(l->length),&(l->rest),&r);
	IntervalScale(&r,l->stiffness,&r);
	if (!Intersection(&(l->force),&r,&r))
	  Error("Wrong force range");
	else
	  {
	    if (IntervalSize(&(l->force))>IntervalSize(&r)+1e-6)
	      {
		CopyInterval(&(l->force),&r);
		reduction=TRUE;
	      }
	  }
	    
	/* l=f/k+r */
	if (fabs(l->stiffness)>ZERO)
	  {
	    IntervalScale(&(l->force),1.0/l->stiffness,&r);
	    IntervalAdd(&r,&(l->rest),&r);
	      
	    if (!Intersection(&(l->length),&r,&r))
	      Error("Wrong length range");
	    else
	      {
		if (IntervalSize(&(l->length))>IntervalSize(&r)+ZERO)
		  {
		    CopyInterval(&(l->length),&r);
		    reduction=TRUE;
		  }
	      }
	  }
	    
	/* r=l-f/k */
	if (fabs(l->stiffness)>ZERO)
	  {
	    IntervalScale(&(l->force),1.0/l->stiffness,&r);
	    IntervalSubstract(&(l->length),&r,&r);
	      
	    if (!Intersection(&(l->rest),&r,&r))
	      Error("Wrong rest range");
	    else
	      {
		if (IntervalSize(&(l->rest))>IntervalSize(&r)+ZERO)
		  {
		    CopyInterval(&(l->rest),&r);
		    reduction=TRUE;
		  }
	      }
	  }
      } while (reduction);
    }
}

void InitAxisXLink(char *name,unsigned int forceModel,
		   Tinterval *length,Tinterval *force,
		   double mass,double **iMatrix,THTransform *iFrame,Tlink *l)
{  
  /* Initialize as a normal link, even if some structures will not be
     actually used */
  InitLink(name,mass,iMatrix,iFrame,l);

  if (LowerLimit(length)<0)
    Error("Wrong length in InitAxisXLink");
  if (IntervalSize(length)>ZERO)
    Error("The length of AxisX links must be constant");
  
  /* need the length of the leg, at least to print the link */
  l->varLength=FALSE;
  CopyInterval(&(l->length),length); /* actually a point */

  /* force model, if any, is not lineal */
  l->stiffness=0.0;
  NewInterval(0.0,0.0,&(l->rest));
  
  l->forceModel=forceModel;
  switch(forceModel)
    {
    case NO_FORCE:
      if (!ZeroInterval(force))
	Error("Force must be zero for NO_FORCE links");
      NewInterval(0.0,0.0,&(l->force));
      break;
    case VAR_FORCE:
      CopyInterval(&(l->force),force);
      break;
    case LINEAR_FORCE:
      Error("InitAxisXLink can not have linear force model (the length is constant)");
      break;
    default:
      Error("Unknown force model in InitAxisXLink");
    }
  
  l->type=LINK_AxisX;
}

void InitDeformXLink(char *name,unsigned int forceModel,
		     Tinterval *length,double stiffness,
		     Tinterval *rest,Tinterval *force,
		     double mass,double **iMatrix,THTransform *iFrame,Tlink *l)
{  
  /* Initialize as a normal link, even if some structures will not be
     actually used */
  InitLink(name,mass,iMatrix,iFrame,l);
    
  if (LowerLimit(length)<0)
    Error("Wrong length in InitDeformXLink");
  
  /* set to variable length even if in some cases the length may be constant */
  l->varLength=TRUE;
  CopyInterval(&(l->length),length);

  l->forceModel=forceModel;
  switch(forceModel)
    {
    case NO_FORCE:
      if ((!ZeroInterval(force))||(fabs(stiffness)>ZERO)||(!ZeroInterval(rest)))
	Error("NO_FORCE links do not use force, stiffness nor rest length");
      
      NewInterval(0.0,0.0,&(l->force));
      l->stiffness=0.0;
      NewInterval(0.0,0.0,&(l->rest));
      break;
    case VAR_FORCE:
      if ((fabs(stiffness)>ZERO)||(!ZeroInterval(rest)))
	Error("VAR_FORCE links do not use stiffness nor rest length");
      
      CopyInterval(&(l->force),force);
      l->stiffness=0.0;
      NewInterval(0.0,0.0,&(l->rest));
      break;
    case LINEAR_FORCE:
      if (fabs(stiffness)<ZERO)
	Error("Wrong linear force model stiffness parameter in InitDeformXLink");
      
      if (LowerLimit(rest)<0)
	Error("Wrong rest in InitDeformXLink");
      if (LowerLimit(rest)>UpperLimit(length))
	Error("Wrong length/rest in InitDeformXLink");
      if (IntervalSize(length)<ZERO)
	Error("Force model can not be linear for constant length InitDeformXLink");
  
      CopyInterval(&(l->force),force);
      l->stiffness=stiffness;
      CopyInterval(&(l->rest),rest);

      AdjustLinkForceParameters(l);
      break;
    default:
      Error("Unknown force model in InitDeformXLink");
    }
        
  l->type=LINK_DeformX;
}

void InitPrismaticXLink(char *name,unsigned int forceModel,
			Tinterval *length,double stiffness,
			Tinterval *rest,Tinterval *force,
			double mass,double **iMatrix,THTransform *iFrame,Tlink *l)
{  
  /* If there is no deformation -> use AxisX link */
  if (IntervalSize(length)<ZERO)
    {
      if (forceModel==LINEAR_FORCE)
	Error("Can not define linear force modesl on constant link prismatic legs");
      if ((fabs(stiffness)>ZERO)||(!ZeroInterval(rest)))
	Error("Wrong force parameters when defining a prismatic link");
      
      InitAxisXLink(name,forceModel,length,force,mass,iMatrix,iFrame,l);
    }
  else
    {
      /* Initialize as a normal link, even if some structures will not be
	 actually used */
      InitLink(name,mass,iMatrix,iFrame,l);
      
      if (LowerLimit(length)<0)
	Error("Wrong length in InitPrismaticXLink");
      
      if (LowerLimit(length)<IntervalSize(length))
	Error("Wrong min-max length in InitPrismaticXLink");
      
      l->varLength=TRUE;
      CopyInterval(&(l->length),length);

      l->forceModel=forceModel;
      switch(forceModel)
	{
	case NO_FORCE:
	  if ((!ZeroInterval(force))||(fabs(stiffness)>ZERO)||(!ZeroInterval(rest)))
	    Error("NO_FORCE links do not use force, stiffness nor rest length");
	  
	  NewInterval(0.0,0.0,&(l->force));
	  l->stiffness=0.0;
	  NewInterval(0.0,0.0,&(l->rest));
	  break;
	case VAR_FORCE:
	  if ((fabs(stiffness)>ZERO)||(!ZeroInterval(rest)))
	    Error("VAR_FORCE links do not use stiffness nor rest length");
	  
	  CopyInterval(&(l->force),force);
	  l->stiffness=0.0;
	  NewInterval(0.0,0.0,&(l->rest));
	  break;
	case LINEAR_FORCE:
	  if (fabs(stiffness)<ZERO)
	    Error("Wrong linear force model stiffness parameter in InitPrismaticXLink");
	  
	  if (LowerLimit(rest)<0)
	    Error("Wrong rest in InitPrismaticXLink");
	  if (LowerLimit(rest)>UpperLimit(length))
	    Error("Wrong length/rest in InitPrismaticXLink");
  
	  CopyInterval(&(l->force),force);
	  l->stiffness=stiffness;
	  CopyInterval(&(l->rest),rest);

	  AdjustLinkForceParameters(l);
	  break;
	default:
	  Error("Unknown force model in InitPrismaticXLink");
	}
        
      l->type=LINK_PrismaticX;
    }
}

void InitConnectLink(char *name,unsigned int type,
		     unsigned int l1,unsigned int l2,double *p1,double *p2,
		     double r,Tcolor *c,unsigned int gr,unsigned int bs,
		     Tinterval *rest,double stiffness,
		     Tlink *l)
{
  unsigned int i;
  Tpolyhedron b;
  
  InitLink(name,0.0,NULL,NULL,l);

  l->type=LINK_Connect;
  l->l1=l1;
  l->l2=l2;

  for(i=0;i<3;i++)
    {
      l->p1[i]=p1[i];
      l->p2[i]=p2[i];
    }

  switch(type)
    {
    case C_CABLE:
      {
	double p1[3],p2[3];

	p1[0]=p1[1]=p1[2]=0.0;
	p2[0]=1.0;
	p2[1]=p2[2]=0.0;
	
	NewCylinder(r,p1,p2,c,gr,bs,&b);
	AddBody2Link(&b,l);
	DeletePolyhedron(&b);
      }
      break;
    case C_SPRING:
      {
	CopyInterval(&(l->rest),rest);
	l->stiffness=stiffness;
	
	NewSpring(1.0,0.1,r,gr,c,&b);
	AddBody2Link(&b,l);
	DeletePolyhedron(&b);
	/* if collisions may be detected... */
	if (bs!=DECOR_SHAPE)
	  {
	    double p1[3],p2[3];

	    p1[0]=0.1;
	    p1[1]=p1[2]=0.0;
	    
	    p2[0]=1.0-0.1;
	    p2[1]=p2[2]=0.0;
	    
	    NewCylinder(r,p1,p2,c,gr,HIDDEN_SHAPE,&b);
	    AddBody2Link(&b,l);
	    DeletePolyhedron(&b);
	  }
      }
      break;
    case C_LEG:
      {
	double p1[3],p2[3];

	p1[0]=p1[1]=p1[2]=0.0;
	p2[0]=1.0;
	p2[1]=p2[2]=0.0;

	NewSphere(2*r,p1,c,gr,bs,&b);
	AddBody2Link(&b,l);
	DeletePolyhedron(&b);
	
	NewCylinder(r,p1,p2,c,gr,bs,&b);
	AddBody2Link(&b,l);
	DeletePolyhedron(&b);
	
	NewSphere(2*r,p2,c,gr,bs,&b);
	AddBody2Link(&b,l);
	DeletePolyhedron(&b);
      }
      break;
    default:
      Error("Unknown type connection link");
    }
}

void CopyLink(Tlink *l_dst,Tlink *l_src)
{
  unsigned int i,j,n;

  if (l_src==NULL)
    l_dst->name=NULL;
  else
    {
      NEW(l_dst->name,strlen(l_src->name)+1,char);
      strcpy(l_dst->name,l_src->name);
    }
  
  l_dst->type=l_src->type;
  
  InitVector(sizeof(double *),CopyVoidPtr,DeleteVoidPtr,INIT_NUM_SHAPES,&(l_dst->bodies));

  l_dst->allSpheres=TRUE;

  n=LinkNBodies(l_src);
  for(i=0;i<n;i++)
    AddBody2Link(GetLinkBody(i,l_src),l_dst);
  
  l_dst->c=l_src->c;
  l_dst->s=l_src->s;
  HTransformCopy(&(l_dst->R),&(l_src->R));
  HTransformCopy(&(l_dst->iR),&(l_src->iR));

  for(i=0;i<3;i++)
    l_dst->axisID[i]=l_src->axisID[i];

  l_dst->maxCoord=l_src->maxCoord;
  
  if (l_src->csvID==NULL)
    {
      l_dst->csvID=NULL;
      l_dst->nvID=0;
      l_dst->vID=NULL;
    }
  else
    {
      l_dst->csvID=l_src->csvID;
      l_dst->nvID=l_src->nvID;
      NEW(l_dst->vID,l_dst->nvID,unsigned int);
      memcpy(l_dst->vID,l_src->vID,l_dst->nvID*sizeof(unsigned int));
    }

  l_dst->mass=l_src->mass;

  NEW(l_dst->iMatrix,3,double*)
    for(i=0;i<3;i++)
      {
	NEW(l_dst->iMatrix[i],3,double);
	for(j=0;j<3;j++)
	  l_dst->iMatrix[i][j]=l_src->iMatrix[i][j];
      }
  
  HTransformCopy(&(l_dst->iFrame),&(l_src->iFrame));
  
  l_dst->forceEquilibrium=l_src->forceEquilibrium;
  
  for(i=0;i<3;i++)
    {
      l_dst->extForce[i]=l_src->extForce[i];
      l_dst->fixedDim[i]=l_src->fixedDim[i];
    }
  
  CopyInterval(&(l_dst->length),&(l_src->length));
  l_dst->varLength=l_src->varLength;
  
  l_dst->stiffness=l_src->stiffness;
  CopyInterval(&(l_dst->rest),&(l_src->rest));
  CopyInterval(&(l_dst->force),&(l_src->force));
  l_dst->forceModel=l_src->forceModel;

  l_dst->l1=l_src->l1;
  l_dst->l2=l_src->l2;
  for(i=0;i<3;i++)
    {
      l_dst->p1[i]=l_src->p1[i];
      l_dst->p2[i]=l_src->p2[i];
    }
}

void SetLinkMass(double mass,Tlink *l)
{
  if (mass<0.0)
    Error("Negative mass in SetLinkMass");
  l->mass=mass;
  if (mass==0)
    {
      SetLinkInertiaMatrix(NULL,l);
      SetLinkInertialFrame(NULL,l);
    }
    
}

void SetLinkInertiaMatrix(double **m,Tlink *l)
{
  unsigned int i,j;
  
  for(i=0;i<3;i++)
    {
      for(j=i;j<3;j++)
	l->iMatrix[i][j]=(m==NULL?0.0:m[i][j]);
    }
  l->iMatrix[1][0]=l->iMatrix[0][1];
  l->iMatrix[2][0]=l->iMatrix[0][2];
  l->iMatrix[2][1]=l->iMatrix[1][2];
}

void SetLinkInertialFrame(THTransform *t,Tlink *l)
{
  if (t==NULL)
    HTransformIdentity(&(l->iFrame));
  else
    HTransformCopy(&(l->iFrame),t);
}

inline double GetLinkMass(Tlink *l)
{
  return(l->mass);
}

double **GetLinkInertiaMatrix(Tlink *l)
{
  return(l->iMatrix);
}

THTransform *GetLinkInertialFrame(Tlink *l)
{
  return(&(l->iFrame));
}

void AddBody2Link(Tpolyhedron *b,Tlink *l)
{
  Tpolyhedron *bint;

  if (l->type==LINK_NoRot)
    Error("AddBody2Link can not be used for free-rotation links");

  if (!EmptyPolyhedron(b))
    {
      /* for LINK_AxisX only X-symmetric links make sense. */
      NEW(bint,1,Tpolyhedron);
      CopyPolyhedron(bint,b);
      
      NewVectorElement(&bint,&(l->bodies));
      
      l->allSpheres=((l->allSpheres)&&
		     ((GetPolyhedronType(bint)==SPHERE)||
		      (GetPolyhedronStatus(bint)==DECOR_SHAPE)));
      
      l->maxCoord+=GetPolyhedronMaxCoordinate(bint);
    }
}

void AddForce2Link(double fx,double fy,double fz,Tlink *l)
{
  l->extForce[0]+=fx;
  l->extForce[1]+=fy;
  l->extForce[2]+=fz;
}

double GetForceOnLink(unsigned int dim,Tlink *l)
{
  if (dim>2)
    Error("Dimension out of range in GetForceOnLink");
  return(l->extForce[dim]);
}

void NoForceEquilibriumLink(Tlink *l)
{
  /* only possibly TRUE for NoRot links */
  l->forceEquilibrium=FALSE;
}

boolean IsForceEquilibriumLink(Tlink *l)
{
  return(l->forceEquilibrium);
}

void SetLinkTrans(unsigned int dim,double t,Tlink *l)
{
  if (dim>2)
    Error("Dimension out of range in SetLinkTrans");
  l->fixedDim[dim]=t;
}

double GetLinkTrans(unsigned int dim,Tlink *l)
{
  if (dim>2)
    Error("Dimension out of range in GetLinkTrans");
  return(l->fixedDim[dim]);
}

Tinterval *GetLinkLength(Tlink *l)
{
  return(&(l->length));
}

double GetLinkStiffness(Tlink *l)
{
  if ((l->forceModel!=LINEAR_FORCE)&&(!IsConnectionSpring(l)))
    Error("Link without stiffness");

  return(l->stiffness);
}

Tinterval *GetLinkRest(Tlink *l)
{
  if ((l->forceModel!=LINEAR_FORCE)&&(!IsConnectionSpring(l)))
    Error("Link without rest length");
  
  return(&(l->rest));
}

Tinterval *GetLinkMaxForce(Tlink *l)
{
  if (l->forceModel==NO_FORCE)
    Error("Link without force");
  return(&(l->force));
}

void ChangeLinkReferenceFrame(unsigned int r,double **p1,double **p2,Tlink *l)
{
  if (l->type!=LINK_FullRot)
    Error("ChangeLinkReferenceFrame should only be used for full-rotation links");
  
  if ((r!=REP_QLINKS)&&(r!=REP_JOINTS))
    {
      /* This function has no effect when using quaternions.  */
      double v[3][3],n1,n2;
      unsigned int i,j;
      double s,c,d,ac;

      /* Define the vectors from the points */
      n1=0;
      n2=0;
      for(i=0;i<3;i++)
	{
	  v[0][i]=p1[1][i]-p1[0][i];
	  v[1][i]=p2[1][i]-p2[0][i];
	  n1+=v[0][i]*v[0][i];
	  n2+=v[1][i]*v[1][i];
	}
      /* Normalize the vectors */
      n1=sqrt(n1);
      n2=sqrt(n2);
      for(i=0;i<3;i++)
	{
	  v[0][i]/=n1;
	  v[1][i]/=n2;
	}

      /*compute the cos/sin between the two vectors*/
      /*The dot product of the two vectors is the cosinus
	between the vectors*/
      c=0; 
      for(i=0;i<3;i++)
	c+=v[0][i]*v[1][i];
      ac=fabs(c);
      if (ac<0.9) /*Ensure the two vectors are (by far) not aligned*/
	{
	  /*The cross product of the two vectors is a vector
	    orthogonal to the two vectors with norm the sinus
	    of the angle between the vectors*/
	  v[2][0]=v[0][1]*v[1][2]-v[0][2]*v[1][1];
	  v[2][1]=v[0][2]*v[1][0]-v[0][0]*v[1][2];
	  v[2][2]=v[0][0]*v[1][1]-v[0][1]*v[1][0];
	
	  s=0;
	  for(i=0;i<3;i++)
	    s+=v[2][i]*v[2][i];
	  s=sqrt(s);
	  for(i=0;i<3;i++)
	    v[2][i]/=s;
       
	  l->c=c;
	  l->s=s;

	  /* Compute the inverse of the matrix with vector 'v' as colums
	     (i.e., the inverse of the basis change).
	     Rows of R are computed taking into account that 
	     R * [v1 v2 v3] = Id 
	     R=[w1;w2;w3]
	     From construction w3=v3
	     and w1=\alpha v1 + \beta v2
	         w2=\gamma v1 + \delta v2
	     where \alpa, \beta, \gamma, \delta are easy to find
	     taking into account that w1*v1\tr=1 w1*v2\tr=0,... 
	  */
	  d=(1/(s*s));
	  for(j=0;j<3;j++)
	    HTransformSetElement(0,j,d*(v[0][j]-c*v[1][j]),&(l->R));
	  for(j=0;j<3;j++)
	    HTransformSetElement(1,j,d*(v[1][j]-c*v[0][j]),&(l->R));
	  for(j=0;j<3;j++)
	    HTransformSetElement(2,j,v[2][j],&(l->R));
	  
	  /* iR: The inverse of R: v1 v2 v3 in colums */
	   for(i=0;i<3;i++)
	     {
	       for(j=0;j<3;j++)
		 HTransformSetElement(j,i,v[i][j],&(l->iR));
	     }
	}
    }
}

unsigned int LinkNBodies(Tlink *l)
{
  return(VectorSize(&(l->bodies)));
}

unsigned int LinkNAtoms(Tlink *l)
{
  unsigned int i,m,n;
  Tpolyhedron *bd;

  /* Number of spheres used to represent atoms */
  n=0;
  m=LinkNBodies(l);
	
  if ((m>0)&&(VisibleLink(l)))
    {
      for(i=0;i<m;i++)
	{
	  bd=GetLinkBody(i,l);
	  if (GetPolyhedronType(bd)==SPHERE) 
	    n++;
	}
    }
  return(n);
}

Tpolyhedron *GetLinkBody(unsigned int i,Tlink *l)
{
  Tpolyhedron **b;

  b=(Tpolyhedron **)GetVectorElement(i,&(l->bodies));
  if (b==NULL)
    return(NULL);
  else
    return(*b);
}

unsigned int GetLinkBodyStatus(unsigned int i,Tlink *l)
{
  Tpolyhedron **b;

  b=(Tpolyhedron **)GetVectorElement(i,&(l->bodies));
  if (b==NULL)
    return(NO_UINT);
  else
    return(GetPolyhedronStatus(*b));
}

char *GetLinkName(Tlink *l)
{
  return(l->name);
}

unsigned int GetLinkType(Tlink *l)
{
  return(l->type);
}

boolean IsVariableLengthLink(Tlink *l)
{
  return(l->varLength);
}

unsigned int GetLinkForceModel(Tlink *l)
{
  return(l->forceModel);
}  

void GetLinkForceVars(unsigned int r,
		      unsigned int *xID,unsigned int *yID,unsigned int *zID,
		      unsigned int *le,
		      unsigned int *re,unsigned int *f,
		      TCuikSystem *cs,
		      Tlink *l)
{
  unsigned int vID[MAX_ROT_VARS];

  if ((l->type==LINK_NoRot)||(l->type==LINK_Connect))
    Error("Using GetLinkForceVars on an incorrect type of link");
  
  GetRotVarID(r,cs,vID,l);
  switch(l->forceModel)
    {
    case NO_FORCE:
      *xID=vID[0];
      *yID=vID[1];
      *zID=vID[2];
      *le=NO_UINT;
      *f=NO_UINT;
      *re=NO_UINT;
      break;
    case VAR_FORCE:
      *xID=vID[0];
      *yID=vID[1];
      *zID=vID[2];
      *le=vID[3];
      *f=vID[4];
      *re=NO_UINT;
      break;
    case LINEAR_FORCE:
      *xID=vID[0];
      *yID=vID[1];
      *zID=vID[2];
      *le=vID[3];
      *f=vID[4];
      *re=vID[5];
      break;
    default:
      Error("Unknown force model in GetLinkForcevars");
    }
}

double LinkPotentialEnergy(unsigned int r,TCuikSystem *cs,double *p,Tlink *l)
{
  double e;

  /* Only consider elements with variable length. Element with constant length
     produce a constant offset to the energy level.
     Note that all variable length elements have possitive stiffness. */
  if ((l->varLength)&&(l->forceModel==LINEAR_FORCE))
    {
      double d;
      unsigned int vID[MAX_ROT_VARS];
      
      GetRotVarID(r,cs,vID,l);

      if ((vID[3]==NO_UINT)||(vID[5]==NO_UINT))
	Error("Missing force field variable");
      
      d=p[vID[3]]-p[vID[5]]; /* length - rest */
      e=0.5*l->stiffness*d*d;   /* 0.5*k*(length-rest)^2 */
    }
  else
    e=0.0;
  
  return(e);
}

void LinkForceField(unsigned int r,TCuikSystem *cs,double *p,double *g,Tlink *l)
{
  if ((l->varLength)&&(l->forceModel==LINEAR_FORCE))
    {
      double f;
      unsigned int vID[MAX_ROT_VARS];
      
      GetRotVarID(r,cs,vID,l);

      if ((vID[3]==NO_UINT)||(vID[5]==NO_UINT))
	Error("Missing force field variable");
      
      f=l->stiffness*(p[vID[3]]-p[vID[5]]);   /* k*(length-rest)*/
      
      g[vID[3]]=+f;
      g[vID[5]]=-f;
    }
}

void GetLinkTransSeq(Tparameters *p,TCuikSystem *cs,TTransSeq *ts,Tlink *l)
{
  InitTransSeq(ts);

  if (l->varLength)
    {
      char *vname;
      unsigned int vID;
      
      NEW(vname,strlen(l->name)+20,char);
      
      LINK_LENGTH(vname,l->name);
      vID=GetCSVariableID(vname,cs);
      if (vID==NO_UINT)
	Error("Undefined variable in GetLinkTransSeq");
      AddVarTrans2TransSeq(TX,1,vID,ts);

      free(vname);
    }
}

void GetLinkTransform(double *dof,THTransform *t,Tlink *l)
{
  if (l->varLength)
    HTransformTx(dof[0],t);
  else
    HTransformIdentity(t);
}

void GetLinkTransformFromConf(TLinkConf *def,THTransform *t,Tlink *l)
{
  GetLinkTransform(def->p,t,l);
}

void GetLinkConfFromSolution(unsigned int r,TCuikSystem *cs,double *sol,TLinkConf *def,Tlink *l)
{
  def->l=l;
  def->ndp=NumLinkDOF(l);
  if (def->ndp>0)
    {
      unsigned int k;
      unsigned int vID[MAX_ROT_VARS];
  
      GetRotVarID(r,cs,vID,l);
	
      NEW(def->p,def->ndp,double);
  
      k=0;
      if (l->varLength)
	{
	  def->p[k]=sol[vID[3]]; /* length, if variable */
	  k++;
	}
      
      if (l->forceModel!=NO_FORCE)
	{ 
	  def->p[k]=sol[vID[4]]; /* force, if variable */
	  k++;
	  if (l->forceModel==LINEAR_FORCE)
	    def->p[k]=sol[vID[5]]; /* rest, if variable */
	}
    }
  else
    def->p=NULL;
}

void GetLinkConfFromDOF(double *dof,TLinkConf *def,Tlink *l)
{
  def->l=l;
  def->ndp=NumLinkDOF(l);
  if (def->ndp>0)
    {
      unsigned int k;
      
      NEW(def->p,def->ndp,double);
      k=0;
      if (l->varLength)
	{
	  def->p[k]=dof[k]; /* length, if variable */
	  k++;
	}

      if (l->forceModel!=NO_FORCE)
	{ 
	  def->p[k]=dof[k]; /* force, if variable */
	  k++;
	  if (l->forceModel==LINEAR_FORCE)
	    def->p[k]=dof[k]; /* rest, if variable */
	}
    }
  else
    def->p=NULL;
}

void GenerateSolutionFromLinkConf(unsigned int r,TCuikSystem *cs,TLinkConf *def,double *sol,Tlink *l)
{
  if (def->l!=l)
    Error("Link missmatch in GenerateSolutionFromLinkConf");
  if (NumLinkDOF(l)>0)
    {
      unsigned int k;
      unsigned int vID[MAX_ROT_VARS];
  
      GetRotVarID(r,cs,vID,l);

      k=0; 
      if (l->varLength)
	{
	  sol[vID[3]]=def->p[k]; /* length, if variable */
	  k++;
	}
      
      if (l->forceModel!=NO_FORCE)
	{
	  sol[vID[4]]=def->p[k]; /* force, if variable */
	  k++;
	  
	  if (l->forceModel==LINEAR_FORCE)
	     sol[vID[5]]=def->p[k]; /* rest, if variable */
	}
    }
}

void GenerateDOFFromLinkConf(TLinkConf *def,double *dof,Tlink *l)
{  
  if (def->l!=l)
    Error("Link missmatch in GenerateDeformationDOF");
  
  if (def->ndp>0)
    memcpy(dof,def->p,sizeof(double)*def->ndp);
}

inline unsigned int NumLinkDOF(Tlink *l)
{
  /*
    varLength -> length variable
    varForce -> force variable
    linearForce -> force variable + rest length
   */
  return((l->varLength?1:0)+(l->forceModel==VAR_FORCE?1:(l->forceModel==LINEAR_FORCE?2:0)));
}

Tinterval *GetLinkDOFRange(unsigned int i,Tlink *l)
{
  unsigned int nd;
  Tinterval *s=NULL;

  nd=NumLinkDOF(l);
  if (nd>0)
    {
      if (i>=nd)
	Error("Wrong index in GetDeformationRange");
      
      switch(i)
	{
	case 0:
	  if (l->varLength)
	    s=&(l->length);
	  else
	    s=&(l->force);
	  break;
	case 1:
	  if (l->varLength)
	    s=&(l->force);
	  else
	    s=&(l->rest);
	  break;
	case 2:
	  s=&(l->rest);
	}
    }
  else
    Error("Using GetDeformationRange on a link without internal degrees of freedom");

  return(s);
}

void GetLinkDOFLabel(unsigned int i,char **n,Tlink *l)
{
  unsigned int nd;

  *n=NULL;
  
  nd=NumLinkDOF(l);
  if (nd>0)
    {
      if (i>=nd)
	Error("Wrong index in GetDeformationLabel");
      
      NEW(*n,20,char);
      switch(i)
	{
	case 0:
	  if (l->varLength)
	    sprintf(*n,"Elongation");
	  else
	    sprintf(*n,"Force");
	  break;
	case 1:
	  if (l->varLength)
	    sprintf(*n,"Force");
	  else
	    sprintf(*n,"Rest");
	  break;
	case 2:
	    sprintf(*n,"Rest");
	}
    }
  else
    Error("Using GetDeformationLabel on a non-deformable link");
}

boolean IsLinkAllSpheres(Tlink *l)
{
  return(l->allSpheres);
}

void SetPoseVars(unsigned int r,boolean *vars,TCuikSystem *cs,Tlink *l)
{
  SetTransVars(vars,cs,l);
  SetRotVars(r,vars,cs,l);
}

unsigned int SetForceVars(unsigned int r,boolean *vars,TCuikSystem *cs,Tlink *l)
{
  unsigned int n;
  
  if (l->forceModel!=NO_FORCE)
    {
       unsigned int vID[MAX_ROT_VARS];
      
      GetRotVarID(r,cs,vID,l);
      vars[vID[4]]=TRUE; /* force */
      n=1;
    }
  else
    n=0;

  return(n);
}

unsigned int SetForceRelatedVars(unsigned int r,boolean *vars,TCuikSystem *cs,Tlink *l)
{
  unsigned int n;
  
  if (l->forceModel!=NO_FORCE)
    {
       unsigned int vID[MAX_ROT_VARS];
      
      GetRotVarID(r,cs,vID,l);
      vars[vID[4]]=TRUE; /* force */
      n=1;
      if (l->forceModel==LINEAR_FORCE)
	{
	  vars[vID[5]]=TRUE; /* rest length */
	  n++;
	}
    }
  else
    n=0;

  return(n);
}

void SetTransVars(boolean *vars,TCuikSystem *cs,Tlink *l)
{
  if (l->type!=LINK_Connect)
    {
      char *vname;
      unsigned int k,id;
      
      NEW(vname,strlen(l->name)+100,char);
      for(k=0;k<3;k++)
	{
	  LINK_TRANS(vname,l->name,k);
	  id=GetCSVariableID(vname,cs);
	  if (id!=NO_UINT) /*Ground links has no variables*/
	    vars[id]=TRUE;
	}
      free(vname);
    }
}

void GetRotVarID(unsigned int r,TCuikSystem *cs,unsigned int *vID,Tlink *l)
{ 
  /* Many threads can access the link information in parallel. We must be sure
     that the information stored in the link itself is valid and consistent 
     (i.e., that no other thread re-writes it while we access it). 
     In some particular condition we might have a race issue here... but not
     in the way we use this function (csvID is only changed once from NULL
     to a particular value. We do not call this function with different cs's)*/
    if (cs!=l->csvID)
      {
	#pragma omp critical
	{
	  /* The first thread that enters the critical section changes l->csvID
	     The threads possibly waiting in the critical section can skip the
	     update. 
	     Note that if a process is inside the critical region csvID is NULL
	     and, thus the 'if' above will not hold during this period, i.e., when
	     a process is modifying the cache, all other process will wait at the
	     beginning of the critial region. When they cross it, they might
	     eventually realize that the work is already done*/
	  if (cs!=l->csvID)
	    {
	      l->csvID=NULL; /* to force threads to wait before the critial region */
	
	      /* When we are in this block is for sure that we are the only
		 thread manipulating the link information. */
	      /* The information stored in the link is not valid for 'cs'. 
		 Re-generate the link information. In general, the information
		 is only generated once and later calls to this function just
		 use the memcpy below -> they are fast. */
	      switch(l->type)
		{
		case LINK_AxisX:
		case LINK_DeformX:
		case LINK_PrismaticX:
		  /* Those links have relevant variables (force-related) even
		     if representation is JOINTS */
		  GetRotVarIDAxisX(cs,l);
		  break;
		case LINK_FullRot:
		  switch(r)
		    {
		    case REP_LINKS:
		      GetRotVarIDLinks(cs,l);
		      break;
		    case REP_FLINKS:
		      GetRotVarIDFLinks(cs,l);
		      break;
		    case REP_QLINKS:
		      GetRotVarIDQLinks(cs,l);
		      break;
		    case REP_JOINTS:
		      /* Full Rot links generate no joint variable */
		      break;
		    default:
		      Error("Undefined representation type in GetRotVarID");
		    }
		  break;
		case LINK_NoRot:
		case LINK_Connect:
		  /* no variable is used for NoRot and Connect links */
		  l->nvID=0;
		  break;
		default:
		  Error("Unkown link type in GetRotVarID");     
		}
	      l->csvID=cs; /* from this point on the cache is valid and can be accesed in parallel */
	    }
	}
      }
    
  /*  Copy the information stored in the link. */
  if (l->nvID>0)
    memcpy(vID,l->vID,sizeof(unsigned int)*l->nvID);
}

void GetRotVarIDAxisX(TCuikSystem *cs,Tlink *l)
{
  char *vname;
  unsigned int i;

  l->nvID=6;
  if (l->csvID==NULL)
    NEW(l->vID,l->nvID,unsigned int);
      
  NEW(vname,strlen(l->name)+100,char);
  for(i=0;i<3;i++)
    {
      LINK_ROT(vname,l->name,0,i);
      l->vID[i]=GetCSVariableID(vname,cs);
    }

  if (l->varLength)
    {
      LINK_LENGTH(vname,l->name);
      l->vID[3]=GetCSVariableID(vname,cs);
    }
  else
    l->vID[3]=NO_UINT;
      
  /* now the compression/tension parameter, if any */
  if (l->forceModel!=NO_FORCE)
    {	  
      LINK_MAX_FORCE(vname,l->name);
      l->vID[4]=GetCSVariableID(vname,cs);

      if (l->forceModel==LINEAR_FORCE)
	{
	  LINK_REST(vname,l->name);
	  l->vID[5]=GetCSVariableID(vname,cs);
	}
      else
	l->vID[5]=NO_UINT;
    }
  else
    l->vID[4]=l->vID[5]=NO_UINT;
      
  free(vname);
}

void GetRotVarIDFLinks(TCuikSystem *cs,Tlink *l)
{
  char *vname;
  unsigned int i,j,k;

  l->nvID=9;
  if (l->csvID==NULL)
    NEW(l->vID,l->nvID,unsigned int);
      
  NEW(vname,strlen(l->name)+100,char);
  k=0;
  for(i=0;i<3;i++) /*vector*/
    {
      for(j=0;j<3;j++) /*component*/
	{
	  LINK_ROT(vname,l->name,i,j);
	  /* for the ground link all vID will be NO_UINT. Use at your own
	     risk. */
	  l->vID[k]=GetCSVariableID(vname,cs);
	  k++;
	}
    }
  free(vname);
}

void GetRotVarIDLinks(TCuikSystem *cs,Tlink *l)
{
  char *vname;
  unsigned int i,j,k;

  l->nvID=12;
  if (l->csvID==NULL)
    NEW(l->vID,l->nvID,unsigned int);
      
  NEW(vname,strlen(l->name)+100,char);
  k=0;
  for(i=0;i<4;i++) /*vector*/
    {
      for(j=0;j<3;j++) /*component*/
	{
	  LINK_ROT2(vname,l->name,i,j);
	  /* for the ground link all vID will be NO_UINT. Use at your own*/
	  l->vID[k]=GetCSVariableID(vname,cs);
	  k++;
	}
    }
  free(vname);
}

void GetRotVarIDQLinks(TCuikSystem *cs,Tlink *l) 
{ 
  char *vname;
  unsigned int i,j,k; 
      
  NEW(vname,strlen(l->name)+100,char);
      
  l->nvID=14; 
  if (l->csvID==NULL) 
    NEW(l->vID,l->nvID,unsigned int);
      
  k=0; 
  for(j=0;j<4;j++)
    {
      LINK_ROT3_Q(vname,l->name,j);  
      l->vID[k]=GetCSVariableID(vname,cs); 
      k++;
    }

  for(i=0;i<4;i++)  
    {
      for(j=i;j<4;j++) 
	{
	  LINK_ROT3_E(vname,l->name,i,j);
	  /* for the ground link all vID will be NO_UINT. Use at your own risk */
	  l->vID[k]=GetCSVariableID(vname,cs); 
	  k++;
	}
    }
      
  free(vname);
}

void SetRotVars(unsigned int r,boolean *vars,TCuikSystem *cs,Tlink *l)
{
  if (r!=REP_JOINTS) /* When using joint representation links 
			do not generate variables */
    {
      unsigned int i,id,n=0;
      unsigned int vID[MAX_ROT_VARS];
      
      GetRotVarID(r,cs,vID,l);	  
      switch(l->type)
	{
	case LINK_AxisX:
	case LINK_DeformX:
	case LINK_PrismaticX:
	  n=6; /* max 6 system vars: 3 director vector + 3 length/force/rest */
	  break;
	case LINK_FullRot:
	  switch(r)
	    {
	    case REP_LINKS:
	      n=6;
	      break;
	    case REP_FLINKS:
	      n=9;
	      break;
	    case REP_QLINKS:
	      n=4;
	      break;
	    default:
	      Error("Undefined representation type in SetRotVars");
	    }
	  break;
	case LINK_NoRot:
	case LINK_Connect:
	  n=0;
	  break;
	default:
	  Error("Unknown link type in SetRotVars");
	}
      
      for(i=0;i<n;i++) 
	{
	  id=vID[i];
	  if (id!=NO_UINT) /*Ground links has not variables*/
	    vars[id]=TRUE;
	}
	
    }
}

void GetLinkPoseSimpVars(Tparameters *p,boolean *sv,
			 TCuikSystem *cs,Tlink *l)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r!=REP_JOINTS) /* When using joint representation links 
			do not generate variables */
    {
      unsigned int i,id,n=0;
      char *v;
      unsigned int vID[MAX_ROT_VARS];
  
      GetRotVarID(r,cs,vID,l);
	  
      switch(l->type)
	{
	case LINK_AxisX:
	case LINK_DeformX:
	case LINK_PrismaticX:
	  n=6; /* max 6 system vars: 3 director vector + 3 length/force/rest */
	  break;
	case LINK_FullRot:
	  switch(r)
	    {
	    case REP_LINKS:
	      n=6;
	      break;
	    case REP_FLINKS:
	      n=9;
	      break;
	    case REP_QLINKS:
	      n=4;
	      break;
	    default:
	      Error("Undefined representation type in SetRotVars");
	    }
	  break;
	case LINK_NoRot:
	case LINK_Connect:
	  n=0;
	  break;
	default:
	  Error("Unknown link type in SetRotVars");
	}
      
      for(i=0;i<n;i++)
	{
	  id=vID[i];
	  if (id!=NO_UINT) /*Ground links has not variables*/
	    {
	      v=GetCSVariableName(id,cs);
	      if (IsSystemVarInSimpCS(p,v,cs))
		sv[id]=TRUE;
	    }
	}
    }
}

void GenerateLinkRot(Tparameters *p,unsigned int lID,
		     TCuikSystem *cs,Tlink *l)
{
  unsigned int r;
  
  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r!=REP_JOINTS)
    {
      switch(l->type)
	{
	case LINK_AxisX:
	case LINK_DeformX:
	case LINK_PrismaticX:
	  GenerateLinkRotAxisX(p,lID,cs,l);
	  break;
	case LINK_FullRot:
	  switch(r)
	    {
	    case REP_LINKS:
	      GenerateLinkRotLinks(p,lID,cs,l);
	      break;
	    case REP_FLINKS:
	      GenerateLinkRotFLinks(p,lID,cs,l);
	      break;
	    case REP_QLINKS:
	      GenerateLinkRotQLinks(p,lID,cs,l);
	      break;
	    default:
	      Error("Undefined representation type in GenerateLinkRot");
	    }
	  break;
	case LINK_NoRot:
	case LINK_Connect:

	  break;
	default:
	  Error("Unkonw link type in GenerateLinkRot");
	}
    }
  GenerateLinkConf(p,cs,l);
}

void GenerateLinkConf(Tparameters *p,TCuikSystem *cs,Tlink *l)
{
  unsigned int le,re,fr,rep;
  char *vname;
  Tvariable var;
      
  NEW(vname,strlen(l->name)+100,char);

  if (l->varLength)
    {
      LINK_LENGTH(vname,l->name);
      /* Check that the var/equation are not already created */
       if (GetCSVariableID(vname,cs)==NO_UINT)
	{
	  NewVariable(SYSTEM_VAR,vname,&var);
	  SetVariableInterval(&(l->length),&var);
	  le=AddVariable2CS(&var,cs);	  
	  DeleteVariable(&var);
	}
    }
  else
    le=NO_UINT;
      
  if (l->forceModel!=NO_FORCE)
    { 
      /* We generate the variables even if they have
	 ct range */
      LINK_MAX_FORCE(vname,l->name);

      /* Check that the force var/equation are not already created */
      if (GetCSVariableID(vname,cs)==NO_UINT)
	{
	  Tmonomial f;
	  Tequation eq;
	  
	  if (l->forceModel==LINEAR_FORCE)
	    {
	      /* Create the rest length variable */
	      LINK_REST(vname,l->name);
	      NewVariable(SYSTEM_VAR,vname,&var);
	      SetVariableInterval(&(l->rest),&var);
	      re=AddVariable2CS(&var,cs);	  
	      DeleteVariable(&var);
	    }
	  
	  /* actually create the force variable */
	  LINK_MAX_FORCE(vname,l->name);
	  NewVariable(SYSTEM_VAR,vname,&var);
	  SetVariableInterval(&(l->force),&var);
	  fr=AddVariable2CS(&var,cs);	  
	  DeleteVariable(&var);

	  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
	  
	  if (((rep==REP_LINKS)||(rep==REP_FLINKS))&&(l->forceModel==LINEAR_FORCE))
	    {  
	      /* Now the equation linking length, stiffnes, rest and force. */
	      InitEquation(&eq);
	      InitMonomial(&f);
	      
	      /* stiffness * length */
	      AddCt2Monomial(l->stiffness,&f); 
	      if (le==NO_UINT)
		Error("Can not have constant length in linear force models");
	      else
		AddVariable2Monomial(NFUN,le,1,&f); 
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);
	      
	      /* -stiffness * rest_length */
	      AddCt2Monomial(-l->stiffness,&f);
	      AddVariable2Monomial(NFUN,re,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);
      
	      AddCt2Monomial(-1,&f);                /* = force */
	      AddVariable2Monomial(NFUN,fr,1,&f);
	      AddMonomial(&f,&eq);
      	      DeleteMonomial(&f);
      
	      SetEquationCmp(EQU,&eq);
	      SetEquationValue(0,&eq);
	      SetEquationType(SYSTEM_EQ,&eq);
      
	      AddEquation2CS(p,&eq,cs);
	      DeleteEquation(&eq);
	    }
	}
    }
  free(vname);
}
  
void GenerateLinkRotAxisX(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l)
{
  if (!IsGroundLink(lID))
    {
      char *vname;

      NEW(vname,strlen(l->name)+100,char);
      LINK_ROT(vname,l->name,0,0);
      
      /* only create the director vector if it is not already there */
      if (GetCSVariableID(vname,cs)==NO_UINT)
	{
	  unsigned int j;
	  Tinterval range;
	  Tequation eqn;
	  unsigned int linkVars[3]; 
	  Tvariable var;

	  NewInterval(-1.0,1.0,&range);
	  for(j=0;j<3;j++) /*component*/
	    {
	      LINK_ROT(vname,l->name,0,j);
	      NewVariable(SYSTEM_VAR,vname,&var);
	      SetVariableInterval(&range,&var);
	      linkVars[j]=AddVariable2CS(&var,cs);	  
	      DeleteVariable(&var);
	    }
	  
	  GenerateNormEquation(linkVars[0],linkVars[1],linkVars[2],1.0,&eqn);
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);
	}
      free(vname);
    }
}

void GenerateLinkRotFLinks(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l)
{
  if (!IsGroundLink(lID))
    {
      char *vname;

      /*If the cuiksytem already has the link variables (and thus the corresponding equations)
	there is nothing to be done. */
      
      NEW(vname,strlen(l->name)+100,char);

      LINK_ROT(vname,l->name,0,0); /* This variable is used both in LINK_FullRot  and LINK_AxisX */

      if (GetCSVariableID(vname,cs)==NO_UINT)
	{
	  unsigned int i,j;
	  Tinterval range;
	  Tequation eqn;
	  Tequation eq[3];
	  unsigned int linkVars[9]; 
	  Tvariable var;

	  NewInterval(-1.0,1.0,&range);
	  for(i=0;i<3;i++) /*vector*/
	    {
	      for(j=0;j<3;j++) /*component*/
		{
		  LINK_ROT(vname,l->name,i,j);
		  NewVariable(SYSTEM_VAR,vname,&var);
		  SetVariableInterval(&range,&var);
		  linkVars[i*3+j]=AddVariable2CS(&var,cs);	  
		  DeleteVariable(&var);
		}
	    }

	  for(i=0;i<2+ROT_REDUNDANCY;i++)
	    {
	      GenerateNormEquation(linkVars[3*i+0],linkVars[3*i+1],linkVars[3*i+2],1.0,&eqn);
	      AddEquation2CS(p,&eqn,cs);
	      DeleteEquation(&eqn);
	    } 

	  /*ONLY ONE OF THE THREE FOLLOWING BLOCKS IS REQUIRED, THE OTHER TWO ARE REDUNDANT. */
	  #if (ROT_REDUNDANCY==1)
	    /*********************************************************************/

	    GenerateDotProductEquation(linkVars[0],linkVars[1],linkVars[2], /* X */
				       linkVars[3],linkVars[4],linkVars[5], /* Y */
				       NO_UINT,l->c,&eqn);
	    AddEquation2CS(p,&eqn,cs);
	    DeleteEquation(&eqn);


	    GenerateCrossProductEquations(linkVars[0],linkVars[1],linkVars[2], /* X */
					  linkVars[3],linkVars[4],linkVars[5], /* Y */
					  linkVars[6],linkVars[7],linkVars[8], /* Z */
					  NO_UINT,l->s,eq);
	    for(i=0;i<3;i++)
	      {
		AddEquation2CS(p,&(eq[i]),cs);
		DeleteEquation(&(eq[i]));
	      }
	    /*********************************************************************/
	  #endif
         
	  /*********************************************************************/
	  GenerateDotProductEquation(linkVars[6],linkVars[7],linkVars[8], /* Z */
				     linkVars[0],linkVars[1],linkVars[2], /* X */
				     NO_UINT,0,&eqn);
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);
	  if (l->s==1) /*This second redundant equation is only used for orthogonal X-Y vectors */
	    { 
	      GenerateCrossProductEquations(linkVars[6],linkVars[7],linkVars[8], /* Z */
					    linkVars[0],linkVars[1],linkVars[2], /* X */
					    linkVars[3],linkVars[4],linkVars[5], /* Y */
					    NO_UINT,1.0,eq);
	      for(i=0;i<3;i++)
		{
		  AddEquation2CS(p,&(eq[i]),cs);
		  DeleteEquation(&(eq[i]));
		}
	    }
	  /*********************************************************************/

	  #if (ROT_REDUNDANCY==1) /*Redundancy is only used for orthogonal X-Y vectors */
	    /*********************************************************************/
	    GenerateDotProductEquation(linkVars[3],linkVars[4],linkVars[5], /* Y */
				       linkVars[6],linkVars[7],linkVars[8], /* Z */
				       NO_UINT,0,&eqn);
	    AddEquation2CS(p,&eqn,cs);
	    DeleteEquation(&eqn);
	    
	    
	    if (l->s==1) /*This second redundant equation is only used for orthogonal X-Y vectors */
	      { 
		GenerateCrossProductEquations(linkVars[3],linkVars[4],linkVars[5], /* Y */
					      linkVars[6],linkVars[7],linkVars[8], /* Z */
					      linkVars[0],linkVars[1],linkVars[2], /* X */
					      NO_UINT,1.0,eq);
		for(i=0;i<3;i++)
		  {
		    AddEquation2CS(p,&(eq[i]),cs);
		    DeleteEquation(&(eq[i]));
		  }
	      }
	    /*********************************************************************/
	  #endif
	}

      free(vname);
    }
}

void GenerateLinkRotLinks(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l)
{
  if (!IsGroundLink(lID))
    {
      char *vname;

      /*If the cuiksytem already has the link variables (and thus the corresponding equations)
	there is nothing to be done. */

      NEW(vname,strlen(l->name)+100,char);
  
      LINK_ROT(vname,l->name,0,0);
      
      if (GetCSVariableID(vname,cs)==NO_UINT)
	{
	  unsigned int i,j;
	  Tinterval range;
	  Tequation eqn;
	  unsigned int linkVars[12]; 
	  Tvariable var;

	  NewInterval(-1.0,1.0,&range);
	  /* vectors u,v,w,wp */
	  for(i=0;i<4;i++) /*vector*/
	    {
	      for(j=0;j<3;j++) /*component*/
		{
		  LINK_ROT2(vname,l->name,i,j);
		  NewVariable((i<2?SYSTEM_VAR:DUMMY_VAR),vname,&var);
		  SetVariableInterval(&range,&var);
		  linkVars[i*3+j]=AddVariable2CS(&var,cs);	  
		  DeleteVariable(&var);
		}
	    }

	  /* define w and wp from x and y */
	  GenerateScaledSaddleEquation(l->s,linkVars[1],linkVars[5],linkVars[6],&eqn); 
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);

	  GenerateScaledSaddleEquation(l->s,linkVars[2],linkVars[3],linkVars[7],&eqn); 
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);

	  GenerateScaledSaddleEquation(l->s,linkVars[0],linkVars[4],linkVars[8],&eqn); 
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);

	  GenerateScaledSaddleEquation(l->s,linkVars[2],linkVars[4],linkVars[9],&eqn); 
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);

	  GenerateScaledSaddleEquation(l->s,linkVars[0],linkVars[5],linkVars[10],&eqn); 
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);

	  GenerateScaledSaddleEquation(l->s,linkVars[1],linkVars[3],linkVars[11],&eqn); 
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);

	      
	  GenerateDotProductEquation(linkVars[0],linkVars[1],linkVars[2], /* X */
	    linkVars[3],linkVars[4],linkVars[5], /* Y */
	    NO_UINT,l->c,&eqn);
	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);

	  /* norm of x and y */
	  for(i=0;i<2;i++)
	    {
	      GenerateNormEquation(linkVars[3*i+0],linkVars[3*i+1],linkVars[3*i+2],1.0,&eqn);
	      AddEquation2CS(p,&eqn,cs);
	      DeleteEquation(&eqn);
	    }
	}

      free(vname);
    }
}

void GenerateLinkRotQLinks(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l)
{ 
  if (!IsGroundLink(lID))
    {
      char *vname;

      /*If the cuiksytem already has the link variables (and thus the corresponding equations)
	there is nothing to be done. */

      NEW(vname,strlen(l->name)+100,char);
      
      LINK_ROT3_Q(vname,l->name,0); /* used both in LINK_FullRot and LINK_AxisX */

      if (GetCSVariableID(vname,cs)==NO_UINT)
	{
	  unsigned int i,j,n;
	  Tinterval range,range2;
	  Tequation eqn;
	  unsigned int linkVars[10]; 
	  unsigned int qVars[4];
	  Tvariable var;
	  Tmonomial f;
	  
	  NewInterval(-1.0,1.0,&range);
	  NewInterval(0.0,1.0,&range2);

	  /* q variables are used in all cases */
	  for(j=0;j<4;j++)
	    {
	      LINK_ROT3_Q(vname,l->name,j);
	      NewVariable(SYSTEM_VAR,vname,&var);
	      if (j==0)
		SetVariableInterval(&range2,&var);
	      else
		SetVariableInterval(&range,&var);
	      qVars[j]=AddVariable2CS(&var,cs);	  
	      DeleteVariable(&var);
	    }
	  
	  /* Add the relation between the E variables (dummies) and the
	     Q variables (system) */

	  n=0;
	  for(i=0;i<4;i++)
	    { 
	      for(j=i;j<4;j++)
		{
		  LINK_ROT3_E(vname,l->name,i,j);
		  NewVariable(DUMMY_VAR,vname,&var);
		  if (i==j)
		    SetVariableInterval(&range2,&var);
		  else
		    SetVariableInterval(&range,&var);
		  linkVars[n]=AddVariable2CS(&var,cs);
		  n++;
		  DeleteVariable(&var);
		}
	    }

	  n=0;
	  for(i=0;i<4;i++)
	    { 
	      for(j=i;j<4;j++)
		{
		  /* When i=j (-> qVars[i]==qVars[j]) a parabola equation is generated! */
		  GenerateSaddleEquation(qVars[i],qVars[j],linkVars[n],&eqn);
		  AddEquation2CS(p,&eqn,cs);
		  DeleteEquation(&eqn);
		  n++;
		}
	    }
	      
	  /* norm of the Q (system) variables is 1 (we use the already introduced
	     dummy e_i variables) */
	  InitEquation(&eqn);
	  InitMonomial(&f);
	  
	  AddVariable2Monomial(NFUN,linkVars[0],1,&f);
	  AddMonomial(&f,&eqn);ResetMonomial(&f);
	  AddVariable2Monomial(NFUN,linkVars[4],1,&f);
	  AddMonomial(&f,&eqn);ResetMonomial(&f);
	  AddVariable2Monomial(NFUN,linkVars[7],1,&f);
	  AddMonomial(&f,&eqn);ResetMonomial(&f);
	  AddVariable2Monomial(NFUN,linkVars[9],1,&f);
	  AddMonomial(&f,&eqn);
	   
	    
	  /* add the q normalization equation */
	  DeleteMonomial(&f);

	  SetEquationCmp(EQU,&eqn);
	  SetEquationValue(1,&eqn);
	  SetEquationType(SYSTEM_EQ,&eqn);

	  AddEquation2CS(p,&eqn,cs);
	  DeleteEquation(&eqn);
		
	}
      free(vname);
    }
}

void FixLinkZToZero(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l)
{
  unsigned int r;

  if (l->type==LINK_Connect)
    Error("The Z of connection links can not be fixed");
 
  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r!=REP_JOINTS)
    { 
      if ((l->type==LINK_AxisX)||(l->type==LINK_DeformX)||(l->type==LINK_PrismaticX))
	{
	  Tmonomial f;
	  Tequation eq;
	  unsigned int vID[MAX_ROT_VARS];
	  
	  if (IsGroundLink(lID))
	    Error("The root link of a tensegrity can not be an active element");
	  
	  GetRotVarID(r,cs,vID,l);

	  /* z */
	  InitEquation(&eq);
	  InitMonomial(&f);
	  AddVariable2Monomial(NFUN,vID[2],1,&f);
	  AddMonomial(&f,&eq);
	  DeleteMonomial(&f);

	  /* = 0 */
	  SetEquationCmp(EQU,&eq);
	  SetEquationValue(0.0,&eq);
	  
	  SetEquationType(SYSTEM_EQ,&eq);
	  AddEquation2CS(p,&eq,cs);
	  DeleteEquation(&eq);
	} 
    }
}

void ApplyLinkRot(Tparameters *pr,
		  double sf,unsigned int sv,double *p,Tequation *eq,
		  TCuikSystem *cs,boolean groundLink,Tlink *l)
{
  unsigned int r;

  if (l->type==LINK_Connect)
    Error("ApplyLinkRot is not defined in connection links");
  
  r=(unsigned int)(GetParameter(CT_REPRESENTATION,pr));
  if ((r!=REP_JOINTS)&&(fabs(sf)*Norm(3,p)>ZERO))
    {
      switch(l->type)
	{
	case LINK_AxisX:
	  ApplyLinkRotAxisX(sf,sv,p,eq,cs,groundLink,l);
	  break;
	case LINK_DeformX:
	case LINK_PrismaticX:
	  ApplyLinkRotDeformX(pr,sf,sv,p,eq,cs,groundLink,l);
	  break;
	case LINK_FullRot:
	  switch(r)
	    {
	    case REP_LINKS:
	      ApplyLinkRotLinks(sf,sv,p,eq,cs,groundLink,l);
	      break;
	    case REP_FLINKS:
	      ApplyLinkRotFLinks(sf,sv,p,eq,cs,groundLink,l);
	      break;
	    case REP_QLINKS:
	      ApplyLinkRotQLinks(sf,sv,p,eq,cs,groundLink,l);
	      break;
	    default:
	      Error("Undefined representation type in ApplyLinkRot");
	    }
	  break;
	case LINK_NoRot:
	  /* NoRot links have the same orientation as the global frame */
	  switch(r)
	    {
	    case REP_LINKS:
	      ApplyLinkRotLinks(sf,sv,p,eq,cs,TRUE,l);
	      break;
	    case REP_FLINKS:
	      ApplyLinkRotFLinks(sf,sv,p,eq,cs,TRUE,l);
	      break;
	    case REP_QLINKS:
	      ApplyLinkRotQLinks(sf,sv,p,eq,cs,TRUE,l);
	      break;
	    default:
	      Error("Undefined representation type in ApplyLinkRot");
	    }
	  break;
	default:
	  Error("Unkown link type in ApplyLinkRot");
	}
    }
}

void ApplyLinkRotNoDeform(Tparameters *pr,
			  double sf,unsigned int sv,double *p,Tequation *eq,
			  TCuikSystem *cs,boolean groundLink,Tlink *l)
{
  if (l->varLength)
    ApplyLinkRotAxisX(sf,sv,p,eq,cs,groundLink,l);
  else
    ApplyLinkRot(pr,sf,sv,p,eq,cs,groundLink,l);
}

void ApplyLinkRotAxisX(double sf,unsigned int sv,double *p,Tequation *eq,
		       TCuikSystem *cs,boolean groundLink,Tlink *l)
{
  Tmonomial f;

  /*
    sf*sv*T(px 0 0) where T is defined from the linkVars (check that hasVars==TRUE) 
    T only has x component
  */
  if (Norm(2,&(p[1]))>ZERO)
    Error("X only links can only be used on points on the X-axis");

  InitMonomial(&f);
  if (groundLink)
    {
      if (sv!=NO_UINT)
	AddVariable2Monomial(NFUN,sv,1,&f);
      AddCt2Monomial(sf*p[0],&f);
      
      AddMonomial(&f,&(eq[0]));
      ResetMonomial(&f);
    }
  else
    {
      unsigned int j;
      unsigned int linkVars[3]; 
      char *vname;

      NEW(vname,strlen(l->name)+100,char);

      for(j=0;j<3;j++)
	{
	  LINK_ROT(vname,l->name,0,j);
	  linkVars[j]=GetCSVariableID(vname,cs);
	  if (linkVars[j]==NO_UINT)
	    Error("Undefined reference variable in ApplyLinkRotAxisX");
	}
  
      for(j=0;j<3;j++)
	{
	  AddVariable2Monomial(NFUN,linkVars[j],1,&f);
	  if (sv!=NO_UINT)
	    AddVariable2Monomial(NFUN,sv,1,&f);
	  AddCt2Monomial(sf*p[0],&f);
	  
	  AddMonomial(&f,&(eq[j]));
	  ResetMonomial(&f);
	}
	  
      free(vname);
    }
  DeleteMonomial(&f);
}

void ApplyLinkRotDeformX(Tparameters *pr,double sf,unsigned int sv,double *p,Tequation *eq,
			 TCuikSystem *cs,boolean groundLink,Tlink *l)
{
  Tmonomial f;
  unsigned int j;
  unsigned int linkVars[4]; 
  char *vname;
      
  /*
    sf*sv*T(px 0 0) where T is defined from the linkVars (check that hasVars==TRUE) 
    T only has x component
  */
  if (Norm(2,&(p[1]))>ZERO)
    Error("Deform X only links can only be used on points on the X-axis");

  NEW(vname,strlen(l->name)+100,char);
  LINK_LENGTH(vname,l->name);
  linkVars[3]=GetCSVariableID(vname,cs);
  if (linkVars[3]==NO_UINT)
    Error("Undefined reference variable in ApplyLinkRotDeformX");
  
  InitMonomial(&f);
  if (groundLink)
    {
      if (sv!=NO_UINT)
	AddVariable2Monomial(NFUN,sv,1,&f);
      AddVariable2Monomial(NFUN,linkVars[3],1,&f);
      AddCt2Monomial(sf*p[0],&f);
      
      AddMonomial(&f,&(eq[0]));
      ResetMonomial(&f);
    }
  else
    {
      for(j=0;j<3;j++)
	{
	  LINK_ROT(vname,l->name,0,j);
	  linkVars[j]=GetCSVariableID(vname,cs);
	  if (linkVars[j]==NO_UINT)
	    Error("Undefined reference variable in ApplyLinkRotDeformX");
	}
  
      for(j=0;j<3;j++)
	{
	  AddVariable2Monomial(NFUN,linkVars[j],1,&f);
	  if (sv!=NO_UINT)
	    AddVariable2Monomial(NFUN,sv,1,&f);
	  AddVariable2Monomial(NFUN,linkVars[3],1,&f);
	  AddCt2Monomial(sf*p[0],&f);
	  
	  AddMonomial(&f,&(eq[j]));
	  ResetMonomial(&f);
	}
    }
  free(vname);
  DeleteMonomial(&f);
}

void ApplyLinkRotFLinks(double sf,unsigned int sv,double *p,Tequation *eq,
			TCuikSystem *cs,boolean groundLink,Tlink *l)
{
  /*
  sf*sv*R*T(px py px) where T is defined from the linkVars (check that hasVars==TRUE) 
  */
  
  Tmonomial f;
  unsigned int i;

  InitMonomial(&f);
  if (groundLink)
    {
      for(i=0;i<3;i++)
	{ 
	  if (sv!=NO_UINT)
	    AddVariable2Monomial(NFUN,sv,1,&f);
	  AddCt2Monomial(sf*p[i],&f);
	  
	  AddMonomial(&f,&(eq[i]));
	  ResetMonomial(&f);
	}
    }
  else
    {
      unsigned int j;
      unsigned int linkVars[9]; 
      char *vname;
      double pInt[3];

      HTransformApply(p,pInt,&(l->R));

      NEW(vname,strlen(l->name)+100,char);

      for(i=0;i<3;i++) /* vector */
	{
	  for(j=0;j<3;j++) /* component */
	    {
	      LINK_ROT(vname,l->name,i,j);
	      linkVars[i*3+j]=GetCSVariableID(vname,cs);
	      if (linkVars[i*3+j]==NO_UINT)
		Error("Undefined reference variable in ApplyLinkRotFLinks");
	    }
	}
  
      for(i=0;i<3;i++) /* component (row) */
	{
	  for(j=0;j<3;j++) /* vector (column) */
	    {
	      if (fabs(pInt[j])>ZERO)
		{
		  AddVariable2Monomial(NFUN,linkVars[j*3+i],1,&f);
		  if (sv!=NO_UINT)
		    AddVariable2Monomial(NFUN,sv,1,&f);
		  AddCt2Monomial(sf*pInt[j],&f);
		  
		  AddMonomial(&f,&(eq[i]));
		  ResetMonomial(&f);
		}
	    }
	}
      free(vname);
    }
  DeleteMonomial(&f);
}

void ApplyLinkRotLinks(double sf,unsigned int sv,double *p,Tequation *eq,
		       TCuikSystem *cs,boolean groundLink,Tlink *l)
{
  /*
  sf*sv*R*T(px py px) where T is defined from the linkVars (check that hasVars==TRUE) 
  */
  
  Tmonomial f;

  InitMonomial(&f);
  if (groundLink)
    {
      unsigned int i;

      for(i=0;i<3;i++)
	{
	  if (sv!=NO_UINT)
	    AddVariable2Monomial(NFUN,sv,1,&f);
	  AddCt2Monomial(sf*p[i],&f);
	  
	  AddMonomial(&f,&(eq[i]));
	  ResetMonomial(&f);
	}
    }
  else
    {
      unsigned int i,j,n;
      unsigned int linkVars[12]; 
      char *vname;
      double pInt[3];

      HTransformApply(p,pInt,&(l->R));

      NEW(vname,strlen(l->name)+100,char);
      
      for(i=0;i<4;i++) /*vector*/
	{
	  for(j=0;j<3;j++) /*component*/
	    {
	      LINK_ROT2(vname,l->name,i,j);
	      n=i*3+j;
	      linkVars[n]=GetCSVariableID(vname,cs);
	      if (linkVars[n]==NO_UINT)
		Error("Undefined reference variable in ApplyLinkRotPM");
	    }
	}

      for(i=0;i<3;i++) /*row = component */
	{
	  for(j=0;j<4;j++) /*column = vector */
	    {
	      if (fabs(pInt[(j<2?j:2)])>ZERO)
		{
		  AddVariable2Monomial(NFUN,linkVars[j*3+i],1,&f);
		  if (sv!=NO_UINT)
		    AddVariable2Monomial(NFUN,sv,1,&f);
		  AddCt2Monomial((j==3?-1:1)*sf*pInt[(j<2?j:2)],&f);
		  
		  AddMonomial(&f,&(eq[i]));
		  ResetMonomial(&f);
		}
	    }
	}

      free(vname);
    }
  DeleteMonomial(&f);  
}

void ApplyLinkRotQLinks(double sf,unsigned int sv,double *p,Tequation *eq,
			TCuikSystem *cs,boolean groundLink,Tlink *l)
{
  /*
  sf*sv*R*T(px py px) where T is defined from the linkVars (check that hasVars==TRUE) 
  (R=Id for quaternions -> not used)
  */
  Tmonomial f;
  unsigned int i;

  /*Note that quaternions asume an orthonormal rotation matrix (i.e., we do not allow
    the change of the link reference)*/
 
  InitMonomial(&f);
  if (groundLink)
    {
      unsigned int j;
      /* Replace id by anoher matrix if necessary */
      double id[3][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0}};
      double ct;

      for(i=0;i<3;i++) /* row */
	{ 
	  ct=0.0;
	  for(j=0;j<3;j++) /* column */
	    ct+=id[i][j]*p[j];

	  if (sv!=NO_UINT)
	    AddVariable2Monomial(NFUN,sv,1,&f);
	  AddCt2Monomial(sf*ct,&f);
	  
	  AddMonomial(&f,&(eq[i]));
	  ResetMonomial(&f);
	}
    }
  else
    {
      unsigned int i,j,n;
      unsigned int linkVars[10]; 
      char *vname;
      
      /* indices of the two 'e' variables that define each
         element in the rotation matrix */
      unsigned int map[2][3][3]={
	{{7,5,6},
	 {5,4,8},
	 {6,8,4}},
        {{9,3,2},
	 {3,9,1},
	 {2,1,7}}};
      /* sign for each of the two 'e' variables that define
         each element of the rotation matrix. */
      double sg[2][3][3]={
	{{-1.0,+1.0,+1.0}, /* fist variable is alwoys + but for the diagonal */
	 {+1.0,-1.0,+1.0},
	 {+1.0,+1.0,-1.0}},
	{{-1.0,-1.0,+1.0},
	 {+1.0,-1.0,-1.0},
	 {-1.0,+1.0,-1.0}}};
      
      /*
	The rotation matrix is
	1-2*c^2-2*d^2       2*b*c-2*a*d      2*b*d+2*a*c
         2*b*c+2*a*d       1-2*b^2-2*d^2     2*c*d-2*a*b
         2*b*d-2*a*c        2*c*d+2*a*b     1-2*b^2-2*c^2

	1-2*e_2_2-2*e_3_3       2*e_1_2-2*e_0_3      2*e_1_3+2*e_0_2
         2*e_1_2+2*e_0_3       1-2*e_1_1-2*e_3_3     2*e_2_3-2*e_0_1
         2*e_1_3-2*e_0_2        2*e_2_3+2*e_0_1     1-2*e_1_1-2*e_2_2

	1-2*v[7]-2*v[9]       2*v[5]-2*v[3]      2*v[6]+2*v[2]
         2*v[5]+2*v[3]       1-2*v[4]-2*v[9]     2*v[8]-2*v[1]
         2*v[6]-2*v[2]        2*v[8]+2*v[1]     1-2*v[4]-2*v[7]

       */
      NEW(vname,strlen(l->name)+100,char);

      n=0;
      for(i=0;i<4;i++)
	{ 
	  for(j=i;j<4;j++)
	    {
	      LINK_ROT3_E(vname,l->name,i,j);
	      linkVars[n]=GetCSVariableID(vname,cs);
	      if (linkVars[n]==NO_UINT)
		Error("Undefined reference variable in ApplyLinkRot");
	      n++;
	    }
	}

      /* The ones in the diagonal */
      for(i=0;i<3;i++)
	{
	   if (sv!=NO_UINT)
	     AddVariable2Monomial(NFUN,sv,1,&f);
	   AddCt2Monomial(sf*p[i],&f);

	  AddMonomial(&f,&(eq[i]));
	  ResetMonomial(&f);
	}

      for(n=0;n<2;n++) /* each rotation matix is the result of operation to 'e' variables */
	{
	  for(i=0;i<3;i++) /*row*/
	    {
	      for(j=0;j<3;j++) /*column*/
		{
		  if (fabs(p[j])>ZERO)
		    {
		      AddVariable2Monomial(NFUN,linkVars[map[n][i][j]],1,&f);
		      if (sv!=NO_UINT)
			AddVariable2Monomial(NFUN,sv,1,&f);
		      AddCt2Monomial(2.0*sg[n][i][j]*sf*p[j],&f);
		      
		      AddMonomial(&f,&(eq[i]));
		      ResetMonomial(&f);
		    }
		}
	    }
	}

      free(vname);
    }
  DeleteMonomial(&f);  
}

void ApplyLinkRotVar(Tparameters *pr,double sf,unsigned int *vID,Tequation *eq,
		     TCuikSystem *cs,boolean groundLink,Tlink *l)
{
  unsigned int r;

  if (l->type==LINK_Connect)
    Error("ApplyLinkRotVar is not defined in connection links");
  
  r=(unsigned int)(GetParameter(CT_REPRESENTATION,pr));
  if ((r!=REP_JOINTS)&&(fabs(sf)>ZERO))
    {
      Tequation u[3],v[3],w[3];
      unsigned int i,j;
      double ct[3]={1,0,0};
	  
      switch(l->type)
	{
	case LINK_AxisX:
	  if (((vID[1]!=NO_UINT)||(vID[2]!=NO_UINT)))
	    Error("ApplyLinkRotVar only works on points on X for Axis_X links");
	      
	  for(i=0;i<3;i++)
	    InitEquation(&(u[i]));
	      
	  for(i=0;i<3;i++)
	    ApplyLinkRot(pr,sf,NO_UINT,ct,u,cs,groundLink,l);
	  
	  for(i=0;i<3;i++)
	    VarAccumulateEquations(&(u[i]),vID[0],&(eq[i]));
	      
	  for(i=0;i<3;i++)
	    DeleteEquation(&(u[i]));
	  break;
	case LINK_DeformX:
	case LINK_PrismaticX:
	  {
	    unsigned int lvID[MAX_ROT_VARS];
	 
	    if (((vID[1]!=NO_UINT)||(vID[2]!=NO_UINT)))
	      Error("ApplyLinkRotVar only works on points on X for Deform_X links");

	    for(i=0;i<3;i++)
	      InitEquation(&(u[i]));
	  
	    /* ensure that no one accessing the link information
	       in parallel invalidates the cache while we use it*/
	  
	    for(i=0;i<3;i++)
	      ApplyLinkRot(pr,sf,NO_UINT,ct,u,cs,groundLink,l);
	  
	    GetRotVarID(r,cs,lvID,l);
	    for(i=0;i<3;i++)
	      {
		VarScaleEquation(lvID[3],&(u[i])); /* deformation parameter */
		VarAccumulateEquations(&(u[i]),vID[0],&(eq[i]));
	      }
	    for(i=0;i<3;i++)
	      DeleteEquation(&(u[i]));
	  }
	  break;
	case LINK_FullRot:
	  for(i=0;i<3;i++)
	    {
	      InitEquation(&(u[i]));
	      InitEquation(&(v[i]));
	      InitEquation(&(w[i]));
	    }
	  /* We have to compute M*R*[vID]
	     M=matrix given by the link variables (=M*iR) 
	     R=Basis change
	     vID=given variable vector 
	     This is computed as (M*R)*[vID] 
	     First [u v w]=M*R  
	     u=M*R_1  (first column or R)
	     v=M*R_2  (second column or R)
	     w=M*R_3  (third column or R)
	     and then [u v w]*[vID] -> linear combination of u,v,w 
	  */
	  /*  For LINK_AxisX links R is the identity.  */
	  for(i=0;i<3;i++)
	    {
	      for(j=0;j<3;j++)
		ct[j]=l->R[j][i];
	      ApplyLinkRot(pr,sf,NO_UINT,ct,(i==0?u:(i==1?v:w)),cs,groundLink,l);
	    }
	  
	  for(i=0;i<3;i++)
	    {
	      VarAccumulateEquations(&(u[i]),vID[0],&(eq[i]));
	      VarAccumulateEquations(&(v[i]),vID[1],&(eq[i]));
	      VarAccumulateEquations(&(w[i]),vID[2],&(eq[i]));
	    }
	  for(i=0;i<3;i++)
	    {
	      DeleteEquation(&(u[i]));
	      DeleteEquation(&(v[i]));
	      DeleteEquation(&(w[i]));
	    }
	  break;
	case LINK_NoRot:
	  break;
	default:
	  Error("Unkown link type in ApplyLinkRotVar");
	}
    }
}

void RegenerateLinkSolution(Tparameters *p,TCuikSystem *cs,double *sol,
			    boolean groundLink,Tlink *l)
{
  unsigned int r;
  
  /* in joints all variables are system */
  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r!=REP_JOINTS)
    {
      if (l->type==LINK_FullRot) /* NoRot, AxisX, DeformX and Connect links do not need 
				    regeneration (don't generate dummy variables) */
	{
	  switch(r)
	    {
	    case REP_LINKS:
	      RegenerateLinkSolutionLinks(r,cs,sol,groundLink,l);
	      break;
	    case REP_FLINKS:
	      /* When using 9 variables all variables used to represent the
		 rotation of the link are system variables and, thus, no
		 dummy has to be computed.*/
	      break;
	    case REP_QLINKS:
	      RegenerateLinkSolutionQLinks(r,cs,sol,groundLink,l);
	      break;
	    default:
	      Error("Undefined representation type in RegenerateLinkSolution");
	    }
	}
      RegenerateLinkSolutionConf(r,cs,sol,l);
    }
}

void RegenerateLinkSolutionConf(unsigned int r,TCuikSystem *cs,double *sol,Tlink *l)
{
  /* nothing need to be done (all internal conf. variables, if any, are already system variables) */
}

void RegenerateLinkSolutionLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,Tlink *l)
{
  if (!groundLink)
    {
      unsigned int vID[MAX_ROT_VARS];
      
      GetRotVarID(r,cs,vID,l);
      
      /* compute w and wp from u and v (recall that u X v = s*(w - wp) )*/
      sol[vID[6]]=sol[vID[1]]*sol[vID[5]]/l->s;
      sol[vID[7]]=sol[vID[2]]*sol[vID[3]]/l->s;
      sol[vID[8]]=sol[vID[0]]*sol[vID[4]]/l->s;

      sol[vID[9]] =sol[vID[2]]*sol[vID[4]]/l->s;
      sol[vID[10]]=sol[vID[0]]*sol[vID[5]]/l->s;
      sol[vID[11]]=sol[vID[1]]*sol[vID[3]]/l->s;
    }
}

void RegenerateLinkSolutionQLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,Tlink *l)
{
  if (!groundLink)
    {
      unsigned int i,j,n;
      double qVars[4];
      unsigned int vID[MAX_ROT_VARS];
      
      GetRotVarID(r,cs,vID,l);

      for(j=0;j<4;j++)
	qVars[j]=sol[vID[j]];

      n=4;
      for(i=0;i<4;i++)
	{
	  for(j=i;j<4;j++)
	    {
	      sol[vID[n]]=qVars[i]*qVars[j];
	      n++;
	    }
	}
    }
}

void RegenerateLinkBox(Tparameters *p,TCuikSystem *cs,Tbox *b,
		       boolean groundLink,Tlink *l)
{
  unsigned int r;
  
  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r!=REP_JOINTS)
    {
      if (l->type==LINK_FullRot) /* NoRot, AxisX, DeformX, and Connect links do not need
				    regeneration (don't generate dummy variables) */
	{
	  unsigned int r;

	  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
	  switch(r)
	    {
	    case REP_LINKS:
	      RegenerateLinkBoxLinks(r,cs,b,groundLink,l);
	      break;
	    case REP_FLINKS:
	      /* When using 9 variables all variables used to represent the
		 rotation of the link are system variables and, thus, no
		 dummy has to be computed.*/
	      break;
	    case REP_QLINKS:
	      RegenerateLinkBoxQLinks(r,cs,b,groundLink,l);
	      break;
	    default:
	      Error("Undefined representation type in RegenerateLinkBox");
	    }
	}
      RegenerateLinkBoxConf(r,cs,b,l);
    }
}

void RegenerateLinkBoxConf(unsigned int r,TCuikSystem *cs,Tbox *b,Tlink *l)
{
  /* nothing need to be done (all internal conf. variables, if any, are already system variables) */
}

void RegenerateLinkBoxLinks(unsigned int r,TCuikSystem *cs,Tbox *b,boolean groundLink,Tlink *l)
{
  if (!groundLink)
    {
      Tinterval range,*is;
      unsigned int vID[MAX_ROT_VARS];
            
      GetRotVarID(r,cs,vID,l);

      is=GetBoxIntervals(b);

      /* compute w and wp from u and v (recall that u X v = s*(w - wp)) */
      IntervalProduct(&(is[vID[1]]),&(is[vID[5]]),&range);
      IntervalScale(&range,1/l->s,&range);
      SetBoxInterval(vID[6],&range,b);

      IntervalProduct(&(is[vID[2]]),&(is[vID[3]]),&range);
      IntervalScale(&range,1/l->s,&range);
      SetBoxInterval(vID[7],&range,b);

      IntervalProduct(&(is[vID[0]]),&(is[vID[4]]),&range);
      IntervalScale(&range,1/l->s,&range);
      SetBoxInterval(vID[8],&range,b);

      IntervalProduct(&(is[vID[2]]),&(is[vID[4]]),&range);
      IntervalScale(&range,1/l->s,&range);
      SetBoxInterval(vID[9],&range,b);

      IntervalProduct(&(is[vID[0]]),&(is[vID[5]]),&range);
      IntervalScale(&range,1/l->s,&range);
      SetBoxInterval(vID[10],&range,b);

      IntervalProduct(&(is[vID[1]]),&(is[vID[3]]),&range);
      IntervalScale(&range,1/l->s,&range);
      SetBoxInterval(vID[11],&range,b);
    }
}

void RegenerateLinkBoxQLinks(unsigned int r,TCuikSystem *cs,Tbox *b,boolean groundLink,Tlink *l)
{
 if (!groundLink)
   {
     unsigned int i,j,n;
     Tinterval qVars[4];
     Tinterval range;
     unsigned int vID[MAX_ROT_VARS];
      
     GetRotVarID(r,cs,vID,l);

     for(j=0;j<4;j++)
       CopyInterval(&(qVars[j]),GetBoxInterval(vID[j],b));

     n=4;
     for(i=0;i<4;i++)
       {
	 for(j=i;j<4;j++)
	   {
	     IntervalProduct(&(qVars[i]),&(qVars[j]),&range);
	     SetBoxInterval(vID[n],&range,b);
	     n++;
	   }
       }
   }
}

void GetTransform2Link(Tparameters *p,TCuikSystem *cs,double *sol,
		       boolean groundLink,double *trans,THTransform *t,
		       TLinkConf *def,Tlink *l)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r!=REP_JOINTS)
    { 
      switch(l->type)
	{
	case LINK_AxisX:
	case LINK_DeformX:
	case LINK_PrismaticX:
	  GetTransform2LinkAxisX(r,cs,sol,groundLink,trans,t,l);
	  break;
	case LINK_FullRot:
	  switch(r)
	    {
	    case REP_LINKS:
	      GetTransform2LinkLinks(r,cs,sol,groundLink,trans,t,l);
	      break;
	    case REP_FLINKS:
	      GetTransform2LinkFLinks(r,cs,sol,groundLink,trans,t,l);
	      break;
	    case REP_QLINKS:
	      GetTransform2LinkQLinks(r,cs,sol,groundLink,trans,t,l);
	      break;
	    default:
	      Error("Undefined representation type in GetTransform2Link");
	    }
	  break;
	case LINK_NoRot:
	  HTransformTxyz(trans[0],trans[1],trans[2],t);
	  break;
	case LINK_Connect:
	  Error("GetTransform2Link not defined for connection links. Use GetTransform2ConnectionLink");
	  break;
	default:
	  Error("Unkown link type in GetTransform2Link");
	}
      
      GetLinkConfFromSolution(r,cs,sol,def,l);
    }
}

void GetTransform2ConnectionLink(THTransform *tl,THTransform *t,TLinkConf *def,Tlink *l)
{
  if (l->type==LINK_Connect)
    {
      double pt1[3],pt2[3];
      double u[3],v[3],w[3];
      double le;
      unsigned int i;

      HTransformApply(l->p1,pt1,&(tl[l->l1]));
      HTransformApply(l->p2,pt2,&(tl[l->l2]));

      DifferenceVector(3,pt2,pt1,u);
      le=Norm(3,u);
      Normalize(3,u);
      DefineNormalVector(v,u);
      CrossProduct(u,v,w);
      
      HTransformIdentity(t);
      for(i=0;i<3;i++)
	{
	  HTransformSetElement(i,AXIS_X,u[i]*le,t); /* deformation along X */
	  HTransformSetElement(i,AXIS_Y,v[i],t);
	  HTransformSetElement(i,AXIS_Z,w[i],t);
	  HTransformSetElement(i,AXIS_H,pt1[i],t);
	}

      /* connection links do not have link configuration */
      def->l=l;
      def->ndp=0;
      def->p=NULL;
    }
  else
    Error("GetTransform2ConnectionLink not defined for non-connect links. Use GetTransform2Link");
}

void GetConnectionLinkWrench(THTransform *tl,double *wr1,double *wr2,Tlink *l)
{
  if (l->type==LINK_Connect)
    {
      memset(wr1,0,sizeof(double)*6);
      memset(wr2,0,sizeof(double)*6);
      
      if (IsConnectionSpring(l))
	{
	  double pt1[3],pt2[3];
	  double u[3];
	  double d,f;

	  /* Get the global coordinates of the attach points */
	  HTransformApply(l->p1,pt1,&(tl[l->l1]));
	  HTransformApply(l->p2,pt2,&(tl[l->l2]));

	  /* u points from pt1 to pt2 */
	  DifferenceVector(3,pt2,pt1,u);

	  /*
	  PrintVector(stderr,"pt1",3,pt1);
	  PrintVector(stderr,"pt2",3,pt2);
	  PrintVector(stderr,"vf",3,u);
	  */
	  
	  /* Compute the force using Hooke's law */
	  d=Norm(3,u);
	  f=(d-IntervalCenter(&(l->rest)))*l->stiffness;
	  
	  /* Set the magnitude of 'u' to the force */
	  ScaleVector(f/d,3,u);

	  /* Compute the wrenches!!!  */
	  CrossProduct(pt1,u,wr1); /* torque depents on the applied point (in global coordinates) */
	  wr1[3]=u[0];
	  wr1[4]=u[1];
	  wr1[5]=u[2];	 
	  
	  /* The torque at the second attachment point is the same but with opposite sign */
	  CrossProduct(u,pt2,wr2);
	  wr2[3]=-u[0];
	  wr2[4]=-u[1];
	  wr2[5]=-u[2];
	} 
    }
  else
    Error("GetConnectionLinkWrench only works on connection links"); 
}


double GetConnectionLinkPotentialEnergy(THTransform *tl,Tlink *l)
{
  double e;

  e=0;
  
  if ((l->type==LINK_Connect)&&(IsConnectionSpring(l)))
    { 
      double pt1[3],pt2[3];
      double u[3];
      double d;

      /* Get the global coordinates of the attach points */
      HTransformApply(l->p1,pt1,&(tl[l->l1]));
      HTransformApply(l->p2,pt2,&(tl[l->l2]));

      /* u points from pt1 to pt2 */
      DifferenceVector(3,pt2,pt1,u);
	  
      /* Compute the force using Hooke's law */
      d=(Norm(3,u)-IntervalCenter(&(l->rest))); /* displacement w.r.t. rest length */

      e=0.5*l->stiffness*d*d;
    }

  return(e);
}

void GetTransform2LinkAxisX(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,
			    double *trans,THTransform *t,Tlink *l)
{
  if (groundLink)
    HTransformIdentity(t);
  else
    {
      unsigned int i;
      double u[3],v[3],w[3];
      unsigned int vID[MAX_ROT_VARS];
            
      GetRotVarID(r,cs,vID,l);

      /* We only have the X vector and, thus, we define an arbitrary, but
	 correct reference system */
      for(i=0;i<3;i++)
	{
	  u[i]=sol[vID[i]];
	  if (fabs(u[i])<ZERO) u[i]=0.0;
	}
      Normalize(3,u);
      
      DefineNormalVector(v,u);
      CrossProduct(u,v,w);

      HTransformIdentity(t);
      for(i=0;i<3;i++)
	{
	  HTransformSetElement(i,AXIS_X,u[i],t);
	  HTransformSetElement(i,AXIS_Y,v[i],t);
	  HTransformSetElement(i,AXIS_Z,w[i],t);
	  HTransformSetElement(i,AXIS_H,trans[i],t);
	}
    }
}

void GetTransform2LinkFLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,
			     double *trans,THTransform *t,Tlink *l)
{
  if (groundLink)
    HTransformIdentity(t);
  else
    {
      unsigned int i,j;
      unsigned int vID[MAX_ROT_VARS];
      
      GetRotVarID(r,cs,vID,l);

      HTransformIdentity(t);

      /* Define the homogeneous transform using the rotation and the translation.*/
      for(i=0;i<3;i++)
	{
	  HTransformSetElement(i,AXIS_H,trans[i],t);
	  for(j=0;j<3;j++)
	    HTransformSetElement(i,j,sol[vID[i+j*3]],t);
	}
      
      /* The link variables representing the link rotation encode
	 M*iR
	 M = orthonormal rotation matrix
	 iR= basis change to obtain a more numerically safe basis
	 The orthonormal matrix is obtained by multiplying
	 (M*iR)*R

	 See ChangeLinkReferenceFrame
      */
      HTransformProduct(t,&(l->R),t);
      /* This ensures that the transformation is actually rigid 
	 (fixes numerical errors and the error of taking the center
	 of the solution box as a proper solution) */
      HTransformOrthonormalize(t,t);
    }
}

void GetTransform2LinkLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,
			    double *trans,THTransform *t,Tlink *l)
{
  if (groundLink)
    HTransformIdentity(t);
  else
    {
      unsigned int i,j;
      unsigned int vID[MAX_ROT_VARS];
            
      GetRotVarID(r,cs,vID,l);
      
      /* Define the homogeneous transform using the rotation and the translation.*/
      HTransformIdentity(t);
      for(i=0;i<3;i++) /* component */
	{
	  HTransformSetElement(i,AXIS_H,trans[i],t);
	  for(j=0;j<3;j++) /* vector */
	    { 
	      if (j<2)
		HTransformSetElement(i,j,sol[vID[i+j*3]],t);
	      else
		HTransformSetElement(i,j,(sol[vID[i+j*3]]-sol[vID[i+(j+1)*3]]),t);
	    }
	}
      
      /* The link variables representing the link rotation encode
	 M*iR
	 M = orthonormal rotation matrix
	 iR= basis change to obtain a more numerically safe basis
	 The orthonormal matrix is obtained by multiplying
	 (M*iR)*R

	 See ChangeLinkReferenceFrame
      */
      HTransformProduct(t,&(l->R),t);  
      /* This ensures that the transformation is actually rigid
	 (fixes numerical errors and the error of taking the center
	 of the solution box as a proper solution) */   
      HTransformOrthonormalize(t,t);
    }
}


void GetTransform2LinkQLinks(unsigned int r,TCuikSystem *cs,double *sol,boolean groundLink,
			     double *trans,THTransform *t,Tlink *l)
{ 
  if (groundLink)
    HTransformIdentity(t);
  else
    {
      double e[4][4]; /* only the upper half is used */
      unsigned int i,j,n;
      unsigned int vID[MAX_ROT_VARS];
            
      GetRotVarID(r,cs,vID,l);

      n=4;
      for(i=0;i<4;i++)
	{
	  for(j=i;j<4;j++)
	    {
	      e[i][j]=2*sol[vID[n]];
	      n++;
	    }
	}
      
      /* Define the homogeneous transform using the rotation and the translation.*/
      HTransformIdentity(t);
     
      HTransformSetElement(0,0,1-e[2][2]-e[3][3],t);
      HTransformSetElement(0,1,  e[1][2]+e[0][3],t);
      HTransformSetElement(0,2,  e[1][3]-e[0][2],t);
      HTransformSetElement(0,3,trans[0],t);

      HTransformSetElement(1,0,  e[1][2]-e[0][3],t);
      HTransformSetElement(1,1,1-e[1][1]-e[3][3],t);
      HTransformSetElement(1,2,  e[2][3]+e[0][1],t);
      HTransformSetElement(1,3,trans[1],t);

      HTransformSetElement(2,0,  e[1][3]+e[0][2],t);
      HTransformSetElement(2,1,  e[2][3]-e[0][1],t);
      HTransformSetElement(2,2,1-e[1][1]-e[2][2],t);
      HTransformSetElement(2,3,trans[2],t);
      
      /* No basis change (R) is used in Quaternion representation */

      /* This ensures that the transformation is actually rigid */
      HTransformOrthonormalize(t,t);
    }
}

void GenerateLinkSolution(Tparameters *p,THTransform *t,TLinkConf *def,
			  TCuikSystem *cs,double *sol,boolean groundLink,Tlink *l)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r!=REP_JOINTS)
    {
      switch(l->type)
	{
	case LINK_AxisX:
	case LINK_DeformX:
	case LINK_PrismaticX:
	  GenerateLinkSolutionAxisX(r,t,cs,sol,groundLink,l);
	  break;
	case LINK_FullRot:
	  switch(r)
	    {
	    case REP_LINKS:
	      GenerateLinkSolutionLinks(r,t,cs,sol,groundLink,l);
	      break;
	    case REP_FLINKS:
	      GenerateLinkSolutionFLinks(r,t,cs,sol,groundLink,l);
	      break;
	    case REP_QLINKS:
	      GenerateLinkSolutionQLinks(r,t,cs,sol,groundLink,l);
	      break;
	    default:
	      Error("Undefined representation type in GenerateLinkSolution");
	    }
	  break;
	case LINK_NoRot:
	case LINK_Connect:
	  break;
	default:
	  Error("Unknown link type in GenerateLinkSolution");
	}
      
      GenerateSolutionFromLinkConf(r,cs,def,sol,l);
    }
}

void GenerateLinkSolutionAxisX(unsigned int r,THTransform *t,TCuikSystem *cs,
			       double *sol,boolean groundLink,Tlink *l)
{
  if (!groundLink)
    {
      unsigned int j;
      unsigned int vID[MAX_ROT_VARS];
            
      GetRotVarID(r,cs,vID,l);

      for(j=0;j<3;j++) 
	sol[vID[j]]=HTransformGetElement(j,0,t);
    }
}

void GenerateLinkSolutionFLinks(unsigned int r,THTransform *t,TCuikSystem *cs,
				double *sol,boolean groundLink,Tlink *l)
{
  if (!groundLink)
    {
      THTransform it;
      unsigned int i,j,n;
      unsigned int vID[MAX_ROT_VARS];
      
      /* The link variables encode (M*iR) and the given 't' is only M */
      HTransformProduct(t,&(l->iR),&it);
	         
      GetRotVarID(r,cs,vID,l);
      
      n=0;
      for(i=0;i<3;i++) /*vector*/
	{ 
	  for(j=0;j<3;j++) /*component*/
	    {
	      sol[vID[n]]=HTransformGetElement(j,i,&it);
	      n++;
	    }
	}
      HTransformDelete(&it);
    }
}

void GenerateLinkSolutionLinks(unsigned int r,THTransform *t,TCuikSystem *cs,
			       double *sol,boolean groundLink,Tlink *l)
{
  if (!groundLink)
    {
      THTransform it;
      unsigned int i,j,n;
      unsigned int vID[MAX_ROT_VARS];
      
      /* The link variables encode (M*iR) and the given 't' is only M */
      HTransformProduct(t,&(l->iR),&it);
      	       
      GetRotVarID(r,cs,vID,l);
      
      n=0;
      for(i=0;i<2;i++) /*vector*/
	{ 
	  for(j=0;j<3;j++) /*componet*/
	    {
	      sol[vID[n]]=HTransformGetElement(j,i,&it);
	      n++;
	    }
	}
      HTransformDelete(&it);

      RegenerateLinkSolutionLinks(r,cs,sol,groundLink,l);
    }
}

void GenerateLinkSolutionQLinks(unsigned int r,THTransform *t,TCuikSystem *cs,
				double *sol,boolean groundLink,Tlink *l)
{  
  if (!groundLink)
    {
      double u,s,q;
      unsigned int vID[MAX_ROT_VARS];
            
      GetRotVarID(r,cs,vID,l);
	
      /* Recover the 4 quaternion elements from the transformation
	 matrix*/ 
      q=HTransformGetElement(0,0,t)+
	HTransformGetElement(1,1,t)+
	HTransformGetElement(2,2,t); 
      u=sqrt(1.0+q);
      s=0.5/u;

      sol[vID[0]]=0.5*u;
      sol[vID[1]]=(HTransformGetElement(2,1,t)-HTransformGetElement(1,2,t))*s;
      sol[vID[2]]=(HTransformGetElement(0,2,t)-HTransformGetElement(2,0,t))*s;
      sol[vID[3]]=(HTransformGetElement(1,0,t)-HTransformGetElement(0,1,t))*s;

      RegenerateLinkSolutionQLinks(r,cs,sol,groundLink,l);
    }
}

boolean IsConnectionCable(Tlink *l)
{
  return((l->type==LINK_Connect)&&
	 (LinkNBodies(l)==1)&&
	 (GetPolyhedronType(GetLinkBody(0,l))==CYLINDER));
}

boolean IsConnectionSpring(Tlink *l)
{
  return((l->type==LINK_Connect)&&
	 (LinkNBodies(l)>=1)&&
	 (GetPolyhedronType(GetLinkBody(0,l))==SEGMENTS));
}

boolean IsConnectionLeg(Tlink *l)
{
  return((l->type==LINK_Connect)&&
	 (LinkNBodies(l)==3)&&
	 (GetPolyhedronType(GetLinkBody(0,l))==SPHERE)&&
	 (GetPolyhedronType(GetLinkBody(1,l))==CYLINDER)&&
	 (GetPolyhedronType(GetLinkBody(2,l))==SPHERE));
}

unsigned int GetConnectLinkFrom(Tlink *l)
{
  if (l->type!=LINK_Connect)
    Error("GetConnectLinkFrom is only defined for connection links");

  return(l->l1);
}

unsigned int GetConnectLinkTo(Tlink *l)
{
  if (l->type!=LINK_Connect)
    Error("GetConnectLinkTo is only defined for connection links");

  return(l->l2);
}

void GetConnectLinkPointFrom(double *p,Tlink *l)
{
  unsigned int i;
  
  if (l->type!=LINK_Connect)
    Error("GetConnectLinkPointFrom is only defined for connection links");
  
  for(i=0;i<3;i++)
    p[i]=l->p1[i];
}

void GetConnectLinkPointTo(double *p,Tlink *l)
{
  unsigned int i;
  
  if (l->type!=LINK_Connect)
    Error("GetConnectLinkPointTo is only defined for connection links");
  
  for(i=0;i<3;i++)
    p[i]=l->p2[i];
}

boolean VisibleLink(Tlink *l)
{
  /* A visible link is a link with at least one visible body */
  boolean found;

  found=FALSE;

  if (l->type!=LINK_NoRot)
    {
      unsigned int i,n; 

      n=LinkNBodies(l);
  
      for(i=0;((i<n)&&(!found));i++)
	found=(GetPolyhedronStatus(GetLinkBody(i,l))!=HIDDEN_SHAPE);
    }
  return(found);
}

double GetLinkMaxCoordinate(Tlink *l)
{
  return(l->maxCoord);
}

void LinkPrintAtoms(FILE *f,THTransform *tl,Tlink *l)
{
  unsigned int i,m;
  Tpolyhedron *bd;

  m=LinkNBodies(l);

  if ((m>0)&&(VisibleLink(l)))
    {
      for(i=0;i<m;i++)
	{
	  bd=GetLinkBody(i,l);
	  PolyhedronPrintCenter(f,tl,bd);
	}
    }
}

void LinkStoreAtoms(FILE *f,THTransform *tl,Tlink *l)
{
  unsigned int i,m;
  Tpolyhedron *bd;

  m=LinkNBodies(l);

  if ((m>0)&&(VisibleLink(l)))
    {
      for(i=0;i<m;i++)
	{
	  bd=GetLinkBody(i,l);
	  PolyhedronPrintCenterAndRadius(f,tl,bd);
	}
    }
}

void PlotLink(Tplot3d *pt,double axesLength,Tlink *l)
{
  unsigned int n,i;

  n=LinkNBodies(l);

  if ((n>0)&&(VisibleLink(l)))
    {
      for(i=0;i<n;i++)
	PlotPolyhedron(pt,GetLinkBody(i,l));
    }
  
  /* default no axis shown */
  for(i=0;i<3;i++)
    l->axisID[i]=NO_UINT;
  
  if (axesLength>0)
    {
      double points[3][2]={{0,0},{0,0},{0,0}};
      Tcolor axesColor;

      for(i=0;i<((l->type!=LINK_AxisX)&&(l->type!=LINK_DeformX)&&(l->type!=LINK_PrismaticX)&&(l->type!=LINK_Connect)?3:1);i++)
	{
	  NewColor((i==0?1:0),(i==1?1:0),(i==2?1:0),&axesColor);
	  l->axisID[i]=StartNew3dObject(&axesColor,pt);
	  DeleteColor(&axesColor);

	  points[i][1]=axesLength;
	  PlotVect3d(2,points[0],points[1],points[2],pt);
	  points[i][1]=0;

	  Close3dObject(pt);
	}
    }
}

void MoveLinkFromTransform(Tplot3d *pt,THTransform *t,TLinkConf *def,Tlink *l)
{
  unsigned int m,i;

  m=LinkNBodies(l);

  for(i=0;i<3;i++)
    {
      if (l->axisID[i]!=NO_UINT)
	Move3dObject(l->axisID[i],t,pt);
    }
      
  if ((m>0)&&(VisibleLink(l)))
    {
      Tpolyhedron *bd;
      THTransform td;
      boolean intConf;

      intConf=(!EmptyLinkConf(def));

      for(i=0;i<m;i++)
	{
	  bd=GetLinkBody(i,l);
	  if (intConf)
	    {
	      /* internal body configuration (displacement/deformation) */
	      GetLinkConfTransform(i,&td,def);
	      HTransformProduct(t,&td,&td);
	      MovePolyhedron(pt,&td,bd);
	      HTransformDelete(&td);
	    }
	  else
	    MovePolyhedron(pt,t,bd);
	}
    }
}

void PrintLink(FILE *f,char *path,char *prefix,char *l1,char *l2,Tlink *l)
{
  /* only FR links are printed. The rest of links are
     not defined in the world files but automatically
     generated from joints. They will be printed when
     printing the joints. */
  if ((l->type==LINK_FullRot)||(l->type==LINK_Connect))
    {
      unsigned int i,n,le;
      char *s;

      le=strlen(l->name);
	  
      if (l->type==LINK_FullRot)
	{
	  Tpolyhedron *b;
	  char *label;

	  le+=5;
	  NEW(s,le+1,char);
	  for(i=0;i<le;i++)
	    s[i]=' ';
	  s[i]=0;
	  
	  if (prefix==NULL)
	    label=l->name;
	  else
	    {
	      unsigned int ln,lp;

	      ln=strlen(l->name);
	      lp=strlen(prefix);
	      NEW(label,ln+2+lp,char);
	      sprintf(label,"%s_%s",prefix,l->name);
	      label[lp+ln+1]=0;
	    }
		
	  fprintf(f,"  %s",l->name);
	  
	  n=LinkNBodies(l);
	  if (n>0)
	    fprintf(f," : ");
	  for(i=0;i<n;i++)
	    {
	      b=GetLinkBody(i,l);
	      PrintPolyhedron(f,path,le-5,label,i,b);
	    }
	  
	  if (prefix!=NULL)
	    free(label);
	}
      else
	{
	  Tpolyhedron *b;
	  unsigned int st;
	  
	  if (IsConnectionCable(l))
	    { 
	      fprintf(f,"  c_cable ");
	      b=GetLinkBody(0,l);
	      le+=13;
	    }
	  else
	    {
	      if (IsConnectionSpring(l))
		{
		  fprintf(f,"  c_spring ");
		  b=GetLinkBody(0,l);
		  le+=14;
		}
	      else
		{
		  if (IsConnectionLeg(l))
		    {
		      fprintf(f,"  c_leg ");
		      b=GetLinkBody(1,l);
		      le+=11;
		    }
		  else
		    Error("Unknow type of connection link");
		}
	    }
      
	  NEW(s,le+1,char);
	  for(i=0;i<le;i++)
	    s[i]=' ';
	  s[i]=0;
	  
	  fprintf(f,"%s : %s (%.16f,%.16f,%.16f) %s (%.16f,%.16f,%.16f)\n",
		  l->name,
		  l1,l->p1[0],l->p1[1],l->p1[2],
		  l2,l->p2[0],l->p2[1],l->p2[2]);
	  
	  fprintf(f,"%sradius %f\n",s,GetPolyhedronRadius(b));

	  st=GetPolyhedronStatus(b);
	  
	  if (st!=HIDDEN_SHAPE)
	    {
	      Tcolor co;
	      
	      SetPolyhedronColor(&co,b);
	      
	      fprintf(f,"%scolor (%g,%g,%g)\n",s,
		      GetRed(&co),GetGreen(&co),GetBlue(&co));
	    }

	  fprintf(f,"%sgranularity %f\n",s,GetPolyhedronGranularity(b));
	  
	  switch(st)
	    {
	    case NORMAL_SHAPE:
	      break;
	    case HIDDEN_SHAPE:
	      fprintf(f,"%shidden",s);
	      break;
	    case DECOR_SHAPE:
	      fprintf(f,"%sdecoration",s);
	      break;
	    default:
	      Error("Unknown body display status in PrintLink");
	    }
      
	  fprintf(f,"%srest %f\n",s,IntervalCenter(&(l->rest)));
	  fprintf(f,"%sstiffness %f\n",s,l->stiffness);
	}
      
      if (l->mass!=0.0)
	{
	  fprintf(f,"%smass %.16f\n",s,l->mass);
      
	  if (!TrivialInertiaMatrix(l->iMatrix))
	    {
	      unsigned int j;
	      boolean first;
	  
	      fprintf(f,"%sinertia matrix ",s);
	      first=TRUE;
	      for(i=0;i<3;i++)
		{
		  for(j=i;j<3;j++)
		    {
		      if (!first)
			fprintf(f,", ");
		      fprintf(f,"%.16f",l->iMatrix[i][j]);
		      first=FALSE;
		    } 
		}
	      fprintf(f,"\n");
	    }
	  
	  if (!HTransformIsIdentity(&(l->iFrame)))
	    {
	      fprintf(f,"%sinertial frame ",s);
	      HTransformPrettyPrint(f,&(l->iFrame));
	      fprintf(f,"\n");
	    }
	}
      fprintf(f,"\n");

      free(s);
    }
}

void DeleteLink(Tlink *l)
{
  unsigned int i,n;
  Tpolyhedron *b;

  if (l->name!=NULL)
    free(l->name);
     
  /*Bodies are not deleted since mechanisms take care of them
    (here we only have IDs of the bodies)*/

  n=LinkNBodies(l);  
  for(i=0;i<n;i++)
    {
      b=GetLinkBody(i,l);
      DeletePolyhedron(b);
      free(b);
    }
  DeleteVector(&(l->bodies));

  HTransformDelete(&(l->R));
  HTransformDelete(&(l->iR));

  if (l->csvID!=NULL)
    {
      free(l->vID);
      l->vID=NULL;
      l->csvID=NULL;
      l->nvID=0;
    }

  for(i=0;i<3;i++)
    free(l->iMatrix[i]);
  free(l->iMatrix);
  
  l->varLength=FALSE;
  DeleteInterval(&(l->length));
  l->forceModel=NO_FORCE;
  l->stiffness=0;
  DeleteInterval(&(l->rest));
  DeleteInterval(&(l->force));
}
