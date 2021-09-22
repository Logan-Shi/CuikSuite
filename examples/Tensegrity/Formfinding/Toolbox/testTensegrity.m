% Evaluates the solution of the form-finding procedure
% The main test is the equilibrium in all the selected nodes.
%
% Inputs:
%    T: The tensegrity structure to evaluate.
%
% Outputs:
%     error: Error of the point obtained with the form-finding 
%            procedure.
%     pretension: Norm of the vector of compressions and tensions.
%
function [error,pretension]=testTensegrity(T)
  % This completes the definition, Now we verify that all nodes are in
  % equilibrium
  f=zeros(1,T.nPoints);
  for i=1:T.nPoints
    v=forceInNode(i,T);
    f(i)=norm(v);
  end
  ee=norm(f);
  fprintf('Error in equilibrium     : %g\n',ee);
  
  % Gamma and Lambda (stiffness constants for bars and cables) must be
  % possitive
  eg=norm(T.stiffnessString(T.stiffnessString<0));
  fprintf('Error in string stiffness: %g\n',eg);
  el=norm(T.stiffnessBar(T.stiffnessBar<0));
  fprintf('Error in bar stiffness   : %g\n',el);
  
  if isfield(T,'restBar')
    ec=norm(T.compression+T.stiffnessBar.*(T.lengthBar-T.restBar));
  else
    ec=norm(T.compression-T.stiffnessBar.*T.lengthBar);
  end
  fprintf('Error in compression     : %g\n',ec);
  
  if isfield(T,'restString')
    et=norm(T.tension-T.stiffnessString.*(T.lengthString-T.restString));
  else
    et=norm(T.tension-T.stiffnessString.*T.lengthString);
  end
  fprintf('Error in tension         : %g\n',et);
  
  error=sum([ee,eg,el,ec,et]);
  
  pretension=norm([T.tension T.compression]);
  fprintf('Pretension               : %g\n',pretension);
