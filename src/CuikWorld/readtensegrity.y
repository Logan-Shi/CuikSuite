%{ 
/** \cond */
#include "world.h"

#include "boolean.h"
#include "error.h"
#include "vector.h"
#include "polyhedron.h"
#include "error_tensegrity.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
* Definition of the function that initilizes a kinematic equations from a file.
* This is a method of the equations object.
*/

  /*Lex and Yacc variables*/
  extern FILE *ReadTensegrityin;

  /*Lex and Yacc functions*/
  int ReadTensegritylex(void); 

  /*Our own variables*/
  extern unsigned int RTline; /* line number currently processed 
				 (incremented by the LEX processor)*/

  /* different types of tensegrities */ 
  #define NO_TYPE 0
  #define PLANAR  1
  #define SPATIAL 2

  typedef struct {
    unsigned int type; /**< Type of couple: length, stiffness, rest, orientation. */
    unsigned int l1; /**< First link to couple. */
    unsigned int l2; /**< Second link to couple. */
    double scale;    /**< Scale factor of the couple. */
    THTransform t;   /**< Fixed transform. Only used when coupling orientations. */
  } Tcouple;

  /*
    Auxiliary function to copy Tcouple structures.
  */
  void CopyCouple(void *l_dst,void *l_src);
  
  typedef struct {
    unsigned int id;   /**< Identifier of the free flying body. */
    unsigned int n[3]; /**< The nodes used to fix the add on. */
    double **p;        /**< Points used to fix the add on. */ 
  } Taddon;
  
  /*
    Auxiliary function to copy Taddon structures.
  */
  void CopyAddon(void *l_dst,void *l_src);
  /*
    Auxiliary function to delete Taddon structures.
  */
  void DeleteAddon(void *l);
  
  /*Auxiliary variables used along readwordl*/
  double **rt_point;
  unsigned int rt_i;
  unsigned int rt_type;
  unsigned int rt_elementID;
  Tpolyhedron rt_cbody;
  Tconstants rt_constants;
  Tfilename *rt_filename;
  Tvector rt_couples;
  Tvector rt_addons;
  boolean rt_hasStiffness;
  boolean rt_hasForce;
  unsigned int rt_coupleLinkID;
  Tlink *rt_coupleLink;
  unsigned int rt_coupleType;
  boolean rt_free_fly;
  double rt_fly_range[3];
  boolean rt_canFix;
  unsigned int rt_base=NO_UINT;
  Tlink rt_link;
  double rt_mass;
  double **rt_imatrix;
  THTransform rt_iframe;
  double rt_velocity,rt_acceleration,rt_effort,rt_cost,rt_friction,rt_damping;

  /* Global pointer to allow the different parts of the parser to acces the 
     equations being initialized*/
  Tworld *rt_world;

  /* Global pointer to the parameter structure */
  Tparameters *rt_parameters;

%}

%union 
{ 
  char *id; 
  char *string;
  int int_number;
  double real_number;
  Tcolor color;
  Tinterval range;
  THTransform t;
} 

%start tensegrity

%token _CONSTANTS _STRUCTURE _PLANAR _FREE _FLYING _ASSIGN _EQUAL _NOT_EQUAL _LESS_EQUAL _GREATER_EQUAL _LESS _GREATER _PI _EXP _PARAMETER _COS _SIN _TAN _COT _ACOS _ASIN _ATAN _ATAN2 _SQRT _ABS _PRINT _ID _TX _TY _TZ _TXYZ _RX _RY _RZ _OBSTACLES _COLLISIONS _CHECK _DO _NOT _ALL _CONNECTED _BODY _GRANULARITY _STRUT _BAR _CABLE _SPRING _PRISMATIC _LOOPS _STIFFNESS _REST _FORCE _COUPLE _ORIENTATION _FORCES _ADDONS _NO _NULL _FIXED_POINTS _X _Y _Z _BOX _PRISM _SPHERE _CYLINDER _LENGTH _RADIUS _MASS _INERTIAL _FRAME _INERTIA _MATRIX _VELOCITY _ACCELERATION _EFFORT _COST _FRICTION _DAMPING _COLOR _RED _GREEN _BLUE _PURPLE _CYAN _YELLOW _WHITE _BLACK _GREY _DECORATION _HIDDEN

%token <id> _IDENTIFIER
%token <int_number> _INTEGER 
%token <real_number> _REAL
%token <string> _STRING

%type <int_number> couple_element
%type <int_number> opt_granularity
%type <int_number> opt_body_status
%type <int_number> opt_loops
%type <int_number> dim 
%type <real_number> expr 
%type <real_number> opt_scale
%type <real_number> opt_rad
%type <range> opt_rest
%type <range> opt_force
%type <real_number> opt_stiffness
%type <range> range_or_ct
%type <color> color body_color opt_element_color
%type <t> opt_transform trans_seq trans

%left _EQUAL _NOT_EQUAL _LESS_EQUAL _GREATER_EQUAL _LESS _GREATER
%left '+' '-' 
%left '*' '/'
%right _MAX_PRECEDENCE 
%left '^'
%% 

tensegrity : tensegrity def_block
           |
           ;

def_block : constant_defs
          | structure_defs
          | couple_defs
          | fix_point_defs
          | addon_defs
          | forces_defs
          | obstacle_defs 
          | collision_defs
          ;

constant_defs: _CONSTANTS constant_list
             ;

constant_list : constant_definition constant_list
              | 
              ;

