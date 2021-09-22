%{ 
/** \cond */
#include "world.h"

#include "boolean.h"
#include "error.h"
#include "error_world.h"
#include "constants.h"
#include "defines.h"
#include "color.h"
#include "htransform.h"
#include "vector.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
* Definition of the function that initilizes a kinematic equations from a file.
* This is a method of the equations object.
*/

  /*Lex and Yacc variables*/
  extern FILE *ReadWorldin;

  /* first link/object in the file currently bein parsed */
  extern unsigned int firstLink; /* first link in the current object */
  extern unsigned int firstObject; /* first object in the current file */

  /*Lex and Yacc functions*/
  int ReadWorldlex(void); 
  void Switch2File(char *ln,unsigned int nl,unsigned int no,char *path,char *file);

  /*Our own variables*/
  extern unsigned int RWline; /* line number currently processed 
				 (incremented by the LEX processor)*/
  
  /*Auxiliary variables used along readwordl*/
  unsigned int rw_lID,rw_lID1,rw_lID2; /*link identifier*/
  Tlink rw_link;
  Tjoint rw_joint;
  boolean rw_visible;

  /* Global pointer to allow the different parts of the parser to acces the 
     equations being initialized*/
  Tworld *rw_world;

  /* Global pointer to the paramters */
  Tparameters *rw_parameters;
  
  THTransform rw_transform;

  unsigned int rw_r;

  double **rw_point;
  unsigned int rw_i,rw_max;
  double *rw_X,*rw_Y,*rw_Z;
  double rw_angle;
  Tinterval rw_range,rw_range0;
  boolean rw_has_limits;
  boolean rw_has_reference;
  double **rw_range_point;
  double **rw_in_patch_point;
  Tcolor rw_color_default,rw_color_body;
  Tfilename *rw_filename;
  Tpolyhedron rw_cbody;
  boolean rw_endEffector;
  double **rw_imatrix;
  double rw_mass;
  THTransform rw_iframe;
  double rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping;
  double rw_rest,rw_stiffness;
  boolean rw_visualization;
  boolean rw_empty_cbody;
  
  Tconstants rw_constants;

  boolean rw_avoidLimits;
  double rw_avoidLimitsWeight;

  boolean rw_prevolute;

  char *rw_eqFile;
%}

%union 
{ 
  char *id; 
  char *string;
  int int_number;
  double real_number;
  Tcolor color;
} 

%start world

%token _CONSTANTS _ASSIGN _EQUAL _NOT_EQUAL _LESS_EQUAL _GREATER_EQUAL _LESS _GREATER _PI _EXP _COS _SIN _TAN _COT _ACOS _ASIN _ATAN _ATAN2 _SQRT _ABS _PARAMETER _PRINT _LINKS _JOINTS _OBSTACLES _COLLISIONS _CHECK _NO _ALL _CONNECTED _BODY _GRANULARITY _FIX  _ID _TX _TY _TZ _TXYZ _RX _RY _RZ _TR _INV _MASS _INERTIAL _FRAME _INERTIA _MATRIX _VELOCITY _ACCELERATION _TORQUE _FORCE _EFFORT _COST _FRICTION _DAMPING _PRISMATIC _REVOLUTE _CREVOLUTE _SPHERICAL _UNIVERSAL _SPH_SPH _SPH_PRS_SPH _SPRING _XYSPRING _REST _STIFFNESS _C_CABLE _C_SPRING _C_LEG _IN_PATCH _BOX _PRISM _SPHERE _SOLID _ELLIPSOID _CYLINDER _ROD_X _ROD_Y _ROD_Z _CYLINDER_X _CYLINDER_Y _CYLINDER_Z _LINE _SEGMENTS _LENGTH _RADIUS _SELFCOLLISIONS _RANGE _REFERENCE _COLOR _RED _GREEN _BLUE _PURPLE _CYAN _YELLOW _WHITE _BLACK _GREY _DECORATION _HIDDEN _AVOID _LIMITS _INCLUDE _EQUATIONS _EQFILE

%token <id> _IDENTIFIER
%token <id> _EXT_IDENTIFIER
%token <int_number> _INTEGER 
%token <real_number> _REAL
%token <string> _STRING

%type <int_number> granularity
%type <int_number> shape_status
%type <int_number> connector
%type <real_number> expr
%type <color> color
%type <id> any_id
%type <int_number> spring_type
%type <int_number> opt_invert

%left _EQUAL _NOT_EQUAL _LESS_EQUAL _GREATER_EQUAL _LESS _GREATER
%left '+' '-' 
%left '*' '/'
%left '^'
%right _MAX_PRECEDENCE 
%% 

world : world def_block
      |
      ;

def_block : constant_defs
          | link_defs 
          | joint_defs 
          | obstacle_defs 
          | collision_defs 
          | included_defs
          | equations_defs
          ;

constant_defs: _CONSTANTS constant_list
             ;

constant_list : constant_definition constant_list
              | 
              ;

constant_definition : _IDENTIFIER _ASSIGN expr
                      {
			if (GetConstantWithName($1,&rw_constants)!=NO_UINT)
			  {
			    char s[200];
			    
			    sprintf(s,"Duplicated constant %.100s",$1);
			    ReadWorlderror(s);
			  }
			
			AddConstant($1,$3,&rw_constants);
			free($1);
		      }
                    | _PRINT _IDENTIFIER
		      {
			unsigned int nc;
	 
			nc=GetConstantWithName($2,&rw_constants);
			if (nc==NO_UINT)
			  {
			    char ms[200];
			    
			    sprintf(ms,"Undefined constant: %.100s",$2);
			    ReadWorlderror(ms);
			  }
			fprintf(stderr,"  %s = %.12f\n",$2,GetConstantValue(nc,&rw_constants));
			free($2);
		      }
                    ;

any_id : _IDENTIFIER
         {
	   $$=$1; /* do not free $1, we will free $$ */
	 }
       | _EXT_IDENTIFIER
         {
	   $$=$1; /* do not free $1, we will free $$ */
	 }
       ;

