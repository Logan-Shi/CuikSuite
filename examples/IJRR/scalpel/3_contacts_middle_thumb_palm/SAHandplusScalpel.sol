
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
Equations from file: /home/porta/cuik/CuikSuite/examples/IJRR/scalpel/3_contacts_middle_thumb_palm/SAHandplusScalpel_kin.cuik
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
   X_4_u_x : [-1,1]
   X_4_u_y : [-1,1]
   X_4_u_z : [-1,1]
   X_4_v_x : [-1,1]
   X_4_v_y : [-1,1]
   X_4_v_z : [-1,1]

[DUMMY VARS]
   X_4_w_x : [-1,1]
   X_4_w_y : [-1,1]
   X_4_w_z : [-1,1]
   X_4_wp_x : [-1,1]
   X_4_wp_y : [-1,1]
   X_4_wp_z : [-1,1]

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
   cos_0_palm_p12_0 : [1,1]
   cos_1_palm_p12_0 : [1,1]
   w1_p12_p13_x_1 : [-1,1]
   w1_p12_p13_y_1 : [-1,1]
   w1_p12_p13_z_1 : [-1,1]
   w2_p12_p13_x_1 : [-1,1]
   w2_p12_p13_y_1 : [-1,1]
   w2_p12_p13_z_1 : [-1,1]
   cos_p12_p13_1 : [1,1]
   w1_p13_p14_x_2 : [-1,1]
   w1_p13_p14_y_2 : [-1,1]
   w1_p13_p14_z_2 : [-1,1]
   w2_p13_p14_x_2 : [-1,1]
   w2_p13_p14_y_2 : [-1,1]
   w2_p13_p14_z_2 : [-1,1]
   cos_p13_p14_2 : [1,1]
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
   cos_0_palm_p32_6 : [1,1]
   cos_1_palm_p32_6 : [1,1]
   w1_p32_p33_x_7 : [-1,1]
   w1_p32_p33_y_7 : [-1,1]
   w1_p32_p33_z_7 : [-1,1]
   w2_p32_p33_x_7 : [-1,1]
   w2_p32_p33_y_7 : [-1,1]
   w2_p32_p33_z_7 : [-1,1]
   cos_p32_p33_7 : [1,1]
   w1_p33_p34_x_8 : [-1,1]
   w1_p33_p34_y_8 : [-1,1]
   w1_p33_p34_z_8 : [-1,1]
   w2_p33_p34_x_8 : [-1,1]
   w2_p33_p34_y_8 : [-1,1]
   w2_p33_p34_z_8 : [-1,1]
   cos_p33_p34_8 : [1,1]
   w1_palm_p40_x_9 : [-1,1]
   w1_palm_p40_y_9 : [-1,1]
   w1_palm_p40_z_9 : [-1,1]
   w2_palm_p40_x_9 : [-1,1]
   w2_palm_p40_y_9 : [-1,1]
   w2_palm_p40_z_9 : [-1,1]
   cos_palm_p40_9 : [0.707106781187,1]
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
   cos_0_p40_p42_10 : [0.923879532511,1]
   cos_1_p40_p42_10 : [0.707106781187,1]
   w1_p42_p43_x_11 : [-1,1]
   w1_p42_p43_y_11 : [-1,1]
   w1_p42_p43_z_11 : [-1,1]
   w2_p42_p43_x_11 : [-1,1]
   w2_p42_p43_y_11 : [-1,1]
   w2_p42_p43_z_11 : [-1,1]
   cos_p42_p43_11 : [0.707106781187,1]
   w1_p43_p44_x_12 : [-1,1]
   w1_p43_p44_y_12 : [-1,1]
   w1_p43_p44_z_12 : [-1,1]
   w2_p43_p44_x_12 : [-1,1]
   w2_p43_p44_y_12 : [-1,1]
   w2_p43_p44_z_12 : [-1,1]
   cos_p43_p44_12 : [0.707106781187,1]
   sph_w1_p24_X_2_x_13 : [-1,1]
   sph_w1_p24_X_2_y_13 : [-1,1]
   sph_w1_p24_X_2_z_13 : [-1,1]
   sph_w2_p24_X_2_x_13 : [-1,1]
   sph_w2_p24_X_2_y_13 : [-1,1]
   sph_w2_p24_X_2_z_13 : [-1,1]
   cos_p24_X_2_13 : [-1,1]

[SYSTEM VARS]
   in_patch_X_2_object_u_14 : [0,1]
   in_patch_X_2_object_v_14 : [0,1]

[DUMMY VARS]
   in_patch_X_2_object_w_14 : [0,1]

[SECONDARY VARS]
   in_patch_X_2_object_l_14 : [9.55155098744,9.55155098744]
   sph_w1_p44_X_4_x_15 : [-1,1]
   sph_w1_p44_X_4_y_15 : [-1,1]
   sph_w1_p44_X_4_z_15 : [-1,1]
   sph_w2_p44_X_4_x_15 : [-1,1]
   sph_w2_p44_X_4_y_15 : [-1,1]
   sph_w2_p44_X_4_z_15 : [-1,1]
   cos_p44_X_4_15 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_4_object_u_16 : [0,1]
   in_patch_X_4_object_v_16 : [0,1]

[DUMMY VARS]
   in_patch_X_4_object_w_16 : [0,1]

[SECONDARY VARS]
   in_patch_X_4_object_l_16 : [9.68483120378,9.74728773384]
   sph_w1_palm_X_P_x_17 : [-1,1]
   sph_w1_palm_X_P_y_17 : [-1,1]
   sph_w1_palm_X_P_z_17 : [-1,1]
   sph_w2_palm_X_P_x_17 : [-1,1]
   sph_w2_palm_X_P_y_17 : [-1,1]
   sph_w2_palm_X_P_z_17 : [-1,1]
   cos_palm_X_P_17 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_P_object_u_18 : [0,1]
   in_patch_X_P_object_v_18 : [0,1]

[DUMMY VARS]
   in_patch_X_P_object_w_18 : [0,1]

[SECONDARY VARS]
   in_patch_X_P_object_l_18 : [172.585556066,172.585556066]

[CARTESIAN VARS]
   p14_r_x : [-1710.10398103,1710.10398103]
   p14_r_y : [-1710.10398103,1710.10398103]
   p14_r_z : [-1710.10398103,1710.10398103]
   p34_r_x : [-1710.10398103,1710.10398103]
   p34_r_y : [-1710.10398103,1710.10398103]
   p34_r_z : [-1710.10398103,1710.10398103]

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
   X_2_u_x^2+X_2_u_y^2+X_2_u_z^2 = 1;
   X_2_v_x^2+X_2_v_y^2+X_2_v_z^2 = 1;
   X_2_u_x*X_2_v_x+X_2_u_y*X_2_v_y+X_2_u_z*X_2_v_z = 0;
   X_4_u_x^2+X_4_u_y^2+X_4_u_z^2 = 1;
   X_4_v_x^2+X_4_v_y^2+X_4_v_z^2 = 1;
   X_4_u_x*X_4_v_x+X_4_u_y*X_4_v_y+X_4_u_z*X_4_v_z = 0;
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
   p12_w_x-p12_wp_x-w2_palm_p12_x_0 = -0;
   p12_w_y-p12_wp_y-w2_palm_p12_y_0 = -0;
   p12_w_z-p12_wp_z-w2_palm_p12_z_0 = -0;
   uni_v_palm_p12_x_0*w1_palm_p12_x_0+uni_v_palm_p12_y_0*w1_palm_p12_y_0+uni_v_palm_p12_z_0*w1_palm_p12_z_0-cos_0_palm_p12_0 = 0;
   uni_u_palm_p12_x_0*w2_palm_p12_x_0+uni_u_palm_p12_y_0*w2_palm_p12_y_0+uni_u_palm_p12_z_0*w2_palm_p12_z_0-cos_1_palm_p12_0 = 0;
   p12_v_x-p13_v_x = -0;
   p12_v_y-p13_v_y = -0;
   p12_v_z-p13_v_z = -0;
   p12_u_x-w1_p12_p13_x_1 = -0;
   p12_u_y-w1_p12_p13_y_1 = -0;
   p12_u_z-w1_p12_p13_z_1 = -0;
   p13_u_x-w2_p12_p13_x_1 = -0;
   p13_u_y-w2_p12_p13_y_1 = -0;
   p13_u_z-w2_p12_p13_z_1 = -0;
   w1_p12_p13_x_1*w2_p12_p13_x_1+w1_p12_p13_y_1*w2_p12_p13_y_1+w1_p12_p13_z_1*w2_p12_p13_z_1-cos_p12_p13_1 = 0;
   p13_v_x-p14_v_x = -0;
   p13_v_y-p14_v_y = -0;
   p13_v_z-p14_v_z = -0;
   p13_u_x-w1_p13_p14_x_2 = -0;
   p13_u_y-w1_p13_p14_y_2 = -0;
   p13_u_z-w1_p13_p14_z_2 = -0;
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
   p32_w_x-p32_wp_x-w2_palm_p32_x_6 = -0;
   p32_w_y-p32_wp_y-w2_palm_p32_y_6 = -0;
   p32_w_z-p32_wp_z-w2_palm_p32_z_6 = -0;
   uni_v_palm_p32_x_6*w1_palm_p32_x_6+uni_v_palm_p32_y_6*w1_palm_p32_y_6+uni_v_palm_p32_z_6*w1_palm_p32_z_6-cos_0_palm_p32_6 = 0;
   uni_u_palm_p32_x_6*w2_palm_p32_x_6+uni_u_palm_p32_y_6*w2_palm_p32_y_6+uni_u_palm_p32_z_6*w2_palm_p32_z_6-cos_1_palm_p32_6 = 0;
   p32_v_x-p33_v_x = -0;
   p32_v_y-p33_v_y = -0;
   p32_v_z-p33_v_z = -0;
   p32_u_x-w1_p32_p33_x_7 = -0;
   p32_u_y-w1_p32_p33_y_7 = -0;
   p32_u_z-w1_p32_p33_z_7 = -0;
   p33_u_x-w2_p32_p33_x_7 = -0;
   p33_u_y-w2_p32_p33_y_7 = -0;
   p33_u_z-w2_p32_p33_z_7 = -0;
   w1_p32_p33_x_7*w2_p32_p33_x_7+w1_p32_p33_y_7*w2_p32_p33_y_7+w1_p32_p33_z_7*w2_p32_p33_z_7-cos_p32_p33_7 = 0;
   p33_v_x-p34_v_x = -0;
   p33_v_y-p34_v_y = -0;
   p33_v_z-p34_v_z = -0;
   p33_u_x-w1_p33_p34_x_8 = -0;
   p33_u_y-w1_p33_p34_y_8 = -0;
   p33_u_z-w1_p33_p34_z_8 = -0;
   p34_u_x-w2_p33_p34_x_8 = -0;
   p34_u_y-w2_p33_p34_y_8 = -0;
   p34_u_z-w2_p33_p34_z_8 = -0;
   w1_p33_p34_x_8*w2_p33_p34_x_8+w1_p33_p34_y_8*w2_p33_p34_y_8+w1_p33_p34_z_8*w2_p33_p34_z_8-cos_p33_p34_8 = 0;
   p40_u_x = 0;
   p40_u_y = 0;
   p40_u_z = 1;
   w1_palm_p40_x_9 = -0.707106781187;
   w1_palm_p40_y_9 = -0.707106781187;
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
   0.707106781187*p42_u_x+0.707106781187*p42_w_x-0.707106781187*p42_wp_x-w2_p40_p42_x_10 = -0;
   0.707106781187*p42_u_y+0.707106781187*p42_w_y-0.707106781187*p42_wp_y-w2_p40_p42_y_10 = -0;
   0.707106781187*p42_u_z+0.707106781187*p42_w_z-0.707106781187*p42_wp_z-w2_p40_p42_z_10 = -0;
   uni_v_p40_p42_x_10*w1_p40_p42_x_10+uni_v_p40_p42_y_10*w1_p40_p42_y_10+uni_v_p40_p42_z_10*w1_p40_p42_z_10-cos_0_p40_p42_10 = 0;
   uni_u_p40_p42_x_10*w2_p40_p42_x_10+uni_u_p40_p42_y_10*w2_p40_p42_y_10+uni_u_p40_p42_z_10*w2_p40_p42_z_10-cos_1_p40_p42_10 = 0;
   p42_v_x-p43_v_x = -0;
   p42_v_y-p43_v_y = -0;
   p42_v_z-p43_v_z = -0;
   0.707106781187*p42_u_x+0.707106781187*p42_w_x-0.707106781187*p42_wp_x-w1_p42_p43_x_11 = -0;
   0.707106781187*p42_u_y+0.707106781187*p42_w_y-0.707106781187*p42_wp_y-w1_p42_p43_y_11 = -0;
   0.707106781187*p42_u_z+0.707106781187*p42_w_z-0.707106781187*p42_wp_z-w1_p42_p43_z_11 = -0;
   p43_u_x-w2_p42_p43_x_11 = -0;
   p43_u_y-w2_p42_p43_y_11 = -0;
   p43_u_z-w2_p42_p43_z_11 = -0;
   w1_p42_p43_x_11*w2_p42_p43_x_11+w1_p42_p43_y_11*w2_p42_p43_y_11+w1_p42_p43_z_11*w2_p42_p43_z_11-cos_p42_p43_11 = 0;
   p43_v_x-p44_v_x = -0;
   p43_v_y-p44_v_y = -0;
   p43_v_z-p44_v_z = -0;
   0.707106781187*p43_u_x+0.707106781187*p43_w_x-0.707106781187*p43_wp_x-w1_p43_p44_x_12 = -0;
   0.707106781187*p43_u_y+0.707106781187*p43_w_y-0.707106781187*p43_wp_y-w1_p43_p44_y_12 = -0;
   0.707106781187*p43_u_z+0.707106781187*p43_w_z-0.707106781187*p43_wp_z-w1_p43_p44_z_12 = -0;
   p44_u_x-w2_p43_p44_x_12 = -0;
   p44_u_y-w2_p43_p44_y_12 = -0;
   p44_u_z-w2_p43_p44_z_12 = -0;
   w1_p43_p44_x_12*w2_p43_p44_x_12+w1_p43_p44_y_12*w2_p43_p44_y_12+w1_p43_p44_z_12*w2_p43_p44_z_12-cos_p43_p44_12 = 0;
   0.140021004726*p24_u_x+0.990148533421*p24_w_x-0.990148533421*p24_wp_x-sph_w1_p24_X_2_x_13 = -0;
   0.140021004726*p24_u_y+0.990148533421*p24_w_y-0.990148533421*p24_wp_y-sph_w1_p24_X_2_y_13 = -0;
   0.140021004726*p24_u_z+0.990148533421*p24_w_z-0.990148533421*p24_wp_z-sph_w1_p24_X_2_z_13 = -0;
   X_2_w_x-X_2_wp_x-sph_w2_p24_X_2_x_13 = -0;
   X_2_w_y-X_2_wp_y-sph_w2_p24_X_2_y_13 = -0;
   X_2_w_z-X_2_wp_z-sph_w2_p24_X_2_z_13 = -0;
   sph_w1_p24_X_2_x_13*sph_w2_p24_X_2_x_13+sph_w1_p24_X_2_y_13*sph_w2_p24_X_2_y_13+sph_w1_p24_X_2_z_13*sph_w2_p24_X_2_z_13-cos_p24_X_2_13 = 0;
   in_patch_X_2_object_l_14^2 = 91.2321262656;
   X_2_w_x*in_patch_X_2_object_l_14-X_2_wp_x*in_patch_X_2_object_l_14+9.5052*object_u_x-0.93984*object_w_x+0.93984*object_wp_x = 0;
   X_2_w_y*in_patch_X_2_object_l_14-X_2_wp_y*in_patch_X_2_object_l_14+9.5052*object_u_y-0.93984*object_w_y+0.93984*object_wp_y = 0;
   X_2_w_z*in_patch_X_2_object_l_14-X_2_wp_z*in_patch_X_2_object_l_14+9.5052*object_u_z-0.93984*object_w_z+0.93984*object_wp_z = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_15 = -0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_15 = -0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_15 = -0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_15 = -0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_15 = -0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_15 = -0;
   sph_w1_p44_X_4_x_15*sph_w2_p44_X_4_x_15+sph_w1_p44_X_4_y_15*sph_w2_p44_X_4_y_15+sph_w1_p44_X_4_z_15*sph_w2_p44_X_4_z_15-cos_p44_X_4_15 = 0;
   0.003851459072*in_patch_X_4_object_v_16^2-in_patch_X_4_object_l_16^2-1.20981126144*in_patch_X_4_object_v_16 = -95.0057667072;
   0.006256*object_u_x*in_patch_X_4_object_v_16-0.061744*object_w_x*in_patch_X_4_object_v_16+0.061744*object_wp_x*in_patch_X_4_object_v_16+X_4_w_x*in_patch_X_4_object_l_16-X_4_wp_x*in_patch_X_4_object_l_16-0.98256*object_u_x+9.69744*object_w_x-9.69744*object_wp_x = 0;
   0.006256*object_u_y*in_patch_X_4_object_v_16-0.061744*object_w_y*in_patch_X_4_object_v_16+0.061744*object_wp_y*in_patch_X_4_object_v_16+X_4_w_y*in_patch_X_4_object_l_16-X_4_wp_y*in_patch_X_4_object_l_16-0.98256*object_u_y+9.69744*object_w_y-9.69744*object_wp_y = 0;
   0.006256*object_u_z*in_patch_X_4_object_v_16-0.061744*object_w_z*in_patch_X_4_object_v_16+0.061744*object_wp_z*in_patch_X_4_object_v_16+X_4_w_z*in_patch_X_4_object_l_16-X_4_wp_z*in_patch_X_4_object_l_16-0.98256*object_u_z+9.69744*object_w_z-9.69744*object_wp_z = 0;
   sph_w1_palm_X_P_x_17 = 0.707106781187;
   sph_w1_palm_X_P_y_17 = 0.707106781187;
   sph_w1_palm_X_P_z_17 = 0;
   X_P_w_x-X_P_wp_x-sph_w2_palm_X_P_x_17 = -0;
   X_P_w_y-X_P_wp_y-sph_w2_palm_X_P_y_17 = -0;
   X_P_w_z-X_P_wp_z-sph_w2_palm_X_P_z_17 = -0;
   sph_w1_palm_X_P_x_17*sph_w2_palm_X_P_x_17+sph_w1_palm_X_P_y_17*sph_w2_palm_X_P_y_17+sph_w1_palm_X_P_z_17*sph_w2_palm_X_P_z_17-cos_palm_X_P_17 = 0;
   in_patch_X_P_object_l_18^2 = 29785.7741625;
   X_P_w_x*in_patch_X_P_object_l_18-X_P_wp_x*in_patch_X_P_object_l_18+171.706432*object_u_x+17.397568*object_w_x-17.397568*object_wp_x = 0;
   X_P_w_y*in_patch_X_P_object_l_18-X_P_wp_y*in_patch_X_P_object_l_18+171.706432*object_u_y+17.397568*object_w_y-17.397568*object_wp_y = 0;
   X_P_w_z*in_patch_X_P_object_l_18-X_P_wp_z*in_patch_X_P_object_l_18+171.706432*object_u_z+17.397568*object_w_z-17.397568*object_wp_z = 0;
   0.176*object_u_x*in_patch_X_2_object_v_14+1.816*object_u_x*in_patch_X_4_object_v_16-5.34*object_v_x*in_patch_X_2_object_u_14+5.34*object_v_x*in_patch_X_4_object_u_16-0.034*object_v_x*in_patch_X_4_object_w_16+1.78*object_w_x*in_patch_X_2_object_v_14+0.184*object_w_x*in_patch_X_4_object_v_16-1.78*object_wp_x*in_patch_X_2_object_v_14-0.184*object_wp_x*in_patch_X_4_object_v_16-67.8*p22_u_x-30*p23_u_x-20*p24_u_x+97*p40_u_x+6*p40_v_x-87*p40_w_x+87*p40_wp_x+67.8*p42_u_x+30*p43_u_x+20*p44_u_x+8.876*object_u_x-10.836*object_w_x+10.836*object_wp_x-13*X_2_w_x+13*X_2_wp_x+13*X_4_w_x-13*X_4_wp_x = -1.3;
   0.176*object_u_y*in_patch_X_2_object_v_14+1.816*object_u_y*in_patch_X_4_object_v_16-5.34*object_v_y*in_patch_X_2_object_u_14+5.34*object_v_y*in_patch_X_4_object_u_16-0.034*object_v_y*in_patch_X_4_object_w_16+1.78*object_w_y*in_patch_X_2_object_v_14+0.184*object_w_y*in_patch_X_4_object_v_16-1.78*object_wp_y*in_patch_X_2_object_v_14-0.184*object_wp_y*in_patch_X_4_object_v_16-67.8*p22_u_y-30*p23_u_y-20*p24_u_y+97*p40_u_y+6*p40_v_y-87*p40_w_y+87*p40_wp_y+67.8*p42_u_y+30*p43_u_y+20*p44_u_y+8.876*object_u_y-10.836*object_w_y+10.836*object_wp_y-13*X_2_w_y+13*X_2_wp_y+13*X_4_w_y-13*X_4_wp_y = -27.1;
   0.176*object_u_z*in_patch_X_2_object_v_14+1.816*object_u_z*in_patch_X_4_object_v_16-5.34*object_v_z*in_patch_X_2_object_u_14+5.34*object_v_z*in_patch_X_4_object_u_16-0.034*object_v_z*in_patch_X_4_object_w_16+1.78*object_w_z*in_patch_X_2_object_v_14+0.184*object_w_z*in_patch_X_4_object_v_16-1.78*object_wp_z*in_patch_X_2_object_v_14-0.184*object_wp_z*in_patch_X_4_object_v_16-67.8*p22_u_z-30*p23_u_z-20*p24_u_z+97*p40_u_z+6*p40_v_z-87*p40_w_z+87*p40_wp_z+67.8*p42_u_z+30*p43_u_z+20*p44_u_z+8.876*object_u_z-10.836*object_w_z+10.836*object_wp_z-13*X_2_w_z+13*X_2_wp_z+13*X_4_w_z-13*X_4_wp_z = 150.15;
   0.176*object_u_x*in_patch_X_2_object_v_14+0.184*object_u_x*in_patch_X_P_object_v_18-5.34*object_v_x*in_patch_X_2_object_u_14+94.552*object_v_x*in_patch_X_P_object_u_18+1.78*object_w_x*in_patch_X_2_object_v_14-1.816*object_w_x*in_patch_X_P_object_v_18-1.78*object_wp_x*in_patch_X_2_object_v_14+1.816*object_wp_x*in_patch_X_P_object_v_18-67.8*p22_u_x-30*p23_u_x-20*p24_u_x-0.176*object_u_x-205.888*object_v_x-1.78*object_w_x+1.78*object_wp_x+13*X_P_w_x-13*X_P_wp_x-13*X_2_w_x+13*X_2_wp_x = -2.421;
   0.176*object_u_y*in_patch_X_2_object_v_14+0.184*object_u_y*in_patch_X_P_object_v_18-5.34*object_v_y*in_patch_X_2_object_u_14+94.552*object_v_y*in_patch_X_P_object_u_18+1.78*object_w_y*in_patch_X_2_object_v_14-1.816*object_w_y*in_patch_X_P_object_v_18-1.78*object_wp_y*in_patch_X_2_object_v_14+1.816*object_wp_y*in_patch_X_P_object_v_18-67.8*p22_u_y-30*p23_u_y-20*p24_u_y-0.176*object_u_y-205.888*object_v_y-1.78*object_w_y+1.78*object_wp_y+13*X_P_w_y-13*X_P_wp_y-13*X_2_w_y+13*X_2_wp_y = -49.495;
   0.176*object_u_z*in_patch_X_2_object_v_14+0.184*object_u_z*in_patch_X_P_object_v_18-5.34*object_v_z*in_patch_X_2_object_u_14+94.552*object_v_z*in_patch_X_P_object_u_18+1.78*object_w_z*in_patch_X_2_object_v_14-1.816*object_w_z*in_patch_X_P_object_v_18-1.78*object_wp_z*in_patch_X_2_object_v_14+1.816*object_wp_z*in_patch_X_P_object_v_18-67.8*p22_u_z-30*p23_u_z-20*p24_u_z-0.176*object_u_z-205.888*object_v_z-1.78*object_w_z+1.78*object_wp_z+13*X_P_w_z-13*X_P_wp_z-13*X_2_w_z+13*X_2_wp_z = 45.15;

% Equations added to couple the revolute joints in between phalanx
cos_p12_p13_1 - cos_p13_p14_2 = 0;
cos_p22_p23_4 - cos_p23_p24_5 = 0;
cos_p32_p33_7 - cos_p33_p34_8 = 0;
cos_p42_p43_11 - cos_p43_p44_12 = 0;

