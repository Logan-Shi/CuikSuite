function v=tenvar(varargin)
% constructor fot the tenvar class
% this function is the constructor for the tenvar class. This class
% encapsulates the information for a generic variable, which is the type of
% the variable (fixed,passive,parameter,actuated), the name of the variable,
% its symbol and its value if necessary.
%
% v=tenvar() returns a new object initialized by default.
%
% v=tenvar(tenvar) if tenvar is an other tenvar object, this function 
% returns a copy of that object
%
% v=tenvar(type,name) builds a new node object with the attributes 
% specified as the parameters to the constructor when the variable type is 
% either passive, parameter or actuated.
%
% v=tenvar(type,name,value) builds a new node object with the attributes 
% specified as the parameters to the constructor when the variable type is 
% fixed.
%
% See also tenvar

switch nargin
    case 0
        v.type='none';
        v.name='none';
        v.var=[];
        v.value=0;
        v=class(v,'tenvar');
    case 1
        if isa(varargin{1},'tenvar')
            v=varargin{1};
        else
            error('tenvar - invalid variable structure');
        end
    case 2
        v=tenvar();
        try
            v=settype(v,varargin{1});
        catch
            rethrow(lasterror);
        end
        if ischar(varargin{2})
            v.name=varargin{2};
            v.var=sym([varargin{2}]);
        else
            error('tenvar - Invalid parameter value');
        end
    case 3
        v=tenvar();
        try
            v=settype(v,varargin{1});
        catch
            rethrow(lasterror);
        end
        if ischar(varargin{2})
            v.name=varargin{2};
            v.var=sym([varargin{2}]);
            if isnumeric(varargin{3})
                v.value=varargin{3};
            else
                error('tenvar - Invalid parameter value');
            end
         else
            error('tenvar - Invalid parameter value');
        end
    otherwise
        error('tenvar - Invalid number of arguments');
end