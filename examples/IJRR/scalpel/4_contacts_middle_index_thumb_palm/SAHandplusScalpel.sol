
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
Equations from file: /home/porta/cuik/CuikSuite/examples/IJRR/scalpel/4_contacts_middle_index_thumb_palm/SAHandplusScalpel_kin.cuik
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
   cos_p24_X_2_13 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_2_object_u_14 : [0,1]
   in_patch_X_2_object_v_14 : [0,1]

[DUMMY VARS]
   in_patch_X_2_object_w_14 : [0,1]

[SECONDARY VARS]
   in_patch_X_2_object_l_14 : [9.55155098744,9.55155098744]
   sph_w1_p34_X_3_x_15 : [-1,1]
   sph_w1_p34_X_3_y_15 : [-1,1]
   sph_w1_p34_X_3_z_15 : [-1,1]
   sph_w2_p34_X_3_x_15 : [-1,1]
   sph_w2_p34_X_3_y_15 : [-1,1]
   sph_w2_p34_X_3_z_15 : [-1,1]
   cos_p34_X_3_15 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_16 : [0,1]
   in_patch_X_3_object_v_16 : [0,1]

[DUMMY VARS]
   in_patch_X_3_object_w_16 : [0,1]

[SECONDARY VARS]
   in_patch_X_3_object_l_16 : [9.84343798184,9.84343798184]
   sph_w1_p44_X_4_x_17 : [-1,1]
   sph_w1_p44_X_4_y_17 : [-1,1]
   sph_w1_p44_X_4_z_17 : [-1,1]
   sph_w2_p44_X_4_x_17 : [-1,1]
   sph_w2_p44_X_4_y_17 : [-1,1]
   sph_w2_p44_X_4_z_17 : [-1,1]
   cos_p44_X_4_17 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_4_object_u_18 : [0,1]
   in_patch_X_4_object_v_18 : [0,1]

[DUMMY VARS]
   in_patch_X_4_object_w_18 : [0,1]

[SECONDARY VARS]
   in_patch_X_4_object_l_18 : [9.68483120378,9.74728773384]
   sph_w1_palm_X_P_x_19 : [-1,1]
   sph_w1_palm_X_P_y_19 : [-1,1]
   sph_w1_palm_X_P_z_19 : [-1,1]
   sph_w2_palm_X_P_x_19 : [-1,1]
   sph_w2_palm_X_P_y_19 : [-1,1]
   sph_w2_palm_X_P_z_19 : [-1,1]
   cos_palm_X_P_19 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_P_object_u_20 : [0,1]
   in_patch_X_P_object_v_20 : [0,1]

[DUMMY VARS]
   in_patch_X_P_object_w_20 : [0,1]

[SECONDARY VARS]
   in_patch_X_P_object_l_20 : [172.585556066,172.585556066]

