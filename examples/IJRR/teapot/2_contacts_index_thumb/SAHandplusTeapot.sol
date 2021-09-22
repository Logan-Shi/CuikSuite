
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
Equations from file: /home/porta/cuik/CuikSuite/examples/IJRR/teapot/2_contacts_index_thumb/SAHandplusTeapot_kin.cuik
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
   object_v_z : [-1,0]

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
   in_patch_X_3_object_l_14 : [4.41222566605,12.2874962728]
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
   in_patch_X_4_object_l_16 : [4.41222566605,12.2874962728]

[CARTESIAN VARS]
   p14_r_x : [-1666.05628136,1666.05628136]
   p14_r_y : [-1666.05628136,1666.05628136]
   p14_r_z : [-1666.05628136,1666.05628136]
   p24_r_x : [-1666.05628136,1666.05628136]
   p24_r_y : [-1666.05628136,1666.05628136]
   p24_r_z : [-1666.05628136,1666.05628136]

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
   22.5563573497*in_patch_X_3_object_u_14^2+22.5326392873*in_patch_X_3_object_v_14^2-in_patch_X_3_object_l_14^2-32.8864531944*in_patch_X_3_object_u_14+20.4033612072*in_patch_X_3_object_v_14-33.1360182873*in_patch_X_3_object_w_14 = -85.4902068098;
   1.516785*object_u_x*in_patch_X_3_object_u_14+1.870557*object_u_x*in_patch_X_3_object_v_14+4.323051*object_v_x*in_patch_X_3_object_u_14-4.326698*object_v_x*in_patch_X_3_object_v_14+1.251779*object_w_x*in_patch_X_3_object_u_14-0.559768*object_w_x*in_patch_X_3_object_v_14-1.251779*object_wp_x*in_patch_X_3_object_u_14+0.559768*object_wp_x*in_patch_X_3_object_v_14+X_3_w_x*in_patch_X_3_object_l_14-X_3_wp_x*in_patch_X_3_object_l_14+0.030175*object_u_x-1.158008*object_v_x-9.173239*object_w_x+9.173239*object_wp_x = 0;
   1.516785*object_u_y*in_patch_X_3_object_u_14+1.870557*object_u_y*in_patch_X_3_object_v_14+4.323051*object_v_y*in_patch_X_3_object_u_14-4.326698*object_v_y*in_patch_X_3_object_v_14+1.251779*object_w_y*in_patch_X_3_object_u_14-0.559768*object_w_y*in_patch_X_3_object_v_14-1.251779*object_wp_y*in_patch_X_3_object_u_14+0.559768*object_wp_y*in_patch_X_3_object_v_14+X_3_w_y*in_patch_X_3_object_l_14-X_3_wp_y*in_patch_X_3_object_l_14+0.030175*object_u_y-1.158008*object_v_y-9.173239*object_w_y+9.173239*object_wp_y = 0;
   1.516785*object_u_z*in_patch_X_3_object_u_14+1.870557*object_u_z*in_patch_X_3_object_v_14+4.323051*object_v_z*in_patch_X_3_object_u_14-4.326698*object_v_z*in_patch_X_3_object_v_14+1.251779*object_w_z*in_patch_X_3_object_u_14-0.559768*object_w_z*in_patch_X_3_object_v_14-1.251779*object_wp_z*in_patch_X_3_object_u_14+0.559768*object_wp_z*in_patch_X_3_object_v_14+X_3_w_z*in_patch_X_3_object_l_14-X_3_wp_z*in_patch_X_3_object_l_14+0.030175*object_u_z-1.158008*object_v_z-9.173239*object_w_z+9.173239*object_wp_z = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_15 = -0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_15 = -0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_15 = -0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_15 = -0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_15 = -0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_15 = -0;
   sph_w1_p44_X_4_x_15*sph_w2_p44_X_4_x_15+sph_w1_p44_X_4_y_15*sph_w2_p44_X_4_y_15+sph_w1_p44_X_4_z_15*sph_w2_p44_X_4_z_15-cos_p44_X_4_15 = 0;
   22.5563573497*in_patch_X_4_object_u_16^2+22.5326392873*in_patch_X_4_object_v_16^2-in_patch_X_4_object_l_16^2-32.8864531944*in_patch_X_4_object_u_16+20.4033612072*in_patch_X_4_object_v_16-33.1360182873*in_patch_X_4_object_w_16 = -85.4902068098;
   1.516785*object_u_x*in_patch_X_4_object_u_16+1.870557*object_u_x*in_patch_X_4_object_v_16-4.323051*object_v_x*in_patch_X_4_object_u_16+4.326698*object_v_x*in_patch_X_4_object_v_16+1.251779*object_w_x*in_patch_X_4_object_u_16-0.559768*object_w_x*in_patch_X_4_object_v_16-1.251779*object_wp_x*in_patch_X_4_object_u_16+0.559768*object_wp_x*in_patch_X_4_object_v_16-X_4_w_x*in_patch_X_4_object_l_16+X_4_wp_x*in_patch_X_4_object_l_16+0.030175*object_u_x+1.158008*object_v_x-9.173239*object_w_x+9.173239*object_wp_x = -0;
   1.516785*object_u_y*in_patch_X_4_object_u_16+1.870557*object_u_y*in_patch_X_4_object_v_16-4.323051*object_v_y*in_patch_X_4_object_u_16+4.326698*object_v_y*in_patch_X_4_object_v_16+1.251779*object_w_y*in_patch_X_4_object_u_16-0.559768*object_w_y*in_patch_X_4_object_v_16-1.251779*object_wp_y*in_patch_X_4_object_u_16+0.559768*object_wp_y*in_patch_X_4_object_v_16-X_4_w_y*in_patch_X_4_object_l_16+X_4_wp_y*in_patch_X_4_object_l_16+0.030175*object_u_y+1.158008*object_v_y-9.173239*object_w_y+9.173239*object_wp_y = -0;
   1.516785*object_u_z*in_patch_X_4_object_u_16+1.870557*object_u_z*in_patch_X_4_object_v_16-4.323051*object_v_z*in_patch_X_4_object_u_16+4.326698*object_v_z*in_patch_X_4_object_v_16+1.251779*object_w_z*in_patch_X_4_object_u_16-0.559768*object_w_z*in_patch_X_4_object_v_16-1.251779*object_wp_z*in_patch_X_4_object_u_16+0.559768*object_wp_z*in_patch_X_4_object_v_16-X_4_w_z*in_patch_X_4_object_l_16+X_4_wp_z*in_patch_X_4_object_l_16+0.030175*object_u_z+1.158008*object_v_z-9.173239*object_w_z+9.173239*object_wp_z = -0;
   3.341*object_u_x*in_patch_X_3_object_u_14+3.414*object_u_x*in_patch_X_3_object_v_14-0.262*object_u_x*in_patch_X_3_object_w_14+3.341*object_u_x*in_patch_X_4_object_u_16+3.414*object_u_x*in_patch_X_4_object_v_16-0.262*object_u_x*in_patch_X_4_object_w_16-1.22*object_v_x*in_patch_X_3_object_u_14+1.499*object_v_x*in_patch_X_3_object_v_14-0.279*object_v_x*in_patch_X_3_object_w_14+1.22*object_v_x*in_patch_X_4_object_u_16-1.499*object_v_x*in_patch_X_4_object_v_16+0.279*object_v_x*in_patch_X_4_object_w_16+0.165*object_w_x*in_patch_X_3_object_u_14-0.178*object_w_x*in_patch_X_3_object_v_14+1.281*object_w_x*in_patch_X_3_object_w_14+0.165*object_w_x*in_patch_X_4_object_u_16-0.178*object_w_x*in_patch_X_4_object_v_16+1.281*object_w_x*in_patch_X_4_object_w_16-0.165*object_wp_x*in_patch_X_3_object_u_14+0.178*object_wp_x*in_patch_X_3_object_v_14-1.281*object_wp_x*in_patch_X_3_object_w_14-0.165*object_wp_x*in_patch_X_4_object_u_16+0.178*object_wp_x*in_patch_X_4_object_v_16-1.281*object_wp_x*in_patch_X_4_object_w_16+67.8*p32_u_x+30*p33_u_x+20*p34_u_x+10*p34_v_x-97*p40_u_x-6*p40_v_x+87*p40_w_x-87*p40_wp_x-67.8*p42_u_x-30*p43_u_x-20*p44_u_x-12.986*object_u_x+30.416*object_w_x-30.416*object_wp_x+13*X_3_w_x-13*X_3_wp_x-13*X_4_w_x+13*X_4_wp_x = 1.3;
   3.341*object_u_y*in_patch_X_3_object_u_14+3.414*object_u_y*in_patch_X_3_object_v_14-0.262*object_u_y*in_patch_X_3_object_w_14+3.341*object_u_y*in_patch_X_4_object_u_16+3.414*object_u_y*in_patch_X_4_object_v_16-0.262*object_u_y*in_patch_X_4_object_w_16-1.22*object_v_y*in_patch_X_3_object_u_14+1.499*object_v_y*in_patch_X_3_object_v_14-0.279*object_v_y*in_patch_X_3_object_w_14+1.22*object_v_y*in_patch_X_4_object_u_16-1.499*object_v_y*in_patch_X_4_object_v_16+0.279*object_v_y*in_patch_X_4_object_w_16+0.165*object_w_y*in_patch_X_3_object_u_14-0.178*object_w_y*in_patch_X_3_object_v_14+1.281*object_w_y*in_patch_X_3_object_w_14+0.165*object_w_y*in_patch_X_4_object_u_16-0.178*object_w_y*in_patch_X_4_object_v_16+1.281*object_w_y*in_patch_X_4_object_w_16-0.165*object_wp_y*in_patch_X_3_object_u_14+0.178*object_wp_y*in_patch_X_3_object_v_14-1.281*object_wp_y*in_patch_X_3_object_w_14-0.165*object_wp_y*in_patch_X_4_object_u_16+0.178*object_wp_y*in_patch_X_4_object_v_16-1.281*object_wp_y*in_patch_X_4_object_w_16+67.8*p32_u_y+30*p33_u_y+20*p34_u_y+10*p34_v_y-97*p40_u_y-6*p40_v_y+87*p40_w_y-87*p40_wp_y-67.8*p42_u_y-30*p43_u_y-20*p44_u_y-12.986*object_u_y+30.416*object_w_y-30.416*object_wp_y+13*X_3_w_y-13*X_3_wp_y-13*X_4_w_y+13*X_4_wp_y = -13.065;
   3.341*object_u_z*in_patch_X_3_object_u_14+3.414*object_u_z*in_patch_X_3_object_v_14-0.262*object_u_z*in_patch_X_3_object_w_14+3.341*object_u_z*in_patch_X_4_object_u_16+3.414*object_u_z*in_patch_X_4_object_v_16-0.262*object_u_z*in_patch_X_4_object_w_16-1.22*object_v_z*in_patch_X_3_object_u_14+1.499*object_v_z*in_patch_X_3_object_v_14-0.279*object_v_z*in_patch_X_3_object_w_14+1.22*object_v_z*in_patch_X_4_object_u_16-1.499*object_v_z*in_patch_X_4_object_v_16+0.279*object_v_z*in_patch_X_4_object_w_16+0.165*object_w_z*in_patch_X_3_object_u_14-0.178*object_w_z*in_patch_X_3_object_v_14+1.281*object_w_z*in_patch_X_3_object_w_14+0.165*object_w_z*in_patch_X_4_object_u_16-0.178*object_w_z*in_patch_X_4_object_v_16+1.281*object_w_z*in_patch_X_4_object_w_16-0.165*object_wp_z*in_patch_X_3_object_u_14+0.178*object_wp_z*in_patch_X_3_object_v_14-1.281*object_wp_z*in_patch_X_3_object_w_14-0.165*object_wp_z*in_patch_X_4_object_u_16+0.178*object_wp_z*in_patch_X_4_object_v_16-1.281*object_wp_z*in_patch_X_4_object_w_16+67.8*p32_u_z+30*p33_u_z+20*p34_u_z+10*p34_v_z-97*p40_u_z-6*p40_v_z+87*p40_w_z-87*p40_wp_z-67.8*p42_u_z-30*p43_u_z-20*p44_u_z-12.986*object_u_z+30.416*object_w_z-30.416*object_wp_z+13*X_3_w_z-13*X_3_wp_z-13*X_4_w_z+13*X_4_wp_z = -145.43;

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

 MIN 172.582639308*cos_0_palm_p32_6^2+11.6568542495*cos_1_palm_p32_6^2+11.6568542495*cos_p32_p33_7^2+11.6568542495*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+11.6568542495*cos_p42_p43_11^2+11.6568542495*cos_p43_p44_12^2+4*cos_p34_X_3_13^2+4*in_patch_X_3_object_u_14^2+4*in_patch_X_3_object_v_14^2+4*cos_p44_X_4_15^2+4*in_patch_X_4_object_u_16^2+4*in_patch_X_4_object_v_16^2-345.165278616*cos_0_palm_p32_6-23.313708499*cos_1_palm_p32_6-23.313708499*cos_p32_p33_7-23.313708499*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-23.313708499*cos_p42_p43_11-23.313708499*cos_p43_p44_12-8*cos_p34_X_3_13-4*in_patch_X_3_object_u_14-4*in_patch_X_3_object_v_14-8*cos_p44_X_4_15-4*in_patch_X_4_object_u_16-4*in_patch_X_4_object_v_16+438.763258362




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
%   in_patch_X_3_object_w_14=in_patch_X_3_object_w_14
%   in_patch_X_3_object_l_14=in_patch_X_3_object_l_14
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
   object_u_x : [-1,1]
   object_u_y : [-1,1]
   object_u_z : [-1,1]
   object_v_x : [-1,1]
   object_v_y : [-1,1]
   object_v_z : [-1,0]

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

