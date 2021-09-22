
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
Equations from file: /home/porta/cuik/CuikSuite/examples/IJRR/teapot/3_contacts_middle_index_thumb/SAHandplusTeapot_kin.cuik
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
   object_u_z : [0.9,1]
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
   in_patch_X_2_object_l_14 : [428.915319233,428.915319233]
   sph_w1_p33_X_3_x_15 : [-1,1]
   sph_w1_p33_X_3_y_15 : [-1,1]
   sph_w1_p33_X_3_z_15 : [-1,1]
   sph_w2_p33_X_3_x_15 : [-1,1]
   sph_w2_p33_X_3_y_15 : [-1,1]
   sph_w2_p33_X_3_z_15 : [-1,1]
   cos_p33_X_3_15 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_16 : [0,1]
   in_patch_X_3_object_v_16 : [0,1]

[DUMMY VARS]
   in_patch_X_3_object_w_16 : [0,1]

[SECONDARY VARS]
   in_patch_X_3_object_l_16 : [145.796048374,155.363688164]
   sph_w1_p44_X_4_x_17 : [-1,1]
   sph_w1_p44_X_4_y_17 : [-1,1]
   sph_w1_p44_X_4_z_17 : [-1,1]
   sph_w2_p44_X_4_x_17 : [-1,1]
   sph_w2_p44_X_4_y_17 : [-1,1]
   sph_w2_p44_X_4_z_17 : [-1,1]
   cos_p44_X_4_17 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_4_object_u_18 : [0,1]
   in_patch_X_4_object_v_18 : [0,1]

[DUMMY VARS]
   in_patch_X_4_object_w_18 : [0,1]

[SECONDARY VARS]
   in_patch_X_4_object_l_18 : [752.793978529,752.793978529]

[CARTESIAN VARS]
   p14_r_x : [-1666.12699203,1666.12699203]
   p14_r_y : [-1666.12699203,1666.12699203]
   p14_r_z : [-1666.12699203,1666.12699203]
   p34_r_x : [-1666.12699203,1666.12699203]
   p34_r_y : [-1666.12699203,1666.12699203]
   p34_r_z : [-1666.12699203,1666.12699203]

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
   0.5*p12_u_x+0.866025403784*p12_w_x-0.866025403784*p12_wp_x-w2_palm_p12_x_0 = -0;
   0.5*p12_u_y+0.866025403784*p12_w_y-0.866025403784*p12_wp_y-w2_palm_p12_y_0 = -0;
   0.5*p12_u_z+0.866025403784*p12_w_z-0.866025403784*p12_wp_z-w2_palm_p12_z_0 = -0;
   uni_v_palm_p12_x_0*w1_palm_p12_x_0+uni_v_palm_p12_y_0*w1_palm_p12_y_0+uni_v_palm_p12_z_0*w1_palm_p12_z_0-cos_0_palm_p12_0 = 0;
   uni_u_palm_p12_x_0*w2_palm_p12_x_0+uni_u_palm_p12_y_0*w2_palm_p12_y_0+uni_u_palm_p12_z_0*w2_palm_p12_z_0-cos_1_palm_p12_0 = 0;
   p12_v_x-p13_v_x = -0;
   p12_v_y-p13_v_y = -0;
   p12_v_z-p13_v_z = -0;
   0.5*p12_u_x+0.866025403784*p12_w_x-0.866025403784*p12_wp_x-w1_p12_p13_x_1 = -0;
   0.5*p12_u_y+0.866025403784*p12_w_y-0.866025403784*p12_wp_y-w1_p12_p13_y_1 = -0;
   0.5*p12_u_z+0.866025403784*p12_w_z-0.866025403784*p12_wp_z-w1_p12_p13_z_1 = -0;
   p13_u_x-w2_p12_p13_x_1 = -0;
   p13_u_y-w2_p12_p13_y_1 = -0;
   p13_u_z-w2_p12_p13_z_1 = -0;
   w1_p12_p13_x_1*w2_p12_p13_x_1+w1_p12_p13_y_1*w2_p12_p13_y_1+w1_p12_p13_z_1*w2_p12_p13_z_1-cos_p12_p13_1 = 0;
   p13_v_x-p14_v_x = -0;
   p13_v_y-p14_v_y = -0;
   p13_v_z-p14_v_z = -0;
   0.5*p13_u_x+0.866025403784*p13_w_x-0.866025403784*p13_wp_x-w1_p13_p14_x_2 = -0;
   0.5*p13_u_y+0.866025403784*p13_w_y-0.866025403784*p13_wp_y-w1_p13_p14_y_2 = -0;
   0.5*p13_u_z+0.866025403784*p13_w_z-0.866025403784*p13_wp_z-w1_p13_p14_z_2 = -0;
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
   p24_v_x+sph_w1_p24_X_2_x_13 = 0;
   p24_v_y+sph_w1_p24_X_2_y_13 = 0;
   p24_v_z+sph_w1_p24_X_2_z_13 = 0;
   X_2_w_x-X_2_wp_x-sph_w2_p24_X_2_x_13 = -0;
   X_2_w_y-X_2_wp_y-sph_w2_p24_X_2_y_13 = -0;
   X_2_w_z-X_2_wp_z-sph_w2_p24_X_2_z_13 = -0;
   sph_w1_p24_X_2_x_13*sph_w2_p24_X_2_x_13+sph_w1_p24_X_2_y_13*sph_w2_p24_X_2_y_13+sph_w1_p24_X_2_z_13*sph_w2_p24_X_2_z_13-cos_p24_X_2_13 = 0;
   in_patch_X_2_object_l_14^2 = 183968.351073;
   X_2_w_x*in_patch_X_2_object_l_14-X_2_wp_x*in_patch_X_2_object_l_14-302.8971*object_u_x-303.680256*object_v_x = 0;
   X_2_w_y*in_patch_X_2_object_l_14-X_2_wp_y*in_patch_X_2_object_l_14-302.8971*object_u_y-303.680256*object_v_y = 0;
   X_2_w_z*in_patch_X_2_object_l_14-X_2_wp_z*in_patch_X_2_object_l_14-302.8971*object_u_z-303.680256*object_v_z = 0;
   p33_w_x-p33_wp_x-sph_w1_p33_X_3_x_15 = -0;
   p33_w_y-p33_wp_y-sph_w1_p33_X_3_y_15 = -0;
   p33_w_z-p33_wp_z-sph_w1_p33_X_3_z_15 = -0;
   X_3_w_x-X_3_wp_x-sph_w2_p33_X_3_x_15 = -0;
   X_3_w_y-X_3_wp_y-sph_w2_p33_X_3_y_15 = -0;
   X_3_w_z-X_3_wp_z-sph_w2_p33_X_3_z_15 = -0;
   sph_w1_p33_X_3_x_15*sph_w2_p33_X_3_x_15+sph_w1_p33_X_3_y_15*sph_w2_p33_X_3_y_15+sph_w1_p33_X_3_z_15*sph_w2_p33_X_3_z_15-cos_p33_X_3_15 = 0;
   378.308644719*in_patch_X_3_object_u_16^2+81.7127553646*in_patch_X_3_object_v_16^2-in_patch_X_3_object_l_16^2-2001.89856534*in_patch_X_3_object_u_16+364.961013971*in_patch_X_3_object_v_16-54.5068990643*in_patch_X_3_object_w_16 = -23312.893186;
   5.422522*object_u_x*in_patch_X_3_object_u_16+1.934302*object_u_x*in_patch_X_3_object_v_16+4.274256*object_v_x*in_patch_X_3_object_u_16-8.830132*object_v_x*in_patch_X_3_object_v_16+18.183389*object_w_x*in_patch_X_3_object_u_16-18.183389*object_wp_x*in_patch_X_3_object_u_16-X_3_w_x*in_patch_X_3_object_l_16+X_3_wp_x*in_patch_X_3_object_l_16-143.520004*object_u_x-52.104718*object_v_x = -0;
   5.422522*object_u_y*in_patch_X_3_object_u_16+1.934302*object_u_y*in_patch_X_3_object_v_16+4.274256*object_v_y*in_patch_X_3_object_u_16-8.830132*object_v_y*in_patch_X_3_object_v_16+18.183389*object_w_y*in_patch_X_3_object_u_16-18.183389*object_wp_y*in_patch_X_3_object_u_16-X_3_w_y*in_patch_X_3_object_l_16+X_3_wp_y*in_patch_X_3_object_l_16-143.520004*object_u_y-52.104718*object_v_y = -0;
   5.422522*object_u_z*in_patch_X_3_object_u_16+1.934302*object_u_z*in_patch_X_3_object_v_16+4.274256*object_v_z*in_patch_X_3_object_u_16-8.830132*object_v_z*in_patch_X_3_object_v_16+18.183389*object_w_z*in_patch_X_3_object_u_16-18.183389*object_wp_z*in_patch_X_3_object_u_16-X_3_w_z*in_patch_X_3_object_l_16+X_3_wp_z*in_patch_X_3_object_l_16-143.520004*object_u_z-52.104718*object_v_z = -0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_17 = -0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_17 = -0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_17 = -0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_17 = -0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_17 = -0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_17 = -0;
   sph_w1_p44_X_4_x_17*sph_w2_p44_X_4_x_17+sph_w1_p44_X_4_y_17*sph_w2_p44_X_4_y_17+sph_w1_p44_X_4_z_17*sph_w2_p44_X_4_z_17-cos_p44_X_4_17 = 0;
   in_patch_X_4_object_l_18^2 = 566698.774109;
   X_4_w_x*in_patch_X_4_object_l_18-X_4_wp_x*in_patch_X_4_object_l_18-36.224804*object_u_x+751.921896*object_v_x = 0;
   X_4_w_y*in_patch_X_4_object_l_18-X_4_wp_y*in_patch_X_4_object_l_18-36.224804*object_u_y+751.921896*object_v_y = 0;
   X_4_w_z*in_patch_X_4_object_l_18-X_4_wp_z*in_patch_X_4_object_l_18-36.224804*object_u_z+751.921896*object_v_z = 0;
   19.776*object_u_x*in_patch_X_2_object_u_14-6.007*object_u_x*in_patch_X_3_object_u_16-1.018*object_u_x*in_patch_X_3_object_w_16-19.725*object_v_x*in_patch_X_2_object_u_14+16.546*object_v_x*in_patch_X_3_object_u_16-0.223*object_v_x*in_patch_X_3_object_w_16-15.356*object_w_x*in_patch_X_2_object_v_14-2.098*object_w_x*in_patch_X_3_object_u_16-8.674*object_w_x*in_patch_X_3_object_v_16+0.356*object_w_x*in_patch_X_3_object_w_16+15.356*object_wp_x*in_patch_X_2_object_v_14+2.098*object_wp_x*in_patch_X_3_object_u_16+8.674*object_wp_x*in_patch_X_3_object_v_16-0.356*object_wp_x*in_patch_X_3_object_w_16+67.8*p22_u_x+30*p23_u_x+3.852*p24_u_x+0.811*p24_v_x-11.268*p24_w_x+11.268*p24_wp_x-67.8*p32_u_x-14.619*p33_u_x+0.012*p33_v_x+0.141*p33_w_x-0.141*p33_wp_x-8.05*object_u_x+19.536*object_v_x+12.015*object_w_x-12.015*object_wp_x+13*X_2_w_x-13*X_2_wp_x-13*X_3_w_x+13*X_3_wp_x = -0;
   19.776*object_u_y*in_patch_X_2_object_u_14-6.007*object_u_y*in_patch_X_3_object_u_16-1.018*object_u_y*in_patch_X_3_object_w_16-19.725*object_v_y*in_patch_X_2_object_u_14+16.546*object_v_y*in_patch_X_3_object_u_16-0.223*object_v_y*in_patch_X_3_object_w_16-15.356*object_w_y*in_patch_X_2_object_v_14-2.098*object_w_y*in_patch_X_3_object_u_16-8.674*object_w_y*in_patch_X_3_object_v_16+0.356*object_w_y*in_patch_X_3_object_w_16+15.356*object_wp_y*in_patch_X_2_object_v_14+2.098*object_wp_y*in_patch_X_3_object_u_16+8.674*object_wp_y*in_patch_X_3_object_v_16-0.356*object_wp_y*in_patch_X_3_object_w_16+67.8*p22_u_y+30*p23_u_y+3.852*p24_u_y+0.811*p24_v_y-11.268*p24_w_y+11.268*p24_wp_y-67.8*p32_u_y-14.619*p33_u_y+0.012*p33_v_y+0.141*p33_w_y-0.141*p33_wp_y-8.05*object_u_y+19.536*object_v_y+12.015*object_w_y-12.015*object_wp_y+13*X_2_w_y-13*X_2_wp_y-13*X_3_w_y+13*X_3_wp_y = 40.165;
   19.776*object_u_z*in_patch_X_2_object_u_14-6.007*object_u_z*in_patch_X_3_object_u_16-1.018*object_u_z*in_patch_X_3_object_w_16-19.725*object_v_z*in_patch_X_2_object_u_14+16.546*object_v_z*in_patch_X_3_object_u_16-0.223*object_v_z*in_patch_X_3_object_w_16-15.356*object_w_z*in_patch_X_2_object_v_14-2.098*object_w_z*in_patch_X_3_object_u_16-8.674*object_w_z*in_patch_X_3_object_v_16+0.356*object_w_z*in_patch_X_3_object_w_16+15.356*object_wp_z*in_patch_X_2_object_v_14+2.098*object_wp_z*in_patch_X_3_object_u_16+8.674*object_wp_z*in_patch_X_3_object_v_16-0.356*object_wp_z*in_patch_X_3_object_w_16+67.8*p22_u_z+30*p23_u_z+3.852*p24_u_z+0.811*p24_v_z-11.268*p24_w_z+11.268*p24_wp_z-67.8*p32_u_z-14.619*p33_u_z+0.012*p33_v_z+0.141*p33_w_z-0.141*p33_wp_z-8.05*object_u_z+19.536*object_v_z+12.015*object_w_z-12.015*object_wp_z+13*X_2_w_z-13*X_2_wp_z-13*X_3_w_z+13*X_3_wp_z = -4.72;
   19.776*object_u_x*in_patch_X_2_object_u_14+48.966*object_u_x*in_patch_X_4_object_u_18-19.725*object_v_x*in_patch_X_2_object_u_14+2.359*object_v_x*in_patch_X_4_object_u_18-15.356*object_w_x*in_patch_X_2_object_v_14+15.356*object_w_x*in_patch_X_4_object_v_18+15.356*object_wp_x*in_patch_X_2_object_v_14-15.356*object_wp_x*in_patch_X_4_object_v_18+67.8*p22_u_x+30*p23_u_x+3.852*p24_u_x+0.811*p24_v_x-11.268*p24_w_x+11.268*p24_wp_x-97*p40_u_x-6*p40_v_x+87*p40_w_x-87*p40_wp_x-67.8*p42_u_x-30*p43_u_x-20*p44_u_x-9.743*object_u_x+57.299*object_v_x+13*X_2_w_x-13*X_2_wp_x-13*X_4_w_x+13*X_4_wp_x = 1.3;
   19.776*object_u_y*in_patch_X_2_object_u_14+48.966*object_u_y*in_patch_X_4_object_u_18-19.725*object_v_y*in_patch_X_2_object_u_14+2.359*object_v_y*in_patch_X_4_object_u_18-15.356*object_w_y*in_patch_X_2_object_v_14+15.356*object_w_y*in_patch_X_4_object_v_18+15.356*object_wp_y*in_patch_X_2_object_v_14-15.356*object_wp_y*in_patch_X_4_object_v_18+67.8*p22_u_y+30*p23_u_y+3.852*p24_u_y+0.811*p24_v_y-11.268*p24_w_y+11.268*p24_wp_y-97*p40_u_y-6*p40_v_y+87*p40_w_y-87*p40_wp_y-67.8*p42_u_y-30*p43_u_y-20*p44_u_y-9.743*object_u_y+57.299*object_v_y+13*X_2_w_y-13*X_2_wp_y-13*X_4_w_y+13*X_4_wp_y = 27.1;
   19.776*object_u_z*in_patch_X_2_object_u_14+48.966*object_u_z*in_patch_X_4_object_u_18-19.725*object_v_z*in_patch_X_2_object_u_14+2.359*object_v_z*in_patch_X_4_object_u_18-15.356*object_w_z*in_patch_X_2_object_v_14+15.356*object_w_z*in_patch_X_4_object_v_18+15.356*object_wp_z*in_patch_X_2_object_v_14-15.356*object_wp_z*in_patch_X_4_object_v_18+67.8*p22_u_z+30*p23_u_z+3.852*p24_u_z+0.811*p24_v_z-11.268*p24_w_z+11.268*p24_wp_z-97*p40_u_z-6*p40_v_z+87*p40_w_z-87*p40_wp_z-67.8*p42_u_z-30*p43_u_z-20*p44_u_z-9.743*object_u_z+57.299*object_v_z+13*X_2_w_z-13*X_2_wp_z-13*X_4_w_z+13*X_4_wp_z = -150.15;

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