constant_definition : _IDENTIFIER _ASSIGN expr
                      {
			if (GetConstantWithName($1,&rt_constants)!=NO_UINT)
			  {
			    char s[200];
			    
			    sprintf(s,"Duplicated constant %.100s",$1);
			    ReadTensegrityerror(s);
			  } 
			
			AddConstant($1,$3,&rt_constants);
			free($1);
		      }
                    | _PRINT _IDENTIFIER
		      {
			unsigned int nc;
	 
			nc=GetConstantWithName($2,&rt_constants);
			if (nc==NO_UINT)
			  {
			    char ms[200];
			    
			    sprintf(ms,"Undefined constant: %.100s",$2);
			    ReadTensegrityerror(ms);
			  }
			fprintf(stderr,"  %s = %.12f\n",$2,GetConstantValue(nc,&rt_constants));
			free($2);
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

	 n=GetParameterID($3,rt_parameters);
	 if (n==NO_UINT)
	   {
	     char ms[200];
	     
	     sprintf(ms,"Undefined parameter: %.100s",$3);
	     ReadTensegrityerror(ms);
	   }
	 $$=GetParameter(n,rt_parameters);
	 
	 free($3);
       }
     | _IDENTIFIER
       {
	 unsigned int nc;
	 
	 nc=GetConstantWithName($1,&rt_constants);
	 
	 if (nc!=NO_UINT)
	   $$=GetConstantValue(nc,&rt_constants);
	 else
	   {
	     char ms[200];
	     
	     sprintf(ms,"Undefined constant: %.100s",$1);
	     ReadTensegrityerror(ms);
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

structure_defs : structure_type structure_list
               ;

structure_type : '[' _STRUCTURE ']'
                 {
		   if (rt_type==NO_TYPE)
		     {
		       rt_type=SPATIAL;
		       rt_free_fly=FALSE;
		       rt_fly_range[0]=rt_fly_range[1]=rt_fly_range[2]==0.0;
		       rt_canFix=TRUE;
		     }
		   else
		     {
		       if (rt_type!=SPATIAL)
			 ReadTensegrityerror("Cannot mix spatial and planar structures");
		     }
		 }
               | '[' _FREE _FLYING _STRUCTURE expr ',' expr ',' expr ']'
                 {
		   if (rt_type==NO_TYPE)
		     {
		       rt_type=SPATIAL;
		       rt_free_fly=TRUE;
		       rt_fly_range[0]=$5;
		       rt_fly_range[1]=$7;
		       rt_fly_range[2]=$9;
		       rt_canFix=FALSE;
		       if ((rt_fly_range[0]<0)||(rt_fly_range[1]<0)||(rt_fly_range[2]<0))
			 ReadTensegrityerror("The free flying range can not be negative");
		     }
		   else
		     {
		       if (rt_type!=SPATIAL)
			 ReadTensegrityerror("Cannot mix spatial and planar structures");
		     }
		 }
               | '[' _PLANAR _STRUCTURE ']'
                 {
		   if (rt_type==NO_TYPE)
		     {
		       rt_type=PLANAR;
		       rt_free_fly=FALSE;
		       rt_fly_range[0]=rt_fly_range[1]=rt_fly_range[2]==0.0;
		       rt_canFix=TRUE;
		     }
		   else
		     {
		       if (rt_type!=PLANAR)
			 ReadTensegrityerror("Cannot mix spatial and planar structures");
		     }
		 }
               | '[' _FREE _FLYING _PLANAR _STRUCTURE expr ',' expr ']'
                 {
		   if (rt_type==NO_TYPE)
		     {
		       rt_type=PLANAR;
		       rt_free_fly=TRUE;
		       rt_fly_range[0]=$6;
		       rt_fly_range[1]=$8;
		       rt_fly_range[2]=0.0;
		       rt_canFix=FALSE;
		       if ((rt_fly_range[0]<0)||(rt_fly_range[1]<0))
			 ReadTensegrityerror("The free flying range can not be negative");
		     }
		   else
		     {
		       if (rt_type!=PLANAR)
			 ReadTensegrityerror("Cannot mix spatial and planar structures");
		     }
		 }

structure_list : basic_element structure_list
               | 
               ;

elementID : _STRUT
            {
	      rt_elementID=STRUT; /* Fixed length. Tension/stiffness is negative */
	    }
          | _BAR
            {
	      rt_elementID=BAR; /* Fixed length. Tension/stiffnes is free */
	    }
          | _CABLE
            {
	      rt_elementID=CABLE; /* Fixed/variable length. Tension/stiffnes is possitive */
	    }
          | _SPRING
            {
	      rt_elementID=SPRING; /* Variable length. Tension/stiffnes is possitive */
	    }
          | _PRISMATIC
            {
	      rt_elementID=PRISMATIC_BAR; /* Variable length. Tension/stiffnes is free */
	    }
          ;


basic_element : elementID _IDENTIFIER ':' _IDENTIFIER  _IDENTIFIER
                _LENGTH range_or_ct
                opt_stiffness
                opt_rest
                opt_force
                opt_rad
                opt_loops
                opt_granularity
                opt_element_color
                opt_body_status
                opt_element_dynamics
                {
		  unsigned int nf0,nf1,nf2,n1,n2;
		  Tlink l;
		  unsigned int k;
		  double **points;
		  double rad;

		  if ((!rt_hasStiffness)&&(!rt_hasForce))
		    ReadTensegrityerror("Stiffness or force must be given");

		  NEW(points,4,double*); /* last two points only used in case of free-flying */
		  for(k=0;k<4;k++)
		    {
		      NEW(points[k],3,double);
		      points[k][0]=points[k][1]=points[k][2]=0.0;
		    }

		  if (rt_free_fly)
		    {
		      Tjoint j;
		      Tinterval range;
		      
		      InitNoRotLink("world0",&l);
		      nf0=AddLink2World(&l,FALSE,rt_world);
		      DeleteLink(&l);
		      
		      InitNoRotLink("world1",&l);
		      nf1=AddLink2World(&l,FALSE,rt_world);
		      DeleteLink(&l);

		      if (rt_type!=PLANAR)
			{
			  InitNoRotLink("world2",&l);
			  nf2=AddLink2World(&l,FALSE,rt_world);
			  DeleteLink(&l);
			}

		      NewInterval(-rt_fly_range[0],rt_fly_range[0],&range);
		      points[1][0]=points[3][0]=1; /* translation along X axis */
		      NewPrismaticJoint(GetWorldNJoints(rt_world),
					nf0,GetWorldLink(nf0,rt_world),
					nf1,GetWorldLink(nf1,rt_world),
					points,&range,
					FALSE,0.0,
					INF,INF,INF,1.0,0.0,0.0,&j);
		      AddJoint2World(&j,rt_world);
		      DeleteJoint(&j);
		      points[1][0]=points[3][0]=0; /* cancel translation along X axis */
		      DeleteInterval(&range);
	      
		      if (rt_type!=PLANAR)
			{
			  NewInterval(-rt_fly_range[1],rt_fly_range[1],&range);
			  points[1][1]=points[3][1]=1; /* translation along Y axis */
			  NewPrismaticJoint(GetWorldNJoints(rt_world),
					    nf1,GetWorldLink(nf1,rt_world),
					    nf2,GetWorldLink(nf2,rt_world),
					    points,&range,
					    FALSE,0.0,
					    INF,INF,INF,1.0,0.0,0.0,&j);
			  AddJoint2World(&j,rt_world);
			  DeleteJoint(&j);
			  points[1][1]=points[3][1]=0; /* cancel translation along Y axis */
			  DeleteInterval(&range);
			}
		      
		    }
		  
		  n1=GetWorldLinkID($4,rt_world);
		  if (n1==NO_UINT)
		    {
		      InitNoRotLink($4,&l);
		      n1=AddLink2World(&l,FALSE,rt_world);
		      DeleteLink(&l);
		    }

		  if (rt_free_fly)
		    {
		      Tjoint j;
		      Tinterval range;

		      if (rt_type==PLANAR)
			{
			  NewInterval(-rt_fly_range[1],rt_fly_range[1],&range);
			  points[1][1]=points[3][1]=1; /* translation along Y axis */
			  NewPrismaticJoint(GetWorldNJoints(rt_world),
					    nf1,GetWorldLink(nf1,rt_world),
					    n1,GetWorldLink(n1,rt_world),
					    points,&range,
					    FALSE,0.0,
					    INF,INF,INF,1.0,0.0,0.0,&j);
			  AddJoint2World(&j,rt_world);
			  DeleteJoint(&j);
			  points[1][1]=points[3][1]=0; /* cancel translation along Y axis */
			  DeleteInterval(&range);
			}
		      else
			{
			  NewInterval(-rt_fly_range[2],rt_fly_range[2],&range);
			  points[1][2]=points[3][2]=1; /* translation along Z axis */
			  NewPrismaticJoint(GetWorldNJoints(rt_world),
					    nf2,GetWorldLink(nf2,rt_world),
					    n1,GetWorldLink(n1,rt_world),
					    points,&range,
					    FALSE,0.0,
					    INF,INF,INF,1.0,0.0,0.0,&j);
			  AddJoint2World(&j,rt_world);
			  DeleteJoint(&j);
			  points[1][2]=points[3][2]=0; /* cancel translation along Z axis */
			  DeleteInterval(&range);
			}
		      		      
		      /* the free-flying mechanism is already set */
		      rt_free_fly=FALSE;

		      /* keepp the identifier of the first link in the tensegrity */
		      rt_base=n1;
		    }
		  
		  n2=GetWorldLinkID($5,rt_world);
		  if (n2==NO_UINT)
		    {
		      InitNoRotLink($5,&l);
		      n2=AddLink2World(&l,FALSE,rt_world);
		      DeleteLink(&l);
		    }


		  /* struts must have negative force */
		  if ((rt_elementID==STRUT)&&(UpperLimit(&($10))>0.0)) 
		    ReadTensegrityerror("Struts work in compression (i.e., negative forces)");

		  /* cables must have positive stiffness */
		  if (((rt_elementID==CABLE)||(rt_elementID==SPRING))&&($8<0))
		    ReadTensegrityerror("Stiffness of cables must be positive");

		  /* cables must have positive force */
		  if (((rt_elementID==CABLE)||(rt_elementID==SPRING))&&(LowerLimit(&($10))<0.0))
		    ReadTensegrityerror("Cables/springs work on tension (i.e., possitive forces)");
		  
		  /* struts and bars must have constant length */
		  if (((rt_elementID==STRUT)||(rt_elementID==BAR))&&(IntervalSize(&($7))>ZERO))
		    ReadTensegrityerror("Struts/bars must have constant length");

		  /* can not have rest length without stiffness */
		  if ((fabs($8)<ZERO)&&(!ZeroInterval(&($9))))
		    ReadTensegrityerror("Wrong stiffness/rest length");
		  
		  /* contant length cables can not have linear force information */
		  if ((rt_elementID==CABLE)&&(IntervalSize(&($7))<ZERO)&&((fabs($8)>ZERO)||(!ZeroInterval(&($9)))))
		    ReadTensegrityerror("Constant length cables can not have stiffness nor rest length");

		  /* springs can not be constant length */
		  if ((rt_elementID==SPRING)&&(IntervalSize(&($7))<ZERO))
		    ReadTensegrityerror("Springs can not have constant length");
		  
		  /* prismatic bars must be properly extensible (upper part must fit inside
		     the lower part) */
		  if ((rt_elementID==PRISMATIC_BAR)&&(IntervalSize(&($7))<ZERO))
		    ReadTensegrityerror("Springs can not have constant length");
		  
		  if ((rt_elementID==PRISMATIC_BAR)&&(LowerLimit(&($7))<IntervalSize(&($7))))
		    ReadTensegrityerror("Wrong length range in prismatic bar");

		  if ($11==0)
		    {
		      /* default radius */
		      if (rt_elementID==SPRING)
			rad=0.00625;
		      else
			{
			  if (rt_elementID==CABLE)
			    rad=0.003125; /* very thin cylinder */
			  else
			    rad=0.025; /* struts, bar, prismatic */
			}
		    }
		  else
		    rad=$11;
		  
		  AddLeg2World($2,                              /* link name */
			       (rt_type==PLANAR),               /* planar */
			       rt_elementID,                    /* element type: strut, bar, ... */
			       n1,n2,                           /* connected links */
			       points,                          /* connection points on links */
			       &($7),                           /* length */
			       $8,                              /* stiffness */
			       &($9),                           /* rest */
			       &($10),                          /* force range */
			       rad,                             /* radius */
			       (rt_elementID==SPRING?$12:$13),  /* granularity/loops */
			       &($14),                          /* color */
			       $15,                             /* shape_status */
			       rt_mass,rt_imatrix,&rt_iframe,
			       rt_velocity,rt_acceleration,rt_effort,rt_cost,rt_friction,rt_damping,
			       rt_world);
		  
		  for(k=0;k<4;k++)
		    free(points[k]);
		  free(points);
		  
		  DeleteInterval(&($7));
		  DeleteInterval(&($9));
		  DeleteInterval(&($10));
		  
		  free($2);
		  free($4);
		  free($5);
		  
		  rt_hasStiffness=FALSE;
		  rt_hasForce=FALSE;
		}
              ;

opt_element_dynamics : opt_link_dynamics opt_joint_dynamics                       
                     ;

opt_link_dynamics : opt_element_mass opt_element_inertialframe opt_element_inertiamatrix
                  ;

opt_joint_dynamics : opt_velocity opt_acceleration opt_effort opt_cost opt_friction opt_damping
                   ;

opt_element_mass : _MASS expr
                   {
		     rt_mass=$2;
		   }
                 |
		   {
		     rt_mass=0.0;
		   }
                 ;

opt_element_inertiamatrix : _INERTIA _MATRIX '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'
                            {
			      rt_imatrix[0][0]= $4; rt_imatrix[0][1]= $6; rt_imatrix[0][2]=$8;
			      rt_imatrix[1][0]= $6; rt_imatrix[1][1]=$10; rt_imatrix[1][2]=$12;
			      rt_imatrix[2][0]= $8; rt_imatrix[2][1]=$12; rt_imatrix[2][2]=$14;
			    }
                          |
                            {
			      rt_imatrix[0][0]= 0.0; rt_imatrix[0][1]= 0.0; rt_imatrix[0][2]= 0.0;
			      rt_imatrix[1][0]= 0.0; rt_imatrix[1][1]= 0.0; rt_imatrix[1][2]= 0.0;
			      rt_imatrix[2][0]= 0.0; rt_imatrix[2][1]= 0.0; rt_imatrix[2][2]= 0.0;
			    }
                          ;

opt_element_inertialframe : _INERTIAL _FRAME
                            {
			      HTransformIdentity(&rt_iframe);
			    }
                            transforms
                          |
			    {
			      HTransformIdentity(&rt_iframe);
			    }
                          ;

opt_velocity : _VELOCITY expr
               {
		 rt_velocity=fabs($2);
	       }
             |
	       {
		 rt_velocity=INF;
	       }
             ;

opt_acceleration : _ACCELERATION expr
                   {
		     rt_acceleration=fabs($2);
	           }
                 |
	           {
		     rt_acceleration=INF;
	           }
                 ;

opt_effort : _EFFORT expr
             {
	       rt_effort=fabs($2);
	     }
           |
	     {
	       rt_effort=INF;
	     }
           ;

opt_cost : _COST expr
             {
	       rt_cost=fabs($2);
	     }
           |
	     {
	       rt_cost=1.0;
	     }
           ;

opt_friction : _FRICTION expr
               {
		 rt_friction=fabs($2);
	       }
             |
	       {
		 rt_friction=0.0;
	       }
             ;

opt_damping : _DAMPING expr
              {
		rt_damping=fabs($2);
	      }
            |
	      {
		rt_damping=0.0;
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
	      
	      HTransformProduct(&rt_iframe,&t,&rt_iframe);
	    }
          | _TY '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformTy($3,&t);
	      
	      HTransformProduct(&rt_iframe,&t,&rt_iframe);
	    }
          | _TZ '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformTz($3,&t);
	      
	      HTransformProduct(&rt_iframe,&t,&rt_iframe);
	    }
          | _TXYZ '(' expr ',' expr ',' expr')'
            {
	      THTransform t;
	      
	      HTransformTxyz($3,$5,$7,&t);
	      
	      HTransformProduct(&rt_iframe,&t,&rt_iframe);
	    }
          | _RX '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformRx($3,&t);
	      
	      HTransformProduct(&rt_iframe,&t,&rt_iframe);
	    }
          | _RY '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformRy($3,&t);
	      
	      HTransformProduct(&rt_iframe,&t,&rt_iframe);
	    }
          | _RZ '(' expr ')'
            {
	      THTransform t;
	      
	      HTransformRz($3,&t);
	      
	      HTransformProduct(&rt_iframe,&t,&rt_iframe);
	    }
          ;


