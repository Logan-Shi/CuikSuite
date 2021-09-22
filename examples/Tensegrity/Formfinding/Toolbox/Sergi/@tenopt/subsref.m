function out=subsref(to,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal tenopt object 
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
                out=subsref(to(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=to(index(1).subs{:});
        end
    case '.'
        switch index(1).subs
            case 'const'
                out=to.const;
            case 'penalty'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            out=to.penalty(index(2).subs{:});
                        otherwise
                            error('tenopt - Invalid indexing modes');
                    end
                else
                    out=to.penalty;
                end
            case 'penalty_update'
                if ~isempty(to.penalty_update_h)
                    out=func2str(to.penalty_update_h);
                else
                    out='none';
                end
            case 'beta'
                out=to.beta;
            case 's'
                out=to.s;
            case 'sigma'
                out=to.sigma;
            case 'tolerance'
                out=to.tolerance;
            case 'num_eq'
                out=to.num_eq;
            case 'eq_const'
                out=to.eq_const;
            case 'num_ineq'
                out=to.num_ineq;
            case 'ineq_const'
                out=to.ineq_const;
            case 'function'
                out=to.function;
            case 'gradient'
                out=to.gradient;
            case 'const_file'
                if size(index,2)>1
                    try
                        out=to.const_file(index(2).subs{:});
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=to.const_file;
                end
            case 'grad_file'
                if size(index,2)>1
                    try
                        out=to.grad_file(index(2).subs{:});
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=to.grad_file;
                end
            case 'func_file'
                if size(index,2)>1
                    try
                        out=to.func_file(index(2).subs{:});
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=to.func_file;
                end
            case 'solution'
                out=to.solution;
            otherwise
                error('tenopt - Invalid parameter');
        end
    case '{}'
        error('tenopt - Invalid indexing mode');
end