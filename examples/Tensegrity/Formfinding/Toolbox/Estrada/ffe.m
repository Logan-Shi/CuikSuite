function [xyz,t]=ffe(b,t)
%
% 21.12.2006 : changed QR=CU for QR=(CU)'*(CU); now it calculates
% the truncated icosahedron in Matlab 7.3.0.298 (R2006b)
%

if nargin < 2
  xyz = [];
  t   = [];
  help newff;
  return;
end;

% initialisations
t     = diag(diag(t));                  % column vector
proto = sign(t);                        % vector of prototypes +1/-1
tol   = 1e-9;                           % for zero tests
C     = makec(b);                       % the incidence matrix
sigma = 1;                              % iterate till sigma > tol

while sigma > tol
  % from tension coefficients to coordinates
  [U,V] = schur(C'*diag(t)*C);		% basis for coordinates
  N = sum(diag(V)<tol);			% potential nullity
  if N < 4, N=1:4; else N=1:N; end;     % get enough nullspace anyway,
  U = U(:, N);				% i.e. narrow the search space

  [Q,R] = qr((C*U)'*(C*U));             % projections
  n = []; for i=1:size(R,2),            % norm_2
    n(i)=norm(R(:,i)); end;             % n_i >= 0
  [val,ind] = sort(n);                  % sort to discard the 1-vector
  ind = ind(find(val > tol));           % which has n_i=0, or it is hidden

  if length(ind) > 3                    % search through the triplets
    for i=1:length(ind)-2               % is it all right?
      l = C*U(:,ind(i:i+2));            % get tentative coordinates
      if det(l'*l)>tol                  % linearly independent vectors?
        ind = ind(i:end);               % yes -> we're done.
        break;
      end;
    end;
  end;

  % take the coordinates
  x = U(:,ind(1));
  y = U(:,ind(2));
  z = U(:,ind(3));

  % from coordinates to tension coefficients
  A = [ C'*diag(C*x) ; C'*diag(C*y) ; C'*diag(C*z) ];
  [U,V,W] = svd(A,0);

  % select the tension coefficients that better match the prototypes
  for i=0:size(A,2)-1
    t = W(:,(end-i):end) * (W(:,(end-i):end) \ proto);
    if sum(sign(t) - sign(proto) ~= 0) == 0
      break;
    end;
  end;

  sigma = V(end,end);                   % while sigma > tol 
end;

% coordinates, tension coefficients
xyz = [x y z];

return
