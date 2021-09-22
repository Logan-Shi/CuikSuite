function eenv=subsasgn(eenv,index,val)

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                eenv(index(1).subs{:})=subsasgn(eenv(index(1).subs{:}),index(2:size(index,2)),val);
            catch
                rethrow(lasterror);
            end
        else
            eenv(index(1).subs{:})=val;
        end
    case '.'        
        switch index(1).subs
            case 'radius'
                if isnumeric(val)
                    eenv.radius=val;
                else
                    error('edgeenv - Invalid parameter value');
                end
            otherwise
                try
                    eenv.edgeconst=subsasgn(eenv.edgeconst,index,val);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('edgeenv - Cell array indexing not allowed for edge environment objects');
end