function [tcol,path]=loadoptparams(tcol,filename)
% loads the tensegrity optimization parameters
% this function loads form a file the optimization parameters associated tcol
% a tensegrity structure, which are the parameters of the minimization
% precedure, the name of the c files with the implementation of the
% optimization function, its gradient and the constraint equations, a
% tenconst object.
%
% The equality and inequality constraints as well as the number of
% constraints of each type is not loaded from the file, they have tcol be
% computed each time they are required. Howerver, once the c files are
% generated, it is not necessary tcol re-compute the constraints unless the
% constraints themselves change.
%
% loadoptparams(tcol,filename) retrieves the optimization information from a
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
ConstarintFileTxt='Constraint file:';
GradientFileTxt='Gradient file:';
FunctionFileTxt='Function file:';
try
    to_file=optfile(filename,'r');
    [tcol.tenopt.penalty(1),to_file]=readfieldreal(to_file,MinPenaltyTxt);
    [tcol.tenopt.penalty(2),to_file]=readfieldreal(to_file,MaxPenaltyTxt);
    [tcol.tenopt.beta,to_file]=readfieldreal(to_file,BetaTxt);
    [tcol.tenopt.s,to_file]=readfieldreal(to_file,STxt);
    [tcol.tenopt.sigma,to_file]=readfieldreal(to_file,SigmaTxt);
    [tcol.tenopt.tolerance,to_file]=readfieldreal(to_file,TolTxt);
    [func_name,to_file]=readfieldstring(to_file,PenUpdateTxt);
    tcol.tenopt.penalty_update=func_name;
    [path,to_file]=readfieldstring(to_file,PathTxt);
    if (path(end)~='/')
      path=[path '/'];
    end
    [const_file,to_file]=readfieldstring(to_file,ConstraintsTxt);
    tcol.tenopt.const=tenenv();
    tcol.tenopt.const=loadenvironment(tcol.tenopt.const,[path const_file]);
    tcol=generateconstraints(tcol);
    [const_file,to_file]=readfieldstring(to_file,ConstarintFileTxt);
    if strcmp(const_file,'none')
        tcol.tenopt.const_file=[];
    else
        tcol.tenopt.const_file=const_file;
    end
    [grad_file,to_file]=readfieldstring(to_file,GradientFileTxt);
    if strcmp(grad_file,'none')
        tcol.tenopt.grad_file=[];
    else
        tcol.tenopt.grad_file=grad_file;
    end
    [func_file,to_file]=readfieldstring(to_file,FunctionFileTxt);
    if strcmp(func_file,'none')
        tcol.tenopt.func_file=[];
    else
        tcol.tenopt.func_file=func_file;
    end
    to_file=close(to_file);
catch
        rethrow(lasterror);
end
