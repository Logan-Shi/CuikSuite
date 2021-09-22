function to=subsasgn(to,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of some internal tenopt object 
% atributes. All tenopt attributes can be modified this way.
%
% See also tenconst

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                to(index(1).subs{:})=subasgn(tsegrity(to(index(1).subs{:})),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            if isa(val,'tencol')
                to(index(1).subs{:})=val;
            else
                error('tenopt - Invalid parameter value');
            end
        end
    case '.'
        switch index(1).subs
            otherwise
                error('tenopt - Invalid parameter');
        end
    case '{}'
        error('tenopt - cell array indexing not supported by tensegrity objects');
end
