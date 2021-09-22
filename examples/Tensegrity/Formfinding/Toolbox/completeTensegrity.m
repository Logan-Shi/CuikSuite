% Form-finding method based on analyzing the kernel of
% the transposed rigidity matrix.
%
function T=completeTensegrity(T)

  % ------------------------
  % From here all is defined automatically
  T=completeTensegrityInfo(T);
  
  % Compute the compression/tension
  % In this case we have the coordinates of the nodes, so we can
  % solve finding the kernel of the rigidity matrix.
  T=solveRigidityMatrix(T);
  
  % Save the tensegrity info
  saveTensegrityInfo(T);
  
  
  