opt_stiffness : _STIFFNESS expr
                {
		  if ((rt_elementID==STRUT)||(rt_elementID==BAR))
		    ReadTensegrityerror("Contant length elements (struts, bars) can not have stiffness (just a force range)");

		  $$=$2;
		  rt_hasStiffness=TRUE;
		}
              |
                {
		  $$=0.0;
		  rt_hasStiffness=FALSE;
		}
              ;

opt_rest : _REST range_or_ct
           {
	     if ((rt_elementID==STRUT)||(rt_elementID==BAR))
	       ReadTensegrityerror("Contant length elements (struts, bars) can not have rest lenght");

	     CopyInterval(&($$),&($2));
	   }
         |
           {
	     NewInterval(0.0,0.0,&($$));
	   }
         ;

opt_force : _FORCE range_or_ct
            {	      
	      CopyInterval(&($$),&($2));
	      rt_hasForce=TRUE;
	    }
          |
            {
	      if (rt_elementID==STRUT)
		NewInterval(-INF,0.0,&($$));
	      else
		{
		  if ((rt_elementID==CABLE)||(rt_elementID==SPRING))
		    NewInterval(0.0,INF,&($$));
		  else
		    NewInterval(-INF,INF,&($$));
		}
	    }
          ;


range_or_ct : '[' expr ',' expr ']'
              {
		NewInterval($2,$4,&($$));
		if (EmptyInterval(&($$)))
		  ReadTensegrityerror("Empty interval");
	      }
            | expr 
              {
		NewInterval($1,$1,&($$));
	      }
            ;

