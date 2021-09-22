% Definition of the files for the symmetrial 3D tower example.
%
% This equilibrium manifold can be described in closed form, as
% described in 
%      C. Sultan, M. Corles and R. E. Skelton
%      The pre-estressability problem of tensegrity structures: some
%      analytical results, 
%      International journal of solids and structures, vol 38, 2011
%
% Besides the output structucture, this function also creates three
% files
%      - Tower3D.tens  -> The tensegrity definition.
%      - Tower3D.links -> A solution point for the problem.
%      - Tower3D.param -> A temptative set of parameters.
%
% These files can be directly processed by the CuikSuite tools. You
% can also used them as a starting point to define other tensegrity
% structures.
%
% The function also plots the tensegrity configuration stored in
% the links file.
%
% Inputs:
%       alpha: One of the director angles for the first strut.
%              This value is in degrees an a reasonable value is 60.
%       delta: The other director angle for the first strut.
%              This value is in degrees an a reasonable value is 30.
%       info: [optional] true/false. If false no file is generated,
%             only the structure 'T' is generated.
%             If not given true is assumed (outpu files are generated).
% Outputs:
%       T: The complete tensegrity structure (this can be manipulated with
%          the functions in the Toolbox folder.
%
function T=defineTower3D(alpha,delta,varargin)

  % We model a SVDB struture (section 4) which essentially has the same
  % solutions as a SVD structure (section 3)

  % Driving parameters (set as parameters of the function?)
  % Temptative values 60,30
  
  % get the name of the current structure
  I=dbstack();
  T.name=I(end).name(7:end);
  
  % Convert from degrees to radians
  alpha=alpha*pi/180;
  delta=delta*pi/180;
  
  if nargin>2
    info=varargin{1};
  else
    info=true;
  end
  
  % Structural parameters
  l=0.40;         % Length of struts
  b=0.27;         % size of base/platform
  P=1;            % Pre-tension coeficient 
  
  % Verify that the boundary conditions hold
  if alpha<=pi/6 || alpha>=pi/2
    error('alpha out of domain');
  end
  
  if delta<=0 || delta>=pi/2
    error('delta out of domain');
  end
  
  if l*sin(delta)*abs(cos(alpha+pi/6))>=b/(2*sqrt(3))
    error('Parameters out of domain');
  end
  
  if sin(alpha+pi/6)>=3*l*sin(delta)/(2*b)
    error('Parameters out of domain');
  end
  
  %auxiliary parameter
  a=pi/3;         % interior angle of equilateral triangles (60 deg.)
  
  % derived parameters.
  %    h: parametrization of the distance between the base and the
  %    platoform
  if alpha==pi/3
    h=l*cos(delta)/2;
  else
    u=sin(delta)*cos(alpha+pi/6);
    h=cos(delta)*(l*u+sqrt(b^2/3-3*l^2*u^2)-b/sqrt(3))/(2*u);
  end
  
  % Conversion between the labels in the paper and our node notation
  k2n=containers.Map({'A_11' 'A_21' 'A_31' 'B_11' 'B_21' 'B_31' 'A_12' 'A_22' 'A_32' 'B_12' 'B_22' 'B_32'}, {1,3 5 2 4 6 7 9 11 8 10 12});
  
  % Topology of the struts
  T.nBars=6;
  T.nPoints=2*T.nBars;
  for i=1:T.nBars
    T.bars{i}=[2*i-1 2*i];
  end
  
  % The extremes of the struts can be computed taking into account that
  % the base and the platoform are equilateral triangles with side 'b' with
  % opposite orientation. The struts depart from the vertices of such
  % triangles with the declination and azimuts given by equatoin (12)
  
  % Start of the base struts
  x1=[0 0 0];
  x3=[b*cos(a) b*sin(a) 0];
  x5=[b 0 0];
  
  % End of the base struts
  lxy=l*sin(delta);
  lz=l*cos(delta);
  x2=x1+[lxy*cos(alpha) lxy*sin(alpha) lz];
  x4=x3+[lxy*cos(alpha+4*pi/3) lxy*sin(alpha+4*pi/3) lz];
  x6=x5+[lxy*cos(alpha+2*pi/3) lxy*sin(alpha+2*pi/3) lz];
  
  % end of the platform struts
  x8=[0 b/(2*sin(a)) 2*lz-h];
  x10=[b b/(2*sin(a)) 2*lz-h];
  x12=[b*cos(a) b/(2*sin(a))-b*sin(a) 2*lz-h];
  
  % In this example we have to take into account the pose of the platform
  u=x10-x8;
  u=u/norm(u);
  s=x12-x8;
  s=s/norm(s);
  w=cross(s,u)/sin(pi/3);
  v=cross(w,u);
  
  T.platform.nodes=[8 10 12];
  T.platform.p=[0 0 0 x10-x8 x12-x8];
  T.platform.u=u;
  T.platform.v=v;
  T.platform.w=w;
  T.platform.r=x8;
  
  % start of the platform struts
  x7=x8-[lxy*cos(alpha+2*pi/3) lxy*sin(alpha+2*pi/3) lz];
  x9=x10-[lxy*cos(alpha) lxy*sin(alpha) lz];
  x11=x12-[lxy*cos(alpha+4*pi/3) lxy*sin(alpha+4*pi/3) lz];
  
  % Vector of node coordinates
  T.p=[x1 x2 x3 x4 x5 x6 x7 x8 x9 x10 x11 x12]'; 
  
  % Topology of the strings
  T.strings={ [k2n('A_11') k2n('A_32')]... %1 Diagonal
              [k2n('A_11') k2n('B_31')]... %2 Vertical
              [k2n('A_21') k2n('A_12')]... %3 Diagonal
              [k2n('A_21') k2n('B_11')]... %4 Vertical
              [k2n('A_31') k2n('A_22')]... %5 Diagonal
              [k2n('A_31') k2n('B_21')]... %6 Vertical
              [k2n('A_12') k2n('B_21')]... %7 Saddle
              [k2n('A_12') k2n('B_11')]... %8 Saddle
              [k2n('A_22') k2n('B_31')]... %9 Saddle
              [k2n('A_22') k2n('B_21')]... %10 Saddle
              [k2n('A_32') k2n('B_11')]... %11 Saddle
              [k2n('A_32') k2n('B_31')]... %12 Saddle
              [k2n('A_32') k2n('B_12')]... %13 Vertical
              [k2n('B_11') k2n('B_12')]... %14 Diagonal
              [k2n('A_12') k2n('B_22')]... %15 Vertical
              [k2n('B_21') k2n('B_22')]... %16 Diagonal
              [k2n('A_22') k2n('B_32')]... %17 Vertical
              [k2n('B_31') k2n('B_32')]... %18 Diagonal
              [k2n('A_11') k2n('A_21')]... %19 Base
              [k2n('A_11') k2n('A_31')]... %20 Base
              [k2n('A_21') k2n('A_31')]... %21 Base
              [k2n('B_12') k2n('B_22')]... %22 Platform
              [k2n('B_12') k2n('B_32')]... %23 Platform
              [k2n('B_22') k2n('B_32')] }; %24 Platform
            
  % Some of the strings have fixed length
  T.fixedStrings=[false(1,18) true(1,6)];
  
  % Number of strings
  T.nStrings=size(T.strings,2);
  
  % Length of the different strings. Eqs 13-15
  % Can be computed directly but...          
  S=sqrt(h^2+b^2/3+l^2*sin(delta)^2-2*l*b*sin(delta)*cos(alpha-pi/6)/sqrt(3));
  V=sqrt(b^2+l^2-2*l*b*sin(delta)*sin(alpha+pi/6));
  D=sqrt(h^2+b^2/3+l^2-2*l*b*sin(delta)*sin(alpha)/sqrt(3)-2*l*h*cos(delta));
 
  % Length of the struts
  T.lengthBar=l*ones(1,T.nBars); 
  % length of strings
  T.lengthString=[D V D V D V S S S S S S V D V D V D b b b b b b]; 
  
  % Tension in the different types of strings. Eqs 26-30
  T_d=1;
  if alpha==pi/3
    T_v=V*T_d*(3*l*sin(delta)/(2*b)-1)/D;
  else
    T_v=V*T_d*((l*cos(delta)/h-1)*sin(alpha-pi/6)-cos(alpha))/(D*sqrt(3)*cos(alpha+pi/6));
  end
  if alpha==pi/3
    T_s=T_d;
  else
    T_s=S*T_d*(l*cos(delta)/h-1)/D;
  end
  
  % Tension in the base/platform strings. Eq B.8 (Appendix B)
  if alpha==pi/3
    T_b=T_d*(2*b^2-9*l*b*sin(delta)+9*l^2*sin(delta)^2)/(6*D*b);
  else
    T_b=T_d*(3*l^2*sin(delta)*cos(delta)+6*b*h*cos(alpha-pi/3)-6*l*h*sin(delta)-2*sqrt(3)*b*l*cos(delta)*sin(alpha))/(6*D*sqrt(3)*h*cos(alpha+pi/6));
  end
  
  % Strut compression. Eqs 34-35 (here we fix a sign error in equation 34!)
  if alpha==pi/3
    C=T_d*(3*l^2*sin(delta)/(2*b)-l/2)/D;
  else
    C=T_d*(2*sqrt(3)*h*b*sin(delta)...
             -sqrt(3)*l*b*sin(2*delta)/2 ...
             +6*h^2*cos(delta)*sin(alpha-pi/3)...
             -6*l*h*(cos(delta)^2*sin(alpha-pi/3)+sin(alpha+pi/6)/sqrt(3))...
             +2*sqrt(3)*l^2*cos(delta)*cos(alpha)...
             +6*l^2*cos(delta)^3*sin(alpha-pi/3))/(6*D*h*sin(pi/3-alpha));
  end

  
  % "normalize" tensions. Eqs 25-27
  n=sqrt(6)*norm([T_d T_v T_s T_b C]);
  T_v=P*T_v/n;
  T_d=P*T_d/n;
  T_s=P*T_s/n;
  T_b=P*T_b/n;
  C=P*C/n;
  
  % Tension in form of a vector
  % for now leave the tension of base/platform cables to 0
  T.tension=[T_d T_v T_d T_v T_d T_v T_s T_s T_s T_s T_s T_s T_v T_d T_v T_d T_v T_d T_b T_b T_b T_b T_b T_b];
  
  % Set the compression
  T.compression=C*ones(1,T.nBars);
  
  % Compute 'stiffnessString' as defined in the paper
  E=14e10;  % N/m^2 Young's modulus
  s=2.5e9;  % N/m^2 maximum tendon stress 
  g=4;      % safety margin
  T.stiffnessString=(E*P*g/s)*T.tension;
  
  % Tension = stiffnessString * (length-rest) -> rest= length-Tension/k
  T.restString=(T.stiffnessString.*T.lengthString)./(T.tension+T.stiffnessString);
  
  % Set the 'stiffnessString' as we use it
  T.stiffnessString=T.stiffnessString./T.restString;
  
  % For struts we assime rest=0
  T.stiffnessBar=T.compression./T.lengthBar; 
  
  if (info)
    % Save the tensegrity info
    saveTensegrityInfo(T);
  end
  