expr : '+' expr    %prec _MAX_PRECEDENCE
       {
	 $$=$2;
       }
     | '-' expr    %prec _MAX_PRECEDENCE
       {
	 $$=-$2;
       }
     | expr '+' expr 
       {
	 $$=$1+$3;
       }
     | expr '-' expr 
       {
	 $$=$1-$3;
       }
     | expr '*' expr 
       {
	 $$=$1*$3;
       }
     | expr '^' expr 
       {
	 $$=pow($1,$3);
       }
     | expr '/' expr 
       { 
	 $$=$1/$3;
       }
     | '(' expr ')'
       {
	 $$=$2;
       }    
     | '(' expr '?' expr ':' expr ')'
       {
	 if ($2)
	   $$=$4;
	 else
	   $$=$6;
       }
     | expr _EQUAL expr 
       {
	 $$=($1==$3);
       }
     | expr _NOT_EQUAL expr 
       {
	 $$=($1!=$3);
       }
     | expr _LESS_EQUAL expr  
       {
	 $$=($1<=$3);
       }
     | expr _GREATER_EQUAL expr     
       {
	 $$=($1>=$3);
       }
     | expr _LESS expr        
       {
	 $$=($1<$3);
       }
     | expr _GREATER expr   
       {
	 $$=($1>$3);
       }   
     | _PI 
       {
	 $$=M_PI;
       } 
     | _SIN '(' expr ')'
       {
	 $$=sin($3);
       }
     | _COS '(' expr ')'
       {
	 $$=cos($3);
       }
     | _TAN '(' expr ')'
       {
	 $$=tan($3);
       }
     | _COT '(' expr ')'
       {
	 $$=tan(M_PI_2-$3);
       }
     | _ASIN '(' expr ')'
       {
	 $$=asin($3);
       }
     | _ACOS '(' expr ')'
       {
	 $$=acos($3);
       }
     | _ATAN '(' expr ')'
       {
	 $$=atan($3);
       }
     | _ATAN2 '(' expr ',' expr ')'
       {
	 $$=atan2($3,$5);
       }
     | _EXP '(' expr ')'
       {
	 $$=exp($3);
       }
     | _SQRT '(' expr ')'
       {
	 $$=sqrt($3);
       }
     | _ABS '(' expr ')'
       {
	 $$=fabs($3);
       }
     | _PARAMETER '(' _IDENTIFIER ')'
       {
	 unsigned int n;

	 n=GetParameterID($3,rw_parameters);
	 if (n==NO_UINT)
	   {
	     char ms[200];
	     
	     sprintf(ms,"Undefined parameter: %.100s",$3);
	     ReadWorlderror(ms);
	   }
	 $$=GetParameter(n,rw_parameters);
       }
     | any_id
       {
	 unsigned int nc;
	 
	 nc=GetConstantWithName($1,&rw_constants);
	 
	 if (nc!=NO_UINT)
	   $$=GetConstantValue(nc,&rw_constants);
	 else
	   {
	     char ms[200];
	     
	     sprintf(ms,"Undefined constant: %.100s",$1);
	     ReadWorlderror(ms);
	   }
	 free($1);
       }
     | _INTEGER 
       {
	 $$=(double)$1;
       } 
     | _REAL
       {
	 $$=$1;
       }
     ; 

link_defs : _LINKS link_list
          ;
         
link_list : link_definition link_list
          | 
          ;

link_definition: _IDENTIFIER 
                 {
		   if (GetConstantWithName($1,&rw_constants)!=NO_UINT)
		     ReadWorlderror("Link with the name of a constant");

		   if (GetWorldLinkID($1,rw_world)!=NO_UINT)
		     ReadWorlderror("Duplicated link");

		   rw_mass=0.0;
		   
		   /*adds an empty link to the world*/
		   InitLink($1,0.0,NULL,NULL,&rw_link);
		   
		   free($1);
		 }
                 opt_link_definition
                 {
		   SetLinkMass(rw_mass,&rw_link);
		   SetLinkInertiaMatrix(rw_imatrix,&rw_link);
		   SetLinkInertialFrame(&rw_iframe,&rw_link);
		   
		   AddLink2World(&rw_link,rw_endEffector,rw_world);
		   DeleteLink(&rw_link);
		 }
                 ;


opt_link_definition : link_separator link_color link_shapes opt_link_dynamics
                    |
                    ;

opt_link_dynamics : link_mass link_inertiamatrix link_inertialframe 
                  ;

link_mass : _MASS expr
            {
	      rw_mass=$2;
	    }
          |
	    {
	      rw_mass=0.0;
	    }
          ;

link_inertiamatrix : _INERTIA _MATRIX inertia_def
                   |
                     {
		       rw_imatrix[0][0]= 0.0; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		       rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]= 0.0; rw_imatrix[1][2]= 0.0;
		       rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]= 0.0;
	              }
                   ;

inertia_def :  expr ',' expr ',' expr ',' expr ',' expr ',' expr 
              {
		rw_imatrix[0][0]= $1; rw_imatrix[0][1]= $3; rw_imatrix[0][2]= $5;
		rw_imatrix[1][0]= $3; rw_imatrix[1][1]= $7; rw_imatrix[1][2]= $9;
		rw_imatrix[2][0]= $5; rw_imatrix[2][1]= $9; rw_imatrix[2][2]=$11;
	      }
            | _ROD_X expr
	      {
		double v;

		v=1.0/12.0*rw_mass*$2*$2;
		
		rw_imatrix[0][0]= 0.0; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=   v; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=   v;
	      }
            | _ROD_Y expr
	      {
		double v;

		v=1.0/12.0*rw_mass*$2*$2;
		
		rw_imatrix[0][0]=   v; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]= 0.0; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=   v;
	      }
            | _ROD_Z expr
	      {
		double v;

		v=1.0/12.0*rw_mass*$2*$2;
		
		rw_imatrix[0][0]=   v; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=   v; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]= 0.0;
	      }
	    | _CYLINDER_X expr ',' expr ',' expr
	      {
		double v1,v2;

		if ($2>=$4)
		  {
		    char ms[200];
		    
		    sprintf(ms,"Inner cylinder diameter larger than the external one: %5.3f vs %5.3f",$2,$4);
		    ReadWorlderror(ms);
		  }
		
		v1=1.0/12.0*rw_mass*(3*($2*$2+$4*$4)+$6*$6);
		v2=1.0/2.0*rw_mass*($2*$2+$4*$4);
		
		rw_imatrix[0][0]=  v2; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=  v1; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=  v1;
	      }
	    | _CYLINDER_Y expr ',' expr ',' expr
	      {
		double v1,v2;

		if ($2>=$4)
		  {
		    char ms[200];
		    
		    sprintf(ms,"Inner cylinder diameter larger than the external one: %5.3f vs %5.3f",$2,$4);
		    ReadWorlderror(ms);
		  }
		
		v1=1.0/12.0*rw_mass*(3*($2*$2+$4*$4)+$6*$6);
		v2=1.0/2.0*rw_mass*($2*$2+$4*$4);
		
		rw_imatrix[0][0]=  v1; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=  v2; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=  v1;
	      }
            | _CYLINDER_Z expr ',' expr ',' expr
	      {
		double v1,v2;

		if ($2>=$4)
		  {
		    char ms[200];
		    
		    sprintf(ms,"Inner cylinder diameter larger than the external one: %5.3f vs %5.3f",$2,$4);
		    ReadWorlderror(ms);
		  }
		
		v1=1.0/12.0*rw_mass*(3*($2*$2+$4*$4)+$6*$6);
		v2=1.0/2.0*rw_mass*($2*$2+$4*$4);
		
		rw_imatrix[0][0]=  v1; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=  v1; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=  v2;
	      }
	    | _SOLID _CYLINDER_X expr ',' expr
	      {
		double v1,v2;
		
		v1=1.0/12.0*rw_mass*(3*$3*$3+$5*$5);
		v2=1.0/2.0*rw_mass*($3*$3);
		
		rw_imatrix[0][0]=  v2; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=  v1; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=  v1;
	      }
            | _SOLID _CYLINDER_Y expr ',' expr
	      {
		double v1,v2;
		
		v1=1.0/12.0*rw_mass*(3*$3*$3+$5*$5);
		v2=1.0/2.0*rw_mass*($3*$3);
		
		rw_imatrix[0][0]=  v1; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=  v2; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=  v1;
	      }
            | _SOLID _CYLINDER_Z expr ',' expr
	      {
		double v1,v2;
		
		v1=1.0/12.0*rw_mass*(3*$3*$3+$5*$5);
		v2=1.0/2.0*rw_mass*($3*$3);
		
		rw_imatrix[0][0]=  v1; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=  v1; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=  v2;
	      }
            | _SPHERE expr
	      {
		double v;

		v=2.0/3.0*rw_mass*$2*$2;
		
		rw_imatrix[0][0]=   v; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=   v; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=   v;
	      }
            | _SOLID _SPHERE expr
	      {
		double v;

		v=2.0/5.0*rw_mass*$3*$3;
		
		rw_imatrix[0][0]=   v; rw_imatrix[0][1]= 0.0; rw_imatrix[0][2]= 0.0;
		rw_imatrix[1][0]= 0.0; rw_imatrix[1][1]=   v; rw_imatrix[1][2]= 0.0;
		rw_imatrix[2][0]= 0.0; rw_imatrix[2][1]= 0.0; rw_imatrix[2][2]=   v;
	      }
            | _BOX expr ',' expr ',' expr
	      {
		double v;

		v=1.0/12.0*rw_mass;
		
		rw_imatrix[0][0]= v*($4*$4+$6*$6); rw_imatrix[0][1]=             0.0; rw_imatrix[0][2]=             0.0;
		rw_imatrix[1][0]=             0.0; rw_imatrix[1][1]= v*($2*$2+$6*$6); rw_imatrix[1][2]=             0.0;
		rw_imatrix[2][0]=             0.0; rw_imatrix[2][1]=             0.0; rw_imatrix[2][2]= v*($2*$2+$4*$4);
	      }
            | _ELLIPSOID expr ',' expr ',' expr
	      {
		double v;

		v=1.0/5.0*rw_mass;
		
		rw_imatrix[0][0]= v*($4*$4+$6*$6); rw_imatrix[0][1]=             0.0; rw_imatrix[0][2]=             0.0;
		rw_imatrix[1][0]=             0.0; rw_imatrix[1][1]= v*($2*$2+$6*$6); rw_imatrix[1][2]=             0.0;
		rw_imatrix[2][0]=             0.0; rw_imatrix[2][1]=             0.0; rw_imatrix[2][2]= v*($2*$2+$4*$4);
	      }
            ;