opt_rad : _RADIUS expr
          {
	    $$=$2;
	  }
        |
          {
	    $$=0.0;
	  }
        ;

opt_loops : _LOOPS expr
            {
	      if (rt_elementID!=SPRING)
		ReadTensegrityerror("Loops con only be given for springs. Do you mean granularity?");
	      if ($2<ZERO)
		ReadTensegrityerror("The number of loops must be positive");
	      if ($2-floor($2)>ZERO)
		  ReadTensegrityerror("The number of loops must be a natural number");
		
	      $$=(unsigned int)floor($2);
	    }
          |
	    {
	      $$=80;
	    }
          ;

opt_granularity : _GRANULARITY _INTEGER
                  {
		    if (rt_elementID==SPRING)
		      ReadTensegrityerror("Can not give granularity for springs. Do you mean loops?");
		    if ($2<ZERO)
		      ReadTensegrityerror("The granularity must be positive");
		    if ($2-floor($2)>ZERO)
		      ReadTensegrityerror("The granularity must be a natural number");
		    
		    $$=$2;
		  }
                |
                  {
		    $$=5;
		  }
                ;

opt_element_color : color
                    {
		      CopyColor(&($$),&($1));
		    }
                  |
                    {
		      if ((rt_elementID==CABLE)||(rt_elementID==SPRING))
			NewColor(0,0,1,&($$)); // blue 
		      else
			NewColor(0,0,0,&($$)); // black 
		    }
                  ;

