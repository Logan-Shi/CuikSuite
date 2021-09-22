function v=subsasgn(v,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of some internal tenvar object 
% atributes. All the object attributes can be modified this way.
%
% See also edge

global error;
switch index(1).type
    case '()'
        if size(index,2)>1
            try
                v(index(1).subs{:})=subsasgn(v(index(1).subs{:}),index(2:size(index,2)),val);
            catch
                rethrow(lasterror);
            end
        else
            if isa(val,'tenvar')
                v(index(1).subs{:})=val;
            else
                error('tenvar - Invalid parameter value');
            end
        end
    case '.'
        switch index(1).subs
            case 'type'
                try
                    v=settype(v,val);
                catch
                    rethrow(lasterror);
                end
            case 'name'
                if ischar(val)
                    v.name=val;
                else
                    error('tenvat - Invalid parameter value');
                end
            case 'value'
                if isnumeric(val)
                    if size(index,2)>1
                        switch index(2).type
                            case '()' 
                                v.value(index(2).subs{:})=val;
                            otherwise
                                error('tenvar - Invalid indexing mode');
                        end
                    else
                        v.value=val;
                    end
                else
                    error('tenvar - Invalid parameter value');
                end
            otherwise
                error('tenvar - Impossible to acces private members');
        end
    case '{}'
        error('tenvar - cell array indexing not supported by variable objects');
end
