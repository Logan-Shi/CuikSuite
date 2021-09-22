#include "world.h"
#include "error.h"
#include "defines.h"

#include <strings.h>

/** \file cuiktransform.c

    \brief Main body of the \ref cuiktransform.c "cuiktransform" application.
    
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiktransform    [label="cuiktransform"  color="#99ff99" shape=ellipse];
      
      shapeIn   [label="shape"   color="#ff9999" ];
      shapeOut  [label="shape"   color="#ff9999" ];

      shapeIn -> cuiktransform
      cuiktransform -> shapeOut;
    }
    \enddot
    </center>

    Applies a rigid transform to a convex body. 
    
    This is useful to rotate/translate bodies to be latter used to define mechanisms
    or obstacles.

    \todo Integrate the \b CuikSuite with a proper 3D modeler such as
    <a href="http://www.blender.org/">blender</a>.
*/

/** 
   \brief Main body of the \ref cuiktransform.c "cuiktransform"  application.

   Main body of the \ref cuiktransform.c "cuiktransform" application.

   Use: <br>
     - \b cuiktransform \e body_in \e transfrom \e value \e body_in \e body_out
     .
   Where: 
     - \e body_in: Body to transform.
     - \e transform:  One of the following strings Tx, Ty, Tz, Rx, Ry, Rz, Sc.
     - \e value:  Value for the transform (angles in degrees!!).
     - \e body_out: File where to store the transformed body  (can be the same as the input).
     .

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiktransform command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  boolean wrongParameters=FALSE;
  
  if (argc>3)
    {
      Tpolyhedron body;
      THTransform transform;
      Tfilename bodyIn;
      Tfilename bodyOut;
      Tcolor color;
      char *transforms[11]={"Tx","Ty","Tz","Rx","Ry","Rz","Sc","Sx","Sy","Sz","Sp"};
      unsigned int i;
      boolean found;
     
      found=FALSE;
      i=0;
      while((!found)&&(i<11))
	{
	  found=(strcasecmp(arg[2],transforms[i])==0);
	  if (!found)
	    i++;
	}

      if ((i<10)&&(argc==4))
	wrongParameters=TRUE;
      else
	{
	  if (!found)
	    Error("Unknown transform in cuiktransform");
	  
	  NewColor(1,1,1,&color);
      
	  CreateFileName(NULL,arg[1],NULL,NULL,&bodyIn);
	  InitPolyhedronFromFile(&bodyIn,&color,1,NORMAL_SHAPE,&body);
      
	  switch(i)
	    {
	    case 0:
	      HTransformTx(atof(arg[3]),&transform);
	      break;
	    case 1:
	      HTransformTy(atof(arg[3]),&transform);
	      break;
	    case 2:
	      HTransformTz(atof(arg[3]),&transform);
	      break;
	    case 3:
	      HTransformRx(atof(arg[3])*DEG2RAD,&transform);
	      break;
	    case 4:
	      HTransformRy(atof(arg[3])*DEG2RAD,&transform);
	      break;
	    case 5:
	      HTransformRz(atof(arg[3])*DEG2RAD,&transform);
	      break;
	    case 6:
	      HTransformScale(atof(arg[3]),&transform);
	      break;
	    case 7:
	      HTransformScaleX(atof(arg[3]),&transform);
	      break;
	    case 8:
	      HTransformScaleY(atof(arg[3]),&transform);
	      break;
	    case 9:
	      HTransformScaleZ(atof(arg[3]),&transform);
	      break;
	    case 10:
	      SimplifyPolyhedron(&body);
	      break;
	    }
	  if (i<10)
	    {
	      TransformPolyhedron(&transform,&body);
	      CreateFileName(NULL,arg[4],NULL,NULL,&bodyOut);
	    }
	  else
	    CreateFileName(NULL,arg[3],NULL,NULL,&bodyOut);
	    
	  SavePolyhedron(GetFileFullName(&bodyOut),&body);
      
	  HTransformDelete(&transform);
	  DeletePolyhedron(&body);
	  DeleteColor(&color);
	  DeleteFileName(&bodyIn);      
	  DeleteFileName(&bodyOut);
	}
    }
  else
    wrongParameters=TRUE;

  if (wrongParameters)
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuiktransform <body in> <transform> <value> <body out>\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <body in>: File with the convex body to transform\n");
      fprintf(stdout,"     <transform>: Transform to apply (Tx,Ty,Tz,Rx,Ry,Rz,Sc,Sx,Sy,Sz,Sp)\n");
      fprintf(stdout,"     <value>: Parameter for the transform (angles in degrees!!).\n");
      fprintf(stdout,"     <body out>: Name of output file with the transformed convex body.\n");
    }

  return(EXIT_SUCCESS);
}