opt_body_status : _HIDDEN
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

couple_defs : _COUPLE couple_list
            ;

couple_list : couple couple_list
            | 
            ;

couple_element : _LENGTH
                 {
		   $$=COUPLE_LENGTH;
		 }
               | _REST
                 {
		   $$=COUPLE_REST;
		 }
               | _FORCE
                 {
		   $$=COUPLE_FORCE;
		 }
               ;

couple : couple_element ':' _IDENTIFIER 
         {
	   rt_coupleType=$1;
	   
	   rt_coupleLinkID=GetWorldLinkID($3,rt_world);
	   if (rt_coupleLinkID==NO_UINT)
	     ReadTensegrityerror("Undefined first link in couple");
		   
	   rt_coupleLink=GetWorldLink(rt_coupleLinkID,rt_world);
	   
	   if ((rt_coupleType==COUPLE_LENGTH)&&(!IsVariableLengthLink(rt_coupleLink)))
	     ReadTensegrityerror("Can not couple the length of fixed-length elements");
	   
	   free($3);
	 }
         coupled_items 
       | _ORIENTATION ':' _IDENTIFIER 
         {
	   rt_coupleType=COUPLE_ORIENTATION;

	   rt_coupleLinkID=GetWorldLinkID($3,rt_world);
	   if (rt_coupleLinkID==NO_UINT)
	     ReadTensegrityerror("Undefined first link in orientation couple");
	 
	   rt_coupleLink=GetWorldLink(rt_coupleLinkID,rt_world);
	   
	   free($3);
	 }
         coupled_orientation_items
       ;

coupled_items : coupled_item coupled_items
              | coupled_item 
              ;

coupled_orientation_items : coupled_orientation_item coupled_orientation_items
                          | coupled_orientation_item 
                          ;

coupled_item : ',' opt_scale _IDENTIFIER
               {
		 Tcouple couple;
		 unsigned int n2;
		 Tlink *l2;

		 n2=GetWorldLinkID($3,rt_world);
		 if (n2==NO_UINT)
		   ReadTensegrityerror("Undefined coupled link");

		 l2=GetWorldLink(n2,rt_world);
	   
		 if ((GetLinkType(rt_coupleLink)!=GetLinkType(l2))||
		     (GetLinkForceModel(rt_coupleLink)!=GetLinkForceModel(l2))||
		     (IsVariableLengthLink(rt_coupleLink)!=IsVariableLengthLink(l2)))
		   ReadTensegrityerror("The two links to couple must be of the same type");
	   
		 couple.type=rt_coupleType;
		 couple.l1=rt_coupleLinkID;
		 couple.l2=n2;
		 couple.scale=$2;
		 HTransformIdentity(&(couple.t));

		 NewVectorElement((void *)&couple,&rt_couples);
		 
		 free($3);
	       }
             ;

coupled_orientation_item : ',' opt_transform _IDENTIFIER
                            {
			      Tcouple couple;
			      unsigned int n2;
	 
			      n2=GetWorldLinkID($3,rt_world);
			      if (n2==NO_UINT)
				ReadTensegrityerror("Undefined coupled link");

			      couple.type=COUPLE_ORIENTATION;
			      couple.l1=rt_coupleLinkID;
			      couple.l2=n2;
			      couple.scale=1.0;
			      HTransformCopy(&(couple.t),&($2));
			      HTransformDelete(&($2));

			      NewVectorElement((void *)&couple,&rt_couples);
			      
			      free($3);
			    }
                         ;

opt_scale : '[' expr ']'
            {
	      $$=$2;
	    }
          |
            {
	      $$=1.0;
	    }
          ;

opt_transform : '[' trans_seq ']'
                {
		  HTransformCopy(&($$),&($2));
		  HTransformDelete(&($2));
		}
              | 
	        {
		  HTransformIdentity(&($$));
		}
              ;

trans_seq : trans '*' trans_seq
            {
	      HTransformProduct(&($1),&($3),&($$));
	      HTransformDelete(&($1));
	      HTransformDelete(&($3));
	    }
          | trans
	    {
	      HTransformCopy(&($$),&($1));
	      HTransformDelete(&($1));
	    }
          ;

trans : _RX '(' expr ')'
        {
	  HTransformRx($3,&($$));
        }
      | _RY '(' expr ')'
        {
	  HTransformRy($3,&($$));
        }
      | _RZ '(' expr ')'
        {
	  HTransformRz($3,&($$));
        }
      ;

fix_point_defs : _FIXED_POINTS fix_point_list
               ;

fix_point_list : fix_point fix_point_list
               |
               ;

