function out=subsref(nenv,index)

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                out=subsref(nenv(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=nenv(index(1).subs{:});
        end
    case '.'        
        switch index(1).subs
            case 'friction'
                out=nenv.friction;
            otherwise
                try
                    out=subsref(nenv.nodeconst,index);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('nodeenv - Cell array indexing not allowed for node environment objects');
end