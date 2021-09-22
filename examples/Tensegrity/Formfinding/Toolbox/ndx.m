% Index of a sub-vector in a lager vector.
% In a vector that includes 3-d subvectors
% (e.g., vector T.p which includes the 3D position
% of the tensegrity structure), this function
% provides a simple way to get the indices for
% the n-th sub-vector.
%
% Input
%     n: Index of the sub-vector
% Output
%     r: Range for the sub-vector
function r=ndx(n)
  r=(n-1)*3+(1:3);