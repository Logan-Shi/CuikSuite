function to=checkconstraints(to,parameters)
% checks the violation of any of the constraints
% this functions checks all the constraint equations associated to a
% tensegrity structure and throws an error if any of the constraints is
% violated. This function can be used after an optimization porcess to
% check the validity of the solution.
%
% to=checkconstraints(to,parameters) throws an error if any of the
% constraints is violated and returns normally otherwise.
%
% The tensegrity optimization object must be initialized before calling
% this funciton and the vector of parameters must be trhe same as the one
% used in the optimization process.
%
% See also: tenopt, tenconst

try
    to.tenopt=checkconstraints(to.tenopt,parameters);
    eval(['value=',to.tenopt.const_file,'(to.tenopt.solution,parameters);']);    
    % comprovar totes les restriccions d'igualtat
    i=to.tenopt.num_eq+to.tenopt.num_ineq;
    for j=1:1:to.num_env_eq
        i=i+1;
        if abs(value(i))>10^(-8);
            error('tenopt - Constraint violation');
        end
    end
    % comprovar totes les restriccions de desigualtat
    for j=1:1:to.num_env_ineq
        i=i+1;    
        if value(i)<-0.00001
            error('tenopt - Constraint violation');
        end
    end
    
catch
    rethrow(lasterror);
end

