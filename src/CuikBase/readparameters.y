%{ 
/** \cond */

#include "parameters.h"
#include "error.h"
#include "boolean.h"
#include "defines.h"

#include <stdlib.h> 
#include <stdio.h>
#include <math.h>

  Tparameters *rp_ps; /*global pointer used from inside the parser to refer to the current set of
		       parameter being read*/

  /*Lex and Yacc variables*/
  extern FILE *ReadParametersin; 

  /*Lex and Yacc functions*/
  int ReadParameterslex(void); 

  /*Our own variables*/
  extern unsigned int RPNline; /*line number currently processed (incremented by the LEX processor)*/

%}
%union 
{ 
  double realValue;
} 
 
%start parameters

%token _TRUE _FALSE _OR _AND _NOT _GEQ _LEQ _EQU _PI _COS _SIN _TAN _EXP _LOG _SQRT _INF _EPSILON _REPRESENTATION _SIGMA _SMALL_SIGMA _R _SR _E _CE _DELTA _BETA _RHO _STATE_PERIOD _N_SOLUTIONS _MAX_NEWTON_ITERATIONS _N_DOF _GAMMA _DUMMIFY _SPLIT_TYPE  _SAFE_SIMPLEX _SIMPLIFICATION_LEVEL _LR2TM_Q _LR2TM_S _VDW_RATIO _LINKS _FLINKS _QLINKS _JOINTS _CUT_X _CUT_Y _CUT_Z _COEF_TEMP _NFAIL_MAX _DETECT_BIFURCATIONS _MAX_PLANNING_TIME _MAX_CHARTS _MAX_PLANNING_ITERATIONS _MAX_NODES_RRT _BI_RRT _RRT_GRAPH _DYNAMIC_DOMAIN _CD_ENGINE _SOLID _VCOLLIDE _PQP _FCL _C_FCL _BULLET _C_BULLET _RIGIDCLL _NONE _SAMPLING _TANGENT_SAMPLING _AMBIENT_SAMPLING _KDTREE_SAMPLING _PRETENSION _DYNAMICS _L_TRAPEZOID _L_EULER _L_RK4 _EULER _RK4 _INTEGRATION_TIME _DEFAULT_MAX_VELOCITY _N_DYNAMIC_ACTIONS _DYNAMIC_GOAL_ERROR _G_COMPENSATION _NEG_LM _G_AXIS _X _Y _Z _TAU _LQR_PLANNING_TIME

%token <realValue> _INTEGER
%token <realValue> _REAL

%type <realValue> ct

%type <realValue> expr
%type <realValue> select_axis
%type <realValue> opt_sign

%type <realValue> boolean_value
%type <realValue> rep_type
%type <realValue> col_engine
%type <realValue> sampling_mode
%type <realValue> int_method

%left _MIN_PRECEDENCE
%left '<' '>' _LEQ _GEQ _EQU
%left '+' '-' _OR
%left '*' '/' _AND
%left '^' _NOT
%right _MAX_PRECEDENCE 

%% 

parameters : parameter parameters
           |
	   ;

