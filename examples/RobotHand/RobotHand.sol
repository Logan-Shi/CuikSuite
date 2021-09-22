
==========================================================================
% COMPILATION FLAGS:
%   SIMPLEX ENGINE: clp
%   MPI: 1
%   DEBUG: 1
%   PROFILE: 0
%
% PARAMETERS:
   EPSILON = 1e-06
   REPRESENTATION = 0
   RHO = 0.95
   SMALL_SIGMA = 0.0001
   SIGMA = 0.1
   E = 0.4
   CE = 0.4
   R = 0.4
   SR = 1.25
   DELTA = 0.04
   BETA = 1.1
   STATE_PERIOD = 1000
   N_SOLUTIONS = 1
   MAX_NEWTON_ITERATIONS = 0
   N_DOF = 0
   GAMMA = 4
   DUMMIFY = 1
   ERROR_SPLIT = 1
   SAVE_SIMPLEX = 6
   SIMPLIFICATION_LEVEL = 3
   LR2TM_Q = 0.5
   LR2TM_S = 0.1
   VDW_RATIO = 0.8
   CUT_X = -1.79769e+308
   CUT_Y = -1.79769e+308
   CUT_Z = -1.79769e+308
   COEF_TEMP = 1.1
   NFAIL_MAX = 10
   DETECT_BIFURCATIONS = 0
   MAX_PLANNING_TIME = 600
   MAX_PLANNING_ITERATIONS = 10001
   MAX_CHARTS = 150000
   MAX_NODES_RRT = 250000
   BI_RRT = 1
   RRT_GRAPH = 1

==========================================================================
Equations from file: /home/porta/cuik/CuikSuite/examples/RobotHand/RobotHand.cuik
% Kinematic equations

[SYSTEM VARS]
   p12_u_x : [-1,1]
   p12_u_y : [-1,1]
   p12_u_z : [-1,1]
   p12_v_x : [-1,1]
   p12_v_y : [-1,1]
   p12_v_z : [-1,1]

[DUMMY VARS]
   p12_w_x : [-1,1]
   p12_w_y : [-1,1]
   p12_w_z : [-1,1]
   p12_wp_x : [-1,1]
   p12_wp_y : [-1,1]
   p12_wp_z : [-1,1]

[SYSTEM VARS]
   p13_u_x : [-1,1]
   p13_u_y : [-1,1]
   p13_u_z : [-1,1]
   p13_v_x : [-1,1]
   p13_v_y : [-1,1]
   p13_v_z : [-1,1]

[DUMMY VARS]
   p13_w_x : [-1,1]
   p13_w_y : [-1,1]
   p13_w_z : [-1,1]
   p13_wp_x : [-1,1]
   p13_wp_y : [-1,1]
   p13_wp_z : [-1,1]

[SYSTEM VARS]
   p14_u_x : [-1,1]
   p14_u_y : [-1,1]
   p14_u_z : [-1,1]
   p14_v_x : [-1,1]
   p14_v_y : [-1,1]
   p14_v_z : [-1,1]

[DUMMY VARS]
   p14_w_x : [-1,1]
   p14_w_y : [-1,1]
   p14_w_z : [-1,1]
   p14_wp_x : [-1,1]
   p14_wp_y : [-1,1]
   p14_wp_z : [-1,1]

[SYSTEM VARS]
   p22_u_x : [-1,1]
   p22_u_y : [-1,1]
   p22_u_z : [-1,1]
   p22_v_x : [-1,1]
   p22_v_y : [-1,1]
   p22_v_z : [-1,1]

[DUMMY VARS]
   p22_w_x : [-1,1]
   p22_w_y : [-1,1]
   p22_w_z : [-1,1]
   p22_wp_x : [-1,1]
   p22_wp_y : [-1,1]
   p22_wp_z : [-1,1]

[SYSTEM VARS]
   p23_u_x : [-1,1]
   p23_u_y : [-1,1]
   p23_u_z : [-1,1]
   p23_v_x : [-1,1]
   p23_v_y : [-1,1]
   p23_v_z : [-1,1]

[DUMMY VARS]
   p23_w_x : [-1,1]
   p23_w_y : [-1,1]
   p23_w_z : [-1,1]
   p23_wp_x : [-1,1]
   p23_wp_y : [-1,1]
   p23_wp_z : [-1,1]

[SYSTEM VARS]
   p24_u_x : [-1,1]
   p24_u_y : [-1,1]
   p24_u_z : [-1,1]
   p24_v_x : [-1,1]
   p24_v_y : [-1,1]
   p24_v_z : [-1,1]

[DUMMY VARS]
   p24_w_x : [-1,1]
   p24_w_y : [-1,1]
   p24_w_z : [-1,1]
   p24_wp_x : [-1,1]
   p24_wp_y : [-1,1]
   p24_wp_z : [-1,1]

[SYSTEM VARS]
   p32_u_x : [-1,1]
   p32_u_y : [-1,1]
   p32_u_z : [-1,1]
   p32_v_x : [-1,1]
   p32_v_y : [-1,1]
   p32_v_z : [-1,1]

[DUMMY VARS]
   p32_w_x : [-1,1]
   p32_w_y : [-1,1]
   p32_w_z : [-1,1]
   p32_wp_x : [-1,1]
   p32_wp_y : [-1,1]
   p32_wp_z : [-1,1]

[SYSTEM VARS]
   p33_u_x : [-1,1]
   p33_u_y : [-1,1]
   p33_u_z : [-1,1]
   p33_v_x : [-1,1]
   p33_v_y : [-1,1]
   p33_v_z : [-1,1]

[DUMMY VARS]
   p33_w_x : [-1,1]
   p33_w_y : [-1,1]
   p33_w_z : [-1,1]
   p33_wp_x : [-1,1]
   p33_wp_y : [-1,1]
   p33_wp_z : [-1,1]

[SYSTEM VARS]
   p34_u_x : [-1,1]
   p34_u_y : [-1,1]
   p34_u_z : [-1,1]
   p34_v_x : [-1,1]
   p34_v_y : [-1,1]
   p34_v_z : [-1,1]

[DUMMY VARS]
   p34_w_x : [-1,1]
   p34_w_y : [-1,1]
   p34_w_z : [-1,1]
   p34_wp_x : [-1,1]
   p34_wp_y : [-1,1]
   p34_wp_z : [-1,1]

[SYSTEM VARS]
   p42_u_x : [-1,1]
   p42_u_y : [-1,1]
   p42_u_z : [-1,1]
   p42_v_x : [-1,1]
   p42_v_y : [-1,1]
   p42_v_z : [-1,1]

[DUMMY VARS]
   p42_w_x : [-1,1]
   p42_w_y : [-1,1]
   p42_w_z : [-1,1]
   p42_wp_x : [-1,1]
   p42_wp_y : [-1,1]
   p42_wp_z : [-1,1]

[SYSTEM VARS]
   p43_u_x : [-1,1]
   p43_u_y : [-1,1]
   p43_u_z : [-1,1]
   p43_v_x : [-1,1]
   p43_v_y : [-1,1]
   p43_v_z : [-1,1]

[DUMMY VARS]
   p43_w_x : [-1,1]
   p43_w_y : [-1,1]
   p43_w_z : [-1,1]
   p43_wp_x : [-1,1]
   p43_wp_y : [-1,1]
   p43_wp_z : [-1,1]

[SYSTEM VARS]
   p44_u_x : [-1,1]
   p44_u_y : [-1,1]
   p44_u_z : [-1,1]
   p44_v_x : [-1,1]
   p44_v_y : [-1,1]
   p44_v_z : [-1,1]

[DUMMY VARS]
   p44_w_x : [-1,1]
   p44_w_y : [-1,1]
   p44_w_z : [-1,1]
   p44_wp_x : [-1,1]
   p44_wp_y : [-1,1]
   p44_wp_z : [-1,1]

[SYSTEM VARS]
   object_u_x : [-1,1]
   object_u_y : [-1,1]
   object_u_z : [-1,1]
   object_v_x : [-1,1]
   object_v_y : [-1,1]
   object_v_z : [-1,1]

[DUMMY VARS]
   object_w_x : [-1,1]
   object_w_y : [-1,1]
   object_w_z : [-1,1]
   object_wp_x : [-1,1]
   object_wp_y : [-1,1]
   object_wp_z : [-1,1]

[SECONDARY VARS]
   uni_u_palm_p12_x_0 : [-1,1]
   uni_u_palm_p12_y_0 : [-1,1]
   uni_u_palm_p12_z_0 : [-1,1]
   uni_v_palm_p12_x_0 : [-1,1]
   uni_v_palm_p12_y_0 : [-1,1]
   uni_v_palm_p12_z_0 : [-1,1]
   w1_palm_p12_x_0 : [-1,1]
   w1_palm_p12_y_0 : [-1,1]
   w1_palm_p12_z_0 : [-1,1]
   w2_palm_p12_x_0 : [-1,1]
   w2_palm_p12_y_0 : [-1,1]
   w2_palm_p12_z_0 : [-1,1]
   cos_0_palm_p12_0 : [0.965924826289,1.000001]
   cos_1_palm_p12_0 : [0.707105781187,1.000001]
   w1_p12_p13_x_1 : [-1,1]
   w1_p12_p13_y_1 : [-1,1]
   w1_p12_p13_z_1 : [-1,1]
   w2_p12_p13_x_1 : [-1,1]
   w2_p12_p13_y_1 : [-1,1]
   w2_p12_p13_z_1 : [-1,1]
   cos_p12_p13_1 : [0.707105781187,1.000001]
   w1_p13_p14_x_2 : [-1,1]
   w1_p13_p14_y_2 : [-1,1]
   w1_p13_p14_z_2 : [-1,1]
   w2_p13_p14_x_2 : [-1,1]
   w2_p13_p14_y_2 : [-1,1]
   w2_p13_p14_z_2 : [-1,1]
   cos_p13_p14_2 : [0.707105781187,1.000001]
   uni_u_palm_p22_x_3 : [-1,1]
   uni_u_palm_p22_y_3 : [-1,1]
   uni_u_palm_p22_z_3 : [-1,1]
   uni_v_palm_p22_x_3 : [-1,1]
   uni_v_palm_p22_y_3 : [-1,1]
   uni_v_palm_p22_z_3 : [-1,1]
   w1_palm_p22_x_3 : [-1,1]
   w1_palm_p22_y_3 : [-1,1]
   w1_palm_p22_z_3 : [-1,1]
   w2_palm_p22_x_3 : [-1,1]
   w2_palm_p22_y_3 : [-1,1]
   w2_palm_p22_z_3 : [-1,1]
   cos_0_palm_p22_3 : [0.965924826289,1.000001]
   cos_1_palm_p22_3 : [0.707105781187,1.000001]
   w1_p22_p23_x_4 : [-1,1]
   w1_p22_p23_y_4 : [-1,1]
   w1_p22_p23_z_4 : [-1,1]
   w2_p22_p23_x_4 : [-1,1]
   w2_p22_p23_y_4 : [-1,1]
   w2_p22_p23_z_4 : [-1,1]
   cos_p22_p23_4 : [0.707105781187,1.000001]
   w1_p23_p24_x_5 : [-1,1]
   w1_p23_p24_y_5 : [-1,1]
   w1_p23_p24_z_5 : [-1,1]
   w2_p23_p24_x_5 : [-1,1]
   w2_p23_p24_y_5 : [-1,1]
   w2_p23_p24_z_5 : [-1,1]
   cos_p23_p24_5 : [0.707105781187,1.000001]
   uni_u_palm_p32_x_6 : [-1,1]
   uni_u_palm_p32_y_6 : [-1,1]
   uni_u_palm_p32_z_6 : [-1,1]
   uni_v_palm_p32_x_6 : [-1,1]
   uni_v_palm_p32_y_6 : [-1,1]
   uni_v_palm_p32_z_6 : [-1,1]
   w1_palm_p32_x_6 : [-1,1]
   w1_palm_p32_y_6 : [-1,1]
   w1_palm_p32_z_6 : [-1,1]
   w2_palm_p32_x_6 : [-1,1]
   w2_palm_p32_y_6 : [-1,1]
   w2_palm_p32_z_6 : [-1,1]
   cos_0_palm_p32_6 : [0.965924826289,1.000001]
   cos_1_palm_p32_6 : [0.707105781187,1.000001]
   w1_p32_p33_x_7 : [-1,1]
   w1_p32_p33_y_7 : [-1,1]
   w1_p32_p33_z_7 : [-1,1]
   w2_p32_p33_x_7 : [-1,1]
   w2_p32_p33_y_7 : [-1,1]
   w2_p32_p33_z_7 : [-1,1]
   cos_p32_p33_7 : [0.707105781187,1.000001]
   w1_p33_p34_x_8 : [-1,1]
   w1_p33_p34_y_8 : [-1,1]
   w1_p33_p34_z_8 : [-1,1]
   w2_p33_p34_x_8 : [-1,1]
   w2_p33_p34_y_8 : [-1,1]
   w2_p33_p34_z_8 : [-1,1]
   cos_p33_p34_8 : [0.707105781187,1.000001]
   uni_u_palm_p42_x_9 : [-1,1]
   uni_u_palm_p42_y_9 : [-1,1]
   uni_u_palm_p42_z_9 : [-1,1]
   uni_v_palm_p42_x_9 : [-1,1]
   uni_v_palm_p42_y_9 : [-1,1]
   uni_v_palm_p42_z_9 : [-1,1]
   w1_palm_p42_x_9 : [-1,1]
   w1_palm_p42_y_9 : [-1,1]
   w1_palm_p42_z_9 : [-1,1]
   w2_palm_p42_x_9 : [-1,1]
   w2_palm_p42_y_9 : [-1,1]
   w2_palm_p42_z_9 : [-1,1]
   cos_0_palm_p42_9 : [0.965924826289,1.000001]
   cos_1_palm_p42_9 : [-1.00000000018e-06,1.000001]
   w1_p42_p43_x_10 : [-1,1]
   w1_p42_p43_y_10 : [-1,1]
   w1_p42_p43_z_10 : [-1,1]
   w2_p42_p43_x_10 : [-1,1]
   w2_p42_p43_y_10 : [-1,1]
   w2_p42_p43_z_10 : [-1,1]
   cos_p42_p43_10 : [0.707105781187,1.000001]
   w1_p43_p44_x_11 : [-1,1]
   w1_p43_p44_y_11 : [-1,1]
   w1_p43_p44_z_11 : [-1,1]
   w2_p43_p44_x_11 : [-1,1]
   w2_p43_p44_y_11 : [-1,1]
   w2_p43_p44_z_11 : [-1,1]
   cos_p43_p44_11 : [0.707105781187,1.000001]