[CARTESIAN VARS]
   p14_r_x : [-1710.17469171,1710.17469171]
   p14_r_y : [-1710.17469171,1710.17469171]
   p14_r_z : [-1710.17469171,1710.17469171]

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
   X_3_u_x^2+X_3_u_y^2+X_3_u_z^2 = 1;
   X_3_v_x^2+X_3_v_y^2+X_3_v_z^2 = 1;
   X_3_u_x*X_3_v_x+X_3_u_y*X_3_v_y+X_3_u_z*X_3_v_z = 0;
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
   0.140021004726*p34_u_x+0.990148533421*p34_w_x-0.990148533421*p34_wp_x-sph_w1_p34_X_3_x_15 = -0;
   0.140021004726*p34_u_y+0.990148533421*p34_w_y-0.990148533421*p34_wp_y-sph_w1_p34_X_3_y_15 = -0;
   0.140021004726*p34_u_z+0.990148533421*p34_w_z-0.990148533421*p34_wp_z-sph_w1_p34_X_3_z_15 = -0;
   X_3_w_x-X_3_wp_x-sph_w2_p34_X_3_x_15 = -0;
   X_3_w_y-X_3_wp_y-sph_w2_p34_X_3_y_15 = -0;
   X_3_w_z-X_3_wp_z-sph_w2_p34_X_3_z_15 = -0;
   sph_w1_p34_X_3_x_15*sph_w2_p34_X_3_x_15+sph_w1_p34_X_3_y_15*sph_w2_p34_X_3_y_15+sph_w1_p34_X_3_z_15*sph_w2_p34_X_3_z_15-cos_p34_X_3_15 = 0;
   in_patch_X_3_object_l_16^2 = 96.8932713024;
   X_3_w_x*in_patch_X_3_object_l_16-X_3_wp_x*in_patch_X_3_object_l_16-2.92632*object_u_x-9.3984*object_w_x+9.3984*object_wp_x = 0;
   X_3_w_y*in_patch_X_3_object_l_16-X_3_wp_y*in_patch_X_3_object_l_16-2.92632*object_u_y-9.3984*object_w_y+9.3984*object_wp_y = 0;
   X_3_w_z*in_patch_X_3_object_l_16-X_3_wp_z*in_patch_X_3_object_l_16-2.92632*object_u_z-9.3984*object_w_z+9.3984*object_wp_z = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_17 = -0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_17 = -0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_17 = -0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_17 = -0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_17 = -0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_17 = -0;
   sph_w1_p44_X_4_x_17*sph_w2_p44_X_4_x_17+sph_w1_p44_X_4_y_17*sph_w2_p44_X_4_y_17+sph_w1_p44_X_4_z_17*sph_w2_p44_X_4_z_17-cos_p44_X_4_17 = 0;
   0.003851459072*in_patch_X_4_object_v_18^2-in_patch_X_4_object_l_18^2-1.20981126144*in_patch_X_4_object_v_18 = -95.0057667072;
   0.006256*object_u_x*in_patch_X_4_object_v_18-0.061744*object_w_x*in_patch_X_4_object_v_18+0.061744*object_wp_x*in_patch_X_4_object_v_18+X_4_w_x*in_patch_X_4_object_l_18-X_4_wp_x*in_patch_X_4_object_l_18-0.98256*object_u_x+9.69744*object_w_x-9.69744*object_wp_x = 0;
   0.006256*object_u_y*in_patch_X_4_object_v_18-0.061744*object_w_y*in_patch_X_4_object_v_18+0.061744*object_wp_y*in_patch_X_4_object_v_18+X_4_w_y*in_patch_X_4_object_l_18-X_4_wp_y*in_patch_X_4_object_l_18-0.98256*object_u_y+9.69744*object_w_y-9.69744*object_wp_y = 0;
   0.006256*object_u_z*in_patch_X_4_object_v_18-0.061744*object_w_z*in_patch_X_4_object_v_18+0.061744*object_wp_z*in_patch_X_4_object_v_18+X_4_w_z*in_patch_X_4_object_l_18-X_4_wp_z*in_patch_X_4_object_l_18-0.98256*object_u_z+9.69744*object_w_z-9.69744*object_wp_z = 0;
   sph_w1_palm_X_P_x_19 = 0.707106781187;
   sph_w1_palm_X_P_y_19 = 0.707106781187;
   sph_w1_palm_X_P_z_19 = 0;
   X_P_w_x-X_P_wp_x-sph_w2_palm_X_P_x_19 = -0;
   X_P_w_y-X_P_wp_y-sph_w2_palm_X_P_y_19 = -0;
   X_P_w_z-X_P_wp_z-sph_w2_palm_X_P_z_19 = -0;
   sph_w1_palm_X_P_x_19*sph_w2_palm_X_P_x_19+sph_w1_palm_X_P_y_19*sph_w2_palm_X_P_y_19+sph_w1_palm_X_P_z_19*sph_w2_palm_X_P_z_19-cos_palm_X_P_19 = 0;
   in_patch_X_P_object_l_20^2 = 29785.7741625;
   X_P_w_x*in_patch_X_P_object_l_20-X_P_wp_x*in_patch_X_P_object_l_20+171.706432*object_u_x+17.397568*object_w_x-17.397568*object_wp_x = 0;
   X_P_w_y*in_patch_X_P_object_l_20-X_P_wp_y*in_patch_X_P_object_l_20+171.706432*object_u_y+17.397568*object_w_y-17.397568*object_wp_y = 0;
   X_P_w_z*in_patch_X_P_object_l_20-X_P_wp_z*in_patch_X_P_object_l_20+171.706432*object_u_z+17.397568*object_w_z-17.397568*object_wp_z = 0;
   0.176*object_u_x*in_patch_X_2_object_v_14-1.76*object_u_x*in_patch_X_3_object_v_16-5.34*object_v_x*in_patch_X_2_object_u_14+5.34*object_v_x*in_patch_X_3_object_u_16+1.78*object_w_x*in_patch_X_2_object_v_14+0.548*object_w_x*in_patch_X_3_object_v_16-1.78*object_wp_x*in_patch_X_2_object_v_14-0.548*object_wp_x*in_patch_X_3_object_v_16-67.8*p22_u_x-30*p23_u_x-20*p24_u_x+67.8*p32_u_x+30*p33_u_x+20*p34_u_x+10*p34_v_x+12.42*object_u_x+11.06*object_v_x+6.552*object_w_x-6.552*object_wp_x-13*X_2_w_x+13*X_2_wp_x+13*X_3_w_x-13*X_3_wp_x = 0;
   0.176*object_u_y*in_patch_X_2_object_v_14-1.76*object_u_y*in_patch_X_3_object_v_16-5.34*object_v_y*in_patch_X_2_object_u_14+5.34*object_v_y*in_patch_X_3_object_u_16+1.78*object_w_y*in_patch_X_2_object_v_14+0.548*object_w_y*in_patch_X_3_object_v_16-1.78*object_wp_y*in_patch_X_2_object_v_14-0.548*object_wp_y*in_patch_X_3_object_v_16-67.8*p22_u_y-30*p23_u_y-20*p24_u_y+67.8*p32_u_y+30*p33_u_y+20*p34_u_y+10*p34_v_y+12.42*object_u_y+11.06*object_v_y+6.552*object_w_y-6.552*object_wp_y-13*X_2_w_y+13*X_2_wp_y+13*X_3_w_y-13*X_3_wp_y = -40.165;
   0.176*object_u_z*in_patch_X_2_object_v_14-1.76*object_u_z*in_patch_X_3_object_v_16-5.34*object_v_z*in_patch_X_2_object_u_14+5.34*object_v_z*in_patch_X_3_object_u_16+1.78*object_w_z*in_patch_X_2_object_v_14+0.548*object_w_z*in_patch_X_3_object_v_16-1.78*object_wp_z*in_patch_X_2_object_v_14-0.548*object_wp_z*in_patch_X_3_object_v_16-67.8*p22_u_z-30*p23_u_z-20*p24_u_z+67.8*p32_u_z+30*p33_u_z+20*p34_u_z+10*p34_v_z+12.42*object_u_z+11.06*object_v_z+6.552*object_w_z-6.552*object_wp_z-13*X_2_w_z+13*X_2_wp_z+13*X_3_w_z-13*X_3_wp_z = 4.72;
   0.176*object_u_x*in_patch_X_2_object_v_14+1.816*object_u_x*in_patch_X_4_object_v_18-5.34*object_v_x*in_patch_X_2_object_u_14+5.34*object_v_x*in_patch_X_4_object_u_18-0.034*object_v_x*in_patch_X_4_object_w_18+1.78*object_w_x*in_patch_X_2_object_v_14+0.184*object_w_x*in_patch_X_4_object_v_18-1.78*object_wp_x*in_patch_X_2_object_v_14-0.184*object_wp_x*in_patch_X_4_object_v_18-67.8*p22_u_x-30*p23_u_x-20*p24_u_x+97*p40_u_x+6*p40_v_x-87*p40_w_x+87*p40_wp_x+67.8*p42_u_x+30*p43_u_x+20*p44_u_x+8.876*object_u_x-10.836*object_w_x+10.836*object_wp_x-13*X_2_w_x+13*X_2_wp_x+13*X_4_w_x-13*X_4_wp_x = -1.3;
   0.176*object_u_y*in_patch_X_2_object_v_14+1.816*object_u_y*in_patch_X_4_object_v_18-5.34*object_v_y*in_patch_X_2_object_u_14+5.34*object_v_y*in_patch_X_4_object_u_18-0.034*object_v_y*in_patch_X_4_object_w_18+1.78*object_w_y*in_patch_X_2_object_v_14+0.184*object_w_y*in_patch_X_4_object_v_18-1.78*object_wp_y*in_patch_X_2_object_v_14-0.184*object_wp_y*in_patch_X_4_object_v_18-67.8*p22_u_y-30*p23_u_y-20*p24_u_y+97*p40_u_y+6*p40_v_y-87*p40_w_y+87*p40_wp_y+67.8*p42_u_y+30*p43_u_y+20*p44_u_y+8.876*object_u_y-10.836*object_w_y+10.836*object_wp_y-13*X_2_w_y+13*X_2_wp_y+13*X_4_w_y-13*X_4_wp_y = -27.1;
   0.176*object_u_z*in_patch_X_2_object_v_14+1.816*object_u_z*in_patch_X_4_object_v_18-5.34*object_v_z*in_patch_X_2_object_u_14+5.34*object_v_z*in_patch_X_4_object_u_18-0.034*object_v_z*in_patch_X_4_object_w_18+1.78*object_w_z*in_patch_X_2_object_v_14+0.184*object_w_z*in_patch_X_4_object_v_18-1.78*object_wp_z*in_patch_X_2_object_v_14-0.184*object_wp_z*in_patch_X_4_object_v_18-67.8*p22_u_z-30*p23_u_z-20*p24_u_z+97*p40_u_z+6*p40_v_z-87*p40_w_z+87*p40_wp_z+67.8*p42_u_z+30*p43_u_z+20*p44_u_z+8.876*object_u_z-10.836*object_w_z+10.836*object_wp_z-13*X_2_w_z+13*X_2_wp_z+13*X_4_w_z-13*X_4_wp_z = 150.15;
   0.176*object_u_x*in_patch_X_2_object_v_14+0.184*object_u_x*in_patch_X_P_object_v_20-5.34*object_v_x*in_patch_X_2_object_u_14+94.552*object_v_x*in_patch_X_P_object_u_20+1.78*object_w_x*in_patch_X_2_object_v_14-1.816*object_w_x*in_patch_X_P_object_v_20-1.78*object_wp_x*in_patch_X_2_object_v_14+1.816*object_wp_x*in_patch_X_P_object_v_20-67.8*p22_u_x-30*p23_u_x-20*p24_u_x-0.176*object_u_x-205.888*object_v_x-1.78*object_w_x+1.78*object_wp_x+13*X_P_w_x-13*X_P_wp_x-13*X_2_w_x+13*X_2_wp_x = -2.421;
   0.176*object_u_y*in_patch_X_2_object_v_14+0.184*object_u_y*in_patch_X_P_object_v_20-5.34*object_v_y*in_patch_X_2_object_u_14+94.552*object_v_y*in_patch_X_P_object_u_20+1.78*object_w_y*in_patch_X_2_object_v_14-1.816*object_w_y*in_patch_X_P_object_v_20-1.78*object_wp_y*in_patch_X_2_object_v_14+1.816*object_wp_y*in_patch_X_P_object_v_20-67.8*p22_u_y-30*p23_u_y-20*p24_u_y-0.176*object_u_y-205.888*object_v_y-1.78*object_w_y+1.78*object_wp_y+13*X_P_w_y-13*X_P_wp_y-13*X_2_w_y+13*X_2_wp_y = -49.495;
   0.176*object_u_z*in_patch_X_2_object_v_14+0.184*object_u_z*in_patch_X_P_object_v_20-5.34*object_v_z*in_patch_X_2_object_u_14+94.552*object_v_z*in_patch_X_P_object_u_20+1.78*object_w_z*in_patch_X_2_object_v_14-1.816*object_w_z*in_patch_X_P_object_v_20-1.78*object_wp_z*in_patch_X_2_object_v_14+1.816*object_wp_z*in_patch_X_P_object_v_20-67.8*p22_u_z-30*p23_u_z-20*p24_u_z-0.176*object_u_z-205.888*object_v_z-1.78*object_w_z+1.78*object_wp_z+13*X_P_w_z-13*X_P_wp_z-13*X_2_w_z+13*X_2_wp_z = 45.15;

% Equations added to couple the revolute joints in between phalanx
cos_p12_p13_1 - cos_p13_p14_2 = 0;
cos_p22_p23_4 - cos_p23_p24_5 = 0;
cos_p32_p33_7 - cos_p33_p34_8 = 0;
cos_p42_p43_11 - cos_p43_p44_12 = 0;

