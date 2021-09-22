function T=ffw(T)

  %---------------------------------------------------------------------------------
  % Now we compute the configuration from the bar vectors using the
  % procedure described in
  %   Equilibrium conditions of Class 1 Tensegrity Structures
  %     by D. Williamson, R. E. Skelton, J. Han
  %     Revue francaise de genie civil. 2003
  
  % This is our own (experimental) implementation and it has been only
  % tested with the prims1 example. It may fail in other examles. 
  % Use at your own risk.
  
  % Name of teh problem
  I=dbstack();
  T.name=I(end).name(7:end);

  % The fields below are automatically defined
  T.nBars=size(T.p,1)/6;
  T.nPoints=2*T.nBars;
  T.nStrings=size(T.strings,2);
  b=zeros(3*T.nBars,1);
  % Topology of the bars: The bars are defined in between consecutive points
  for i=1:T.nBars
    n1=2*i-1;
    n2=2*i;
    T.bars{i}=[n1 n2];
    b(ndx(i))=T.p(ndx(n2))-T.p(ndx(n1));
  end
  
  % for bars, posstive if the bar vector enter the node and
  % negative otherwise
  B=zeros(3*T.nPoints,3*T.nBars); % 3*nPoints x 3*nBars
  for i=1:T.nBars
    % Bar from(-) node T.bars{i}(1) to(+) T.bars{i}(2)
    B((T.bars{i}(1)-1)*3+(1:3),(i-1)*3+(1:3))=-eye(3);
    B((T.bars{i}(2)-1)*3+(1:3),(i-1)*3+(1:3))=+eye(3);
  end
  
  % for strings, possitive if the string leaves the node and
  % positive otherwise
  S=zeros(3*T.nPoints,3*T.nStrings); % 3*nPoints x 3*nStrings
  for i=1:T.nStrings
    % String from(+) node T.strings{i}(1) to(-) node T.strings{i}(2)
    S((T.strings{i}(1)-1)*3+(1:3),(i-1)*3+(1:3))=+eye(3);
    S((T.strings{i}(2)-1)*3+(1:3),(i-1)*3+(1:3))=-eye(3);
  end
  
  P1=B'.*(B'<0); % 3*nBars x 3*nPoints
  
  P2=abs(B'); % 3*nBars x 3*nPoints
  
  P=[P1' P2']; % 3*nPoints x 3*2*nBars = 3*nPoints x 3*nPoints
  % Here we can test that T.B'*P=[I 0]
  
  S1=P1*S; % 3*nBars x 3*nStrings
  S2=P2*S; % 3*nBars x 3*nStrings
  
  [U,D,V]=svd(S2); % U -> 3*nBars x 3*nBars
  % D -> 3*nBars x 3*nStrings
  % V -> 3*nSrings x 3*nStrings
  
  r=rank(D);
  nsr=3*T.nStrings-r;
  nbr=3*T.nBars-r;
  
  U1=U(:,1:r); % 3*nBars x r
  U2=U(:,(r+1):end); % 3*nBars x (3*nBars-r) = 3*nBars x nbr
  
  Sigma=D(1:r,1:r); % r x r
  iSigma=Sigma\eye(r); % r x r
  
  V1=V(:,1:r); % 3*nStrings x r
  V2=V(:,(r+1):end); % 3*nStrings x (3*nStrings-r) = 3*nBars x nsr
  
  Gamma=diag(kron(T.stiffnessString,[1 1 1])); % 3*nStrings x 3*nStrings
  iGamma=Gamma\eye(3*T.nStrings); % 3*nStrings x 3*nStrings
  
  M=V2'*iGamma*V2; % nsr x nsr
  iM=M\eye(nsr); % nsr x nsr
  
  S1V2=S1*V2;
  
  Lambda=S1V2*iM*S1V2'; % 3*nBars x 3*nBars
  if size(find(abs(Lambda)>1e-6),1)~=3*T.nBars
    warning('No equilibrium is possible with the given input tensile coefficients');
  end
  
  T.stiffnessBar=diag(Lambda)'; % nBars
  T.stiffnessBar=T.stiffnessBar(1:3:3*T.nBars);
      
  R=iGamma*V2*iM*V2'-eye(3*T.nStrings); % 3*nStrings x 3*nStrings
  L=U1*iSigma*V1'*R*S1'; % 3*nBars x 3*nBars
  Q=[eye(3*T.nBars) zeros(3*T.nBars,nbr);L U2]; % 3*2*nBars x (3*nBars+nbr) = 3*nPoints x (3*nBars+nbr)
  A=P*Q; % 3*nPoints x (3*nBars+nbr) (not in the paper but useful)
  
  
  % Now that everything is pre-computed we can generate the configuration
  % from the bar vectors.
  T.p=A*[b ; zeros(size(A,2)-3*T.nBars,1)]; % 3*nPoints 
  % The zeros above can be replaced by rand. This typically produces a
  % global translation of the structure that we cancel below. 
  % So, we use zeros instead.
  
  % Rotate/Translate the structure
  T=setBase(T,T.bars{1}(1),T.bars{2}(1),T.bars{3}(1));
  
  %%%
  % Complete some information with the final node coordinates
  
  % Length of bars
  T.lengthBar=zeros(1,T.nBars);
  for i=1:T.nBars
    n1=T.bars{i}(1);
    n2=T.bars{i}(2);
    T.lengthBar(i)=norm(T.p(ndx(n1))-T.p(ndx(n2)));
  end
  
  % Length of the strings varies
  T.lengthString=zeros(1,T.nStrings);
  for i=1:T.nStrings
    n1=T.strings{i}(1);
    n2=T.strings{i}(2);
    T.lengthString(i)=norm(T.p(ndx(n1))-T.p(ndx(n2)));
  end
  
  % Compute tension/compression for bars and strings
  T.compression=T.stiffnessBar.*T.lengthBar;
  T.tension=T.stiffnessString.*T.lengthString;
  
  % normalize the forces
  n=norm([T.compression T.tension]);
  T.compression=T.compression/n;
  T.tension=T.tension/n;
  
  % after the normalization, adjust the stiffness coefficients
  T.stiffnessBar=T.compression./T.lengthBar;
  T.stiffnessString=T.tension./T.lengthString;
  
  