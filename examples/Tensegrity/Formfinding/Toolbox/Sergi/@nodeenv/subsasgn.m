function nenv=subsasgn(nenv,index,val)

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                nenv(index(1).subs{:})=subsasgn(nenv(index(1).subs{:}),index(2:size(index,2)),val);
            catch
                rethrow(lasterror);
            end
        else
            nenv(index(1).subs{:})=val;
        end
    case '.'        
        switch index(1).subs
            case 'friction'
                if isnumeric(val)
                    nenv.friction=val;
                else
                    error('nodeenv - Invalid parameter value');
                end
            otherwise
                try
                    nenv.nodeconst=subsasgn(nenv.nodeconst,index,val);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('nodeenv - Cell array indexing not allowed for node environment objects');
end