[COORD EQS]

   67.8*p12_u_x+30*p13_u_x-p14_r_x = 4.3;
   67.8*p12_u_y+30*p13_u_y-p14_r_y = 40.165;
   67.8*p12_u_z+30*p13_u_z-p14_r_z = -145.43;

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
   X_3_u_y*X_3_v_z-X_3_w_x = 0;
   X_3_u_z*X_3_v_x-X_3_w_y = 0;
   X_3_u_x*X_3_v_y-X_3_w_z = 0;
   X_3_u_z*X_3_v_y-X_3_wp_x = 0;
   X_3_u_x*X_3_v_z-X_3_wp_y = 0;
   X_3_u_y*X_3_v_x-X_3_wp_z = 0;
   X_4_u_y*X_4_v_z-X_4_w_x = 0;
   X_4_u_z*X_4_v_x-X_4_w_y = 0;
   X_4_u_x*X_4_v_y-X_4_w_z = 0;
   X_4_u_z*X_4_v_y-X_4_wp_x = 0;
   X_4_u_x*X_4_v_z-X_4_wp_y = 0;
   X_4_u_y*X_4_v_x-X_4_wp_z = 0;
   in_patch_X_2_object_u_14*in_patch_X_2_object_v_14-in_patch_X_2_object_w_14 = 0;
   in_patch_X_3_object_u_16*in_patch_X_3_object_v_16-in_patch_X_3_object_w_16 = 0;
   in_patch_X_4_object_u_18*in_patch_X_4_object_v_18-in_patch_X_4_object_w_18 = 0;
   in_patch_X_P_object_u_20*in_patch_X_P_object_v_20-in_patch_X_P_object_w_20 = 0;

[SEARCH]

 MIN 172.582639308*cos_0_palm_p22_3^2+11.6568542495*cos_1_palm_p22_3^2+11.6568542495*cos_p22_p23_4^2+11.6568542495*cos_p23_p24_5^2+172.582639308*cos_0_palm_p32_6^2+11.6568542495*cos_1_palm_p32_6^2+11.6568542495*cos_p32_p33_7^2+11.6568542495*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+11.6568542495*cos_p42_p43_11^2+11.6568542495*cos_p43_p44_12^2+cos_p24_X_2_13^2+4*in_patch_X_2_object_u_14^2+4*in_patch_X_2_object_v_14^2+cos_p34_X_3_15^2+4*in_patch_X_3_object_u_16^2+4*in_patch_X_3_object_v_16^2+4*cos_p44_X_4_17^2+4*in_patch_X_4_object_u_18^2+4*in_patch_X_4_object_v_18^2+4*cos_palm_X_P_19^2+4*in_patch_X_P_object_u_20^2+4*in_patch_X_P_object_v_20^2-345.165278616*cos_0_palm_p22_3-23.313708499*cos_1_palm_p22_3-23.313708499*cos_p22_p23_4-23.313708499*cos_p23_p24_5-345.165278616*cos_0_palm_p32_6-23.313708499*cos_1_palm_p32_6-23.313708499*cos_p32_p33_7-23.313708499*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-23.313708499*cos_p42_p43_11-23.313708499*cos_p43_p44_12-2*cos_p24_X_2_13-4*in_patch_X_2_object_u_14-4*in_patch_X_2_object_v_14-2*cos_p34_X_3_15-4*in_patch_X_3_object_u_16-4*in_patch_X_3_object_v_16-8*cos_p44_X_4_17-4*in_patch_X_4_object_u_18-4*in_patch_X_4_object_v_18-8*cos_palm_X_P_19-4*in_patch_X_P_object_u_20-4*in_patch_X_P_object_v_20+652.316460418




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
%   sph_w1_p34_X_3_x_15=sph_w1_p34_X_3_x_15
%   sph_w1_p34_X_3_y_15=sph_w1_p34_X_3_y_15
%   sph_w1_p34_X_3_z_15=sph_w1_p34_X_3_z_15
%   sph_w2_p34_X_3_x_15=sph_w2_p34_X_3_x_15
%   sph_w2_p34_X_3_y_15=sph_w2_p34_X_3_y_15
%   sph_w2_p34_X_3_z_15=sph_w2_p34_X_3_z_15
%   cos_p34_X_3_15=cos_p34_X_3_15
%   in_patch_X_3_object_u_16=in_patch_X_3_object_u_16
%   in_patch_X_3_object_v_16=in_patch_X_3_object_v_16
%   in_patch_X_3_object_w_16=No in simplification
%   in_patch_X_3_object_l_16= +9.84343798184
%   sph_w1_p44_X_4_x_17=sph_w1_p44_X_4_x_17
%   sph_w1_p44_X_4_y_17=sph_w1_p44_X_4_y_17
%   sph_w1_p44_X_4_z_17=sph_w1_p44_X_4_z_17
%   sph_w2_p44_X_4_x_17=sph_w2_p44_X_4_x_17
%   sph_w2_p44_X_4_y_17=sph_w2_p44_X_4_y_17
%   sph_w2_p44_X_4_z_17=sph_w2_p44_X_4_z_17
%   cos_p44_X_4_17=cos_p44_X_4_17
%   in_patch_X_4_object_u_18=in_patch_X_4_object_u_18
%   in_patch_X_4_object_v_18=in_patch_X_4_object_v_18
%   in_patch_X_4_object_w_18=in_patch_X_4_object_w_18
%   in_patch_X_4_object_l_18=in_patch_X_4_object_l_18
%   sph_w1_palm_X_P_x_19= +0.707106781187
%   sph_w1_palm_X_P_y_19= +0.707106781187
%   sph_w1_palm_X_P_z_19= -0
%   sph_w2_palm_X_P_x_19=sph_w2_palm_X_P_x_19
%   sph_w2_palm_X_P_y_19=sph_w2_palm_X_P_y_19
%   sph_w2_palm_X_P_z_19=sph_w2_palm_X_P_z_19
%   cos_palm_X_P_19=cos_palm_X_P_19
%   in_patch_X_P_object_u_20=in_patch_X_P_object_u_20
%   in_patch_X_P_object_v_20=in_patch_X_P_object_v_20
%   in_patch_X_P_object_w_20=No in simplification
%   in_patch_X_P_object_l_20= +172.585556066
%   p14_r_x=p14_r_x
%   p14_r_y=p14_r_y
%   p14_r_z=p14_r_z

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
   cos_0_palm_p32_6 : [0.923879532511,1]
   w1_p32_p33_x_7 : [0.707106781163,1]
   w1_p32_p33_y_7 : [-1,1]
   w1_p32_p33_z_7 : [-1,1]
   w1_p33_p34_x_8 : [-1,1]
   w1_p33_p34_y_8 : [-1,1]
   w1_p33_p34_z_8 : [-1,1]
   cos_p33_p34_8 : [0.707106781187,1]
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
   cos_p24_X_2_13 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_2_object_u_14 : [0,1]
   in_patch_X_2_object_v_14 : [0,1]

[SECONDARY VARS]
   sph_w1_p34_X_3_x_15 : [-1,1]
   sph_w1_p34_X_3_y_15 : [-1,1]
   sph_w1_p34_X_3_z_15 : [-1,1]
   sph_w2_p34_X_3_x_15 : [-1,1]
   sph_w2_p34_X_3_y_15 : [-1,1]
   sph_w2_p34_X_3_z_15 : [-1,1]
   cos_p34_X_3_15 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_16 : [0,1]
   in_patch_X_3_object_v_16 : [0,1]

[SECONDARY VARS]
   sph_w1_p44_X_4_x_17 : [-1,1]
   sph_w1_p44_X_4_y_17 : [-1,1]
   sph_w1_p44_X_4_z_17 : [-1,1]
   sph_w2_p44_X_4_x_17 : [-1,1]
   sph_w2_p44_X_4_y_17 : [-1,1]
   sph_w2_p44_X_4_z_17 : [-1,1]
   cos_p44_X_4_17 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_4_object_u_18 : [0,1]
   in_patch_X_4_object_v_18 : [0,1]

[DUMMY VARS]
   in_patch_X_4_object_w_18 : [0,1]

[SECONDARY VARS]
   in_patch_X_4_object_l_18 : [9.68483120378,9.74728773384]
   sph_w2_palm_X_P_x_19 : [-1,1]
   sph_w2_palm_X_P_y_19 : [-1,1]
   sph_w2_palm_X_P_z_19 : [-1,1]
   cos_palm_X_P_19 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_P_object_u_20 : [0,1]
   in_patch_X_P_object_v_20 : [0,1]

