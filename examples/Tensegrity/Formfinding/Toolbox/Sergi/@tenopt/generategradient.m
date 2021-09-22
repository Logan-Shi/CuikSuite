function to=generategradient(to)
% generates the gradient for the optimization function
% this function computes the partial derivative of the optmization function
% with respect to all the optimization variables. 
%
% to=generategradient(to) returns a modified version of the tenopt object
% updated with the gradient of the optimization function. The result is
% stored internally to the object, but can be accessed externally by simple
% field indexing.
%
% The tensegrity optimization object must be initialized before calling
% this function. 
%
% See also: tenopt
if isa(to,'tenopt')
    if ~isempty(to.function)
        tc=to.const;
        num_opt=0;
        for i=1:1:tc.num_var
            if ~strcmp(tc.variables(i).type,'fixed') && ~strcmp(tc.variables(i).type,'parameter')
                num_opt=num_opt+1;
                var(num_opt)=tc.variables(i).var;
            end
        end
        to.gradient=sym(zeros(num_opt,1));
        for i=1:1:num_opt
            to.gradient(i)=diff(to.function,var(i));
        end
    else
        error('tenopt - No optimization function present');
    end
else
    error('tenopt - Invalid tensegrity optimzation structure');
end