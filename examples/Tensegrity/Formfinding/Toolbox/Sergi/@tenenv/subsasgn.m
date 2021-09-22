function te=subsasgn(te,index,val)

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                te(index(1).subs{:})=subasgn(te(index(1).subs{:}),index(2:size(index,2)),val);
            catch
                rethrow(lasterror);
            end
        else
            if isa(val,'tenconst')
                te(index(1).subs{:})=val;
            else
                error('tenconst - Invalid parameter value');
            end
        end
    case '.'
        switch index(1).subs
            otherwise
                te.tenconst=subsasgn(te.tenconst,index,val);
        end
    case '{}'
        error('tenconst - cell array indexing not supported by tensegrity objects');
end