[SEARCH]

 MIN 172.582639308*cos_0_palm_p22_3^2+11.6568542495*cos_1_palm_p22_3^2+11.6568542495*cos_p22_p23_4^2+11.6568542495*cos_p23_p24_5^2+172.582639308*cos_0_palm_p32_6^2+11.6568542495*cos_1_palm_p32_6^2+11.6568542495*cos_p32_p33_7^2+11.6568542495*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+11.6568542495*cos_p42_p43_11^2+11.6568542495*cos_p43_p44_12^2+cos_p24_X_2_13^2+4*in_patch_X_2_object_u_14^2+4*in_patch_X_2_object_v_14^2+cos_p33_X_3_15^2+4*in_patch_X_3_object_u_16^2+4*in_patch_X_3_object_v_16^2+cos_p44_X_4_17^2+4*in_patch_X_4_object_u_18^2+4*in_patch_X_4_object_v_18^2-345.165278616*cos_0_palm_p22_3-23.313708499*cos_1_palm_p22_3-23.313708499*cos_p22_p23_4-23.313708499*cos_p23_p24_5-345.165278616*cos_0_palm_p32_6-23.313708499*cos_1_palm_p32_6-23.313708499*cos_p32_p33_7-23.313708499*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-23.313708499*cos_p42_p43_11-23.313708499*cos_p43_p44_12-2*cos_p24_X_2_13-4*in_patch_X_2_object_u_14-4*in_patch_X_2_object_v_14-2*cos_p33_X_3_15-4*in_patch_X_3_object_u_16-4*in_patch_X_3_object_v_16-2*cos_p44_X_4_17-4*in_patch_X_4_object_u_18-4*in_patch_X_4_object_v_18+643.316460418




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
%   p12_w_z=p12_w_z
%   p12_wp_x=p12_wp_x
%   p12_wp_y=p12_wp_y
%   p12_wp_z= -0
%   p13_u_x=p13_u_x
%   p13_u_y=p13_u_y
%   p13_u_z=p13_u_z
%   p13_v_x= -0
%   p13_v_y=+0.0343212495372*p14_v_z -1.00058880074
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
%   p33_w_z=sph_w1_p33_X_3_z_15
%   p33_wp_x=p33_wp_x
%   p33_wp_y=-sph_w1_p33_X_3_y_15
%   p33_wp_z= -0
%   p34_u_x=p34_u_x
%   p34_u_y=p34_u_y
%   p34_u_z=p34_u_z
%   p34_v_x= -0
%   p34_v_y=p34_v_y
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
%   w2_palm_p12_y_0=w1_p12_p13_y_1
%   w2_palm_p12_z_0=w1_p12_p13_z_1
%   cos_0_palm_p12_0= +1
%   cos_1_palm_p12_0= +1
%   w1_p12_p13_x_1= +1
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
%   sph_w1_p24_X_2_x_13= -0
%   sph_w1_p24_X_2_y_13=-p24_v_y
%   sph_w1_p24_X_2_z_13=-p24_v_z
%   sph_w2_p24_X_2_x_13=sph_w2_p24_X_2_x_13
%   sph_w2_p24_X_2_y_13=sph_w2_p24_X_2_y_13
%   sph_w2_p24_X_2_z_13=sph_w2_p24_X_2_z_13
%   cos_p24_X_2_13=cos_p24_X_2_13
%   in_patch_X_2_object_u_14=in_patch_X_2_object_u_14
%   in_patch_X_2_object_v_14=in_patch_X_2_object_v_14
%   in_patch_X_2_object_w_14=No in simplification
%   in_patch_X_2_object_l_14= +428.915319233
%   sph_w1_p33_X_3_x_15=sph_w1_p33_X_3_x_15
%   sph_w1_p33_X_3_y_15=sph_w1_p33_X_3_y_15
%   sph_w1_p33_X_3_z_15=sph_w1_p33_X_3_z_15
%   sph_w2_p33_X_3_x_15=sph_w2_p33_X_3_x_15
%   sph_w2_p33_X_3_y_15=sph_w2_p33_X_3_y_15
%   sph_w2_p33_X_3_z_15=sph_w2_p33_X_3_z_15
%   cos_p33_X_3_15=cos_p33_X_3_15
%   in_patch_X_3_object_u_16=in_patch_X_3_object_u_16
%   in_patch_X_3_object_v_16=in_patch_X_3_object_v_16
%   in_patch_X_3_object_w_16=in_patch_X_3_object_w_16
%   in_patch_X_3_object_l_16=in_patch_X_3_object_l_16
%   sph_w1_p44_X_4_x_17=sph_w1_p44_X_4_x_17
%   sph_w1_p44_X_4_y_17=sph_w1_p44_X_4_y_17
%   sph_w1_p44_X_4_z_17=sph_w1_p44_X_4_z_17
%   sph_w2_p44_X_4_x_17=sph_w2_p44_X_4_x_17
%   sph_w2_p44_X_4_y_17=sph_w2_p44_X_4_y_17
%   sph_w2_p44_X_4_z_17=sph_w2_p44_X_4_z_17
%   cos_p44_X_4_17=cos_p44_X_4_17
%   in_patch_X_4_object_u_18=in_patch_X_4_object_u_18
%   in_patch_X_4_object_v_18=in_patch_X_4_object_v_18
%   in_patch_X_4_object_w_18=No in simplification
%   in_patch_X_4_object_l_18= +752.793978529
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
   p33_wp_x : [-1,1]

[SYSTEM VARS]
   p34_u_x : [-1,1]
   p34_u_y : [-1,1]
   p34_u_z : [-1,1]
   p34_v_y : [-1,1]
   p34_v_z : [-1,1]
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
   object_u_z : [0.9,1]
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
   w1_p12_p13_y_1 : [-1,1]
   w1_p12_p13_z_1 : [-1,1]
   w1_p13_p14_x_2 : [-1,1]
   w1_p13_p14_y_2 : [-1,1]
   w1_p13_p14_z_2 : [-1,1]
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
   sph_w2_p24_X_2_x_13 : [-1,1]
   sph_w2_p24_X_2_y_13 : [-1,1]
   sph_w2_p24_X_2_z_13 : [-1,1]
   cos_p24_X_2_13 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_2_object_u_14 : [0,1]
   in_patch_X_2_object_v_14 : [0,1]

[SECONDARY VARS]
   sph_w1_p33_X_3_x_15 : [-1,1]
   sph_w1_p33_X_3_y_15 : [-1,1]
   sph_w1_p33_X_3_z_15 : [-1,1]
   sph_w2_p33_X_3_x_15 : [-1,1]
   sph_w2_p33_X_3_y_15 : [-1,1]
   sph_w2_p33_X_3_z_15 : [-1,1]
   cos_p33_X_3_15 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_3_object_u_16 : [0,1]
   in_patch_X_3_object_v_16 : [0,1]

[DUMMY VARS]
   in_patch_X_3_object_w_16 : [0,1]

[SECONDARY VARS]
   in_patch_X_3_object_l_16 : [145.796048374,155.363688164]
   sph_w1_p44_X_4_x_17 : [-1,1]
   sph_w1_p44_X_4_y_17 : [-1,1]
   sph_w1_p44_X_4_z_17 : [-1,1]
   sph_w2_p44_X_4_x_17 : [-1,1]
   sph_w2_p44_X_4_y_17 : [-1,1]
   sph_w2_p44_X_4_z_17 : [-1,1]
   cos_p44_X_4_17 : [-1.83690953073e-16,1]

[SYSTEM VARS]
   in_patch_X_4_object_u_18 : [0,1]
   in_patch_X_4_object_v_18 : [0,1]