parameter : _EPSILON '=' expr
            {
	      // 0
	      if ($3<0.0)
		Error("Parameter EPSILON must be greater than (or equal to) 0.0");
	      SetParameter(CT_EPSILON,"EPSILON",$3,rp_ps);
            }
          | _REPRESENTATION '=' rep_type
            {
	      // 1
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter REPRESENTATION must be an integer");
	      SetParameter(CT_REPRESENTATION,"REPRESENTATION",floor($3),rp_ps);
            }
          | _RHO '=' expr
            {
	      // 2
	      if (($3>0.0)&&($3<1.0))
		SetParameter(CT_RHO,"RHO",$3,rp_ps);
	      else
		Error("Parameter RHO must in the interval (0,1)");
	    }
          | _SIGMA '=' expr
            {
	      // 3
	      if ($3<0.0)
		Error("Parameter SIGMA  must be greater than (or equal to) 0.0");
	      SetParameter(CT_SIGMA,"SIGMA",$3,rp_ps);
            }
          | _SMALL_SIGMA '=' expr
            {
	      // 4 
	      if ($3<0.0)
		Error("Parameter SMALL SIGMA  must be greater than (or equal to) 0.0");
	      SetParameter(CT_SMALL_SIGMA,"SMALL_SIGMA",$3,rp_ps);
            }
          | _E '=' expr
            {
	      // 5
	      if ($3<0.0)
		Error("Parameter E must be greater than (or equal to) 0.0");
	      SetParameter(CT_E,"E",$3,rp_ps);
            }
         | _CE '=' expr
            {
	      // 6
	      if ($3<0.0)
		Error("Parameter CE must be greater than (or equal to) 0.0");
	      SetParameter(CT_CE,"CE",$3,rp_ps);
            }
          | _R '=' expr
            {
	      // 7
	      if ($3<=0.0)
		Error("Parameter R must be greater than 0.0");
	      SetParameter(CT_R,"R",$3,rp_ps);
            }
          | _SR '=' expr
            {
	      // 8
	      if ($3<0.0)
		Error("Parameter SR must be below 0.0");
	      SetParameter(CT_SR,"SR",$3,rp_ps);
            }
          | _DELTA '=' expr
            {
	      // 9
	      if ($3<0.0)
		Error("Parameter DELTA must be greater than (or equal to) 0.0");
	      SetParameter(CT_DELTA,"DELTA",$3,rp_ps);
            }
          | _BETA '=' expr
            {
	      // 10
	      if ($3<1.0)
		Error("Parameter BETA must be larger or equal to 1");
	      SetParameter(CT_ATLASGBF_BETA,"BETA",$3,rp_ps);
            }
          | _STATE_PERIOD '=' expr
            {
	      // 11
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter STATE_PERIOD  must be an integer");
	      if ($3<0)
		Error("Parameter STATE_PERIOD must be greater than (or equal to) 0");
	      SetParameter(CT_STATE_PERIOD,"STATE_PERIOD",floor($3),rp_ps);
            }   
          | _N_SOLUTIONS '=' expr
            {
	      // 12
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter N_SOLUTIONS must be an integer");
	      if ($3<0)
		Error("Parameter N_SOLUTIONS must be greater than (or equal to) 0");
	      SetParameter(CT_N_SOLUTIONS,"N_SOLUTIONS",floor($3),rp_ps);
	    }
          | _MAX_NEWTON_ITERATIONS '=' expr
            {
	      // 13
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter MAX_NEWTON_ITERATIONS must be an integer");
	      if ($3<0)
		Error("Parameter MAX_NEWTON_ITERATIONS must be greater than (or equal to) 0");
	      
	      SetParameter(CT_MAX_NEWTON_ITERATIONS,"MAX_NEWTON_ITERATIONS",floor($3),rp_ps);
	    }
          | _N_DOF '=' expr
            {
	      // 14
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter N_DOF must be an integer");
	      if ($3<0)
		Error("Parameter N_DOF must be greater than (or equal to) 0");
	      SetParameter(CT_N_DOF,"N_DOF",floor($3),rp_ps);
            }
          | _GAMMA '=' expr
            {
	      // 15
	      if ($3<0)
		Error("Parameter GAMNA must be greater than (or equal to) 0");
	      SetParameter(CT_GAMMA,"GAMMA",$3,rp_ps);
            }
          | _DUMMIFY '=' expr
            {
	      // 16
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter DUMMIFY must be an integer");
	      if ($3<0)
		Error("Parameter DUMMIFY can not be negative");
	      SetParameter(CT_DUMMIFY,"DUMMIFY",floor($3),rp_ps);
            }
          | _SPLIT_TYPE '=' expr
            {
	      // 17
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter SPLIT_TYPE must be an integer");
	      if (($3<0)||($3>2))
		Error("Parameter SPLIT_TYPE must be 0, 1, or 2");
	      SetParameter(CT_SPLIT_TYPE,"SPLIT_TYPE",$3,rp_ps);
            }
          | _SAFE_SIMPLEX '=' expr
	    {
	      // 18
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter SAFE_SIMPLEX must be an integer");
	      if ($3<0)
		Error("Parameter SAFE_SIMPLEX can not be negative");
	      SetParameter(CT_SAFE_SIMPLEX,"SAVE_SIMPLEX",floor($3),rp_ps);
            } 
          | _SIMPLIFICATION_LEVEL '=' expr
            {
	      // 19
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter SIMPLIFICATION_LEVEL must be an integer");
	      if ($3<0)
		Error("Parameter SIMPLIFICATION_LEVEL can not be negative");
	      SetParameter(CT_SIMPLIFICATION_LEVEL,"SIMPLIFICATION_LEVEL",floor($3),rp_ps);
            }
          | _LR2TM_Q '=' expr
            {
	      // 20
	      SetParameter(CT_LR2TM_Q,"LR2TM_Q",$3,rp_ps);
            }  
          | _LR2TM_S '=' expr
            {
	      // 21
	      SetParameter(CT_LR2TM_S,"LR2TM_S",$3,rp_ps);
            }
          | _VDW_RATIO '=' expr
            {
	      // 22
	      if ($3<=0.0)
		Error("Parameter VDW_RATIO must positive");
	      SetParameter(CT_VDW_RATIO,"VDW_RATIO",$3,rp_ps);
            }
          | _CUT_X '=' expr
            {
	      // 23
	      SetParameter(CT_CUT_X,"CUT_X",$3,rp_ps);
            }  
          | _CUT_Y '=' expr
            {
	      // 24
	      SetParameter(CT_CUT_Y,"CUT_Y",$3,rp_ps);
            }  
          | _CUT_Z '=' expr
            {
	      // 25
	      SetParameter(CT_CUT_Z,"CUT_Z",$3,rp_ps);
            }
          | _COEF_TEMP '=' expr
            {
	      // 26
	      SetParameter(CT_COEF_TEMP,"COEF_TEMP",$3,rp_ps);
            }  
          | _NFAIL_MAX '=' expr
            {
	      // 27
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter NFAIL_MAX must be an integer");
	      if ($3<0)
		Error("Parameter NFAIL_MAX can not be negative");
	      SetParameter(CT_NFAIL_MAX,"NFAIL_MAX",floor($3),rp_ps);
            }
          | _DETECT_BIFURCATIONS '=' expr
            {
	      // 28
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter DETECT_BIFURCATIONS must be an integer");
	      if ($3<0)
		Error("Parameter DETECT_BIFURCATIONS can not be negative");
	      SetParameter(CT_DETECT_BIFURCATIONS,"DETECT_BIFURCATIONS",floor($3),rp_ps);
            }
          | _MAX_PLANNING_TIME '=' expr
            {
	      // 29
	      if ($3<=0)
		Error("Parameter MAX_PLANNING_TIME must positive");

	      SetParameter(CT_MAX_PLANNING_TIME,"MAX_PLANNING_TIME",$3,rp_ps);
            }
          | _MAX_PLANNING_ITERATIONS '=' expr
            {
	      // 30
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter MAX_PLANNING_ITERATIONS must be an integer");	      
	      if ($3<1)
		Error("Parameter MAX_PLANNING_ITERATIONS must larger than 0");
	   
	      SetParameter(CT_MAX_PLANNING_ITERATIONS,"MAX_PLANNING_ITERATIONS",floor($3),rp_ps);
            }
          | _MAX_CHARTS '=' expr
            {
	      // 31
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter MAX_CHARTS must be an integer");	      
	      if ($3<1)
		Error("Parameter MAX_CHARTS must larger than 0");
	      if ($3>1000000)
		Error("Parameter MAX_CHARTS must lower than 10000000 (or enlarge the kd-tree)");

	      SetParameter(CT_MAX_CHARTS,"MAX_CHARTS",floor($3),rp_ps);
            }
          | _MAX_NODES_RRT '=' expr
            {
	      // 32
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter MAX_NODES_RRT must be an integer");	     
	      if ($3<1)
		Error("Parameter MAX_NODES_RRT must larger than 1");
	      if ($3>1000000)
		Error("Parameter MAX_NODES_RRT must lower than 10000000 (or enlarge the kd-tree)");
	   
	      SetParameter(CT_MAX_NODES_RRT,"MAX_NODES_RRT",floor($3),rp_ps);
            }
          | _BI_RRT '=' expr
	    {
	      // 33
	      SetParameter(CT_BI_RRT,"BI_RRT",(double)($3>0),rp_ps);
	    }
          | _RRT_GRAPH '=' expr
	    {
	      // 34
	      SetParameter(CT_RRT_GRAPH,"RRT_GRAPH",(double)($3>0),rp_ps);
	    }
          | _DYNAMIC_DOMAIN '=' expr
	    {
	      // 35
	      SetParameter(CT_DYNAMIC_DOMAIN,"DYNAMIC_DOMAIN",$3,rp_ps);
	    }
          | _CD_ENGINE '=' col_engine
            {
	      // 36
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter CD_ENGINE must be an integer");
	      SetParameter(CT_CD_ENGINE,"CD_ENGINE",floor($3),rp_ps);
            }
          | _SAMPLING '=' sampling_mode
            {
	      // 37
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter SAMPLING must be an integer");
	      if ($3<0)
		Error("Parameter SAMPLING can not be negative");
	      SetParameter(CT_SAMPLING,"SAMPLING",floor($3),rp_ps);
            }
          | _PRETENSION '=' expr
            {
	      // 38
	      if ($3<0)
		Error("Parameter PRETENSION must larger than 0");
	      
	      SetParameter(CT_PRETENSION,"PRETENSION",$3,rp_ps);
            }
          | _DYNAMICS '=' int_method
            {
	      // 39
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter DYNAMICS must be an integer");
	      if ($3<0)
		Error("Parameter DYNAMICS must larger than 0");
	      SetParameter(CT_DYNAMICS,"DYNAMICS",floor($3),rp_ps);
            }
          | _INTEGRATION_TIME '=' expr
            {
	      // 40
	      if ($3<0)
		Error("Parameter INTEGRATION_TIME must larger than 0");
	      
	      SetParameter(CT_INTEGRATION_TIME,"INTEGRATION_TIME",$3,rp_ps);
            }
          | _DEFAULT_MAX_VELOCITY '=' expr
            {
	      // 41
	      if ($3<0)
		Error("Parameter DEFAULT_MAX_VELOCITY must larger than 0");
	      
	      SetParameter(CT_DEFAULT_MAX_VELOCITY,"DEFAULT_MAX_VELOCITY",$3,rp_ps);
            }
          | _N_DYNAMIC_ACTIONS '=' expr
            {
	      // 42
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter N_DYNAMIC_ACTIONS must be an integer");
	      if ($3<0)
		Error("Parameter N_DYNAMIC_ACTIONS must larger than 0");
	      
	      SetParameter(CT_N_DYNAMIC_ACTIONS,"N_DYNAMIC_ACTIONS",floor($3),rp_ps);
            }
          | _DYNAMIC_GOAL_ERROR '=' expr
            {
	      // 43
	      if ($3<=0)
		Error("Parameter DYNAMIC_GOAL_ERROR must larger than 0");
	      
	      SetParameter(CT_DYNAMIC_GOAL_ERROR,"DYNAMIC_GOAL_ERROR",$3,rp_ps);
            }
          | _G_COMPENSATION '=' expr
	    {
	      // 44
	      SetParameter(CT_G_COMPENSATION,"G_COMPENSATION",(double)($3>0),rp_ps);
	    }
          | _NEG_LM '=' expr
            {
	      // 45
	      SetParameter(CT_NEG_LM,"NEG_LM",(double)($3>0),rp_ps);
            }
          | _G_AXIS '=' select_axis
            {
	      // 46
	      if (fabs($3-floor($3))>1e-10)
		Error("Parameter G_AXIS  must be an integer");
	      if ($3<0)
		Error("Parameter G_AXIS must non-negative (0:x 1:y 2:z 3:-x 4:-y 5:-z)");
	      if ($3>6)
		Error("Parameter G_AXIS must lower than 6");
	      
	      SetParameter(CT_G_AXIS,"G_AXIS",$3,rp_ps);
            }	  
          | _TAU '=' expr
            {
	      // 47
	      if ($3<=0)
		Error("Parameter TAU must be possitive");
	      
	      SetParameter(CT_TAU,"TAU",$3,rp_ps);
            }	  
          | _LQR_PLANNING_TIME '=' expr
            {
	      // 48
	      if ($3<0)
		Error("Parameter LQR_PLANNING_TIME must be possitive");
	      
	      SetParameter(CT_LQR_PLANNING_TIME,"LQR_PLANNING_TIME",$3,rp_ps);
            }	  
          ;

