function ec=subsasgn(ec,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of internal edgeconst object 
% atributs. All edgeocnst class attributes can be modified in this way.
%
% See also file

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                ec(index(1).subs{:})=subsasgn(ec(index(1).subs{:}),index(2:size(index,2)),val);
            catch
                rethrow(lasterror);
            end
        else
            ec(index(1).subs{:})=val;
        end
    case '.'        
        switch index(1).subs
            case 'stiffness'
                if size(index,2)>1
                    try
                        ec.siffness=subsasgn(ec.stiffness,index(2:size(index,2)),val);
                    catch
                        rethrow(lasterorr);
                    end
                else
                    if isa(val,'tenvar')
                        ec.stiffness=val;
                    else
                        error('edgeconst - Invalid parameter value');
                    end
                end
            case 'rest_length'
                if size(index,2)>1
                    try
                        ec.rest_length=subsasgn(ec.rest_length,index(2:size(index,2)),val);
                    catch
                        rethrow(lasterror);
                    end
                else
                    if isa(val,'tenvar')
                        ec.rest_length=val;
                    else
                        error('edgeconst - Invalid parameter value');
                    end
                end
            case 'length'
                if size(index,2)>1
                    try
                        ec.length=subsasgn(ec.length,index(2:size(index,2)),val);
                    catch
                        rethrow(lasterror);
                    end
                else
                    if isa(val,'tenvar')
                        ec.length=val;
                    else
                        error('edgeconst - Invalid parameter value');
                    end
                end
            otherwise
                try
                    ec.edge=subsasgn(ec.edge,index,val);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('edgeconst - Cell array indexing not allowed for edge constraint objects');
end