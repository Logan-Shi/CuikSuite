
==========================================================================
Random seed: 1632297321
==========================================================================
% **************************************************
% COMPILATION FLAGS:
%   DEBUG: 1
%   SIMPLEX ENGINE: clp
%   MPI: 1
%   OpenMP: 1
%   Lapack: 1
%   Cblas: 1
%   KDTree: 1
%
% PARAMETERS:
   EPSILON = 1e-06
   REPRESENTATION = FLINKS
   RHO = 0.4
   SMALL_SIGMA = 0.0001
   SIGMA = 0.1
   E = 0.4
   CE = 0.4
   R = 0.4
   SR = 1.25
   DELTA = 0.04
   BETA = 1.1
   STATE_PERIOD = 1000
   N_SOLUTIONS = 0
   MAX_NEWTON_ITERATIONS = 0
   N_DOF = 0
   GAMMA = 4
   DUMMIFY = 1
   SPLIT_TYPE = 1
   SAVE_SIMPLEX = 6
   SIMPLIFICATION_LEVEL = 2
   LR2TM_Q = 0.25
   LR2TM_S = 0.1
   VDW_RATIO = 0.8
   CUT_X = 0
   CUT_Y = 0
   CUT_Z = 0
   COEF_TEMP = 1.1
   NFAIL_MAX = 10
   DETECT_BIFURCATIONS = 0
   MAX_PLANNING_TIME = 600
   MAX_PLANNING_ITERATIONS = 10001
   MAX_CHARTS = 150000
   MAX_NODES_RRT = 250000
   BI_RRT = 1
   RRT_GRAPH = 1
   DYNAMIC_DOMAIN = 0
   CD_ENGINE = SOLID
   SAMPLING = TANGENT_SAMPLING
   PRETENSION = 1
   DYNAMICS = 0
   INTEGRATION_TIME = 0
   DEFAULT_MAX_VELOCITY = 100
   N_DYNAMIC_ACTIONS = 0
   DYNAMIC_GOAL_ERROR = 0.4
   G_COMPENSATION = 0
   NEG_LM = 0
   G_AXIS = -Z
   TAU = 1
   LQR_PLANNING_TIME = 0

==========================================================================
Equations from file: /home/logan/Downloads/CuikSuite3/bash/../examples/Welding/Welding0D.cuik
% Kinematic equations

[SYSTEM VARS]
   link1_u_x : [-1,1]
   link1_u_y : [-1,1]
   link1_u_z : [-1,1]
   link1_v_x : [-1,1]
   link1_v_y : [-1,1]
   link1_v_z : [-1,1]
   link1_w_x : [-1,1]
   link1_w_y : [-1,1]
   link1_w_z : [-1,1]
   link2_u_x : [-1,1]
   link2_u_y : [-1,1]
   link2_u_z : [-1,1]
   link2_v_x : [-1,1]
   link2_v_y : [-1,1]
   link2_v_z : [-1,1]
   link2_w_x : [-1,1]
   link2_w_y : [-1,1]
   link2_w_z : [-1,1]
   link3_u_x : [-1,1]
   link3_u_y : [-1,1]
   link3_u_z : [-1,1]
   link3_v_x : [-1,1]
   link3_v_y : [-1,1]
   link3_v_z : [-1,1]
   link3_w_x : [-1,1]
   link3_w_y : [-1,1]
   link3_w_z : [-1,1]

[SYSTEM EQS]
   link1_u_x^2+link1_u_y^2+link1_u_z^2 = 1;
   link1_v_x^2+link1_v_y^2+link1_v_z^2 = 1;
   link1_u_x*link1_w_x+link1_u_y*link1_w_y+link1_u_z*link1_w_z = 0;
   link1_u_y*link1_w_z-link1_u_z*link1_w_y+link1_v_x = -0;
   link1_u_x*link1_w_z-link1_u_z*link1_w_x-link1_v_y = 0;
   link1_u_x*link1_w_y-link1_u_y*link1_w_x+link1_v_z = -0;
   link2_u_x^2+link2_u_y^2+link2_u_z^2 = 1;
   link2_v_x^2+link2_v_y^2+link2_v_z^2 = 1;
   link2_u_x*link2_w_x+link2_u_y*link2_w_y+link2_u_z*link2_w_z = 0;
   link2_u_y*link2_w_z-link2_u_z*link2_w_y+link2_v_x = -0;
   link2_u_x*link2_w_z-link2_u_z*link2_w_x-link2_v_y = 0;
   link2_u_x*link2_w_y-link2_u_y*link2_w_x+link2_v_z = -0;
   link3_u_x^2+link3_u_y^2+link3_u_z^2 = 1;
   link3_v_x^2+link3_v_y^2+link3_v_z^2 = 1;
   link3_u_x*link3_w_x+link3_u_y*link3_w_y+link3_u_z*link3_w_z = 0;
   link3_u_y*link3_w_z-link3_u_z*link3_w_y+link3_v_x = -0;
   link3_u_x*link3_w_z-link3_u_z*link3_w_x-link3_v_y = 0;
   link3_u_x*link3_w_y-link3_u_y*link3_w_x+link3_v_z = -0;
   link1_w_x = -0;
   link1_w_y = -0;
   link1_w_z = 1;
   link1_w_x-link2_w_x = 0;
   link1_w_y-link2_w_y = 0;
   link1_w_z-link2_w_z = 0;
   link2_w_x-link3_w_x = 0;
   link2_w_y-link3_w_y = 0;
   link2_w_z-link3_w_z = 0;
   link3_u_x = -0;
   link3_u_y = 1;
   link3_u_z = -0;
   link3_v_x = -1;
   link3_v_y = -0;
   link3_v_z = -0;
   link3_w_x = -0;
   link3_w_y = -0;
   link3_w_z = 1;
   link1_u_x+link2_u_x = 0.25;
   link1_u_y+link2_u_y = 0.75;
   link1_u_z+link2_u_z = 0;