[CARTESIAN VARS]
   p14_r_x : [-1666.12699203,1666.12699203]
   p14_r_y : [-1666.12699203,1666.12699203]
   p14_r_z : [-1666.12699203,1666.12699203]
   p34_r_x : [-1666.12699203,1666.12699203]
   p34_r_y : [-1666.12699203,1666.12699203]
   p34_r_z : [-1666.12699203,1666.12699203]

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
   dummy_X_2_u_x_X_2_v_x : [-1,1]
   dummy_X_2_u_y_X_2_v_y : [-1,1]
   dummy_X_2_u_z_X_2_v_z : [-1,1]
   dummy_X_3_u_x_X_3_v_x : [-1,1]
   dummy_X_3_u_y_X_3_v_y : [-1,1]
   dummy_X_3_u_z_X_3_v_z : [-1,1]
   dummy_X_4_u_x_X_4_v_x : [-1,1]
   dummy_X_4_u_y_X_4_v_y : [-1,1]
   dummy_X_4_u_z_X_4_v_z : [-1,1]
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
   dummy_p24_v_y_sph_w2_p24_X_2_y_13 : [-1,1]
   dummy_p24_v_z_sph_w2_p24_X_2_z_13 : [-1,1]
   dummy_sph_w1_p33_X_3_x_15_sph_w2_p33_X_3_x_15 : [-1,1]
   dummy_sph_w1_p33_X_3_y_15_sph_w2_p33_X_3_y_15 : [-1,1]
   dummy_sph_w1_p33_X_3_z_15_sph_w2_p33_X_3_z_15 : [-1,1]
   dummy_in_patch_X_3_object_u_16_2 : [0,1]
   dummy_in_patch_X_3_object_v_16_2 : [0,1]
   dummy_in_patch_X_3_object_l_16_2 : [21256.4877215,24137.8755999]
   dummy_object_u_x_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_u_x_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_u_16 : [-1,1]
   dummy_X_3_w_x_in_patch_X_3_object_l_16 : [-155.363688164,155.363688164]
   dummy_X_3_wp_x_in_patch_X_3_object_l_16 : [-155.363688164,155.363688164]
   dummy_object_u_y_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_u_16 : [-1,1]
   dummy_X_3_w_y_in_patch_X_3_object_l_16 : [-155.363688164,155.363688164]
   dummy_X_3_wp_y_in_patch_X_3_object_l_16 : [-155.363688164,155.363688164]
   dummy_object_u_z_in_patch_X_3_object_u_16 : [0,1]
   dummy_object_u_z_in_patch_X_3_object_v_16 : [0,1]
   dummy_object_v_z_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_v_z_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_u_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_u_16 : [-1,1]
   dummy_X_3_w_z_in_patch_X_3_object_l_16 : [-155.363688164,155.363688164]
   dummy_X_3_wp_z_in_patch_X_3_object_l_16 : [-155.363688164,155.363688164]
   dummy_sph_w1_p44_X_4_x_17_sph_w2_p44_X_4_x_17 : [-1,1]
   dummy_sph_w1_p44_X_4_y_17_sph_w2_p44_X_4_y_17 : [-1,1]
   dummy_sph_w1_p44_X_4_z_17_sph_w2_p44_X_4_z_17 : [-1,1]
   dummy_object_u_x_in_patch_X_2_object_u_14 : [-1,1]
   dummy_object_u_x_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_v_x_in_patch_X_2_object_u_14 : [-1,1]
   dummy_object_v_x_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_w_x_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_x_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_wp_x_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_u_y_in_patch_X_2_object_u_14 : [-1,1]
   dummy_object_u_y_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_v_y_in_patch_X_2_object_u_14 : [-1,1]
   dummy_object_v_y_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_w_y_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_y_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_2_object_v_14 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_wp_y_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_u_z_in_patch_X_3_object_w_16 : [0,1]
   dummy_object_u_z_in_patch_X_4_object_u_18 : [0,1]
   dummy_object_v_z_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_v_z_in_patch_X_4_object_u_18 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_w_z_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_w_z_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_v_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_3_object_w_16 : [-1,1]
   dummy_object_wp_z_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_u_x_in_patch_X_4_object_u_18 : [-1,1]
   dummy_object_v_x_in_patch_X_4_object_u_18 : [-1,1]
   dummy_object_w_x_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_wp_x_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_u_y_in_patch_X_4_object_u_18 : [-1,1]
   dummy_object_v_y_in_patch_X_4_object_u_18 : [-1,1]
   dummy_object_w_y_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_wp_y_in_patch_X_4_object_v_18 : [-1,1]
   dummy_object_u_z_in_patch_X_2_object_u_14 : [0,1]
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
   X_2_u_x^2+X_2_u_y^2+X_2_u_z^2 = 1;
   X_2_v_x^2+X_2_v_y^2+X_2_v_z^2 = 1;
   dummy_X_2_u_x_X_2_v_x+dummy_X_2_u_y_X_2_v_y+dummy_X_2_u_z_X_2_v_z = 0;
   X_3_u_x^2+X_3_u_y^2+X_3_u_z^2 = 1;
   X_3_v_x^2+X_3_v_y^2+X_3_v_z^2 = 1;
   dummy_X_3_u_x_X_3_v_x+dummy_X_3_u_y_X_3_v_y+dummy_X_3_u_z_X_3_v_z = 0;
   X_4_u_x^2+X_4_u_y^2+X_4_u_z^2 = 1;
   X_4_v_x^2+X_4_v_y^2+X_4_v_z^2 = 1;
   dummy_X_4_u_x_X_4_v_x+dummy_X_4_u_y_X_4_v_y+dummy_X_4_u_z_X_4_v_z = 0;
   0.5*p12_u_x+0.866025403784*p12_w_x-0.866025403784*p12_wp_x = 1;
   0.5*p12_u_y-0.866025403784*p12_wp_y-w1_p12_p13_y_1 = 0;
   0.5*p12_u_z+0.866025403784*p12_w_z-w1_p12_p13_z_1 = 0;
   p13_u_x+dummy_p13_u_y_w1_p12_p13_y_1+dummy_p13_u_z_w1_p12_p13_z_1 = 1;
   0.5*p13_u_x+0.866025403784*p13_w_x-0.866025403784*p13_wp_x-w1_p13_p14_x_2 = 0;
   0.5*p13_u_y-0.866025403784*p13_wp_y-w1_p13_p14_y_2 = 0;
   0.5*p13_u_z+0.866025403784*p13_w_z-w1_p13_p14_z_2 = 0;
   dummy_p14_u_x_w1_p13_p14_x_2+dummy_p14_u_y_w1_p13_p14_y_2+dummy_p14_u_z_w1_p13_p14_z_2 = 1;
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
   0.707106781187*p33_u_x-w1_p33_p34_x_8+0.707106781187*sph_w1_p33_X_3_x_15 = 0;
   0.707106781187*p33_u_y-w1_p33_p34_y_8+0.707106781187*sph_w1_p33_X_3_y_15 = 0;
   0.707106781187*p33_u_z-w1_p33_p34_z_8+0.707106781187*sph_w1_p33_X_3_z_15 = 0;
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
   X_2_w_x-X_2_wp_x-sph_w2_p24_X_2_x_13 = 0;
   X_2_w_y-X_2_wp_y-sph_w2_p24_X_2_y_13 = 0;
   X_2_w_z-X_2_wp_z-sph_w2_p24_X_2_z_13 = 0;
   cos_p24_X_2_13+dummy_p24_v_y_sph_w2_p24_X_2_y_13+dummy_p24_v_z_sph_w2_p24_X_2_z_13 = 0;
   302.8971*object_u_x+303.680256*object_v_x-428.915319233*sph_w2_p24_X_2_x_13 = 0;
   302.8971*object_u_y+303.680256*object_v_y-428.915319233*sph_w2_p24_X_2_y_13 = 0;
   302.8971*object_u_z+303.680256*object_v_z-428.915319233*sph_w2_p24_X_2_z_13 = 0;
   p33_w_x-p33_wp_x-sph_w1_p33_X_3_x_15 = 0;
   X_3_w_x-X_3_wp_x-sph_w2_p33_X_3_x_15 = 0;
   X_3_w_y-X_3_wp_y-sph_w2_p33_X_3_y_15 = 0;
   X_3_w_z-X_3_wp_z-sph_w2_p33_X_3_z_15 = 0;
   cos_p33_X_3_15-dummy_sph_w1_p33_X_3_x_15_sph_w2_p33_X_3_x_15-dummy_sph_w1_p33_X_3_y_15_sph_w2_p33_X_3_y_15-dummy_sph_w1_p33_X_3_z_15_sph_w2_p33_X_3_z_15 = -0;
   2001.89856534*in_patch_X_3_object_u_16-364.961013971*in_patch_X_3_object_v_16+54.5068990643*in_patch_X_3_object_w_16-378.308644719*dummy_in_patch_X_3_object_u_16_2-81.7127553646*dummy_in_patch_X_3_object_v_16_2+dummy_in_patch_X_3_object_l_16_2 = 23312.893186;
   143.520004*object_u_x+52.104718*object_v_x-5.422522*dummy_object_u_x_in_patch_X_3_object_u_16-1.934302*dummy_object_u_x_in_patch_X_3_object_v_16-4.274256*dummy_object_v_x_in_patch_X_3_object_u_16+8.830132*dummy_object_v_x_in_patch_X_3_object_v_16-18.183389*dummy_object_w_x_in_patch_X_3_object_u_16+18.183389*dummy_object_wp_x_in_patch_X_3_object_u_16+dummy_X_3_w_x_in_patch_X_3_object_l_16-dummy_X_3_wp_x_in_patch_X_3_object_l_16 = -0;
   143.520004*object_u_y+52.104718*object_v_y-5.422522*dummy_object_u_y_in_patch_X_3_object_u_16-1.934302*dummy_object_u_y_in_patch_X_3_object_v_16-4.274256*dummy_object_v_y_in_patch_X_3_object_u_16+8.830132*dummy_object_v_y_in_patch_X_3_object_v_16-18.183389*dummy_object_w_y_in_patch_X_3_object_u_16+18.183389*dummy_object_wp_y_in_patch_X_3_object_u_16+dummy_X_3_w_y_in_patch_X_3_object_l_16-dummy_X_3_wp_y_in_patch_X_3_object_l_16 = -0;
   143.520004*object_u_z+52.104718*object_v_z-5.422522*dummy_object_u_z_in_patch_X_3_object_u_16-1.934302*dummy_object_u_z_in_patch_X_3_object_v_16-4.274256*dummy_object_v_z_in_patch_X_3_object_u_16+8.830132*dummy_object_v_z_in_patch_X_3_object_v_16-18.183389*dummy_object_w_z_in_patch_X_3_object_u_16+18.183389*dummy_object_wp_z_in_patch_X_3_object_u_16+dummy_X_3_w_z_in_patch_X_3_object_l_16-dummy_X_3_wp_z_in_patch_X_3_object_l_16 = -0;
   0.140021004726*p44_u_x+0.990148533421*p44_w_x-0.990148533421*p44_wp_x-sph_w1_p44_X_4_x_17 = 0;
   0.140021004726*p44_u_y+0.990148533421*p44_w_y-0.990148533421*p44_wp_y-sph_w1_p44_X_4_y_17 = 0;
   0.140021004726*p44_u_z+0.990148533421*p44_w_z-0.990148533421*p44_wp_z-sph_w1_p44_X_4_z_17 = 0;
   X_4_w_x-X_4_wp_x-sph_w2_p44_X_4_x_17 = 0;
   X_4_w_y-X_4_wp_y-sph_w2_p44_X_4_y_17 = 0;
   X_4_w_z-X_4_wp_z-sph_w2_p44_X_4_z_17 = 0;
   cos_p44_X_4_17-dummy_sph_w1_p44_X_4_x_17_sph_w2_p44_X_4_x_17-dummy_sph_w1_p44_X_4_y_17_sph_w2_p44_X_4_y_17-dummy_sph_w1_p44_X_4_z_17_sph_w2_p44_X_4_z_17 = -0;
   36.224804*object_u_x-751.921896*object_v_x-752.793978529*sph_w2_p44_X_4_x_17 = 0;
   36.224804*object_u_y-751.921896*object_v_y-752.793978529*sph_w2_p44_X_4_y_17 = 0;
   36.224804*object_u_z-751.921896*object_v_z-752.793978529*sph_w2_p44_X_4_z_17 = 0;
   67.8*p22_u_x+30*p23_u_x+3.852*p24_u_x-11.268*p24_w_x+11.268*p24_wp_x-67.8*p32_u_x-14.619*p33_u_x+1.13051215107*object_u_x+28.7402488365*object_v_x+12.015*object_w_x-12.015*object_wp_x+0.141*sph_w1_p33_X_3_x_15-13*sph_w2_p33_X_3_x_15-6.007*dummy_object_u_x_in_patch_X_3_object_u_16+16.546*dummy_object_v_x_in_patch_X_3_object_u_16-2.098*dummy_object_w_x_in_patch_X_3_object_u_16+2.098*dummy_object_wp_x_in_patch_X_3_object_u_16+19.776*dummy_object_u_x_in_patch_X_2_object_u_14-1.018*dummy_object_u_x_in_patch_X_3_object_w_16-19.725*dummy_object_v_x_in_patch_X_2_object_u_14-0.223*dummy_object_v_x_in_patch_X_3_object_w_16-15.356*dummy_object_w_x_in_patch_X_2_object_v_14-8.674*dummy_object_w_x_in_patch_X_3_object_v_16+0.356*dummy_object_w_x_in_patch_X_3_object_w_16+15.356*dummy_object_wp_x_in_patch_X_2_object_v_14+8.674*dummy_object_wp_x_in_patch_X_3_object_v_16-0.356*dummy_object_wp_x_in_patch_X_3_object_w_16 = 0;
   67.8*p22_u_y+30*p23_u_y+3.852*p24_u_y+0.811*p24_v_y+11.268*p24_wp_y-67.8*p32_u_y-14.619*p33_u_y+0.012*p34_v_y+1.13051215107*object_u_y+28.7402488365*object_v_y+12.015*object_w_y-12.015*object_wp_y+0.141*sph_w1_p33_X_3_y_15-13*sph_w2_p33_X_3_y_15-6.007*dummy_object_u_y_in_patch_X_3_object_u_16+16.546*dummy_object_v_y_in_patch_X_3_object_u_16-2.098*dummy_object_w_y_in_patch_X_3_object_u_16+2.098*dummy_object_wp_y_in_patch_X_3_object_u_16+19.776*dummy_object_u_y_in_patch_X_2_object_u_14-1.018*dummy_object_u_y_in_patch_X_3_object_w_16-19.725*dummy_object_v_y_in_patch_X_2_object_u_14-0.223*dummy_object_v_y_in_patch_X_3_object_w_16-15.356*dummy_object_w_y_in_patch_X_2_object_v_14-8.674*dummy_object_w_y_in_patch_X_3_object_v_16+0.356*dummy_object_w_y_in_patch_X_3_object_w_16+15.356*dummy_object_wp_y_in_patch_X_2_object_v_14+8.674*dummy_object_wp_y_in_patch_X_3_object_v_16-0.356*dummy_object_wp_y_in_patch_X_3_object_w_16 = 40.165;
   67.8*p32_u_z+14.619*p33_u_z-0.012*p34_v_z-67.8*p42_u_z-30*p43_u_z-20*p44_u_z-2.31856617804*object_u_z+50.7479400059*object_v_z-12.015*object_w_z+12.015*object_wp_z-0.141*sph_w1_p33_X_3_z_15+13*sph_w2_p33_X_3_z_15+6.007*dummy_object_u_z_in_patch_X_3_object_u_16-16.546*dummy_object_v_z_in_patch_X_3_object_u_16+2.098*dummy_object_w_z_in_patch_X_3_object_u_16-2.098*dummy_object_wp_z_in_patch_X_3_object_u_16+1.018*dummy_object_u_z_in_patch_X_3_object_w_16+48.966*dummy_object_u_z_in_patch_X_4_object_u_18+0.223*dummy_object_v_z_in_patch_X_3_object_w_16+2.359*dummy_object_v_z_in_patch_X_4_object_u_18+8.674*dummy_object_w_z_in_patch_X_3_object_v_16-0.356*dummy_object_w_z_in_patch_X_3_object_w_16+15.356*dummy_object_w_z_in_patch_X_4_object_v_18-8.674*dummy_object_wp_z_in_patch_X_3_object_v_16+0.356*dummy_object_wp_z_in_patch_X_3_object_w_16-15.356*dummy_object_wp_z_in_patch_X_4_object_v_18 = -48.43;
   67.8*p22_u_x+30*p23_u_x+3.852*p24_u_x-11.268*p24_w_x+11.268*p24_wp_x-6*p40_v_x-87*p40_v_y-67.8*p42_u_x-30*p43_u_x-20*p44_u_x-1.18805402697*object_u_x+79.4881888424*object_v_x+19.776*dummy_object_u_x_in_patch_X_2_object_u_14-19.725*dummy_object_v_x_in_patch_X_2_object_u_14-15.356*dummy_object_w_x_in_patch_X_2_object_v_14+15.356*dummy_object_wp_x_in_patch_X_2_object_v_14+48.966*dummy_object_u_x_in_patch_X_4_object_u_18+2.359*dummy_object_v_x_in_patch_X_4_object_u_18+15.356*dummy_object_w_x_in_patch_X_4_object_v_18-15.356*dummy_object_wp_x_in_patch_X_4_object_v_18 = 1.3;
   67.8*p22_u_y+30*p23_u_y+3.852*p24_u_y+0.811*p24_v_y+11.268*p24_wp_y+87*p40_v_x-6*p40_v_y-67.8*p42_u_y-30*p43_u_y-20*p44_u_y-1.18805402697*object_u_y+79.4881888424*object_v_y+19.776*dummy_object_u_y_in_patch_X_2_object_u_14-19.725*dummy_object_v_y_in_patch_X_2_object_u_14-15.356*dummy_object_w_y_in_patch_X_2_object_v_14+15.356*dummy_object_wp_y_in_patch_X_2_object_v_14+48.966*dummy_object_u_y_in_patch_X_4_object_u_18+2.359*dummy_object_v_y_in_patch_X_4_object_u_18+15.356*dummy_object_w_y_in_patch_X_4_object_v_18-15.356*dummy_object_wp_y_in_patch_X_4_object_v_18 = 27.1;
   67.8*p22_u_z+30*p23_u_z+3.852*p24_u_z+0.811*p24_v_z-11.268*p24_w_z-67.8*p42_u_z-30*p43_u_z-20*p44_u_z-1.18805402697*object_u_z+79.4881888424*object_v_z+48.966*dummy_object_u_z_in_patch_X_4_object_u_18+2.359*dummy_object_v_z_in_patch_X_4_object_u_18+15.356*dummy_object_w_z_in_patch_X_4_object_v_18-15.356*dummy_object_wp_z_in_patch_X_4_object_v_18+19.776*dummy_object_u_z_in_patch_X_2_object_u_14-19.725*dummy_object_v_z_in_patch_X_2_object_u_14-15.356*dummy_object_w_z_in_patch_X_2_object_v_14+15.356*dummy_object_wp_z_in_patch_X_2_object_v_14 = -53.15;

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
   X_2_u_x*X_2_v_x-dummy_X_2_u_x_X_2_v_x = 0;
   X_2_u_y*X_2_v_y-dummy_X_2_u_y_X_2_v_y = 0;
   X_2_u_z*X_2_v_z-dummy_X_2_u_z_X_2_v_z = 0;
   X_3_u_x*X_3_v_x-dummy_X_3_u_x_X_3_v_x = 0;
   X_3_u_y*X_3_v_y-dummy_X_3_u_y_X_3_v_y = 0;
   X_3_u_z*X_3_v_z-dummy_X_3_u_z_X_3_v_z = 0;
   X_4_u_x*X_4_v_x-dummy_X_4_u_x_X_4_v_x = 0;
   X_4_u_y*X_4_v_y-dummy_X_4_u_y_X_4_v_y = 0;
   X_4_u_z*X_4_v_z-dummy_X_4_u_z_X_4_v_z = 0;
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
   p24_v_y*sph_w2_p24_X_2_y_13-dummy_p24_v_y_sph_w2_p24_X_2_y_13 = 0;
   p24_v_z*sph_w2_p24_X_2_z_13-dummy_p24_v_z_sph_w2_p24_X_2_z_13 = 0;
   sph_w1_p33_X_3_x_15*sph_w2_p33_X_3_x_15-dummy_sph_w1_p33_X_3_x_15_sph_w2_p33_X_3_x_15 = 0;
   sph_w1_p33_X_3_y_15*sph_w2_p33_X_3_y_15-dummy_sph_w1_p33_X_3_y_15_sph_w2_p33_X_3_y_15 = 0;
   sph_w1_p33_X_3_z_15*sph_w2_p33_X_3_z_15-dummy_sph_w1_p33_X_3_z_15_sph_w2_p33_X_3_z_15 = 0;
   in_patch_X_3_object_u_16^2-dummy_in_patch_X_3_object_u_16_2 = 0;
   in_patch_X_3_object_v_16^2-dummy_in_patch_X_3_object_v_16_2 = 0;
   in_patch_X_3_object_l_16^2-dummy_in_patch_X_3_object_l_16_2 = 0;
   object_u_x*in_patch_X_3_object_u_16-dummy_object_u_x_in_patch_X_3_object_u_16 = 0;
   object_u_x*in_patch_X_3_object_v_16-dummy_object_u_x_in_patch_X_3_object_v_16 = 0;
   object_v_x*in_patch_X_3_object_u_16-dummy_object_v_x_in_patch_X_3_object_u_16 = 0;
   object_v_x*in_patch_X_3_object_v_16-dummy_object_v_x_in_patch_X_3_object_v_16 = 0;
   object_w_x*in_patch_X_3_object_u_16-dummy_object_w_x_in_patch_X_3_object_u_16 = 0;
   object_wp_x*in_patch_X_3_object_u_16-dummy_object_wp_x_in_patch_X_3_object_u_16 = 0;
   X_3_w_x*in_patch_X_3_object_l_16-dummy_X_3_w_x_in_patch_X_3_object_l_16 = 0;
   X_3_wp_x*in_patch_X_3_object_l_16-dummy_X_3_wp_x_in_patch_X_3_object_l_16 = 0;
   object_u_y*in_patch_X_3_object_u_16-dummy_object_u_y_in_patch_X_3_object_u_16 = 0;
   object_u_y*in_patch_X_3_object_v_16-dummy_object_u_y_in_patch_X_3_object_v_16 = 0;
   object_v_y*in_patch_X_3_object_u_16-dummy_object_v_y_in_patch_X_3_object_u_16 = 0;
   object_v_y*in_patch_X_3_object_v_16-dummy_object_v_y_in_patch_X_3_object_v_16 = 0;
   object_w_y*in_patch_X_3_object_u_16-dummy_object_w_y_in_patch_X_3_object_u_16 = 0;
   object_wp_y*in_patch_X_3_object_u_16-dummy_object_wp_y_in_patch_X_3_object_u_16 = 0;
   X_3_w_y*in_patch_X_3_object_l_16-dummy_X_3_w_y_in_patch_X_3_object_l_16 = 0;
   X_3_wp_y*in_patch_X_3_object_l_16-dummy_X_3_wp_y_in_patch_X_3_object_l_16 = 0;
   object_u_z*in_patch_X_3_object_u_16-dummy_object_u_z_in_patch_X_3_object_u_16 = 0;
   object_u_z*in_patch_X_3_object_v_16-dummy_object_u_z_in_patch_X_3_object_v_16 = 0;
   object_v_z*in_patch_X_3_object_u_16-dummy_object_v_z_in_patch_X_3_object_u_16 = 0;
   object_v_z*in_patch_X_3_object_v_16-dummy_object_v_z_in_patch_X_3_object_v_16 = 0;
   object_w_z*in_patch_X_3_object_u_16-dummy_object_w_z_in_patch_X_3_object_u_16 = 0;
   object_wp_z*in_patch_X_3_object_u_16-dummy_object_wp_z_in_patch_X_3_object_u_16 = 0;
   X_3_w_z*in_patch_X_3_object_l_16-dummy_X_3_w_z_in_patch_X_3_object_l_16 = 0;
   X_3_wp_z*in_patch_X_3_object_l_16-dummy_X_3_wp_z_in_patch_X_3_object_l_16 = 0;
   sph_w1_p44_X_4_x_17*sph_w2_p44_X_4_x_17-dummy_sph_w1_p44_X_4_x_17_sph_w2_p44_X_4_x_17 = 0;
   sph_w1_p44_X_4_y_17*sph_w2_p44_X_4_y_17-dummy_sph_w1_p44_X_4_y_17_sph_w2_p44_X_4_y_17 = 0;
   sph_w1_p44_X_4_z_17*sph_w2_p44_X_4_z_17-dummy_sph_w1_p44_X_4_z_17_sph_w2_p44_X_4_z_17 = 0;
   object_u_x*in_patch_X_2_object_u_14-dummy_object_u_x_in_patch_X_2_object_u_14 = 0;
   object_u_x*in_patch_X_3_object_w_16-dummy_object_u_x_in_patch_X_3_object_w_16 = 0;
   object_v_x*in_patch_X_2_object_u_14-dummy_object_v_x_in_patch_X_2_object_u_14 = 0;
   object_v_x*in_patch_X_3_object_w_16-dummy_object_v_x_in_patch_X_3_object_w_16 = 0;
   object_w_x*in_patch_X_2_object_v_14-dummy_object_w_x_in_patch_X_2_object_v_14 = 0;
   object_w_x*in_patch_X_3_object_v_16-dummy_object_w_x_in_patch_X_3_object_v_16 = 0;
   object_w_x*in_patch_X_3_object_w_16-dummy_object_w_x_in_patch_X_3_object_w_16 = 0;
   object_wp_x*in_patch_X_2_object_v_14-dummy_object_wp_x_in_patch_X_2_object_v_14 = 0;
   object_wp_x*in_patch_X_3_object_v_16-dummy_object_wp_x_in_patch_X_3_object_v_16 = 0;
   object_wp_x*in_patch_X_3_object_w_16-dummy_object_wp_x_in_patch_X_3_object_w_16 = 0;
   object_u_y*in_patch_X_2_object_u_14-dummy_object_u_y_in_patch_X_2_object_u_14 = 0;
   object_u_y*in_patch_X_3_object_w_16-dummy_object_u_y_in_patch_X_3_object_w_16 = 0;
   object_v_y*in_patch_X_2_object_u_14-dummy_object_v_y_in_patch_X_2_object_u_14 = 0;
   object_v_y*in_patch_X_3_object_w_16-dummy_object_v_y_in_patch_X_3_object_w_16 = 0;
   object_w_y*in_patch_X_2_object_v_14-dummy_object_w_y_in_patch_X_2_object_v_14 = 0;
   object_w_y*in_patch_X_3_object_v_16-dummy_object_w_y_in_patch_X_3_object_v_16 = 0;
   object_w_y*in_patch_X_3_object_w_16-dummy_object_w_y_in_patch_X_3_object_w_16 = 0;
   object_wp_y*in_patch_X_2_object_v_14-dummy_object_wp_y_in_patch_X_2_object_v_14 = 0;
   object_wp_y*in_patch_X_3_object_v_16-dummy_object_wp_y_in_patch_X_3_object_v_16 = 0;
   object_wp_y*in_patch_X_3_object_w_16-dummy_object_wp_y_in_patch_X_3_object_w_16 = 0;
   object_u_z*in_patch_X_3_object_w_16-dummy_object_u_z_in_patch_X_3_object_w_16 = 0;
   object_u_z*in_patch_X_4_object_u_18-dummy_object_u_z_in_patch_X_4_object_u_18 = 0;
   object_v_z*in_patch_X_3_object_w_16-dummy_object_v_z_in_patch_X_3_object_w_16 = 0;
   object_v_z*in_patch_X_4_object_u_18-dummy_object_v_z_in_patch_X_4_object_u_18 = 0;
   object_w_z*in_patch_X_3_object_v_16-dummy_object_w_z_in_patch_X_3_object_v_16 = 0;
   object_w_z*in_patch_X_3_object_w_16-dummy_object_w_z_in_patch_X_3_object_w_16 = 0;
   object_w_z*in_patch_X_4_object_v_18-dummy_object_w_z_in_patch_X_4_object_v_18 = 0;
   object_wp_z*in_patch_X_3_object_v_16-dummy_object_wp_z_in_patch_X_3_object_v_16 = 0;
   object_wp_z*in_patch_X_3_object_w_16-dummy_object_wp_z_in_patch_X_3_object_w_16 = 0;
   object_wp_z*in_patch_X_4_object_v_18-dummy_object_wp_z_in_patch_X_4_object_v_18 = 0;
   object_u_x*in_patch_X_4_object_u_18-dummy_object_u_x_in_patch_X_4_object_u_18 = 0;
   object_v_x*in_patch_X_4_object_u_18-dummy_object_v_x_in_patch_X_4_object_u_18 = 0;
   object_w_x*in_patch_X_4_object_v_18-dummy_object_w_x_in_patch_X_4_object_v_18 = 0;
   object_wp_x*in_patch_X_4_object_v_18-dummy_object_wp_x_in_patch_X_4_object_v_18 = 0;
   object_u_y*in_patch_X_4_object_u_18-dummy_object_u_y_in_patch_X_4_object_u_18 = 0;
   object_v_y*in_patch_X_4_object_u_18-dummy_object_v_y_in_patch_X_4_object_u_18 = 0;
   object_w_y*in_patch_X_4_object_v_18-dummy_object_w_y_in_patch_X_4_object_v_18 = 0;
   object_wp_y*in_patch_X_4_object_v_18-dummy_object_wp_y_in_patch_X_4_object_v_18 = 0;
   object_u_z*in_patch_X_2_object_u_14-dummy_object_u_z_in_patch_X_2_object_u_14 = 0;
   object_v_z*in_patch_X_2_object_u_14-dummy_object_v_z_in_patch_X_2_object_u_14 = 0;
   object_w_z*in_patch_X_2_object_v_14-dummy_object_w_z_in_patch_X_2_object_v_14 = 0;
   object_wp_z*in_patch_X_2_object_v_14-dummy_object_wp_z_in_patch_X_2_object_v_14 = 0;
   p12_u_y*p14_v_z-p12_w_x = 0;
   0.0343212495372*p12_u_x*p14_v_z-1.00058880074*p12_u_x-p12_w_z = 0;
   0.0343212495372*p12_u_z*p14_v_z-1.00058880074*p12_u_z-p12_wp_x = 0;
   p12_u_x*p14_v_z-p12_wp_y = 0;
   p13_u_y*p14_v_z-p13_w_x = 0;
   0.0343212495372*p13_u_x*p14_v_z-1.00058880074*p13_u_x-p13_w_z = 0;
   0.0343212495372*p13_u_z*p14_v_z-1.00058880074*p13_u_z-p13_wp_x = 0;
   p13_u_x*p14_v_z-p13_wp_y = 0;
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
   p33_u_x*p34_v_y-sph_w1_p33_X_3_z_15 = 0;
   p33_u_z*p34_v_y-p33_wp_x = 0;
   p33_u_x*p34_v_z+sph_w1_p33_X_3_y_15 = 0;
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
   in_patch_X_3_object_u_16*in_patch_X_3_object_v_16-in_patch_X_3_object_w_16 = 0;

