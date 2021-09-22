
==========================================================================
%COMPILATION FLAGS:
%   SIMPLEX ENGINE: clp
%   MPI: 1
%   DEBUG: 1
%   PROFILE: 0
%==========================================================================
%PARAMETERS:
   Epsilon= 1e-06
   Rho= 0.45
   Small Sigma= 0.0001
   Sigma= 0.1
   Large Sigma= 1.79769e+308
   Period between state files= 1000
   D= 1.79769e+308
   Number of solutions= 1
   Number of samples= 1
   Max Newton Iterations= 0
   Max Path Refinements= 0
   Period between trace files= 0
   Num DOF= 16
   Small-White bias= 0
   Clearance-Grey bias= 0
   Dummification Level= 1
   Error Split = 0
   Save Simplex= 1
   Simplification Level= 3
   LR2TM_Q= 0.5
   LR2TM_S= 0.1

==========================================================================
Equations from file: /home/porta/cuik/CuikSuite/examples/IJRR/teapot/4_contacts_index_middle_ring_palm/SAHandplusTeapot_kin.cuik
% Kinematic subsystem

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
   p40_u_x : [-1,1]
   p40_u_y : [-1,1]
   p40_u_z : [-1,1]
   p40_v_x : [-1,1]
   p40_v_y : [-1,1]
   p40_v_z : [-1,1]

[DUMMY VARS]
   p40_w_x : [-1,1]
   p40_w_y : [-1,1]
   p40_w_z : [-1,1]
   p40_wp_x : [-1,1]
   p40_wp_y : [-1,1]
   p40_wp_z : [-1,1]

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

[SYSTEM VARS]
   X_P_u_x : [-1,1]
   X_P_u_y : [-1,1]
   X_P_u_z : [-1,1]
   X_P_v_x : [-1,1]
   X_P_v_y : [-1,1]
   X_P_v_z : [-1,1]

[DUMMY VARS]
   X_P_w_x : [-1,1]
   X_P_w_y : [-1,1]
   X_P_w_z : [-1,1]
   X_P_wp_x : [-1,1]
   X_P_wp_y : [-1,1]
   X_P_wp_z : [-1,1]

[SYSTEM VARS]
   X_1_u_x : [-1,1]
   X_1_u_y : [-1,1]
   X_1_u_z : [-1,1]
   X_1_v_x : [-1,1]
   X_1_v_y : [-1,1]
   X_1_v_z : [-1,1]

[DUMMY VARS]
   X_1_w_x : [-1,1]
   X_1_w_y : [-1,1]
   X_1_w_z : [-1,1]
   X_1_wp_x : [-1,1]
   X_1_wp_y : [-1,1]
   X_1_wp_z : [-1,1]

[SYSTEM VARS]
   X_2_u_x : [-1,1]
   X_2_u_y : [-1,1]
   X_2_u_z : [-1,1]
   X_2_v_x : [-1,1]
   X_2_v_y : [-1,1]
   X_2_v_z : [-1,1]

[DUMMY VARS]
   X_2_w_x : [-1,1]
   X_2_w_y : [-1,1]
   X_2_w_z : [-1,1]
   X_2_wp_x : [-1,1]
   X_2_wp_y : [-1,1]
   X_2_wp_z : [-1,1]

[SYSTEM VARS]
   X_3_u_x : [-1,1]
   X_3_u_y : [-1,1]
   X_3_u_z : [-1,1]
   X_3_v_x : [-1,1]
   X_3_v_y : [-1,1]
   X_3_v_z : [-1,1]

[DUMMY VARS]
   X_3_w_x : [-1,1]
   X_3_w_y : [-1,1]
   X_3_w_z : [-1,1]
   X_3_wp_x : [-1,1]
   X_3_wp_y : [-1,1]
   X_3_wp_z : [-1,1]

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
   cos_0_palm_p12_0 : [0.923879532511,1]
   cos_1_palm_p12_0 : [0.707106781187,1]
   w1_p12_p13_x_1 : [-1,1]
   w1_p12_p13_y_1 : [-1,1]
   w1_p12_p13_z_1 : [-1,1]
   w2_p12_p13_x_1 : [-1,1]
   w2_p12_p13_y_1 : [-1,1]
   w2_p12_p13_z_1 : [-1,1]
   cos_p12_p13_1 : [0.707106781187,1]
   w1_p13_p14_x_2 : [-1,1]
   w1_p13_p14_y_2 : [-1,1]
   w1_p13_p14_z_2 : [-1,1]
   w2_p13_p14_x_2 : [-1,1]
   w2_p13_p14_y_2 : [-1,1]
   w2_p13_p14_z_2 : [-1,1]
   cos_p13_p14_2 : [0.707106781187,1]
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
   cos_0_palm_p22_3 : [0.923879532511,1]
   cos_1_palm_p22_3 : [0.707106781187,1]
   w1_p22_p23_x_4 : [-1,1]
   w1_p22_p23_y_4 : [-1,1]
   w1_p22_p23_z_4 : [-1,1]
   w2_p22_p23_x_4 : [-1,1]
   w2_p22_p23_y_4 : [-1,1]
   w2_p22_p23_z_4 : [-1,1]
   cos_p22_p23_4 : [0.707106781187,1]
   w1_p23_p24_x_5 : [-1,1]
   w1_p23_p24_y_5 : [-1,1]
   w1_p23_p24_z_5 : [-1,1]
   w2_p23_p24_x_5 : [-1,1]
   w2_p23_p24_y_5 : [-1,1]
   w2_p23_p24_z_5 : [-1,1]
   cos_p23_p24_5 : [0.707106781187,1]
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
   cos_0_palm_p32_6 : [0.923879532511,1]
   cos_1_palm_p32_6 : [0.707106781187,1]
   w1_p32_p33_x_7 : [-1,1]
   w1_p32_p33_y_7 : [-1,1]
   w1_p32_p33_z_7 : [-1,1]
   w2_p32_p33_x_7 : [-1,1]
   w2_p32_p33_y_7 : [-1,1]
   w2_p32_p33_z_7 : [-1,1]
   cos_p32_p33_7 : [0.707106781187,1]
   w1_p33_p34_x_8 : [-1,1]
   w1_p33_p34_y_8 : [-1,1]
   w1_p33_p34_z_8 : [-1,1]
   w2_p33_p34_x_8 : [-1,1]
   w2_p33_p34_y_8 : [-1,1]
   w2_p33_p34_z_8 : [-1,1]
   cos_p33_p34_8 : [0.707106781187,1]
   w1_palm_p40_x_9 : [-1,1]
   w1_palm_p40_y_9 : [-1,1]
   w1_palm_p40_z_9 : [-1,1]
   w2_palm_p40_x_9 : [-1,1]
   w2_palm_p40_y_9 : [-1,1]
   w2_palm_p40_z_9 : [-1,1]
   cos_palm_p40_9 : [1,1]
   uni_u_p40_p42_x_10 : [-1,1]
   uni_u_p40_p42_y_10 : [-1,1]
   uni_u_p40_p42_z_10 : [-1,1]
   uni_v_p40_p42_x_10 : [-1,1]
   uni_v_p40_p42_y_10 : [-1,1]
   uni_v_p40_p42_z_10 : [-1,1]
   w1_p40_p42_x_10 : [-1,1]
   w1_p40_p42_y_10 : [-1,1]
   w1_p40_p42_z_10 : [-1,1]
   w2_p40_p42_x_10 : [-1,1]
   w2_p40_p42_y_10 : [-1,1]
   w2_p40_p42_z_10 : [-1,1]
   cos_0_p40_p42_10 : [1,1]
   cos_1_p40_p42_10 : [1,1]
   w1_p42_p43_x_11 : [-1,1]
   w1_p42_p43_y_11 : [-1,1]
   w1_p42_p43_z_11 : [-1,1]
   w2_p42_p43_x_11 : [-1,1]
   w2_p42_p43_y_11 : [-1,1]
   w2_p42_p43_z_11 : [-1,1]
   cos_p42_p43_11 : [1,1]
   w1_p43_p44_x_12 : [-1,1]
   w1_p43_p44_y_12 : [-1,1]
   w1_p43_p44_z_12 : [-1,1]
   w2_p43_p44_x_12 : [-1,1]
   w2_p43_p44_y_12 : [-1,1]
   w2_p43_p44_z_12 : [-1,1]
   cos_p43_p44_12 : [1,1]
   sph_w1_p14_X_1_x_13 : [-1,1]
   sph_w1_p14_X_1_y_13 : [-1,1]
   sph_w1_p14_X_1_z_13 : [-1,1]
   sph_w2_p14_X_1_x_13 : [-1,1]
   sph_w2_p14_X_1_y_13 : [-1,1]
   sph_w2_p14_X_1_z_13 : [-1,1]
   cos_p14_X_1_13 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_1_object_u_14 : [0,1]
   in_patch_X_1_object_v_14 : [0,1]

[DUMMY VARS]
   in_patch_X_1_object_w_14 : [0,1]

[SECONDARY VARS]
   in_patch_X_1_object_l_14 : [556.258042284,587.242331635]
   sph_w1_p24_X_2_x_15 : [-1,1]
   sph_w1_p24_X_2_y_15 : [-1,1]
   sph_w1_p24_X_2_z_15 : [-1,1]
   sph_w2_p24_X_2_x_15 : [-1,1]
   sph_w2_p24_X_2_y_15 : [-1,1]
   sph_w2_p24_X_2_z_15 : [-1,1]
   cos_p24_X_2_15 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_2_object_u_16 : [0,1]
   in_patch_X_2_object_v_16 : [0,1]

[DUMMY VARS]
   in_patch_X_2_object_w_16 : [0,1]

[SECONDARY VARS]
   in_patch_X_2_object_l_16 : [594.179172658,625.399218835]
   sph_w1_p34_X_3_x_17 : [-1,1]
   sph_w1_p34_X_3_y_17 : [-1,1]
   sph_w1_p34_X_3_z_17 : [-1,1]
   sph_w2_p34_X_3_x_17 : [-1,1]
   sph_w2_p34_X_3_y_17 : [-1,1]
   sph_w2_p34_X_3_z_17 : [-1,1]
   cos_p34_X_3_17 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_18 : [0,1]
   in_patch_X_3_object_v_18 : [0,1]

[DUMMY VARS]
   in_patch_X_3_object_w_18 : [0,1]

[SECONDARY VARS]
   in_patch_X_3_object_l_18 : [556.258042284,587.242331635]
   sph_w1_palm_X_P_x_19 : [-1,1]
   sph_w1_palm_X_P_y_19 : [-1,1]
   sph_w1_palm_X_P_z_19 : [-1,1]
   sph_w2_palm_X_P_x_19 : [-1,1]
   sph_w2_palm_X_P_y_19 : [-1,1]
   sph_w2_palm_X_P_z_19 : [-1,1]
   cos_palm_X_P_19 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_P_object_u_20 : [0,1]
   in_patch_X_P_object_v_20 : [0,1]

[DUMMY VARS]
   in_patch_X_P_object_w_20 : [0,1]

[SECONDARY VARS]
   in_patch_X_P_object_l_20 : [9385,9385.1]

