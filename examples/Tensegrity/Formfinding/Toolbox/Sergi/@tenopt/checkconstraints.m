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

eval(['value=',to.const_file,'(to.solution,parameters);']);
% comprovar totes les restriccions d'igualtat
for i=1:1:to.num_eq
    if abs(value(i))>10^(-8);
        error('tenopt - Constraint violation');
    end
end
% comprovar totes les restriccions de desigualtat
for j=1:1:to.num_ineq
    i=i+1;    
    if value(i)<-0.0001
        error('tenopt - Constraint violation');
    end
end
