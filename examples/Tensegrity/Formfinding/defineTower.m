% Definition of the files for the tower example.
%
% Since we have the coordinates of the tensegrity nodes, we can
% solve the form-finding method analyzing the kernel of the
% transposed rigidity matrix.
%
% This example is taken from
%     Wijdeven, J. v. d., Jagerm, B. d.,
%     Shape change of tensegrity structures: Design and control. 
%     In: American Control Conference. pp. 2522-2527, 2005
%
% Besides the output structucture, this function also creates three
% files
%      - tower.tens  -> The tensegrity definition.
%      - tower.links -> A solution point for the problem.
%      - tower.param -> A temptative set of parameters.
%
% These files can be directly processed by the CuikSuite tools. You
% can also used them as a starting point to define other tensegrity
% structures.
%
% The function also plots the tensegrity configuration stored in
% the links file.
%
% Outputs:
%       T: The complete tensegrity structure (this can be manipulated with
%          the functions in the Toolbox folder.
%
function T=defineTower

  % Parametrization of a planar tensegrity taken from
  %   Shape Change of Tensegrity Structures: Design and Control
  %   by J. van de Wijdeven and B. de Jager
  %   American Control Conference 2005
   
  T.planar=true;
  
  % Topology of the struts
  T.bars={[1 4] [2 3] [5 8] [6 7] [9 12] [10 11]};
  
  % The points
  x1=[0 0 0];
  x2=[0 0.25 0];
  x3=[0.5 0 0];
  x4=[0.5 0.25 0];
  x5=[0.35 0 0];
  x6=[0.35 0.25 0];
  x7=[0.85 0 0];
  x8=[0.85 0.25 0];
  x9=[0.7 0 0];
  x10=[0.7 0.25 0];
  x11=[1.2 0 0];
  x12=[1.2 0.25 0];
  
  % Vector of node coordinates
  T.p=[x1 x2 x3 x4 x5 x6 x7 x8 x9 x10 x11 x12]'; 
  
  % Topology of the strings
  T.strings={ [1 2] [11 12] [1 6] [2 5] [7 12] [8 11]  ...
              [3 10] [4 9] [1 5] [2 6] [5 3] [6 4] ...
              [3 9] [4 10] [9 7] [10 8] [7 11] [8 12] };
 
  % Set 'stiffnesString' for each string
  k_v=2;
  k_p=0.397576169574137;
  k_d1=1;
  k_d2=5;
  k_h1=5;
  k_h2=10;
  k_h3=1;
  
  T.stiffnessString=[k_v k_p k_d1 k_d1 k_d1 k_d1 k_d2 k_d2 k_h1 k_h1 k_h2 k_h2 k_h3 k_h3 k_h2 k_h2 k_h1 k_h1];

  % Complete the definition
  T=completeTensegrity(T);
  