function to=generatefunction(to)
% generates the optimization function 
% this function computes the cost function from the specified cost function
% and the constraints specified by the tenconst object associated to the
% tenopt object. This function must be called before calling the
% generategradient function.
%
% to=generatefunction(to) returns a modified version of the tenopt object
% updated with the optimization function. The result is stored internally 
% to the object, but can be accessed externally by simple field indexing.
%
% The tensegrity optimization object must be initialized before calling
% this function. 
%
% See also: tenopt
try
    to.function=sym('0');
    penalty=tenvar('parameter','penalty',0);
    to.const=addvariable(to.const,penalty);
    % equality constraitns
    for i=1:1:to.num_eq
        to.function=to.function+penalty.var*to.eq_const(i)*to.eq_const(i);
    end
    % inequality constraints
    for i=1:1:to.num_ineq
        to.function=to.function+(1/penalty.var)*(exp(-penalty.var*to.ineq_const(i))-1);
    end
    % cost function
    cost_func=to.const.cost_func(to.const);
    % total optimization function
    to.function=(to.function+cost_func);
catch
    rethrow(lasterror);
end