[SEARCH]

 MIN 172.582639308*p24_v_y^2+11.6568542495*w1_p22_p23_x_4^2+23.313708499*cos_p23_p24_5^2+172.582639308*cos_0_palm_p32_6^2+11.6568542495*w1_p32_p33_x_7^2+23.313708499*cos_p33_p34_8^2+11.6568542495*cos_palm_p40_9^2+172.582639308*cos_0_p40_p42_10^2+11.6568542495*cos_1_p40_p42_10^2+23.313708499*cos_p43_p44_12^2+cos_p24_X_2_13^2+4*in_patch_X_2_object_u_14^2+4*in_patch_X_2_object_v_14^2+cos_p33_X_3_15^2+4*in_patch_X_3_object_u_16^2+4*in_patch_X_3_object_v_16^2+cos_p44_X_4_17^2+4*in_patch_X_4_object_u_18^2+4*in_patch_X_4_object_v_18^2+345.165278616*p24_v_y-23.313708499*w1_p22_p23_x_4-46.627416998*cos_p23_p24_5-345.165278616*cos_0_palm_p32_6-23.313708499*w1_p32_p33_x_7-46.627416998*cos_p33_p34_8-23.313708499*cos_palm_p40_9-345.165278616*cos_0_p40_p42_10-23.313708499*cos_1_p40_p42_10-46.627416998*cos_p43_p44_12-2*cos_p24_X_2_13-4*in_patch_X_2_object_u_14-4*in_patch_X_2_object_v_14-2*cos_p33_X_3_15-4*in_patch_X_3_object_u_16-4*in_patch_X_3_object_v_16-2*cos_p44_X_4_17-4*in_patch_X_4_object_u_18-4*in_patch_X_4_object_v_18+643.316460418

