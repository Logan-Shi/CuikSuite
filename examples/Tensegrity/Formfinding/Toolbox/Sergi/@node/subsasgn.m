function n=subsasgn(n,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of some internal node object 
% atributes. All the object attributes can be modified this way.
%
% See also edge

switch index.type
    case '()'
        if size(index,2)>1
            try
                n(index(1).subs{:})=subasgn(n(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            if isa(val,'node')
                n(index(1).subs{:})=val;
            else
                error('node - Invalid parameter value');
            end
        end
    case '.'
        switch index(1).subs
            case 'name'
                if ischar(val)
                    n.name=val;
                else
                    error('node - Invalid parameter value');
                end
            otherwise
                error('node - Impossible to access member');
        end
    case '{}'
        error('node - cell array indexing not supported by node objects');
end
