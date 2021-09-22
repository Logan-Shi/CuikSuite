function tc=subsasgn(tc,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of some internal tenconst object 
% atributes. Only the attributes from the center of mass and complanar sets
% constraints can be modified this way, as well as the base class
% attributes.
%
% See also tenconst

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                tc(index(1).subs{:})=subasgn(tc(index(1).subs{:}),index(2:size(index,2)),val);
            catch
                rethrow(lasterror);
            end
        else
            if isa(val,'tenconst')
                tc(index(1).subs{:})=val;
            else
                error('tenconst - Invalid parameter value');
            end
        end
    case '.'
        switch index(1).subs
            case 'tensegrity'
                if size(index,2)>1
                    tc.tensegrity=subsasgn(tc.tensegrity,index(2:size(index,2)),val);
                else
                    if isa(val,'tensegrity')
                        tc.tensegrity=val;
                    else
                        error('tenconst - Invalid tensegrity object');
                    end
                end
            case 'cm'
                if size(index,2)>1
                    switch index(2).type
                        case '.'
                            switch index(2).subs
                                case 'position'
                                    if size(index,2)>2
                                        try
                                            tc.cm.position=subsasgn(tc.cm.position,index(3:size(index,2)),val);
                                        catch
                                            rethrow(lasterror);
                                        end
                                    else
                                        if isa(val,'tenvar')
                                            tc.cm.position=val;
                                        else
                                            error('tenconst - Invalid parameter');
                                        end
                                    end
                                case 'orientation'
                                    if size(index,2)>2
                                        try
                                            tc.cm.orientation=subsasgn(tc.cm.orientation,index(3:size(index,2)),val);
                                        catch
                                            rethrow(lasterror);
                                        end
                                    else
                                        if isa(val,'tenvar')
                                            tc.cm.orientation=val;
                                        else
                                            error('tenconst - Invalid parameter');
                                        end
                                    end
                                otherwise
                                    error('tenconst - Invalid parameter');
                            end
                        otherwise
                            error('tenconst - Invalid indexing mode');
                    end
                else
                    error('tenconst - Impossible to access private members');
                end
            case 'cop_sets'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            if size(index,2)>2
                                switch index(3).type
                                    case '.'
                                        switch index(3).subs
                                            case 'normal'
                                                if size(index,2)>3
                                                    try
                                                        tc.cop_sets(index(2).subs{:}).normal=subsasgn(tc.cop_sets(index(2).subs{:}).normal,index(4:size(index,2)),val);
                                                    catch
                                                        rethrow(lasterror);
                                                    end
                                                else
                                                    tc.cop_sets(index(2).subs{:}).normal=val;
                                                end
                                            case 'dist'
                                                if size(index,2)>3
                                                    try
                                                        tc.cop_sets(index(2).subs{:}).dist=subsasgn(tc.cop_sets(index(2).subs{:}).dist,index(4:size(index,2)),val);
                                                    catch
                                                        rethrow(lasterror);
                                                    end
                                                else
                                                    tc.cop_sets(index(2).subs{:}).dist=val;
                                                end
                                        end
                                    otherwise
                                        error('tenconst - Invalid indexing mode');
                                end
                            else
                                error('tenconst - Impossible to access private members');
                            end
                        case '.'
                            error('tenconst - Invalid indexing mode');
                        case '{}'
                            error('tenconst - Invalid indexing mode');
                    end
                else
                    error('tenconst - impossible to access private members');
                end
            otherwise
                try
                    tc.tensegrity=subsasgn(tc.tensegrity,index,val);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('tenconst - cell array indexing not supported by tensegrity objects');
end
