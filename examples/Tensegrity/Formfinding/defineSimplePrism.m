% Definition of the files for the simple prism example.
%
% Since we have the coordinates of the tensegrity nodes, we can
% solve the form-finding method analyzing the kernel of the
% transposed rigidity matrix.
%
% Besides the output structucture, this function also creates three
% files
%      - SimplePrism.tens  -> The tensegrity definition.
%      - SimplePrism.links -> A solution point for the problem.
%      - SimplePrism.param -> A temptative set of parameters.
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
function T=defineSimplePrism
  
  % Topology of the struts
  T.bars={[1 2] [3 4] [5 6]};
  
  % The points
  x1=[0 0 0];
  x2=[0.965925826289067 0.258819045102519 1];
  
  x3=[0.896575472168053 0 0];
  x4=[0.189468690981504 0.707106781186546 1];

  x5=[0.448287736084027 0.776457135307562 0];
  x6=[0.189468690981504 -0.189468690981508 1];
    
  % Length of the struts (assume that they are all the same)
  T.lengthBar=[norm(x2-x1) norm(x4-x3) norm(x6-x5)];
  
  % Vector of node coordinates
  T.p=[x1 x2 x3 x4 x5 x6]'; 
  
  % Topology of the strings
  T.strings={[1 3] [3 5] [1 5] [2 4] [4 6] [2 6] [1 6] [2 3] [4 5]};
  
  % Set stiffness coeficients of the cables 
  T.stiffnessString=[[1 1 1 1 1 1]*0.175494628703572 [1 1 1]*0.303965613370022];
    
  % Complete the definition
  T=completeTensegrity(T);