==========================================================================
Cuik executed in 32 processors
SOLUTIONS (to input file /home/porta/cuik/CuikSuite/examples/IJRR/teapot/3_contacts_middle_index_thumb/SAHandplusTeapot_kin.cuik):

   1 (err:0.865014 min:8.73571 tm:254):{ 257  p12_u_x:[0.499084890323,0.500973447698] p12_u_y:[0.0296775437051,0.0297591727031] p12_u_z:[0.864952148486,0.866044125109] p12_v_x:[-0,0] p12_v_y:[-0.999411891012,-0.999410141083] p12_v_z:[0.0342909930712,0.0343419797981] p13_u_x:[0.99999746834,1] p13_u_y:[-7.73212104449e-05,7.73212104449e-05] p13_u_z:[-0.00225017870922,0.00225017870922] p13_v_x:[-0,0] p13_v_y:[-0.999411891012,-0.999410141083] p13_v_z:[0.0342909930712,0.0343419797981] p14_u_x:[0.487816096436,0.511989939498] p14_u_y:[-0.0299812860131,-0.0294578242852] p14_u_z:[-0.872506519218,-0.858541519242] p14_v_x:[-0,0] p14_v_y:[-0.999411891012,-0.999410141083] p14_v_z:[0.0342909930712,0.0343419797981] p22_u_x:[-8.47272782982e-05,0.001093501823] p22_u_y:[0.297605376552,0.309676911463] p22_u_z:[0.950803525872,0.954688975465] p22_v_x:[-0,0] p22_v_y:[-0.954704625282,-0.9507887485] p22_v_z:[0.297558247813,0.309736086312] p23_u_x:[0.999934389885,1] p23_u_y:[-1.05368926641e-11,0.00355207997199] p23_u_z:[-0,0.0108695363952] p23_v_x:[-0,0] p23_v_y:[-0.954704625282,-0.9507887485] p23_v_z:[0.297558247813,0.309736086312] p24_u_x:[0.999999635866,1] p24_u_y:[-1.05368926641e-11,0.000266064384574] p24_u_z:[-0,0.000808981783726] p24_v_x:[-0,0] p24_v_y:[-0.954704625282,-0.9507887485] p24_v_z:[0.297558247813,0.309736086312] p32_u_x:[0.367009124706,0.373381390043] p32_u_y:[0.294150012896,0.309808311454] p32_u_z:[0.875866065992,0.882485168327] p32_v_x:[-0,0] p32_v_y:[-0.948766379196,-0.942846157879] p32_v_z:[0.316144819104,0.333108954947] p33_u_x:[0.508178626424,0.540520758806] p33_u_y:[0.270980795527,0.286981516378] p33_u_z:[0.7944025944,0.817229516741] p33_v_x:[-0,0] p33_v_y:[-0.948766379196,-0.942846157879] p33_v_z:[0.316144819104,0.333108954947] p34_u_x:[0.639531936987,0.696281000055] p34_u_y:[0.231368008972,0.25665678735] p34_u_z:[0.677040829401,0.730561794131] p34_v_x:[-0,0] p34_v_y:[-0.948766379196,-0.942846157879] p34_v_z:[0.316144819104,0.333108954947] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.897610793531,-0.88941506245] p40_v_y:[0.440838884735,0.456861187593] p40_v_z:[-0,0] p42_u_x:[-0,3.92638966012e-07] p42_u_y:[-4.20270444256e-09,3.12030634481e-07] p42_u_z:[0.999999999984,1] p42_v_x:[-0.897654894773,-0.889469781938] p42_v_y:[0.440654493257,0.457033992481] p42_v_z:[-0,1.79425014419e-09] p43_u_x:[-3.28755679702e-08,0] p43_u_y:[-0,2.3293357942e-11] p43_u_z:[0.999999999985,1] p43_v_x:[-0.897654894773,-0.889469781938] p43_v_y:[0.440654493257,0.457033992481] p43_v_z:[-0,1.79425014419e-09] p44_u_x:[-0,5.7310412112e-10] p44_u_y:[-0,2.76671884942e-10] p44_u_z:[0.999999998515,1] p44_v_x:[-0.897654894773,-0.889469781938] p44_v_y:[0.440654493257,0.457033992481] p44_v_z:[-0,1.79425014419e-09] object_u_x:[-2.76053943594e-13,9.53800624672e-11] object_u_y:[0.428406037843,0.43588989437] object_u_z:[0.9,0.903595792518] object_v_x:[-0,9.5409430431e-11] object_v_y:[0.899999999562,0.903583938636] object_v_z:[-0.435889895233,-0.428411094442] X_2_u_x:[0.999999999985,1] X_2_u_y:[-0,7.16639629755e-11] X_2_u_z:[-1.06124196755e-11,3.11814591748e-11] X_2_v_x:[-0,3.99606702823e-11] X_2_v_y:[0.326955528805,0.334791666696] X_2_v_z:[-0.945039725202,-0.942292173312] X_3_u_x:[-0,0.0643069086197] X_3_u_y:[-0.695980561168,-0.685065528249] X_3_u_z:[0.715884959924,0.72851583064] X_3_v_x:[-0.998915447281,-0.996091282297] X_3_v_y:[-0,0.0446898917711] X_3_v_z:[0.0376145111586,0.0882689593214] X_4_u_x:[0.999999999985,1] X_4_u_y:[-0,1.66324767382e-11] X_4_u_z:[-2.06005118712e-11,0] X_4_v_x:[-1.80877531059e-11,0] X_4_v_y:[0.471395671621,0.478693361463] X_4_v_z:[0.877982155679,0.881922069794] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411891012,-0.999410141083] uni_v_palm_p12_z_0:[0.0342909930712,0.0343419797981] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.86664891513e-05,3.6342344802e-05] w2_palm_p12_z_0:[-0.00112374738972,0.00105606219937] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[1,1] w1_p12_p13_y_1:[-3.86664891513e-05,3.6342344802e-05] w1_p12_p13_z_1:[-0.00112374738972,0.00105606219937] w2_p12_p13_x_1:[0.99999746834,1] w2_p12_p13_y_1:[-7.73212104449e-05,7.73212104449e-05] w2_p12_p13_z_1:[-0.00225017870922,0.00225017870922] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[0.498048868668,0.501949865506] w1_p13_p14_y_2:[-0.0297796875266,-0.0296581352485] w1_p13_p14_z_2:[-0.866641175912,-0.864387290343] w2_p13_p14_x_2:[0.487816096436,0.511989939498] w2_p13_p14_y_2:[-0.0299812860131,-0.0294578242852] w2_p13_p14_z_2:[-0.872506519218,-0.858541519242] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.954704625282,-0.9507887485] uni_v_palm_p22_z_3:[0.297558247813,0.309736086312] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.707106781156,0.70775986915] w2_palm_p22_y_3:[0.210226204369,0.218987682035] w2_palm_p22_z_3:[0.671582426373,0.675101040907] cos_0_palm_p22_3:[0.9507887485,0.954704625282] cos_1_palm_p22_3:[0.707106781187,0.70775986915] w1_p22_p23_x_4:[0.707106781156,0.70775986915] w1_p22_p23_y_4:[0.210226204369,0.218987682035] w1_p22_p23_z_4:[0.671582426373,0.675101040907] w2_p22_p23_x_4:[0.999934389885,1] w2_p22_p23_y_4:[-1.05368926641e-11,0.00355207997199] w2_p22_p23_z_4:[-0,0.0108695363952] cos_p22_p23_4:[0.707106781187,0.715176025298] w1_p23_p24_x_5:[0.707106781153,0.715176025296] w1_p23_p24_y_5:[-0.222835073117,-0.208814145305] w1_p23_p24_z_5:[-0.675078114594,-0.664123450813] w2_p23_p24_x_5:[0.999999635866,1] w2_p23_p24_y_5:[-1.05368926641e-11,0.000266064384574] w2_p23_p24_z_5:[-0,0.000808981783726] cos_p23_p24_5:[0.707106781187,0.715176025298] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.948766379196,-0.942846157879] uni_v_palm_p32_z_6:[0.316144819104,0.333108954947] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.91709837942,0.920082052483] w2_palm_p32_y_6:[0.125455643988,0.132676267008] w2_palm_p32_z_6:[0.370029610064,0.377839790299] cos_0_palm_p32_6:[0.930432778468,0.936949745494] cos_1_palm_p32_6:[0.91709837942,0.920082052483] w1_p32_p33_x_7:[0.91709837942,0.920082052483] w1_p32_p33_y_7:[0.125455643988,0.132676267008] w1_p32_p33_z_7:[0.370029610064,0.377839790299] w2_p32_p33_x_7:[0.508178626424,0.540520758806] w2_p32_p33_y_7:[0.270980795527,0.286981516378] w2_p32_p33_z_7:[0.7944025944,0.817229516741] cos_p32_p33_7:[0.807055972084,0.831224064375] w1_p33_p34_x_8:[0.968066216304,0.977402583124] w1_p33_p34_y_8:[0.0684882643618,0.0832748383665] w1_p33_p34_z_8:[0.200709436256,0.236812924404] w2_p33_p34_x_8:[0.639531936987,0.696281000055] w2_p33_p34_y_8:[0.231368008972,0.25665678735] w2_p33_p34_z_8:[0.677040829401,0.730561794131] cos_p33_p34_8:[0.807055972084,0.831224064375] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.456861187593,-0.440838884735] w2_palm_p40_y_9:[-0.897610793531,-0.88941506245] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.94637837415,0.95209576621] uni_u_p40_p42_x_10:[-0.374237703555,-0.361113039017] uni_u_p40_p42_y_10:[-0.735277609874,-0.728564079236] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.897654894773,-0.889469781938] uni_v_p40_p42_y_10:[0.440654493257,0.457033992481] uni_v_p40_p42_z_10:[-0,1.79425014419e-09] w1_p40_p42_x_10:[-0.897610793531,-0.88941506245] w1_p40_p42_y_10:[0.440838884735,0.456861187593] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.323171835369,-0.303565564158] w2_p40_p42_y_10:[-0.634737866303,-0.628812622372] w2_p40_p42_z_10:[0.707106512676,0.707106968782] cos_0_p40_p42_10:[0.999645501099,1] cos_1_p40_p42_10:[0.977299961478,0.984946848575] w1_p42_p43_x_11:[-0.323171835369,-0.303565564158] w1_p42_p43_y_11:[-0.634737866303,-0.628812622372] w1_p42_p43_z_11:[0.707106512676,0.707106968782] w2_p42_p43_x_11:[-3.28755679702e-08,0] w2_p42_p43_y_11:[-0,2.3293357942e-11] w2_p42_p43_z_11:[0.999999999985,1] cos_p42_p43_11:[0.707106781187,0.707106781368] w1_p43_p44_x_12:[-0.323410611291,-0.311589779566] w1_p43_p44_y_12:[-0.638629610734,-0.628950114365] w1_p43_p44_z_12:[0.707106780287,0.707106781344] w2_p43_p44_x_12:[-0,5.7310412112e-10] w2_p43_p44_y_12:[-0,2.76671884942e-10] w2_p43_p44_z_12:[0.999999998515,1] cos_p43_p44_12:[0.707106781187,0.707106781368] sph_w1_p24_X_2_x_13:[-0,0] sph_w1_p24_X_2_y_13:[0.9507887485,0.954704625282] sph_w1_p24_X_2_z_13:[-0.309736086312,-0.297558247813] sph_w2_p24_X_2_x_13:[-1.94950473299e-13,6.73334409477e-11] sph_w2_p24_X_2_y_13:[0.942292173208,0.945039725239] sph_w2_p24_X_2_z_13:[0.326955528841,0.334789987326] cos_p24_X_2_13:[0.792940526191,0.804946489201] in_patch_X_2_object_u_14:[-0,0.0159636410257] in_patch_X_2_object_v_14:[0.334840744123,0.365806472739] in_patch_X_2_object_l_14:[428.915319233,428.915319233] sph_w1_p33_X_3_x_15:[0.841002827201,0.861441762215] sph_w1_p33_X_3_y_15:[-0.177903803043,-0.16033908037] sph_w1_p33_X_3_z_15:[-0.51149257836,-0.479084926772] sph_w2_p33_X_3_x_15:[-0.0606268928327,-0.0553252862243] sph_w2_p33_X_3_y_15:[-0.72719929907,-0.719134184073] sph_w2_p33_X_3_z_15:[-0.692183483138,-0.684204599938] cos_p33_X_3_15:[0.396804116383,0.428276123835] in_patch_X_3_object_u_16:[0.458091393777,0.500000000005] in_patch_X_3_object_v_16:[0.332094090861,0.388053420117] in_patch_X_3_object_l_16:[150.091372801,150.397780107] sph_w1_p44_X_4_x_17:[-0.452531537453,-0.425077625771] sph_w1_p44_X_4_y_17:[-0.894261220526,-0.880707198642] sph_w1_p44_X_4_z_17:[0.140021004497,0.14002101214] sph_w2_p44_X_4_x_17:[-0,4.60301778072e-12] sph_w2_p44_X_4_y_17:[-0.881922069672,-0.87798215572] sph_w2_p44_X_4_z_17:[0.471395397162,0.478693361463] cos_p44_X_4_17:[0.839833579946,0.854676400072] in_patch_X_4_object_u_18:[0.560371923713,0.577235256921] in_patch_X_4_object_v_18:[0.249999999997,0.312500000003] in_patch_X_4_object_l_18:[752.793978529,752.793978529] p14_r_x:[59.5378796141,59.6659997542] p14_r_y:[-38.1551821739,-38.1450084541] p14_r_z:[204.006250305,204.215297047] p34_r_x:[35.8285774479,36.7988414197] p34_r_y:[68.2877555936,69.7734202822] p34_r_z:[228.824876033,229.779379916] }
   2 (err:0.865019 min:8.70545 tm:254):{ 257  p12_u_x:[0.499084890323,0.500973447698] p12_u_y:[0.0296775437051,0.029759067996] p12_u_z:[0.864952152088,0.866044125109] p12_v_x:[-0,0] p12_v_y:[-0.999411890787,-0.99941014523] p12_v_z:[0.0342909996263,0.034341858967] p13_u_x:[0.99999746834,1] p13_u_y:[-7.7320928076e-05,7.73209380717e-05] p13_u_z:[-0.00225017870922,0.00225017870922] p13_v_x:[-0,0] p13_v_y:[-0.999411890787,-0.99941014523] p13_v_z:[0.0342909996263,0.034341858967] p14_u_x:[0.48790679906,0.511901626579] p14_u_y:[-0.0299793011898,-0.0294574800918] p14_u_z:[-0.872451830568,-0.858606550656] p14_v_x:[-0,0] p14_v_y:[-0.999411890787,-0.99941014523] p14_v_z:[0.0342909996263,0.034341858967] p22_u_x:[-4.41185871138e-05,0.00109350182303] p22_u_y:[0.301924933011,0.313496848733] p22_u_z:[0.949582528028,0.953348513935] p22_v_x:[-0,0] p22_v_y:[-0.953355364302,-0.949574944988] p22_v_z:[0.301909482393,0.313527801583] p23_u_x:[0.999937323658,1] p23_u_y:[-1.05344041179e-11,0.00339513890593] p23_u_z:[-0,0.0104400464366] p23_v_x:[-0,0] p23_v_y:[-0.953355364302,-0.949574944988] p23_v_z:[0.301909482393,0.313527801583] p24_u_x:[0.999999989442,1] p24_u_y:[-1.05344041179e-11,4.5656170506e-05] p24_u_z:[-0,0.000137845607833] p24_v_x:[-0,0] p24_v_y:[-0.953355364302,-0.949574944988] p24_v_z:[0.301909482393,0.313527801583] p32_u_x:[0.367009124706,0.373229472278] p32_u_y:[0.298285868386,0.313593790907] p32_u_z:[0.874572310257,0.881139188828] p32_v_x:[-0,0] p32_v_y:[-0.947246997882,-0.94145037569] p32_v_z:[0.320604345992,0.337159272492] p33_u_x:[0.508611232741,0.540114230288] p33_u_y:[0.274967134437,0.290343191322] p33_u_z:[0.79346904012,0.815729720595] p33_v_x:[-0,0] p33_v_y:[-0.947246997882,-0.94145037569] p33_v_z:[0.320604345992,0.337159272492] p34_u_x:[0.639531936987,0.69494946251] p34_u_y:[0.235423598075,0.259528252451] p34_u_z:[0.677846561695,0.729117518125] p34_v_x:[-0,0] p34_v_y:[-0.947246997882,-0.94145037569] p34_v_z:[0.320604345992,0.337159272492] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.902749984653,-0.894965995912] p40_v_y:[0.430240788518,0.446135840085] p40_v_z:[-0,0] p42_u_x:[-0,3.90183321495e-07] p42_u_y:[-4.19566703569e-09,3.10079130981e-07] p42_u_z:[0.999999999984,1] p42_v_x:[-0.902782973708,-0.894936983171] p42_v_y:[0.430170553437,0.446207585292] p42_v_z:[-0,1.79425014419e-09] p43_u_x:[-3.26699574342e-08,0] p43_u_y:[-0,2.32543533345e-11] p43_u_z:[0.999999999985,1] p43_v_x:[-0.902782973708,-0.894936983171] p43_v_y:[0.430170553437,0.446207585292] p43_v_z:[-0,1.79425014419e-09] p44_u_x:[-0,5.72144461229e-10] p44_u_y:[-0,2.74941522303e-10] p44_u_z:[0.999999998515,1] p44_v_x:[-0.902782973708,-0.894936983171] p44_v_y:[0.430170553437,0.446207585292] p44_v_z:[-0,1.79425014419e-09] object_u_x:[-2.76053943594e-13,9.53800624672e-11] object_u_y:[0.428968396185,0.43588989437] object_u_z:[0.9,0.903324079135] object_v_x:[-0,9.5409430431e-11] object_v_y:[0.899999999562,0.903319814674] object_v_z:[-0.435889895233,-0.428980174553] X_2_u_x:[0.999999999985,1] X_2_u_y:[-0,7.16605073418e-11] X_2_u_z:[-1.0611907945e-11,3.11814591729e-11] X_2_v_x:[-0,3.99606702823e-11] X_2_v_y:[0.326955528824,0.334234068093] X_2_v_z:[-0.945039725195,-0.942497073946] X_3_u_x:[-0,0.064300348866] X_3_u_y:[-0.695449104434,-0.685080758917] X_3_u_z:[0.716418045382,0.728481449128] X_3_v_x:[-0.998915447281,-0.996095200385] X_3_v_y:[-0,0.0446755057037] X_3_v_z:[0.0377225114328,0.0882635595124] X_4_u_x:[0.999999999985,1] X_4_u_y:[-0,1.66324767379e-11] X_4_u_z:[-2.06005118709e-11,0] X_4_v_x:[-1.80877531059e-11,0] X_4_v_y:[0.471950739077,0.478693361438] X_4_v_z:[0.877982155692,0.881632209778] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411890787,-0.99941014523] uni_v_palm_p12_z_0:[0.0342909996263,0.034341858967] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.86664891513e-05,3.63420859742e-05] w2_palm_p12_z_0:[-0.00112374737124,0.00105606219937] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[1,1] w1_p12_p13_y_1:[-3.86664891513e-05,3.63420859742e-05] w1_p12_p13_z_1:[-0.00112374737124,0.00105606219937] w2_p12_p13_x_1:[0.99999746834,1] w2_p12_p13_y_1:[-7.7320928076e-05,7.73209380717e-05] w2_p12_p13_z_1:[-0.00225017870922,0.00225017870922] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[0.498048868684,0.50194986548] w1_p13_p14_y_2:[-0.0297795827716,-0.0296581411464] w1_p13_p14_z_2:[-0.866641175717,-0.864387293934] w2_p13_p14_x_2:[0.48790679906,0.511901626579] w2_p13_p14_y_2:[-0.0299793011898,-0.0294574800918] w2_p13_p14_z_2:[-0.872451830568,-0.858606550656] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.953355364302,-0.949574944988] uni_v_palm_p22_z_3:[0.301909482393,0.313527801583] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.707106781156,0.70775986915] w2_palm_p22_y_3:[0.213273057913,0.221681147432] w2_palm_p22_z_3:[0.670775229875,0.674078018624] cos_0_palm_p22_3:[0.949574944988,0.953355364302] cos_1_palm_p22_3:[0.707106781187,0.70775986915] w1_p22_p23_x_4:[0.707106781156,0.70775986915] w1_p22_p23_y_4:[0.213273057913,0.221681147432] w1_p22_p23_z_4:[0.670775229875,0.674078018624] w2_p22_p23_x_4:[0.999937323658,1] w2_p22_p23_y_4:[-1.05344041179e-11,0.00339513890593] w2_p22_p23_z_4:[-0,0.0104400464366] cos_p22_p23_4:[0.707106781187,0.715176025298] w1_p23_p24_x_5:[0.707106781153,0.714837359471] w1_p23_p24_y_5:[-0.222357087975,-0.211842779405] w1_p23_p24_z_5:[-0.674124043459,-0.664123450813] w2_p23_p24_x_5:[0.999999989442,1] w2_p23_p24_y_5:[-1.05344041179e-11,4.5656170506e-05] w2_p23_p24_z_5:[-0,0.000137845607833] cos_p23_p24_5:[0.707106781187,0.715176025298] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.947246997882,-0.94145037569] uni_v_palm_p32_z_6:[0.320604345992,0.337159272492] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.91709837942,0.919985149133] w2_palm_p32_y_6:[0.12731909958,0.134274510399] w2_palm_p32_z_6:[0.369606690513,0.377254232633] cos_0_palm_p32_6:[0.928893855156,0.935273288768] cos_1_palm_p32_6:[0.91709837942,0.919985149133] w1_p32_p33_x_7:[0.91709837942,0.919985149133] w1_p32_p33_y_7:[0.12731909958,0.134274510399] w1_p32_p33_z_7:[0.369606690513,0.377254232633] w2_p32_p33_x_7:[0.508611232741,0.540114230288] w2_p32_p33_y_7:[0.274967134437,0.290343191322] w2_p32_p33_z_7:[0.79346904012,0.815729720595] cos_p32_p33_7:[0.807395288186,0.830881184662] w1_p33_p34_x_8:[0.968303660849,0.97724572468] w1_p33_p34_y_8:[0.0697661509183,0.0840433248123] w1_p33_p34_z_8:[0.200887973902,0.236066694335] w2_p33_p34_x_8:[0.639531936987,0.69494946251] w2_p33_p34_y_8:[0.235423598075,0.259528252451] w2_p33_p34_z_8:[0.677846561695,0.729117518125] cos_p33_p34_8:[0.807395288186,0.830881184662] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.446135840085,-0.430240788518] w2_palm_p40_y_9:[-0.902749984653,-0.894965995912] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.942540905259,0.94833247281] uni_u_p40_p42_x_10:[-0.36545203839,-0.352431611708] uni_u_p40_p42_y_10:[-0.739487376727,-0.733111124702] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.902782973708,-0.894936983171] uni_v_p40_p42_y_10:[0.430170553437,0.446207585292] uni_v_p40_p42_z_10:[-0,1.79425014419e-09] w1_p40_p42_x_10:[-0.902749984653,-0.894965995912] w1_p40_p42_y_10:[0.430240788518,0.446135840085] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.315516409429,-0.304074737933] w2_p40_p42_y_10:[-0.638363965692,-0.632770098932] w2_p40_p42_z_10:[0.707106512676,0.707106968782] cos_0_p40_p42_10:[0.999838308016,1] cos_1_p40_p42_10:[0.980578578052,0.984855400524] w1_p42_p43_x_11:[-0.315516409429,-0.304074737933] w1_p42_p43_y_11:[-0.638363965692,-0.632770098932] w1_p42_p43_z_11:[0.707106512676,0.707106968782] w2_p42_p43_x_11:[-3.26699574342e-08,0] w2_p42_p43_y_11:[-0,2.32543533345e-11] w2_p42_p43_z_11:[0.999999999985,1] cos_p42_p43_11:[0.707106781187,0.707106781368] w1_p43_p44_x_12:[-0.315597431839,-0.304176514627] w1_p43_p44_y_12:[-0.638363962734,-0.632770318175] w1_p43_p44_z_12:[0.707106780287,0.707106781344] w2_p43_p44_x_12:[-0,5.72144461229e-10] w2_p43_p44_y_12:[-0,2.74941522303e-10] w2_p43_p44_z_12:[0.999999998515,1] cos_p43_p44_12:[0.707106781187,0.707106781368] sph_w1_p24_X_2_x_13:[-0,0] sph_w1_p24_X_2_y_13:[0.949574944988,0.953355364302] sph_w1_p24_X_2_z_13:[-0.313527801583,-0.301909482393] sph_w2_p24_X_2_x_13:[-1.94950473299e-13,6.73334409477e-11] sph_w2_p24_X_2_y_13:[0.9424970741,0.945039725239] sph_w2_p24_X_2_z_13:[0.326955528841,0.334192711105] cos_p24_X_2_13:[0.790950605684,0.802284610187] in_patch_X_2_object_u_14:[-0,0.0146765856416] in_patch_X_2_object_v_14:[0.335641994454,0.365806472739] in_patch_X_2_object_l_14:[428.915319233,428.915319233] sph_w1_p33_X_3_x_15:[0.841407066885,0.861202066128] sph_w1_p33_X_3_y_15:[-0.179949743778,-0.162838142734] sph_w1_p33_X_3_z_15:[-0.510246469124,-0.478781032758] sph_w2_p33_X_3_x_15:[-0.0606240084027,-0.0554734958674] sph_w2_p33_X_3_y_15:[-0.727182441349,-0.719655220237] sph_w2_p33_X_3_z_15:[-0.691680551909,-0.68421340124] cos_p33_X_3_15:[0.398380066798,0.428754648438] in_patch_X_3_object_u_16:[0.459272315412,0.500000000005] in_patch_X_3_object_v_16:[0.333540918678,0.388053420117] in_patch_X_3_object_l_16:[150.093250663,150.391043459] sph_w1_p44_X_4_x_17:[-0.441925208083,-0.425932740628] sph_w1_p44_X_4_y_17:[-0.893921962446,-0.886120539922] sph_w1_p44_X_4_z_17:[0.140021004497,0.14002101214] sph_w2_p44_X_4_x_17:[-0,4.60301778072e-12] sph_w2_p44_X_4_y_17:[-0.881630491649,-0.87798215572] sph_w2_p44_X_4_z_17:[0.471950739155,0.478693361463] cos_p44_X_4_17:[0.844018542318,0.854193231286] in_patch_X_4_object_u_18:[0.563746748152,0.579263179912] in_patch_X_4_object_v_18:[0.312499999997,0.375000000004] in_patch_X_4_object_l_18:[752.793978529,752.793978529] p14_r_x:[59.5378796141,59.6659997542] p14_r_y:[-38.1551821657,-38.1450155614] p14_r_z:[204.006250549,204.215297047] p34_r_x:[35.8415556374,36.7866455642] p34_r_y:[68.6754755329,70.1329379352] p34_r_z:[228.704114019,229.641737509] }
   3 (err:0.865028 min:8.7942 tm:255):{ 257  p12_u_x:[0.499084890323,0.500973447698] p12_u_y:[0.0296775471445,0.0297591934882] p12_u_z:[0.864952147769,0.866044125109] p12_v_x:[-0,0] p12_v_y:[-0.999411890967,-0.999410141914] p12_v_z:[0.034290994383,0.0343419555743] p13_u_x:[0.99999746834,1] p13_u_y:[-7.73211558405e-05,7.73211558405e-05] p13_u_z:[-0.00225017870922,0.00225017870922] p13_v_x:[-0,0] p13_v_y:[-0.999411890967,-0.999410141914] p13_v_z:[0.034290994383,0.0343419555743] p14_u_x:[0.48751805151,0.512267138199] p14_u_y:[-0.0299871430216,-0.0294500031475] p14_u_z:[-0.872677584344,-0.858397108396] p14_v_x:[-0,0] p14_v_y:[-0.999411890967,-0.999410141914] p14_v_z:[0.034290994383,0.0343419555743] p22_u_x:[-9.30661142538e-06,8.54887745585e-05] p22_u_y:[0.317292135745,0.322467886563] p22_u_z:[0.946580398618,0.948328626997] p22_v_x:[-0,0] p22_v_y:[-0.948331442454,-0.946578569628] p22_v_z:[0.317288178038,0.322474710827] p23_u_x:[0.999987779963,1] p23_u_y:[-1.05643839585e-11,0.00158249162865] p23_u_z:[-0,0.0046656743286] p23_v_x:[-0,0] p23_v_y:[-0.948331442454,-0.946578569628] p23_v_z:[0.317288178038,0.322474710827] p24_u_x:[0.999999996845,1] p24_u_y:[-1.05643839585e-11,2.55313039722e-05] p24_u_z:[-0,7.49424063798e-05] p24_v_x:[-0,0] p24_v_y:[-0.948331442454,-0.946578569628] p24_v_z:[0.317288178038,0.322474710827] p32_u_x:[0.367009124706,0.375216265111] p32_u_y:[0.322067458553,0.325264026199] p32_u_z:[0.868431046994,0.872564110503] p32_v_x:[-0,0] p32_v_y:[-0.938072202463,-0.936877205065] p32_v_z:[0.346443499557,0.349658551481] p33_u_x:[0.544495612756,0.566203979103] p33_u_y:[0.288216211455,0.293303746706] p33_u_z:[0.772248233279,0.786452430636] p33_v_x:[-0,0] p33_v_y:[-0.938072202463,-0.936877205065] p33_v_z:[0.346443499557,0.349658551481] p34_u_x:[0.701101454753,0.737308750389] p34_u_y:[0.236141247586,0.249328062827] p34_u_z:[0.632829821245,0.668051096265] p34_v_x:[-0,0] p34_v_y:[-0.938072202463,-0.936877205065] p34_v_z:[0.346443499557,0.349658551481] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.919718829799,-0.913805147604] p40_v_y:[0.39257726325,0.406153050618] p40_v_z:[-0,0] p42_u_x:[-0,4.25257695604e-07] p42_u_y:[-4.59693808312e-09,3.16442547853e-07] p42_u_z:[0.999999999984,1] p42_v_x:[-0.919756465482,-0.913788253523] p42_v_y:[0.392539607139,0.406200813867] p42_v_z:[-0,1.79425014419e-09] p43_u_x:[-3.19946740738e-08,0] p43_u_y:[-0,2.5478385566e-11] p43_u_z:[0.999999999985,1] p43_v_x:[-0.919756465482,-0.913788253523] p43_v_y:[0.392539607139,0.406200813867] p43_v_z:[-0,1.79425014419e-09] p44_u_x:[-0,6.26864010205e-10] p44_u_y:[-0,2.69258520253e-10] p44_u_z:[0.999999998515,1] p44_v_x:[-0.919756465482,-0.913788253523] p44_v_y:[0.392539607139,0.406200813867] p44_v_z:[-0,1.79425014419e-09] object_u_x:[-2.76053943594e-13,9.53800624672e-11] object_u_y:[0.433332774773,0.43588989437] object_u_z:[0.9,0.901235060673] object_v_x:[-0,9.5409430431e-11] object_v_y:[0.899999999539,0.901234103291] object_v_z:[-0.43588989528,-0.433332540998] X_2_u_x:[0.999999999985,1] X_2_u_y:[-0,7.1526154627e-11] X_2_u_z:[-1.05920122075e-11,3.11814591783e-11] X_2_v_x:[-0,3.99606702823e-11] X_2_v_y:[0.326955528768,0.329637226831] X_2_v_z:[-0.945039725215,-0.944107673235] X_3_u_x:[-0,0.0689362671094] X_3_u_y:[-0.68398011226,-0.674467090494] X_3_u_z:[0.727110047775,0.738312654506] X_3_v_x:[-0.998758592709,-0.995596134593] X_3_v_y:[-0,0.047096974993] X_3_v_z:[0.0404534946039,0.0936984524383] X_4_u_x:[0.999999999985,1] X_4_u_y:[-0,1.66324767387e-11] X_4_u_z:[-2.06005118718e-11,0] X_4_v_x:[-1.80877531059e-11,0] X_4_v_y:[0.476198173506,0.478693361509] X_4_v_z:[0.87798215566,0.879337989382] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411890967,-0.999410141914] uni_v_palm_p12_z_0:[0.034290994383,0.0343419555743] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.86662260898e-05,3.63424185342e-05] w2_palm_p12_z_0:[-0.00112374737636,0.00105606219937] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[1,1] w1_p12_p13_y_1:[-3.86662260898e-05,3.63424185342e-05] w1_p12_p13_z_1:[-0.00112374737636,0.00105606219937] w2_p12_p13_x_1:[0.99999746834,1] w2_p12_p13_y_1:[-7.73211558405e-05,7.73211558405e-05] w2_p12_p13_z_1:[-0.00225017870922,0.00225017870922] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[0.498048868675,0.501949865503] w1_p13_p14_y_2:[-0.0297796665503,-0.0296581364966] w1_p13_p14_z_2:[-0.866641175873,-0.864387291063] w2_p13_p14_x_2:[0.48751805151,0.512267138199] w2_p13_p14_y_2:[-0.0299871430216,-0.0294500031475] w2_p13_p14_z_2:[-0.872677584344,-0.858397108396] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.948331442454,-0.946578569628] uni_v_palm_p22_z_3:[0.317288178038,0.322474710827] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.707106781156,0.707154066075] w2_palm_p22_y_3:[0.22433460467,0.228021398278] w2_palm_p22_z_3:[0.669260425272,0.670575667259] cos_0_palm_p22_3:[0.946578569628,0.948331442454] cos_1_palm_p22_3:[0.707106781187,0.707154066075] w1_p22_p23_x_4:[0.707106781156,0.707154066075] w1_p22_p23_y_4:[0.22433460467,0.228021398278] w1_p22_p23_z_4:[0.669260425272,0.670575667259] w2_p22_p23_x_4:[0.999987779963,1] w2_p22_p23_y_4:[-1.05643839585e-11,0.00158249162865] w2_p22_p23_z_4:[-0,0.0046656743286] cos_p22_p23_4:[0.707106781187,0.710587290789] w1_p23_p24_x_5:[0.707106781153,0.710587290919] w1_p23_p24_y_5:[-0.228024054856,-0.223902458927] w1_p23_p24_z_5:[-0.670571594727,-0.666642313213] w2_p23_p24_x_5:[0.999999996845,1] w2_p23_p24_y_5:[-1.05643839585e-11,2.55313039722e-05] w2_p23_p24_z_5:[-0,7.49424063798e-05] cos_p23_p24_5:[0.707106781187,0.710587290789] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.938072202463,-0.936877205065] uni_v_palm_p32_z_6:[0.346443499557,0.349658551481] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.917268802719,0.920771673779] w2_palm_p32_y_6:[0.136413122884,0.139254885239] w2_palm_p32_z_6:[0.365502610347,0.373569373763] cos_0_palm_p32_6:[0.923879532511,0.925187844328] cos_1_palm_p32_6:[0.917268802719,0.920771673779] w1_p32_p33_x_7:[0.917268802719,0.920771673779] w1_p32_p33_y_7:[0.136413122884,0.139254885239] w1_p32_p33_z_7:[0.365502610347,0.373569373763] w2_p32_p33_x_7:[0.544495612756,0.566203979103] w2_p32_p33_y_7:[0.288216211455,0.293303746706] w2_p32_p33_z_7:[0.772248233279,0.786452430636] cos_p32_p33_7:[0.831073413468,0.847789868298] w1_p33_p34_x_8:[0.978095660251,0.983284551317] w1_p33_p34_y_8:[0.0638080065584,0.0727587819703] w1_p33_p34_z_8:[0.170953239214,0.194961348793] w2_p33_p34_x_8:[0.701101454753,0.737308750389] w2_p33_p34_y_8:[0.236141247586,0.249328062827] w2_p33_p34_z_8:[0.632829821245,0.668051096265] cos_p33_p34_8:[0.831073413468,0.847789868298] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.406153050618,-0.39257726325] w2_palm_p40_y_9:[-0.919718829799,-0.913805147604] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.927933466307,0.933358341546] uni_u_p40_p42_x_10:[-0.332700148498,-0.321579546383] uni_u_p40_p42_y_10:[-0.753387401092,-0.748543210109] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.919756465482,-0.913788253523] uni_v_p40_p42_y_10:[0.392539607139,0.406200813867] uni_v_p40_p42_z_10:[-0,1.79425014419e-09] w1_p40_p42_x_10:[-0.919718829799,-0.913805147604] w1_p40_p42_y_10:[0.39257726325,0.406153050618] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.287227350059,-0.277531719275] w2_p40_p42_y_10:[-0.650366037059,-0.646125419316] w2_p40_p42_z_10:[0.707106512676,0.707106968782] cos_0_p40_p42_10:[0.999888437687,1] cos_1_p40_p42_10:[0.98355941805,0.984843874141] w1_p42_p43_x_11:[-0.287227350059,-0.277531719275] w1_p42_p43_y_11:[-0.650366037059,-0.646125419316] w1_p42_p43_z_11:[0.707106512676,0.707106968782] w2_p42_p43_x_11:[-3.19946740738e-08,0] w2_p42_p43_y_11:[-0,2.5478385566e-11] w2_p42_p43_z_11:[0.999999999985,1] cos_p42_p43_11:[0.707106781187,0.707106781368] w1_p43_p44_x_12:[-0.287265846112,-0.277567417319] w1_p43_p44_y_12:[-0.650366033783,-0.646145870528] w1_p43_p44_z_12:[0.707106780287,0.707106781344] w2_p43_p44_x_12:[-0,6.26864010205e-10] w2_p43_p44_y_12:[-0,2.69258520253e-10] w2_p43_p44_z_12:[0.999999998515,1] cos_p43_p44_12:[0.707106781187,0.707106781368] sph_w1_p24_X_2_x_13:[-0,0] sph_w1_p24_X_2_y_13:[0.946578569628,0.948331442454] sph_w1_p24_X_2_z_13:[-0.322474710827,-0.317288178038] sph_w2_p24_X_2_x_13:[-1.94950473299e-13,6.73334409477e-11] sph_w2_p24_X_2_y_13:[0.944107673131,0.945039725273] sph_w2_p24_X_2_z_13:[0.326955528808,0.329637226447] cos_p24_X_2_13:[0.788284344046,0.792477885999] in_patch_X_2_object_u_14:[-0,0.00669882799506] in_patch_X_2_object_v_14:[0.253209333119,0.324375682229] in_patch_X_2_object_l_14:[428.915319233,428.915319233] sph_w1_p33_X_3_x_15:[0.824270314133,0.838830225636] sph_w1_p33_X_3_y_15:[-0.197978063174,-0.189013504137] sph_w1_p33_X_3_z_15:[-0.530492117888,-0.510117055774] sph_w2_p33_X_3_x_15:[-0.0635938398609,-0.0603629469622] sph_w2_p33_X_3_y_15:[-0.736764245726,-0.730714471943] sph_w2_p33_X_3_z_15:[-0.679892756225,-0.67345176806] cos_p33_X_3_15:[0.433108573401,0.452948302844] in_patch_X_3_object_u_16:[0.499999999995,0.524921466254] in_patch_X_3_object_v_16:[0.541533122896,0.640129834258] in_patch_X_3_object_l_16:[150.240733434,150.51976758] sph_w1_p44_X_4_x_17:[-0.402199140194,-0.38862294715] sph_w1_p44_X_4_y_17:[-0.910695516447,-0.904757773439] sph_w1_p44_X_4_z_17:[0.140021004497,0.14002101214] sph_w2_p44_X_4_x_17:[-0,4.60301778072e-12] sph_w2_p44_X_4_y_17:[-0.879337879597,-0.877982155697] sph_w2_p44_X_4_z_17:[0.476198322281,0.478693361509] cos_p44_X_4_17:[0.861387140565,0.866641612412] in_patch_X_4_object_u_18:[0.580266041637,0.586595997995] in_patch_X_4_object_v_18:[0.499999999995,0.551681979644] in_patch_X_4_object_l_18:[752.793978529,752.793978529] p14_r_x:[59.5378796141,59.6659997542] p14_r_y:[-38.1551819387,-38.1450070461] p14_r_z:[204.006250256,204.215297047] p34_r_x:[36.9180870342,37.5865923183] p34_r_y:[70.7122857648,71.0170133783] p34_r_z:[227.685974402,228.174827701] }
   4 (err:1.70559 min:8.84741 tm:256):{ 257  p12_u_x:[0.499084890323,0.500973447698] p12_u_y:[0.0296775631998,0.0297587573544] p12_u_z:[0.864952162751,0.866044125109] p12_v_x:[-0,0] p12_v_y:[-0.999411890114,-0.999410157524] p12_v_z:[0.034291019234,0.0343415007442] p13_u_x:[0.99999746834,1] p13_u_y:[-7.73201305783e-05,7.73201305783e-05] p13_u_z:[-0.00225017870922,0.00225017870922] p13_v_x:[-0,0] p13_v_y:[-0.999411890114,-0.999410157524] p13_v_z:[0.034291019234,0.0343415007442] p14_u_x:[0.487807700398,0.512067827158] p14_u_y:[-0.0299809432556,-0.029455597904] p14_u_z:[-0.872508729915,-0.858493884774] p14_v_x:[-0,0] p14_v_y:[-0.999411890114,-0.999410157524] p14_v_z:[0.034291019234,0.0343415007442] p22_u_x:[-0.000135551706024,0.000867906912569] p22_u_y:[0.332728984598,0.333982573852] p22_u_z:[0.942578970129,0.943022493281] p22_v_x:[-0,0] p22_v_y:[-0.943037697228,-0.942574701559] p22_v_z:[0.332685890341,0.333995407088] p23_u_x:[0.999999764273,1] p23_u_y:[-1.06092386986e-11,0.00022932237025] p23_u_z:[-0,0.000647174931488] p23_v_x:[-0,0] p23_v_y:[-0.943037697228,-0.942574701559] p23_v_z:[0.332685890341,0.333995407088] p24_u_x:[0.999999996211,1] p24_u_y:[-1.06092386986e-11,2.90169116059e-05] p24_u_z:[-0,8.18891404392e-05] p24_v_x:[-0,0] p24_v_y:[-0.943037697228,-0.942574701559] p24_v_z:[0.332685890341,0.333995407088] p32_u_x:[0.308823344657,0.311111147436] p32_u_y:[0.331897367901,0.332614853062] p32_u_z:[0.890384605911,0.89123349178] p32_v_x:[-0,0] p32_v_y:[-0.937104576383,-0.936877205458] p32_v_z:[0.34904872575,0.34965855043] p33_u_x:[0.627422079961,0.630060205228] p33_u_y:[0.271509401937,0.272272565441] p33_u_z:[0.727531881557,0.72981105654] p33_v_x:[-0,0] p33_v_y:[-0.937104576383,-0.936877205458] p33_v_z:[0.34904872575,0.34965855043] p34_u_x:[0.864028603678,0.86712799081] p34_u_y:[0.173915656061,0.1760330516] p34_u_z:[0.466644788721,0.471664008327] p34_v_x:[-0,0] p34_v_y:[-0.937104576383,-0.936877205458] p34_v_z:[0.34904872575,0.34965855043] p40_u_x:[-0,0] p40_u_y:[-0,0] p40_u_z:[1,1] p40_v_x:[-0.935424317868,-0.934383874529] p40_v_y:[0.353527008227,0.356267841609] p40_v_z:[-0,0] p42_u_x:[-0,2.73001348424e-07] p42_u_y:[-4.6791439504e-09,3.20390009644e-09] p42_u_z:[0.99999999997,1] p42_v_x:[-0.935424978407,-0.934383364445] p42_v_y:[0.353525672292,0.356269558877] p42_v_z:[-0,1.64419558387e-09] p43_u_x:[-3.12884955471e-08,0] p43_u_y:[-0,2.82865218359e-11] p43_u_z:[0.999999999985,1] p43_v_x:[-0.935424978407,-0.934383364445] p43_v_y:[0.353525672292,0.356269558877] p43_v_z:[-0,1.64419558387e-09] p44_u_x:[-0,1.80403612973e-09] p44_u_y:[-0,6.8255978506e-10] p44_u_z:[0.999999999352,1] p44_v_x:[-0.935424978407,-0.934383364445] p44_v_y:[0.353525672292,0.356269558877] p44_v_z:[-0,1.64419558387e-09] object_u_x:[-2.76053943594e-13,9.53800624672e-11] object_u_y:[0.43550882649,0.43588989437] object_u_z:[0.9,0.900184460026] object_v_x:[-0,9.5409430431e-11] object_v_y:[0.89999999974,0.900184457487] object_v_z:[-0.435889894865,-0.435508831738] X_2_u_x:[0.999999999985,1] X_2_u_y:[-0,7.14660857785e-11] X_2_u_z:[-1.05831168603e-11,3.11814591481e-11] X_2_v_x:[-0,3.99606702823e-11] X_2_v_y:[0.326955529085,0.327355602128] X_2_v_z:[-0.945039725105,-0.944901216916] X_3_u_x:[-0,0.0574292001133] X_3_u_y:[-0.682544672966,-0.679695495973] X_3_u_z:[0.729117494014,0.733494398592] X_3_v_x:[-0.999022158291,-0.996930066165] X_3_v_y:[-0,0.0392232855426] X_3_v_z:[0.035707520753,0.0782857471743] X_4_u_x:[0.999999999985,1] X_4_u_y:[-0,1.66324767346e-11] X_4_u_z:[-2.06005118668e-11,0] X_4_v_x:[-1.80877531059e-11,0] X_4_v_y:[0.478321612924,0.478693361112] X_4_v_z:[0.87798215587,0.878184737156] uni_u_palm_p12_x_0:[1,1] uni_u_palm_p12_y_0:[-0,0] uni_u_palm_p12_z_0:[-0,0] uni_v_palm_p12_x_0:[-0,0] uni_v_palm_p12_y_0:[-0.999411890114,-0.999410157524] uni_v_palm_p12_z_0:[0.034291019234,0.0343415007442] w1_palm_p12_x_0:[-0,0] w1_palm_p12_y_0:[-0.999411545741,-0.999411545741] w1_palm_p12_z_0:[0.0343010530517,0.0343010530517] w2_palm_p12_x_0:[1,1] w2_palm_p12_y_0:[-3.86654856156e-05,3.63413188955e-05] w2_palm_p12_z_0:[-0.00112374736963,0.00105606219937] cos_0_palm_p12_0:[1,1] cos_1_palm_p12_0:[1,1] w1_p12_p13_x_1:[1,1] w1_p12_p13_y_1:[-3.86654856156e-05,3.63413188955e-05] w1_p12_p13_z_1:[-0.00112374736963,0.00105606219937] w2_p12_p13_x_1:[0.99999746834,1] w2_p12_p13_y_1:[-7.73201305783e-05,7.73201305783e-05] w2_p12_p13_z_1:[-0.00225017870922,0.00225017870922] cos_p12_p13_1:[1,1] w1_p13_p14_x_2:[0.498048868723,0.501949865431] w1_p13_p14_y_2:[-0.0297792721138,-0.0296581584466] w1_p13_p14_z_2:[-0.866641175134,-0.864387304582] w2_p13_p14_x_2:[0.487807700398,0.512067827158] w2_p13_p14_y_2:[-0.0299809432556,-0.029455597904] w2_p13_p14_z_2:[-0.872508729915,-0.858493884774] cos_p13_p14_2:[1,1] uni_u_palm_p22_x_3:[1,1] uni_u_palm_p22_y_3:[-0,0] uni_u_palm_p22_z_3:[-0,0] uni_v_palm_p22_x_3:[-0,0] uni_v_palm_p22_y_3:[-0.943037697228,-0.942574701559] uni_v_palm_p22_z_3:[0.332685890341,0.333995407088] w1_palm_p22_x_3:[-0,0] w1_palm_p22_y_3:[-1,-1] w1_palm_p22_z_3:[-0,0] w2_palm_p22_x_3:[0.707106781156,0.70716126456] w2_palm_p22_y_3:[0.235208253142,0.236173129967] w2_palm_p22_z_3:[0.666169812834,0.666839843203] cos_0_palm_p22_3:[0.942574701559,0.943037697228] cos_1_palm_p22_3:[0.707106781187,0.70716126456] w1_p22_p23_x_4:[0.707106781156,0.70716126456] w1_p22_p23_y_4:[0.235208253142,0.236173129967] w1_p22_p23_z_4:[0.666169812834,0.666839843203] w2_p22_p23_x_4:[0.999999764273,1] w2_p22_p23_y_4:[-1.06092386986e-11,0.00022932237025] w2_p22_p23_z_4:[-0,0.000647174931488] cos_p22_p23_4:[0.707106781187,0.707592495] w1_p23_p24_x_5:[0.707106781153,0.707592494958] w1_p23_p24_y_5:[-0.236170417245,-0.235082238211] w1_p23_p24_z_5:[-0.666828350625,-0.666043184333] w2_p23_p24_x_5:[0.999999996211,1] w2_p23_p24_y_5:[-1.06092386986e-11,2.90169116059e-05] w2_p23_p24_z_5:[-0,8.18891404392e-05] cos_p23_p24_5:[0.707106781187,0.707592495] uni_u_palm_p32_x_6:[1,1] uni_u_palm_p32_y_6:[-0,0] uni_u_palm_p32_z_6:[-0,0] uni_v_palm_p32_x_6:[-0,0] uni_v_palm_p32_y_6:[-0.937104576383,-0.936877205458] uni_v_palm_p32_z_6:[0.34904872575,0.34965855043] w1_palm_p32_x_6:[-0,0] w1_palm_p32_y_6:[-0.999370208806,-0.999370208806] w1_palm_p32_z_6:[-0.0354850074141,-0.0354850074141] w2_palm_p32_x_6:[0.890754264806,0.892012349161] w2_palm_p32_y_6:[0.158042413235,0.158928519274] w2_palm_p32_z_6:[0.42349425279,0.425567352179] cos_0_palm_p32_6:[0.923879532511,0.924128399551] cos_1_palm_p32_6:[0.890754264806,0.892012349161] w1_p32_p33_x_7:[0.890754264806,0.892012349161] w1_p32_p33_y_7:[0.158042413235,0.158928519274] w1_p32_p33_z_7:[0.42349425279,0.425567352179] w2_p32_p33_x_7:[0.627422079961,0.630060205228] w2_p32_p33_y_7:[0.271509401937,0.272272565441] w2_p32_p33_z_7:[0.727531881557,0.72981105654] cos_p32_p33_7:[0.911836870858,0.914039310745] w1_p33_p34_x_8:[0.994146209636,0.994647304242] w1_p33_p34_y_8:[0.0362144267612,0.0373982204007] w1_p33_p34_z_8:[0.0970380609094,0.100022114587] w2_p33_p34_x_8:[0.864028603678,0.86712799081] w2_p33_p34_y_8:[0.173915656061,0.1760330516] w2_p33_p34_z_8:[0.466644788721,0.471664008327] cos_p33_p34_8:[0.911836870858,0.914039310745] w1_palm_p40_x_9:[-0.707106781187,-0.707106781187] w1_palm_p40_y_9:[-0.707106781187,-0.707106781187] w1_palm_p40_z_9:[-0,0] w2_palm_p40_x_9:[-0.356267841609,-0.353527008227] w2_palm_p40_y_9:[-0.935424317868,-0.934383874529] w2_palm_p40_z_9:[-0,0] cos_palm_p40_9:[0.911426223267,0.912628580636] uni_u_p40_p42_x_10:[-0.291836694636,-0.289591541799] uni_u_p40_p42_y_10:[-0.766252546891,-0.765400268042] uni_u_p40_p42_z_10:[0.573579788091,0.573579788091] uni_v_p40_p42_x_10:[-0.935424978407,-0.934383364445] uni_v_p40_p42_y_10:[0.353525672292,0.356269558877] uni_v_p40_p42_z_10:[-0,1.64419558387e-09] w1_p40_p42_x_10:[-0.935424317868,-0.934383874529] w1_p40_p42_y_10:[0.353527008227,0.356267841609] w1_p40_p42_z_10:[-0,0] w2_p40_p42_x_10:[-0.251920621059,-0.24997991596] w2_p40_p42_y_10:[-0.661445348858,-0.660708638376] w2_p40_p42_z_10:[0.707106767504,0.707106782072] cos_0_p40_p42_10:[0.999994873755,1] cos_1_p40_p42_10:[0.983680788037,0.984809713267] w1_p42_p43_x_11:[-0.251920621059,-0.24997991596] w1_p42_p43_y_11:[-0.661445348858,-0.660708638376] w1_p42_p43_z_11:[0.707106767504,0.707106782072] w2_p42_p43_x_11:[-3.12884955471e-08,0] w2_p42_p43_y_11:[-0,2.82865218359e-11] w2_p42_p43_z_11:[0.999999999985,1] cos_p42_p43_11:[0.707106781187,0.707106781645] w1_p43_p44_x_12:[-0.251920643183,-0.249980108666] w1_p43_p44_y_12:[-0.661445345549,-0.660708640631] w1_p43_p44_z_12:[0.707106781156,0.707106781621] w2_p43_p44_x_12:[-0,1.80403612973e-09] w2_p43_p44_y_12:[-0,6.8255978506e-10] w2_p43_p44_z_12:[0.999999999352,1] cos_p43_p44_12:[0.707106781187,0.707106781645] sph_w1_p24_X_2_x_13:[-0,0] sph_w1_p24_X_2_y_13:[0.942574701559,0.943037697228] sph_w1_p24_X_2_z_13:[-0.333995407088,-0.332685890341] sph_w2_p24_X_2_x_13:[-1.94950473299e-13,6.73334409477e-11] sph_w2_p24_X_2_y_13:[0.944901216828,0.945039725135] sph_w2_p24_X_2_z_13:[0.326955529101,0.327355593507] cos_p24_X_2_13:[0.78155573894,0.782434594895] in_patch_X_2_object_u_14:[-0,0.00093383298579] in_patch_X_2_object_v_14:[0.153373574598,0.159160249523] in_patch_X_2_object_l_14:[428.915319233,428.915319233] sph_w1_p33_X_3_x_15:[0.776539134926,0.77914855398] sph_w1_p33_X_3_y_15:[-0.220305938041,-0.21900087752] sph_w1_p33_X_3_z_15:[-0.590299339764,-0.587960102449] sph_w2_p33_X_3_x_15:[-0.0532829142605,-0.0526461675628] sph_w2_p33_X_3_y_15:[-0.732317962477,-0.73167598729] sph_w2_p33_X_3_z_15:[-0.679578633207,-0.678885954497] cos_p33_X_3_15:[0.517991338224,0.521144618438] in_patch_X_3_object_u_16:[0.436410928248,0.441341027445] in_patch_X_3_object_v_16:[0.499999999995,0.508465035016] in_patch_X_3_object_l_16:[150.645073223,150.67341112] sph_w1_p44_X_4_x_17:[-0.352759781289,-0.350042517382] sph_w1_p44_X_4_y_17:[-0.926209670777,-0.92517831715] sph_w1_p44_X_4_z_17:[0.140021004614,0.140021025182] sph_w2_p44_X_4_x_17:[-0,4.60301778072e-12] sph_w2_p44_X_4_y_17:[-0.878184737124,-0.877982155898] sph_w2_p44_X_4_z_17:[0.478321612902,0.478693361112] cos_p44_X_4_17:[0.879265021638,0.88041033144] in_patch_X_4_object_u_18:[0.592862155518,0.594037244168] in_patch_X_4_object_v_18:[0.624999999994,0.636719596651] in_patch_X_4_object_l_18:[752.793978529,752.793978529] p14_r_x:[59.5378796141,59.6659997542] p14_r_y:[-38.1551808197,-38.1450366471] p14_r_z:[204.006251272,204.215297047] p34_r_x:[35.4996270307,35.6178211738] p34_r_y:[70.8262837452,70.8844640013] p34_r_z:[227.664813623,227.738097021] }


Cuik executed in 31 (31) child processors
STATITISTICS FOR Cuik:

Volume of the search space: 1.10407e+18
Volume of the solution space: 0
  Volume ratio:  0.00 %
Max solution diagonal: 0.183447
Number of processors: 32
User time in process: 262.000000 seg (4.366667 min)
Box level information:
  N processed boxes :   1739
  Max depth         :     49
  Types of boxes:
    N solution boxes:      4 (0) ( 0.23%)
    N empty boxes   :    145  ( 8.34%)
    N bisected boxes:   1590  (91.43%)
    N lost boxes    :      0  ( 0.00%)
  Box Reductions    :   2161
  N Errors          :      0 


==========================================================================

END OF THE SOLUTION FILE

