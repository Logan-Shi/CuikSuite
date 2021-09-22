% Basic function of the form-finding method that relies on analyzing
% the kernel of the transposed rigidity matrix.
%
% Input:
%    T: The tensegrity structure.
%
% Outputs
%     T: The updated tensegrity structure.
%
function T=solveRigidityMatrix(T)

  % We have the coordinates of the points. We can use the rigidity
  % matrix. Its kernel is a basis of the valid compression/tensions for the
  % structure.
  G=zeros(2*T.nPoints,(T.nBars+T.nStrings));
  for i=1:T.nBars
    a=T.bars{i}(1);
    b=T.bars{i}(2);
    ra=(a-1)*2+(1:2);
    rb=(b-1)*2+(1:2);
    v=T.p(ndx(b))-T.p(ndx(a));
    G(ra,i)=+v(1:2);
    G(rb,i)=-v(1:2);
  end
  for i=1:T.nStrings
    a=T.strings{i}(1);
    b=T.strings{i}(2);
    ra=(a-1)*2+(1:2);
    rb=(b-1)*2+(1:2);
    v=T.p(ndx(b))-T.p(ndx(a));
    G(ra,T.nBars+i)=+v(1:2);
    G(rb,T.nBars+i)=-v(1:2);
  end
  
  % Solve
  N=null(G);
  point=ones(T.nBars+T.nStrings,1);
  p=N'*point;
  f=N*p;
  T.compression=-f(1:T.nBars)'.*T.lengthBar;
  T.tension=f(T.nBars+(1:T.nStrings))'.*T.lengthString;
  
  if isfield(T,'virtualString') 
    T.tension(T.virtualString)=0;
  end
  
  % Normalize
  n=norm([T.compression T.tension]);
  T.compression=T.compression/n*T.pretension;
  T.tension=T.tension/n*T.pretension;
  
  % Adjust stiffness coeficients
  if isfield(T,'restString')
    T.stiffnessString=T.tension./(T.lengthString-T.restString);
  else
    T.stiffnessString=T.tension./T.lengthString;
  end
  
  if isfield(T,'restBar')
    T.stiffnessBar=T.compression./(T.lengthBar-T.restBar);
  else
    T.stiffnessBar=T.compression./T.lengthBar; 
  end
   