[CARTESIAN VARS]
   p14_r_x : [-1710.17469171,1710.17469171]
   p14_r_y : [-1710.17469171,1710.17469171]
   p14_r_z : [-1710.17469171,1710.17469171]

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
   dummy_p32_u_y_p34_v_y : [-1,1]
   dummy_p32_u_z_p34_v_z : [-1,1]
   dummy_p33_u_y_p34_v_y : [-1,1]
   dummy_p33_u_z_p34_v_z : [-1,1]
   dummy_p34_u_y_p34_v_y : [-1,1]
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
   dummy_X_3_u_x_X_3_v_x : [-1,1]
   dummy_X_3_u_y_X_3_v_y : [-1,1]
   dummy_X_3_u_z_X_3_v_z : [-1,1]
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
   dummy_p33_u_x_w1_p32_p33_x_7 : [-1,1]
   dummy_p33_u_y_w1_p32_p33_y_7 : [-1,1]
   dummy_p33_u_z_w1_p32_p33_z_7 : [-1,1]
   dummy_p34_u_x_w1_p33_p34_x_8 : [-1,1]
   dummy_p34_u_y_w1_p33_p34_y_8 : [-1,1]
   dummy_p34_u_z_w1_p33_p34_z_8 : [-1,1]
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
   dummy_sph_w1_p34_X_3_x_15_sph_w2_p34_X_3_x_15 : [-1,1]
   dummy_sph_w1_p34_X_3_y_15_sph_w2_p34_X_3_y_15 : [-1,1]
   dummy_sph_w1_p34_X_3_z_15_sph_w2_p34_X_3_z_15 : [-1,1]
   dummy_sph_w1_p44_X_4_x_17_sph_w2_p44_X_4_x_17 : [-1,1]
   dummy_sph_w1_p44_X_4_y_17_sph_w2_p44_X_4_y_17 : [-1,1]
   dummy_sph_w1_p44_X_4_z_17_sph_w2_p44_X_4_z_17 : [-1,1]
   dummy_in_patch_X_4_object_v_18_2 : [0,1]
   dummy_in_patch_X_4_object_l_18_2 : [93.7959554457,95.0096181663]
   dummy_object_u_x_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_w_x_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_wp_x_in_patch_X_4_object_v_18 : [-1,1]
   dummy_X_4_w_x_in_patch_X_4_object_l_18 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_x_in_patch_X_4_object_l_18 : [-9.74728773384,9.74728773384]
   dummy_object_u_y_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_w_y_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_wp_y_in_patch_X_4_object_v_18 : [-1,1]
   dummy_X_4_w_y_in_patch_X_4_object_l_18 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_y_in_patch_X_4_object_l_18 : [-9.74728773384,9.74728773384]
   dummy_object_u_z_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_w_z_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_wp_z_in_patch_X_4_object_v_18 : [-1,1]
   dummy_X_4_w_z_in_patch_X_4_object_l_18 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_z_in_patch_X_4_object_l_18 : [-9.74728773384,9.74728773384]
   dummy_object_u_x_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_u_x_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_v_x_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_x_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_u_y_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_v_y_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_y_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_u_z_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_u_z_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_v_z_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_v_z_in_patch_X_P_object_u_20 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_z_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_P_object_v_20 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_u_18 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_w_18 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_u_18 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_w_18 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_u_18 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_w_18 : [-1,1]
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
   p34_v_y^2+p34_v_z^2 = 1;
   dummy_p32_u_y_p34_v_y+dummy_p32_u_z_p34_v_z = 0;
   p33_u_x^2+p33_u_y^2+p33_u_z^2 = 1;
   dummy_p33_u_y_p34_v_y+dummy_p33_u_z_p34_v_z = 0;
   p34_u_x^2+p34_u_y^2+p34_u_z^2 = 1;
   dummy_p34_u_y_p34_v_y+dummy_p34_u_z_p34_v_z = 0;
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
   X_3_u_x^2+X_3_u_y^2+X_3_u_z^2 = 1;
   X_3_v_x^2+X_3_v_y^2+X_3_v_z^2 = 1;
   dummy_X_3_u_x_X_3_v_x+dummy_X_3_u_y_X_3_v_y+dummy_X_3_u_z_X_3_v_z = 0;
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
   0.999370208806*p34_v_y+0.0354850074141*p34_v_z+cos_0_palm_p32_6 = 0;
   0.707106781187*p32_u_x+0.707106781187*p32_w_x-0.707106781187*p32_wp_x-w1_p32_p33_x_7 = 0;
   0.707106781187*p32_u_y-0.707106781187*p32_wp_y-w1_p32_p33_y_7 = 0;
   0.707106781187*p32_u_z+0.707106781187*p32_w_z-w1_p32_p33_z_7 = 0;
   cos_p33_p34_8-dummy_p33_u_x_w1_p32_p33_x_7-dummy_p33_u_y_w1_p32_p33_y_7-dummy_p33_u_z_w1_p32_p33_z_7 = -0;
   0.707106781187*p33_u_x+0.707106781187*p33_w_x-0.707106781187*p33_wp_x-w1_p33_p34_x_8 = 0;
   0.707106781187*p33_u_y-0.707106781187*p33_wp_y-w1_p33_p34_y_8 = 0;
   0.707106781187*p33_u_z+0.707106781187*p33_w_z-w1_p33_p34_z_8 = 0;
   cos_p33_p34_8-dummy_p34_u_x_w1_p33_p34_x_8-dummy_p34_u_y_w1_p33_p34_y_8-dummy_p34_u_z_w1_p33_p34_z_8 = -0;
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
   0.140021004726*p34_u_x+0.990148533421*p34_w_x-0.990148533421*p34_wp_x-sph_w1_p34_X_3_x_15 = 0;
   0.140021004726*p34_u_y-0.990148533421*p34_wp_y-sph_w1_p34_X_3_y_15 = 0;
   0.140021004726*p34_u_z+0.990148533421*p34_w_z-sph_w1_p34_X_3_z_15 = 0;
   X_3_w_x-X_3_wp_x-sph_w2_p34_X_3_x_15 = 0;
   X_3_w_y-X_3_wp_y-sph_w2_p34_X_3_y_15 = 0;
   X_3_w_z-X_3_wp_z-sph_w2_p34_X_3_z_15 = 0;
   cos_p34_X_3_15-dummy_sph_w1_p34_X_3_x_15_sph_w2_p34_X_3_x_15-dummy_sph_w1_p34_X_3_y_15_sph_w2_p34_X_3_y_15-dummy_sph_w1_p34_X_3_z_15_sph_w2_p34_X_3_z_15 = -0;
   97.97832*object_u_x+95.5155098744*sph_w2_p24_X_2_x_13-9.84343798184*sph_w2_p34_X_3_x_15 = 0;
   97.97832*object_u_y+95.5155098744*sph_w2_p24_X_2_y_13-9.84343798184*sph_w2_p34_X_3_y_15 = 0;
   97.97832*object_u_z+95.5155098744*sph_w2_p24_X_2_z_13-9.84343798184*sph_w2_p34_X_3_z_15 = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_17 = 0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_17 = 0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_17 = 0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_17 = 0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_17 = 0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_17 = 0;
   cos_p44_X_4_17-dummy_sph_w1_p44_X_4_x_17_sph_w2_p44_X_4_x_17-dummy_sph_w1_p44_X_4_y_17_sph_w2_p44_X_4_y_17-dummy_sph_w1_p44_X_4_z_17_sph_w2_p44_X_4_z_17 = -0;
   1.20981126144*in_patch_X_4_object_v_18-0.003851459072*dummy_in_patch_X_4_object_v_18_2+dummy_in_patch_X_4_object_l_18_2 = 95.0057667072;
   97.0938218182*object_u_x+98.554639734*sph_w2_p24_X_2_x_13+0.006256*dummy_object_u_x_in_patch_X_4_object_v_18-0.061744*dummy_object_w_x_in_patch_X_4_object_v_18+0.061744*dummy_object_wp_x_in_patch_X_4_object_v_18+dummy_X_4_w_x_in_patch_X_4_object_l_18-dummy_X_4_wp_x_in_patch_X_4_object_l_18 = 0;
   97.0938218182*object_u_y+98.554639734*sph_w2_p24_X_2_y_13+0.006256*dummy_object_u_y_in_patch_X_4_object_v_18-0.061744*dummy_object_w_y_in_patch_X_4_object_v_18+0.061744*dummy_object_wp_y_in_patch_X_4_object_v_18+dummy_X_4_w_y_in_patch_X_4_object_l_18-dummy_X_4_wp_y_in_patch_X_4_object_l_18 = 0;
   97.0938218182*object_u_z+98.554639734*sph_w2_p24_X_2_z_13+0.006256*dummy_object_u_z_in_patch_X_4_object_v_18-0.061744*dummy_object_w_z_in_patch_X_4_object_v_18+0.061744*dummy_object_wp_z_in_patch_X_4_object_v_18+dummy_X_4_w_z_in_patch_X_4_object_l_18-dummy_X_4_wp_z_in_patch_X_4_object_l_18 = 0;
   X_P_w_x-X_P_wp_x-sph_w2_palm_X_P_x_19 = 0;
   X_P_w_y-X_P_wp_y-sph_w2_palm_X_P_y_19 = 0;
   X_P_w_z-X_P_wp_z-sph_w2_palm_X_P_z_19 = 0;
   0.707106781187*sph_w2_palm_X_P_x_19+0.707106781187*sph_w2_palm_X_P_y_19-cos_palm_X_P_19 = 0;
   347.659108364*object_u_x+176.810688851*sph_w2_p24_X_2_x_13+172.585556066*sph_w2_palm_X_P_x_19 = 0;
   347.659108364*object_u_y+176.810688851*sph_w2_p24_X_2_y_13+172.585556066*sph_w2_palm_X_P_y_19 = 0;
   347.659108364*object_u_z+176.810688851*sph_w2_p24_X_2_z_13+172.585556066*sph_w2_palm_X_P_z_19 = 0;
   67.8*p32_u_x+30*p33_u_x+20*p34_u_x+10.0017181818*object_u_x+216.948*object_v_x+21.7265412479*sph_w2_p34_X_3_x_15-13*sph_w2_palm_X_P_x_19-1.76*dummy_object_u_x_in_patch_X_3_object_v_16-0.184*dummy_object_u_x_in_patch_X_P_object_v_20+5.34*dummy_object_v_x_in_patch_X_3_object_u_16-94.552*dummy_object_v_x_in_patch_X_P_object_u_20+0.548*dummy_object_w_x_in_patch_X_3_object_v_16+1.816*dummy_object_w_x_in_patch_X_P_object_v_20-0.548*dummy_object_wp_x_in_patch_X_3_object_v_16-1.816*dummy_object_wp_x_in_patch_X_P_object_v_20 = 2.421;
   67.8*p32_u_y+30*p33_u_y+20*p34_u_y+10*p34_v_y+10.0017181818*object_u_y+216.948*object_v_y+21.7265412479*sph_w2_p34_X_3_y_15-13*sph_w2_palm_X_P_y_19-1.76*dummy_object_u_y_in_patch_X_3_object_v_16-0.184*dummy_object_u_y_in_patch_X_P_object_v_20+5.34*dummy_object_v_y_in_patch_X_3_object_u_16-94.552*dummy_object_v_y_in_patch_X_P_object_u_20+0.548*dummy_object_w_y_in_patch_X_3_object_v_16+1.816*dummy_object_w_y_in_patch_X_P_object_v_20-0.548*dummy_object_wp_y_in_patch_X_3_object_v_16-1.816*dummy_object_wp_y_in_patch_X_P_object_v_20 = 9.33;
   67.8*p32_u_z+30*p33_u_z+20*p34_u_z+10*p34_v_z+10.0017181818*object_u_z+216.948*object_v_z+21.7265412479*sph_w2_p34_X_3_z_15-13*sph_w2_palm_X_P_z_19-1.76*dummy_object_u_z_in_patch_X_3_object_v_16-0.184*dummy_object_u_z_in_patch_X_P_object_v_20+5.34*dummy_object_v_z_in_patch_X_3_object_u_16-94.552*dummy_object_v_z_in_patch_X_P_object_u_20+0.548*dummy_object_w_z_in_patch_X_3_object_v_16+1.816*dummy_object_w_z_in_patch_X_P_object_v_20-0.548*dummy_object_wp_z_in_patch_X_3_object_v_16-1.816*dummy_object_wp_z_in_patch_X_P_object_v_20 = -40.43;
   6*p40_v_x+87*p40_v_y+67.8*p42_u_x+30*p43_u_x+20*p44_u_x+98.4307826087*object_u_x+205.888*object_v_x+13*sph_w2_p44_X_4_x_17+76.8363952786*sph_w2_palm_X_P_x_19+1.816*dummy_object_u_x_in_patch_X_4_object_v_18+0.184*dummy_object_w_x_in_patch_X_4_object_v_18-0.184*dummy_object_wp_x_in_patch_X_4_object_v_18-0.184*dummy_object_u_x_in_patch_X_P_object_v_20-94.552*dummy_object_v_x_in_patch_X_P_object_u_20+1.816*dummy_object_w_x_in_patch_X_P_object_v_20-1.816*dummy_object_wp_x_in_patch_X_P_object_v_20+5.34*dummy_object_v_x_in_patch_X_4_object_u_18-0.034*dummy_object_v_x_in_patch_X_4_object_w_18 = 1.121;
   87*p40_v_x-6*p40_v_y-67.8*p42_u_y-30*p43_u_y-20*p44_u_y-98.4307826087*object_u_y-205.888*object_v_y-13*sph_w2_p44_X_4_y_17-76.8363952786*sph_w2_palm_X_P_y_19-1.816*dummy_object_u_y_in_patch_X_4_object_v_18-0.184*dummy_object_w_y_in_patch_X_4_object_v_18+0.184*dummy_object_wp_y_in_patch_X_4_object_v_18+0.184*dummy_object_u_y_in_patch_X_P_object_v_20+94.552*dummy_object_v_y_in_patch_X_P_object_u_20-1.816*dummy_object_w_y_in_patch_X_P_object_v_20+1.816*dummy_object_wp_y_in_patch_X_P_object_v_20-5.34*dummy_object_v_y_in_patch_X_4_object_u_18+0.034*dummy_object_v_y_in_patch_X_4_object_w_18 = -22.395;
   67.8*p42_u_z+30*p43_u_z+20*p44_u_z+98.4307826087*object_u_z+205.888*object_v_z+13*sph_w2_p44_X_4_z_17+76.8363952786*sph_w2_palm_X_P_z_19+1.816*dummy_object_u_z_in_patch_X_4_object_v_18+0.184*dummy_object_w_z_in_patch_X_4_object_v_18-0.184*dummy_object_wp_z_in_patch_X_4_object_v_18-0.184*dummy_object_u_z_in_patch_X_P_object_v_20-94.552*dummy_object_v_z_in_patch_X_P_object_u_20+1.816*dummy_object_w_z_in_patch_X_P_object_v_20-1.816*dummy_object_wp_z_in_patch_X_P_object_v_20+5.34*dummy_object_v_z_in_patch_X_4_object_u_18-0.034*dummy_object_v_z_in_patch_X_4_object_w_18 = 8;
   67.8*p22_u_x+30*p23_u_x+20*p24_u_x-42.9534504328*object_u_x+205.888*object_v_x-43.3471192931*sph_w2_palm_X_P_x_19-0.184*dummy_object_u_x_in_patch_X_P_object_v_20-94.552*dummy_object_v_x_in_patch_X_P_object_u_20+1.816*dummy_object_w_x_in_patch_X_P_object_v_20-1.816*dummy_object_wp_x_in_patch_X_P_object_v_20-0.176*dummy_object_u_x_in_patch_X_2_object_v_14+5.34*dummy_object_v_x_in_patch_X_2_object_u_14-1.78*dummy_object_w_x_in_patch_X_2_object_v_14+1.78*dummy_object_wp_x_in_patch_X_2_object_v_14 = 2.421;
   67.8*p22_u_y+30*p23_u_y+20*p24_u_y-42.9534504328*object_u_y+205.888*object_v_y-43.3471192931*sph_w2_palm_X_P_y_19-0.184*dummy_object_u_y_in_patch_X_P_object_v_20-94.552*dummy_object_v_y_in_patch_X_P_object_u_20+1.816*dummy_object_w_y_in_patch_X_P_object_v_20-1.816*dummy_object_wp_y_in_patch_X_P_object_v_20-0.176*dummy_object_u_y_in_patch_X_2_object_v_14+5.34*dummy_object_v_y_in_patch_X_2_object_u_14-1.78*dummy_object_w_y_in_patch_X_2_object_v_14+1.78*dummy_object_wp_y_in_patch_X_2_object_v_14 = 49.495;
   67.8*p22_u_z+30*p23_u_z+20*p24_u_z-42.9534504328*object_u_z+205.888*object_v_z-43.3471192931*sph_w2_palm_X_P_z_19-0.184*dummy_object_u_z_in_patch_X_P_object_v_20-94.552*dummy_object_v_z_in_patch_X_P_object_u_20+1.816*dummy_object_w_z_in_patch_X_P_object_v_20-1.816*dummy_object_wp_z_in_patch_X_P_object_v_20-0.176*dummy_object_u_z_in_patch_X_2_object_v_14+5.34*dummy_object_v_z_in_patch_X_2_object_u_14-1.78*dummy_object_w_z_in_patch_X_2_object_v_14+1.78*dummy_object_wp_z_in_patch_X_2_object_v_14 = -45.15;