ct : _EPSILON
     {
       // 0
       if (ParameterSet(CT_EPSILON,rp_ps))
	 $$=GetParameter(CT_EPSILON,rp_ps);
       else
	 Error("Undefined parameter in expression (EPSILON)");
     }

   | _REPRESENTATION
     {
       // 1
       if (ParameterSet(CT_REPRESENTATION,rp_ps))
	 $$=GetParameter(CT_REPRESENTATION,rp_ps);
       else
	 Error("Undefined parameter in expression (REPRESENTATION)");
     }
  | _RHO
    {
      // 2
      if (ParameterSet(CT_RHO,rp_ps))
	$$=GetParameter(CT_RHO,rp_ps);
      else
	Error("Undefined parameter in expression (RHO)");
    }
  | _SIGMA
    {
      // 3
      if (ParameterSet(CT_SIGMA,rp_ps))
	$$=GetParameter(CT_SIGMA,rp_ps);
      else
	Error("Undefined parameter in expression (SIGMA)");
    }
  | _SMALL_SIGMA
    {
      // 4
      if (ParameterSet(CT_SMALL_SIGMA,rp_ps))
	$$=GetParameter(CT_SMALL_SIGMA,rp_ps);
      else
	Error("Undefined parameter in expression (SMALL_SIGMA)");
    }
  | _E
    {
      // 5
      if (ParameterSet(CT_E,rp_ps))
	$$=GetParameter(CT_E,rp_ps);
      else
	Error("Undefined parameter in expression (E)");
    }
  | _CE
     {
       // 6
       if (ParameterSet(CT_CE,rp_ps))
	 $$=GetParameter(CT_CE,rp_ps);
       else
	 Error("Undefined parameter in expression (CE)");
     }
   | _R
     {
       // 7
       if (ParameterSet(CT_R,rp_ps))
	 $$=GetParameter(CT_R,rp_ps);
       else
	 Error("Undefined parameter in expression (R)");
     }
   | _SR
     {
       // 8
       if (ParameterSet(CT_SR,rp_ps))
	 $$=GetParameter(CT_SR,rp_ps);
       else
	 Error("Undefined parameter in expression (SR)");
     }
   | _DELTA
     {
       // 9
       if (ParameterSet(CT_DELTA,rp_ps))
	 $$=GetParameter(CT_DELTA,rp_ps);
       else
	 Error("Undefined parameter in expression (DELTA)");
     }
  | _BETA
    {
      // 10
      if (ParameterSet(CT_ATLASGBF_BETA,rp_ps))
	$$=GetParameter(CT_ATLASGBF_BETA,rp_ps);
      else
	Error("Undefined parameter in expression (BETA)");
    }
  | _STATE_PERIOD
    {
      // 11
      if (ParameterSet(CT_STATE_PERIOD,rp_ps))
	$$=GetParameter(CT_STATE_PERIOD,rp_ps);
      else
	Error("Undefined parameter in expression (STATE_PERIOD)");
    }
  | _N_SOLUTIONS
    {
      // 12
      if (ParameterSet(CT_N_SOLUTIONS,rp_ps))
	$$=GetParameter(CT_N_SOLUTIONS,rp_ps);
      else
	Error("Undefined parameter in expression (N_SOLUTIONS)");
    }
  | _MAX_NEWTON_ITERATIONS
    {
      // 13
      if (ParameterSet(CT_MAX_NEWTON_ITERATIONS,rp_ps))
	$$=GetParameter(CT_MAX_NEWTON_ITERATIONS,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_NEWTON_ITERATIONS)");
    }
  | _N_DOF
    {
      // 14
      if (ParameterSet(CT_N_DOF,rp_ps))
	$$=GetParameter(CT_N_DOF,rp_ps);
      else
	Error("Undefined parameter in expression (N_DOF)");
    }
  | _GAMMA
    {
      // 15
      if (ParameterSet(CT_GAMMA,rp_ps))
	$$=GetParameter(CT_GAMMA,rp_ps);
      else
	Error("Undefined parameter in expression (GAMMA)");
    }
  | _DUMMIFY
    {
      // 15
      if (ParameterSet(CT_DUMMIFY,rp_ps))
	$$=GetParameter(CT_DUMMIFY,rp_ps);
      else
	Error("Undefined parameter in expression (DUMMIFY)");
    }
   | _SPLIT_TYPE
     {
       // 17
       if (ParameterSet(CT_SPLIT_TYPE,rp_ps))
	 $$=GetParameter(CT_SPLIT_TYPE,rp_ps);
       else
	 Error("Undefined parameter in expression (SPLIT_TYPE)");
     }
   | _SAFE_SIMPLEX
    {
      // 18
      if (ParameterSet(CT_SAFE_SIMPLEX,rp_ps))
	$$=GetParameter(CT_SAFE_SIMPLEX,rp_ps);
      else
	Error("Undefined parameter in expression (SAFE_SIMPLEX)");
    }
  | _SIMPLIFICATION_LEVEL
    {
      // 19
      if (ParameterSet(CT_SIMPLIFICATION_LEVEL,rp_ps))
	$$=GetParameter(CT_SIMPLIFICATION_LEVEL,rp_ps);
      else
	Error("Undefined parameter in expression (SIMPLIFICATION_LEVEL)");
    }
  | _LR2TM_Q
    {
      // 20
      if (ParameterSet(CT_LR2TM_Q,rp_ps))
	$$=GetParameter(CT_LR2TM_Q,rp_ps);
      else
	Error("Undefined parameter in expression (LR2TM_Q)");
    }
  | _LR2TM_S
    {
      // 21
      if (ParameterSet(CT_LR2TM_S,rp_ps))
	$$=GetParameter(CT_LR2TM_S,rp_ps);
      else
	Error("Undefined parameter in expression (LR2TM_S)");
    }
  | _VDW_RATIO
    {
      // 22
      if (ParameterSet(CT_VDW_RATIO,rp_ps))
	$$=GetParameter(CT_VDW_RATIO,rp_ps);
      else
	Error("Undefined parameter in expression (VDW_RATIO)");
    }
  | _CUT_X
    {
      // 23
      if (ParameterSet(CT_CUT_X,rp_ps))
	$$=GetParameter(CT_CUT_X,rp_ps);
      else
	Error("Undefined parameter in expression (CUT_X)");
    }
  | _CUT_Y
    {
      // 24
      if (ParameterSet(CT_CUT_Y,rp_ps))
	$$=GetParameter(CT_CUT_Y,rp_ps);
      else
	Error("Undefined parameter in expression (CUT_Y)");
    }
  | _CUT_Z
    {
      // 25
      if (ParameterSet(CT_CUT_Z,rp_ps))
	$$=GetParameter(CT_CUT_Z,rp_ps);
      else
	Error("Undefined parameter in expression (CUT_Z)");
    }
  | _COEF_TEMP
    {
      // 26
      if (ParameterSet(CT_COEF_TEMP,rp_ps))
	$$=GetParameter(CT_COEF_TEMP,rp_ps);
      else
	Error("Undefined parameter in expression (COEF_TEMP)");
    }
  | _NFAIL_MAX
    {
      // 27
      if (ParameterSet(CT_NFAIL_MAX,rp_ps))
	$$=GetParameter(CT_NFAIL_MAX,rp_ps);
      else
	Error("Undefined parameter in expression (N_FAILS)");
    }
  | _DETECT_BIFURCATIONS
    {
      // 28
      if (ParameterSet(CT_DETECT_BIFURCATIONS,rp_ps))
	$$=GetParameter(CT_DETECT_BIFURCATIONS,rp_ps);
      else
	Error("Undefined parameter in expression (DETECT_BIFURCATIONS)");
    }
  | _MAX_PLANNING_TIME
    {
      // 29
      if (ParameterSet(CT_MAX_PLANNING_TIME,rp_ps))
	$$=GetParameter(CT_MAX_PLANNING_TIME,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_PLANNING_TIME)");
    }
  | _MAX_PLANNING_ITERATIONS
    {
      // 30
      if (ParameterSet(CT_MAX_PLANNING_ITERATIONS,rp_ps))
	$$=GetParameter(CT_MAX_PLANNING_ITERATIONS,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_PLANNING_ITERATIONS)");
    }
  | _MAX_CHARTS
    {
      // 31
      if (ParameterSet(CT_MAX_CHARTS,rp_ps))
	$$=GetParameter(CT_MAX_CHARTS,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_CHARTS)");
    }
  | _MAX_NODES_RRT
    {
      // 32
      if (ParameterSet(CT_MAX_NODES_RRT,rp_ps))
	$$=GetParameter(CT_MAX_NODES_RRT,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_NODES_RRT)");
    }
   | _BI_RRT
     {
       // 33
       if (ParameterSet(CT_BI_RRT,rp_ps))
	 $$=GetParameter(CT_BI_RRT,rp_ps);
       else
	 Error("Undefined parameter in expression (BI_RRT)");
     }
   | _RRT_GRAPH
     {
       // 34
       if (ParameterSet(CT_RRT_GRAPH,rp_ps))
	 $$=GetParameter(CT_RRT_GRAPH,rp_ps);
       else
	 Error("Undefined parameter in expression (RRT_GRAPH)");
     }
  | _DYNAMIC_DOMAIN
    {
      // 35
      if (ParameterSet(CT_DYNAMIC_DOMAIN,rp_ps))
	$$=GetParameter(CT_DYNAMIC_DOMAIN,rp_ps);
      else
	Error("Undefined parameter in expression (DYNAMIC_DOMAIN)");
    }
  | _CD_ENGINE
    {
      // 36
      if (ParameterSet(CT_CD_ENGINE,rp_ps))
	$$=GetParameter(CT_CD_ENGINE,rp_ps);
      else
	Error("Undefined parameter in expression (CD_ENGINE)");
    }
  | _SAMPLING
    {
      // 37
      if (ParameterSet(CT_SAMPLING,rp_ps))
	$$=GetParameter(CT_SAMPLING,rp_ps);
      else
	Error("Undefined parameter in expression (SAMPLING)");
    }
  | _PRETENSION
    {
      // 38
      if (ParameterSet(CT_PRETENSION,rp_ps))
	$$=GetParameter(CT_PRETENSION,rp_ps);
      else
	Error("Undefined parameter in expression (PRETENSION)");
    }
  | _DYNAMICS
    {
      //  39
      if (ParameterSet(CT_DYNAMICS,rp_ps))
	$$=GetParameter(CT_DYNAMICS,rp_ps);
      else
	Error("Undefined parameter in expression (DYNAMICS)");
    }
  | _INTEGRATION_TIME
    {
      //40
      if (ParameterSet(CT_INTEGRATION_TIME,rp_ps))
	$$=GetParameter(CT_INTEGRATION_TIME,rp_ps);
      else
	Error("Undefined parameter in expression (INTEGRATION_TIME)");
    }
  | _DEFAULT_MAX_VELOCITY
    {
      // 41
      if (ParameterSet(CT_DEFAULT_MAX_VELOCITY,rp_ps))
	$$=GetParameter(CT_DEFAULT_MAX_VELOCITY,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_VELOCITY)");
    }
  | _N_DYNAMIC_ACTIONS
    {
      // 42
      if (ParameterSet(CT_N_DYNAMIC_ACTIONS,rp_ps))
	$$=GetParameter(CT_N_DYNAMIC_ACTIONS,rp_ps);
      else
	Error("Undefined parameter in expression (N_DYNAMIC_ACTIONS)");
    }
  | _DYNAMIC_GOAL_ERROR
    {
      // 43
      if (ParameterSet(CT_DYNAMIC_GOAL_ERROR,rp_ps))
	$$=GetParameter(CT_DYNAMIC_GOAL_ERROR,rp_ps);
      else
	Error("Undefined parameter in expression (DYNAMIC_GOAL_ERROR)");
    }
   | _G_COMPENSATION
     {
       // 44
       if (ParameterSet(CT_G_COMPENSATION,rp_ps))
	 $$=GetParameter(CT_G_COMPENSATION,rp_ps);
       else
	 Error("Undefined parameter in expression (G_COMPENSATION)");
     }
  | _NEG_LM
    {
      // 45
      if (ParameterSet(CT_NEG_LM,rp_ps))
	$$=GetParameter(CT_NEG_LM,rp_ps);
      else
	Error("Undefined parameter in expression (NEG_LM)");
    }
  | _G_AXIS
    {
      // 46
      if (ParameterSet(CT_G_AXIS,rp_ps))
	$$=GetParameter(CT_G_AXIS,rp_ps);
      else
	Error("Undefined parameter in expression (G_AXIS)");
    }
  | _TAU
    {
      // 47
      if (ParameterSet(CT_TAU,rp_ps))
	$$=GetParameter(CT_TAU,rp_ps);
      else
	Error("Undefined parameter in expression (TAU)");
    }
  | _LQR_PLANNING_TIME
    {
      // 48
      if (ParameterSet(CT_LQR_PLANNING_TIME,rp_ps))
	$$=GetParameter(CT_LQR_PLANNING_TIME,rp_ps);
      else
	Error("Undefined parameter in expression (LQR_PLANNING_TIME)");
    }
  ;

