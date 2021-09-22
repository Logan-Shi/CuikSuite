function [C] = makec(b)
%
% generates the incidence matrix
%

[ l c ] = size(b);

C = zeros(l, max(max(b)));

for i=1:l
  C(i, b(i,1)) =  1;
  C(i, b(i,2)) = -1;
end;