[CARTESIAN VARS]
   p44_r_x : [-1666.19770271,1666.19770271]
   p44_r_y : [-1666.19770271,1666.19770271]
   p44_r_z : [-1666.19770271,1666.19770271]

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
   p40_u_x^2+p40_u_y^2+p40_u_z^2 = 1;
   p40_v_x^2+p40_v_y^2+p40_v_z^2 = 1;
   p40_u_x*p40_v_x+p40_u_y*p40_v_y+p40_u_z*p40_v_z = 0;
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
   X_P_u_x^2+X_P_u_y^2+X_P_u_z^2 = 1;
   X_P_v_x^2+X_P_v_y^2+X_P_v_z^2 = 1;
   X_P_u_x*X_P_v_x+X_P_u_y*X_P_v_y+X_P_u_z*X_P_v_z = 0;
   X_1_u_x^2+X_1_u_y^2+X_1_u_z^2 = 1;
   X_1_v_x^2+X_1_v_y^2+X_1_v_z^2 = 1;
   X_1_u_x*X_1_v_x+X_1_u_y*X_1_v_y+X_1_u_z*X_1_v_z = 0;
   X_2_u_x^2+X_2_u_y^2+X_2_u_z^2 = 1;
   X_2_v_x^2+X_2_v_y^2+X_2_v_z^2 = 1;
   X_2_u_x*X_2_v_x+X_2_u_y*X_2_v_y+X_2_u_z*X_2_v_z = 0;
   X_3_u_x^2+X_3_u_y^2+X_3_u_z^2 = 1;
   X_3_v_x^2+X_3_v_y^2+X_3_v_z^2 = 1;
   X_3_u_x*X_3_v_x+X_3_u_y*X_3_v_y+X_3_u_z*X_3_v_z = 0;
   uni_u_palm_p12_x_0 = 1;
   uni_u_palm_p12_y_0 = -0;
   uni_u_palm_p12_z_0 = -0;
   p12_v_x-uni_v_palm_p12_x_0 = 0;
   p12_v_y-uni_v_palm_p12_y_0 = 0;
   p12_v_z-uni_v_palm_p12_z_0 = 0;
   uni_u_palm_p12_x_0*uni_v_palm_p12_x_0+uni_u_palm_p12_y_0*uni_v_palm_p12_y_0+uni_u_palm_p12_z_0*uni_v_palm_p12_z_0 = 0;
   w1_palm_p12_x_0 = 0;
   w1_palm_p12_y_0 = -0.999411545741;
   w1_palm_p12_z_0 = 0.0343010530517;
   0.707106781187*p12_u_x+0.707106781187*p12_w_x-0.707106781187*p12_wp_x-w2_palm_p12_x_0 = -0;
   0.707106781187*p12_u_y+0.707106781187*p12_w_y-0.707106781187*p12_wp_y-w2_palm_p12_y_0 = -0;
   0.707106781187*p12_u_z+0.707106781187*p12_w_z-0.707106781187*p12_wp_z-w2_palm_p12_z_0 = -0;
   uni_v_palm_p12_x_0*w1_palm_p12_x_0+uni_v_palm_p12_y_0*w1_palm_p12_y_0+uni_v_palm_p12_z_0*w1_palm_p12_z_0-cos_0_palm_p12_0 = 0;
   uni_u_palm_p12_x_0*w2_palm_p12_x_0+uni_u_palm_p12_y_0*w2_palm_p12_y_0+uni_u_palm_p12_z_0*w2_palm_p12_z_0-cos_1_palm_p12_0 = 0;
   p12_v_x-p13_v_x = -0;
   p12_v_y-p13_v_y = -0;
   p12_v_z-p13_v_z = -0;
   0.707106781187*p12_u_x+0.707106781187*p12_w_x-0.707106781187*p12_wp_x-w1_p12_p13_x_1 = -0;
   0.707106781187*p12_u_y+0.707106781187*p12_w_y-0.707106781187*p12_wp_y-w1_p12_p13_y_1 = -0;
   0.707106781187*p12_u_z+0.707106781187*p12_w_z-0.707106781187*p12_wp_z-w1_p12_p13_z_1 = -0;
   p13_u_x-w2_p12_p13_x_1 = -0;
   p13_u_y-w2_p12_p13_y_1 = -0;
   p13_u_z-w2_p12_p13_z_1 = -0;
   w1_p12_p13_x_1*w2_p12_p13_x_1+w1_p12_p13_y_1*w2_p12_p13_y_1+w1_p12_p13_z_1*w2_p12_p13_z_1-cos_p12_p13_1 = 0;
   p13_v_x-p14_v_x = -0;
   p13_v_y-p14_v_y = -0;
   p13_v_z-p14_v_z = -0;
   0.707106781187*p13_u_x+0.707106781187*p13_w_x-0.707106781187*p13_wp_x-w1_p13_p14_x_2 = -0;
   0.707106781187*p13_u_y+0.707106781187*p13_w_y-0.707106781187*p13_wp_y-w1_p13_p14_y_2 = -0;
   0.707106781187*p13_u_z+0.707106781187*p13_w_z-0.707106781187*p13_wp_z-w1_p13_p14_z_2 = -0;
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
   0.707106781187*p22_u_x+0.707106781187*p22_w_x-0.707106781187*p22_wp_x-w2_palm_p22_x_3 = -0;
   0.707106781187*p22_u_y+0.707106781187*p22_w_y-0.707106781187*p22_wp_y-w2_palm_p22_y_3 = -0;
   0.707106781187*p22_u_z+0.707106781187*p22_w_z-0.707106781187*p22_wp_z-w2_palm_p22_z_3 = -0;
   uni_v_palm_p22_x_3*w1_palm_p22_x_3+uni_v_palm_p22_y_3*w1_palm_p22_y_3+uni_v_palm_p22_z_3*w1_palm_p22_z_3-cos_0_palm_p22_3 = 0;
   uni_u_palm_p22_x_3*w2_palm_p22_x_3+uni_u_palm_p22_y_3*w2_palm_p22_y_3+uni_u_palm_p22_z_3*w2_palm_p22_z_3-cos_1_palm_p22_3 = 0;
   p22_v_x-p23_v_x = -0;
   p22_v_y-p23_v_y = -0;
   p22_v_z-p23_v_z = -0;
   0.707106781187*p22_u_x+0.707106781187*p22_w_x-0.707106781187*p22_wp_x-w1_p22_p23_x_4 = -0;
   0.707106781187*p22_u_y+0.707106781187*p22_w_y-0.707106781187*p22_wp_y-w1_p22_p23_y_4 = -0;
   0.707106781187*p22_u_z+0.707106781187*p22_w_z-0.707106781187*p22_wp_z-w1_p22_p23_z_4 = -0;
   p23_u_x-w2_p22_p23_x_4 = -0;
   p23_u_y-w2_p22_p23_y_4 = -0;
   p23_u_z-w2_p22_p23_z_4 = -0;
   w1_p22_p23_x_4*w2_p22_p23_x_4+w1_p22_p23_y_4*w2_p22_p23_y_4+w1_p22_p23_z_4*w2_p22_p23_z_4-cos_p22_p23_4 = 0;
   p23_v_x-p24_v_x = -0;
   p23_v_y-p24_v_y = -0;
   p23_v_z-p24_v_z = -0;
   0.707106781187*p23_u_x+0.707106781187*p23_w_x-0.707106781187*p23_wp_x-w1_p23_p24_x_5 = -0;
   0.707106781187*p23_u_y+0.707106781187*p23_w_y-0.707106781187*p23_wp_y-w1_p23_p24_y_5 = -0;
   0.707106781187*p23_u_z+0.707106781187*p23_w_z-0.707106781187*p23_wp_z-w1_p23_p24_z_5 = -0;
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
   w1_palm_p32_y_6 = -0.999370208806;
   w1_palm_p32_z_6 = -0.0354850074141;
   0.707106781187*p32_u_x+0.707106781187*p32_w_x-0.707106781187*p32_wp_x-w2_palm_p32_x_6 = -0;
   0.707106781187*p32_u_y+0.707106781187*p32_w_y-0.707106781187*p32_wp_y-w2_palm_p32_y_6 = -0;
   0.707106781187*p32_u_z+0.707106781187*p32_w_z-0.707106781187*p32_wp_z-w2_palm_p32_z_6 = -0;
   uni_v_palm_p32_x_6*w1_palm_p32_x_6+uni_v_palm_p32_y_6*w1_palm_p32_y_6+uni_v_palm_p32_z_6*w1_palm_p32_z_6-cos_0_palm_p32_6 = 0;
   uni_u_palm_p32_x_6*w2_palm_p32_x_6+uni_u_palm_p32_y_6*w2_palm_p32_y_6+uni_u_palm_p32_z_6*w2_palm_p32_z_6-cos_1_palm_p32_6 = 0;
   p32_v_x-p33_v_x = -0;
   p32_v_y-p33_v_y = -0;
   p32_v_z-p33_v_z = -0;
   0.707106781187*p32_u_x+0.707106781187*p32_w_x-0.707106781187*p32_wp_x-w1_p32_p33_x_7 = -0;
   0.707106781187*p32_u_y+0.707106781187*p32_w_y-0.707106781187*p32_wp_y-w1_p32_p33_y_7 = -0;
   0.707106781187*p32_u_z+0.707106781187*p32_w_z-0.707106781187*p32_wp_z-w1_p32_p33_z_7 = -0;
   p33_u_x-w2_p32_p33_x_7 = -0;
   p33_u_y-w2_p32_p33_y_7 = -0;
   p33_u_z-w2_p32_p33_z_7 = -0;
   w1_p32_p33_x_7*w2_p32_p33_x_7+w1_p32_p33_y_7*w2_p32_p33_y_7+w1_p32_p33_z_7*w2_p32_p33_z_7-cos_p32_p33_7 = 0;
   p33_v_x-p34_v_x = -0;
   p33_v_y-p34_v_y = -0;
   p33_v_z-p34_v_z = -0;
   0.707106781187*p33_u_x+0.707106781187*p33_w_x-0.707106781187*p33_wp_x-w1_p33_p34_x_8 = -0;
   0.707106781187*p33_u_y+0.707106781187*p33_w_y-0.707106781187*p33_wp_y-w1_p33_p34_y_8 = -0;
   0.707106781187*p33_u_z+0.707106781187*p33_w_z-0.707106781187*p33_wp_z-w1_p33_p34_z_8 = -0;
   p34_u_x-w2_p33_p34_x_8 = -0;
   p34_u_y-w2_p33_p34_y_8 = -0;
   p34_u_z-w2_p33_p34_z_8 = -0;
   w1_p33_p34_x_8*w2_p33_p34_x_8+w1_p33_p34_y_8*w2_p33_p34_y_8+w1_p33_p34_z_8*w2_p33_p34_z_8-cos_p33_p34_8 = 0;
   p40_u_x = 0;
   p40_u_y = 0;
   p40_u_z = 1;
   w1_palm_p40_x_9 = 0;
   w1_palm_p40_y_9 = -1;
   w1_palm_p40_z_9 = 0;
   p40_w_x-p40_wp_x-w2_palm_p40_x_9 = -0;
   p40_w_y-p40_wp_y-w2_palm_p40_y_9 = -0;
   p40_w_z-p40_wp_z-w2_palm_p40_z_9 = -0;
   w1_palm_p40_x_9*w2_palm_p40_x_9+w1_palm_p40_y_9*w2_palm_p40_y_9+w1_palm_p40_z_9*w2_palm_p40_z_9-cos_palm_p40_9 = 0;
   0.573579788091*p40_u_x+0.819149697365*p40_w_x-0.819149697365*p40_wp_x-uni_u_p40_p42_x_10 = 0;
   0.573579788091*p40_u_y+0.819149697365*p40_w_y-0.819149697365*p40_wp_y-uni_u_p40_p42_y_10 = 0;
   0.573579788091*p40_u_z+0.819149697365*p40_w_z-0.819149697365*p40_wp_z-uni_u_p40_p42_z_10 = 0;
   p42_v_x-uni_v_p40_p42_x_10 = 0;
   p42_v_y-uni_v_p40_p42_y_10 = 0;
   p42_v_z-uni_v_p40_p42_z_10 = 0;
   uni_u_p40_p42_x_10*uni_v_p40_p42_x_10+uni_u_p40_p42_y_10*uni_v_p40_p42_y_10+uni_u_p40_p42_z_10*uni_v_p40_p42_z_10 = 0;
   p40_v_x-w1_p40_p42_x_10 = -0;
   p40_v_y-w1_p40_p42_y_10 = -0;
   p40_v_z-w1_p40_p42_z_10 = -0;
   p42_w_x-p42_wp_x-w2_p40_p42_x_10 = -0;
   p42_w_y-p42_wp_y-w2_p40_p42_y_10 = -0;
   p42_w_z-p42_wp_z-w2_p40_p42_z_10 = -0;
   uni_v_p40_p42_x_10*w1_p40_p42_x_10+uni_v_p40_p42_y_10*w1_p40_p42_y_10+uni_v_p40_p42_z_10*w1_p40_p42_z_10-cos_0_p40_p42_10 = 0;
   uni_u_p40_p42_x_10*w2_p40_p42_x_10+uni_u_p40_p42_y_10*w2_p40_p42_y_10+uni_u_p40_p42_z_10*w2_p40_p42_z_10-cos_1_p40_p42_10 = 0;
   p42_v_x-p43_v_x = -0;
   p42_v_y-p43_v_y = -0;
   p42_v_z-p43_v_z = -0;
   p42_u_x-w1_p42_p43_x_11 = -0;
   p42_u_y-w1_p42_p43_y_11 = -0;
   p42_u_z-w1_p42_p43_z_11 = -0;
   p43_u_x-w2_p42_p43_x_11 = -0;
   p43_u_y-w2_p42_p43_y_11 = -0;
   p43_u_z-w2_p42_p43_z_11 = -0;
   w1_p42_p43_x_11*w2_p42_p43_x_11+w1_p42_p43_y_11*w2_p42_p43_y_11+w1_p42_p43_z_11*w2_p42_p43_z_11-cos_p42_p43_11 = 0;
   p43_v_x-p44_v_x = -0;
   p43_v_y-p44_v_y = -0;
   p43_v_z-p44_v_z = -0;
   p43_u_x-w1_p43_p44_x_12 = -0;
   p43_u_y-w1_p43_p44_y_12 = -0;
   p43_u_z-w1_p43_p44_z_12 = -0;
   p44_u_x-w2_p43_p44_x_12 = -0;
   p44_u_y-w2_p43_p44_y_12 = -0;
   p44_u_z-w2_p43_p44_z_12 = -0;
   w1_p43_p44_x_12*w2_p43_p44_x_12+w1_p43_p44_y_12*w2_p43_p44_y_12+w1_p43_p44_z_12*w2_p43_p44_z_12-cos_p43_p44_12 = 0;
   0.140021004726*p14_u_x+0.990148533421*p14_w_x-0.990148533421*p14_wp_x-sph_w1_p14_X_1_x_13 = -0;
   0.140021004726*p14_u_y+0.990148533421*p14_w_y-0.990148533421*p14_wp_y-sph_w1_p14_X_1_y_13 = -0;
   0.140021004726*p14_u_z+0.990148533421*p14_w_z-0.990148533421*p14_wp_z-sph_w1_p14_X_1_z_13 = -0;
   X_1_w_x-X_1_wp_x-sph_w2_p14_X_1_x_13 = -0;
   X_1_w_y-X_1_wp_y-sph_w2_p14_X_1_y_13 = -0;
   X_1_w_z-X_1_wp_z-sph_w2_p14_X_1_z_13 = -0;
   sph_w1_p14_X_1_x_13*sph_w2_p14_X_1_x_13+sph_w1_p14_X_1_y_13*sph_w2_p14_X_1_y_13+sph_w1_p14_X_1_z_13*sph_w2_p14_X_1_z_13-cos_p14_X_1_13 = 0;
   393.807391911*in_patch_X_1_object_u_14^2+222.178992984*in_patch_X_1_object_v_14^2-in_patch_X_1_object_l_14^2+20252.7183989*in_patch_X_1_object_u_14+14095.6431958*in_patch_X_1_object_v_14+466.198479171*in_patch_X_1_object_w_14 = -309423.009606;
   6.042184*object_u_x*in_patch_X_1_object_u_14+12.104014*object_u_x*in_patch_X_1_object_v_14-1.527356*object_v_x*in_patch_X_1_object_u_14-2.690918*object_v_x*in_patch_X_1_object_v_14+18.840557*object_w_x*in_patch_X_1_object_u_14+8.272291*object_w_x*in_patch_X_1_object_v_14-18.840557*object_wp_x*in_patch_X_1_object_u_14-8.272291*object_wp_x*in_patch_X_1_object_v_14+X_1_w_x*in_patch_X_1_object_l_14-X_1_wp_x*in_patch_X_1_object_l_14+301.673446*object_u_x+123.487436*object_v_x+450.740496*object_w_x-450.740496*object_wp_x = 0;
   6.042184*object_u_y*in_patch_X_1_object_u_14+12.104014*object_u_y*in_patch_X_1_object_v_14-1.527356*object_v_y*in_patch_X_1_object_u_14-2.690918*object_v_y*in_patch_X_1_object_v_14+18.840557*object_w_y*in_patch_X_1_object_u_14+8.272291*object_w_y*in_patch_X_1_object_v_14-18.840557*object_wp_y*in_patch_X_1_object_u_14-8.272291*object_wp_y*in_patch_X_1_object_v_14+X_1_w_y*in_patch_X_1_object_l_14-X_1_wp_y*in_patch_X_1_object_l_14+301.673446*object_u_y+123.487436*object_v_y+450.740496*object_w_y-450.740496*object_wp_y = 0;
   6.042184*object_u_z*in_patch_X_1_object_u_14+12.104014*object_u_z*in_patch_X_1_object_v_14-1.527356*object_v_z*in_patch_X_1_object_u_14-2.690918*object_v_z*in_patch_X_1_object_v_14+18.840557*object_w_z*in_patch_X_1_object_u_14+8.272291*object_w_z*in_patch_X_1_object_v_14-18.840557*object_wp_z*in_patch_X_1_object_u_14-8.272291*object_wp_z*in_patch_X_1_object_v_14+X_1_w_z*in_patch_X_1_object_l_14-X_1_wp_z*in_patch_X_1_object_l_14+301.673446*object_u_z+123.487436*object_v_z+450.740496*object_w_z-450.740496*object_wp_z = 0;
   0.140021004726*p24_u_x+0.990148533421*p24_w_x-0.990148533421*p24_wp_x-sph_w1_p24_X_2_x_15 = -0;
   0.140021004726*p24_u_y+0.990148533421*p24_w_y-0.990148533421*p24_wp_y-sph_w1_p24_X_2_y_15 = -0;
   0.140021004726*p24_u_z+0.990148533421*p24_w_z-0.990148533421*p24_wp_z-sph_w1_p24_X_2_z_15 = -0;
   X_2_w_x-X_2_wp_x-sph_w2_p24_X_2_x_15 = -0;
   X_2_w_y-X_2_wp_y-sph_w2_p24_X_2_y_15 = -0;
   X_2_w_z-X_2_wp_z-sph_w2_p24_X_2_z_15 = -0;
   sph_w1_p24_X_2_x_15*sph_w2_p24_X_2_x_15+sph_w1_p24_X_2_y_15*sph_w2_p24_X_2_y_15+sph_w1_p24_X_2_z_15*sph_w2_p24_X_2_z_15-cos_p24_X_2_15 = 0;
   433.903558139*in_patch_X_2_object_u_16^2+433.903558139*in_patch_X_2_object_v_16^2-in_patch_X_2_object_l_16^2+18345.4385175*in_patch_X_2_object_u_16+18345.4385175*in_patch_X_2_object_v_16+516.609546527*in_patch_X_2_object_w_16 = -353048.889221;
   9.370133*object_u_x*in_patch_X_2_object_u_16-9.370133*object_u_x*in_patch_X_2_object_v_16+6.585909*object_v_x*in_patch_X_2_object_u_16+6.585909*object_v_x*in_patch_X_2_object_v_16-17.399137*object_w_x*in_patch_X_2_object_u_16-17.399137*object_w_x*in_patch_X_2_object_v_16+17.399137*object_wp_x*in_patch_X_2_object_u_16+17.399137*object_wp_x*in_patch_X_2_object_v_16-X_2_w_x*in_patch_X_2_object_l_16+X_2_wp_x*in_patch_X_2_object_l_16-135.564496*object_v_x-578.507698*object_w_x+578.507698*object_wp_x = -0;
   9.370133*object_u_y*in_patch_X_2_object_u_16-9.370133*object_u_y*in_patch_X_2_object_v_16+6.585909*object_v_y*in_patch_X_2_object_u_16+6.585909*object_v_y*in_patch_X_2_object_v_16-17.399137*object_w_y*in_patch_X_2_object_u_16-17.399137*object_w_y*in_patch_X_2_object_v_16+17.399137*object_wp_y*in_patch_X_2_object_u_16+17.399137*object_wp_y*in_patch_X_2_object_v_16-X_2_w_y*in_patch_X_2_object_l_16+X_2_wp_y*in_patch_X_2_object_l_16-135.564496*object_v_y-578.507698*object_w_y+578.507698*object_wp_y = -0;
   9.370133*object_u_z*in_patch_X_2_object_u_16-9.370133*object_u_z*in_patch_X_2_object_v_16+6.585909*object_v_z*in_patch_X_2_object_u_16+6.585909*object_v_z*in_patch_X_2_object_v_16-17.399137*object_w_z*in_patch_X_2_object_u_16-17.399137*object_w_z*in_patch_X_2_object_v_16+17.399137*object_wp_z*in_patch_X_2_object_u_16+17.399137*object_wp_z*in_patch_X_2_object_v_16-X_2_w_z*in_patch_X_2_object_l_16+X_2_wp_z*in_patch_X_2_object_l_16-135.564496*object_v_z-578.507698*object_w_z+578.507698*object_wp_z = -0;
   0.140021004726*p34_u_x+0.990148533421*p34_w_x-0.990148533421*p34_wp_x-sph_w1_p34_X_3_x_17 = -0;
   0.140021004726*p34_u_y+0.990148533421*p34_w_y-0.990148533421*p34_wp_y-sph_w1_p34_X_3_y_17 = -0;
   0.140021004726*p34_u_z+0.990148533421*p34_w_z-0.990148533421*p34_wp_z-sph_w1_p34_X_3_z_17 = -0;
   X_3_w_x-X_3_wp_x-sph_w2_p34_X_3_x_17 = -0;
   X_3_w_y-X_3_wp_y-sph_w2_p34_X_3_y_17 = -0;
   X_3_w_z-X_3_wp_z-sph_w2_p34_X_3_z_17 = -0;
   sph_w1_p34_X_3_x_17*sph_w2_p34_X_3_x_17+sph_w1_p34_X_3_y_17*sph_w2_p34_X_3_y_17+sph_w1_p34_X_3_z_17*sph_w2_p34_X_3_z_17-cos_p34_X_3_17 = 0;
   222.178992984*in_patch_X_3_object_u_18^2+393.807391911*in_patch_X_3_object_v_18^2-in_patch_X_3_object_l_18^2+14095.6431958*in_patch_X_3_object_u_18+20252.7183989*in_patch_X_3_object_v_18+466.198479171*in_patch_X_3_object_w_18 = -309423.009606;
   12.104014*object_u_x*in_patch_X_3_object_u_18+6.042184*object_u_x*in_patch_X_3_object_v_18+2.690918*object_v_x*in_patch_X_3_object_u_18+1.527356*object_v_x*in_patch_X_3_object_v_18-8.272291*object_w_x*in_patch_X_3_object_u_18-18.840557*object_w_x*in_patch_X_3_object_v_18+8.272291*object_wp_x*in_patch_X_3_object_u_18+18.840557*object_wp_x*in_patch_X_3_object_v_18-X_3_w_x*in_patch_X_3_object_l_18+X_3_wp_x*in_patch_X_3_object_l_18+301.673446*object_u_x-123.487436*object_v_x-450.740496*object_w_x+450.740496*object_wp_x = -0;
   12.104014*object_u_y*in_patch_X_3_object_u_18+6.042184*object_u_y*in_patch_X_3_object_v_18+2.690918*object_v_y*in_patch_X_3_object_u_18+1.527356*object_v_y*in_patch_X_3_object_v_18-8.272291*object_w_y*in_patch_X_3_object_u_18-18.840557*object_w_y*in_patch_X_3_object_v_18+8.272291*object_wp_y*in_patch_X_3_object_u_18+18.840557*object_wp_y*in_patch_X_3_object_v_18-X_3_w_y*in_patch_X_3_object_l_18+X_3_wp_y*in_patch_X_3_object_l_18+301.673446*object_u_y-123.487436*object_v_y-450.740496*object_w_y+450.740496*object_wp_y = -0;
   12.104014*object_u_z*in_patch_X_3_object_u_18+6.042184*object_u_z*in_patch_X_3_object_v_18+2.690918*object_v_z*in_patch_X_3_object_u_18+1.527356*object_v_z*in_patch_X_3_object_v_18-8.272291*object_w_z*in_patch_X_3_object_u_18-18.840557*object_w_z*in_patch_X_3_object_v_18+8.272291*object_wp_z*in_patch_X_3_object_u_18+18.840557*object_wp_z*in_patch_X_3_object_v_18-X_3_w_z*in_patch_X_3_object_l_18+X_3_wp_z*in_patch_X_3_object_l_18+301.673446*object_u_z-123.487436*object_v_z-450.740496*object_w_z+450.740496*object_wp_z = -0;
   sph_w1_palm_X_P_x_19 = 1;
   sph_w1_palm_X_P_y_19 = 0;
   sph_w1_palm_X_P_z_19 = 0;
   X_P_w_x-X_P_wp_x-sph_w2_palm_X_P_x_19 = -0;
   X_P_w_y-X_P_wp_y-sph_w2_palm_X_P_y_19 = -0;
   X_P_w_z-X_P_wp_z-sph_w2_palm_X_P_z_19 = -0;
   sph_w1_palm_X_P_x_19*sph_w2_palm_X_P_x_19+sph_w1_palm_X_P_y_19*sph_w2_palm_X_P_y_19+sph_w1_palm_X_P_z_19*sph_w2_palm_X_P_z_19-cos_palm_X_P_19 = 0;
   in_patch_X_P_object_l_20^2 = 88078306.4618;
   X_P_w_x*in_patch_X_P_object_l_20-X_P_wp_x*in_patch_X_P_object_l_20-9385.00434*object_v_x = 0;
   X_P_w_y*in_patch_X_P_object_l_20-X_P_wp_y*in_patch_X_P_object_l_20-9385.00434*object_v_y = 0;
   X_P_w_z*in_patch_X_P_object_l_20-X_P_wp_z*in_patch_X_P_object_l_20-9385.00434*object_v_z = 0;
   16.238*object_u_x*in_patch_X_1_object_u_14-12.034*object_u_x*in_patch_X_1_object_v_14-0.205*object_u_x*in_patch_X_1_object_w_14-18.143*object_u_x*in_patch_X_2_object_u_16+18.143*object_u_x*in_patch_X_2_object_v_16-15.943*object_v_x*in_patch_X_1_object_u_14-15.943*object_v_x*in_patch_X_1_object_v_14-0.959*object_v_x*in_patch_X_1_object_w_14+15.943*object_v_x*in_patch_X_2_object_u_16+15.943*object_v_x*in_patch_X_2_object_v_16+0.959*object_v_x*in_patch_X_2_object_w_16-6.5*object_w_x*in_patch_X_1_object_u_14+12.422*object_w_x*in_patch_X_1_object_v_14-0.012*object_w_x*in_patch_X_1_object_w_14-3.736*object_w_x*in_patch_X_2_object_u_16-3.736*object_w_x*in_patch_X_2_object_v_16+0.363*object_w_x*in_patch_X_2_object_w_16+6.5*object_wp_x*in_patch_X_1_object_u_14-12.422*object_wp_x*in_patch_X_1_object_v_14+0.012*object_wp_x*in_patch_X_1_object_w_14+3.736*object_wp_x*in_patch_X_2_object_u_16+3.736*object_wp_x*in_patch_X_2_object_v_16-0.363*object_wp_x*in_patch_X_2_object_w_16+67.8*p12_u_x+30*p13_u_x+20*p14_u_x-67.8*p22_u_x-30*p23_u_x-20*p24_u_x-51.188*object_u_x+15.356*object_w_x-15.356*object_wp_x+18*X_1_w_x-18*X_1_wp_x-18*X_2_w_x+18*X_2_wp_x = -0;
   16.238*object_u_y*in_patch_X_1_object_u_14-12.034*object_u_y*in_patch_X_1_object_v_14-0.205*object_u_y*in_patch_X_1_object_w_14-18.143*object_u_y*in_patch_X_2_object_u_16+18.143*object_u_y*in_patch_X_2_object_v_16-15.943*object_v_y*in_patch_X_1_object_u_14-15.943*object_v_y*in_patch_X_1_object_v_14-0.959*object_v_y*in_patch_X_1_object_w_14+15.943*object_v_y*in_patch_X_2_object_u_16+15.943*object_v_y*in_patch_X_2_object_v_16+0.959*object_v_y*in_patch_X_2_object_w_16-6.5*object_w_y*in_patch_X_1_object_u_14+12.422*object_w_y*in_patch_X_1_object_v_14-0.012*object_w_y*in_patch_X_1_object_w_14-3.736*object_w_y*in_patch_X_2_object_u_16-3.736*object_w_y*in_patch_X_2_object_v_16+0.363*object_w_y*in_patch_X_2_object_w_16+6.5*object_wp_y*in_patch_X_1_object_u_14-12.422*object_wp_y*in_patch_X_1_object_v_14+0.012*object_wp_y*in_patch_X_1_object_w_14+3.736*object_wp_y*in_patch_X_2_object_u_16+3.736*object_wp_y*in_patch_X_2_object_v_16-0.363*object_wp_y*in_patch_X_2_object_w_16+67.8*p12_u_y+30*p13_u_y+20*p14_u_y-67.8*p22_u_y-30*p23_u_y-20*p24_u_y-51.188*object_u_y+15.356*object_w_y-15.356*object_wp_y+18*X_1_w_y-18*X_1_wp_y-18*X_2_w_y+18*X_2_wp_y = 40.165;
   16.238*object_u_z*in_patch_X_1_object_u_14-12.034*object_u_z*in_patch_X_1_object_v_14-0.205*object_u_z*in_patch_X_1_object_w_14-18.143*object_u_z*in_patch_X_2_object_u_16+18.143*object_u_z*in_patch_X_2_object_v_16-15.943*object_v_z*in_patch_X_1_object_u_14-15.943*object_v_z*in_patch_X_1_object_v_14-0.959*object_v_z*in_patch_X_1_object_w_14+15.943*object_v_z*in_patch_X_2_object_u_16+15.943*object_v_z*in_patch_X_2_object_v_16+0.959*object_v_z*in_patch_X_2_object_w_16-6.5*object_w_z*in_patch_X_1_object_u_14+12.422*object_w_z*in_patch_X_1_object_v_14-0.012*object_w_z*in_patch_X_1_object_w_14-3.736*object_w_z*in_patch_X_2_object_u_16-3.736*object_w_z*in_patch_X_2_object_v_16+0.363*object_w_z*in_patch_X_2_object_w_16+6.5*object_wp_z*in_patch_X_1_object_u_14-12.422*object_wp_z*in_patch_X_1_object_v_14+0.012*object_wp_z*in_patch_X_1_object_w_14+3.736*object_wp_z*in_patch_X_2_object_u_16+3.736*object_wp_z*in_patch_X_2_object_v_16-0.363*object_wp_z*in_patch_X_2_object_w_16+67.8*p12_u_z+30*p13_u_z+20*p14_u_z-67.8*p22_u_z-30*p23_u_z-20*p24_u_z-51.188*object_u_z+15.356*object_w_z-15.356*object_wp_z+18*X_1_w_z-18*X_1_wp_z-18*X_2_w_z+18*X_2_wp_z = 4.72;
   16.238*object_u_x*in_patch_X_1_object_u_14-12.034*object_u_x*in_patch_X_1_object_v_14-0.205*object_u_x*in_patch_X_1_object_w_14-12.034*object_u_x*in_patch_X_3_object_u_18+16.238*object_u_x*in_patch_X_3_object_v_18-0.205*object_u_x*in_patch_X_3_object_w_18-15.943*object_v_x*in_patch_X_1_object_u_14-15.943*object_v_x*in_patch_X_1_object_v_14-0.959*object_v_x*in_patch_X_1_object_w_14+15.943*object_v_x*in_patch_X_3_object_u_18+15.943*object_v_x*in_patch_X_3_object_v_18+0.959*object_v_x*in_patch_X_3_object_w_18-6.5*object_w_x*in_patch_X_1_object_u_14+12.422*object_w_x*in_patch_X_1_object_v_14-0.012*object_w_x*in_patch_X_1_object_w_14-12.422*object_w_x*in_patch_X_3_object_u_18+6.5*object_w_x*in_patch_X_3_object_v_18+0.012*object_w_x*in_patch_X_3_object_w_18+6.5*object_wp_x*in_patch_X_1_object_u_14-12.422*object_wp_x*in_patch_X_1_object_v_14+0.012*object_wp_x*in_patch_X_1_object_w_14+12.422*object_wp_x*in_patch_X_3_object_u_18-6.5*object_wp_x*in_patch_X_3_object_v_18-0.012*object_wp_x*in_patch_X_3_object_w_18+67.8*p12_u_x+30*p13_u_x+20*p14_u_x-67.8*p32_u_x-30*p33_u_x-20*p34_u_x-102.376*object_u_x+18*X_1_w_x-18*X_1_wp_x-18*X_3_w_x+18*X_3_wp_x = -0;
   16.238*object_u_y*in_patch_X_1_object_u_14-12.034*object_u_y*in_patch_X_1_object_v_14-0.205*object_u_y*in_patch_X_1_object_w_14-12.034*object_u_y*in_patch_X_3_object_u_18+16.238*object_u_y*in_patch_X_3_object_v_18-0.205*object_u_y*in_patch_X_3_object_w_18-15.943*object_v_y*in_patch_X_1_object_u_14-15.943*object_v_y*in_patch_X_1_object_v_14-0.959*object_v_y*in_patch_X_1_object_w_14+15.943*object_v_y*in_patch_X_3_object_u_18+15.943*object_v_y*in_patch_X_3_object_v_18+0.959*object_v_y*in_patch_X_3_object_w_18-6.5*object_w_y*in_patch_X_1_object_u_14+12.422*object_w_y*in_patch_X_1_object_v_14-0.012*object_w_y*in_patch_X_1_object_w_14-12.422*object_w_y*in_patch_X_3_object_u_18+6.5*object_w_y*in_patch_X_3_object_v_18+0.012*object_w_y*in_patch_X_3_object_w_18+6.5*object_wp_y*in_patch_X_1_object_u_14-12.422*object_wp_y*in_patch_X_1_object_v_14+0.012*object_wp_y*in_patch_X_1_object_w_14+12.422*object_wp_y*in_patch_X_3_object_u_18-6.5*object_wp_y*in_patch_X_3_object_v_18-0.012*object_wp_y*in_patch_X_3_object_w_18+67.8*p12_u_y+30*p13_u_y+20*p14_u_y-67.8*p32_u_y-30*p33_u_y-20*p34_u_y-102.376*object_u_y+18*X_1_w_y-18*X_1_wp_y-18*X_3_w_y+18*X_3_wp_y = 80.33;
   16.238*object_u_z*in_patch_X_1_object_u_14-12.034*object_u_z*in_patch_X_1_object_v_14-0.205*object_u_z*in_patch_X_1_object_w_14-12.034*object_u_z*in_patch_X_3_object_u_18+16.238*object_u_z*in_patch_X_3_object_v_18-0.205*object_u_z*in_patch_X_3_object_w_18-15.943*object_v_z*in_patch_X_1_object_u_14-15.943*object_v_z*in_patch_X_1_object_v_14-0.959*object_v_z*in_patch_X_1_object_w_14+15.943*object_v_z*in_patch_X_3_object_u_18+15.943*object_v_z*in_patch_X_3_object_v_18+0.959*object_v_z*in_patch_X_3_object_w_18-6.5*object_w_z*in_patch_X_1_object_u_14+12.422*object_w_z*in_patch_X_1_object_v_14-0.012*object_w_z*in_patch_X_1_object_w_14-12.422*object_w_z*in_patch_X_3_object_u_18+6.5*object_w_z*in_patch_X_3_object_v_18+0.012*object_w_z*in_patch_X_3_object_w_18+6.5*object_wp_z*in_patch_X_1_object_u_14-12.422*object_wp_z*in_patch_X_1_object_v_14+0.012*object_wp_z*in_patch_X_1_object_w_14+12.422*object_wp_z*in_patch_X_3_object_u_18-6.5*object_wp_z*in_patch_X_3_object_v_18-0.012*object_wp_z*in_patch_X_3_object_w_18+67.8*p12_u_z+30*p13_u_z+20*p14_u_z-67.8*p32_u_z-30*p33_u_z-20*p34_u_z-102.376*object_u_z+18*X_1_w_z-18*X_1_wp_z-18*X_3_w_z+18*X_3_wp_z = -0;
   16.238*object_u_x*in_patch_X_1_object_u_14-12.034*object_u_x*in_patch_X_1_object_v_14-0.205*object_u_x*in_patch_X_1_object_w_14+18.342*object_u_x*in_patch_X_P_object_u_20-95.124*object_u_x*in_patch_X_P_object_v_20-15.943*object_v_x*in_patch_X_1_object_u_14-15.943*object_v_x*in_patch_X_1_object_v_14-0.959*object_v_x*in_patch_X_1_object_w_14-6.5*object_w_x*in_patch_X_1_object_u_14+12.422*object_w_x*in_patch_X_1_object_v_14-0.012*object_w_x*in_patch_X_1_object_w_14-95.124*object_w_x*in_patch_X_P_object_u_20-18.342*object_w_x*in_patch_X_P_object_v_20+6.5*object_wp_x*in_patch_X_1_object_u_14-12.422*object_wp_x*in_patch_X_1_object_v_14+0.012*object_wp_x*in_patch_X_1_object_w_14+95.124*object_wp_x*in_patch_X_P_object_u_20+18.342*object_wp_x*in_patch_X_P_object_v_20+67.8*p12_u_x+30*p13_u_x+20*p14_u_x-12.797*object_u_x-34.125*object_v_x-18.911*object_w_x+18.911*object_wp_x-18*X_P_w_x+18*X_P_wp_x+18*X_1_w_x-18*X_1_wp_x = 6.85;
   16.238*object_u_y*in_patch_X_1_object_u_14-12.034*object_u_y*in_patch_X_1_object_v_14-0.205*object_u_y*in_patch_X_1_object_w_14+18.342*object_u_y*in_patch_X_P_object_u_20-95.124*object_u_y*in_patch_X_P_object_v_20-15.943*object_v_y*in_patch_X_1_object_u_14-15.943*object_v_y*in_patch_X_1_object_v_14-0.959*object_v_y*in_patch_X_1_object_w_14-6.5*object_w_y*in_patch_X_1_object_u_14+12.422*object_w_y*in_patch_X_1_object_v_14-0.012*object_w_y*in_patch_X_1_object_w_14-95.124*object_w_y*in_patch_X_P_object_u_20-18.342*object_w_y*in_patch_X_P_object_v_20+6.5*object_wp_y*in_patch_X_1_object_u_14-12.422*object_wp_y*in_patch_X_1_object_v_14+0.012*object_wp_y*in_patch_X_1_object_w_14+95.124*object_wp_y*in_patch_X_P_object_u_20+18.342*object_wp_y*in_patch_X_P_object_v_20+67.8*p12_u_y+30*p13_u_y+20*p14_u_y-12.797*object_u_y-34.125*object_v_y-18.911*object_w_y+18.911*object_wp_y-18*X_P_w_y+18*X_P_wp_y+18*X_1_w_y-18*X_1_wp_y = 40.112;
   16.238*object_u_z*in_patch_X_1_object_u_14-12.034*object_u_z*in_patch_X_1_object_v_14-0.205*object_u_z*in_patch_X_1_object_w_14+18.342*object_u_z*in_patch_X_P_object_u_20-95.124*object_u_z*in_patch_X_P_object_v_20-15.943*object_v_z*in_patch_X_1_object_u_14-15.943*object_v_z*in_patch_X_1_object_v_14-0.959*object_v_z*in_patch_X_1_object_w_14-6.5*object_w_z*in_patch_X_1_object_u_14+12.422*object_w_z*in_patch_X_1_object_v_14-0.012*object_w_z*in_patch_X_1_object_w_14-95.124*object_w_z*in_patch_X_P_object_u_20-18.342*object_w_z*in_patch_X_P_object_v_20+6.5*object_wp_z*in_patch_X_1_object_u_14-12.422*object_wp_z*in_patch_X_1_object_v_14+0.012*object_wp_z*in_patch_X_1_object_w_14+95.124*object_wp_z*in_patch_X_P_object_u_20+18.342*object_wp_z*in_patch_X_P_object_v_20+67.8*p12_u_z+30*p13_u_z+20*p14_u_z-12.797*object_u_z-34.125*object_v_z-18.911*object_w_z+18.911*object_wp_z-18*X_P_w_z+18*X_P_wp_z+18*X_1_w_z-18*X_1_wp_z = -28.082;