col_engine : _SOLID
             {
	       $$=SOLID;
	     }
           | _VCOLLIDE
             {
	       $$=VCOLLIDE;
	     }
           | _PQP
             {
	       $$=PQP;
	     }
           | _FCL
             {
	       $$=FCL;
	     }
           | _C_FCL
             {
	       $$=C_FCL;
	     }
           | _BULLET
             {
	       $$=BULLET;
	     }
           | _C_BULLET
             {
	       $$=C_BULLET;
	     }
           | _RIGIDCLL
             {
	       $$=RIGIDCLL;
	     }
           | _NONE
             {
	       $$=NOCD;
	     }
           ;

sampling_mode : _TANGENT_SAMPLING
                {
		  $$=TANGENT_SAMPLING;
		}
              | _AMBIENT_SAMPLING
                {
		  $$=AMBIENT_SAMPLING;
		}
              | _KDTREE_SAMPLING
                {
		  #if (_KDTREE!=1)
		    Error("KDTREE_SAMPLING can only be used if the cuik-kdtree library is available");
		  #endif
		  $$=KDTREE_SAMPLING;
		}
              ;

rep_type : _LINKS
         {
	   $$=REP_LINKS;
	 }
         | _FLINKS
         {
	   $$=REP_FLINKS;
	 }
         | _QLINKS
         {
	   $$=REP_QLINKS;
	 }
         | _JOINTS
         {
	   $$=REP_JOINTS;
	 }
         ;

