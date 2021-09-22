% Definition of the files for the simple prism example.
%
% This is the same as defineSimplePrism but here we use
% the form-finding method described in
%       D. Williamson, R. E. Skelton, J. Han 
%       Equilibrium conditions of a tensegrity structure 
%       International Journal of Solids and Structures 
%       40 (23), 6347-6367, 2003.
%
% Besides the output structucture, this function also creates three
% files
%      - SimplePrismWilliamson.tens  -> The tensegrity definition.
%      - SimplePrismWilliamson.links -> A solution point for the problem.
%      - SimplePrismWilliamson.param -> A temptative set of parameters.
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
function T=defineSimplePrismWilliamson

  % In this form-finding methods bars indices are pre-defined 
  % (consecutive indices: [1 2] [3 4] [5 6] ...)
  
  % Extremes of the bars. This is NOT an equilibrium configuration.
  % Only used to determine the length of the bars and their director 
  % vectors.
  % These vectors must span R3 !
  x1=[0 0 0];
  x2=[1 0 1];
  
  x3=[1 0 0];
  x4=[0.5 sqrt(0.75) 1];
  
  x5=[0.5 sqrt(0.75) 0];
  x6=[0 0 1];
  
  T.p=[x1 x2 x3 x4 x5 x6]'; 
    
  % Topology of the strings
  T.strings={[1 3] [3 5] [1 5] [2 4] [4 6] [2 6] [1 6] [2 3] [4 5]};
  
  % This from finding method requires the tensile coefficients per string.
  % They may be scaled at the output.
  % This is a strong assumption.
  T.stiffnessString=[1 1 1 1 1 1 sqrt(3) sqrt(3) sqrt(3)]; 
    
  % Call the form-finding solver
  T=ffw(T);
   
  % Save the tensegrity info
  saveTensegrityInfo(T);
  
   
   