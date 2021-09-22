#ifndef VARNAMESH
#define VARNAMESH

#include <stdio.h>

/** 
   \file varnames.h

   \brief Definition of variable names.

   Definition of macros to unify the name of the variables included
   in the cuiksystems. 

   Ensuring names are always the same, we can query the identifier of
   a variable by constructing its name and querying the corresponding
   cuiksystem.
*/

/** 
   \brief Auxiliary variables for in_patch.

   Auxiliary varibles for in_patch joints when
   \ref CT_REPRESENTATION  is \ref REP_JOINTS.
  
   Two variables are defined representing the inverse of the norm
   of the vector normal to the surface and the tangent vector
   along the 'u' parameter. These two vectors define a reference
   frame but can only be defined in un-normalized form.
   The inverse norm are used to normalize them.
   
   \param vname String where to store the varaible name.
   \param id The joint identifier.
   \param ln1 Name of the first link involved in the joint.
   \param ln2 Name of the second link involved in the joint.
   \param i Component of the dof (0 for x, 1 for y).
*/
#define IN_PATCH_DOF_VAR(vname,id,ln1,ln2,i) sprintf(vname,"_n_%s_%s_%s_%u",ln1,ln2,(i==0?"x":"y"),id)

/** 
   \brief Name for the degrees of freedom.

   Name given to the variables representing degrees of freedom.
   Only used if \ref CT_REPRESENTATION  is \ref REP_JOINTS.

   \param vname String where to store the varaible name.
   \param id The joint identifier.
   \param ln1 Name of the first link involved in the joint.
   \param ln2 Name of the second link involved in the joint.
   \param i Number of the degrees of freedom of this joint (many joints have more
            than one dof).
*/
#define DOF_VAR(vname,id,ln1,ln2,i) sprintf(vname,"_d_%s_%s_%u_%u",ln1,ln2,i,id)

/** 
    \brief Frame of reference for a link.

    Three vectors (u,v,w) defining (in global coordinates) the frame of reference for
    a given link.

    Note that this in only one of the ways to parametrize the rotation matrix.
    See \ref LINK_ROT2 and \ref LINK_ROT3_E  for alternative ways.

   \param vname String where to store the variable name.
   \param linkName Name of the link.
   \param vn Vector identifier (0 for u, 1 for v, and 2 for w).
   \param cn The component of the vector (0 for x, 1 for y and 2 for z).
*/
#define LINK_ROT(vname,linkName,vn,cn) sprintf(vname,"_%s_%s_%s",linkName,(vn==0?"u":(vn==1?"v":"w")),(cn==0?"x":(cn==1?"y":"z")))

/** 
    \brief Frame of reference for a link.

    Three vectors in the form of (u,v,w-wp) defining (in global coordinates) 
    the frame of reference for a given link.

    The third vector w-wp are dummified forms of the cross product of u and v.

    Note that this in only one of the ways to parametrize the rotation matrix.
    See \ref LINK_ROT and \ref LINK_ROT3_E for alternative ways.

   \param vname String where to store the variable name.
   \param linkName Name of the link.
   \param vn Vector identifier (0 for u, 1 for v, and 2 for w, and 3 for w_b).
   \param cn The component of the vector (0 for x, 1 for y and 2 for z).
*/
#define LINK_ROT2(vname,linkName,vn,cn) (vn<3?LINK_ROT(vname,linkName,vn,cn):sprintf(vname,"_%s_wp_%s",linkName,(cn==0?"x":(cn==1?"y":"z"))))

/** 
    \brief Link length.

    A variable representing the variable length for a link. Only used
    in tensegrities (and for DeformX links).

    \param vname String where to store the variable name.
    \param linkName Name of the link.
*/
#define LINK_LENGTH(vname,linkName) sprintf(vname,"_l_%s",linkName)
  
/** 
    \brief Rest variable.

    A variable representing the variable rest for a link. Only used
    in tensegrities.

    \param vname String where to store the variable name.
    \param linkName Name of the link.
*/
#define LINK_REST(vname,linkName) sprintf(vname,"_r_%s",linkName)

/** 
    \brief Max force variable.

    A variable representing the maximum compression/tension
    force on a link. Only used in tensegrities.

   \param vname String where to store the variable name.
   \param linkName Name of the link.
*/
#define LINK_MAX_FORCE(vname,linkName) sprintf(vname,"_f_%s",linkName)