[COORD EQS]

   67.8*p12_u_x+30*p13_u_x-p14_r_x = 4.3;
   67.8*p12_u_y+30*p13_u_y-p14_r_y = 40.165;
   67.8*p12_u_z+30*p13_u_z-p14_r_z = -145.43;

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
   p32_u_y*p34_v_y-dummy_p32_u_y_p34_v_y = 0;
   p32_u_z*p34_v_z-dummy_p32_u_z_p34_v_z = 0;
   p33_u_y*p34_v_y-dummy_p33_u_y_p34_v_y = 0;
   p33_u_z*p34_v_z-dummy_p33_u_z_p34_v_z = 0;
   p34_u_y*p34_v_y-dummy_p34_u_y_p34_v_y = 0;
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
   X_3_u_x*X_3_v_x-dummy_X_3_u_x_X_3_v_x = 0;
   X_3_u_y*X_3_v_y-dummy_X_3_u_y_X_3_v_y = 0;
   X_3_u_z*X_3_v_z-dummy_X_3_u_z_X_3_v_z = 0;
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
   p33_u_x*w1_p32_p33_x_7-dummy_p33_u_x_w1_p32_p33_x_7 = 0;
   p33_u_y*w1_p32_p33_y_7-dummy_p33_u_y_w1_p32_p33_y_7 = 0;
   p33_u_z*w1_p32_p33_z_7-dummy_p33_u_z_w1_p32_p33_z_7 = 0;
   p34_u_x*w1_p33_p34_x_8-dummy_p34_u_x_w1_p33_p34_x_8 = 0;
   p34_u_y*w1_p33_p34_y_8-dummy_p34_u_y_w1_p33_p34_y_8 = 0;
   p34_u_z*w1_p33_p34_z_8-dummy_p34_u_z_w1_p33_p34_z_8 = 0;
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
   sph_w1_p34_X_3_x_15*sph_w2_p34_X_3_x_15-dummy_sph_w1_p34_X_3_x_15_sph_w2_p34_X_3_x_15 = 0;
   sph_w1_p34_X_3_y_15*sph_w2_p34_X_3_y_15-dummy_sph_w1_p34_X_3_y_15_sph_w2_p34_X_3_y_15 = 0;
   sph_w1_p34_X_3_z_15*sph_w2_p34_X_3_z_15-dummy_sph_w1_p34_X_3_z_15_sph_w2_p34_X_3_z_15 = 0;
   sph_w1_p44_X_4_x_17*sph_w2_p44_X_4_x_17-dummy_sph_w1_p44_X_4_x_17_sph_w2_p44_X_4_x_17 = 0;
   sph_w1_p44_X_4_y_17*sph_w2_p44_X_4_y_17-dummy_sph_w1_p44_X_4_y_17_sph_w2_p44_X_4_y_17 = 0;
   sph_w1_p44_X_4_z_17*sph_w2_p44_X_4_z_17-dummy_sph_w1_p44_X_4_z_17_sph_w2_p44_X_4_z_17 = 0;
   in_patch_X_4_object_v_18^2-dummy_in_patch_X_4_object_v_18_2 = 0;
   in_patch_X_4_object_l_18^2-dummy_in_patch_X_4_object_l_18_2 = 0;
   object_u_x*in_patch_X_4_object_v_18-dummy_object_u_x_in_patch_X_4_object_v_18 = 0;
   object_w_x*in_patch_X_4_object_v_18-dummy_object_w_x_in_patch_X_4_object_v_18 = 0;
   object_wp_x*in_patch_X_4_object_v_18-dummy_object_wp_x_in_patch_X_4_object_v_18 = 0;
   X_4_w_x*in_patch_X_4_object_l_18-dummy_X_4_w_x_in_patch_X_4_object_l_18 = 0;
   X_4_wp_x*in_patch_X_4_object_l_18-dummy_X_4_wp_x_in_patch_X_4_object_l_18 = 0;
   object_u_y*in_patch_X_4_object_v_18-dummy_object_u_y_in_patch_X_4_object_v_18 = 0;
   object_w_y*in_patch_X_4_object_v_18-dummy_object_w_y_in_patch_X_4_object_v_18 = 0;
   object_wp_y*in_patch_X_4_object_v_18-dummy_object_wp_y_in_patch_X_4_object_v_18 = 0;
   X_4_w_y*in_patch_X_4_object_l_18-dummy_X_4_w_y_in_patch_X_4_object_l_18 = 0;
   X_4_wp_y*in_patch_X_4_object_l_18-dummy_X_4_wp_y_in_patch_X_4_object_l_18 = 0;
   object_u_z*in_patch_X_4_object_v_18-dummy_object_u_z_in_patch_X_4_object_v_18 = 0;
   object_w_z*in_patch_X_4_object_v_18-dummy_object_w_z_in_patch_X_4_object_v_18 = 0;
   object_wp_z*in_patch_X_4_object_v_18-dummy_object_wp_z_in_patch_X_4_object_v_18 = 0;
   X_4_w_z*in_patch_X_4_object_l_18-dummy_X_4_w_z_in_patch_X_4_object_l_18 = 0;
   X_4_wp_z*in_patch_X_4_object_l_18-dummy_X_4_wp_z_in_patch_X_4_object_l_18 = 0;
   object_u_x*in_patch_X_3_object_v_16-dummy_object_u_x_in_patch_X_3_object_v_16 = 0;
   object_u_x*in_patch_X_P_object_v_20-dummy_object_u_x_in_patch_X_P_object_v_20 = 0;
   object_v_x*in_patch_X_3_object_u_16-dummy_object_v_x_in_patch_X_3_object_u_16 = 0;
   object_v_x*in_patch_X_P_object_u_20-dummy_object_v_x_in_patch_X_P_object_u_20 = 0;
   object_w_x*in_patch_X_3_object_v_16-dummy_object_w_x_in_patch_X_3_object_v_16 = 0;
   object_w_x*in_patch_X_P_object_v_20-dummy_object_w_x_in_patch_X_P_object_v_20 = 0;
   object_wp_x*in_patch_X_3_object_v_16-dummy_object_wp_x_in_patch_X_3_object_v_16 = 0;
   object_wp_x*in_patch_X_P_object_v_20-dummy_object_wp_x_in_patch_X_P_object_v_20 = 0;
   object_u_y*in_patch_X_3_object_v_16-dummy_object_u_y_in_patch_X_3_object_v_16 = 0;
   object_u_y*in_patch_X_P_object_v_20-dummy_object_u_y_in_patch_X_P_object_v_20 = 0;
   object_v_y*in_patch_X_3_object_u_16-dummy_object_v_y_in_patch_X_3_object_u_16 = 0;
   object_v_y*in_patch_X_P_object_u_20-dummy_object_v_y_in_patch_X_P_object_u_20 = 0;
   object_w_y*in_patch_X_3_object_v_16-dummy_object_w_y_in_patch_X_3_object_v_16 = 0;
   object_w_y*in_patch_X_P_object_v_20-dummy_object_w_y_in_patch_X_P_object_v_20 = 0;
   object_wp_y*in_patch_X_3_object_v_16-dummy_object_wp_y_in_patch_X_3_object_v_16 = 0;
   object_wp_y*in_patch_X_P_object_v_20-dummy_object_wp_y_in_patch_X_P_object_v_20 = 0;
   object_u_z*in_patch_X_3_object_v_16-dummy_object_u_z_in_patch_X_3_object_v_16 = 0;
   object_u_z*in_patch_X_P_object_v_20-dummy_object_u_z_in_patch_X_P_object_v_20 = 0;
   object_v_z*in_patch_X_3_object_u_16-dummy_object_v_z_in_patch_X_3_object_u_16 = 0;
   object_v_z*in_patch_X_P_object_u_20-dummy_object_v_z_in_patch_X_P_object_u_20 = 0;
   object_w_z*in_patch_X_3_object_v_16-dummy_object_w_z_in_patch_X_3_object_v_16 = 0;
   object_w_z*in_patch_X_P_object_v_20-dummy_object_w_z_in_patch_X_P_object_v_20 = 0;
   object_wp_z*in_patch_X_3_object_v_16-dummy_object_wp_z_in_patch_X_3_object_v_16 = 0;
   object_wp_z*in_patch_X_P_object_v_20-dummy_object_wp_z_in_patch_X_P_object_v_20 = 0;
   object_v_x*in_patch_X_4_object_u_18-dummy_object_v_x_in_patch_X_4_object_u_18 = 0;
   object_v_x*in_patch_X_4_object_w_18-dummy_object_v_x_in_patch_X_4_object_w_18 = 0;
   object_v_y*in_patch_X_4_object_u_18-dummy_object_v_y_in_patch_X_4_object_u_18 = 0;
   object_v_y*in_patch_X_4_object_w_18-dummy_object_v_y_in_patch_X_4_object_w_18 = 0;
   object_v_z*in_patch_X_4_object_u_18-dummy_object_v_z_in_patch_X_4_object_u_18 = 0;
   object_v_z*in_patch_X_4_object_w_18-dummy_object_v_z_in_patch_X_4_object_w_18 = 0;
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
   X_3_u_y*X_3_v_z-X_3_w_x = 0;
   X_3_u_z*X_3_v_x-X_3_w_y = 0;
   X_3_u_x*X_3_v_y-X_3_w_z = 0;
   X_3_u_z*X_3_v_y-X_3_wp_x = 0;
   X_3_u_x*X_3_v_z-X_3_wp_y = 0;
   X_3_u_y*X_3_v_x-X_3_wp_z = 0;
   X_4_u_y*X_4_v_z-X_4_w_x = 0;
   X_4_u_z*X_4_v_x-X_4_w_y = 0;
   X_4_u_x*X_4_v_y-X_4_w_z = 0;
   X_4_u_z*X_4_v_y-X_4_wp_x = 0;
   X_4_u_x*X_4_v_z-X_4_wp_y = 0;
   X_4_u_y*X_4_v_x-X_4_wp_z = 0;
   in_patch_X_4_object_u_18*in_patch_X_4_object_v_18-in_patch_X_4_object_w_18 = 0;

