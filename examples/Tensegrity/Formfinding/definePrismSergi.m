% Definition of the files for the prism example using Sergi's
% form finding method.
%
% The form finding method is described in
%
%         S. Hernandez-Juan and J.M. Mirats-Tur 
%         A method to generate stable, collision free
%         configurations 
%         for tensegrity based robots. 
%         In: IEEE/RSJ International Conference on Intelligent
%             Robots and Systems, pp. 3769-3774, 2008.
%
% See function 'formFindingSergi' for detail about the interface
% with this method.
%
% Besides the output structucture, this function also creates three
% files
%      - PrismSergi.tens  -> The tensegrity definition.
%      - PrismSergi.links -> A solution point for the problem.
%      - PrismSergi.param -> A temptative set of parameters.
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
function T=definePrismSergi

  % main file describing the problem
  filename='Toolbox/Sergi/prisma2_fixed_col_jm.col';

  % Position of the center of mass of the platform (x,y,z)
  params=[0.4,0.4,0.7];

  % solve the form finding
  T=formFindingSergi(filename,params);
  
  % Save the information if CuiksSuite format
  saveTensegrityInfo(T);