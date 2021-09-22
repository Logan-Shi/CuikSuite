function e=subsasgn(e,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of some internal edge object 
% atributes. All the object attributes can be modified this way.
%
% See also edge

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                e(index(1).subs{:})=subsasgn(e(index(1).subs{:}),index(2:size(index,2)),val);
            catch
                rethrow(lasterror);
            end
        else
            if isa(val,'edge')
                e(index(1).subs{:})=val;
            else
                error('edge - Invalid parameter value');
            end
        end
    case '.'
        try
            switch index(1).subs
                case 'name'
                    e=setname(e,val);
                case 'type'
                    e=settype(e,val);
                case 'origin'
                    e=setorigin(e,val);
                case 'end'
                    e=setend(e,val);
            end
        catch
            rethrow(lasterror);
        end
    case '{}'
        error('edge - cell array indexing not supported by node objects');
end
