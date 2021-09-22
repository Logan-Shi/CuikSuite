% Defines a tempetative file of paramters. This complements the
% .tens and .links files generated with saveTensegrity and
% saveTensegrityConfiguration, respectively.
% 
% Inputs:
%     error: Error of the point obtained with the form-finding 
%            procedure.
%     pretension: Norm of the vector of compressions and tensions.
%     T: The tensegrity
% Outputs
%     A .param file
%
function saveTensegrityParameters(error,pretension,T) 

  fname=[T.name '.param'];
  fprintf('Saving parameters to     : %s\n',fname);
  
  fid=fopen(fname,'w');
  
  fprintf(fid,'%% Automatically generated parameters for problem %s\n\n',T.name);
  
  fprintf(fid,'  REPRESENTATION = FLINKS\n');
  fprintf(fid,'  DUMMIFY = 0\n\n');
  
  if error<1e-8
    fprintf(fid,'  EPSILON = 1e-7\n\n');
  else
    fprintf(fid,'  EPSILON = %g\n\n',10*error);
  end
    
  
  fprintf(fid,'  N_DOF = 0  %% Computed on the fly\n');
  fprintf(fid,'  SR = 0     %% Set to N_DOF\n\n');

  fprintf(fid,'  R = 0.4\n');
  fprintf(fid,'  E = 0.1\n');
  fprintf(fid,'  CE = 0.1\n');
  fprintf(fid,'  DELTA = 0.05\n\n');
  
  fprintf(fid,'  MAX_NEWTON_ITERATIONS = 50\n\n');
  
  if isfield(T,'pretension') && (T.pretension<1e-6) 
    fprintf(fid,'  PRETENSION = 0\n\n');
  else
    fprintf(fid,'  PRETENSION = %g\n\n',pretension);
  end
  
  fclose(fid);
