function saveoptparams(to,filename)
% saves the tensegrity optimization parameters
% this function saves into a file the optimization parameters associated to
% a tensegrity structure, which are the parameters of the minimization
% precedure, the name of the c files with the implementation of the
% optimization function, its gradient and the constraint equations, a
% tenconst object.
%
% The equality and inequality constraints as well as the number of
% constraints of each type is not saved into the file, they have to be
% computed each time they are required. Howerver, once the c files are
% generated, it is not necessary to re-compute the constraints unless the
% constraints themselves change.
%
% saveoptparams(to,filename) saves the optimization information into a file
% specified by filename.
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
ConstraintsTxt='Constraints:';
ConstarintFileTxt='Constarint file:';
GradientFileTxt='Gradient file:';
FunctionFileTxt='Function file:';
try
    to_file=optfile(filename,'w');
    to_file=writefieldreal(to_file,MinPenaltyTxt,to.penalty(1));
    to_file=writefieldreal(to_file,MaxPenaltyTxt,to.penalty(2));
    to_file=writefieldreal(to_file,BetaTxt,to.beta);
    to_file=writefieldreal(to_file,STxt,to.s);
    to_file=writefieldreal(to_file,SigmaTxt,to.sigma);
    to_file=writefieldreal(to_file,TolTxt,to.tolerance);
    func_name=func2str(to.penalty_update_h);
    to_file=writefieldstring(to_file,PenUpdateTxt,func_name);
    to_file=writefieldstring(to_file,ConstraintsTxt,to.const.const_filename);
    if isempty(to.const_file)
        to_file=writefieldstring(to_file,ConstarintFileTxt,'none');
    else
        to_file=writefieldstring(to_file,ConstarintFileTxt,to.const_file);
    end
    if isempty(to.grad_file)
        to_file=writefieldstring(to_file,GradientFileTxt,'none');
    else
        to_file=writefieldstring(to_file,GradientFileTxt,to.grad_file);
    end
    if isempty(to.func_file)
        to_file=writefieldstring(to_file,FunctionFileTxt,'none');
    else
        to_file=writefieldstring(to_file,FunctionFileTxt,to.func_file);
    end
    to_file=close(to_file);
catch
    rethrow(lasterror);
end
