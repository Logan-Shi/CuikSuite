function out=subsref(eenv,index)

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                out=subsref(eenv(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=eenv(index(1).subs{:});
        end
    case '.'        
        switch index(1).subs
            case 'radius'
                out=eenv.radius;
            otherwise
                try
                    out=subsref(eenv.edgeconst,index);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('edgeenv - Cell array indexing not allowed for edge environment objects');
end