fix_point : _IDENTIFIER '(' dim ')' '=' expr
            {
	      unsigned int n1;
	      Tlink *l;

	      if (!rt_canFix)
		ReadTensegrityerror("Free-flying structures can not have fixed points");
	      
	      n1=GetWorldLinkID($1,rt_world);
	      if (n1==NO_UINT)
		ReadTensegrityerror("Undefined link");

	      l=GetWorldLink(n1,rt_world);
		  
	      if (GetLinkType(l)!=LINK_NoRot)
		ReadTensegrityerror("Only nodes can be fixed");
	      
	      if ((IsGroundLink(n1))&&(fabs($6)>ZERO))
		ReadTensegrityerror("The translation of the ground link can only be fixed to 0");
	      
	      SetLinkTrans($3,$6,l);

	      free($1);
	    }
          | _IDENTIFIER '=' '(' expr ',' expr ',' expr ')'
	    {
	      unsigned int n1;
	      Tlink *l;

	      if (!rt_canFix)
		ReadTensegrityerror("Free-flying structures can not have fixed points");
	      
	      n1=GetWorldLinkID($1,rt_world);
	      if (n1==NO_UINT)
		ReadTensegrityerror("Undefined link");

	      l=GetWorldLink(n1,rt_world);
		  
	      if (GetLinkType(l)!=LINK_NoRot)
		ReadTensegrityerror("Only nodes can be fixed");
	      
	      if ((IsGroundLink(n1))&&((fabs($4)>ZERO)||(fabs($6)>ZERO)||(fabs($8)>ZERO)))
		ReadTensegrityerror("The translation of the ground link can only be fixed to 0");
	      
	      SetLinkTrans(0,$4,l); /* X */
	      SetLinkTrans(1,$6,l); /* Y */
	      SetLinkTrans(2,$8,l); /* Z */

	      free($1);
	    }
          ;

dim : _X
      {
	$$=0;
      }
    | _Y
      {
	$$=1;
      }
    | _Z
      {
	$$=2;
      }
    ;

addon_defs : _ADDONS addon_list
           ;

addon_list : addon addon_list
           |
           ;

addon : _IDENTIFIER ':'
        {
	  InitLink($1,0.0,NULL,NULL,&rt_link);
	  free($1);
	}
        shape_list
        '(' expr ',' expr ',' expr ')' _IDENTIFIER
        '(' expr ',' expr ',' expr ')' _IDENTIFIER
        '(' expr ',' expr ',' expr ')' _IDENTIFIER
	opt_link_dynamics
	{
	  Taddon a;
	  Tjoint j;
	  
	  /* Set the dynamical parameters */
	  SetLinkMass(rt_mass,&rt_link);
	  SetLinkInertiaMatrix(rt_imatrix,&rt_link);
	  SetLinkInertialFrame(&rt_iframe,&rt_link);
		   
	  /* Add the geometry as a link */
	  a.id=AddLink2World(&rt_link,FALSE,rt_world);
	  DeleteLink(&rt_link);
	  
	  /* and add a free joint from thw world to the addon */
	  NewFreeJoint(GetWorldNJoints(rt_world),
		       0,GetWorldLink(0,rt_world),
		       a.id,GetWorldLink(a.id,rt_world),
		       INF,INF,INF,1.0,0.0,0.0,
		       &j);
	  AddJoint2World(&j,rt_world);
	  DeleteJoint(&j);
	  
	  a.n[0]=GetWorldLinkID($12,rt_world);

	  NEW(a.p,3,double*);
	  if (a.n[0]==NO_UINT)
	    ReadTensegrityerror("Undefined first anchor node");
	  if (GetLinkType(GetWorldLink(a.n[0],rt_world))!=LINK_NoRot)
	    ReadTensegrityerror("Only nodes can be used to fix addons");
	  NEW(a.p[0],3,double);  
	  a.p[0][0]=$6;
	  a.p[0][1]=$8;
	  a.p[0][2]=$10;
	  
	  a.n[1]=GetWorldLinkID($20,rt_world);
	  if (a.n[1]==NO_UINT)
	    ReadTensegrityerror("Undefined second anchor node");
	  if (GetLinkType(GetWorldLink(a.n[1],rt_world))!=LINK_NoRot)
	    ReadTensegrityerror("Only nodes can be used to fix addons");
	  NEW(a.p[1],3,double);  
	  a.p[1][0]=$14;
	  a.p[1][1]=$16;
	  a.p[1][2]=$18;
	  
	  a.n[2]=GetWorldLinkID($28,rt_world);
	  if (a.n[2]==NO_UINT)
	    ReadTensegrityerror("Undefined third anchor node");
	  if (GetLinkType(GetWorldLink(a.n[2],rt_world))!=LINK_NoRot)
	    ReadTensegrityerror("Only nodes can be used to fix addons");
	  NEW(a.p[2],3,double);  
	  a.p[2][0]=$22;
	  a.p[2][1]=$24;
	  a.p[2][2]=$26;

	  NewVectorElement((void *)&a,&rt_addons);

	  free(a.p[0]);
	  free(a.p[1]);
	  free(a.p[2]);
	  free(a.p);
	  
	  free($12);
	  free($20);
	  free($28);
	}
      ;

shape_list : shape
             {
	       AddBody2Link(&rt_cbody,&rt_link);
	       DeletePolyhedron(&rt_cbody);
	     }
             shape_list
           |
           ;

forces_defs : _FORCES force_list
            ;

force_list : force force_list
           |
           ;

force : _IDENTIFIER '(' expr ',' expr ',' expr ')'
        {
	  unsigned int n1;
	  Tlink *l;
	  
	  n1=GetWorldLinkID($1,rt_world);
	  if (n1==NO_UINT)
	    ReadTensegrityerror("Undefined link");
	  l=GetWorldLink(n1,rt_world);
	  if (!IsForceEquilibriumLink(l))
	    ReadTensegrityerror("Adding forces to a non-equilibrium node");

	  AddForce2Link($3,$5,$7,l);
	  
	  free($1);
        }
      | _NO _NULL _FORCE ':' no_force_list
      ; 

no_force_list : no_force_id ',' no_force_list
              | no_force_id
              ;

no_force_id : _IDENTIFIER
              {
		unsigned int n1;
		Tlink *l;
		
		n1=GetWorldLinkID($1,rt_world);
		if (n1==NO_UINT)
		  ReadTensegrityerror("Undefined link");
		
		l=GetWorldLink(n1,rt_world);
		if (GetLinkType(l)!=LINK_NoRot)
		  ReadTensegrityerror("Only nodes can be in equilibrium");
		
		NoForceEquilibriumLink(l);
		
		free($1);
	      }
            ;
        