[COORD EQS]

   67.8*p12_u_x+30*p13_u_x-p14_r_x = 4.3;
   67.8*p12_u_y+30*p13_u_y-p14_r_y = 40.165;
   67.8*p12_u_z+30*p13_u_z-p14_r_z = -145.43;
   67.8*p32_u_x+30*p33_u_x-p34_r_x = 4.3;
   67.8*p32_u_y+30*p33_u_y-p34_r_y = -40.165;
   67.8*p32_u_z+30*p33_u_z-p34_r_z = -145.43;

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
   X_2_u_y*X_2_v_z-X_2_w_x = 0;
   X_2_u_z*X_2_v_x-X_2_w_y = 0;
   X_2_u_x*X_2_v_y-X_2_w_z = 0;
   X_2_u_z*X_2_v_y-X_2_wp_x = 0;
   X_2_u_x*X_2_v_z-X_2_wp_y = 0;
   X_2_u_y*X_2_v_x-X_2_wp_z = 0;
   X_4_u_y*X_4_v_z-X_4_w_x = 0;
   X_4_u_z*X_4_v_x-X_4_w_y = 0;
   X_4_u_x*X_4_v_y-X_4_w_z = 0;
   X_4_u_z*X_4_v_y-X_4_wp_x = 0;
   X_4_u_x*X_4_v_z-X_4_wp_y = 0;
   X_4_u_y*X_4_v_x-X_4_wp_z = 0;
   in_patch_X_2_object_u_14*in_patch_X_2_object_v_14-in_patch_X_2_object_w_14 = 0;
   in_patch_X_4_object_u_16*in_patch_X_4_object_v_16-in_patch_X_4_object_w_16 = 0;
   in_patch_X_P_object_u_18*in_patch_X_P_object_v_18-in_patch_X_P_object_w_18 = 0;

[SEARCH]

 MIN 172.582639308*cos_0_palm_p22_3^2+11.6568542495*cos_1_palm_p22_3^2+11.6568542495*cos_p22_p23_4^2+11.6568542495*cos_p23_p24_5^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+11.6568542495*cos_p42_p43_11^2+11.6568542495*cos_p43_p44_12^2+0.25*cos_p24_X_2_13^2+in_patch_X_2_object_u_14^2+in_patch_X_2_object_v_14^2+4*cos_p44_X_4_15^2+in_patch_X_4_object_u_16^2+in_patch_X_4_object_v_16^2+4*cos_palm_X_P_17^2+in_patch_X_P_object_u_18^2+in_patch_X_P_object_v_18^2-345.165278616*cos_0_palm_p22_3-23.313708499*cos_1_palm_p22_3-23.313708499*cos_p22_p23_4-23.313708499*cos_p23_p24_5-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-23.313708499*cos_p42_p43_11-23.313708499*cos_p43_p44_12-0.5*cos_p24_X_2_13-in_patch_X_2_object_u_14-in_patch_X_2_object_v_14-8*cos_p44_X_4_15-in_patch_X_4_object_u_16-in_patch_X_4_object_v_16-8*cos_palm_X_P_17-in_patch_X_P_object_u_18-in_patch_X_P_object_v_18+436.513258362




==========================================================================
%****************************************
% Simplified system 
% SIMPLIFICATION_LEVEL: 3
%   p12_u_x=p12_u_x
%   p12_u_y=p12_u_y
%   p12_u_z=p12_u_z
%   p12_v_x= -0
%   p12_v_y=+0.0343212495372*p14_v_z -1.00058880074
%   p12_v_z=p14_v_z
%   p12_w_x=p12_wp_x +1
%   p12_w_y= -0
%   p12_w_z=w2_palm_p12_z_0
%   p12_wp_x=p12_wp_x
%   p12_wp_y=-w2_palm_p12_y_0
%   p12_wp_z= -0
%   p13_u_x=p13_u_x
%   p13_u_y=p13_u_y
%   p13_u_z=p13_u_z
%   p13_v_x= -0
%   p13_v_y=+0.0343212495372*p14_v_z -1.00058880074
%   p13_v_z=p14_v_z
%   p13_w_x=No in simplification
%   p13_w_y=No in simplification
%   p13_w_z=No in simplification
%   p13_wp_x=No in simplification
%   p13_wp_y=No in simplification
%   p13_wp_z=No in simplification
%   p14_u_x=p14_u_x
%   p14_u_y=p14_u_y
%   p14_u_z=p14_u_z
%   p14_v_x= -0
%   p14_v_y=+0.0343212495372*p14_v_z -1.00058880074
%   p14_v_z=p14_v_z
%   p14_w_x=No in simplification
%   p14_w_y=No in simplification
%   p14_w_z=No in simplification
%   p14_wp_x=No in simplification
%   p14_wp_y=No in simplification
%   p14_wp_z=No in simplification
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
%   p32_v_y=-0.0355073696428*p34_v_z -1.00063018808
%   p32_v_z=p34_v_z
%   p32_w_x=p32_wp_x +1
%   p32_w_y= -0
%   p32_w_z=w2_palm_p32_z_6
%   p32_wp_x=p32_wp_x
%   p32_wp_y=-w2_palm_p32_y_6
%   p32_wp_z= -0
%   p33_u_x=p33_u_x
%   p33_u_y=p33_u_y
%   p33_u_z=p33_u_z
%   p33_v_x= -0
%   p33_v_y=-0.0355073696428*p34_v_z -1.00063018808
%   p33_v_z=p34_v_z
%   p33_w_x=No in simplification
%   p33_w_y=No in simplification
%   p33_w_z=No in simplification
%   p33_wp_x=No in simplification
%   p33_wp_y=No in simplification
%   p33_wp_z=No in simplification
%   p34_u_x=p34_u_x
%   p34_u_y=p34_u_y
%   p34_u_z=p34_u_z
%   p34_v_x= -0
%   p34_v_y=-0.0355073696428*p34_v_z -1.00063018808
%   p34_v_z=p34_v_z
%   p34_w_x=No in simplification
%   p34_w_y=No in simplification
%   p34_w_z=No in simplification
%   p34_wp_x=No in simplification
%   p34_wp_y=No in simplification
%   p34_wp_z=No in simplification
%   p40_u_x= -0
%   p40_u_y= -0
%   p40_u_z= +1
%   p40_v_x=p40_v_x
%   p40_v_y=p40_v_y
%   p40_v_z= -0
%   p40_w_x= -0
%   p40_w_y=p40_v_x
%   p40_w_z= -0
%   p40_wp_x=p40_v_y
%   p40_wp_y= -0
%   p40_wp_z= -0
%   p42_u_x=p42_u_x
%   p42_u_y=p42_u_y
%   p42_u_z=p42_u_z
%   p42_v_x=p44_v_x
%   p42_v_y=p44_v_y
%   p42_v_z=p44_v_z
%   p42_w_x=p42_w_x
%   p42_w_y=p42_w_y
%   p42_w_z=p42_w_z
%   p42_wp_x=p42_wp_x
%   p42_wp_y=p42_wp_y
%   p42_wp_z=p42_wp_z
%   p43_u_x=p43_u_x
%   p43_u_y=p43_u_y
%   p43_u_z=p43_u_z
%   p43_v_x=p44_v_x
%   p43_v_y=p44_v_y
%   p43_v_z=p44_v_z
%   p43_w_x=p43_w_x
%   p43_w_y=p43_w_y
%   p43_w_z=p43_w_z
%   p43_wp_x=p43_wp_x
%   p43_wp_y=p43_wp_y
%   p43_wp_z=p43_wp_z
%   p44_u_x=p44_u_x
%   p44_u_y=p44_u_y
%   p44_u_z=p44_u_z
%   p44_v_x=p44_v_x
%   p44_v_y=p44_v_y
%   p44_v_z=p44_v_z
%   p44_w_x=p44_w_x
%   p44_w_y=p44_w_y
%   p44_w_z=p44_w_z
%   p44_wp_x=p44_wp_x
%   p44_wp_y=p44_wp_y
%   p44_wp_z=p44_wp_z
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
%   X_4_u_x=X_4_u_x
%   X_4_u_y=X_4_u_y
%   X_4_u_z=X_4_u_z
%   X_4_v_x=X_4_v_x
%   X_4_v_y=X_4_v_y
%   X_4_v_z=X_4_v_z
%   X_4_w_x=X_4_w_x
%   X_4_w_y=X_4_w_y
%   X_4_w_z=X_4_w_z
%   X_4_wp_x=X_4_wp_x
%   X_4_wp_y=X_4_wp_y
%   X_4_wp_z=X_4_wp_z
%   uni_u_palm_p12_x_0= +1
%   uni_u_palm_p12_y_0= -0
%   uni_u_palm_p12_z_0= -0
%   uni_v_palm_p12_x_0= -0
%   uni_v_palm_p12_y_0=+0.0343212495372*p14_v_z -1.00058880074
%   uni_v_palm_p12_z_0=p14_v_z
%   w1_palm_p12_x_0= -0
%   w1_palm_p12_y_0= -0.999411545741
%   w1_palm_p12_z_0= +0.0343010530517
%   w2_palm_p12_x_0= +1
%   w2_palm_p12_y_0=w2_palm_p12_y_0
%   w2_palm_p12_z_0=w2_palm_p12_z_0
%   cos_0_palm_p12_0= +1
%   cos_1_palm_p12_0= +1
%   w1_p12_p13_x_1=p12_u_x
%   w1_p12_p13_y_1=p12_u_y
%   w1_p12_p13_z_1=p12_u_z
%   w2_p12_p13_x_1=p13_u_x
%   w2_p12_p13_y_1=p13_u_y
%   w2_p12_p13_z_1=p13_u_z
%   cos_p12_p13_1= +1
%   w1_p13_p14_x_2=p13_u_x
%   w1_p13_p14_y_2=p13_u_y
%   w1_p13_p14_z_2=p13_u_z
%   w2_p13_p14_x_2=p14_u_x
%   w2_p13_p14_y_2=p14_u_y
%   w2_p13_p14_z_2=p14_u_z
%   cos_p13_p14_2= +1
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
%   uni_v_palm_p32_y_6=-0.0355073696428*p34_v_z -1.00063018808
%   uni_v_palm_p32_z_6=p34_v_z
%   w1_palm_p32_x_6= -0
%   w1_palm_p32_y_6= -0.999370208806
%   w1_palm_p32_z_6= -0.0354850074141
%   w2_palm_p32_x_6= +1
%   w2_palm_p32_y_6=w2_palm_p32_y_6
%   w2_palm_p32_z_6=w2_palm_p32_z_6
%   cos_0_palm_p32_6= +1
%   cos_1_palm_p32_6= +1
%   w1_p32_p33_x_7=p32_u_x
%   w1_p32_p33_y_7=p32_u_y
%   w1_p32_p33_z_7=p32_u_z
%   w2_p32_p33_x_7=p33_u_x
%   w2_p32_p33_y_7=p33_u_y
%   w2_p32_p33_z_7=p33_u_z
%   cos_p32_p33_7= +1
%   w1_p33_p34_x_8=p33_u_x
%   w1_p33_p34_y_8=p33_u_y
%   w1_p33_p34_z_8=p33_u_z
%   w2_p33_p34_x_8=p34_u_x
%   w2_p33_p34_y_8=p34_u_y
%   w2_p33_p34_z_8=p34_u_z
%   cos_p33_p34_8= +1
%   w1_palm_p40_x_9= -0.707106781187
%   w1_palm_p40_y_9= -0.707106781187
%   w1_palm_p40_z_9= -0
%   w2_palm_p40_x_9=-p40_v_y
%   w2_palm_p40_y_9=p40_v_x
%   w2_palm_p40_z_9= -0
%   cos_palm_p40_9=cos_palm_p40_9
%   uni_u_p40_p42_x_10=-0.819149697365*p40_v_y
%   uni_u_p40_p42_y_10=+0.819149697365*p40_v_x
%   uni_u_p40_p42_z_10= +0.573579788091
%   uni_v_p40_p42_x_10=p44_v_x
%   uni_v_p40_p42_y_10=p44_v_y
%   uni_v_p40_p42_z_10=p44_v_z
%   w1_p40_p42_x_10=p40_v_x
%   w1_p40_p42_y_10=p40_v_y
%   w1_p40_p42_z_10= -0
%   w2_p40_p42_x_10=w1_p42_p43_x_11
%   w2_p40_p42_y_10=w1_p42_p43_y_11
%   w2_p40_p42_z_10=w1_p42_p43_z_11
%   cos_0_p40_p42_10=cos_0_p40_p42_10
%   cos_1_p40_p42_10=cos_1_p40_p42_10
%   w1_p42_p43_x_11=w1_p42_p43_x_11
%   w1_p42_p43_y_11=w1_p42_p43_y_11
%   w1_p42_p43_z_11=w1_p42_p43_z_11
%   w2_p42_p43_x_11=p43_u_x
%   w2_p42_p43_y_11=p43_u_y
%   w2_p42_p43_z_11=p43_u_z
%   cos_p42_p43_11=cos_p43_p44_12
%   w1_p43_p44_x_12=w1_p43_p44_x_12
%   w1_p43_p44_y_12=w1_p43_p44_y_12
%   w1_p43_p44_z_12=w1_p43_p44_z_12
%   w2_p43_p44_x_12=p44_u_x
%   w2_p43_p44_y_12=p44_u_y
%   w2_p43_p44_z_12=p44_u_z
%   cos_p43_p44_12=cos_p43_p44_12
%   sph_w1_p24_X_2_x_13=sph_w1_p24_X_2_x_13
%   sph_w1_p24_X_2_y_13=sph_w1_p24_X_2_y_13
%   sph_w1_p24_X_2_z_13=sph_w1_p24_X_2_z_13
%   sph_w2_p24_X_2_x_13=sph_w2_p24_X_2_x_13
%   sph_w2_p24_X_2_y_13=sph_w2_p24_X_2_y_13
%   sph_w2_p24_X_2_z_13=sph_w2_p24_X_2_z_13
%   cos_p24_X_2_13=cos_p24_X_2_13
%   in_patch_X_2_object_u_14=in_patch_X_2_object_u_14
%   in_patch_X_2_object_v_14=in_patch_X_2_object_v_14
%   in_patch_X_2_object_w_14=No in simplification
%   in_patch_X_2_object_l_14= +9.55155098744
%   sph_w1_p44_X_4_x_15=sph_w1_p44_X_4_x_15
%   sph_w1_p44_X_4_y_15=sph_w1_p44_X_4_y_15
%   sph_w1_p44_X_4_z_15=sph_w1_p44_X_4_z_15
%   sph_w2_p44_X_4_x_15=sph_w2_p44_X_4_x_15
%   sph_w2_p44_X_4_y_15=sph_w2_p44_X_4_y_15
%   sph_w2_p44_X_4_z_15=sph_w2_p44_X_4_z_15
%   cos_p44_X_4_15=cos_p44_X_4_15
%   in_patch_X_4_object_u_16=in_patch_X_4_object_u_16
%   in_patch_X_4_object_v_16=in_patch_X_4_object_v_16
%   in_patch_X_4_object_w_16=in_patch_X_4_object_w_16
%   in_patch_X_4_object_l_16=in_patch_X_4_object_l_16
%   sph_w1_palm_X_P_x_17= +0.707106781187
%   sph_w1_palm_X_P_y_17= +0.707106781187
%   sph_w1_palm_X_P_z_17= -0
%   sph_w2_palm_X_P_x_17=sph_w2_palm_X_P_x_17
%   sph_w2_palm_X_P_y_17=sph_w2_palm_X_P_y_17
%   sph_w2_palm_X_P_z_17=sph_w2_palm_X_P_z_17
%   cos_palm_X_P_17=cos_palm_X_P_17
%   in_patch_X_P_object_u_18=in_patch_X_P_object_u_18
%   in_patch_X_P_object_v_18=in_patch_X_P_object_v_18
%   in_patch_X_P_object_w_18=No in simplification
%   in_patch_X_P_object_l_18= +172.585556066
%   p14_r_x=p14_r_x
%   p14_r_y=p14_r_y
%   p14_r_z=p14_r_z
%   p34_r_x=p34_r_x
%   p34_r_y=p34_r_y
%   p34_r_z=p34_r_z

[SYSTEM VARS]
   p12_u_x : [-1,1]
   p12_u_y : [-1,1]
   p12_u_z : [-1,1]

[DUMMY VARS]
   p12_wp_x : [-1,2.0000001655e-11]

[SYSTEM VARS]
   p13_u_x : [-1,1]
   p13_u_y : [-1,1]
   p13_u_z : [-1,1]
   p14_u_x : [-1,1]
   p14_u_y : [-1,1]
   p14_u_z : [-1,1]
   p14_v_z : [0.0171555735608,1]
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
   p32_wp_x : [-1,2.0000001655e-11]

[SYSTEM VARS]
   p33_u_x : [-1,1]
   p33_u_y : [-1,1]
   p33_u_z : [-1,1]
   p34_u_x : [-1,1]
   p34_u_y : [-1,1]
   p34_u_z : [-1,1]
   p34_v_z : [-1,-0.0177480919332]
   p40_v_x : [-1,1]
   p40_v_y : [-1,1]
   p42_u_x : [-1,1]
   p42_u_y : [-1,1]
   p42_u_z : [-1,1]

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
   X_4_u_x : [-1,1]
   X_4_u_y : [-1,1]
   X_4_u_z : [-1,1]
   X_4_v_x : [-1,1]
   X_4_v_y : [-1,1]
   X_4_v_z : [-1,1]

[DUMMY VARS]
   X_4_w_x : [-1,1]
   X_4_w_y : [-1,1]
   X_4_w_z : [-1,1]
   X_4_wp_x : [-1,1]
   X_4_wp_y : [-1,1]
   X_4_wp_z : [-1,1]

[SECONDARY VARS]
   w2_palm_p12_y_0 : [-1,1]
   w2_palm_p12_z_0 : [-1,1]
   w1_p22_p23_x_4 : [0.707106781163,1]
   w1_p22_p23_y_4 : [-1,1]
   w1_p22_p23_z_4 : [-1,1]
   w1_p23_p24_x_5 : [-1,1]
   w1_p23_p24_y_5 : [-1,1]
   w1_p23_p24_z_5 : [-1,1]
   cos_p23_p24_5 : [0.707106781187,1]
   w2_palm_p32_y_6 : [-1,1]
   w2_palm_p32_z_6 : [-1,1]
   cos_palm_p40_9 : [0.707106781187,1]
   cos_0_p40_p42_10 : [0.923879532511,1]
   cos_1_p40_p42_10 : [0.707106781187,1]
   w1_p42_p43_x_11 : [-1,1]
   w1_p42_p43_y_11 : [-1,1]
   w1_p42_p43_z_11 : [-1,1]
   w1_p43_p44_x_12 : [-1,1]
   w1_p43_p44_y_12 : [-1,1]
   w1_p43_p44_z_12 : [-1,1]
   cos_p43_p44_12 : [0.707106781187,1]
   sph_w1_p24_X_2_x_13 : [-1,1]
   sph_w1_p24_X_2_y_13 : [-1,1]
   sph_w1_p24_X_2_z_13 : [-1,1]
   sph_w2_p24_X_2_x_13 : [-1,1]
   sph_w2_p24_X_2_y_13 : [-1,1]
   sph_w2_p24_X_2_z_13 : [-1,1]
   cos_p24_X_2_13 : [-1,1]

[SYSTEM VARS]
   in_patch_X_2_object_u_14 : [0,1]
   in_patch_X_2_object_v_14 : [0,1]

[SECONDARY VARS]
   sph_w1_p44_X_4_x_15 : [-1,1]
   sph_w1_p44_X_4_y_15 : [-1,1]
   sph_w1_p44_X_4_z_15 : [-1,1]
   sph_w2_p44_X_4_x_15 : [-1,1]
   sph_w2_p44_X_4_y_15 : [-1,1]
   sph_w2_p44_X_4_z_15 : [-1,1]
   cos_p44_X_4_15 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_4_object_u_16 : [0,1]
   in_patch_X_4_object_v_16 : [0,1]

[DUMMY VARS]
   in_patch_X_4_object_w_16 : [0,1]

[SECONDARY VARS]
   in_patch_X_4_object_l_16 : [9.68483120378,9.74728773384]
   sph_w2_palm_X_P_x_17 : [-1,1]
   sph_w2_palm_X_P_y_17 : [-1,1]
   sph_w2_palm_X_P_z_17 : [-1,1]
   cos_palm_X_P_17 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_P_object_u_18 : [0,1]
   in_patch_X_P_object_v_18 : [0,1]

[CARTESIAN VARS]
   p14_r_x : [-1710.10398103,1710.10398103]
   p14_r_y : [-1710.10398103,1710.10398103]
   p14_r_z : [-1710.10398103,1710.10398103]
   p34_r_x : [-1710.10398103,1710.10398103]
   p34_r_y : [-1710.10398103,1710.10398103]
   p34_r_z : [-1710.10398103,1710.10398103]

[DUMMY VARS]
   dummy_p14_v_z_2 : [0,1]
   dummy_p12_u_y_p14_v_z : [-1,1]
   dummy_p12_u_z_p14_v_z : [-1,1]
   dummy_p13_u_y_p14_v_z : [-1,1]
   dummy_p13_u_z_p14_v_z : [-1,1]
   dummy_p14_u_y_p14_v_z : [-1,1]
   dummy_p14_u_z_p14_v_z : [-1,1]
   dummy_p22_u_y_p24_v_y : [-1,1]
   dummy_p22_u_z_p24_v_z : [-1,1]
   dummy_p23_u_y_p24_v_y : [-1,1]
   dummy_p23_u_z_p24_v_z : [-1,1]
   dummy_p24_u_y_p24_v_y : [-1,1]
   dummy_p24_u_z_p24_v_z : [-1,1]
   dummy_p34_v_z_2 : [0,1]
   dummy_p32_u_y_p34_v_z : [-1,1]
   dummy_p32_u_z_p34_v_z : [-1,1]
   dummy_p33_u_y_p34_v_z : [-1,1]
   dummy_p33_u_z_p34_v_z : [-1,1]
   dummy_p34_u_y_p34_v_z : [-1,1]
   dummy_p34_u_z_p34_v_z : [-1,1]
   dummy_p42_u_x_p44_v_x : [-1,1]
   dummy_p42_u_y_p44_v_y : [-1,1]
   dummy_p42_u_z_p44_v_z : [-1,1]
   dummy_p43_u_x_p44_v_x : [-1,1]
   dummy_p43_u_y_p44_v_y : [-1,1]
   dummy_p43_u_z_p44_v_z : [-1,1]
   dummy_p44_u_x_p44_v_x : [-1,1]
   dummy_p44_u_y_p44_v_y : [-1,1]
   dummy_p44_u_z_p44_v_z : [-1,1]
   dummy_object_u_x_object_v_x : [-1,1]
   dummy_object_u_y_object_v_y : [-1,1]
   dummy_object_u_z_object_v_z : [-1,1]
   dummy_X_P_u_x_X_P_v_x : [-1,1]
   dummy_X_P_u_y_X_P_v_y : [-1,1]
   dummy_X_P_u_z_X_P_v_z : [-1,1]
   dummy_X_2_u_x_X_2_v_x : [-1,1]
   dummy_X_2_u_y_X_2_v_y : [-1,1]
   dummy_X_2_u_z_X_2_v_z : [-1,1]
   dummy_X_4_u_x_X_4_v_x : [-1,1]
   dummy_X_4_u_y_X_4_v_y : [-1,1]
   dummy_X_4_u_z_X_4_v_z : [-1,1]
   dummy_p12_u_x_p13_u_x : [-1,1]
   dummy_p12_u_y_p13_u_y : [-1,1]
   dummy_p12_u_z_p13_u_z : [-1,1]
   dummy_p13_u_x_p14_u_x : [-1,1]
   dummy_p13_u_y_p14_u_y : [-1,1]
   dummy_p13_u_z_p14_u_z : [-1,1]
   dummy_p23_u_x_w1_p22_p23_x_4 : [-1,1]
   dummy_p23_u_y_w1_p22_p23_y_4 : [-1,1]
   dummy_p23_u_z_w1_p22_p23_z_4 : [-1,1]
   dummy_p24_u_x_w1_p23_p24_x_5 : [-1,1]
   dummy_p24_u_y_w1_p23_p24_y_5 : [-1,1]
   dummy_p24_u_z_w1_p23_p24_z_5 : [-1,1]
   dummy_p32_u_x_p33_u_x : [-1,1]
   dummy_p32_u_y_p33_u_y : [-1,1]
   dummy_p32_u_z_p33_u_z : [-1,1]
   dummy_p33_u_x_p34_u_x : [-1,1]
   dummy_p33_u_y_p34_u_y : [-1,1]
   dummy_p33_u_z_p34_u_z : [-1,1]
   dummy_p40_v_x_p44_v_y : [-1,1]
   dummy_p40_v_y_p44_v_x : [-1,1]
   dummy_p40_v_x_p44_v_x : [-1,1]
   dummy_p40_v_y_p44_v_y : [-1,1]
   dummy_p40_v_x_w1_p42_p43_y_11 : [-1,1]
   dummy_p40_v_y_w1_p42_p43_x_11 : [-1,1]
   dummy_p43_u_x_w1_p42_p43_x_11 : [-1,1]
   dummy_p43_u_y_w1_p42_p43_y_11 : [-1,1]
   dummy_p43_u_z_w1_p42_p43_z_11 : [-1,1]
   dummy_p44_u_x_w1_p43_p44_x_12 : [-1,1]
   dummy_p44_u_y_w1_p43_p44_y_12 : [-1,1]
   dummy_p44_u_z_w1_p43_p44_z_12 : [-1,1]
   dummy_sph_w1_p24_X_2_x_13_sph_w2_p24_X_2_x_13 : [-1,1]
   dummy_sph_w1_p24_X_2_y_13_sph_w2_p24_X_2_y_13 : [-1,1]
   dummy_sph_w1_p24_X_2_z_13_sph_w2_p24_X_2_z_13 : [-1,1]
   dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15 : [-1,1]
   dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15 : [-1,1]
   dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 : [-1,1]
   dummy_in_patch_X_4_object_v_16_2 : [0,1]
   dummy_in_patch_X_4_object_l_16_2 : [93.7959554457,95.0096181663]
   dummy_object_u_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_w_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_x_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_x_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_object_u_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_w_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_y_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_y_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_object_u_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_w_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_z_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_z_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_object_u_x_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_v_x_in_patch_X_P_object_u_18 : [-1,1]
   dummy_object_w_x_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_wp_x_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_u_y_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_v_y_in_patch_X_P_object_u_18 : [-1,1]
   dummy_object_w_y_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_wp_y_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_u_z_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_v_z_in_patch_X_P_object_u_18 : [-1,1]
   dummy_object_w_z_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_wp_z_in_patch_X_P_object_v_18 : [-1,1]
   dummy_object_u_x_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_v_x_in_patch_X_2_object_u_14 : [-1,1]
   dummy_object_w_x_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_u_y_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_v_y_in_patch_X_2_object_u_14 : [-1,1]
   dummy_object_w_y_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_u_z_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_v_z_in_patch_X_2_object_u_14 : [-1,1]
   dummy_object_w_z_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_2_object_v_14 : [-1,1]

