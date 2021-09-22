function tcol=generatefunction(tcol)
% generates the optimization function 
% this function computes the cost function from the specified cost function
% and the constraints specified by the tenconst object associated tcol the
% tenopt object. This function must be called before calling the
% generategradient function.
%
% tcol=generatefunction(tcol) returns a modified version of the tenopt object
% updated with the optimization function. The result is stored internally 
% tcol the object, but can be accessed externally by simple field indexing.
%
% The tensegrity optimization object must be initialized before calling
% this function. 
%
% See also: tenopt
try
    tcol.tenopt=generatefunction(tcol.tenopt);
    penalty=tenvar('parameter','penalty',0);
    % equality constraitns
    for i=1:1:tcol.num_env_eq
        tcol.tenopt.function=tcol.tenopt.function+penalty.var*tcol.env_eq_const(i)*tcol.env_eq_const(i);
    end
    % inequality constraints
    for i=1:1:tcol.num_env_ineq
        tcol.tenopt.function=tcol.tenopt.function+(1/penalty.var)*(exp(-penalty.var*tcol.env_ineq_const(i))-1);
    end
    
catch
    rethrow(lasterror);
end