[SEARCH]

 MIN 172.582639308*p24_v_y^2+11.6568542495*w1_p22_p23_x_4^2+23.313708499*cos_p23_p24_5^2+172.582639308*cos_0_palm_p32_6^2+11.6568542495*w1_p32_p33_x_7^2+23.313708499*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+23.313708499*cos_p43_p44_12^2+cos_p24_X_2_13^2+4*in_patch_X_2_object_u_14^2+4*in_patch_X_2_object_v_14^2+cos_p34_X_3_15^2+4*in_patch_X_3_object_u_16^2+4*in_patch_X_3_object_v_16^2+4*cos_p44_X_4_17^2+4*in_patch_X_4_object_u_18^2+4*in_patch_X_4_object_v_18^2+4*cos_palm_X_P_19^2+4*in_patch_X_P_object_u_20^2+4*in_patch_X_P_object_v_20^2+345.165278616*p24_v_y-23.313708499*w1_p22_p23_x_4-46.627416998*cos_p23_p24_5-345.165278616*cos_0_palm_p32_6-23.313708499*w1_p32_p33_x_7-46.627416998*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-46.627416998*cos_p43_p44_12-2*cos_p24_X_2_13-4*in_patch_X_2_object_u_14-4*in_patch_X_2_object_v_14-2*cos_p34_X_3_15-4*in_patch_X_3_object_u_16-4*in_patch_X_3_object_v_16-8*cos_p44_X_4_17-4*in_patch_X_4_object_u_18-4*in_patch_X_4_object_v_18-8*cos_palm_X_P_19-4*in_patch_X_P_object_u_20-4*in_patch_X_P_object_v_20+652.316460418