link_inertialframe : _INERTIAL _FRAME
                     {
		       HTransformIdentity(&rw_transform);
		     }
                     transforms
		     {
		       HTransformCopy(&rw_iframe,&rw_transform);
		     }
                   |
		     {
		       HTransformIdentity(&rw_iframe);
		     }
                   ;


link_separator : ':'
                 {
		   rw_endEffector=FALSE;
		 }
               | '-'
                 {
		   rw_endEffector=TRUE;
		 }
               ;

link_shapes : shape 
              {
		if (!rw_empty_cbody)
		  {
		    AddBody2Link(&rw_cbody,&rw_link);
		    DeletePolyhedron(&rw_cbody);
		  }
	      }
              link_shapes
            | shape 
              {
		if (!rw_empty_cbody)
		  {
		    AddBody2Link(&rw_cbody,&rw_link);
		    DeletePolyhedron(&rw_cbody);
		  }
	      }
            ;

shape: _BODY _STRING body_color granularity shape_status 
       {
	 if ((rw_visualization)||($5!=DECOR_SHAPE))
	   {
	     Tfilename fb;

	     CreateFileName(GetFilePath(rw_filename),$2,NULL,NULL,&fb);

	     rw_empty_cbody=FALSE;
	     
	     InitPolyhedronFromFile(&fb,&rw_color_body,
				    $4,$5,&rw_cbody);

	     DeleteFileName(&fb);
	   }
	 else
	   /* For planning (i.e. not visualization tasks) we skip reading potentially
	      large decoration objects. Other decoration shapes (boxes, spheres,..) 
	      could also be removed but are comparatively inexpensive */
	   rw_empty_cbody=TRUE;
	 free($2);
       }
     | _BOX
       {
	 rw_i=0;
	 rw_lID=NO_UINT;
       } 
       point pointp body_color shape_status
       {
	 rw_empty_cbody=FALSE;
	 NewBox(rw_point[0][0],rw_point[0][1],rw_point[0][2],
		rw_point[1][0],rw_point[1][1],rw_point[1][2],
		&rw_color_body,$6,&rw_cbody);
       }
     | _PRISM
       {
	 rw_i=0;
       }
       point point point expr body_color shape_status
       {
	 rw_empty_cbody=FALSE;
	 NewTriangularPrism(rw_point[0],rw_point[1],rw_point[2],
			    $6,
			    &rw_color_body,$8,&rw_cbody);
       }
     | _SPHERE  expr  
       {
	 rw_i=0;
	 rw_lID=NO_UINT;
       } 
       point body_color granularity shape_status
       {
	 rw_empty_cbody=FALSE;
	 NewSphere($2,rw_point[0],&rw_color_body,$6,$7,&rw_cbody);
       }
     | _CYLINDER  expr 
       {
	 rw_i=0;
	 rw_lID=NO_UINT;
       } 
       point pointp body_color granularity shape_status 
       {
	 rw_empty_cbody=FALSE;
	 NewCylinder($2,rw_point[0],rw_point[1],&rw_color_body,2*$7,$8,&rw_cbody);
       }
     | _LINE 
       {
	 rw_i=0;
	 rw_lID=NO_UINT;
       } 
       point pointp body_color shape_status 
       {
	 rw_empty_cbody=FALSE;
	 NewLine(rw_point[0],rw_point[1],&rw_color_body,$6,&rw_cbody);
       }
     | _SEGMENTS 
       {
	 rw_i=0;
	 rw_max=100;
	 NEW(rw_X,rw_max,double);
	 NEW(rw_Y,rw_max,double);
	 NEW(rw_Z,rw_max,double);
	 rw_lID=NO_UINT;
       } 
       point_list body_color 
       {
	 rw_empty_cbody=FALSE;
	 NewSegments(rw_i,rw_X,rw_Y,rw_Z,&rw_color_body,&rw_cbody);
	 free(rw_X);
	 free(rw_Y);
	 free(rw_Z);
       }
     ;

granularity : _GRANULARITY _INTEGER
              {
		$$=$2;
	      }
            |
              {
		$$=DEFAULT_DICE;
	      }

            ;

shape_status : _HIDDEN
               {
	         $$=HIDDEN_SHAPE;
	       }
             | _DECORATION
               {
	         $$=DECOR_SHAPE;
	       }
             |
               {
	         $$=NORMAL_SHAPE;
	       }
             ;

