% Definition of the files for the robot example.
%
% We use the form-finding method for the Tower3D example and, then,
% replace some of the cables by springs.
%
% Besides the output structucture, this function also creates three
% files
%      - Robot.tens  -> The tensegrity definition.
%      - Robot.links -> A solution point for the problem.
%      - Robot.param -> A temptative set of parameters.
%
% These files can be directly processed by the CuikSuite tools. You
% can also used them as a starting point to define other tensegrity
% structures.
%
% The function also plots the tensegrity configuration stored in
% the links file.
%
% Outputs:
%       T: The complete tensegrity structure (this can be manipulated with
%          the functions in the Toolbox folder.
%
function T=defineRobot

  % Use the symmetrical two level tower as a starting point
  T=defineTower3D(60,30,false);
  
  % Replace the vertical cables by springs. They have smaller stiffness and
  % also smaller rest length (larger displacement). 
  % The result in the same force: f=stiffnessString*(lengthString-restString)
  beta=0.5; % factor to define the rest length w.r.t. length of vertical tendons
  
  % index of the vertical tendons (taken from defineTower3D)
  V=[2 4 6 13 15 17];
  % define the rest length as a fraction of the cable length
  T.restString(V)=beta*T.lengthString(V);
  % recompute stiffness of strings
  T.stiffnessString(V)=T.tension(V)./(T.lengthString(V)-T.restString(V));
  
  % Save the tensegrity info
  saveTensegrityInfo(T);