/** 
    \brief Frame of reference for a link using quaternions.

    Rotation matrix represented using <a href="http://en.wikipedia.org/wiki/Rotation_representation_(mathematics)">
    quaternions</a>.

    This macro only gives the name the \e qq_ij variables (i,j=0..3) derived from the
    \e q_i, i=0..3, quaternion variables. If i=j then only one sub-index is used.

    Note that this in only one of the ways to parametrize the rotation matrix.
    See \ref LINK_ROT and \ref LINK_ROT2 for alternative ways.

   \param vname String where to store the variable name.
   \param linkName Name of the link.
   \param rn Row number.
   \param cn Column number.
*/
#define LINK_ROT3_E(vname,linkName,rn,cn) (rn==cn?sprintf(vname,"_%s_qq_%u",linkName,rn):sprintf(vname,"_%s_qq_%u_%u",linkName,rn,cn)) 
/** 
   \brief System variables for a rotation matrix using quaternions.

   \ref LINK_ROT3_E give the name for the variables used in the rotation matrics
   when using quaternions as a representation tool. However, these variables
   are not the basic varaiables of the quaternion but combinations of them.

   This macro gives the name of the original quaternion variables \e q_i (i=0..3)

   The variables defined with \ref LINK_ROT3_E are related with the \e q_i
   variables by 
   <center><em>e_ij=q_i*q_j</em></center>
   These relations appear in the form of dummy equations in the quaternion-based systems.
*/
#define LINK_ROT3_Q(vname,linkName,j) sprintf(vname,"_%s_q_%u",linkName,j)

/** 
   \brief Translation part of the homogeneous transform defining the position
          of a link in global coordinates.

   The vectors defined in LINK_ROT define the rotatin of a link in global
   coordinates. These variables define the translation part of the homogenous
   transform placing the link in the global frame of reference.

   \param vname String where to store the variable name.
   \param linkName Name of the link.
   \param cn The component of the vector (0 for x, 1 for y and 2 for z).

*/
#define LINK_TRANS(vname,linkName,cn) sprintf(vname,"_%s_r_%s",linkName,(cn==0?"x":(cn==1?"y":"z")))

/** 
   \brief Variables for a free joint.
   
   A free vector defining a generic the translation from link 1 to link 2.

   Note that the name of the variables generated for a free joint when one
   of the links involved is the ground link is the same as the name generated
   for the translation component of this link (see \ref LINK_TRANS).

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param id1 Identifier of the first link involved in the joint.
   \param ln1 Name of the first link involved in the joint.
   \param id2 Identifier of the first link involved in the joint.
   \param ln2 Name of the second link involved in the joint.
   \param k Component of the vector (0 for x, 1 for y and 2 for z).
*/
#define FREE_JOINT_VAR(vname,id,id1,ln1,id2,ln2,k) (id1==0?LINK_TRANS(vname,ln2,k):(id2==0?LINK_TRANS(vname,ln1,k):sprintf(vname,"_%s_%s_%s_%u",ln1,ln2,(k==0?"x":(k==1?"y":"z")),id)))

/** 
   \brief One variable for each prismatic joint.

   One variable for each prismatic joint: the displacement along the 
   sliding axis.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
*/
#define PRS_JOINT_VAR(vname,id,ln1,ln2) sprintf(vname,"_d_%s_%s_%u",ln1,ln2,id)

/** 
   \brief One end-range singularity variable for each prismatic joint.

   Auxiliar variable to detect singularities in bounded prismatic joints.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
*/
#define PRS_JOINT_VAR_SING_SIN(vname,id,ln1,ln2) sprintf(vname,"_d_sing_sin_%s_%s_%u",ln1,ln2,id)

/** 
   \brief One end-range singularity variable for each prismatic joint.

   Auxiliar variable to detect singularities in bounded prismatic joints.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
*/
#define PRS_JOINT_VAR_SING_COS(vname,id,ln1,ln2) sprintf(vname,"_d_sing_cos_%s_%s_%u",ln1,ln2,id)

/** 
   \brief Two vectors for each universal joint.

   Two vectors for each universal joint defining the copunctual orthogonal 
   rotation axis that define the universal joint.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param i 0 for the first axis of the universal joint and 1 for the second.
   \param k Component of the vector (0 for x, 1 for y and 2 for z).
*/
#define UNV_JOINT_VAR(vname,id,ln1,ln2,i,k) sprintf(vname,"_uni_%s_%s_%s_%s_%u",(i==0?"u":"v"),ln1,ln2,(k==0?"x":(k==1?"y":"z")),id)

/** 
   \brief Control variables defining a first order Bezier patch.

   A first order Bezier is defined with two variables (u,v). Here
   we additionally define a third variable w that is u*v so that
   all equations remain linear or bilinear.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param i The control variable (0 for u, 1 for v and 2 for w).
*/	 
#define IN_PATCH_JOINT_CTRL_VAR(vname,id,ln1,ln2,i) sprintf(vname,"_in_patch_%s_%s_%s_%u",ln1,ln2,(i==0?"u":(i==1?"v":"w")),id)

/** 
   \brief End-range singularity variable for each in_patch joint.

   Auxiliar variable to detect singularities in in_patch joints.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param i The control variable (0 for u, 1 for v and 2 for w).
*/	 
#define IN_PATCH_JOINT_CTRL_VAR_SING_SIN(vname,id,ln1,ln2,i) sprintf(vname,"_in_patch_sing_sin_%s_%s_%s_%u",ln1,ln2,(i==0?"u":(i==1?"v":"w")),id)

