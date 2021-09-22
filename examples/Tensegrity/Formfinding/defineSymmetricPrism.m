% Definition of the files for the symmetrial prism example.
% This is the prism but with symmetry constraints so that the
% equilibrium manifold in one-dimensional.
%
% This equilibrium manifold can be described in closed form, as
% described in 
%      Cornel Sultan
%      Stiffness formulations and necessary and sufficient
%      conditions for exponential stability of prestressable structures
%      International Journal of Solids and Structures 50 (2013)
%
% Besides the output structucture, this function also creates three
% files
%      - SymmetricPrism.tens  -> The tensegrity definition.
%      - SymmetricPrism.links -> A solution point for the problem.
%      - SymmetricPrism.param -> A temptative set of parameters.
%
% These files can be directly processed by the CuikSuite tools. You
% can also used them as a starting point to define other tensegrity
% structures.
%
% The function also plots the tensegrity configuration stored in
% the links file.
%
% Inputs:
%       alpha: [optional] Director angle of the first strut. The other
%              director angle (delta) is computed from alpha.
%              This value is in degrees and the default value is 5.6.
% Outputs:
%       T: The complete tensegrity structure (this can be manipulated with
%          the functions in the Toolbox folder.
%
function T=defineSymmetricPrism(varargin)

  % Parametrization of a one-prism tower taken from 
  %   Stiffness formulations and necessary and sufficient conditions 
  %   for exponential stability of prestressable structures
  %   by C. Sultan
  %   International Journal of Solids and Structures 50 (2013) 2180?2195

  % get the name of the current structure
  I=dbstack();
  T.name=I.name(7:end);
  
  % Driving parameter 
  % Temptative value:  5.6
  
  % Convert from degrees to radians
  if nargin>0
    alpha=varargin{1}*pi/180;
  else
    alpha=5.6*pi/180;
  end
    
  % Structural parameters
  l=3;         % Length of struts
  b=1;         % size of base/platform
  P=1;         % Pre-tension coeficient 
  
  % delta
  delta = asin(b/(2*sqrt(3)*l*sin(alpha)));
  
  % Verify that the boundary conditions hold
  if alpha<=0 || alpha>=pi/6
    error('alpha out of domain');
  end
  
  %auxiliary parameter
  a=pi/3;         % interior angle of equilateral triangles (60 deg.)
  
  % Conversion between the labels in the paper and our node notation
  k2n=containers.Map({'A_1' 'A_2' 'A_3' 'B_1' 'B_2' 'B_3' }, {1,3 5 2 4 6});
  
  % Topology of the struts
  T.nBars=3;
  T.nPoints=2*T.nBars;
  for i=1:T.nBars
    T.bars{i}=[2*i-1 2*i];
  end
  
  % equilibrium nodes (base nodes should not be considered for
  % equilibrium conditions)
  T.equilibriumNode=[false true false true false true];
  
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
  
  
  % Vector of node coordinates
  T.p=[x1 x2 x3 x4 x5 x6]'; 
  
  % Topology of the strings
  T.strings={ [k2n('A_1') k2n('B_2')]... % Vertical
              [k2n('A_2') k2n('B_3')]... % Vertical
              [k2n('A_3') k2n('B_1')]... % Vertical
              [k2n('B_1') k2n('B_2')]... % Platform
              [k2n('B_2') k2n('B_3')]... % Platform
              [k2n('B_1') k2n('B_3')] }; % Platform
  
  % Number of strings
  T.nStrings=size(T.strings,2);
  
  % Length of the different strings. Eqs 13-15
  % Can be computed directly but...          
  V = sqrt(l^2+b^2-2*l*b*cos(alpha)*sin(delta));
  B = sqrt(3*l^2*sin(delta)^2+b^2-3*l*b*sin(delta)*cos(alpha)-sqrt(3)*l*b*sin(delta)*sin(alpha));

  % Length of the bars
  T.lengthBar=l*ones(1,3); 
  
  % length of strings
  T.lengthString=[V V V B B B]; 
  
  % Tension in the different types of strings. Eqs 26-30
  T_v_0 = (cot(alpha)-sqrt(3))*sqrt(3)/2;
  
  % Compression for bars
  C_0 = l*T_v_0;
  
  % normalizatin factor
  n = sqrt(3*(T_v_0^2*V^2+B^2+C_0^2));
  
  % Tension / compression
  T_v = P*T_v_0*V/n;
  T_b = P*B/n;
  C = P*C_0/n;
  
  % Tension in form of a vector
  % for now leave the tension of base/platform cables to 0
  T.tension=[T_v T_v T_v T_b T_b T_b];
  
  % Set the compression after the test ()
  T.compression=C*ones(1,T.nBars);
  
  % Compute string stiffness as defined in the paper
  T.stiffnessString=[50 50 50 10 10 10];
  
  % Tension = stiffnessString * (length-rest) -> rest= length-Tension/k
  T.restString=(T.stiffnessString.*T.lengthString)./(T.tension+T.stiffnessString);
  
  % Set the 'stiffnessString' as we use it
  T.stiffnessString=T.stiffnessString./T.restString;
  
  % For struts we assime rest=0
  T.stiffnessBar=T.compression./T.lengthBar;  % compression coefficients per bar
  
  % Save the tensegrity info
  saveTensegrityInfo(T);
  