==========================================================================
%****************************************
% Simplified system 
% SIMPLIFICATION_LEVEL: 2
% Variable reduction 27 -> 2
% Num syst+secu+vel variables in original  : 27 
% Num syst+secu+ve variables in simplified: 2 
%   link1_u_x=link1_u_x
%   link1_u_y=link1_u_y
%   link1_u_z= -0
%   link1_v_x=-link1_u_y
%   link1_v_y=link1_u_x
%   link1_v_z= -0
%   link1_w_x= -0
%   link1_w_y= -0
%   link1_w_z= +1
%   link2_u_x=-link1_u_x +0.25
%   link2_u_y=-link1_u_y +0.75
%   link2_u_z= -0
%   link2_v_x=link1_u_y -0.75
%   link2_v_y=-link1_u_x +0.25
%   link2_v_z= -0
%   link2_w_x= -0
%   link2_w_y= -0
%   link2_w_z= +1
%   link3_u_x= -0
%   link3_u_y= +1
%   link3_u_z= -0
%   link3_v_x= -1
%   link3_v_y= -0
%   link3_v_z= -0
%   link3_w_x= -0
%   link3_w_y= -0
%   link3_w_z= +1

[SYSTEM VARS]
   link1_u_x : [-0.750000000035,1]
   link1_u_y : [-0.250000000025,1]

[SYSTEM EQS]
   link1_u_x^2+link1_u_y^2 = 1;
   0.5*link1_u_x+1.5*link1_u_y = 0.625;

==========================================================================
Cuik executed in 1 processors
SOLUTIONS (to input file /home/logan/Downloads/CuikSuite3/bash/../examples/Welding/Welding0D.cuik):

   1 (err:1.23606e-06 tm:0):{ 27  link1_u_x[-0.746422392554,-0.746420914196] link1_u_y[0.665472472673,0.665474130856] link1_u_z[-0,0] link1_v_x[-0.665474130856,-0.665472472673] link1_v_y[-0.746422392554,-0.746420914196] link1_v_z[-0,0] link1_w_x[-0,0] link1_w_y[-0,0] link1_w_z[1,1] link2_u_x[0.996420914196,0.996422392554] link2_u_y[0.0845258691444,0.0845275273269] link2_u_z[-0,0] link2_v_x[-0.0845275273269,-0.0845258691444] link2_v_y[0.996420914196,0.996422392554] link2_v_z[-0,0] link2_w_x[-0,0] link2_w_y[-0,0] link2_w_z[1,1] link3_u_x[-0,0] link3_u_y[1,1] link3_u_z[-0,0] link3_v_x[-1,-1] link3_v_y[-0,0] link3_v_z[-0,0] link3_w_x[-0,0] link3_w_y[-0,0] link3_w_z[1,1] }
   2 (err:1.79596e-06 tm:0):{ 27  link1_u_x[0.996420982237,0.996421252977] link1_u_y[0.0845262482597,0.084527843841] link1_u_z[-0,0] link1_v_x[-0.084527843841,-0.0845262482597] link1_v_y[0.996420982237,0.996421252977] link1_v_z[-0,0] link1_w_x[-0,0] link1_w_y[-0,0] link1_w_z[1,1] link2_u_x[-0.746421252977,-0.746420982237] link2_u_y[0.665472156159,0.66547375174] link2_u_z[-0,0] link2_v_x[-0.66547375174,-0.665472156159] link2_v_y[-0.746421252977,-0.746420982237] link2_v_z[-0,0] link2_w_x[-0,0] link2_w_y[-0,0] link2_w_z[1,1] link3_u_x[-0,0] link3_u_y[1,1] link3_u_z[-0,0] link3_v_x[-1,-1] link3_v_y[-0,0] link3_v_z[-0,0] link3_w_x[-0,0] link3_w_y[-0,0] link3_w_z[1,1] }
STATITISTICS FOR Cuik:

Volume of the search space: 2.1875
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 4.44302e-06
Number of processors: 1
User time in process: 0.000000 seg (0.000000 min)
Box level information:
  N processed boxes :      3
  Max depth         :      2
  Types of boxes:
    N solution boxes:      2 (0) (66.67%)
    N empty boxes   :      0  ( 0.00%)
    N bisected boxes:      1  (33.33%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :      3
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