[SYSTEM EQS]

   p12_u_x^2+p12_u_y^2+p12_u_z^2 = 1;
   0.0686829158287*p14_v_z-1.00117794817*dummy_p14_v_z_2 = 0.00117794816892;
   1.00058880074*p12_u_y-0.0343212495372*dummy_p12_u_y_p14_v_z-dummy_p12_u_z_p14_v_z = -0;
   p13_u_x^2+p13_u_y^2+p13_u_z^2 = 1;
   1.00058880074*p13_u_y-0.0343212495372*dummy_p13_u_y_p14_v_z-dummy_p13_u_z_p14_v_z = -0;
   p14_u_x^2+p14_u_y^2+p14_u_z^2 = 1;
   1.00058880074*p14_u_y-0.0343212495372*dummy_p14_u_y_p14_v_z-dummy_p14_u_z_p14_v_z = -0;
   p22_u_x^2+p22_u_y^2+p22_u_z^2 = 1;
   p24_v_y^2+p24_v_z^2 = 1;
   dummy_p22_u_y_p24_v_y+dummy_p22_u_z_p24_v_z = 0;
   p23_u_x^2+p23_u_y^2+p23_u_z^2 = 1;
   dummy_p23_u_y_p24_v_y+dummy_p23_u_z_p24_v_z = 0;
   p24_u_x^2+p24_u_y^2+p24_u_z^2 = 1;
   dummy_p24_u_y_p24_v_y+dummy_p24_u_z_p24_v_z = 0;
   p32_u_x^2+p32_u_y^2+p32_u_z^2 = 1;
   0.0710594919279*p34_v_z+1.0012607733*dummy_p34_v_z_2 = -0.00126077329883;
   1.00063018808*p32_u_y+0.0355073696428*dummy_p32_u_y_p34_v_z-dummy_p32_u_z_p34_v_z = 0;
   p33_u_x^2+p33_u_y^2+p33_u_z^2 = 1;
   1.00063018808*p33_u_y+0.0355073696428*dummy_p33_u_y_p34_v_z-dummy_p33_u_z_p34_v_z = 0;
   p34_u_x^2+p34_u_y^2+p34_u_z^2 = 1;
   1.00063018808*p34_u_y+0.0355073696428*dummy_p34_u_y_p34_v_z-dummy_p34_u_z_p34_v_z = 0;
   p40_v_x^2+p40_v_y^2 = 1;
   p42_u_x^2+p42_u_y^2+p42_u_z^2 = 1;
   p44_v_x^2+p44_v_y^2+p44_v_z^2 = 1;
   dummy_p42_u_x_p44_v_x+dummy_p42_u_y_p44_v_y+dummy_p42_u_z_p44_v_z = 0;
   p43_u_x^2+p43_u_y^2+p43_u_z^2 = 1;
   dummy_p43_u_x_p44_v_x+dummy_p43_u_y_p44_v_y+dummy_p43_u_z_p44_v_z = 0;
   p44_u_x^2+p44_u_y^2+p44_u_z^2 = 1;
   dummy_p44_u_x_p44_v_x+dummy_p44_u_y_p44_v_y+dummy_p44_u_z_p44_v_z = 0;
   object_u_x^2+object_u_y^2+object_u_z^2 = 1;
   object_v_x^2+object_v_y^2+object_v_z^2 = 1;
   dummy_object_u_x_object_v_x+dummy_object_u_y_object_v_y+dummy_object_u_z_object_v_z = 0;
   X_P_u_x^2+X_P_u_y^2+X_P_u_z^2 = 1;
   X_P_v_x^2+X_P_v_y^2+X_P_v_z^2 = 1;
   dummy_X_P_u_x_X_P_v_x+dummy_X_P_u_y_X_P_v_y+dummy_X_P_u_z_X_P_v_z = 0;
   X_2_u_x^2+X_2_u_y^2+X_2_u_z^2 = 1;
   X_2_v_x^2+X_2_v_y^2+X_2_v_z^2 = 1;
   dummy_X_2_u_x_X_2_v_x+dummy_X_2_u_y_X_2_v_y+dummy_X_2_u_z_X_2_v_z = 0;
   X_4_u_x^2+X_4_u_y^2+X_4_u_z^2 = 1;
   X_4_v_x^2+X_4_v_y^2+X_4_v_z^2 = 1;
   dummy_X_4_u_x_X_4_v_x+dummy_X_4_u_y_X_4_v_y+dummy_X_4_u_z_X_4_v_z = 0;
   dummy_p12_u_x_p13_u_x+dummy_p12_u_y_p13_u_y+dummy_p12_u_z_p13_u_z = 1;
   dummy_p13_u_x_p14_u_x+dummy_p13_u_y_p14_u_y+dummy_p13_u_z_p14_u_z = 1;
   0.707106781187*p22_u_x+0.707106781187*p22_w_x-0.707106781187*p22_wp_x-w1_p22_p23_x_4 = 0;
   0.707106781187*p22_u_y-0.707106781187*p22_wp_y-w1_p22_p23_y_4 = 0;
   0.707106781187*p22_u_z+0.707106781187*p22_w_z-w1_p22_p23_z_4 = 0;
   cos_p23_p24_5-dummy_p23_u_x_w1_p22_p23_x_4-dummy_p23_u_y_w1_p22_p23_y_4-dummy_p23_u_z_w1_p22_p23_z_4 = -0;
   0.707106781187*p23_u_x+0.707106781187*p23_w_x-0.707106781187*p23_wp_x-w1_p23_p24_x_5 = 0;
   0.707106781187*p23_u_y-0.707106781187*p23_wp_y-w1_p23_p24_y_5 = 0;
   0.707106781187*p23_u_z+0.707106781187*p23_w_z-w1_p23_p24_z_5 = 0;
   cos_p23_p24_5-dummy_p24_u_x_w1_p23_p24_x_5-dummy_p24_u_y_w1_p23_p24_y_5-dummy_p24_u_z_w1_p23_p24_z_5 = -0;
   dummy_p32_u_x_p33_u_x+dummy_p32_u_y_p33_u_y+dummy_p32_u_z_p33_u_z = 1;
   dummy_p33_u_x_p34_u_x+dummy_p33_u_y_p34_u_y+dummy_p33_u_z_p34_u_z = 1;
   0.707106781187*p40_v_x-0.707106781187*p40_v_y+cos_palm_p40_9 = 0;
   0.573579788091*p44_v_z+0.819149697365*dummy_p40_v_x_p44_v_y-0.819149697365*dummy_p40_v_y_p44_v_x = 0;
   cos_0_p40_p42_10-dummy_p40_v_x_p44_v_x-dummy_p40_v_y_p44_v_y = -0;
   cos_1_p40_p42_10-0.573579788091*w1_p42_p43_z_11-0.819149697365*dummy_p40_v_x_w1_p42_p43_y_11+0.819149697365*dummy_p40_v_y_w1_p42_p43_x_11 = -0;
   0.707106781187*p42_u_x+0.707106781187*p42_w_x-0.707106781187*p42_wp_x-w1_p42_p43_x_11 = 0;
   0.707106781187*p42_u_y+0.707106781187*p42_w_y-0.707106781187*p42_wp_y-w1_p42_p43_y_11 = 0;
   0.707106781187*p42_u_z+0.707106781187*p42_w_z-0.707106781187*p42_wp_z-w1_p42_p43_z_11 = 0;
   cos_p43_p44_12-dummy_p43_u_x_w1_p42_p43_x_11-dummy_p43_u_y_w1_p42_p43_y_11-dummy_p43_u_z_w1_p42_p43_z_11 = -0;
   0.707106781187*p43_u_x+0.707106781187*p43_w_x-0.707106781187*p43_wp_x-w1_p43_p44_x_12 = 0;
   0.707106781187*p43_u_y+0.707106781187*p43_w_y-0.707106781187*p43_wp_y-w1_p43_p44_y_12 = 0;
   0.707106781187*p43_u_z+0.707106781187*p43_w_z-0.707106781187*p43_wp_z-w1_p43_p44_z_12 = 0;
   cos_p43_p44_12-dummy_p44_u_x_w1_p43_p44_x_12-dummy_p44_u_y_w1_p43_p44_y_12-dummy_p44_u_z_w1_p43_p44_z_12 = -0;
   0.140021004726*p24_u_x+0.990148533421*p24_w_x-0.990148533421*p24_wp_x-sph_w1_p24_X_2_x_13 = 0;
   0.140021004726*p24_u_y-0.990148533421*p24_wp_y-sph_w1_p24_X_2_y_13 = 0;
   0.140021004726*p24_u_z+0.990148533421*p24_w_z-sph_w1_p24_X_2_z_13 = 0;
   X_2_w_x-X_2_wp_x-sph_w2_p24_X_2_x_13 = 0;
   X_2_w_y-X_2_wp_y-sph_w2_p24_X_2_y_13 = 0;
   X_2_w_z-X_2_wp_z-sph_w2_p24_X_2_z_13 = 0;
   cos_p24_X_2_13-dummy_sph_w1_p24_X_2_x_13_sph_w2_p24_X_2_x_13-dummy_sph_w1_p24_X_2_y_13_sph_w2_p24_X_2_y_13-dummy_sph_w1_p24_X_2_z_13_sph_w2_p24_X_2_z_13 = -0;
   9.5052*object_u_x-0.93984*object_w_x+0.93984*object_wp_x+9.55155098744*sph_w2_p24_X_2_x_13 = 0;
   9.5052*object_u_y-0.93984*object_w_y+0.93984*object_wp_y+9.55155098744*sph_w2_p24_X_2_y_13 = 0;
   9.5052*object_u_z-0.93984*object_w_z+0.93984*object_wp_z+9.55155098744*sph_w2_p24_X_2_z_13 = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_15 = 0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_15 = 0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_15 = 0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_15 = 0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_15 = 0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_15 = 0;
   cos_p44_X_4_15-dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15-dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15-dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 = -0;
   1.20981126144*in_patch_X_4_object_v_16-0.003851459072*dummy_in_patch_X_4_object_v_16_2+dummy_in_patch_X_4_object_l_16_2 = 95.0057667072;
   97.0938218182*object_u_x+98.554639734*sph_w2_p24_X_2_x_13+0.006256*dummy_object_u_x_in_patch_X_4_object_v_16-0.061744*dummy_object_w_x_in_patch_X_4_object_v_16+0.061744*dummy_object_wp_x_in_patch_X_4_object_v_16+dummy_X_4_w_x_in_patch_X_4_object_l_16-dummy_X_4_wp_x_in_patch_X_4_object_l_16 = 0;
   97.0938218182*object_u_y+98.554639734*sph_w2_p24_X_2_y_13+0.006256*dummy_object_u_y_in_patch_X_4_object_v_16-0.061744*dummy_object_w_y_in_patch_X_4_object_v_16+0.061744*dummy_object_wp_y_in_patch_X_4_object_v_16+dummy_X_4_w_y_in_patch_X_4_object_l_16-dummy_X_4_wp_y_in_patch_X_4_object_l_16 = 0;
   97.0938218182*object_u_z+98.554639734*sph_w2_p24_X_2_z_13+0.006256*dummy_object_u_z_in_patch_X_4_object_v_16-0.061744*dummy_object_w_z_in_patch_X_4_object_v_16+0.061744*dummy_object_wp_z_in_patch_X_4_object_v_16+dummy_X_4_w_z_in_patch_X_4_object_l_16-dummy_X_4_wp_z_in_patch_X_4_object_l_16 = 0;
   X_P_w_x-X_P_wp_x-sph_w2_palm_X_P_x_17 = 0;
   X_P_w_y-X_P_wp_y-sph_w2_palm_X_P_y_17 = 0;
   X_P_w_z-X_P_wp_z-sph_w2_palm_X_P_z_17 = 0;
   0.707106781187*sph_w2_palm_X_P_x_17+0.707106781187*sph_w2_palm_X_P_y_17-cos_palm_X_P_17 = 0;
   347.659108364*object_u_x+176.810688851*sph_w2_p24_X_2_x_13+172.585556066*sph_w2_palm_X_P_x_17 = 0;
   347.659108364*object_u_y+176.810688851*sph_w2_p24_X_2_y_13+172.585556066*sph_w2_palm_X_P_y_17 = 0;
   347.659108364*object_u_z+176.810688851*sph_w2_p24_X_2_z_13+172.585556066*sph_w2_palm_X_P_z_17 = 0;
   6*p40_v_x+87*p40_v_y+67.8*p42_u_x+30*p43_u_x+20*p44_u_x+98.4307826087*object_u_x+205.888*object_v_x+13*sph_w2_p44_X_4_x_15+76.8363952786*sph_w2_palm_X_P_x_17+1.816*dummy_object_u_x_in_patch_X_4_object_v_16+0.184*dummy_object_w_x_in_patch_X_4_object_v_16-0.184*dummy_object_wp_x_in_patch_X_4_object_v_16-0.184*dummy_object_u_x_in_patch_X_P_object_v_18+5.34*dummy_object_v_x_in_patch_X_4_object_u_16-0.034*dummy_object_v_x_in_patch_X_4_object_w_16-94.552*dummy_object_v_x_in_patch_X_P_object_u_18+1.816*dummy_object_w_x_in_patch_X_P_object_v_18-1.816*dummy_object_wp_x_in_patch_X_P_object_v_18 = 1.121;
   87*p40_v_x-6*p40_v_y-67.8*p42_u_y-30*p43_u_y-20*p44_u_y-98.4307826087*object_u_y-205.888*object_v_y-13*sph_w2_p44_X_4_y_15-76.8363952786*sph_w2_palm_X_P_y_17-1.816*dummy_object_u_y_in_patch_X_4_object_v_16-0.184*dummy_object_w_y_in_patch_X_4_object_v_16+0.184*dummy_object_wp_y_in_patch_X_4_object_v_16+0.184*dummy_object_u_y_in_patch_X_P_object_v_18-5.34*dummy_object_v_y_in_patch_X_4_object_u_16+0.034*dummy_object_v_y_in_patch_X_4_object_w_16+94.552*dummy_object_v_y_in_patch_X_P_object_u_18-1.816*dummy_object_w_y_in_patch_X_P_object_v_18+1.816*dummy_object_wp_y_in_patch_X_P_object_v_18 = -22.395;
   67.8*p42_u_z+30*p43_u_z+20*p44_u_z+98.4307826087*object_u_z+205.888*object_v_z+13*sph_w2_p44_X_4_z_15+76.8363952786*sph_w2_palm_X_P_z_17+1.816*dummy_object_u_z_in_patch_X_4_object_v_16+0.184*dummy_object_w_z_in_patch_X_4_object_v_16-0.184*dummy_object_wp_z_in_patch_X_4_object_v_16-0.184*dummy_object_u_z_in_patch_X_P_object_v_18+5.34*dummy_object_v_z_in_patch_X_4_object_u_16-0.034*dummy_object_v_z_in_patch_X_4_object_w_16-94.552*dummy_object_v_z_in_patch_X_P_object_u_18+1.816*dummy_object_w_z_in_patch_X_P_object_v_18-1.816*dummy_object_wp_z_in_patch_X_P_object_v_18 = 8;
   67.8*p22_u_x+30*p23_u_x+20*p24_u_x-42.9534504328*object_u_x+205.888*object_v_x-43.3471192931*sph_w2_palm_X_P_x_17-0.184*dummy_object_u_x_in_patch_X_P_object_v_18-94.552*dummy_object_v_x_in_patch_X_P_object_u_18+1.816*dummy_object_w_x_in_patch_X_P_object_v_18-1.816*dummy_object_wp_x_in_patch_X_P_object_v_18-0.176*dummy_object_u_x_in_patch_X_2_object_v_14+5.34*dummy_object_v_x_in_patch_X_2_object_u_14-1.78*dummy_object_w_x_in_patch_X_2_object_v_14+1.78*dummy_object_wp_x_in_patch_X_2_object_v_14 = 2.421;
   67.8*p22_u_y+30*p23_u_y+20*p24_u_y-42.9534504328*object_u_y+205.888*object_v_y-43.3471192931*sph_w2_palm_X_P_y_17-0.184*dummy_object_u_y_in_patch_X_P_object_v_18-94.552*dummy_object_v_y_in_patch_X_P_object_u_18+1.816*dummy_object_w_y_in_patch_X_P_object_v_18-1.816*dummy_object_wp_y_in_patch_X_P_object_v_18-0.176*dummy_object_u_y_in_patch_X_2_object_v_14+5.34*dummy_object_v_y_in_patch_X_2_object_u_14-1.78*dummy_object_w_y_in_patch_X_2_object_v_14+1.78*dummy_object_wp_y_in_patch_X_2_object_v_14 = 49.495;
   67.8*p22_u_z+30*p23_u_z+20*p24_u_z-42.9534504328*object_u_z+205.888*object_v_z-43.3471192931*sph_w2_palm_X_P_z_17-0.184*dummy_object_u_z_in_patch_X_P_object_v_18-94.552*dummy_object_v_z_in_patch_X_P_object_u_18+1.816*dummy_object_w_z_in_patch_X_P_object_v_18-1.816*dummy_object_wp_z_in_patch_X_P_object_v_18-0.176*dummy_object_u_z_in_patch_X_2_object_v_14+5.34*dummy_object_v_z_in_patch_X_2_object_u_14-1.78*dummy_object_w_z_in_patch_X_2_object_v_14+1.78*dummy_object_wp_z_in_patch_X_2_object_v_14 = -45.15;

[COORD EQS]

   67.8*p12_u_x+30*p13_u_x-p14_r_x = 4.3;
   67.8*p12_u_y+30*p13_u_y-p14_r_y = 40.165;
   67.8*p12_u_z+30*p13_u_z-p14_r_z = -145.43;
   67.8*p32_u_x+30*p33_u_x-p34_r_x = 4.3;
   67.8*p32_u_y+30*p33_u_y-p34_r_y = -40.165;
   67.8*p32_u_z+30*p33_u_z-p34_r_z = -145.43;

