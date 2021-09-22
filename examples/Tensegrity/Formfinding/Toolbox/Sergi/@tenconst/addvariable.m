function tc=addvariable(tc,var)
% adds a user variable to the tenconst object
% this function adds a new tenvar object to the tenconst object. This
% variables may be used as constants or to define new constraints.
% 
% tc=addvariable(tc,var) returns a modified version of the tensegrity
% constraint object with the new user variable added.
%
% Both the tensegrity constraint object and the tensegrity variable object
% must be initialized before calling this function.
%
% See also tenconst,tenvar

if isa(tc,'tenconst')
    if isa(var,'tenvar');
        try
            tc.num_user_var=tc.num_user_var+1;
            tc.user_variables(tc.num_user_var)=var;
            [tc,num,var]=getvariables(tc);
        catch
            rethrow(lasterror);
        end
    else
        error('tenconst - Invalid variable');
    end
else
    error('tenconst - Invalid tensegrity constraint structure');
end