function P = projmatrix(A,Q)
%
% function P = projmatrix(A,Q)
%
% Given a matrix A and matrix of weight Q, it gives the projector matrix P,
% such that the quadratic form x'Qx subject to the linear constraint x = Ay  + b
% has its global minimum in ~x~ = P*b.
%
%

% Get the dimensions
[M,N] = size(A);

% First, calculate the Q-weighted pseudoinverse of A

AQpinv = inv((A'*Q*A))*A'*Q;

% And then, calculate the projector matrix as

P = eye(M) - A*AQpinv;
