function out=subsref(tc,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal tenconst object 
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
                out=subsref(tc(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=tc(index(1).subs{:});
        end
    case '.'
        switch index(1).subs
            case 'tensegrity'
                if size(index,2)>1
                    try
                        out=subsref(tc.tensegrity,index(2:size(index,2)));
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=tc.tensegrity;
                end
            case 'const_filename'
                out=tc.const_file;
            case 'num_var'
                out=tc.num_var;
            case 'variables'
                if size(index,2)>1
                    try
                        out=subsref(tc.variables,index(2:size(index,2)));
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=tc.variables;
                end
            case 'num_user_var'
                out=tc.num_user_var;
            case 'user_variables';
                if size(index,2)>1
                    try
                        out=subsref(tc.user_variables,index(2:size(index,2)));
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=tc.user_variables;
                end
            case 'cm'
                if size(index,2)>1
                    switch index(2).type
                        case '.'
                            switch index(2).subs
                                case 'num_nodes'
                                    out=tc.cm.num_nodes;
                                case 'nodes'
                                    if size(index,2)>2
                                        switch index(3).type
                                            case '()'
                                                if size(index,2)>3
                                                    switch index(4).type
                                                        case '.'
                                                            out=tc.cm.nodes(index(3).subs{:}).name;
                                                        otherwise
                                                            error('tenconst - Invalid indexing mode');
                                                    end
                                                else
                                                    out=tc.cm.nodes(index(3).subs{:});
                                                end
                                            otherwise
                                                error('tenconst - Invalid indexing mode');
                                        end
                                    else
                                        out=tc.cm.nodes;
                                    end
                                case 'position'
                                    if size(index,2)>2
                                        try
                                            out=subsref(tc.cm.position,index(3:size(index,2)));
                                        catch
                                            rethrow(lasterror);
                                        end
                                    else
                                        out=tc.cm.position;
                                    end
                                case 'orientation'
                                    if size(index,2)>2
                                        try
                                            out=subsref(tc.cm.orientation,index(3:size(index,2)));
                                        catch
                                            rethrow(lasterror);
                                        end
                                    else
                                        out=tc.cm.orientation;
                                    end
                                otherwise
                                    error('tenconst - Invalid parameter');
                            end
                        otherwise
                            error('tenconst - Invalid indexing mode');
                    end
                else
                    out=tc.cm;
                end
            case 'num_cop_sets'
                out=tc.num_cop_sets;
            case 'cop_sets'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            if size(index,2)>2
                                switch index(3).type
                                    case '.'
                                        switch index(3).subs
                                            case 'num_nodes'
                                                out=tc.cop_sets(index(2).subs{:}).num_nodes;
                                            case 'name'
                                                out=tc.cop_sets(index(2).subs{:}).name;
                                            case 'nodes'
                                                if size(index,2)>3
                                                    switch index(4).type
                                                        case '()'
                                                            out=tc.cop_sets(index(2).subs{:}).nodes(index(4).subs{:});                                                    
                                                        otherwise
                                                            error('tenconst - Invalid indexing mode');
                                                    end
                                                else
                                                    out=tc.cop_sets(index(2).subs{:}).nodes;
                                                end
                                            case 'normal'
                                                if size(index,2)>3
                                                    try
                                                        out=subsref(tc.cop_sets(index(2).subs{:}).normal,index(4:size(index,2)));
                                                    catch
                                                        rethrow(lasterror);
                                                    end
                                                else
                                                    out=tc.cop_sets(index(2).subs{:}).normal;
                                                end
                                            case 'dist'
                                                if size(index,2)>3
                                                    try
                                                        out=subsref(tc.cop_sets(index(2).subs{:}).dist,index(4:size(index,2)));
                                                    catch
                                                        rethrow(lasterror);
                                                    end
                                                else
                                                    out=tc.cop_sets(index(2).subs{:}).dist;
                                                end
                                        end
                                    otherwise
                                        error('tenconst - Invalid indexing mode');
                                end
                            else
                                out=tc.cop_sets(index(2).subs{:});
                            end
                        case '.'
                            error('tenconst - Invalid indexing mode');
                        case '{}'
                            error('tenconst - Invalid indexing mode');
                    end
                else
                    out=tc.cop_sets;
                end
            case 'sym'
                if size(index,2)>1
                    switch index(2).type
                        case '.'
                            switch index(2).subs
                                case 'num_sets'
                                    out=tc.sym.num_sets;
                                case 'sets'
                                    if size(index,2)>2
                                        switch index(3).type
                                            case '()'
                                                if size(index,2)>3
                                                    switch index(4).type
                                                        case '.'
                                                            switch index(4).subs
                                                                case 'num_edges'
                                                                    out=tc.sym.sets(index(3).subs{:}).num_edges;
                                                                case 'edges'
                                                                    if size(index,2)>4
                                                                        switch index(5).type
                                                                            case '()'
                                                                                out=tc.sym.sets(index(3).subs{:}).edges(index(5).subs{:}).name;
                                                                            otherwise
                                                                                error('Invalid indexing mode');
                                                                        end
                                                                    else
                                                                        out=tc.sym.sets(index(3).subs{:}).edges;
                                                                    end
                                                                otherwise
                                                                    error('tenconst - Invalid attribute');
                                                            end
                                                        otherwise
                                                            error('tenconst - Invalid indexing mode');
                                                    end
                                                else
                                                    out=tc.sym.sets(index(3).subs{:});
                                                end
                                            otherwise
                                                error('tenconst - Invalid indexing mode');
                                        end
                                    else
                                        out=tc.sym.sets;
                                    end
                                otherwise
                                    error('tenconst - Invalid attribute');
                            end
                        otherwise 
                            error('tenconst - Invalid indexing mode');
                    end
                else
                    out=tc.sym;
                end
            case 'cost_func'
                if size(index,2)>1
                    try
                        out=tc.cost_func_h(index(2).subs{:});
                    catch
                        rethrow(lasterror);
                    end
                else
                    if ~isempty(tc.cost_func_h)
                        out=func2str(tc.cost_func_h);
                    else
                        out='none';
                    end
                end
            otherwise
                try
                    out=subsref(tc.tensegrity,index);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('tenconst - Invalid indexing mode');
end