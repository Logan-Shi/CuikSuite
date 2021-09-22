% Definition of the files for the simple prism example.
%
% This is the same as defineSimplePrism but here we use
% the form-finding method described in
%       G. Gomez-Estrada, H.-J. Bungartz, and C. Mohrdieck. 
%       Numerical form-finding of tensegrity structures 
%       International Journal of Solids and Structures
%       43(22-23):6855-6868, 2006.
% 
% See function 'formFindingEstrada' more more details about the
% interface with this method.
%
% Besides the output structucture, this function also creates three
% files
%      - SimplePrismEstrada.tens  -> The tensegrity definition.
%      - SimplePrismEstrada.links -> A solution point for the problem.
%      - SimplePrismEstrada.param -> A temptative set of parameters.
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
function T=defineSimplePrismEstrada
  
  % Topology of the struts
  T.bars={[1 2] [3 4] [5 6]};
  
  % Topology of the strings
  T.strings={[1 3] [3 5] [1 5] [2 4] [4 6] [2 6] [1 6] [2 3] [4 5]};
      
  % Complete the definition using Estrada's form-finding method
  T=formFindingEstrada(T);