[SYSTEM EQS]

   p12_u_x^2+p12_u_y^2+p12_u_z^2 = 1;
   p12_v_x^2+p12_v_y^2+p12_v_z^2 = 1;
   p12_u_x*p12_v_x+p12_u_y*p12_v_y+p12_u_z*p12_v_z = 0;
   p13_u_x^2+p13_u_y^2+p13_u_z^2 = 1;
   p13_v_x^2+p13_v_y^2+p13_v_z^2 = 1;
   p13_u_x*p13_v_x+p13_u_y*p13_v_y+p13_u_z*p13_v_z = 0;
   p14_u_x^2+p14_u_y^2+p14_u_z^2 = 1;
   p14_v_x^2+p14_v_y^2+p14_v_z^2 = 1;
   p14_u_x*p14_v_x+p14_u_y*p14_v_y+p14_u_z*p14_v_z = 0;
   p22_u_x^2+p22_u_y^2+p22_u_z^2 = 1;
   p22_v_x^2+p22_v_y^2+p22_v_z^2 = 1;
   p22_u_x*p22_v_x+p22_u_y*p22_v_y+p22_u_z*p22_v_z = 0;
   p23_u_x^2+p23_u_y^2+p23_u_z^2 = 1;
   p23_v_x^2+p23_v_y^2+p23_v_z^2 = 1;
   p23_u_x*p23_v_x+p23_u_y*p23_v_y+p23_u_z*p23_v_z = 0;
   p24_u_x^2+p24_u_y^2+p24_u_z^2 = 1;
   p24_v_x^2+p24_v_y^2+p24_v_z^2 = 1;
   p24_u_x*p24_v_x+p24_u_y*p24_v_y+p24_u_z*p24_v_z = 0;
   p32_u_x^2+p32_u_y^2+p32_u_z^2 = 1;
   p32_v_x^2+p32_v_y^2+p32_v_z^2 = 1;
   p32_u_x*p32_v_x+p32_u_y*p32_v_y+p32_u_z*p32_v_z = 0;
   p33_u_x^2+p33_u_y^2+p33_u_z^2 = 1;
   p33_v_x^2+p33_v_y^2+p33_v_z^2 = 1;
   p33_u_x*p33_v_x+p33_u_y*p33_v_y+p33_u_z*p33_v_z = 0;
   p34_u_x^2+p34_u_y^2+p34_u_z^2 = 1;
   p34_v_x^2+p34_v_y^2+p34_v_z^2 = 1;
   p34_u_x*p34_v_x+p34_u_y*p34_v_y+p34_u_z*p34_v_z = 0;
   p42_u_x^2+p42_u_y^2+p42_u_z^2 = 1;
   p42_v_x^2+p42_v_y^2+p42_v_z^2 = 1;
   p42_u_x*p42_v_x+p42_u_y*p42_v_y+p42_u_z*p42_v_z = 0;
   p43_u_x^2+p43_u_y^2+p43_u_z^2 = 1;
   p43_v_x^2+p43_v_y^2+p43_v_z^2 = 1;
   p43_u_x*p43_v_x+p43_u_y*p43_v_y+p43_u_z*p43_v_z = 0;
   p44_u_x^2+p44_u_y^2+p44_u_z^2 = 1;
   p44_v_x^2+p44_v_y^2+p44_v_z^2 = 1;
   p44_u_x*p44_v_x+p44_u_y*p44_v_y+p44_u_z*p44_v_z = 0;
   object_u_x^2+object_u_y^2+object_u_z^2 = 1;
   object_v_x^2+object_v_y^2+object_v_z^2 = 1;
   object_u_x*object_v_x+object_u_y*object_v_y+object_u_z*object_v_z = 0;
   uni_u_palm_p12_x_0 = 1;
   uni_u_palm_p12_y_0 = -0;
   uni_u_palm_p12_z_0 = -0;
   p12_v_x-uni_v_palm_p12_x_0 = 0;
   p12_v_y-uni_v_palm_p12_y_0 = 0;
   p12_v_z-uni_v_palm_p12_z_0 = 0;
   uni_u_palm_p12_x_0*uni_v_palm_p12_x_0+uni_u_palm_p12_y_0*uni_v_palm_p12_y_0+uni_u_palm_p12_z_0*uni_v_palm_p12_z_0 = 0;
   w1_palm_p12_x_0 = 0;
   w1_palm_p12_y_0 = -1;
   w1_palm_p12_z_0 = 0;
   0.7071067811865476*p12_u_x+0.7071067811865475*p12_w_x-0.7071067811865475*p12_wp_x-w2_palm_p12_x_0 = -0;
   0.7071067811865476*p12_u_y+0.7071067811865475*p12_w_y-0.7071067811865475*p12_wp_y-w2_palm_p12_y_0 = -0;
   0.7071067811865476*p12_u_z+0.7071067811865475*p12_w_z-0.7071067811865475*p12_wp_z-w2_palm_p12_z_0 = -0;
   uni_v_palm_p12_x_0*w1_palm_p12_x_0+uni_v_palm_p12_y_0*w1_palm_p12_y_0+uni_v_palm_p12_z_0*w1_palm_p12_z_0-cos_0_palm_p12_0 = 0;
   uni_u_palm_p12_x_0*w2_palm_p12_x_0+uni_u_palm_p12_y_0*w2_palm_p12_y_0+uni_u_palm_p12_z_0*w2_palm_p12_z_0-cos_1_palm_p12_0 = 0;
   p12_v_x-p13_v_x = -0;
   p12_v_y-p13_v_y = -0;
   p12_v_z-p13_v_z = -0;
   0.7071067811865476*p12_u_x+0.7071067811865475*p12_w_x-0.7071067811865475*p12_wp_x-w1_p12_p13_x_1 = -0;
   0.7071067811865476*p12_u_y+0.7071067811865475*p12_w_y-0.7071067811865475*p12_wp_y-w1_p12_p13_y_1 = -0;
   0.7071067811865476*p12_u_z+0.7071067811865475*p12_w_z-0.7071067811865475*p12_wp_z-w1_p12_p13_z_1 = -0;
   p13_u_x-w2_p12_p13_x_1 = -0;
   p13_u_y-w2_p12_p13_y_1 = -0;
   p13_u_z-w2_p12_p13_z_1 = -0;
   w1_p12_p13_x_1*w2_p12_p13_x_1+w1_p12_p13_y_1*w2_p12_p13_y_1+w1_p12_p13_z_1*w2_p12_p13_z_1-cos_p12_p13_1 = 0;
   p13_v_x-p14_v_x = -0;
   p13_v_y-p14_v_y = -0;
   p13_v_z-p14_v_z = -0;
   0.7071067811865476*p13_u_x+0.7071067811865475*p13_w_x-0.7071067811865475*p13_wp_x-w1_p13_p14_x_2 = -0;
   0.7071067811865476*p13_u_y+0.7071067811865475*p13_w_y-0.7071067811865475*p13_wp_y-w1_p13_p14_y_2 = -0;
   0.7071067811865476*p13_u_z+0.7071067811865475*p13_w_z-0.7071067811865475*p13_wp_z-w1_p13_p14_z_2 = -0;
   p14_u_x-w2_p13_p14_x_2 = -0;
   p14_u_y-w2_p13_p14_y_2 = -0;
   p14_u_z-w2_p13_p14_z_2 = -0;
   w1_p13_p14_x_2*w2_p13_p14_x_2+w1_p13_p14_y_2*w2_p13_p14_y_2+w1_p13_p14_z_2*w2_p13_p14_z_2-cos_p13_p14_2 = 0;
   uni_u_palm_p22_x_3 = 1;
   uni_u_palm_p22_y_3 = -0;
   uni_u_palm_p22_z_3 = -0;
   p22_v_x-uni_v_palm_p22_x_3 = 0;
   p22_v_y-uni_v_palm_p22_y_3 = 0;
   p22_v_z-uni_v_palm_p22_z_3 = 0;
   uni_u_palm_p22_x_3*uni_v_palm_p22_x_3+uni_u_palm_p22_y_3*uni_v_palm_p22_y_3+uni_u_palm_p22_z_3*uni_v_palm_p22_z_3 = 0;
   w1_palm_p22_x_3 = 0;
   w1_palm_p22_y_3 = -1;
   w1_palm_p22_z_3 = 0;
   0.7071067811865476*p22_u_x+0.7071067811865475*p22_w_x-0.7071067811865475*p22_wp_x-w2_palm_p22_x_3 = -0;
   0.7071067811865476*p22_u_y+0.7071067811865475*p22_w_y-0.7071067811865475*p22_wp_y-w2_palm_p22_y_3 = -0;
   0.7071067811865476*p22_u_z+0.7071067811865475*p22_w_z-0.7071067811865475*p22_wp_z-w2_palm_p22_z_3 = -0;
   uni_v_palm_p22_x_3*w1_palm_p22_x_3+uni_v_palm_p22_y_3*w1_palm_p22_y_3+uni_v_palm_p22_z_3*w1_palm_p22_z_3-cos_0_palm_p22_3 = 0;
   uni_u_palm_p22_x_3*w2_palm_p22_x_3+uni_u_palm_p22_y_3*w2_palm_p22_y_3+uni_u_palm_p22_z_3*w2_palm_p22_z_3-cos_1_palm_p22_3 = 0;
   p22_v_x-p23_v_x = -0;
   p22_v_y-p23_v_y = -0;
   p22_v_z-p23_v_z = -0;
   0.7071067811865476*p22_u_x+0.7071067811865475*p22_w_x-0.7071067811865475*p22_wp_x-w1_p22_p23_x_4 = -0;
   0.7071067811865476*p22_u_y+0.7071067811865475*p22_w_y-0.7071067811865475*p22_wp_y-w1_p22_p23_y_4 = -0;
   0.7071067811865476*p22_u_z+0.7071067811865475*p22_w_z-0.7071067811865475*p22_wp_z-w1_p22_p23_z_4 = -0;
   p23_u_x-w2_p22_p23_x_4 = -0;
   p23_u_y-w2_p22_p23_y_4 = -0;
   p23_u_z-w2_p22_p23_z_4 = -0;
   w1_p22_p23_x_4*w2_p22_p23_x_4+w1_p22_p23_y_4*w2_p22_p23_y_4+w1_p22_p23_z_4*w2_p22_p23_z_4-cos_p22_p23_4 = 0;
   p23_v_x-p24_v_x = -0;
   p23_v_y-p24_v_y = -0;
   p23_v_z-p24_v_z = -0;
   0.7071067811865476*p23_u_x+0.7071067811865475*p23_w_x-0.7071067811865475*p23_wp_x-w1_p23_p24_x_5 = -0;
   0.7071067811865476*p23_u_y+0.7071067811865475*p23_w_y-0.7071067811865475*p23_wp_y-w1_p23_p24_y_5 = -0;
   0.7071067811865476*p23_u_z+0.7071067811865475*p23_w_z-0.7071067811865475*p23_wp_z-w1_p23_p24_z_5 = -0;
   p24_u_x-w2_p23_p24_x_5 = -0;
   p24_u_y-w2_p23_p24_y_5 = -0;
   p24_u_z-w2_p23_p24_z_5 = -0;
   w1_p23_p24_x_5*w2_p23_p24_x_5+w1_p23_p24_y_5*w2_p23_p24_y_5+w1_p23_p24_z_5*w2_p23_p24_z_5-cos_p23_p24_5 = 0;
   uni_u_palm_p32_x_6 = 1;
   uni_u_palm_p32_y_6 = -0;
   uni_u_palm_p32_z_6 = -0;
   p32_v_x-uni_v_palm_p32_x_6 = 0;
   p32_v_y-uni_v_palm_p32_y_6 = 0;
   p32_v_z-uni_v_palm_p32_z_6 = 0;
   uni_u_palm_p32_x_6*uni_v_palm_p32_x_6+uni_u_palm_p32_y_6*uni_v_palm_p32_y_6+uni_u_palm_p32_z_6*uni_v_palm_p32_z_6 = 0;
   w1_palm_p32_x_6 = 0;
   w1_palm_p32_y_6 = -1;
   w1_palm_p32_z_6 = 0;
   0.7071067811865476*p32_u_x+0.7071067811865475*p32_w_x-0.7071067811865475*p32_wp_x-w2_palm_p32_x_6 = -0;
   0.7071067811865476*p32_u_y+0.7071067811865475*p32_w_y-0.7071067811865475*p32_wp_y-w2_palm_p32_y_6 = -0;
   0.7071067811865476*p32_u_z+0.7071067811865475*p32_w_z-0.7071067811865475*p32_wp_z-w2_palm_p32_z_6 = -0;
   uni_v_palm_p32_x_6*w1_palm_p32_x_6+uni_v_palm_p32_y_6*w1_palm_p32_y_6+uni_v_palm_p32_z_6*w1_palm_p32_z_6-cos_0_palm_p32_6 = 0;
   uni_u_palm_p32_x_6*w2_palm_p32_x_6+uni_u_palm_p32_y_6*w2_palm_p32_y_6+uni_u_palm_p32_z_6*w2_palm_p32_z_6-cos_1_palm_p32_6 = 0;
   p32_v_x-p33_v_x = -0;
   p32_v_y-p33_v_y = -0;
   p32_v_z-p33_v_z = -0;
   0.7071067811865476*p32_u_x+0.7071067811865475*p32_w_x-0.7071067811865475*p32_wp_x-w1_p32_p33_x_7 = -0;
   0.7071067811865476*p32_u_y+0.7071067811865475*p32_w_y-0.7071067811865475*p32_wp_y-w1_p32_p33_y_7 = -0;
   0.7071067811865476*p32_u_z+0.7071067811865475*p32_w_z-0.7071067811865475*p32_wp_z-w1_p32_p33_z_7 = -0;
   p33_u_x-w2_p32_p33_x_7 = -0;
   p33_u_y-w2_p32_p33_y_7 = -0;
   p33_u_z-w2_p32_p33_z_7 = -0;
   w1_p32_p33_x_7*w2_p32_p33_x_7+w1_p32_p33_y_7*w2_p32_p33_y_7+w1_p32_p33_z_7*w2_p32_p33_z_7-cos_p32_p33_7 = 0;
   p33_v_x-p34_v_x = -0;
   p33_v_y-p34_v_y = -0;
   p33_v_z-p34_v_z = -0;
   0.7071067811865476*p33_u_x+0.7071067811865475*p33_w_x-0.7071067811865475*p33_wp_x-w1_p33_p34_x_8 = -0;
   0.7071067811865476*p33_u_y+0.7071067811865475*p33_w_y-0.7071067811865475*p33_wp_y-w1_p33_p34_y_8 = -0;
   0.7071067811865476*p33_u_z+0.7071067811865475*p33_w_z-0.7071067811865475*p33_wp_z-w1_p33_p34_z_8 = -0;
   p34_u_x-w2_p33_p34_x_8 = -0;
   p34_u_y-w2_p33_p34_y_8 = -0;
   p34_u_z-w2_p33_p34_z_8 = -0;
   w1_p33_p34_x_8*w2_p33_p34_x_8+w1_p33_p34_y_8*w2_p33_p34_y_8+w1_p33_p34_z_8*w2_p33_p34_z_8-cos_p33_p34_8 = 0;
   uni_u_palm_p42_x_9 = -1;
   uni_u_palm_p42_y_9 = -0;
   uni_u_palm_p42_z_9 = -0;
   p42_v_x+uni_v_palm_p42_x_9 = -0;
   p42_v_y+uni_v_palm_p42_y_9 = -0;
   p42_v_z+uni_v_palm_p42_z_9 = -0;
   uni_u_palm_p42_x_9*uni_v_palm_p42_x_9+uni_u_palm_p42_y_9*uni_v_palm_p42_y_9+uni_u_palm_p42_z_9*uni_v_palm_p42_z_9 = 0;
   w1_palm_p42_x_9 = 0;
   w1_palm_p42_y_9 = -1;
   w1_palm_p42_z_9 = 0;
   p42_u_x+w2_palm_p42_x_9 = 0;
   p42_u_y+w2_palm_p42_y_9 = 0;
   p42_u_z+w2_palm_p42_z_9 = 0;
   uni_v_palm_p42_x_9*w1_palm_p42_x_9+uni_v_palm_p42_y_9*w1_palm_p42_y_9+uni_v_palm_p42_z_9*w1_palm_p42_z_9-cos_0_palm_p42_9 = 0;
   uni_u_palm_p42_x_9*w2_palm_p42_x_9+uni_u_palm_p42_y_9*w2_palm_p42_y_9+uni_u_palm_p42_z_9*w2_palm_p42_z_9-cos_1_palm_p42_9 = 0;
   p42_v_x-p43_v_x = -0;
   p42_v_y-p43_v_y = -0;
   p42_v_z-p43_v_z = -0;
   0.7071067811865476*p42_u_x+0.7071067811865475*p42_w_x-0.7071067811865475*p42_wp_x-w1_p42_p43_x_10 = -0;
   0.7071067811865476*p42_u_y+0.7071067811865475*p42_w_y-0.7071067811865475*p42_wp_y-w1_p42_p43_y_10 = -0;
   0.7071067811865476*p42_u_z+0.7071067811865475*p42_w_z-0.7071067811865475*p42_wp_z-w1_p42_p43_z_10 = -0;
   p43_u_x-w2_p42_p43_x_10 = -0;
   p43_u_y-w2_p42_p43_y_10 = -0;
   p43_u_z-w2_p42_p43_z_10 = -0;
   w1_p42_p43_x_10*w2_p42_p43_x_10+w1_p42_p43_y_10*w2_p42_p43_y_10+w1_p42_p43_z_10*w2_p42_p43_z_10-cos_p42_p43_10 = 0;
   p43_v_x-p44_v_x = -0;
   p43_v_y-p44_v_y = -0;
   p43_v_z-p44_v_z = -0;
   0.7071067811865476*p43_u_x+0.7071067811865475*p43_w_x-0.7071067811865475*p43_wp_x-w1_p43_p44_x_11 = -0;
   0.7071067811865476*p43_u_y+0.7071067811865475*p43_w_y-0.7071067811865475*p43_wp_y-w1_p43_p44_y_11 = -0;
   0.7071067811865476*p43_u_z+0.7071067811865475*p43_w_z-0.7071067811865475*p43_wp_z-w1_p43_p44_z_11 = -0;
   p44_u_x-w2_p43_p44_x_11 = -0;
   p44_u_y-w2_p43_p44_y_11 = -0;
   p44_u_z-w2_p43_p44_z_11 = -0;
   w1_p43_p44_x_11*w2_p43_p44_x_11+w1_p43_p44_y_11*w2_p43_p44_y_11+w1_p43_p44_z_11*w2_p43_p44_z_11-cos_p43_p44_11 = 0;
   p14_w_x-p14_wp_x+0.7071067811865475*object_u_x+0.7071067811865475*object_w_x-0.7071067811865475*object_wp_x = 0;
   p14_w_y-p14_wp_y+0.7071067811865475*object_u_y+0.7071067811865475*object_w_y-0.7071067811865475*object_wp_y = 0;
   p14_w_z-p14_wp_z+0.7071067811865475*object_u_z+0.7071067811865475*object_w_z-0.7071067811865475*object_wp_z = 0;
   p24_w_x-p24_wp_x+0.5164943340882256*object_u_x+0.8562906065435731*object_w_x-0.8562906065435731*object_wp_x = 0;
   p24_w_y-p24_wp_y+0.5164943340882256*object_u_y+0.8562906065435731*object_w_y-0.8562906065435731*object_wp_y = 0;
   p24_w_z-p24_wp_z+0.5164943340882256*object_u_z+0.8562906065435731*object_w_z-0.8562906065435731*object_wp_z = 0;
   p34_w_x-p34_wp_x+0.7071067811865475*object_u_x+0.7071067811865475*object_w_x-0.7071067811865475*object_wp_x = 0;
   p34_w_y-p34_wp_y+0.7071067811865475*object_u_y+0.7071067811865475*object_w_y-0.7071067811865475*object_wp_y = 0;
   p34_w_z-p34_wp_z+0.7071067811865475*object_u_z+0.7071067811865475*object_w_z-0.7071067811865475*object_wp_z = 0;
   p44_w_x-p44_wp_x+0.9778216247643486*object_u_x+0.05420119867276273*object_v_x-0.2023044740129221*object_w_x+0.2023044740129221*object_wp_x = 0;
   p44_w_y-p44_wp_y+0.9778216247643486*object_u_y+0.05420119867276273*object_v_y-0.2023044740129221*object_w_y+0.2023044740129221*object_wp_y = 0;
   p44_w_z-p44_wp_z+0.9778216247643486*object_u_z+0.05420119867276273*object_v_z-0.2023044740129221*object_w_z+0.2023044740129221*object_wp_z = 0;
   76.66*p12_u_x+56*p13_u_x+27.85682109737468*p14_u_x+19.1514*p14_w_x-19.1514*p14_wp_x-76.66*p22_u_x-56*p23_u_x-27.85682109737468*p24_u_x-19.15165185920876*p24_w_x+19.15165185920876*p24_wp_x-8.444599999999994*object_u_x+67*object_v_x+27.33940000000001*object_w_x-27.33940000000001*object_wp_x = -0;
   76.66*p12_u_y+56*p13_u_y+27.85682109737468*p14_u_y+19.1514*p14_w_y-19.1514*p14_wp_y-76.66*p22_u_y-56*p23_u_y-27.85682109737468*p24_u_y-19.15165185920876*p24_w_y+19.15165185920876*p24_wp_y-8.444599999999994*object_u_y+67*object_v_y+27.33940000000001*object_w_y-27.33940000000001*object_wp_y = 67;
   76.66*p12_u_z+56*p13_u_z+27.85682109737468*p14_u_z+19.1514*p14_w_z-19.1514*p14_wp_z-76.66*p22_u_z-56*p23_u_z-27.85682109737468*p24_u_z-19.15165185920876*p24_w_z+19.15165185920876*p24_wp_z-8.444599999999994*object_u_z+67*object_v_z+27.33940000000001*object_w_z-27.33940000000001*object_wp_z = -0;
   76.66*p12_u_x+56*p13_u_x+27.85682109737468*p14_u_x+19.1514*p14_w_x-19.1514*p14_wp_x-76.66*p32_u_x-56*p33_u_x-27.85682109737468*p34_u_x-19.15165185920876*p34_w_x+19.15165185920876*p34_wp_x-0.0001999999999924285*object_u_x+134*object_v_x-0.0002000000000066393*object_w_x+0.0002000000000066393*object_wp_x = -0;
   76.66*p12_u_y+56*p13_u_y+27.85682109737468*p14_u_y+19.1514*p14_w_y-19.1514*p14_wp_y-76.66*p32_u_y-56*p33_u_y-27.85682109737468*p34_u_y-19.15165185920876*p34_w_y+19.15165185920876*p34_wp_y-0.0001999999999924285*object_u_y+134*object_v_y-0.0002000000000066393*object_w_y+0.0002000000000066393*object_wp_y = 134;
   76.66*p12_u_z+56*p13_u_z+27.85682109737468*p14_u_z+19.1514*p14_w_z-19.1514*p14_wp_z-76.66*p32_u_z-56*p33_u_z-27.85682109737468*p34_u_z-19.15165185920876*p34_w_z+19.15165185920876*p34_wp_z-0.0001999999999924285*object_u_z+134*object_v_z-0.0002000000000066393*object_w_z+0.0002000000000066393*object_wp_z = -0;
   76.66*p12_u_x+56*p13_u_x+27.85682109737468*p14_u_x+19.1514*p14_w_x-19.1514*p14_wp_x-76.66*p42_u_x-66*p43_u_x-34.76240698960329*p44_u_x-19.50828346766322*p44_w_x+19.50828346766322*p44_wp_x+34.55749999999999*object_u_x+77.4509*object_v_x-78.69970000000001*object_w_x+78.69970000000001*object_wp_x = 30.665;
   76.66*p12_u_y+56*p13_u_y+27.85682109737468*p14_u_y+19.1514*p14_w_y-19.1514*p14_wp_y-76.66*p42_u_y-66*p43_u_y-34.76240698960329*p44_u_y-19.50828346766322*p44_w_y+19.50828346766322*p44_wp_y+34.55749999999999*object_u_y+77.4509*object_v_y-78.69970000000001*object_w_y+78.69970000000001*object_wp_y = 97.012;
   76.66*p12_u_z+56*p13_u_z+27.85682109737468*p14_u_z+19.1514*p14_w_z-19.1514*p14_wp_z-76.66*p42_u_z-66*p43_u_z-34.76240698960329*p44_u_z-19.50828346766322*p44_w_z+19.50828346766322*p44_wp_z+34.55749999999999*object_u_z+77.4509*object_v_z-78.69970000000001*object_w_z+78.69970000000001*object_wp_z = -130.7358;

[DUMMY EQS]

   p12_u_y*p12_v_z-p12_w_x = 0;
   p12_u_z*p12_v_x-p12_w_y = 0;
   p12_u_x*p12_v_y-p12_w_z = 0;
   p12_u_z*p12_v_y-p12_wp_x = 0;
   p12_u_x*p12_v_z-p12_wp_y = 0;
   p12_u_y*p12_v_x-p12_wp_z = 0;
   p13_u_y*p13_v_z-p13_w_x = 0;
   p13_u_z*p13_v_x-p13_w_y = 0;
   p13_u_x*p13_v_y-p13_w_z = 0;
   p13_u_z*p13_v_y-p13_wp_x = 0;
   p13_u_x*p13_v_z-p13_wp_y = 0;
   p13_u_y*p13_v_x-p13_wp_z = 0;
   p14_u_y*p14_v_z-p14_w_x = 0;
   p14_u_z*p14_v_x-p14_w_y = 0;
   p14_u_x*p14_v_y-p14_w_z = 0;
   p14_u_z*p14_v_y-p14_wp_x = 0;
   p14_u_x*p14_v_z-p14_wp_y = 0;
   p14_u_y*p14_v_x-p14_wp_z = 0;
   p22_u_y*p22_v_z-p22_w_x = 0;
   p22_u_z*p22_v_x-p22_w_y = 0;
   p22_u_x*p22_v_y-p22_w_z = 0;
   p22_u_z*p22_v_y-p22_wp_x = 0;
   p22_u_x*p22_v_z-p22_wp_y = 0;
   p22_u_y*p22_v_x-p22_wp_z = 0;
   p23_u_y*p23_v_z-p23_w_x = 0;
   p23_u_z*p23_v_x-p23_w_y = 0;
   p23_u_x*p23_v_y-p23_w_z = 0;
   p23_u_z*p23_v_y-p23_wp_x = 0;
   p23_u_x*p23_v_z-p23_wp_y = 0;
   p23_u_y*p23_v_x-p23_wp_z = 0;
   p24_u_y*p24_v_z-p24_w_x = 0;
   p24_u_z*p24_v_x-p24_w_y = 0;
   p24_u_x*p24_v_y-p24_w_z = 0;
   p24_u_z*p24_v_y-p24_wp_x = 0;
   p24_u_x*p24_v_z-p24_wp_y = 0;
   p24_u_y*p24_v_x-p24_wp_z = 0;
   p32_u_y*p32_v_z-p32_w_x = 0;
   p32_u_z*p32_v_x-p32_w_y = 0;
   p32_u_x*p32_v_y-p32_w_z = 0;
   p32_u_z*p32_v_y-p32_wp_x = 0;
   p32_u_x*p32_v_z-p32_wp_y = 0;
   p32_u_y*p32_v_x-p32_wp_z = 0;
   p33_u_y*p33_v_z-p33_w_x = 0;
   p33_u_z*p33_v_x-p33_w_y = 0;
   p33_u_x*p33_v_y-p33_w_z = 0;
   p33_u_z*p33_v_y-p33_wp_x = 0;
   p33_u_x*p33_v_z-p33_wp_y = 0;
   p33_u_y*p33_v_x-p33_wp_z = 0;
   p34_u_y*p34_v_z-p34_w_x = 0;
   p34_u_z*p34_v_x-p34_w_y = 0;
   p34_u_x*p34_v_y-p34_w_z = 0;
   p34_u_z*p34_v_y-p34_wp_x = 0;
   p34_u_x*p34_v_z-p34_wp_y = 0;
   p34_u_y*p34_v_x-p34_wp_z = 0;
   p42_u_y*p42_v_z-p42_w_x = 0;
   p42_u_z*p42_v_x-p42_w_y = 0;
   p42_u_x*p42_v_y-p42_w_z = 0;
   p42_u_z*p42_v_y-p42_wp_x = 0;
   p42_u_x*p42_v_z-p42_wp_y = 0;
   p42_u_y*p42_v_x-p42_wp_z = 0;
   p43_u_y*p43_v_z-p43_w_x = 0;
   p43_u_z*p43_v_x-p43_w_y = 0;
   p43_u_x*p43_v_y-p43_w_z = 0;
   p43_u_z*p43_v_y-p43_wp_x = 0;
   p43_u_x*p43_v_z-p43_wp_y = 0;
   p43_u_y*p43_v_x-p43_wp_z = 0;
   p44_u_y*p44_v_z-p44_w_x = 0;
   p44_u_z*p44_v_x-p44_w_y = 0;
   p44_u_x*p44_v_y-p44_w_z = 0;
   p44_u_z*p44_v_y-p44_wp_x = 0;
   p44_u_x*p44_v_z-p44_wp_y = 0;
   p44_u_y*p44_v_x-p44_wp_z = 0;
   object_u_y*object_v_z-object_w_x = 0;
   object_u_z*object_v_x-object_w_y = 0;
   object_u_x*object_v_y-object_w_z = 0;
   object_u_z*object_v_y-object_wp_x = 0;
   object_u_x*object_v_z-object_wp_y = 0;
   object_u_y*object_v_x-object_wp_z = 0;