int_method : _NONE
             {
	       $$=0;
	     }
           | _L_TRAPEZOID
             {
	       $$=1;
	     }
           | _L_EULER
             {
	       $$=2;
	     }
           | _L_RK4
             {
	       $$=3;
	     }
           | _EULER
             {
	       $$=4;
	     }
           | _RK4
             {
	       $$=5;
	     }
           | expr
             {
	       $$=$1;
	     }
           ;

select_axis : expr
              {
		$$=$1;
	      }
            | opt_sign _X
	      {
		$$=($1<0?4:1);
	      }
            | opt_sign _Y
	      {
		$$=($1<0?5:2);
	      }
            | opt_sign _Z
	      {
		$$=($1<0?6:3);
	      }
            ;

opt_sign : '+'
           {
	     $$=+1.0;
	   }
         | '-'
           {
	     $$=-1.0;
	   }
         |
           {
	     $$=+1.0;
	   }
         ;

expr : _INTEGER
       {
	 $$=$1;
       }
     | _REAL
       {
	 $$=$1;
       }
     | _PI
       {
	 $$=M_PI;
       }
     | _INF
       {
	 $$=INF;
       }
     | boolean_value
       {
	 $$=$1;
       }
     | ct
       {
	 $$=$1;
       }
     | '+' expr                 %prec _MAX_PRECEDENCE
       {
	 $$=$2;
       }
     | '-' expr                 %prec _MAX_PRECEDENCE
       {
	 $$=-$2;
       }
     | '(' expr ')'
       {
	 $$=$2;
       }
     | '(' expr '?' expr ':' expr ')'
       { 
	 if ($2>0)
	   $$=$4;
	 else
	   $$=$6;
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
     | _COS '(' expr ')'
       {
	 $$=cos($3);
       }
     | _SIN '(' expr ')'
       {
	 $$=sin($3);
       }
     | _TAN '(' expr ')'
       {
	 $$=tan($3);
       }
     | _EXP '(' expr ')'
       {
	 $$=exp($3);
       }
     | _LOG '(' expr ')'
       {
	 $$=log($3);
       }
     | _SQRT '(' expr ')'
       {
	 $$=sqrt($3);
       }
     | _NOT expr
       {
	 if ((fabs($2-floor($2))>1e-10)||($2<0)||($2>1))
	   Error("Boolean operation on a non-logical expresion");
	 $$=!(($2)>0);
       }
     | expr _AND expr
       {
	 if ((fabs($1-floor($1))>1e-10)||($1<0)||($1>1))
	   Error("Boolean operation on a non-logical expresion");	 
	 if ((fabs($3-floor($3))>1e-10)||($3<0)||($3>1))
	   Error("Boolean operation on a non-logical expresion");
	 
	 $$=((($1)>0)&&(($3)>0));
       }
     | expr _OR expr
       {
	 if ((fabs($1-floor($1))>1e-10)||($1<0)||($1>1))
	   Error("Boolean operation on a non-logical expresion");	 
	 if ((fabs($3-floor($3))>1e-10)||($3<0)||($3>1))
	   Error("Boolean operation on a non-logical expresion");
	 
	 $$=((($1)>0)||(($3)>0));
       }
     | expr '<' expr
       { 
	 $$=(($1)<($3));
       }
     | expr '>' expr
       { 
	 $$=(($1)>($3));
       }
     | expr _LEQ expr
       { 
	 $$=(($1)<=($3));
       }
     | expr _GEQ expr
       { 
	 $$=(($1)>=($3));
       }
     | expr _EQU expr
       { 
	 $$=(($1)==($3));
       }
     ;

boolean_value : _TRUE
                {
	          $$=1.0;
                }
              | _FALSE
                {
	          $$=0.0;
                }
              ;

%%
/** \endcond */
boolean ReadParameters(char *file,Tparameters *p)
{
  unsigned int i;
  boolean fileExists;

  ReadParametersin=fopen(file,"r");
  if (!ReadParametersin) 
    fileExists=FALSE;
  else
    {
      fileExists=TRUE;
    
      /*Set up the global pointer to make the parameter structure under initialization
	to be accesible form everywhere in the parser*/
      rp_ps=p;
  
      /*Reset the lines numbering*/
      RPNline=1;

      /*and process the file*/
      ReadParametersparse();

      for(i=0;i<NPARAMETERS;i++)
	{
	  if ((*p)[i].name==NULL)
	    {
	      char ErrorText[200];
	      
	      sprintf(ErrorText,"Parameter number %u is undefined (see sources/parameters.h to see parameter numbering)",i);
	      Error(ErrorText);
	    }
	}

      if (GetParameter(CT_SMALL_SIGMA,p)>GetParameter(CT_SIGMA,p))
	Error("SMALL_SIGMA can not be larger than SIGMA");

      if (GetParameter(CT_EPSILON,p)>GetParameter(CT_SIGMA,p))
	Error("EPSILON can not be larger than SIGMA");

      if (GetParameter(CT_DELTA,p)>=GetParameter(CT_R,p))
	Error("DELTA can not be larger than R");

      fclose(ReadParametersin);
    }

  return(fileExists);
} 