% Equations added to couple the revolute joints in between phalanx
cos_p12_p13_1 - cos_p13_p14_2 = 0;
cos_p22_p23_4 - cos_p23_p24_5 = 0;
cos_p32_p33_7 - cos_p33_p34_8 = 0;
cos_p42_p43_11 - cos_p43_p44_12 = 0;

[COORD EQS]

   97*p40_u_x+6*p40_v_x-87*p40_w_x+87*p40_wp_x+67.8*p42_u_x+30*p43_u_x-p44_r_x = 3;
   97*p40_u_y+6*p40_v_y-87*p40_w_y+87*p40_wp_y+67.8*p42_u_y+30*p43_u_y-p44_r_y = -27.1;
   97*p40_u_z+6*p40_v_z-87*p40_w_z+87*p40_wp_z+67.8*p42_u_z+30*p43_u_z-p44_r_z = 0;

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
   p40_u_y*p40_v_z-p40_w_x = 0;
   p40_u_z*p40_v_x-p40_w_y = 0;
   p40_u_x*p40_v_y-p40_w_z = 0;
   p40_u_z*p40_v_y-p40_wp_x = 0;
   p40_u_x*p40_v_z-p40_wp_y = 0;
   p40_u_y*p40_v_x-p40_wp_z = 0;
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
   X_P_u_y*X_P_v_z-X_P_w_x = 0;
   X_P_u_z*X_P_v_x-X_P_w_y = 0;
   X_P_u_x*X_P_v_y-X_P_w_z = 0;
   X_P_u_z*X_P_v_y-X_P_wp_x = 0;
   X_P_u_x*X_P_v_z-X_P_wp_y = 0;
   X_P_u_y*X_P_v_x-X_P_wp_z = 0;
   X_1_u_y*X_1_v_z-X_1_w_x = 0;
   X_1_u_z*X_1_v_x-X_1_w_y = 0;
   X_1_u_x*X_1_v_y-X_1_w_z = 0;
   X_1_u_z*X_1_v_y-X_1_wp_x = 0;
   X_1_u_x*X_1_v_z-X_1_wp_y = 0;
   X_1_u_y*X_1_v_x-X_1_wp_z = 0;
   X_2_u_y*X_2_v_z-X_2_w_x = 0;
   X_2_u_z*X_2_v_x-X_2_w_y = 0;
   X_2_u_x*X_2_v_y-X_2_w_z = 0;
   X_2_u_z*X_2_v_y-X_2_wp_x = 0;
   X_2_u_x*X_2_v_z-X_2_wp_y = 0;
   X_2_u_y*X_2_v_x-X_2_wp_z = 0;
   X_3_u_y*X_3_v_z-X_3_w_x = 0;
   X_3_u_z*X_3_v_x-X_3_w_y = 0;
   X_3_u_x*X_3_v_y-X_3_w_z = 0;
   X_3_u_z*X_3_v_y-X_3_wp_x = 0;
   X_3_u_x*X_3_v_z-X_3_wp_y = 0;
   X_3_u_y*X_3_v_x-X_3_wp_z = 0;
   in_patch_X_1_object_u_14*in_patch_X_1_object_v_14-in_patch_X_1_object_w_14 = 0;
   in_patch_X_2_object_u_16*in_patch_X_2_object_v_16-in_patch_X_2_object_w_16 = 0;
   in_patch_X_3_object_u_18*in_patch_X_3_object_v_18-in_patch_X_3_object_w_18 = 0;
   in_patch_X_P_object_u_20*in_patch_X_P_object_v_20-in_patch_X_P_object_w_20 = 0;

[SEARCH]

 MIN 172.582639308*cos_0_palm_p12_0^2+11.6568542495*cos_1_palm_p12_0^2+11.6568542495*cos_p12_p13_1^2+11.6568542495*cos_p13_p14_2^2+172.582639308*cos_0_palm_p22_3^2+11.6568542495*cos_1_palm_p22_3^2+11.6568542495*cos_p22_p23_4^2+11.6568542495*cos_p23_p24_5^2+172.582639308*cos_0_palm_p32_6^2+11.6568542495*cos_1_palm_p32_6^2+11.6568542495*cos_p32_p33_7^2+11.6568542495*cos_p33_p34_8^2+cos_p14_X_1_13^2+4*in_patch_X_1_object_u_14^2+4*in_patch_X_1_object_v_14^2+cos_p24_X_2_15^2+4*in_patch_X_2_object_u_16^2+4*in_patch_X_2_object_v_16^2+cos_p34_X_3_17^2+4*in_patch_X_3_object_u_18^2+4*in_patch_X_3_object_v_18^2+cos_palm_X_P_19^2+4*in_patch_X_P_object_u_20^2+4*in_patch_X_P_object_v_20^2-345.165278616*cos_0_palm_p12_0-23.313708499*cos_1_palm_p12_0-23.313708499*cos_p12_p13_1-23.313708499*cos_p13_p14_2-345.165278616*cos_0_palm_p22_3-23.313708499*cos_1_palm_p22_3-23.313708499*cos_p22_p23_4-23.313708499*cos_p23_p24_5-345.165278616*cos_0_palm_p32_6-23.313708499*cos_1_palm_p32_6-23.313708499*cos_p32_p33_7-23.313708499*cos_p33_p34_8-2*cos_p14_X_1_13-4*in_patch_X_1_object_u_14-4*in_patch_X_1_object_v_14-2*cos_p24_X_2_15-4*in_patch_X_2_object_u_16-4*in_patch_X_2_object_v_16-2*cos_p34_X_3_17-4*in_patch_X_3_object_u_18-4*in_patch_X_3_object_v_18-2*cos_palm_X_P_19-4*in_patch_X_P_object_u_20-4*in_patch_X_P_object_v_20+634.659606169




==========================================================================
%****************************************
% Simplified system 
% SIMPLIFICATION_LEVEL: 3
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
%   p14_w_z=p14_w_z
%   p14_wp_x=p14_wp_x
%   p14_wp_y=p14_wp_y
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
%   p40_u_x= -0
%   p40_u_y= -0
%   p40_u_z= +1
%   p40_v_x= -1
%   p40_v_y= -0
%   p40_v_z= -0
%   p40_w_x= -0
%   p40_w_y= -1
%   p40_w_z= -0
%   p40_wp_x= -0
%   p40_wp_y= -0
%   p40_wp_z= -0
%   p42_u_x= -0
%   p42_u_y=-1.42813556958*p42_u_z +1.74343660771
%   p42_u_z=p42_u_z
%   p42_v_x= -1
%   p42_v_y= -0
%   p42_v_z= -0
%   p42_w_x= -0
%   p42_w_y=-p42_u_z -1.11022302463e-16
%   p42_w_z= -0
%   p42_wp_x= -0
%   p42_wp_y= -0
%   p42_wp_z=+1.42813556958*p42_u_z -1.74343660771
%   p43_u_x= -0
%   p43_u_y=p43_u_y
%   p43_u_z=p43_u_z
%   p43_v_x= -1
%   p43_v_y= -0
%   p43_v_z= -0
%   p43_w_x=No in simplification
%   p43_w_y=No in simplification
%   p43_w_z=No in simplification
%   p43_wp_x=No in simplification
%   p43_wp_y=No in simplification
%   p43_wp_z=No in simplification
%   p44_u_x= -0
%   p44_u_y=p44_u_y
%   p44_u_z=p44_u_z
%   p44_v_x= -1
%   p44_v_y= -0
%   p44_v_z= -0
%   p44_w_x=No in simplification
%   p44_w_y=No in simplification
%   p44_w_z=No in simplification
%   p44_wp_x=No in simplification
%   p44_wp_y=No in simplification
%   p44_wp_z=No in simplification
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
%   X_P_u_x=X_P_u_x
%   X_P_u_y=X_P_u_y
%   X_P_u_z=X_P_u_z
%   X_P_v_x=X_P_v_x
%   X_P_v_y=X_P_v_y
%   X_P_v_z=X_P_v_z
%   X_P_w_x=X_P_w_x
%   X_P_w_y=X_P_w_y
%   X_P_w_z=X_P_w_z
%   X_P_wp_x=X_P_wp_x
%   X_P_wp_y=X_P_wp_y
%   X_P_wp_z=X_P_wp_z
%   X_1_u_x=X_1_u_x
%   X_1_u_y=X_1_u_y
%   X_1_u_z=X_1_u_z
%   X_1_v_x=X_1_v_x
%   X_1_v_y=X_1_v_y
%   X_1_v_z=X_1_v_z
%   X_1_w_x=X_1_w_x
%   X_1_w_y=X_1_w_y
%   X_1_w_z=X_1_w_z
%   X_1_wp_x=X_1_wp_x
%   X_1_wp_y=X_1_wp_y
%   X_1_wp_z=X_1_wp_z
%   X_2_u_x=X_2_u_x
%   X_2_u_y=X_2_u_y
%   X_2_u_z=X_2_u_z
%   X_2_v_x=X_2_v_x
%   X_2_v_y=X_2_v_y
%   X_2_v_z=X_2_v_z
%   X_2_w_x=X_2_w_x
%   X_2_w_y=X_2_w_y
%   X_2_w_z=X_2_w_z
%   X_2_wp_x=X_2_wp_x
%   X_2_wp_y=X_2_wp_y
%   X_2_wp_z=X_2_wp_z
%   X_3_u_x=X_3_u_x
%   X_3_u_y=X_3_u_y
%   X_3_u_z=X_3_u_z
%   X_3_v_x=X_3_v_x
%   X_3_v_y=X_3_v_y
%   X_3_v_z=X_3_v_z
%   X_3_w_x=X_3_w_x
%   X_3_w_y=X_3_w_y
%   X_3_w_z=X_3_w_z
%   X_3_wp_x=X_3_wp_x
%   X_3_wp_y=X_3_wp_y
%   X_3_wp_z=X_3_wp_z
%   uni_u_palm_p12_x_0= +1
%   uni_u_palm_p12_y_0= -0
%   uni_u_palm_p12_z_0= -0
%   uni_v_palm_p12_x_0= -0
%   uni_v_palm_p12_y_0=p14_v_y
%   uni_v_palm_p12_z_0=p14_v_z
%   w1_palm_p12_x_0= -0
%   w1_palm_p12_y_0= -0.999411545741
%   w1_palm_p12_z_0= +0.0343010530517
%   w2_palm_p12_x_0=w1_p12_p13_x_1
%   w2_palm_p12_y_0=w1_p12_p13_y_1
%   w2_palm_p12_z_0=w1_p12_p13_z_1
%   cos_0_palm_p12_0=cos_0_palm_p12_0
%   cos_1_palm_p12_0=w1_p12_p13_x_1
%   w1_p12_p13_x_1=w1_p12_p13_x_1
%   w1_p12_p13_y_1=w1_p12_p13_y_1
%   w1_p12_p13_z_1=w1_p12_p13_z_1
%   w2_p12_p13_x_1=p13_u_x
%   w2_p12_p13_y_1=p13_u_y
%   w2_p12_p13_z_1=p13_u_z
%   cos_p12_p13_1=cos_p13_p14_2
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
%   cos_p22_p23_4=cos_p23_p24_5
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
%   w1_palm_p32_y_6= -0.999370208806
%   w1_palm_p32_z_6= -0.0354850074141
%   w2_palm_p32_x_6=w1_p32_p33_x_7
%   w2_palm_p32_y_6=w1_p32_p33_y_7
%   w2_palm_p32_z_6=w1_p32_p33_z_7
%   cos_0_palm_p32_6=cos_0_palm_p32_6
%   cos_1_palm_p32_6=w1_p32_p33_x_7
%   w1_p32_p33_x_7=w1_p32_p33_x_7
%   w1_p32_p33_y_7=w1_p32_p33_y_7
%   w1_p32_p33_z_7=w1_p32_p33_z_7
%   w2_p32_p33_x_7=p33_u_x
%   w2_p32_p33_y_7=p33_u_y
%   w2_p32_p33_z_7=p33_u_z
%   cos_p32_p33_7=cos_p33_p34_8
%   w1_p33_p34_x_8=w1_p33_p34_x_8
%   w1_p33_p34_y_8=w1_p33_p34_y_8
%   w1_p33_p34_z_8=w1_p33_p34_z_8
%   w2_p33_p34_x_8=p34_u_x
%   w2_p33_p34_y_8=p34_u_y
%   w2_p33_p34_z_8=p34_u_z
%   cos_p33_p34_8=cos_p33_p34_8
%   w1_palm_p40_x_9= -0
%   w1_palm_p40_y_9= -1
%   w1_palm_p40_z_9= -0
%   w2_palm_p40_x_9= -0
%   w2_palm_p40_y_9= -1
%   w2_palm_p40_z_9= -0
%   cos_palm_p40_9= +1
%   uni_u_p40_p42_x_10= -0
%   uni_u_p40_p42_y_10= -0.819149697365
%   uni_u_p40_p42_z_10= +0.573579788091
%   uni_v_p40_p42_x_10= -1
%   uni_v_p40_p42_y_10= -0
%   uni_v_p40_p42_z_10= -0
%   w1_p40_p42_x_10= -1
%   w1_p40_p42_y_10= -0
%   w1_p40_p42_z_10= -0
%   w2_p40_p42_x_10= -0
%   w2_p40_p42_y_10=-p42_u_z -1.11022302463e-16
%   w2_p40_p42_z_10=-1.42813556958*p42_u_z +1.74343660771
%   cos_0_p40_p42_10= +1
%   cos_1_p40_p42_10= +1
%   w1_p42_p43_x_11= -0
%   w1_p42_p43_y_11=-1.42813556958*p42_u_z +1.74343660771
%   w1_p42_p43_z_11=p42_u_z
%   w2_p42_p43_x_11= -0
%   w2_p42_p43_y_11=p43_u_y
%   w2_p42_p43_z_11=p43_u_z
%   cos_p42_p43_11= +1
%   w1_p43_p44_x_12= -0
%   w1_p43_p44_y_12=p43_u_y
%   w1_p43_p44_z_12=p43_u_z
%   w2_p43_p44_x_12= -0
%   w2_p43_p44_y_12=p44_u_y
%   w2_p43_p44_z_12=p44_u_z
%   cos_p43_p44_12= +1
%   sph_w1_p14_X_1_x_13=sph_w1_p14_X_1_x_13
%   sph_w1_p14_X_1_y_13=sph_w1_p14_X_1_y_13
%   sph_w1_p14_X_1_z_13=sph_w1_p14_X_1_z_13
%   sph_w2_p14_X_1_x_13=sph_w2_p14_X_1_x_13
%   sph_w2_p14_X_1_y_13=sph_w2_p14_X_1_y_13
%   sph_w2_p14_X_1_z_13=sph_w2_p14_X_1_z_13
%   cos_p14_X_1_13=cos_p14_X_1_13
%   in_patch_X_1_object_u_14=in_patch_X_1_object_u_14
%   in_patch_X_1_object_v_14=in_patch_X_1_object_v_14
%   in_patch_X_1_object_w_14=in_patch_X_1_object_w_14
%   in_patch_X_1_object_l_14=in_patch_X_1_object_l_14
%   sph_w1_p24_X_2_x_15=sph_w1_p24_X_2_x_15
%   sph_w1_p24_X_2_y_15=sph_w1_p24_X_2_y_15
%   sph_w1_p24_X_2_z_15=sph_w1_p24_X_2_z_15
%   sph_w2_p24_X_2_x_15=sph_w2_p24_X_2_x_15
%   sph_w2_p24_X_2_y_15=sph_w2_p24_X_2_y_15
%   sph_w2_p24_X_2_z_15=sph_w2_p24_X_2_z_15
%   cos_p24_X_2_15=cos_p24_X_2_15
%   in_patch_X_2_object_u_16=in_patch_X_2_object_u_16
%   in_patch_X_2_object_v_16=in_patch_X_2_object_v_16
%   in_patch_X_2_object_w_16=in_patch_X_2_object_w_16
%   in_patch_X_2_object_l_16=in_patch_X_2_object_l_16
%   sph_w1_p34_X_3_x_17=sph_w1_p34_X_3_x_17
%   sph_w1_p34_X_3_y_17=sph_w1_p34_X_3_y_17
%   sph_w1_p34_X_3_z_17=sph_w1_p34_X_3_z_17
%   sph_w2_p34_X_3_x_17=sph_w2_p34_X_3_x_17
%   sph_w2_p34_X_3_y_17=sph_w2_p34_X_3_y_17
%   sph_w2_p34_X_3_z_17=sph_w2_p34_X_3_z_17
%   cos_p34_X_3_17=cos_p34_X_3_17
%   in_patch_X_3_object_u_18=in_patch_X_3_object_u_18
%   in_patch_X_3_object_v_18=in_patch_X_3_object_v_18
%   in_patch_X_3_object_w_18=in_patch_X_3_object_w_18
%   in_patch_X_3_object_l_18=in_patch_X_3_object_l_18
%   sph_w1_palm_X_P_x_19= +1
%   sph_w1_palm_X_P_y_19= -0
%   sph_w1_palm_X_P_z_19= -0
%   sph_w2_palm_X_P_x_19=cos_palm_X_P_19
%   sph_w2_palm_X_P_y_19=sph_w2_palm_X_P_y_19
%   sph_w2_palm_X_P_z_19=sph_w2_palm_X_P_z_19
%   cos_palm_X_P_19=cos_palm_X_P_19
%   in_patch_X_P_object_u_20=in_patch_X_P_object_u_20
%   in_patch_X_P_object_v_20=in_patch_X_P_object_v_20
%   in_patch_X_P_object_w_20=No in simplification
%   in_patch_X_P_object_l_20=in_patch_X_P_object_l_20
%   p44_r_x= -9
%   p44_r_y=p44_r_y
%   p44_r_z=p44_r_z

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
   p14_v_y : [-1,1]
   p14_v_z : [-1,1]

[DUMMY VARS]
   p14_w_x : [-1,1]
   p14_w_z : [-1,1]
   p14_wp_x : [-1,1]
   p14_wp_y : [-1,1]

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
   p24_v_y : [-1,-0.923879532483]
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
   p34_v_y : [-1,1]
   p34_v_z : [-1,1]

[DUMMY VARS]
   p34_w_x : [-1,1]
   p34_w_z : [-1,1]
   p34_wp_x : [-1,1]
   p34_wp_y : [-1,1]

[SYSTEM VARS]
   p42_u_z : [0.520564450266,1]
   p43_u_y : [-1,1]
   p43_u_z : [-1,1]
   p44_u_y : [-1,1]
   p44_u_z : [-1,1]
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

[SYSTEM VARS]
   X_P_u_x : [-1,1]
   X_P_u_y : [-1,1]
   X_P_u_z : [-1,1]
   X_P_v_x : [-1,1]
   X_P_v_y : [-1,1]
   X_P_v_z : [-1,1]

[DUMMY VARS]
   X_P_w_x : [-1,1]
   X_P_w_y : [-1,1]
   X_P_w_z : [-1,1]
   X_P_wp_x : [-1,1]
   X_P_wp_y : [-1,1]
   X_P_wp_z : [-1,1]

[SYSTEM VARS]
   X_1_u_x : [-1,1]
   X_1_u_y : [-1,1]
   X_1_u_z : [-1,1]
   X_1_v_x : [-1,1]
   X_1_v_y : [-1,1]
   X_1_v_z : [-1,1]

[DUMMY VARS]
   X_1_w_x : [-1,1]
   X_1_w_y : [-1,1]
   X_1_w_z : [-1,1]
   X_1_wp_x : [-1,1]
   X_1_wp_y : [-1,1]
   X_1_wp_z : [-1,1]

[SYSTEM VARS]
   X_2_u_x : [-1,1]
   X_2_u_y : [-1,1]
   X_2_u_z : [-1,1]
   X_2_v_x : [-1,1]
   X_2_v_y : [-1,1]
   X_2_v_z : [-1,1]

[DUMMY VARS]
   X_2_w_x : [-1,1]
   X_2_w_y : [-1,1]
   X_2_w_z : [-1,1]
   X_2_wp_x : [-1,1]
   X_2_wp_y : [-1,1]
   X_2_wp_z : [-1,1]

[SYSTEM VARS]
   X_3_u_x : [-1,1]
   X_3_u_y : [-1,1]
   X_3_u_z : [-1,1]
   X_3_v_x : [-1,1]
   X_3_v_y : [-1,1]
   X_3_v_z : [-1,1]

[DUMMY VARS]
   X_3_w_x : [-1,1]
   X_3_w_y : [-1,1]
   X_3_w_z : [-1,1]
   X_3_wp_x : [-1,1]
   X_3_wp_y : [-1,1]
   X_3_wp_z : [-1,1]

[SECONDARY VARS]
   cos_0_palm_p12_0 : [0.923879532511,1]
   w1_p12_p13_x_1 : [0.707106781163,1]
   w1_p12_p13_y_1 : [-1,1]
   w1_p12_p13_z_1 : [-1,1]
   w1_p13_p14_x_2 : [-1,1]
   w1_p13_p14_y_2 : [-1,1]
   w1_p13_p14_z_2 : [-1,1]
   cos_p13_p14_2 : [0.707106781187,1]
   w1_p22_p23_x_4 : [0.707106781163,1]
   w1_p22_p23_y_4 : [-1,1]
   w1_p22_p23_z_4 : [-1,1]
   w1_p23_p24_x_5 : [-1,1]
   w1_p23_p24_y_5 : [-1,1]
   w1_p23_p24_z_5 : [-1,1]
   cos_p23_p24_5 : [0.707106781187,1]
   cos_0_palm_p32_6 : [0.923879532511,1]
   w1_p32_p33_x_7 : [0.707106781163,1]
   w1_p32_p33_y_7 : [-1,1]
   w1_p32_p33_z_7 : [-1,1]
   w1_p33_p34_x_8 : [-1,1]
   w1_p33_p34_y_8 : [-1,1]
   w1_p33_p34_z_8 : [-1,1]
   cos_p33_p34_8 : [0.707106781187,1]
   sph_w1_p14_X_1_x_13 : [-1,1]
   sph_w1_p14_X_1_y_13 : [-1,1]
   sph_w1_p14_X_1_z_13 : [-1,1]
   sph_w2_p14_X_1_x_13 : [-1,1]
   sph_w2_p14_X_1_y_13 : [-1,1]
   sph_w2_p14_X_1_z_13 : [-1,1]
   cos_p14_X_1_13 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_1_object_u_14 : [0,1]
   in_patch_X_1_object_v_14 : [0,1]

[DUMMY VARS]
   in_patch_X_1_object_w_14 : [0,1]

[SECONDARY VARS]
   in_patch_X_1_object_l_14 : [556.258042284,587.242331635]
   sph_w1_p24_X_2_x_15 : [-1,1]
   sph_w1_p24_X_2_y_15 : [-1,1]
   sph_w1_p24_X_2_z_15 : [-1,1]
   sph_w2_p24_X_2_x_15 : [-1,1]
   sph_w2_p24_X_2_y_15 : [-1,1]
   sph_w2_p24_X_2_z_15 : [-1,1]
   cos_p24_X_2_15 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_2_object_u_16 : [0,1]
   in_patch_X_2_object_v_16 : [0,1]

[DUMMY VARS]
   in_patch_X_2_object_w_16 : [0,1]

[SECONDARY VARS]
   in_patch_X_2_object_l_16 : [594.179172658,625.399218835]
   sph_w1_p34_X_3_x_17 : [-1,1]
   sph_w1_p34_X_3_y_17 : [-1,1]
   sph_w1_p34_X_3_z_17 : [-1,1]
   sph_w2_p34_X_3_x_17 : [-1,1]
   sph_w2_p34_X_3_y_17 : [-1,1]
   sph_w2_p34_X_3_z_17 : [-1,1]
   cos_p34_X_3_17 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_18 : [0,1]
   in_patch_X_3_object_v_18 : [0,1]

