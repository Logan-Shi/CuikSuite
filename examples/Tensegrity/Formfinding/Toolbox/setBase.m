% Rotates and translates the tensegrity nodes so that
% the plane defined by three of the nodes is the X-Y plane.
% This is used to elimitate trivial flexes.
%
% Inputs
%     T: The tensegrity structure.
%     n1: Index of the first node.
%     n2: Index of the second node.
%     n3: Index of the third node.
%
% Outputs
%     T: The updated tensegrity structure.
%
function T=setBase(T,n1,n2,n3)

  % Rotate so that points n1,n2,n3 are co-planar.
  % define a ref. system from points n1 n2 n3
  vx=T.p(ndx(n2))-T.p(ndx(n1));
  vx=vx/norm(vx);
  vy=T.p(ndx(n3))-T.p(ndx(n1));
  vy=vy-vy'*vx*vx;
  vy=vy/norm(vy);
  vz=cross(vx,vy);
  
  Tr=[vx vy vz T.p(ndx(n1)); 0 0 0 1];
  iTr=Tr\eye(4);
  for i=1:T.nPoints
    n=iTr*[T.p(ndx(i));1];
    T.p(ndx(i))=n(1:3);
  end
  