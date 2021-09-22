
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
Equations from file: /home/porta/cuik/CuikSuite/examples/IJRR/scalpel/2_contacts_index_thumb/SAHandplusScalpel_kin.cuik
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
   object_u_x : [-0.4,0.4]
   object_u_y : [-0.4,0.4]
   object_u_z : [0.8,1]
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
   cos_0_palm_p22_3 : [1,1]
   cos_1_palm_p22_3 : [1,1]
   w1_p22_p23_x_4 : [-1,1]
   w1_p22_p23_y_4 : [-1,1]
   w1_p22_p23_z_4 : [-1,1]
   w2_p22_p23_x_4 : [-1,1]
   w2_p22_p23_y_4 : [-1,1]
   w2_p22_p23_z_4 : [-1,1]
   cos_p22_p23_4 : [1,1]
   w1_p23_p24_x_5 : [-1,1]
   w1_p23_p24_y_5 : [-1,1]
   w1_p23_p24_z_5 : [-1,1]
   w2_p23_p24_x_5 : [-1,1]
   w2_p23_p24_y_5 : [-1,1]
   w2_p23_p24_z_5 : [-1,1]
   cos_p23_p24_5 : [1,1]
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
   sph_w1_p34_X_3_x_13 : [-1,1]
   sph_w1_p34_X_3_y_13 : [-1,1]
   sph_w1_p34_X_3_z_13 : [-1,1]
   sph_w2_p34_X_3_x_13 : [-1,1]
   sph_w2_p34_X_3_y_13 : [-1,1]
   sph_w2_p34_X_3_z_13 : [-1,1]
   cos_p34_X_3_13 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_14 : [0,1]
   in_patch_X_3_object_v_14 : [0,1]

[DUMMY VARS]
   in_patch_X_3_object_w_14 : [0,1]

[SECONDARY VARS]
   in_patch_X_3_object_l_14 : [9.84343798184,9.84343798184]
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

[CARTESIAN VARS]
   p14_r_x : [-1710.03327036,1710.03327036]
   p14_r_y : [-1710.03327036,1710.03327036]
   p14_r_z : [-1710.03327036,1710.03327036]
   p24_r_x : [-1710.03327036,1710.03327036]
   p24_r_y : [-1710.03327036,1710.03327036]
   p24_r_z : [-1710.03327036,1710.03327036]

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
   p22_w_x-p22_wp_x-w2_palm_p22_x_3 = -0;
   p22_w_y-p22_wp_y-w2_palm_p22_y_3 = -0;
   p22_w_z-p22_wp_z-w2_palm_p22_z_3 = -0;
   uni_v_palm_p22_x_3*w1_palm_p22_x_3+uni_v_palm_p22_y_3*w1_palm_p22_y_3+uni_v_palm_p22_z_3*w1_palm_p22_z_3-cos_0_palm_p22_3 = 0;
   uni_u_palm_p22_x_3*w2_palm_p22_x_3+uni_u_palm_p22_y_3*w2_palm_p22_y_3+uni_u_palm_p22_z_3*w2_palm_p22_z_3-cos_1_palm_p22_3 = 0;
   p22_v_x-p23_v_x = -0;
   p22_v_y-p23_v_y = -0;
   p22_v_z-p23_v_z = -0;
   p22_u_x-w1_p22_p23_x_4 = -0;
   p22_u_y-w1_p22_p23_y_4 = -0;
   p22_u_z-w1_p22_p23_z_4 = -0;
   p23_u_x-w2_p22_p23_x_4 = -0;
   p23_u_y-w2_p22_p23_y_4 = -0;
   p23_u_z-w2_p22_p23_z_4 = -0;
   w1_p22_p23_x_4*w2_p22_p23_x_4+w1_p22_p23_y_4*w2_p22_p23_y_4+w1_p22_p23_z_4*w2_p22_p23_z_4-cos_p22_p23_4 = 0;
   p23_v_x-p24_v_x = -0;
   p23_v_y-p24_v_y = -0;
   p23_v_z-p24_v_z = -0;
   p23_u_x-w1_p23_p24_x_5 = -0;
   p23_u_y-w1_p23_p24_y_5 = -0;
   p23_u_z-w1_p23_p24_z_5 = -0;
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
   0.140021004726*p34_u_x+0.990148533421*p34_w_x-0.990148533421*p34_wp_x-sph_w1_p34_X_3_x_13 = -0;
   0.140021004726*p34_u_y+0.990148533421*p34_w_y-0.990148533421*p34_wp_y-sph_w1_p34_X_3_y_13 = -0;
   0.140021004726*p34_u_z+0.990148533421*p34_w_z-0.990148533421*p34_wp_z-sph_w1_p34_X_3_z_13 = -0;
   X_3_w_x-X_3_wp_x-sph_w2_p34_X_3_x_13 = -0;
   X_3_w_y-X_3_wp_y-sph_w2_p34_X_3_y_13 = -0;
   X_3_w_z-X_3_wp_z-sph_w2_p34_X_3_z_13 = -0;
   sph_w1_p34_X_3_x_13*sph_w2_p34_X_3_x_13+sph_w1_p34_X_3_y_13*sph_w2_p34_X_3_y_13+sph_w1_p34_X_3_z_13*sph_w2_p34_X_3_z_13-cos_p34_X_3_13 = 0;
   in_patch_X_3_object_l_14^2 = 96.8932713024;
   X_3_w_x*in_patch_X_3_object_l_14-X_3_wp_x*in_patch_X_3_object_l_14-2.92632*object_u_x-9.3984*object_w_x+9.3984*object_wp_x = 0;
   X_3_w_y*in_patch_X_3_object_l_14-X_3_wp_y*in_patch_X_3_object_l_14-2.92632*object_u_y-9.3984*object_w_y+9.3984*object_wp_y = 0;
   X_3_w_z*in_patch_X_3_object_l_14-X_3_wp_z*in_patch_X_3_object_l_14-2.92632*object_u_z-9.3984*object_w_z+9.3984*object_wp_z = 0;
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
   1.76*object_u_x*in_patch_X_3_object_v_14+1.816*object_u_x*in_patch_X_4_object_v_16-5.34*object_v_x*in_patch_X_3_object_u_14+5.34*object_v_x*in_patch_X_4_object_u_16-0.034*object_v_x*in_patch_X_4_object_w_16-0.548*object_w_x*in_patch_X_3_object_v_14+0.184*object_w_x*in_patch_X_4_object_v_16+0.548*object_wp_x*in_patch_X_3_object_v_14-0.184*object_wp_x*in_patch_X_4_object_v_16-67.8*p32_u_x-30*p33_u_x-20*p34_u_x-10*p34_v_x+97*p40_u_x+6*p40_v_x-87*p40_w_x+87*p40_wp_x+67.8*p42_u_x+30*p43_u_x+20*p44_u_x-3.544*object_u_x-11.06*object_v_x-17.388*object_w_x+17.388*object_wp_x-13*X_3_w_x+13*X_3_wp_x+13*X_4_w_x-13*X_4_wp_x = -1.3;
   1.76*object_u_y*in_patch_X_3_object_v_14+1.816*object_u_y*in_patch_X_4_object_v_16-5.34*object_v_y*in_patch_X_3_object_u_14+5.34*object_v_y*in_patch_X_4_object_u_16-0.034*object_v_y*in_patch_X_4_object_w_16-0.548*object_w_y*in_patch_X_3_object_v_14+0.184*object_w_y*in_patch_X_4_object_v_16+0.548*object_wp_y*in_patch_X_3_object_v_14-0.184*object_wp_y*in_patch_X_4_object_v_16-67.8*p32_u_y-30*p33_u_y-20*p34_u_y-10*p34_v_y+97*p40_u_y+6*p40_v_y-87*p40_w_y+87*p40_wp_y+67.8*p42_u_y+30*p43_u_y+20*p44_u_y-3.544*object_u_y-11.06*object_v_y-17.388*object_w_y+17.388*object_wp_y-13*X_3_w_y+13*X_3_wp_y+13*X_4_w_y-13*X_4_wp_y = 13.065;
   1.76*object_u_z*in_patch_X_3_object_v_14+1.816*object_u_z*in_patch_X_4_object_v_16-5.34*object_v_z*in_patch_X_3_object_u_14+5.34*object_v_z*in_patch_X_4_object_u_16-0.034*object_v_z*in_patch_X_4_object_w_16-0.548*object_w_z*in_patch_X_3_object_v_14+0.184*object_w_z*in_patch_X_4_object_v_16+0.548*object_wp_z*in_patch_X_3_object_v_14-0.184*object_wp_z*in_patch_X_4_object_v_16-67.8*p32_u_z-30*p33_u_z-20*p34_u_z-10*p34_v_z+97*p40_u_z+6*p40_v_z-87*p40_w_z+87*p40_wp_z+67.8*p42_u_z+30*p43_u_z+20*p44_u_z-3.544*object_u_z-11.06*object_v_z-17.388*object_w_z+17.388*object_wp_z-13*X_3_w_z+13*X_3_wp_z+13*X_4_w_z-13*X_4_wp_z = 145.43;

% Equations added to couple the revolute joints in between phalanx
cos_p12_p13_1 - cos_p13_p14_2 = 0;
cos_p22_p23_4 - cos_p23_p24_5 = 0;
cos_p32_p33_7 - cos_p33_p34_8 = 0;
cos_p42_p43_11 - cos_p43_p44_12 = 0;

[COORD EQS]

   67.8*p12_u_x+30*p13_u_x-p14_r_x = 4.3;
   67.8*p12_u_y+30*p13_u_y-p14_r_y = 40.165;
   67.8*p12_u_z+30*p13_u_z-p14_r_z = -145.43;
   67.8*p22_u_x+30*p23_u_x-p24_r_x = 4.3;
   67.8*p22_u_y+30*p23_u_y-p24_r_y = 0;
   67.8*p22_u_z+30*p23_u_z-p24_r_z = -150.15;

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
   in_patch_X_3_object_u_14*in_patch_X_3_object_v_14-in_patch_X_3_object_w_14 = 0;
   in_patch_X_4_object_u_16*in_patch_X_4_object_v_16-in_patch_X_4_object_w_16 = 0;

