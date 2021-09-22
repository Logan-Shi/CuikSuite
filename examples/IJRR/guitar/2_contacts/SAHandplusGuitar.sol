
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
Equations from file: /home/porta/cuik/CuikSuite/examples/IJRR/guitar/2_contacts/SAHandplusGuitar_kin.cuik
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
   cos_p34_X_3_13 : [0.980785280403,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_14 : [0,1]
   in_patch_X_3_object_v_14 : [0,1]

[DUMMY VARS]
   in_patch_X_3_object_w_14 : [0,1]

[SECONDARY VARS]
   in_patch_X_3_object_l_14 : [382.253093035,382.253093035]
   sph_w1_p44_X_4_x_15 : [-1,1]
   sph_w1_p44_X_4_y_15 : [-1,1]
   sph_w1_p44_X_4_z_15 : [-1,1]
   sph_w2_p44_X_4_x_15 : [-1,1]
   sph_w2_p44_X_4_y_15 : [-1,1]
   sph_w2_p44_X_4_z_15 : [-1,1]
   cos_p44_X_4_15 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_4_object_u_16 : [0,1]
   in_patch_X_4_object_v_16 : [0,1]

[DUMMY VARS]
   in_patch_X_4_object_w_16 : [0,1]

[SECONDARY VARS]
   in_patch_X_4_object_l_16 : [382.265354258,382.265354258]

[CARTESIAN VARS]
   p14_r_x : [-2972.57682136,2972.57682136]
   p14_r_y : [-2972.57682136,2972.57682136]
   p14_r_z : [-2972.57682136,2972.57682136]
   p24_r_x : [-2972.57682136,2972.57682136]
   p24_r_y : [-2972.57682136,2972.57682136]
   p24_r_z : [-2972.57682136,2972.57682136]

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
   0.309016994375*p12_u_x+0.951056516295*p12_w_x-0.951056516295*p12_wp_x-w2_palm_p12_x_0 = -0;
   0.309016994375*p12_u_y+0.951056516295*p12_w_y-0.951056516295*p12_wp_y-w2_palm_p12_y_0 = -0;
   0.309016994375*p12_u_z+0.951056516295*p12_w_z-0.951056516295*p12_wp_z-w2_palm_p12_z_0 = -0;
   uni_v_palm_p12_x_0*w1_palm_p12_x_0+uni_v_palm_p12_y_0*w1_palm_p12_y_0+uni_v_palm_p12_z_0*w1_palm_p12_z_0-cos_0_palm_p12_0 = 0;
   uni_u_palm_p12_x_0*w2_palm_p12_x_0+uni_u_palm_p12_y_0*w2_palm_p12_y_0+uni_u_palm_p12_z_0*w2_palm_p12_z_0-cos_1_palm_p12_0 = 0;
   p12_v_x-p13_v_x = -0;
   p12_v_y-p13_v_y = -0;
   p12_v_z-p13_v_z = -0;
   p12_w_x-p12_wp_x-w1_p12_p13_x_1 = -0;
   p12_w_y-p12_wp_y-w1_p12_p13_y_1 = -0;
   p12_w_z-p12_wp_z-w1_p12_p13_z_1 = -0;
   p13_u_x-w2_p12_p13_x_1 = -0;
   p13_u_y-w2_p12_p13_y_1 = -0;
   p13_u_z-w2_p12_p13_z_1 = -0;
   w1_p12_p13_x_1*w2_p12_p13_x_1+w1_p12_p13_y_1*w2_p12_p13_y_1+w1_p12_p13_z_1*w2_p12_p13_z_1-cos_p12_p13_1 = 0;
   p13_v_x-p14_v_x = -0;
   p13_v_y-p14_v_y = -0;
   p13_v_z-p14_v_z = -0;
   p13_w_x-p13_wp_x-w1_p13_p14_x_2 = -0;
   p13_w_y-p13_wp_y-w1_p13_p14_y_2 = -0;
   p13_w_z-p13_wp_z-w1_p13_p14_z_2 = -0;
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
   0.309016994375*p22_u_x+0.951056516295*p22_w_x-0.951056516295*p22_wp_x-w2_palm_p22_x_3 = -0;
   0.309016994375*p22_u_y+0.951056516295*p22_w_y-0.951056516295*p22_wp_y-w2_palm_p22_y_3 = -0;
   0.309016994375*p22_u_z+0.951056516295*p22_w_z-0.951056516295*p22_wp_z-w2_palm_p22_z_3 = -0;
   uni_v_palm_p22_x_3*w1_palm_p22_x_3+uni_v_palm_p22_y_3*w1_palm_p22_y_3+uni_v_palm_p22_z_3*w1_palm_p22_z_3-cos_0_palm_p22_3 = 0;
   uni_u_palm_p22_x_3*w2_palm_p22_x_3+uni_u_palm_p22_y_3*w2_palm_p22_y_3+uni_u_palm_p22_z_3*w2_palm_p22_z_3-cos_1_palm_p22_3 = 0;
   p22_v_x-p23_v_x = -0;
   p22_v_y-p23_v_y = -0;
   p22_v_z-p23_v_z = -0;
   p22_w_x-p22_wp_x-w1_p22_p23_x_4 = -0;
   p22_w_y-p22_wp_y-w1_p22_p23_y_4 = -0;
   p22_w_z-p22_wp_z-w1_p22_p23_z_4 = -0;
   p23_u_x-w2_p22_p23_x_4 = -0;
   p23_u_y-w2_p22_p23_y_4 = -0;
   p23_u_z-w2_p22_p23_z_4 = -0;
   w1_p22_p23_x_4*w2_p22_p23_x_4+w1_p22_p23_y_4*w2_p22_p23_y_4+w1_p22_p23_z_4*w2_p22_p23_z_4-cos_p22_p23_4 = 0;
   p23_v_x-p24_v_x = -0;
   p23_v_y-p24_v_y = -0;
   p23_v_z-p24_v_z = -0;
   p23_w_x-p23_wp_x-w1_p23_p24_x_5 = -0;
   p23_w_y-p23_wp_y-w1_p23_p24_y_5 = -0;
   p23_w_z-p23_wp_z-w1_p23_p24_z_5 = -0;
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
   p34_v_x+sph_w1_p34_X_3_x_13 = 0;
   p34_v_y+sph_w1_p34_X_3_y_13 = 0;
   p34_v_z+sph_w1_p34_X_3_z_13 = 0;
   X_3_w_x-X_3_wp_x-sph_w2_p34_X_3_x_13 = -0;
   X_3_w_y-X_3_wp_y-sph_w2_p34_X_3_y_13 = -0;
   X_3_w_z-X_3_wp_z-sph_w2_p34_X_3_z_13 = -0;
   sph_w1_p34_X_3_x_13*sph_w2_p34_X_3_x_13+sph_w1_p34_X_3_y_13*sph_w2_p34_X_3_y_13+sph_w1_p34_X_3_z_13*sph_w2_p34_X_3_z_13-cos_p34_X_3_13 = 0;
   in_patch_X_3_object_l_14^2 = 146117.427135;
   X_3_w_x*in_patch_X_3_object_l_14-X_3_wp_x*in_patch_X_3_object_l_14+54.75938*object_u_x+378.310504*object_w_x-378.310504*object_wp_x = 0;
   X_3_w_y*in_patch_X_3_object_l_14-X_3_wp_y*in_patch_X_3_object_l_14+54.75938*object_u_y+378.310504*object_w_y-378.310504*object_wp_y = 0;
   X_3_w_z*in_patch_X_3_object_l_14-X_3_wp_z*in_patch_X_3_object_l_14+54.75938*object_u_z+378.310504*object_w_z-378.310504*object_wp_z = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_15 = -0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_15 = -0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_15 = -0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_15 = -0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_15 = -0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_15 = -0;
   sph_w1_p44_X_4_x_15*sph_w2_p44_X_4_x_15+sph_w1_p44_X_4_y_15*sph_w2_p44_X_4_y_15+sph_w1_p44_X_4_z_15*sph_w2_p44_X_4_z_15-cos_p44_X_4_15 = 0;
   in_patch_X_4_object_l_16^2 = 146126.801066;
   X_4_w_x*in_patch_X_4_object_l_16-X_4_wp_x*in_patch_X_4_object_l_16-54.75938*object_u_x-378.322893*object_w_x+378.322893*object_wp_x = 0;
   X_4_w_y*in_patch_X_4_object_l_16-X_4_wp_y*in_patch_X_4_object_l_16-54.75938*object_u_y-378.322893*object_w_y+378.322893*object_wp_y = 0;
   X_4_w_z*in_patch_X_4_object_l_16-X_4_wp_z*in_patch_X_4_object_l_16-54.75938*object_u_z-378.322893*object_w_z+378.322893*object_wp_z = 0;
   30.536*object_u_x*in_patch_X_3_object_v_14-30.537*object_u_x*in_patch_X_4_object_v_16+12.389*object_v_x*in_patch_X_3_object_u_14+12.389*object_v_x*in_patch_X_4_object_u_16-4.42*object_w_x*in_patch_X_3_object_v_14+4.42*object_w_x*in_patch_X_4_object_v_16+4.42*object_wp_x*in_patch_X_3_object_v_14-4.42*object_wp_x*in_patch_X_4_object_v_16-67.8*p32_u_x-30*p33_u_x-8.146*p34_u_x+1.271*p34_v_x+0.335*p34_w_x-0.335*p34_wp_x+97*p40_u_x+6*p40_v_x-87*p40_w_x+87*p40_wp_x+67.8*p42_u_x+30*p43_u_x+20*p44_u_x+1.29*object_u_x-12.389*object_v_x+3.96*object_w_x-3.96*object_wp_x-13*X_3_w_x+13*X_3_wp_x+13*X_4_w_x-13*X_4_wp_x = -1.3;
   30.536*object_u_y*in_patch_X_3_object_v_14-30.537*object_u_y*in_patch_X_4_object_v_16+12.389*object_v_y*in_patch_X_3_object_u_14+12.389*object_v_y*in_patch_X_4_object_u_16-4.42*object_w_y*in_patch_X_3_object_v_14+4.42*object_w_y*in_patch_X_4_object_v_16+4.42*object_wp_y*in_patch_X_3_object_v_14-4.42*object_wp_y*in_patch_X_4_object_v_16-67.8*p32_u_y-30*p33_u_y-8.146*p34_u_y+1.271*p34_v_y+0.335*p34_w_y-0.335*p34_wp_y+97*p40_u_y+6*p40_v_y-87*p40_w_y+87*p40_wp_y+67.8*p42_u_y+30*p43_u_y+20*p44_u_y+1.29*object_u_y-12.389*object_v_y+3.96*object_w_y-3.96*object_wp_y-13*X_3_w_y+13*X_3_wp_y+13*X_4_w_y-13*X_4_wp_y = 13.065;
   30.536*object_u_z*in_patch_X_3_object_v_14-30.537*object_u_z*in_patch_X_4_object_v_16+12.389*object_v_z*in_patch_X_3_object_u_14+12.389*object_v_z*in_patch_X_4_object_u_16-4.42*object_w_z*in_patch_X_3_object_v_14+4.42*object_w_z*in_patch_X_4_object_v_16+4.42*object_wp_z*in_patch_X_3_object_v_14-4.42*object_wp_z*in_patch_X_4_object_v_16-67.8*p32_u_z-30*p33_u_z-8.146*p34_u_z+1.271*p34_v_z+0.335*p34_w_z-0.335*p34_wp_z+97*p40_u_z+6*p40_v_z-87*p40_w_z+87*p40_wp_z+67.8*p42_u_z+30*p43_u_z+20*p44_u_z+1.29*object_u_z-12.389*object_v_z+3.96*object_w_z-3.96*object_wp_z-13*X_3_w_z+13*X_3_wp_z+13*X_4_w_z-13*X_4_wp_z = 145.43;


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

 MIN 172.582639308*cos_0_palm_p32_6^2+11.6568542495*cos_1_palm_p32_6^2+11.6568542495*cos_p32_p33_7^2+11.6568542495*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+11.6568542495*cos_p42_p43_11^2+11.6568542495*cos_p43_p44_12^2+2708.51907038*cos_p34_X_3_13^2+4*in_patch_X_3_object_u_14^2+4*in_patch_X_3_object_v_14^2+cos_p44_X_4_15^2+4*in_patch_X_4_object_u_16^2+4*in_patch_X_4_object_v_16^2-345.165278616*cos_0_palm_p32_6-23.313708499*cos_1_palm_p32_6-23.313708499*cos_p32_p33_7-23.313708499*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-23.313708499*cos_p42_p43_11-23.313708499*cos_p43_p44_12-5417.03814077*cos_p34_X_3_13-4*in_patch_X_3_object_u_14-4*in_patch_X_3_object_v_14-2*cos_p44_X_4_15-4*in_patch_X_4_object_u_16-4*in_patch_X_4_object_v_16+3140.28232874




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
%   p12_w_x=p12_w_x
%   p12_w_y= -0
%   p12_w_z=w1_p12_p13_z_1
%   p12_wp_x=p12_wp_x
%   p12_wp_y=-w1_p12_p13_y_1
%   p12_wp_z= -0
%   p13_u_x=p13_u_x
%   p13_u_y=p13_u_y
%   p13_u_z=p13_u_z
%   p13_v_x= -0
%   p13_v_y=+0.0343212495372*p14_v_z -1.00058880074
%   p13_v_z=p14_v_z
%   p13_w_x=p13_w_x
%   p13_w_y= -0
%   p13_w_z=w1_p13_p14_z_2
%   p13_wp_x=p13_wp_x
%   p13_wp_y=-w1_p13_p14_y_2
%   p13_wp_z= -0
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
%   p22_u_y= -0
%   p22_u_z=-0.324919696233*p22_u_x +1.05146222424
%   p22_v_x= -0
%   p22_v_y= -1
%   p22_v_z= -0
%   p22_w_x= -0
%   p22_w_y= -0
%   p22_w_z=-p22_u_x
%   p22_wp_x=+0.324919696233*p22_u_x -1.05146222424
%   p22_wp_y= -0
%   p22_wp_z= -0
%   p23_u_x=p23_u_x
%   p23_u_y= -0
%   p23_u_z=p23_u_z
%   p23_v_x= -0
%   p23_v_y= -1
%   p23_v_z= -0
%   p23_w_x= -0
%   p23_w_y= -0
%   p23_w_z=-p23_u_x
%   p23_wp_x=-p23_u_z
%   p23_wp_y= -0
%   p23_wp_z= -0
%   p24_u_x=p24_u_x
%   p24_u_y= -0
%   p24_u_z=p24_u_z
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
%   w1_p12_p13_x_1=-0.324919696233*p12_u_x +1.05146222424
%   w1_p12_p13_y_1=w1_p12_p13_y_1
%   w1_p12_p13_z_1=w1_p12_p13_z_1
%   w2_p12_p13_x_1=p13_u_x
%   w2_p12_p13_y_1=p13_u_y
%   w2_p12_p13_z_1=p13_u_z
%   cos_p12_p13_1= +1
%   w1_p13_p14_x_2=w1_p13_p14_x_2
%   w1_p13_p14_y_2=w1_p13_p14_y_2
%   w1_p13_p14_z_2=w1_p13_p14_z_2
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
%   w2_palm_p22_z_3=-1.05146222424*p22_u_x +0.324919696233
%   cos_0_palm_p22_3= +1
%   cos_1_palm_p22_3= +1
%   w1_p22_p23_x_4=-0.324919696233*p22_u_x +1.05146222424
%   w1_p22_p23_y_4= -0
%   w1_p22_p23_z_4=-p22_u_x
%   w2_p22_p23_x_4=p23_u_x
%   w2_p22_p23_y_4= -0
%   w2_p22_p23_z_4=p23_u_z
%   cos_p22_p23_4= +1
%   w1_p23_p24_x_5=p23_u_z
%   w1_p23_p24_y_5= -0
%   w1_p23_p24_z_5=-p23_u_x
%   w2_p23_p24_x_5=p24_u_x
%   w2_p23_p24_y_5= -0
%   w2_p23_p24_z_5=p24_u_z
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
%   sph_w1_p34_X_3_x_13= -0
%   sph_w1_p34_X_3_y_13=-p34_v_y
%   sph_w1_p34_X_3_z_13=-p34_v_z
%   sph_w2_p34_X_3_x_13=sph_w2_p34_X_3_x_13
%   sph_w2_p34_X_3_y_13=sph_w2_p34_X_3_y_13
%   sph_w2_p34_X_3_z_13=sph_w2_p34_X_3_z_13
%   cos_p34_X_3_13=cos_p34_X_3_13
%   in_patch_X_3_object_u_14=in_patch_X_3_object_u_14
%   in_patch_X_3_object_v_14=in_patch_X_3_object_v_14
%   in_patch_X_3_object_w_14=No in simplification
%   in_patch_X_3_object_l_14= +382.253093035
%   sph_w1_p44_X_4_x_15=sph_w1_p44_X_4_x_15
%   sph_w1_p44_X_4_y_15=sph_w1_p44_X_4_y_15
%   sph_w1_p44_X_4_z_15=sph_w1_p44_X_4_z_15
%   sph_w2_p44_X_4_x_15=sph_w2_p44_X_4_x_15
%   sph_w2_p44_X_4_y_15=sph_w2_p44_X_4_y_15
%   sph_w2_p44_X_4_z_15=sph_w2_p44_X_4_z_15
%   cos_p44_X_4_15=cos_p44_X_4_15
%   in_patch_X_4_object_u_16=in_patch_X_4_object_u_16
%   in_patch_X_4_object_v_16=in_patch_X_4_object_v_16
%   in_patch_X_4_object_w_16=No in simplification
%   in_patch_X_4_object_l_16= +382.265354258
%   p14_r_x=p14_r_x
%   p14_r_y=p14_r_y
%   p14_r_z=p14_r_z
%   p24_r_x=p24_r_x
%   p24_r_y= -0
%   p24_r_z=p24_r_z

[SYSTEM VARS]
   p12_u_x : [0.158384440259,1]
   p12_u_y : [-1,1]
   p12_u_z : [-1,1]

[DUMMY VARS]
   p12_w_x : [-1,1]
   p12_wp_x : [-1,1]

[SYSTEM VARS]
   p13_u_x : [-1,1]
   p13_u_y : [-1,1]
   p13_u_z : [-1,1]

[DUMMY VARS]
   p13_w_x : [-1,1]
   p13_wp_x : [-1,1]

[SYSTEM VARS]
   p14_u_x : [-1,1]
   p14_u_y : [-1,1]
   p14_u_z : [-1,1]
   p14_v_z : [0.0171555735608,1]
   p22_u_x : [0.158384440259,1]
   p23_u_x : [-1,1]
   p23_u_z : [-1,1]
   p24_u_x : [-1,1]
   p24_u_z : [-1,1]
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
   w1_p12_p13_y_1 : [-1,1]
   w1_p12_p13_z_1 : [-1,1]
   w1_p13_p14_x_2 : [-1,1]
   w1_p13_p14_y_2 : [-1,1]
   w1_p13_p14_z_2 : [-1,1]
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
   sph_w2_p34_X_3_x_13 : [-1,1]
   sph_w2_p34_X_3_y_13 : [-1,1]
   sph_w2_p34_X_3_z_13 : [-1,1]
   cos_p34_X_3_13 : [0.980785280403,1]

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
   cos_p44_X_4_15 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_4_object_u_16 : [0,1]
   in_patch_X_4_object_v_16 : [0,1]

[CARTESIAN VARS]
   p14_r_x : [-2972.57682136,2972.57682136]
   p14_r_y : [-2972.57682136,2972.57682136]
   p14_r_z : [-2972.57682136,2972.57682136]
   p24_r_x : [-2972.57682136,2972.57682136]
   p24_r_z : [-2972.57682136,2972.57682136]

[DUMMY VARS]
   dummy_p14_v_z_2 : [0,1]
   dummy_p12_u_y_p14_v_z : [-1,1]
   dummy_p12_u_z_p14_v_z : [-1,1]
   dummy_p13_u_y_p14_v_z : [-1,1]
   dummy_p13_u_z_p14_v_z : [-1,1]
   dummy_p14_u_y_p14_v_z : [-1,1]
   dummy_p14_u_z_p14_v_z : [-1,1]
   dummy_p22_u_x_2 : [0,1]
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
   dummy_p13_u_y_w1_p12_p13_y_1 : [-1,1]
   dummy_p13_u_z_w1_p12_p13_z_1 : [-1,1]
   dummy_p14_u_x_w1_p13_p14_x_2 : [-1,1]
   dummy_p14_u_y_w1_p13_p14_y_2 : [-1,1]
   dummy_p14_u_z_w1_p13_p14_z_2 : [-1,1]
   dummy_p22_u_x_p23_u_x : [-1,1]
   dummy_p22_u_x_p23_u_z : [-1,1]
   dummy_p23_u_x_p24_u_z : [-1,1]
   dummy_p23_u_z_p24_u_x : [-1,1]
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
   dummy_p34_v_y_sph_w2_p34_X_3_y_13 : [-1,1]
   dummy_p34_v_z_sph_w2_p34_X_3_z_13 : [-1,1]
   dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15 : [-1,1]
   dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15 : [-1,1]
   dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 : [-1,1]
   dummy_object_u_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_u_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_w_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_u_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_w_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_u_z_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_u_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_v_z_in_patch_X_3_object_u_14 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_u_16 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_w_z_in_patch_X_4_object_v_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_v_14 : [-1,1]
   dummy_object_wp_z_in_patch_X_4_object_v_16 : [-1,1]

[SYSTEM EQS]

   p12_u_x^2+p12_u_y^2+p12_u_z^2 = 1;
   0.0686829158287*p14_v_z-1.00117794817*dummy_p14_v_z_2 = 0.00117794816892;
   1.00058880074*p12_u_y-0.0343212495372*dummy_p12_u_y_p14_v_z-dummy_p12_u_z_p14_v_z = -0;
   p13_u_x^2+p13_u_y^2+p13_u_z^2 = 1;
   1.00058880074*p13_u_y-0.0343212495372*dummy_p13_u_y_p14_v_z-dummy_p13_u_z_p14_v_z = -0;
   p14_u_x^2+p14_u_y^2+p14_u_z^2 = 1;
   1.00058880074*p14_u_y-0.0343212495372*dummy_p14_u_y_p14_v_z-dummy_p14_u_z_p14_v_z = -0;
   0.683281573*p22_u_x-1.105572809*dummy_p22_u_x_2 = 0.105572809;
   p23_u_x^2+p23_u_z^2 = 1;
   p24_u_x^2+p24_u_z^2 = 1;
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
   0.309016994375*p12_u_y-w2_palm_p12_y_0+0.951056516295*w1_p12_p13_y_1 = 0;
   0.309016994375*p12_u_z-w2_palm_p12_z_0+0.951056516295*w1_p12_p13_z_1 = 0;
   0.324919696233*p12_u_x+p12_w_x-p12_wp_x = 1.05146222424;
   1.05146222424*p13_u_x-0.324919696233*dummy_p12_u_x_p13_u_x+dummy_p13_u_y_w1_p12_p13_y_1+dummy_p13_u_z_w1_p12_p13_z_1 = 1;
   p13_w_x-p13_wp_x-w1_p13_p14_x_2 = 0;
   dummy_p14_u_x_w1_p13_p14_x_2+dummy_p14_u_y_w1_p13_p14_y_2+dummy_p14_u_z_w1_p13_p14_z_2 = 1;
   1.05146222424*p23_u_x-0.324919696233*dummy_p22_u_x_p23_u_x-dummy_p22_u_x_p23_u_z = 1;
   dummy_p23_u_x_p24_u_z-dummy_p23_u_z_p24_u_x = -1;
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
   X_3_w_x-X_3_wp_x-sph_w2_p34_X_3_x_13 = 0;
   X_3_w_y-X_3_wp_y-sph_w2_p34_X_3_y_13 = 0;
   X_3_w_z-X_3_wp_z-sph_w2_p34_X_3_z_13 = 0;
   cos_p34_X_3_13+dummy_p34_v_y_sph_w2_p34_X_3_y_13+dummy_p34_v_z_sph_w2_p34_X_3_z_13 = 0;
   54.75938*object_u_x+378.310504*object_w_x-378.310504*object_wp_x+382.253093035*sph_w2_p34_X_3_x_13 = 0;
   54.75938*object_u_y+378.310504*object_w_y-378.310504*object_wp_y+382.253093035*sph_w2_p34_X_3_y_13 = 0;
   54.75938*object_u_z+378.310504*object_w_z-378.310504*object_wp_z+382.253093035*sph_w2_p34_X_3_z_13 = 0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_15 = 0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_15 = 0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_15 = 0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_15 = 0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_15 = 0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_15 = 0;
   cos_p44_X_4_15-dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15-dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15-dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 = -0;
   0.00179327285827*object_u_x+382.265611148*sph_w2_p34_X_3_x_13+382.265354258*sph_w2_p44_X_4_x_15 = 0;
   0.00179327285827*object_u_y+382.265611148*sph_w2_p34_X_3_y_13+382.265354258*sph_w2_p44_X_4_y_15 = 0;
   0.00179327285827*object_u_z+382.265611148*sph_w2_p34_X_3_z_13+382.265354258*sph_w2_p44_X_4_z_15 = 0;
   67.8*p32_u_x+30*p33_u_x+8.146*p34_u_x-0.335*p34_w_x+0.335*p34_wp_x-6*p40_v_x-87*p40_v_y-67.8*p42_u_x-30*p43_u_x-20*p44_u_x-0.716880908578*object_u_x+12.389*object_v_x-30.0012579882*sph_w2_p44_X_4_x_15-30.536*dummy_object_u_x_in_patch_X_3_object_v_14+30.537*dummy_object_u_x_in_patch_X_4_object_v_16-12.389*dummy_object_v_x_in_patch_X_3_object_u_14-12.389*dummy_object_v_x_in_patch_X_4_object_u_16+4.42*dummy_object_w_x_in_patch_X_3_object_v_14-4.42*dummy_object_w_x_in_patch_X_4_object_v_16-4.42*dummy_object_wp_x_in_patch_X_3_object_v_14+4.42*dummy_object_wp_x_in_patch_X_4_object_v_16 = 1.3;
   67.8*p32_u_y+30*p33_u_y+8.146*p34_u_y-1.271*p34_v_y+0.335*p34_wp_y+87*p40_v_x-6*p40_v_y-67.8*p42_u_y-30*p43_u_y-20*p44_u_y-0.716880908578*object_u_y+12.389*object_v_y-30.0012579882*sph_w2_p44_X_4_y_15-30.536*dummy_object_u_y_in_patch_X_3_object_v_14+30.537*dummy_object_u_y_in_patch_X_4_object_v_16-12.389*dummy_object_v_y_in_patch_X_3_object_u_14-12.389*dummy_object_v_y_in_patch_X_4_object_u_16+4.42*dummy_object_w_y_in_patch_X_3_object_v_14-4.42*dummy_object_w_y_in_patch_X_4_object_v_16-4.42*dummy_object_wp_y_in_patch_X_3_object_v_14+4.42*dummy_object_wp_y_in_patch_X_4_object_v_16 = -13.065;
   67.8*p32_u_z+30*p33_u_z+8.146*p34_u_z-1.271*p34_v_z-0.335*p34_w_z-67.8*p42_u_z-30*p43_u_z-20*p44_u_z-0.716880908578*object_u_z+12.389*object_v_z-30.0012579882*sph_w2_p44_X_4_z_15-30.536*dummy_object_u_z_in_patch_X_3_object_v_14+30.537*dummy_object_u_z_in_patch_X_4_object_v_16-12.389*dummy_object_v_z_in_patch_X_3_object_u_14-12.389*dummy_object_v_z_in_patch_X_4_object_u_16+4.42*dummy_object_w_z_in_patch_X_3_object_v_14-4.42*dummy_object_w_z_in_patch_X_4_object_v_16-4.42*dummy_object_wp_z_in_patch_X_3_object_v_14+4.42*dummy_object_wp_z_in_patch_X_4_object_v_16 = -48.43;

[COORD EQS]

   67.8*p12_u_x+30*p13_u_x-p14_r_x = 4.3;
   67.8*p12_u_y+30*p13_u_y-p14_r_y = 40.165;
   67.8*p12_u_z+30*p13_u_z-p14_r_z = -145.43;
   67.8*p22_u_x+30*p23_u_x-p24_r_x = 4.3;
   22.0295554046*p22_u_x-30*p23_u_z+p24_r_z = 221.439138803;

[DUMMY EQS]

   p14_v_z^2-dummy_p14_v_z_2 = 0;
   p12_u_y*p14_v_z-dummy_p12_u_y_p14_v_z = 0;
   p12_u_z*p14_v_z-dummy_p12_u_z_p14_v_z = 0;
   p13_u_y*p14_v_z-dummy_p13_u_y_p14_v_z = 0;
   p13_u_z*p14_v_z-dummy_p13_u_z_p14_v_z = 0;
   p14_u_y*p14_v_z-dummy_p14_u_y_p14_v_z = 0;
   p14_u_z*p14_v_z-dummy_p14_u_z_p14_v_z = 0;
   p22_u_x^2-dummy_p22_u_x_2 = 0;
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
   p13_u_y*w1_p12_p13_y_1-dummy_p13_u_y_w1_p12_p13_y_1 = 0;
   p13_u_z*w1_p12_p13_z_1-dummy_p13_u_z_w1_p12_p13_z_1 = 0;
   p14_u_x*w1_p13_p14_x_2-dummy_p14_u_x_w1_p13_p14_x_2 = 0;
   p14_u_y*w1_p13_p14_y_2-dummy_p14_u_y_w1_p13_p14_y_2 = 0;
   p14_u_z*w1_p13_p14_z_2-dummy_p14_u_z_w1_p13_p14_z_2 = 0;
   p22_u_x*p23_u_x-dummy_p22_u_x_p23_u_x = 0;
   p22_u_x*p23_u_z-dummy_p22_u_x_p23_u_z = 0;
   p23_u_x*p24_u_z-dummy_p23_u_x_p24_u_z = 0;
   p23_u_z*p24_u_x-dummy_p23_u_z_p24_u_x = 0;
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
   p34_v_y*sph_w2_p34_X_3_y_13-dummy_p34_v_y_sph_w2_p34_X_3_y_13 = 0;
   p34_v_z*sph_w2_p34_X_3_z_13-dummy_p34_v_z_sph_w2_p34_X_3_z_13 = 0;
   sph_w1_p44_X_4_x_15*sph_w2_p44_X_4_x_15-dummy_sph_w1_p44_X_4_x_15_sph_w2_p44_X_4_x_15 = 0;
   sph_w1_p44_X_4_y_15*sph_w2_p44_X_4_y_15-dummy_sph_w1_p44_X_4_y_15_sph_w2_p44_X_4_y_15 = 0;
   sph_w1_p44_X_4_z_15*sph_w2_p44_X_4_z_15-dummy_sph_w1_p44_X_4_z_15_sph_w2_p44_X_4_z_15 = 0;
   object_u_x*in_patch_X_3_object_v_14-dummy_object_u_x_in_patch_X_3_object_v_14 = 0;
   object_u_x*in_patch_X_4_object_v_16-dummy_object_u_x_in_patch_X_4_object_v_16 = 0;
   object_v_x*in_patch_X_3_object_u_14-dummy_object_v_x_in_patch_X_3_object_u_14 = 0;
   object_v_x*in_patch_X_4_object_u_16-dummy_object_v_x_in_patch_X_4_object_u_16 = 0;
   object_w_x*in_patch_X_3_object_v_14-dummy_object_w_x_in_patch_X_3_object_v_14 = 0;
   object_w_x*in_patch_X_4_object_v_16-dummy_object_w_x_in_patch_X_4_object_v_16 = 0;
   object_wp_x*in_patch_X_3_object_v_14-dummy_object_wp_x_in_patch_X_3_object_v_14 = 0;
   object_wp_x*in_patch_X_4_object_v_16-dummy_object_wp_x_in_patch_X_4_object_v_16 = 0;
   object_u_y*in_patch_X_3_object_v_14-dummy_object_u_y_in_patch_X_3_object_v_14 = 0;
   object_u_y*in_patch_X_4_object_v_16-dummy_object_u_y_in_patch_X_4_object_v_16 = 0;
   object_v_y*in_patch_X_3_object_u_14-dummy_object_v_y_in_patch_X_3_object_u_14 = 0;
   object_v_y*in_patch_X_4_object_u_16-dummy_object_v_y_in_patch_X_4_object_u_16 = 0;
   object_w_y*in_patch_X_3_object_v_14-dummy_object_w_y_in_patch_X_3_object_v_14 = 0;
   object_w_y*in_patch_X_4_object_v_16-dummy_object_w_y_in_patch_X_4_object_v_16 = 0;
   object_wp_y*in_patch_X_3_object_v_14-dummy_object_wp_y_in_patch_X_3_object_v_14 = 0;
   object_wp_y*in_patch_X_4_object_v_16-dummy_object_wp_y_in_patch_X_4_object_v_16 = 0;
   object_u_z*in_patch_X_3_object_v_14-dummy_object_u_z_in_patch_X_3_object_v_14 = 0;
   object_u_z*in_patch_X_4_object_v_16-dummy_object_u_z_in_patch_X_4_object_v_16 = 0;
   object_v_z*in_patch_X_3_object_u_14-dummy_object_v_z_in_patch_X_3_object_u_14 = 0;
   object_v_z*in_patch_X_4_object_u_16-dummy_object_v_z_in_patch_X_4_object_u_16 = 0;
   object_w_z*in_patch_X_3_object_v_14-dummy_object_w_z_in_patch_X_3_object_v_14 = 0;
   object_w_z*in_patch_X_4_object_v_16-dummy_object_w_z_in_patch_X_4_object_v_16 = 0;
   object_wp_z*in_patch_X_3_object_v_14-dummy_object_wp_z_in_patch_X_3_object_v_14 = 0;
   object_wp_z*in_patch_X_4_object_v_16-dummy_object_wp_z_in_patch_X_4_object_v_16 = 0;
   p12_u_y*p14_v_z-p12_w_x = 0;
   0.0343212495372*p12_u_x*p14_v_z-1.00058880074*p12_u_x-w1_p12_p13_z_1 = 0;
   0.0343212495372*p12_u_z*p14_v_z-1.00058880074*p12_u_z-p12_wp_x = 0;
   p12_u_x*p14_v_z+w1_p12_p13_y_1 = 0;
   p13_u_y*p14_v_z-p13_w_x = 0;
   0.0343212495372*p13_u_x*p14_v_z-1.00058880074*p13_u_x-w1_p13_p14_z_2 = 0;
   0.0343212495372*p13_u_z*p14_v_z-1.00058880074*p13_u_z-p13_wp_x = 0;
   p13_u_x*p14_v_z+w1_p13_p14_y_2 = 0;
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

[SEARCH]

 MIN 172.582639308*cos_0_palm_p32_6^2+11.6568542495*w1_p32_p33_x_7^2+23.313708499*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+23.313708499*cos_p43_p44_12^2+2708.51907038*cos_p34_X_3_13^2+4*in_patch_X_3_object_u_14^2+4*in_patch_X_3_object_v_14^2+cos_p44_X_4_15^2+4*in_patch_X_4_object_u_16^2+4*in_patch_X_4_object_v_16^2-345.165278616*cos_0_palm_p32_6-23.313708499*w1_p32_p33_x_7-46.627416998*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-46.627416998*cos_p43_p44_12-5417.03814077*cos_p34_X_3_13-4*in_patch_X_3_object_u_14-4*in_patch_X_3_object_v_14-2*cos_p44_X_4_15-4*in_patch_X_4_object_u_16-4*in_patch_X_4_object_v_16+3140.28232874

==========================================================================
Cuik executed in 32 processors
SOLUTIONS (to input file /home/porta/cuik/CuikSuite/examples/IJRR/guitar/2_contacts/SAHandplusGuitar_kin.cuik):

   1 (err:2.73132 min:5.42488 tm:67):{ 241  p12_u_x:[0.306397852165,0.309116060806] p12_u_y:[0.0326073217248,0.0326703802437] p12_u_z:[0.95046330706,0.951344867977] p12_v_x:[-0,0] p12_v_y:[-0.999412043167,-0.999410096608] p12_v_z:[0.0342865597951,0.0343432756441] p13_u_x:[0.948003594041,0.954362587616] p13_u_y:[-0.0109349456412,-0.0102422694019] p13_u_z:[-0.318213533055,-0.298542409304] p13_v_x:[-0,0] p13_v_y:[-0.999412043167,-0.999410096608] p13_v_z:[0.0342865597951,0.0343432756441] p14_u_x:[-0.312482031499,-0.246914325166] p14_u_y:[-0.0332807454857,-0.032569542125] p14_u_z:[-0.968489825048,-0.949363040173] p14_v_x:[-0,0] p14_v_y:[-0.999412043167,-0.999410096608] p14_v_z:[0.0342865597951,0.0343432756441] p22_u_x:[0.309005579307,0.309024737093] p22_u_y:[-0,0] p22_u_z:[0.951054000532,0.951060225278] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[0.951036193096,0.95108645817] p23_u_y:[-0,0] p23_u_z:[-0.309079535743,-0.308924827608] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0.311052588047,-0.306935176129] p24_u_y:[-0,0] p24_u_z:[-0.951732717707,-0.950394960353] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.311617151491,0.344525626559] p32_u_y:[0.0828936083947,0.127352226391] p32_u_z:[0.933855434656,0.943068509957] p32_v_x:[-0,0] p32_v_y:[-0.996097445749,-0.99100658836] p32_v_z:[0.0876819878303,0.133813085375] p33_u_x:[0.999596108039,1] p33_u_y:[-0.00363274456371,1.0090750271e-11] p33_u_z:[-0.0244840843319,0] p33_v_x:[-0,0] p33_v_y:[-0.996097445749,-0.99100658836] p33_v_z:[0.0876819878303,0.133813085375] p34_u_x:[0.936989490133,0.954480589203] p34_u_y:[-0.0473307805227,-0.0276425301045] p34_u_z:[-0.344910042498,-0.298553345957] p34_v_x:[-0,0] p34_v_y:[-0.996097445749,-0.99100658836] p34_v_z:[0.0876819878303,0.133813085375] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.573484988384,-0.536709868564] p40_v_y:[0.819207374837,0.842731463395] p40_v_z:[-0,0] p42_u_x:[-0,0.0135547166435] p42_u_y:[-0.00128372114173,0] p42_u_z:[0.999815361361,1] p42_v_x:[-0.574193535073,-0.535055126219] p42_v_y:[0.81882144803,0.844533521699] p42_v_z:[-0,0.00804594621155] p43_u_x:[-0,0.0134170449543] p43_u_y:[-0,0.0012834486607] p43_u_z:[0.99981848073,1] p43_v_x:[-0.574193535073,-0.535055126219] p43_v_y:[0.81882144803,0.844533521699] p43_v_z:[-0,0.00804594621155] p44_u_x:[-0,0.0140515413696] p44_u_y:[-0,0.00176911573632] p44_u_z:[0.999806254408,1] p44_v_x:[-0.574193535073,-0.535055126219] p44_v_y:[0.81882144803,0.844533521699] p44_v_z:[-0,0.00804594621155] object_u_x:[0.999562610049,1] object_u_y:[-0,0.0232949261613] object_u_z:[-0,1.48657863726e-08] object_v_x:[-4.7826921301e-07,1.00080163875e-11] object_v_y:[-0,2.15350566096e-09] object_v_z:[0.999999999985,1] X_3_u_x:[-0,1.49355925771e-08] X_3_u_y:[-2.17616715146e-09,0] X_3_u_z:[0.999999999985,1] X_3_v_x:[0.985958497732,0.989685920219] X_3_v_y:[0.143254247228,0.16582306762] X_3_v_z:[-9.0967047695e-08,1.06698270343e-08] X_4_u_x:[0.879433644452,0.913676747432] X_4_u_y:[0.126514279488,0.154347073024] X_4_u_z:[-0.452112063848,-0.386294397279] X_4_v_x:[0.379048548213,0.444039341385] X_4_v_y:[0.05396312805,0.0759430390515] X_4_v_z:[0.892682447157,0.923646197548] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412043167,-0.999410096608] uni_v_palm_p12_z_0:[0.0342865597951,0.0343432756441] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.6569877765e-06,9.44543429603e-05] w2_palm_p12_z_0:[-0.000104108197329,0.00275139200207] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[0.951024327658,0.951907527189] w1_p12_p13_y_1:[-0.0106160580822,-0.0105053282795] w1_p12_p13_z_1:[-0.308934313936,-0.306217700756] w2_p12_p13_x_1:[0.948003594041,0.954362587616] w2_p12_p13_y_1:[-0.0109349456412,-0.0102422694019] w2_p12_p13_z_1:[-0.318213533055,-0.298542409304] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.318401979116,-0.298650363683] w1_p13_p14_y_2:[-0.0327590349823,-0.0325036015559] w1_p13_p14_z_2:[-0.95380146371,-0.94744446722] w2_p13_p14_x_2:[-0.312482031499,-0.246914325166] w2_p13_p14_y_2:[-0.0332807454857,-0.032569542125] w2_p13_p14_z_2:[-0.968489825048,-0.949363040173] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-8.1411747902e-06,1.20025124769e-05] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[0.951054000532,0.951060225278] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[-0.309024737093,-0.309005579307] w2_p22_p23_x_4:[0.951036193096,0.95108645817] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[-0.309079535743,-0.308924827608] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0.309079535743,-0.308924827608] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[-0.95108645817,-0.951036193096] w2_p23_p24_x_5:[-0.311052588047,-0.306935176129] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[-0.951732717707,-0.950394960353] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.996097445749,-0.99100658836] uni_v_palm_p32_z_6:[0.0876819878303,0.133813085375] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.889472519726,0.907682078555] w2_palm_p32_y_6:[0.0361599544675,0.0605727553809] w2_palm_p32_z_6:[0.418726006263,0.448634072887] cos_0_palm_p32_6:[0.98563410278,0.992337905176] cos_1_palm_p32_6:[0.889472519726,0.907682078555] w1_p32_p33_x_7:[0.889472519726,0.907682078555] w1_p32_p33_y_7:[0.0361599544675,0.0605727553809] w1_p32_p33_z_7:[0.418726006263,0.448634072887] w2_p32_p33_x_7:[0.999596108039,1] w2_p32_p33_y_7:[-0.00363274456371,1.0090750271e-11] w2_p32_p33_z_7:[-0.0244840843319,0] cos_p32_p33_7:[0.879154152634,0.907472906157] w1_p33_p34_x_8:[0.689429731308,0.707106781195] w1_p33_p34_y_8:[-0.0971723327906,-0.0619924883559] w1_p33_p34_z_8:[-0.718373266787,-0.700743891328] w2_p33_p34_x_8:[0.936989490133,0.954480589203] w2_p33_p34_y_8:[-0.0473307805227,-0.0276425301045] w2_p33_p34_z_8:[-0.344910042498,-0.298553345957] cos_p33_p34_8:[0.879154152634,0.907472906157] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.842731463395,-0.819207374837] w2_palm_p40_y_9:[-0.573484988384,-0.536709868564] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.975412320069,0.985484926171] uni_u_p40_p42_x_10:[-0.690323223201,-0.671053473175] uni_u_p40_p42_y_10:[-0.469770054679,-0.439645726406] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.574193535073,-0.535055126219] uni_v_p40_p42_y_10:[0.81882144803,0.844533521699] uni_v_p40_p42_z_10:[-0,0.00804594621155] w1_p40_p42_x_10:[-0.573484988384,-0.536709868564] w1_p40_p42_y_10:[0.819207374837,0.842731463395] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.597181123075,-0.571929291505] w2_p40_p42_y_10:[-0.406902663609,-0.378469505196] w2_p40_p42_z_10:[0.707106781156,0.715059790085] cos_0_p40_p42_10:[0.996336405925,1] cos_1_p40_p42_10:[0.980262945098,0.986229732647] w1_p42_p43_x_11:[-0.597181123075,-0.571929291505] w1_p42_p43_y_11:[-0.406902663609,-0.378469505196] w1_p42_p43_z_11:[0.707106781156,0.715059790085] w2_p42_p43_x_11:[-0,0.0134170449543] w2_p42_p43_y_11:[-0,0.0012834486607] w2_p42_p43_z_11:[0.99981848073,1] cos_p42_p43_11:[0.707106781187,0.70824527692] w1_p43_p44_x_12:[-0.597178037263,-0.571896673534] w1_p43_p44_y_12:[-0.406043097853,-0.378317738153] w1_p43_p44_z_12:[0.707106781156,0.715059744098] w2_p43_p44_x_12:[-0,0.0140515413696] w2_p43_p44_y_12:[-0,0.00176911573632] w2_p43_p44_z_12:[0.999806254408,1] cos_p43_p44_12:[0.707106781187,0.70824527692] sph_w1_p34_X_3_x_13:[-0,0] sph_w1_p34_X_3_y_13:[0.99100658836,0.996097445749] sph_w1_p34_X_3_z_13:[-0.133813085375,-0.0876819878303] sph_w2_p34_X_3_x_13:[-0.165823051525,-0.143254249563] sph_w2_p34_X_3_y_13:[0.986085626765,0.989685933366] sph_w2_p34_X_3_z_13:[-1.11022302465e-27,2.12958707153e-09] cos_p34_X_3_13:[0.980785280403,0.985833178139] in_patch_X_3_object_u_14:[0.314107892375,0.37821578476] in_patch_X_3_object_v_14:[0.499999999995,0.543786187331] in_patch_X_3_object_l_14:[382.253093035,382.253093035] sph_w1_p44_X_4_x_15:[-0.836217523197,-0.810517503329] sph_w1_p44_X_4_y_15:[-0.568581492898,-0.52977618247] sph_w1_p44_X_4_z_15:[0.140021004692,0.151869810418] sph_w2_p44_X_4_x_15:[0.14324965466,0.165818472991] sph_w2_p44_X_4_y_15:[-0.989686598455,-0.986086398714] sph_w2_p44_X_4_z_15:[-2.12968440046e-09,4.22178933133e-16] cos_p44_X_4_15:[0.400389270237,0.445957276581] in_patch_X_4_object_u_16:[-0,0.0615954730844] in_patch_X_4_object_v_16:[0.956900388765,1] in_patch_X_4_object_l_16:[382.265354258,382.265354258] p14_r_x:[44.9138822001,45.2615353935] p14_r_y:[-38.2822719566,-38.257534732] p14_r_z:[200.325006229,200.974909765] p24_r_x:[45.1818434488,45.1843640211] p24_r_y:[-0,0] p24_r_z:[205.35907516,205.364138449] }
   2 (err:2.8149 min:5.27815 tm:67):{ 241  p12_u_x:[0.306397849274,0.309116060806] p12_u_y:[0.0326073245061,0.0326703802437] p12_u_z:[0.950463302881,0.951344867977] p12_v_x:[-0,0] p12_v_y:[-0.999412043267,-0.999410095721] p12_v_z:[0.0342865568954,0.0343433014674] p13_u_x:[0.94796376305,0.954362587626] p13_u_y:[-0.0109349538834,-0.0102396933534] p13_u_z:[-0.318213533083,-0.298474789664] p13_v_x:[-0,0] p13_v_y:[-0.999412043267,-0.999410095721] p13_v_z:[0.0342865568954,0.0343433014674] p14_u_x:[-0.345758896276,-0.312482031493] p14_u_y:[-0.0326240451757,-0.0321718783201] p14_u_z:[-0.949378735244,-0.93777171452] p14_v_x:[-0,0] p14_v_y:[-0.999412043267,-0.999410095721] p14_v_z:[0.0342865568954,0.0343433014674] p22_u_x:[0.309005579117,0.309024737169] p22_u_y:[-0,0] p22_u_z:[0.951054000507,0.95106022534] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[0.951036191749,0.951086461827] p23_u_y:[-0,0] p23_u_z:[-0.309079539887,-0.308924816349] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0.311052588047,-0.306928060094] p24_u_y:[-0,0] p24_u_z:[-0.951732717707,-0.95039270171] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.311404710275,0.345536017753] p32_u_y:[0.0782565271213,0.127353880418] p32_u_z:[0.933854925027,0.943279083143] p32_v_x:[-0,0] p32_v_y:[-0.996534258702,-0.99100658836] p32_v_z:[0.0827877854285,0.133813085375] p33_u_x:[0.999579498671,1] p33_u_y:[-0.00371890660221,1.0090750271e-11] p33_u_z:[-0.0254746560844,0] p33_v_x:[-0,0] p33_v_y:[-0.996534258702,-0.99100658836] p33_v_z:[0.0827877854285,0.133813085375] p34_u_x:[0.936629917896,0.954526183636] p34_u_y:[-0.0473338087291,-0.0260735375801] p34_u_z:[-0.346066437163,-0.298275031083] p34_v_x:[-0,0] p34_v_y:[-0.996534258702,-0.99100658836] p34_v_z:[0.0827877854285,0.133813085375] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.573584591564,-0.535688000754] p40_v_y:[0.819143662028,0.843385110381] p40_v_z:[-0,0] p42_u_x:[-0,0.0140969813987] p42_u_y:[-0.00128381419545,0] p42_u_z:[0.999807975272,1] p42_v_x:[-0.574193519998,-0.534041134947] p42_v_y:[0.818758586205,0.845181579137] p42_v_z:[-0,0.00835137903304] p43_u_x:[-0,0.0139575948755] p43_u_y:[-0,0.00128353504301] p43_u_z:[0.999811164409,1] p43_v_x:[-0.574193519998,-0.534041134947] p43_v_y:[0.818758586205,0.845181579137] p43_v_z:[-0,0.00835137903304] p44_u_x:[-0,0.0145903447898] p44_u_y:[-0,0.00176915652638] p44_u_z:[0.999798791545,1] p44_v_x:[-0.574193519998,-0.534041134947] p44_v_y:[0.818758586205,0.845181579137] p44_v_z:[-0,0.00835137903304] object_u_x:[0.999330473371,1] object_u_y:[-0,0.0334805695711] object_u_z:[-0,1.48657863726e-08] object_v_x:[-4.78269235393e-07,1.00080168558e-11] object_v_y:[-0,2.15350576175e-09] object_v_z:[0.999999999985,1] X_3_u_x:[-0,1.49355925771e-08] X_3_u_y:[-2.1762335396e-09,0] X_3_u_z:[0.999999999985,1] X_3_v_x:[0.983160599546,0.989685920219] X_3_v_y:[0.143254247228,0.182743639861] X_3_v_z:[-9.0967047695e-08,1.06698270343e-08] X_4_u_x:[0.879268534334,0.913676747432] X_4_u_y:[0.12651423285,0.155472550773] X_4_u_z:[-0.452199511905,-0.386294397279] X_4_v_x:[0.378962087985,0.444039341385] X_4_v_y:[0.05396312805,0.0764547276124] X_4_v_z:[0.892643754747,0.923621261739] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412043267,-0.999410095721] uni_v_palm_p12_z_0:[0.0342865568954,0.0343433014674] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.6569877765e-06,9.44543429603e-05] w2_palm_p12_z_0:[-0.000104108346203,0.00275141405617] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[0.951024327658,0.951907528128] w1_p12_p13_y_1:[-0.0106160660646,-0.0105053272919] w1_p12_p13_z_1:[-0.308934313983,-0.306217677566] w2_p12_p13_x_1:[0.94796376305,0.954362587626] w2_p12_p13_y_1:[-0.0109349538834,-0.0102396933534] w2_p12_p13_z_1:[-0.318213533083,-0.298474789664] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.31840137988,-0.298650301737] w1_p13_p14_y_2:[-0.0327590349823,-0.0325024134969] w1_p13_p14_z_2:[-0.953801463785,-0.94740454884] w2_p13_p14_x_2:[-0.345758896276,-0.312482031493] w2_p13_p14_y_2:[-0.0326240451757,-0.0321718783201] w2_p13_p14_z_2:[-0.949378735244,-0.93777171452] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-8.14125556881e-06,1.2002712957e-05] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[0.951054000507,0.95106022534] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[-0.309024737169,-0.309005579117] w2_p22_p23_x_4:[0.951036191749,0.951086461827] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[-0.309079539887,-0.308924816349] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0.309079539887,-0.308924816349] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[-0.951086461827,-0.951036191749] w2_p23_p24_x_5:[-0.311052588047,-0.306928060094] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[-0.951732717707,-0.95039270171] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.996534258702,-0.99100658836] uni_v_palm_p32_z_6:[0.0827877854285,0.133813085375] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.889434186551,0.908141071463] w2_palm_p32_y_6:[0.033993045167,0.0605860734242] w2_palm_p32_z_6:[0.417945488717,0.448759279797] cos_0_palm_p32_6:[0.98563410278,0.992948113833] cos_1_palm_p32_6:[0.889434186551,0.908141071463] w1_p32_p33_x_7:[0.889434186551,0.908141071463] w1_p32_p33_y_7:[0.033993045167,0.0605860734242] w1_p32_p33_z_7:[0.417945488717,0.448759279797] w2_p32_p33_x_7:[0.999579498671,1] w2_p32_p33_y_7:[-0.00371890660221,1.0090750271e-11] w2_p32_p33_z_7:[-0.0254746560844,0] cos_p32_p33_7:[0.878693851564,0.907939154951] w1_p33_p34_x_8:[0.688693921866,0.707106781195] w1_p33_p34_y_8:[-0.0972322156282,-0.0585327170126] w1_p33_p34_z_8:[-0.719288565218,-0.700743891312] w2_p33_p34_x_8:[0.936629917896,0.954526183636] w2_p33_p34_y_8:[-0.0473338087291,-0.0260735375801] w2_p33_p34_z_8:[-0.346066437163,-0.298275031083] cos_p33_p34_8:[0.878693851564,0.907939154951] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.843385110381,-0.819143662028] w2_palm_p40_y_9:[-0.573584591564,-0.535688000754] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.975151948625,0.985513422077] uni_u_p40_p42_x_10:[-0.690858657932,-0.671001282847] uni_u_p40_p42_y_10:[-0.469851644594,-0.438808663699] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.574193519998,-0.534041134947] uni_v_p40_p42_y_10:[0.818758586205,0.845181579137] uni_v_p40_p42_z_10:[-0,0.00835137903304] w1_p40_p42_x_10:[-0.573584591564,-0.535688000754] w1_p40_p42_y_10:[0.819143662028,0.843385110381] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.597639192827,-0.57126667118] w2_p40_p42_y_10:[-0.406908472565,-0.377748626276] w2_p40_p42_z_10:[0.707106781156,0.715370411493] cos_0_p40_p42_10:[0.996333910484,1] cos_1_p40_p42_10:[0.980176636982,0.986230810827] w1_p42_p43_x_11:[-0.597639192827,-0.57126667118] w1_p42_p43_y_11:[-0.406908472565,-0.377748626276] w1_p42_p43_z_11:[0.707106781156,0.715370411493] w2_p42_p43_x_11:[-0,0.0139575948755] w2_p42_p43_y_11:[-0,0.00128353504301] w2_p42_p43_z_11:[0.999811164409,1] cos_p42_p43_11:[0.707106781187,0.708245303907] w1_p43_p44_x_12:[-0.597636199101,-0.571235365643] w1_p43_p44_y_12:[-0.406046252246,-0.377601448828] w1_p43_p44_z_12:[0.707106781156,0.71536983729] w2_p43_p44_x_12:[-0,0.0145903447898] w2_p43_p44_y_12:[-0,0.00176915652638] w2_p43_p44_z_12:[0.999798791545,1] cos_p43_p44_12:[0.707106781187,0.708245303907] sph_w1_p34_X_3_x_13:[-0,0] sph_w1_p34_X_3_y_13:[0.99100658836,0.996534258702] sph_w1_p34_X_3_z_13:[-0.133813085375,-0.0827877854285] sph_w2_p34_X_3_x_13:[-0.167061732573,-0.143254249563] sph_w2_p34_X_3_y_13:[0.984889699477,0.989685933366] sph_w2_p34_X_3_z_13:[-1.11022302465e-27,2.12958707153e-09] cos_p34_X_3_13:[0.980785280403,0.985833231337] in_patch_X_3_object_u_14:[0.249999999997,0.328618991718] in_patch_X_3_object_v_14:[0.499999999995,0.54500599574] in_patch_X_3_object_l_14:[382.253093035,382.253093035] sph_w1_p44_X_4_x_15:[-0.836859073222,-0.810449026752] sph_w1_p44_X_4_y_15:[-0.568586022099,-0.528772419644] sph_w1_p44_X_4_z_15:[0.140021004692,0.152308531589] sph_w2_p44_X_4_x_15:[0.14324965466,0.167057154989] sph_w2_p44_X_4_y_15:[-0.989686598455,-0.984890518405] sph_w2_p44_X_4_z_15:[-2.12968440046e-09,4.22178933133e-16] cos_p44_X_4_15:[0.399887151312,0.446256712407] in_patch_X_4_object_u_16:[0.0641078923845,0.128215784772] in_patch_X_4_object_v_16:[0.955111697055,1] in_patch_X_4_object_l_16:[382.265354258,382.265354258] p14_r_x:[44.9126870718,45.2615353935] p14_r_y:[-38.2822720153,-38.2572517621] p14_r_z:[200.32500594,200.97693836] p24_r_x:[45.1818434488,45.1843640211] p24_r_y:[-0,0] p24_r_z:[205.359075034,205.364138789] }
   3 (err:2.71041 min:5.29995 tm:67):{ 241  p12_u_x:[0.306397107426,0.309116060806] p12_u_y:[0.03260729142,0.0326696723241] p12_u_z:[0.950463307998,0.951345135365] p12_v_x:[-0,0] p12_v_y:[-0.999412043068,-0.999410097493] p12_v_z:[0.0342865626936,0.0343432498525] p13_u_x:[0.94807892117,0.954310660871] p13_u_y:[-0.0109269581901,-0.0102453827375] p13_u_z:[-0.317981331912,-0.298703831835] p13_v_x:[-0,0] p13_v_y:[-0.999412043068,-0.999410097493] p13_v_z:[0.0342865626936,0.0343432498525] p14_u_x:[-0.345356492132,-0.312514873816] p14_u_y:[-0.0326236187166,-0.0321769644207] p14_u_z:[-0.949367752597,-0.937919809652] p14_v_x:[-0,0] p14_v_y:[-0.999412043068,-0.999410097493] p14_v_z:[0.0342865626936,0.0343432498525] p22_u_x:[0.309005579518,0.309024737016] p22_u_y:[-0,0] p22_u_z:[0.951054000557,0.951060225209] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[0.95103619275,0.951089181018] p23_u_y:[-0,0] p23_u_z:[-0.309079540707,-0.308924767537] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0.311073577206,-0.306906348563] p24_u_y:[-0,0] p24_u_z:[-0.951739719271,-0.950385831943] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.311699658748,0.34403491744] p32_u_y:[0.0836044319159,0.127345618923] p32_u_z:[0.933986416057,0.943029741185] p32_v_x:[-0,0] p32_v_y:[-0.996030839157,-0.99100658836] p32_v_z:[0.0884283150364,0.133813085375] p33_u_x:[0.99960985866,1] p33_u_y:[-0.00356832599739,1.0090750271e-11] p33_u_z:[-0.0240262067923,0] p33_v_x:[-0,0] p33_v_y:[-0.996030839157,-0.99100658836] p33_v_z:[0.0884283150364,0.133813085375] p34_u_x:[0.937174259914,0.954415257501] p34_u_y:[-0.0472850568329,-0.0278652858732] p34_u_z:[-0.344383982167,-0.298721579683] p34_v_x:[-0,0] p34_v_y:[-0.996030839157,-0.99100658836] p34_v_z:[0.0884283150364,0.133813085375] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.572878322383,-0.537267749095] p40_v_y:[0.819633245887,0.842394399584] p40_v_z:[-0,0] p42_u_x:[-0,0.0133101171169] p42_u_y:[-0.0012651485479,0] p42_u_z:[0.999819790397,1] p42_v_x:[-0.573571279025,-0.535635579382] p42_v_y:[0.819256400701,0.844166892877] p42_v_z:[-0,0.00790673344143] p43_u_x:[-0,0.013173360301] p43_u_y:[-0,0.00126489658397] p43_u_z:[0.999822824756,1] p43_v_x:[-0.573571279025,-0.535635579382] p43_v_y:[0.819256400701,0.844166892877] p43_v_z:[-0,0.00790673344143] p44_u_x:[-0,0.0137989522788] p44_u_y:[-0,0.00174261660113] p44_u_z:[0.99981107113,1] p44_v_x:[-0.573571279025,-0.535635579382] p44_v_y:[0.819256400701,0.844166892877] p44_v_z:[-0,0.00790673344143] object_u_x:[0.999572471387,1] object_u_y:[-0,0.0223162634532] object_u_z:[-0,1.48657863726e-08] object_v_x:[-4.7826785809e-07,1.00079880351e-11] object_v_y:[-0,2.15349956016e-09] object_v_z:[0.999999999985,1] X_3_u_x:[-0,1.49355925771e-08] X_3_u_y:[-2.17619605285e-09,0] X_3_u_z:[0.999999999985,1] X_3_v_x:[0.98317753529,0.989685920219] X_3_v_y:[0.143254247228,0.182652495446] X_3_v_z:[-9.0967047695e-08,1.06698270343e-08] X_4_u_x:[0.87935949882,0.91367628512] X_4_u_y:[0.126510027783,0.158178277224] X_4_u_z:[-0.452273008726,-0.386294397279] X_4_v_x:[0.378957258689,0.444107144477] X_4_v_y:[0.0539634166487,0.0777250634114] X_4_v_z:[0.89260766769,0.923645498338] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412043068,-0.999410097493] uni_v_palm_p12_z_0:[0.0342865626936,0.0343432498525] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.65788358435e-06,9.44839289572e-05] w2_palm_p12_z_0:[-0.000104108207301,0.00275224170562] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[0.951024327658,0.951907769169] w1_p12_p13_y_1:[-0.0106160501096,-0.010505303633] w1_p12_p13_z_1:[-0.308934313905,-0.306216894204] w2_p12_p13_x_1:[0.94807892117,0.954310660871] w2_p12_p13_y_1:[-0.0109269581901,-0.0102453827375] w2_p12_p13_z_1:[-0.317981331912,-0.298703831835] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.318169040677,-0.298879485712] w1_p13_p14_y_2:[-0.0327590349823,-0.032505088286] w1_p13_p14_z_2:[-0.9537495674,-0.947519835331] w2_p13_p14_x_2:[-0.345356492132,-0.312514873816] w2_p13_p14_y_2:[-0.0326236187166,-0.0321769644207] w2_p13_p14_z_2:[-0.949367752597,-0.937919809652] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-8.14109401354e-06,1.20022904185e-05] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[0.951054000557,0.951060225209] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[-0.309024737016,-0.309005579518] w2_p22_p23_x_4:[0.95103619275,0.951089181018] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[-0.309079540707,-0.308924767537] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0.309079540707,-0.308924767537] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[-0.951089181018,-0.95103619275] w2_p23_p24_x_5:[-0.311073577206,-0.306906348563] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[-0.951739719271,-0.950385831943] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.996030839157,-0.99100658836] uni_v_palm_p32_z_6:[0.0884283150364,0.133813085375] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.889526901853,0.907455496223] w2_palm_p32_y_6:[0.0365278192239,0.0605583749473] w2_palm_p32_z_6:[0.41916814566,0.448507183485] cos_0_palm_p32_6:[0.98563410278,0.992244863584] cos_1_palm_p32_6:[0.889526901853,0.907455496223] w1_p32_p33_x_7:[0.889526901853,0.907455496223] w1_p32_p33_y_7:[0.0365278192239,0.0605583749473] w1_p32_p33_z_7:[0.41916814566,0.448507183485] w2_p32_p33_x_7:[0.99960985866,1] w2_p32_p33_y_7:[-0.00356832599739,1.0090750271e-11] w2_p32_p33_z_7:[-0.0240262067923,0] cos_p32_p33_7:[0.879414115929,0.907246512026] w1_p33_p34_x_8:[0.689762633296,0.707106781204] w1_p33_p34_y_8:[-0.0971273506564,-0.0625203725759] w1_p33_p34_z_8:[-0.718053524127,-0.70074397522] w2_p33_p34_x_8:[0.937174259914,0.954415257501] w2_p33_p34_y_8:[-0.0472850568329,-0.0278652858732] w2_p33_p34_z_8:[-0.344383982167,-0.298721579683] cos_p33_p34_8:[0.879414115929,0.907246512026] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.842394399584,-0.819633245887] w2_palm_p40_y_9:[-0.572878322383,-0.537267749095] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.975568461066,0.985343143227] uni_u_p40_p42_x_10:[-0.690047117483,-0.671402325317] uni_u_p40_p42_y_10:[-0.469273104408,-0.440102714074] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.573571279025,-0.535635579382] uni_v_p40_p42_y_10:[0.819256400701,0.844166892877] uni_v_p40_p42_z_10:[-0,0.00790673344143] w1_p40_p42_x_10:[-0.572878322383,-0.537267749095] w1_p40_p42_y_10:[0.819633245887,0.842394399584] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.596921901988,-0.572327565172] w2_p40_p42_y_10:[-0.40644943143,-0.378881794567] w2_p40_p42_z_10:[0.707106781156,0.714914649054] cos_0_p40_p42_10:[0.996405304374,1] cos_1_p40_p42_10:[0.980343400119,0.986206968417] w1_p42_p43_x_11:[-0.596921901988,-0.572327565172] w1_p42_p43_y_11:[-0.40644943143,-0.378881794567] w1_p42_p43_z_11:[0.707106781156,0.714914649054] w2_p42_p43_x_11:[-0,0.013173360301] w2_p42_p43_y_11:[-0,0.00126489658397] w2_p42_p43_z_11:[0.999822824756,1] cos_p42_p43_11:[0.707106781187,0.708228473696] w1_p43_p44_x_12:[-0.596918810241,-0.572295659538] w1_p43_p44_y_12:[-0.405602446418,-0.378728359755] w1_p43_p44_z_12:[0.707106781156,0.714915334084] w2_p43_p44_x_12:[-0,0.0137989522788] w2_p43_p44_y_12:[-0,0.00174261660113] w2_p43_p44_z_12:[0.99981107113,1] cos_p43_p44_12:[0.707106781187,0.708228473696] sph_w1_p34_X_3_x_13:[-0,0] sph_w1_p34_X_3_y_13:[0.99100658836,0.996030839157] sph_w1_p34_X_3_z_13:[-0.133813085375,-0.0884283150364] sph_w2_p34_X_3_x_13:[-0.171219744979,-0.143254249563] sph_w2_p34_X_3_y_13:[0.986090101112,0.989685933366] sph_w2_p34_X_3_z_13:[-1.11022302465e-27,2.12958707153e-09] cos_p34_X_3_13:[0.980785280403,0.985767470448] in_patch_X_3_object_u_14:[0.0649550927238,0.125393974081] in_patch_X_3_object_v_14:[-0,0.0429818232613] in_patch_X_3_object_l_14:[382.253093035,382.253093035] sph_w1_p44_X_4_x_15:[-0.835854533562,-0.810951951971] sph_w1_p44_X_4_y_15:[-0.567964270765,-0.530350873737] sph_w1_p44_X_4_z_15:[0.140021004692,0.151656360022] sph_w2_p44_X_4_x_15:[0.14324965466,0.171215169691] sph_w2_p44_X_4_y_15:[-0.989686598455,-0.986090855668] sph_w2_p44_X_4_z_15:[-2.12968440046e-09,4.22178933133e-16] cos_p44_X_4_15:[0.40129658365,0.445669459343] in_patch_X_4_object_u_16:[0.249999999997,0.310438881373] in_patch_X_4_object_v_16:[0.457691020917,0.500000000005] in_patch_X_4_object_l_16:[382.265354258,382.265354258] p14_r_x:[44.9160915186,45.2615353935] p14_r_y:[-38.2820343889,-38.2582149861] p14_r_z:[200.331972324,200.970085224] p24_r_x:[45.1818435866,45.1843640211] p24_r_y:[-0,0] p24_r_z:[205.359075013,205.364140245] }
   4 (err:2.72044 min:5.27983 tm:67):{ 241  p12_u_x:[0.306397110311,0.309116060806] p12_u_y:[0.0326073272286,0.0326696723241] p12_u_z:[0.950463308829,0.951345135365] p12_v_x:[-0,0] p12_v_y:[-0.999412042968,-0.999410098377] p12_v_z:[0.0342865655909,0.0343432240926] p13_u_x:[0.948117597049,0.954282430759] p13_u_y:[-0.010922989447,-0.0102509511237] p13_u_z:[-0.317866077725,-0.29879554719] p13_v_x:[-0,0] p13_v_y:[-0.999412042968,-0.999410098377] p13_v_z:[0.0342865655909,0.0343432240926] p14_u_x:[-0.312514873822,-0.273528937398] p14_u_y:[-0.0330340476066,-0.0325691772643] p14_u_z:[-0.961312212221,-0.94935246885] p14_v_x:[-0,0] p14_v_y:[-0.999412042968,-0.999410098377] p14_v_z:[0.0342865655909,0.0343432240926] p22_u_x:[0.309005579709,0.309024736939] p22_u_y:[-0,0] p22_u_z:[0.951054000582,0.951060225147] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[0.951036194016,0.951089176535] p23_u_y:[-0,0] p23_u_z:[-0.309079536809,-0.308916472254] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0.311073577206,-0.306906348563] p24_u_y:[-0,0] p24_u_z:[-0.951739719271,-0.950385831943] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.31166356481,0.344102351262] p32_u_y:[0.0834658365294,0.127354950925] p32_u_z:[0.933965437345,0.943058684728] p32_v_x:[-0,0] p32_v_y:[-0.996044047409,-0.99100658836] p32_v_z:[0.0882709811697,0.133813085375] p33_u_x:[0.999603217684,1] p33_u_y:[-0.00359969275843,1.0090750271e-11] p33_u_z:[-0.0241448874858,0] p33_v_x:[-0,0] p33_v_y:[-0.996044047409,-0.99100658836] p33_v_z:[0.0882709811697,0.133813085375] p34_u_x:[0.93711772562,0.954508363607] p34_u_y:[-0.0473359513434,-0.0277778634954] p34_u_z:[-0.344499522108,-0.298495669685] p34_v_x:[-0,0] p34_v_y:[-0.996044047409,-0.99100658836] p34_v_z:[0.0882709811697,0.133813085375] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.572919151199,-0.537175796968] p40_v_y:[0.819600174873,0.842443081061] p40_v_z:[-0,0] p42_u_x:[-0,0.0133816898399] p42_u_y:[-0.00128319238981,0] p42_u_z:[0.999817150573,1] p42_v_x:[-0.573675655088,-0.535528676409] p42_v_y:[0.819222290483,0.844232838302] p42_v_z:[-0,0.00795498907261] p43_u_x:[-0,0.0132457382925] p43_u_y:[-0,0.00128293529736] p43_u_z:[0.999820205236,1] p43_v_x:[-0.573675655088,-0.535528676409] p43_v_y:[0.819222290483,0.844232838302] p43_v_z:[-0,0.00795498907261] p44_u_x:[-0,0.0138819198665] p44_u_y:[-0,0.00176772157484] p44_u_z:[0.999808231841,1] p44_v_x:[-0.573675655088,-0.535528676409] p44_v_y:[0.819222290483,0.844232838302] p44_v_z:[-0,0.00795498907261] object_u_x:[0.999528025239,1] object_u_y:[-0,0.0236422245577] object_u_z:[-0,1.48657863726e-08] object_v_x:[-4.78267920949e-07,1.00079893505e-11] object_v_y:[-0,2.15349984319e-09] object_v_z:[0.999999999985,1] X_3_u_x:[-0,1.49355925771e-08] X_3_u_y:[-2.17617777028e-09,0] X_3_u_z:[0.999999999985,1] X_3_v_x:[0.983185795191,0.989685920219] X_3_v_y:[0.143254247228,0.182608028648] X_3_v_z:[-9.0967047695e-08,1.06698270343e-08] X_4_u_x:[0.879307910731,0.91367628512] X_4_u_y:[0.12651003182,0.158411903892] X_4_u_z:[-0.452292604826,-0.386294397279] X_4_v_x:[0.378937918248,0.444107144477] X_4_v_y:[0.0539634166487,0.0778353058085] X_4_v_z:[0.892598677245,0.923623316158] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412042968,-0.999410098377] uni_v_palm_p12_z_0:[0.0342865655909,0.0343432240926] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.65259524086e-06,9.44839289572e-05] w2_palm_p12_z_0:[-0.000104108180752,0.00275224170562] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[0.951024327658,0.951907768232] w1_p12_p13_y_1:[-0.0106160421468,-0.0105053046196] w1_p12_p13_z_1:[-0.308934313874,-0.306216894204] w2_p12_p13_x_1:[0.948117597049,0.954282430759] w2_p12_p13_y_1:[-0.010922989447,-0.0102509511237] w2_p12_p13_z_1:[-0.317866077725,-0.29879554719] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.318054316861,-0.298970653624] w1_p13_p14_y_2:[-0.0327590349823,-0.0325064150455] w1_p13_p14_z_2:[-0.953721353762,-0.947520951374] w2_p13_p14_x_2:[-0.312514873822,-0.273528937398] w2_p13_p14_y_2:[-0.0330340476066,-0.0325691772643] w2_p13_p14_z_2:[-0.961312212221,-0.94935246885] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-8.14101323893e-06,1.20020899541e-05] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[0.951054000582,0.951060225147] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[-0.309024736939,-0.309005579709] w2_p22_p23_x_4:[0.951036194016,0.951089176535] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[-0.309079536809,-0.308916472254] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0.309079536809,-0.308916472254] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[-0.951089176535,-0.951036194016] w2_p23_p24_x_5:[-0.311073577206,-0.306906348563] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[-0.951739719271,-0.950385831943] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.996044047409,-0.99100658836] uni_v_palm_p32_z_6:[0.0882709811697,0.133813085375] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.889452922813,0.90749255678] w2_palm_p32_y_6:[0.0364464394569,0.0605740288914] w2_palm_p32_z_6:[0.419112769226,0.44860078448] cos_0_palm_p32_6:[0.98563410278,0.9922632869] cos_1_palm_p32_6:[0.889452922813,0.90749255678] w1_p32_p33_x_7:[0.889452922813,0.90749255678] w1_p32_p33_y_7:[0.0364464394569,0.0605740288914] w1_p32_p33_z_7:[0.419112769226,0.44860078448] w2_p32_p33_x_7:[0.999603217684,1] w2_p32_p33_y_7:[-0.00359969275843,1.0090750271e-11] w2_p32_p33_z_7:[-0.0241448874858,0] cos_p32_p33_7:[0.87928619915,0.90728000905] w1_p33_p34_x_8:[0.689674866491,0.707106781204] w1_p33_p34_y_8:[-0.097149403476,-0.0624087901083] w1_p33_p34_z_8:[-0.718144938002,-0.700743878549] w2_p33_p34_x_8:[0.93711772562,0.954508363607] w2_p33_p34_y_8:[-0.0473359513434,-0.0277778634954] w2_p33_p34_z_8:[-0.344499522108,-0.298495669685] cos_p33_p34_8:[0.87928619915,0.90728000905] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.842443081061,-0.819600174873] w2_palm_p40_y_9:[-0.572919151199,-0.537175796968] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.975537864096,0.985355434806] uni_u_p40_p42_x_10:[-0.6900869949,-0.671375235206] uni_u_p40_p42_y_10:[-0.469306549321,-0.440027391517] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.573675655088,-0.535528676409] uni_v_p40_p42_y_10:[0.819222290483,0.844232838302] uni_v_p40_p42_z_10:[-0,0.00795498907261] w1_p40_p42_x_10:[-0.572919151199,-0.537175796968] w1_p40_p42_y_10:[0.819600174873,0.842443081061] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.596968654484,-0.572266364367] w2_p40_p42_y_10:[-0.406532167636,-0.378806993661] w2_p40_p42_z_10:[0.707106781156,0.714956828321] cos_0_p40_p42_10:[0.99637224757,1] cos_1_p40_p42_10:[0.980308954137,0.986222284507] w1_p42_p43_x_11:[-0.596968654484,-0.572266364367] w1_p42_p43_y_11:[-0.406532167636,-0.378806993661] w1_p42_p43_z_11:[0.707106781156,0.714956828321] w2_p42_p43_x_11:[-0,0.0132457382925] w2_p42_p43_y_11:[-0,0.00128293529736] w2_p42_p43_z_11:[0.999820205236,1] cos_p42_p43_11:[0.707106781187,0.708244925434] w1_p43_p44_x_12:[-0.596965496794,-0.572232058972] w1_p43_p44_y_12:[-0.405675101981,-0.378651550485] w1_p43_p44_z_12:[0.707106781156,0.71495854737] w2_p43_p44_x_12:[-0,0.0138819198665] w2_p43_p44_y_12:[-0,0.00176772157484] w2_p43_p44_z_12:[0.999808231841,1] cos_p43_p44_12:[0.707106781187,0.708244925434] sph_w1_p34_X_3_x_13:[-0,0] sph_w1_p34_X_3_y_13:[0.99100658836,0.996044047409] sph_w1_p34_X_3_z_13:[-0.133813085375,-0.0882709811697] sph_w2_p34_X_3_x_13:[-0.171469834109,-0.143254249563] sph_w2_p34_X_3_y_13:[0.986182085831,0.989685933366] sph_w2_p34_X_3_z_13:[-1.11022302465e-27,2.12958707153e-09] cos_p34_X_3_13:[0.980785280403,0.985780612566] in_patch_X_3_object_u_14:[0.0649550927238,0.12991018545] in_patch_X_3_object_v_14:[-0,0.0431861404173] in_patch_X_3_object_l_14:[382.253093035,382.253093035] sph_w1_p44_X_4_x_15:[-0.835919909613,-0.810914911303] sph_w1_p44_X_4_y_15:[-0.568066100329,-0.530244869792] sph_w1_p44_X_4_z_15:[0.140021004692,0.151727639373] sph_w2_p44_X_4_x_15:[0.14324965466,0.171465259257] sph_w2_p44_X_4_y_15:[-0.989686598455,-0.986182849387] sph_w2_p44_X_4_z_15:[-2.12968440046e-09,4.22178933133e-16] cos_p44_X_4_15:[0.401039537246,0.445715435012] in_patch_X_4_object_u_16:[0.249999999997,0.32832092457] in_patch_X_4_object_v_16:[0.457489706968,0.500000000005] in_patch_X_4_object_l_16:[382.265354258,382.265354258] p14_r_x:[44.9172519906,45.2615353935] p14_r_y:[-38.2815066952,-38.2582149861] p14_r_z:[200.335430006,200.967333763] p24_r_x:[45.1818435866,45.1843640211] p24_r_y:[-0,0] p24_r_z:[205.359075131,205.364389099] }
   5 (err:2.70419 min:5.29326 tm:67):{ 241  p12_u_x:[0.306397056817,0.309116060806] p12_u_y:[0.0326073189238,0.0326695748395] p12_u_z:[0.950463308802,0.951345135365] p12_v_x:[-0,0] p12_v_y:[-0.999412042968,-0.999410098377] p12_v_z:[0.0342865655909,0.0343432240926] p13_u_x:[0.948078920293,0.954290841877] p13_u_y:[-0.0109231248608,-0.0102475535077] p13_u_z:[-0.317870018334,-0.298703827898] p13_v_x:[-0,0] p13_v_y:[-0.999412042968,-0.999410098377] p13_v_z:[0.0342865655909,0.0343432240926] p14_u_x:[-0.312514873822,-0.246996183666] p14_u_y:[-0.0332799791541,-0.0325687001367] p14_u_z:[-0.968468980128,-0.949329709064] p14_v_x:[-0,0] p14_v_y:[-0.999412042968,-0.999410098377] p14_v_z:[0.0342865655909,0.0343432240926] p22_u_x:[0.309005579709,0.309024736939] p22_u_y:[-0,0] p22_u_z:[0.951054000582,0.951060225147] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[0.95103619275,0.951089181018] p23_u_y:[-0,0] p23_u_z:[-0.309079540707,-0.308946055486] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0.311073577206,-0.30691355967] p24_u_y:[-0,0] p24_u_z:[-0.951739719271,-0.950388139504] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.311701103055,0.344032949541] p32_u_y:[0.083608127897,0.127345341371] p32_u_z:[0.933987114518,0.943028792287] p32_v_x:[-0,0] p32_v_y:[-0.996030480034,-0.99100658836] p32_v_z:[0.0884325640567,0.133813085375] p33_u_x:[0.999610097679,1] p33_u_y:[-0.00356724673135,1.0090750271e-11] p33_u_z:[-0.0240225823509,0] p33_v_x:[-0,0] p33_v_y:[-0.996030480034,-0.99100658836] p33_v_z:[0.0884325640567,0.133813085375] p34_u_x:[0.937175824997,0.954412784796] p34_u_y:[-0.0472839780379,-0.0278678510784] p34_u_z:[-0.344380896886,-0.29872889581] p34_v_x:[-0,0] p34_v_y:[-0.996030480034,-0.99100658836] p34_v_z:[0.0884325640567,0.133813085375] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.572893190238,-0.537270810367] p40_v_y:[0.81962458689,0.84239299918] p40_v_z:[-0,0] p42_u_x:[-0,0.0133077913112] p42_u_y:[-0.00126452767379,0] p42_u_z:[0.999819866928,1] p42_v_x:[-0.573558578698,-0.535639390573] p42_v_y:[0.819248096576,0.84416458597] p42_v_z:[-0,0.00790519417407] p43_u_x:[-0,0.0131710741074] p43_u_y:[-0,0.00126427625817] p43_u_z:[0.999822899901,1] p43_v_x:[-0.573558578698,-0.535639390573] p43_v_y:[0.819248096576,0.84416458597] p43_v_z:[-0,0.00790519417407] p44_u_x:[-0,0.0137963655138] p44_u_y:[-0,0.00174177778547] p44_u_z:[0.999811152473,1] p44_v_x:[-0.573558578698,-0.535639390573] p44_v_y:[0.819248096576,0.84416458597] p44_v_z:[-0,0.00790519417407] object_u_x:[0.999573497601,1] object_u_y:[-0,0.0227730198223] object_u_z:[-0,1.48657863726e-08] object_v_x:[-4.78268395328e-07,1.00079992771e-11] object_v_y:[-0,2.15350197918e-09] object_v_z:[0.999999999985,1] X_3_u_x:[-0,1.49355925772e-08] X_3_u_y:[-2.17616371906e-09,0] X_3_u_z:[0.999999999985,1] X_3_v_x:[0.986044679918,0.989685920219] X_3_v_y:[0.143254247228,0.165301833581] X_3_v_z:[-9.0967047695e-08,1.06698270343e-08] X_4_u_x:[0.844844771541,0.886269432565] X_4_u_y:[0.121130423988,0.149282966184] X_4_u_z:[-0.51490191281,-0.446683635683] X_4_v_x:[0.444107144468,0.511804278223] X_4_v_y:[0.062130746925,0.0868905970763] X_4_v_z:[0.85606708919,0.893828159386] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412042968,-0.999410098377] uni_v_palm_p12_z_0:[0.0342865655909,0.0343432240926] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.65788358435e-06,9.44839289572e-05] w2_palm_p12_z_0:[-0.000104108207301,0.00275222812593] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[0.951024327658,0.951907785613] w1_p12_p13_y_1:[-0.0106160421468,-0.0105053026812] w1_p12_p13_z_1:[-0.308934313891,-0.306216908483] w2_p12_p13_x_1:[0.948078920293,0.954290841877] w2_p12_p13_y_1:[-0.0109231248608,-0.0102475535077] w2_p12_p13_z_1:[-0.317870018334,-0.298703827898] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.318058259804,-0.298879517928] w1_p13_p14_y_2:[-0.0327590349823,-0.0325063700863] w1_p13_p14_z_2:[-0.953729759935,-0.947520483062] w2_p13_p14_x_2:[-0.312514873822,-0.246996183666] w2_p13_p14_y_2:[-0.0332799791541,-0.0325687001367] w2_p13_p14_z_2:[-0.968468980128,-0.949329709064] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-8.14101323893e-06,1.20020899541e-05] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[0.951054000582,0.951060225147] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[-0.309024736939,-0.309005579709] w2_p22_p23_x_4:[0.95103619275,0.951089181018] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[-0.309079540707,-0.308946055486] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0.309079540707,-0.308946055486] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[-0.951089181018,-0.95103619275] w2_p23_p24_x_5:[-0.311073577206,-0.30691355967] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[-0.951739719271,-0.950388139504] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.996030480034,-0.99100658836] uni_v_palm_p32_z_6:[0.0884325640567,0.133813085375] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.889529353661,0.907454376209] w2_palm_p32_y_6:[0.0365302242146,0.0605576693868] w2_palm_p32_z_6:[0.419169795848,0.448497289322] cos_0_palm_p32_6:[0.98563410278,0.992244362305] cos_1_palm_p32_6:[0.889529353661,0.907454376209] w1_p32_p33_x_7:[0.889529353661,0.907454376209] w1_p32_p33_y_7:[0.0365302242146,0.0605576693868] w1_p32_p33_z_7:[0.419169795848,0.448497289322] w2_p32_p33_x_7:[0.999610097679,1] w2_p32_p33_y_7:[-0.00356724673135,1.0090750271e-11] w2_p32_p33_z_7:[-0.0240225823509,0] cos_p32_p33_7:[0.879418255897,0.907245497184] w1_p33_p34_x_8:[0.689765331843,0.707106781204] w1_p33_p34_y_8:[-0.097126592356,-0.0625233881105] w1_p33_p34_z_8:[-0.718050767305,-0.70074397838] w2_p33_p34_x_8:[0.937175824997,0.954412784796] w2_p33_p34_y_8:[-0.0472839780379,-0.0278678510784] w2_p33_p34_z_8:[-0.344380896886,-0.29872889581] cos_p33_p34_8:[0.879418255897,0.907245497184] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.84239299918,-0.81962458689] w2_palm_p40_y_9:[-0.572893190238,-0.537270810367] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.975569635477,0.985347147623] uni_u_p40_p42_x_10:[-0.690045970342,-0.671395232302] uni_u_p40_p42_y_10:[-0.469285283407,-0.440105221714] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.573558578698,-0.535639390573] uni_v_p40_p42_y_10:[0.819248096576,0.84416458597] uni_v_p40_p42_z_10:[-0,0.00790519417407] w1_p40_p42_x_10:[-0.572893190238,-0.537270810367] w1_p40_p42_y_10:[0.81962458689,0.84239299918] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.596920267766,-0.572329816875] w2_p40_p42_y_10:[-0.406441413723,-0.378884477649] w2_p40_p42_z_10:[0.707106781156,0.714913263383] cos_0_p40_p42_10:[0.996407164161,1] cos_1_p40_p42_10:[0.980344981083,0.986206383606] w1_p42_p43_x_11:[-0.596920267766,-0.572329816875] w1_p42_p43_y_11:[-0.406441413723,-0.378884477649] w1_p42_p43_z_11:[0.707106781156,0.714913263383] w2_p42_p43_x_11:[-0,0.0131710741074] w2_p42_p43_y_11:[-0,0.00126427625817] w2_p42_p43_z_11:[0.999822899901,1] cos_p42_p43_11:[0.707106781187,0.708227940283] w1_p43_p44_x_12:[-0.596917177636,-0.572297936239] w1_p43_p44_y_12:[-0.405594208746,-0.378731092506] w1_p43_p44_z_12:[0.707106781156,0.714913947195] w2_p43_p44_x_12:[-0,0.0137963655138] w2_p43_p44_y_12:[-0,0.00174177778547] w2_p43_p44_z_12:[0.999811152473,1] cos_p43_p44_12:[0.707106781187,0.708227940283] sph_w1_p34_X_3_x_13:[-0,0] sph_w1_p34_X_3_y_13:[0.99100658836,0.996030480034] sph_w1_p34_X_3_z_13:[-0.133813085375,-0.0884325640567] sph_w2_p34_X_3_x_13:[-0.165301817484,-0.143254249563] sph_w2_p34_X_3_y_13:[0.986170789548,0.989685933366] sph_w2_p34_X_3_z_13:[-1.11022302465e-27,2.12958707153e-09] cos_p34_X_3_13:[0.980785280403,0.985767087209] in_patch_X_3_object_u_14:[0.0649550928144,0.129910185631] in_patch_X_3_object_v_14:[-0,0.0429748578818] in_patch_X_3_object_l_14:[382.253093035,382.253093035] sph_w1_p44_X_4_x_15:[-0.835852247418,-0.810943807125] sph_w1_p44_X_4_y_15:[-0.567952757114,-0.530354651209] sph_w1_p44_X_4_z_15:[0.140021004692,0.151654101521] sph_w2_p44_X_4_x_15:[0.14324965466,0.165297238552] sph_w2_p44_X_4_y_15:[-0.989686598455,-0.986171559106] sph_w2_p44_X_4_z_15:[-2.12968440046e-09,4.22178933133e-16] cos_p44_X_4_15:[0.401278826936,0.44566965423] in_patch_X_4_object_u_16:[0.249999999997,0.310429722234] in_patch_X_4_object_v_16:[0.457698040698,0.500000000005] in_patch_X_4_object_l_16:[382.265354258,382.265354258] p14_r_x:[44.916088061,45.2615353935] p14_r_y:[-38.2819175235,-38.2582149861] p14_r_z:[200.335311785,200.970085342] p24_r_x:[45.1818435866,45.1842640971] p24_r_y:[-0,0] p24_r_z:[205.359075016,205.363501602] }
   6 (err:2.74623 min:5.27792 tm:67):{ 241  p12_u_x:[0.306397050891,0.309116060806] p12_u_y:[0.0326073300381,0.0326702072014] p12_u_z:[0.950463302895,0.951345135365] p12_v_x:[-0,0] p12_v_y:[-0.999412043068,-0.999410097493] p12_v_z:[0.0342865626936,0.0343432498525] p13_u_x:[0.948115047084,0.954290841886] p13_u_y:[-0.0109231330646,-0.0102475526407] p13_u_z:[-0.317870018362,-0.29876558035] p13_v_x:[-0,0] p13_v_y:[-0.999412043068,-0.999410097493] p13_v_z:[0.0342865626936,0.0343432498525] p14_u_x:[-0.37803356307,-0.312514873816] p14_u_y:[-0.0326241210312,-0.0317422217043] p14_u_z:[-0.949382370387,-0.925247565099] p14_v_x:[-0,0] p14_v_y:[-0.999412043068,-0.999410097493] p14_v_z:[0.0342865626936,0.0343432498525] p22_u_x:[0.309005579518,0.309024737016] p22_u_y:[-0,0] p22_u_z:[0.951054000557,0.951060225209] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[0.951036191483,0.951089181018] p23_u_y:[-0,0] p23_u_z:[-0.309079540707,-0.308916444651] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0.311073577206,-0.306906348563] p24_u_y:[-0,0] p24_u_z:[-0.951739719271,-0.950385831943] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.311552017783,0.34493220785] p32_u_y:[0.0794894587941,0.127346108667] p32_u_z:[0.933986503385,0.94315840053] p32_v_x:[-0,0] p32_v_y:[-0.996419117559,-0.99100658836] p32_v_z:[0.0840856075535,0.133813085375] p33_u_x:[0.999602534677,1] p33_u_y:[-0.0036052297393,1.0090750271e-11] p33_u_z:[-0.0244815996434,0] p33_v_x:[-0,0] p33_v_y:[-0.996419117559,-0.99100658836] p33_v_z:[0.0840856075535,0.133813085375] p34_u_x:[0.936855167932,0.954421001575] p34_u_y:[-0.0472864486058,-0.0264741578945] p34_u_z:[-0.345411228719,-0.298705916811] p34_v_x:[-0,0] p34_v_y:[-0.996419117559,-0.99100658836] p34_v_z:[0.0840856075535,0.133813085375] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.57299249275,-0.536375173277] p40_v_y:[0.819560615961,0.84296511152] p40_v_z:[-0,0] p42_u_x:[-0,0.0135584631967] p42_u_y:[-0.0012649515667,0] p42_u_z:[0.999816448427,1] p42_v_x:[-0.573566106164,-0.534750148062] p42_v_y:[0.819177372078,0.844732369202] p42_v_z:[-0,0.00804822411962] p43_u_x:[-0,0.0134208486013] p43_u_y:[-0,0.00126469372602] p43_u_z:[0.999819514667,1] p43_v_x:[-0.573566106164,-0.534750148062] p43_v_y:[0.819177372078,0.844732369202] p43_v_z:[-0,0.00804822411962] p44_u_x:[-0,0.0140455476363] p44_u_y:[-0,0.00174230143532] p44_u_z:[0.999807700057,1] p44_v_x:[-0.573566106164,-0.534750148062] p44_v_y:[0.819177372078,0.844732369202] p44_v_z:[-0,0.00804822411962] object_u_x:[0.999411077719,1] object_u_y:[-0,0.0308400936449] object_u_z:[-0,1.48657863726e-08] object_v_x:[-4.78268314453e-07,1.00079975847e-11] object_v_y:[-0,2.15350161502e-09] object_v_z:[0.999999999985,1] X_3_u_x:[-0,1.49355925772e-08] X_3_u_y:[-2.17617574844e-09,0] X_3_u_z:[0.999999999985,1] X_3_v_x:[0.984855444574,0.989685920219] X_3_v_y:[0.143254247228,0.173720204689] X_3_v_z:[-9.0967047695e-08,1.06698270343e-08] X_4_u_x:[0.844844474004,0.886269434054] X_4_u_y:[0.121130423588,0.149284732609] X_4_u_z:[-0.51490191281,-0.446683635303] X_4_v_x:[0.444107144468,0.511804284136] X_4_v_y:[0.0621307447369,0.0868915837995] X_4_v_z:[0.856055352021,0.893828159386] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412043068,-0.999410097493] uni_v_palm_p12_z_0:[0.0342865626936,0.0343432498525] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.65262514279e-06,9.44839289572e-05] w2_palm_p12_z_0:[-0.000104108207301,0.00275223626432] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[0.951024327658,0.951907787538] w1_p12_p13_y_1:[-0.0106160501096,-0.0105053016946] w1_p12_p13_z_1:[-0.308934313905,-0.306216899925] w2_p12_p13_x_1:[0.948115047084,0.954290841886] w2_p12_p13_y_1:[-0.0109231330646,-0.0102475526407] w2_p12_p13_z_1:[-0.317870018362,-0.29876558035] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.318058260399,-0.298879517928] w1_p13_p14_y_2:[-0.0327590349823,-0.0325074309265] w1_p13_p14_z_2:[-0.953729760069,-0.947557568794] w2_p13_p14_x_2:[-0.37803356307,-0.312514873816] w2_p13_p14_y_2:[-0.0326241210312,-0.0317422217043] w2_p13_p14_z_2:[-0.949382370387,-0.925247565099] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-8.14109401354e-06,1.20022904185e-05] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[0.951054000557,0.951060225209] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[-0.309024737016,-0.309005579518] w2_p22_p23_x_4:[0.951036191483,0.951089181018] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[-0.309079540707,-0.308916444651] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0.309079540707,-0.308916444651] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[-0.951089181018,-0.951036191483] w2_p23_p24_x_5:[-0.311073577206,-0.306906348563] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[-0.951739719271,-0.950385831943] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.996419117559,-0.99100658836] uni_v_palm_p32_z_6:[0.0840856075535,0.133813085375] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.889519247456,0.907863105979] w2_palm_p32_y_6:[0.0346044932312,0.0605597120992] w2_palm_p32_z_6:[0.418475196246,0.448569503048] cos_0_palm_p32_6:[0.98563410278,0.992787058275] cos_1_palm_p32_6:[0.889519247456,0.907863105979] w1_p32_p33_x_7:[0.889519247456,0.907863105979] w1_p32_p33_y_7:[0.0346044932312,0.0605597120992] w1_p32_p33_z_7:[0.418475196246,0.448569503048] w2_p32_p33_x_7:[0.999602534677,1] w2_p32_p33_y_7:[-0.0036052297393,1.0090750271e-11] w2_p32_p33_z_7:[-0.0244815996434,0] cos_p32_p33_7:[0.87939850163,0.907661145976] w1_p33_p34_x_8:[0.689423166912,0.707106781204] w1_p33_p34_y_8:[-0.0971529807184,-0.0594504384245] w1_p33_p34_z_8:[-0.71859487134,-0.70074397654] w2_p33_p34_x_8:[0.936855167932,0.954421001575] w2_p33_p34_y_8:[-0.0472864486058,-0.0264741578945] w2_p33_p34_z_8:[-0.345411228719,-0.298705916811] cos_p33_p34_8:[0.87939850163,0.907661145976] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.84296511152,-0.819560615961] w2_palm_p40_y_9:[-0.57299249275,-0.536375173277] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.975340868932,0.985374076122] uni_u_p40_p42_x_10:[-0.690514615993,-0.671342830536] uni_u_p40_p42_y_10:[-0.46936662703,-0.439371560863] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.573566106164,-0.534750148062] uni_v_p40_p42_y_10:[0.819177372078,0.844732369202] uni_v_p40_p42_z_10:[-0,0.00804822411962] w1_p40_p42_x_10:[-0.57299249275,-0.536375173277] w1_p40_p42_y_10:[0.819560615961,0.84296511152] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.597321600814,-0.571860842192] w2_p40_p42_y_10:[-0.406452396047,-0.378252309037] w2_p40_p42_z_10:[0.707106781156,0.715056070861] cos_0_p40_p42_10:[0.996404875173,1] cos_1_p40_p42_10:[0.980304258441,0.986207665583] w1_p42_p43_x_11:[-0.597321600814,-0.571860842192] w1_p42_p43_y_11:[-0.406452396047,-0.378252309037] w1_p42_p43_z_11:[0.707106781156,0.715056070861] w2_p42_p43_x_11:[-0,0.0134208486013] w2_p42_p43_y_11:[-0,0.00126469372602] w2_p42_p43_z_11:[0.999819514667,1] cos_p42_p43_11:[0.707106781187,0.708228274029] w1_p43_p44_x_12:[-0.597318589157,-0.571829641534] w1_p43_p44_y_12:[-0.405602483964,-0.378102886125] w1_p43_p44_z_12:[0.707106781156,0.715056525253] w2_p43_p44_x_12:[-0,0.0140455476363] w2_p43_p44_y_12:[-0,0.00174230143532] w2_p43_p44_z_12:[0.999807700057,1] cos_p43_p44_12:[0.707106781187,0.708228274029] sph_w1_p34_X_3_x_13:[-0,0] sph_w1_p34_X_3_y_13:[0.99100658836,0.996419117559] sph_w1_p34_X_3_z_13:[-0.133813085375,-0.0840856075535] sph_w2_p34_X_3_x_13:[-0.165303848134,-0.143254249563] sph_w2_p34_X_3_y_13:[0.984855531388,0.989685933366] sph_w2_p34_X_3_z_13:[-1.11022302465e-27,2.12958707153e-09] cos_p34_X_3_13:[0.980785280403,0.98576735176] in_patch_X_3_object_u_14:[0.0649550928144,0.129910185631] in_patch_X_3_object_v_14:[-0,0.0438115997044] in_patch_X_3_object_l_14:[382.253093035,382.253093035] sph_w1_p44_X_4_x_15:[-0.836414331795,-0.810873041858] sph_w1_p44_X_4_y_15:[-0.567964449015,-0.529474373659] sph_w1_p44_X_4_z_15:[0.140021004692,0.151855995533] sph_w2_p44_X_4_x_15:[0.14324965466,0.165299269203] sph_w2_p44_X_4_y_15:[-0.989686598455,-0.984856337907] sph_w2_p44_X_4_z_15:[-2.12968440046e-09,4.22178933133e-16] cos_p44_X_4_15:[0.400864497018,0.445724134467] in_patch_X_4_object_u_16:[0.249999999997,0.327354174978] in_patch_X_4_object_v_16:[0.456874697006,0.500000000005] in_patch_X_4_object_l_16:[382.265354258,382.265354258] p14_r_x:[44.9171716635,45.2615353935] p14_r_y:[-38.2813930472,-38.2582149861] p14_r_z:[200.335311382,200.968232836] p24_r_x:[45.1818435866,45.1843640211] p24_r_y:[-0,0] p24_r_z:[205.359075013,205.364389933] }
   7 (err:2.73509 min:5.28272 tm:67):{ 241  p12_u_x:[0.30637400452,0.309116060806] p12_u_y:[0.0326073297877,0.0326700523996] p12_u_z:[0.95046330628,0.951352628067] p12_v_x:[-0,0] p12_v_y:[-0.999412043068,-0.999410097493] p12_v_z:[0.0342865626936,0.0343432498525] p13_u_x:[0.947922846446,0.954404023204] p13_u_y:[-0.0109434775384,-0.0102369747973] p13_u_z:[-0.3184620556,-0.29841209168] p13_v_x:[-0,0] p13_v_y:[-0.999412043068,-0.999410097493] p13_v_z:[0.0342865626936,0.0343432498525] p14_u_x:[-0.377850667375,-0.31237469835] p14_u_y:[-0.0326257032877,-0.0317447815975] p14_u_z:[-0.949428415874,-0.925322182903] p14_v_x:[-0,0] p14_v_y:[-0.999412043068,-0.999410097493] p14_v_z:[0.0342865626936,0.0343432498525] p22_u_x:[0.309005579498,0.309024737016] p22_u_y:[-0,0] p22_u_z:[0.951054000557,0.951060225216] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[0.951036194443,0.951086454514] p23_u_y:[-0,0] p23_u_z:[-0.3090795316,-0.308924838863] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0.311066529654,-0.306913680979] p24_u_y:[-0,0] p24_u_z:[-0.951737354764,-0.950388138669] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.311638426395,0.344674050584] p32_u_y:[0.0827250413379,0.127347873549] p32_u_z:[0.933817617277,0.943055864648] p32_v_x:[-0,0] p32_v_y:[-0.996113170106,-0.99100658836] p32_v_z:[0.0875125645563,0.133813085375] p33_u_x:[0.999595875311,1] p33_u_y:[-0.00363438238879,1.0090750271e-11] p33_u_z:[-0.0245641104761,0] p33_v_x:[-0,0] p33_v_y:[-0.996113170106,-0.99100658836] p33_v_z:[0.0875125645563,0.133813085375] p34_u_x:[0.936957384609,0.954436526887] p34_u_y:[-0.0473150220542,-0.0276210253202] p34_u_z:[-0.345037411487,-0.298662403498] p34_v_x:[-0,0] p34_v_y:[-0.996113170106,-0.99100658836] p34_v_z:[0.0875125645563,0.133813085375] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.573447924752,-0.536565340652] p40_v_y:[0.819237462275,0.842830750487] p40_v_z:[-0,0] p42_u_x:[-0,0.0135869710508] p42_u_y:[-0.00127055813799,0] p42_u_z:[0.999816332004,1] p42_v_x:[-0.574111678801,-0.534921508057] p42_v_y:[0.818850912673,0.844620100974] p42_v_z:[-0,0.00805559611778] p43_u_x:[-0,0.0134492756865] p43_u_y:[-0,0.00127029827642] p43_u_z:[0.999819387657,1] p43_v_x:[-0.574111678801,-0.534921508057] p43_v_y:[0.818850912673,0.844620100974] p43_v_z:[-0,0.00805559611778] p44_u_x:[-0,0.0140754375187] p44_u_y:[-0,0.00174933847351] p44_u_z:[0.999807593744,1] p44_v_x:[-0.574111678801,-0.534921508057] p44_v_y:[0.818850912673,0.844620100974] p44_v_z:[-0,0.00805559611778] object_u_x:[0.99955860148,1] object_u_y:[-0,0.0228911180335] object_u_z:[-0,1.48657863726e-08] object_v_x:[-4.78271842191e-07,1.00080714044e-11] object_v_y:[-0,2.15351749939e-09] object_v_z:[0.999999999985,1] X_3_u_x:[-0,1.49355925772e-08] X_3_u_y:[-2.1761604322e-09,0] X_3_u_z:[0.999999999985,1] X_3_v_x:[0.986097553255,0.989685920219] X_3_v_y:[0.143254247228,0.165874361041] X_3_v_z:[-9.0967047695e-08,1.06698270343e-08] X_4_u_x:[0.844353049538,0.886161773897] X_4_u_y:[0.121089950993,0.154402584399] X_4_u_z:[-0.515274177921,-0.446913856391] X_4_v_x:[0.44433935887,0.512182568631] X_4_v_y:[0.0621537741196,0.0897073942341] X_4_v_z:[0.855826808776,0.893708254068] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412043068,-0.999410097493] uni_v_palm_p12_z_0:[0.0342865626936,0.0343432498525] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.65362038227e-06,9.53818480996e-05] w2_palm_p12_z_0:[-0.000104108359912,0.00277692830768] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[0.951024327658,0.951915275758] w1_p12_p13_y_1:[-0.0106160501096,-0.0105045114125] w1_p12_p13_z_1:[-0.308934313908,-0.306193371701] w2_p12_p13_x_1:[0.947922846446,0.954404023204] w2_p12_p13_y_1:[-0.0109434775384,-0.0102369747973] w2_p12_p13_z_1:[-0.3184620556,-0.29841209168] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.318650048874,-0.298587608766] w1_p13_p14_y_2:[-0.0327590349823,-0.0325008323716] w1_p13_p14_z_2:[-0.953842874812,-0.947321188068] w2_p13_p14_x_2:[-0.377850667375,-0.31237469835] w2_p13_p14_y_2:[-0.0326257032877,-0.0317447815975] w2_p13_p14_z_2:[-0.949428415874,-0.925322182903] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-8.14109401354e-06,1.20023120043e-05] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[0.951054000557,0.951060225216] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[-0.309024737016,-0.309005579498] w2_p22_p23_x_4:[0.951036194443,0.951086454514] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[-0.3090795316,-0.308924838863] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0.3090795316,-0.308924838863] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[-0.951086454514,-0.951036194443] w2_p23_p24_x_5:[-0.311066529654,-0.306913680979] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[-0.951737354764,-0.950388138669] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.996113170106,-0.99100658836] uni_v_palm_p32_z_6:[0.0875125645563,0.133813085375] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.889508925217,0.907746712739] w2_palm_p32_y_6:[0.036078026322,0.0605645089758] w2_palm_p32_z_6:[0.418588438743,0.448540772776] cos_0_palm_p32_6:[0.98563410278,0.99235980113] cos_1_palm_p32_6:[0.889508925217,0.907746712739] w1_p32_p33_x_7:[0.889508925217,0.907746712739] w1_p32_p33_y_7:[0.036078026322,0.0605645089758] w1_p32_p33_z_7:[0.418588438743,0.448540772776] w2_p32_p33_x_7:[0.999595875311,1] w2_p32_p33_y_7:[-0.00363438238879,1.0090750271e-11] w2_p32_p33_z_7:[-0.0245641104761,0] cos_p32_p33_7:[0.879158128939,0.907539957752] w1_p33_p34_x_8:[0.689373502114,0.707106781204] w1_p33_p34_y_8:[-0.097173388217,-0.0618728465822] w1_p33_p34_z_8:[-0.718424587813,-0.700743951552] w2_p33_p34_x_8:[0.936957384609,0.954436526887] w2_p33_p34_y_8:[-0.0473150220542,-0.0276210253202] w2_p33_p34_z_8:[-0.345037411487,-0.298662403498] cos_p33_p34_8:[0.879158128939,0.907539957752] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.842830750487,-0.819237462275] w2_palm_p40_y_9:[-0.573447924752,-0.536565340652] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.975380329978,0.985475355401] uni_u_p40_p42_x_10:[-0.690404554192,-0.671078119291] uni_u_p40_p42_y_10:[-0.469739694016,-0.439527336411] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.574111678801,-0.534921508057] uni_v_p40_p42_y_10:[0.818850912673,0.844620100974] uni_v_p40_p42_z_10:[-0,0.00805559611778] w1_p40_p42_x_10:[-0.573447924752,-0.536565340652] w1_p40_p42_y_10:[0.819237462275,0.842830750487] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.597242216041,-0.571989700471] w2_p40_p42_y_10:[-0.406838205327,-0.37837358489] w2_p40_p42_z_10:[0.707106781156,0.715078684713] cos_0_p40_p42_10:[0.996357499797,1] cos_1_p40_p42_10:[0.98027220562,0.986221636488] w1_p42_p43_x_11:[-0.597242216041,-0.571989700471] w1_p42_p43_y_11:[-0.406838205327,-0.37837358489] w1_p42_p43_z_11:[0.707106781156,0.715078684713] w2_p42_p43_x_11:[-0,0.0134492756865] w2_p42_p43_y_11:[-0,0.00127029827642] w2_p42_p43_z_11:[0.999819387657,1] cos_p42_p43_11:[0.707106781187,0.70823222317] w1_p43_p44_x_12:[-0.597239204431,-0.571958262329] w1_p43_p44_y_12:[-0.405985996613,-0.378223904808] w1_p43_p44_z_12:[0.707106781156,0.715078526964] w2_p43_p44_x_12:[-0,0.0140754375187] w2_p43_p44_y_12:[-0,0.00174933847351] w2_p43_p44_z_12:[0.999807593744,1] cos_p43_p44_12:[0.707106781187,0.70823222317] sph_w1_p34_X_3_x_13:[-0,0] sph_w1_p34_X_3_y_13:[0.99100658836,0.996113170106] sph_w1_p34_X_3_z_13:[-0.133813085375,-0.0875125645563] sph_w2_p34_X_3_x_13:[-0.172610583022,-0.143254249563] sph_w2_p34_X_3_y_13:[0.985992269363,0.989685933366] sph_w2_p34_X_3_z_13:[-1.11022302465e-27,2.12958707153e-09] cos_p34_X_3_13:[0.980785280403,0.985848636174] in_patch_X_3_object_u_14:[0.0637664951427,0.127532990288] in_patch_X_3_object_v_14:[0.499999999995,0.543928716134] in_patch_X_3_object_l_14:[382.253093035,382.253093035] sph_w1_p44_X_4_x_15:[-0.836303169381,-0.810549191213] sph_w1_p44_X_4_y_15:[-0.568501411859,-0.52964405518] sph_w1_p44_X_4_z_15:[0.140021004692,0.151888879883] sph_w2_p44_X_4_x_15:[0.14324965466,0.172606008682] sph_w2_p44_X_4_y_15:[-0.989686598455,-0.985993026788] sph_w2_p44_X_4_z_15:[-2.12968440046e-09,4.22178933133e-16] cos_p44_X_4_15:[0.400259898582,0.445906533176] in_patch_X_4_object_u_16:[0.249999999997,0.328412653556] in_patch_X_4_object_v_16:[0.956762933142,1] in_patch_X_4_object_l_16:[382.265354258,382.265354258] p14_r_x:[44.9098428999,45.2615353935] p14_r_y:[-38.2821437392,-38.2572517621] p14_r_z:[200.317550495,200.979345434] p24_r_x:[45.1818434488,45.1843640211] p24_r_y:[-0,0] p24_r_z:[205.359075286,205.364138105] }
   8 (err:2.7325 min:5.29387 tm:67):{ 241  p12_u_x:[0.306374210515,0.309116060806] p12_u_y:[0.0326073048434,0.0326696322339] p12_u_z:[0.950463308834,0.951352582674] p12_v_x:[-0,0] p12_v_y:[-0.999412042968,-0.999410098377] p12_v_z:[0.0342865655909,0.0343432240926] p13_u_x:[0.947880351509,0.954404023195] p13_u_y:[-0.0109434693101,-0.0102351549206] p13_u_z:[-0.318462055572,-0.298342424333] p13_v_x:[-0,0] p13_v_y:[-0.999412042968,-0.999410098377] p13_v_z:[0.0342865655909,0.0343432240926] p14_u_x:[-0.312374698357,-0.246898728429] p14_u_y:[-0.0332808306911,-0.0325707580733] p14_u_z:[-0.968493760375,-0.94939832293] p14_v_x:[-0,0] p14_v_y:[-0.999412042968,-0.999410098377] p14_v_z:[0.0342865655909,0.0343432240926] p22_u_x:[0.309005579689,0.309024736939] p22_u_y:[-0,0] p22_u_z:[0.951054000582,0.951060225154] p22_v_x:[-0,0] p22_v_y:[-1,-1] p22_v_z:[-0,0] p23_u_x:[0.951036194443,0.951086454514] p23_u_y:[-0,0] p23_u_z:[-0.3090795316,-0.308924838863] p23_v_x:[-0,0] p23_v_y:[-1,-1] p23_v_z:[-0,0] p24_u_x:[-0.311066529654,-0.306913680979] p24_u_y:[-0,0] p24_u_z:[-0.951737354764,-0.950388138669] p24_v_x:[-0,0] p24_v_y:[-1,-1] p24_v_z:[-0,0] p32_u_x:[0.311606202868,0.344526094291] p32_u_y:[0.0828754430508,0.127354565483] p32_u_z:[0.933854100615,0.943077247707] p32_v_x:[-0,0] p32_v_y:[-0.99609917141,-0.99100658836] p32_v_z:[0.0876591457551,0.133813085375] p33_u_x:[0.999594294932,1] p33_u_y:[-0.00364079839029,1.0090750271e-11] p33_u_z:[-0.0245026629635,0] p33_v_x:[-0,0] p33_v_y:[-0.99609917141,-0.99100658836] p33_v_z:[0.0876591457551,0.133813085375] p34_u_x:[0.936975505342,0.954505652051] p34_u_y:[-0.0473452631253,-0.0276191346714] p34_u_z:[-0.344925857326,-0.298485563582] p34_v_x:[-0,0] p34_v_y:[-0.99609917141,-0.99100658836] p34_v_z:[0.0876591457551,0.133813085375] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.573487306228,-0.536704390653] p40_v_y:[0.819205229137,0.84273287997] p40_v_z:[-0,0] p42_u_x:[-0,0.013569607379] p42_u_y:[-0.0012908806024,0] p42_u_z:[0.999814417232,1] p42_v_x:[-0.57421612449,-0.535044802228] p42_v_y:[0.818819350399,0.84453944002] p42_v_z:[-0,0.00805766370016] p43_u_x:[-0,0.0134316169711] p43_u_y:[-0,0.00129060584378] p43_u_z:[0.99981757139,1] p43_v_x:[-0.57421612449,-0.535044802228] p43_v_y:[0.818819350399,0.84453944002] p43_v_z:[-0,0.00805766370016] p44_u_x:[-0,0.014070526219] p44_u_y:[-0,0.00177985822476] p44_u_z:[0.999805143901,1] p44_v_x:[-0.57421612449,-0.535044802228] p44_v_y:[0.818819350399,0.84453944002] p44_v_z:[-0,0.00805766370016] object_u_x:[0.99955924459,1] object_u_y:[-0,0.0228598750018] object_u_z:[-0,1.48657863726e-08] object_v_x:[-4.78271841681e-07,1.00080713937e-11] object_v_y:[-0,2.1535174971e-09] object_v_z:[0.999999999985,1] X_3_u_x:[-0,1.49355925772e-08] X_3_u_y:[-2.17628898756e-09,0] X_3_u_z:[0.999999999985,1] X_3_v_x:[0.984835702946,0.989685920219] X_3_v_y:[0.143254247228,0.172593886435] X_3_v_z:[-9.0967047695e-08,1.06698270343e-08] X_4_u_x:[0.844357005998,0.8861620897] X_4_u_y:[0.121089659402,0.154385839584] X_4_u_z:[-0.515274177921,-0.446913367526] X_4_v_x:[0.44433935887,0.512182527562] X_4_v_y:[0.062153626522,0.089698007884] X_4_v_z:[0.855837706952,0.893708254068] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999412042968,-0.999410098377] uni_v_palm_p12_z_0:[0.0342865655909,0.0343432240926] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.65362038227e-06,9.52265154193e-05] w2_palm_p12_z_0:[-0.000104108359912,0.00277644600309] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[0.951024327658,0.951915208826] w1_p12_p13_y_1:[-0.0106160421468,-0.0105045193631] w1_p12_p13_z_1:[-0.308934313891,-0.306193864077] w2_p12_p13_x_1:[0.947880351509,0.954404023195] w2_p12_p13_y_1:[-0.0109434693101,-0.0102351549206] w2_p12_p13_z_1:[-0.318462055572,-0.298342424333] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[-0.318650647633,-0.298517920018] w1_p13_p14_y_2:[-0.0327590349823,-0.0324995618446] w1_p13_p14_z_2:[-0.953842874737,-0.947321188939] w2_p13_p14_x_2:[-0.312374698357,-0.246898728429] w2_p13_p14_y_2:[-0.0332808306911,-0.0325707580733] w2_p13_p14_z_2:[-0.968493760375,-0.94939832293] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-1,-1] uni_v_palm_p22_z_3:[-0,0] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[1,1] w2_palm_p22_y_3:[-0,0] w2_palm_p22_z_3:[-8.14101323893e-06,1.2002111539e-05] cos_0_palm_p22_3:[1,1] cos_1_palm_p22_3:[1,1] w1_p22_p23_x_4:[0.951054000582,0.951060225154] w1_p22_p23_y_4:[-0,0] w1_p22_p23_z_4:[-0.309024736939,-0.309005579689] w2_p22_p23_x_4:[0.951036194443,0.951086454514] w2_p22_p23_y_4:[-0,0] w2_p22_p23_z_4:[-0.3090795316,-0.308924838863] cos_p22_p23_4:[1,1] w1_p23_p24_x_5:[-0.3090795316,-0.308924838863] w1_p23_p24_y_5:[-0,0] w1_p23_p24_z_5:[-0.951086454514,-0.951036194443] w2_p23_p24_x_5:[-0.311066529654,-0.306913680979] w2_p23_p24_y_5:[-0,0] w2_p23_p24_z_5:[-0.951737354764,-0.950388138669] cos_p23_p24_5:[1,1] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.99609917141,-0.99100658836] uni_v_palm_p32_z_6:[0.0876591457551,0.133813085375] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.889451596217,0.907684138491] w2_palm_p32_y_6:[0.0361472362514,0.0605771947306] w2_palm_p32_z_6:[0.418727150286,0.448655158587] cos_0_palm_p32_6:[0.98563410278,0.992340342147] cos_1_palm_p32_6:[0.889451596217,0.907684138491] w1_p32_p33_x_7:[0.889451596217,0.907684138491] w1_p32_p33_y_7:[0.0361472362514,0.0605771947306] w1_p32_p33_z_7:[0.418727150286,0.448655158587] w2_p32_p33_x_7:[0.999594294932,1] w2_p32_p33_y_7:[-0.00364079839029,1.0090750271e-11] w2_p32_p33_z_7:[-0.0245026629635,0] cos_p32_p33_7:[0.879123807439,0.907473618905] w1_p33_p34_x_8:[0.689415446244,0.707106781195] w1_p33_p34_y_8:[-0.0971780032749,-0.0619762333255] w1_p33_p34_z_8:[-0.718388584322,-0.700743857546] w2_p33_p34_x_8:[0.936975505342,0.954505652051] w2_p33_p34_y_8:[-0.0473452631253,-0.0276191346714] w2_p33_p34_z_8:[-0.344925857326,-0.298485563582] cos_p33_p34_8:[0.879123807439,0.907473618905] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.84273287997,-0.819205229137] w2_palm_p40_y_9:[-0.573487306228,-0.536704390653] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.975409448223,0.985486419936] uni_u_p40_p42_x_10:[-0.690324383588,-0.671051715526] uni_u_p40_p42_y_10:[-0.46977195334,-0.439641239177] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.57421612449,-0.535044802228] uni_v_p40_p42_y_10:[0.818819350399,0.84453944002] uni_v_p40_p42_z_10:[-0,0.00805766370016] w1_p40_p42_x_10:[-0.573487306228,-0.536704390653] w1_p40_p42_y_10:[0.819205229137,0.84273287997] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.597185366273,-0.571977874128] w2_p40_p42_y_10:[-0.406922359527,-0.378462759571] w2_p40_p42_z_10:[0.707106781156,0.715068479578] cos_0_p40_p42_10:[0.996327996268,1] cos_1_p40_p42_10:[0.9802528259,0.986235670802] w1_p42_p43_x_11:[-0.597185366273,-0.571977874128] w1_p42_p43_y_11:[-0.406922359527,-0.378462759571] w1_p42_p43_z_11:[0.707106781156,0.715068479578] w2_p42_p43_x_11:[-0,0.0134316169711] w2_p42_p43_y_11:[-0,0.00129060584378] w2_p42_p43_z_11:[0.99981757139,1] cos_p42_p43_11:[0.707106781187,0.7082521742] w1_p43_p44_x_12:[-0.59718224696,-0.571944696476] w1_p43_p44_y_12:[-0.406058693922,-0.378309988052] w1_p43_p44_z_12:[0.707106781156,0.715068760365] w2_p43_p44_x_12:[-0,0.014070526219] w2_p43_p44_y_12:[-0,0.00177985822476] w2_p43_p44_z_12:[0.999805143901,1] cos_p43_p44_12:[0.707106781187,0.7082521742] sph_w1_p34_X_3_x_13:[-0,0] sph_w1_p34_X_3_y_13:[0.99100658836,0.99609917141] sph_w1_p34_X_3_z_13:[-0.133813085375,-0.0876591457551] sph_w2_p34_X_3_x_13:[-0.172593870338,-0.143254249563] sph_w2_p34_X_3_y_13:[0.986101908078,0.989685933366] sph_w2_p34_X_3_z_13:[-1.11022302465e-27,2.12958707153e-09] cos_p34_X_3_13:[0.980785280403,0.985835005579] in_patch_X_3_object_u_14:[0.0641485745212,0.128297149045] in_patch_X_3_object_v_14:[0.499999999995,0.543820673296] in_patch_X_3_object_l_14:[382.253093035,382.253093035] sph_w1_p44_X_4_x_15:[-0.836223423804,-0.810514024432] sph_w1_p44_X_4_y_15:[-0.568603395751,-0.529765863425] sph_w1_p44_X_4_z_15:[0.140021004692,0.151887000878] sph_w2_p44_X_4_x_15:[0.14324965466,0.172589295985] sph_w2_p44_X_4_y_15:[-0.989686598455,-0.986102673685] sph_w2_p44_X_4_z_15:[-2.12968440046e-09,4.22178933133e-16] cos_p44_X_4_15:[0.400387381643,0.445948924791] in_patch_X_4_object_u_16:[0.249999999997,0.311639977212] in_patch_X_4_object_v_16:[0.95686916883,1] in_patch_X_4_object_l_16:[382.265354258,382.265354258] p14_r_x:[44.9085820183,45.2615353935] p14_r_y:[-38.2821437392,-38.257345333] p14_r_z:[200.317550671,200.981432074] p24_r_x:[45.1818434488,45.1843640211] p24_r_y:[-0,0] p24_r_z:[205.359075288,205.364138101] }


Cuik executed in 31 (31) child processors
STATITISTICS FOR Cuik:

Volume of the search space: 2.5082e+16
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 0.242152
Number of processors: 32
User time in process: 68.000000 seg (1.133333 min)
Box level information:
  N processed boxes :   1286
  Max depth         :     45
  Types of boxes:
    N solution boxes:      8 (0) ( 0.62%)
    N empty boxes   :    213  (16.56%)
    N bisected boxes:   1065  (82.81%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :   1770
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