color : _COLOR  '(' expr ',' expr ',' expr ')'
        {
	  NewColor($3,$5,$7,&($$));
	}
      | _RED
        {
	  NewColorWithID(RED,&($$));
	}
      | _GREEN
        {
	  NewColorWithID(GREEN,&($$));
	}
      | _BLUE
        {
	  NewColorWithID(BLUE,&($$));
	}
      | _BLACK
        {
	  NewColorWithID(BLACK,&($$));
	}
      | _GREY
        {
	  NewColorWithID(GREY,&($$));
	}
      | _WHITE
        {
	  NewColorWithID(WHITE,&($$));
	}
      | _YELLOW
        {
	  NewColorWithID(YELLOW,&($$));
	}
      | _PURPLE
        {
	  NewColorWithID(PURPLE,&($$));
	}
      | _CYAN
        {
	  NewColorWithID(CYAN,&($$));
	}
      | _INTEGER '*' color
        {
	  CopyColor(&($$),&($3));
	  ScaleColor((double)$1,&($$));
	}
      | _REAL '*' color
        {
	  CopyColor(&($$),&($3));
	  ScaleColor($1,&($$));
	}
      | color '+' color
        {
	  CopyColor(&($$),&($3));
	  AccumulateColor(&($1),&($$));
	}
      ;

link_color: color
            {
	      CopyColor(&rw_color_default,&($1));
	    }
          |
            {
	      NewColor(DLC_R,DLC_G,DLC_B,&rw_color_default);
	    }
          ;

body_color: color
            {
	      CopyColor(&rw_color_body,&($1));
	    }
          |
            {
	      CopyColor(&rw_color_body,&rw_color_default);
	    }
          ;

joint_defs : _JOINTS joint_list
           ;

joint_list : joint_definition joint_list
           | 
           ;

joint_definition: fix_joint
                | prismatic_joint 
                | revolute_joint
                | crevolute_joint
                | spherical_joint
                | universal_joint
                | sph_sph_joint
                | sph_prs_sph_joint
                | spring_joint
                | in_patch_joint
                | connection_joint 
                ;

fix_joint : _FIX  ':' any_id any_id
            {
	      HTransformIdentity(&rw_transform);
	    }
            transforms
            {
	      unsigned int id1,id2;
		   
	      id1=GetWorldLinkID($3,rw_world);	
	      if (id1==NO_UINT)
		ReadWorlderror("Unkown link (1st id) when defining a fix joint");
		   
	      id2=GetWorldLinkID($4,rw_world);		
	      if (id2==NO_UINT)
		ReadWorlderror("Unkown link (2st id) when allowing a fix joint");

	      NewFixJoint(GetWorldNJoints(rw_world),
			  id1,GetWorldLink(id1,rw_world),
			  id2,GetWorldLink(id2,rw_world),
			  &rw_transform,&rw_joint);

	      AddJoint2World(&rw_joint,rw_world);

	      DeleteJoint(&rw_joint);
	      free($3);
	      free($4);

	      HTransformDelete(&rw_transform);

	      rw_prevolute=FALSE;
	    }
          ;

transforms: transform '*' transforms
          | transform 
          ;

transform : _ID 
            {
	      /* Nothing need to be done */
	    }
          |
            _TX '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformTx($3,&t);
	      
	      HTransformProduct(&rw_transform,&t,&rw_transform);
	    }
          | _TY '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformTy($3,&t);
	      
	      HTransformProduct(&rw_transform,&t,&rw_transform);
	    }
          | _TZ '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformTz($3,&t);
	      
	      HTransformProduct(&rw_transform,&t,&rw_transform);
	    }
          | _TXYZ '(' expr ',' expr ',' expr')'
            {
	      THTransform t;
	      
	      HTransformTxyz($3,$5,$7,&t);
	      
	      HTransformProduct(&rw_transform,&t,&rw_transform);
	    }
          | _RX '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformRx($3,&t);
	      
	      HTransformProduct(&rw_transform,&t,&rw_transform);
	    }
          | _RY '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformRy($3,&t);
	      
	      HTransformProduct(&rw_transform,&t,&rw_transform);
	    }
          | _RZ '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformRz($3,&t);
	      
	      HTransformProduct(&rw_transform,&t,&rw_transform);
	    }
          | _TR '(' expr ',' expr ',' expr ',' expr ';'  expr ',' expr ',' expr ',' expr ';'  expr ',' expr ',' expr ',' expr ')' opt_invert
	    {
	      THTransform t;
	      
	      HTransformIdentity(&t);
	 
	      HTransformSetElement(0,0,$3,&t);
	      HTransformSetElement(0,1,$5,&t);
	      HTransformSetElement(0,2,$7,&t);
	      HTransformSetElement(0,3,$9,&t);
	      HTransformSetElement(1,0,$11,&t);
	      HTransformSetElement(1,1,$13,&t);
	      HTransformSetElement(1,2,$15,&t);
	      HTransformSetElement(1,3,$17,&t);
	      HTransformSetElement(2,0,$19,&t);
	      HTransformSetElement(2,1,$21,&t);
	      HTransformSetElement(2,2,$23,&t);
	      HTransformSetElement(2,3,$25,&t);
	      
	      if ($27<0)
		HTransformInverse(&t,&t);
	      
	      HTransformProduct(&rw_transform,&t,&rw_transform);
	    }
          ;

opt_invert :_INV
             {
	       $$=-1;
             }
           |
             {
	       $$=1;
             }
           ;

prismatic_joint: _PRISMATIC ':'
                 any_id 
                  { 
		    rw_lID1=rw_lID=GetWorldLinkID($3,rw_world); 
		    if (rw_lID1==NO_UINT)
		      ReadWorlderror("Unkown link (1st id) when defining a prismatic joint");

		    rw_i=0;
		  }
                 point pointp
                 any_id
                 { 
		   rw_lID2=rw_lID=GetWorldLinkID($7,rw_world);
		   if (rw_lID2==NO_UINT)
		     ReadWorlderror("Unkown link (2st id) when allowing a prismatic joint");
		 } 
                 point pointp 
                 _RANGE range
                 avoid_limits
		 opt_joint_dynamics
                 {
		   NewPrismaticJoint(GetWorldNJoints(rw_world),
				     rw_lID1,GetWorldLink(rw_lID1,rw_world),
				     rw_lID2,GetWorldLink(rw_lID2,rw_world),
				     rw_point,&rw_range,
				     rw_avoidLimits,rw_avoidLimitsWeight,
				     rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
				     &rw_joint);
		   
		   AddJoint2World(&rw_joint,rw_world);

		   DeleteJoint(&rw_joint);
		   free($3);
		   free($7);

		   rw_prevolute=FALSE;
		 }
                 ;

opt_joint_dynamics : opt_velocity opt_acceleration opt_effort opt_cost opt_friction opt_damping
               ;

opt_velocity : _VELOCITY expr
               {
		 rw_velocity=fabs($2);
	       }
             |
	       {
		 rw_velocity=GetParameter(CT_DEFAULT_MAX_VELOCITY,rw_parameters);
	       }
             ;

opt_acceleration : _ACCELERATION expr
                   {
		     rw_acceleration=fabs($2);
	           }
                 |
	           {
		     rw_acceleration=INF;
	           }
                 ;

etf : _EFFORT
    | _TORQUE
    | _FORCE
    ;

opt_effort : etf expr
             {
	       rw_effort=fabs($2);
	     }
           |
	     {
	       rw_effort=INF;
	     }
           ;

