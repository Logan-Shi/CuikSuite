function out=subsref(tcol,index)
% Subscripted reference for objects
% this function allows tcol retrieve the value of internal tenopt object 
% atributs. All internal attributes can be accessed by () and . 
% indexing modes
%
% A(i) returns the element at the i-th position
% 
% A.i return the field identified by i
%
% See also tenconst

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                out=subsref(tcol(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=tcol(index(1).subs{:});
        end
    case '.'
        switch index(1).subs
            case 'num_env_eq'
				out=tcol.num_env_eq;
            case 'env_eq_const'
				if size(index,2)>1
                    switch index(2).type
                        case '()'
                            out=tcol.env_eq_const(index(2).subs{:});
                        otherwise
                            error('tencol - Invalid indexing mode');
                    end
                else
                    out=tcol.env_eq_const;
                end
            case 'num_env_ineq'
                out=tcol.num_env_ineq;
            case 'env_ineq_const'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            out=tcol.env_ineq_const(index(2).subs{:});
                        otherwise
                            error('tencol - Invalid indexing mode');
                    end
                else
                    out=tcol.env_ineq_const;
                end
            otherwise
                out=subsref(tcol.tenopt,index);
        end
    case '{}'
        error('tenopt - Invalid indexing mode');
end