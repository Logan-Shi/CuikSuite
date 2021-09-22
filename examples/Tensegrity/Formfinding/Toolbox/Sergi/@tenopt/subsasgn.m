function to=subsasgn(to,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of some internal tenopt object 
% atributes. All tenopt attributes can be modified this way.
%
% See also tenconst

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                to(index(1).subs{:})=subasgn(tsegrity(to(index(1).subs{:})),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            if isa(val,'tenopt')
                to(index(1).subs{:})=val;
            else
                error('tenopt - Invalid parameter value');
            end
        end
    case '.'
        switch index(1).subs
            case 'const'
                if size(index,2)>1
                    to.const=subsasg(to.const,index(2:size(index,2)),val);
                else
                    if isa(val,'tenconst')
                        to.const=val;
                    else
                        error('tenopt - Invalid parameter value');
                    end
                end
            case 'penalty'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            to.penalty(index(2).subs{:})=val;
                        otherwise
                            error('tenopt - Invalid indexing mode');
                    end
                else
                    if isnumeric(val) && size(val,2)==2
                        to.penalty=val;
                    else
                        error('tenopt - Invalid parameter value');
                    end
                end
            case 'penalty_update'
                if ischar(val)
                    to.penalty_update_h=str2func(val);
                else
                    error('tenopt - Invalid parameter value');
                end
            case 'beta'
                if isnumeric(val)
                    to.beta=val;
                else
                    error('tenopt - Invalid parameter value');
                end
            case 's'
                if isnumeric(val)
                    to.s=val;
                else
                    error('tenopt - Invalid parameter value');
                end
            case 'sigma'
                if isnumeric(val)
                    to.sigma=val;
                else
                    error('tenopt - Invalid parameter value');
                end
            case 'tolerance'
                if isnumeric(val)
                    to.tolerance=val;
                else
                    error('tenopt - Invalid parameter value');
                end
            case 'function'
                to.function=val;
            case 'gradient'
                to.gradient=val;
            case 'const_file'
                if ischar(val)
                    to.const_file=val;
                else
                    error('tenopt - Invalid Parameter value');
                end
            case 'grad_file'
                if ischar(val)
                    to.grad_file=val;
                else
                    error('tenopt - Invalid Parameter value');
                end
            case 'func_file'
                if ischar(val)
                    to.func_file=val;
                else
                    error('tenopt - Invalid Parameter value');
                end
            otherwise
                error('tenopt - Invalid parameter');
        end
    case '{}'
        error('tenopt - cell array indexing not supported by tensegrity objects');
end