[DUMMY VARS]
   in_patch_X_3_object_w_18 : [0,1]

[SECONDARY VARS]
   in_patch_X_3_object_l_18 : [556.258042284,587.242331635]
   sph_w2_palm_X_P_y_19 : [-1,1]
   sph_w2_palm_X_P_z_19 : [-1,1]
   cos_palm_X_P_19 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_P_object_u_20 : [0,1]
   in_patch_X_P_object_v_20 : [0,1]

[SECONDARY VARS]
   in_patch_X_P_object_l_20 : [9385,9385.1]

[CARTESIAN VARS]
   p44_r_y : [-1666.19770271,1666.19770271]
   p44_r_z : [-1666.19770271,1666.19770271]

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
   dummy_p42_u_z_2 : [0,1]
   dummy_object_u_x_object_v_x : [-1,1]
   dummy_object_u_y_object_v_y : [-1,1]
   dummy_object_u_z_object_v_z : [-1,1]
   dummy_X_P_u_x_X_P_v_x : [-1,1]
   dummy_X_P_u_y_X_P_v_y : [-1,1]
   dummy_X_P_u_z_X_P_v_z : [-1,1]
   dummy_X_1_u_x_X_1_v_x : [-1,1]
   dummy_X_1_u_y_X_1_v_y : [-1,1]
   dummy_X_1_u_z_X_1_v_z : [-1,1]
   dummy_X_2_u_x_X_2_v_x : [-1,1]
   dummy_X_2_u_y_X_2_v_y : [-1,1]
   dummy_X_2_u_z_X_2_v_z : [-1,1]
   dummy_X_3_u_x_X_3_v_x : [-1,1]
   dummy_X_3_u_y_X_3_v_y : [-1,1]
   dummy_X_3_u_z_X_3_v_z : [-1,1]
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
   dummy_p42_u_z_p43_u_y : [-1,1]
   dummy_p42_u_z_p43_u_z : [-1,1]
   dummy_p43_u_y_p44_u_y : [-1,1]
   dummy_p43_u_z_p44_u_z : [-1,1]
   dummy_sph_w1_p14_X_1_x_13_sph_w2_p14_X_1_x_13 : [-1,1]
   dummy_sph_w1_p14_X_1_y_13_sph_w2_p14_X_1_y_13 : [-1,1]
   dummy_sph_w1_p14_X_1_z_13_sph_w2_p14_X_1_z_13 : [-1,1]
   dummy_in_patch_X_1_object_u_14_2 : [0,1]
   dummy_in_patch_X_1_object_v_14_2 : [0,1]
   dummy_in_patch_X_1_object_l_14_2 : [309423.009606,344853.556064]
   dummy_object_u_x_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_u_x_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_v_x_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_v_x_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_w_x_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_w_x_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_1_object_v_14 : [-1,1]
   dummy_X_1_w_x_in_patch_X_1_object_l_14 : [-587.242331635,587.242331635]
   dummy_X_1_wp_x_in_patch_X_1_object_l_14 : [-587.242331635,587.242331635]
   dummy_object_u_y_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_u_y_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_v_y_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_v_y_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_w_y_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_w_y_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_1_object_v_14 : [-1,1]
   dummy_X_1_w_y_in_patch_X_1_object_l_14 : [-587.242331635,587.242331635]
   dummy_X_1_wp_y_in_patch_X_1_object_l_14 : [-587.242331635,587.242331635]
   dummy_object_u_z_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_u_z_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_v_z_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_v_z_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_w_z_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_w_z_in_patch_X_1_object_v_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_1_object_u_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_1_object_v_14 : [-1,1]
   dummy_X_1_w_z_in_patch_X_1_object_l_14 : [-587.242331635,587.242331635]
   dummy_X_1_wp_z_in_patch_X_1_object_l_14 : [-587.242331635,587.242331635]
   dummy_sph_w1_p24_X_2_x_15_sph_w2_p24_X_2_x_15 : [-1,1]
   dummy_sph_w1_p24_X_2_y_15_sph_w2_p24_X_2_y_15 : [-1,1]
   dummy_sph_w1_p24_X_2_z_15_sph_w2_p24_X_2_z_15 : [-1,1]
   dummy_in_patch_X_2_object_u_16_2 : [0,1]
   dummy_in_patch_X_2_object_v_16_2 : [0,1]
   dummy_in_patch_X_2_object_l_16_2 : [353048.889221,391124.182919]
   dummy_object_u_x_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_u_x_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_v_x_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_v_x_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_w_x_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_w_x_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_2_object_v_16 : [-1,1]
   dummy_X_2_w_x_in_patch_X_2_object_l_16 : [-625.399218835,625.399218835]
   dummy_X_2_wp_x_in_patch_X_2_object_l_16 : [-625.399218835,625.399218835]
   dummy_object_u_y_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_u_y_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_v_y_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_v_y_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_w_y_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_w_y_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_2_object_v_16 : [-1,1]
   dummy_X_2_w_y_in_patch_X_2_object_l_16 : [-625.399218835,625.399218835]
   dummy_X_2_wp_y_in_patch_X_2_object_l_16 : [-625.399218835,625.399218835]
   dummy_object_u_z_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_u_z_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_v_z_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_v_z_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_w_z_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_w_z_in_patch_X_2_object_v_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_2_object_u_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_2_object_v_16 : [-1,1]
   dummy_X_2_w_z_in_patch_X_2_object_l_16 : [-625.399218835,625.399218835]
   dummy_X_2_wp_z_in_patch_X_2_object_l_16 : [-625.399218835,625.399218835]
   dummy_sph_w1_p34_X_3_x_17_sph_w2_p34_X_3_x_17 : [-1,1]
   dummy_sph_w1_p34_X_3_y_17_sph_w2_p34_X_3_y_17 : [-1,1]
   dummy_sph_w1_p34_X_3_z_17_sph_w2_p34_X_3_z_17 : [-1,1]
   dummy_in_patch_X_3_object_u_18_2 : [0,1]
   dummy_in_patch_X_3_object_v_18_2 : [0,1]
   dummy_in_patch_X_3_object_l_18_2 : [309423.009606,344853.556064]
   dummy_object_u_x_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_u_x_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_v_18 : [-1,1]
   dummy_X_3_w_x_in_patch_X_3_object_l_18 : [-587.242331635,587.242331635]
   dummy_X_3_wp_x_in_patch_X_3_object_l_18 : [-587.242331635,587.242331635]
   dummy_object_u_y_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_v_18 : [-1,1]
   dummy_X_3_w_y_in_patch_X_3_object_l_18 : [-587.242331635,587.242331635]
   dummy_X_3_wp_y_in_patch_X_3_object_l_18 : [-587.242331635,587.242331635]
   dummy_object_u_z_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_u_z_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_v_z_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_v_z_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_v_18 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_u_18 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_v_18 : [-1,1]
   dummy_X_3_w_z_in_patch_X_3_object_l_18 : [-587.242331635,587.242331635]
   dummy_X_3_wp_z_in_patch_X_3_object_l_18 : [-587.242331635,587.242331635]
   dummy_X_P_w_x_in_patch_X_P_object_l_20 : [-9385.1,9385.1]
   dummy_X_P_wp_x_in_patch_X_P_object_l_20 : [-9385.1,9385.1]
   dummy_X_P_w_y_in_patch_X_P_object_l_20 : [-9385.1,9385.1]
   dummy_X_P_wp_y_in_patch_X_P_object_l_20 : [-9385.1,9385.1]
   dummy_X_P_w_z_in_patch_X_P_object_l_20 : [-9385.1,9385.1]
   dummy_X_P_wp_z_in_patch_X_P_object_l_20 : [-9385.1,9385.1]
   dummy_object_u_x_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_u_x_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_v_x_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_w_x_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_w_x_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_w_x_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_wp_x_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_wp_x_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_u_y_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_u_y_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_v_y_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_w_y_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_w_y_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_w_y_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_wp_y_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_wp_y_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_u_z_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_u_z_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_v_z_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_w_z_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_w_z_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_w_z_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_wp_z_in_patch_X_2_object_w_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_wp_z_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_u_x_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_u_z_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_v_z_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_w_18 : [-1,1]
   dummy_object_u_x_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_v_x_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_w_x_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_u_y_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_v_y_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_w_y_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_u_z_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_v_z_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_w_z_in_patch_X_1_object_w_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_1_object_w_14 : [-1,1]

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
   4.97972766556*p42_u_z-3.0395712051*dummy_p42_u_z_2 = 2.0395712051;
   p43_u_y^2+p43_u_z^2 = 1;
   p44_u_y^2+p44_u_z^2 = 1;
   object_u_x^2+object_u_y^2+object_u_z^2 = 1;
   object_v_x^2+object_v_y^2+object_v_z^2 = 1;
   dummy_object_u_x_object_v_x+dummy_object_u_y_object_v_y+dummy_object_u_z_object_v_z = 0;
   X_P_u_x^2+X_P_u_y^2+X_P_u_z^2 = 1;
   X_P_v_x^2+X_P_v_y^2+X_P_v_z^2 = 1;
   dummy_X_P_u_x_X_P_v_x+dummy_X_P_u_y_X_P_v_y+dummy_X_P_u_z_X_P_v_z = 0;
   X_1_u_x^2+X_1_u_y^2+X_1_u_z^2 = 1;
   X_1_v_x^2+X_1_v_y^2+X_1_v_z^2 = 1;
   dummy_X_1_u_x_X_1_v_x+dummy_X_1_u_y_X_1_v_y+dummy_X_1_u_z_X_1_v_z = 0;
   X_2_u_x^2+X_2_u_y^2+X_2_u_z^2 = 1;
   X_2_v_x^2+X_2_v_y^2+X_2_v_z^2 = 1;
   dummy_X_2_u_x_X_2_v_x+dummy_X_2_u_y_X_2_v_y+dummy_X_2_u_z_X_2_v_z = 0;
   X_3_u_x^2+X_3_u_y^2+X_3_u_z^2 = 1;
   X_3_v_x^2+X_3_v_y^2+X_3_v_z^2 = 1;
   dummy_X_3_u_x_X_3_v_x+dummy_X_3_u_y_X_3_v_y+dummy_X_3_u_z_X_3_v_z = 0;
   0.999411545741*p14_v_y-0.0343010530517*p14_v_z+cos_0_palm_p12_0 = 0;
   0.707106781187*p12_u_x+0.707106781187*p12_w_x-0.707106781187*p12_wp_x-w1_p12_p13_x_1 = 0;
   0.707106781187*p12_u_y-0.707106781187*p12_wp_y-w1_p12_p13_y_1 = 0;
   0.707106781187*p12_u_z+0.707106781187*p12_w_z-w1_p12_p13_z_1 = 0;
   cos_p13_p14_2-dummy_p13_u_x_w1_p12_p13_x_1-dummy_p13_u_y_w1_p12_p13_y_1-dummy_p13_u_z_w1_p12_p13_z_1 = -0;
   0.707106781187*p13_u_x+0.707106781187*p13_w_x-0.707106781187*p13_wp_x-w1_p13_p14_x_2 = 0;
   0.707106781187*p13_u_y-0.707106781187*p13_wp_y-w1_p13_p14_y_2 = 0;
   0.707106781187*p13_u_z+0.707106781187*p13_w_z-w1_p13_p14_z_2 = 0;
   cos_p13_p14_2-dummy_p14_u_x_w1_p13_p14_x_2-dummy_p14_u_y_w1_p13_p14_y_2-dummy_p14_u_z_w1_p13_p14_z_2 = -0;
   0.707106781187*p22_u_x+0.707106781187*p22_w_x-0.707106781187*p22_wp_x-w1_p22_p23_x_4 = 0;
   0.707106781187*p22_u_y-0.707106781187*p22_wp_y-w1_p22_p23_y_4 = 0;
   0.707106781187*p22_u_z+0.707106781187*p22_w_z-w1_p22_p23_z_4 = 0;
   cos_p23_p24_5-dummy_p23_u_x_w1_p22_p23_x_4-dummy_p23_u_y_w1_p22_p23_y_4-dummy_p23_u_z_w1_p22_p23_z_4 = -0;
   0.707106781187*p23_u_x+0.707106781187*p23_w_x-0.707106781187*p23_wp_x-w1_p23_p24_x_5 = 0;
   0.707106781187*p23_u_y-0.707106781187*p23_wp_y-w1_p23_p24_y_5 = 0;
   0.707106781187*p23_u_z+0.707106781187*p23_w_z-w1_p23_p24_z_5 = 0;
   cos_p23_p24_5-dummy_p24_u_x_w1_p23_p24_x_5-dummy_p24_u_y_w1_p23_p24_y_5-dummy_p24_u_z_w1_p23_p24_z_5 = -0;
   0.999370208806*p34_v_y+0.0354850074141*p34_v_z+cos_0_palm_p32_6 = 0;
   0.707106781187*p32_u_x+0.707106781187*p32_w_x-0.707106781187*p32_wp_x-w1_p32_p33_x_7 = 0;
   0.707106781187*p32_u_y-0.707106781187*p32_wp_y-w1_p32_p33_y_7 = 0;
   0.707106781187*p32_u_z+0.707106781187*p32_w_z-w1_p32_p33_z_7 = 0;
   cos_p33_p34_8-dummy_p33_u_x_w1_p32_p33_x_7-dummy_p33_u_y_w1_p32_p33_y_7-dummy_p33_u_z_w1_p32_p33_z_7 = -0;
   0.707106781187*p33_u_x+0.707106781187*p33_w_x-0.707106781187*p33_wp_x-w1_p33_p34_x_8 = 0;
   0.707106781187*p33_u_y-0.707106781187*p33_wp_y-w1_p33_p34_y_8 = 0;
   0.707106781187*p33_u_z+0.707106781187*p33_w_z-w1_p33_p34_z_8 = 0;
   cos_p33_p34_8-dummy_p34_u_x_w1_p33_p34_x_8-dummy_p34_u_y_w1_p33_p34_y_8-dummy_p34_u_z_w1_p33_p34_z_8 = -0;
   1.74343660771*p43_u_y-1.42813556958*dummy_p42_u_z_p43_u_y+dummy_p42_u_z_p43_u_z = 1;
   dummy_p43_u_y_p44_u_y+dummy_p43_u_z_p44_u_z = 1;
   0.140021004726*p14_u_x+0.990148533421*p14_w_x-0.990148533421*p14_wp_x-sph_w1_p14_X_1_x_13 = 0;
   0.140021004726*p14_u_y-0.990148533421*p14_wp_y-sph_w1_p14_X_1_y_13 = 0;
   0.140021004726*p14_u_z+0.990148533421*p14_w_z-sph_w1_p14_X_1_z_13 = 0;
   X_1_w_x-X_1_wp_x-sph_w2_p14_X_1_x_13 = 0;
   X_1_w_y-X_1_wp_y-sph_w2_p14_X_1_y_13 = 0;
   X_1_w_z-X_1_wp_z-sph_w2_p14_X_1_z_13 = 0;
   cos_p14_X_1_13-dummy_sph_w1_p14_X_1_x_13_sph_w2_p14_X_1_x_13-dummy_sph_w1_p14_X_1_y_13_sph_w2_p14_X_1_y_13-dummy_sph_w1_p14_X_1_z_13_sph_w2_p14_X_1_z_13 = -0;
   20252.7183989*in_patch_X_1_object_u_14+14095.6431958*in_patch_X_1_object_v_14+466.198479171*in_patch_X_1_object_w_14+393.807391911*dummy_in_patch_X_1_object_u_14_2+222.178992984*dummy_in_patch_X_1_object_v_14_2-dummy_in_patch_X_1_object_l_14_2 = -309423.009606;
   301.673446*object_u_x+123.487436*object_v_x+450.740496*object_w_x-450.740496*object_wp_x+6.042184*dummy_object_u_x_in_patch_X_1_object_u_14+12.104014*dummy_object_u_x_in_patch_X_1_object_v_14-1.527356*dummy_object_v_x_in_patch_X_1_object_u_14-2.690918*dummy_object_v_x_in_patch_X_1_object_v_14+18.840557*dummy_object_w_x_in_patch_X_1_object_u_14+8.272291*dummy_object_w_x_in_patch_X_1_object_v_14-18.840557*dummy_object_wp_x_in_patch_X_1_object_u_14-8.272291*dummy_object_wp_x_in_patch_X_1_object_v_14+dummy_X_1_w_x_in_patch_X_1_object_l_14-dummy_X_1_wp_x_in_patch_X_1_object_l_14 = 0;
   301.673446*object_u_y+123.487436*object_v_y+450.740496*object_w_y-450.740496*object_wp_y+6.042184*dummy_object_u_y_in_patch_X_1_object_u_14+12.104014*dummy_object_u_y_in_patch_X_1_object_v_14-1.527356*dummy_object_v_y_in_patch_X_1_object_u_14-2.690918*dummy_object_v_y_in_patch_X_1_object_v_14+18.840557*dummy_object_w_y_in_patch_X_1_object_u_14+8.272291*dummy_object_w_y_in_patch_X_1_object_v_14-18.840557*dummy_object_wp_y_in_patch_X_1_object_u_14-8.272291*dummy_object_wp_y_in_patch_X_1_object_v_14+dummy_X_1_w_y_in_patch_X_1_object_l_14-dummy_X_1_wp_y_in_patch_X_1_object_l_14 = 0;
   301.673446*object_u_z+123.487436*object_v_z+450.740496*object_w_z-450.740496*object_wp_z+6.042184*dummy_object_u_z_in_patch_X_1_object_u_14+12.104014*dummy_object_u_z_in_patch_X_1_object_v_14-1.527356*dummy_object_v_z_in_patch_X_1_object_u_14-2.690918*dummy_object_v_z_in_patch_X_1_object_v_14+18.840557*dummy_object_w_z_in_patch_X_1_object_u_14+8.272291*dummy_object_w_z_in_patch_X_1_object_v_14-18.840557*dummy_object_wp_z_in_patch_X_1_object_u_14-8.272291*dummy_object_wp_z_in_patch_X_1_object_v_14+dummy_X_1_w_z_in_patch_X_1_object_l_14-dummy_X_1_wp_z_in_patch_X_1_object_l_14 = 0;
   0.140021004726*p24_u_x+0.990148533421*p24_w_x-0.990148533421*p24_wp_x-sph_w1_p24_X_2_x_15 = 0;
   0.140021004726*p24_u_y-0.990148533421*p24_wp_y-sph_w1_p24_X_2_y_15 = 0;
   0.140021004726*p24_u_z+0.990148533421*p24_w_z-sph_w1_p24_X_2_z_15 = 0;
   X_2_w_x-X_2_wp_x-sph_w2_p24_X_2_x_15 = 0;
   X_2_w_y-X_2_wp_y-sph_w2_p24_X_2_y_15 = 0;
   X_2_w_z-X_2_wp_z-sph_w2_p24_X_2_z_15 = 0;
   cos_p24_X_2_15-dummy_sph_w1_p24_X_2_x_15_sph_w2_p24_X_2_x_15-dummy_sph_w1_p24_X_2_y_15_sph_w2_p24_X_2_y_15-dummy_sph_w1_p24_X_2_z_15_sph_w2_p24_X_2_z_15 = -0;
   18345.4385175*in_patch_X_2_object_u_16+18345.4385175*in_patch_X_2_object_v_16+516.609546527*in_patch_X_2_object_w_16+433.903558139*dummy_in_patch_X_2_object_u_16_2+433.903558139*dummy_in_patch_X_2_object_v_16_2-dummy_in_patch_X_2_object_l_16_2 = -353048.889221;
   135.564496*object_v_x+578.507698*object_w_x-578.507698*object_wp_x-9.370133*dummy_object_u_x_in_patch_X_2_object_u_16+9.370133*dummy_object_u_x_in_patch_X_2_object_v_16-6.585909*dummy_object_v_x_in_patch_X_2_object_u_16-6.585909*dummy_object_v_x_in_patch_X_2_object_v_16+17.399137*dummy_object_w_x_in_patch_X_2_object_u_16+17.399137*dummy_object_w_x_in_patch_X_2_object_v_16-17.399137*dummy_object_wp_x_in_patch_X_2_object_u_16-17.399137*dummy_object_wp_x_in_patch_X_2_object_v_16+dummy_X_2_w_x_in_patch_X_2_object_l_16-dummy_X_2_wp_x_in_patch_X_2_object_l_16 = -0;
   135.564496*object_v_y+578.507698*object_w_y-578.507698*object_wp_y-9.370133*dummy_object_u_y_in_patch_X_2_object_u_16+9.370133*dummy_object_u_y_in_patch_X_2_object_v_16-6.585909*dummy_object_v_y_in_patch_X_2_object_u_16-6.585909*dummy_object_v_y_in_patch_X_2_object_v_16+17.399137*dummy_object_w_y_in_patch_X_2_object_u_16+17.399137*dummy_object_w_y_in_patch_X_2_object_v_16-17.399137*dummy_object_wp_y_in_patch_X_2_object_u_16-17.399137*dummy_object_wp_y_in_patch_X_2_object_v_16+dummy_X_2_w_y_in_patch_X_2_object_l_16-dummy_X_2_wp_y_in_patch_X_2_object_l_16 = -0;
   135.564496*object_v_z+578.507698*object_w_z-578.507698*object_wp_z-9.370133*dummy_object_u_z_in_patch_X_2_object_u_16+9.370133*dummy_object_u_z_in_patch_X_2_object_v_16-6.585909*dummy_object_v_z_in_patch_X_2_object_u_16-6.585909*dummy_object_v_z_in_patch_X_2_object_v_16+17.399137*dummy_object_w_z_in_patch_X_2_object_u_16+17.399137*dummy_object_w_z_in_patch_X_2_object_v_16-17.399137*dummy_object_wp_z_in_patch_X_2_object_u_16-17.399137*dummy_object_wp_z_in_patch_X_2_object_v_16+dummy_X_2_w_z_in_patch_X_2_object_l_16-dummy_X_2_wp_z_in_patch_X_2_object_l_16 = -0;
   0.140021004726*p34_u_x+0.990148533421*p34_w_x-0.990148533421*p34_wp_x-sph_w1_p34_X_3_x_17 = 0;
   0.140021004726*p34_u_y-0.990148533421*p34_wp_y-sph_w1_p34_X_3_y_17 = 0;
   0.140021004726*p34_u_z+0.990148533421*p34_w_z-sph_w1_p34_X_3_z_17 = 0;
   X_3_w_x-X_3_wp_x-sph_w2_p34_X_3_x_17 = 0;
   X_3_w_y-X_3_wp_y-sph_w2_p34_X_3_y_17 = 0;
   X_3_w_z-X_3_wp_z-sph_w2_p34_X_3_z_17 = 0;
   cos_p34_X_3_17-dummy_sph_w1_p34_X_3_x_17_sph_w2_p34_X_3_x_17-dummy_sph_w1_p34_X_3_y_17_sph_w2_p34_X_3_y_17-dummy_sph_w1_p34_X_3_z_17_sph_w2_p34_X_3_z_17 = -0;
   14095.6431958*in_patch_X_3_object_u_18+20252.7183989*in_patch_X_3_object_v_18+466.198479171*in_patch_X_3_object_w_18+222.178992984*dummy_in_patch_X_3_object_u_18_2+393.807391911*dummy_in_patch_X_3_object_v_18_2-dummy_in_patch_X_3_object_l_18_2 = -309423.009606;
   301.673446*object_u_x-123.487436*object_v_x-450.740496*object_w_x+450.740496*object_wp_x+12.104014*dummy_object_u_x_in_patch_X_3_object_u_18+6.042184*dummy_object_u_x_in_patch_X_3_object_v_18+2.690918*dummy_object_v_x_in_patch_X_3_object_u_18+1.527356*dummy_object_v_x_in_patch_X_3_object_v_18-8.272291*dummy_object_w_x_in_patch_X_3_object_u_18-18.840557*dummy_object_w_x_in_patch_X_3_object_v_18+8.272291*dummy_object_wp_x_in_patch_X_3_object_u_18+18.840557*dummy_object_wp_x_in_patch_X_3_object_v_18-dummy_X_3_w_x_in_patch_X_3_object_l_18+dummy_X_3_wp_x_in_patch_X_3_object_l_18 = 0;
   301.673446*object_u_y-123.487436*object_v_y-450.740496*object_w_y+450.740496*object_wp_y+12.104014*dummy_object_u_y_in_patch_X_3_object_u_18+6.042184*dummy_object_u_y_in_patch_X_3_object_v_18+2.690918*dummy_object_v_y_in_patch_X_3_object_u_18+1.527356*dummy_object_v_y_in_patch_X_3_object_v_18-8.272291*dummy_object_w_y_in_patch_X_3_object_u_18-18.840557*dummy_object_w_y_in_patch_X_3_object_v_18+8.272291*dummy_object_wp_y_in_patch_X_3_object_u_18+18.840557*dummy_object_wp_y_in_patch_X_3_object_v_18-dummy_X_3_w_y_in_patch_X_3_object_l_18+dummy_X_3_wp_y_in_patch_X_3_object_l_18 = 0;
   301.673446*object_u_z-123.487436*object_v_z-450.740496*object_w_z+450.740496*object_wp_z+12.104014*dummy_object_u_z_in_patch_X_3_object_u_18+6.042184*dummy_object_u_z_in_patch_X_3_object_v_18+2.690918*dummy_object_v_z_in_patch_X_3_object_u_18+1.527356*dummy_object_v_z_in_patch_X_3_object_v_18-8.272291*dummy_object_w_z_in_patch_X_3_object_u_18-18.840557*dummy_object_w_z_in_patch_X_3_object_v_18+8.272291*dummy_object_wp_z_in_patch_X_3_object_u_18+18.840557*dummy_object_wp_z_in_patch_X_3_object_v_18-dummy_X_3_w_z_in_patch_X_3_object_l_18+dummy_X_3_wp_z_in_patch_X_3_object_l_18 = 0;
   X_P_w_x-X_P_wp_x-cos_palm_X_P_19 = 0;
   X_P_w_y-X_P_wp_y-sph_w2_palm_X_P_y_19 = 0;
   X_P_w_z-X_P_wp_z-sph_w2_palm_X_P_z_19 = 0;
   in_patch_X_P_object_l_20^2 = 88078306.4618;
   9385.00434*object_v_x-dummy_X_P_w_x_in_patch_X_P_object_l_20+dummy_X_P_wp_x_in_patch_X_P_object_l_20 = -0;
   9385.00434*object_v_y-dummy_X_P_w_y_in_patch_X_P_object_l_20+dummy_X_P_wp_y_in_patch_X_P_object_l_20 = -0;
   9385.00434*object_v_z-dummy_X_P_w_z_in_patch_X_P_object_l_20+dummy_X_P_wp_z_in_patch_X_P_object_l_20 = -0;
   67.8*p22_u_x+30*p23_u_x+20*p24_u_x+38.391*object_u_x-63.2338550574*object_v_x-158.486078206*object_w_x+158.486078206*object_wp_x+18*sph_w2_p24_X_2_x_15-18*cos_palm_X_P_19+20.1549858179*dummy_object_u_x_in_patch_X_2_object_u_16-20.1549858179*dummy_object_u_x_in_patch_X_2_object_v_16-14.5288519291*dummy_object_v_x_in_patch_X_2_object_u_16-14.5288519291*dummy_object_v_x_in_patch_X_2_object_v_16-0.21472329346*dummy_X_2_w_x_in_patch_X_2_object_l_16+0.21472329346*dummy_X_2_wp_x_in_patch_X_2_object_l_16+18.342*dummy_object_u_x_in_patch_X_P_object_u_20-95.124*dummy_object_u_x_in_patch_X_P_object_v_20-0.959*dummy_object_v_x_in_patch_X_2_object_w_16-0.363*dummy_object_w_x_in_patch_X_2_object_w_16-95.124*dummy_object_w_x_in_patch_X_P_object_u_20-18.342*dummy_object_w_x_in_patch_X_P_object_v_20+0.363*dummy_object_wp_x_in_patch_X_2_object_w_16+95.124*dummy_object_wp_x_in_patch_X_P_object_u_20+18.342*dummy_object_wp_x_in_patch_X_P_object_v_20 = 6.85;
   67.8*p22_u_y+30*p23_u_y+20*p24_u_y+38.391*object_u_y-63.2338550574*object_v_y-158.486078206*object_w_y+158.486078206*object_wp_y+18*sph_w2_p24_X_2_y_15-18*sph_w2_palm_X_P_y_19+20.1549858179*dummy_object_u_y_in_patch_X_2_object_u_16-20.1549858179*dummy_object_u_y_in_patch_X_2_object_v_16-14.5288519291*dummy_object_v_y_in_patch_X_2_object_u_16-14.5288519291*dummy_object_v_y_in_patch_X_2_object_v_16-0.21472329346*dummy_X_2_w_y_in_patch_X_2_object_l_16+0.21472329346*dummy_X_2_wp_y_in_patch_X_2_object_l_16+18.342*dummy_object_u_y_in_patch_X_P_object_u_20-95.124*dummy_object_u_y_in_patch_X_P_object_v_20-0.959*dummy_object_v_y_in_patch_X_2_object_w_16-0.363*dummy_object_w_y_in_patch_X_2_object_w_16-95.124*dummy_object_w_y_in_patch_X_P_object_u_20-18.342*dummy_object_w_y_in_patch_X_P_object_v_20+0.363*dummy_object_wp_y_in_patch_X_2_object_w_16+95.124*dummy_object_wp_y_in_patch_X_P_object_u_20+18.342*dummy_object_wp_y_in_patch_X_P_object_v_20 = -0.053;
   67.8*p22_u_z+30*p23_u_z+20*p24_u_z+38.391*object_u_z-63.2338550574*object_v_z-158.486078206*object_w_z+158.486078206*object_wp_z+18*sph_w2_p24_X_2_z_15-18*sph_w2_palm_X_P_z_19+20.1549858179*dummy_object_u_z_in_patch_X_2_object_u_16-20.1549858179*dummy_object_u_z_in_patch_X_2_object_v_16-14.5288519291*dummy_object_v_z_in_patch_X_2_object_u_16-14.5288519291*dummy_object_v_z_in_patch_X_2_object_v_16-0.21472329346*dummy_X_2_w_z_in_patch_X_2_object_l_16+0.21472329346*dummy_X_2_wp_z_in_patch_X_2_object_l_16+18.342*dummy_object_u_z_in_patch_X_P_object_u_20-95.124*dummy_object_u_z_in_patch_X_P_object_v_20-0.959*dummy_object_v_z_in_patch_X_2_object_w_16-0.363*dummy_object_w_z_in_patch_X_2_object_w_16-95.124*dummy_object_w_z_in_patch_X_P_object_u_20-18.342*dummy_object_w_z_in_patch_X_P_object_v_20+0.363*dummy_object_wp_z_in_patch_X_2_object_w_16+95.124*dummy_object_wp_z_in_patch_X_P_object_u_20+18.342*dummy_object_wp_z_in_patch_X_P_object_v_20 = -32.802;
   67.8*p32_u_x+30*p33_u_x+20*p34_u_x+89.579*object_u_x-34.125*object_v_x-18.911*object_w_x+18.911*object_wp_x+18*sph_w2_p34_X_3_x_17-18*cos_palm_X_P_19+12.034*dummy_object_u_x_in_patch_X_3_object_u_18-16.238*dummy_object_u_x_in_patch_X_3_object_v_18-15.943*dummy_object_v_x_in_patch_X_3_object_u_18-15.943*dummy_object_v_x_in_patch_X_3_object_v_18+12.422*dummy_object_w_x_in_patch_X_3_object_u_18-6.5*dummy_object_w_x_in_patch_X_3_object_v_18-12.422*dummy_object_wp_x_in_patch_X_3_object_u_18+6.5*dummy_object_wp_x_in_patch_X_3_object_v_18+18.342*dummy_object_u_x_in_patch_X_P_object_u_20-95.124*dummy_object_u_x_in_patch_X_P_object_v_20-95.124*dummy_object_w_x_in_patch_X_P_object_u_20-18.342*dummy_object_w_x_in_patch_X_P_object_v_20+95.124*dummy_object_wp_x_in_patch_X_P_object_u_20+18.342*dummy_object_wp_x_in_patch_X_P_object_v_20+0.205*dummy_object_u_x_in_patch_X_3_object_w_18-0.959*dummy_object_v_x_in_patch_X_3_object_w_18-0.012*dummy_object_w_x_in_patch_X_3_object_w_18+0.012*dummy_object_wp_x_in_patch_X_3_object_w_18 = 6.85;
   67.8*p32_u_y+30*p33_u_y+20*p34_u_y+89.579*object_u_y-34.125*object_v_y-18.911*object_w_y+18.911*object_wp_y+18*sph_w2_p34_X_3_y_17-18*sph_w2_palm_X_P_y_19+12.034*dummy_object_u_y_in_patch_X_3_object_u_18-16.238*dummy_object_u_y_in_patch_X_3_object_v_18-15.943*dummy_object_v_y_in_patch_X_3_object_u_18-15.943*dummy_object_v_y_in_patch_X_3_object_v_18+12.422*dummy_object_w_y_in_patch_X_3_object_u_18-6.5*dummy_object_w_y_in_patch_X_3_object_v_18-12.422*dummy_object_wp_y_in_patch_X_3_object_u_18+6.5*dummy_object_wp_y_in_patch_X_3_object_v_18+18.342*dummy_object_u_y_in_patch_X_P_object_u_20-95.124*dummy_object_u_y_in_patch_X_P_object_v_20-95.124*dummy_object_w_y_in_patch_X_P_object_u_20-18.342*dummy_object_w_y_in_patch_X_P_object_v_20+95.124*dummy_object_wp_y_in_patch_X_P_object_u_20+18.342*dummy_object_wp_y_in_patch_X_P_object_v_20+0.205*dummy_object_u_y_in_patch_X_3_object_w_18-0.959*dummy_object_v_y_in_patch_X_3_object_w_18-0.012*dummy_object_w_y_in_patch_X_3_object_w_18+0.012*dummy_object_wp_y_in_patch_X_3_object_w_18 = -40.218;
   67.8*p32_u_z+30*p33_u_z+20*p34_u_z+89.579*object_u_z-34.125*object_v_z-18.911*object_w_z+18.911*object_wp_z+18*sph_w2_p34_X_3_z_17-18*sph_w2_palm_X_P_z_19+12.034*dummy_object_u_z_in_patch_X_3_object_u_18-16.238*dummy_object_u_z_in_patch_X_3_object_v_18-15.943*dummy_object_v_z_in_patch_X_3_object_u_18-15.943*dummy_object_v_z_in_patch_X_3_object_v_18+12.422*dummy_object_w_z_in_patch_X_3_object_u_18-6.5*dummy_object_w_z_in_patch_X_3_object_v_18-12.422*dummy_object_wp_z_in_patch_X_3_object_u_18+6.5*dummy_object_wp_z_in_patch_X_3_object_v_18+18.342*dummy_object_u_z_in_patch_X_P_object_u_20-95.124*dummy_object_u_z_in_patch_X_P_object_v_20-95.124*dummy_object_w_z_in_patch_X_P_object_u_20-18.342*dummy_object_w_z_in_patch_X_P_object_v_20+95.124*dummy_object_wp_z_in_patch_X_P_object_u_20+18.342*dummy_object_wp_z_in_patch_X_P_object_v_20+0.205*dummy_object_u_z_in_patch_X_3_object_w_18-0.959*dummy_object_v_z_in_patch_X_3_object_w_18-0.012*dummy_object_w_z_in_patch_X_3_object_w_18+0.012*dummy_object_wp_z_in_patch_X_3_object_w_18 = -28.082;
   67.8*p12_u_x+30*p13_u_x+20*p14_u_x-12.797*object_u_x-34.125*object_v_x-18.911*object_w_x+18.911*object_wp_x+18*sph_w2_p14_X_1_x_13-18*cos_palm_X_P_19+16.238*dummy_object_u_x_in_patch_X_1_object_u_14-12.034*dummy_object_u_x_in_patch_X_1_object_v_14-15.943*dummy_object_v_x_in_patch_X_1_object_u_14-15.943*dummy_object_v_x_in_patch_X_1_object_v_14-6.5*dummy_object_w_x_in_patch_X_1_object_u_14+12.422*dummy_object_w_x_in_patch_X_1_object_v_14+6.5*dummy_object_wp_x_in_patch_X_1_object_u_14-12.422*dummy_object_wp_x_in_patch_X_1_object_v_14+18.342*dummy_object_u_x_in_patch_X_P_object_u_20-95.124*dummy_object_u_x_in_patch_X_P_object_v_20-95.124*dummy_object_w_x_in_patch_X_P_object_u_20-18.342*dummy_object_w_x_in_patch_X_P_object_v_20+95.124*dummy_object_wp_x_in_patch_X_P_object_u_20+18.342*dummy_object_wp_x_in_patch_X_P_object_v_20-0.205*dummy_object_u_x_in_patch_X_1_object_w_14-0.959*dummy_object_v_x_in_patch_X_1_object_w_14-0.012*dummy_object_w_x_in_patch_X_1_object_w_14+0.012*dummy_object_wp_x_in_patch_X_1_object_w_14 = 6.85;
   67.8*p12_u_y+30*p13_u_y+20*p14_u_y-12.797*object_u_y-34.125*object_v_y-18.911*object_w_y+18.911*object_wp_y+18*sph_w2_p14_X_1_y_13-18*sph_w2_palm_X_P_y_19+16.238*dummy_object_u_y_in_patch_X_1_object_u_14-12.034*dummy_object_u_y_in_patch_X_1_object_v_14-15.943*dummy_object_v_y_in_patch_X_1_object_u_14-15.943*dummy_object_v_y_in_patch_X_1_object_v_14-6.5*dummy_object_w_y_in_patch_X_1_object_u_14+12.422*dummy_object_w_y_in_patch_X_1_object_v_14+6.5*dummy_object_wp_y_in_patch_X_1_object_u_14-12.422*dummy_object_wp_y_in_patch_X_1_object_v_14+18.342*dummy_object_u_y_in_patch_X_P_object_u_20-95.124*dummy_object_u_y_in_patch_X_P_object_v_20-95.124*dummy_object_w_y_in_patch_X_P_object_u_20-18.342*dummy_object_w_y_in_patch_X_P_object_v_20+95.124*dummy_object_wp_y_in_patch_X_P_object_u_20+18.342*dummy_object_wp_y_in_patch_X_P_object_v_20-0.205*dummy_object_u_y_in_patch_X_1_object_w_14-0.959*dummy_object_v_y_in_patch_X_1_object_w_14-0.012*dummy_object_w_y_in_patch_X_1_object_w_14+0.012*dummy_object_wp_y_in_patch_X_1_object_w_14 = 40.112;
   67.8*p12_u_z+30*p13_u_z+20*p14_u_z-12.797*object_u_z-34.125*object_v_z-18.911*object_w_z+18.911*object_wp_z+18*sph_w2_p14_X_1_z_13-18*sph_w2_palm_X_P_z_19+16.238*dummy_object_u_z_in_patch_X_1_object_u_14-12.034*dummy_object_u_z_in_patch_X_1_object_v_14-15.943*dummy_object_v_z_in_patch_X_1_object_u_14-15.943*dummy_object_v_z_in_patch_X_1_object_v_14-6.5*dummy_object_w_z_in_patch_X_1_object_u_14+12.422*dummy_object_w_z_in_patch_X_1_object_v_14+6.5*dummy_object_wp_z_in_patch_X_1_object_u_14-12.422*dummy_object_wp_z_in_patch_X_1_object_v_14+18.342*dummy_object_u_z_in_patch_X_P_object_u_20-95.124*dummy_object_u_z_in_patch_X_P_object_v_20-95.124*dummy_object_w_z_in_patch_X_P_object_u_20-18.342*dummy_object_w_z_in_patch_X_P_object_v_20+95.124*dummy_object_wp_z_in_patch_X_P_object_u_20+18.342*dummy_object_wp_z_in_patch_X_P_object_v_20-0.205*dummy_object_u_z_in_patch_X_1_object_w_14-0.959*dummy_object_v_z_in_patch_X_1_object_w_14-0.012*dummy_object_w_z_in_patch_X_1_object_w_14+0.012*dummy_object_wp_z_in_patch_X_1_object_w_14 = -28.082;