[DUMMY VARS]
   in_patch_X_3_object_w_14 : [0,1]

[SECONDARY VARS]
   in_patch_X_3_object_l_14 : [4.41222566605,12.2874962728]
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
   in_patch_X_4_object_l_16 : [4.41222566605,12.2874962728]

[CARTESIAN VARS]
   p14_r_x : [-1666.05628136,1666.05628136]
   p14_r_y : [-1666.05628136,1666.05628136]
   p14_r_z : [-1666.05628136,1666.05628136]

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
   dummy_object_u_x_object_v_x : [-1,1]
   dummy_object_u_y_object_v_y : [-1,1]
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
   dummy_in_patch_X_3_object_u_14_2 : [0,1]
   dummy_in_patch_X_3_object_v_14_2 : [0,1]
   dummy_in_patch_X_3_object_l_14_2 : [19.4677353282,150.982564654]
   dummy_object_u_x_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_u_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_X_3_w_x_in_patch_X_3_object_l_14 : [-12.2874962728,12.2874962728]
   dummy_X_3_wp_x_in_patch_X_3_object_l_14 : [-12.2874962728,12.2874962728]
   dummy_object_u_y_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_X_3_w_y_in_patch_X_3_object_l_14 : [-12.2874962728,12.2874962728]
   dummy_X_3_wp_y_in_patch_X_3_object_l_14 : [-12.2874962728,12.2874962728]
   dummy_object_u_z_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_u_z_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_v_z_in_patch_X_3_object_u_14 : [-1,-0]
   dummy_object_v_z_in_patch_X_3_object_v_14 : [-1,-0]
   dummy_object_w_z_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_v_14 : [-1,1]
   dummy_X_3_w_z_in_patch_X_3_object_l_14 : [-12.2874962728,12.2874962728]
   dummy_X_3_wp_z_in_patch_X_3_object_l_14 : [-12.2874962728,12.2874962728]
   dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15 : [-1,1]
   dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15 : [-1,1]
   dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 : [-1,1]
   dummy_in_patch_X_4_object_u_16_2 : [0,1]
   dummy_in_patch_X_4_object_v_16_2 : [0,1]
   dummy_in_patch_X_4_object_l_16_2 : [19.4677353282,150.982564654]
   dummy_object_u_x_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_u_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_w_x_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_w_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_x_in_patch_X_4_object_l_16 : [-12.2874962728,12.2874962728]
   dummy_X_4_wp_x_in_patch_X_4_object_l_16 : [-12.2874962728,12.2874962728]
   dummy_object_u_y_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_u_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_w_y_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_w_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_y_in_patch_X_4_object_l_16 : [-12.2874962728,12.2874962728]
   dummy_X_4_wp_y_in_patch_X_4_object_l_16 : [-12.2874962728,12.2874962728]
   dummy_object_u_z_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_u_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_u_16 : [-1,-0]
   dummy_object_v_z_in_patch_X_4_object_v_16 : [-1,-0]
   dummy_object_w_z_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_w_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_X_4_w_z_in_patch_X_4_object_l_16 : [-12.2874962728,12.2874962728]
   dummy_X_4_wp_z_in_patch_X_4_object_l_16 : [-12.2874962728,12.2874962728]
   dummy_object_u_x_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_u_x_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_w_x_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_u_y_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_w_y_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_u_z_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_u_z_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_v_z_in_patch_X_3_object_w_14 : [-1,-0]
   dummy_object_v_z_in_patch_X_4_object_w_16 : [-1,-0]
   dummy_object_w_z_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_w_z_in_patch_X_4_object_w_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_w_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_4_object_w_16 : [-1,1]

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
   32.8864531944*in_patch_X_3_object_u_14-20.4033612072*in_patch_X_3_object_v_14+33.1360182873*in_patch_X_3_object_w_14-22.5563573497*dummy_in_patch_X_3_object_u_14_2-22.5326392873*dummy_in_patch_X_3_object_v_14_2+dummy_in_patch_X_3_object_l_14_2 = 85.4902068098;
   0.030175*object_u_x-1.158008*object_v_x-9.173239*object_w_x+9.173239*object_wp_x+1.516785*dummy_object_u_x_in_patch_X_3_object_u_14+1.870557*dummy_object_u_x_in_patch_X_3_object_v_14+4.323051*dummy_object_v_x_in_patch_X_3_object_u_14-4.326698*dummy_object_v_x_in_patch_X_3_object_v_14+1.251779*dummy_object_w_x_in_patch_X_3_object_u_14-0.559768*dummy_object_w_x_in_patch_X_3_object_v_14-1.251779*dummy_object_wp_x_in_patch_X_3_object_u_14+0.559768*dummy_object_wp_x_in_patch_X_3_object_v_14+dummy_X_3_w_x_in_patch_X_3_object_l_14-dummy_X_3_wp_x_in_patch_X_3_object_l_14 = 0;
   0.030175*object_u_y-1.158008*object_v_y-9.173239*object_w_y+9.173239*object_wp_y+1.516785*dummy_object_u_y_in_patch_X_3_object_u_14+1.870557*dummy_object_u_y_in_patch_X_3_object_v_14+4.323051*dummy_object_v_y_in_patch_X_3_object_u_14-4.326698*dummy_object_v_y_in_patch_X_3_object_v_14+1.251779*dummy_object_w_y_in_patch_X_3_object_u_14-0.559768*dummy_object_w_y_in_patch_X_3_object_v_14-1.251779*dummy_object_wp_y_in_patch_X_3_object_u_14+0.559768*dummy_object_wp_y_in_patch_X_3_object_v_14+dummy_X_3_w_y_in_patch_X_3_object_l_14-dummy_X_3_wp_y_in_patch_X_3_object_l_14 = 0;
   0.030175*object_u_z-1.158008*object_v_z-9.173239*object_w_z+9.173239*object_wp_z+1.516785*dummy_object_u_z_in_patch_X_3_object_u_14+1.870557*dummy_object_u_z_in_patch_X_3_object_v_14+4.323051*dummy_object_v_z_in_patch_X_3_object_u_14-4.326698*dummy_object_v_z_in_patch_X_3_object_v_14+1.251779*dummy_object_w_z_in_patch_X_3_object_u_14-0.559768*dummy_object_w_z_in_patch_X_3_object_v_14-1.251779*dummy_object_wp_z_in_patch_X_3_object_u_14+0.559768*dummy_object_wp_z_in_patch_X_3_object_v_14+dummy_X_3_w_z_in_patch_X_3_object_l_14-dummy_X_3_wp_z_in_patch_X_3_object_l_14 = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_15 = 0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_15 = 0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_15 = 0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_15 = 0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_15 = 0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_15 = 0;
   cos_p44_X_4_15-dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15-dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15-dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 = -0;
   32.8864531944*in_patch_X_4_object_u_16-20.4033612072*in_patch_X_4_object_v_16+33.1360182873*in_patch_X_4_object_w_16-22.5563573497*dummy_in_patch_X_4_object_u_16_2-22.5326392873*dummy_in_patch_X_4_object_v_16_2+dummy_in_patch_X_4_object_l_16_2 = 85.4902068098;
   0.030175*object_u_x+1.158008*object_v_x-9.173239*object_w_x+9.173239*object_wp_x+1.516785*dummy_object_u_x_in_patch_X_4_object_u_16+1.870557*dummy_object_u_x_in_patch_X_4_object_v_16-4.323051*dummy_object_v_x_in_patch_X_4_object_u_16+4.326698*dummy_object_v_x_in_patch_X_4_object_v_16+1.251779*dummy_object_w_x_in_patch_X_4_object_u_16-0.559768*dummy_object_w_x_in_patch_X_4_object_v_16-1.251779*dummy_object_wp_x_in_patch_X_4_object_u_16+0.559768*dummy_object_wp_x_in_patch_X_4_object_v_16-dummy_X_4_w_x_in_patch_X_4_object_l_16+dummy_X_4_wp_x_in_patch_X_4_object_l_16 = 0;
   0.030175*object_u_y+1.158008*object_v_y-9.173239*object_w_y+9.173239*object_wp_y+1.516785*dummy_object_u_y_in_patch_X_4_object_u_16+1.870557*dummy_object_u_y_in_patch_X_4_object_v_16-4.323051*dummy_object_v_y_in_patch_X_4_object_u_16+4.326698*dummy_object_v_y_in_patch_X_4_object_v_16+1.251779*dummy_object_w_y_in_patch_X_4_object_u_16-0.559768*dummy_object_w_y_in_patch_X_4_object_v_16-1.251779*dummy_object_wp_y_in_patch_X_4_object_u_16+0.559768*dummy_object_wp_y_in_patch_X_4_object_v_16-dummy_X_4_w_y_in_patch_X_4_object_l_16+dummy_X_4_wp_y_in_patch_X_4_object_l_16 = 0;
   0.030175*object_u_z+1.158008*object_v_z-9.173239*object_w_z+9.173239*object_wp_z+1.516785*dummy_object_u_z_in_patch_X_4_object_u_16+1.870557*dummy_object_u_z_in_patch_X_4_object_v_16-4.323051*dummy_object_v_z_in_patch_X_4_object_u_16+4.326698*dummy_object_v_z_in_patch_X_4_object_v_16+1.251779*dummy_object_w_z_in_patch_X_4_object_u_16-0.559768*dummy_object_w_z_in_patch_X_4_object_v_16-1.251779*dummy_object_wp_z_in_patch_X_4_object_u_16+0.559768*dummy_object_wp_z_in_patch_X_4_object_v_16-dummy_X_4_w_z_in_patch_X_4_object_l_16+dummy_X_4_wp_z_in_patch_X_4_object_l_16 = 0;
   67.8*p32_u_x+30*p33_u_x+20*p34_u_x-6*p40_v_x-87*p40_v_y-67.8*p42_u_x-30*p43_u_x-20*p44_u_x-12.986*object_u_x+30.416*object_w_x-30.416*object_wp_x+13*sph_w2_p34_X_3_x_13-13*sph_w2_p44_X_4_x_15+3.341*dummy_object_u_x_in_patch_X_3_object_u_14+3.414*dummy_object_u_x_in_patch_X_3_object_v_14-1.22*dummy_object_v_x_in_patch_X_3_object_u_14+1.499*dummy_object_v_x_in_patch_X_3_object_v_14+0.165*dummy_object_w_x_in_patch_X_3_object_u_14-0.178*dummy_object_w_x_in_patch_X_3_object_v_14-0.165*dummy_object_wp_x_in_patch_X_3_object_u_14+0.178*dummy_object_wp_x_in_patch_X_3_object_v_14+3.341*dummy_object_u_x_in_patch_X_4_object_u_16+3.414*dummy_object_u_x_in_patch_X_4_object_v_16+1.22*dummy_object_v_x_in_patch_X_4_object_u_16-1.499*dummy_object_v_x_in_patch_X_4_object_v_16+0.165*dummy_object_w_x_in_patch_X_4_object_u_16-0.178*dummy_object_w_x_in_patch_X_4_object_v_16-0.165*dummy_object_wp_x_in_patch_X_4_object_u_16+0.178*dummy_object_wp_x_in_patch_X_4_object_v_16-0.262*dummy_object_u_x_in_patch_X_3_object_w_14-0.262*dummy_object_u_x_in_patch_X_4_object_w_16-0.279*dummy_object_v_x_in_patch_X_3_object_w_14+0.279*dummy_object_v_x_in_patch_X_4_object_w_16+1.281*dummy_object_w_x_in_patch_X_3_object_w_14+1.281*dummy_object_w_x_in_patch_X_4_object_w_16-1.281*dummy_object_wp_x_in_patch_X_3_object_w_14-1.281*dummy_object_wp_x_in_patch_X_4_object_w_16 = 1.3;
   67.8*p32_u_y+30*p33_u_y+20*p34_u_y+10*p34_v_y+87*p40_v_x-6*p40_v_y-67.8*p42_u_y-30*p43_u_y-20*p44_u_y-12.986*object_u_y+30.416*object_w_y-30.416*object_wp_y+13*sph_w2_p34_X_3_y_13-13*sph_w2_p44_X_4_y_15+3.341*dummy_object_u_y_in_patch_X_3_object_u_14+3.414*dummy_object_u_y_in_patch_X_3_object_v_14-1.22*dummy_object_v_y_in_patch_X_3_object_u_14+1.499*dummy_object_v_y_in_patch_X_3_object_v_14+0.165*dummy_object_w_y_in_patch_X_3_object_u_14-0.178*dummy_object_w_y_in_patch_X_3_object_v_14-0.165*dummy_object_wp_y_in_patch_X_3_object_u_14+0.178*dummy_object_wp_y_in_patch_X_3_object_v_14+3.341*dummy_object_u_y_in_patch_X_4_object_u_16+3.414*dummy_object_u_y_in_patch_X_4_object_v_16+1.22*dummy_object_v_y_in_patch_X_4_object_u_16-1.499*dummy_object_v_y_in_patch_X_4_object_v_16+0.165*dummy_object_w_y_in_patch_X_4_object_u_16-0.178*dummy_object_w_y_in_patch_X_4_object_v_16-0.165*dummy_object_wp_y_in_patch_X_4_object_u_16+0.178*dummy_object_wp_y_in_patch_X_4_object_v_16-0.262*dummy_object_u_y_in_patch_X_3_object_w_14-0.262*dummy_object_u_y_in_patch_X_4_object_w_16-0.279*dummy_object_v_y_in_patch_X_3_object_w_14+0.279*dummy_object_v_y_in_patch_X_4_object_w_16+1.281*dummy_object_w_y_in_patch_X_3_object_w_14+1.281*dummy_object_w_y_in_patch_X_4_object_w_16-1.281*dummy_object_wp_y_in_patch_X_3_object_w_14-1.281*dummy_object_wp_y_in_patch_X_4_object_w_16 = -13.065;
   67.8*p32_u_z+30*p33_u_z+20*p34_u_z+10*p34_v_z-67.8*p42_u_z-30*p43_u_z-20*p44_u_z-12.986*object_u_z+30.416*object_w_z-30.416*object_wp_z+13*sph_w2_p34_X_3_z_13-13*sph_w2_p44_X_4_z_15+3.341*dummy_object_u_z_in_patch_X_3_object_u_14+3.414*dummy_object_u_z_in_patch_X_3_object_v_14-1.22*dummy_object_v_z_in_patch_X_3_object_u_14+1.499*dummy_object_v_z_in_patch_X_3_object_v_14+0.165*dummy_object_w_z_in_patch_X_3_object_u_14-0.178*dummy_object_w_z_in_patch_X_3_object_v_14-0.165*dummy_object_wp_z_in_patch_X_3_object_u_14+0.178*dummy_object_wp_z_in_patch_X_3_object_v_14+3.341*dummy_object_u_z_in_patch_X_4_object_u_16+3.414*dummy_object_u_z_in_patch_X_4_object_v_16+1.22*dummy_object_v_z_in_patch_X_4_object_u_16-1.499*dummy_object_v_z_in_patch_X_4_object_v_16+0.165*dummy_object_w_z_in_patch_X_4_object_u_16-0.178*dummy_object_w_z_in_patch_X_4_object_v_16-0.165*dummy_object_wp_z_in_patch_X_4_object_u_16+0.178*dummy_object_wp_z_in_patch_X_4_object_v_16-0.262*dummy_object_u_z_in_patch_X_3_object_w_14-0.262*dummy_object_u_z_in_patch_X_4_object_w_16-0.279*dummy_object_v_z_in_patch_X_3_object_w_14+0.279*dummy_object_v_z_in_patch_X_4_object_w_16+1.281*dummy_object_w_z_in_patch_X_3_object_w_14+1.281*dummy_object_w_z_in_patch_X_4_object_w_16-1.281*dummy_object_wp_z_in_patch_X_3_object_w_14-1.281*dummy_object_wp_z_in_patch_X_4_object_w_16 = -48.43;

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
   in_patch_X_3_object_u_14^2-dummy_in_patch_X_3_object_u_14_2 = 0;
   in_patch_X_3_object_v_14^2-dummy_in_patch_X_3_object_v_14_2 = 0;
   in_patch_X_3_object_l_14^2-dummy_in_patch_X_3_object_l_14_2 = 0;
   object_u_x*in_patch_X_3_object_u_14-dummy_object_u_x_in_patch_X_3_object_u_14 = 0;
   object_u_x*in_patch_X_3_object_v_14-dummy_object_u_x_in_patch_X_3_object_v_14 = 0;
   object_v_x*in_patch_X_3_object_u_14-dummy_object_v_x_in_patch_X_3_object_u_14 = 0;
   object_v_x*in_patch_X_3_object_v_14-dummy_object_v_x_in_patch_X_3_object_v_14 = 0;
   object_w_x*in_patch_X_3_object_u_14-dummy_object_w_x_in_patch_X_3_object_u_14 = 0;
   object_w_x*in_patch_X_3_object_v_14-dummy_object_w_x_in_patch_X_3_object_v_14 = 0;
   object_wp_x*in_patch_X_3_object_u_14-dummy_object_wp_x_in_patch_X_3_object_u_14 = 0;
   object_wp_x*in_patch_X_3_object_v_14-dummy_object_wp_x_in_patch_X_3_object_v_14 = 0;
   X_3_w_x*in_patch_X_3_object_l_14-dummy_X_3_w_x_in_patch_X_3_object_l_14 = 0;
   X_3_wp_x*in_patch_X_3_object_l_14-dummy_X_3_wp_x_in_patch_X_3_object_l_14 = 0;
   object_u_y*in_patch_X_3_object_u_14-dummy_object_u_y_in_patch_X_3_object_u_14 = 0;
   object_u_y*in_patch_X_3_object_v_14-dummy_object_u_y_in_patch_X_3_object_v_14 = 0;
   object_v_y*in_patch_X_3_object_u_14-dummy_object_v_y_in_patch_X_3_object_u_14 = 0;
   object_v_y*in_patch_X_3_object_v_14-dummy_object_v_y_in_patch_X_3_object_v_14 = 0;
   object_w_y*in_patch_X_3_object_u_14-dummy_object_w_y_in_patch_X_3_object_u_14 = 0;
   object_w_y*in_patch_X_3_object_v_14-dummy_object_w_y_in_patch_X_3_object_v_14 = 0;
   object_wp_y*in_patch_X_3_object_u_14-dummy_object_wp_y_in_patch_X_3_object_u_14 = 0;
   object_wp_y*in_patch_X_3_object_v_14-dummy_object_wp_y_in_patch_X_3_object_v_14 = 0;
   X_3_w_y*in_patch_X_3_object_l_14-dummy_X_3_w_y_in_patch_X_3_object_l_14 = 0;
   X_3_wp_y*in_patch_X_3_object_l_14-dummy_X_3_wp_y_in_patch_X_3_object_l_14 = 0;
   object_u_z*in_patch_X_3_object_u_14-dummy_object_u_z_in_patch_X_3_object_u_14 = 0;
   object_u_z*in_patch_X_3_object_v_14-dummy_object_u_z_in_patch_X_3_object_v_14 = 0;
   object_v_z*in_patch_X_3_object_u_14-dummy_object_v_z_in_patch_X_3_object_u_14 = 0;
   object_v_z*in_patch_X_3_object_v_14-dummy_object_v_z_in_patch_X_3_object_v_14 = 0;
   object_w_z*in_patch_X_3_object_u_14-dummy_object_w_z_in_patch_X_3_object_u_14 = 0;
   object_w_z*in_patch_X_3_object_v_14-dummy_object_w_z_in_patch_X_3_object_v_14 = 0;
   object_wp_z*in_patch_X_3_object_u_14-dummy_object_wp_z_in_patch_X_3_object_u_14 = 0;
   object_wp_z*in_patch_X_3_object_v_14-dummy_object_wp_z_in_patch_X_3_object_v_14 = 0;
   X_3_w_z*in_patch_X_3_object_l_14-dummy_X_3_w_z_in_patch_X_3_object_l_14 = 0;
   X_3_wp_z*in_patch_X_3_object_l_14-dummy_X_3_wp_z_in_patch_X_3_object_l_14 = 0;
   sph_w1_p44_X_4_x_15*sph_w2_p44_X_4_x_15-dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15 = 0;
   sph_w1_p44_X_4_y_15*sph_w2_p44_X_4_y_15-dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15 = 0;
   sph_w1_p44_X_4_z_15*sph_w2_p44_X_4_z_15-dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 = 0;
   in_patch_X_4_object_u_16^2-dummy_in_patch_X_4_object_u_16_2 = 0;
   in_patch_X_4_object_v_16^2-dummy_in_patch_X_4_object_v_16_2 = 0;
   in_patch_X_4_object_l_16^2-dummy_in_patch_X_4_object_l_16_2 = 0;
   object_u_x*in_patch_X_4_object_u_16-dummy_object_u_x_in_patch_X_4_object_u_16 = 0;
   object_u_x*in_patch_X_4_object_v_16-dummy_object_u_x_in_patch_X_4_object_v_16 = 0;
   object_v_x*in_patch_X_4_object_u_16-dummy_object_v_x_in_patch_X_4_object_u_16 = 0;
   object_v_x*in_patch_X_4_object_v_16-dummy_object_v_x_in_patch_X_4_object_v_16 = 0;
   object_w_x*in_patch_X_4_object_u_16-dummy_object_w_x_in_patch_X_4_object_u_16 = 0;
   object_w_x*in_patch_X_4_object_v_16-dummy_object_w_x_in_patch_X_4_object_v_16 = 0;
   object_wp_x*in_patch_X_4_object_u_16-dummy_object_wp_x_in_patch_X_4_object_u_16 = 0;
   object_wp_x*in_patch_X_4_object_v_16-dummy_object_wp_x_in_patch_X_4_object_v_16 = 0;
   X_4_w_x*in_patch_X_4_object_l_16-dummy_X_4_w_x_in_patch_X_4_object_l_16 = 0;
   X_4_wp_x*in_patch_X_4_object_l_16-dummy_X_4_wp_x_in_patch_X_4_object_l_16 = 0;
   object_u_y*in_patch_X_4_object_u_16-dummy_object_u_y_in_patch_X_4_object_u_16 = 0;
   object_u_y*in_patch_X_4_object_v_16-dummy_object_u_y_in_patch_X_4_object_v_16 = 0;
   object_v_y*in_patch_X_4_object_u_16-dummy_object_v_y_in_patch_X_4_object_u_16 = 0;
   object_v_y*in_patch_X_4_object_v_16-dummy_object_v_y_in_patch_X_4_object_v_16 = 0;
   object_w_y*in_patch_X_4_object_u_16-dummy_object_w_y_in_patch_X_4_object_u_16 = 0;
   object_w_y*in_patch_X_4_object_v_16-dummy_object_w_y_in_patch_X_4_object_v_16 = 0;
   object_wp_y*in_patch_X_4_object_u_16-dummy_object_wp_y_in_patch_X_4_object_u_16 = 0;
   object_wp_y*in_patch_X_4_object_v_16-dummy_object_wp_y_in_patch_X_4_object_v_16 = 0;
   X_4_w_y*in_patch_X_4_object_l_16-dummy_X_4_w_y_in_patch_X_4_object_l_16 = 0;
   X_4_wp_y*in_patch_X_4_object_l_16-dummy_X_4_wp_y_in_patch_X_4_object_l_16 = 0;
   object_u_z*in_patch_X_4_object_u_16-dummy_object_u_z_in_patch_X_4_object_u_16 = 0;
   object_u_z*in_patch_X_4_object_v_16-dummy_object_u_z_in_patch_X_4_object_v_16 = 0;
   object_v_z*in_patch_X_4_object_u_16-dummy_object_v_z_in_patch_X_4_object_u_16 = 0;
   object_v_z*in_patch_X_4_object_v_16-dummy_object_v_z_in_patch_X_4_object_v_16 = 0;
   object_w_z*in_patch_X_4_object_u_16-dummy_object_w_z_in_patch_X_4_object_u_16 = 0;
   object_w_z*in_patch_X_4_object_v_16-dummy_object_w_z_in_patch_X_4_object_v_16 = 0;
   object_wp_z*in_patch_X_4_object_u_16-dummy_object_wp_z_in_patch_X_4_object_u_16 = 0;
   object_wp_z*in_patch_X_4_object_v_16-dummy_object_wp_z_in_patch_X_4_object_v_16 = 0;
   X_4_w_z*in_patch_X_4_object_l_16-dummy_X_4_w_z_in_patch_X_4_object_l_16 = 0;
   X_4_wp_z*in_patch_X_4_object_l_16-dummy_X_4_wp_z_in_patch_X_4_object_l_16 = 0;
   object_u_x*in_patch_X_3_object_w_14-dummy_object_u_x_in_patch_X_3_object_w_14 = 0;
   object_u_x*in_patch_X_4_object_w_16-dummy_object_u_x_in_patch_X_4_object_w_16 = 0;
   object_v_x*in_patch_X_3_object_w_14-dummy_object_v_x_in_patch_X_3_object_w_14 = 0;
   object_v_x*in_patch_X_4_object_w_16-dummy_object_v_x_in_patch_X_4_object_w_16 = 0;
   object_w_x*in_patch_X_3_object_w_14-dummy_object_w_x_in_patch_X_3_object_w_14 = 0;
   object_w_x*in_patch_X_4_object_w_16-dummy_object_w_x_in_patch_X_4_object_w_16 = 0;
   object_wp_x*in_patch_X_3_object_w_14-dummy_object_wp_x_in_patch_X_3_object_w_14 = 0;
   object_wp_x*in_patch_X_4_object_w_16-dummy_object_wp_x_in_patch_X_4_object_w_16 = 0;
   object_u_y*in_patch_X_3_object_w_14-dummy_object_u_y_in_patch_X_3_object_w_14 = 0;
   object_u_y*in_patch_X_4_object_w_16-dummy_object_u_y_in_patch_X_4_object_w_16 = 0;
   object_v_y*in_patch_X_3_object_w_14-dummy_object_v_y_in_patch_X_3_object_w_14 = 0;
   object_v_y*in_patch_X_4_object_w_16-dummy_object_v_y_in_patch_X_4_object_w_16 = 0;
   object_w_y*in_patch_X_3_object_w_14-dummy_object_w_y_in_patch_X_3_object_w_14 = 0;
   object_w_y*in_patch_X_4_object_w_16-dummy_object_w_y_in_patch_X_4_object_w_16 = 0;
   object_wp_y*in_patch_X_3_object_w_14-dummy_object_wp_y_in_patch_X_3_object_w_14 = 0;
   object_wp_y*in_patch_X_4_object_w_16-dummy_object_wp_y_in_patch_X_4_object_w_16 = 0;
   object_u_z*in_patch_X_3_object_w_14-dummy_object_u_z_in_patch_X_3_object_w_14 = 0;
   object_u_z*in_patch_X_4_object_w_16-dummy_object_u_z_in_patch_X_4_object_w_16 = 0;
   object_v_z*in_patch_X_3_object_w_14-dummy_object_v_z_in_patch_X_3_object_w_14 = 0;
   object_v_z*in_patch_X_4_object_w_16-dummy_object_v_z_in_patch_X_4_object_w_16 = 0;
   object_w_z*in_patch_X_3_object_w_14-dummy_object_w_z_in_patch_X_3_object_w_14 = 0;
   object_w_z*in_patch_X_4_object_w_16-dummy_object_w_z_in_patch_X_4_object_w_16 = 0;
   object_wp_z*in_patch_X_3_object_w_14-dummy_object_wp_z_in_patch_X_3_object_w_14 = 0;
   object_wp_z*in_patch_X_4_object_w_16-dummy_object_wp_z_in_patch_X_4_object_w_16 = 0;
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
   in_patch_X_3_object_u_14*in_patch_X_3_object_v_14-in_patch_X_3_object_w_14 = 0;
   in_patch_X_4_object_u_16*in_patch_X_4_object_v_16-in_patch_X_4_object_w_16 = 0;