[SEARCH]

 MIN 172.582639308*cos_0_palm_p32_6^2+11.6568542495*cos_1_palm_p32_6^2+11.6568542495*cos_p32_p33_7^2+11.6568542495*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+11.6568542495*cos_p42_p43_11^2+11.6568542495*cos_p43_p44_12^2+4*cos_p34_X_3_13^2+in_patch_X_3_object_u_14^2+in_patch_X_3_object_v_14^2+4*cos_p44_X_4_15^2+in_patch_X_4_object_u_16^2+in_patch_X_4_object_v_16^2-345.165278616*cos_0_palm_p32_6-23.313708499*cos_1_palm_p32_6-23.313708499*cos_p32_p33_7-23.313708499*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-23.313708499*cos_p42_p43_11-23.313708499*cos_p43_p44_12-8*cos_p34_X_3_13-in_patch_X_3_object_u_14-in_patch_X_3_object_v_14-8*cos_p44_X_4_15-in_patch_X_4_object_u_16-in_patch_X_4_object_v_16+435.763258362




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
%   p22_u_x= -0
%   p22_u_y= -0
%   p22_u_z= +1
%   p22_v_x= -0
%   p22_v_y= -1
%   p22_v_z= -0
%   p22_w_x= -0
%   p22_w_y= -0
%   p22_w_z= -0
%   p22_wp_x= -1
%   p22_wp_y= -0
%   p22_wp_z= -0
%   p23_u_x= -0
%   p23_u_y= -0
%   p23_u_z= +1
%   p23_v_x= -0
%   p23_v_y= -1
%   p23_v_z= -0
%   p23_w_x=No in simplification
%   p23_w_y=No in simplification
%   p23_w_z=No in simplification
%   p23_wp_x=No in simplification
%   p23_wp_y=No in simplification
%   p23_wp_z=No in simplification
%   p24_u_x= -0
%   p24_u_y= -0
%   p24_u_z= +1
%   p24_v_x= -0
%   p24_v_y= -1
%   p24_v_z= -0
%   p24_w_x=No in simplification
%   p24_w_y=No in simplification
%   p24_w_z=No in simplification
%   p24_wp_x=No in simplification
%   p24_wp_y=No in simplification
%   p24_wp_z=No in simplification
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
%   uni_v_palm_p22_y_3= -1
%   uni_v_palm_p22_z_3= -0
%   w1_palm_p22_x_3= -0
%   w1_palm_p22_y_3= -1
%   w1_palm_p22_z_3= -0
%   w2_palm_p22_x_3= +1
%   w2_palm_p22_y_3= -0
%   w2_palm_p22_z_3= -0
%   cos_0_palm_p22_3= +1
%   cos_1_palm_p22_3= +1
%   w1_p22_p23_x_4= -0
%   w1_p22_p23_y_4= -0
%   w1_p22_p23_z_4= +1
%   w2_p22_p23_x_4= -0
%   w2_p22_p23_y_4= -0
%   w2_p22_p23_z_4= +1
%   cos_p22_p23_4= +1
%   w1_p23_p24_x_5= -0
%   w1_p23_p24_y_5= -0
%   w1_p23_p24_z_5= +1
%   w2_p23_p24_x_5= -0
%   w2_p23_p24_y_5= -0
%   w2_p23_p24_z_5= +1
%   cos_p23_p24_5= +1
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
%   sph_w1_p34_X_3_x_13=sph_w1_p34_X_3_x_13
%   sph_w1_p34_X_3_y_13=sph_w1_p34_X_3_y_13
%   sph_w1_p34_X_3_z_13=sph_w1_p34_X_3_z_13
%   sph_w2_p34_X_3_x_13=sph_w2_p34_X_3_x_13
%   sph_w2_p34_X_3_y_13=sph_w2_p34_X_3_y_13
%   sph_w2_p34_X_3_z_13=sph_w2_p34_X_3_z_13
%   cos_p34_X_3_13=cos_p34_X_3_13
%   in_patch_X_3_object_u_14=in_patch_X_3_object_u_14
%   in_patch_X_3_object_v_14=in_patch_X_3_object_v_14
%   in_patch_X_3_object_w_14=No in simplification
%   in_patch_X_3_object_l_14= +9.84343798184
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
%   p14_r_x=p14_r_x
%   p14_r_y=p14_r_y
%   p14_r_z=p14_r_z
%   p24_r_x= -4.3
%   p24_r_y= -0
%   p24_r_z= +247.95

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
   object_u_x : [-0.4,0.4]
   object_u_y : [-0.4,0.4]
   object_u_z : [0.8,1]
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
   sph_w1_p34_X_3_x_13 : [-1,1]
   sph_w1_p34_X_3_y_13 : [-1,1]
   sph_w1_p34_X_3_z_13 : [-1,1]
   sph_w2_p34_X_3_x_13 : [-1,1]
   sph_w2_p34_X_3_y_13 : [-1,1]
   sph_w2_p34_X_3_z_13 : [-1,1]
   cos_p34_X_3_13 : [0.5,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_14 : [0,1]
   in_patch_X_3_object_v_14 : [0,1]

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

[CARTESIAN VARS]
   p14_r_x : [-1710.03327036,1710.03327036]
   p14_r_y : [-1710.03327036,1710.03327036]
   p14_r_z : [-1710.03327036,1710.03327036]

[DUMMY VARS]
   dummy_p14_v_z_2 : [0,1]
   dummy_p12_u_y_p14_v_z : [-1,1]
   dummy_p12_u_z_p14_v_z : [-1,1]
   dummy_p13_u_y_p14_v_z : [-1,1]
   dummy_p13_u_z_p14_v_z : [-1,1]
   dummy_p14_u_y_p14_v_z : [-1,1]
   dummy_p14_u_z_p14_v_z : [-1,1]
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
   dummy_object_u_x_object_v_x : [-0.4,0.4]
   dummy_object_u_y_object_v_y : [-0.4,0.4]
   dummy_object_u_z_object_v_z : [-1,1]
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
   dummy_sph_w1_p34_X_3_x_13_sph_w2_p34_X_3_x_13 : [-1,1]
   dummy_sph_w1_p34_X_3_y_13_sph_w2_p34_X_3_y_13 : [-1,1]
   dummy_sph_w1_p34_X_3_z_13_sph_w2_p34_X_3_z_13 : [-1,1]
   dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15 : [-1,1]
   dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15 : [-1,1]
   dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 : [-1,1]
   dummy_in_patch_X_4_object_v_16_2 : [0,1]
   dummy_in_patch_X_4_object_l_16_2 : [93.7959554457,95.0096181663]
   dummy_object_u_x_in_patch_X_4_object_v_16 : [-0.4,0.4]
   dummy_object_w_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_x_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_x_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_object_u_y_in_patch_X_4_object_v_16 : [-0.4,0.4]
   dummy_object_w_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_y_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_y_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_object_u_z_in_patch_X_4_object_v_16 : [0,1]
   dummy_object_w_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_z_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_X_4_wp_z_in_patch_X_4_object_l_16 : [-9.74728773384,9.74728773384]
   dummy_object_u_x_in_patch_X_3_object_v_14 : [-0.4,0.4]
   dummy_object_v_x_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_v_14 : [-0.4,0.4]
   dummy_object_v_y_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_u_z_in_patch_X_3_object_v_14 : [0,1]
   dummy_object_v_z_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_v_14 : [-1,1]

[SYSTEM EQS]

   p12_u_x^2+p12_u_y^2+p12_u_z^2 = 1;
   0.0686829158287*p14_v_z-1.00117794817*dummy_p14_v_z_2 = 0.00117794816892;
   1.00058880074*p12_u_y-0.0343212495372*dummy_p12_u_y_p14_v_z-dummy_p12_u_z_p14_v_z = -0;
   p13_u_x^2+p13_u_y^2+p13_u_z^2 = 1;
   1.00058880074*p13_u_y-0.0343212495372*dummy_p13_u_y_p14_v_z-dummy_p13_u_z_p14_v_z = -0;
   p14_u_x^2+p14_u_y^2+p14_u_z^2 = 1;
   1.00058880074*p14_u_y-0.0343212495372*dummy_p14_u_y_p14_v_z-dummy_p14_u_z_p14_v_z = -0;
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
   X_3_u_x^2+X_3_u_y^2+X_3_u_z^2 = 1;
   X_3_v_x^2+X_3_v_y^2+X_3_v_z^2 = 1;
   dummy_X_3_u_x_X_3_v_x+dummy_X_3_u_y_X_3_v_y+dummy_X_3_u_z_X_3_v_z = 0;
   X_4_u_x^2+X_4_u_y^2+X_4_u_z^2 = 1;
   X_4_v_x^2+X_4_v_y^2+X_4_v_z^2 = 1;
   dummy_X_4_u_x_X_4_v_x+dummy_X_4_u_y_X_4_v_y+dummy_X_4_u_z_X_4_v_z = 0;
   dummy_p12_u_x_p13_u_x+dummy_p12_u_y_p13_u_y+dummy_p12_u_z_p13_u_z = 1;
   dummy_p13_u_x_p14_u_x+dummy_p13_u_y_p14_u_y+dummy_p13_u_z_p14_u_z = 1;
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
   0.140021004726*p34_u_x+0.990148533421*p34_w_x-0.990148533421*p34_wp_x-sph_w1_p34_X_3_x_13 = 0;
   0.140021004726*p34_u_y-0.990148533421*p34_wp_y-sph_w1_p34_X_3_y_13 = 0;
   0.140021004726*p34_u_z+0.990148533421*p34_w_z-sph_w1_p34_X_3_z_13 = 0;
   X_3_w_x-X_3_wp_x-sph_w2_p34_X_3_x_13 = 0;
   X_3_w_y-X_3_wp_y-sph_w2_p34_X_3_y_13 = 0;
   X_3_w_z-X_3_wp_z-sph_w2_p34_X_3_z_13 = 0;
   cos_p34_X_3_13-dummy_sph_w1_p34_X_3_x_13_sph_w2_p34_X_3_x_13-dummy_sph_w1_p34_X_3_y_13_sph_w2_p34_X_3_y_13-dummy_sph_w1_p34_X_3_z_13_sph_w2_p34_X_3_z_13 = -0;
   2.92632*object_u_x+9.3984*object_w_x-9.3984*object_wp_x-9.84343798184*sph_w2_p34_X_3_x_13 = 0;
   2.92632*object_u_y+9.3984*object_w_y-9.3984*object_wp_y-9.84343798184*sph_w2_p34_X_3_y_13 = 0;
   2.92632*object_u_z+9.3984*object_w_z-9.3984*object_wp_z-9.84343798184*sph_w2_p34_X_3_z_13 = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_15 = 0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_15 = 0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_15 = 0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_15 = 0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_15 = 0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_15 = 0;
   cos_p44_X_4_15-dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15-dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15-dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 = -0;
   1.20981126144*in_patch_X_4_object_v_16-0.003851459072*dummy_in_patch_X_4_object_v_16_2+dummy_in_patch_X_4_object_l_16_2 = 95.0057667072;
   4.00199018182*object_u_x-10.1566382813*sph_w2_p34_X_3_x_13-0.006256*dummy_object_u_x_in_patch_X_4_object_v_16+0.061744*dummy_object_w_x_in_patch_X_4_object_v_16-0.061744*dummy_object_wp_x_in_patch_X_4_object_v_16-dummy_X_4_w_x_in_patch_X_4_object_l_16+dummy_X_4_wp_x_in_patch_X_4_object_l_16 = -0;
   4.00199018182*object_u_y-10.1566382813*sph_w2_p34_X_3_y_13-0.006256*dummy_object_u_y_in_patch_X_4_object_v_16+0.061744*dummy_object_w_y_in_patch_X_4_object_v_16-0.061744*dummy_object_wp_y_in_patch_X_4_object_v_16-dummy_X_4_w_y_in_patch_X_4_object_l_16+dummy_X_4_wp_y_in_patch_X_4_object_l_16 = -0;
   4.00199018182*object_u_z-10.1566382813*sph_w2_p34_X_3_z_13-0.006256*dummy_object_u_z_in_patch_X_4_object_v_16+0.061744*dummy_object_w_z_in_patch_X_4_object_v_16-0.061744*dummy_object_wp_z_in_patch_X_4_object_v_16-dummy_X_4_w_z_in_patch_X_4_object_l_16+dummy_X_4_wp_z_in_patch_X_4_object_l_16 = -0;
   67.8*p32_u_x+30*p33_u_x+20*p34_u_x-6*p40_v_x-87*p40_v_y-67.8*p42_u_x-30*p43_u_x-20*p44_u_x-1.86999090909*object_u_x+11.06*object_v_x+31.2113657248*sph_w2_p34_X_3_x_13-13*sph_w2_p44_X_4_x_15-1.816*dummy_object_u_x_in_patch_X_4_object_v_16-0.184*dummy_object_w_x_in_patch_X_4_object_v_16+0.184*dummy_object_wp_x_in_patch_X_4_object_v_16-1.76*dummy_object_u_x_in_patch_X_3_object_v_14+5.34*dummy_object_v_x_in_patch_X_3_object_u_14-5.34*dummy_object_v_x_in_patch_X_4_object_u_16+0.034*dummy_object_v_x_in_patch_X_4_object_w_16+0.548*dummy_object_w_x_in_patch_X_3_object_v_14-0.548*dummy_object_wp_x_in_patch_X_3_object_v_14 = 1.3;
   67.8*p32_u_y+30*p33_u_y+20*p34_u_y+10*p34_v_y+87*p40_v_x-6*p40_v_y-67.8*p42_u_y-30*p43_u_y-20*p44_u_y-1.86999090909*object_u_y+11.06*object_v_y+31.2113657248*sph_w2_p34_X_3_y_13-13*sph_w2_p44_X_4_y_15-1.816*dummy_object_u_y_in_patch_X_4_object_v_16-0.184*dummy_object_w_y_in_patch_X_4_object_v_16+0.184*dummy_object_wp_y_in_patch_X_4_object_v_16-1.76*dummy_object_u_y_in_patch_X_3_object_v_14+5.34*dummy_object_v_y_in_patch_X_3_object_u_14-5.34*dummy_object_v_y_in_patch_X_4_object_u_16+0.034*dummy_object_v_y_in_patch_X_4_object_w_16+0.548*dummy_object_w_y_in_patch_X_3_object_v_14-0.548*dummy_object_wp_y_in_patch_X_3_object_v_14 = -13.065;
   67.8*p32_u_z+30*p33_u_z+20*p34_u_z+10*p34_v_z-67.8*p42_u_z-30*p43_u_z-20*p44_u_z-1.86999090909*object_u_z+11.06*object_v_z+31.2113657248*sph_w2_p34_X_3_z_13-13*sph_w2_p44_X_4_z_15-1.816*dummy_object_u_z_in_patch_X_4_object_v_16-0.184*dummy_object_w_z_in_patch_X_4_object_v_16+0.184*dummy_object_wp_z_in_patch_X_4_object_v_16-1.76*dummy_object_u_z_in_patch_X_3_object_v_14+5.34*dummy_object_v_z_in_patch_X_3_object_u_14-5.34*dummy_object_v_z_in_patch_X_4_object_u_16+0.034*dummy_object_v_z_in_patch_X_4_object_w_16+0.548*dummy_object_w_z_in_patch_X_3_object_v_14-0.548*dummy_object_wp_z_in_patch_X_3_object_v_14 = -48.43;

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
   sph_w1_p34_X_3_x_13*sph_w2_p34_X_3_x_13-dummy_sph_w1_p34_X_3_x_13_sph_w2_p34_X_3_x_13 = 0;
   sph_w1_p34_X_3_y_13*sph_w2_p34_X_3_y_13-dummy_sph_w1_p34_X_3_y_13_sph_w2_p34_X_3_y_13 = 0;
   sph_w1_p34_X_3_z_13*sph_w2_p34_X_3_z_13-dummy_sph_w1_p34_X_3_z_13_sph_w2_p34_X_3_z_13 = 0;
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
   object_u_x*in_patch_X_3_object_v_14-dummy_object_u_x_in_patch_X_3_object_v_14 = 0;
   object_v_x*in_patch_X_3_object_u_14-dummy_object_v_x_in_patch_X_3_object_u_14 = 0;
   object_v_x*in_patch_X_4_object_u_16-dummy_object_v_x_in_patch_X_4_object_u_16 = 0;
   object_v_x*in_patch_X_4_object_w_16-dummy_object_v_x_in_patch_X_4_object_w_16 = 0;
   object_w_x*in_patch_X_3_object_v_14-dummy_object_w_x_in_patch_X_3_object_v_14 = 0;
   object_wp_x*in_patch_X_3_object_v_14-dummy_object_wp_x_in_patch_X_3_object_v_14 = 0;
   object_u_y*in_patch_X_3_object_v_14-dummy_object_u_y_in_patch_X_3_object_v_14 = 0;
   object_v_y*in_patch_X_3_object_u_14-dummy_object_v_y_in_patch_X_3_object_u_14 = 0;
   object_v_y*in_patch_X_4_object_u_16-dummy_object_v_y_in_patch_X_4_object_u_16 = 0;
   object_v_y*in_patch_X_4_object_w_16-dummy_object_v_y_in_patch_X_4_object_w_16 = 0;
   object_w_y*in_patch_X_3_object_v_14-dummy_object_w_y_in_patch_X_3_object_v_14 = 0;
   object_wp_y*in_patch_X_3_object_v_14-dummy_object_wp_y_in_patch_X_3_object_v_14 = 0;
   object_u_z*in_patch_X_3_object_v_14-dummy_object_u_z_in_patch_X_3_object_v_14 = 0;
   object_v_z*in_patch_X_3_object_u_14-dummy_object_v_z_in_patch_X_3_object_u_14 = 0;
   object_v_z*in_patch_X_4_object_u_16-dummy_object_v_z_in_patch_X_4_object_u_16 = 0;
   object_v_z*in_patch_X_4_object_w_16-dummy_object_v_z_in_patch_X_4_object_w_16 = 0;
   object_w_z*in_patch_X_3_object_v_14-dummy_object_w_z_in_patch_X_3_object_v_14 = 0;
   object_wp_z*in_patch_X_3_object_v_14-dummy_object_wp_z_in_patch_X_3_object_v_14 = 0;
   p12_u_y*p14_v_z-p12_wp_x = 1;
   0.0343212495372*p12_u_x*p14_v_z-1.00058880074*p12_u_x-w2_palm_p12_z_0 = 0;
   0.0343212495372*p12_u_z*p14_v_z-1.00058880074*p12_u_z-p12_wp_x = 0;
   p12_u_x*p14_v_z+w2_palm_p12_y_0 = 0;
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
   in_patch_X_4_object_u_16*in_patch_X_4_object_v_16-in_patch_X_4_object_w_16 = 0;

[SEARCH]

 MIN 172.582639308*cos_0_palm_p32_6^2+11.6568542495*w1_p32_p33_x_7^2+23.313708499*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+23.313708499*cos_p43_p44_12^2+4*cos_p34_X_3_13^2+in_patch_X_3_object_u_14^2+in_patch_X_3_object_v_14^2+4*cos_p44_X_4_15^2+in_patch_X_4_object_u_16^2+in_patch_X_4_object_v_16^2-345.165278616*cos_0_palm_p32_6-23.313708499*w1_p32_p33_x_7-46.627416998*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-46.627416998*cos_p43_p44_12-8*cos_p34_X_3_13-in_patch_X_3_object_u_14-in_patch_X_3_object_v_14-8*cos_p44_X_4_15-in_patch_X_4_object_u_16-in_patch_X_4_object_v_16+435.763258362

==========================================================================
Cuik executed in 32 processors
SOLUTIONS (to input file /home/porta/cuik/CuikSuite/examples/IJRR/scalpel/2_contacts_index_thumb/SAHandplusScalpel_kin.cuik):

   1 (err:2.90587 min:3.17767 tm:105):{ 241  p12_u_x:[-0.00206210882792,0.00206210882792] p12_u_y:[0.0342895893587,0.0343206222767] p12_u_z:[0.999409812208,0.999411936786] p12_v_x:[-0,0] p12_v_y:[-0.999411936686,-0.999410875351] p12_v_z:[0.0342896622764,0.034320585816] p13_u_x:[-0.00498391965421,0.00498391965421] p13_u_y:[0.0342892363927,0.0343206075183] p13_u_z:[0.999399526513,0.999411936816] p13_v_x:[-0,0] p13_v_y:[-0.999411936686,-0.999410875351] p13_v_z:[0.0342896622764,0.034320585816] p14_u_x:[-0.0103927781199,0.0103927781199] p14_u_y:[0.0342878104032,0.0343205966884] p14_u_z:[0.999357982666,0.999411937207] p14_v_x:[-0,0] p14_v_y:[-0.999411936686,-0.999410875351] p14_v_z:[0.0342896622764,0.034320585816] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.404594767257,0.464537197132] p32_u_y:[-0.0695915454496,1.00331839452e-11] p32_u_z:[0.882708433791,0.911655769083] p32_v_x:[-0,0] p32_v_y:[-1,-0.996831085559] p32_v_z:[-0.077861271247,0] p33_u_x:[0.773697776386,0.800203317183] p33_u_y:[-0.0487040797699,1.00331839452e-11] p33_u_z:[0.59882642712,0.631752078265] p33_v_x:[-0,0] p33_v_y:[-1,-0.996831085559] p33_v_z:[-0.077861271247,0] p34_u_x:[0.96207350088,0.977772868659] p34_u_y:[-0.0209246961172,1.00331839452e-11] p34_u_z:[0.209666920002,0.272441148915] p34_v_x:[-0,0] p34_v_y:[-1,-0.996831085559] p34_v_z:[-0.077861271247,0] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0643794105914,3.82843494672e-11] p40_v_y:[0.997832977912,1] p40_v_z:[-0,0] p42_u_x:[0.24928478791,0.315973028778] p42_u_y:[-0,0.0180798229995] p42_u_z:[0.948588653291,0.968430221825] p42_v_x:[-0.06034274831,4.01147622522e-11] p42_v_y:[0.998076874836,1] p42_v_z:[-0,0.00586283415991] p43_u_x:[0.138654203903,0.200251019754] p43_u_y:[-0,0.0115283618069] p43_u_z:[0.979756588898,0.990801771595] p43_v_x:[-0.06034274831,4.01147622522e-11] p43_v_y:[0.998076874836,1] p43_v_z:[-0,0.00586283415991] p44_u_x:[-0,0.0945626505201] p44_u_y:[-0,0.00571568895017] p44_u_z:[0.995502116055,1] p44_v_x:[-0.06034274831,4.01147622522e-11] p44_v_y:[0.998076874836,1] p44_v_z:[-0,0.00586283415991] object_u_x:[0.377317022608,0.4] object_u_y:[0.267246290382,0.319920545535] object_u_z:[0.858866022452,0.877024252683] object_v_x:[0.427283891818,0.504797444123] object_v_y:[-0.896572426895,-0.858511925963] object_v_z:[0.0701624126268,0.133372023007] X_3_u_x:[-0.476084935664,-0.386287150597] X_3_u_y:[0.876313894372,0.920268059813] X_3_u_z:[0.0253647405704,0.12445333338] X_3_v_x:[0.184659505302,0.228886476143] X_3_v_y:[-0.0259641752099,0.0561322390347] X_3_v_z:[0.971833397631,0.982265707823] X_4_u_x:[0.642169854977,0.692947103627] X_4_u_y:[-0.377505733444,-0.329960361537] X_4_u_z:[0.614546815355,0.691643469093] X_4_v_x:[-0,0.0370385557545] X_4_v_y:[0.851429799068,0.902285251494] X_4_v_z:[0.433598321792,0.524452004729] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411936686,-0.999410875351] uni_v_palm_p12_z_0:[0.0342896622764,0.034320585816] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-7.07727829898e-05,7.07727829898e-05] w2_palm_p12_z_0:[-0.00206089619852,0.00206089619852] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00206210882792,0.00206210882792] w1_p12_p13_y_1:[0.0342895893587,0.0343206222767] w1_p12_p13_z_1:[0.999409812208,0.999411936786] w2_p12_p13_x_1:[-0.00498391965421,0.00498391965421] w2_p12_p13_y_1:[0.0342892363927,0.0343206075183] w2_p12_p13_z_1:[0.999399526513,0.999411936816] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00498391965421,0.00498391965421] w1_p13_p14_y_2:[0.0342892363927,0.0343206075183] w1_p13_p14_z_2:[0.999399526513,0.999411936816] w2_p13_p14_x_2:[-0.0103927781199,0.0103927781199] w2_p13_p14_y_2:[0.0342878104032,0.0343205966884] w2_p13_p14_z_2:[0.999357982666,0.999411937207] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-1,-0.996831085559] uni_v_palm_p32_z_6:[-0.077861271247,0] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.930565815666,0.95618109964] w2_palm_p32_y_6:[-0.0274660713701,0.000665458482836] w2_palm_p32_z_6:[0.296396786798,0.359459807578] cos_0_palm_p32_6:[0.998966197907,1] cos_1_palm_p32_6:[0.930565815666,0.95618109964] w1_p32_p33_x_7:[0.930565815666,0.95618109964] w1_p32_p33_y_7:[-0.0274660713701,0.000665458482836] w1_p32_p33_z_7:[0.296396786798,0.359459807578] w2_p32_p33_x_7:[0.773697776386,0.800203317183] w2_p32_p33_y_7:[-0.0487040797699,1.00331839452e-11] w2_p32_p33_z_7:[0.59882642712,0.631752078265] cos_p32_p33_7:[0.926536297745,0.951882357963] w1_p33_p34_x_8:[0.988725262155,0.995794649571] w1_p33_p34_y_8:[-0.000757347677259,0.0105361852366] w1_p33_p34_z_8:[-0.141242296031,-0.0987668284217] w2_p33_p34_x_8:[0.96207350088,0.977772868659] w2_p33_p34_y_8:[-0.0209246961172,1.00331839452e-11] w2_p33_p34_z_8:[0.209666920002,0.272441148915] cos_p33_p34_8:[0.926536297745,0.951882357963] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.997832977912] w2_palm_p40_y_9:[-0.0643794105914,3.82843494672e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.751497665691] uni_u_p40_p42_x_10:[-0.819149697375,-0.817374581876] uni_u_p40_p42_y_10:[-0.0527363747026,3.136061328e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.06034274831,4.01147622522e-11] uni_v_p40_p42_y_10:[0.998076874836,1] uni_v_p40_p42_z_10:[-0,0.00586283415991] w1_p40_p42_x_10:[-0.0643794105914,3.82843494672e-11] w1_p40_p42_y_10:[0.997832977912,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.508512613005,-0.446039216874] w2_p40_p42_y_10:[-0.0353404688128,0.00161931489796] w2_p40_p42_z_10:[0.860748337752,0.895183095339] cos_0_p40_p42_10:[0.997849581658,1] cos_1_p40_p42_10:[0.878009690926,0.911171027718] w1_p42_p43_x_11:[-0.508512613005,-0.446039216874] w1_p42_p43_y_11:[-0.0353404688128,0.00161931489796] w1_p42_p43_z_11:[0.860748337752,0.895183095339] w2_p42_p43_x_11:[0.138654203903,0.200251019754] w2_p42_p43_y_11:[-0,0.0115283618069] w2_p42_p43_z_11:[0.979756588898,0.990801771595] cos_p42_p43_11:[0.758450831564,0.812379259382] w1_p43_p44_x_12:[-0.60255922365,-0.550774724885] w1_p43_p44_y_12:[-0.0401856444587,3.45883110631e-05] w1_p43_p44_z_12:[0.798414022422,0.834769443972] w2_p43_p44_x_12:[-0,0.0945626505201] w2_p43_p44_y_12:[-0,0.00571568895017] w2_p43_p44_z_12:[0.995502116055,1] cos_p43_p44_12:[0.758450831564,0.812379259382] sph_w1_p34_X_3_x_13:[0.344030599839,0.405515123448] sph_w1_p34_X_3_y_13:[-3.99999111912e-11,0.0729829594517] sph_w1_p34_X_3_z_13:[-0.938782599155,-0.91151859784] sph_w2_p34_X_3_x_13:[0.84891209241,0.894027675263] sph_w2_p34_X_3_y_13:[0.395002922935,0.474843909917] sph_w2_p34_X_3_z_13:[-0.227767627789,-0.194113645348] cos_p34_X_3_13:[0.5,0.588450799148] in_patch_X_3_object_u_14:[0.437499999996,0.500000000005] in_patch_X_3_object_v_14:[0.437499999996,0.500000000005] in_patch_X_3_object_l_14:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_15:[-0.990148533442,-0.970554451304] sph_w1_p44_X_4_y_15:[-0.0602046621868,4.80247707011e-05] sph_w1_p44_X_4_z_15:[0.140021004665,0.233463849291] sph_w2_p44_X_4_x_15:[-0.767375096082,-0.720322836314] sph_w2_p44_X_4_y_15:[-0.363419588056,-0.280227339713] sph_w2_p44_X_4_z_15:[0.561825772624,0.59001024194] cos_p44_X_4_15:[0.795679337735,0.883800213675] in_patch_X_4_object_u_16:[0.437499999996,0.500000000005] in_patch_X_4_object_v_16:[0.374999999996,0.437500000004] in_patch_X_4_object_l_16:[9.71993866774,9.72381781325] p14_r_x:[-4.5893285682,-4.0106714318] p14_r_y:[-36.8114865803,-36.8084435827] p14_r_z:[243.172034546,243.17248742] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }
   2 (err:2.63304 min:3.13727 tm:105):{ 241  p12_u_x:[-0.00206163370251,0.00206163370251] p12_u_y:[0.0342895928476,0.034320611473] p12_u_z:[0.999409813068,0.999411936667] p12_v_x:[-0,0] p12_v_y:[-0.999411936568,-0.999410875721] p12_v_z:[0.0342896657316,0.0343205750292] p13_u_x:[-0.00498274183974,0.00498274183974] p13_u_y:[0.0342892400492,0.0343205858777] p13_u_z:[0.999399532407,0.999411936697] p13_v_x:[-0,0] p13_v_y:[-0.999411936568,-0.999410875721] p13_v_z:[0.0342896657316,0.0343205750292] p14_u_x:[-0.0103905076106,0.0103905076106] p14_u_y:[0.0342878146674,0.0343206075254] p14_u_z:[0.999358004642,0.999411937088] p14_v_x:[-0,0] p14_v_y:[-0.999411936568,-0.999410875721] p14_v_z:[0.0342896657316,0.0343205750292] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.36953881208,0.464891423425] p32_u_y:[-0.0886977196076,1.00489112509e-11] p32_u_z:[0.880962056968,0.928373012214] p32_v_x:[-0,0] p32_v_y:[-1,-0.995138824627] p32_v_z:[-0.098419759256,0] p33_u_x:[0.752816372533,0.808713735542] p33_u_y:[-0.062750274542,1.00489112509e-11] p33_u_z:[0.587501477976,0.656081263347] p33_v_x:[-0,0] p33_v_y:[-1,-0.995138824627] p33_v_z:[-0.098419759256,0] p34_u_x:[0.961782908236,0.980879657724] p34_u_y:[-0.026681541253,1.00489112509e-11] p34_u_z:[0.194615254006,0.272508668214] p34_v_x:[-0,0] p34_v_y:[-1,-0.995138824627] p34_v_z:[-0.098419759256,0] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0823656732322,3.82843494672e-11] p40_v_y:[0.996598108929,1] p40_v_z:[-0,0] p42_u_x:[0.241461986851,0.315973028778] p42_u_y:[-0,0.0229677935142] p42_u_z:[0.948489789252,0.970410278662] p42_v_x:[-0.0773358314148,4.14143862995e-11] p42_v_y:[0.996975270405,1] p42_v_z:[-0,0.00734983342052] p43_u_x:[0.118313722352,0.203466511623] p43_u_y:[-0,0.0146766326423] p43_u_z:[0.979056973723,0.992979894653] p43_v_x:[-0.0773358314148,4.14143862995e-11] p43_v_y:[0.996975270405,1] p43_v_z:[-0,0.00734983342052] p44_u_x:[-0,0.0945626505201] p44_u_y:[-0,0.00717176343369] p44_u_z:[0.995493046549,1] p44_v_x:[-0.0773358314148,4.14143862995e-11] p44_v_y:[0.996975270405,1] p44_v_z:[-0,0.00734983342052] object_u_x:[0.344173901621,0.4] object_u_y:[0.311526493934,0.4] object_u_z:[0.82800316424,0.873818145449] object_v_x:[0.493112636578,0.55533820153] object_v_y:[-0.866446326835,-0.819250228831] object_v_z:[0.0781943545677,0.145039285443] X_3_u_x:[-0.51542950499,-0.450766875925] X_3_u_y:[0.854823887686,0.891765263411] X_3_u_z:[-0,0.0694706240192] X_3_v_x:[0.164045710977,0.228886476143] X_3_v_y:[0.056139188991,0.137779627271] X_3_v_z:[0.9636533012,0.982909891999] X_4_u_x:[0.649861118809,0.724045005886] X_4_u_y:[-0.43266715984,-0.377505733436] X_4_u_z:[0.576187945532,0.652068451844] X_4_v_x:[-0,0.0810593767939] X_4_v_y:[0.847568949879,0.873746817089] X_4_v_z:[0.485168392596,0.524452004729] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411936568,-0.999410875721] uni_v_palm_p12_z_0:[0.0342896657316,0.0343205750292] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-7.0756454169e-05,7.0756454169e-05] w2_palm_p12_z_0:[-0.00206042135227,0.00206042135227] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00206163370251,0.00206163370251] w1_p12_p13_y_1:[0.0342895928476,0.034320611473] w1_p12_p13_z_1:[0.999409813068,0.999411936667] w2_p12_p13_x_1:[-0.00498274183974,0.00498274183974] w2_p12_p13_y_1:[0.0342892400492,0.0343205858777] w2_p12_p13_z_1:[0.999399532407,0.999411936697] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00498274183974,0.00498274183974] w1_p13_p14_y_2:[0.0342892400492,0.0343205858777] w1_p13_p14_z_2:[0.999399532407,0.999411936697] w2_p13_p14_x_2:[-0.0103905076106,0.0103905076106] w2_p13_p14_y_2:[0.0342878146674,0.0343206075254] w2_p13_p14_z_2:[0.999358004642,0.999411937088] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-1,-0.995138824627] uni_v_palm_p32_z_6:[-0.098419759256,0] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.9151433554,0.957458124726] w2_palm_p32_y_6:[-0.0375932921545,0.000665458482836] w2_palm_p32_z_6:[0.295252334145,0.394705939001] cos_0_palm_p32_6:[0.998004520845,1] cos_1_palm_p32_6:[0.9151433554,0.957458124726] w1_p32_p33_x_7:[0.9151433554,0.957458124726] w1_p32_p33_y_7:[-0.0375932921545,0.000665458482836] w1_p32_p33_z_7:[0.295252334145,0.394705939001] w2_p32_p33_x_7:[0.752816372533,0.808713735542] w2_p32_p33_y_7:[-0.062750274542,1.00489112509e-11] w2_p32_p33_z_7:[0.587501477976,0.656081263347] cos_p32_p33_7:[0.922639066883,0.962243458449] w1_p33_p34_x_8:[0.986085270424,0.999531185226] w1_p33_p34_y_8:[-0.00304802242381,0.0138387804652] w1_p33_p34_z_8:[-0.154474582657,-0.0663789025927] w2_p33_p34_x_8:[0.961782908236,0.980879657724] w2_p33_p34_y_8:[-0.026681541253,1.00489112509e-11] w2_p33_p34_z_8:[0.194615254006,0.272508668214] cos_p33_p34_8:[0.922639066883,0.962243458449] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.996598108929] w2_palm_p40_y_9:[-0.0823656732322,3.82843494672e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.763545575563] uni_u_p40_p42_x_10:[-0.819149697375,-0.816363039322] uni_u_p40_p42_y_10:[-0.0674698163015,3.136061328e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0773358314148,4.14143862995e-11] uni_v_p40_p42_y_10:[0.996975270405,1] uni_v_p40_p42_z_10:[-0,0.00734983342052] w1_p40_p42_x_10:[-0.0823656732322,3.82843494672e-11] w1_p40_p42_y_10:[0.996598108929,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.515444280298,-0.445248036217] w2_p40_p42_y_10:[-0.046284584258,0.00221607162278] w2_p40_p42_z_10:[0.856438461695,0.895527998099] cos_0_p40_p42_10:[0.996761217133,1] cos_1_p40_p42_10:[0.877232895406,0.914915230711] w1_p42_p43_x_11:[-0.515444280298,-0.445248036217] w1_p42_p43_y_11:[-0.046284584258,0.00221607162278] w1_p42_p43_z_11:[0.856438461695,0.895527998099] w2_p42_p43_x_11:[0.118313722352,0.203466511623] w2_p42_p43_y_11:[-0,0.0146766326423] w2_p42_p43_z_11:[0.979056973723,0.992979894653] cos_p42_p43_11:[0.754885867764,0.812813797961] w1_p43_p44_x_12:[-0.618179630056,-0.547286076165] w1_p43_p44_y_12:[-0.0523846903686,3.45883110631e-05] w1_p43_p44_z_12:[0.785859642481,0.83687457743] w2_p43_p44_x_12:[-0,0.0945626505201] w2_p43_p44_y_12:[-0,0.00717176343369] w2_p43_p44_z_12:[0.995493046549,1] cos_p43_p44_12:[0.754885867764,0.812813797961] sph_w1_p34_X_3_x_13:[0.329330395222,0.406379915943] sph_w1_p34_X_3_y_13:[-3.99999111912e-11,0.092395533627] sph_w1_p34_X_3_z_13:[-0.943966331188,-0.909532063733] sph_w2_p34_X_3_x_13:[0.822479000777,0.868845166341] sph_w2_p34_X_3_y_13:[0.447681025754,0.511905234026] sph_w2_p34_X_3_z_13:[-0.268489431109,-0.189212964669] cos_p34_X_3_13:[0.5,0.627205197406] in_patch_X_3_object_u_14:[0.374999999996,0.437500000004] in_patch_X_3_object_v_14:[0.374999999996,0.437500000004] in_patch_X_3_object_l_14:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_15:[-0.990148533442,-0.969457309163] sph_w1_p44_X_4_y_15:[-0.0771339977662,4.80247707011e-05] sph_w1_p44_X_4_z_15:[0.140021004665,0.233618022108] sph_w2_p44_X_4_x_15:[-0.761427893391,-0.692776821969] sph_w2_p44_X_4_y_15:[-0.37194249049,-0.312573692318] sph_w2_p44_X_4_z_15:[0.554733898275,0.622592197799] cos_p44_X_4_15:[0.771803754545,0.884063993371] in_patch_X_4_object_u_16:[0.437499999996,0.500000000005] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] p14_r_x:[-4.58926102027,-4.01073897974] p14_r_y:[-36.8114862413,-36.8084449644] p14_r_z:[243.172034565,243.172487408] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }
   3 (err:2.33805 min:3.16454 tm:105):{ 241  p12_u_x:[-0.00206147766977,0.00206147766977] p12_u_y:[0.0342895928693,0.0343205751157] p12_u_z:[0.999409813204,0.999411936785] p12_v_x:[-0,0] p12_v_y:[-0.999411936568,-0.999410875721] p12_v_z:[0.0342896657316,0.0343205750292] p13_u_x:[-0.00498244775432,0.00498244775432] p13_u_y:[0.0342892400994,0.0343205966896] p13_u_z:[0.999399535027,0.999411936697] p13_v_x:[-0,0] p13_v_y:[-0.999411936568,-0.999410875721] p13_v_z:[0.0342896657316,0.0343205750292] p14_u_x:[-0.0103902928375,0.0103902928375] p14_u_y:[0.0342878147546,0.0343205751388] p14_u_z:[0.99935800307,0.999411937207] p14_v_x:[-0,0] p14_v_y:[-0.999411936568,-0.999410875721] p14_v_z:[0.0342896657316,0.0343205750292] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.392042066382,0.464891423425] p32_u_y:[-0.0777700900731,1.00388822023e-11] p32_u_z:[0.881929943399,0.916958828743] p32_v_x:[-0,0] p32_v_y:[-1,-0.996161438264] p32_v_z:[-0.087142465889,0] p33_u_x:[0.769892300188,0.802590657517] p33_u_y:[-0.0542983986097,1.00388822023e-11] p33_u_z:[0.595407985716,0.636325311363] p33_v_x:[-0,0] p33_v_y:[-1,-0.996161438264] p33_v_z:[-0.087142465889,0] p34_u_x:[0.961891843492,0.978658275361] p34_u_y:[-0.022627179852,1.00388822023e-11] p34_u_z:[0.205494477046,0.272508668214] p34_v_x:[-0,0] p34_v_y:[-1,-0.996161438264] p34_v_z:[-0.087142465889,0] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0708663599238,3.82843494672e-11] p40_v_y:[0.997475711959,1] p40_v_z:[-0,0] p42_u_x:[0.246136066695,0.315973028778] p42_u_y:[-0,0.0193417835432] p42_u_z:[0.948570478543,0.96923528449] p42_v_x:[-0.0664971742454,4.06279345176e-11] p42_v_y:[0.997759172151,1] p42_v_z:[-0,0.00632388252307] p43_u_x:[0.129019567053,0.201485397545] p43_u_y:[-0,0.0127626639167] p43_u_z:[0.979493090244,0.991758617216] p43_v_x:[-0.0664971742454,4.06279345176e-11] p43_v_y:[0.997759172151,1] p43_v_z:[-0,0.00632388252307] p44_u_x:[-0,0.0945626505201] p44_u_y:[-0,0.00617088849997] p44_u_z:[0.995499334282,1] p44_v_x:[-0.0664971742454,4.06279345176e-11] p44_v_y:[0.997759172151,1] p44_v_z:[-0,0.00632388252307] object_u_x:[0.347575048416,0.4] object_u_y:[0.311526493934,0.383638781756] object_u_z:[0.846641173487,0.876036509347] object_v_x:[0.458540783856,0.535918075553] object_v_y:[-0.882581042344,-0.831941573323] object_v_z:[0.0784678394417,0.145039285443] X_3_u_x:[-0.497721718262,-0.438730282372] X_3_u_y:[0.863842142347,0.898097898537] X_3_u_z:[0.0308639438489,0.129440479749] X_3_v_x:[0.183154414872,0.228886476143] X_3_v_y:[-0.0259641752099,0.0561391889922] X_3_v_z:[0.971832996183,0.982594184956] X_4_u_x:[0.646861996052,0.695436118548] X_4_u_y:[-0.432478639154,-0.377505733436] X_4_u_z:[0.607824129693,0.661390652716] X_4_v_x:[-0,0.067195598066] X_4_v_y:[0.848776738966,0.874636398306] X_4_v_z:[0.484414618798,0.524452004729] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411936568,-0.999410875721] uni_v_palm_p12_z_0:[0.0342896657316,0.0343205750292] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-7.07510990355e-05,7.07510990355e-05] w2_palm_p12_z_0:[-0.00206026541129,0.00206026541129] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00206147766977,0.00206147766977] w1_p12_p13_y_1:[0.0342895928693,0.0343205751157] w1_p12_p13_z_1:[0.999409813204,0.999411936785] w2_p12_p13_x_1:[-0.00498244775432,0.00498244775432] w2_p12_p13_y_1:[0.0342892400994,0.0343205966896] w2_p12_p13_z_1:[0.999399535027,0.999411936697] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00498244775432,0.00498244775432] w1_p13_p14_y_2:[0.0342892400994,0.0343205966896] w1_p13_p14_z_2:[0.999399535027,0.999411936697] w2_p13_p14_x_2:[-0.0103902928375,0.0103902928375] w2_p13_p14_y_2:[0.0342878147546,0.0343205751388] w2_p13_p14_z_2:[0.99935800307,0.999411937207] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-1,-0.996161438264] uni_v_palm_p32_z_6:[-0.087142465889,0] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.925238125545,0.956655334395] w2_palm_p32_y_6:[-0.0307343735295,0.000665458482836] w2_palm_p32_z_6:[0.295742707519,0.372142349668] cos_0_palm_p32_6:[0.998626315611,1] cos_1_palm_p32_6:[0.925238125545,0.956655334395] w1_p32_p33_x_7:[0.925238125545,0.956655334395] w1_p32_p33_y_7:[-0.0307343735295,0.000665458482836] w1_p32_p33_z_7:[0.295742707519,0.372142349668] w2_p32_p33_x_7:[0.769892300188,0.802590657517] w2_p32_p33_y_7:[-0.0542983986097,1.00388822023e-11] w2_p32_p33_z_7:[0.595407985716,0.636325311363] cos_p32_p33_7:[0.925157519175,0.954910124395] w1_p33_p34_x_8:[0.98795311534,0.99659920773] w1_p33_p34_y_8:[-0.00127091681146,0.0123628013119] w1_p33_p34_z_8:[-0.145045947594,-0.0927316593627] w2_p33_p34_x_8:[0.961891843492,0.978658275361] w2_p33_p34_y_8:[-0.022627179852,1.00388822023e-11] w2_p33_p34_z_8:[0.205494477046,0.272508668214] cos_p33_p34_8:[0.925157519175,0.954910124395] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.997475711959] w2_palm_p40_y_9:[-0.0708663599238,3.82843494672e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.755879984174] uni_u_p40_p42_x_10:[-0.819149697375,-0.817081927578] uni_u_p40_p42_y_10:[-0.0580501572851,3.136061328e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0664971742454,4.06279345176e-11] uni_v_p40_p42_y_10:[0.997759172151,1] uni_v_p40_p42_z_10:[-0,0.00632388252307] w1_p40_p42_x_10:[-0.0708663599238,3.82843494672e-11] w1_p40_p42_y_10:[0.997475711959,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.511308360398,-0.445861033497] w2_p40_p42_y_10:[-0.0383286697991,0.00179140440556] w2_p40_p42_z_10:[0.859039345568,0.895273944357] cos_0_p40_p42_10:[0.997591424806,1] cos_1_p40_p42_10:[0.877832271449,0.912594718322] w1_p42_p43_x_11:[-0.511308360398,-0.445861033497] w1_p42_p43_y_11:[-0.0383286697991,0.00179140440556] w1_p42_p43_z_11:[0.859039345568,0.895273944357] w2_p42_p43_x_11:[0.129019567053,0.201485397545] w2_p42_p43_y_11:[-0,0.0127626639167] w2_p42_p43_z_11:[0.979493090244,0.991758617216] cos_p42_p43_11:[0.757057113254,0.812516454322] w1_p43_p44_x_12:[-0.610048510912,-0.549390350292] w1_p43_p44_y_12:[-0.0441304587904,3.45883110631e-05] w1_p43_p44_z_12:[0.792466487022,0.835596159082] w2_p43_p44_x_12:[-0,0.0945626505201] w2_p43_p44_y_12:[-0,0.00617088849997] w2_p43_p44_z_12:[0.995499334282,1] cos_p43_p44_12:[0.757057113254,0.812516454322] sph_w1_p34_X_3_x_13:[0.339948658771,0.405863595411] sph_w1_p34_X_3_y_13:[-3.99999111912e-11,0.0819211508742] sph_w1_p34_X_3_z_13:[-0.940243512958,-0.910887594748] sph_w2_p34_X_3_x_13:[0.835279564743,0.879678645495] sph_w2_p34_X_3_y_13:[0.434713659629,0.497834192219] sph_w2_p34_X_3_z_13:[-0.232626944451,-0.191026762936] cos_p34_X_3_13:[0.5,0.591678499741] in_patch_X_3_object_u_14:[0.437499999996,0.500000000005] in_patch_X_3_object_v_14:[0.437499999996,0.500000000005] in_patch_X_3_object_l_14:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_15:[-0.990148533442,-0.970239644748] sph_w1_p44_X_4_y_15:[-0.0663245930067,4.80247707011e-05] sph_w1_p44_X_4_z_15:[0.140021004665,0.233509406754] sph_w2_p44_X_4_x_15:[-0.76142375138,-0.71798289452] sph_w2_p44_X_4_y_15:[-0.364664261067,-0.308034367853] sph_w2_p44_X_4_z_15:[0.558184685802,0.592959376465] cos_p44_X_4_15:[0.793635230449,0.881021445607] in_patch_X_4_object_u_16:[0.437499999996,0.500000000005] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990976,9.71993905446] p14_r_x:[-4.58924161868,-4.01075838132] p14_r_y:[-36.8114865815,-36.8084471058] p14_r_z:[243.172035091,243.17248742] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }
   4 (err:2.60377 min:3.13743 tm:105):{ 241  p12_u_x:[-0.00206111799494,0.00206111799494] p12_u_y:[0.034289592884,0.0343205859027] p12_u_z:[0.999409813947,0.999411936667] p12_v_x:[-0,0] p12_v_y:[-0.999411936568,-0.999410875721] p12_v_z:[0.0342896657316,0.0343205750292] p13_u_x:[-0.00498276539632,0.00498276539632] p13_u_y:[0.0342892400559,0.0343205751035] p13_u_z:[0.999399533406,0.999411936816] p13_v_x:[-0,0] p13_v_y:[-0.999411936568,-0.999410875721] p13_v_z:[0.0342896657316,0.0343205750292] p14_u_x:[-0.0103904616087,0.0103904616087] p14_u_y:[0.0342878146838,0.0343206075254] p14_u_z:[0.999358008025,0.999411937088] p14_v_x:[-0,0] p14_v_y:[-0.999411936568,-0.999410875721] p14_v_z:[0.0342896657316,0.0343205750292] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.368736449159,0.464891423425] p32_u_y:[-0.0856563405426,1.00458188003e-11] p32_u_z:[0.881248784488,0.928715411779] p32_v_x:[-0,0] p32_v_y:[-1,-0.995451487894] p32_v_z:[-0.0951391781325,0] p33_u_x:[0.754043463033,0.808465682546] p33_u_y:[-0.0604979895103,1.00458188003e-11] p33_u_z:[0.587888277595,0.654811260895] p33_v_x:[-0,0] p33_v_y:[-1,-0.995451487894] p33_v_z:[-0.0951391781325,0] p34_u_x:[0.961805804232,0.980879657724] p34_u_y:[-0.0257643730953,1.00458188003e-11] p34_u_z:[0.194615254006,0.272508668214] p34_v_x:[-0,0] p34_v_y:[-1,-0.995451487894] p34_v_z:[-0.0951391781325,0] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0793717240222,3.82843494672e-11] p40_v_y:[0.996832012722,1] p40_v_z:[-0,0] p42_u_x:[0.241461986851,0.315973028778] p42_u_y:[-0,0.0221700733021] p42_u_z:[0.948507670181,0.970410278662] p42_v_x:[-0.0745149117633,4.14143862995e-11] p42_v_y:[0.99718614013,1] p42_v_z:[-0,0.00708869246899] p43_u_x:[0.118352864561,0.204034972206] p43_u_y:[-0,0.0142233852938] p43_u_z:[0.978939328851,0.992978544787] p43_v_x:[-0.0745149117633,4.14143862995e-11] p43_v_y:[0.99718614013,1] p43_v_z:[-0,0.00708869246899] p44_u_x:[-0,0.0945626505201] p44_u_y:[-0,0.00691579000969] p44_u_z:[0.995494400498,1] p44_v_x:[-0.0745149117633,4.14143862995e-11] p44_v_y:[0.99718614013,1] p44_v_z:[-0,0.00708869246899] object_u_x:[0.345247865089,0.4] object_u_y:[0.311526493934,0.4] object_u_z:[0.828023308293,0.873254476318] object_v_x:[0.493112636578,0.555290856763] object_v_y:[-0.866446326835,-0.81927943408] object_v_z:[0.0782507003011,0.145039285443] X_3_u_x:[-0.51542950499,-0.450822644044] X_3_u_y:[0.854828102626,0.891747321667] X_3_u_z:[-0,0.069442588373] X_3_v_x:[0.165834832413,0.228886476143] X_3_v_y:[0.056139188991,0.137779564143] X_3_v_z:[0.963653307507,0.982473210621] X_4_u_x:[0.651591025519,0.723977127918] X_4_u_y:[-0.432635472537,-0.377505733436] X_4_u_z:[0.576239816334,0.652048634185] X_4_v_x:[-0,0.0809993156513] X_4_v_y:[0.847571780907,0.873711175126] X_4_v_z:[0.485232466758,0.524452004729] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411936568,-0.999410875721] uni_v_palm_p12_z_0:[0.0342896657316,0.0343205750292] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-7.07387547886e-05,7.07387547886e-05] w2_palm_p12_z_0:[-0.00205990593759,0.00205990594797] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00206111799494,0.00206111799494] w1_p12_p13_y_1:[0.034289592884,0.0343205859027] w1_p12_p13_z_1:[0.999409813947,0.999411936667] w2_p12_p13_x_1:[-0.00498276539632,0.00498276539632] w2_p12_p13_y_1:[0.0342892400559,0.0343205751035] w2_p12_p13_z_1:[0.999399533406,0.999411936816] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00498276539632,0.00498276539632] w1_p13_p14_y_2:[0.0342892400559,0.0343205751035] w1_p13_p14_z_2:[0.999399533406,0.999411936816] w2_p13_p14_x_2:[-0.0103904616087,0.0103904616087] w2_p13_p14_y_2:[0.0342878146838,0.0343206075254] w2_p13_p14_z_2:[0.999358008025,0.999411937088] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-1,-0.995451487894] uni_v_palm_p32_z_6:[-0.0951391781325,0] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.914995963269,0.957378069089] w2_palm_p32_y_6:[-0.0362413626436,0.000665458482836] w2_palm_p32_z_6:[0.295386124631,0.395546498958] cos_0_palm_p32_6:[0.998200575754,1] cos_1_palm_p32_6:[0.914995963269,0.957378069089] w1_p32_p33_x_7:[0.914995963269,0.957378069089] w1_p32_p33_y_7:[-0.0362413626436,0.000665458482836] w1_p32_p33_z_7:[0.295386124631,0.395546498958] w2_p32_p33_x_7:[0.754043463033,0.808465682546] w2_p32_p33_y_7:[-0.0604979895103,1.00458188003e-11] w2_p32_p33_z_7:[0.587888277595,0.654811260895] cos_p32_p33_7:[0.922910131551,0.962296347588] w1_p33_p34_x_8:[0.986245488772,0.999300535752] w1_p33_p34_y_8:[-0.00288988680261,0.0134658672616] w1_p33_p34_z_8:[-0.154133651364,-0.0682911562902] w2_p33_p34_x_8:[0.961805804232,0.980879657724] w2_p33_p34_y_8:[-0.0257643730953,1.00458188003e-11] w2_p33_p34_z_8:[0.194615254006,0.272508668214] cos_p33_p34_8:[0.922910131551,0.962296347588] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.996832012722] w2_palm_p40_y_9:[-0.0793717240222,3.82843494672e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.761554085488] uni_u_p40_p42_x_10:[-0.819149697375,-0.816554641543] uni_u_p40_p42_y_10:[-0.0650173237122,3.136061328e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0745149117633,4.14143862995e-11] uni_v_p40_p42_y_10:[0.99718614013,1] uni_v_p40_p42_z_10:[-0,0.00708869246899] w1_p40_p42_x_10:[-0.0793717240222,3.82843494672e-11] w1_p40_p42_y_10:[0.996832012722,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.515444280298,-0.445395678149] w2_p40_p42_y_10:[-0.0445743100144,0.00213916517027] w2_p40_p42_z_10:[0.856470639005,0.895484764747] cos_0_p40_p42_10:[0.996977878571,1] cos_1_p40_p42_10:[0.877380591214,0.914843178123] w1_p42_p43_x_11:[-0.515444280298,-0.445395678149] w1_p42_p43_y_11:[-0.0445743100144,0.00213916517027] w1_p42_p43_z_11:[0.856470639005,0.895484764747] w2_p42_p43_x_11:[0.118352864561,0.204034972206] w2_p42_p43_y_11:[-0,0.0142233852938] w2_p42_p43_z_11:[0.978939328851,0.992978544787] cos_p42_p43_11:[0.754895661198,0.812787489712] w1_p43_p44_x_12:[-0.618173209033,-0.546925226151] w1_p43_p44_y_12:[-0.0504441028664,3.45883110631e-05] w1_p43_p44_z_12:[0.785876021414,0.837200270667] w2_p43_p44_x_12:[-0,0.0945626505201] w2_p43_p44_y_12:[-0,0.00691579000969] w2_p43_p44_z_12:[0.995494400498,1] cos_p43_p44_12:[0.754895661198,0.812787489712] sph_w1_p34_X_3_x_13:[0.329374291225,0.406272900147] sph_w1_p34_X_3_y_13:[-3.99999111912e-11,0.0893762607651] sph_w1_p34_X_3_z_13:[-0.943966331188,-0.909856783761] sph_w2_p34_X_3_x_13:[0.822488005671,0.868326475259] sph_w2_p34_X_3_y_13:[0.447697313586,0.511867202302] sph_w2_p34_X_3_z_13:[-0.268463626017,-0.191278539059] cos_p34_X_3_13:[0.5,0.625578781682] in_patch_X_3_object_u_14:[0.437499999996,0.500000000005] in_patch_X_3_object_v_14:[0.374999999996,0.437500000004] in_patch_X_3_object_l_14:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_15:[-0.990148533442,-0.969666942322] sph_w1_p44_X_4_y_15:[-0.0743214912508,4.80247707011e-05] sph_w1_p44_X_4_z_15:[0.140021004665,0.233592199548] sph_w2_p44_X_4_x_15:[-0.759679706911,-0.692786205226] sph_w2_p44_X_4_y_15:[-0.371876788801,-0.312606514156] sph_w2_p44_X_4_z_15:[0.556658262551,0.622558152387] cos_p44_X_4_15:[0.77181822591,0.882673631934] in_patch_X_4_object_u_16:[0.437499999996,0.500000000005] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] p14_r_x:[-4.58922676199,-4.01077323802] p14_r_y:[-36.8114879682,-36.8084470224] p14_r_z:[243.172034902,243.17248743] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }
   5 (err:2.62657 min:3.15316 tm:106):{ 241  p12_u_x:[-0.00206163370251,0.00206163370251] p12_u_y:[0.0342895928476,0.034320611473] p12_u_z:[0.999409813068,0.999411936667] p12_v_x:[-0,0] p12_v_y:[-0.999411936568,-0.999410875721] p12_v_z:[0.0342896657316,0.0343205750292] p13_u_x:[-0.00498274183974,0.00498274183974] p13_u_y:[0.0342892400492,0.0343205858777] p13_u_z:[0.999399532407,0.999411936697] p13_v_x:[-0,0] p13_v_y:[-0.999411936568,-0.999410875721] p13_v_z:[0.0342896657316,0.0343205750292] p14_u_x:[-0.0103905076106,0.0103905076106] p14_u_y:[0.0342878146674,0.0343206075254] p14_u_z:[0.999358004642,0.999411937088] p14_v_x:[-0,0] p14_v_y:[-0.999411936568,-0.999410875721] p14_v_z:[0.0342896657316,0.0343205750292] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.36860769449,0.464891423425] p32_u_y:[-0.085767660522,1.00489112509e-11] p32_u_z:[0.881101843527,0.928776734803] p32_v_x:[-0,0] p32_v_y:[-1,-0.995293932104] p32_v_z:[-0.0952794403954,0] p33_u_x:[0.753745518954,0.808713735542] p33_u_y:[-0.0606909525673,1.00489112509e-11] p33_u_z:[0.587543421961,0.655018557167] p33_v_x:[-0,0] p33_v_y:[-1,-0.995293932104] p33_v_z:[-0.0952794403954,0] p34_u_x:[0.961793345166,0.980879657724] p34_u_y:[-0.0259225628588,1.00489112509e-11] p34_u_z:[0.194615254006,0.272508668214] p34_v_x:[-0,0] p34_v_y:[-1,-0.995293932104] p34_v_z:[-0.0952794403954,0] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0796060657141,3.82843494672e-11] p40_v_y:[0.996712101386,1] p40_v_z:[-0,0] p42_u_x:[0.241461986851,0.315973028778] p42_u_y:[-0,0.0222723324567] p42_u_z:[0.94849817048,0.970410278662] p42_v_x:[-0.0746643752738,4.14143862995e-11] p42_v_y:[0.997079329519,1] p42_v_z:[-0,0.00722323818253] p43_u_x:[0.11832549511,0.204107772359] p43_u_y:[-0,0.0143180180942] p43_u_z:[0.978954410358,0.992979894653] p43_v_x:[-0.0746643752738,4.14143862995e-11] p43_v_y:[0.997079329519,1] p43_v_z:[-0,0.00722323818253] p44_u_x:[-0,0.0945626505201] p44_u_y:[-0,0.00704776534732] p44_u_z:[0.995493492826,1] p44_v_x:[-0.0746643752738,4.14143862995e-11] p44_v_y:[0.997079329519,1] p44_v_z:[-0,0.00722323818253] object_u_x:[0.345082047084,0.4] object_u_y:[0.311526493934,0.4] object_u_z:[0.82800316424,0.873317265222] object_v_x:[0.493112636578,0.55533820153] object_v_y:[-0.866446326835,-0.819250228831] object_v_z:[0.0781943545677,0.145039285443] X_3_u_x:[-0.51542950499,-0.450766875806] X_3_u_y:[0.854823887686,0.891765263411] X_3_u_z:[-0,0.0694706240192] X_3_v_x:[0.165592366469,0.228886476143] X_3_v_y:[0.056139188991,0.137779627271] X_3_v_z:[0.9636533012,0.982505027707] X_4_u_x:[0.651352411369,0.724045005886] X_4_u_y:[-0.43266715984,-0.377505733436] X_4_u_z:[0.576187945532,0.652068451844] X_4_v_x:[-0,0.0810593767939] X_4_v_y:[0.847568949879,0.873746817089] X_4_v_z:[0.485168392596,0.524452004729] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411936568,-0.999410875721] uni_v_palm_p12_z_0:[0.0342896657316,0.0343205750292] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-7.0756454169e-05,7.0756454169e-05] w2_palm_p12_z_0:[-0.00206042134189,0.00206042135227] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00206163370251,0.00206163370251] w1_p12_p13_y_1:[0.0342895928476,0.034320611473] w1_p12_p13_z_1:[0.999409813068,0.999411936667] w2_p12_p13_x_1:[-0.00498274183974,0.00498274183974] w2_p12_p13_y_1:[0.0342892400492,0.0343205858777] w2_p12_p13_z_1:[0.999399532407,0.999411936697] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00498274183974,0.00498274183974] w1_p13_p14_y_2:[0.0342892400492,0.0343205858777] w1_p13_p14_z_2:[0.999399532407,0.999411936697] w2_p13_p14_x_2:[-0.0103905076106,0.0103905076106] w2_p13_p14_y_2:[0.0342878146674,0.0343206075254] w2_p13_p14_z_2:[0.999358004642,0.999411937088] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-1,-0.995293932104] uni_v_palm_p32_z_6:[-0.0952794403954,0] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.914787354437,0.957458124727] w2_palm_p32_y_6:[-0.036390493779,0.000665458482836] w2_palm_p32_z_6:[0.295305485093,0.395702851634] cos_0_palm_p32_6:[0.998048096399,1] cos_1_palm_p32_6:[0.914787354437,0.957458124727] w1_p32_p33_x_7:[0.914787354437,0.957458124727] w1_p32_p33_y_7:[-0.036390493779,0.000665458482836] w1_p32_p33_z_7:[0.295305485093,0.395702851634] w2_p32_p33_x_7:[0.753745518954,0.808713735542] w2_p32_p33_y_7:[-0.0606909525673,1.00489112509e-11] w2_p32_p33_z_7:[0.587543421961,0.655018557167] cos_p32_p33_7:[0.922644753369,0.962412106633] w1_p33_p34_x_8:[0.986085270424,0.999365319297] w1_p33_p34_y_8:[-0.002993890025,0.0135899725968] w1_p33_p34_z_8:[-0.154474582657,-0.0678732088555] w2_p33_p34_x_8:[0.961793345166,0.980879657724] w2_p33_p34_y_8:[-0.0259225628588,1.00489112509e-11] w2_p33_p34_z_8:[0.194615254006,0.272508668214] cos_p33_p34_8:[0.922644753369,0.962412106633] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.996712101386] w2_palm_p40_y_9:[-0.0796060657141,3.82843494672e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.761674843213] uni_u_p40_p42_x_10:[-0.819149697375,-0.816456416209] uni_u_p40_p42_y_10:[-0.0652092846383,3.136061328e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0746643752738,4.14143862995e-11] uni_v_p40_p42_y_10:[0.997079329519,1] uni_v_p40_p42_z_10:[-0,0.00722323818253] w1_p40_p42_x_10:[-0.0796060657141,3.82843494672e-11] w1_p40_p42_y_10:[0.996712101386,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.515444280298,-0.445320624246] w2_p40_p42_y_10:[-0.044858425591,0.00221607162278] w2_p40_p42_z_10:[0.856438461695,0.895513673695] cos_0_p40_p42_10:[0.996761906874,1] cos_1_p40_p42_10:[0.877239585961,0.914912404142] w1_p42_p43_x_11:[-0.515444280298,-0.445320624246] w1_p42_p43_y_11:[-0.044858425591,0.00221607162278] w1_p42_p43_z_11:[0.856438461695,0.895513673695] w2_p42_p43_x_11:[0.11832549511,0.204107772359] w2_p42_p43_y_11:[-0,0.0143180180942] w2_p42_p43_z_11:[0.978954410358,0.992979894653] cos_p42_p43_11:[0.754885867764,0.812805550503] w1_p43_p44_x_12:[-0.618179630056,-0.546840875164] w1_p43_p44_y_12:[-0.0506886193119,3.45883110631e-05] w1_p43_p44_z_12:[0.785859642481,0.837253253578] w2_p43_p44_x_12:[-0,0.0945626505201] w2_p43_p44_y_12:[-0,0.00704776534732] w2_p43_p44_z_12:[0.995493492826,1] cos_p43_p44_12:[0.754885867764,0.812805550503] sph_w1_p34_X_3_x_13:[0.329330395222,0.406338521172] sph_w1_p34_X_3_y_13:[-3.99999111912e-11,0.0895367267898] sph_w1_p34_X_3_z_13:[-0.943966331188,-0.909695930068] sph_w2_p34_X_3_x_13:[0.822479000777,0.868383768684] sph_w2_p34_X_3_y_13:[0.447681025754,0.511905234026] sph_w2_p34_X_3_z_13:[-0.268489431109,-0.191026548978] cos_p34_X_3_13:[0.5,0.6258127908] in_patch_X_3_object_u_14:[0.374999999996,0.437500000004] in_patch_X_3_object_v_14:[0.374999999996,0.437500000004] in_patch_X_3_object_l_14:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_15:[-0.990148533442,-0.969560561132] sph_w1_p44_X_4_y_15:[-0.0744888935722,4.80247707011e-05] sph_w1_p44_X_4_z_15:[0.140021004665,0.233608787394] sph_w2_p44_X_4_x_15:[-0.759879523827,-0.692776821969] sph_w2_p44_X_4_y_15:[-0.37194249049,-0.312573692318] sph_w2_p44_X_4_z_15:[0.556409805514,0.622592197799] cos_p44_X_4_15:[0.771803754545,0.882750206923] in_patch_X_4_object_u_16:[0.374999999996,0.437500000004] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] p14_r_x:[-4.58926102027,-4.01073897974] p14_r_y:[-36.8114862413,-36.8084449644] p14_r_z:[243.172034565,243.172487408] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }
   6 (err:2.62465 min:3.14472 tm:106):{ 241  p12_u_x:[-0.00206163370251,0.00206163370251] p12_u_y:[0.0342895928582,0.0343205751309] p12_u_z:[0.999409813068,0.999411936785] p12_v_x:[-0,0] p12_v_y:[-0.999411936568,-0.999410875721] p12_v_z:[0.0342896657316,0.0343205750292] p13_u_x:[-0.00498281629534,0.00498281629534] p13_u_y:[0.0342892400472,0.0343205751163] p13_u_z:[0.999399532981,0.999411936816] p13_v_x:[-0,0] p13_v_y:[-0.999411936568,-0.999410875721] p13_v_z:[0.0342896657316,0.0343205750292] p14_u_x:[-0.0103904807483,0.0103904807483] p14_u_y:[0.0342878146769,0.0343206075254] p14_u_z:[0.999358005329,0.999411937088] p14_v_x:[-0,0] p14_v_y:[-0.999411936568,-0.999410875721] p14_v_z:[0.0342896657316,0.0343205750292] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.368626862982,0.464891423425] p32_u_y:[-0.086302289296,1.00494935145e-11] p32_u_z:[0.881050008993,0.928634255413] p32_v_x:[-0,0] p32_v_y:[-1,-0.995233476012] p32_v_z:[-0.0959354985077,0] p33_u_x:[0.754573104126,0.808702420815] p33_u_y:[-0.0610055051297,1.00494935145e-11] p33_u_z:[0.58749577643,0.654030470493] p33_v_x:[-0,0] p33_v_y:[-1,-0.995233476012] p33_v_z:[-0.0959354985077,0] p34_u_x:[0.961789127925,0.980879657724] p34_u_y:[-0.0260840941763,1.00494935145e-11] p34_u_z:[0.194615254006,0.272508668214] p34_v_x:[-0,0] p34_v_y:[-1,-0.995233476012] p34_v_z:[-0.0959354985077,0] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0799184244963,3.82843494672e-11] p40_v_y:[0.996689022437,1] p40_v_z:[-0,0] p42_u_x:[0.241461986851,0.315973028778] p42_u_y:[-0,0.0223869905144] p42_u_z:[0.948495544804,0.970410278662] p42_v_x:[-0.074959966452,4.14143862995e-11] p42_v_y:[0.997058790314,1] p42_v_z:[-0,0.00724850076926] p43_u_x:[0.118320418779,0.204238370575] p43_u_y:[-0,0.0144232502531] p43_u_z:[0.978925050603,0.992980527762] p43_v_x:[-0.074959966452,4.14143862995e-11] p43_v_y:[0.997058790314,1] p43_v_z:[-0,0.00724850076926] p44_u_x:[-0,0.0945626505201] p44_u_y:[-0,0.00707255542234] p44_u_z:[0.995493312314,1] p44_v_x:[-0.074959966452,4.14143862995e-11] p44_v_y:[0.997058790314,1] p44_v_z:[-0,0.00724850076926] object_u_x:[0.345754860911,0.4] object_u_y:[0.311526493934,0.4] object_u_z:[0.828019470996,0.872954537672] object_v_x:[0.493112636578,0.555298057763] object_v_y:[-0.866442708298,-0.81927645237] object_v_z:[0.0782397857316,0.145039285443] X_3_u_x:[-0.51542950499,-0.450811632582] X_3_u_y:[0.854828064544,0.891750959905] X_3_u_z:[-0,0.0694478757275] X_3_v_x:[0.166742807516,0.228886476143] X_3_v_y:[0.056139188991,0.137779425911] X_3_v_z:[0.963653323302,0.982226698164] X_4_u_x:[0.652438675654,0.723990583095] X_4_u_y:[-0.432632639092,-0.377505733436] X_4_u_z:[0.576236592324,0.652048100771] X_4_v_x:[-0,0.0810033685819] X_4_v_y:[0.847573698139,0.873717726321] X_4_v_z:[0.485222157281,0.524452004729] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411936568,-0.999410875721] uni_v_palm_p12_z_0:[0.0342896657316,0.0343205750292] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-7.0756454169e-05,7.0756454169e-05] w2_palm_p12_z_0:[-0.00206042135227,0.00206042134189] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00206163370251,0.00206163370251] w1_p12_p13_y_1:[0.0342895928582,0.0343205751309] w1_p12_p13_z_1:[0.999409813068,0.999411936785] w2_p12_p13_x_1:[-0.00498281629534,0.00498281629534] w2_p12_p13_y_1:[0.0342892400472,0.0343205751163] w2_p12_p13_z_1:[0.999399532981,0.999411936816] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00498281629534,0.00498281629534] w1_p13_p14_y_2:[0.0342892400472,0.0343205751163] w1_p13_p14_z_2:[0.999399532981,0.999411936816] w2_p13_p14_x_2:[-0.0103904807483,0.0103904807483] w2_p13_p14_y_2:[0.0342878146769,0.0343206075254] w2_p13_p14_z_2:[0.999358005329,0.999411937088] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-1,-0.995233476012] uni_v_palm_p32_z_6:[-0.0959354985077,0] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.914762856137,0.957474154436] w2_palm_p32_y_6:[-0.0365376132936,0.000665458482836] w2_palm_p32_z_6:[0.295282171254,0.395598908033] cos_0_palm_p32_6:[0.998010958608,1] cos_1_palm_p32_6:[0.914762856137,0.957474154436] w1_p32_p33_x_7:[0.914762856137,0.957474154436] w1_p32_p33_y_7:[-0.0365376132936,0.000665458482836] w1_p32_p33_z_7:[0.295282171254,0.395598908033] w2_p32_p33_x_7:[0.754573104126,0.808702420815] w2_p32_p33_y_7:[-0.0610055051297,1.00494935145e-11] w2_p32_p33_z_7:[0.58749577643,0.654030470493] cos_p32_p33_7:[0.922675687858,0.96239696247] w1_p33_p34_x_8:[0.986066744726,0.999258566472] w1_p33_p34_y_8:[-0.0029272463038,0.0137554055939] w1_p33_p34_z_8:[-0.154482509071,-0.0691201187994] w2_p33_p34_x_8:[0.961789127925,0.980879657724] w2_p33_p34_y_8:[-0.0260840941763,1.00494935145e-11] w2_p33_p34_z_8:[0.194615254006,0.272508668214] cos_p33_p34_8:[0.922675687858,0.96239696247] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.996689022437] w2_palm_p40_y_9:[-0.0799184244963,3.82843494672e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.761883116032] uni_u_p40_p42_x_10:[-0.819149697375,-0.816437511094] uni_u_p40_p42_y_10:[-0.0654651532402,3.136061328e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.074959966452,4.14143862995e-11] uni_v_p40_p42_y_10:[0.997058790314,1] uni_v_p40_p42_z_10:[-0,0.00724850076926] w1_p40_p42_x_10:[-0.0799184244963,3.82843494672e-11] w1_p40_p42_y_10:[0.996689022437,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.515444280298,-0.445300047125] w2_p40_p42_y_10:[-0.0450027257117,0.00222286542682] w2_p40_p42_z_10:[0.856435175014,0.895519503866] cos_0_p40_p42_10:[0.996741960081,1] cos_1_p40_p42_10:[0.877224840732,0.91491956778] w1_p42_p43_x_11:[-0.515444280298,-0.445300047125] w1_p42_p43_y_11:[-0.0450027257117,0.00222286542682] w1_p42_p43_z_11:[0.856435175014,0.895519503866] w2_p42_p43_x_11:[0.118320418779,0.204238370575] w2_p42_p43_y_11:[-0,0.0144232502531] w2_p42_p43_z_11:[0.978925050603,0.992980527762] cos_p42_p43_11:[0.754874430802,0.812813807928] w1_p43_p44_x_12:[-0.618186667511,-0.546721155629] w1_p43_p44_y_12:[-0.0508542165045,3.45883110631e-05] w1_p43_p44_z_12:[0.785852385441,0.837328595353] w2_p43_p44_x_12:[-0,0.0945626505201] w2_p43_p44_y_12:[-0,0.00707255542234] w2_p43_p44_z_12:[0.995493312314,1] cos_p43_p44_12:[0.754874430802,0.812813807928] sph_w1_p34_X_3_x_13:[0.329322083811,0.406358251941] sph_w1_p34_X_3_y_13:[-3.99999111912e-11,0.0901951365872] sph_w1_p34_X_3_z_13:[-0.943966331188,-0.909637372436] sph_w2_p34_X_3_x_13:[0.822486442476,0.868056036332] sph_w2_p34_X_3_y_13:[0.447693935532,0.511874423143] sph_w2_p34_X_3_z_13:[-0.268469116013,-0.192345679882] cos_p34_X_3_13:[0.5,0.626067831601] in_patch_X_3_object_u_14:[0.437499999996,0.500000000005] in_patch_X_3_object_v_14:[0.374999999996,0.437500000004] in_patch_X_3_object_l_14:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_15:[-0.990148533442,-0.969540092957] sph_w1_p44_X_4_y_15:[-0.0747832844851,4.80247707011e-05] sph_w1_p44_X_4_z_15:[0.140021004665,0.233611768649] sph_w2_p44_X_4_x_15:[-0.758773583252,-0.692784599469] sph_w2_p44_X_4_y_15:[-0.371886463289,-0.312599656772] sph_w2_p44_X_4_z_15:[0.557646790489,0.622565671359] cos_p44_X_4_15:[0.771817134658,0.882101543775] in_patch_X_4_object_u_16:[0.437499999996,0.500000000005] in_patch_X_4_object_v_16:[0.374999999996,0.437500000004] in_patch_X_4_object_l_16:[9.71993866774,9.72381781325] p14_r_x:[-4.58926325393,-4.01073674607] p14_r_y:[-36.8114865731,-36.8084477526] p14_r_z:[243.172035024,243.17248742] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }
   7 (err:2.63135 min:3.14435 tm:106):{ 241  p12_u_x:[-0.00206163370251,0.00206163370251] p12_u_y:[0.0342895928476,0.034320611473] p12_u_z:[0.999409813068,0.999411936667] p12_v_x:[-0,0] p12_v_y:[-0.999411936568,-0.999410875721] p12_v_z:[0.0342896657316,0.0343205750292] p13_u_x:[-0.00498281629534,0.00498281629534] p13_u_y:[0.0342892400365,0.0343206074969] p13_u_z:[0.9993995331,0.999411936697] p13_v_x:[-0,0] p13_v_y:[-0.999411936568,-0.999410875721] p13_v_z:[0.0342896657316,0.0343205750292] p14_u_x:[-0.0103904807483,0.0103904807483] p14_u_y:[0.0342878146769,0.0343206075254] p14_u_z:[0.999358005329,0.999411937088] p14_v_x:[-0,0] p14_v_y:[-0.999411936568,-0.999410875721] p14_v_z:[0.0342896657316,0.0343205750292] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.369575403803,0.464891423425] p32_u_y:[-0.0892388841101,1.00494935145e-11] p32_u_z:[0.880909216772,0.928233268366] p32_v_x:[-0,0] p32_v_y:[-1,-0.995076993651] p32_v_z:[-0.0990850081792,0] p33_u_x:[0.753642217637,0.808702420815] p33_u_y:[-0.0630684215311,1.00494935145e-11] p33_u_z:[0.587453627159,0.655096127023] p33_v_x:[-0,0] p33_v_y:[-1,-0.995076993651] p33_v_z:[-0.0990850081792,0] p34_u_x:[0.961778609231,0.980879657724] p34_u_y:[-0.0268448663913,1.00494935145e-11] p34_u_z:[0.194615254006,0.272508668214] p34_v_x:[-0,0] p34_v_y:[-1,-0.995076993651] p34_v_z:[-0.0990850081792,0] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0826856424166,3.82843494672e-11] p40_v_y:[0.996574362861,1] p40_v_z:[-0,0] p42_u_x:[0.241461986851,0.315973028778] p42_u_y:[-0,0.0230956310577] p42_u_z:[0.948486959981,0.970410278662] p42_v_x:[-0.0776387929698,4.14143862995e-11] p42_v_y:[0.996954124219,1] p42_v_z:[-0,0.00737544531805] p43_u_x:[0.118307246752,0.203594397047] p43_u_y:[-0,0.0147825227076] p43_u_z:[0.979028091749,0.992980527762] p43_v_x:[-0.0776387929698,4.14143862995e-11] p43_v_y:[0.996954124219,1] p43_v_z:[-0,0.00737544531805] p44_u_x:[-0,0.0945626505201] p44_u_y:[-0,0.0071968993171] p44_u_z:[0.995492863195,1] p44_v_x:[-0.0776387929698,4.14143862995e-11] p44_v_y:[0.996954124219,1] p44_v_z:[-0,0.00737544531805] object_u_x:[0.344844784701,0.4] object_u_y:[0.311526493934,0.4] object_u_z:[0.828019470996,0.87345561692] object_v_x:[0.493112636578,0.555298057763] object_v_y:[-0.866442708298,-0.81927645237] object_v_z:[0.0782397857316,0.145039285443] X_3_u_x:[-0.51542950499,-0.450811632575] X_3_u_y:[0.854828064544,0.891750959905] X_3_u_z:[-0,0.0694478757275] X_3_v_x:[0.165199671952,0.228886476143] X_3_v_y:[0.056139188991,0.137779425911] X_3_v_z:[0.963653323302,0.98263165592] X_4_u_x:[0.650944177795,0.723990583095] X_4_u_y:[-0.432632639092,-0.377505733436] X_4_u_z:[0.576236592324,0.652048100771] X_4_v_x:[-0,0.0810033685819] X_4_v_y:[0.847573698139,0.873717726321] X_4_v_z:[0.485222157281,0.524452004729] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411936568,-0.999410875721] uni_v_palm_p12_z_0:[0.0342896657316,0.0343205750292] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-7.0756454169e-05,7.0756454169e-05] w2_palm_p12_z_0:[-0.00206042134189,0.00206042135227] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00206163370251,0.00206163370251] w1_p12_p13_y_1:[0.0342895928476,0.034320611473] w1_p12_p13_z_1:[0.999409813068,0.999411936667] w2_p12_p13_x_1:[-0.00498281629534,0.00498281629534] w2_p12_p13_y_1:[0.0342892400365,0.0343206074969] w2_p12_p13_z_1:[0.9993995331,0.999411936697] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00498281629534,0.00498281629534] w1_p13_p14_y_2:[0.0342892400365,0.0343206074969] w1_p13_p14_z_2:[0.9993995331,0.999411936697] w2_p13_p14_x_2:[-0.0103904807483,0.0103904807483] w2_p13_p14_y_2:[0.0342878146769,0.0343206075254] w2_p13_p14_z_2:[0.999358005329,0.999411937088] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-1,-0.995076993651] uni_v_palm_p32_z_6:[-0.0990850081792,0] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.915125484673,0.957474154435] w2_palm_p32_y_6:[-0.0377422908852,0.000665458482836] w2_palm_p32_z_6:[0.295228670647,0.39462250246] cos_0_palm_p32_6:[0.997966335173,1] cos_1_palm_p32_6:[0.915125484673,0.957474154435] w1_p32_p33_x_7:[0.915125484673,0.957474154435] w1_p32_p33_y_7:[-0.0377422908852,0.000665458482836] w1_p32_p33_z_7:[0.295228670647,0.39462250246] w2_p32_p33_x_7:[0.753642217637,0.808702420815] w2_p32_p33_y_7:[-0.0630684215311,1.00494935145e-11] w2_p32_p33_z_7:[0.587453627159,0.655096127023] cos_p32_p33_7:[0.922669779378,0.96222895807] w1_p33_p34_x_8:[0.986066744726,0.999425830999] w1_p33_p34_y_8:[-0.00298215503279,0.0140055350862] w1_p33_p34_z_8:[-0.154482509071,-0.0676216602553] w2_p33_p34_x_8:[0.961778609231,0.980879657724] w2_p33_p34_y_8:[-0.0268448663913,1.00494935145e-11] w2_p33_p34_z_8:[0.194615254006,0.272508668214] cos_p33_p34_8:[0.922669779378,0.96222895807] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.996574362861] w2_palm_p40_y_9:[-0.0826856424166,3.82843494672e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.763758758005] uni_u_p40_p42_x_10:[-0.819149697375,-0.816343587738] uni_u_p40_p42_y_10:[-0.0677319189621,3.136061328e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0776387929698,4.14143862995e-11] uni_v_p40_p42_y_10:[0.996954124219,1] uni_v_p40_p42_z_10:[-0,0.00737544531805] w1_p40_p42_x_10:[-0.0826856424166,3.82843494672e-11] w1_p40_p42_y_10:[0.996574362861,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.515444280298,-0.445227045086] w2_p40_p42_y_10:[-0.0464313765086,0.00222286542682] w2_p40_p42_z_10:[0.856435175014,0.895534191329] cos_0_p40_p42_10:[0.996741266008,1] cos_1_p40_p42_10:[0.877217993689,0.914922403568] w1_p42_p43_x_11:[-0.515444280298,-0.445227045086] w1_p42_p43_y_11:[-0.0464313765086,0.00222286542682] w1_p42_p43_z_11:[0.856435175014,0.895534191329] w2_p42_p43_x_11:[0.118307246752,0.203594397047] w2_p42_p43_y_11:[-0,0.0147825227076] w2_p42_p43_z_11:[0.979028091749,0.992980527762] cos_p42_p43_11:[0.754874430802,0.812822618481] w1_p43_p44_x_12:[-0.618186667511,-0.547168161745] w1_p43_p44_y_12:[-0.052552488067,3.45883110631e-05] w1_p43_p44_z_12:[0.785852385441,0.83694838481] w2_p43_p44_x_12:[-0,0.0945626505201] w2_p43_p44_y_12:[-0,0.0071968993171] w2_p43_p44_z_12:[0.995492863195,1] cos_p43_p44_12:[0.754874430802,0.812822618481] sph_w1_p34_X_3_x_13:[0.329322083811,0.406399969528] sph_w1_p34_X_3_y_13:[-3.99999111912e-11,0.0930582310472] sph_w1_p34_X_3_z_13:[-0.943966331188,-0.909472161272] sph_w2_p34_X_3_x_13:[0.822486442476,0.868519724244] sph_w2_p34_X_3_y_13:[0.447693935532,0.511874423143] sph_w2_p34_X_3_z_13:[-0.268469116013,-0.190536001605] cos_p34_X_3_13:[0.5,0.627466248927] in_patch_X_3_object_u_14:[0.374999999996,0.437500000004] in_patch_X_3_object_v_14:[0.374999999996,0.437500000004] in_patch_X_3_object_l_14:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_15:[-0.990148533442,-0.969436238496] sph_w1_p44_X_4_y_15:[-0.0774356861073,4.80247707011e-05] sph_w1_p44_X_4_z_15:[0.140021004665,0.233621062002] sph_w2_p44_X_4_x_15:[-0.760339995477,-0.692784599469] sph_w2_p44_X_4_y_15:[-0.371886463289,-0.312599656772] sph_w2_p44_X_4_z_15:[0.555975205897,0.622565671351] cos_p44_X_4_15:[0.771817134658,0.883584161827] in_patch_X_4_object_u_16:[0.437499999996,0.500000000005] in_patch_X_4_object_v_16:[0.374999999996,0.437500000004] in_patch_X_4_object_l_16:[9.71993866774,9.72381781325] p14_r_x:[-4.58926325393,-4.01073674607] p14_r_y:[-36.8114862262,-36.8084443158] p14_r_z:[243.172035024,243.172487408] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }
   8 (err:2.59712 min:3.15346 tm:106):{ 241  p12_u_x:[-0.00206111799494,0.00206111799494] p12_u_y:[0.034289592884,0.0343205859027] p12_u_z:[0.999409813947,0.999411936667] p12_v_x:[-0,0] p12_v_y:[-0.999411936568,-0.999410875721] p12_v_z:[0.0342896657316,0.0343205750292] p13_u_x:[-0.00498276539632,0.00498276539632] p13_u_y:[0.0342892400559,0.0343205751079] p13_u_z:[0.999399533406,0.999411936816] p13_v_x:[-0,0] p13_v_y:[-0.999411936568,-0.999410875721] p13_v_z:[0.0342896657316,0.0343205750292] p14_u_x:[-0.0103904616087,0.0103904616087] p14_u_y:[0.0342878146944,0.0343205751277] p14_u_z:[0.999358008227,0.999411937207] p14_v_x:[-0,0] p14_v_y:[-0.999411936568,-0.999410875721] p14_v_z:[0.0342896657316,0.0343205750292] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.367751414523,0.464891423425] p32_u_y:[-0.0827255829331,1.00458188003e-11] p32_u_z:[0.881384593056,0.929112175581] p32_v_x:[-0,0] p32_v_y:[-1,-0.995602579378] p32_v_z:[-0.0919788656051,0] p33_u_x:[0.754967403621,0.808465682546] p33_u_y:[-0.0584419505774,1.00458188003e-11] p33_u_z:[0.587928607418,0.653749985472] p33_v_x:[-0,0] p33_v_y:[-1,-0.995602579378] p33_v_z:[-0.0919788656051,0] p34_u_x:[0.961815940657,0.980879657724] p34_u_y:[-0.0250056459703,1.00458188003e-11] p34_u_z:[0.194615254006,0.272508668214] p34_v_x:[-0,0] p34_v_y:[-1,-0.995602579378] p34_v_z:[-0.0919788656051,0] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0766176790601,3.82843494672e-11] p40_v_y:[0.996941946648,1] p40_v_z:[-0,0] p42_u_x:[0.241461986851,0.315973028778] p42_u_y:[-0,0.0214627666485] p42_u_z:[0.948515924545,0.970410278662] p42_v_x:[-0.0718488654839,4.14143862995e-11] p42_v_y:[0.997286394443,1] p42_v_z:[-0,0.00696235361969] p43_u_x:[0.118365940665,0.204679128542] p43_u_y:[-0,0.0138629009957] p43_u_z:[0.97883603498,0.992978544787] p43_v_x:[-0.0718488654839,4.14143862995e-11] p43_v_y:[0.997286394443,1] p43_v_z:[-0,0.00696235361969] p44_u_x:[-0,0.0945626505201] p44_u_y:[-0,0.00679207459825] p44_u_z:[0.99549483805,1] p44_v_x:[-0.0718488654839,4.14143862995e-11] p44_v_y:[0.997286394443,1] p44_v_z:[-0,0.00696235361969] object_u_x:[0.346155596933,0.4] object_u_y:[0.311526493934,0.4] object_u_z:[0.828023308293,0.87276244757] object_v_x:[0.493112636578,0.555290856763] object_v_y:[-0.866446326835,-0.81927943408] object_v_z:[0.0782507003011,0.145039285443] X_3_u_x:[-0.51542950499,-0.450822644044] X_3_u_y:[0.854828102626,0.891747321667] X_3_u_z:[-0,0.069442588373] X_3_v_x:[0.167348535397,0.228886476143] X_3_v_y:[0.056139188991,0.137779564143] X_3_v_z:[0.963653307507,0.982075702704] X_4_u_x:[0.653076661892,0.723977127918] X_4_u_y:[-0.432635472537,-0.377505733436] X_4_u_z:[0.576239816334,0.652048634185] X_4_v_x:[-0,0.0809993156513] X_4_v_y:[0.847571780907,0.873711175126] X_4_v_z:[0.485232466758,0.524452004729] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411936568,-0.999410875721] uni_v_palm_p12_z_0:[0.0342896657316,0.0343205750292] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-7.07387547886e-05,7.07387547886e-05] w2_palm_p12_z_0:[-0.00205990594797,0.00205990594797] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00206111799494,0.00206111799494] w1_p12_p13_y_1:[0.034289592884,0.0343205859027] w1_p12_p13_z_1:[0.999409813947,0.999411936667] w2_p12_p13_x_1:[-0.00498276539632,0.00498276539632] w2_p12_p13_y_1:[0.0342892400559,0.0343205751079] w2_p12_p13_z_1:[0.999399533406,0.999411936816] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00498276539632,0.00498276539632] w1_p13_p14_y_2:[0.0342892400559,0.0343205751079] w1_p13_p14_z_2:[0.999399533406,0.999411936816] w2_p13_p14_x_2:[-0.0103904616087,0.0103904616087] w2_p13_p14_y_2:[0.0342878146944,0.0343205751277] w2_p13_p14_z_2:[0.999358008227,0.999411937207] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-1,-0.995602579378] uni_v_palm_p32_z_6:[-0.0919788656051,0] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.914618910933,0.957378069088] w2_palm_p32_y_6:[-0.0350338835941,0.000665458482836] w2_palm_p32_z_6:[0.295437762583,0.396525736108] cos_0_palm_p32_6:[0.998239428369,1] cos_1_palm_p32_6:[0.914618910933,0.957378069088] w1_p32_p33_x_7:[0.914618910933,0.957378069088] w1_p32_p33_y_7:[-0.0350338835941,0.000665458482836] w1_p32_p33_z_7:[0.295437762583,0.396525736108] w2_p32_p33_x_7:[0.754967403621,0.808465682546] w2_p32_p33_y_7:[-0.0584419505774,1.00458188003e-11] w2_p32_p33_z_7:[0.587928607418,0.653749985472] cos_p32_p33_7:[0.922916012476,0.962470202583] w1_p33_p34_x_8:[0.986245488772,0.999134305798] w1_p33_p34_y_8:[-0.00283718725403,0.0132176163577] w1_p33_p34_z_8:[-0.154133651364,-0.0697781877825] w2_p33_p34_x_8:[0.961815940657,0.980879657724] w2_p33_p34_y_8:[-0.0250056459703,1.00458188003e-11] w2_p33_p34_z_8:[0.194615254006,0.272508668214] cos_p33_p34_8:[0.922916012476,0.962470202583] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.996941946648] w2_palm_p40_y_9:[-0.0766176790601,3.82843494672e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.759684416663] uni_u_p40_p42_x_10:[-0.819149697375,-0.816644693886] uni_u_p40_p42_y_10:[-0.062761348615,3.136061328e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0718488654839,4.14143862995e-11] uni_v_p40_p42_y_10:[0.997286394443,1] uni_v_p40_p42_z_10:[-0,0.00696235361969] w1_p40_p42_x_10:[-0.0766176790601,3.82843494672e-11] w1_p40_p42_y_10:[0.996941946648,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.515444280298,-0.445465857782] w2_p40_p42_y_10:[-0.0431476325394,0.00213916517027] w2_p40_p42_z_10:[0.856470639005,0.895470613619] cos_0_p40_p42_10:[0.996978554935,1] cos_1_p40_p42_10:[0.877387026858,0.914840275436] w1_p42_p43_x_11:[-0.515444280298,-0.445465857782] w1_p42_p43_y_11:[-0.0431476325394,0.00213916517027] w1_p42_p43_z_11:[0.856470639005,0.895470613619] w2_p42_p43_x_11:[0.118365940665,0.204679128542] w2_p42_p43_y_11:[-0,0.0138629009957] w2_p42_p43_z_11:[0.97883603498,0.992978544787] cos_p42_p43_11:[0.754895661198,0.812778983603] w1_p43_p44_x_12:[-0.618173209033,-0.546474639588] w1_p43_p44_y_12:[-0.0487473993109,3.45883110631e-05] w1_p43_p44_z_12:[0.785876021414,0.837580475047] w2_p43_p44_x_12:[-0,0.0945626505201] w2_p43_p44_y_12:[-0,0.00679207459825] w2_p43_p44_z_12:[0.99549483805,1] cos_p43_p44_12:[0.754895661198,0.812778983603] sph_w1_p34_X_3_x_13:[0.329374291225,0.406232689798] sph_w1_p34_X_3_y_13:[-3.99999111912e-11,0.0865129206073] sph_w1_p34_X_3_z_13:[-0.943966331188,-0.910015432783] sph_w2_p34_X_3_x_13:[0.822488005671,0.867862663578] sph_w2_p34_X_3_y_13:[0.447697313586,0.511867202302] sph_w2_p34_X_3_z_13:[-0.268463626017,-0.193053593024] cos_p34_X_3_13:[0.5,0.624174965307] in_patch_X_3_object_u_14:[0.437499999996,0.500000000005] in_patch_X_3_object_v_14:[0.374999999996,0.437500000004] in_patch_X_3_object_l_14:[9.84343798184,9.84343798184] sph_w1_p44_X_4_x_15:[-0.990148533442,-0.969766426836] sph_w1_p44_X_4_y_15:[-0.0716817423832,4.80247707011e-05] sph_w1_p44_X_4_z_15:[0.140021004665,0.233583143999] sph_w2_p44_X_4_x_15:[-0.758113375634,-0.692786205226] sph_w2_p44_X_4_y_15:[-0.371876788801,-0.312606514156] sph_w2_p44_X_4_z_15:[0.55829748847,0.622558152387] cos_p44_X_4_15:[0.77181822591,0.881263994684] in_patch_X_4_object_u_16:[0.374999999996,0.437500000004] in_patch_X_4_object_v_16:[0.437499999996,0.500000000005] in_patch_X_4_object_l_16:[9.71605990988,9.71993905446] p14_r_x:[-4.58922676199,-4.01077323802] p14_r_y:[-36.8114879682,-36.8084470224] p14_r_z:[243.172034902,243.17248743] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }


Cuik executed in 31 (31) child processors
STATITISTICS FOR Cuik:

Volume of the search space: 7.08214e+13
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 0.447161
Number of processors: 32
User time in process: 106.000000 seg (1.766667 min)
Box level information:
  N processed boxes :   2003
  Max depth         :     70
  Types of boxes:
    N solution boxes:      8 (0) ( 0.40%)
    N empty boxes   :     82  ( 4.09%)
    N bisected boxes:   1913  (95.51%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :   2176
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