/** 
   \brief End-range singularity variable for each in_patch joint.

   Auxiliar variable to detect singularities in in_patch joints.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param i The control variable (0 for u, 1 for v and 2 for w).
*/	 
#define IN_PATCH_JOINT_CTRL_VAR_SING_COS(vname,id,ln1,ln2,i) sprintf(vname,"_in_patch_sing_cos_%s_%s_%s_%u",ln1,ln2,(i==0?"u":(i==1?"v":"w")),id)


/** 
   \brief Scale factor for the normal vector to a first order Bezier patch.

   When defining a IN_PATCH joint, the normal vectors at the two links in contact 
   at the contact point are equated. In the first link this vector is constant
   but in the second link it is variable (depends on the control points defining
   the patch). This scale variable is used to make the two vectors equal.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
*/	 
#define IN_PATCH_JOINT_SCALE_VAR(vname,id,ln1,ln2) sprintf(vname,"_in_patch_%s_%s_l_%u",ln1,ln2,id)

/** 
   \brief Two vectors to define the angle in a revolute joint.

   Two vectors (x-y-z variables) orthogonal to the rotation axis 
   one attached to the 1st link and the another to the 2nd link.

   A third vector aligned with the rotation axis used to define
   the cross product between the two first vectors.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param k Number of the vector to which to variable is referred (0,1).
            The varible for 0 is named *_w1_* and for 1 we get *_w2_*
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param i Component of the vector (0 for x, 1 for y and 2 for z).

*/
#define ROT_JOINT_VAR_REF(vname,id,k,ln1,ln2,i) sprintf(vname,"_%s_%s_%s_%s_%u",(k==0?"w1":"w2"),ln1,ln2,(i==0?"x":(i==1?"y":"z")),id)


/** 
   \brief Two vectors to define the angle in a universal joint.

   Two vectors (x-y-z variables) to define the angle in a universal joint.
   The first vector defines the first angle w.r.t. the second rotation axis of the
   universal joint.
   The second vector defines the first angle w.r.t. the first rotation axis of the
   universal joint.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param k Number of the vector to which to variable is referred (0,1).
            The varible for 0 is named *_w1_* and  for 1 we get *_w2_*
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param i Component of the vector (0 for x, 1 for y and 2 for z).

*/
#define UNV_JOINT_VAR_REF(vname,id,k,ln1,ln2,i) sprintf(vname,"_%s_%s_%s_%s_%u",(k==0?"w1":"w2"),ln1,ln2,(i==0?"x":(i==1?"y":"z")),id)

/** 
   \brief Cosinus between two links for rotation/spherical joints.

   Cosinus between two links articulated by a rotation/spherical joint (actually, cosinus 
   between two vectors rigidly attached to two links).

   In revolute/spherical joints only one \e angle is possible between two links
   for a give joint

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.

*/
#define COS_VAR(vname,id,ln1,ln2) sprintf(vname,"_cos_%s_%s_%u",ln1,ln2,id)

/** 
   \brief One end-range singularity variable for each revolute joint.

   Auxiliar variable to detect singularities in bounded revolute/spherical joints.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.

*/
#define COS_VAR_SING(vname,id,ln1,ln2) sprintf(vname,"_cos_sing_%s_%s_%u",ln1,ln2,id)

/** 
   \brief Cosinus between two links for universal joints.

   Cosinus between two links articulated by a universal joint.
   Two cosinus are defined, one for the first rotation and another for the second
   rotation of the universal joint.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param k Identifier of the universal joint rotation (0 for the first rotation and
            1 for the second one).

*/
#define COS_VAR_UNI(vname,id,ln1,ln2,k) sprintf(vname,"_cos_%u_%s_%s_%u",k,ln1,ln2,id)

/** 
   \brief End-range singularity variable for each universal joint.

   Auxiliar variables to detect singularities in bounded universal joints.

   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param k Identifier of the universal joint rotation (0 for the first rotation and
            1 for the second one).
*/
#define COS_VAR_UNI_SING(vname,id,ln1,ln2,k) sprintf(vname,"_cos_sing_%u_%s_%s_%u",k,ln1,ln2,id)

/** 
   \brief Two vectors defined for when limiting the movement of a spherical joints.
   
   We define two vectors, the first attached to link1 and the second to link2, that
   must coincide for angle 0.
  
   \param vname String where to store the variable name.
   \param id Unique identifier for the joint.
   \param v Vector identifier (0 for w1, 1 for w2).
   \param ln1 Identifier of the first link involved in the joint.
   \param ln2 Identifier of the second link involved in the joint.
   \param k Component of the vector (0 for x, 1 for y and 2 for z).
*/
#define SPH_JOINT_VAR_REF(vname,id,v,ln1,ln2,k) sprintf(vname,"_sph_%s_%s_%s_%s_%u",(v==0?"w1":"w2"),ln1,ln2,(k==0?"x":(k==1?"y":"z")),id)

#endif