==========================================================================
Cuik executed in 32 processors
SOLUTIONS (to input file /home/porta/cuik/CuikSuite/examples/IJRR/scalpel/4_contacts_middle_index_thumb_palm/SAHandplusScalpel_kin.cuik):

   1 (err:0.99882 min:9.01914 tm:415):{ 270  p12_u_x:[-0.00148625497711,0.00148625497711] p12_u_y:[0.0342827392959,0.0343145877605] p12_u_z:[0.999411069153,0.999412174301] p12_v_x:[-0,0] p12_v_y:[-0.999412172992,-0.999411082499] p12_v_z:[0.034282777166,0.0343145502604] p13_u_x:[-0.00405505470336,0.00405505470336] p13_u_y:[0.0342824952954,0.0343145503312] p13_u_z:[0.999403957289,0.999412173333] p13_v_x:[-0,0] p13_v_y:[-0.999412172992,-0.999411082499] p13_v_z:[0.034282777166,0.0343145502604] p14_u_x:[-0.00862872500843,0.00862872500843] p14_u_y:[0.0342815008764,0.0343145503249] p14_u_z:[0.999374974112,0.999412174827] p14_v_x:[-0,0] p14_v_y:[-0.999412172992,-0.999411082499] p14_v_z:[0.034282777166,0.0343145502604] p22_u_x:[0.220166429673,0.221577344037] p22_u_y:[0.362271867248,0.363421853952] p22_u_z:[0.905096024442,0.905612966355] p22_v_x:[-0,0] p22_v_y:[-0.928467550579,-0.928004911465] p22_v_z:[0.371411391732,0.372567959268] p23_u_x:[0.760586364189,0.762569084578] p23_u_y:[0.240414035676,0.241776984951] p23_u_z:[0.600561579789,0.60253819144] p23_v_x:[-0,0] p23_v_y:[-0.928467550579,-0.928004911465] p23_v_z:[0.371411391732,0.372567959268] p24_u_x:[0.997967519948,0.99820411154] p24_u_y:[0.0222631523665,0.0237417572051] p24_u_z:[0.055613881196,0.0591367742047] p24_v_x:[-0,0] p24_v_y:[-0.928467550579,-0.928004911465] p24_v_z:[0.371411391732,0.372567959268] p32_u_x:[0.415999782237,0.416571822344] p32_u_y:[0.316926392775,0.317967268986] p32_u_z:[0.851716460976,0.852071972186] p32_v_x:[-0,0] p32_v_y:[-0.937266219898,-0.93687720568] p32_v_z:[0.348614447583,0.349658549833] p33_u_x:[0.615664059068,0.616918008935] p33_u_y:[0.274369332438,0.275534190707] p33_u_z:[0.737458226982,0.738268506243] p33_v_x:[-0,0] p33_v_y:[-0.937266219898,-0.93687720568] p33_v_z:[0.348614447583,0.349658549833] p34_u_x:[0.781313235371,0.783355881234] p34_u_y:[0.216865045117,0.218235575991] p34_u_z:[0.582341453941,0.584741705022] p34_v_x:[-0,0] p34_v_y:[-0.937266219898,-0.93687720568] p34_v_z:[0.348614447583,0.349658549833] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0768142500587,-0.0746172651175] p40_v_y:[0.997045420709,0.997212246092] p40_v_z:[-0,0] p42_u_x:[-2.94955850621e-07,0] p42_u_y:[-2.56258204517e-07,1.66346840976e-07] p42_u_z:[0.999999999983,1] p42_v_x:[-0.0768223570244,-0.0746170795571] p42_v_y:[0.997044796101,0.997213183561] p42_v_z:[-1.65845252117e-07,0] p43_u_x:[-7.49193356821e-11,1.34039748698e-10] p43_u_y:[-1.66336802699e-07,0] p43_u_z:[0.999999999983,1] p43_v_x:[-0.0768223570244,-0.0746170795571] p43_v_y:[0.997044796101,0.997213183561] p43_v_z:[-1.65845252117e-07,0] p44_u_x:[-0,3.83035496502e-07] p44_u_y:[-0,4.99115953081e-07] p44_u_z:[0.999999999982,1] p44_v_x:[-0.0768223570244,-0.0746170795571] p44_v_y:[0.997044796101,0.997213183561] p44_v_z:[-1.65845252117e-07,0] object_u_x:[-0.551278486606,-0.549308875568] object_u_y:[-0.825605011382,-0.824161969338] object_u_z:[0.12895035414,0.129827723684] object_v_x:[-0.423287130222,-0.422562098932] object_v_y:[0.141394092358,0.142336018561] object_v_z:[-0.895200272079,-0.894825341839] X_P_u_x:[-0,0.0413136981584] X_P_u_y:[0.0748738615195,0.0980380669906] X_P_u_z:[0.995180953361,0.996620652133] X_P_v_x:[0.878392764458,0.880997678735] X_P_v_y:[-0.477801448771,-0.471449676046] X_P_v_z:[-0,0.0467447897971] X_2_u_x:[0.0445957517825,0.108326708839] X_2_u_y:[0.132162102442,0.182882566304] X_2_u_z:[0.98202201638,0.986266180956] X_2_v_x:[0.77755645351,0.786665081845] X_2_v_y:[-0.628820829642,-0.61380119533] X_2_v_z:[-0,0.0773157063152] X_3_u_x:[0.848259804586,0.853369540799] X_3_u_y:[0.470775372017,0.504021372206] X_3_u_z:[0.161513294496,0.228926394707] X_3_v_x:[-0,0.0633635926633] X_3_v_y:[-0.434138939396,-0.39696467626] X_3_v_z:[0.90085120985,0.916591748087] X_4_u_x:[-0.514331771505,-0.483264541959] X_4_u_y:[-0.87381903036,-0.857592749802] X_4_u_z:[-0,0.066239628207] X_4_v_x:[0.374472762285,0.412810094178] X_4_v_y:[-0.226297208735,-0.162673613379] X_4_v_z:[0.895991348901,0.900292642881] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412172992,-0.999411082499] uni_v_palm_p12_z_0:[0.034282777166,0.0343145502604] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.10001711113e-05,5.10001711113e-05] w2_palm_p12_z_0:[-0.00148538133741,0.00148538133741] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00148625497711,0.00148625497711] w1_p12_p13_y_1:[0.0342827392959,0.0343145877605] w1_p12_p13_z_1:[0.999411069153,0.999412174301] w2_p12_p13_x_1:[-0.00405505470336,0.00405505470336] w2_p12_p13_y_1:[0.0342824952954,0.0343145503312] w2_p12_p13_z_1:[0.999403957289,0.999412173333] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00405505470336,0.00405505470336] w1_p13_p14_y_2:[0.0342824952954,0.0343145503312] w1_p13_p14_z_2:[0.999403957289,0.999412173333] w2_p13_p14_x_2:[-0.00862872500843,0.00862872500843] w2_p13_p14_y_2:[0.0342815008764,0.0343145503249] w2_p13_p14_z_2:[0.999374974112,0.999412174827] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.928467550579,-0.928004911465] uni_v_palm_p22_z_3:[0.371411391732,0.372567959268] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.845429953783,0.846206487052] w2_palm_p22_y_3:[0.198031223588,0.198975223126] w2_palm_p22_z_3:[0.494678744163,0.495628149445] cos_0_palm_p22_3:[0.928004911465,0.928467550579] cos_1_palm_p22_3:[0.845429953783,0.846206487052] w1_p22_p23_x_4:[0.845429953783,0.846206487052] w1_p22_p23_y_4:[0.198031223588,0.198975223126] w1_p22_p23_z_4:[0.494678744163,0.495628149445] w2_p22_p23_x_4:[0.760586364189,0.762569084578] w2_p22_p23_y_4:[0.240414035676,0.241776984951] w2_p22_p23_z_4:[0.600561579789,0.60253819144] cos_p22_p23_4:[0.989642626403,0.990016174597] w1_p23_p24_x_5:[0.99664091619,0.996901949238] w1_p23_p24_y_5:[-0.0304000390216,-0.0293211560243] w1_p23_p24_z_5:[-0.0759352110872,-0.0730703437969] w2_p23_p24_x_5:[0.997967519948,0.99820411154] w2_p23_p24_y_5:[0.0222631523665,0.0237417572051] w2_p23_p24_z_5:[0.055613881196,0.0591367742047] cos_p23_p24_5:[0.989642626403,0.990016174597] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.937266219898,-0.93687720568] uni_v_palm_p32_z_6:[0.348614447583,0.349658549833] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.936911178548,0.937396074462] w2_palm_p32_y_6:[0.121411425026,0.12198255838] w2_palm_p32_z_6:[0.32628605129,0.32684141667] cos_0_palm_p32_6:[0.923879532511,0.924305351629] cos_1_palm_p32_6:[0.936911178548,0.937396074462] w1_p32_p33_x_7:[0.936911178548,0.937396074462] w1_p32_p33_y_7:[0.121411425026,0.12198255838] w1_p32_p33_z_7:[0.32628605129,0.32684141667] w2_p32_p33_x_7:[0.615664059068,0.616918008935] w2_p32_p33_y_7:[0.274369332438,0.275534190707] w2_p32_p33_z_7:[0.737458226982,0.738268506243] cos_p32_p33_7:[0.851551483104,0.852579056366] w1_p33_p34_x_8:[0.992546120071,0.992743206369] w1_p33_p34_y_8:[0.0419312583651,0.0426159259159] w1_p33_p34_z_8:[0.112739413289,0.114173985127] w2_p33_p34_x_8:[0.781313235371,0.783355881234] w2_p33_p34_y_8:[0.216865045117,0.218235575991] w2_p33_p34_z_8:[0.582341453941,0.584741705022] cos_p33_p34_8:[0.851551483104,0.852579056366] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.997212246092,-0.997045420709] w2_palm_p40_y_9:[-0.0768142500587,-0.0746172651175] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.75789791562,0.759333455229] uni_u_p40_p42_x_10:[-0.816866109597,-0.816729454631] uni_u_p40_p42_y_10:[-0.0629223696891,-0.061122710139] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0768223570244,-0.0746170795571] uni_v_p40_p42_y_10:[0.997044796101,0.997213183561] uni_v_p40_p42_z_10:[-1.65845252117e-07,0] w1_p40_p42_x_10:[-0.0768142500587,-0.0746172651175] w1_p40_p42_y_10:[0.997045420709,0.997212246092] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.705136186219,-0.705017136465] w2_p40_p42_y_10:[-0.0543217908008,-0.0527621252953] w2_p40_p42_z_10:[0.707106679094,0.707106883108] cos_0_p40_p42_10:[0.999997544761,1] cos_1_p40_p42_10:[0.984806975301,0.985001161293] w1_p42_p43_x_11:[-0.705136186219,-0.705017136465] w1_p42_p43_y_11:[-0.0543217908008,-0.0527621252953] w1_p42_p43_z_11:[0.707106679094,0.707106883108] w2_p42_p43_x_11:[-7.49193356821e-11,1.34039748698e-10] w2_p42_p43_y_11:[-1.66336802699e-07,0] w2_p42_p43_z_11:[0.999999999983,1] cos_p42_p43_11:[0.707106781187,0.707106985084] w1_p43_p44_x_12:[-0.705135977707,-0.705017136368] w1_p43_p44_y_12:[-0.0543217272166,-0.0527535143908] w1_p43_p44_z_12:[0.707106781154,0.707107051217] w2_p43_p44_x_12:[-0,3.83035496502e-07] w2_p43_p44_y_12:[-0,4.99115953081e-07] w2_p43_p44_z_12:[0.999999999982,1] cos_p43_p44_12:[0.707106781187,0.707106985084] sph_w1_p24_X_2_x_13:[0.199097249734,0.202842296773] sph_w1_p24_X_2_y_13:[-0.365021656309,-0.363907432904] sph_w1_p24_X_2_z_13:[-0.909797066404,-0.908714741451] sph_w2_p24_X_2_x_13:[0.617568902768,0.619390478299] sph_w2_p24_X_2_y_13:[0.766207172086,0.767850001388] sph_w2_p24_X_2_z_13:[-0.171148242087,-0.17030067554] cos_p24_X_2_13:[-1.83690953073e-16,0.000814576187248] in_patch_X_2_object_u_14:[0.99393155767,1] in_patch_X_2_object_v_14:[0.374999999996,0.465663989181] in_patch_X_2_object_l_14:[9.55155098744,9.55155098744] sph_w1_p34_X_3_x_15:[0.725136012318,0.72739759041] sph_w1_p34_X_3_y_15:[-0.240776142794,-0.239869549628] sph_w1_p34_X_3_z_15:[-0.645141884433,-0.642907219731] sph_w2_p34_X_3_x_15:[0.522990939697,0.52494767395] sph_w2_p34_X_3_y_15:[-0.768581234147,-0.766980671367] sph_w2_p34_X_3_z_15:[-0.369520107869,-0.368466596058] cos_p34_X_3_15:[0.801913569054,0.803162563997] in_patch_X_3_object_u_16:[0.0624999999994,0.0662267454365] in_patch_X_3_object_v_16:[0.609709331318,0.625000000006] in_patch_X_3_object_l_16:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_17:[-0.987389171212,-0.987222388973] sph_w1_p44_X_4_y_17:[-0.0760655441532,-0.0738696995688] sph_w1_p44_X_4_z_17:[0.140021004702,0.140021933738] sph_w2_p44_X_4_x_17:[-0.772557178248,-0.771304211485] sph_w2_p44_X_4_y_17:[0.460225664608,0.462490025548] sph_w2_p44_X_4_z_17:[0.437239957357,0.438146063523] cos_p44_X_4_17:[0.787886279726,0.790166998818] in_patch_X_4_object_u_18:[0.490347780213,0.500000000005] in_patch_X_4_object_v_18:[0.723825327402,0.750000000008] in_patch_X_4_object_l_18:[9.70054503824,9.7021695105] sph_w1_palm_X_P_x_19:[0.707106781187,0.707106781187] sph_w1_palm_X_P_y_19:[0.707106781187,0.707106781187] sph_w1_palm_X_P_z_19:[-0,0] sph_w2_palm_X_P_x_19:[0.473848195959,0.475950200297] sph_w2_palm_X_P_y_19:[0.875240054045,0.876463928304] sph_w2_palm_X_P_z_19:[-0.0861889245619,-0.0852897766869] cos_palm_X_P_19:[0.954809809678,0.955439788953] in_patch_X_P_object_u_20:[0.770287120079,0.770950104674] in_patch_X_P_object_v_20:[0.374999999996,0.435162666059] in_patch_X_P_object_l_20:[172.585556066,172.585556066] p14_r_x:[-4.52241972859,-4.07758027141] p14_r_y:[-36.8121554172,-36.8090344403] p14_r_z:[243.17222205,243.172510621] }


Cuik executed in 31 (31) child processors
STATITISTICS FOR Cuik:

Volume of the search space: 1.41321e+21
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 0.23075
Number of processors: 32
User time in process: 418.000000 seg (6.966667 min)
Box level information:
  N processed boxes :   3606
  Max depth         :     67
  Types of boxes:
    N solution boxes:      1 (0) ( 0.03%)
    N empty boxes   :    545  (15.11%)
    N bisected boxes:   3060  (84.86%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :   4526
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