opt_cost : _COST expr
           {
	     rw_cost=fabs($2);
	   }
         |
	   {
	     if (rw_effort<INF)
	       rw_cost=rw_effort*rw_effort;
	     else
	       rw_cost=1.0;
	   }
         ;

opt_friction : _FRICTION expr
               {
		 rw_friction=fabs($2);
	       }
             |
	       {
		 rw_friction=0.0;
	       }
             ;

opt_damping : _DAMPING expr
              {
		rw_damping=fabs($2);
	      }
            |
	      {
		rw_damping=0.0;
	      }
            ;


point : '(' expr ',' expr ',' expr ')'
        {
	  rw_point[rw_i][0]=$2;
	  rw_point[rw_i][1]=$4;
	  rw_point[rw_i][2]=$6;
	  rw_i++;
	}
      | _INTEGER
        {
	  Tpolyhedron *b;
	  
	  if (rw_lID==NO_UINT)
	    ReadWorlderror("Reference to body points can only be used inside joint definition");
	  b=GetLinkBody(0,GetWorldLink(rw_lID,rw_world));
	  GetPolyhedronDefiningPoint($1,rw_point[rw_i],b);
	  rw_i++;
	}
      | _INTEGER ':' _INTEGER
        {
	  Tpolyhedron *b;
	  
	  if (rw_lID==NO_UINT)
	    ReadWorlderror("Reference to body points can only be used inside joint definition");
	  b=GetLinkBody($1,GetWorldLink(rw_lID,rw_world));
	  GetPolyhedronDefiningPoint($3,rw_point[rw_i],b);
	  rw_i++;
	}
      ;

pointp : point
       | '+''(' expr ',' expr ',' expr ')'
         {
	   if (rw_i==0)
	     Error("Incremental vector in a wrong position??");
	   
	   rw_point[rw_i][0]=rw_point[rw_i-1][0]+$3;
	   rw_point[rw_i][1]=rw_point[rw_i-1][1]+$5;
	   rw_point[rw_i][2]=rw_point[rw_i-1][2]+$7;
	   rw_i++;
	 }
       ;

point_list : '(' coordinates3D ')'
           ;

coordinates3D : xyz ';' coordinates3D
              | xyz
              ;

xyz :  expr ',' expr ',' expr
       {
	 if (rw_i==rw_max)
	   {
	     MEM_DUP(rw_X,rw_max,double);
	     MEM_EXPAND(rw_Y,rw_max,double);
	     MEM_EXPAND(rw_Z,rw_max,double);
	   }
	 rw_X[rw_i]=$1;
	 rw_Y[rw_i]=$3;
	 rw_Z[rw_i]=$5;
	 rw_i++;
       }


range : '[' expr ',' expr ']'
        {
	  NewInterval($2,$4,&rw_range);
	  if (EmptyInterval(&rw_range))
	    ReadWorlderror("Empty range");
	}
        ;

revolute_joint: _REVOLUTE ':'
                any_id 
                { 
		  rw_lID1=rw_lID=GetWorldLinkID($3,rw_world);
		  if (rw_lID1==NO_UINT)
		    ReadWorlderror("Unkown link (1st id) when defining a revolute joint");

		  rw_i=0; 
		} 
                point pointp
                any_id
                { 
		  rw_lID2=rw_lID=GetWorldLinkID($7,rw_world);
		  if (rw_lID2==NO_UINT)
		    ReadWorlderror("Unkown link (2st id) when allowing a revolute joint");
		} 
                point pointp
		opt_revolute_range
		opt_joint_dynamics
                {
		  NewRevoluteJoint(GetWorldNJoints(rw_world),rw_r,
				   rw_lID1,GetWorldLink(rw_lID1,rw_world),
				   rw_lID2,GetWorldLink(rw_lID2,rw_world),
				   rw_point,
				   rw_has_limits,rw_has_reference,&rw_range,rw_range_point,
				   rw_avoidLimits,rw_avoidLimitsWeight,NULL,
				   rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
				   &rw_joint);

		  AddJoint2World(&rw_joint,rw_world);

		  DeleteJoint(&rw_joint);
		  free($3);
		  free($7);

		  rw_prevolute=TRUE;
		}
                ;

crevolute_joint: _CREVOLUTE ':'
                 any_id 
                 { 
		   rw_lID1=rw_lID=GetWorldLinkID($3,rw_world);
		   if (rw_lID1==NO_UINT)
		     ReadWorlderror("Unkown link (1st id) when defining a revolute joint");
		   
		   rw_i=0; 
		 } 
                 point pointp
                 any_id 
                 { 
		   rw_lID2=rw_lID=GetWorldLinkID($7,rw_world);
		   if (rw_lID2==NO_UINT)
		     ReadWorlderror("Unkown link (2st id) when allowing a revolute joint");
		 } 
                 point pointp
		 opt_revolute_range
		 opt_joint_dynamics
                 {
		   unsigned int id,k;
		   Tjoint *jp;

		   id=GetWorldNJoints(rw_world);

		   if ((!rw_prevolute)||(id<1))
		     ReadWorlderror("Coupled revolute joints need a previous revolute joint");
		   
		   id=GetWorldNJoints(rw_world);
		   k=id;
		   /* take into account that we can have a chain of coupled joints: determine the
		      original non-coupled joints (only revolute joints can be coupled) */
		   do {
		     k--;
		     jp=GetWorldJoint(k,rw_world);
		   } while ((k>0)&&(GetJointType(jp)==REV_JOINT)&&(CoupledWith(jp)!=NO_UINT));
		   if ((GetJointType(jp)!=REV_JOINT)||(CoupledWith(jp)!=NO_UINT))
		     Error("Error defining a chain of coupled revolute joints");

		   NewRevoluteJoint(id,rw_r,
				    rw_lID1,GetWorldLink(rw_lID1,rw_world),
				    rw_lID2,GetWorldLink(rw_lID2,rw_world),
				    rw_point,
				    rw_has_limits,rw_has_reference,&rw_range,rw_range_point,
				    rw_avoidLimits,rw_avoidLimitsWeight,jp,
				    rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
				    &rw_joint);
		   
		   AddJoint2World(&rw_joint,rw_world);
		   
		   DeleteJoint(&rw_joint);
		   free($3);
		   free($7);

		   rw_prevolute=TRUE;
		 }
                 ;