[SEARCH]

 MIN 172.582639308*cos_0_palm_p32_6^2+11.6568542495*w1_p32_p33_x_7^2+23.313708499*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+23.313708499*cos_p43_p44_12^2+4*cos_p34_X_3_13^2+4*in_patch_X_3_object_u_14^2+4*in_patch_X_3_object_v_14^2+4*cos_p44_X_4_15^2+4*in_patch_X_4_object_u_16^2+4*in_patch_X_4_object_v_16^2-345.165278616*cos_0_palm_p32_6-23.313708499*w1_p32_p33_x_7-46.627416998*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-46.627416998*cos_p43_p44_12-8*cos_p34_X_3_13-4*in_patch_X_3_object_u_14-4*in_patch_X_3_object_v_14-8*cos_p44_X_4_15-4*in_patch_X_4_object_u_16-4*in_patch_X_4_object_v_16+438.763258362

==========================================================================
Cuik executed in 32 processors
SOLUTIONS (to input file /home/porta/cuik/CuikSuite/examples/IJRR/teapot/2_contacts_index_thumb/SAHandplusTeapot_kin.cuik):

   1 (err:1 min:6.16124 tm:109):{ 241  p12_u_x:[-0.00167489771894,0.00167489771894] p12_u_y:[0.0342736213774,0.0343142060683] p12_u_z:[0.999411083751,0.999412487238] p12_v_x:[-0,0] p12_v_y:[-0.999412485579,-0.999411095951] p12_v_z:[0.0342736694745,0.0343141582969] p13_u_x:[-0.00457362764014,0.00457362764014] p13_u_y:[0.0342733109798,0.034314177121] p13_u_z:[0.99940203721,0.999412485475] p13_v_x:[-0,0] p13_v_y:[-0.999412485579,-0.999411095951] p13_v_z:[0.0342736694745,0.0343141582969] p14_u_x:[-0.0097349461207,0.0097349461207] p14_u_y:[0.0342720453796,0.0343141583837] p14_u_z:[0.999365145412,0.999412488745] p14_v_x:[-0,0] p14_v_y:[-0.999412485579,-0.999411095951] p14_v_z:[0.0342736694745,0.0343141582969] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.665321090247,0.669464581492] p32_u_y:[-0.0422542165241,-0.0314602330076] p32_u_z:[0.741810125841,0.745517756972] p32_v_x:[-0,0] p32_v_y:[-0.999125699903,-0.998367848038] p32_v_z:[-0.0568558237135,-0.0423315503736] p33_u_x:[0.912618045898,0.914661788162] p33_u_y:[-0.0230134409883,-0.0170846206414] p33_u_z:[0.4035587784,0.408247128857] p33_v_x:[-0,0] p33_v_y:[-0.999125699903,-0.998367848038] p33_v_z:[-0.0568558237135,-0.0423315503736] p34_u_x:[0.999986645018,1] p34_u_y:[-0.000243602278907,1.00171846395e-11] p34_u_z:[-0,0.00419982134996] p34_v_x:[-0,0] p34_v_y:[-0.999125699903,-0.998367848038] p34_v_z:[-0.0568558237135,-0.0423315503736] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.00495803780364,2.99250190956e-11] p40_v_y:[0.999982359263,1] p40_v_z:[-0,0] p42_u_x:[0.570013384077,0.573606388138] p42_u_y:[-0,0.0041022699765] p42_u_z:[0.819137171241,0.821639883916] p42_v_x:[-0.00715079045623,1.7612180063e-11] p42_v_y:[0.999969695539,1] p42_v_z:[-0,0.00273121379883] p43_u_x:[0.464929718133,0.468789576879] p43_u_y:[-0,0.00335279554057] p43_u_z:[0.883310480593,0.88535194724] p43_v_x:[-0.00715079045623,1.7612180063e-11] p43_v_y:[0.999969695539,1] p43_v_z:[-0,0.00273121379883] p44_u_x:[0.351174454577,0.356803865701] p44_u_y:[-0,0.00255151027389] p44_u_z:[0.934174892074,0.93631233175] p44_v_x:[-0.00715079045623,1.7612180063e-11] p44_v_y:[0.999969695539,1] p44_v_z:[-0,0.00273121379883] object_u_x:[-0.0744259162763,-0.0660783978763] object_u_y:[-0.984452166169,-0.980417138167] object_u_z:[0.159673292842,0.183682496495] object_v_x:[-0,0.00207579541278] object_v_y:[-0.184271150606,-0.160140479722] object_v_z:[-0.987149992211,-0.982875214075] X_3_u_x:[-0,2.44847494617e-11] X_3_u_y:[0.999999999985,1] X_3_u_z:[-0,1.10229193943e-11] X_3_v_x:[0.410494290972,0.420698135534] X_3_v_y:[-0,1.58950986294e-11] X_3_v_z:[0.907200682724,0.911849303434] X_4_u_x:[0.0944833341679,0.118369558192] X_4_u_y:[-0,1.00029782351e-11] X_4_u_z:[0.992968182711,0.995469764861] X_4_v_x:[-0,1.11322136841e-10] X_4_v_y:[0.999999999985,1] X_4_v_z:[-0,1.00709205322e-11] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412485579,-0.999411095951] uni_v_palm_p12_z_0:[0.0342736694745,0.0343141582969] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.74727054581e-05,5.74727054581e-05] w2_palm_p12_z_0:[-0.00167391370313,0.0016739137135] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.00167489771894,0.00167489771894] w1_p12_p13_y_1:[0.0342736213774,0.0343142060683] w1_p12_p13_z_1:[0.999411083751,0.999412487238] w2_p12_p13_x_1:[-0.00457362764014,0.00457362764014] w2_p12_p13_y_1:[0.0342733109798,0.034314177121] w2_p12_p13_z_1:[0.99940203721,0.999412485475] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00457362764014,0.00457362764014] w1_p13_p14_y_2:[0.0342733109798,0.034314177121] w1_p13_p14_z_2:[0.99940203721,0.999412485475] w2_p13_p14_x_2:[-0.0097349461207,0.0097349461207] w2_p13_p14_y_2:[0.0342720453796,0.0343141583837] w2_p13_p14_z_2:[0.999365145412,0.999412488745] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999125699903,-0.998367848038] uni_v_palm_p32_z_6:[-0.0568558237135,-0.0423315503736] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.998246115457,0.998707605219] w2_palm_p32_y_6:[-0.00306891162364,-0.00218593596456] w2_palm_p32_z_6:[0.0517918057757,0.0573560763282] cos_0_palm_p32_6:[0.99975661412,0.999999490904] cos_1_palm_p32_6:[0.998246115457,0.998707605219] w1_p32_p33_x_7:[0.998246115457,0.998707605219] w1_p32_p33_y_7:[-0.00306891162364,-0.00218593596456] w1_p32_p33_z_7:[0.0517918057757,0.0573560763282] w2_p32_p33_x_7:[0.912618045898,0.914661788162] w2_p32_p33_y_7:[-0.0230134409883,-0.0170846206414] w2_p32_p33_z_7:[0.4035587784,0.408247128857] cos_p32_p33_7:[0.932784653963,0.934629175763] w1_p33_p34_x_8:[0.932535165735,0.934397115239] w1_p33_p34_y_8:[0.015253974556,0.0205315543399] w1_p33_p34_z_8:[-0.360478792229,-0.35575304736] w2_p33_p34_x_8:[0.999986645018,1] w2_p33_p34_y_8:[-0.000243602278907,1.00171846395e-11] w2_p33_p34_z_8:[-0,0.00419982134996] cos_p33_p34_8:[0.932784653963,0.934629175763] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.999982359263] w2_palm_p40_y_9:[-0.00495803780364,2.99250190956e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.710604627904] uni_u_p40_p42_x_10:[-0.819149697375,-0.819135246959] uni_u_p40_p42_y_10:[-0.00406137516638,2.45130703358e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.00715079045623,1.7612180063e-11] uni_v_p40_p42_y_10:[0.999969695539,1] uni_v_p40_p42_z_10:[-0,0.00273121379883] w1_p40_p42_x_10:[-0.00495803780364,2.99250190956e-11] w1_p40_p42_y_10:[0.999982359263,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.17759503609,-0.173609167837] w2_p40_p42_y_10:[-0.00397230484958,1.1241297338e-10] w2_p40_p42_z_10:[0.983611705422,0.984824713136] cos_0_p40_p42_10:[0.999942851121,1] cos_1_p40_p42_10:[0.707106781187,0.709941559042] w1_p42_p43_x_11:[-0.17759503609,-0.173609167837] w1_p42_p43_y_11:[-0.00397230484958,1.1241297338e-10] w1_p42_p43_z_11:[0.983611705422,0.984824713136] w2_p42_p43_x_11:[0.464929718133,0.468789576879] w2_p42_p43_y_11:[-0,0.00335279554057] w2_p42_p43_z_11:[0.883310480593,0.88535194724] cos_p42_p43_11:[0.787105902724,0.790979171167] w1_p43_p44_x_12:[-0.296973578049,-0.293041334427] w1_p43_p44_y_12:[-0.00537910533831,1.50966012543e-05] w1_p43_p44_z_12:[0.955025044957,0.95634031149] w2_p43_p44_x_12:[0.351174454577,0.356803865701] w2_p43_p44_y_12:[-0,0.00255151027389] w2_p43_p44_z_12:[0.934174892074,0.93631233175] cos_p43_p44_12:[0.787105902724,0.790979171167] sph_w1_p34_X_3_x_13:[0.140021003114,0.144175647386] sph_w1_p34_X_3_y_13:[0.0393480487235,0.0562957275662] sph_w1_p34_X_3_z_13:[-0.989282847337,-0.9878417894] sph_w2_p34_X_3_x_13:[0.907251536308,0.911849303328] sph_w2_p34_X_3_y_13:[-1.2374815009e-09,1.7906394016e-11] sph_w2_p34_X_3_z_13:[-0.420264797484,-0.409988694383] cos_p34_X_3_13:[0.532885693098,0.545208669488] in_patch_X_3_object_u_14:[-0,0.031037212555] in_patch_X_3_object_v_14:[0.735844336247,0.750000000008] in_patch_X_3_object_l_14:[10.5618705228,10.6521048307] sph_w1_p44_X_4_x_15:[-0.877916501109,-0.874974568209] sph_w1_p44_X_4_y_15:[-0.00759107000928,7.4976013254e-05] sph_w1_p44_X_4_z_15:[0.47881821395,0.484196018701] sph_w2_p44_X_4_x_15:[-0.99546976474,-0.992968182508] sph_w2_p44_X_4_y_15:[-1.3416084453e-12,3.16122091207e-10] sph_w2_p44_X_4_z_15:[0.0944833339545,0.11836955815] cos_p44_X_4_15:[0.916734753003,0.92893251444] in_patch_X_4_object_u_16:[0.454075428536,0.500000000005] in_patch_X_4_object_v_16:[-0,0.00589982737238] in_patch_X_4_object_l_16:[8.64043688535,8.67181069219] p14_r_x:[-4.55076689459,-4.04923310541] p14_r_y:[-36.8130477043,-36.8090715135] p14_r_z:[243.172174696,243.1725412] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }
   2 (err:1 min:6.05508 tm:110):{ 241  p12_u_x:[-0.0016760038278,0.0016760038278] p12_u_y:[0.0342735673597,0.0343142178552] p12_u_z:[0.999411083751,0.999412489092] p12_v_x:[-0,0] p12_v_y:[-0.999412487431,-0.99941109555] p12_v_z:[0.0342736155095,0.0343141700063] p13_u_x:[-0.00457687320936,0.00457687320936] p13_u_y:[0.0342732565063,0.0343141794683] p13_u_z:[0.999402024366,0.999412487327] p13_v_x:[-0,0] p13_v_y:[-0.999412487431,-0.99941109555] p13_v_z:[0.0342736155095,0.0343141700063] p14_u_x:[-0.00974214138485,0.00974214138485] p14_u_y:[0.034272012294,0.0343141701043] p14_u_z:[0.999365077828,0.999412489117] p14_v_x:[-0,0] p14_v_y:[-0.999412487431,-0.99941109555] p14_v_z:[0.0342736155095,0.0343141700063] p22_u_x:[-0,0] p22_u_y:[-0,0] p22_u_z:[1,1] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[-0,0] p23_u_y:[-0,0] p23_u_z:[1,1] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0,0] p24_u_y:[-0,0] p24_u_z:[1,1] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.658863352795,0.670895797043] p32_u_y:[-0.0461838887944,-0.024000558294] p32_u_z:[0.740205217967,0.751064695145] p32_v_x:[-0,0] p32_v_y:[-0.999474894189,-0.997986601988] p32_v_z:[-0.0623620421767,-0.0324309912613] p33_u_x:[0.911314806105,0.915337176965] p33_u_y:[-0.0252871720004,-0.0128820428236] p33_u_z:[0.401967602484,0.411042615803] p33_v_x:[-0,0] p33_v_y:[-0.999474894189,-0.997986601988] p33_v_z:[-0.0623620421767,-0.0324309912613] p34_u_x:[0.999905489048,1] p34_u_y:[-0.000750847128235,1.00217221272e-11] p34_u_z:[-0,0.0116615230482] p34_v_x:[-0,0] p34_v_y:[-0.999474894189,-0.997986601988] p34_v_z:[-0.0623620421767,-0.0324309912613] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.0126034772266,3.00657079067e-11] p40_v_y:[0.999897554123,1] p40_v_z:[-0,0] p42_u_x:[0.56330600601,0.573768517198] p42_u_y:[-0,0.0047645041987] p42_u_z:[0.819017514267,0.826267970713] p42_v_x:[-0.0106569291394,1.78550453928e-11] p42_v_y:[0.999928157067,1] p42_v_z:[-0,0.00373805862823] p43_u_x:[0.459625379416,0.469351292652] p43_u_y:[-0,0.00591742611069] p43_u_z:[0.88299170332,0.888131789309] p43_v_x:[-0.0106569291394,1.78550453928e-11] p43_v_y:[0.999928157067,1] p43_v_z:[-0,0.00373805862823] p44_u_x:[0.340937464913,0.356803865701] p44_u_y:[-0,0.00461519649392] p44_u_z:[0.934167919251,0.940105123377] p44_v_x:[-0.0106569291394,1.78550453928e-11] p44_v_y:[0.999928157067,1] p44_v_z:[-0,0.00373805862823] object_u_x:[-0.0720061568973,-0.0594947838833] object_u_y:[-0.981476357519,-0.97041132579] object_u_z:[0.183682496491,0.232550516543] object_v_x:[-0,0.00476267380604] object_v_y:[-0.232597127098,-0.183517739288] object_v_z:[-0.983083758222,-0.972298799958] X_3_u_x:[-0,2.54982495343e-11] X_3_u_y:[0.999999999985,1] X_3_u_z:[-0,1.10432941973e-11] X_3_v_x:[0.394530435474,0.422395941036] X_3_v_y:[-0,1.58950986294e-11] X_3_v_z:[0.906373564764,0.918837271827] X_4_u_x:[0.0723266183672,0.121296249222] X_4_u_y:[-0,1.00029782351e-11] X_4_u_z:[0.99261635081,0.997380095875] X_4_v_x:[-0,1.58892031005e-10] X_4_v_y:[0.999999999985,1] X_4_v_z:[-0,1.00743857301e-11] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412487431,-0.99941109555] uni_v_palm_p12_z_0:[0.0342736155095,0.0343141700063] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-5.75106802779e-05,5.75106802779e-05] w2_palm_p12_z_0:[-0.00167501917562,0.00167501917562] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[-0.0016760038278,0.0016760038278] w1_p12_p13_y_1:[0.0342735673597,0.0343142178552] w1_p12_p13_z_1:[0.999411083751,0.999412489092] w2_p12_p13_x_1:[-0.00457687320936,0.00457687320936] w2_p12_p13_y_1:[0.0342732565063,0.0343141794683] w2_p12_p13_z_1:[0.999402024366,0.999412487327] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.00457687320936,0.00457687320936] w1_p13_p14_y_2:[0.0342732565063,0.0343141794683] w1_p13_p14_z_2:[0.999402024366,0.999412487327] w2_p13_p14_x_2:[-0.00974214138485,0.00974214138485] w2_p13_p14_y_2:[0.034272012294,0.0343141701043] w2_p13_p14_z_2:[0.999365077828,0.999412489117] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-0,0] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[-0,0] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[1,1] w2_p22_p23_x_4:[-0,0] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[1,1] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0,0] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[1,1] w2_p23_p24_x_5:[-0,0] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[1,1] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.999474894189,-0.997986601988] uni_v_palm_p32_z_6:[-0.0623620421767,-0.0324309912613] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.997304252999,0.999022254136] w2_palm_p32_y_6:[-0.00375003794687,-0.00140106631657] w2_palm_p32_z_6:[0.0497384795167,0.0659122829588] cos_0_palm_p32_6:[0.999570996344,1] cos_1_palm_p32_6:[0.997304252999,0.999022254136] w1_p32_p33_x_7:[0.997304252999,0.999022254136] w1_p32_p33_y_7:[-0.00375003794687,-0.00140106631657] w1_p32_p33_z_7:[0.0497384795167,0.0659122829588] w2_p32_p33_x_7:[0.911314806105,0.915337176965] w2_p32_p33_y_7:[-0.0252871720004,-0.0128820428236] w2_p32_p33_z_7:[0.401967602484,0.411042615803] cos_p32_p33_7:[0.931148963671,0.936721836757] w1_p33_p34_x_8:[0.931718005728,0.935525344343] w1_p33_p34_y_8:[0.0116788480038,0.0226318261183] w1_p33_p34_z_8:[-0.361920719314,-0.352749306622] w2_p33_p34_x_8:[0.999905489048,1] w2_p33_p34_y_8:[-0.000750847128235,1.00217221272e-11] w2_p33_p34_z_8:[-0,0.0116615230482] cos_p33_p34_8:[0.931148963671,0.936721836757] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-1,-0.999897554123] w2_palm_p40_y_9:[-0.0126034772266,3.00657079067e-11] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.707106781187,0.715969487271] uni_u_p40_p42_x_10:[-0.819149697375,-0.819065778854] uni_u_p40_p42_y_10:[-0.0103241345559,2.46283155329e-11] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.0106569291394,1.78550453928e-11] uni_v_p40_p42_y_10:[0.999928157067,1] uni_v_p40_p42_z_10:[-0,0.00373805862823] w1_p40_p42_x_10:[-0.0126034772266,3.00657079067e-11] w1_p40_p42_y_10:[0.999897554123,1] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.187245394393,-0.17346267237] w2_p40_p42_y_10:[-0.00715884828106,1.1241297338e-10] w2_p40_p42_z_10:[0.982746716044,0.98501556098] cos_0_p40_p42_10:[0.999769774073,1] cos_1_p40_p42_10:[0.707106781187,0.718367424692] w1_p42_p43_x_11:[-0.187245394393,-0.17346267237] w1_p42_p43_y_11:[-0.00715884828106,1.1241297338e-10] w1_p42_p43_z_11:[0.982746716044,0.98501556098] w2_p42_p43_x_11:[0.459625379416,0.469351292652] w2_p42_p43_y_11:[-0,0.00591742611069] w2_p42_p43_z_11:[0.88299170332,0.888131789309] cos_p42_p43_11:[0.783646818863,0.793938509258] w1_p43_p44_x_12:[-0.302364958793,-0.292434409086] w1_p43_p44_y_12:[-0.00647264077044,0.000192377795374] w1_p43_p44_z_12:[0.952642368755,0.956171154489] w2_p43_p44_x_12:[0.340937464913,0.356803865701] w2_p43_p44_y_12:[-0,0.00461519649392] w2_p43_p44_z_12:[0.934167919251,0.940105123377] cos_p43_p44_12:[0.783646818863,0.793938509258] sph_w1_p34_X_3_x_13:[0.140020979188,0.151578459779] sph_w1_p34_X_3_y_13:[0.0321008865052,0.0617479084765] sph_w1_p34_X_3_z_13:[-0.989872695313,-0.986880339573] sph_w2_p34_X_3_x_13:[0.906373564639,0.918837271701] sph_w2_p34_X_3_y_13:[-1.2374815009e-09,1.7906394016e-11] sph_w2_p34_X_3_z_13:[-0.422395940963,-0.39504773391] cos_p34_X_3_13:[0.519157485745,0.549285195485] in_patch_X_3_object_u_14:[-0,0.0707180668893] in_patch_X_3_object_v_14:[0.718158055359,0.750000000008] in_patch_X_3_object_l_14:[10.410392197,10.6521048307] sph_w1_p44_X_4_x_15:[-0.883105396233,-0.874897003525] sph_w1_p44_X_4_y_15:[-0.0103285006773,7.07503021211e-05] sph_w1_p44_X_4_z_15:[0.469210075568,0.484140540604] sph_w2_p44_X_4_x_15:[-0.998017576335,-0.992616350758] sph_w2_p44_X_4_y_15:[-1.3416084453e-12,3.16122091207e-10] sph_w2_p44_X_4_z_15:[0.0688387820015,0.120460440836] cos_p44_X_4_15:[0.904387973015,0.933720067959] in_patch_X_4_object_u_16:[0.402975434955,0.500000000005] in_patch_X_4_object_v_16:[-0,0.0118291470602] in_patch_X_4_object_l_16:[8.63470177267,8.71579454429] p14_r_x:[-4.55093925585,-4.04906074416] p14_r_y:[-36.8130544393,-36.8090706439] p14_r_z:[243.172174367,243.172541382] p24_r_x:[-4.3,-4.3] p24_r_y:[-0,0] p24_r_z:[247.95,247.95] }


Cuik executed in 31 (31) child processors
STATITISTICS FOR Cuik:

Volume of the search space: 2.21317e+15
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 0.172161
Number of processors: 32
User time in process: 114.000000 seg (1.900000 min)
Box level information:
  N processed boxes :   1454
  Max depth         :     49
  Types of boxes:
    N solution boxes:      2 (0) ( 0.14%)
    N empty boxes   :    180  (12.38%)
    N bisected boxes:   1272  (87.48%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :   1680
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

