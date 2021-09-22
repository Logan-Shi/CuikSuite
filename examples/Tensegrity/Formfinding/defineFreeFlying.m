% Definition of the files for the free-flying kite example.
%
% Since we have the coordinates of the tensegrity nodes, we can
% solve the form-finding method analyzing the kernel of the
% transposed rigidity matrix.
%
% Besides the output structucture, this function also creates three
% files
%      - FreeFlying.tens  -> The tensegrity definition.
%      - FreeFlying.links -> A solution point for the problem.
%      - FreeFlying.param -> A temptative set of parameters.
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
function T=defineFreeFlying

  % Parametrization of a X of Snelson
  
  T.planar=true;
  T.freeFlying=true;
  
  % Topology of the struts
  T.bars={[1 2] [3 4]};
    
  % The points
  x1=[0 0 0];
  x2=[1 0 0];
  x3=[0.5 -0.5 0];
  x4=[0.5 +0.5 0];
  
  T.platform.r=[0 0];
    
  % Vector of node coordinates
  T.p=[x1 x2 x3 x4]'; 
  
  % Topology of the strings
  T.strings={ [1 3] [2 3] [1 4] [2 4] };
 
  % Set stiffness coeficients of the strings 
  T.stiffnessString=[1 1 1 1];
  
  % Complete the definition and solve the form-finding
  T=completeTensegrity(T);
  
  
  