[COORD EQS]

   96.8275916175*p42_u_z-30*p43_u_y+p44_r_y = 232.305002003;
   67.8*p42_u_z+30*p43_u_z-p44_r_z = -97;

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
   p42_u_z^2-dummy_p42_u_z_2 = 0;
   object_u_x*object_v_x-dummy_object_u_x_object_v_x = 0;
   object_u_y*object_v_y-dummy_object_u_y_object_v_y = 0;
   object_u_z*object_v_z-dummy_object_u_z_object_v_z = 0;
   X_P_u_x*X_P_v_x-dummy_X_P_u_x_X_P_v_x = 0;
   X_P_u_y*X_P_v_y-dummy_X_P_u_y_X_P_v_y = 0;
   X_P_u_z*X_P_v_z-dummy_X_P_u_z_X_P_v_z = 0;
   X_1_u_x*X_1_v_x-dummy_X_1_u_x_X_1_v_x = 0;
   X_1_u_y*X_1_v_y-dummy_X_1_u_y_X_1_v_y = 0;
   X_1_u_z*X_1_v_z-dummy_X_1_u_z_X_1_v_z = 0;
   X_2_u_x*X_2_v_x-dummy_X_2_u_x_X_2_v_x = 0;
   X_2_u_y*X_2_v_y-dummy_X_2_u_y_X_2_v_y = 0;
   X_2_u_z*X_2_v_z-dummy_X_2_u_z_X_2_v_z = 0;
   X_3_u_x*X_3_v_x-dummy_X_3_u_x_X_3_v_x = 0;
   X_3_u_y*X_3_v_y-dummy_X_3_u_y_X_3_v_y = 0;
   X_3_u_z*X_3_v_z-dummy_X_3_u_z_X_3_v_z = 0;
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
   p42_u_z*p43_u_y-dummy_p42_u_z_p43_u_y = 0;
   p42_u_z*p43_u_z-dummy_p42_u_z_p43_u_z = 0;
   p43_u_y*p44_u_y-dummy_p43_u_y_p44_u_y = 0;
   p43_u_z*p44_u_z-dummy_p43_u_z_p44_u_z = 0;
   sph_w1_p14_X_1_x_13*sph_w2_p14_X_1_x_13-dummy_sph_w1_p14_X_1_x_13_sph_w2_p14_X_1_x_13 = 0;
   sph_w1_p14_X_1_y_13*sph_w2_p14_X_1_y_13-dummy_sph_w1_p14_X_1_y_13_sph_w2_p14_X_1_y_13 = 0;
   sph_w1_p14_X_1_z_13*sph_w2_p14_X_1_z_13-dummy_sph_w1_p14_X_1_z_13_sph_w2_p14_X_1_z_13 = 0;
   in_patch_X_1_object_u_14^2-dummy_in_patch_X_1_object_u_14_2 = 0;
   in_patch_X_1_object_v_14^2-dummy_in_patch_X_1_object_v_14_2 = 0;
   in_patch_X_1_object_l_14^2-dummy_in_patch_X_1_object_l_14_2 = 0;
   object_u_x*in_patch_X_1_object_u_14-dummy_object_u_x_in_patch_X_1_object_u_14 = 0;
   object_u_x*in_patch_X_1_object_v_14-dummy_object_u_x_in_patch_X_1_object_v_14 = 0;
   object_v_x*in_patch_X_1_object_u_14-dummy_object_v_x_in_patch_X_1_object_u_14 = 0;
   object_v_x*in_patch_X_1_object_v_14-dummy_object_v_x_in_patch_X_1_object_v_14 = 0;
   object_w_x*in_patch_X_1_object_u_14-dummy_object_w_x_in_patch_X_1_object_u_14 = 0;
   object_w_x*in_patch_X_1_object_v_14-dummy_object_w_x_in_patch_X_1_object_v_14 = 0;
   object_wp_x*in_patch_X_1_object_u_14-dummy_object_wp_x_in_patch_X_1_object_u_14 = 0;
   object_wp_x*in_patch_X_1_object_v_14-dummy_object_wp_x_in_patch_X_1_object_v_14 = 0;
   X_1_w_x*in_patch_X_1_object_l_14-dummy_X_1_w_x_in_patch_X_1_object_l_14 = 0;
   X_1_wp_x*in_patch_X_1_object_l_14-dummy_X_1_wp_x_in_patch_X_1_object_l_14 = 0;
   object_u_y*in_patch_X_1_object_u_14-dummy_object_u_y_in_patch_X_1_object_u_14 = 0;
   object_u_y*in_patch_X_1_object_v_14-dummy_object_u_y_in_patch_X_1_object_v_14 = 0;
   object_v_y*in_patch_X_1_object_u_14-dummy_object_v_y_in_patch_X_1_object_u_14 = 0;
   object_v_y*in_patch_X_1_object_v_14-dummy_object_v_y_in_patch_X_1_object_v_14 = 0;
   object_w_y*in_patch_X_1_object_u_14-dummy_object_w_y_in_patch_X_1_object_u_14 = 0;
   object_w_y*in_patch_X_1_object_v_14-dummy_object_w_y_in_patch_X_1_object_v_14 = 0;
   object_wp_y*in_patch_X_1_object_u_14-dummy_object_wp_y_in_patch_X_1_object_u_14 = 0;
   object_wp_y*in_patch_X_1_object_v_14-dummy_object_wp_y_in_patch_X_1_object_v_14 = 0;
   X_1_w_y*in_patch_X_1_object_l_14-dummy_X_1_w_y_in_patch_X_1_object_l_14 = 0;
   X_1_wp_y*in_patch_X_1_object_l_14-dummy_X_1_wp_y_in_patch_X_1_object_l_14 = 0;
   object_u_z*in_patch_X_1_object_u_14-dummy_object_u_z_in_patch_X_1_object_u_14 = 0;
   object_u_z*in_patch_X_1_object_v_14-dummy_object_u_z_in_patch_X_1_object_v_14 = 0;
   object_v_z*in_patch_X_1_object_u_14-dummy_object_v_z_in_patch_X_1_object_u_14 = 0;
   object_v_z*in_patch_X_1_object_v_14-dummy_object_v_z_in_patch_X_1_object_v_14 = 0;
   object_w_z*in_patch_X_1_object_u_14-dummy_object_w_z_in_patch_X_1_object_u_14 = 0;
   object_w_z*in_patch_X_1_object_v_14-dummy_object_w_z_in_patch_X_1_object_v_14 = 0;
   object_wp_z*in_patch_X_1_object_u_14-dummy_object_wp_z_in_patch_X_1_object_u_14 = 0;
   object_wp_z*in_patch_X_1_object_v_14-dummy_object_wp_z_in_patch_X_1_object_v_14 = 0;
   X_1_w_z*in_patch_X_1_object_l_14-dummy_X_1_w_z_in_patch_X_1_object_l_14 = 0;
   X_1_wp_z*in_patch_X_1_object_l_14-dummy_X_1_wp_z_in_patch_X_1_object_l_14 = 0;
   sph_w1_p24_X_2_x_15*sph_w2_p24_X_2_x_15-dummy_sph_w1_p24_X_2_x_15_sph_w2_p24_X_2_x_15 = 0;
   sph_w1_p24_X_2_y_15*sph_w2_p24_X_2_y_15-dummy_sph_w1_p24_X_2_y_15_sph_w2_p24_X_2_y_15 = 0;
   sph_w1_p24_X_2_z_15*sph_w2_p24_X_2_z_15-dummy_sph_w1_p24_X_2_z_15_sph_w2_p24_X_2_z_15 = 0;
   in_patch_X_2_object_u_16^2-dummy_in_patch_X_2_object_u_16_2 = 0;
   in_patch_X_2_object_v_16^2-dummy_in_patch_X_2_object_v_16_2 = 0;
   in_patch_X_2_object_l_16^2-dummy_in_patch_X_2_object_l_16_2 = 0;
   object_u_x*in_patch_X_2_object_u_16-dummy_object_u_x_in_patch_X_2_object_u_16 = 0;
   object_u_x*in_patch_X_2_object_v_16-dummy_object_u_x_in_patch_X_2_object_v_16 = 0;
   object_v_x*in_patch_X_2_object_u_16-dummy_object_v_x_in_patch_X_2_object_u_16 = 0;
   object_v_x*in_patch_X_2_object_v_16-dummy_object_v_x_in_patch_X_2_object_v_16 = 0;
   object_w_x*in_patch_X_2_object_u_16-dummy_object_w_x_in_patch_X_2_object_u_16 = 0;
   object_w_x*in_patch_X_2_object_v_16-dummy_object_w_x_in_patch_X_2_object_v_16 = 0;
   object_wp_x*in_patch_X_2_object_u_16-dummy_object_wp_x_in_patch_X_2_object_u_16 = 0;
   object_wp_x*in_patch_X_2_object_v_16-dummy_object_wp_x_in_patch_X_2_object_v_16 = 0;
   X_2_w_x*in_patch_X_2_object_l_16-dummy_X_2_w_x_in_patch_X_2_object_l_16 = 0;
   X_2_wp_x*in_patch_X_2_object_l_16-dummy_X_2_wp_x_in_patch_X_2_object_l_16 = 0;
   object_u_y*in_patch_X_2_object_u_16-dummy_object_u_y_in_patch_X_2_object_u_16 = 0;
   object_u_y*in_patch_X_2_object_v_16-dummy_object_u_y_in_patch_X_2_object_v_16 = 0;
   object_v_y*in_patch_X_2_object_u_16-dummy_object_v_y_in_patch_X_2_object_u_16 = 0;
   object_v_y*in_patch_X_2_object_v_16-dummy_object_v_y_in_patch_X_2_object_v_16 = 0;
   object_w_y*in_patch_X_2_object_u_16-dummy_object_w_y_in_patch_X_2_object_u_16 = 0;
   object_w_y*in_patch_X_2_object_v_16-dummy_object_w_y_in_patch_X_2_object_v_16 = 0;
   object_wp_y*in_patch_X_2_object_u_16-dummy_object_wp_y_in_patch_X_2_object_u_16 = 0;
   object_wp_y*in_patch_X_2_object_v_16-dummy_object_wp_y_in_patch_X_2_object_v_16 = 0;
   X_2_w_y*in_patch_X_2_object_l_16-dummy_X_2_w_y_in_patch_X_2_object_l_16 = 0;
   X_2_wp_y*in_patch_X_2_object_l_16-dummy_X_2_wp_y_in_patch_X_2_object_l_16 = 0;
   object_u_z*in_patch_X_2_object_u_16-dummy_object_u_z_in_patch_X_2_object_u_16 = 0;
   object_u_z*in_patch_X_2_object_v_16-dummy_object_u_z_in_patch_X_2_object_v_16 = 0;
   object_v_z*in_patch_X_2_object_u_16-dummy_object_v_z_in_patch_X_2_object_u_16 = 0;
   object_v_z*in_patch_X_2_object_v_16-dummy_object_v_z_in_patch_X_2_object_v_16 = 0;
   object_w_z*in_patch_X_2_object_u_16-dummy_object_w_z_in_patch_X_2_object_u_16 = 0;
   object_w_z*in_patch_X_2_object_v_16-dummy_object_w_z_in_patch_X_2_object_v_16 = 0;
   object_wp_z*in_patch_X_2_object_u_16-dummy_object_wp_z_in_patch_X_2_object_u_16 = 0;
   object_wp_z*in_patch_X_2_object_v_16-dummy_object_wp_z_in_patch_X_2_object_v_16 = 0;
   X_2_w_z*in_patch_X_2_object_l_16-dummy_X_2_w_z_in_patch_X_2_object_l_16 = 0;
   X_2_wp_z*in_patch_X_2_object_l_16-dummy_X_2_wp_z_in_patch_X_2_object_l_16 = 0;
   sph_w1_p34_X_3_x_17*sph_w2_p34_X_3_x_17-dummy_sph_w1_p34_X_3_x_17_sph_w2_p34_X_3_x_17 = 0;
   sph_w1_p34_X_3_y_17*sph_w2_p34_X_3_y_17-dummy_sph_w1_p34_X_3_y_17_sph_w2_p34_X_3_y_17 = 0;
   sph_w1_p34_X_3_z_17*sph_w2_p34_X_3_z_17-dummy_sph_w1_p34_X_3_z_17_sph_w2_p34_X_3_z_17 = 0;
   in_patch_X_3_object_u_18^2-dummy_in_patch_X_3_object_u_18_2 = 0;
   in_patch_X_3_object_v_18^2-dummy_in_patch_X_3_object_v_18_2 = 0;
   in_patch_X_3_object_l_18^2-dummy_in_patch_X_3_object_l_18_2 = 0;
   object_u_x*in_patch_X_3_object_u_18-dummy_object_u_x_in_patch_X_3_object_u_18 = 0;
   object_u_x*in_patch_X_3_object_v_18-dummy_object_u_x_in_patch_X_3_object_v_18 = 0;
   object_v_x*in_patch_X_3_object_u_18-dummy_object_v_x_in_patch_X_3_object_u_18 = 0;
   object_v_x*in_patch_X_3_object_v_18-dummy_object_v_x_in_patch_X_3_object_v_18 = 0;
   object_w_x*in_patch_X_3_object_u_18-dummy_object_w_x_in_patch_X_3_object_u_18 = 0;
   object_w_x*in_patch_X_3_object_v_18-dummy_object_w_x_in_patch_X_3_object_v_18 = 0;
   object_wp_x*in_patch_X_3_object_u_18-dummy_object_wp_x_in_patch_X_3_object_u_18 = 0;
   object_wp_x*in_patch_X_3_object_v_18-dummy_object_wp_x_in_patch_X_3_object_v_18 = 0;
   X_3_w_x*in_patch_X_3_object_l_18-dummy_X_3_w_x_in_patch_X_3_object_l_18 = 0;
   X_3_wp_x*in_patch_X_3_object_l_18-dummy_X_3_wp_x_in_patch_X_3_object_l_18 = 0;
   object_u_y*in_patch_X_3_object_u_18-dummy_object_u_y_in_patch_X_3_object_u_18 = 0;
   object_u_y*in_patch_X_3_object_v_18-dummy_object_u_y_in_patch_X_3_object_v_18 = 0;
   object_v_y*in_patch_X_3_object_u_18-dummy_object_v_y_in_patch_X_3_object_u_18 = 0;
   object_v_y*in_patch_X_3_object_v_18-dummy_object_v_y_in_patch_X_3_object_v_18 = 0;
   object_w_y*in_patch_X_3_object_u_18-dummy_object_w_y_in_patch_X_3_object_u_18 = 0;
   object_w_y*in_patch_X_3_object_v_18-dummy_object_w_y_in_patch_X_3_object_v_18 = 0;
   object_wp_y*in_patch_X_3_object_u_18-dummy_object_wp_y_in_patch_X_3_object_u_18 = 0;
   object_wp_y*in_patch_X_3_object_v_18-dummy_object_wp_y_in_patch_X_3_object_v_18 = 0;
   X_3_w_y*in_patch_X_3_object_l_18-dummy_X_3_w_y_in_patch_X_3_object_l_18 = 0;
   X_3_wp_y*in_patch_X_3_object_l_18-dummy_X_3_wp_y_in_patch_X_3_object_l_18 = 0;
   object_u_z*in_patch_X_3_object_u_18-dummy_object_u_z_in_patch_X_3_object_u_18 = 0;
   object_u_z*in_patch_X_3_object_v_18-dummy_object_u_z_in_patch_X_3_object_v_18 = 0;
   object_v_z*in_patch_X_3_object_u_18-dummy_object_v_z_in_patch_X_3_object_u_18 = 0;
   object_v_z*in_patch_X_3_object_v_18-dummy_object_v_z_in_patch_X_3_object_v_18 = 0;
   object_w_z*in_patch_X_3_object_u_18-dummy_object_w_z_in_patch_X_3_object_u_18 = 0;
   object_w_z*in_patch_X_3_object_v_18-dummy_object_w_z_in_patch_X_3_object_v_18 = 0;
   object_wp_z*in_patch_X_3_object_u_18-dummy_object_wp_z_in_patch_X_3_object_u_18 = 0;
   object_wp_z*in_patch_X_3_object_v_18-dummy_object_wp_z_in_patch_X_3_object_v_18 = 0;
   X_3_w_z*in_patch_X_3_object_l_18-dummy_X_3_w_z_in_patch_X_3_object_l_18 = 0;
   X_3_wp_z*in_patch_X_3_object_l_18-dummy_X_3_wp_z_in_patch_X_3_object_l_18 = 0;
   X_P_w_x*in_patch_X_P_object_l_20-dummy_X_P_w_x_in_patch_X_P_object_l_20 = 0;
   X_P_wp_x*in_patch_X_P_object_l_20-dummy_X_P_wp_x_in_patch_X_P_object_l_20 = 0;
   X_P_w_y*in_patch_X_P_object_l_20-dummy_X_P_w_y_in_patch_X_P_object_l_20 = 0;
   X_P_wp_y*in_patch_X_P_object_l_20-dummy_X_P_wp_y_in_patch_X_P_object_l_20 = 0;
   X_P_w_z*in_patch_X_P_object_l_20-dummy_X_P_w_z_in_patch_X_P_object_l_20 = 0;
   X_P_wp_z*in_patch_X_P_object_l_20-dummy_X_P_wp_z_in_patch_X_P_object_l_20 = 0;
   object_u_x*in_patch_X_P_object_u_20-dummy_object_u_x_in_patch_X_P_object_u_20 = 0;
   object_u_x*in_patch_X_P_object_v_20-dummy_object_u_x_in_patch_X_P_object_v_20 = 0;
   object_v_x*in_patch_X_2_object_w_16-dummy_object_v_x_in_patch_X_2_object_w_16 = 0;
   object_w_x*in_patch_X_2_object_w_16-dummy_object_w_x_in_patch_X_2_object_w_16 = 0;
   object_w_x*in_patch_X_P_object_u_20-dummy_object_w_x_in_patch_X_P_object_u_20 = 0;
   object_w_x*in_patch_X_P_object_v_20-dummy_object_w_x_in_patch_X_P_object_v_20 = 0;
   object_wp_x*in_patch_X_2_object_w_16-dummy_object_wp_x_in_patch_X_2_object_w_16 = 0;
   object_wp_x*in_patch_X_P_object_u_20-dummy_object_wp_x_in_patch_X_P_object_u_20 = 0;
   object_wp_x*in_patch_X_P_object_v_20-dummy_object_wp_x_in_patch_X_P_object_v_20 = 0;
   object_u_y*in_patch_X_P_object_u_20-dummy_object_u_y_in_patch_X_P_object_u_20 = 0;
   object_u_y*in_patch_X_P_object_v_20-dummy_object_u_y_in_patch_X_P_object_v_20 = 0;
   object_v_y*in_patch_X_2_object_w_16-dummy_object_v_y_in_patch_X_2_object_w_16 = 0;
   object_w_y*in_patch_X_2_object_w_16-dummy_object_w_y_in_patch_X_2_object_w_16 = 0;
   object_w_y*in_patch_X_P_object_u_20-dummy_object_w_y_in_patch_X_P_object_u_20 = 0;
   object_w_y*in_patch_X_P_object_v_20-dummy_object_w_y_in_patch_X_P_object_v_20 = 0;
   object_wp_y*in_patch_X_2_object_w_16-dummy_object_wp_y_in_patch_X_2_object_w_16 = 0;
   object_wp_y*in_patch_X_P_object_u_20-dummy_object_wp_y_in_patch_X_P_object_u_20 = 0;
   object_wp_y*in_patch_X_P_object_v_20-dummy_object_wp_y_in_patch_X_P_object_v_20 = 0;
   object_u_z*in_patch_X_P_object_u_20-dummy_object_u_z_in_patch_X_P_object_u_20 = 0;
   object_u_z*in_patch_X_P_object_v_20-dummy_object_u_z_in_patch_X_P_object_v_20 = 0;
   object_v_z*in_patch_X_2_object_w_16-dummy_object_v_z_in_patch_X_2_object_w_16 = 0;
   object_w_z*in_patch_X_2_object_w_16-dummy_object_w_z_in_patch_X_2_object_w_16 = 0;
   object_w_z*in_patch_X_P_object_u_20-dummy_object_w_z_in_patch_X_P_object_u_20 = 0;
   object_w_z*in_patch_X_P_object_v_20-dummy_object_w_z_in_patch_X_P_object_v_20 = 0;
   object_wp_z*in_patch_X_2_object_w_16-dummy_object_wp_z_in_patch_X_2_object_w_16 = 0;
   object_wp_z*in_patch_X_P_object_u_20-dummy_object_wp_z_in_patch_X_P_object_u_20 = 0;
   object_wp_z*in_patch_X_P_object_v_20-dummy_object_wp_z_in_patch_X_P_object_v_20 = 0;
   object_u_x*in_patch_X_3_object_w_18-dummy_object_u_x_in_patch_X_3_object_w_18 = 0;
   object_v_x*in_patch_X_3_object_w_18-dummy_object_v_x_in_patch_X_3_object_w_18 = 0;
   object_w_x*in_patch_X_3_object_w_18-dummy_object_w_x_in_patch_X_3_object_w_18 = 0;
   object_wp_x*in_patch_X_3_object_w_18-dummy_object_wp_x_in_patch_X_3_object_w_18 = 0;
   object_u_y*in_patch_X_3_object_w_18-dummy_object_u_y_in_patch_X_3_object_w_18 = 0;
   object_v_y*in_patch_X_3_object_w_18-dummy_object_v_y_in_patch_X_3_object_w_18 = 0;
   object_w_y*in_patch_X_3_object_w_18-dummy_object_w_y_in_patch_X_3_object_w_18 = 0;
   object_wp_y*in_patch_X_3_object_w_18-dummy_object_wp_y_in_patch_X_3_object_w_18 = 0;
   object_u_z*in_patch_X_3_object_w_18-dummy_object_u_z_in_patch_X_3_object_w_18 = 0;
   object_v_z*in_patch_X_3_object_w_18-dummy_object_v_z_in_patch_X_3_object_w_18 = 0;
   object_w_z*in_patch_X_3_object_w_18-dummy_object_w_z_in_patch_X_3_object_w_18 = 0;
   object_wp_z*in_patch_X_3_object_w_18-dummy_object_wp_z_in_patch_X_3_object_w_18 = 0;
   object_u_x*in_patch_X_1_object_w_14-dummy_object_u_x_in_patch_X_1_object_w_14 = 0;
   object_v_x*in_patch_X_1_object_w_14-dummy_object_v_x_in_patch_X_1_object_w_14 = 0;
   object_w_x*in_patch_X_1_object_w_14-dummy_object_w_x_in_patch_X_1_object_w_14 = 0;
   object_wp_x*in_patch_X_1_object_w_14-dummy_object_wp_x_in_patch_X_1_object_w_14 = 0;
   object_u_y*in_patch_X_1_object_w_14-dummy_object_u_y_in_patch_X_1_object_w_14 = 0;
   object_v_y*in_patch_X_1_object_w_14-dummy_object_v_y_in_patch_X_1_object_w_14 = 0;
   object_w_y*in_patch_X_1_object_w_14-dummy_object_w_y_in_patch_X_1_object_w_14 = 0;
   object_wp_y*in_patch_X_1_object_w_14-dummy_object_wp_y_in_patch_X_1_object_w_14 = 0;
   object_u_z*in_patch_X_1_object_w_14-dummy_object_u_z_in_patch_X_1_object_w_14 = 0;
   object_v_z*in_patch_X_1_object_w_14-dummy_object_v_z_in_patch_X_1_object_w_14 = 0;
   object_w_z*in_patch_X_1_object_w_14-dummy_object_w_z_in_patch_X_1_object_w_14 = 0;
   object_wp_z*in_patch_X_1_object_w_14-dummy_object_wp_z_in_patch_X_1_object_w_14 = 0;
   p12_u_y*p14_v_z-p12_w_x = 0;
   p12_u_x*p14_v_y-p12_w_z = 0;
   p12_u_z*p14_v_y-p12_wp_x = 0;
   p12_u_x*p14_v_z-p12_wp_y = 0;
   p13_u_y*p14_v_z-p13_w_x = 0;
   p13_u_x*p14_v_y-p13_w_z = 0;
   p13_u_z*p14_v_y-p13_wp_x = 0;
   p13_u_x*p14_v_z-p13_wp_y = 0;
   p14_u_y*p14_v_z-p14_w_x = 0;
   p14_u_x*p14_v_y-p14_w_z = 0;
   p14_u_z*p14_v_y-p14_wp_x = 0;
   p14_u_x*p14_v_z-p14_wp_y = 0;
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
   object_u_y*object_v_z-object_w_x = 0;
   object_u_z*object_v_x-object_w_y = 0;
   object_u_x*object_v_y-object_w_z = 0;
   object_u_z*object_v_y-object_wp_x = 0;
   object_u_x*object_v_z-object_wp_y = 0;
   object_u_y*object_v_x-object_wp_z = 0;
   X_P_u_y*X_P_v_z-X_P_w_x = 0;
   X_P_u_z*X_P_v_x-X_P_w_y = 0;
   X_P_u_x*X_P_v_y-X_P_w_z = 0;
   X_P_u_z*X_P_v_y-X_P_wp_x = 0;
   X_P_u_x*X_P_v_z-X_P_wp_y = 0;
   X_P_u_y*X_P_v_x-X_P_wp_z = 0;
   X_1_u_y*X_1_v_z-X_1_w_x = 0;
   X_1_u_z*X_1_v_x-X_1_w_y = 0;
   X_1_u_x*X_1_v_y-X_1_w_z = 0;
   X_1_u_z*X_1_v_y-X_1_wp_x = 0;
   X_1_u_x*X_1_v_z-X_1_wp_y = 0;
   X_1_u_y*X_1_v_x-X_1_wp_z = 0;
   X_2_u_y*X_2_v_z-X_2_w_x = 0;
   X_2_u_z*X_2_v_x-X_2_w_y = 0;
   X_2_u_x*X_2_v_y-X_2_w_z = 0;
   X_2_u_z*X_2_v_y-X_2_wp_x = 0;
   X_2_u_x*X_2_v_z-X_2_wp_y = 0;
   X_2_u_y*X_2_v_x-X_2_wp_z = 0;
   X_3_u_y*X_3_v_z-X_3_w_x = 0;
   X_3_u_z*X_3_v_x-X_3_w_y = 0;
   X_3_u_x*X_3_v_y-X_3_w_z = 0;
   X_3_u_z*X_3_v_y-X_3_wp_x = 0;
   X_3_u_x*X_3_v_z-X_3_wp_y = 0;
   X_3_u_y*X_3_v_x-X_3_wp_z = 0;
   in_patch_X_1_object_u_14*in_patch_X_1_object_v_14-in_patch_X_1_object_w_14 = 0;
   in_patch_X_2_object_u_16*in_patch_X_2_object_v_16-in_patch_X_2_object_w_16 = 0;
   in_patch_X_3_object_u_18*in_patch_X_3_object_v_18-in_patch_X_3_object_w_18 = 0;

