function nc=subsasgn(nc,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of internal nodeconst object 
% atributes. All nodeconst class attributes can be modified in this way.
%
% See also file

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                nc(index(1).subs{:})=subsasgn(nc(index(1).subs{:}),index(2:size(index,2)),val);
            catch
                rethrow(lasterror);
            end
        else
            nc(index(1).subs{:})=val;
        end
    case '.'        
        switch index(1).subs
            case 'position'
                if size(index,2)>1
                    if strcmp(index(2).type,'()') && index(2).subs{:}<4 && index(2).subs{:}>0
                        try
                            nc.position=subsasgn(nc.position,index(2:size(index,2)),val);
                        catch
                            rethrow(lasterror);
                        end
                    else
                        error('nodeconst - Invalid indexing mode');
                    end
                else
                    if isa(val,'tenvar')
                        nc.position=val;
                    else
                        error('nodeconst - Invalid parameter value');
                    end
                end
            case 'forces'
                if size(index,2)>1
                    try
                        nc.forces=subsasgn(nc.forces,index(2:size(index,2)),val);
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=nc.forces;
                end
            otherwise
                try
                    nc.node=subsasgn(nc.node,index,val);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('nodeconst - Cell array indexing not allowed for node constraint objects');
end