spherical_joint : _SPHERICAL ':'
                  any_id
                  {
		    rw_lID1=rw_lID=GetWorldLinkID($3,rw_world);
		    if (rw_lID1==NO_UINT)
		      ReadWorlderror("Unkown link (1st id) when defining a spherical joint");

		    rw_i=0; 
		  } 
                  point 
		  any_id 
                  { 
		    rw_lID2=rw_lID=GetWorldLinkID($6,rw_world);
		    if (rw_lID2==NO_UINT)
		      ReadWorlderror("Unkown link (2st id) when allowing a spherical joint");
		    /* skip rw_i==1 (the opt_spherical_range is defined over rw_point[0] and rw_point[2]) 
		       This is implemented in this way for compatibility with the range definiton of the
		       revolute joint which uses 2 points on each link and not just one. */
		    rw_i++;
		  } 
                  point
		  opt_spherical_range
		  opt_joint_dynamics
                  {
		    unsigned int i;
		    /* move point[2] to point[1] since NewSphericalJoint only uses two points */
		    for(i=0;i<3;i++)
		      rw_point[1][i]=rw_point[2][i];
		    NewSphericalJoint(GetWorldNJoints(rw_world),
				      rw_lID1,GetWorldLink(rw_lID1,rw_world),
				      rw_lID2,GetWorldLink(rw_lID2,rw_world),
				      rw_point,
				      rw_has_limits,rw_angle,rw_range_point,
				      rw_avoidLimits,rw_avoidLimitsWeight,
				      rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
				      &rw_joint);
		    
		    AddJoint2World(&rw_joint,rw_world);

		    DeleteJoint(&rw_joint);
		    free($3);
		    free($6);
		    
		    rw_prevolute=FALSE;
		  }
                  ;

universal_joint : _UNIVERSAL ':'
                  any_id 
                  { 
		    rw_lID1=rw_lID=GetWorldLinkID($3,rw_world);
		    if (rw_lID1==NO_UINT)
		      ReadWorlderror("Unkown link (1st id) when defining a universal joint");

		    rw_i=0; 
		  } 
                  point pointp
		  any_id
                  { 
		    rw_lID2=rw_lID=GetWorldLinkID($7,rw_world);

		    if (rw_lID2==NO_UINT)
		      ReadWorlderror("Unkown link (2nd id) when defining a universal joint");
		  } 
                  point pointp
		  opt_universal_range
		  opt_joint_dynamics
                  {
		    NewUniversalJoint(GetWorldNJoints(rw_world),rw_r,
				      rw_lID1,GetWorldLink(rw_lID1,rw_world),
				      rw_lID2,GetWorldLink(rw_lID2,rw_world),
				      rw_point,
				      rw_has_limits,rw_has_reference,
				      &rw_range0,&rw_range,rw_range_point,
				      rw_avoidLimits,rw_avoidLimitsWeight,
				      rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
				      &rw_joint);
		    
		    AddJoint2World(&rw_joint,rw_world);
		    
		    DeleteJoint(&rw_joint);
		    free($3);
		    free($7);

		    rw_prevolute=FALSE;
		  }
		;

sph_sph_joint: _SPH_SPH _IDENTIFIER ':'
               any_id
               { 
		 rw_lID1=rw_lID=GetWorldLinkID($4,rw_world);
		 if (rw_lID1==NO_UINT)
		   ReadWorlderror("Unkown link (1st id) when defining a spherical-spherical joint");

		 rw_i=0; 
	       } 
               point 
	       any_id
               { 
		 rw_lID2=rw_lID=GetWorldLinkID($7,rw_world);
		 if (rw_lID2==NO_UINT)
		   ReadWorlderror("Unkown link (2st id) when defining a spherical-spherical joint");
	       } 
               point
	       _LENGTH expr
	       _RADIUS expr
	       granularity link_color shape_status
	       opt_link_dynamics
	       opt_joint_dynamics
               {
		 Tinterval zero,length;

		 NewInterval($11,$11,&length);
		 NewInterval(0.0,0.0,&zero);

		 AddLeg2World($2,               /* link name */
			      FALSE,            /* non-planar */
			      LEG,              /* a normal leg */
			      rw_lID1,rw_lID2,  /* connected links */
			      rw_point,         /* connection points on links */
			      &length,          /* length */
			      0.0,              /* stiffness */
			      &zero,            /* rest */
			      &zero,            /* force range */
			      $13,              /* radius */
			      $14,              /* granularity */
			      &rw_color_default,/* color */
			      $16,              /* shape_status */
			      rw_mass,rw_imatrix,&rw_iframe,
			      rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
			      rw_world);
		 
		 DeleteInterval(&length);
		 DeleteInterval(&zero);
		 if ($2!=NULL)
		   free($2);
		 free($4);
		 free($7);

		 rw_prevolute=FALSE;
	       }
             ;

sph_prs_sph_joint: _SPH_PRS_SPH _IDENTIFIER ':'
                   any_id 
                   { 
		     rw_lID1=rw_lID=GetWorldLinkID($4,rw_world);
		     if (rw_lID1==NO_UINT)
		       ReadWorlderror("Unkown link (1st id) when defining a spherical-spherical joint");
		     
		     rw_i=0; 
		   } 
                   point 
	           any_id
                   { 
		     rw_lID2=rw_lID=GetWorldLinkID($7,rw_world);
		     if (rw_lID2==NO_UINT)
		       ReadWorlderror("Unkown link (2st id) when defining a spherical-spherical joint");
		   }  
                   point
		   _RANGE range 
		   _RADIUS expr 
		   granularity link_color shape_status
		   opt_joint_dynamics
                   {
		     Tinterval zero;
		     
		     NewInterval(0.0,0.0,&zero);

		     AddLeg2World($2,                /* link name */
				  FALSE,             /* non-planar */
				  PRISMATIC_LEG,     /* a prismatic leg */
				  rw_lID1,rw_lID2,   /* connected links */
				  rw_point,          /* connection points on links */
				  &rw_range,         /* length */
				  0.0,               /* stiffness */
				  &zero,             /* rest */
				  &zero,             /* force range */
				  $13,               /* radius */
				  $14,               /* granularity */
				  &rw_color_default, /* color */
				  $16,               /* shape_status */
				  rw_mass,rw_imatrix,&rw_iframe,
				  rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
				  rw_world);

		     DeleteInterval(&zero);
		     if ($2!=NULL)
		       free($2);
		     free($4);
		     free($7);

		     rw_prevolute=FALSE;
		   }
                 ;

spring_type : _XYSPRING
              {
		$$=0;
	      }
            | _SPRING
              {
		$$=1;
	      }
	    ;

spring_joint: spring_type _IDENTIFIER ':'
              any_id 
              { 
		rw_lID1=rw_lID=GetWorldLinkID($4,rw_world);
		if (rw_lID1==NO_UINT)
		  ReadWorlderror("Unkown link (1st id) when defining a spherical-spherical joint");
		
		rw_i=0; 
	      } 
              point 
	      any_id
	      { 
		rw_lID2=rw_lID=GetWorldLinkID($7,rw_world);
		if (rw_lID2==NO_UINT)
		  ReadWorlderror("Unkown link (2st id) when defining a spherical-spherical joint");
	      }  
              point
	      _RANGE range 
	      _RADIUS expr
	      granularity link_color shape_status
	      opt_rest
	      opt_stiffness
	      opt_joint_dynamics
	      {
		Tinterval zero,rest;
		     
		NewInterval(0,0,&zero);
		NewInterval(rw_rest,rw_rest,&rest);

		AddLeg2World($2,                /* link name */
			     ($1==0),           /* planar / non-planar */
			     KSPRING,           /* a spring leg */
			     rw_lID1,rw_lID2,   /* connected links */
			     rw_point,          /* connection points on links */
			     &rw_range,         /* length */
			     rw_stiffness,      /* stiffness*/
			     &rest,             /* rest */
			     &zero,             /* force range (0) */
			     $13,               /* radius */
			     $14,               /* granularity */
			     &rw_color_default, /* color */
			     $16,               /* shape_status */
			     rw_mass,rw_imatrix,&rw_iframe,
			     rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
			     rw_world);

		DeleteInterval(&zero);
		DeleteInterval(&rest);
	       
		free($2);
		free($4);
		free($7);

		rw_prevolute=FALSE;
	      }
              ;

