% From finding method by G. Gomez-Estrada et al.
%
% Inputs:
%       T: The partial tensegrity structure. It only need to
%          include the topology. See defineSimplePrismEstrada
%          for an example.
% Outputs:
%       T: The complete tensegrity structure (this can be manipulated with
%          the functions in the Toolbox folder.
%  
function T=formFindingEstrada(T)

  % Form finding method described in
  %    G. Gomez-Estrada, H.-J. Bungartz, and C. Mohrdieck
  %    Numerical form-finding of tensegrity structures
  %    International Journal of Solids and Structures 
  %    43(22-23):6855-6868, 2006.
  %
  % The code is in the 'Estrada' subfolder and ti is taken form here:
  %     https://sites.google.com/site/giovaniestrada


  T=completeTensegrityInfo(T);
  
  % 'b' vector input for the Estrada form-finding
  % First the tension elements and then the compression ones.
  n=T.nStrings+T.nBars;
  b=zeros(n,2);
  
  for i=1:T.nStrings
    b(i,:)=T.strings{i};
  end
  for i=1:T.nBars
    b(T.nStrings+i,:)=T.bars{i};
  end
  
  t=[ones(1,T.nStrings) -ones(1,T.nBars)];
  
  % Call the basic function developed by Estrada et at.
  % This is the call to the original code
  [xyz,q]=ffe(b,t);
  
  x=xyz(:,1); 
  y=xyz(:,2); 
  z=xyz(:,3); 
  T.p=zeros(3*T.nPoints,1);
  for i=1:T.nPoints
    T.p(ndx(i))=[x(i) y(i) z(i)];
  end

  C=makec(b);
  l = sqrt((C*x).^2 + (C*y).^2 + (C*z).^2);
  T.lengthString=l(1:T.nStrings)';
  T.lengthBar=l((T.nStrings+1):end)'; 
  
  % normalize the forces (default pre-tension=1)
  f=q.*l;
  nf=norm(f);
  q=q/nf;
  f=f/nf;
  if isfield(T,'P')
    q=q*T.P; % pretension
    f=f*T.P;
  end
  
  T.tension=f(1:T.nStrings)';
  T.compression=-f((T.nStrings+1):end)';

  T.stiffnessString=q(1:T.nStrings)';
  T.stiffnessBar=-q((T.nStrings+1):end)';
  
  % Rotate/translate so that first nodes of the 3 first bars are
  % in the plane z=0
  T=setBase(T,T.bars{1}(1),T.bars{2}(1),T.bars{3}(1));
  
  % Save the tensegrity info
  saveTensegrityInfo(T);
  
  
  
  
  