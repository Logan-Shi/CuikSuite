function vars=getparamvars(to)
% returns the number of optimization variables for a given problem
% this function returns the number of optimization variables for a given
% problem. This information may be useful to generate the vector of initial
% values for the optimization variables.
%
% num=getnumoptvar(to) return the number of optimization variables.
%
% The tensegrity optimization object must be initialized before calling
% this function.
% 
% See also: tenopt, tenconst

vars=[];
num=0;
tc=to.const;
for i=1:1:tc.num_var
    if strcmp(tc.variables(i).type,'parameter')
        num=num+1;
        vars(num).name=tc.variables(i).name;
    end
end