opt_rest : _REST expr
           {
	     rw_rest=$2;
	   }
         |
           {
	     rw_rest=0.0;
	   }
         ;

opt_stiffness : _STIFFNESS expr
                {
		  rw_stiffness=$2;
		}
              |
                {
		  rw_stiffness=0.0;
		}
              ;

in_patch_joint : _IN_PATCH ':'
                 any_id 
                 { 
		   rw_lID1=rw_lID=GetWorldLinkID($3,rw_world);
		   if (rw_lID1==NO_UINT)
		     ReadWorlderror("Unkown link (1st id) when defining a in_patch joint");
		   
		   rw_i=0; 
		 } 
                 point pointp
                 {
		   /*save the points in a different location*/
		   unsigned int i,j;

		   for(i=0;i<2;i++)
		     {
		       for(j=0;j<3;j++)
			 rw_in_patch_point[i][j]=rw_point[i][j];
		     }

		   rw_i=0; 
		 }
                 any_id
                 {
		   rw_lID2=rw_lID=GetWorldLinkID($8,rw_world);
		   if (rw_lID2==NO_UINT)
		     ReadWorlderror("Unkown link (2st id) when defining a in_patch joint");
		 }
                 point point point point
                 avoid_limits
		 opt_joint_dynamics
                 {
		   NewInPatchJoint(GetWorldNJoints(rw_world),
				   rw_lID1,GetWorldLink(rw_lID1,rw_world),
				   rw_lID2,GetWorldLink(rw_lID2,rw_world),
				   rw_in_patch_point,rw_point,
				   rw_avoidLimits,rw_avoidLimitsWeight,
				   rw_velocity,rw_acceleration,rw_effort,rw_cost,rw_friction,rw_damping,
				   &rw_joint);
		   
		   AddJoint2World(&rw_joint,rw_world);
		   
		   DeleteJoint(&rw_joint);
		   free($3);
		   free($8);

		   rw_prevolute=FALSE;
		 }
	       ;

connector : _C_CABLE
            {
	      $$=C_CABLE;
	    }
          | _C_SPRING
            {
	      $$=C_SPRING;
	    }
          | _C_LEG
            {
	      $$=C_LEG;
	    }
          ;

connection_joint : connector _IDENTIFIER ':'
                   any_id 
		   { 
		     rw_lID1=rw_lID=GetWorldLinkID($4,rw_world);
		     if (rw_lID1==NO_UINT)
		       ReadWorlderror("Unkown link (1st id) when defining a connection joint");
		     
		      rw_i=0;
		   }
                   point
		   _IDENTIFIER
		   { 
		     rw_lID2=rw_lID=GetWorldLinkID($7,rw_world);
		     if (rw_lID2==NO_UINT)
		       ReadWorlderror("Unkown link (2nd id) when defining a connection joint");
		   }
		   point
		   _RADIUS expr
		   granularity body_color shape_status
	           opt_rest
	           opt_stiffness
		   {
		     Tinterval rest;
		     
		     NewInterval(rw_rest,rw_rest,&rest);
		     
		     InitConnectLink($2,$1,
				     rw_lID1,rw_lID2,rw_point[0],rw_point[1],
				     $11,&rw_color_body,$12,$14,
				     &rest,rw_stiffness,&rw_link);
		     
		     AddLink2World(&rw_link,FALSE,rw_world);

		     DeleteLink(&rw_link);
		     DeleteInterval(&rest);

		     free($2);
		     free($4);
		     free($7);
		   }
                 ;
		   

rpointp : '(' expr ',' expr ',' expr ')'
          {
	    rw_range_point[rw_i][0]=$2;
	    rw_range_point[rw_i][1]=$4;
	    rw_range_point[rw_i][2]=$6;
	    rw_i++;
	  }
        | '+' '(' expr ',' expr ',' expr ')'
          {
	    rw_range_point[rw_i][0]=rw_point[2*rw_i][0]+$3;
	    rw_range_point[rw_i][1]=rw_point[2*rw_i][1]+$5;
	    rw_range_point[rw_i][2]=rw_point[2*rw_i][2]+$7;
	    rw_i++;
          }
        ;

opt_revolute_range: _RANGE
                    {
		      rw_i=0;
	              rw_has_limits=TRUE;
		      rw_has_reference=TRUE;
                    } 
                    range 
                    opt_reference rpointp rpointp
		    avoid_limits
		  | _REFERENCE
                    {
		      rw_i=0;
	              rw_has_limits=FALSE;
		      rw_has_reference=TRUE;
                    } 
                    rpointp rpointp
                  |
                    {
	              rw_has_limits=FALSE;
		      rw_has_reference=FALSE;
	            }
                  ;

opt_reference : _REFERENCE
              |
              ;

opt_spherical_range : _RANGE 
                      {
			rw_i=0;
			rw_has_limits=TRUE;
		      }
                      '[' expr ']'
                      {
			rw_angle=$4;
		      }
                      rpointp rpointp
		      avoid_limits
                    |
                      {
			rw_has_limits=FALSE;
	              }
                    ;

opt_universal_range : _RANGE
                      {
			rw_i=0;
			rw_has_limits=TRUE;
			rw_has_reference=TRUE;
		      } 
                      range 
                      {
			CopyInterval(&rw_range0,&rw_range);
		      }
                      rpointp 
                      range rpointp
		      avoid_limits
		    | _REFERENCE
                      {
			rw_i=0;
			rw_has_limits=FALSE;
			rw_has_reference=TRUE;
		      } 
                      rpointp 
                      rpointp
                    |
                      {
			rw_has_limits=FALSE;
			rw_has_reference=FALSE;
		      }
                    ;

obstacle_defs : _OBSTACLES obstacle_list
              ;

obstacle_list : obstacle_definition obstacle_list
              | 
              ;

obstacle_definition: _IDENTIFIER ':' shape
                     { 
		       if (GetConstantWithName($1,&rw_constants)!=NO_UINT)
			 ReadWorlderror("Obstacle with the name of a constant");

		       if (GetWorldLinkID($1,rw_world)!=NO_UINT)
			 ReadWorlderror("Obstacle with the name of a link");

		       if (GetWorldObstacleID($1,rw_world)!=NO_UINT)
			 ReadWorlderror("Duplicated obstacle");

		       if (!rw_empty_cbody)
			 {
			   AddObstacle2World($1,&rw_cbody,rw_world);

			   DeletePolyhedron(&rw_cbody);
			 }

		       free($1);
		     }

collision_defs : _COLLISIONS collision_list
               ;

collision_list : collision_definition collision_list
               | 
               ;

