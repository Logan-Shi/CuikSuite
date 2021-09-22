function [to,path]=loadoptparams(to,filename)
% loads the tensegrity optimization parameters
% this function loads form a file the optimization parameters associated to
% a tensegrity structure, which are the parameters of the minimization
% precedure, the name of the c files with the implementation of the
% optimization function, its gradient and the constraint equations, a
% tenconst object.
%
% The equality and inequality constraints as well as the number of
% constraints of each type is not loaded from the file, they have to be
% computed each time they are required. Howerver, once the c files are
% generated, it is not necessary to re-compute the constraints unless the
% constraints themselves change.
%
% loadoptparams(to,filename) retrieves the optimization information from a
% file specified by filename.
%
% The tensegrity optimization object must be initialized before calling
% this function and the filename must be a string terminated by .opt.
%
% See also tenopt, optfile

MinPenaltyTxt='Min. penalty:';
MaxPenaltyTxt='Max. penalty:';
BetaTxt='Beta:';
STxt='S:';
SigmaTxt='Sigma:';
TolTxt='Tolerance:';
PenUpdateTxt='Penalty update function:';
PathTxt='Path:';
ConstraintsTxt='Constraints:';
ConstraintFileTxt='Constraint file:';
GradientFileTxt='Gradient file:';
FunctionFileTxt='Function file:';
try
    to_file=optfile(filename,'r');
    [to.penalty(1),to_file]=readfieldreal(to_file,MinPenaltyTxt);
    [to.penalty(2),to_file]=readfieldreal(to_file,MaxPenaltyTxt);
    [to.beta,to_file]=readfieldreal(to_file,BetaTxt);
    [to.s,to_file]=readfieldreal(to_file,STxt);
    [to.sigma,to_file]=readfieldreal(to_file,SigmaTxt);
    [to.tolerance,to_file]=readfieldreal(to_file,TolTxt);
    [func_name,to_file]=readfieldstring(to_file,PenUpdateTxt);
    to.penalty_update_h=str2func(func_name);
    [path,to_file]=readfieldstring(to_file,PathTxt);
    if (path(end)~='/')
      path=[path '/'];
    end
    [const_file,to_file]=readfieldstring(to_file,ConstraintsTxt);
    to.const=tenconst();
    to.const=loadconstraints(to.const,[path const_file]);
    to=generateconstraints(to);
    [const_file,to_file]=readfieldstring(to_file,ConstraintFileTxt);
    if strcmp(const_file,'none')
        to.const_file=[];
    else
        to.const_file=const_file;
    end
    [grad_file,to_file]=readfieldstring(to_file,GradientFileTxt);
    if strcmp(grad_file,'none')
        to.grad_file=[];
    else
        to.grad_file=grad_file;
    end
    [func_file,to_file]=readfieldstring(to_file,FunctionFileTxt);
    if strcmp(func_file,'none')
        to.func_file=[];
    else
        to.func_file=func_file;
    end
    to_file=close(to_file);
catch
    rethrow(lasterror);
end