[SEARCH]

 MIN 172.582639308*p24_v_y^2+172.582639308*cos_0_palm_p12_0^2+11.6568542495*w1_p12_p13_x_1^2+23.313708499*cos_p13_p14_2^2+11.6568542495*w1_p22_p23_x_4^2+23.313708499*cos_p23_p24_5^2+172.582639308*cos_0_palm_p32_6^2+11.6568542495*w1_p32_p33_x_7^2+23.313708499*cos_p33_p34_8^2+cos_p14_X_1_13^2+4*in_patch_X_1_object_u_14^2+4*in_patch_X_1_object_v_14^2+cos_p24_X_2_15^2+4*in_patch_X_2_object_u_16^2+4*in_patch_X_2_object_v_16^2+cos_p34_X_3_17^2+4*in_patch_X_3_object_u_18^2+4*in_patch_X_3_object_v_18^2+cos_palm_X_P_19^2+4*in_patch_X_P_object_u_20^2+4*in_patch_X_P_object_v_20^2+345.165278616*p24_v_y-345.165278616*cos_0_palm_p12_0-23.313708499*w1_p12_p13_x_1-46.627416998*cos_p13_p14_2-23.313708499*w1_p22_p23_x_4-46.627416998*cos_p23_p24_5-345.165278616*cos_0_palm_p32_6-23.313708499*w1_p32_p33_x_7-46.627416998*cos_p33_p34_8-2*cos_p14_X_1_13-4*in_patch_X_1_object_u_14-4*in_patch_X_1_object_v_14-2*cos_p24_X_2_15-4*in_patch_X_2_object_u_16-4*in_patch_X_2_object_v_16-2*cos_p34_X_3_17-4*in_patch_X_3_object_u_18-4*in_patch_X_3_object_v_18-2*cos_palm_X_P_19-4*in_patch_X_P_object_u_20-4*in_patch_X_P_object_v_20+634.659606169