==========================================================================
%****************************************
% Simplified system 
% SIMPLIFICATION_LEVEL: 3
% Variable reduction 268 -> 134
% Num syst+secu variables in original  : 190 
% Num syst+secu variables in simplified: 82 
%   p12_u_x=p12_u_x
%   p12_u_y=p12_u_y
%   p12_u_z=p12_u_z
%   p12_v_x= -0
%   p12_v_y=p14_v_y
%   p12_v_z=p14_v_z
%   p12_w_x=p12_w_x
%   p12_w_y= -0
%   p12_w_z=p12_w_z
%   p12_wp_x=p12_wp_x
%   p12_wp_y=p12_wp_y
%   p12_wp_z= -0
%   p13_u_x=p13_u_x
%   p13_u_y=p13_u_y
%   p13_u_z=p13_u_z
%   p13_v_x= -0
%   p13_v_y=p14_v_y
%   p13_v_z=p14_v_z
%   p13_w_x=p13_w_x
%   p13_w_y= -0
%   p13_w_z=p13_w_z
%   p13_wp_x=p13_wp_x
%   p13_wp_y=p13_wp_y
%   p13_wp_z= -0
%   p14_u_x=p14_u_x
%   p14_u_y=p14_u_y
%   p14_u_z=p14_u_z
%   p14_v_x= -0
%   p14_v_y=p14_v_y
%   p14_v_z=p14_v_z
%   p14_w_x=p14_w_x
%   p14_w_y= -0
%   p14_w_z=p34_w_z
%   p14_wp_x=p14_wp_x
%   p14_wp_y=p34_wp_y
%   p14_wp_z= -0
%   p22_u_x=p22_u_x
%   p22_u_y=p22_u_y
%   p22_u_z=p22_u_z
%   p22_v_x= -0
%   p22_v_y=p24_v_y
%   p22_v_z=p24_v_z
%   p22_w_x=p22_w_x
%   p22_w_y= -0
%   p22_w_z=p22_w_z
%   p22_wp_x=p22_wp_x
%   p22_wp_y=p22_wp_y
%   p22_wp_z= -0
%   p23_u_x=p23_u_x
%   p23_u_y=p23_u_y
%   p23_u_z=p23_u_z
%   p23_v_x= -0
%   p23_v_y=p24_v_y
%   p23_v_z=p24_v_z
%   p23_w_x=p23_w_x
%   p23_w_y= -0
%   p23_w_z=p23_w_z
%   p23_wp_x=p23_wp_x
%   p23_wp_y=p23_wp_y
%   p23_wp_z= -0
%   p24_u_x=p24_u_x
%   p24_u_y=p24_u_y
%   p24_u_z=p24_u_z
%   p24_v_x= -0
%   p24_v_y=p24_v_y
%   p24_v_z=p24_v_z
%   p24_w_x=p24_w_x
%   p24_w_y= -0
%   p24_w_z=p24_w_z
%   p24_wp_x=p24_wp_x
%   p24_wp_y=p24_wp_y
%   p24_wp_z= -0
%   p32_u_x=p32_u_x
%   p32_u_y=p32_u_y
%   p32_u_z=p32_u_z
%   p32_v_x= -0
%   p32_v_y=p34_v_y
%   p32_v_z=p34_v_z
%   p32_w_x=p32_w_x
%   p32_w_y= -0
%   p32_w_z=p32_w_z
%   p32_wp_x=p32_wp_x
%   p32_wp_y=p32_wp_y
%   p32_wp_z= -0
%   p33_u_x=p33_u_x
%   p33_u_y=p33_u_y
%   p33_u_z=p33_u_z
%   p33_v_x= -0
%   p33_v_y=p34_v_y
%   p33_v_z=p34_v_z
%   p33_w_x=p33_w_x
%   p33_w_y= -0
%   p33_w_z=p33_w_z
%   p33_wp_x=p33_wp_x
%   p33_wp_y=p33_wp_y
%   p33_wp_z= -0
%   p34_u_x=p34_u_x
%   p34_u_y=p34_u_y
%   p34_u_z=p34_u_z
%   p34_v_x= -0
%   p34_v_y=p34_v_y
%   p34_v_z=p34_v_z
%   p34_w_x=p34_w_x
%   p34_w_y= -0
%   p34_w_z=p34_w_z
%   p34_wp_x=p34_wp_x
%   p34_wp_y=p34_wp_y
%   p34_wp_z= -0
%   p42_u_x=p42_u_x
%   p42_u_y=p42_u_y
%   p42_u_z=p42_u_z
%   p42_v_x= -0
%   p42_v_y=p44_v_y
%   p42_v_z=p44_v_z
%   p42_w_x=p42_w_x
%   p42_w_y= -0
%   p42_w_z=p42_w_z
%   p42_wp_x=p42_wp_x
%   p42_wp_y=p42_wp_y
%   p42_wp_z= -0
%   p43_u_x=p43_u_x
%   p43_u_y=p43_u_y
%   p43_u_z=p43_u_z
%   p43_v_x= -0
%   p43_v_y=p44_v_y
%   p43_v_z=p44_v_z
%   p43_w_x=p43_w_x
%   p43_w_y= -0
%   p43_w_z=p43_w_z
%   p43_wp_x=p43_wp_x
%   p43_wp_y=p43_wp_y
%   p43_wp_z= -0
%   p44_u_x=p44_u_x
%   p44_u_y=p44_u_y
%   p44_u_z=p44_u_z
%   p44_v_x= -0
%   p44_v_y=p44_v_y
%   p44_v_z=p44_v_z
%   p44_w_x=p44_w_x
%   p44_w_y= -0
%   p44_w_z=p44_w_z
%   p44_wp_x=p44_wp_x
%   p44_wp_y=p44_wp_y
%   p44_wp_z= -0
%   object_u_x=object_u_x
%   object_u_y=object_u_y
%   object_u_z=object_u_z
%   object_v_x=object_v_x
%   object_v_y=object_v_y
%   object_v_z=object_v_z
%   object_w_x=object_w_x
%   object_w_y=object_w_y
%   object_w_z=object_w_z
%   object_wp_x=object_wp_x
%   object_wp_y=object_wp_y
%   object_wp_z=object_wp_z
%   uni_u_palm_p12_x_0= +1
%   uni_u_palm_p12_y_0= -0
%   uni_u_palm_p12_z_0= -0
%   uni_v_palm_p12_x_0= -0
%   uni_v_palm_p12_y_0=p14_v_y
%   uni_v_palm_p12_z_0=p14_v_z
%   w1_palm_p12_x_0= -0
%   w1_palm_p12_y_0= -1
%   w1_palm_p12_z_0= -0
%   w2_palm_p12_x_0=w1_p12_p13_x_1
%   w2_palm_p12_y_0=w1_p12_p13_y_1
%   w2_palm_p12_z_0=w1_p12_p13_z_1
%   cos_0_palm_p12_0=-p14_v_y
%   cos_1_palm_p12_0=w1_p12_p13_x_1
%   w1_p12_p13_x_1=w1_p12_p13_x_1
%   w1_p12_p13_y_1=w1_p12_p13_y_1
%   w1_p12_p13_z_1=w1_p12_p13_z_1
%   w2_p12_p13_x_1=p13_u_x
%   w2_p12_p13_y_1=p13_u_y
%   w2_p12_p13_z_1=p13_u_z
%   cos_p12_p13_1=cos_p12_p13_1
%   w1_p13_p14_x_2=w1_p13_p14_x_2
%   w1_p13_p14_y_2=w1_p13_p14_y_2
%   w1_p13_p14_z_2=w1_p13_p14_z_2
%   w2_p13_p14_x_2=p14_u_x
%   w2_p13_p14_y_2=p14_u_y
%   w2_p13_p14_z_2=p14_u_z
%   cos_p13_p14_2=cos_p13_p14_2
%   uni_u_palm_p22_x_3= +1
%   uni_u_palm_p22_y_3= -0
%   uni_u_palm_p22_z_3= -0
%   uni_v_palm_p22_x_3= -0
%   uni_v_palm_p22_y_3=p24_v_y
%   uni_v_palm_p22_z_3=p24_v_z
%   w1_palm_p22_x_3= -0
%   w1_palm_p22_y_3= -1
%   w1_palm_p22_z_3= -0
%   w2_palm_p22_x_3=w1_p22_p23_x_4
%   w2_palm_p22_y_3=w1_p22_p23_y_4
%   w2_palm_p22_z_3=w1_p22_p23_z_4
%   cos_0_palm_p22_3=-p24_v_y
%   cos_1_palm_p22_3=w1_p22_p23_x_4
%   w1_p22_p23_x_4=w1_p22_p23_x_4
%   w1_p22_p23_y_4=w1_p22_p23_y_4
%   w1_p22_p23_z_4=w1_p22_p23_z_4
%   w2_p22_p23_x_4=p23_u_x
%   w2_p22_p23_y_4=p23_u_y
%   w2_p22_p23_z_4=p23_u_z
%   cos_p22_p23_4=cos_p22_p23_4
%   w1_p23_p24_x_5=w1_p23_p24_x_5
%   w1_p23_p24_y_5=w1_p23_p24_y_5
%   w1_p23_p24_z_5=w1_p23_p24_z_5
%   w2_p23_p24_x_5=p24_u_x
%   w2_p23_p24_y_5=p24_u_y
%   w2_p23_p24_z_5=p24_u_z
%   cos_p23_p24_5=cos_p23_p24_5
%   uni_u_palm_p32_x_6= +1
%   uni_u_palm_p32_y_6= -0
%   uni_u_palm_p32_z_6= -0
%   uni_v_palm_p32_x_6= -0
%   uni_v_palm_p32_y_6=p34_v_y
%   uni_v_palm_p32_z_6=p34_v_z
%   w1_palm_p32_x_6= -0
%   w1_palm_p32_y_6= -1
%   w1_palm_p32_z_6= -0
%   w2_palm_p32_x_6=w1_p32_p33_x_7
%   w2_palm_p32_y_6=w1_p32_p33_y_7
%   w2_palm_p32_z_6=w1_p32_p33_z_7
%   cos_0_palm_p32_6=-p34_v_y
%   cos_1_palm_p32_6=w1_p32_p33_x_7
%   w1_p32_p33_x_7=w1_p32_p33_x_7
%   w1_p32_p33_y_7=w1_p32_p33_y_7
%   w1_p32_p33_z_7=w1_p32_p33_z_7
%   w2_p32_p33_x_7=p33_u_x
%   w2_p32_p33_y_7=p33_u_y
%   w2_p32_p33_z_7=p33_u_z
%   cos_p32_p33_7=cos_p32_p33_7
%   w1_p33_p34_x_8=w1_p33_p34_x_8
%   w1_p33_p34_y_8=w1_p33_p34_y_8
%   w1_p33_p34_z_8=w1_p33_p34_z_8
%   w2_p33_p34_x_8=p34_u_x
%   w2_p33_p34_y_8=p34_u_y
%   w2_p33_p34_z_8=p34_u_z
%   cos_p33_p34_8=cos_p33_p34_8
%   uni_u_palm_p42_x_9= -1
%   uni_u_palm_p42_y_9= -0
%   uni_u_palm_p42_z_9= -0
%   uni_v_palm_p42_x_9= -0
%   uni_v_palm_p42_y_9=-p44_v_y
%   uni_v_palm_p42_z_9=-p44_v_z
%   w1_palm_p42_x_9= -0
%   w1_palm_p42_y_9= -1
%   w1_palm_p42_z_9= -0
%   w2_palm_p42_x_9=-p42_u_x
%   w2_palm_p42_y_9=-p42_u_y
%   w2_palm_p42_z_9=-p42_u_z
%   cos_0_palm_p42_9=p44_v_y
%   cos_1_palm_p42_9=p42_u_x
%   w1_p42_p43_x_10=w1_p42_p43_x_10
%   w1_p42_p43_y_10=w1_p42_p43_y_10
%   w1_p42_p43_z_10=w1_p42_p43_z_10
%   w2_p42_p43_x_10=p43_u_x
%   w2_p42_p43_y_10=p43_u_y
%   w2_p42_p43_z_10=p43_u_z
%   cos_p42_p43_10=cos_p42_p43_10
%   w1_p43_p44_x_11=w1_p43_p44_x_11
%   w1_p43_p44_y_11=w1_p43_p44_y_11
%   w1_p43_p44_z_11=w1_p43_p44_z_11
%   w2_p43_p44_x_11=p44_u_x
%   w2_p43_p44_y_11=p44_u_y
%   w2_p43_p44_z_11=p44_u_z
%   cos_p43_p44_11=cos_p43_p44_11

[SYSTEM VARS]
   p12_u_x : [-1,1]
   p12_u_y : [-1,1]
   p12_u_z : [-1,1]

[DUMMY VARS]
   p12_w_x : [-1,1]
   p12_w_z : [-1,1]
   p12_wp_x : [-1,1]
   p12_wp_y : [-1,1]

[SYSTEM VARS]
   p13_u_x : [-1,1]
   p13_u_y : [-1,1]
   p13_u_z : [-1,1]

[DUMMY VARS]
   p13_w_x : [-1,1]
   p13_w_z : [-1,1]
   p13_wp_x : [-1,1]
   p13_wp_y : [-1,1]

[SYSTEM VARS]
   p14_u_x : [-1,1]
   p14_u_y : [-1,1]
   p14_u_z : [-1,1]
   p14_v_y : [-1,-0.96592482625]
   p14_v_z : [-1,1]

[DUMMY VARS]
   p14_w_x : [-1,1]
   p14_wp_x : [-1,1]

[SYSTEM VARS]
   p22_u_x : [-1,1]
   p22_u_y : [-1,1]
   p22_u_z : [-1,1]

[DUMMY VARS]
   p22_w_x : [-1,1]
   p22_w_z : [-1,1]
   p22_wp_x : [-1,1]
   p22_wp_y : [-1,1]

[SYSTEM VARS]
   p23_u_x : [-1,1]
   p23_u_y : [-1,1]
   p23_u_z : [-1,1]

[DUMMY VARS]
   p23_w_x : [-1,1]
   p23_w_z : [-1,1]
   p23_wp_x : [-1,1]
   p23_wp_y : [-1,1]

[SYSTEM VARS]
   p24_u_x : [-1,1]
   p24_u_y : [-1,1]
   p24_u_z : [-1,1]
   p24_v_y : [-1,-0.96592482625]
   p24_v_z : [-1,1]

[DUMMY VARS]
   p24_w_x : [-1,1]
   p24_w_z : [-1,1]
   p24_wp_x : [-1,1]
   p24_wp_y : [-1,1]

[SYSTEM VARS]
   p32_u_x : [-1,1]
   p32_u_y : [-1,1]
   p32_u_z : [-1,1]

[DUMMY VARS]
   p32_w_x : [-1,1]
   p32_w_z : [-1,1]
   p32_wp_x : [-1,1]
   p32_wp_y : [-1,1]

[SYSTEM VARS]
   p33_u_x : [-1,1]
   p33_u_y : [-1,1]
   p33_u_z : [-1,1]

[DUMMY VARS]
   p33_w_x : [-1,1]
   p33_w_z : [-1,1]
   p33_wp_x : [-1,1]
   p33_wp_y : [-1,1]

[SYSTEM VARS]
   p34_u_x : [-1,1]
   p34_u_y : [-1,1]
   p34_u_z : [-1,1]
   p34_v_y : [-1,-0.96592482625]
   p34_v_z : [-1,1]

[DUMMY VARS]
   p34_w_x : [-1,1]
   p34_w_z : [-1,1]
   p34_wp_x : [-1,1]
   p34_wp_y : [-1,1]

[SYSTEM VARS]
   p42_u_x : [-1.00001000021e-06,1]
   p42_u_y : [-1,1]
   p42_u_z : [-1,1]

[DUMMY VARS]
   p42_w_x : [-1,1]
   p42_w_z : [-1,1]
   p42_wp_x : [-1,1]
   p42_wp_y : [-1,1]

[SYSTEM VARS]
   p43_u_x : [-1,1]
   p43_u_y : [-1,1]
   p43_u_z : [-1,1]

[DUMMY VARS]
   p43_w_x : [-1,1]
   p43_w_z : [-1,1]
   p43_wp_x : [-1,1]
   p43_wp_y : [-1,1]

[SYSTEM VARS]
   p44_u_x : [-1,1]
   p44_u_y : [-1,1]
   p44_u_z : [-1,1]
   p44_v_y : [0.96592482625,1]
   p44_v_z : [-1,1]

[DUMMY VARS]
   p44_w_x : [-1,1]
   p44_w_z : [-1,1]
   p44_wp_x : [-1,1]
   p44_wp_y : [-1,1]

[SYSTEM VARS]
   object_u_x : [-1,1]
   object_u_y : [-1,1]
   object_u_z : [-1,1]
   object_v_x : [-1,1]
   object_v_y : [-1,1]
   object_v_z : [-1,1]

[DUMMY VARS]
   object_w_x : [-1,1]
   object_w_y : [-1,1]
   object_w_z : [-1,1]
   object_wp_x : [-1,1]
   object_wp_y : [-1,1]
   object_wp_z : [-1,1]

[SECONDARY VARS]
   w1_p12_p13_x_1 : [0.707105781156,1]
   w1_p12_p13_y_1 : [-1,1]
   w1_p12_p13_z_1 : [-1,1]
   cos_p12_p13_1 : [0.707105781187,1.000001]
   w1_p13_p14_x_2 : [-1,1]
   w1_p13_p14_y_2 : [-1,1]
   w1_p13_p14_z_2 : [-1,1]
   cos_p13_p14_2 : [0.707105781187,1.000001]
   w1_p22_p23_x_4 : [0.707105781156,1]
   w1_p22_p23_y_4 : [-1,1]
   w1_p22_p23_z_4 : [-1,1]
   cos_p22_p23_4 : [0.707105781187,1.000001]
   w1_p23_p24_x_5 : [-1,1]
   w1_p23_p24_y_5 : [-1,1]
   w1_p23_p24_z_5 : [-1,1]
   cos_p23_p24_5 : [0.707105781187,1.000001]
   w1_p32_p33_x_7 : [0.707105781156,1]
   w1_p32_p33_y_7 : [-1,1]
   w1_p32_p33_z_7 : [-1,1]
   cos_p32_p33_7 : [0.707105781187,1.000001]
   w1_p33_p34_x_8 : [-1,1]
   w1_p33_p34_y_8 : [-1,1]
   w1_p33_p34_z_8 : [-1,1]
   cos_p33_p34_8 : [0.707105781187,1.000001]
   w1_p42_p43_x_10 : [-1,1]
   w1_p42_p43_y_10 : [-1,1]
   w1_p42_p43_z_10 : [-1,1]
   cos_p42_p43_10 : [0.707105781187,1.000001]
   w1_p43_p44_x_11 : [-1,1]
   w1_p43_p44_y_11 : [-1,1]
   w1_p43_p44_z_11 : [-1,1]
   cos_p43_p44_11 : [0.707105781187,1.000001]

[DUMMY VARS]
   dummy_p12_u_y_p14_v_y : [-1,1]
   dummy_p12_u_z_p14_v_z : [-1,1]
   dummy_p13_u_y_p14_v_y : [-1,1]
   dummy_p13_u_z_p14_v_z : [-1,1]
   dummy_p14_u_y_p14_v_y : [-1,1]
   dummy_p14_u_z_p14_v_z : [-1,1]
   dummy_p22_u_y_p24_v_y : [-1,1]
   dummy_p22_u_z_p24_v_z : [-1,1]
   dummy_p23_u_y_p24_v_y : [-1,1]
   dummy_p23_u_z_p24_v_z : [-1,1]
   dummy_p24_u_y_p24_v_y : [-1,1]
   dummy_p24_u_z_p24_v_z : [-1,1]
   dummy_p32_u_y_p34_v_y : [-1,1]
   dummy_p32_u_z_p34_v_z : [-1,1]
   dummy_p33_u_y_p34_v_y : [-1,1]
   dummy_p33_u_z_p34_v_z : [-1,1]
   dummy_p34_u_y_p34_v_y : [-1,1]
   dummy_p34_u_z_p34_v_z : [-1,1]
   dummy_p42_u_y_p44_v_y : [-1,1]
   dummy_p42_u_z_p44_v_z : [-1,1]
   dummy_p43_u_y_p44_v_y : [-1,1]
   dummy_p43_u_z_p44_v_z : [-1,1]
   dummy_p44_u_y_p44_v_y : [-1,1]
   dummy_p44_u_z_p44_v_z : [-1,1]
   dummy_object_u_x_object_v_x : [-1,1]
   dummy_object_u_y_object_v_y : [-1,1]
   dummy_object_u_z_object_v_z : [-1,1]
   dummy_p13_u_x_w1_p12_p13_x_1 : [-1,1]
   dummy_p13_u_y_w1_p12_p13_y_1 : [-1,1]
   dummy_p13_u_z_w1_p12_p13_z_1 : [-1,1]
   dummy_p14_u_x_w1_p13_p14_x_2 : [-1,1]
   dummy_p14_u_y_w1_p13_p14_y_2 : [-1,1]
   dummy_p14_u_z_w1_p13_p14_z_2 : [-1,1]
   dummy_p23_u_x_w1_p22_p23_x_4 : [-1,1]
   dummy_p23_u_y_w1_p22_p23_y_4 : [-1,1]
   dummy_p23_u_z_w1_p22_p23_z_4 : [-1,1]
   dummy_p24_u_x_w1_p23_p24_x_5 : [-1,1]
   dummy_p24_u_y_w1_p23_p24_y_5 : [-1,1]
   dummy_p24_u_z_w1_p23_p24_z_5 : [-1,1]
   dummy_p33_u_x_w1_p32_p33_x_7 : [-1,1]
   dummy_p33_u_y_w1_p32_p33_y_7 : [-1,1]
   dummy_p33_u_z_w1_p32_p33_z_7 : [-1,1]
   dummy_p34_u_x_w1_p33_p34_x_8 : [-1,1]
   dummy_p34_u_y_w1_p33_p34_y_8 : [-1,1]
   dummy_p34_u_z_w1_p33_p34_z_8 : [-1,1]
   dummy_p43_u_x_w1_p42_p43_x_10 : [-1,1]
   dummy_p43_u_y_w1_p42_p43_y_10 : [-1,1]
   dummy_p43_u_z_w1_p42_p43_z_10 : [-1,1]
   dummy_p44_u_x_w1_p43_p44_x_11 : [-1,1]
   dummy_p44_u_y_w1_p43_p44_y_11 : [-1,1]
   dummy_p44_u_z_w1_p43_p44_z_11 : [-1,1]

