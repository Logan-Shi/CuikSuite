%{ 
/** \cond */
#include "cuiksystem.h"
#include "readcuiksystemtypes.h"

#include "boolean.h"
#include "error.h"
#include "interval.h"
#include "monomial.h"
#include "equations.h"
#include "equation.h"
#include "mequation.h"
#include "kequation.h"
#include "variable.h"
#include "variable_set.h"
#include "defines.h"
#include "parameters.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>

  /*Lex and Yacc variables*/
  extern FILE *Readcuiksystemin; 

  /*Lex and Yacc functions*/
  int Readcuiksystemlex(void); 

  /*Our own variables*/
  extern unsigned int RCSline; /*line number currently processed (incremented by the LEX processor)*/
  
  double rcs_sgn=1.0; /* sign for the monomials added to an equation. */

  Tparameters *rcs_parameters=NULL;

  /*Global pointer to allow the different parts of the parser to acces the equations being initialized*/
  TCuikSystem *rcs_cuiksystem=NULL;
  
  Tequation rcs_equation;
  TMequation rcs_mequation;
  TMequation rcs_vmequation;
  TKequation rcs_kequation;
  Tmonomial rcs_monomial;

  unsigned int rcs_scaleID;
  
  unsigned int rcs_i;
  double **rcs_point;

  double rcs_vect[3];

  unsigned int rcs_eq_type=SYSTEM_EQ;
  unsigned int rcs_var_type=SYSTEM_VAR;

  unsigned int rcs_topology;
  
  Tconstants *rcs_constants;

  /* if true, variable identifiers are prefixed with '_'. This is used in atomatically
     generated equation files (and only internally). We only need to add the prefix
     when adding equations to an automatically generated system (in memory) */
  boolean rcs_prefixID;
  /* space to store the identifiers with prefix */
  char *rcs_ID;
%}

%union 
{ 
  char *id; 
  int int_number;
  double real_number;
  Texpr expr;
} 
 
%start problem

%token _CONSTANTS _SYSTEM_VARS _SECONDARY_VARS _DUMMY_VARS _CARTESIAN_VARS _VELOCITY_VARS _NON_DYNAMIC_VARS _SYSTEM_EQS _COORD_EQS _DUMMY_EQS _VELOCITY_EQS _NON_DYNAMIC_EQS _SEARCH _DEPTH _BREADTH _FIRST _MIN _EQU _LEQ _GEQ _ASSIGN _INF _PI _SIN _COS _TAN _COT _ACOS _ASIN _ATAN _ATAN2 _EXP _PWP _SQRT _ABS _DIFF _PARAMETER _PRINT _TR _TX _TY _TZ _TV _PA _RX _RY _RZ _ID _Z _DRX _DRY _DRZ _DPA_U _DPA_V _DDRX _DDRY _DDRZ _DDPA_UU _DDPA_UV _DDPA_VV _INV _EQUAL _LESS _GREATER

%token <id> _IDENTIFIER
%token <int_number> _INTEGER
%token <real_number> _REAL

%type <expr> expr
%type <int_number> cmp 
%type <int_number> power
%type <int_number> trans_type
%type <int_number> patch_type
%type <int_number> opt_invert

%left _MIN_PRECEDENCE
%left _EQUAL _NOT_EQUAL _LEQ _GEQ _LESS _GREATER
%left '+' '-' 
%left '*' '/'
%left '^'
%left '\''
%right _MAX_PRECEDENCE 
 
%% 

problem: ct_defs var_defs non_dynamic_vars system_eqs coord_eqs dummy_eqs non_dynamic_eqs velocity_eqs search 
       ;

ct_defs : _CONSTANTS ct_list  
        |
        ;
         
ct_list : ct_definition ct_list
        |
        ;

ct_definition: _IDENTIFIER _ASSIGN expr
               {
		 if (GetConstantWithName($1,rcs_constants)!=NO_UINT)
		   {
		     char s[250];
		     
		     sprintf(s,"Duplicated constant %.150s",$1);
		     ReadcuiksystemSemanticError(s);
		   }

		 if ($3.id!=NULL)
		   ReadcuiksystemSemanticError("Constant assigned to a variable");

	         AddConstant($1,$3.value,rcs_constants);
		 free($1);
               }
             | _PRINT _IDENTIFIER
	       {
		 unsigned int nc;
		 
		 nc=GetConstantWithName($2,rcs_constants);
		 if (nc==NO_UINT)
		   {
		     char ms[250];
		     
		     sprintf(ms,"Undefined constant: %.150s",$2);
		     ReadcuiksystemSemanticError(ms);
		   }
		 fprintf(stderr,"  %s = %.12f\n",$2,GetConstantValue(nc,rcs_constants));
		 free($2);
	       }
             ;