==========================================================================
Cuik executed in 32 processors
SOLUTIONS (to input file /home/porta/cuik/CuikSuite/examples/IJRR/teapot/4_contacts_index_middle_ring_palm/SAHandplusTeapot_kin.cuik):

   1 (err:378.627 min:8.58288 tm:371):{ 270  p12_u_x:[-0.00364797781379,0.0125955184377] p12_u_y:[-0.321882851607,-0.25127565921] p12_u_z:[0.946695718133,0.967915566966] p12_v_x:[-0,0] p12_v_y:[-0.969437233342,-0.946415398465] p12_v_z:[-0.322951843969,-0.245617368372] p13_u_x:[0.993512298342,0.999296663577] p13_u_y:[-0.0342934835061,-0.0113761956134] p13_u_z:[0.0440352809977,0.108894102142] p13_v_x:[-0,0] p13_v_y:[-0.969437233342,-0.946415398465] p13_v_z:[-0.322951843969,-0.245617368372] p14_u_x:[0.999982185501,1] p14_u_y:[-0.00192769115896,1.05661848025e-11] p14_u_z:[-0,0.0056491288729] p14_v_x:[-0,0] p14_v_y:[-0.969437233342,-0.946415398465] p14_v_z:[-0.322951843969,-0.245617368372] p22_u_x:[-0.000314479522475,0.00122471918759] p22_u_y:[-0.10555367202,-0.0702931838224] p22_u_z:[0.99441285249,0.997526374758] p22_v_x:[-0,0] p22_v_y:[-0.997530245127,-0.994407680349] p22_v_z:[-0.105609494146,-0.0702382552243] p23_u_x:[0.958903144366,0.963337156981] p23_u_y:[-0.0299647414063,-0.018844478403] p23_u_z:[0.267631103649,0.282146901402] p23_v_x:[-0,0] p23_v_y:[-0.997530245127,-0.994407680349] p23_v_z:[-0.105609494146,-0.0702382552243] p24_u_x:[0.999999809903,1] p24_u_y:[-6.51161944637e-05,1.00562376958e-11] p24_u_z:[-0,0.000613127014889] p24_v_x:[-0,0] p24_v_y:[-0.997530245127,-0.994407680349] p24_v_z:[-0.105609494146,-0.0702382552243] p32_u_x:[-0.000380789183503,0.000859639121192] p32_u_y:[0.0692877253978,0.10763944578] p32_u_z:[0.994189638235,0.997596717687] p32_v_x:[-0,0] p32_v_y:[-0.997600970231,-0.994182873814] p32_v_z:[0.0692264705423,0.107707802767] p33_u_x:[0.999911451623,1] p33_u_y:[-5.58487888959e-06,0.00143329782131] p33_u_z:[-5.15257375252e-05,0.0132300597176] p33_v_x:[-0,0] p33_v_y:[-0.997600970231,-0.994182873814] p33_v_z:[0.0692264705423,0.107707802767] p34_u_x:[0.999999997908,1] p34_u_y:[-1.00585144676e-11,6.94163022533e-06] p34_u_z:[-0,6.17944133604e-05] p34_v_x:[-0,0] p34_v_y:[-0.997600970231,-0.994182873814] p34_v_z:[0.0692264705423,0.107707802767] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-1,-1] p40_v_y:[-0,0] p40_v_z:[-0,0] p42_u_x:[-0,0] p42_u_y:[0.573567851275,0.573596798316] p42_u_z:[0.819137786572,0.819158055689] p42_v_x:[-1,-1] p42_v_y:[-0,0] p42_v_z:[-0,0] p43_u_x:[-0,0] p43_u_y:[0.573423457018,0.573727167697] p43_u_z:[0.819046495105,0.819259158874] p43_v_x:[-1,-1] p43_v_y:[-0,0] p43_v_z:[-0,0] p44_u_x:[-0,0] p44_u_y:[0.572495839268,0.575147420334] p44_u_z:[0.818049781423,0.819907625308] p44_v_x:[-1,-1] p44_v_y:[-0,0] p44_v_z:[-0,0] object_u_x:[-0,1.03476999037e-11] object_u_y:[-1,-0.999999999985] object_u_z:[-0,3.90499139206e-11] object_v_x:[0.966501311667,0.966639729296] object_v_y:[-0,1.06552960849e-15] object_v_z:[0.256137083417,0.256661673293] X_P_u_x:[-0,1.10246059228e-15] X_P_u_y:[0.999999999985,1] X_P_u_z:[-0,8.58946458974e-10] X_P_v_x:[-0.256661673297,-0.256137083415] X_P_v_y:[-2.61888689099e-09,0] X_P_v_z:[0.966501311656,0.966639729525] X_1_u_x:[-0,2.11951383699e-11] X_1_u_y:[0.841419802186,0.841984135806] X_1_u_z:[0.539502319511,0.540382681054] X_1_v_x:[0.999999999985,1] X_1_v_y:[-0,1.18848563637e-11] X_1_v_z:[-0,1.8555329134e-11] X_2_u_x:[-0,1.00091245177e-11] X_2_u_y:[0.999999999985,1] X_2_u_z:[-0,2.38256707543e-10] X_2_v_x:[0.999088380046,0.999118806843] X_2_v_y:[-0,1.0004119378e-11] X_2_v_z:[0.0419715360933,0.042689680558] X_3_u_x:[-0,0.000274787392849] X_3_u_y:[0.841885261138,0.842122198513] X_3_u_z:[-0.539656494031,-0.539286683738] X_3_v_x:[0.999999817081,1] X_3_v_y:[-0,0.000326395240859] X_3_v_z:[-0,0.00050918933394] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.969437233342,-0.946415398465] uni_v_palm_p12_z_0:[-0.322951843969,-0.245617368372] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[0.707106781156,0.710849814942] w2_palm_p12_y_0:[-0.225801996866,-0.174802389513] w2_palm_p12_z_0:[0.662673959064,0.68692412658] cos_0_palm_p12_0:[0.934780887928,0.960441829522] cos_1_palm_p12_0:[0.707106781187,0.710849814942] w1_p12_p13_x_1:[0.707106781156,0.710849814942] w1_p12_p13_y_1:[-0.225801996866,-0.174802389513] w1_p12_p13_z_1:[0.662673959064,0.68692412658] w2_p12_p13_x_1:[0.993512298342,0.999296663577] w2_p12_p13_y_1:[-0.0342934835061,-0.0113761956134] w2_p12_p13_z_1:[0.0440352809977,0.108894102142] cos_p12_p13_1:[0.738205130315,0.783565005698] w1_p13_p14_x_2:[0.739204722026,0.783565005696] w1_p13_p14_y_2:[0.16789394769,0.211443358001] w1_p13_p14_z_2:[-0.647107325103,-0.596453687889] w2_p13_p14_x_2:[0.999982185501,1] w2_p13_p14_y_2:[-0.00192769115896,1.05661848025e-11] w2_p13_p14_z_2:[-0,0.0056491288729] cos_p13_p14_2:[0.738205130315,0.783565005698] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.997530245127,-0.994407680349] uni_v_palm_p22_z_3:[-0.105609494146,-0.0702382552243] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.707106781156,0.707527864775] w2_palm_p22_y_3:[-0.0746326526213,-0.0496855588835] w2_palm_p22_z_3:[0.702301314172,0.705579488566] cos_0_palm_p22_3:[0.994407680349,0.997530245127] cos_1_palm_p22_3:[0.707106781187,0.707527864775] w1_p22_p23_x_4:[0.707106781156,0.707527864775] w1_p22_p23_y_4:[-0.0746326526213,-0.0496855588835] w1_p22_p23_z_4:[0.702301314172,0.705579488566] w2_p22_p23_x_4:[0.958903144366,0.963337156981] w2_p22_p23_y_4:[-0.0299647414063,-0.018844478403] w2_p22_p23_z_4:[0.267631103649,0.282146901402] cos_p22_p23_4:[0.870796562782,0.878756126626] w1_p23_p24_x_5:[0.870890684155,0.878756054632] w1_p23_p24_y_5:[0.0333820792973,0.0507217266463] w1_p23_p24_z_5:[-0.490256114894,-0.474747073529] w2_p23_p24_x_5:[0.999999809903,1] w2_p23_p24_y_5:[-6.51161944637e-05,1.00562376958e-11] w2_p23_p24_z_5:[-0,0.000613127014889] cos_p23_p24_5:[0.870796562782,0.878756126626] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.997600970231,-0.994182873814] uni_v_palm_p32_z_6:[0.0692264705423,0.107707802767] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.707106781156,0.707184636866] w2_palm_p32_y_6:[0.0489853861429,0.0761410552559] w2_palm_p32_z_6:[0.702430830336,0.705669818943] cos_0_palm_p32_6:[0.989734846006,0.994516188104] cos_1_palm_p32_6:[0.707106781187,0.707184636866] w1_p32_p33_x_7:[0.707106781156,0.707184636866] w1_p32_p33_y_7:[0.0489853861429,0.0761410552559] w1_p32_p33_z_7:[0.702430830336,0.705669818943] w2_p32_p33_x_7:[0.999911451623,1] w2_p32_p33_y_7:[-5.58487888959e-06,0.00143329782131] w2_p32_p33_z_7:[-5.15257375252e-05,0.0132300597176] cos_p32_p33_7:[0.707106781187,0.716478540139] w1_p33_p34_x_8:[0.707106781155,0.716478540114] w1_p33_p34_y_8:[-0.0761635260177,-0.0489401529924] w1_p33_p34_z_8:[-0.705428418337,-0.693576030843] w2_p33_p34_x_8:[0.999999997908,1] w2_p33_p34_y_8:[-1.00585144676e-11,6.94163022533e-06] w2_p33_p34_z_8:[-0,6.17944133604e-05] cos_p33_p34_8:[0.707106781187,0.716478540139] w1_palm_p40_x_9:[-0,0] w1_palm_p40_y_9:[-1,-1] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0,0] w2_palm_p40_y_9:[-1,-1] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[1,1] uni_u_p40_p42_x_10:[-0,0] uni_u_p40_p42_y_10:[-0.819149697365,-0.819149697365] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-1,-1] uni_v_p40_p42_y_10:[-0,0] uni_v_p40_p42_z_10:[-0,0] w1_p40_p42_x_10:[-1,-1] w1_p40_p42_y_10:[-0,0] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0,0] w2_p40_p42_y_10:[-0.819158055689,-0.819137786572] w2_p40_p42_z_10:[0.573567851275,0.573596798316] cos_0_p40_p42_10:[1,1] cos_1_p40_p42_10:[1,1] w1_p42_p43_x_11:[-0,0] w1_p42_p43_y_11:[0.573567851275,0.573596798316] w1_p42_p43_z_11:[0.819137786572,0.819158055689] w2_p42_p43_x_11:[-0,0] w2_p42_p43_y_11:[0.573423457018,0.573727167697] w2_p42_p43_z_11:[0.819046495105,0.819259158874] cos_p42_p43_11:[1,1] w1_p43_p44_x_12:[-0,0] w1_p43_p44_y_12:[0.573423457018,0.573727167697] w1_p43_p44_z_12:[0.819046495105,0.819259158874] w2_p43_p44_x_12:[-0,0] w2_p43_p44_y_12:[0.572495839268,0.575147420334] w2_p43_p44_z_12:[0.818049781423,0.819907625308] cos_p43_p44_12:[1,1] sph_w1_p14_X_1_x_13:[0.140020973477,0.145902639942] sph_w1_p14_X_1_y_13:[0.242648261712,0.319677626921] sph_w1_p14_X_1_z_13:[-0.961342666608,-0.936284128256] sph_w2_p14_X_1_x_13:[-5.2369413436e-10,4.17338333234e-11] sph_w2_p14_X_1_y_13:[0.539502318945,0.540402117963] sph_w2_p14_X_1_z_13:[-0.842351364931,-0.841406887333] cos_p14_X_1_13:[0.930937841692,0.966053820244] in_patch_X_1_object_u_14:[0.499999999995,0.548498661715] in_patch_X_1_object_v_14:[0.0971778402998,0.159848149159] in_patch_X_1_object_l_14:[566.733303409,567.492714988] sph_w1_p24_X_2_x_15:[0.140020997103,0.140632185786] sph_w1_p24_X_2_y_15:[0.0695371575517,0.104567386394] sph_w1_p24_X_2_z_15:[-0.987703109256,-0.984525446455] sph_w2_p24_X_2_x_15:[0.0419715361042,0.0426683854141] sph_w2_p24_X_2_y_15:[-1.08221498804e-11,7.43514993672e-10] sph_w2_p24_X_2_z_15:[-0.999118806873,-0.999088380041] cos_p24_X_2_15:[0.989504651897,0.992832282983] in_patch_X_2_object_u_16:[0.382583037296,0.391059376764] in_patch_X_2_object_v_16:[0.382583037097,0.391059394559] in_patch_X_2_object_l_16:[606.043595927,606.307608698] sph_w1_p34_X_3_x_17:[0.14002100441,0.140084077827] sph_w1_p34_X_3_y_17:[-0.106646722962,-0.0685441363059] sph_w1_p34_X_3_z_17:[-0.987773137614,-0.984380065347] sph_w2_p34_X_3_x_17:[-0,0.000428749498102] sph_w2_p34_X_3_y_17:[-0.539656395302,-0.53928658498] sph_w2_p34_X_3_z_17:[-0.842121954759,-0.841885017325] cos_p34_X_3_17:[0.865803733735,0.887867531706] in_patch_X_3_object_u_18:[0.0784611874933,0.105014463422] in_patch_X_3_object_v_18:[0.531570527116,0.554826456542] in_patch_X_3_object_l_18:[567.237437954,567.526026587] sph_w1_palm_X_P_x_19:[1,1] sph_w1_palm_X_P_y_19:[-0,0] sph_w1_palm_X_P_z_19:[-0,0] sph_w2_palm_X_P_x_19:[0.966501311622,0.966640469829] sph_w2_palm_X_P_y_19:[-2.10008040809e-10,1.00000000002e-11] sph_w2_palm_X_P_z_19:[0.2561370834,0.256661673311] cos_palm_X_P_19:[0.966501311622,0.966640469829] in_patch_X_P_object_u_20:[0.368337997455,0.376592203856] in_patch_X_P_object_v_20:[0.530114382851,0.560246123345] in_patch_X_P_object_l_20:[9385.00433991,9385.00434009] p44_r_x:[-9,-9] p44_r_y:[170.190604023,170.20167796] p44_r_z:[177.108936782,177.116690945] }
   2 (err:61.9879 min:8.72795 tm:371):{ 270  p12_u_x:[-0.00364797781379,0.00497788512493] p12_u_y:[-0.309741437775,-0.242617547347] p12_u_z:[0.950533557765,0.970641522234] p12_v_x:[-0,0] p12_v_y:[-0.970907529658,-0.950173533974] p12_v_z:[-0.310588901358,-0.242054964283] p13_u_x:[0.993597109278,0.999296663577] p13_u_y:[-0.0341831049423,-0.00994872020245] p13_u_z:[0.0438338500598,0.108222009251] p13_v_x:[-0,0] p13_v_y:[-0.970907529658,-0.950173533974] p13_v_z:[-0.310588901358,-0.242054964283] p14_u_x:[0.999982225149,1] p14_u_y:[-0.00188653525586,1.05661848025e-11] p14_u_z:[-0,0.0056491288729] p14_v_x:[-0,0] p14_v_y:[-0.970907529658,-0.950173533974] p14_v_z:[-0.310588901358,-0.242054964283] p22_u_x:[-0.000314479522475,0.00122471918759] p22_u_y:[-0.10555367202,-0.0702931838224] p22_u_z:[0.994412856836,0.997526374758] p22_v_x:[-0,0] p22_v_y:[-0.997530245127,-0.994407768696] p22_v_z:[-0.105609494146,-0.0702382552243] p23_u_x:[0.958903145734,0.963337156981] p23_u_y:[-0.0299646864071,-0.018844478403] p23_u_z:[0.267631103649,0.282146901402] p23_v_x:[-0,0] p23_v_y:[-0.997530245127,-0.994407768696] p23_v_z:[-0.105609494146,-0.0702382552243] p24_u_x:[0.999999809903,1] p24_u_y:[-6.5115915457e-05,1.00562376958e-11] p24_u_z:[-0,0.000613127014889] p24_v_x:[-0,0] p24_v_y:[-0.997530245127,-0.994407768696] p24_v_z:[-0.105609494146,-0.0702382552243] p32_u_x:[-0.000371986206312,0.000859639121192] p32_u_y:[0.0692877253978,0.10763944578] p32_u_z:[0.994189638235,0.997596717687] p32_v_x:[-0,0] p32_v_y:[-0.997600970231,-0.994182873814] p32_v_z:[0.0692412941924,0.107707802767] p33_u_x:[0.999911451623,1] p33_u_y:[-5.58487888959e-06,0.00143329782131] p33_u_z:[-5.15257375252e-05,0.0132300597176] p33_v_x:[-0,0] p33_v_y:[-0.997600970231,-0.994182873814] p33_v_z:[0.0692412941924,0.107707802767] p34_u_x:[0.999999997908,1] p34_u_y:[-1.00585144676e-11,6.94163022533e-06] p34_u_z:[-0,6.40737046268e-05] p34_v_x:[-0,0] p34_v_y:[-0.997600970231,-0.994182873814] p34_v_z:[0.0692412941924,0.107707802767] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-1,-1] p40_v_y:[-0,0] p40_v_z:[-0,0] p42_u_x:[-0,0] p42_u_y:[0.573567851275,0.573596798316] p42_u_z:[0.819137786572,0.819158055689] p42_v_x:[-1,-1] p42_v_y:[-0,0] p42_v_z:[-0,0] p43_u_x:[-0,0] p43_u_y:[0.573423457018,0.573727167697] p43_u_z:[0.819046495105,0.819259158874] p43_v_x:[-1,-1] p43_v_y:[-0,0] p43_v_z:[-0,0] p44_u_x:[-0,0] p44_u_y:[0.572495839268,0.575147420334] p44_u_z:[0.818049781423,0.819907625308] p44_v_x:[-1,-1] p44_v_y:[-0,0] p44_v_z:[-0,0] object_u_x:[-0,1.03476999037e-11] object_u_y:[-1,-0.999999999985] object_u_z:[-0,3.90499139206e-11] object_v_x:[0.966516774871,0.966640468068] object_v_y:[-0,1.06552960849e-15] object_v_z:[0.256137083417,0.256603391229] X_P_u_x:[-0,1.10246059228e-15] X_P_u_y:[0.999999999985,1] X_P_u_z:[-0,8.58946458974e-10] X_P_v_x:[-0.256603531342,-0.256137083415] X_P_v_y:[-2.61888689099e-09,0] X_P_v_z:[0.966516772931,0.966640468079] X_1_u_x:[-0,2.11951383699e-11] X_1_u_y:[0.841406887394,0.842461954712] X_1_u_z:[0.5387556186,0.540402118638] X_1_v_x:[0.999999999985,1] X_1_v_y:[-0,1.18848563637e-11] X_1_v_z:[-0,1.85648258165e-11] X_2_u_x:[-0,1.00091245177e-11] X_2_u_y:[0.999999999985,1] X_2_u_z:[-0,2.38256707543e-10] X_2_v_x:[0.999088380046,0.999118806843] X_2_v_y:[-0,1.0004119378e-11] X_2_v_z:[0.0419715360933,0.042689680558] X_3_u_x:[-0,0.000274787392849] X_3_u_y:[0.841885261138,0.842122198513] X_3_u_z:[-0.539656494031,-0.539286683738] X_3_v_x:[0.999999817081,1] X_3_v_y:[-0,0.000326395240859] X_3_v_z:[-0,0.000406613645391] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.970907529658,-0.950173533974] uni_v_palm_p12_z_0:[-0.310588901358,-0.242054964283] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[0.707106781156,0.710849814942] w2_palm_p12_y_0:[-0.21953267881,-0.17173934749] w2_palm_p12_z_0:[0.669053503812,0.687605802628] cos_0_palm_p12_0:[0.93897627746,0.962033454816] cos_1_palm_p12_0:[0.707106781187,0.710849814942] w1_p12_p13_x_1:[0.707106781156,0.710849814942] w1_p12_p13_y_1:[-0.21953267881,-0.17173934749] w1_p12_p13_z_1:[0.669053503812,0.687605802628] w2_p12_p13_x_1:[0.993597109278,0.999296663577] w2_p12_p13_y_1:[-0.0341831049423,-0.00994872020245] w2_p12_p13_z_1:[0.0438338500598,0.108222009251] cos_p12_p13_1:[0.737881047027,0.783565005698] w1_p13_p14_x_2:[0.7378551157,0.783100704241] w1_p13_p14_y_2:[0.153968973923,0.20115736284] w1_p13_p14_z_2:[-0.650809668069,-0.596453687889] w2_p13_p14_x_2:[0.999982225149,1] w2_p13_p14_y_2:[-0.00188653525586,1.05661848025e-11] w2_p13_p14_z_2:[-0,0.0056491288729] cos_p13_p14_2:[0.737881047027,0.783565005698] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.997530245127,-0.994407768696] uni_v_palm_p22_z_3:[-0.105609494146,-0.0702382552243] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.707106781156,0.707527864775] w2_palm_p22_y_3:[-0.0746326526213,-0.0496855588835] w2_palm_p22_z_3:[0.702301314172,0.705579488605] cos_0_palm_p22_3:[0.994407768696,0.997530245127] cos_1_palm_p22_3:[0.707106781187,0.707527864775] w1_p22_p23_x_4:[0.707106781156,0.707527864775] w1_p22_p23_y_4:[-0.0746326526213,-0.0496855588835] w1_p22_p23_z_4:[0.702301314172,0.705579488605] w2_p22_p23_x_4:[0.958903145734,0.963337156981] w2_p22_p23_y_4:[-0.0299646864071,-0.018844478403] w2_p22_p23_z_4:[0.267631103649,0.282146901402] cos_p22_p23_4:[0.870796562782,0.878756126654] w1_p23_p24_x_5:[0.870890684155,0.878756054632] w1_p23_p24_y_5:[0.0333820792973,0.0507217266463] w1_p23_p24_z_5:[-0.490256114894,-0.474747073529] w2_p23_p24_x_5:[0.999999809903,1] w2_p23_p24_y_5:[-6.5115915457e-05,1.00562376958e-11] w2_p23_p24_z_5:[-0,0.000613127014889] cos_p23_p24_5:[0.870796562782,0.878756126654] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.997600970231,-0.994182873814] uni_v_palm_p32_z_6:[0.0692412941924,0.107707802767] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.707106781156,0.70714991508] w2_palm_p32_y_6:[0.048989162222,0.0761410552559] w2_palm_p32_z_6:[0.702430830336,0.705669818943] cos_0_palm_p32_6:[0.989734565868,0.994515662122] cos_1_palm_p32_6:[0.707106781187,0.70714991508] w1_p32_p33_x_7:[0.707106781156,0.70714991508] w1_p32_p33_y_7:[0.048989162222,0.0761410552559] w1_p32_p33_z_7:[0.702430830336,0.705669818943] w2_p32_p33_x_7:[0.999911451623,1] w2_p32_p33_y_7:[-5.58487888959e-06,0.00143329782131] w2_p32_p33_z_7:[-5.15257375252e-05,0.0132300597176] cos_p32_p33_7:[0.707106781187,0.716478540139] w1_p33_p34_x_8:[0.707106781155,0.716478540114] w1_p33_p34_y_8:[-0.0761635260177,-0.0489616363266] w1_p33_p34_z_8:[-0.70542840949,-0.693575939754] w2_p33_p34_x_8:[0.999999997908,1] w2_p33_p34_y_8:[-1.00585144676e-11,6.94163022533e-06] w2_p33_p34_z_8:[-0,6.40737046268e-05] cos_p33_p34_8:[0.707106781187,0.716478540139] w1_palm_p40_x_9:[-0,0] w1_palm_p40_y_9:[-1,-1] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0,0] w2_palm_p40_y_9:[-1,-1] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[1,1] uni_u_p40_p42_x_10:[-0,0] uni_u_p40_p42_y_10:[-0.819149697365,-0.819149697365] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-1,-1] uni_v_p40_p42_y_10:[-0,0] uni_v_p40_p42_z_10:[-0,0] w1_p40_p42_x_10:[-1,-1] w1_p40_p42_y_10:[-0,0] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0,0] w2_p40_p42_y_10:[-0.819158055689,-0.819137786572] w2_p40_p42_z_10:[0.573567851275,0.573596798316] cos_0_p40_p42_10:[1,1] cos_1_p40_p42_10:[1,1] w1_p42_p43_x_11:[-0,0] w1_p42_p43_y_11:[0.573567851275,0.573596798316] w1_p42_p43_z_11:[0.819137786572,0.819158055689] w2_p42_p43_x_11:[-0,0] w2_p42_p43_y_11:[0.573423457018,0.573727167697] w2_p42_p43_z_11:[0.819046495105,0.819259158874] cos_p42_p43_11:[1,1] w1_p43_p44_x_12:[-0,0] w1_p43_p44_y_12:[0.573423457018,0.573727167697] w1_p43_p44_z_12:[0.819046495105,0.819259158874] w2_p43_p44_x_12:[-0,0] w2_p43_p44_y_12:[0.572495839268,0.575147420334] w2_p43_p44_z_12:[0.818049781423,0.819907625308] cos_p43_p44_12:[1,1] sph_w1_p14_X_1_x_13:[0.140020971086,0.145902639942] sph_w1_p14_X_1_y_13:[0.239566650845,0.319677626921] sph_w1_p14_X_1_z_13:[-0.961342666578,-0.940012211409] sph_w2_p14_X_1_x_13:[-5.2369413436e-10,4.17338333234e-11] sph_w2_p14_X_1_y_13:[0.538653046704,0.539749376229] sph_w2_p14_X_1_z_13:[-0.842461954595,-0.84170960469] cos_p14_X_1_13:[0.937660667528,0.966053820244] in_patch_X_1_object_u_14:[0.511816206969,0.586242657639] in_patch_X_1_object_v_14:[0.0423239831912,0.0971778403017] in_patch_X_1_object_l_14:[566.822075766,567.542134742] sph_w1_p24_X_2_x_15:[0.140020997103,0.140632185786] sph_w1_p24_X_2_y_15:[0.0695387099346,0.104569085746] sph_w1_p24_X_2_z_15:[-0.987703109256,-0.984525355552] sph_w2_p24_X_2_x_15:[0.0419715361042,0.042689680547] sph_w2_p24_X_2_y_15:[-1.08221498804e-11,7.43514993672e-10] sph_w2_p24_X_2_z_15:[-0.999118806873,-0.999088380012] cos_p24_X_2_15:[0.989504651897,0.992834876668] in_patch_X_2_object_u_16:[0.382583037296,0.391059376764] in_patch_X_2_object_v_16:[0.382583037097,0.391059394559] in_patch_X_2_object_l_16:[606.043595927,606.247981964] sph_w1_p34_X_3_x_17:[0.140021004432,0.140084077827] sph_w1_p34_X_3_y_17:[-0.106646722962,-0.0685441363059] sph_w1_p34_X_3_z_17:[-0.987773137614,-0.984379740614] sph_w2_p34_X_3_x_17:[-0,0.000342384099715] sph_w2_p34_X_3_y_17:[-0.539656395302,-0.53928658498] sph_w2_p34_X_3_z_17:[-0.842121954759,-0.841885017461] cos_p34_X_3_17:[0.865803733735,0.887867531706] in_patch_X_3_object_u_18:[0.0784611874933,0.103983834258] in_patch_X_3_object_v_18:[0.53219857604,0.554826456542] in_patch_X_3_object_l_18:[567.237437954,567.522323091] sph_w1_palm_X_P_x_19:[1,1] sph_w1_palm_X_P_y_19:[-0,0] sph_w1_palm_X_P_z_19:[-0,0] sph_w2_palm_X_P_x_19:[0.96651677476,0.966640469829] sph_w2_palm_X_P_y_19:[-2.10008040809e-10,1.00000000002e-11] sph_w2_palm_X_P_z_19:[0.2561370834,0.256603531399] cos_palm_X_P_19:[0.96651677476,0.966640469829] in_patch_X_P_object_u_20:[0.368337997455,0.376477287424] in_patch_X_P_object_v_20:[0.530237883417,0.560246123345] in_patch_X_P_object_l_20:[9385.00433991,9385.00434009] p44_r_x:[-9,-9] p44_r_y:[170.190604023,170.20167796] p44_r_z:[177.108936782,177.116690945] }
   3 (err:164.292 min:9.03248 tm:373):{ 270  p12_u_x:[-0.000497433522394,0.00163277155985] p12_u_y:[-0.351138863729,-0.309689288682] p12_u_z:[0.936349652882,0.950885631881] p12_v_x:[-0,0] p12_v_y:[-0.951031432425,-0.936462316142] p12_v_z:[-0.350768200442,-0.309552581006] p13_u_x:[0.999561713085,1] p13_u_y:[-0.0103840658292,0.000203982649731] p13_u_z:[-0.000431650253826,0.0277228875922] p13_v_x:[-0,0] p13_v_y:[-0.951031432425,-0.936462316142] p13_v_z:[-0.350768200442,-0.309552581006] p14_u_x:[0.999999749559,1] p14_u_y:[-0.00024824198237,1.06784862858e-11] p14_u_z:[-0,0.00066274323465] p14_v_x:[-0,0] p14_v_y:[-0.951031432425,-0.936462316142] p14_v_z:[-0.350768200442,-0.309552581006] p22_u_x:[-0.000591810789144,0.00759432552899] p22_u_y:[-0.0782893110479,-0.0322600287318] p22_u_z:[0.996878365734,0.999479509833] p22_v_x:[-0,0] p22_v_y:[-0.999479735257,-0.996877053688] p22_v_z:[-0.0783343192431,-0.0322530438853] p23_u_x:[0.959111765043,0.964293405762] p23_u_y:[-0.0221409261182,-0.00912974019921] p23_u_z:[0.264502705047,0.282146901402] p23_v_x:[-0,0] p23_v_y:[-0.999479735257,-0.996877053688] p23_v_z:[-0.0783343192431,-0.0322530438853] p24_u_x:[0.999975738532,1] p24_u_y:[-0.000551989384512,1.00325752552e-11] p24_u_z:[-0,0.0069435329803] p24_v_x:[-0,0] p24_v_y:[-0.999479735257,-0.996877053688] p24_v_z:[-0.0783343192431,-0.0322530438853] p32_u_x:[-0.00122766341126,0.00543631459237] p32_u_y:[0.108780798397,0.172980372088] p32_u_z:[0.985087822314,0.994271037881] p32_v_x:[-0,0] p32_v_y:[-0.994462771716,-0.98482655456] p32_v_z:[0.108534047249,0.173541514932] p33_u_x:[0.999743517483,1] p33_u_y:[-0.000125881037684,0.00366444804174] p33_u_z:[-0.000714359204913,0.021002145194] p33_v_x:[-0,0] p33_v_y:[-0.994462771716,-0.98482655456] p33_v_z:[0.108534047249,0.173541514932] p34_u_x:[0.999999236456,1] p34_u_y:[-1.01540722616e-11,0.000214452459611] p34_u_z:[-0,0.00121699102949] p34_v_x:[-0,0] p34_v_y:[-0.994462771716,-0.98482655456] p34_v_z:[0.108534047249,0.173541514932] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-1,-1] p40_v_y:[-0,0] p40_v_z:[-0,0] p42_u_x:[-0,0] p42_u_y:[0.573567851059,0.573596798754] p42_u_z:[0.819137786265,0.81915805584] p42_v_x:[-1,-1] p42_v_y:[-0,0] p42_v_z:[-0,0] p43_u_x:[-0,0] p43_u_y:[0.573423430476,0.573727167696] p43_u_z:[0.819046480397,0.819259158873] p43_v_x:[-1,-1] p43_v_y:[-0,0] p43_v_z:[-0,0] p44_u_x:[-0,0] p44_u_y:[0.57249888583,0.574663411209] p44_u_z:[0.818389860532,0.819905498054] p44_v_x:[-1,-1] p44_v_y:[-0,0] p44_v_z:[-0,0] object_u_x:[-0,1.03506889007e-11] object_u_y:[-1,-0.999999999985] object_u_z:[-0,3.88820718485e-11] object_v_x:[0.966222212424,0.966346815568] object_v_y:[-0,1.06552960849e-15] object_v_z:[0.257242749262,0.257698721481] X_P_u_x:[-0,1.10277904482e-15] X_P_u_y:[0.999999999985,1] X_P_u_z:[-0,8.55254585189e-10] X_P_v_x:[-0.257710372732,-0.25724274926] X_P_v_y:[-2.61888689099e-09,0] X_P_v_z:[0.966222212412,0.96634681558] X_1_u_x:[-0,2.11951383699e-11] X_1_u_y:[0.839675297903,0.84020371655] X_1_u_z:[0.542270886007,0.543088753403] X_1_v_x:[0.999999999985,1] X_1_v_y:[-0,1.19093654715e-11] X_1_v_z:[-0,1.84409964242e-11] X_2_u_x:[-0,1.00098195742e-11] X_2_u_y:[0.999999999985,1] X_2_u_z:[-0,2.31625935571e-10] X_2_v_x:[0.999019005883,0.999067608861] X_2_v_y:[-0,1.0004119378e-11] X_2_v_z:[0.043183813456,0.0442834715662] X_3_u_x:[-0,0.000964061657662] X_3_u_y:[0.841542989989,0.841885291343] X_3_u_z:[-0.540189240579,-0.539655655769] X_3_v_x:[0.999997751555,0.999999822158] X_3_v_y:[-0,0.00114558246717] X_3_v_z:[0.000596417346661,0.00178451581571] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.951031432425,-0.936462316142] uni_v_palm_p12_z_0:[-0.350768200442,-0.309552581006] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[0.707106781156,0.707557744692] w2_palm_p12_y_0:[-0.248361348941,-0.218653027686] w2_palm_p12_z_0:[0.661033113391,0.671716723815] cos_0_palm_p12_0:[0.923879532511,0.939844800721] cos_1_palm_p12_0:[0.707106781187,0.707557744692] w1_p12_p13_x_1:[0.707106781156,0.707557744692] w1_p12_p13_y_1:[-0.248361348941,-0.218653027686] w1_p12_p13_z_1:[0.661033113391,0.671716723815] w2_p12_p13_x_1:[0.999561713085,1] w2_p12_p13_y_1:[-0.0103840658292,0.000203982649731] w2_p12_p13_z_1:[-0.000431650253826,0.0277228875922] cos_p12_p13_1:[0.707106781187,0.727955439911] w1_p13_p14_x_2:[0.707106781153,0.727955439908] w1_p13_p14_y_2:[0.218916698224,0.248093000149] w1_p13_p14_z_2:[-0.672629853446,-0.642364584546] w2_p13_p14_x_2:[0.999999749559,1] w2_p13_p14_y_2:[-0.00024824198237,1.06784862858e-11] w2_p13_p14_z_2:[-0,0.00066274323465] cos_p13_p14_2:[0.707106781187,0.727955439911] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.999479735257,-0.996877053688] uni_v_palm_p22_z_3:[-0.0783343192431,-0.0322530438853] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.707106781156,0.711627665195] w2_palm_p22_y_3:[-0.055372249747,-0.0227800111766] w2_palm_p22_z_3:[0.70009816891,0.707157024284] cos_0_palm_p22_3:[0.996877053688,0.999479735257] cos_1_palm_p22_3:[0.707106781187,0.711627665195] w1_p22_p23_x_4:[0.707106781156,0.711627665195] w1_p22_p23_y_4:[-0.055372249747,-0.0227800111766] w1_p22_p23_z_4:[0.70009816891,0.707157024284] w2_p22_p23_x_4:[0.959111765043,0.964293405762] w2_p22_p23_y_4:[-0.0221409261182,-0.00912974019921] w2_p22_p23_z_4:[0.264502705047,0.282146901402] cos_p22_p23_4:[0.868755704143,0.878538021561] w1_p23_p24_x_5:[0.868905276087,0.878445748694] w1_p23_p24_y_5:[0.0151110643281,0.0380131785359] w1_p23_p24_z_5:[-0.493991698288,-0.476568351967] w2_p23_p24_x_5:[0.999975738532,1] w2_p23_p24_y_5:[-0.000551989384512,1.00325752552e-11] w2_p23_p24_z_5:[-0,0.0069435329803] cos_p23_p24_5:[0.868755704143,0.878538021561] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.994462771716,-0.98482655456] uni_v_palm_p32_z_6:[0.108534047249,0.173541514932] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.707106781156,0.707910376735] w2_palm_p32_y_6:[0.0766090394637,0.121932570997] w2_palm_p32_z_6:[0.69403757394,0.702251401294] cos_0_palm_p32_6:[0.978048197493,0.989961532281] cos_1_palm_p32_6:[0.707106781187,0.707910376735] w1_p32_p33_x_7:[0.707106781156,0.707910376735] w1_p32_p33_y_7:[0.0766090394637,0.121932570997] w1_p32_p33_z_7:[0.69403757394,0.702251401294] w2_p32_p33_x_7:[0.999743517483,1] w2_p32_p33_y_7:[-0.000125881037684,0.00366444804174] w2_p32_p33_z_7:[-0.000714359204913,0.021002145194] cos_p32_p33_7:[0.707106781187,0.722948367861] w1_p33_p34_x_8:[0.707106781154,0.722054783962] w1_p33_p34_y_8:[-0.122801393374,-0.0766332470677] w1_p33_p34_z_8:[-0.703292004226,-0.682322328862] w2_p33_p34_x_8:[0.999999236456,1] w2_p33_p34_y_8:[-1.01540722616e-11,0.000214452459611] w2_p33_p34_z_8:[-0,0.00121699102949] cos_p33_p34_8:[0.707106781187,0.722948367861] w1_palm_p40_x_9:[-0,0] w1_palm_p40_y_9:[-1,-1] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0,0] w2_palm_p40_y_9:[-1,-1] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[1,1] uni_u_p40_p42_x_10:[-0,0] uni_u_p40_p42_y_10:[-0.819149697365,-0.819149697365] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-1,-1] uni_v_p40_p42_y_10:[-0,0] uni_v_p40_p42_z_10:[-0,0] w1_p40_p42_x_10:[-1,-1] w1_p40_p42_y_10:[-0,0] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0,0] w2_p40_p42_y_10:[-0.81915805584,-0.819137786265] w2_p40_p42_z_10:[0.573567851059,0.573596798754] cos_0_p40_p42_10:[1,1] cos_1_p40_p42_10:[1,1] w1_p42_p43_x_11:[-0,0] w1_p42_p43_y_11:[0.573567851059,0.573596798754] w1_p42_p43_z_11:[0.819137786265,0.81915805584] w2_p42_p43_x_11:[-0,0] w2_p42_p43_y_11:[0.573423430476,0.573727167696] w2_p42_p43_z_11:[0.819046480397,0.819259158873] cos_p42_p43_11:[1,1] w1_p43_p44_x_12:[-0,0] w1_p43_p44_y_12:[0.573423430476,0.573727167696] w1_p43_p44_z_12:[0.819046480397,0.819259158873] w2_p43_p44_x_12:[-0,0] w2_p43_p44_y_12:[0.57249888583,0.574663411209] w2_p43_p44_z_12:[0.818389860532,0.819905498054] cos_p43_p44_12:[1,1] sph_w1_p14_X_1_x_13:[0.140020999052,0.140726652111] sph_w1_p14_X_1_y_13:[0.306502958211,0.34731261924] sph_w1_p14_X_1_z_13:[-0.941825964211,-0.927143758749] sph_w2_p14_X_1_x_13:[-5.2369413436e-10,4.17338333234e-11] sph_w2_p14_X_1_y_13:[0.542272384254,0.543088752729] sph_w2_p14_X_1_z_13:[-0.840203716344,-0.839675297843] cos_p14_X_1_13:[0.957178301537,0.967863938788] in_patch_X_1_object_u_14:[0.28753801715,0.347942896905] in_patch_X_1_object_v_14:[0.249999999997,0.292254179477] in_patch_X_1_object_l_14:[565.133558844,565.770858294] sph_w1_p24_X_2_x_15:[0.140020998118,0.146925633845] sph_w1_p24_X_2_y_15:[0.0318881291383,0.0797260371415] sph_w1_p24_X_2_z_15:[-0.989633394049,-0.986071978489] sph_w2_p24_X_2_x_15:[0.0431730582023,0.0442834715771] sph_w2_p24_X_2_y_15:[-1.08221498804e-11,7.43514993672e-10] sph_w2_p24_X_2_z_15:[-0.999067608861,-0.999019005878] cos_p24_X_2_15:[0.991015320628,0.99491455346] in_patch_X_2_object_u_16:[0.387158498685,0.406761806499] in_patch_X_2_object_v_16:[0.386982648827,0.40676182391] in_patch_X_2_object_l_16:[606.186032719,606.796746059] sph_w1_p34_X_3_x_17:[0.14002098513,0.141250654968] sph_w1_p34_X_3_y_17:[-0.170365883755,-0.102400776852] sph_w1_p34_X_3_z_17:[-0.984836057129,-0.975158175941] sph_w2_p34_X_3_x_17:[0.000738532784429,0.00141778181521] sph_w2_p34_X_3_y_17:[-0.540189746227,-0.539654442367] sph_w2_p34_X_3_z_17:[-0.84188229398,-0.841511378897] cos_p34_X_3_17:[0.883645586694,0.918244526648] in_patch_X_3_object_u_18:[0.118705614894,0.143428016389] in_patch_X_3_object_v_18:[0.510500889897,0.547390643176] in_patch_X_3_object_l_18:[567.070793637,567.769121302] sph_w1_palm_X_P_x_19:[1,1] sph_w1_palm_X_P_y_19:[-0,0] sph_w1_palm_X_P_z_19:[-0,0] sph_w2_palm_X_P_x_19:[0.966222212378,0.966346815686] sph_w2_palm_X_P_y_19:[-2.10008040809e-10,1.00000000002e-11] sph_w2_palm_X_P_z_19:[0.257242749245,0.257710372746] cos_palm_X_P_19:[0.966222212378,0.966346815686] in_patch_X_P_object_u_20:[0.373906673025,0.382957347824] in_patch_X_P_object_v_20:[0.501633914813,0.539523178761] in_patch_X_P_object_l_20:[9385.00433991,9385.00434009] p44_r_x:[-9,-9] p44_r_y:[170.190603978,170.20167799] p44_r_z:[177.108936318,177.116690953] }
   4 (err:265.901 min:8.72326 tm:374):{ 270  p12_u_x:[-0.00432841921602,0.00535536248316] p12_u_y:[-0.325880343068,-0.247053366505] p12_u_z:[0.945411022781,0.969216271075] p12_v_x:[-0,0] p12_v_y:[-0.969451704476,-0.945090331565] p12_v_z:[-0.326884631251,-0.24641777074] p13_u_x:[0.998923570236,1] p13_u_y:[-0.0147888296407,0.000456236753522] p13_u_z:[-0.00103122582257,0.0439692319777] p13_v_x:[-0,0] p13_v_y:[-0.969451704476,-0.945090331565] p13_v_z:[-0.326884631251,-0.24641777074] p14_u_x:[0.999997858614,1] p14_u_y:[-0.000676382026187,1.05812911591e-11] p14_u_z:[-0,0.00195578907157] p14_v_x:[-0,0] p14_v_y:[-0.969451704476,-0.945090331565] p14_v_z:[-0.326884631251,-0.24641777074] p22_u_x:[-0.000830500209413,0.0143392409729] p22_u_y:[-0.0672102054245,-0.0106519215708] p22_u_z:[0.997697440422,0.999943266689] p22_v_x:[-0,0] p22_v_y:[-0.999943517014,-0.997734862564] p22_v_z:[-0.0672691905237,-0.0106283964786] p23_u_x:[0.959182597799,0.967304739369] p23_u_y:[-0.0190228831207,-0.0026955419731] p23_u_z:[0.253602670568,0.282146901402] p23_v_x:[-0,0] p23_v_y:[-0.999943517014,-0.997734862564] p23_v_z:[-0.0672691905237,-0.0106283964786] p24_u_x:[0.999967073153,1] p24_u_y:[-0.000545886814573,1.00227027994e-11] p24_u_z:[-0,0.00809657871121] p24_v_x:[-0,0] p24_v_y:[-0.999943517014,-0.997734862564] p24_v_z:[-0.0672691905237,-0.0106283964786] p32_u_x:[-0.000734691372056,0.00771350765052] p32_u_y:[0.138546457766,0.190725927998] p32_u_z:[0.981623890666,0.990499244957] p32_v_x:[-0,0] p32_v_y:[-0.990523034288,-0.981699884436] p32_v_z:[0.13847123502,0.190434599982] p33_u_x:[0.999731249563,1] p33_u_y:[-4.61085477306e-05,0.00440019695132] p33_u_z:[-0.000223833710407,0.0226595143315] p33_v_x:[-0,0] p33_v_y:[-0.990523034288,-0.981699884436] p33_v_z:[0.13847123502,0.190434599982] p34_u_x:[0.999999770548,1] p34_u_y:[-1.01864125265e-11,0.000129000812476] p34_u_z:[-0,0.000665005585707] p34_v_x:[-0,0] p34_v_y:[-0.990523034288,-0.981699884436] p34_v_z:[0.13847123502,0.190434599982] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-1,-1] p40_v_y:[-0,0] p40_v_z:[-0,0] p42_u_x:[-0,0] p42_u_y:[0.573567851328,0.573596798171] p42_u_z:[0.819137786673,0.819158055652] p42_v_x:[-1,-1] p42_v_y:[-0,0] p42_v_z:[-0,0] p43_u_x:[-0,0] p43_u_y:[0.573423350792,0.573727230724] p43_u_z:[0.819046436247,0.819259214647] p43_v_x:[-1,-1] p43_v_y:[-0,0] p43_v_z:[-0,0] p44_u_x:[-0,0] p44_u_y:[0.572499955299,0.57466341145] p44_u_z:[0.818390634423,0.819905498267] p44_v_x:[-1,-1] p44_v_y:[-0,0] p44_v_z:[-0,0] object_u_x:[-0,1.03495396073e-11] object_u_y:[-1,-0.999999999985] object_u_z:[-0,3.89942367626e-11] object_v_x:[0.966329509251,0.966499133595] object_v_y:[-0,1.06552960849e-15] object_v_z:[0.256648885132,0.257307752592] X_P_u_x:[-0,1.10265659726e-15] X_P_u_y:[0.999999999985,1] X_P_u_z:[-0,8.57743350105e-10] X_P_v_x:[-0.257307752596,-0.256669965681] X_P_v_y:[-2.61888689099e-09,0] X_P_v_z:[0.966329509239,0.966499133823] X_1_u_x:[-0,2.11951383699e-11] X_1_u_y:[0.840535168316,0.841101782162] X_1_u_z:[0.540876873292,0.541757179647] X_1_v_x:[0.999999999985,1] X_1_v_y:[-0,1.18981666204e-11] X_1_v_z:[-0,1.84884961696e-11] X_2_u_x:[-0,1.00098698534e-11] X_2_u_y:[0.999999999985,1] X_2_u_z:[-0,2.34757239933e-10] X_2_v_x:[0.999013987847,0.999092327556] X_2_v_y:[-0,1.0004119378e-11] X_2_v_z:[0.0426131451673,0.0443965320269] X_3_u_x:[-0,0.000637052132285] X_3_u_y:[0.84120261431,0.841748981369] X_3_u_z:[-0.54070878266,-0.53986864856] X_3_v_x:[0.99999910821,1] X_3_v_y:[-0,0.000628980001363] X_3_v_z:[-0,0.00117810569388] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.969451704476,-0.945090331565] uni_v_palm_p12_z_0:[-0.326884631251,-0.24641777074] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[0.707106781156,0.708377729831] w2_palm_p12_y_0:[-0.230916568927,-0.174780737838] w2_palm_p12_z_0:[0.66621422089,0.686576408881] cos_0_palm_p12_0:[0.933324695474,0.960428837612] cos_1_palm_p12_0:[0.707106781187,0.708377729831] w1_p12_p13_x_1:[0.707106781156,0.708377729831] w1_p12_p13_y_1:[-0.230916568927,-0.174780737838] w1_p12_p13_z_1:[0.66621422089,0.686576408881] w2_p12_p13_x_1:[0.998923570236,1] w2_p12_p13_y_1:[-0.0147888296407,0.000456236753522] w2_p12_p13_z_1:[-0.00103122582257,0.0439692319777] cos_p12_p13_1:[0.707106781187,0.739272814261] w1_p13_p14_x_2:[0.707106781153,0.739272814234] w1_p13_p14_y_2:[0.172755677385,0.226257164319] w1_p13_p14_z_2:[-0.685923201834,-0.640821184104] w2_p13_p14_x_2:[0.999997858614,1] w2_p13_p14_y_2:[-0.000676382026187,1.05812911591e-11] w2_p13_p14_z_2:[-0,0.00195578907157] cos_p13_p14_2:[0.707106781187,0.739272814261] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.999943517014,-0.997734862564] uni_v_palm_p22_z_3:[-0.0672691905237,-0.0106283964786] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.707106781156,0.717771173586] w2_palm_p22_y_3:[-0.0475494089424,-0.00737323621083] w2_palm_p22_z_3:[0.695777241452,0.707654038053] cos_0_palm_p22_3:[0.997734862564,0.999943517014] cos_1_palm_p22_3:[0.707106781187,0.717771173586] w1_p22_p23_x_4:[0.707106781156,0.717771173586] w1_p22_p23_y_4:[-0.0475494089424,-0.00737323621083] w1_p22_p23_z_4:[0.695777241452,0.707654038053] w2_p22_p23_x_4:[0.959182597799,0.967304739369] w2_p22_p23_y_4:[-0.0190228831207,-0.0026955419731] w2_p22_p23_z_4:[0.253602670568,0.282146901402] cos_p22_p23_4:[0.863067017556,0.878410689079] w1_p23_p24_x_5:[0.863202472703,0.878409115288] w1_p23_p24_y_5:[0.00447152138253,0.0329285719851] w1_p23_p24_z_5:[-0.504377450154,-0.477200214988] w2_p23_p24_x_5:[0.999967073153,1] w2_p23_p24_y_5:[-0.000545886814573,1.00227027994e-11] w2_p23_p24_z_5:[-0,0.00809657871121] cos_p23_p24_5:[0.863067017556,0.878410689079] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.990523034288,-0.981699884436] uni_v_palm_p32_z_6:[0.13847123502,0.190434599982] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.707106781156,0.711416800441] w2_palm_p32_y_6:[0.0979761674762,0.134921887457] w2_palm_p32_z_6:[0.688837917853,0.700903713838] cos_0_palm_p32_6:[0.974324045275,0.984985558803] cos_1_palm_p32_6:[0.707106781187,0.711416800441] w1_p32_p33_x_7:[0.707106781156,0.711416800441] w1_p32_p33_y_7:[0.0979761674762,0.134921887457] w1_p32_p33_z_7:[0.688837917853,0.700903713838] w2_p32_p33_x_7:[0.999731249563,1] w2_p32_p33_y_7:[-4.61085477306e-05,0.00440019695132] w2_p32_p33_z_7:[-0.000223833710407,0.0226595143315] cos_p32_p33_7:[0.707106781187,0.723483959343] w1_p33_p34_x_8:[0.707106781153,0.72334209626] w1_p33_p34_y_8:[-0.134676954284,-0.0979125442842] w1_p33_p34_z_8:[-0.700483796469,-0.678184777766] w2_p33_p34_x_8:[0.999999770548,1] w2_p33_p34_y_8:[-1.01864125265e-11,0.000129000812476] w2_p33_p34_z_8:[-0,0.000665005585707] cos_p33_p34_8:[0.707106781187,0.723483959343] w1_palm_p40_x_9:[-0,0] w1_palm_p40_y_9:[-1,-1] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0,0] w2_palm_p40_y_9:[-1,-1] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[1,1] uni_u_p40_p42_x_10:[-0,0] uni_u_p40_p42_y_10:[-0.819149697365,-0.819149697365] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-1,-1] uni_v_p40_p42_y_10:[-0,0] uni_v_p40_p42_z_10:[-0,0] w1_p40_p42_x_10:[-1,-1] w1_p40_p42_y_10:[-0,0] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0,0] w2_p40_p42_y_10:[-0.819158055652,-0.819137786673] w2_p40_p42_z_10:[0.573567851328,0.573596798171] cos_0_p40_p42_10:[1,1] cos_1_p40_p42_10:[1,1] w1_p42_p43_x_11:[-0,0] w1_p42_p43_y_11:[0.573567851328,0.573596798171] w1_p42_p43_z_11:[0.819137786673,0.819158055652] w2_p42_p43_x_11:[-0,0] w2_p42_p43_y_11:[0.573423350792,0.573727230724] w2_p42_p43_z_11:[0.819046436247,0.819259214647] cos_p42_p43_11:[1,1] w1_p43_p44_x_12:[-0,0] w1_p43_p44_y_12:[0.573423350792,0.573727230724] w1_p43_p44_z_12:[0.819046436247,0.819259214647] w2_p43_p44_x_12:[-0,0] w2_p43_p44_y_12:[0.572499955299,0.57466341145] w2_p43_p44_z_12:[0.818390634423,0.819905498267] cos_p43_p44_12:[1,1] sph_w1_p14_X_1_x_13:[0.140020962471,0.142094530506] sph_w1_p14_X_1_y_13:[0.242799142267,0.323664338249] sph_w1_p14_X_1_z_13:[-0.959901183439,-0.935478126413] sph_w2_p14_X_1_x_13:[-5.2369413436e-10,4.17338333234e-11] sph_w2_p14_X_1_y_13:[0.540876873313,0.541750061765] sph_w2_p14_X_1_z_13:[-0.841058453415,-0.84053516843] cos_p14_X_1_13:[0.935422928015,0.962798797024] in_patch_X_1_object_u_14:[0.37282962293,0.428933095316] in_patch_X_1_object_v_14:[0.16583606857,0.211600333909] in_patch_X_1_object_l_14:[565.736774464,566.649366127] sph_w1_p24_X_2_x_15:[0.140020995867,0.148063027873] sph_w1_p24_X_2_y_15:[0.0104469090538,0.06659522475] sph_w1_p24_X_2_z_15:[-0.990092607004,-0.986739491215] sph_w2_p24_X_2_x_15:[0.0426071913122,0.0443607338733] sph_w2_p24_X_2_y_15:[-1.08221498804e-11,7.43514993672e-10] sph_w2_p24_X_2_z_15:[-0.999092327586,-0.999013987812] cos_p24_X_2_15:[0.992085871719,0.995408710345] in_patch_X_2_object_u_16:[0.382475928448,0.419243443715] in_patch_X_2_object_v_16:[0.382475928246,0.419243443512] in_patch_X_2_object_l_16:[606.128275376,607.184344812] sph_w1_p34_X_3_x_17:[0.140020983703,0.140694755286] sph_w1_p34_X_3_y_17:[-0.188558539886,-0.135975548816] sph_w1_p34_X_3_z_17:[-0.98076492975,-0.971935363059] sph_w2_p34_X_3_x_17:[2.32177835683e-05,0.000991270122661] sph_w2_p34_X_3_y_17:[-0.540743026445,-0.539868166642] sph_w2_p34_X_3_z_17:[-0.84174473211,-0.841202614548] cos_p34_X_3_17:[0.891080491552,0.920537625706] in_patch_X_3_object_u_18:[0.109947266769,0.171424067421] in_patch_X_3_object_v_18:[0.468833005681,0.510500889907] in_patch_X_3_object_l_18:[566.691881393,567.49673727] sph_w1_palm_X_P_x_19:[1,1] sph_w1_palm_X_P_y_19:[-0,0] sph_w1_palm_X_P_z_19:[-0,0] sph_w2_palm_X_P_x_19:[0.96632950908,0.96649913541] sph_w2_palm_X_P_y_19:[-2.10008040809e-10,1.00000000002e-11] sph_w2_palm_X_P_z_19:[0.256648885047,0.25730775261] cos_palm_X_P_19:[0.96632950908,0.96649913541] in_patch_X_P_object_u_20:[0.375351395861,0.386662855136] in_patch_X_P_object_v_20:[0.485827951251,0.529718233908] in_patch_X_P_object_l_20:[9385.00433991,9385.00434009] p44_r_x:[-9,-9] p44_r_y:[170.190601567,170.201679841] p44_r_z:[177.108935021,177.116692614] }


Cuik executed in 31 (31) child processors
STATITISTICS FOR Cuik:

Volume of the search space: 2.69285e+18
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 0.268161
Number of processors: 32
User time in process: 375.000000 seg (6.250000 min)
Box level information:
  N processed boxes :   1329
  Max depth         :     50
  Types of boxes:
    N solution boxes:      4 (0) ( 0.30%)
    N empty boxes   :    128  ( 9.63%)
    N bisected boxes:   1197  (90.07%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :   1683
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