[SYSTEM EQS]

   p12_u_x^2+p12_u_y^2+p12_u_z^2 = 1;
   p14_v_y^2+p14_v_z^2 = 1;
   dummy_p12_u_y_p14_v_y+dummy_p12_u_z_p14_v_z = 0;
   p13_u_x^2+p13_u_y^2+p13_u_z^2 = 1;
   dummy_p13_u_y_p14_v_y+dummy_p13_u_z_p14_v_z = 0;
   p14_u_x^2+p14_u_y^2+p14_u_z^2 = 1;
   dummy_p14_u_y_p14_v_y+dummy_p14_u_z_p14_v_z = 0;
   p22_u_x^2+p22_u_y^2+p22_u_z^2 = 1;
   p24_v_y^2+p24_v_z^2 = 1;
   dummy_p22_u_y_p24_v_y+dummy_p22_u_z_p24_v_z = 0;
   p23_u_x^2+p23_u_y^2+p23_u_z^2 = 1;
   dummy_p23_u_y_p24_v_y+dummy_p23_u_z_p24_v_z = 0;
   p24_u_x^2+p24_u_y^2+p24_u_z^2 = 1;
   dummy_p24_u_y_p24_v_y+dummy_p24_u_z_p24_v_z = 0;
   p32_u_x^2+p32_u_y^2+p32_u_z^2 = 1;
   p34_v_y^2+p34_v_z^2 = 1;
   dummy_p32_u_y_p34_v_y+dummy_p32_u_z_p34_v_z = 0;
   p33_u_x^2+p33_u_y^2+p33_u_z^2 = 1;
   dummy_p33_u_y_p34_v_y+dummy_p33_u_z_p34_v_z = 0;
   p34_u_x^2+p34_u_y^2+p34_u_z^2 = 1;
   dummy_p34_u_y_p34_v_y+dummy_p34_u_z_p34_v_z = 0;
   p42_u_x^2+p42_u_y^2+p42_u_z^2 = 1;
   p44_v_y^2+p44_v_z^2 = 1;
   dummy_p42_u_y_p44_v_y+dummy_p42_u_z_p44_v_z = 0;
   p43_u_x^2+p43_u_y^2+p43_u_z^2 = 1;
   dummy_p43_u_y_p44_v_y+dummy_p43_u_z_p44_v_z = 0;
   p44_u_x^2+p44_u_y^2+p44_u_z^2 = 1;
   dummy_p44_u_y_p44_v_y+dummy_p44_u_z_p44_v_z = 0;
   object_u_x^2+object_u_y^2+object_u_z^2 = 1;
   object_v_x^2+object_v_y^2+object_v_z^2 = 1;
   dummy_object_u_x_object_v_x+dummy_object_u_y_object_v_y+dummy_object_u_z_object_v_z = 0;
   0.7071067811865476*p12_u_x+0.7071067811865475*p12_w_x-0.7071067811865475*p12_wp_x-w1_p12_p13_x_1 = 0;
   0.7071067811865476*p12_u_y-0.7071067811865475*p12_wp_y-w1_p12_p13_y_1 = 0;
   0.7071067811865476*p12_u_z+0.7071067811865475*p12_w_z-w1_p12_p13_z_1 = 0;
   cos_p12_p13_1-dummy_p13_u_x_w1_p12_p13_x_1-dummy_p13_u_y_w1_p12_p13_y_1-dummy_p13_u_z_w1_p12_p13_z_1 = -0;
   0.7071067811865476*p13_u_x+0.7071067811865475*p13_w_x-0.7071067811865475*p13_wp_x-w1_p13_p14_x_2 = 0;
   0.7071067811865476*p13_u_y-0.7071067811865475*p13_wp_y-w1_p13_p14_y_2 = 0;
   0.7071067811865476*p13_u_z+0.7071067811865475*p13_w_z-w1_p13_p14_z_2 = 0;
   cos_p13_p14_2-dummy_p14_u_x_w1_p13_p14_x_2-dummy_p14_u_y_w1_p13_p14_y_2-dummy_p14_u_z_w1_p13_p14_z_2 = -0;
   0.7071067811865476*p22_u_x+0.7071067811865475*p22_w_x-0.7071067811865475*p22_wp_x-w1_p22_p23_x_4 = 0;
   0.7071067811865476*p22_u_y-0.7071067811865475*p22_wp_y-w1_p22_p23_y_4 = 0;
   0.7071067811865476*p22_u_z+0.7071067811865475*p22_w_z-w1_p22_p23_z_4 = 0;
   cos_p22_p23_4-dummy_p23_u_x_w1_p22_p23_x_4-dummy_p23_u_y_w1_p22_p23_y_4-dummy_p23_u_z_w1_p22_p23_z_4 = -0;
   0.7071067811865476*p23_u_x+0.7071067811865475*p23_w_x-0.7071067811865475*p23_wp_x-w1_p23_p24_x_5 = 0;
   0.7071067811865476*p23_u_y-0.7071067811865475*p23_wp_y-w1_p23_p24_y_5 = 0;
   0.7071067811865476*p23_u_z+0.7071067811865475*p23_w_z-w1_p23_p24_z_5 = 0;
   cos_p23_p24_5-dummy_p24_u_x_w1_p23_p24_x_5-dummy_p24_u_y_w1_p23_p24_y_5-dummy_p24_u_z_w1_p23_p24_z_5 = -0;
   0.7071067811865476*p32_u_x+0.7071067811865475*p32_w_x-0.7071067811865475*p32_wp_x-w1_p32_p33_x_7 = 0;
   0.7071067811865476*p32_u_y-0.7071067811865475*p32_wp_y-w1_p32_p33_y_7 = 0;
   0.7071067811865476*p32_u_z+0.7071067811865475*p32_w_z-w1_p32_p33_z_7 = 0;
   cos_p32_p33_7-dummy_p33_u_x_w1_p32_p33_x_7-dummy_p33_u_y_w1_p32_p33_y_7-dummy_p33_u_z_w1_p32_p33_z_7 = -0;
   0.7071067811865476*p33_u_x+0.7071067811865475*p33_w_x-0.7071067811865475*p33_wp_x-w1_p33_p34_x_8 = 0;
   0.7071067811865476*p33_u_y-0.7071067811865475*p33_wp_y-w1_p33_p34_y_8 = 0;
   0.7071067811865476*p33_u_z+0.7071067811865475*p33_w_z-w1_p33_p34_z_8 = 0;
   cos_p33_p34_8-dummy_p34_u_x_w1_p33_p34_x_8-dummy_p34_u_y_w1_p33_p34_y_8-dummy_p34_u_z_w1_p33_p34_z_8 = -0;
   0.7071067811865476*p42_u_x+0.7071067811865475*p42_w_x-0.7071067811865475*p42_wp_x-w1_p42_p43_x_10 = 0;
   0.7071067811865476*p42_u_y-0.7071067811865475*p42_wp_y-w1_p42_p43_y_10 = 0;
   0.7071067811865476*p42_u_z+0.7071067811865475*p42_w_z-w1_p42_p43_z_10 = 0;
   cos_p42_p43_10-dummy_p43_u_x_w1_p42_p43_x_10-dummy_p43_u_y_w1_p42_p43_y_10-dummy_p43_u_z_w1_p42_p43_z_10 = -0;
   0.7071067811865476*p43_u_x+0.7071067811865475*p43_w_x-0.7071067811865475*p43_wp_x-w1_p43_p44_x_11 = 0;
   0.7071067811865476*p43_u_y-0.7071067811865475*p43_wp_y-w1_p43_p44_y_11 = 0;
   0.7071067811865476*p43_u_z+0.7071067811865475*p43_w_z-w1_p43_p44_z_11 = 0;
   cos_p43_p44_11-dummy_p44_u_x_w1_p43_p44_x_11-dummy_p44_u_y_w1_p43_p44_y_11-dummy_p44_u_z_w1_p43_p44_z_11 = -0;
   p14_w_x-p14_wp_x-p34_w_x+p34_wp_x = 0;
   p24_w_x-p24_wp_x+0.5164943340882256*object_u_x+0.8562906065435731*object_w_x-0.8562906065435731*object_wp_x = 0;
   p24_wp_y-1.210977789106605*p34_wp_y+0.3397962724553475*object_u_y = 0;
   p24_w_z-1.210977789106605*p34_w_z-0.3397962724553475*object_u_z = 0;
   p34_w_x-p34_wp_x+0.7071067811865475*object_u_x+0.7071067811865475*object_w_x-0.7071067811865475*object_wp_x = 0;
   p34_wp_y-0.7071067811865475*object_u_y-0.7071067811865475*object_w_y+0.7071067811865475*object_wp_y = -0;
   p34_w_z+0.7071067811865475*object_u_z+0.7071067811865475*object_w_z-0.7071067811865475*object_wp_z = 0;
   p44_w_x-p44_wp_x+0.9778216247643486*object_u_x+0.05420119867276273*object_v_x-0.2023044740129221*object_w_x+0.2023044740129221*object_wp_x = 0;
   0.2861017308778298*p34_wp_y+p44_wp_y-1.180126098777271*object_u_y-0.05420119867276273*object_v_y = -0;
   0.2861017308778298*p34_w_z+p44_w_z+1.180126098777271*object_u_z+0.05420119867276273*object_v_z = 0;
   76.66*p22_u_x+56*p23_u_x+27.85682109737468*p24_u_x-76.66*p42_u_x-66*p43_u_x-34.76240698960329*p44_u_x+52.18600176300236*object_u_x+11.50827234799539*object_v_x-126.3850926126538*object_w_x+126.3850926126538*object_wp_x = 30.665;
   76.66*p12_u_y+56*p13_u_y+27.85682109737468*p14_u_y-76.66*p22_u_y-56*p23_u_y-27.85682109737468*p24_u_y+42.70457529334703*p34_wp_y-42.29165991312167*object_u_y+67*object_v_y = 67;
   76.66*p12_u_z+56*p13_u_z+27.85682109737468*p14_u_z-76.66*p22_u_z-56*p23_u_z-27.85682109737468*p24_u_z-42.70457529334703*p34_w_z-42.29165991312167*object_u_z+67*object_v_z = 0;
   76.66*p12_u_x+56*p13_u_x+27.85682109737468*p14_u_x-76.66*p32_u_x-56*p33_u_x-27.85682109737468*p34_u_x+3.098350370578373e-05*p34_w_x-3.098350370578373e-05*p34_wp_x+134*object_v_x = 0;
   76.66*p12_u_y+56*p13_u_y+27.85682109737468*p14_u_y-76.66*p32_u_y-56*p33_u_y-27.85682109737468*p34_u_y-3.098350370578373e-05*p34_wp_y+134*object_v_y = 134;
   76.66*p12_u_z+56*p13_u_z+27.85682109737468*p14_u_z-76.66*p32_u_z-56*p33_u_z-27.85682109737468*p34_u_z+3.098350370578373e-05*p34_w_z+134*object_v_z = 0;
   76.66*p12_u_x+56*p13_u_x+27.85682109737468*p14_u_x+19.1514*p14_w_x-19.1514*p14_wp_x-76.66*p42_u_x-66*p43_u_x-34.76240698960329*p44_u_x+53.63312143671392*object_u_x+78.50827234799539*object_v_x-82.6463130258206*object_w_x+82.6463130258206*object_wp_x = 30.665;
   76.66*p12_u_y+56*p13_u_y+27.85682109737468*p14_u_y-76.66*p42_u_y-66*p43_u_y-34.76240698960329*p44_u_y+475.4635225165245*p44_wp_y-424.8274774757906*object_u_y+52.73757950242565*object_v_y = 97.012;
   76.66*p12_u_z+56*p13_u_z+27.85682109737468*p14_u_z-76.66*p42_u_z-66*p43_u_z-34.76240698960329*p44_u_z-475.4635225165245*p44_w_z-424.8274774757906*object_u_z+52.73757950242565*object_v_z = -130.7358;

[DUMMY EQS]

   p12_u_y*p14_v_y-dummy_p12_u_y_p14_v_y = 0;
   p12_u_z*p14_v_z-dummy_p12_u_z_p14_v_z = 0;
   p13_u_y*p14_v_y-dummy_p13_u_y_p14_v_y = 0;
   p13_u_z*p14_v_z-dummy_p13_u_z_p14_v_z = 0;
   p14_u_y*p14_v_y-dummy_p14_u_y_p14_v_y = 0;
   p14_u_z*p14_v_z-dummy_p14_u_z_p14_v_z = 0;
   p22_u_y*p24_v_y-dummy_p22_u_y_p24_v_y = 0;
   p22_u_z*p24_v_z-dummy_p22_u_z_p24_v_z = 0;
   p23_u_y*p24_v_y-dummy_p23_u_y_p24_v_y = 0;
   p23_u_z*p24_v_z-dummy_p23_u_z_p24_v_z = 0;
   p24_u_y*p24_v_y-dummy_p24_u_y_p24_v_y = 0;
   p24_u_z*p24_v_z-dummy_p24_u_z_p24_v_z = 0;
   p32_u_y*p34_v_y-dummy_p32_u_y_p34_v_y = 0;
   p32_u_z*p34_v_z-dummy_p32_u_z_p34_v_z = 0;
   p33_u_y*p34_v_y-dummy_p33_u_y_p34_v_y = 0;
   p33_u_z*p34_v_z-dummy_p33_u_z_p34_v_z = 0;
   p34_u_y*p34_v_y-dummy_p34_u_y_p34_v_y = 0;
   p34_u_z*p34_v_z-dummy_p34_u_z_p34_v_z = 0;
   p42_u_y*p44_v_y-dummy_p42_u_y_p44_v_y = 0;
   p42_u_z*p44_v_z-dummy_p42_u_z_p44_v_z = 0;
   p43_u_y*p44_v_y-dummy_p43_u_y_p44_v_y = 0;
   p43_u_z*p44_v_z-dummy_p43_u_z_p44_v_z = 0;
   p44_u_y*p44_v_y-dummy_p44_u_y_p44_v_y = 0;
   p44_u_z*p44_v_z-dummy_p44_u_z_p44_v_z = 0;
   object_u_x*object_v_x-dummy_object_u_x_object_v_x = 0;
   object_u_y*object_v_y-dummy_object_u_y_object_v_y = 0;
   object_u_z*object_v_z-dummy_object_u_z_object_v_z = 0;
   p13_u_x*w1_p12_p13_x_1-dummy_p13_u_x_w1_p12_p13_x_1 = 0;
   p13_u_y*w1_p12_p13_y_1-dummy_p13_u_y_w1_p12_p13_y_1 = 0;
   p13_u_z*w1_p12_p13_z_1-dummy_p13_u_z_w1_p12_p13_z_1 = 0;
   p14_u_x*w1_p13_p14_x_2-dummy_p14_u_x_w1_p13_p14_x_2 = 0;
   p14_u_y*w1_p13_p14_y_2-dummy_p14_u_y_w1_p13_p14_y_2 = 0;
   p14_u_z*w1_p13_p14_z_2-dummy_p14_u_z_w1_p13_p14_z_2 = 0;
   p23_u_x*w1_p22_p23_x_4-dummy_p23_u_x_w1_p22_p23_x_4 = 0;
   p23_u_y*w1_p22_p23_y_4-dummy_p23_u_y_w1_p22_p23_y_4 = 0;
   p23_u_z*w1_p22_p23_z_4-dummy_p23_u_z_w1_p22_p23_z_4 = 0;
   p24_u_x*w1_p23_p24_x_5-dummy_p24_u_x_w1_p23_p24_x_5 = 0;
   p24_u_y*w1_p23_p24_y_5-dummy_p24_u_y_w1_p23_p24_y_5 = 0;
   p24_u_z*w1_p23_p24_z_5-dummy_p24_u_z_w1_p23_p24_z_5 = 0;
   p33_u_x*w1_p32_p33_x_7-dummy_p33_u_x_w1_p32_p33_x_7 = 0;
   p33_u_y*w1_p32_p33_y_7-dummy_p33_u_y_w1_p32_p33_y_7 = 0;
   p33_u_z*w1_p32_p33_z_7-dummy_p33_u_z_w1_p32_p33_z_7 = 0;
   p34_u_x*w1_p33_p34_x_8-dummy_p34_u_x_w1_p33_p34_x_8 = 0;
   p34_u_y*w1_p33_p34_y_8-dummy_p34_u_y_w1_p33_p34_y_8 = 0;
   p34_u_z*w1_p33_p34_z_8-dummy_p34_u_z_w1_p33_p34_z_8 = 0;
   p43_u_x*w1_p42_p43_x_10-dummy_p43_u_x_w1_p42_p43_x_10 = 0;
   p43_u_y*w1_p42_p43_y_10-dummy_p43_u_y_w1_p42_p43_y_10 = 0;
   p43_u_z*w1_p42_p43_z_10-dummy_p43_u_z_w1_p42_p43_z_10 = 0;
   p44_u_x*w1_p43_p44_x_11-dummy_p44_u_x_w1_p43_p44_x_11 = 0;
   p44_u_y*w1_p43_p44_y_11-dummy_p44_u_y_w1_p43_p44_y_11 = 0;
   p44_u_z*w1_p43_p44_z_11-dummy_p44_u_z_w1_p43_p44_z_11 = 0;
   p12_u_y*p14_v_z-p12_w_x = 0;
   p12_u_x*p14_v_y-p12_w_z = 0;
   p12_u_z*p14_v_y-p12_wp_x = 0;
   p12_u_x*p14_v_z-p12_wp_y = 0;
   p13_u_y*p14_v_z-p13_w_x = 0;
   p13_u_x*p14_v_y-p13_w_z = 0;
   p13_u_z*p14_v_y-p13_wp_x = 0;
   p13_u_x*p14_v_z-p13_wp_y = 0;
   p14_u_y*p14_v_z-p14_w_x = 0;
   p14_u_x*p14_v_y-p34_w_z = 0;
   p14_u_z*p14_v_y-p14_wp_x = 0;
   p14_u_x*p14_v_z-p34_wp_y = 0;
   p22_u_y*p24_v_z-p22_w_x = 0;
   p22_u_x*p24_v_y-p22_w_z = 0;
   p22_u_z*p24_v_y-p22_wp_x = 0;
   p22_u_x*p24_v_z-p22_wp_y = 0;
   p23_u_y*p24_v_z-p23_w_x = 0;
   p23_u_x*p24_v_y-p23_w_z = 0;
   p23_u_z*p24_v_y-p23_wp_x = 0;
   p23_u_x*p24_v_z-p23_wp_y = 0;
   p24_u_y*p24_v_z-p24_w_x = 0;
   p24_u_x*p24_v_y-p24_w_z = 0;
   p24_u_z*p24_v_y-p24_wp_x = 0;
   p24_u_x*p24_v_z-p24_wp_y = 0;
   p32_u_y*p34_v_z-p32_w_x = 0;
   p32_u_x*p34_v_y-p32_w_z = 0;
   p32_u_z*p34_v_y-p32_wp_x = 0;
   p32_u_x*p34_v_z-p32_wp_y = 0;
   p33_u_y*p34_v_z-p33_w_x = 0;
   p33_u_x*p34_v_y-p33_w_z = 0;
   p33_u_z*p34_v_y-p33_wp_x = 0;
   p33_u_x*p34_v_z-p33_wp_y = 0;
   p34_u_y*p34_v_z-p34_w_x = 0;
   p34_u_x*p34_v_y-p34_w_z = 0;
   p34_u_z*p34_v_y-p34_wp_x = 0;
   p34_u_x*p34_v_z-p34_wp_y = 0;
   p42_u_y*p44_v_z-p42_w_x = 0;
   p42_u_x*p44_v_y-p42_w_z = 0;
   p42_u_z*p44_v_y-p42_wp_x = 0;
   p42_u_x*p44_v_z-p42_wp_y = 0;
   p43_u_y*p44_v_z-p43_w_x = 0;
   p43_u_x*p44_v_y-p43_w_z = 0;
   p43_u_z*p44_v_y-p43_wp_x = 0;
   p43_u_x*p44_v_z-p43_wp_y = 0;
   p44_u_y*p44_v_z-p44_w_x = 0;
   p44_u_x*p44_v_y-p44_w_z = 0;
   p44_u_z*p44_v_y-p44_wp_x = 0;
   p44_u_x*p44_v_z-p44_wp_y = 0;
   object_u_y*object_v_z-object_w_x = 0;
   object_u_z*object_v_x-object_w_y = 0;
   object_u_x*object_v_y-object_w_z = 0;
   object_u_z*object_v_y-object_wp_x = 0;
   object_u_x*object_v_z-object_wp_y = 0;
   object_u_y*object_v_x-object_wp_z = 0;