[DUMMY EQS]

   p14_v_z^2-dummy_p14_v_z_2 = 0;
   p12_u_y*p14_v_z-dummy_p12_u_y_p14_v_z = 0;
   p12_u_z*p14_v_z-dummy_p12_u_z_p14_v_z = 0;
   p13_u_y*p14_v_z-dummy_p13_u_y_p14_v_z = 0;
   p13_u_z*p14_v_z-dummy_p13_u_z_p14_v_z = 0;
   p14_u_y*p14_v_z-dummy_p14_u_y_p14_v_z = 0;
   p14_u_z*p14_v_z-dummy_p14_u_z_p14_v_z = 0;
   p22_u_y*p24_v_y-dummy_p22_u_y_p24_v_y = 0;
   p22_u_z*p24_v_z-dummy_p22_u_z_p24_v_z = 0;
   p23_u_y*p24_v_y-dummy_p23_u_y_p24_v_y = 0;
   p23_u_z*p24_v_z-dummy_p23_u_z_p24_v_z = 0;
   p24_u_y*p24_v_y-dummy_p24_u_y_p24_v_y = 0;
   p24_u_z*p24_v_z-dummy_p24_u_z_p24_v_z = 0;
   p34_v_z^2-dummy_p34_v_z_2 = 0;
   p32_u_y*p34_v_z-dummy_p32_u_y_p34_v_z = 0;
   p32_u_z*p34_v_z-dummy_p32_u_z_p34_v_z = 0;
   p33_u_y*p34_v_z-dummy_p33_u_y_p34_v_z = 0;
   p33_u_z*p34_v_z-dummy_p33_u_z_p34_v_z = 0;
   p34_u_y*p34_v_z-dummy_p34_u_y_p34_v_z = 0;
   p34_u_z*p34_v_z-dummy_p34_u_z_p34_v_z = 0;
   p42_u_x*p44_v_x-dummy_p42_u_x_p44_v_x = 0;
   p42_u_y*p44_v_y-dummy_p42_u_y_p44_v_y = 0;
   p42_u_z*p44_v_z-dummy_p42_u_z_p44_v_z = 0;
   p43_u_x*p44_v_x-dummy_p43_u_x_p44_v_x = 0;
   p43_u_y*p44_v_y-dummy_p43_u_y_p44_v_y = 0;
   p43_u_z*p44_v_z-dummy_p43_u_z_p44_v_z = 0;
   p44_u_x*p44_v_x-dummy_p44_u_x_p44_v_x = 0;
   p44_u_y*p44_v_y-dummy_p44_u_y_p44_v_y = 0;
   p44_u_z*p44_v_z-dummy_p44_u_z_p44_v_z = 0;
   object_u_x*object_v_x-dummy_object_u_x_object_v_x = 0;
   object_u_y*object_v_y-dummy_object_u_y_object_v_y = 0;
   object_u_z*object_v_z-dummy_object_u_z_object_v_z = 0;
   X_P_u_x*X_P_v_x-dummy_X_P_u_x_X_P_v_x = 0;
   X_P_u_y*X_P_v_y-dummy_X_P_u_y_X_P_v_y = 0;
   X_P_u_z*X_P_v_z-dummy_X_P_u_z_X_P_v_z = 0;
   X_2_u_x*X_2_v_x-dummy_X_2_u_x_X_2_v_x = 0;
   X_2_u_y*X_2_v_y-dummy_X_2_u_y_X_2_v_y = 0;
   X_2_u_z*X_2_v_z-dummy_X_2_u_z_X_2_v_z = 0;
   X_4_u_x*X_4_v_x-dummy_X_4_u_x_X_4_v_x = 0;
   X_4_u_y*X_4_v_y-dummy_X_4_u_y_X_4_v_y = 0;
   X_4_u_z*X_4_v_z-dummy_X_4_u_z_X_4_v_z = 0;
   p12_u_x*p13_u_x-dummy_p12_u_x_p13_u_x = 0;
   p12_u_y*p13_u_y-dummy_p12_u_y_p13_u_y = 0;
   p12_u_z*p13_u_z-dummy_p12_u_z_p13_u_z = 0;
   p13_u_x*p14_u_x-dummy_p13_u_x_p14_u_x = 0;
   p13_u_y*p14_u_y-dummy_p13_u_y_p14_u_y = 0;
   p13_u_z*p14_u_z-dummy_p13_u_z_p14_u_z = 0;
   p23_u_x*w1_p22_p23_x_4-dummy_p23_u_x_w1_p22_p23_x_4 = 0;
   p23_u_y*w1_p22_p23_y_4-dummy_p23_u_y_w1_p22_p23_y_4 = 0;
   p23_u_z*w1_p22_p23_z_4-dummy_p23_u_z_w1_p22_p23_z_4 = 0;
   p24_u_x*w1_p23_p24_x_5-dummy_p24_u_x_w1_p23_p24_x_5 = 0;
   p24_u_y*w1_p23_p24_y_5-dummy_p24_u_y_w1_p23_p24_y_5 = 0;
   p24_u_z*w1_p23_p24_z_5-dummy_p24_u_z_w1_p23_p24_z_5 = 0;
   p32_u_x*p33_u_x-dummy_p32_u_x_p33_u_x = 0;
   p32_u_y*p33_u_y-dummy_p32_u_y_p33_u_y = 0;
   p32_u_z*p33_u_z-dummy_p32_u_z_p33_u_z = 0;
   p33_u_x*p34_u_x-dummy_p33_u_x_p34_u_x = 0;
   p33_u_y*p34_u_y-dummy_p33_u_y_p34_u_y = 0;
   p33_u_z*p34_u_z-dummy_p33_u_z_p34_u_z = 0;
   p40_v_x*p44_v_y-dummy_p40_v_x_p44_v_y = 0;
   p40_v_y*p44_v_x-dummy_p40_v_y_p44_v_x = 0;
   p40_v_x*p44_v_x-dummy_p40_v_x_p44_v_x = 0;
   p40_v_y*p44_v_y-dummy_p40_v_y_p44_v_y = 0;
   p40_v_x*w1_p42_p43_y_11-dummy_p40_v_x_w1_p42_p43_y_11 = 0;
   p40_v_y*w1_p42_p43_x_11-dummy_p40_v_y_w1_p42_p43_x_11 = 0;
   p43_u_x*w1_p42_p43_x_11-dummy_p43_u_x_w1_p42_p43_x_11 = 0;
   p43_u_y*w1_p42_p43_y_11-dummy_p43_u_y_w1_p42_p43_y_11 = 0;
   p43_u_z*w1_p42_p43_z_11-dummy_p43_u_z_w1_p42_p43_z_11 = 0;
   p44_u_x*w1_p43_p44_x_12-dummy_p44_u_x_w1_p43_p44_x_12 = 0;
   p44_u_y*w1_p43_p44_y_12-dummy_p44_u_y_w1_p43_p44_y_12 = 0;
   p44_u_z*w1_p43_p44_z_12-dummy_p44_u_z_w1_p43_p44_z_12 = 0;
   sph_w1_p24_X_2_x_13*sph_w2_p24_X_2_x_13-dummy_sph_w1_p24_X_2_x_13_sph_w2_p24_X_2_x_13 = 0;
   sph_w1_p24_X_2_y_13*sph_w2_p24_X_2_y_13-dummy_sph_w1_p24_X_2_y_13_sph_w2_p24_X_2_y_13 = 0;
   sph_w1_p24_X_2_z_13*sph_w2_p24_X_2_z_13-dummy_sph_w1_p24_X_2_z_13_sph_w2_p24_X_2_z_13 = 0;
   sph_w1_p44_X_4_x_15*sph_w2_p44_X_4_x_15-dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15 = 0;
   sph_w1_p44_X_4_y_15*sph_w2_p44_X_4_y_15-dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15 = 0;
   sph_w1_p44_X_4_z_15*sph_w2_p44_X_4_z_15-dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 = 0;
   in_patch_X_4_object_v_16^2-dummy_in_patch_X_4_object_v_16_2 = 0;
   in_patch_X_4_object_l_16^2-dummy_in_patch_X_4_object_l_16_2 = 0;
   object_u_x*in_patch_X_4_object_v_16-dummy_object_u_x_in_patch_X_4_object_v_16 = 0;
   object_w_x*in_patch_X_4_object_v_16-dummy_object_w_x_in_patch_X_4_object_v_16 = 0;
   object_wp_x*in_patch_X_4_object_v_16-dummy_object_wp_x_in_patch_X_4_object_v_16 = 0;
   X_4_w_x*in_patch_X_4_object_l_16-dummy_X_4_w_x_in_patch_X_4_object_l_16 = 0;
   X_4_wp_x*in_patch_X_4_object_l_16-dummy_X_4_wp_x_in_patch_X_4_object_l_16 = 0;
   object_u_y*in_patch_X_4_object_v_16-dummy_object_u_y_in_patch_X_4_object_v_16 = 0;
   object_w_y*in_patch_X_4_object_v_16-dummy_object_w_y_in_patch_X_4_object_v_16 = 0;
   object_wp_y*in_patch_X_4_object_v_16-dummy_object_wp_y_in_patch_X_4_object_v_16 = 0;
   X_4_w_y*in_patch_X_4_object_l_16-dummy_X_4_w_y_in_patch_X_4_object_l_16 = 0;
   X_4_wp_y*in_patch_X_4_object_l_16-dummy_X_4_wp_y_in_patch_X_4_object_l_16 = 0;
   object_u_z*in_patch_X_4_object_v_16-dummy_object_u_z_in_patch_X_4_object_v_16 = 0;
   object_w_z*in_patch_X_4_object_v_16-dummy_object_w_z_in_patch_X_4_object_v_16 = 0;
   object_wp_z*in_patch_X_4_object_v_16-dummy_object_wp_z_in_patch_X_4_object_v_16 = 0;
   X_4_w_z*in_patch_X_4_object_l_16-dummy_X_4_w_z_in_patch_X_4_object_l_16 = 0;
   X_4_wp_z*in_patch_X_4_object_l_16-dummy_X_4_wp_z_in_patch_X_4_object_l_16 = 0;
   object_u_x*in_patch_X_P_object_v_18-dummy_object_u_x_in_patch_X_P_object_v_18 = 0;
   object_v_x*in_patch_X_4_object_u_16-dummy_object_v_x_in_patch_X_4_object_u_16 = 0;
   object_v_x*in_patch_X_4_object_w_16-dummy_object_v_x_in_patch_X_4_object_w_16 = 0;
   object_v_x*in_patch_X_P_object_u_18-dummy_object_v_x_in_patch_X_P_object_u_18 = 0;
   object_w_x*in_patch_X_P_object_v_18-dummy_object_w_x_in_patch_X_P_object_v_18 = 0;
   object_wp_x*in_patch_X_P_object_v_18-dummy_object_wp_x_in_patch_X_P_object_v_18 = 0;
   object_u_y*in_patch_X_P_object_v_18-dummy_object_u_y_in_patch_X_P_object_v_18 = 0;
   object_v_y*in_patch_X_4_object_u_16-dummy_object_v_y_in_patch_X_4_object_u_16 = 0;
   object_v_y*in_patch_X_4_object_w_16-dummy_object_v_y_in_patch_X_4_object_w_16 = 0;
   object_v_y*in_patch_X_P_object_u_18-dummy_object_v_y_in_patch_X_P_object_u_18 = 0;
   object_w_y*in_patch_X_P_object_v_18-dummy_object_w_y_in_patch_X_P_object_v_18 = 0;
   object_wp_y*in_patch_X_P_object_v_18-dummy_object_wp_y_in_patch_X_P_object_v_18 = 0;
   object_u_z*in_patch_X_P_object_v_18-dummy_object_u_z_in_patch_X_P_object_v_18 = 0;
   object_v_z*in_patch_X_4_object_u_16-dummy_object_v_z_in_patch_X_4_object_u_16 = 0;
   object_v_z*in_patch_X_4_object_w_16-dummy_object_v_z_in_patch_X_4_object_w_16 = 0;
   object_v_z*in_patch_X_P_object_u_18-dummy_object_v_z_in_patch_X_P_object_u_18 = 0;
   object_w_z*in_patch_X_P_object_v_18-dummy_object_w_z_in_patch_X_P_object_v_18 = 0;
   object_wp_z*in_patch_X_P_object_v_18-dummy_object_wp_z_in_patch_X_P_object_v_18 = 0;
   object_u_x*in_patch_X_2_object_v_14-dummy_object_u_x_in_patch_X_2_object_v_14 = 0;
   object_v_x*in_patch_X_2_object_u_14-dummy_object_v_x_in_patch_X_2_object_u_14 = 0;
   object_w_x*in_patch_X_2_object_v_14-dummy_object_w_x_in_patch_X_2_object_v_14 = 0;
   object_wp_x*in_patch_X_2_object_v_14-dummy_object_wp_x_in_patch_X_2_object_v_14 = 0;
   object_u_y*in_patch_X_2_object_v_14-dummy_object_u_y_in_patch_X_2_object_v_14 = 0;
   object_v_y*in_patch_X_2_object_u_14-dummy_object_v_y_in_patch_X_2_object_u_14 = 0;
   object_w_y*in_patch_X_2_object_v_14-dummy_object_w_y_in_patch_X_2_object_v_14 = 0;
   object_wp_y*in_patch_X_2_object_v_14-dummy_object_wp_y_in_patch_X_2_object_v_14 = 0;
   object_u_z*in_patch_X_2_object_v_14-dummy_object_u_z_in_patch_X_2_object_v_14 = 0;
   object_v_z*in_patch_X_2_object_u_14-dummy_object_v_z_in_patch_X_2_object_u_14 = 0;
   object_w_z*in_patch_X_2_object_v_14-dummy_object_w_z_in_patch_X_2_object_v_14 = 0;
   object_wp_z*in_patch_X_2_object_v_14-dummy_object_wp_z_in_patch_X_2_object_v_14 = 0;
   p12_u_y*p14_v_z-p12_wp_x = 1;
   0.0343212495372*p12_u_x*p14_v_z-1.00058880074*p12_u_x-w2_palm_p12_z_0 = 0;
   0.0343212495372*p12_u_z*p14_v_z-1.00058880074*p12_u_z-p12_wp_x = 0;
   p12_u_x*p14_v_z+w2_palm_p12_y_0 = 0;
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
   p32_u_y*p34_v_z-p32_wp_x = 1;
   0.0355073696428*p32_u_x*p34_v_z+1.00063018808*p32_u_x+w2_palm_p32_z_6 = 0;
   0.0355073696428*p32_u_z*p34_v_z+1.00063018808*p32_u_z+p32_wp_x = 0;
   p32_u_x*p34_v_z+w2_palm_p32_y_6 = 0;
   p42_u_y*p44_v_z-p42_w_x = 0;
   p42_u_z*p44_v_x-p42_w_y = 0;
   p42_u_x*p44_v_y-p42_w_z = 0;
   p42_u_z*p44_v_y-p42_wp_x = 0;
   p42_u_x*p44_v_z-p42_wp_y = 0;
   p42_u_y*p44_v_x-p42_wp_z = 0;
   p43_u_y*p44_v_z-p43_w_x = 0;
   p43_u_z*p44_v_x-p43_w_y = 0;
   p43_u_x*p44_v_y-p43_w_z = 0;
   p43_u_z*p44_v_y-p43_wp_x = 0;
   p43_u_x*p44_v_z-p43_wp_y = 0;
   p43_u_y*p44_v_x-p43_wp_z = 0;
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
   X_2_u_y*X_2_v_z-X_2_w_x = 0;
   X_2_u_z*X_2_v_x-X_2_w_y = 0;
   X_2_u_x*X_2_v_y-X_2_w_z = 0;
   X_2_u_z*X_2_v_y-X_2_wp_x = 0;
   X_2_u_x*X_2_v_z-X_2_wp_y = 0;
   X_2_u_y*X_2_v_x-X_2_wp_z = 0;
   X_4_u_y*X_4_v_z-X_4_w_x = 0;
   X_4_u_z*X_4_v_x-X_4_w_y = 0;
   X_4_u_x*X_4_v_y-X_4_w_z = 0;
   X_4_u_z*X_4_v_y-X_4_wp_x = 0;
   X_4_u_x*X_4_v_z-X_4_wp_y = 0;
   X_4_u_y*X_4_v_x-X_4_wp_z = 0;
   in_patch_X_4_object_u_16*in_patch_X_4_object_v_16-in_patch_X_4_object_w_16 = 0;

[SEARCH]

 MIN 172.582639308*p24_v_y^2+11.6568542495*w1_p22_p23_x_4^2+23.313708499*cos_p23_p24_5^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+23.313708499*cos_p43_p44_12^2+0.25*cos_p24_X_2_13^2+in_patch_X_2_object_u_14^2+in_patch_X_2_object_v_14^2+4*cos_p44_X_4_15^2+in_patch_X_4_object_u_16^2+in_patch_X_4_object_v_16^2+4*cos_palm_X_P_17^2+in_patch_X_P_object_u_18^2+in_patch_X_P_object_v_18^2+345.165278616*p24_v_y-23.313708499*w1_p22_p23_x_4-46.627416998*cos_p23_p24_5-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-46.627416998*cos_p43_p44_12-0.5*cos_p24_X_2_13-in_patch_X_2_object_u_14-in_patch_X_2_object_v_14-8*cos_p44_X_4_15-in_patch_X_4_object_u_16-in_patch_X_4_object_v_16-8*cos_palm_X_P_17-in_patch_X_P_object_u_18-in_patch_X_P_object_v_18+436.513258362