collision_definition: _CHECK ':' _ALL 
                      {
			CheckAllCollisions(firstLink,firstObject,rw_world);
		      }
                    | _NO _CHECK ':' _ALL
                      {
			NoCheckAllCollisions(firstLink,firstObject,rw_world);
		      }
                    | _CHECK ':' _SELFCOLLISIONS
                      {
			CheckSelfCollisions(firstLink,rw_world);
		      }
                    |  _NO _CHECK ':' _SELFCOLLISIONS
                      {
			NoCheckSelfCollisions(firstLink,rw_world);
		      }
                    | _NO _CHECK ':' _CONNECTED
                      {
			NoCheckConnectedCollisions(firstLink,rw_world);
		      }
                    | _CHECK ':'  any_id 
                      {
			unsigned int id;
			
			id=GetWorldObstacleID($3,rw_world);
			if (id==NO_UINT)
			  ReadWorlderror("Unkown obstacle when activating a collision check");
			
			CheckObstacleCollision(firstLink,id,rw_world);
			
			free($3);
		      }
                    | _NO _CHECK ':' any_id 
                      {
			unsigned int id;
			
			id=GetWorldObstacleID($4,rw_world);
			if (id==NO_UINT)
			  ReadWorlderror("Unkown obstacle when disabling a collision check");
			
			NoCheckObstacleCollision(firstLink,id,rw_world);

			free($4);
		      }
                    | _CHECK ':'  any_id ',' any_id
                      {
			unsigned int id1,id2;
			
			id1=GetWorldLinkID($3,rw_world);
			if (id1==NO_UINT)
			  ReadWorlderror("Unkown link (1st id) when activating a collision check");

			id2=GetWorldLinkID($5,rw_world);
			if (id2==NO_UINT)
			  {
			    id2=GetWorldObstacleID($5,rw_world);
			    if (id2==NO_UINT)
			      ReadWorlderror("Unkown link/obstacle (2st id) when activating a collision check");

			    CheckLinkObstacleCollision(id1,id2,rw_world);
			  }
			else
			  CheckLinkLinkCollision(id1,id2,rw_world);

			free($3);
			free($5);
		      }
                    | _NO _CHECK ':' any_id ',' any_id
                      {
			unsigned int id1,id2;
			
			id1=GetWorldLinkID($4,rw_world);
			if (id1==NO_UINT)
			  ReadWorlderror("Unkown link (1st id) when disabling a collision check");

			id2=GetWorldLinkID($6,rw_world);
			if (id2==NO_UINT)
			  {
			    id2=GetWorldObstacleID($6,rw_world);
			    if (id2==NO_UINT)
			      ReadWorlderror("Unkown link/obstacle (2st id) when disabling a collision check");

			    NoCheckLinkObstacleCollision(id1,id2,rw_world);
			  }
			else
			  NoCheckLinkLinkCollision(id1,id2,rw_world);

			free($4);
			free($6);
		      }
                    ; 

avoid_limits : _AVOID _LIMITS opt_weight
               {
		 rw_avoidLimits=TRUE;
	   
	       }
             |
               {
		 rw_avoidLimits=FALSE;
	       }
             ;

opt_weight : expr
             {
	       rw_avoidLimitsWeight=$1;
	     }
           |
             {
	       rw_avoidLimitsWeight=1.0;
	     }
           ;


included_defs : _INCLUDE include_list
              ;

include_list : include_file include_list
             |
             ;

include_file : _IDENTIFIER ':' _STRING
               {
		 Switch2File($1,rw_world->nl,rw_world->no,GetFilePath(rw_filename),$3);
		 free($1);
		 free($3);
	       }   
             ;

equations_defs : _EQUATIONS
                 _EQFILE ':' _STRING
               {
                  if (rw_eqFile!=NULL)
		    ReadWorlderror("Only one equation file can be included");

                  NEW(rw_eqFile,strlen($4)+1,char);
                  strcpy(rw_eqFile,$4);
                  free($4);
	       }
               ;

%%
/** \endcond */

/*
 *
 */
boolean InitWorldFromFile(Tparameters *p,boolean visualization,boolean error,char *fn,Tworld *w)
{
  boolean ok;
  
  /* First we try to  */
  if (InitTensegrityFromFile(p,fn,w))
    ok=TRUE;
  else
    {
      unsigned int i;
      Tfilename fworld;
      
      CreateFileName(NULL,fn,NULL,WORLD_EXT,&fworld);

      ReadWorldin=fopen(GetFileFullName(&fworld),"r");
      
      if (!ReadWorldin)
	{
	  if (error)
	    {
	      char m[500];

	      sprintf(m,"%.390s could not be read",GetFileFullName(&fworld));
	      Error(m);
	    }
	  ok=FALSE;
	}
      else
	{
	  fprintf(stderr,"Reading world from                : %s\n",GetFileFullName(&fworld));

          rw_eqFile=NULL;

	  NEW(rw_point,4,double*);
	  for(i=0;i<4;i++)
	    NEW(rw_point[i],3,double);

	  NEW(rw_range_point,4,double*);
	  for(i=0;i<4;i++)
	    NEW(rw_range_point[i],3,double);

	  NEW(rw_in_patch_point,2,double*);
	  for(i=0;i<2;i++)
	    NEW(rw_in_patch_point[i],3,double);
	  
	  NEW(rw_imatrix,3,double*);
	  for(i=0;i<3;i++)
	    NEW(rw_imatrix[i],3,double);

	  rw_r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  
	  InitWorld(w); /*Generate an empty world*/

	  InitConstants(&rw_constants); /*An empty set of constants*/

	  /* Indicates whether the previous joint was revolute */
	  rw_prevolute=FALSE;

	  /*Reset the lines numbering*/
	  RWline=1;
	  firstLink=0;
	  firstObject=0;
	  rw_visualization=visualization;

	  /*we initalize the global pointer to make the parameters accesibles to any one inside the YACC module*/
	  rw_world=w;
	  rw_filename=&fworld;
	  rw_parameters=p;

	  /*and process the file*/
	  ReadWorldparse();
  
          if (rw_eqFile!=NULL)
	    {
              Tfilename fcuik;

              /* Need to read equations from a user provided file. The name is given relative to 
	         the path of the world file */
              CreateFileName(GetFilePath(&fworld),rw_eqFile,NULL,CUIK_EXT,&fcuik);
	      fprintf(stderr,"Adding equations from             : %s\n",GetFileFullName(&fcuik));
              GenerateWorldEquations(p,&rw_constants,GetFileFullName(&fcuik),w);
              DeleteFileName(&fcuik);
            }
          else
	    GenerateWorldEquations(p,NULL,NULL,w);
	  
	  DeleteConstants(&rw_constants);

	  for(i=0;i<4;i++)
	    free(rw_point[i]);
	  free(rw_point);

	  for(i=0;i<4;i++)
	    free(rw_range_point[i]);
	  free(rw_range_point);

	  for(i=0;i<2;i++)
	    free(rw_in_patch_point[i]);
	  free(rw_in_patch_point);
	  
	  for(i=0;i<3;i++)
	    free(rw_imatrix[i]);
	  free(rw_imatrix);

	  fclose(ReadWorldin);
	  ok=TRUE;
	} 

      DeleteFileName(&fworld);
    }
  return(ok);
} 
 