==========================================================================
Cuik executed in 160 processors
SOLUTIONS (to input file /home/porta/cuik/CuikSuite/examples/RobotHand/RobotHand.cuik):

   1 (err:2.30875 tm:59):{ 190  p12_u_x[0.306059375366,0.391773146342] p12_u_y[-0.0131471614759,0.0634286767948] p12_u_z[0.919147527023,0.952012425747] p12_v_x[-0,0] p12_v_y[-1,-0.997717005041] p12_v_z[-0.0137781787714,0.0672806008644] p13_u_x[0.981185056172,0.994031948981] p13_u_y[-0.0102255198494,0.00266362561326] p13_u_z[-0.192878491559,-0.109089341525] p13_v_x[-0,0] p13_v_y[-1,-0.997717005041] p13_v_z[-0.0137781787714,0.0672806008644] p14_u_x[0.64496966086,0.687424327605] p14_u_y[-0.0514082848845,0.00998691657882] p14_u_z[-0.764293099409,-0.725071493345] p14_v_x[-0,0] p14_v_y[-1,-0.997717005041] p14_v_z[-0.0137781787714,0.0672806008644] p22_u_x[0.0992641058721,0.189996644736] p22_u_y[-0.0176046986969,0.0533705874685] p22_u_z[0.980313760458,0.995080259182] p22_v_x[-0,0] p22_v_y[-1,-0.998505316383] p22_v_z[-0.0175543627018,0.0543444384278] p23_u_x[0.968298291419,0.98269297924] p23_u_y[-0.0044130644369,0.013177339563] p23_u_z[0.185732079923,0.249442116096] p23_v_x[-0,0] p23_v_y[-1,-0.998505316383] p23_v_z[-0.0175543627018,0.0543444384278] p24_u_x[0.809624389579,0.841785023226] p24_u_y[-0.0318876866157,0.0103442716585] p24_u_z[-0.587074579657,-0.539687116751] p24_v_x[-0,0] p24_v_y[-1,-0.998505316383] p24_v_z[-0.0175543627018,0.0543444384278] p32_u_x[0.279551530697,0.367485184522] p32_u_y[-0.0141347296148,0.0640689684408] p32_u_z[0.929211411202,0.959906980933] p32_v_x[-0,0] p32_v_y[-1,-0.99772031673] p32_v_z[-0.0146904484358,0.0673087212055] p33_u_x[0.97843662979,0.992692583787] p33_u_y[-0.0129874465561,0.00303496119018] p33_u_z[-0.206119717588,-0.121182608019] p33_v_x[-0,0] p33_v_y[-1,-0.99772031673] p33_v_z[-0.0146904484358,0.0673087212055] p34_u_x[0.644969481483,0.687527395577] p34_u_y[-0.0514525360937,0.0112536564003] p34_u_z[-0.764293293821,-0.725078982312] p34_v_x[-0,0] p34_v_y[-1,-0.99772031673] p34_v_z[-0.0146904484358,0.0673087212055] p42_u_x[0.950684096252,0.977040671753] p42_u_y[0.0479525022221,0.0750860412692] p42_u_z[-0.302830448793,-0.207990867301] p42_v_x[-0,0] p42_v_y[0.969285949327,0.975314743089] p42_v_z[0.221089256612,0.245939770498] p43_u_x[0.260256545412,0.309076758573] p43_u_y[-0.234734085768,-0.211225165882] p43_u_z[0.921803852025,0.941240962436] p43_v_x[-0,0] p43_v_y[0.969285949327,0.975314743089] p43_v_z[0.221089256612,0.245939770498] p44_u_x[0.239730728609,0.291986452784] p44_u_y[-0.238699595707,-0.211643743568] p44_u_z[0.927753086984,0.945726105755] p44_v_x[-0,0] p44_v_y[0.969285949327,0.975314743089] p44_v_z[0.221089256612,0.245939770498] object_u_x[0.996300323567,0.999584358658] object_u_y[-0.00242866957633,0.0247378039715] object_u_z[-0.0838021411744,-0.0289414243369] object_v_x[-0.0276579211594,0.00398121547146] object_v_y[0.998856163013,1] object_v_z[-0.0401374738192,0.0226382311887] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-1,-0.997717005041] uni_v_palm_p12_z_0[-0.0137781787714,0.0672806008644] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.887346132888,0.92952225583] w2_palm_p12_y_0[-0.00793975680383,0.0289926465761] w2_palm_p12_z_0[0.373153495193,0.457254315855] cos_0_palm_p12_0[0.997717005041,1.00000000001] cos_1_palm_p12_0[0.887346132888,0.92952225583] w1_p12_p13_x_1[0.887346132888,0.92952225583] w1_p12_p13_y_1[-0.00793975680383,0.0289926465761] w1_p12_p13_z_1[0.373153495193,0.457254315855] w2_p12_p13_x_1[0.981185056172,0.994031948981] w2_p12_p13_y_1[-0.0102255198494,0.00266362561326] w2_p12_p13_z_1[-0.192878491559,-0.109089341525] cos_p12_p13_1[0.782502776692,0.880703293302] w1_p13_p14_x_2[0.55715408798,0.626012226531] w1_p13_p14_y_2[-0.0538485790433,0.0115679667809] w1_p13_p14_z_2[-0.830880250147,-0.778385575958] w2_p13_p14_x_2[0.64496966086,0.687424327605] w2_p13_p14_y_2[-0.0514082848845,0.00998691657882] w2_p13_p14_z_2[-0.764293099409,-0.725071493345] cos_p13_p14_2[0.985013578808,1.000001] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-1,-0.998505316383] uni_v_palm_p22_z_3[-0.0175543627018,0.0543444384278] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.772307862613,0.830250432439] w2_palm_p22_y_3[-0.0124339903036,0.0336128500023] w2_palm_p22_z_3[0.558923358483,0.633503184925] cos_0_palm_p22_3[0.998505316383,1.00000000001] cos_1_palm_p22_3[0.772307862613,0.830250432439] w1_p22_p23_x_4[0.772307862613,0.830250432439] w1_p22_p23_y_4[-0.0124339903036,0.0336128500023] w1_p22_p23_z_4[0.558923358483,0.633503184925] w2_p22_p23_x_4[0.968298291419,0.98269297924] w2_p22_p23_y_4[-0.0044130644369,0.013177339563] w2_p22_p23_z_4[0.185732079923,0.249442116096] cos_p22_p23_4[0.880827558068,0.947346166852] w1_p23_p24_x_5[0.825842910201,0.861878351311] w1_p23_p24_y_5[-0.0298465038189,0.0106693386843] w1_p23_p24_z_5[-0.563205175735,-0.507293718038] w2_p23_p24_x_5[0.809624389579,0.841785023226] w2_p23_p24_y_5[-0.0318876866157,0.0103442716585] w2_p23_p24_z_5[-0.587074579657,-0.539687116751] cos_p23_p24_5[0.994416322055,1.000001] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-1,-0.99772031673] uni_v_palm_p32_z_6[-0.0146904484358,0.0673087212055] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.874260027851,0.919456106429] w2_palm_p32_y_6[-0.0089168930207,0.0307351228205] w2_palm_p32_z_6[0.397449898114,0.481012866918] cos_0_palm_p32_6[0.99772031673,1.00000000001] cos_1_palm_p32_6[0.874260027851,0.919456106429] w1_p32_p33_x_7[0.874260027851,0.919456106429] w1_p32_p33_y_7[-0.0089168930207,0.0307351228205] w1_p32_p33_z_7[0.397449898114,0.481012866918] w2_p32_p33_x_7[0.97843662979,0.992692583787] w2_p32_p33_y_7[-0.0129874465561,0.00303496119018] w2_p32_p33_z_7[-0.206119717588,-0.121182608019] cos_p32_p33_7[0.756046800533,0.860908570907] w1_p33_p34_x_8[0.545645301032,0.616390649103] w1_p33_p34_y_8[-0.0555740546199,0.0124578499836] w1_p33_p34_z_8[-0.838363864568,-0.78743988179] w2_p33_p34_x_8[0.644969481483,0.687527395577] w2_p33_p34_y_8[-0.0514525360937,0.0112536564003] w2_p33_p34_z_8[-0.764293293821,-0.725078982312] cos_p33_p34_8[0.981570928025,1.000001] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.975314743089,-0.969285949327] uni_v_palm_p42_z_9[-0.245939770498,-0.221089256612] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.977040671753,-0.950684096252] w2_palm_p42_y_9[-0.0750860412692,-0.0479525022221] w2_palm_p42_z_9[0.207990867301,0.302830448793] cos_0_palm_p42_9[0.969285949327,0.975314743089] cos_1_palm_p42_9[0.950684096252,0.977040671753] w1_p42_p43_x_10[0.842134003334,0.893337998595] w1_p42_p43_y_10[-0.130744730234,-0.104848050925] w1_p42_p43_z_10[0.439382504544,0.523522369453] w2_p42_p43_x_10[0.260256545412,0.309076758573] w2_p42_p43_y_10[-0.234734085768,-0.211225165882] w2_p42_p43_z_10[0.921803852025,0.941240962436] cos_p42_p43_10[0.707105781187,0.775416926296] w1_p43_p44_x_11[-0.498985135793,-0.453676654168] w1_p43_p44_y_11[-0.219195769719,-0.192131373634] w1_p43_p44_z_11[0.84090152604,0.869057266444] w2_p43_p44_x_11[0.239730728609,0.291986452784] w2_p43_p44_y_11[-0.238699595707,-0.211643743568] w2_p43_p44_z_11[0.927753086984,0.945726105755] cos_p43_p44_11[0.707105781187,0.757033008455] }
   2 (err:1.80334 tm:60):{ 190  p12_u_x[0.36531087544,0.438959068855] p12_u_y[-0.012398244227,0.0632496198941] p12_u_z[0.896805912724,0.930907874077] p12_v_x[-0,0] p12_v_y[-1,-0.997640771014] p12_v_z[-0.0132867944055,0.0682836606842] p13_u_x[0.981197566006,0.994031948981] p13_u_y[-0.00842746136169,0.00256884136279] p13_u_z[-0.192878491559,-0.109089341525] p13_v_x[-0,0] p13_v_y[-1,-0.997640771014] p13_v_z[-0.0132867944055,0.0682836606842] p14_u_x[0.628947864138,0.658290512591] p14_u_y[-0.0521678449933,0.00998691657882] p14_u_z[-0.777486587017,-0.751735403539] p14_v_x[-0,0] p14_v_y[-1,-0.997640771014] p14_v_z[-0.0132867944055,0.0682836606842] p22_u_x[0.189996644733,0.261712292649] p22_u_y[-0.0179560600881,0.0519322206728] p22_u_z[0.965029616973,0.981784739655] p22_v_x[-0,0] p22_v_y[-1,-0.998560334007] p22_v_z[-0.018233125057,0.0534977928246] p23_u_x[0.968323951856,0.982450694074] p23_u_y[-0.00456209742476,0.0115071962271] p23_u_z[0.186696669028,0.249442116096] p23_v_x[-0,0] p23_v_y[-1,-0.998560334007] p23_v_z[-0.018233125057,0.0534977928246] p24_u_x[0.797168401276,0.819662279875] p24_u_y[-0.0320755229495,0.0110432955725] p24_u_z[-0.603815035794,-0.572558291184] p24_v_x[-0,0] p24_v_y[-1,-0.998560334007] p24_v_z[-0.018233125057,0.0534977928246] p32_u_x[0.344271432658,0.413464115219] p32_u_y[-0.0130806444439,0.0639556996852] p32_u_z[0.91045757173,0.938199641941] p32_v_x[-0,0] p32_v_y[-1,-0.997643197039] p32_v_z[-0.013909117857,0.0683162565077] p33_u_x[0.978465116031,0.993248530782] p33_u_y[-0.0108707923492,0.00287377933805] p33_u_z[-0.206119717588,-0.116201967465] p33_v_x[-0,0] p33_v_y[-1,-0.997643197039] p33_v_z[-0.013909117857,0.0683162565077] p34_u_x[0.628947811992,0.658302525424] p34_u_y[-0.0520669473218,0.0108399385891] p34_u_z[-0.777486655567,-0.751724736411] p34_v_x[-0,0] p34_v_y[-1,-0.997643197039] p34_v_z[-0.013909117857,0.0683162565077] p42_u_x[0.950876110585,0.966616691326] p42_u_y[0.0570543912555,0.075372338354] p42_u_z[-0.302035898011,-0.249951935691] p42_v_x[-0,0] p42_v_y[0.969656709879,0.975023022204] p42_v_z[0.222190871677,0.244481733293] p43_u_x[0.285121365354,0.309076758573] p43_u_y[-0.232863016444,-0.211591279965] p43_u_z[0.922170272514,0.934537680021] p43_v_x[-0,0] p43_v_y[0.969656709879,0.975023022204] p43_v_z[0.222190871677,0.244481733293] p44_u_x[0.275596636359,0.309713057023] p44_u_y[-0.234612054079,-0.211492312272] p44_u_z[0.922806292939,0.937028138049] p44_v_x[-0,0] p44_v_y[0.969656709879,0.975023022204] p44_v_z[0.222190871677,0.244481733293] object_u_x[0.994414821167,0.997660682177] object_u_y[0.00403727660049,0.0260354038638] object_u_z[-0.104487123554,-0.0681784500771] object_v_x[-0.0294716682977,-0.00194607758044] object_v_y[0.998976332074,0.999998184622] object_v_z[-0.0346126784409,0.025494947311] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-1,-0.997640771014] uni_v_palm_p12_z_0[-0.0132867944055,0.0682836606842] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.915751013308,0.947477154354] w2_palm_p12_y_0[-0.0068762191845,0.0264794729001] w2_palm_p12_z_0[0.324405024822,0.399949319712] cos_0_palm_p12_0[0.997640771014,1.00000000001] cos_1_palm_p12_0[0.915751013308,0.947477154354] w1_p12_p13_x_1[0.915751013308,0.947477154354] w1_p12_p13_y_1[-0.0068762191845,0.0264794729001] w1_p12_p13_z_1[0.324405024822,0.399949319712] w2_p12_p13_x_1[0.981197566006,0.994031948981] w2_p12_p13_y_1[-0.00842746136169,0.00256884136279] w2_p12_p13_z_1[-0.192878491559,-0.109089341525] cos_p12_p13_1[0.825435576623,0.906485915915] w1_p13_p14_x_2[0.557209877901,0.625990032338] w1_p13_p14_y_2[-0.0532515424171,0.0111555566437] w1_p13_p14_z_2[-0.830876552088,-0.778342520025] w2_p13_p14_x_2[0.628947864138,0.658290512591] w2_p13_p14_y_2[-0.0521678449933,0.00998691657882] w2_p13_p14_z_2[-0.777486587017,-0.751735403539] cos_p13_p14_2[0.990767571471,1.000001] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-1,-0.998560334007] uni_v_palm_p22_z_3[-0.018233125057,0.0534977928246] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.82678229054,0.868584079818] w2_palm_p22_y_3[-0.011191292383,0.029591733893] w2_palm_p22_z_3[0.497605045097,0.560072693334] cos_0_palm_p22_3[0.998560334007,1.00000000001] cos_1_palm_p22_3[0.82678229054,0.868584079818] w1_p22_p23_x_4[0.82678229054,0.868584079818] w1_p22_p23_y_4[-0.011191292383,0.029591733893] w1_p22_p23_z_4[0.497605045097,0.560072693334] w2_p22_p23_x_4[0.968323951856,0.982450694074] w2_p22_p23_y_4[-0.00456209742476,0.0115071962271] w2_p22_p23_z_4[0.186696669028,0.249442116096] cos_p22_p23_4[0.917074731552,0.968056499551] w1_p23_p24_x_5[0.826390428607,0.861798217465] w1_p23_p24_y_5[-0.0293878151096,0.0109830411259] w1_p23_p24_z_5[-0.562426091571,-0.507444316821] w2_p23_p24_x_5[0.797168401276,0.819662279875] w2_p23_p24_y_5[-0.0320755229495,0.0110432955725] w2_p23_p24_z_5[-0.603815035794,-0.572558291184] cos_p23_p24_5[0.992326281821,1.000001] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-1,-0.997643197039] uni_v_palm_p32_z_6[-0.013909117857,0.0683162565077] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.905027786408,0.937421932419] w2_palm_p32_y_6[-0.00742733011809,0.0282062739345] w2_palm_p32_z_6[0.351597182451,0.420369561775] cos_0_palm_p32_6[0.997643197039,1.00000000001] cos_1_palm_p32_6[0.905027786408,0.937421932419] w1_p32_p33_x_7[0.905027786408,0.937421932419] w1_p32_p33_y_7[-0.00742733011809,0.0282062739345] w1_p32_p33_z_7[0.351597182451,0.420369561775] w2_p32_p33_x_7[0.978465116031,0.993248530782] w2_p32_p33_y_7[-0.0108707923492,0.00287377933805] w2_p32_p33_z_7[-0.206119717588,-0.116201967465] cos_p32_p33_7[0.799234852387,0.890258890284] w1_p33_p34_x_8[0.545767539581,0.620294047802] w1_p33_p34_y_8[-0.0550374902037,0.0118008981514] w1_p33_p34_z_8[-0.838431812283,-0.784371174395] w2_p33_p34_x_8[0.628947811992,0.658302525424] w2_p33_p34_y_8[-0.0520669473218,0.0108399385891] w2_p33_p34_z_8[-0.777486655567,-0.751724736411] cos_p33_p34_8[0.98807221348,1.000001] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.975023022204,-0.969656709879] uni_v_palm_p42_z_9[-0.244481733293,-0.222190871677] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.966616691326,-0.950876110585] w2_palm_p42_y_9[-0.075372338354,-0.0570543912555] w2_palm_p42_z_9[0.249951935691,0.302035898011] cos_0_palm_p42_9[0.969656709879,0.975023022204] cos_1_palm_p42_9[0.950876110585,0.966616691326] w1_p42_p43_x_10[0.8648671886,0.891833362664] w1_p42_p43_y_10[-0.119705284731,-0.101533198527] w1_p42_p43_z_10[0.439820818751,0.488930602269] w2_p42_p43_x_10[0.285121365354,0.309076758573] w2_p42_p43_y_10[-0.232863016444,-0.211591279965] w2_p42_p43_z_10[0.922170272514,0.934537680021] cos_p42_p43_10[0.707105781187,0.745412884323] w1_p43_p44_x_11[-0.476222781426,-0.453740826567] w1_p43_p44_y_11[-0.217845532593,-0.195508641977] w1_p43_p44_z_11[0.85457059955,0.868801186941] w2_p43_p44_x_11[0.275596636359,0.309713057023] w2_p43_p44_y_11[-0.234612054079,-0.211492312272] w2_p43_p44_z_11[0.922806292939,0.937028138049] cos_p43_p44_11[0.707105781187,0.731873987454] }
   3 (err:3.35325 tm:60):{ 190  p12_u_x[0.17300337553,0.256225379707] p12_u_y[-0.0138116329201,0.0517014351629] p12_u_z[0.965244423219,0.984956529836] p12_v_x[-0,0] p12_v_y[-1,-0.998597722673] p12_v_z[-0.0140028507806,0.0527851529687] p13_u_x[0.995196095516,0.999682154072] p13_u_y[-0.00370718888349,0.00137557624581] p13_u_z[-0.0978637336751,-0.0252109273917] p13_v_x[-0,0] p13_v_y[-1,-0.998597722673] p13_v_z[-0.0140028507806,0.0527851529687] p14_u_x[0.678175978869,0.700029752685] p14_u_y[-0.038742167427,0.00998691657882] p14_u_z[-0.734975154809,-0.71329844506] p14_v_x[-0,0] p14_v_y[-1,-0.998597722673] p14_v_z[-0.0140028507806,0.0527851529687] p22_u_x[0.0121470066236,0.110707295192] p22_u_y[-0.0132145463587,0.0477596433679] p22_u_z[0.993302899453,0.999928334836] p22_v_x[-0,0] p22_v_y[-1,-0.998848461038] p22_v_z[-0.0131446202945,0.0478619172747] p23_u_x[0.921060381859,0.941015162347] p23_u_y[-0.0051460622434,0.0172662825614] p23_u_z[0.338364395673,0.389215077919] p23_v_x[-0,0] p23_v_y[-1,-0.998848461038] p23_v_z[-0.0131446202945,0.0478619172747] p24_u_x[0.834834467639,0.851159384572] p24_u_y[-0.0262865887415,0.00726869392605] p24_u_z[-0.550614682967,-0.524623358174] p24_v_x[-0,0] p24_v_y[-1,-0.998848461038] p24_v_z[-0.0131446202945,0.0478619172747] p32_u_x[0.183780694031,0.270663009753] p32_u_y[-0.0142314715503,0.0516755527091] p32_u_z[0.962601285952,0.983007567659] p32_v_x[-0,0] p32_v_y[-1,-0.998599211365] p32_v_z[-0.0144570935141,0.052801532112] p33_u_x[0.992445080951,0.998627406287] p33_u_y[-0.005897292552,0.00177407988313] p33_u_z[-0.122540661798,-0.0523765543249] p33_v_x[-0,0] p33_v_y[-1,-0.998599211365] p33_v_z[-0.0144570935141,0.052801532112] p34_u_x[0.678167767976,0.700030665201] p34_u_y[-0.0387636811516,0.0106407077745] p34_u_z[-0.734983464505,-0.713298796996] p34_v_x[-0,0] p34_v_y[-1,-0.998599211365] p34_v_z[-0.0144570935141,0.052801532112] p42_u_x[0.984570629956,0.993755428906] p42_u_y[0.0241528600009,0.0397997837185] p42_u_z[-0.170632456023,-0.108994340796] p42_v_x[-0,0] p42_v_y[0.973004500299,0.976698666928] p42_v_z[0.214751040333,0.230787445398] p43_u_x[0.216084825367,0.309076758573] p43_u_y[-0.223364593705,-0.207301112612] p43_u_z[0.927355312103,0.954167196382] p43_v_x[-0,0] p43_v_y[0.973004500299,0.976698666928] p43_v_z[0.214751040333,0.230787445398] p44_u_x[0.217587050945,0.246489976498] p44_u_y[-0.225099156795,-0.208110585085] p44_u_z[0.943986957519,0.953330339467] p44_v_x[-0,0] p44_v_y[0.973004500299,0.976698666928] p44_v_z[0.214751040333,0.230787445398] object_u_x[0.999161557668,0.999941138582] object_u_y[-0.00873822246836,0.0100660264999] object_u_z[-0.0398933589802,-0.0108498572098] object_v_x[-0.0115065401266,0.00920048104337] object_v_y[0.999078242282,1] object_v_z[-0.041440609032,0.011284843891] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-1,-0.998597722673] uni_v_palm_p12_z_0[-0.0140028507806,0.0527851529687] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.81809559537,0.866125303719] w2_palm_p12_y_0[-0.00926654387854,0.0289661789108] w2_palm_p12_z_0[0.501477755672,0.574146395076] cos_0_palm_p12_0[0.998597722673,1.00000000001] cos_1_palm_p12_0[0.81809559537,0.866125303719] w1_p12_p13_x_1[0.81809559537,0.866125303719] w1_p12_p13_y_1[-0.00926654387854,0.0289661789108] w1_p12_p13_z_1[0.501477755672,0.574146395076] w2_p12_p13_x_1[0.995196095516,0.999682154072] w2_p12_p13_y_1[-0.00370718888349,0.00137557624581] w2_p12_p13_z_1[-0.0978637336751,-0.0252109273917] cos_p12_p13_1[0.759423588079,0.853248676304] w1_p13_p14_x_2[0.634563075825,0.689131876147] w1_p13_p14_y_2[-0.0398028748036,0.0108710428794] w1_p13_p14_z_2[-0.773380628084,-0.723713236037] w2_p13_p14_x_2[0.678175978869,0.700029752685] w2_p13_p14_y_2[-0.038742167427,0.00998691657882] w2_p13_p14_z_2[-0.734975154809,-0.71329844506] cos_p13_p14_2[0.995581321971,1.000001] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-1,-0.998848461038] uni_v_palm_p22_z_3[-0.0131446202945,0.0478619172747] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.714999343866,0.782118573008] w2_palm_p22_y_3[-0.0103529835962,0.0324247851102] w2_palm_p22_z_3[0.624093488678,0.698459379153] cos_0_palm_p22_3[0.998848461038,1.00000000001] cos_1_palm_p22_3[0.714999343866,0.782118573008] w1_p22_p23_x_4[0.714999343866,0.782118573008] w1_p22_p23_y_4[-0.0103529835962,0.0324247851102] w1_p22_p23_z_4[0.624093488678,0.698459379153] w2_p22_p23_x_4[0.921060381859,0.941015162347] w2_p22_p23_y_4[-0.0051460622434,0.0172662825614] w2_p22_p23_z_4[0.338364395673,0.389215077919] cos_p22_p23_4[0.908910855401,0.963030851195] w1_p23_p24_x_5[0.904260196959,0.927090580787] w1_p23_p24_y_5[-0.0203586694585,0.00579157747372] w1_p23_p24_z_5[-0.426138443829,-0.376062311951] w2_p23_p24_x_5[0.834834467639,0.851159384572] w2_p23_p24_y_5[-0.0262865887415,0.00726869392605] w2_p23_p24_z_5[-0.550614682967,-0.524623358174] cos_p23_p24_5[0.981679175975,0.995190543831] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-1,-0.998599211365] uni_v_palm_p32_z_6[-0.0144570935141,0.052801532112] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.823418764753,0.873310776864] w2_palm_p32_y_6[-0.0094418275062,0.0288864642334] w2_palm_p32_z_6[0.489410045599,0.565190217737] cos_0_palm_p32_6[0.998599211365,1.00000000001] cos_1_palm_p32_6[0.823418764753,0.873310776864] w1_p32_p33_x_7[0.823418764753,0.873310776864] w1_p32_p33_y_7[-0.0094418275062,0.0288864642334] w1_p32_p33_z_7[0.489410045599,0.565190217737] w2_p32_p33_x_7[0.992445080951,0.998627406287] w2_p32_p33_y_7[-0.005897292552,0.00177407988313] w2_p32_p33_z_7[-0.122540661798,-0.0523765543249] cos_p32_p33_7[0.747951291578,0.84654342616] w1_p33_p34_x_8[0.614942353854,0.669209361608] w1_p33_p34_y_8[-0.0408808182684,0.0114631411601] w1_p33_p34_z_8[-0.788590134612,-0.74267930956] w2_p33_p34_x_8[0.678167767976,0.700030665201] w2_p33_p34_y_8[-0.0387636811516,0.0106407077745] w2_p33_p34_z_8[-0.734983464505,-0.713298796996] cos_p33_p34_8[0.992295493172,1.000001] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.976698666928,-0.973004500299] uni_v_palm_p42_z_9[-0.230787445398,-0.214751040333] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.993755428906,-0.984570629956] w2_palm_p42_y_9[-0.0397997837185,-0.0241528600009] w2_palm_p42_z_9[0.108994340796,0.170632456023] cos_0_palm_p42_9[0.973004500299,0.976698666928] cos_1_palm_p42_9[0.984570629956,0.993755428906] w1_p42_p43_x_10[0.781614867182,0.820246165126] w1_p42_p43_y_10[-0.138763629029,-0.123792402208] w1_p42_p43_z_10[0.55808886274,0.608163252243] w2_p42_p43_x_10[0.216084825367,0.309076758573] w2_p42_p43_y_10[-0.223364593705,-0.207301112612] w2_p42_p43_z_10[0.927355312103,0.954167196382] cos_p42_p43_10[0.751318509941,0.834077873054] w1_p43_p44_x_11[-0.538471142569,-0.453827607989] w1_p43_p44_y_11[-0.204191357503,-0.181206425718] w1_p43_p44_z_11[0.822641893936,0.870482966614] w2_p43_p44_x_11[0.217587050945,0.246489976498] w2_p43_p44_y_11[-0.225099156795,-0.208110585085] w2_p43_p44_z_11[0.943986957519,0.953330339467] cos_p43_p44_11[0.707105781187,0.772131645671] }
   4 (err:2.60127 tm:60):{ 190  p12_u_x[0.256225379701,0.330382802886] p12_u_y[-0.0135593663089,0.0540761863372] p12_u_z[0.942726268888,0.966617067315] p12_v_x[-0,0] p12_v_y[-1,-0.998418508463] p12_v_z[-0.0140054116663,0.0561783265799] p13_u_x[0.995463936699,0.999682154072] p13_u_y[-0.00385220906837,0.00133629345634] p13_u_z[-0.095166810619,-0.0252109273917] p13_v_x[-0,0] p13_v_y[-1,-0.998418508463] p13_v_z[-0.0140054116663,0.0561783265799] p14_u_x[0.662266097553,0.700182112667] p14_u_y[-0.0419452452947,0.00998691657882] p14_u_z[-0.749288945118,-0.713115024779] p14_v_x[-0,0] p14_v_y[-1,-0.998418508463] p14_v_z[-0.0140054116663,0.0561783265799] p22_u_x[0.0845586945913,0.164427061044] p22_u_y[-0.0149329556424,0.048471671043] p22_u_z[0.985234765238,0.99594172752] p22_v_x[-0,0] p22_v_y[-1,-0.998790860879] p22_v_z[-0.0149538607568,0.0490842130495] p23_u_x[0.924084082216,0.941015162347] p23_u_y[-0.00572869190485,0.0176751802514] p23_u_z[0.338364395673,0.381974809008] p23_v_x[-0,0] p23_v_y[-1,-0.998790860879] p23_v_z[-0.0149538607568,0.0490842130495] p24_u_x[0.82284867736,0.851370184602] p24_u_y[-0.0277412838226,0.00851393721939] p24_u_z[-0.568286362987,-0.524461220561] p24_v_x[-0,0] p24_v_y[-1,-0.998790860879] p24_v_z[-0.0149538607568,0.0490842130495] p32_u_x[0.239593958004,0.323470719958] p32_u_y[-0.0143922445036,0.0543333630668] p32_u_z[0.946156125406,0.970380050955] p32_v_x[-0,0] p32_v_y[-1,-0.998417649248] p32_v_z[-0.0148080271796,0.0561935427991] p33_u_x[0.992441870115,0.998627406287] p33_u_y[-0.00650456005278,0.00181746849905] p33_u_z[-0.122540661798,-0.0523765543249] p33_v_x[-0,0] p33_v_y[-1,-0.998417649248] p33_v_z[-0.0148080271796,0.0561935427991] p34_u_x[0.662266075901,0.700186625274] p34_u_y[-0.0419782721762,0.0111131199902] p34_u_z[-0.749288961665,-0.713104832972] p34_v_x[-0,0] p34_v_y[-1,-0.998417649248] p34_v_z[-0.0148080271796,0.0561935427991] p42_u_x[0.98018538671,0.993760069505] p42_u_y[0.0240281028451,0.0453328067065] p42_u_z[-0.192958562143,-0.108935868449] p42_v_x[-0,0] p42_v_y[0.973027309565,0.976810932284] p42_v_z[0.214172292136,0.230694005423] p43_u_x[0.24090339132,0.309076758573] p43_u_y[-0.222461723424,-0.20602703364] p43_u_z[0.925389492121,0.947845541136] p43_v_x[-0,0] p43_v_y[0.973027309565,0.976810932284] p43_v_z[0.214172292136,0.230694005423] p44_u_x[0.21762988595,0.269105541457] p44_u_y[-0.225030505804,-0.206564354838] p44_u_z[0.937641264985,0.952815109531] p44_v_x[-0,0] p44_v_y[0.973027309565,0.976810932284] p44_v_z[0.214172292136,0.230694005423] object_u_x[0.998058816325,0.999941138582] object_u_y[-0.00834672234529,0.0149750008707] object_u_z[-0.0613313617982,-0.0108498572098] object_v_x[-0.0171513287505,0.00931295800039] object_v_y[0.999054326489,1] object_v_z[-0.0407776393106,0.01561003049] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-1,-0.998418508463] uni_v_palm_p12_z_0[-0.0140054116663,0.0561783265799] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.862983055538,0.9024225281] w2_palm_p12_y_0[-0.00811841171936,0.0274156769588] w2_palm_p12_z_0[0.433419642413,0.502610011342] cos_0_palm_p12_0[0.998418508463,1.00000000001] cos_1_palm_p12_0[0.862983055538,0.9024225281] w1_p12_p13_x_1[0.862983055538,0.9024225281] w1_p12_p13_y_1[-0.00811841171936,0.0274156769588] w1_p12_p13_z_1[0.433419642413,0.502610011342] w2_p12_p13_x_1[0.995463936699,0.999682154072] w2_p12_p13_y_1[-0.00385220906837,0.00133629345634] w2_p12_p13_z_1[-0.095166810619,-0.0252109273917] cos_p12_p13_1[0.813056577253,0.891241274511] w1_p13_p14_x_2[0.636673409516,0.689136659592] w1_p13_p14_y_2[-0.0423309338991,0.0108450759967] w1_p13_p14_z_2[-0.771626838855,-0.723586132784] w2_p13_p14_x_2[0.662266097553,0.700182112667] w2_p13_p14_y_2[-0.0419452452947,0.00998691657882] w2_p13_p14_z_2[-0.749288945118,-0.713115024779] cos_p13_p14_2[0.996073393223,1.000001] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-1,-0.998790860879] uni_v_palm_p22_z_3[-0.0149538607568,0.0490842130495] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.762920741111,0.815050675151] w2_palm_p22_y_3[-0.0106478902051,0.0311026615427] w2_palm_p22_z_3[0.580455677392,0.644395851261] cos_0_palm_p22_3[0.998790860879,1.00000000001] cos_1_palm_p22_3[0.762920741111,0.815050675151] w1_p22_p23_x_4[0.762920741111,0.815050675151] w1_p22_p23_y_4[-0.0106478902051,0.0311026615427] w1_p22_p23_z_4[0.580455677392,0.644395851261] w2_p22_p23_x_4[0.924084082216,0.941015162347] w2_p22_p23_y_4[-0.00572869190485,0.0176751802514] w2_p22_p23_z_4[0.338364395673,0.381974809008] cos_p22_p23_4[0.93574819823,0.975344420206] w1_p23_p24_x_5[0.904224174123,0.924049301672] w1_p23_p24_y_5[-0.0209146790197,0.00641678270363] w1_p23_p24_z_5[-0.426138443829,-0.383286530969] w2_p23_p24_x_5[0.82284867736,0.851370184602] w2_p23_p24_y_5[-0.0277412838226,0.00851393721939] w2_p23_p24_z_5[-0.568286362987,-0.524461220561] cos_p23_p24_5[0.978970419179,0.995728268385] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-1,-0.998417649248] uni_v_palm_p32_z_6[-0.0148080271796,0.0561935427991] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.85418652325,0.899069075139] w2_palm_p32_y_6[-0.00900476294466,0.0283064499021] w2_palm_p32_z_6[0.440570091105,0.516818307378] cos_0_palm_p32_6[0.998417649248,1.00000000001] cos_1_palm_p32_6[0.85418652325,0.899069075139] w1_p32_p33_x_7[0.85418652325,0.899069075139] w1_p32_p33_y_7[-0.00900476294466,0.0283064499021] w1_p32_p33_z_7[0.440570091105,0.516818307378] w2_p32_p33_x_7[0.992441870115,0.998627406287] w2_p32_p33_y_7[-0.00650456005278,0.00181746849905] w2_p32_p33_z_7[-0.122540661798,-0.0523765543249] cos_p32_p33_7[0.784368572706,0.874819801271] w1_p33_p34_x_8[0.614913037233,0.669223832896] w1_p33_p34_y_8[-0.0436250776563,0.0117416285031] w1_p33_p34_z_8[-0.788400625766,-0.742579045247] w2_p33_p34_x_8[0.662266075901,0.700186625274] w2_p33_p34_y_8[-0.0419782721762,0.0111131199902] w2_p33_p34_z_8[-0.749288961665,-0.713104832972] cos_p33_p34_8[0.992361219417,1.000001] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.976810932284,-0.973027309565] uni_v_palm_p42_z_9[-0.230694005423,-0.214172292136] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.993760069505,-0.98018538671] w2_palm_p42_y_9[-0.0453328067065,-0.0240281028451] w2_palm_p42_z_9[0.108935868449,0.192958562143] cos_0_palm_p42_9[0.973027309565,0.976810932284] cos_1_palm_p42_9[0.98018538671,0.993760069505] w1_p42_p43_x_10[0.78156787911,0.833815508391] w1_p42_p43_y_10[-0.139220311989,-0.119103330783] w1_p42_p43_z_10[0.538480956821,0.608163252243] w2_p42_p43_x_10[0.24090339132,0.309076758573] w2_p42_p43_y_10[-0.222461723424,-0.20602703364] w2_p42_p43_z_10[0.925389492121,0.947845541136] cos_p42_p43_10[0.753486915076,0.837484568902] w1_p43_p44_x_11[-0.516411322242,-0.453809200931] w1_p43_p44_y_11[-0.205524522185,-0.18355710906] w1_p43_p44_z_11[0.834009675788,0.870350108445] w2_p43_p44_x_11[0.21762988595,0.269105541457] w2_p43_p44_y_11[-0.225030505804,-0.206564354838] w2_p43_p44_z_11[0.937641264985,0.952815109531] cos_p43_p44_11[0.707105781187,0.771747085767] }
   5 (err:2.89912 tm:60):{ 190  p12_u_x[0.271938644541,0.349068588749] p12_u_y[0.00414879319132,0.0830866970647] p12_u_z[0.933888726949,0.96230686529] p12_v_x[-0,0] p12_v_y[-0.999991474112,-0.996169113824] p12_v_z[0.00431982005619,0.0866730738315] p13_u_x[0.99433021007,0.999682148901] p13_u_y[-0.0062099996661,-0.000101681470726] p13_u_z[-0.106187517418,-0.0252109273917] p13_v_x[-0,0] p13_v_y[-0.999991474112,-0.996169113824] p13_v_z[0.00431982005619,0.0866730738315] p14_u_x[0.658583661806,0.700909399735] p14_u_y[-0.0636017672171,-0.00286550711845] p14_u_z[-0.752581498255,-0.710810679028] p14_v_x[-0,0] p14_v_y[-0.999991474112,-0.996169113824] p14_v_z[0.00431982005619,0.0866730738315] p22_u_x[0.079625672499,0.164427061044] p22_u_y[0.00494627662991,0.077398666209] p22_u_z[0.98380604073,0.996530231398] p22_v_x[-0,0] p22_v_y[-0.999987691074,-0.996914277296] p22_v_z[0.00513221248464,0.0781287643358] p23_u_x[0.938626170583,0.955805577037] p23_u_y[0.00145871546111,0.0230409616714] p23_u_z[0.293995869155,0.344441562606] p23_v_x[-0,0] p23_v_y[-0.999987691074,-0.996914277296] p23_v_z[0.00513221248464,0.0781287643358] p24_u_x[0.820224841459,0.851883934519] p24_u_y[-0.0428578721054,-0.00259284281623] p24_u_z[-0.57212987701,-0.522801891332] p24_v_x[-0,0] p24_v_y[-0.999987691074,-0.996914277296] p24_v_z[0.00513221248464,0.0781287643358] p32_u_x[0.245979909559,0.327931529564] p32_u_y[0.00394188043167,0.0839595381795] p32_u_z[0.943222525625,0.967522569346] p32_v_x[-0,0] p32_v_y[-0.999991474158,-0.99616931644] p32_v_z[0.00433278610788,0.0867390819679] p33_u_x[0.981808087926,0.992463370082] p33_u_y[-0.0137031382477,-0.000495258342111] p33_u_z[-0.189367892009,-0.122540661795] p33_v_x[-0,0] p33_v_y[-0.999991474158,-0.99616931644] p33_v_z[0.00433278610788,0.0867390819679] p34_u_x[0.658573898691,0.700910929772] p34_u_y[-0.0618225974722,-0.00287223153929] p34_u_z[-0.75259065735,-0.710981996885] p34_v_x[-0,0] p34_v_y[-0.999991474158,-0.99616931644] p34_v_z[0.00433278610788,0.0867390819679] p42_u_x[0.972451765581,0.990241168035] p42_u_y[0.0315712199014,0.055458483836] p42_u_z[-0.226872064273,-0.13596535112] p42_v_x[-0,0] p42_v_y[0.969636870803,0.974921518249] p42_v_z[0.222694214957,0.244553665542] p43_u_x[0.245753940595,0.309076758573] p43_u_y[-0.232998353777,-0.214708868752] p43_u_z[0.922135962752,0.944786983792] p43_v_x[-0,0] p43_v_y[0.969636870803,0.974921518249] p43_v_z[0.222694214957,0.244553665542] p44_u_x[0.220957586739,0.275427435671] p44_u_y[-0.238427925975,-0.215014752077] p44_u_z[0.933850192169,0.949488338933] p44_v_x[-0,0] p44_v_y[0.969636870803,0.974921518249] p44_v_z[0.222694214957,0.244553665542] object_u_x[0.99763376232,0.999941138582] object_u_y[-0.00158669229894,0.0209050742134] object_u_z[-0.0662164607676,-0.0108498572098] object_v_x[-0.0244916823969,0.00148807878587] object_v_y[0.997450157004,0.999997337629] object_v_z[-0.0684244005005,-0.00245828118553] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-0.999991474112,-0.996169113824] uni_v_palm_p12_z_0[0.00431982005619,0.0866730738315] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.870300365862,0.911284391562] w2_palm_p12_y_0[0.00206260077396,0.042132899637] w2_palm_p12_z_0[0.414161624462,0.488571340564] cos_0_palm_p12_0[0.996169113824,0.999991474112] cos_1_palm_p12_0[0.870300365862,0.911284391562] w1_p12_p13_x_1[0.870300365862,0.911284391562] w1_p12_p13_y_1[0.00206260077396,0.042132899637] w1_p12_p13_z_1[0.414161624462,0.488571340564] w2_p12_p13_x_1[0.99433021007,0.999682148901] w2_p12_p13_y_1[-0.0062099996661,-0.000101681470726] w2_p12_p13_z_1[-0.106187517418,-0.0252109273917] cos_p12_p13_1[0.814712138733,0.900206379808] w1_p13_p14_x_2[0.627811521978,0.689124550386] w1_p13_p14_y_2[-0.0651842383964,-0.00321114787382] w1_p13_p14_z_2[-0.778781492637,-0.721988826918] w2_p13_p14_x_2[0.658583661806,0.700909399735] w2_p13_p14_y_2[-0.0636017672171,-0.00286550711845] w2_p13_p14_z_2[-0.752581498255,-0.710810679028] cos_p13_p14_2[0.994209629278,1.000001] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-0.999987691074,-0.996914277296] uni_v_palm_p22_z_3[0.00513221248464,0.0781287643358] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.759255145279,0.815369824549] w2_palm_p22_y_3[0.00225055353731,0.0502887243898] w2_palm_p22_z_3[0.579555149619,0.647729968425] cos_0_palm_p22_3[0.996914277296,0.999987691074] cos_1_palm_p22_3[0.759255145279,0.815369824549] w1_p22_p23_x_4[0.759255145279,0.815369824549] w1_p22_p23_y_4[0.00225055353731,0.0502887243898] w1_p22_p23_z_4[0.579555149619,0.647729968425] w2_p22_p23_x_4[0.938626170583,0.955805577037] w2_p22_p23_y_4[0.00145871546111,0.0230409616714] w2_p22_p23_z_4[0.293995869155,0.344441562606] cos_p22_p23_4[0.916207104679,0.965192653985] w1_p23_p24_x_5[0.883333912826,0.908073177756] w1_p23_p24_y_5[-0.0365608917484,-0.002397469012] w1_p23_p24_z_5[-0.467961813355,-0.4194521355] w2_p23_p24_x_5[0.820224841459,0.851883934519] w2_p23_p24_y_5[-0.0428578721054,-0.00259284281623] w2_p23_p24_z_5[-0.57212987701,-0.522801891332] cos_p23_p24_5[0.985230309856,1.000001] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-0.999991474158,-0.99616931644] uni_v_palm_p32_z_6[0.00433278610788,0.0867390819679] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.856831101501,0.901702442472] w2_palm_p32_y_6[0.00113478259635,0.0440054954564] w2_palm_p32_z_6[0.435930201658,0.51073318093] cos_0_palm_p32_6[0.99616931644,0.999991474158] cos_1_palm_p32_6[0.856831101501,0.901702442472] w1_p32_p33_x_7[0.856831101501,0.901702442472] w1_p32_p33_y_7[0.00113478259635,0.0440054954564] w1_p32_p33_z_7[0.435930201658,0.51073318093] w2_p32_p33_x_7[0.981808087926,0.992463370082] w2_p32_p33_y_7[-0.0137031382477,-0.000495258342111] w2_p32_p33_z_7[-0.189367892009,-0.122540661795] cos_p32_p33_7[0.744483990246,0.841498419951] w1_p33_p34_x_8[0.559806063076,0.615374887761] w1_p33_p34_y_8[-0.0702067389435,-0.00339008609246] w1_p33_p34_z_8[-0.826951363869,-0.786571719229] w2_p33_p34_x_8[0.658573898691,0.700910929772] w2_p33_p34_y_8[-0.0618225974722,-0.00287223153929] w2_p33_p34_z_8[-0.75259065735,-0.710981996885] cos_p33_p34_8[0.981347201239,1.000001] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.974921518249,-0.969636870803] uni_v_palm_p42_z_9[-0.244553665542,-0.222694214957] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.990241168035,-0.972451765581] w2_palm_p42_y_9[-0.055458483836,-0.0315712199014] w2_palm_p42_z_9[0.13596535112,0.226872064273] cos_0_palm_p42_9[0.969636870803,0.974921518249] cos_1_palm_p42_9[0.972451765581,0.990241168035] w1_p42_p43_x_10[0.798890187653,0.853104742548] w1_p42_p43_y_10[-0.141626328458,-0.116832388826] w1_p42_p43_z_10[0.508183473581,0.584936217032] w2_p42_p43_x_10[0.245753940595,0.309076758573] w2_p42_p43_y_10[-0.232998353777,-0.214708868752] w2_p42_p43_z_10[0.922135962752,0.944786983792] cos_p42_p43_10[0.732927861445,0.821589727174] w1_p43_p44_x_11[-0.512060920775,-0.45374442838] w1_p43_p44_y_11[-0.218022184239,-0.191479795505] w1_p43_p44_z_11[0.834401285838,0.868450521112] w2_p43_p44_x_11[0.220957586739,0.275427435671] w2_p43_p44_y_11[-0.238427925975,-0.215014752077] w2_p43_p44_z_11[0.933850192169,0.949488338933] cos_p43_p44_11[0.707105781187,0.76957761583] }
   6 (err:2.5735 tm:61):{ 190  p12_u_x[0.377959572481,0.448018742037] p12_u_y[-0.0123680481781,0.0573120098728] p12_u_z[0.892486054849,0.925822100403] p12_v_x[-0,0] p12_v_y[-1,-0.998056883231] p12_v_z[-0.013332900531,0.0620667754431] p13_u_x[0.995146285575,0.999682154072] p13_u_y[-0.00335477644859,0.00131752611181] p13_u_z[-0.0985108940085,-0.0252109273917] p13_v_x[-0,0] p13_v_y[-1,-0.998056883231] p13_v_z[-0.013332900531,0.0620667754431] p14_u_x[0.628992418542,0.661160785767] p14_u_y[-0.0474693482027,0.00998691657882] p14_u_z[-0.777440322257,-0.74911590472] p14_v_x[-0,0] p14_v_y[-1,-0.998056883231] p14_v_z[-0.013332900531,0.0620667754431] p22_u_x[0.210081084324,0.305436210156] p22_u_y[-0.0169902036106,0.0477355194842] p22_u_z[0.951529502265,0.977579854706] p22_v_x[-0,0] p22_v_y[-1,-0.998759988692] p22_v_z[-0.0173187888551,0.0497038516642] p23_u_x[0.928064117442,0.944391461983] p23_u_y[-0.00647036089074,0.0167170048785] p23_u_z[0.328823305986,0.372203389982] p23_v_x[-0,0] p23_v_y[-1,-0.998759988692] p23_v_z[-0.0173187888551,0.0497038516642] p24_u_x[0.797246092159,0.821989434641] p24_u_y[-0.0297225300668,0.0104921670648] p24_u_z[-0.603696776453,-0.569249639352] p24_v_x[-0,0] p24_v_y[-1,-0.998759988692] p24_v_z[-0.0173187888551,0.0497038516642] p32_u_x[0.343256843777,0.423543055882] p32_u_y[-0.0131840182525,0.0581343453] p32_u_z[0.905921596876,0.938774140255] p32_v_x[-0,0] p32_v_y[-1,-0.998058133096] p32_v_z[-0.0140164146572,0.0620945880298] p33_u_x[0.992708303216,0.998627406287] p33_u_y[-0.00544379713661,0.00169109333895] p33_u_z[-0.120415085656,-0.0523765543249] p33_v_x[-0,0] p33_v_y[-1,-0.998058133096] p33_v_z[-0.0140164146572,0.0620945880298] p34_u_x[0.628995125092,0.661250309143] p34_u_y[-0.0468765882246,0.0109182376058] p34_u_z[-0.777438177311,-0.749127443032] p34_v_x[-0,0] p34_v_y[-1,-0.998058133096] p34_v_z[-0.0140164146572,0.0620945880298] p42_u_x[0.967519614243,0.983162917355] p42_u_y[0.0397679560744,0.0579631376327] p42_u_z[-0.246678652492,-0.178444900266] p42_v_x[-0,0] p42_v_y[0.972974935174,0.9766125091] p42_v_z[0.215058476769,0.23091572102] p43_u_x[0.284138658533,0.309076758573] p43_u_y[-0.220510664383,-0.205591835073] p43_u_z[0.925323742177,0.935721190786] p43_v_x[-0,0] p43_v_y[0.972974935174,0.9766125091] p43_v_z[0.215058476769,0.23091572102] p44_u_x[0.27382447648,0.309611307241] p44_u_y[-0.22204228398,-0.205657393555] p44_u_z[0.925518164619,0.938321024017] p44_v_x[-0,0] p44_v_y[0.972974935174,0.9766125091] p44_v_z[0.215058476769,0.23091572102] object_u_x[0.994435651279,0.997868783691] object_u_y[0.00290489336453,0.0224653653405] object_u_z[-0.104637389988,-0.0643616853773] object_v_x[-0.0253019929534,-0.00102703268409] object_v_y[0.999102850094,0.999999500289] object_v_z[-0.0344892251171,0.022440153593] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-1,-0.998056883231] uni_v_palm_p12_z_0[-0.013332900531,0.0620667754431] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.92001388647,0.950490903658] w2_palm_p12_y_0[-0.00648374224484,0.0237298635284] w2_palm_p12_z_0[0.31478213243,0.387873916572] cos_0_palm_p12_0[0.998056883231,1.00000000001] cos_1_palm_p12_0[0.92001388647,0.950490903658] w1_p12_p13_x_1[0.92001388647,0.950490903658] w1_p12_p13_y_1[-0.00648374224484,0.0237298635284] w1_p12_p13_z_1[0.31478213243,0.387873916572] w2_p12_p13_x_1[0.995146285575,0.999682154072] w2_p12_p13_y_1[-0.00335477644859,0.00131752611181] w2_p12_p13_z_1[-0.0985108940085,-0.0252109273917] cos_p12_p13_1[0.879326463945,0.942273092231] w1_p13_p14_x_2[0.634166982779,0.689148223312] w1_p13_p14_y_2[-0.0450541282052,0.0103564194434] w1_p13_p14_z_2[-0.773804387007,-0.723332461497] w2_p13_p14_x_2[0.628992418542,0.661160785767] w2_p13_p14_y_2[-0.0474693482027,0.00998691657882] w2_p13_p14_z_2[-0.777440322257,-0.74911590472] cos_p13_p14_2[0.995171782305,1.000001] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-1,-0.998759988692] uni_v_palm_p22_z_3[-0.0173187888551,0.0497038516642] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.838324980879,0.890569008326] w2_palm_p22_y_3[-0.0104459664945,0.026398731933] w2_palm_p22_z_3[0.456886623845,0.542605643456] cos_0_palm_p22_3[0.998759988692,1.00000000001] cos_1_palm_p22_3[0.838324980879,0.890569008326] w1_p22_p23_x_4[0.838324980879,0.890569008326] w1_p22_p23_y_4[-0.0104459664945,0.026398731933] w1_p22_p23_z_4[0.456886623845,0.542605643456] w2_p22_p23_x_4[0.928064117442,0.944391461983] w2_p22_p23_y_4[-0.00647036089074,0.0167170048785] w2_p22_p23_z_4[0.328823305986,0.372203389982] cos_p22_p23_4[0.969839190624,0.998449685492] w1_p23_p24_x_5[0.899841903328,0.919935345796] w1_p23_p24_y_5[-0.021635072665,0.00753085392584] w1_p23_p24_z_5[-0.435272417414,-0.392984896761] w2_p23_p24_x_5[0.797246092159,0.821989434641] w2_p23_p24_y_5[-0.0297225300668,0.0104921670648] w2_p23_p24_z_5[-0.603696776453,-0.569249639352] cos_p23_p24_5[0.971130714192,0.98961449384] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-1,-0.998058133096] uni_v_palm_p32_z_6[-0.0140164146572,0.0620945880298] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.904905721547,0.941385830216] w2_palm_p32_y_6[-0.00751922575593,0.0257168933661] w2_palm_p32_z_6[0.341559207739,0.421228724761] cos_0_palm_p32_6[0.998058133096,1.00000000001] cos_1_palm_p32_6[0.904905721547,0.941385830216] w1_p32_p33_x_7[0.904905721547,0.941385830216] w1_p32_p33_y_7[-0.00751922575593,0.0257168933661] w1_p32_p33_z_7[0.341559207739,0.421228724761] w2_p32_p33_x_7[0.992708303216,0.998627406287] w2_p32_p33_y_7[-0.00544379713661,0.00169109333895] w2_p32_p33_z_7[-0.120415085656,-0.0523765543249] cos_p32_p33_7[0.847574749142,0.922252972705] w1_p33_p34_x_8[0.616634977095,0.669241641961] w1_p33_p34_y_8[-0.0472040924576,0.0110932815035] w1_p33_p34_z_8[-0.78683383898,-0.742393769664] w2_p33_p34_x_8[0.628995125092,0.661250309143] w2_p33_p34_y_8[-0.0468765882246,0.0109182376058] w2_p33_p34_z_8[-0.777438177311,-0.749127443032] cos_p33_p34_8[0.996575685894,1.000001] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.9766125091,-0.972974935174] uni_v_palm_p42_z_9[-0.23091572102,-0.215058476769] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.983162917355,-0.967519614243] w2_palm_p42_y_9[-0.0579631376327,-0.0397679560744] w2_palm_p42_z_9[0.178444900266,0.246678652492] cos_0_palm_p42_9[0.972974935174,0.9766125091] cos_1_palm_p42_9[0.967519614243,0.983162917355] w1_p42_p43_x_10[0.82447469722,0.863470870499] w1_p42_p43_y_10[-0.126214894913,-0.109243284333] w1_p42_p43_z_10[0.492225224916,0.551832457319] w2_p42_p43_x_10[0.284138658533,0.309076758573] w2_p42_p43_y_10[-0.220510664383,-0.205591835073] w2_p42_p43_z_10[0.925323742177,0.935721190786] cos_p42_p43_10[0.746570706704,0.793799871198] w1_p43_p44_x_11[-0.477112173794,-0.453836552383] w1_p43_p44_y_11[-0.205770297142,-0.189337369256] w1_p43_p44_z_11[0.855370014203,0.87004675004] w2_p43_p44_x_11[0.27382447648,0.309611307241] w2_p43_p44_y_11[-0.22204228398,-0.205657393555] w2_p43_p44_z_11[0.925518164619,0.938321024017] cos_p43_p44_11[0.707105781187,0.732930879884] }
   7 (err:2.06252 tm:61):{ 190  p12_u_x[0.308108505155,0.377959572488] p12_u_y[-0.0130095814359,0.0569859450085] p12_u_z[0.92408624654,0.951365147745] p12_v_x[-0,0] p12_v_y[-1,-0.998170415865] p12_v_z[-0.0136496092865,0.0604297101496] p13_u_x[0.994991567374,0.999682154072] p13_u_y[-0.00400465625809,0.00136861901513] p13_u_z[-0.100081912531,-0.0252109273917] p13_v_x[-0,0] p13_v_y[-1,-0.998170415865] p13_v_z[-0.0136496092865,0.0604297101496] p14_u_x[0.64522908147,0.681342684454] p14_u_y[-0.0460908983449,0.00998691657882] p14_u_z[-0.764008775234,-0.731691947881] p14_v_x[-0,0] p14_v_y[-1,-0.998170415865] p14_v_z[-0.0136496092865,0.0604297101496] p22_u_x[0.164427061041,0.23609709091] p22_u_y[-0.0160510193087,0.0481585030735] p22_u_z[0.971076384658,0.98638924448] p22_v_x[-0,0] p22_v_y[-1,-0.998773128663] p22_v_z[-0.0162300217769,0.0494786226443] p23_u_x[0.926270774112,0.944391461983] p23_u_y[-0.00612963444381,0.0170751335645] p23_u_z[0.328823305986,0.376640696724] p23_v_x[-0,0] p23_v_y[-1,-0.998773128663] p23_v_z[-0.0162300217769,0.0494786226443] p24_u_x[0.809787281705,0.837146798827] p24_u_y[-0.0289553800269,0.00954405600592] p24_u_z[-0.5867526011,-0.547010847155] p24_v_x[-0,0] p24_v_y[-1,-0.998773128663] p24_v_z[-0.0162300217769,0.0494786226443] p32_u_x[0.299298446549,0.373987545668] p32_u_y[-0.013779526553,0.0573393382667] p32_u_z[0.927353689378,0.954170240331] p32_v_x[-0,0] p32_v_y[-1,-0.998172874285] p32_v_z[-0.0144149109606,0.060451779622] p33_u_x[0.992705065981,0.998627406287] p33_u_y[-0.00602546342769,0.00173895894925] p33_u_z[-0.120415085656,-0.0523765543249] p33_v_x[-0,0] p33_v_y[-1,-0.998172874285] p33_v_z[-0.0144149109606,0.060451779622] p34_u_x[0.645218246472,0.681360983883] p34_u_y[-0.0455651176614,0.0110334677568] p34_u_z[-0.764018018965,-0.731662622147] p34_v_x[-0,0] p34_v_y[-1,-0.998172874285] p34_v_z[-0.0144149109606,0.060451779622] p42_u_x[0.973975586318,0.989694805537] p42_u_y[0.0309290722346,0.0514572080183] p42_u_z[-0.221214932706,-0.139869318746] p42_v_x[-0,0] p42_v_y[0.972858122093,0.976784887169] p42_v_z[0.214262785576,0.23141053018] p43_u_x[0.260853146256,0.309076758573] p43_u_y[-0.221099797831,-0.205559440652] p43_u_z[0.92520475723,0.942942679059] p43_v_x[-0,0] p43_v_y[0.972858122093,0.976784887169] p43_v_z[0.214262785576,0.23141053018] p44_u_x[0.244277811395,0.289449578343] p44_u_y[-0.223899917212,-0.205804488305] p44_u_z[0.932378320245,0.946407458971] p44_v_x[-0,0] p44_v_y[0.972858122093,0.976784887169] p44_v_z[0.214262785576,0.23141053018] object_u_x[0.9964290058,0.999333557966] object_u_y[-0.002684706136,0.0193083592991] object_u_z[-0.083753594158,-0.0365306922162] object_v_x[-0.0220231634928,0.00411328357723] object_v_y[0.999093462434,1] object_v_z[-0.037185972106,0.0194622336277] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-1,-0.998170415865] uni_v_palm_p12_z_0[-0.0136496092865,0.0604297101496] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.888974277673,0.923361117377] w2_palm_p12_y_0[-0.00754898546121,0.0259763291983] w2_palm_p12_z_0[0.386442652175,0.455040645923] cos_0_palm_p12_0[0.998170415865,1.00000000001] cos_1_palm_p12_0[0.888974277673,0.923361117377] w1_p12_p13_x_1[0.888974277673,0.923361117377] w1_p12_p13_y_1[-0.00754898546121,0.0259763291983] w1_p12_p13_z_1[0.386442652175,0.455040645923] w2_p12_p13_x_1[0.994991567374,0.999682154072] w2_p12_p13_y_1[-0.00400465625809,0.00136861901513] w2_p12_p13_z_1[-0.100081912531,-0.0252109273917] cos_p12_p13_1[0.846117546477,0.913360898501] w1_p13_p14_x_2[0.632930098669,0.68914638566] w1_p13_p14_y_2[-0.0446844557941,0.0106164233099] w1_p13_p14_z_2[-0.77482676865,-0.723411470677] w2_p13_p14_x_2[0.64522908147,0.681342684454] w2_p13_p14_y_2[-0.0460908983449,0.00998691657882] w2_p13_p14_z_2[-0.764008775234,-0.731691947881] cos_p13_p14_2[0.996464995056,1.000001] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-1,-0.998773128663] uni_v_palm_p22_z_3[-0.0162300217769,0.0494786226443] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.812248254801,0.85501790199] w2_palm_p22_y_3[-0.0102742595497,0.0281127463358] w2_palm_p22_z_3[0.51972663693,0.581357825282] cos_0_palm_p22_3[0.998773128663,1.00000000001] cos_1_palm_p22_3[0.812248254801,0.85501790199] w1_p22_p23_x_4[0.812248254801,0.85501790199] w1_p22_p23_y_4[-0.0102742595497,0.0281127463358] w1_p22_p23_z_4[0.51972663693,0.581357825282] w2_p22_p23_x_4[0.926270774112,0.944391461983] w2_p22_p23_y_4[-0.00612963444381,0.0170751335645] w2_p22_p23_z_4[0.328823305986,0.376640696724] cos_p22_p23_4[0.957799322162,0.988776433544] w1_p23_p24_x_5[0.899854659816,0.921853052921] w1_p23_p24_y_5[-0.0215278821809,0.00712236003438] w1_p23_p24_z_5[-0.435272417414,-0.388590981048] w2_p23_p24_x_5[0.809787281705,0.837146798827] w2_p23_p24_y_5[-0.0289553800269,0.00954405600592] w2_p23_p24_z_5[-0.5867526011,-0.547010847155] cos_p23_p24_5[0.975155918376,0.992878589272] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-1,-0.998172874285] uni_v_palm_p32_z_6[-0.0144149109606,0.060451779622] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.88445031335,0.921423193993] w2_palm_p32_y_6[-0.00806887828909,0.0269793228953] w2_palm_p32_z_6[0.3914312246,0.463283577284] cos_0_palm_p32_6[0.998172874285,1.00000000001] cos_1_palm_p32_6[0.88445031335,0.921423193993] w1_p32_p33_x_7[0.88445031335,0.921423193993] w1_p32_p33_y_7[-0.00806887828909,0.0269793228953] w1_p32_p33_z_7[0.3914312246,0.463283577284] w2_p32_p33_x_7[0.992705065981,0.998627406287] w2_p32_p33_y_7[-0.00602546342769,0.00173895894925] w2_p32_p33_z_7[-0.120415085656,-0.0523765543249] cos_p32_p33_7[0.8242125769,0.89970732531] w1_p33_p34_x_8[0.616612602049,0.66923490081] w1_p33_p34_y_8[-0.0461854807102,0.0114085202708] w1_p33_p34_z_8[-0.786981295713,-0.742467618572] w2_p33_p34_x_8[0.645218246472,0.681360983883] w2_p33_p34_y_8[-0.0455651176614,0.0110334677568] w2_p33_p34_z_8[-0.764018018965,-0.731662622147] cos_p33_p34_8[0.994888123053,1.000001] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.976784887169,-0.972858122093] uni_v_palm_p42_z_9[-0.23141053018,-0.214262785576] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.989694805537,-0.973975586318] w2_palm_p42_y_9[-0.0514572080183,-0.0309290722346] w2_palm_p42_z_9[0.139869318746,0.221214932706] cos_0_palm_p42_9[0.972858122093,0.976784887169] cos_1_palm_p42_9[0.973975586318,0.989694805537] w1_p42_p43_x_10[0.801113532642,0.849561890433] w1_p42_p43_y_10[-0.13270771868,-0.113772087841] w1_p42_p43_z_10[0.515940252623,0.583557761741] w2_p42_p43_x_10[0.260853146256,0.309076758573] w2_p42_p43_y_10[-0.221099797831,-0.205559440652] w2_p42_p43_z_10[0.92520475723,0.942942679059] cos_p42_p43_10[0.749182825595,0.818602169699] w1_p43_p44_x_11[-0.498412881687,-0.453815269378] w1_p43_p44_y_11[-0.206261451581,-0.186053137776] w1_p43_p44_z_11[0.846066661003,0.87021957734] w2_p43_p44_x_11[0.244277811395,0.289449578343] w2_p43_p44_y_11[-0.223899917212,-0.205804488305] w2_p43_p44_z_11[0.932378320245,0.946407458971] cos_p43_p44_11[0.707105781187,0.753669756114] }
   8 (err:1.29514 tm:62):{ 190  p12_u_x[0.247965361734,0.306059375372] p12_u_y[-0.00197473576537,0.0535680256753] p12_u_z[0.950522177826,0.968686051622] p12_v_x[-0,0] p12_v_y[-1,-0.998448832333] p12_v_z[-0.00193756918048,0.0554187070879] p13_u_x[0.988691370952,0.994031948981] p13_u_y[-0.00722535636841,0.000298208192358] p13_u_z[-0.149821545619,-0.109089341525] p13_v_x[-0,0] p13_v_y[-1,-0.998448832333] p13_v_z[-0.00193756918048,0.0554187070879] p14_u_x[0.665659253644,0.700067636364] p14_u_y[-0.0409478355564,0.00152135383352] p14_u_z[-0.74628426837,-0.713128406526] p14_v_x[-0,0] p14_v_y[-1,-0.998448832333] p14_v_z[-0.00193756918048,0.0554187070879] p22_u_x[0.0589501726893,0.121505862705] p22_u_y[-0.00179507502449,0.0481168320856] p22_u_z[0.992134868467,0.998260926396] p22_v_x[-0,0] p22_v_y[-1,-0.998823204057] p22_v_z[-0.00172859670762,0.0483783022124] p23_u_x[0.968318042448,0.975956337498] p23_u_y[-0.000433834799148,0.0117513262832] p23_u_z[0.218033501691,0.249442116096] p23_v_x[-0,0] p23_v_y[-1,-0.998823204057] p23_v_z[-0.00172859670762,0.0483783022124] p24_u_x[0.825471866018,0.851197364093] p24_u_y[-0.026860774991,0.00101504970314] p24_u_z[-0.564480280113,-0.524537055211] p24_v_x[-0,0] p24_v_y[-1,-0.998823204057] p24_v_z[-0.00172859670762,0.0483783022124] p32_u_x[0.23967351472,0.304464175524] p32_u_y[-0.00206476279268,0.05369070579] p32_u_z[0.952508622202,0.970211463527] p32_v_x[-0,0] p32_v_y[-1,-0.998449945267] p32_v_z[-0.00201948967811,0.0554337249605] p33_u_x[0.978474536564,0.989192202666] p33_u_y[-0.0100626421801,0.000438655228644] p33_u_z[-0.206119717588,-0.146723793276] p33_v_x[-0,0] p33_v_y[-1,-0.998449945267] p33_v_z[-0.00201948967811,0.0554337249605] p34_u_x[0.665620301573,0.700067783457] p34_u_y[-0.0399820855875,0.00158828784016] p34_u_z[-0.746320629722,-0.713161033647] p34_v_x[-0,0] p34_v_y[-1,-0.998449945267] p34_v_z[-0.00201948967811,0.0554337249605] p42_u_x[0.964110836534,0.981194439612] p42_u_y[0.0441129799633,0.0636694988817] p42_u_z[-0.258037642714,-0.187947213192] p42_v_x[-0,0] p42_v_y[0.969665311186,0.973534834354] p42_v_z[0.228589108728,0.244442949531] p43_u_x[0.24194408078,0.309076758573] p43_u_y[-0.233292360961,-0.217339672149] p43_u_z[0.922168543615,0.944489288185] p43_v_x[-0,0] p43_v_y[0.969665311186,0.973534834354] p43_v_z[0.228589108728,0.244442949531] p44_u_x[0.218827954299,0.26498887076] p44_u_y[-0.238372479702,-0.220958979601] p44_u_z[0.936378262041,0.949670472641] p44_v_x[-0,0] p44_v_y[0.969665311186,0.973534834354] p44_v_z[0.228589108728,0.244442949531] object_u_x[0.998319359435,0.999941138582] object_u_y[-0.00352233912125,0.013682110533] object_u_z[-0.0568958931754,-0.0108498572098] object_v_x[-0.0153963724214,0.00362712742114] object_v_y[0.999080076166,1] object_v_z[-0.040883544122,0.00194663146173] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-1,-0.998448832333] uni_v_palm_p12_z_0[-0.00193756918048,0.0554187070879] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.859547591546,0.890506519333] w2_palm_p12_y_0[-0.00208330102613,0.0277666170906] w2_palm_p12_z_0[0.455921063777,0.509628813717] cos_0_palm_p12_0[0.998448832333,1.00000000001] cos_1_palm_p12_0[0.859547591546,0.890506519333] w1_p12_p13_x_1[0.859547591546,0.890506519333] w1_p12_p13_y_1[-0.00208330102613,0.0277666170906] w1_p12_p13_z_1[0.455921063777,0.509628813717] w2_p12_p13_x_1[0.988691370952,0.994031948981] w2_p12_p13_y_1[-0.00722535636841,0.000298208192358] w2_p12_p13_z_1[-0.149821545619,-0.109089341525] cos_p12_p13_1[0.773446816229,0.835444571889] w1_p13_p14_x_2[0.593015316792,0.625821203131] w1_p13_p14_y_2[-0.0440548217853,0.00164150786701] w1_p13_p14_z_2[-0.805223865626,-0.778915705809] w2_p13_p14_x_2[0.665659253644,0.700067636364] w2_p13_p14_y_2[-0.0409478355564,0.00152135383352] w2_p13_p14_z_2[-0.74628426837,-0.713128406526] cos_p13_p14_2[0.989163771446,0.999325788749] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-1,-0.998823204057] uni_v_palm_p22_z_3[-0.00172859670762,0.0483783022124] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.746664964154,0.788526691243] w2_palm_p22_y_3[-0.00220682355122,0.0317568076878] w2_palm_p22_z_3[0.615995527435,0.664242291005] cos_0_palm_p22_3[0.998823204057,1.00000000001] cos_1_palm_p22_3[0.746664964154,0.788526691243] w1_p22_p23_x_4[0.746664964154,0.788526691243] w1_p22_p23_y_4[-0.00220682355122,0.0317568076878] w1_p22_p23_z_4[0.615995527435,0.664242291005] w2_p22_p23_x_4[0.968318042448,0.975956337498] w2_p22_p23_y_4[-0.000433834799148,0.0117513262832] w2_p22_p23_z_4[0.218033501691,0.249442116096] cos_p22_p23_4[0.875627275006,0.918404157863] w1_p23_p24_x_5[0.844132116815,0.861457415323] w1_p23_p24_y_5[-0.0253761766018,0.00151418694806] w1_p23_p24_z_5[-0.535526544804,-0.507515043264] w2_p23_p24_x_5[0.825471866018,0.851197364093] w2_p23_p24_y_5[-0.026860774991,0.00101504970314] w2_p23_p24_z_5[-0.564480280113,-0.524537055211] cos_p23_p24_5[0.997235711734,1.000001] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-1,-0.998449945267] uni_v_palm_p32_z_6[-0.00201948967811,0.0554337249605] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.854810826357,0.88958091791] w2_palm_p32_y_6[-0.00236164772756,0.028253214941] w2_palm_p32_z_6[0.458357082048,0.516678949302] cos_0_palm_p32_6[0.998449945267,1.00000000001] cos_1_palm_p32_6[0.854810826357,0.88958091791] w1_p32_p33_x_7[0.854810826357,0.88958091791] w1_p32_p33_y_7[-0.00236164772756,0.028253214941] w1_p32_p33_z_7[0.458357082048,0.516678949302] w2_p32_p33_x_7[0.978474536564,0.989192202666] w2_p32_p33_y_7[-0.0100626421801,0.000438655228644] w2_p32_p33_z_7[-0.206119717588,-0.146723793276] cos_p32_p33_7[0.729743239056,0.812689065167] w1_p33_p34_x_8[0.54588039754,0.595737827941] w1_p33_p34_y_8[-0.045444259361,0.0017512143004] w1_p33_p34_z_8[-0.837771972482,-0.803139244906] w2_p33_p34_x_8[0.665620301573,0.700067783457] w2_p33_p34_y_8[-0.0399820855875,0.00158828784016] w2_p33_p34_z_8[-0.746320629722,-0.713161033647] cos_p33_p34_8[0.979482375611,0.996383837638] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.973534834354,-0.969665311186] uni_v_palm_p42_z_9[-0.244442949531,-0.228589108728] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.981194439612,-0.964110836534] w2_palm_p42_y_9[-0.0636694988817,-0.0441129799633] w2_palm_p42_z_9[0.187947213192,0.258037642714] cos_0_palm_p42_9[0.969665311186,0.973534834354] cos_1_palm_p42_9[0.964110836534,0.981194439612] w1_p42_p43_x_10[0.830309423614,0.870124702931] w1_p42_p43_y_10[-0.134661661942,-0.116121502647] w1_p42_p43_z_10[0.479707133119,0.541945981912] w2_p42_p43_x_10[0.24194408078,0.309076758573] w2_p42_p43_y_10[-0.233292360961,-0.217339672149] w2_p42_p43_z_10[0.922168543615,0.944489288185] cos_p42_p43_10[0.707105781187,0.788691917571] w1_p43_p44_x_11[-0.515486883665,-0.453813355091] w1_p43_p44_y_11[-0.217922134664,-0.197933514211] w1_p43_p44_z_11[0.832545048034,0.867897053161] w2_p43_p44_x_11[0.218827954299,0.26498887076] w2_p43_p44_y_11[-0.238372479702,-0.220958979601] w2_p43_p44_z_11[0.936378262041,0.949670472641] cos_p43_p44_11[0.707105781187,0.77086972764] }
   9 (err:2.06172 tm:63):{ 190  p12_u_x[0.193737870606,0.261281012338] p12_u_y[0.00201315044612,0.0362224653709] p12_u_z[0.964741193431,0.981066423605] p12_v_x[-0,0] p12_v_y[-0.999997822022,-0.999287197661] p12_v_z[0.0021657828179,0.037092865142] p13_u_x[0.988700496237,0.993263096309] p13_u_y[-0.00522994115115,-0.000311175910119] p13_u_z[-0.149821545619,-0.116851780791] p13_v_x[-0,0] p13_v_y[-0.999997822022,-0.999287197661] p13_v_z[0.0021657828179,0.037092865142] p14_u_x[0.681428959718,0.699616532119] p14_u_y[-0.0268244393226,-0.00148999907013] p14_u_z[-0.731861032194,-0.714073357171] p14_v_x[-0,0] p14_v_y[-0.999997822022,-0.999287197661] p14_v_z[0.0021657828179,0.037092865142] p22_u_x[-0.000573529198202,0.0589501726905] p22_u_y[0.00323918734201,0.0344117430975] p22_u_z[0.997654829065,0.999994972108] p22_v_x[-0,0] p22_v_y[-0.999994695468,-0.999387112087] p22_v_z[0.00325715619262,0.0344425123003] p23_u_x[0.968353992949,0.974770853041] p23_u_y[0.00083377811073,0.0081851022529] p23_u_z[0.223259859335,0.249442116096] p23_v_x[-0,0] p23_v_y[-0.999994695468,-0.999387112087] p23_v_z[0.00325715619262,0.0344425123003] p24_u_x[0.837285980782,0.85082888566] p24_u_y[-0.0184398840506,-0.00171068662889] p24_u_z[-0.546713364922,-0.525250093699] p24_v_x[-0,0] p24_v_y[-0.999994695468,-0.999387112087] p24_v_z[0.00325715619262,0.0344425123003] p32_u_x[0.19440558582,0.261417711086] p32_u_y[0.00201310081188,0.0363756675108] p32_u_z[0.964719746708,0.980927886534] p32_v_x[-0,0] p32_v_y[-0.999997822021,-0.999287218054] p32_v_z[0.0021657830279,0.0370928372091] p33_u_x[0.978502083452,0.987196087079] p33_u_y[-0.00683158298658,-0.000332866938311] p33_u_z[-0.206119717588,-0.159562028967] p33_v_x[-0,0] p33_v_y[-0.999997822021,-0.999287218054] p33_v_z[0.0021657830279,0.0370928372091] p34_u_x[0.68142927286,0.699616509762] p34_u_y[-0.0264889445702,-0.00149002992581] p34_u_z[-0.731859403461,-0.714086523233] p34_v_x[-0,0] p34_v_y[-0.999997822021,-0.999287218054] p34_v_z[0.0021657830279,0.0370928372091] p42_u_x[0.972112409574,0.980750783589] p42_u_y[0.045177787192,0.0548761095482] p42_u_z[-0.227981859505,-0.189994204841] p42_v_x[-0,0] p42_v_y[0.970334341201,0.972866278113] p42_v_z[0.231405473012,0.241766633393] p43_u_x[0.223212856862,0.308979527022] p43_u_y[-0.232576980545,-0.220704483298] p43_u_z[0.923019241812,0.94843367671] p43_v_x[-0,0] p43_v_y[0.970334341201,0.972866278113] p43_v_z[0.231405473012,0.241766633393] p44_u_x[0.219070592396,0.244490561394] p44_u_y[-0.235810294837,-0.22506819519] p44_u_z[0.942866682402,0.949259032521] p44_v_x[-0,0] p44_v_y[0.970334341201,0.972866278113] p44_v_z[0.231405473012,0.241766633393] object_u_x[0.999346010273,0.999941138582] object_u_y[-0.00260275603439,0.00553758387148] object_u_z[-0.0356796556706,-0.0108498572098] object_v_x[-0.00622436063384,0.00255395144091] object_v_y[0.999481747451,0.999988678844] object_v_z[-0.0311203559427,-0.00478236939575] uni_u_palm_p12_x_0[1,1] uni_u_palm_p12_y_0[-0,0] uni_u_palm_p12_z_0[-0,0] uni_v_palm_p12_x_0[-0,0] uni_v_palm_p12_y_0[-0.999997822022,-0.999287197661] uni_v_palm_p12_z_0[0.0021657828179,0.037092865142] w1_palm_p12_x_0[-0,0] w1_palm_p12_y_0[-1,-1] w1_palm_p12_z_0[-0,0] w2_palm_p12_x_0[0.830238295345,0.867966812983] w2_palm_p12_y_0[0.000276887770055,0.0204176928058] w2_palm_p12_z_0[0.497504868131,0.556703061899] cos_0_palm_p12_0[0.999287197661,0.999997822022] cos_1_palm_p12_0[0.830238295345,0.867966812983] w1_p12_p13_x_1[0.830238295345,0.867966812983] w1_p12_p13_y_1[0.000276887770055,0.0204176928058] w1_p12_p13_z_1[0.497504868131,0.556703061899] w2_p12_p13_x_1[0.988700496237,0.993263096309] w2_p12_p13_y_1[-0.00522994115115,-0.000311175910119] w2_p12_p13_z_1[-0.149821545619,-0.116851780791] cos_p12_p13_1[0.737396137472,0.799863095731] w1_p13_p14_x_2[0.593095896766,0.61967316593] w1_p13_p14_y_2[-0.0297176946396,-0.00167915971481] w1_p13_p14_z_2[-0.805174608549,-0.784406940223] w2_p13_p14_x_2[0.681428959718,0.699616532119] w2_p13_p14_y_2[-0.0268244393226,-0.00148999907013] w2_p13_p14_z_2[-0.731861032194,-0.714073357171] cos_p13_p14_2[0.989845423854,0.994806198463] uni_u_palm_p22_x_3[1,1] uni_u_palm_p22_y_3[-0,0] uni_u_palm_p22_z_3[-0,0] uni_v_palm_p22_x_3[-0,0] uni_v_palm_p22_y_3[-0.999994695468,-0.999387112087] uni_v_palm_p22_z_3[0.00325715619262,0.0344425123003] w1_palm_p22_x_3[-0,0] w1_palm_p22_y_3[-1,-1] w1_palm_p22_z_3[-0,0] w2_palm_p22_x_3[0.707105781149,0.748061785525] w2_palm_p22_y_3[0.0014711913688,0.0242624295428] w2_palm_p22_z_3[0.663774469819,0.707515130232] cos_0_palm_p22_3[0.999387112087,0.999994695468] cos_1_palm_p22_3[0.707105781187,0.748061785525] w1_p22_p23_x_4[0.707105781149,0.748061785525] w1_p22_p23_y_4[0.0014711913688,0.0242624295428] w1_p22_p23_z_4[0.663774469819,0.707515130232] w2_p22_p23_x_4[0.968353992949,0.974770853041] w2_p22_p23_y_4[0.00083377811073,0.0081851022529] w2_p22_p23_z_4[0.223259859335,0.249442116096] cos_p22_p23_4[0.85758957431,0.891040843956] w1_p23_p24_x_5[0.847096775901,0.861308964285] w1_p23_p24_y_5[-0.0178682166744,-0.0013369663874] w1_p23_p24_z_5[-0.531108842824,-0.507926426516] w2_p23_p24_x_5[0.837285980782,0.85082888566] w2_p23_p24_y_5[-0.0184398840506,-0.00171068662889] w2_p23_p24_z_5[-0.546713364922,-0.525250093699] cos_p23_p24_5[0.99874992692,1.000001] uni_u_palm_p32_x_6[1,1] uni_u_palm_p32_y_6[-0,0] uni_u_palm_p32_z_6[-0,0] uni_v_palm_p32_x_6[-0,0] uni_v_palm_p32_y_6[-0.999997822021,-0.999287218054] uni_v_palm_p32_z_6[0.0021657830279,0.0370928372091] w1_palm_p32_x_6[-0,0] w1_palm_p32_y_6[-1,-1] w1_palm_p32_z_6[-0,0] w2_palm_p32_x_6[0.830647532626,0.868030918973] w2_palm_p32_y_6[0.00020479340683,0.0205239875112] w2_palm_p32_z_6[0.497417532221,0.556158807434] cos_0_palm_p32_6[0.999287218054,0.999997822021] cos_1_palm_p32_6[0.830647532626,0.868030918973] w1_p32_p33_x_7[0.830647532626,0.868030918973] w1_p32_p33_y_7[0.00020479340683,0.0205239875112] w1_p32_p33_z_7[0.497417532221,0.556158807434] w2_p32_p33_x_7[0.978502083452,0.987196087079] w2_p32_p33_y_7[-0.00683158298658,-0.000332866938311] w2_p32_p33_z_7[-0.206119717588,-0.159562028967] cos_p32_p33_7[0.707105781187,0.774366301944] w1_p33_p34_x_8[0.546041980651,0.585224431168] w1_p33_p34_y_8[-0.03060665634,-0.00174139194903] w1_p33_p34_z_8[-0.837636665283,-0.810866567594] w2_p33_p34_x_8[0.68142927286,0.699616509762] w2_p33_p34_y_8[-0.0264889445702,-0.00149002992581] w2_p33_p34_z_8[-0.731859403461,-0.714086523233] cos_p33_p34_8[0.980235442789,0.990531433012] uni_u_palm_p42_x_9[-1,-1] uni_u_palm_p42_y_9[-0,0] uni_u_palm_p42_z_9[-0,0] uni_v_palm_p42_x_9[-0,0] uni_v_palm_p42_y_9[-0.972866278113,-0.970334341201] uni_v_palm_p42_z_9[-0.241766633393,-0.231405473012] w1_palm_p42_x_9[-0,0] w1_palm_p42_y_9[-1,-1] w1_palm_p42_z_9[-0,0] w2_palm_p42_x_9[-0.980750783589,-0.972112409574] w2_palm_p42_y_9[-0.0548761095482,-0.045177787192] w2_palm_p42_z_9[0.189994204841,0.227981859505] cos_0_palm_p42_9[0.970334341201,0.972866278113] cos_1_palm_p42_9[0.972112409574,0.980750783589] w1_p42_p43_x_10[0.831569558356,0.853350449066] w1_p42_p43_y_10[-0.132780990458,-0.121438177159] w1_p42_p43_z_10[0.507215429292,0.540208060697] w2_p42_p43_x_10[0.223212856862,0.308979527022] w2_p42_p43_y_10[-0.232576980545,-0.220704483298] w2_p42_p43_z_10[0.923019241812,0.94843367671] cos_p42_p43_10[0.707673836201,0.780694104911] w1_p43_p44_x_11[-0.532174884125,-0.454157450938] w1_p43_p44_y_11[-0.215286181023,-0.198776550428] w1_p43_p44_z_11[0.823348595662,0.865558088903] w2_p43_p44_x_11[0.219070592396,0.244490561394] w2_p43_p44_y_11[-0.235810294837,-0.22506819519] w2_p43_p44_z_11[0.942866682402,0.949259032521] cos_p43_p44_11[0.707105781187,0.770479775892] }


Cuik executed in 159 (159) child processors
STATITISTICS FOR Cuik:

Volume of the search space: 4.74354e+07
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 0.624037
Number of processors: 160
User time in process: 74.000000 seg (1.233333 min)
Box level information:
  N processed boxes :    820
  Max depth         :     23
  Types of boxes:
    N solution boxes:      9 (0) ( 1.10%)
    N empty boxes   :    201  (24.51%)
    N bisected boxes:    610  (74.39%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :   4955
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