expr : '+' expr    %prec _MAX_PRECEDENCE
         {
	   if ($2.id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   $$.id=NULL;
	   $$.value=$2.value;
         }
        | '-' expr    %prec _MAX_PRECEDENCE
         {
	   if ($2.id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   $$.id=NULL;
	   $$.value=-$2.value;
         }
        | expr '+' expr 
         {
	   if (($1.id!=NULL)||($3.id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   $$.id=NULL;
	   $$.value=$1.value+$3.value;
         }
        | expr '-' expr 
         {
	   if (($1.id!=NULL)||($3.id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   $$.id=NULL;
	   $$.value=$1.value-$3.value;
         }
        | expr '*' expr 
         {
	   if (($1.id!=NULL)||($3.id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   $$.id=NULL;
	   $$.value=$1.value*$3.value;
         }
        | expr '^' expr 
         {
	   if (($1.id!=NULL)||($3.id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   $$.id=NULL;
	   $$.value=pow($1.value,$3.value);
         }
        | expr '/' expr 
         {
	   if (($1.id!=NULL)||($3.id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   if ($3.value==0.0)
	     ReadcuiksystemSemanticError("Division by zero");
	   
	   $$.id=NULL;
	   $$.value=$1.value/$3.value;
         }
        | '(' expr ')'
         {
	   if ($2.id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   $$.id=NULL;
	   $$.value=$2.value;
         }
        | '(' expr '?' expr ':' expr ')'
          {
	    if (($2.id!=NULL)||($4.id!=NULL)||($6.id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    if ($2.value)
	      $$.value=$4.value;
	    else
	      $$.value=$6.value;
	  }
        | expr _EQUAL expr 
          {
	    if (($1.id!=NULL)||($3.id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	    $$.id=NULL;
	    $$.value=($1.value==$3.value);
	  }
        | expr _NOT_EQUAL expr 
          {
	    if (($1.id!=NULL)||($3.id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=($1.value!=$3.value);
	  }
        | expr _LEQ expr  
	  {
	    if (($1.id!=NULL)||($3.id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=($1.value<=$3.value);
	  }
        | expr _GEQ expr     
          {
	    if (($1.id!=NULL)||($3.id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=($1.value>=$3.value);
	  }
        | expr _LESS expr        
	  {
	    if (($1.id!=NULL)||($3.id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=($1.value<$3.value);
	  }
        | expr _GREATER expr   
	  {
	    if (($1.id!=NULL)||($3.id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=($1.value>$3.value);
	  }   
        | _PI 
          {
	    $$.id=NULL;
	    $$.value=M_PI;
	  }
        | _INF
          {
	    $$.id=NULL;
	    $$.value=INF;
	  }
        | _SIN '(' expr ')'
          {
	    if ($3.id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=sin($3.value);
	  }
        | _COS '(' expr ')'
          {
	    if ($3.id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=cos($3.value);
	  }
        | _TAN '(' expr ')'
          {
	    if ($3.id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=tan($3.value);
	  }
        | _COT '(' expr ')'
          {
	    if ($3.id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	    $$.id=NULL;
	    $$.value=tan(M_PI_2-$3.value);
	  }
        | _ASIN '(' expr ')'
	  {
	    if ($3.id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	    $$.id=NULL;
	    $$.value=asin($3.value);
	  }
        | _ACOS '(' expr ')'
          {
	    if ($3.id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	    $$.id=NULL;
	    $$.value=acos($3.value);
	  }
        | _ATAN '(' expr ')'
          {
	    if ($3.id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	    $$.id=NULL;
	    $$.value=atan($3.value);
	  }
        | _ATAN2 '(' expr ',' expr ')'
          {
	    if (($3.id!=NULL)||($5.id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    $$.id=NULL;
	    $$.value=atan2($3.value,$5.value);
	  }
        | _EXP '(' expr ')'
         {
	   if ($3.id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	   $$.id=NULL;
	   $$.value=exp($3.value);
	 }
        | _PWP '(' expr ')'
         {
	   if ($3.id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	   $$.id=NULL;
	   if ($3.value<0.0)
	     $$.value=$3.value*$3.value;
	   else
	     $$.value=0.0;
	 }
        | _SQRT '(' expr ')'
         {
	   if ($3.id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	   $$.id=NULL;
	   $$.value=sqrt($3.value);
	 }
        | _ABS '(' expr ')'
         {
	   if ($3.id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	   $$.id=NULL;
	   $$.value=fabs($3.value);
	 }
        | _PARAMETER '(' _IDENTIFIER ')'
          {
	    unsigned int n;
	    
	    n=GetParameterID($3,rcs_parameters);
	    if (n==NO_UINT)
	      {
		char ms[250];
		
		sprintf(ms,"Undefined parameter: %.150s",$3);
		ReadcuiksystemSemanticError(ms);
	      }
	    
	    $$.id=NULL;
	    $$.value=GetParameter(n,rcs_parameters);
	  }
        | _DIFF '(' _IDENTIFIER ')'
         {
	   unsigned int nc;
	   
	   if (rcs_prefixID)
	     ReadcuiksystemSemanticError("Can not use velocity variables in the equation files included into a world file. Velocity variables/equations are automatically defined");
 
	   nc=GetConstantWithName($3,rcs_constants);

	   if (nc!=NO_UINT)
	     {
	       char s[250];
	       
	       sprintf(s,"Constants (%.150s) can not be differentiated",$3);
	       ReadcuiksystemSemanticError(s);
	     }
	   else
	     {
	       NEW(rcs_ID,strlen($3)+20,char);
	       if (rcs_prefixID)
		 sprintf(rcs_ID,"_diff(%s)",$3);
	       else
		 sprintf(rcs_ID,"diff(%s)",$3);
	       
	       if (GetCSVariableID(rcs_ID,rcs_cuiksystem)==NO_UINT) 
		 {
		   char s[250];
		   
		   sprintf(s,"Undefined variable diff(%.150s)",$3);
		   ReadcuiksystemSemanticError(s);
		 }
	       else
		 $$.id=rcs_ID;
	     }
	   free($3);
	 }
        | _IDENTIFIER
         {
	   unsigned int nc;

	   nc=GetConstantWithName($1,rcs_constants);

	   if (nc!=NO_UINT)
	     {
	       $$.id=NULL;
	       $$.value=GetConstantValue(nc,rcs_constants);
	     }
	   else
	     {
	       NEW(rcs_ID,strlen($1)+2,char);
	       if (rcs_prefixID)
		 sprintf(rcs_ID,"_%s",$1);
	       else
		 strcpy(rcs_ID,$1);
	       
	       if (GetCSVariableID(rcs_ID,rcs_cuiksystem)==NO_UINT) 
		 {
		   char s[250];
		   
		   sprintf(s,"Undefined variable %.150s",$1);
		   ReadcuiksystemSemanticError(s);
		 }
	       else
		 $$.id=rcs_ID;
	     }
	   free($1);
	 }
        | _INTEGER
         {
	   $$.id=NULL;
	   $$.value=(double)$1;
         } 
        | _REAL
         {
	   $$.id=NULL;
	   $$.value=$1;
         }
        ; 

var_defs : var_block var_defs 
         | 
         ;

var_block : system_vars
          | secondary_vars
          | dummy_vars
          | cartesian_vars
          | velocity_vars
          ;

system_vars: _SYSTEM_VARS 
             {
	       rcs_var_type=SYSTEM_VAR;
	     }
             range_list
           ;

secondary_vars: _SECONDARY_VARS 
                { 
		  rcs_var_type=SECONDARY_VAR;
	        }
                range_list
	      ;

dummy_vars: _DUMMY_VARS
            { 
	      rcs_var_type=DUMMY_VAR;
	    }
            range_list
          ;

cartesian_vars: _CARTESIAN_VARS 
                {
		  rcs_var_type=CARTESIAN_VAR;	
	        }
                range_list
              ;

velocity_vars: _VELOCITY_VARS 
               {
		 Warning("Velocity variables should be defined automatically and not given in a cuik file. This may lead to an inconsisten system");
		 rcs_var_type=VELOCITY_VAR;
	       }
               vrange_list
             ;

non_dynamic_vars: _NON_DYNAMIC_VARS 
                  {
		    rcs_var_type=NON_DYNAMIC_VAR;
		  }
                  range_list
		|
                ;

range_list: range_definition range_list
          |
          ;

vrange_list: vrange_definition vrange_list
          |
          ;

topology: ':'
          {
	    rcs_topology=TOPOLOGY_R;
	  }
        | '~'
          {
	    rcs_topology=TOPOLOGY_S;
	  }
        ;

range_definition : _IDENTIFIER topology '[' expr ',' expr ']'
                  {
		    Tinterval i_user; 
		    Tvariable v;

		    if (($4.id!=NULL)||($6.id!=NULL))
		      ReadcuiksystemSemanticError("Can not define a range with variables");

		    if (GetConstantWithName($1,rcs_constants)!=NO_UINT)  
		      {
			char s[250];
			
			sprintf(s,"Constant %.150s redefined as a variable",$1);
			ReadcuiksystemSemanticError(s);
		      }
		    
		    NEW(rcs_ID,strlen($1)+2,char);
		    if (rcs_prefixID)
		      sprintf(rcs_ID,"_%s",$1);
		    else
		      strcpy(rcs_ID,$1);
		    
		    if (GetCSVariableID(rcs_ID,rcs_cuiksystem)!=NO_UINT) 
		      {
			char s[250];
			
			sprintf(s,"Repeated range declaration for variable %s",$1);
			ReadcuiksystemSemanticError(s);
		      }
		    
		    if (rcs_topology==TOPOLOGY_S)
		      {
			if ((fabs($4.value+M_PI)>ZERO)||(fabs($6.value-M_PI)>ZERO))
			  {
			    char s[250];
			    
			    sprintf(s,"Circular variable %.150s must have range [-pi,pi]",$1);
			    ReadcuiksystemSemanticError(s);
			  }
			NewInterval(-M_PI,+M_PI,&i_user);
		      }
		    else
		      NewInterval($4.value,$6.value,&i_user);
		    
		    if (EmptyInterval(&i_user))
		      ReadcuiksystemSemanticError("Empty Interval");

		    if ((rcs_prefixID)&&(rcs_var_type==VELOCITY_VAR))
			  ReadcuiksystemSemanticError("Can not define velocity variables in the equation files included into a world file. Velocity variables/equations are automatically defined");
		
		    NewVariable(rcs_var_type,rcs_ID,&v);
		    SetVariableInterval(&i_user,&v);
		    if (rcs_topology==TOPOLOGY_S)
		      SetVariableTopology(TOPOLOGY_S,&v);

		    AddVariable2CS(&v,rcs_cuiksystem);

		    DeleteVariable(&v);
		    free(rcs_ID);
		    free($1);
		  }
                ;

vrange_definition : _DIFF '(' _IDENTIFIER ')' ':' '[' expr ',' expr ']'
                   {
		     Tinterval i_user,c; 
		     Tvariable v;

		     if (($7.id!=NULL)||($9.id!=NULL))
		       ReadcuiksystemSemanticError("Can not define a range with variables");
		     
		     if (rcs_prefixID)
		       ReadcuiksystemSemanticError("Can not define velocity variables in the equation files included into a world file. Velocity variables/equations are automatically defined");
 
		     if (GetConstantWithName($3,rcs_constants)!=NO_UINT)  
		       {
			 char s[250];
			
			 sprintf(s,"Constant %.150s redefined as a velocity variable",$3);
			 ReadcuiksystemSemanticError(s);
		       }
		    
		     NEW(rcs_ID,strlen($3)+10,char);
		     if (rcs_prefixID)
		       sprintf(rcs_ID,"_diff(%s)",$3);
		     else
		       sprintf(rcs_ID,"diff(%s)",$3);
		    
		     if (GetCSVariableID(rcs_ID,rcs_cuiksystem)!=NO_UINT) 
		       {
			 char s[300];
			
			 sprintf(s,"Repeated range declaration for variable diff(%s)",$3);
			 ReadcuiksystemSemanticError(s);
		       }

		     NewInterval(-M_C,M_C,&c);
		     NewInterval($7.value,$9.value,&i_user);
		     Intersection(&c,&i_user,&i_user);
		    
		     if (EmptyInterval(&i_user))
		       ReadcuiksystemSemanticError("Empty Interval");

		     NewVariable(VELOCITY_VAR,rcs_ID,&v);
		     SetVariableInterval(&i_user,&v);

		     AddVariable2CS(&v,rcs_cuiksystem);

		     DeleteVariable(&v);
		     free(rcs_ID);
		     free($3);
		   }
                 ;

system_eqs : _SYSTEM_EQS
             {
	       rcs_eq_type=SYSTEM_EQ;
	     } 
             eq_list
	     meq_list
           |
           ;

coord_eqs : _COORD_EQS 
            {
	      rcs_eq_type=COORD_EQ;
	    }
            eq_list
          |
          ;

dummy_eqs : _DUMMY_EQS 
            {
	      rcs_eq_type=DUMMY_EQ;
	    }
            eq_list
          |
          ;

non_dynamic_eqs : _NON_DYNAMIC_EQS
                  {
	             rcs_eq_type=NON_DYNAMIC_EQ;
		  }
                  eq_list
	          meq_list
                |
                ;

velocity_eqs : _VELOCITY_EQS
               {
		 if (rcs_prefixID)
		   Error("Can not add velocity equations to a world");
		 
		 Warning("Velocity equations should be defined automatically and not given in a cuik file. This may lead to an inconsisten system");
	         rcs_eq_type=VELOCITY_EQ;
	       } 
               eq_list
	       vmeq_list
             |
             ;

search: _SEARCH
        search_type
      |
        { 
	  SetCSSearchMode(DEPTH_FIRST_SEARCH,NULL,rcs_cuiksystem);
        }
      ;

search_type: _DEPTH _FIRST
             {
               SetCSSearchMode(DEPTH_FIRST_SEARCH,NULL,rcs_cuiksystem);
             }
           | _BREADTH _FIRST
             {
               SetCSSearchMode(BREADTH_FIRST_SEARCH,NULL,rcs_cuiksystem);
             }
           | _MIN monomials
             {
	       SetEquationType(SYSTEM_EQ,&rcs_equation);
	       SetEquationCmp(EQU,&rcs_equation);
               SetCSSearchMode(MINIMIZATION_SEARCH,&(rcs_equation),rcs_cuiksystem);
	       ResetEquation(&rcs_equation);
             }
           ;

eq_list: equation 
         {
	   AddEquation2CS(rcs_parameters,&rcs_equation,rcs_cuiksystem);

	   /*Get ready for next equation definition*/
	   ResetEquation(&rcs_equation);
	 }
         eq_list
         |
         ;

equation: monomials cmp 
          {
	    rcs_sgn=-1.0;
          } 
          monomials ';'
          {
	    if ((rcs_prefixID)&&(rcs_eq_type==VELOCITY_EQ))
	      ReadcuiksystemSemanticError("Can not define velocity equations in the equations files included into a world file. Velocity variables/equations are automatically defined");

	    SetEquationType(rcs_eq_type,&rcs_equation);
	    SetEquationCmp($2,&rcs_equation);

	    rcs_sgn=1.0;
	  }
          ;

monomials : opt_sign monomial
          {
	    AddCt2Monomial(rcs_sgn,&rcs_monomial);
	    AddMonomial(&rcs_monomial,&rcs_equation);
	    ResetMonomial(&rcs_monomial);
	  }
          more_monomials
        ;

more_monomials: sign monomial 
              {
		AddCt2Monomial(rcs_sgn,&rcs_monomial);
	        AddMonomial(&rcs_monomial,&rcs_equation);
	        ResetMonomial(&rcs_monomial);
	      }
              more_monomials 
            |
            ;

opt_sign : sign
         |
         ;

sign : '+'
     | '-'
       {
	 AddCt2Monomial(-1.0,&rcs_monomial);
       }
     ;

monomial : item '*' monomial
       | item
       ;

item : _REAL power
       {
	 if ($2==1)
	   AddCt2Monomial($1,&rcs_monomial);
	 else
	   AddCt2Monomial(pow($1,(double)$2),&rcs_monomial);
       } 
     | _INTEGER power
       {
	 if ($2==1)
	   AddCt2Monomial((double)$1,&rcs_monomial);
	 else
	   AddCt2Monomial(pow((double)$1,(double)$2),&rcs_monomial);
       } 
     | _SIN '(' expr ')' power
       {
	 if ($3.id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID($3.id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(SINV,id,$5,&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",$3.id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free($3.id);
	   }
	 else
	   {
	     if ($5==1)
	       AddCt2Monomial(sin($3.value),&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(sin($3.value),(double)$5),&rcs_monomial);  
	   }
       }
     | _COS '(' expr ')' power
       {
	 if ($3.id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID($3.id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(COSV,id,$5,&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",$3.id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free($3.id);
	   }
	 else
	   {
	     if ($5==1)
	       AddCt2Monomial(cos($3.value),&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(cos($3.value),(double)$5),&rcs_monomial);  
	   }  
       }
     | _TAN '(' expr ')' power
       {
	 if ($3.id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID($3.id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(TANV,id,$5,&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",$3.id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free($3.id);
	   }
	 else
	   {
	     if ($5==1)
	       AddCt2Monomial(tan($3.value),&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(tan($3.value),(double)$5),&rcs_monomial);  
	   }  
       }
     | _EXP '(' expr ')' power
       {
	 if ($3.id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID($3.id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(EXPV,id,$5,&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",$3.id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free($3.id);
	   }
	 else
	   {
	     if ($5==1)
	       AddCt2Monomial(exp($3.value),&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(exp($3.value),(double)$5),&rcs_monomial);  
	   }  
       }
     | _PWP '(' expr ')' power
       {
	 if ($3.id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID($3.id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(PWPV,id,$5,&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",$3.id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free($3.id);
	   }
	 else
	   {
	     double v;
	     
	     if ($3.value<0.0)
	       v=$3.value*$3.value;
	     else
	       v=0.0;
	     
	     if ($5==1)
	       AddCt2Monomial(v,&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(v,(double)$5),&rcs_monomial);  
	   }  
       }
     | _PI power
       {
	 AddCt2Monomial(pow(M_PI,(double)($2)),&rcs_monomial);
       }
     | _DIFF '(' _IDENTIFIER ')' power
       {
	 unsigned int id;
	 unsigned int nc;

	 nc=GetConstantWithName($3,rcs_constants);

	 if (nc!=NO_UINT)
	   {
	     char s[250];
	     
	     sprintf(s,"Constants have no differential %.150s",$3);
	     ReadcuiksystemSemanticError(s);
	   }
	 else
	   { 
	     NEW(rcs_ID,strlen($3)+20,char);
	     if (rcs_prefixID)
	       sprintf(rcs_ID,"_diff(%.150s)",$3);
	     else
	       sprintf(rcs_ID,"diff(%.150s)",$3);
	     
	     id=GetCSVariableID(rcs_ID,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       {
		 if (rcs_prefixID)
		   ReadcuiksystemSemanticError("Can not define velocity variables in the equation files included into a world file. Velocity variables/equations are automatically defined");
	    
		 AddVariable2Monomial(NFUN,id,$5,&rcs_monomial);
	       }
	     else
	       {
		 char s[300];
		 
		 sprintf(s,"Unknown variable diff(%.150s)",$3);
		 ReadcuiksystemSemanticError(s);
	       }
	     free(rcs_ID);
	   }
	 free($3);
       }
     | _IDENTIFIER power
       {
	 unsigned int id;
	 unsigned int nc;

	 nc=GetConstantWithName($1,rcs_constants);

	 if (nc!=NO_UINT)
	   AddCt2Monomial(pow(GetConstantValue(nc,rcs_constants),(double)($2)),&rcs_monomial);
	 else
	   {
	     if (rcs_prefixID)
	       {
		 NEW(rcs_ID,strlen($1)+2,char);
		 sprintf(rcs_ID,"_%s",$1);
	       }
	     else
	       rcs_ID=$1;
	     
	     id=GetCSVariableID(rcs_ID,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(NFUN,id,$2,&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable or constant %.150s",rcs_ID);
		 ReadcuiksystemSemanticError(s);
	       }
	     if (rcs_prefixID)
	       free(rcs_ID);
	   }
	 free($1);
       }
     ;

power : '^' _INTEGER
        {
	  $$=$2;
	}
      |
        {
	  $$=1;
	}
      ;

cmp : _EQU
      {
        $$=EQU;
      }
    | _LEQ
      {
        $$=LEQ;
      }
    | _GEQ
      {
        $$=GEQ;
      }
    ;

meq_list: mequation _EQU  _ID  ';'
          {   
	    IdentityRHSMEquation(&rcs_mequation);
	    SimplifyMEquation(&rcs_mequation);
	    if ((rcs_prefixID)||(rcs_eq_type==NON_DYNAMIC_EQ))
	      MarkAsNonDynamicMEquation(&rcs_vmequation);
	    AddMatrixEquation2CS(rcs_parameters,&rcs_mequation,rcs_cuiksystem);

	    ResetMEquation(&rcs_mequation);
	  }
          meq_list
        |
        ;

vmeq_list: mequation_list _EQU  _Z  ';'
           {
	     ZeroRHSMEquation(&rcs_vmequation); // Not necessary but...
	     MarkAsVelocityMEquation(&rcs_vmequation);
	     SimplifyMEquation(&rcs_vmequation);
	     AddMatrixEquation2CS(rcs_parameters,&rcs_vmequation,rcs_cuiksystem);
	     /* Matrix equations with more than one term can not be reset -> destroy + allocate */
	     DeleteMEquation(&rcs_vmequation);	 
	   }
           vmeq_list
         |
         ;

mequation_list : mequation_list '+' scaled_mequation
	         {
		   ZeroRHSMEquation(&rcs_mequation);
		   AccumulateMEquations(rcs_scaleID,&rcs_mequation,&rcs_vmequation);
		   ResetMEquation(&rcs_mequation);
		 }
               | scaled_mequation
	         {
		   ZeroRHSMEquation(&rcs_mequation);
		   CopyMEquation(&rcs_vmequation,&rcs_mequation); /* This already initializes vmequation */
		   if (rcs_scaleID!=NO_UINT)
		     ScaleMEquation(rcs_scaleID,&rcs_vmequation);
		   ResetMEquation(&rcs_mequation);
		 }
               ;

scaled_mequation : mequation scale_mequation
                 ;

scale_mequation : '*' _DIFF '(' _IDENTIFIER ')'
                  {
		    char vname[250];

		    if (rcs_prefixID)
		      sprintf(vname,"_diff(%.150s)",$4);
		    else
		      sprintf(vname,"diff(%.150s)",$4);
		    rcs_scaleID=GetCSVariableID(vname,rcs_cuiksystem);
		    if (rcs_scaleID==NO_UINT) /*a known variable*/
		      {
			char s[300];
		 
			sprintf(s,"Unknown velocity variable diff(%.150s)",$4);
			ReadcuiksystemSemanticError(s);
		      }
		    free($4);
		  }
                |
                  {
		    rcs_scaleID=NO_UINT;
		  }
                ;


mequation : mequation '*' mitem  
          | mitem
          ;  

mitem: _TR '(' expr ',' expr ',' expr ',' expr ';'  expr ',' expr ',' expr ',' expr ';'  expr ',' expr ',' expr ',' expr ')' opt_invert
       {
	 THTransform t;

	 if (($3.id!=NULL)||($5.id!=NULL)||($7.id!=NULL)||($9.id!=NULL)||
	     ($11.id!=NULL)||($13.id!=NULL)||($15.id!=NULL)||($17.id!=NULL)||
	     ($19.id!=NULL)||($21.id!=NULL)||($23.id!=NULL)||($25.id!=NULL))
	   ReadcuiksystemSemanticError("Error defining a constant transform");
	 
	 HTransformIdentity(&t);
	 
	 HTransformSetElement(0,0,$3.value,&t);
	 HTransformSetElement(0,1,$5.value,&t);
	 HTransformSetElement(0,2,$7.value,&t);
	 HTransformSetElement(0,3,$9.value,&t);
	 HTransformSetElement(1,0,$11.value,&t);
	 HTransformSetElement(1,1,$13.value,&t);
	 HTransformSetElement(1,2,$15.value,&t);
	 HTransformSetElement(1,3,$17.value,&t);
	 HTransformSetElement(2,0,$19.value,&t);
	 HTransformSetElement(2,1,$21.value,&t);
	 HTransformSetElement(2,2,$23.value,&t);
	 HTransformSetElement(2,3,$25.value,&t);
	 
	 if ($27<0)
	   HTransformInverse(&t,&t);
	 
	 AddCtTrans2MEquation(&t,&rcs_mequation);
	 
	 HTransformDelete(&t);
       }
     | _TV '(' expr ',' expr ',' expr ',' expr ')' opt_invert
       {
	 unsigned int nv,nc;
	 double ctValue;
	 boolean constant;

	 /* Translation along a vector */

	 if (($3.id!=NULL)||($5.id!=NULL)||($7.id!=NULL))
	   ReadcuiksystemSemanticError("Error defining a TV transform");
	 
	 constant=FALSE;
	 if ($9.id==NULL)
	   {
	     constant=TRUE;
	     ctValue=(double)$11*$9.value;
	   }
	 else
	   {
	     nc=GetConstantWithName($9.id,rcs_constants);
	     if (nc!=NO_UINT)
	       {
		 constant=TRUE;
		 ctValue=(double)$11*GetConstantValue(nc,rcs_constants);
	       }
	   }

	 if (constant)
	   {
	     /* Actually defining a ct transform */
	     THTransform t;

	     HTransformTxyz(ctValue*$3.value,ctValue*$5.value,ctValue*$7.value,&t);
	     AddCtTrans2MEquation(&t,&rcs_mequation); 
	     HTransformDelete(&t);
	   }
	 else
	   {
	     nv=GetCSVariableID($9.id,rcs_cuiksystem);
	     
	     rcs_vect[0]=$3.value;
	     rcs_vect[1]=$5.value;
	     rcs_vect[2]=$7.value;

	     AddDispTrans2MEquation($11,nv,rcs_vect,&rcs_mequation);
	   }
	 if ($9.id!=NULL)
	   free($9.id);
       }  
     | trans_type '(' expr ')' opt_invert
       {
	 unsigned int nv,nc;
	 double ctValue;
	 boolean constant;

	 constant=FALSE;
	 if ($3.id==NULL)
	   {
	     constant=TRUE;
	     ctValue=(double)$5*$3.value;
	   }
	 else
	   {
	     nc=GetConstantWithName($3.id,rcs_constants);
	     if (nc!=NO_UINT)
	       {
		 constant=TRUE;
		 ctValue=(double)$5*GetConstantValue(nc,rcs_constants);
	       }
	   }

	 if (constant)
	   {
	     /* Actually defining a ct transform */
	     THTransform t;

	     if (($1!=TX)&&($1!=TY)&&($1!=TZ)&&($1!=RX)&&($1!=RY)&&($1!=RZ))
	       ReadcuiksystemSemanticError("Only basic transforms (Tx,Ty,Tz,Rx,Ry,Rz) can be set to constant");
	       
	     HTransformCreate($1,ctValue,&t);
	     AddCtTrans2MEquation(&t,&rcs_mequation); 
	     HTransformDelete(&t);
	   }
	 else
	   {
	     nv=GetCSVariableID($3.id,rcs_cuiksystem);
	     AddVarTrans2MEquation($1,$5,nv,&rcs_mequation);
	   }	 
	 if ($3.id!=NULL)
	   free($3.id);
       }
     | patch_type '(' four_points ';'  _IDENTIFIER ',' _IDENTIFIER ')' opt_invert
       {
	 unsigned int u,v;

	 u=GetCSVariableID($5,rcs_cuiksystem);
	 if (u==NO_UINT) 
	   {
	     char s[250];
	     
	     sprintf(s,"Undefined variable %.150s",$5);
	     ReadcuiksystemSemanticError(s);
	   }

	 v=GetCSVariableID($7,rcs_cuiksystem);
	 if (v==NO_UINT) 
	   {
	     char s[250];
	     
	     sprintf(s,"Undefined variable %.150s",$7);
	     ReadcuiksystemSemanticError(s);
	   }

	 AddPatchTrans2MEquation($1,$9,u,v,rcs_point,&rcs_mequation);
       }
     ;

opt_invert : _INV
             {
	       $$=-1;
             }
           |
             {
	       $$=1;
             }
           ;

trans_type : _TX
             {
	       $$=TX;
	     }
           | _TY
             {
	       $$=TY;
	     }
           | _TZ
             {
	       $$=TZ;
	     }
           | _RX
             {
	       $$=RX;
	     }
           | _RY
             {
	       $$=RY;
	     }
           | _RZ
             {
	       $$=RZ;
	     }
           | _DRX
             {
	       $$=dRX;
	     }
           | _DRY
             {
	       $$=dRY;
	     }
           | _DRZ
             {
	       $$=dRZ;
	     }
           | _DDRX
             {
	       $$=ddRX;
	     }
           | _DDRY
             {
	       $$=ddRY;
	     }
           | _DDRZ
	     {
	       $$=ddRZ;
	     }
           ;

patch_type : _PA
             {
	       $$=PA;
	     }
           | _DPA_U
             {
	       $$=dPA_U;
	     }
           | _DPA_V
             {
	       $$=dPA_V;
	     }
           | _DDPA_UU
             {
	       $$=ddPA_UU;
	     }
           | _DDPA_UV
             {
	       $$=ddPA_UV;
	     }
           | _DDPA_VV
             {
	       $$=ddPA_VV;
	     }
           ;

four_points :  expr ',' expr ',' expr  ';'  expr ',' expr ',' expr ';'  expr ',' expr ',' expr ';'  expr ',' expr ',' expr
               {
		 if (($1.id!=NULL)||($3.id!=NULL)||($5.id!=NULL)||
		     ($7.id!=NULL)||($9.id!=NULL)||($11.id!=NULL)||
		     ($13.id!=NULL)||($15.id!=NULL)||($17.id!=NULL)||
		     ($19.id!=NULL)||($21.id!=NULL)||($23.id!=NULL))
		   ReadcuiksystemSemanticError("Error defining a patch transform");

		 rcs_point[0][0]=$1.value;
		 rcs_point[0][1]=$3.value;
		 rcs_point[0][2]=$5.value;

		 rcs_point[1][0]=$7.value;
		 rcs_point[1][1]=$9.value;
		 rcs_point[1][2]=$11.value;

		 rcs_point[2][0]=$13.value;
		 rcs_point[2][1]=$15.value;
		 rcs_point[2][2]=$17.value;

		 rcs_point[3][0]=$19.value;
		 rcs_point[3][1]=$21.value;
		 rcs_point[3][2]=$23.value;
	       }
            ;

%%
/** \endcond */
/*
 * Reads a file containing the constants definitions, kinematic equations to be solved, 
 * and the range constrains for the variables.
 */
void InitCuikSystemFromFile(Tparameters *p,char *filename,TCuikSystem *cs)
{
  
  /*Start the data structures*/
  InitCuikSystem(cs);

  /*Add information to the data structure */
  AddCuikSystemFromFile(p,FALSE,NULL,filename,cs);
  
  if (GetParameter(CT_DYNAMICS,rcs_parameters)>0)
    AddVelocityEquations(p,NULL,cs);
} 

void AddCuikSystemFromFile(Tparameters *p,boolean prefix,Tconstants *cts,char *filename,TCuikSystem *cs)
{
  unsigned int i;

  rcs_parameters=p;
  
  Readcuiksystemin=fopen(filename,"r");
  if (!Readcuiksystemin) 
    {
      char ErrorText[500];

      sprintf(ErrorText,"File %.450s does not exists",filename);
      Error(ErrorText);
    }
  
  /* If true where are adding equations to a system automatically generated
     from a world file. Then, all variables must be preceeded with a '_' symbol */
  rcs_prefixID=prefix;
  
  /* and re-use the previously defined constants (they can appear in the added equations). */
  if (cts!=NULL)
    MergeConstants(&(cs->constants),cts,&(cs->constants));
  
  rcs_constants=&(cs->constants);
  
  /*Reset the lines numbering*/
  RCSline=1;

  /*we initalize the global pointer to make the parameters accesibles to any one inside the YACC module*/
  rcs_cuiksystem=cs;
  
  /*Get ready for first equation*/
  InitEquation(&rcs_equation);
  InitMEquation(&rcs_mequation);
  InitKEquation(&rcs_kequation);
  InitMonomial(&rcs_monomial);

  /* space for points */
  NEW(rcs_point,4,double *);
  for(i=0;i<4;i++)
    { NEW(rcs_point[i],3,double); }

  /*and process the file*/
  Readcuiksystemparse();

  /* and release structures */
  for(i=0;i<4;i++)
    free(rcs_point[i]);
  free(rcs_point);

  DeleteEquation(&rcs_equation);
  DeleteKEquation(&rcs_kequation);
  DeleteMEquation(&rcs_mequation);
  DeleteMonomial(&rcs_monomial);

  cs->updated=FALSE;
  fclose(Readcuiksystemin);
} 
 