obstacle_defs : _OBSTACLES obstacle_list
              ;

obstacle_list : obstacle_definition obstacle_list
              | 
              ;

obstacle_definition: _IDENTIFIER ':' shape
                     { 
		       if (GetConstantWithName($1,&rt_constants)!=NO_UINT)
			 ReadTensegrityerror("Obstacle with the name of a constant");

		       if (GetWorldLinkID($1,rt_world)!=NO_UINT)
			 ReadTensegrityerror("Obstacle with the name of a node");

		       if (GetWorldObstacleID($1,rt_world)!=NO_UINT)
			 ReadTensegrityerror("Duplicated obstacle");

		       AddObstacle2World($1,&rt_cbody,rt_world);

		       DeletePolyhedron(&rt_cbody);

		       free($1);
		     }


shape: _BODY _STRING body_color opt_granularity opt_body_status 
       {
	 Tfilename fb;

	 CreateFileName(GetFilePath(rt_filename),$2,NULL,NULL,&fb);
	 
	 InitPolyhedronFromFile(&fb,&($3),
				 $4,$5,&rt_cbody);

	 DeleteFileName(&fb);
	 free($2);
       }
     | _BOX
       {
	 rt_i=0;
       } 
       point pointp body_color opt_body_status
       {
	 NewBox(rt_point[0][0],rt_point[0][1],rt_point[0][2],
		rt_point[1][0],rt_point[1][1],rt_point[1][2],
		&($5),$6,&rt_cbody);
       }
     | _PRISM
       {
	 rt_i=0;
       }
       point point point expr body_color opt_body_status
       {
	 
	 NewTriangularPrism(rt_point[0],rt_point[1],rt_point[2],
			    $6,
			    &($7),$8,&rt_cbody);
       }
     | _SPHERE  expr  
       {
	 rt_i=0;
       } 
       point body_color opt_granularity opt_body_status
       {
	 NewSphere($2,rt_point[0],&($5),$6,$7,&rt_cbody);
       }
     | _CYLINDER  expr 
       {
	 rt_i=0;
       } 
       point pointp body_color opt_granularity opt_body_status 
       {
	 NewCylinder($2,rt_point[0],rt_point[1],&($6),2*$7,$8,&rt_cbody);
       }
       ;


pointp : point
       | '+''(' expr ',' expr ',' expr ')'
         {
	   if (rt_i==0)
	     Error("Incremental vector in a wrong position??");
	   
	   rt_point[rt_i][0]=rt_point[rt_i-1][0]+$3;
	   rt_point[rt_i][1]=rt_point[rt_i-1][1]+$5;
	   rt_point[rt_i][2]=rt_point[rt_i-1][2]+$7;
	   rt_i++;
	 }
       ;

point : '(' expr ',' expr ',' expr ')'
        {
	  rt_point[rt_i][0]=$2;
	  rt_point[rt_i][1]=$4;
	  rt_point[rt_i][2]=$6;
	  rt_i++;
	}
      ;

color : _COLOR '(' expr ',' expr ',' expr ')'
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



body_color: color
            {
	      CopyColor(&($$),&($1));
	    }
          |
            {
	      NewColor(DLC_R,DLC_G,DLC_B,&($$)); // default color defined in link.h
	    }
          ;


collision_defs : _COLLISIONS collision_list
               ;

collision_list : collision_definition collision_list
               | 
               ;

collision_definition: _CHECK ':' _ALL 
                      {
			CheckAllCollisions(0,0,rt_world);
		      }
                    | _DO _NOT _CHECK ':' _ALL
                      {
			NoCheckAllCollisions(0,0,rt_world);
		      }
                    | _DO _NOT _CHECK ':' _CONNECTED
                      {
			NoCheckConnectedCollisions(0,rt_world);
		      }
                    | _CHECK ':'  _IDENTIFIER 
                      {
			unsigned int id;
			
			id=GetWorldObstacleID($3,rt_world);
			if (id==NO_UINT)
			  ReadTensegrityerror("Unkown obstacle when activating a collision check");
			
			CheckObstacleCollision(0,id,rt_world);
			
			free($3);
		      }
                    | _DO _NOT _CHECK ':' _IDENTIFIER 
                      {
			unsigned int id;
			
			id=GetWorldObstacleID($5,rt_world);
			if (id==NO_UINT)
			  ReadTensegrityerror("Unkown obstacle when disabling a collision check");
			
			NoCheckObstacleCollision(0,id,rt_world);

			free($5);
		      }
                    | _DO _NOT _CHECK ':' _IDENTIFIER ',' _IDENTIFIER 
                      {
			unsigned int id1,id2;
			
			id1=GetWorldLinkID($5,rt_world);
			if (id1==NO_UINT)
			  ReadTensegrityerror("Unkown link (1st id) when disabling a collision check");

			id2=GetWorldLinkID($7,rt_world);
			if (id2==NO_UINT)
			  {
			    id2=GetWorldObstacleID($7,rt_world);
			    if (id2==NO_UINT)
			      ReadTensegrityerror("Unkown link/obstacle (2st id) when disabling a collision check");

			    NoCheckLinkObstacleCollision(id1,id2,rt_world);
			  }
			else
			  {
			    if (id1==id2)
			      ReadTensegrityerror("Repeated link when disabling a collision check");
			    NoCheckLinkLinkCollision(id1,id2,rt_world);
			  }
			
			free($5);
			free($7);
		      }
                    | _CHECK ':' _IDENTIFIER ',' _IDENTIFIER 
                      {
			unsigned int id1,id2;
			
			id1=GetWorldLinkID($3,rt_world);
			if (id1==NO_UINT)
			  ReadTensegrityerror("Unkown link (1st id) when enabling a collision check");

			id2=GetWorldLinkID($5,rt_world);
			if (id2==NO_UINT)
			  {
			    id2=GetWorldObstacleID($5,rt_world);
			    if (id2==NO_UINT)
			      ReadTensegrityerror("Unkown link/obstacle (2st id) when enabling a collision check");

			    CheckLinkObstacleCollision(id1,id2,rt_world);
			  }
			else
			  {
			    if (id1==id2)
			      ReadTensegrityerror("Repeated link when enabling a collision check");
			    CheckLinkLinkCollision(id1,id2,rt_world);
			  }
			
			free($3);
			free($5);
		      }
                    ; 


