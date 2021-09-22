function v=settype(v,type)
% sets the type of the variable
% this function sets the type of an exiting variable, which can be either
% fixed, passive, parameter or actuates. Only fixed variable may have a
% value.
%
% v=settype(v,type) return a modifed version of the variable with the new
% type.
%
% The tenvar object must be initialized before calling this funciton.
%
% See also tenvar

if isa(v,'tenvar')
    if ischar(type)
        if ~strcmp(type,'fixed') && ~strcmp(type,'passive') && ~strcmp(type,'parameter') && ~strcmp(type,'actuated')
            error('tenvar - Invalid variable type');
        else
            v.type=type;
        end
    else
        error('tenvar - Invalid type');
    end
else
    error('tenvar  - Invalid variable structure');
end
