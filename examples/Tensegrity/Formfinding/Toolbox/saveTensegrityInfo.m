% Saves the tensegrity information, plots the tensegrity, and
% evaluates the error of the solution obtained with the
% form-finding process.
%
% This is basically a wrap of different functions: testTensegrity, 
% plotTensegrity, saveTensegrity, saveTensegrityParameters, 
% saveTensegrityConfiguration,...
%
function saveTensegrityInfo(T)

  % Just in case some of the basic trivial fields are not given yet
  T=completeTensegrityInfo(T);

  % Validate the solution
  [error,pretension]=testTensegrity(T);
  
  % Plot
  plotTensegrity(T);
  
  % save the tensegrity structure
  saveTensegrity(T);
  
  % save the tensegrity structure
  saveTensegrityParameters(error,pretension,T);
  
  % save the configuration
  saveTensegrityConfiguration(T);