%%
/** \endcond */

void CopyCouple(void *l_dst,void *l_src)
{
  Tcouple *c_dst,*c_src;

  c_dst=(Tcouple*)l_dst;
  c_src=(Tcouple*)l_src;
  
  c_dst->type=c_src->type;
  c_dst->l1=c_src->l1;
  c_dst->l2=c_src->l2;
  c_dst->scale=c_src->scale;
  HTransformCopy(&(c_dst->t),&(c_src->t));
}
 

void CopyAddon(void *l_dst,void *l_src)
{
  Taddon *a_dst,*a_src;
  unsigned int i,j;
  
  a_dst=(Taddon*)l_dst;
  a_src=(Taddon*)l_src;
  
  a_dst->id=a_src->id;
  for(i=0;i<3;i++)
    a_dst->n[i]=a_src->n[i];

  NEW(a_dst->p,3,double*);
  for(i=0;i<3;i++)
    {
      NEW(a_dst->p[i],3,double);
      for(j=0;j<3;j++)
	a_dst->p[i][j]=a_src->p[i][j];
    }
}

void DeleteAddon(void *l)
{
  Taddon *a;
  unsigned int i;
  
  a=(Taddon*)l;
  
  for(i=0;i<3;i++)
    free(a->p[i]);
  free(a->p);
}

/*
 *
 */
boolean InitTensegrityFromFile(Tparameters *p,char *fn,Tworld *w)
{
  Tfilename ftensegrity;
  boolean ok; 
  
  CreateFileName(NULL,fn,NULL,TENSEGRITY_EXT,&ftensegrity);      

  ReadTensegrityin=fopen(GetFileFullName(&ftensegrity),"r");
  if (!ReadTensegrityin) 
    ok=FALSE;
  else
    {
      unsigned int i;
      unsigned int rep;
      unsigned int col;
      unsigned int dummify;
      unsigned int ncouples;
      unsigned int naddons;
      Tcouple *couple;
      Taddon *addon;

      fprintf(stderr,"Reading tensegrity from           : %s\n",GetFileFullName(&ftensegrity));
      
      rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
      if (rep!=REP_FLINKS)
	{
	  Warning("Switching representation to FLINKS");
	  ChangeParameter(CT_REPRESENTATION,REP_FLINKS,p);
	}
      
      col=(unsigned int)(GetParameter(CT_CD_ENGINE,p));
      if (col!=SOLID)
	{
	  Warning("Switching cd_engine to SOLID");
	  ChangeParameter(CT_CD_ENGINE,SOLID,p);
	}
  
      dummify=(unsigned int)(GetParameter(CT_DUMMIFY,p));
      if (dummify!=0)
	{
	  Warning("Switching dummify to 0");
	  ChangeParameter(CT_DUMMIFY,0,p);
	}
      
      NEW(rt_point,4,double*);
      for(i=0;i<4;i++)
	NEW(rt_point[i],3,double);
      
      NEW(rt_imatrix,3,double*);
      for(i=0;i<3;i++)
	NEW(rt_imatrix[i],3,double);
	  
      InitVector(sizeof(Tcouple),CopyCouple,NULL,100,&rt_couples);
      InitVector(sizeof(Taddon),CopyAddon,DeleteAddon,100,&rt_addons);
      
      InitWorld(w); /*Generate an empty tensegrity*/

      InitConstants(&rt_constants); /*An empty set of constants*/

      /*Reset the lines numbering*/
      RTline=1;

      /* No defined type */
      rt_type=NO_TYPE;

      /* flags used in element definition. At least one of them must be given */
      rt_hasStiffness=FALSE;
      rt_hasForce=FALSE;
      
      /*we initalize the global pointer to make the parameters accesibles to any one inside the YACC module*/
      rt_world=w;
      rt_filename=&ftensegrity;
      rt_parameters=p;

      /*and process the file*/
      ReadTensegrityparse();

      /* The constatns are not needed any more */
      DeleteConstants(&rt_constants); 

      /* Verify that we have something */
      if (rt_type==NO_TYPE)
	ReadTensegrityerror("Tensegrity without structure?");

      /* Generate the kinematic equations */
      GenerateWorldEquations(p,NULL,NULL,w); /* NULL,NULL -> no user provided equations added */

      /* Planar structure are in the XY plane */
      if (rt_type==PLANAR)
	FixZToZero(p,w);

      /* Generate the force equilibrium equations */
      GenerateForceEquilibriumEquations(p,w);

      /* Fix some of the tensegrit nodes */
      FixLinks(p,w);

      /* Add an equation to the base of the tensegrity. In this way the
         translation variables are in the system (avoids problems with
	 translation between original-simplified-dof systems) */
      ncouples=VectorSize(&rt_couples);
      for(i=0;i<ncouples;i++)
	{
	  couple=(Tcouple*)GetVectorElement(i,&rt_couples);
	  WorldCoupleTensegrityVariable(p,
					couple->type,couple->l1,couple->l2,
					couple->scale,&(couple->t),
					w);
	}

      /* Add the equations fixing the addons to the tensegrity structure */
      naddons=VectorSize(&rt_addons);
      for(i=0;i<naddons;i++)
	{
	  addon=(Taddon*)GetVectorElement(i,&rt_addons);
	  WorldFixTensegrityAddon(rt_parameters,addon->id,addon->p,addon->n,w);
	}

      /* Release memory */
      DeleteVector(&rt_addons);
      DeleteVector(&rt_couples);
      for(i=0;i<4;i++)
	free(rt_point[i]);
      free(rt_point);
      for(i=0;i<3;i++)
	free(rt_imatrix[i]);
      free(rt_imatrix);

      fclose(ReadTensegrityin);

      /* if we reached this point it means we correctly defined a 
	 tensegrity structure */
      ok=TRUE;
    }
  
  DeleteFileName(&ftensegrity);
  
  return(ok);
} 
 