==========================================================================
Cuik executed in 32 processors
SOLUTIONS (to input file /home/porta/cuik/CuikSuite/examples/IJRR/scalpel/3_contacts_middle_thumb_palm/SAHandplusScalpel_kin.cuik):

   1 (err:2.41936 min:3.55932 tm:254):{ 257  p12_u_x:[-0.00146777626978,0.00146777626978] p12_u_y:[0.0342826886202,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.0040068984225,0.0040068984225] p13_u_y:[0.0342824503393,0.0343137970218] p13_u_z:[0.999404154269,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.00852090661476,0.00852090661476] p14_u_y:[0.0342814809632,0.0343137970274] p14_u_z:[0.999375905213,0.999412175613] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.40433354884,0.422073198797] p22_u_y:[0.269863887695,0.305540742617] p22_u_z:[0.853857523731,0.865201310585] p22_v_x:[-0,0] p22_v_y:[-0.954808994437,-0.941730739817] p22_v_z:[0.297436019695,0.336432398099] p23_u_x:[0.798074439897,0.807899080525] p23_u_y:[0.175088330319,0.200828227131] p23_u_z:[0.555985688627,0.568567367288] p23_v_x:[-0,0] p23_v_y:[-0.954808994437,-0.941730739817] p23_v_z:[0.297436019695,0.336432398099] p24_u_x:[0.987576315459,0.991404262533] p24_u_y:[0.0383524784296,0.0523199299152] p24_u_z:[0.12546819361,0.147926756316] p24_v_x:[-0,0] p24_v_y:[-0.954808994437,-0.941730739817] p24_v_z:[0.297436019695,0.336432398099] p32_u_x:[-0.00148003356597,0.00148003356597] p32_u_y:[-0.0354977247751,-0.0354676761748] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308287235,0.00402308287235] p33_u_y:[-0.0354975792585,-0.0354674279937] p33_u_z:[0.999362737117,0.999370822835] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855589822412,0.00855589822412] p34_u_y:[-0.0354976912208,-0.0354664168185] p34_u_z:[0.99933425482,0.999370823033] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0886190115559,-0.0416426992762] p40_v_y:[0.996065595612,0.999256937821] p40_v_z:[-0,0] p42_u_x:[0.0999467183475,0.133132164465] p42_u_y:[-0.00257120625992,0.00299050905408] p42_u_z:[0.990949636525,0.995161477687] p42_v_x:[-0.0834400060202,-0.0387060927125] p42_v_y:[0.996469204302,0.999361141125] p42_v_z:[0.00336141174525,0.00965994391675] p43_u_x:[0.0929173748074,0.115538637232] p43_u_y:[-0.00207125780499,0] p43_u_z:[0.993301974965,0.995707945174] p43_v_x:[-0.0834400060202,-0.0387060927125] p43_v_y:[0.996469204302,0.999361141125] p43_v_z:[0.00336141174525,0.00965994391675] p44_u_x:[0.0584288403146,0.116196762043] p44_u_y:[-0,0.00210978302974] p44_u_z:[0.993263571437,0.998454389129] p44_v_x:[-0.0834400060202,-0.0387060927125] p44_v_y:[0.996469204302,0.999361141125] p44_v_z:[0.00336141174525,0.00965994391675] object_u_x:[-0.421705042068,-0.369239075678] object_u_y:[-0.929049509486,-0.904923231709] object_u_z:[0.0350617527892,0.0548978333366] object_v_x:[-0.515929793682,-0.506094358902] object_v_y:[0.164479146691,0.186463187992] object_v_z:[-0.846658353864,-0.839039038678] X_P_u_x:[-0.957496875604,-0.938683261977] X_P_u_y:[0.289075654257,0.344112199878] X_P_u_z:[-0.0616195409437,0] X_P_v_x:[-0.0643013369068,0] X_P_v_y:[-0.0209600463019,0] X_P_v_z:[0.997916436133,1] X_2_u_x:[-0,0.0556340722652] X_2_u_y:[0.076394351729,0.124379701214] X_2_u_z:[0.992186596626,0.996605998698] X_2_v_x:[0.867764382819,0.897492592534] X_2_v_y:[-0.496618489719,-0.440245123435] X_2_v_z:[-0,0.0619866698202] X_4_u_x:[0.585134293517,0.61990296821] X_4_u_y:[0.282866763413,0.364341384468] X_4_u_z:[0.696459557729,0.74799013705] X_4_v_x:[-0,0.0591692127744] X_4_v_y:[0.883021636894,0.914946611225] X_4_v_z:[-0.469338045387,-0.403574898415] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649769101e-05,5.03649769101e-05] w2_palm_p12_z_0:[-0.00146691349497,0.0014669134846] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626978,0.00146777626978] w1_p12_p13_y_1:[0.0342826886202,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.0040068984225,0.0040068984225] w2_p12_p13_y_1:[0.0342824503393,0.0343137970218] w2_p12_p13_z_1:[0.999404154269,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.0040068984225,0.0040068984225] w1_p13_p14_y_2:[0.0342824503393,0.0343137970218] w1_p13_p14_z_2:[0.999404154269,0.999412148261] w2_p13_p14_x_2:[-0.00852090661476,0.00852090661476] w2_p13_p14_y_2:[0.0342814809632,0.0343137970274] w2_p13_p14_z_2:[0.999375905213,0.999412175613] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.954808994437,-0.941730739817] uni_v_palm_p22_z_3:[0.297436019695,0.336432398099] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.931649012318,0.940026716169] w2_palm_p22_y_3:[0.10149121814,0.120587583685] w2_palm_p22_z_3:[0.322378312306,0.340206664475] cos_0_palm_p22_3:[0.941730739817,0.954808994437] cos_1_palm_p22_3:[0.931649012318,0.940026716169] w1_p22_p23_x_4:[0.931649012318,0.940026716169] w1_p22_p23_y_4:[0.10149121814,0.120587583685] w1_p22_p23_z_4:[0.322378312306,0.340206664475] w2_p22_p23_x_4:[0.798074439897,0.807899080525] w2_p22_p23_y_4:[0.175088330319,0.200828227131] w2_p22_p23_z_4:[0.555985688627,0.568567367288] cos_p22_p23_4:[0.955428760809,0.962853537053] w1_p23_p24_x_5:[0.987491739499,0.990651878494] w1_p23_p24_y_5:[-0.051651274272,-0.0448335847393] w1_p23_p24_z_5:[-0.147593408498,-0.130213218635] w2_p23_p24_x_5:[0.987576315459,0.991404262533] w2_p23_p24_y_5:[0.0383524784296,0.0523199299152] w2_p23_p24_z_5:[0.12546819361,0.147926756316] cos_p23_p24_5:[0.955428760809,0.962853537053] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681426e-05,5.25377681426e-05] w2_palm_p32_z_6:[-0.00147910237338,0.00147910238377] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356597,0.00148003356597] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761748] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308287235,0.00402308287235] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674279937] w2_p32_p33_z_7:[0.999362737117,0.999370822835] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308287235,0.00402308287235] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674279937] w1_p33_p34_z_8:[0.999362737117,0.999370822835] w2_p33_p34_x_8:[-0.00855589822412,0.00855589822412] w2_p33_p34_y_8:[-0.0354976912208,-0.0354664168185] w2_p33_p34_z_8:[0.99933425482,0.999370823033] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999256937821,-0.996065595612] w2_palm_p40_y_9:[-0.0886190115559,-0.0416426992762] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.735866502701,0.76733549843] uni_u_p40_p42_x_10:[-0.818541018208,-0.815926831199] uni_u_p40_p42_y_10:[-0.072592236497,-0.0341116045094] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0834400060202,-0.0387060927125] uni_v_p40_p42_y_10:[0.996469204302,0.999361141125] uni_v_p40_p42_z_10:[0.00336141174525,0.00965994391675] w1_p40_p42_x_10:[-0.0886190115559,-0.0416426992762] w1_p40_p42_y_10:[0.996065595612,0.999256937821] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.630868905662,-0.605699724232] w2_p40_p42_y_10:[-0.0593577405045,-0.0266824082995] w2_p40_p42_z_10:[0.774128255755,0.795078710053] cos_0_p40_p42_10:[0.998068818274,1] cos_1_p40_p42_10:[0.951619201318,0.96340300855] w1_p42_p43_x_11:[-0.630868905662,-0.605699724232] w1_p42_p43_y_11:[-0.0593577405045,-0.0266824082995] w1_p42_p43_z_11:[0.774128255755,0.795078710053] w2_p42_p43_x_11:[0.0929173748074,0.115538637232] w2_p42_p43_y_11:[-0.00207125780499,0] w2_p42_p43_z_11:[0.993301974965,0.995707945174] cos_p42_p43_11:[0.707106781187,0.733171642038] w1_p43_p44_x_12:[-0.636333973246,-0.618462151656] w1_p43_p44_y_12:[-0.0594685442146,-0.0274484834117] w1_p43_p44_z_12:[0.769444655951,0.783913389911] w2_p43_p44_x_12:[0.0584288403146,0.116196762043] w2_p43_p44_y_12:[-0,0.00210978302974] w2_p43_p44_z_12:[0.993263571437,0.998454389129] cos_p43_p44_12:[0.707106781187,0.733171642038] sph_w1_p24_X_2_x_13:[0.268292746592,0.293657972431] sph_w1_p24_X_2_y_13:[-0.323932976669,-0.286552944952] sph_w1_p24_X_2_z_13:[-0.919717546489,-0.901309628832] sph_w2_p24_X_2_x_13:[0.443744988334,0.493397502145] sph_w2_p24_X_2_y_13:[0.862973226933,0.891968541324] sph_w2_p24_X_2_z_13:[-0.107944445627,-0.0881984810867] cos_p24_X_2_13:[-0.0794954060492,-0.0141708212763] in_patch_X_2_object_u_14:[0.374999999996,0.437500000004] in_patch_X_2_object_v_14:[0.499999999995,0.562500000006] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.979697708843,-0.963939773563] sph_w1_p44_X_4_y_15:[-0.0831719159564,-0.0380522637172] sph_w1_p44_X_4_z_15:[0.197536075231,0.254108830299] sph_w2_p44_X_4_x_15:[-0.809889804115,-0.787532674555] sph_w2_p44_X_4_y_15:[0.235486010632,0.289043666112] sph_w2_p44_X_4_z_15:[0.531569602227,0.544604012406] cos_p44_X_4_15:[0.865487750991,0.898798558769] in_patch_X_4_object_u_16:[0.499999999995,0.562500000006] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.28914774324,0.344014819516] sph_w2_palm_X_P_y_17:[0.93875444562,0.957707215323] sph_w2_palm_X_P_z_17:[-0,0.0198002106631] cos_palm_X_P_17:[0.881207680685,0.90747244029] in_patch_X_P_object_u_18:[0.679432760263,0.694452122882] in_patch_X_P_object_v_18:[0.437499999996,0.500000000005] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972218381,-4.08027781619] p14_r_y:[-36.8121602017,-36.8091081693] p14_r_z:[243.172229419,243.172509987] p34_r_x:[-4.52103876199,-4.07896123802] p34_r_y:[36.6933268818,36.696267555] p34_r_z:[243.168182564,243.168466567] }
   2 (err:2.41648 min:3.57345 tm:254):{ 257  p12_u_x:[-0.00146777626978,0.00146777626978] p12_u_y:[0.0342826886202,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.00400689831697,0.00400689831697] p13_u_y:[0.0342824503393,0.0343137970322] p13_u_z:[0.999404153398,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.00852088926254,0.00852088926254] p14_u_y:[0.0342814809683,0.0343137970325] p14_u_z:[0.999375902758,0.999412175288] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.404819764494,0.422073198797] p22_u_y:[0.270762329749,0.305456340183] p22_u_z:[0.853856925719,0.864922236056] p22_v_x:[-0,0] p22_v_y:[-0.954489060113,-0.94174055312] p22_v_z:[0.298432878665,0.336400780012] p23_u_x:[0.798276547313,0.807834308683] p23_u_y:[0.175710762461,0.200744006868] p23_u_z:[0.556015019899,0.568298846418] p23_v_x:[-0,0] p23_v_y:[-0.954489060113,-0.94174055312] p23_v_z:[0.298432878665,0.336400780012] p24_u_x:[0.987676721587,0.991401717113] p24_u_y:[0.0385281799397,0.0521124878635] p24_u_z:[0.12546819361,0.147325571945] p24_v_x:[-0,0] p24_v_y:[-0.954489060113,-0.94174055312] p24_v_z:[0.298432878665,0.336400780012] p32_u_x:[-0.00148003356597,0.00148003356597] p32_u_y:[-0.0354977247751,-0.0354676761855] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308278097,0.00402308278097] p33_u_y:[-0.0354975792585,-0.0354674279938] p33_u_z:[0.999362737081,0.999370823594] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855588480224,0.00855588480224] p34_u_y:[-0.0354976869901,-0.0354664168333] p34_u_z:[0.999334252435,0.999370823322] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0886190115559,-0.0429248735394] p40_v_y:[0.996065595612,0.99919004452] p40_v_z:[-0,0] p42_u_x:[0.100327768281,0.132268760513] p42_u_y:[-0.00247065808232,0.00289733602478] p42_u_z:[0.991061748111,0.995114877847] p42_v_x:[-0.083402204727,-0.0398950726381] p42_v_y:[0.996471952468,0.999301905667] p42_v_z:[0.00351611232419,0.00966138517212] p43_u_x:[0.0935555979249,0.115573790972] p43_u_y:[-0.00199607400958,0] p43_u_z:[0.993297656181,0.995645425479] p43_v_x:[-0.083402204727,-0.0398950726381] p43_v_y:[0.996471952468,0.999301905667] p43_v_z:[0.00351611232419,0.00966138517212] p44_u_x:[0.0607447171945,0.116210716883] p44_u_y:[-0,0.00203270968615] p44_u_z:[0.993260322009,0.998287902026] p44_v_x:[-0.083402204727,-0.0398950726381] p44_v_y:[0.996471952468,0.999301905667] p44_v_z:[0.00351611232419,0.00966138517212] object_u_x:[-0.420772722347,-0.369082339602] object_u_y:[-0.929121567301,-0.905354127015] object_u_z:[0.035136813133,0.0548215614299] object_v_x:[-0.515294568483,-0.505687181519] object_v_y:[0.164307121144,0.185675743604] object_v_z:[-0.846934310335,-0.839522397988] X_P_u_x:[-0.9575648227,-0.939046461314] X_P_u_y:[0.288886677773,0.343098428349] X_P_u_z:[-0.0616255652278,0] X_P_v_x:[-0.0643013369068,0] X_P_v_y:[-0.0207945763498,0] X_P_v_z:[0.997918157958,1] X_2_u_x:[-0,0.0554428663785] X_2_u_y:[0.0764376438645,0.124142694712] X_2_u_z:[0.992215455511,0.996601821626] X_2_v_x:[0.868247567787,0.897538550366] X_2_v_y:[-0.495758231383,-0.440142296054] X_2_v_z:[-0,0.0617671844913] X_4_u_x:[0.584737925612,0.618883245937] X_4_u_y:[0.283525275992,0.364341384468] X_4_u_z:[0.697328589719,0.748261303902] X_4_v_x:[-0,0.0586765451908] X_4_v_y:[0.883272804263,0.914946611225] X_4_v_z:[-0.468841422875,-0.403574898415] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649769101e-05,5.03649769101e-05] w2_palm_p12_z_0:[-0.00146691349497,0.00146691349497] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626978,0.00146777626978] w1_p12_p13_y_1:[0.0342826886202,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.00400689831697,0.00400689831697] w2_p12_p13_y_1:[0.0342824503393,0.0343137970322] w2_p12_p13_z_1:[0.999404153398,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00400689831697,0.00400689831697] w1_p13_p14_y_2:[0.0342824503393,0.0343137970322] w1_p13_p14_z_2:[0.999404153398,0.999412148261] w2_p13_p14_x_2:[-0.00852088926254,0.00852088926254] w2_p13_p14_y_2:[0.0342814809683,0.0343137970325] w2_p13_p14_z_2:[0.999375902758,0.999412175288] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.954489060113,-0.94174055312] uni_v_palm_p22_z_3:[0.298432878665,0.336400780012] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.931868380315,0.940010696032] w2_palm_p22_y_3:[0.101849654312,0.120421795016] w2_palm_p22_z_3:[0.322386913287,0.339735976851] cos_0_palm_p22_3:[0.94174055312,0.954489060113] cos_1_palm_p22_3:[0.931868380315,0.940010696032] w1_p22_p23_x_4:[0.931868380315,0.940010696032] w1_p22_p23_y_4:[0.101849654312,0.120421795016] w1_p22_p23_z_4:[0.322386913287,0.339735976851] w2_p22_p23_x_4:[0.798276547313,0.807834308683] w2_p22_p23_y_4:[0.175710762461,0.200744006868] w2_p22_p23_z_4:[0.556015019899,0.568298846418] cos_p22_p23_4:[0.955548308055,0.962768572274] w1_p23_p24_x_5:[0.987521988763,0.990597150617] w1_p23_p24_y_5:[-0.0516517966804,-0.0449812166483] w1_p23_p24_z_5:[-0.147442333611,-0.130531110951] w2_p23_p24_x_5:[0.987676721587,0.991401717113] w2_p23_p24_y_5:[0.0385281799397,0.0521124878635] w2_p23_p24_z_5:[0.12546819361,0.147325571945] cos_p23_p24_5:[0.955548308055,0.962768572274] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681426e-05,5.25377681426e-05] w2_palm_p32_z_6:[-0.00147910238377,0.00147910238377] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356597,0.00148003356597] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761855] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308278097,0.00402308278097] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674279938] w2_p32_p33_z_7:[0.999362737081,0.999370823594] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308278097,0.00402308278097] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674279938] w1_p33_p34_z_8:[0.999362737081,0.999370823594] w2_p33_p34_x_8:[-0.00855588480224,0.00855588480224] w2_p33_p34_y_8:[-0.0354976869901,-0.0354664168333] w2_p33_p34_z_8:[0.999334252435,0.999370823322] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.99919004452,-0.996065595612] w2_palm_p40_y_9:[-0.0886190115559,-0.0429248735394] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.736730531024,0.767325336566] uni_u_p40_p42_x_10:[-0.81848622258,-0.815926831199] uni_u_p40_p42_y_10:[-0.072592236497,-0.0351618971691] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.083402204727,-0.0398950726381] uni_v_p40_p42_y_10:[0.996471952468,0.999301905667] uni_v_p40_p42_z_10:[0.00351611232419,0.00966138517212] w1_p40_p42_x_10:[-0.0886190115559,-0.0429248735394] w1_p40_p42_y_10:[0.996065595612,0.99919004452] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.630558965971,-0.606355703458] w2_p40_p42_y_10:[-0.0593326550852,-0.0275000575934] w2_p40_p42_z_10:[0.774363458883,0.7945348712] cos_0_p40_p42_10:[0.998122996308,1] cos_1_p40_p42_10:[0.951914755081,0.963273756536] w1_p42_p43_x_11:[-0.630558965971,-0.606355703458] w1_p42_p43_y_11:[-0.0593326550852,-0.0275000575934] w1_p42_p43_z_11:[0.774363458883,0.7945348712] w2_p42_p43_x_11:[0.0935555979249,0.115573790972] w2_p42_p43_y_11:[-0.00199607400958,0] w2_p42_p43_z_11:[0.993297656181,0.995645425479] cos_p42_p43_11:[0.707106781187,0.732069522372] w1_p43_p44_x_12:[-0.635727104641,-0.618400054283] w1_p43_p44_y_12:[-0.0594388750938,-0.028296644884] w1_p43_p44_z_12:[0.769853546691,0.78392826589] w2_p43_p44_x_12:[0.0607447171945,0.116210716883] w2_p43_p44_y_12:[-0,0.00203270968615] w2_p43_p44_z_12:[0.993260322009,0.998287902026] cos_p43_p44_12:[0.707106781187,0.732069522372] sph_w1_p24_X_2_x_13:[0.268357699408,0.293041861312] sph_w1_p24_X_2_y_13:[-0.323900884061,-0.287508638188] sph_w1_p24_X_2_z_13:[-0.919401161807,-0.901478362101] sph_w2_p24_X_2_x_13:[0.443622831634,0.492553228697] sph_w2_p24_X_2_y_13:[0.8634658074,0.892053962007] sph_w2_p24_X_2_z_13:[-0.107794473794,-0.0881986524864] cos_p24_X_2_13:[-0.0796223880956,-0.0155528243682] in_patch_X_2_object_u_14:[0.374999999996,0.437500000004] in_patch_X_2_object_v_14:[0.499999999995,0.562500000006] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.979157204908,-0.963923296608] sph_w1_p44_X_4_y_15:[-0.0831352977874,-0.0392513368293] sph_w1_p44_X_4_z_15:[0.199800539548,0.254110605972] sph_w2_p44_X_4_x_15:[-0.810189424692,-0.788291026697] sph_w2_p44_X_4_y_15:[0.23534373833,0.288346739834] sph_w2_p44_X_4_z_15:[0.531141997665,0.54384726871] cos_p44_X_4_15:[0.866615185873,0.898874215068] in_patch_X_4_object_u_16:[0.499999999995,0.562500000006] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.288958107705,0.343001571077] sph_w2_palm_X_P_y_17:[0.939118428451,0.957760150105] sph_w2_palm_X_P_z_17:[-0,0.0196492322424] cos_palm_X_P_17:[0.881112680795,0.907007533229] in_patch_X_P_object_u_18:[0.679757885561,0.694367152215] in_patch_X_P_object_v_18:[0.374999999996,0.437500000004] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972218064,-4.08027781936] p14_r_y:[-36.812160029,-36.8091081689] p14_r_z:[243.172229347,243.172509987] p34_r_x:[-4.52103875924,-4.07896124076] p34_r_y:[36.6933268818,36.6962683538] p34_r_z:[243.168182564,243.168466593] }
   3 (err:2.08983 min:3.52637 tm:254):{ 257  p12_u_x:[-0.00146777626978,0.00146777626978] p12_u_y:[0.0342826886202,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.0040068984225,0.0040068984225] p13_u_y:[0.0342824503286,0.0343138014357] p13_u_z:[0.999404153493,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.00852090661476,0.00852090661476] p14_u_y:[0.0342814809632,0.0343137970274] p14_u_z:[0.999375905128,0.999412175613] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.398483086555,0.422073198797] p22_u_y:[0.259604451888,0.305642044688] p22_u_z:[0.854232684032,0.868662229978] p22_v_x:[-0,0] p22_v_y:[-0.958490676016,-0.94199102886] p22_v_z:[0.286206181713,0.335637152801] p23_u_x:[0.795687173362,0.807953155962] p23_u_y:[0.168521852923,0.201124071379] p23_u_z:[0.556862532356,0.571879087305] p23_v_x:[-0,0] p23_v_y:[-0.958490676016,-0.94199102886] p23_v_z:[0.286206181713,0.335637152801] p24_u_x:[0.986418071968,0.991404262533] p24_u_y:[0.0373026659249,0.0545379030298] p24_u_z:[0.12546819361,0.155338465896] p24_v_x:[-0,0] p24_v_y:[-0.958490676016,-0.94199102886] p24_v_z:[0.286206181713,0.335637152801] p32_u_x:[-0.00148003356597,0.00148003356597] p32_u_y:[-0.0354977247751,-0.0354676761855] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308287235,0.00402308287235] p33_u_y:[-0.0354975792585,-0.0354674279937] p33_u_z:[0.9993627366,0.999370823703] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855589822412,0.00855589822412] p34_u_y:[-0.0354976869741,-0.0354664168292] p34_u_z:[0.999334251584,0.999370823611] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0886190115559,-0.0279722386057] p40_v_y:[0.996065595612,0.999660033775] p40_v_z:[-0,0] p42_u_x:[0.095504173256,0.135233553215] p42_u_y:[-0.00306643976639,0.00307831701773] p42_u_z:[0.9906900808,0.99547803689] p42_v_x:[-0.0836076674481,-0.0260230104526] p42_v_y:[0.996461518738,0.999703251068] p42_v_z:[0.00209845125848,0.00955563014847] p43_u_x:[0.0882451881716,0.11413660674] p43_u_y:[-0.00238558857841,0] p43_u_z:[0.993443771096,0.996182193458] p43_v_x:[-0.0836076674481,-0.0260230104526] p43_v_y:[0.996461518738,0.999703251068] p43_v_z:[0.00209845125848,0.00955563014847] p44_u_x:[0.0495783411198,0.114817260347] p44_u_y:[-0,0.0024260021781] p44_u_z:[0.993369190918,0.999131883397] p44_v_x:[-0.0836076674481,-0.0260230104526] p44_v_y:[0.996461518738,0.999703251068] p44_v_z:[0.00209845125848,0.00955563014847] object_u_x:[-0.432537585636,-0.368991704345] object_u_y:[-0.929049509486,-0.900094870567] object_u_z:[0.031171981613,0.0549493224952] object_v_x:[-0.515421758241,-0.502979327301] object_v_y:[0.164476529489,0.192602075543] object_v_z:[-0.848547678096,-0.838704751439] X_P_u_x:[-0.957496875604,-0.934844367855] X_P_u_y:[0.288721562367,0.355331680127] X_P_u_z:[-0.0616559080279,0] X_P_v_x:[-0.0643013369068,0] X_P_v_y:[-0.0247467859085,0] X_P_v_z:[0.997864924242,1] X_2_u_x:[-0,0.0568487264362] X_2_u_y:[0.0729771380864,0.125112799669] X_2_u_z:[0.992131204912,0.996989593606] X_2_v_x:[0.862052011165,0.897575351623] X_2_v_y:[-0.507039313429,-0.440146658091] X_2_v_z:[-0,0.0633581462752] X_4_u_x:[0.582671173563,0.624302393247] X_4_u_y:[0.275698118297,0.364341384468] X_4_u_z:[0.692922935096,0.750245412431] X_4_v_x:[-0,0.0697426252626] X_4_v_y:[0.879954155663,0.914946611225] X_4_v_z:[-0.475124297059,-0.403574898415] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649769101e-05,5.03649769101e-05] w2_palm_p12_z_0:[-0.0014669134846,0.00146691349497] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626978,0.00146777626978] w1_p12_p13_y_1:[0.0342826886202,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.0040068984225,0.0040068984225] w2_p12_p13_y_1:[0.0342824503286,0.0343138014357] w2_p12_p13_z_1:[0.999404153493,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.0040068984225,0.0040068984225] w1_p13_p14_y_2:[0.0342824503286,0.0343138014357] w1_p13_p14_z_2:[0.999404153493,0.999412148261] w2_p13_p14_x_2:[-0.00852090661476,0.00852090661476] w2_p13_p14_y_2:[0.0342814809632,0.0343137970274] w2_p13_p14_z_2:[0.999375905128,0.999412175613] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.958490676016,-0.94199102886] uni_v_palm_p22_z_3:[0.286206181713,0.335637152801] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.929382616436,0.940026716169] w2_palm_p22_y_3:[0.0975146078891,0.12218616136] w2_palm_p22_z_3:[0.322523793288,0.345999433533] cos_0_palm_p22_3:[0.94199102886,0.958490676016] cos_1_palm_p22_3:[0.929382616436,0.940026716169] w1_p22_p23_x_4:[0.929382616436,0.940026716169] w1_p22_p23_y_4:[0.0975146078891,0.12218616136] w1_p22_p23_z_4:[0.322523793288,0.345999433533] w2_p22_p23_x_4:[0.795687173362,0.807953155962] w2_p22_p23_y_4:[0.168521852923,0.201124071379] w2_p22_p23_z_4:[0.556862532356,0.571879087305] cos_p22_p23_4:[0.954333198841,0.963767083529] w1_p23_p24_x_5:[0.987475891615,0.991244013183] w1_p23_p24_y_5:[-0.0509495956034,-0.0430987172535] w1_p23_p24_z_5:[-0.148148440846,-0.126502712077] w2_p23_p24_x_5:[0.986418071968,0.991404262533] w2_p23_p24_y_5:[0.0373026659249,0.0545379030298] w2_p23_p24_z_5:[0.12546819361,0.155338465896] cos_p23_p24_5:[0.954333198841,0.963767083529] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681426e-05,5.25377681426e-05] w2_palm_p32_z_6:[-0.00147910238377,0.00147910238377] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356597,0.00148003356597] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761855] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308287235,0.00402308287235] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674279937] w2_p32_p33_z_7:[0.9993627366,0.999370823703] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308287235,0.00402308287235] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674279937] w1_p33_p34_z_8:[0.9993627366,0.999370823703] w2_p33_p34_x_8:[-0.00855589822412,0.00855589822412] w2_p33_p34_y_8:[-0.0354976869741,-0.0354664168292] w2_p33_p34_z_8:[0.999334251584,0.999370823611] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999660033775,-0.996065595612] w2_palm_p40_y_9:[-0.0886190115559,-0.0279722386057] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.726591314875,0.76733549843] uni_u_p40_p42_x_10:[-0.818871214137,-0.815926831199] uni_u_p40_p42_y_10:[-0.072592236497,-0.0229134507884] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0836076674481,-0.0260230104526] uni_v_p40_p42_y_10:[0.996461518738,0.999703251068] uni_v_p40_p42_z_10:[0.00209845125848,0.00955563014847] w1_p40_p42_x_10:[-0.0886190115559,-0.0279722386057] w1_p40_p42_y_10:[0.996065595612,0.999660033775] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.634228616476,-0.604493730048] w2_p40_p42_y_10:[-0.0594470724276,-0.0173151441937] w2_p40_p42_z_10:[0.771216500084,0.796441326958] cos_0_p40_p42_10:[0.99806966546,1] cos_1_p40_p42_10:[0.951529667587,0.964483003403] w1_p42_p43_x_11:[-0.634228616476,-0.604493730048] w1_p42_p43_y_11:[-0.0594470724276,-0.0173151441937] w1_p42_p43_z_11:[0.771216500084,0.796441326958] w2_p42_p43_x_11:[0.0882451881716,0.11413660674] w2_p42_p43_y_11:[-0.00238558857841,0] w2_p42_p43_z_11:[0.993443771096,0.996182193458] cos_p42_p43_11:[0.707106781187,0.736785477695] w1_p43_p44_x_12:[-0.639943611719,-0.620022364015] w1_p43_p44_y_12:[-0.0595669541268,-0.018427092643] w1_p43_p44_z_12:[0.766482003525,0.783080532453] w2_p43_p44_x_12:[0.0495783411198,0.114817260347] w2_p43_p44_y_12:[-0,0.0024260021781] w2_p43_p44_z_12:[0.993369190918,0.999131883397] cos_p43_p44_12:[0.707106781187,0.736785477695] sph_w1_p24_X_2_x_13:[0.268060975849,0.301150670696] sph_w1_p24_X_2_y_13:[-0.323174483496,-0.275699160348] sph_w1_p24_X_2_z_13:[-0.923322294914,-0.899588134484] sph_w2_p24_X_2_x_13:[0.443599160327,0.50375084285] sph_w2_p24_X_2_y_13:[0.8572716612,0.892040147856] sph_w2_p24_X_2_z_13:[-0.108045687668,-0.0844107529402] cos_p24_X_2_13:[-0.0801906829112,0.000236564443655] in_patch_X_2_object_u_14:[0.437499999996,0.500000000005] in_patch_X_2_object_v_14:[0.499999999995,0.562500000006] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.982053085689,-0.964370147265] sph_w1_p44_X_4_y_15:[-0.0833110294461,-0.0253883438508] sph_w1_p44_X_4_z_15:[0.188926650216,0.252797539587] sph_w2_p44_X_4_x_15:[-0.811684537384,-0.784009365163] sph_w2_p44_X_4_y_15:[0.234983577639,0.298458505592] sph_w2_p44_X_4_z_15:[0.528614559093,0.545115275755] cos_p44_X_4_15:[0.862218688155,0.900259094142] in_patch_X_4_object_u_16:[0.499999999995,0.562500000006] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.288794030226,0.355248033358] sph_w2_palm_X_P_y_17:[0.934867057743,0.957707215323] sph_w2_palm_X_P_z_17:[-0,0.0237500857173] cos_palm_X_P_17:[0.881033485621,0.912709821848] in_patch_X_P_object_u_18:[0.678533625502,0.697945134837] in_patch_X_P_object_v_18:[0.437499999996,0.500000000005] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972218381,-4.08027781619] p14_r_y:[-36.8121602031,-36.8091080357] p14_r_z:[243.17222928,243.172509987] p34_r_x:[-4.52103876199,-4.07896123802] p34_r_y:[36.6933268818,36.6962687162] p34_r_z:[243.16818251,243.168466596] }
   4 (err:2.08665 min:3.53949 tm:254):{ 257  p12_u_x:[-0.00146777626978,0.00146777626978] p12_u_y:[0.0342826886095,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.00400689831697,0.00400689831697] p13_u_y:[0.0342824503286,0.0343138102708] p13_u_z:[0.999404153966,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.00852088926254,0.00852088926254] p14_u_y:[0.0342814809576,0.0343138058481] p14_u_z:[0.999375902758,0.999412174963] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.398967441861,0.422073198797] p22_u_y:[0.260357267742,0.305556656161] p22_u_z:[0.854233017752,0.868410978483] p22_v_x:[-0,0] p22_v_y:[-0.958228633366,-0.942001935579] p22_v_z:[0.287040167854,0.335603203991] p23_u_x:[0.795889568849,0.807892025983] p23_u_y:[0.169012152467,0.201039668114] p23_u_z:[0.556892560886,0.571610988956] p23_v_x:[-0,0] p23_v_y:[-0.958228633366,-0.942001935579] p23_v_z:[0.287040167854,0.335603203991] p24_u_x:[0.986520154192,0.991401717113] p24_u_y:[0.037405951678,0.0543345197532] p24_u_z:[0.12546819361,0.154740081482] p24_v_x:[-0,0] p24_v_y:[-0.958228633366,-0.942001935579] p24_v_z:[0.287040167854,0.335603203991] p32_u_x:[-0.00148003356597,0.00148003356597] p32_u_y:[-0.0354977247751,-0.0354676761855] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308278097,0.00402308278097] p33_u_y:[-0.0354975792585,-0.0354674280045] p33_u_z:[0.999362736614,0.999370823594] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855588480224,0.00855588480224] p34_u_y:[-0.0354977039525,-0.0354664168226] p34_u_z:[0.999334253664,0.999370823213] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0886190115559,-0.0290162334231] p40_v_y:[0.996065595612,0.999635536494] p40_v_z:[-0,0] p42_u_x:[0.0958713855332,0.13435506143] p42_u_y:[-0.00297869487112,0.0029886604696] p42_u_z:[0.990811418293,0.995446081142] p42_v_x:[-0.0835710385341,-0.026990306956] p42_v_y:[0.996464151743,0.999682303729] p42_v_z:[0.00218512155958,0.00955640883139] p43_u_x:[0.0888852075103,0.114168870148] p43_u_y:[-0.00231095950527,0] p43_u_z:[0.993440186464,0.996120905624] p43_v_x:[-0.0835710385341,-0.026990306956] p43_v_y:[0.996464151743,0.999682303729] p43_v_z:[0.00218512155958,0.00955640883139] p44_u_x:[0.0517905683525,0.114827938515] p44_u_y:[-0,0.00234956938302] p44_u_z:[0.993367133771,0.998979430175] p44_v_x:[-0.0835710385341,-0.026990306956] p44_v_y:[0.996464151743,0.999682303729] p44_v_z:[0.00218512155958,0.00955640883139] object_u_x:[-0.431775148113,-0.368824483208] object_u_y:[-0.929121567301,-0.900463157886] object_u_z:[0.0312415594276,0.0548750641869] object_v_x:[-0.514786744837,-0.502568322973] object_v_y:[0.164302606904,0.191914566704] object_v_z:[-0.848822872586,-0.839176963975] X_P_u_x:[-0.9575648227,-0.935159212631] X_P_u_y:[0.288518215514,0.354495332763] X_P_u_z:[-0.0616607396334,0] X_P_v_x:[-0.0643013369068,0] X_P_v_y:[-0.0246049814028,0] X_P_v_z:[0.997866819808,1] X_2_u_x:[-0,0.0566773575722] X_2_u_y:[0.0730153675226,0.124891623771] X_2_u_z:[0.992158746241,0.996985492138] X_2_v_x:[0.862460434437,0.897624642268] X_2_v_y:[-0.506340951636,-0.440039115514] X_2_v_z:[-0,0.0631607661674] X_4_u_x:[0.582272603881,0.623373377406] X_4_u_y:[0.276250991636,0.364341384468] X_4_u_z:[0.693729177784,0.750514770755] X_4_v_x:[-0,0.0693532158027] X_4_v_y:[0.880166693426,0.914946611225] X_4_v_z:[-0.474716084087,-0.403574898415] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649769101e-05,5.03649769101e-05] w2_palm_p12_z_0:[-0.00146691349497,0.00146691349497] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626978,0.00146777626978] w1_p12_p13_y_1:[0.0342826886095,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.00400689831697,0.00400689831697] w2_p12_p13_y_1:[0.0342824503286,0.0343138102708] w2_p12_p13_z_1:[0.999404153966,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00400689831697,0.00400689831697] w1_p13_p14_y_2:[0.0342824503286,0.0343138102708] w1_p13_p14_z_2:[0.999404153966,0.999412148261] w2_p13_p14_x_2:[-0.00852088926254,0.00852088926254] w2_p13_p14_y_2:[0.0342814809576,0.0343138058481] w2_p13_p14_z_2:[0.999375902758,0.999412174963] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.958228633366,-0.942001935579] uni_v_palm_p22_z_3:[0.287040167854,0.335603203991] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.929602340249,0.940010696032] w2_palm_p22_y_3:[0.0978186060402,0.122021448294] w2_palm_p22_z_3:[0.322532678821,0.345532207207] cos_0_palm_p22_3:[0.942001935579,0.958228633366] cos_1_palm_p22_3:[0.929602340249,0.940010696032] w1_p22_p23_x_4:[0.929602340249,0.940010696032] w1_p22_p23_y_4:[0.0978186060402,0.122021448294] w1_p22_p23_z_4:[0.322532678821,0.345532207207] w2_p22_p23_x_4:[0.795889568849,0.807892025983] w2_p22_p23_y_4:[0.169012152467,0.201039668114] w2_p22_p23_z_4:[0.556892560886,0.571610988956] cos_p22_p23_4:[0.954452266654,0.963682265986] w1_p23_p24_x_5:[0.987505273141,0.991189673332] w1_p23_p24_y_5:[-0.0509500193212,-0.0432462825687] w1_p23_p24_z_5:[-0.1480216757,-0.126821308468] w2_p23_p24_x_5:[0.986520154192,0.991401717113] w2_p23_p24_y_5:[0.037405951678,0.0543345197532] w2_p23_p24_z_5:[0.12546819361,0.154740081482] cos_p23_p24_5:[0.954452266654,0.963682265986] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681426e-05,5.25377681426e-05] w2_palm_p32_z_6:[-0.00147910237338,0.00147910238377] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356597,0.00148003356597] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761855] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308278097,0.00402308278097] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674280045] w2_p32_p33_z_7:[0.999362736614,0.999370823594] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308278097,0.00402308278097] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674280045] w1_p33_p34_z_8:[0.999362736614,0.999370823594] w2_p33_p34_x_8:[-0.00855588480224,0.00855588480224] w2_p33_p34_y_8:[-0.0354977039525,-0.0354664168226] w2_p33_p34_z_8:[0.999334253664,0.999370823213] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999635536494,-0.996065595612] w2_palm_p40_y_9:[-0.0886190115559,-0.0290162334231] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.72730826945,0.767325336566] uni_u_p40_p42_x_10:[-0.818851147196,-0.815926831199] uni_u_p40_p42_y_10:[-0.072592236497,-0.0237686388271] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0835710385341,-0.026990306956] uni_v_p40_p42_y_10:[0.996464151743,0.999682303729] uni_v_p40_p42_z_10:[0.00218512155958,0.00955640883139] w1_p40_p42_x_10:[-0.0886190115559,-0.0290162334231] w1_p40_p42_y_10:[0.996065595612,0.999635536494] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.633938701868,-0.605215056542] w2_p40_p42_y_10:[-0.0594234729607,-0.0180531436912] w2_p40_p42_z_10:[0.771452302489,0.795887110409] cos_0_p40_p42_10:[0.998123856123,1] cos_1_p40_p42_10:[0.951792026171,0.964370533859] w1_p42_p43_x_11:[-0.633938701868,-0.605215056542] w1_p42_p43_y_11:[-0.0594234729607,-0.0180531436912] w1_p42_p43_z_11:[0.771452302489,0.795887110409] w2_p42_p43_x_11:[0.0888852075103,0.114168870148] w2_p42_p43_y_11:[-0.00231095950527,0] w2_p42_p43_z_11:[0.993440186464,0.996120905624] cos_p42_p43_11:[0.707106781187,0.735764127485] w1_p43_p44_x_12:[-0.639344233031,-0.619959340926] w1_p43_p44_y_12:[-0.0595380286553,-0.0191173215367] w1_p43_p44_z_12:[0.766893055248,0.78309435651] w2_p43_p44_x_12:[0.0517905683525,0.114827938515] w2_p43_p44_y_12:[-0,0.00234956938302] w2_p43_p44_z_12:[0.993367133771,0.998979430175] cos_p43_p44_12:[0.707106781187,0.735764127485] sph_w1_p24_X_2_x_13:[0.268100521981,0.300538694455] sph_w1_p24_X_2_y_13:[-0.323140098483,-0.2765002208] sph_w1_p24_X_2_z_13:[-0.923062761931,-0.899759249184] sph_w2_p24_X_2_x_13:[0.44347053485,0.503067055742] sph_w2_p24_X_2_y_13:[0.857689105139,0.892128040523] sph_w2_p24_X_2_z_13:[-0.107899675131,-0.0844058292611] cos_p24_X_2_13:[-0.0803270418455,-0.000937126857144] in_patch_X_2_object_u_14:[0.437499999996,0.500000000005] in_patch_X_2_object_v_14:[0.499999999995,0.562500000006] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.981571894158,-0.96435460715] sph_w1_p44_X_4_y_15:[-0.0832753823014,-0.0263659949015] sph_w1_p44_X_4_z_15:[0.191094239303,0.252797515722] sph_w2_p44_X_4_x_15:[-0.811985443582,-0.784708658195] sph_w2_p44_X_4_y_15:[0.234812590136,0.297908427721] sph_w2_p44_X_4_z_15:[0.528183585468,0.544378504688] cos_p44_X_4_15:[0.863412400692,0.900340301023] in_patch_X_4_object_u_16:[0.499999999995,0.562500000006] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.288590040137,0.354412345268] sph_w2_palm_X_P_y_17:[0.935182244127,0.957760150105] sph_w2_palm_X_P_z_17:[-0,0.0236049738082] cos_palm_X_P_17:[0.880931325232,0.912332380235] in_patch_X_P_object_u_18:[0.678824452746,0.69785895766] in_patch_X_P_object_v_18:[0.374999999996,0.437500000004] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972218064,-4.08027781936] p14_r_y:[-36.8121590993,-36.8091077707] p14_r_z:[243.172229409,243.172509987] p34_r_x:[-4.52103875924,-4.07896124076] p34_r_y:[36.6933268818,36.6962683538] p34_r_z:[243.16818251,243.168466593] }
   5 (err:2.42158 min:3.56073 tm:254):{ 257  p12_u_x:[-0.00146777626948,0.00146777626948] p12_u_y:[0.0342826886202,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.00400690916376,0.00400690916376] p13_u_y:[0.0342824503271,0.0343138058608] p13_u_z:[0.999404153527,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.00852105145985,0.00852105145985] p14_u_y:[0.0342814809102,0.0343138102634] p14_u_z:[0.999375903152,0.999412174963] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.403440599918,0.422073198797] p22_u_y:[0.269292931311,0.306651443426] p22_u_z:[0.853511722829,0.865372832669] p22_v_x:[-0,0] p22_v_y:[-0.955023442065,-0.94133113893] p22_v_z:[0.296791754007,0.337557344301] p23_u_x:[0.797684082831,0.808018513873] p23_u_y:[0.174643956159,0.201619830793] p23_u_z:[0.55570502176,0.56886272866] p23_v_x:[-0,0] p23_v_y:[-0.955023442065,-0.94133113893] p23_v_z:[0.296791754007,0.337557344301] p24_u_x:[0.987381887531,0.991406166575] p24_u_y:[0.0381998964865,0.0528871692143] p24_u_z:[0.12546819361,0.149024844236] p24_v_x:[-0,0] p24_v_y:[-0.955023442065,-0.94133113893] p24_v_z:[0.296791754007,0.337557344301] p32_u_x:[-0.00148003356563,0.00148003356563] p32_u_y:[-0.0354977247751,-0.0354676761748] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308285973,0.00402308285973] p33_u_y:[-0.0354975792585,-0.0354674279937] p33_u_z:[0.999362736429,0.999370822835] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855591046115,0.00855591046115] p34_u_y:[-0.0354976869741,-0.0354664168255] p34_u_z:[0.999334251712,0.999370823901] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0886190115559,-0.0394900497664] p40_v_y:[0.996065595612,0.999365178798] p40_v_z:[-0,0] p42_u_x:[0.0989696107506,0.134933362741] p42_u_y:[-0.00281658027104,0.0032213863676] p42_u_z:[0.990706680786,0.995282834614] p42_v_x:[-0.0835250096265,-0.0367161890187] p42_v_y:[0.99646266591,0.99945665884] p42_v_z:[0.0030824063916,0.0096320945537] p43_u_x:[0.0914964363169,0.11523686535] p43_u_y:[-0.0022561026579,0] p43_u_z:[0.993337221869,0.995844767027] p43_v_x:[-0.0835250096265,-0.0367161890187] p43_v_y:[0.99646266591,0.99945665884] p43_v_z:[0.0030824063916,0.0096320945537] p44_u_x:[0.0527067500052,0.115970785116] p44_u_y:[-0,0.00230099965692] p44_u_z:[0.993311987449,0.998832463836] p44_v_x:[-0.0835250096265,-0.0367161890187] p44_v_y:[0.99646266591,0.99945665884] p44_v_z:[0.0030824063916,0.0096320945537] object_u_x:[-0.422348161648,-0.368635878601] object_u_y:[-0.929332383596,-0.904629029505] object_u_z:[0.034810335715,0.0549070563854] object_v_x:[-0.516056353589,-0.50581466424] object_v_y:[0.163855833769,0.186816867107] object_v_z:[-0.846948158415,-0.838992680177] X_P_u_x:[-0.957728919842,-0.938442093942] X_P_u_y:[0.288423952849,0.344783221336] X_P_u_z:[-0.0616307487397,0] X_P_v_x:[-0.0643013369068,0] X_P_v_y:[-0.0212394578885,0] X_P_v_z:[0.997912504079,1] X_2_u_x:[-0,0.0557456681797] X_2_u_y:[0.0761454230605,0.124445161743] X_2_u_z:[0.992179121007,0.996630543771] X_2_v_x:[0.867418220948,0.897782393461] X_2_v_y:[-0.497236432958,-0.439681671354] X_2_v_z:[-0,0.0620927454499] X_4_u_x:[0.584466906642,0.620264415484] X_4_u_y:[0.282357581924,0.364341384468] X_4_u_z:[0.696170420994,0.748359093987] X_4_v_x:[-0,0.0598200581611] X_4_v_y:[0.88279436515,0.914946611225] X_4_v_z:[-0.469766540145,-0.403574898415] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649768997e-05,5.03649768997e-05] w2_palm_p12_z_0:[-0.00146691349467,0.00146691348429] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626948,0.00146777626948] w1_p12_p13_y_1:[0.0342826886202,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.00400690916376,0.00400690916376] w2_p12_p13_y_1:[0.0342824503271,0.0343138058608] w2_p12_p13_z_1:[0.999404153527,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00400690916376,0.00400690916376] w1_p13_p14_y_2:[0.0342824503271,0.0343138058608] w1_p13_p14_z_2:[0.999404153527,0.999412148261] w2_p13_p14_x_2:[-0.00852105145985,0.00852105145985] w2_p13_p14_y_2:[0.0342814809102,0.0343138102634] w2_p13_p14_z_2:[0.999375903152,0.999412174963] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.955023442065,-0.94133113893] uni_v_palm_p22_z_3:[0.296791754007,0.337557344301] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.931240229053,0.940059075232] w2_palm_p22_y_3:[0.101239802997,0.121264796713] w2_palm_p22_z_3:[0.322229376493,0.340937780444] cos_0_palm_p22_3:[0.94133113893,0.955023442065] cos_1_palm_p22_3:[0.931240229053,0.940059075232] w1_p22_p23_x_4:[0.931240229053,0.940059075232] w1_p22_p23_y_4:[0.101239802997,0.121264796713] w1_p22_p23_z_4:[0.322229376493,0.340937780444] w2_p22_p23_x_4:[0.797684082831,0.808018513873] w2_p22_p23_y_4:[0.174643956159,0.201619830793] w2_p22_p23_z_4:[0.55570502176,0.56886272866] cos_p22_p23_4:[0.955194752616,0.963005568797] w1_p23_p24_x_5:[0.987431830445,0.990758803481] w1_p23_p24_y_5:[-0.0518212991909,-0.0447264307117] w1_p23_p24_z_5:[-0.147815438997,-0.129546270657] w2_p23_p24_x_5:[0.987381887531,0.991406166575] w2_p23_p24_y_5:[0.0381998964865,0.0528871692143] w2_p23_p24_z_5:[0.12546819361,0.149024844236] cos_p23_p24_5:[0.955194752616,0.963005568797] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681306e-05,5.25377681306e-05] w2_palm_p32_z_6:[-0.00147910237304,0.00147910238343] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356563,0.00148003356563] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761748] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308285973,0.00402308285973] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674279937] w2_p32_p33_z_7:[0.999362736429,0.999370822835] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308285973,0.00402308285973] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674279937] w1_p33_p34_z_8:[0.999362736429,0.999370822835] w2_p33_p34_x_8:[-0.00855591046115,0.00855591046115] w2_p33_p34_y_8:[-0.0354976869741,-0.0354664168255] w2_p33_p34_z_8:[0.999334251712,0.999370823901] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999365178798,-0.996065595612] w2_palm_p40_y_9:[-0.0886190115559,-0.0394900497664] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.734410509856,0.767355398019] uni_u_p40_p42_x_10:[-0.818629683771,-0.815926831199] uni_u_p40_p42_y_10:[-0.072592236497,-0.032348262315] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0835250096265,-0.0367161890187] uni_v_p40_p42_y_10:[0.99646266591,0.99945665884] uni_v_p40_p42_z_10:[0.0030824063916,0.0096320945537] w1_p40_p42_x_10:[-0.0886190115559,-0.0394900497664] w1_p40_p42_y_10:[0.996065595612,0.999365178798] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.631660409113,-0.604311336358] w2_p40_p42_y_10:[-0.0594154271532,-0.0253121697201] w2_p40_p42_z_10:[0.773525646599,0.796211061298] cos_0_p40_p42_10:[0.997961007646,1] cos_1_p40_p42_10:[0.951000229374,0.963727494429] w1_p42_p43_x_11:[-0.631660409113,-0.604311336358] w1_p42_p43_y_11:[-0.0594154271532,-0.0253121697201] w1_p42_p43_z_11:[0.773525646599,0.796211061298] w2_p42_p43_x_11:[0.0914964363169,0.11523686535] w2_p42_p43_y_11:[-0.0022561026579,0] w2_p42_p43_z_11:[0.993337221869,0.995844767027] cos_p42_p43_11:[0.707106781187,0.735782518198] w1_p43_p44_x_12:[-0.637921837129,-0.618757240381] w1_p43_p44_y_12:[-0.0595326398684,-0.0260277104132] w1_p43_p44_z_12:[0.768532694329,0.783737893549] w2_p43_p44_x_12:[0.0527067500052,0.115970785116] w2_p43_p44_y_12:[-0,0.00230099965692] w2_p43_p44_z_12:[0.993311987449,0.998832463836] cos_p43_p44_12:[0.707106781187,0.735782518198] sph_w1_p24_X_2_x_13:[0.26821988296,0.294843143591] sph_w1_p24_X_2_y_13:[-0.325014554089,-0.285942436703] sph_w1_p24_X_2_z_13:[-0.919929942206,-0.900631234658] sph_w2_p24_X_2_x_13:[0.443192025987,0.494008997699] sph_w2_p24_X_2_y_13:[0.862628755171,0.892273927528] sph_w2_p24_X_2_z_13:[-0.107962580712,-0.0879594429692] cos_p24_X_2_13:[-0.0807493382372,-0.0132837711588] in_patch_X_2_object_u_14:[0.437499999996,0.500000000005] in_patch_X_2_object_v_14:[0.499999999995,0.562500000006] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.980946630904,-0.964040763781] sph_w1_p44_X_4_y_15:[-0.08325515074,-0.0360358289714] sph_w1_p44_X_4_z_15:[0.191931299108,0.253921659219] sph_w2_p44_X_4_x_15:[-0.810367727238,-0.787284246496] sph_w2_p44_X_4_y_15:[0.235177898909,0.289611272144] sph_w2_p44_X_4_z_15:[0.531085911573,0.544695709216] cos_p44_X_4_15:[0.86367615639,0.899376600401] in_patch_X_4_object_u_16:[0.562499999994,0.625000000006] in_patch_X_4_object_v_16:[0.374999999996,0.437500000004] in_patch_X_4_object_l_16:[9.71993866774,9.72381781325] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.288497327943,0.344684307927] sph_w2_palm_X_P_y_17:[0.938512989248,0.957948446207] sph_w2_palm_X_P_z_17:[-0,0.0200611555289] cos_palm_X_P_17:[0.880885432939,0.907789252858] in_patch_X_P_object_u_18:[0.682738744846,0.698477774268] in_patch_X_P_object_v_18:[0.437499999996,0.500000000005] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972250603,-4.08027749398] p14_r_y:[-36.8121602032,-36.809107903] p14_r_z:[243.172229346,243.172509987] p34_r_x:[-4.52103876158,-4.07896123842] p34_r_y:[36.6933268818,36.6962675589] p34_r_z:[243.168182456,243.168466567] }
   6 (err:2.0937 min:3.52692 tm:254):{ 257  p12_u_x:[-0.00146777626948,0.00146777626948] p12_u_y:[0.0342826886095,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.00400690916376,0.00400690916376] p13_u_y:[0.0342824503378,0.034313797027] p13_u_z:[0.999404153527,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.00852105145985,0.00852105145985] p14_u_y:[0.0342814809102,0.0343138102634] p14_u_z:[0.999375904085,0.999412174963] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.39762714246,0.422073198797] p22_u_y:[0.259228731779,0.306740592636] p22_u_z:[0.853891792028,0.868797097464] p22_v_x:[-0,0] p22_v_y:[-0.958637888733,-0.941596876932] p22_v_z:[0.285782937028,0.336746499129] p23_u_x:[0.795304625673,0.808067705519] p23_u_y:[0.168242238983,0.201906055328] p23_u_z:[0.556585331994,0.572165510073] p23_v_x:[-0,0] p23_v_y:[-0.958637888733,-0.941596876932] p23_v_z:[0.285782937028,0.336746499129] p24_u_x:[0.986224182509,0.991406166575] p24_u_y:[0.0372495552684,0.0550950405042] p24_u_z:[0.12546819361,0.156403888758] p24_v_x:[-0,0] p24_v_y:[-0.958637888733,-0.941596876932] p24_v_z:[0.285782937028,0.336746499129] p32_u_x:[-0.00148003356563,0.00148003356563] p32_u_y:[-0.0354977247751,-0.0354676761748] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308285973,0.00402308285973] p33_u_y:[-0.0354975792585,-0.0354674280045] p33_u_z:[0.999362737081,0.999370823703] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855591046115,0.00855591046115] p34_u_y:[-0.0354976869741,-0.0354664168255] p34_u_z:[0.999334251712,0.999370823901] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0886190115559,-0.0261173380508] p40_v_y:[0.996065595612,0.999704609028] p40_v_z:[-0,0] p42_u_x:[0.0945765351464,0.137191263223] p42_u_y:[-0.00330737471048,0.00331199386716] p42_u_z:[0.99041843149,0.995564243311] p42_v_x:[-0.0836897840106,-0.0243093488575] p42_v_y:[0.996455218704,0.999742384792] p42_v_z:[0.00192537394483,0.00952912016417] p43_u_x:[0.0868385146024,0.113837715749] p43_u_y:[-0.0025866300525,0] p43_u_z:[0.993477505272,0.996313709724] p43_v_x:[-0.0836897840106,-0.0243093488575] p43_v_y:[0.996455218704,0.999742384792] p43_v_z:[0.00192537394483,0.00952912016417] p44_u_x:[0.0437328961995,0.114593631843] p44_u_y:[-0,0.00263356379066] p44_u_z:[0.99341357058,0.999495181911] p44_v_x:[-0.0836897840106,-0.0243093488575] p44_v_y:[0.996455218704,0.999742384792] p44_v_z:[0.00192537394483,0.00952912016417] object_u_x:[-0.432999179312,-0.368384949957] object_u_y:[-0.929332383596,-0.899880389153] object_u_z:[0.0309412314113,0.0549570485802] object_v_x:[-0.515466373989,-0.502715001144] object_v_y:[0.163827116734,0.192841063415] object_v_z:[-0.848834681969,-0.838666840443] X_P_u_x:[-0.957728919842,-0.934667703573] X_P_u_y:[0.288069821478,0.355812809851] X_P_u_z:[-0.0616687420421,0] X_P_v_x:[-0.0643013369068,0] X_P_v_y:[-0.0249922599553,0] X_P_v_z:[0.997860814647,1] X_2_u_x:[-0,0.0569369115046] X_2_u_y:[0.0727461874498,0.125160682608] X_2_u_z:[0.992125307423,0.997011874905] X_2_v_x:[0.861798749587,0.897869990189] X_2_v_y:[-0.507484566923,-0.439573713176] X_2_v_z:[-0,0.0634376937158] X_4_u_x:[0.581999816314,0.624575868305] X_4_u_y:[0.275319014875,0.364341384468] X_4_u_z:[0.692709557742,0.750610324639] X_4_v_x:[-0,0.0702604921179] X_4_v_y:[0.879772367621,0.914946611225] X_4_v_z:[-0.475449300567,-0.403574898415] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649768997e-05,5.03649768997e-05] w2_palm_p12_z_0:[-0.00146691349467,0.00146691349467] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626948,0.00146777626948] w1_p12_p13_y_1:[0.0342826886095,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.00400690916376,0.00400690916376] w2_p12_p13_y_1:[0.0342824503378,0.034313797027] w2_p12_p13_z_1:[0.999404153527,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00400690916376,0.00400690916376] w1_p13_p14_y_2:[0.0342824503378,0.034313797027] w1_p13_p14_z_2:[0.999404153527,0.999412148261] w2_p13_p14_x_2:[-0.00852105145985,0.00852105145985] w2_p13_p14_y_2:[0.0342814809102,0.0343138102634] w2_p13_p14_z_2:[0.999375904085,0.999412174963] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.958637888733,-0.941596876932] uni_v_palm_p22_z_3:[0.285782937028,0.336746499129] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.9289862402,0.940059075241] w2_palm_p22_y_3:[0.097335237975,0.122853472706] w2_palm_p22_z_3:[0.322376903301,0.346690861541] cos_0_palm_p22_3:[0.941596876932,0.958637888733] cos_1_palm_p22_3:[0.9289862402,0.940059075241] w1_p22_p23_x_4:[0.9289862402,0.940059075241] w1_p22_p23_y_4:[0.097335237975,0.122853472706] w1_p22_p23_z_4:[0.322376903301,0.346690861541] w2_p22_p23_x_4:[0.795304625673,0.808067705519] w2_p22_p23_y_4:[0.168242238983,0.201906055328] w2_p22_p23_z_4:[0.556585331994,0.572165510073] cos_p22_p23_4:[0.954103850249,0.963914289729] w1_p23_p24_x_5:[0.987417067852,0.991348253477] w1_p23_p24_y_5:[-0.0511186834904,-0.0430016072012] w1_p23_p24_z_5:[-0.148341841611,-0.125849766309] w2_p23_p24_x_5:[0.986224182509,0.991406166575] w2_p23_p24_y_5:[0.0372495552684,0.0550950405042] w2_p23_p24_z_5:[0.12546819361,0.156403888758] cos_p23_p24_5:[0.954103850249,0.963914289729] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681306e-05,5.25377681306e-05] w2_palm_p32_z_6:[-0.00147910238343,0.00147910237304] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356563,0.00148003356563] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761748] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308285973,0.00402308285973] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674280045] w2_p32_p33_z_7:[0.999362737081,0.999370823703] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308285973,0.00402308285973] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674280045] w1_p33_p34_z_8:[0.999362737081,0.999370823703] w2_p33_p34_x_8:[-0.00855591046115,0.00855591046115] w2_p33_p34_y_8:[-0.0354976869741,-0.0354664168255] w2_p33_p34_z_8:[0.999334251712,0.999370823901] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999704609028,-0.996065595612] w2_palm_p40_y_9:[-0.0886190115559,-0.0261173380508] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.72531438924,0.767355398019] uni_u_p40_p42_x_10:[-0.818907727941,-0.815926831199] uni_u_p40_p42_y_10:[-0.072592236497,-0.0213940095602] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0836897840106,-0.0243093488575] uni_v_p40_p42_y_10:[0.996455218704,0.999742384792] uni_v_p40_p42_z_10:[0.00192537394483,0.00952912016417] w1_p40_p42_x_10:[-0.0886190115559,-0.0261173380508] w1_p40_p42_y_10:[0.996065595612,0.999704609028] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.634960526477,-0.602887529895] w2_p40_p42_y_10:[-0.0595012711965,-0.0161190813762] w2_p40_p42_z_10:[0.770623935649,0.797665523494] cos_0_p40_p42_10:[0.997961826453,1] cos_1_p40_p42_10:[0.950961207467,0.964764375912] w1_p42_p43_x_11:[-0.634960526477,-0.602887529895] w1_p42_p43_y_11:[-0.0595012711965,-0.0161190813762] w1_p42_p43_z_11:[0.770623935649,0.797665523494] w2_p42_p43_x_11:[0.0868385146024,0.113837715749] w2_p42_p43_y_11:[-0.0025866300525,0] w2_p42_p43_z_11:[0.993477505272,0.996313709724] cos_p42_p43_11:[0.707106781187,0.739421951727] w1_p43_p44_x_12:[-0.641612569352,-0.620317380531] w1_p43_p44_y_12:[-0.0596292920314,-0.0172039440864] w1_p43_p44_z_12:[0.76557629792,0.782904332002] w2_p43_p44_x_12:[0.0437328961995,0.114593631843] w2_p43_p44_y_12:[-0,0.00263356379066] w2_p43_p44_z_12:[0.99341357058,0.999495181911] cos_p43_p44_12:[0.707106781187,0.739421951727] sph_w1_p24_X_2_x_13:[0.26802339517,0.302301887546] sph_w1_p24_X_2_y_13:[-0.324241356193,-0.275292618731] sph_w1_p24_X_2_z_13:[-0.923468520044,-0.898918841517] sph_w2_p24_X_2_x_13:[0.443039056537,0.504191346868] sph_w2_p24_X_2_y_13:[0.857020400509,0.892345956426] sph_w2_p24_X_2_z_13:[-0.108060879305,-0.0841920881127] cos_p24_X_2_13:[-0.0814300274222,0.000877241499275] in_patch_X_2_object_u_14:[0.437499999996,0.500000000005] in_patch_X_2_object_v_14:[0.499999999995,0.562500000006] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.98326955667,-0.964466095008] sph_w1_p44_X_4_y_15:[-0.0833919795555,-0.0236475939139] sph_w1_p44_X_4_z_15:[0.183191537309,0.252607782394] sph_w2_p44_X_4_x_15:[-0.812178750353,-0.783831393872] sph_w2_p44_X_4_y_15:[0.234709436189,0.298873898517] sph_w2_p44_X_4_z_15:[0.528134166553,0.545192126754] cos_p44_X_4_15:[0.860166058066,0.900819253725] in_patch_X_4_object_u_16:[0.499999999995,0.562500000006] in_patch_X_4_object_v_16:[0.374999999996,0.437500000004] in_patch_X_4_object_l_16:[9.71993866774,9.72381781325] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.288143576499,0.355727557522] sph_w2_palm_X_P_y_17:[0.934690642921,0.957949985287] sph_w2_palm_X_P_z_17:[-0,0.023990921771] cos_palm_X_P_17:[0.880711618058,0.912939482411] in_patch_X_P_object_u_18:[0.678370683246,0.698442169458] in_patch_X_P_object_v_18:[0.437499999996,0.500000000005] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972250603,-4.08027749398] p14_r_y:[-36.8121602032,-36.8091081691] p14_r_z:[243.172229346,243.172509987] p34_r_x:[-4.52103876158,-4.07896123842] p34_r_y:[36.6933268818,36.6962687162] p34_r_z:[243.168182564,243.168466596] }
   7 (err:2.09725 min:3.53677 tm:254):{ 257  p12_u_x:[-0.00146777626948,0.00146777626948] p12_u_y:[0.0342826886202,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.00400690915779,0.00400690915779] p13_u_y:[0.0342824503271,0.0343138014306] p13_u_z:[0.999404154234,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.0085210514598,0.0085210514598] p14_u_y:[0.0342814809102,0.0343138014413] p14_u_z:[0.999375904541,0.999412174963] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.398055376822,0.422073198797] p22_u_y:[0.259809163717,0.30669521532] p22_u_z:[0.853878839877,0.868584252922] p22_v_x:[-0,0] p22_v_y:[-0.958434522792,-0.941592283849] p22_v_z:[0.286423922716,0.336755711358] p23_u_x:[0.795481591372,0.808033443677] p23_u_y:[0.168586301526,0.201853028105] p23_u_z:[0.556578048995,0.571927648547] p23_v_x:[-0,0] p23_v_y:[-0.958434522792,-0.941592283849] p23_v_z:[0.286423922716,0.336755711358] p24_u_x:[0.98631479408,0.991406000849] p24_u_y:[0.0373046035036,0.0549204616205] p24_u_z:[0.12546819361,0.155873108802] p24_v_x:[-0,0] p24_v_y:[-0.958434522792,-0.941592283849] p24_v_z:[0.286423922716,0.336755711358] p32_u_x:[-0.00148003356597,0.00148003356597] p32_u_y:[-0.0354977247751,-0.0354676761748] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308279664,0.00402308279664] p33_u_y:[-0.0354975792585,-0.0354674279938] p33_u_z:[0.999362737117,0.999370823124] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855584270056,0.00855584270056] p34_u_y:[-0.0354976954759,-0.0354664168354] p34_u_z:[0.999334254893,0.999370823322] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0886190115559,-0.0268827957266] p40_v_y:[0.996065595612,0.999692014287] p40_v_z:[-0,0] p42_u_x:[0.0948994426879,0.136851926433] p42_u_y:[-0.00327749020374,0.00327748092045] p42_u_z:[0.99046438641,0.995538945485] p42_v_x:[-0.0836656358065,-0.0250193488232] p42_v_y:[0.996456651241,0.999731813219] p42_v_z:[0.0019714418269,0.00953461120082] p43_u_x:[0.0873111194858,0.113896980762] p43_u_y:[-0.00255694641456,0] p43_u_z:[0.993470572188,0.996268562016] p43_v_x:[-0.0836656358065,-0.0250193488232] p43_v_y:[0.996456651241,0.999731813219] p43_v_z:[0.0019714418269,0.00953461120082] p44_u_x:[0.0447223915504,0.114653021646] p44_u_y:[-0,0.00260347428271] p44_u_z:[0.993407375787,0.999425574304] p44_v_x:[-0.0836656358065,-0.0250193488232] p44_v_y:[0.996456651241,0.999731813219] p44_v_z:[0.0019714418269,0.00953461120082] object_u_x:[-0.432426168151,-0.368191237654] object_u_y:[-0.929385819636,-0.900152814703] object_u_z:[0.0309765654202,0.054886122184] object_v_x:[-0.514895195018,-0.502284526175] object_v_y:[0.163634757858,0.192268511074] object_v_z:[-0.849125023886,-0.839120558007] X_P_u_x:[-0.957769084695,-0.934902038169] X_P_u_y:[0.287837505069,0.355175712786] X_P_u_z:[-0.0616732715809,0] X_P_v_x:[-0.0643013369068,0] X_P_v_y:[-0.0248940630763,0] X_P_v_z:[0.997862028629,1] X_2_u_x:[-0,0.056799179656] X_2_u_y:[0.072744166568,0.124964980995] X_2_u_z:[0.992149090448,0.997011348444] X_2_v_x:[0.862095615238,0.897938007956] X_2_v_y:[-0.506967842643,-0.439437524154] X_2_v_z:[-0,0.0632783545202] X_4_u_x:[0.581559187386,0.623777233261] X_4_u_y:[0.275713605773,0.364341384468] X_4_u_z:[0.693404582401,0.750916921202] X_4_v_x:[-0,0.0700482835573] X_4_v_y:[0.879911168203,0.914946611225] X_4_v_z:[-0.475168259094,-0.403574898415] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649768997e-05,5.03649768997e-05] w2_palm_p12_z_0:[-0.00146691349467,0.00146691348429] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626948,0.00146777626948] w1_p12_p13_y_1:[0.0342826886202,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.00400690915779,0.00400690915779] w2_p12_p13_y_1:[0.0342824503271,0.0343138014306] w2_p12_p13_z_1:[0.999404154234,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00400690915779,0.00400690915779] w1_p13_p14_y_2:[0.0342824503271,0.0343138014306] w1_p13_p14_z_2:[0.999404154234,0.999412148261] w2_p13_p14_x_2:[-0.0085210514598,0.0085210514598] w2_p13_p14_y_2:[0.0342814809102,0.0343138014413] w2_p13_p14_z_2:[0.999375904541,0.999412174963] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.958434522792,-0.941592283849] uni_v_palm_p22_z_3:[0.286423922716,0.336755711358] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.929171404004,0.940049599234] w2_palm_p22_y_3:[0.0975691888672,0.122717805188] w2_palm_p22_z_3:[0.322377396671,0.346274701638] cos_0_palm_p22_3:[0.941592283849,0.958434522792] cos_1_palm_p22_3:[0.929171404004,0.940049599234] w1_p22_p23_x_4:[0.929171404004,0.940049599234] w1_p22_p23_y_4:[0.0975691888672,0.122717805188] w1_p22_p23_z_4:[0.322377396671,0.346274701638] w2_p22_p23_x_4:[0.795481591372,0.808033443677] w2_p22_p23_y_4:[0.168586301526,0.201853028105] w2_p22_p23_z_4:[0.556578048995,0.571927648547] cos_p22_p23_4:[0.954200155712,0.963842489599] w1_p23_p24_x_5:[0.987431460065,0.991303991521] w1_p23_p24_y_5:[-0.0511407212471,-0.0431278552951] w1_p23_p24_z_5:[-0.148272811444,-0.12612482337] w2_p23_p24_x_5:[0.98631479408,0.991406000849] w2_p23_p24_y_5:[0.0373046035036,0.0549204616205] w2_p23_p24_z_5:[0.12546819361,0.155873108802] cos_p23_p24_5:[0.954200155712,0.963842489599] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681426e-05,5.25377681426e-05] w2_palm_p32_z_6:[-0.00147910238377,0.00147910237338] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356597,0.00148003356597] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761748] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308279664,0.00402308279664] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674279938] w2_p32_p33_z_7:[0.999362737117,0.999370823124] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308279664,0.00402308279664] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674279938] w1_p33_p34_z_8:[0.999362737117,0.999370823124] w2_p33_p34_x_8:[-0.00855584270056,0.00855584270056] w2_p33_p34_y_8:[-0.0354976954759,-0.0354664168354] w2_p33_p34_z_8:[0.999334254893,0.999370823322] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999692014287,-0.996065595612] w2_palm_p40_y_9:[-0.0886190115559,-0.0268827957266] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.725839335507,0.76734957463] uni_u_p40_p42_x_10:[-0.818897410963,-0.815926831199] uni_u_p40_p42_y_10:[-0.072592236497,-0.0220210339837] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0836656358065,-0.0250193488232] uni_v_p40_p42_y_10:[0.996456651241,0.999731813219] uni_v_p40_p42_z_10:[0.0019714418269,0.00953461120082] w1_p40_p42_x_10:[-0.0886190115559,-0.0268827957266] w1_p40_p42_y_10:[0.996065595612,0.999692014287] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.634710139905,-0.603177730425] w2_p40_p42_y_10:[-0.0594856880173,-0.0166968052758] w2_p40_p42_z_10:[0.770833519823,0.797454770847] cos_0_p40_p42_10:[0.997992488558,1] cos_1_p40_p42_10:[0.95106686987,0.964674261915] w1_p42_p43_x_11:[-0.634710139905,-0.603177730425] w1_p42_p43_y_11:[-0.0594856880173,-0.0166968052758] w1_p42_p43_z_11:[0.770833519823,0.797454770847] w2_p42_p43_x_11:[0.0873111194858,0.113896980762] w2_p42_p43_y_11:[-0.00255694641456,0] w2_p42_p43_z_11:[0.993470572188,0.996268562016] cos_p42_p43_11:[0.707106781187,0.739025610295] w1_p43_p44_x_12:[-0.64123544461,-0.620236505907] w1_p43_p44_y_12:[-0.0596116919282,-0.0177098021335] w1_p43_p44_z_12:[0.765879062573,0.782936254195] w2_p43_p44_x_12:[0.0447223915504,0.114653021646] w2_p43_p44_y_12:[-0,0.00260347428271] w2_p43_p44_z_12:[0.993407375787,0.999425574304] cos_p43_p44_12:[0.707106781187,0.739025610295] sph_w1_p24_X_2_x_13:[0.268045487714,0.301761494669] sph_w1_p24_X_2_y_13:[-0.324248857136,-0.275908234438] sph_w1_p24_X_2_z_13:[-0.923268960171,-0.89906047124] sph_w2_p24_X_2_x_13:[0.442885803469,0.503686132817] sph_w2_p24_X_2_y_13:[0.85732692488,0.892417559377] sph_w2_p24_X_2_z_13:[-0.107921418236,-0.0841550375731] cos_p24_X_2_13:[-0.0816275340822,-4.2120831886e-05] in_patch_X_2_object_u_14:[0.437499999996,0.500000000005] in_patch_X_2_object_v_14:[0.499999999995,0.562500000006] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.983051764163,-0.964442796922] sph_w1_p44_X_4_y_15:[-0.0833703701733,-0.0243600557623] sph_w1_p44_X_4_z_15:[0.184160433519,0.252661423913] sph_w2_p44_X_4_x_15:[-0.812492816684,-0.784439341041] sph_w2_p44_X_4_y_15:[0.234517709927,0.298485851186] sph_w2_p44_X_4_z_15:[0.527673983214,0.544488462414] cos_p44_X_4_15:[0.860870636077,0.900975695786] in_patch_X_4_object_u_16:[0.499999999995,0.562500000006] in_patch_X_4_object_v_16:[0.374999999996,0.437500000004] in_patch_X_4_object_l_16:[9.71993866774,9.72381781325] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.287910982545,0.355090703921] sph_w2_palm_X_P_y_17:[0.934925974741,0.957994987244] sph_w2_palm_X_P_z_17:[-0,0.0238818764875] cos_palm_X_P_17:[0.880596993589,0.91265109564] in_patch_X_P_object_u_18:[0.6786088416,0.698379692084] in_patch_X_P_object_v_18:[0.374999999996,0.437500000004] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972250585,-4.08027749416] p14_r_y:[-36.8121602032,-36.8091080359] p14_r_z:[243.172229419,243.172509987] p34_r_x:[-4.52103875971,-4.07896124029] p34_r_y:[36.6933268818,36.696267555] p34_r_z:[243.168182565,243.168466579] }
   8 (err:2.42539 min:3.57223 tm:255):{ 257  p12_u_x:[-0.00146777626948,0.00146777626948] p12_u_y:[0.0342826886095,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.00400690915779,0.00400690915779] p13_u_y:[0.0342824503271,0.0343138014306] p13_u_z:[0.999404154254,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.0085210514598,0.0085210514598] p14_u_y:[0.0342814809102,0.0343138014413] p14_u_z:[0.999375904541,0.999412174963] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.40387130146,0.422073198797] p22_u_y:[0.270099618211,0.306606378544] p22_u_z:[0.853498170021,0.865118496854] p22_v_x:[-0,0] p22_v_y:[-0.954734973493,-0.941325890133] p22_v_z:[0.297684065504,0.337567936604] p23_u_x:[0.797861117102,0.807979333776] p23_u_y:[0.175192314233,0.201566730175] p23_u_z:[0.555697452682,0.568623888722] p23_v_x:[-0,0] p23_v_y:[-0.954734973493,-0.941325890133] p23_v_z:[0.297684065504,0.337567936604] p24_u_x:[0.987471158465,0.991406000849] p24_u_y:[0.0383565726415,0.0527095695595] p24_u_z:[0.12546819361,0.148490942339] p24_v_x:[-0,0] p24_v_y:[-0.954734973493,-0.941325890133] p24_v_z:[0.297684065504,0.337567936604] p32_u_x:[-0.00148003356597,0.00148003356597] p32_u_y:[-0.0354977247751,-0.0354676761855] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308279664,0.00402308279664] p33_u_y:[-0.0354975792585,-0.0354674280045] p33_u_z:[0.999362737117,0.999370823124] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855584270056,0.00855584270056] p34_u_y:[-0.0354976954759,-0.0354664168354] p34_u_z:[0.999334254604,0.999370823213] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0886190115559,-0.0406165090219] p40_v_y:[0.996065595612,0.999305554299] p40_v_z:[-0,0] p42_u_x:[0.0993035355291,0.134484845722] p42_u_y:[-0.00275851376868,0.00318025733935] p42_u_z:[0.990761390354,0.995245416819] p42_v_x:[-0.0835002306693,-0.0377632407277] p42_v_y:[0.996464163659,0.999403696003] p42_v_z:[0.00320889468064,0.00963793589798] p43_u_x:[0.0919675808046,0.115296813828] p43_u_y:[-0.00221675464965,0] p43_u_z:[0.993329952618,0.9957988876] p43_v_x:[-0.0835002306693,-0.0377632407277] p43_v_y:[0.996464163659,0.999403696003] p43_v_z:[0.00320889468064,0.00963793589798] p44_u_x:[0.0540440468751,0.116028944536] p44_u_y:[-0,0.00226100792876] p44_u_z:[0.993305565816,0.998736051789] p44_v_x:[-0.0835002306693,-0.0377632407277] p44_v_y:[0.996464163659,0.999403696003] p44_v_z:[0.00320889468064,0.00963793589798] object_u_x:[-0.42151912426,-0.368452658671] object_u_y:[-0.929385819636,-0.905008232583] object_u_z:[0.0348519495519,0.0548329097463] object_v_x:[-0.515432020885,-0.505387473893] object_v_y:[0.163665099812,0.186089596214] object_v_z:[-0.847239404803,-0.839464538757] X_P_u_x:[-0.957769084695,-0.938760928058] X_P_u_y:[0.288206155583,0.343878403273] X_P_u_z:[-0.0616365880975,0] X_P_v_x:[-0.0643013369068,0] X_P_v_y:[-0.0211123298331,0] X_P_v_z:[0.99791376983,1] X_2_u_x:[-0,0.0555771201972] X_2_u_y:[0.0761489507471,0.124224183007] X_2_u_z:[0.992204980354,0.99662990097] X_2_v_x:[0.867840962965,0.897847523944] X_2_v_y:[-0.496475682641,-0.439549987751] X_2_v_z:[-0,0.0618988088352] X_4_u_x:[0.5840281722,0.619326973287] X_4_u_y:[0.282914984556,0.364341384468] X_4_u_z:[0.696970584737,0.748667190435] X_4_v_x:[-0,0.0594455123762] X_4_v_y:[0.882999564104,0.914946611225] X_4_v_z:[-0.469350998228,-0.403574898415] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649768997e-05,5.03649768997e-05] w2_palm_p12_z_0:[-0.00146691348429,0.00146691349467] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626948,0.00146777626948] w1_p12_p13_y_1:[0.0342826886095,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.00400690915779,0.00400690915779] w2_p12_p13_y_1:[0.0342824503271,0.0343138014306] w2_p12_p13_z_1:[0.999404154254,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00400690915779,0.00400690915779] w1_p13_p14_y_2:[0.0342824503271,0.0343138014306] w1_p13_p14_z_2:[0.999404154254,0.999412148261] w2_p13_p14_x_2:[-0.0085210514598,0.0085210514598] w2_p13_p14_y_2:[0.0342814809102,0.0343138014413] w2_p13_p14_z_2:[0.999375904541,0.999412174963] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.954734973493,-0.941325890133] uni_v_palm_p22_z_3:[0.297684065504,0.337567936604] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.931425473088,0.940049599234] w2_palm_p22_y_3:[0.101559816886,0.121128117893] w2_palm_p22_z_3:[0.322229681907,0.34051819447] cos_0_palm_p22_3:[0.941325890133,0.954734973493] cos_1_palm_p22_3:[0.931425473088,0.940049599234] w1_p22_p23_x_4:[0.931425473088,0.940049599234] w1_p22_p23_y_4:[0.101559816886,0.121128117893] w1_p22_p23_z_4:[0.322229681907,0.34051819447] w2_p22_p23_x_4:[0.797861117102,0.807979333776] w2_p22_p23_y_4:[0.175192314233,0.201566730175] w2_p22_p23_z_4:[0.555697452682,0.568623888722] cos_p22_p23_4:[0.955291469459,0.962933484179] w1_p23_p24_x_5:[0.98744745384,0.990713900601] w1_p23_p24_y_5:[-0.051843715754,-0.0448550048309] w1_p23_p24_z_5:[-0.147711364893,-0.129821576917] w2_p23_p24_x_5:[0.987471158465,0.991406000849] w2_p23_p24_y_5:[0.0383565726415,0.0527095695595] w2_p23_p24_z_5:[0.12546819361,0.148490942339] cos_p23_p24_5:[0.955291469459,0.962933484179] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681426e-05,5.25377681426e-05] w2_palm_p32_z_6:[-0.00147910238377,0.00147910238377] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356597,0.00148003356597] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761855] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308279664,0.00402308279664] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674280045] w2_p32_p33_z_7:[0.999362737117,0.999370823124] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308279664,0.00402308279664] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674280045] w1_p33_p34_z_8:[0.999362737117,0.999370823124] w2_p33_p34_x_8:[-0.00855584270056,0.00855584270056] w2_p33_p34_y_8:[-0.0354976954759,-0.0354664168354] w2_p33_p34_z_8:[0.999334254604,0.999370823213] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999305554299,-0.996065595612] w2_palm_p40_y_9:[-0.0886190115559,-0.0406165090219] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.735167639688,0.76734957463] uni_u_p40_p42_x_10:[-0.818580842381,-0.815926831199] uni_u_p40_p42_y_10:[-0.072592236497,-0.0332710010732] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0835002306693,-0.0377632407277] uni_v_p40_p42_y_10:[0.996464163659,0.999403696003] uni_v_p40_p42_z_10:[0.00320889468064,0.00963793589798] w1_p40_p42_x_10:[-0.0886190115559,-0.0406165090219] w1_p40_p42_y_10:[0.996065595612,0.999305554299] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.631393728974,-0.604635161002] w2_p40_p42_y_10:[-0.0593988040559,-0.0260587512161] w2_p40_p42_z_10:[0.773734436588,0.795925504303] cos_0_p40_p42_10:[0.997991664442,1] cos_1_p40_p42_10:[0.951152821797,0.963623558397] w1_p42_p43_x_11:[-0.631393728974,-0.604635161002] w1_p42_p43_y_11:[-0.0593988040559,-0.0260587512161] w1_p42_p43_z_11:[0.773734436588,0.795925504303] w2_p42_p43_x_11:[0.0919675808046,0.115296813828] w2_p42_p43_y_11:[-0.00221675464965,0] w2_p42_p43_z_11:[0.993329952618,0.9957988876] cos_p42_p43_11:[0.707106781187,0.735166107088] w1_p43_p44_x_12:[-0.637536612185,-0.618677367647] w1_p43_p44_y_12:[-0.0595146327471,-0.0267733464834] w1_p43_p44_z_12:[0.768833899692,0.783769915085] w2_p43_p44_x_12:[0.0540440468751,0.116028944536] w2_p43_p44_y_12:[-0,0.00226100792876] w2_p43_p44_z_12:[0.993305565816,0.998736051789] cos_p43_p44_12:[0.707106781187,0.735166107088] sph_w1_p24_X_2_x_13:[0.268274746165,0.294298702031] sph_w1_p24_X_2_y_13:[-0.325023431408,-0.28679599084] sph_w1_p24_X_2_z_13:[-0.919646932423,-0.90077133467] sph_w2_p24_X_2_x_13:[0.443045154037,0.493262006866] sph_w2_p24_X_2_y_13:[0.863061866792,0.892345279731] sph_w2_p24_X_2_z_13:[-0.107816787748,-0.0879281527888] cos_p24_X_2_13:[-0.0809369375091,-0.0145225696368] in_patch_X_2_object_u_14:[0.437499999996,0.500000000005] in_patch_X_2_object_v_14:[0.499999999995,0.562500000006] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.980614413834,-0.964017590453] sph_w1_p44_X_4_y_15:[-0.0832330248216,-0.0370850379937] sph_w1_p44_X_4_z_15:[0.193236781526,0.253973457646] sph_w2_p44_X_4_x_15:[-0.8106940325,-0.787992940856] sph_w2_p44_X_4_y_15:[0.235012554151,0.289003877115] sph_w2_p44_X_4_z_15:[0.530628847465,0.543960100658] cos_p44_X_4_15:[0.864426197628,0.899528065054] in_patch_X_4_object_u_16:[0.562499999994,0.625000000006] in_patch_X_4_object_v_16:[0.374999999996,0.437500000004] in_patch_X_4_object_l_16:[9.71993866774,9.72381781325] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.288279237608,0.343779456736] sph_w2_palm_X_P_y_17:[0.938833494633,0.957993478047] sph_w2_palm_X_P_z_17:[-0,0.0199453249414] cos_palm_X_P_17:[0.88077804072,0.907372744288] in_patch_X_P_object_u_18:[0.683029849958,0.698415946098] in_patch_X_P_object_v_18:[0.374999999996,0.437500000004] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972250585,-4.08027749416] p14_r_y:[-36.812159099,-36.8091080359] p14_r_z:[243.172229419,243.172509987] p34_r_x:[-4.52103875971,-4.07896124029] p34_r_y:[36.6933268818,36.6962683538] p34_r_z:[243.168182564,243.168466579] }
   9 (err:2.19815 min:3.53262 tm:255):{ 257  p12_u_x:[-0.00146777626978,0.00146777626978] p12_u_y:[0.0342826886202,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.00400688324722,0.00400688324722] p13_u_y:[0.0342824503414,0.0343137970322] p13_u_z:[0.999404153989,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.00852076085953,0.00852076085953] p14_u_y:[0.0342814810058,0.0343137970325] p14_u_z:[0.999375905472,0.999412175288] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.396917238579,0.422073198797] p22_u_y:[0.258085875694,0.307263782732] p22_u_z:[0.853728399797,0.869114271554] p22_v_x:[-0,0] p22_v_y:[-0.959038097339,-0.94140825659] p22_v_z:[0.284508181812,0.337272254067] p23_u_x:[0.793287181815,0.806615057407] p23_u_y:[0.168008779347,0.203043986948] p23_u_z:[0.558441085579,0.574606203914] p23_v_x:[-0,0] p23_v_y:[-0.959038097339,-0.94140825659] p23_v_z:[0.284508181812,0.337272254067] p24_u_x:[0.985119822166,0.990687613507] p24_u_y:[0.0385619816015,0.0573108514777] p24_u_z:[0.130663296217,0.162496370431] p24_v_x:[-0,0] p24_v_y:[-0.959038097339,-0.94140825659] p24_v_z:[0.284508181812,0.337272254067] p32_u_x:[-0.00148003356597,0.00148003356597] p32_u_y:[-0.0354977247751,-0.0354676761748] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308238357,0.00402308238357] p33_u_y:[-0.0354975792585,-0.0354674280045] p33_u_z:[0.999362736601,0.999370824282] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855592462671,0.00855592462671] p34_u_y:[-0.0354976869741,-0.0354664168212] p34_u_z:[0.999334253271,0.999370823611] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0884414207632,-0.0237020605412] p40_v_y:[0.996081379739,0.999767242572] p40_v_z:[-0,0] p42_u_x:[0.0945220244759,0.142659192817] p42_u_y:[-0.00383396990283,0.00380846392426] p42_u_z:[0.989642746708,0.99557523511] p42_v_x:[-0.0836301966451,-0.0220644608746] p42_v_y:[0.996459693611,0.999797412591] p42_v_z:[0.00165931242258,0.00960055608777] p43_u_x:[0.0854216383532,0.114599808675] p43_u_y:[-0.00302720042866,0] p43_u_z:[0.99338712344,0.996444991324] p43_v_x:[-0.0836301966451,-0.0220644608746] p43_v_y:[0.996459693611,0.999797412591] p43_v_z:[0.00165931242258,0.00960055608777] p44_u_x:[0.032587002256,0.115562704634] p44_u_y:[-0,0.00308919890632] p44_u_z:[0.993305197739,0.999779436572] p44_v_x:[-0.0836301966451,-0.0220644608746] p44_v_y:[0.996459693611,0.999797412591] p44_v_z:[0.00165931242258,0.00960055608777] object_u_x:[-0.434421019088,-0.366572935532] object_u_y:[-0.93006610915,-0.899194341395] object_u_z:[0.0299193056331,0.05521548299] object_v_x:[-0.51790201725,-0.504711171942] object_v_y:[0.164333196184,0.194548385634] object_v_z:[-0.847548276317,-0.837031813454] X_P_u_x:[-0.95821883724,-0.934050545011] X_P_u_y:[0.286340114958,0.357456585813] X_P_u_z:[-0.0643039717136,0] X_P_v_x:[-0.0670000519547,0] X_P_v_y:[-0.0264472546156,0] X_P_v_z:[0.997670351598,1] X_2_u_x:[-0,0.0574545306149] X_2_u_y:[0.0720090360295,0.125853062329] X_2_u_z:[0.992036069833,0.997096451356] X_2_v_x:[0.861080550055,0.898873650512] X_2_v_y:[-0.508733488792,-0.437663165656] X_2_v_z:[-0,0.063956112132] X_4_u_x:[0.582969133186,0.62758557892] X_4_u_y:[0.267673992689,0.361924298612] X_4_u_z:[0.691480967917,0.752276295535] X_4_v_x:[-0,0.0746340403038] X_4_v_y:[0.880222429668,0.91712861958] X_4_v_z:[-0.474588588559,-0.398591388732] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649769101e-05,5.03649769101e-05] w2_palm_p12_z_0:[-0.00146691349497,0.0014669134846] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626978,0.00146777626978] w1_p12_p13_y_1:[0.0342826886202,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.00400688324722,0.00400688324722] w2_p12_p13_y_1:[0.0342824503414,0.0343137970322] w2_p12_p13_z_1:[0.999404153989,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00400688324722,0.00400688324722] w1_p13_p14_y_2:[0.0342824503414,0.0343137970322] w1_p13_p14_z_2:[0.999404153989,0.999412148261] w2_p13_p14_x_2:[-0.00852076085953,0.00852076085953] w2_p13_p14_y_2:[0.0342814810058,0.0343137970325] w2_p13_p14_z_2:[0.999375905472,0.999412175288] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.959038097339,-0.94140825659] uni_v_palm_p22_z_3:[0.284508181812,0.337272254067] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.928620432524,0.940104464083] w2_palm_p22_y_3:[0.096859128373,0.123224564674] w2_palm_p22_z_3:[0.322292008039,0.347323340259] cos_0_palm_p22_3:[0.94140825659,0.959038097339] cos_1_palm_p22_3:[0.928620432524,0.940104464083] w1_p22_p23_x_4:[0.928620432524,0.940104464083] w1_p22_p23_y_4:[0.096859128373,0.123224564674] w1_p22_p23_z_4:[0.322292008039,0.347323340259] w2_p22_p23_x_4:[0.793287181815,0.806615057407] w2_p22_p23_y_4:[0.168008779347,0.203043986948] w2_p22_p23_z_4:[0.558441085579,0.574606203914] cos_p22_p23_4:[0.953047966631,0.963304711501] w1_p23_p24_x_5:[0.987741595866,0.991819081376] w1_p23_p24_y_5:[-0.050364204153,-0.0420230595127] w1_p23_p24_z_5:[-0.146077179951,-0.12271171022] w2_p23_p24_x_5:[0.985119822166,0.990687613507] w2_p23_p24_y_5:[0.0385619816015,0.0573108514777] w2_p23_p24_z_5:[0.130663296217,0.162496370431] cos_p23_p24_5:[0.953047966631,0.963304711501] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681426e-05,5.25377681426e-05] w2_palm_p32_z_6:[-0.00147910238377,0.00147910237338] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356597,0.00148003356597] w1_p32_p33_y_7:[-0.0354977247751,-0.0354676761748] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308238357,0.00402308238357] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674280045] w2_p32_p33_z_7:[0.999362736601,0.999370824282] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308238357,0.00402308238357] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674280045] w1_p33_p34_z_8:[0.999362736601,0.999370824282] w2_p33_p34_x_8:[-0.00855592462671,0.00855592462671] w2_p33_p34_y_8:[-0.0354976869741,-0.0354664168212] w2_p33_p34_z_8:[0.999334253271,0.999370823611] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999767242572,-0.996081379739] w2_palm_p40_y_9:[-0.0884414207632,-0.0237020605412] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.723643706069,0.767270652158] uni_u_p40_p42_x_10:[-0.81895903419,-0.815939760763] uni_u_p40_p42_y_10:[-0.0724467630528,-0.0194155357192] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0836301966451,-0.0220644608746] uni_v_p40_p42_y_10:[0.996459693611,0.999797412591] uni_v_p40_p42_z_10:[0.00165931242258,0.00960055608777] w1_p40_p42_x_10:[-0.0884414207632,-0.0237020605412] w1_p40_p42_y_10:[0.996081379739,0.999767242572] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.635040773726,-0.598454657004] w2_p40_p42_y_10:[-0.0594439917805,-0.014701796541] w2_p40_p42_z_10:[0.770597090335,0.801059859158] cos_0_p40_p42_10:[0.997799055507,1] cos_1_p40_p42_10:[0.949256735504,0.964842981219] w1_p42_p43_x_11:[-0.635040773726,-0.598454657004] w1_p42_p43_y_11:[-0.0594439917805,-0.014701796541] w1_p42_p43_z_11:[0.770597090335,0.801059859158] w2_p42_p43_x_11:[0.0854216383532,0.114599808675] w2_p42_p43_y_11:[-0.00302720042866,0] w2_p42_p43_z_11:[0.99338712344,0.996444991324] cos_p42_p43_11:[0.707106781187,0.745133403103] w1_p43_p44_x_12:[-0.643771948792,-0.619784693783] w1_p43_p44_y_12:[-0.0596150733534,-0.0155993090056] w1_p43_p44_z_12:[0.764651140214,0.783397726475] w2_p43_p44_x_12:[0.032587002256,0.115562704634] w2_p43_p44_y_12:[-0,0.00308919890632] w2_p43_p44_z_12:[0.993305197739,0.999779436572] cos_p43_p44_12:[0.707106781187,0.745133403103] sph_w1_p24_X_2_x_13:[0.273190114025,0.308566540504] sph_w1_p24_X_2_y_13:[-0.324237736792,-0.273647179254] sph_w1_p24_X_2_z_13:[-0.922451794667,-0.896922404017] sph_w2_p24_X_2_x_13:[0.441148930552,0.50539573654] sph_w2_p24_X_2_y_13:[0.856267174618,0.893319592107] sph_w2_p24_X_2_z_13:[-0.108569033405,-0.0834285273383] cos_p24_X_2_13:[-0.0802061432032,0.00594796313159] in_patch_X_2_object_u_14:[0.437499999996,0.500000000005] in_patch_X_2_object_v_14:[0.374999999996,0.437500000004] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.985166305015,-0.964276786274] sph_w1_p44_X_4_y_15:[-0.0833455579055,-0.0213379522652] sph_w1_p44_X_4_z_15:[0.172197464328,0.253608444541] sph_w2_p44_X_4_x_15:[-0.811321999455,-0.781776003259] sph_w2_p44_X_4_y_15:[0.232174432968,0.299702117302] sph_w2_p44_X_4_z_15:[0.530136253278,0.547756472104] cos_p44_X_4_15:[0.854545757366,0.901415045155] in_patch_X_4_object_u_16:[0.499999999995,0.562500000006] in_patch_X_4_object_v_16:[0.374999999996,0.437500000004] in_patch_X_4_object_l_16:[9.71993866774,9.72381781325] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.286424619416,0.357358685996] sph_w2_palm_X_P_y_17:[0.934078017348,0.958461905931] sph_w2_palm_X_P_z_17:[-0,0.0252708891412] cos_palm_X_P_17:[0.879842916458,0.913706030931] in_patch_X_P_object_u_18:[0.677047439165,0.697813128372] in_patch_X_P_object_v_18:[0.624999999994,0.687500000007] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972172855,-4.08027827145] p14_r_y:[-36.8121600359,-36.8091081689] p14_r_z:[243.17222941,243.172509987] p34_r_x:[-4.52103874732,-4.07896125268] p34_r_y:[36.6933268818,36.6962687162] p34_r_z:[243.16818251,243.168466613] }
  10 (err:2.19487 min:3.53015 tm:255):{ 257  p12_u_x:[-0.00146777626948,0.00146777626948] p12_u_y:[0.0342826886202,0.0343138336247] p12_u_z:[0.999411098202,0.99941217604] p12_v_x:[-0,0] p12_v_y:[-0.999412174763,-0.999411108353] p12_v_z:[0.0342827255546,0.0343137969645] p13_u_x:[-0.00400685897546,0.00400685897546] p13_u_y:[0.0342824503447,0.034313797027] p13_u_z:[0.999404153609,0.999412148261] p13_v_x:[-0,0] p13_v_y:[-0.999412174763,-0.999411108353] p13_v_z:[0.0342827255546,0.0343137969645] p14_u_x:[-0.00852079885671,0.00852079885671] p14_u_y:[0.0342814809947,0.0343137970274] p14_u_z:[0.999375905829,0.999412175613] p14_v_x:[-0,0] p14_v_y:[-0.999412174763,-0.999411108353] p14_v_z:[0.0342827255546,0.0343137969645] p22_u_x:[0.397738056699,0.422073198797] p22_u_y:[0.258208731659,0.306161618302] p22_u_z:[0.854075430271,0.869016299705] p22_v_x:[-0,0] p22_v_y:[-0.958961161195,-0.941829543328] p22_v_z:[0.284660799905,0.33615428962] p23_u_x:[0.79366261642,0.80650826401] p23_u_y:[0.168092250732,0.202258813728] p23_u_z:[0.558718638877,0.574322965703] p23_v_x:[-0,0] p23_v_y:[-0.958961161195,-0.941829543328] p23_v_z:[0.284660799905,0.33615428962] p24_u_x:[0.985306878847,0.990686672054] p24_u_y:[0.0385482839578,0.0567594099116] p24_u_z:[0.130663296217,0.161475609186] p24_v_x:[-0,0] p24_v_y:[-0.958961161195,-0.941829543328] p24_v_z:[0.284660799905,0.33615428962] p32_u_x:[-0.00148003356597,0.00148003356597] p32_u_y:[-0.0354977247644,-0.0354676761748] p32_u_z:[0.999369728242,0.999370824202] p32_v_x:[-0,0] p32_v_y:[-0.999370822813,-0.99936975859] p32_v_z:[-0.0354976869114,-0.0354677150367] p33_u_x:[-0.00402308225865,0.00402308225865] p33_u_y:[-0.0354975792585,-0.0354674280045] p33_u_z:[0.999362736615,0.999370823304] p33_v_x:[-0,0] p33_v_y:[-0.999370822813,-0.99936975859] p33_v_z:[-0.0354976869114,-0.0354677150367] p34_u_x:[-0.00855576126514,0.00855576126514] p34_u_y:[-0.0354976996966,-0.0354664168601] p34_u_z:[0.99933425389,0.999370823033] p34_v_x:[-0,0] p34_v_y:[-0.999370822813,-0.99936975859] p34_v_z:[-0.0354976869114,-0.0354677150367] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0884414207632,-0.0252125211949] p40_v_y:[0.996081379739,0.999739449228] p40_v_z:[-0,0] p42_u_x:[0.0954097307759,0.140802407184] p42_u_y:[-0.00363544499177,0.00355261206256] p42_u_z:[0.98991470583,0.99551517169] p42_v_x:[-0.0835404153244,-0.0234252175642] p42_v_y:[0.996466577272,0.999772948973] p42_v_z:[0.00178367308836,0.00958660495603] p43_u_x:[0.0870964246871,0.114894620685] p43_u_y:[-0.0028113045023,0] p43_u_z:[0.9933749315,0.996278945585] p43_v_x:[-0.0835404153244,-0.0234252175642] p43_v_y:[0.996466577272,0.999772948973] p43_v_z:[0.00178367308836,0.00958660495603] p44_u_x:[0.0382503104969,0.115730059603] p44_u_y:[-0,0.00286663398367] p44_u_z:[0.993319463671,0.999694218614] p44_v_x:[-0.0835404153244,-0.0234252175642] p44_v_y:[0.996466577272,0.999772948973] p44_v_z:[0.00178367308836,0.00958660495603] object_u_x:[-0.434223088487,-0.367142203693] object_u_y:[-0.929829373085,-0.899298327077] object_u_z:[0.0301003651611,0.0552124098828] object_v_x:[-0.517789088429,-0.50495631435] object_v_y:[0.164983579501,0.194472630549] object_v_z:[-0.847275187305,-0.837045842122] X_P_u_x:[-0.958032953209,-0.9341313275] X_P_u_y:[0.286957053863,0.357253736472] X_P_u_z:[-0.0642927778408,0] X_P_v_x:[-0.0670000519547,0] X_P_v_y:[-0.026271692302,0] X_P_v_z:[0.997673867319,1] X_2_u_x:[-0,0.0574248764337] X_2_u_y:[0.0721772361119,0.125846391743] X_2_u_z:[0.992032609475,0.997083158824] X_2_v_x:[0.861206342506,0.898611911593] X_2_v_y:[-0.508537654234,-0.438185003377] X_2_v_z:[-0,0.0639398173869] X_4_u_x:[0.583585425815,0.627479029463] X_4_u_y:[0.267792173705,0.361924298612] X_4_u_z:[0.691545785929,0.751979511274] X_4_v_x:[-0,0.0743675533897] X_4_v_y:[0.880313491515,0.91712861958] X_4_v_z:[-0.47444673781,-0.398591388732] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412174763,-0.999411108353] uni_v_palm_p12_z_0:[0.0342827255546,0.0343137969645] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.03649768997e-05,5.03649768997e-05] w2_palm_p12_z_0:[-0.00146691348429,0.00146691349467] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00146777626948,0.00146777626948] w1_p12_p13_y_1:[0.0342826886202,0.0343138336247] w1_p12_p13_z_1:[0.999411098202,0.99941217604] w2_p12_p13_x_1:[-0.00400685897546,0.00400685897546] w2_p12_p13_y_1:[0.0342824503447,0.034313797027] w2_p12_p13_z_1:[0.999404153609,0.999412148261] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00400685897546,0.00400685897546] w1_p13_p14_y_2:[0.0342824503447,0.034313797027] w1_p13_p14_z_2:[0.999404153609,0.999412148261] w2_p13_p14_x_2:[-0.00852079885671,0.00852079885671] w2_p13_p14_y_2:[0.0342814809947,0.0343137970274] w2_p13_p14_z_2:[0.999375905829,0.999412175613] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.958961161195,-0.941829543328] uni_v_palm_p22_z_3:[0.284660799905,0.33615428962] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.928999914848,0.94007335232] w2_palm_p22_y_3:[0.0969418734844,0.122560034546] w2_palm_p22_z_3:[0.32243450696,0.346657196053] cos_0_palm_p22_3:[0.941829543328,0.958961161195] cos_1_palm_p22_3:[0.928999914848,0.94007335232] w1_p22_p23_x_4:[0.928999914848,0.94007335232] w1_p22_p23_y_4:[0.0969418734844,0.122560034546] w1_p22_p23_z_4:[0.32243450696,0.346657196053] w2_p22_p23_x_4:[0.79366261642,0.80650826401] w2_p22_p23_y_4:[0.168092250732,0.202258813728] w2_p22_p23_z_4:[0.558718638877,0.574322965703] cos_p22_p23_4:[0.953266519102,0.963156863716] w1_p23_p24_x_5:[0.987806323753,0.991709002749] w1_p23_p24_y_5:[-0.050178196032,-0.0421248832449] w1_p23_p24_z_5:[-0.145913457761,-0.123365305098] w2_p23_p24_x_5:[0.985306878847,0.990686672054] w2_p23_p24_y_5:[0.0385482839578,0.0567594099116] w2_p23_p24_z_5:[0.130663296217,0.161475609186] cos_p23_p24_5:[0.953266519102,0.963156863716] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999370822813,-0.99936975859] uni_v_palm_p32_z_6:[-0.0354976869114,-0.0354677150367] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[1,1] w2_palm_p32_y_6:[-5.25377681426e-05,5.25377681426e-05] w2_palm_p32_z_6:[-0.00147910238377,0.00147910237338] cos_0_palm_p32_6:[1,1] cos_1_palm_p32_6:[1,1] w1_p32_p33_x_7:[-0.00148003356597,0.00148003356597] w1_p32_p33_y_7:[-0.0354977247644,-0.0354676761748] w1_p32_p33_z_7:[0.999369728242,0.999370824202] w2_p32_p33_x_7:[-0.00402308225865,0.00402308225865] w2_p32_p33_y_7:[-0.0354975792585,-0.0354674280045] w2_p32_p33_z_7:[0.999362736615,0.999370823304] cos_p32_p33_7:[1,1] w1_p33_p34_x_8:[-0.00402308225865,0.00402308225865] w1_p33_p34_y_8:[-0.0354975792585,-0.0354674280045] w1_p33_p34_z_8:[0.999362736615,0.999370823304] w2_p33_p34_x_8:[-0.00855576126514,0.00855576126514] w2_p33_p34_y_8:[-0.0354976996966,-0.0354664168601] w2_p33_p34_z_8:[0.99933425389,0.999370823033] cos_p33_p34_8:[1,1] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.999739449228,-0.996081379739] w2_palm_p40_y_9:[-0.0884414207632,-0.0252125211949] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.724688615733,0.767255952559] uni_u_p40_p42_x_10:[-0.81893626728,-0.815939760763] uni_u_p40_p42_y_10:[-0.0724467630528,-0.0206528291066] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0835404153244,-0.0234252175642] uni_v_p40_p42_y_10:[0.996466577272,0.999772948973] uni_v_p40_p42_z_10:[0.00178367308836,0.00958660495603] w1_p40_p42_x_10:[-0.0884414207632,-0.0252125211949] w1_p40_p42_y_10:[0.996081379739,0.999739449228] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.634360146525,-0.60006146017] w2_p40_p42_y_10:[-0.0593869716646,-0.0158442225568] w2_p40_p42_z_10:[0.771179631404,0.799897242576] cos_0_p40_p42_10:[0.997880194816,1] cos_1_p40_p42_10:[0.949900422815,0.96460301295] w1_p42_p43_x_11:[-0.634360146525,-0.60006146017] w1_p42_p43_y_11:[-0.0593869716646,-0.0158442225568] w1_p42_p43_z_11:[0.771179631404,0.799897242576] w2_p42_p43_x_11:[0.0870964246871,0.114894620685] w2_p42_p43_y_11:[-0.0028113045023,0] w2_p42_p43_z_11:[0.9933749315,0.996278945585] cos_p42_p43_11:[0.707106781187,0.742694854923] w1_p43_p44_x_12:[-0.642176684114,-0.619507816793] w1_p43_p44_y_12:[-0.0595383416433,-0.0165785327166] w1_p43_p44_z_12:[0.765728227708,0.783579746954] w2_p43_p44_x_12:[0.0382503104969,0.115730059603] w2_p43_p44_y_12:[-0,0.00286663398367] w2_p43_p44_z_12:[0.993319463671,0.999694218614] cos_p43_p44_12:[0.707106781187,0.742694854923] sph_w1_p24_X_2_x_13:[0.273208500779,0.307458343511] sph_w1_p24_X_2_y_13:[-0.323161846201,-0.273793130787] sph_w1_p24_X_2_z_13:[-0.922375717203,-0.897609573906] sph_w2_p24_X_2_x_13:[0.441667349306,0.505200351714] sph_w2_p24_X_2_y_13:[0.856392108868,0.893061388128] sph_w2_p24_X_2_z_13:[-0.108562990819,-0.0835993057428] cos_p24_X_2_13:[-0.0790037339636,0.00567092287271] in_patch_X_2_object_u_14:[0.437499999996,0.500000000005] in_patch_X_2_object_v_14:[0.374999999996,0.437500000004] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p44_X_4_x_15:[-0.98426476743,-0.964243357501] sph_w1_p44_X_4_y_15:[-0.0832576483588,-0.0227359401402] sph_w1_p44_X_4_z_15:[0.177792193975,0.253750696735] sph_w2_p44_X_4_x_15:[-0.810866134016,-0.781841974622] sph_w2_p44_X_4_y_15:[0.232426931265,0.299514043563] sph_w2_p44_X_4_z_15:[0.530583198873,0.547725876453] cos_p44_X_4_15:[0.856672980878,0.900929480458] in_patch_X_4_object_u_16:[0.499999999995,0.562500000006] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] sph_w1_palm_X_P_x_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_17:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_17:[-0,0] sph_w2_palm_X_P_x_17:[0.287040841626,0.357156264823] sph_w2_palm_X_P_y_17:[0.934160104483,0.958254974275] sph_w2_palm_X_P_z_17:[-0,0.0250811726631] cos_palm_X_P_17:[0.880147356807,0.913599793205] in_patch_X_P_object_u_18:[0.677119493455,0.697329758134] in_patch_X_P_object_v_18:[0.624999999994,0.687500000007] in_patch_X_P_object_l_18:[172.585556066,172.585556066] p14_r_x:[-4.51972100038,-4.08027899963] p14_r_y:[-36.8121602015,-36.8091081691] p14_r_z:[243.172229351,243.172509987] p34_r_x:[-4.52103874358,-4.07896125643] p34_r_y:[36.6933268818,36.6962683538] p34_r_z:[243.168182564,243.168466584] }


Cuik executed in 31 (31) child processors
STATITISTICS FOR Cuik:

Volume of the search space: 5.42237e+18
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 0.358859
Number of processors: 32
User time in process: 255.000000 seg (4.250000 min)
Box level information:
  N processed boxes :   3211
  Max depth         :     56
  Types of boxes:
    N solution boxes:     10 (0) ( 0.31%)
    N empty boxes   :   1032  (32.14%)
    N bisected boxes:   2169  (67.55%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :   3847
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

