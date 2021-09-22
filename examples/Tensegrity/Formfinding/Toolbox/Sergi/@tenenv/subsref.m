function out=subsref(te,index)

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                out=subsref(te(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=te(index(1).subs{:});
        end
    case '.'        
        switch index(1).subs
            case 'tenconst'
                if size(index,2)>1
                    out=subsref(te.tenconst,index(2:size(index,2)));
                else
                    out=te.tenconst;
                end
            case 'num_env_var'
                out=te.num_env_var;
            case 'env_var'
                if size(index,2)>1
                    out=subsref(te.env_var,index(2:size(index,2)));
                else
                    out=te.env_var;
                end
            case 'num_planes'
                out=te.num_planes;
            case 'planes'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            if size(index,2)>2
                                switch index(3).type
                                    case '.'
                                        switch index(3).subs
                                            case 'name'
                                                out=te.planes(index(2).subs{:}).name;
                                            case 'normal'
                                                if size(index,2)>3
                                                    switch index(4).type
                                                        case '()'
                                                            if index(4).subs{:}>0 || index(4).subs{:}<4
                                                                out=subsref(te.planes(index(2).subs{:}).normal,index(4:size(index,2)));
                                                            else
                                                                error('tenenv - Invalid parameter');                                                    
                                                            end
                                                        otherwise
                                                            error('tenenv - Invalid indexing mode');
                                                    end
                                                else
                                                    out=te.planes(index(2).subs{:}).normal;
                                                end
                                            case 'offset'
                                                if size(index,2)>3
                                                    switch index(4).type
                                                        case '()'
                                                            if index(4).subs{:}>0 || index(4).subs{:}<4
                                                                out=subsref(te.planes(index(2).subs{:}).offset,index(4:size(index,2)));
                                                            else
                                                                error('tenenv - Invalid parameter');                                                    
                                                            end
                                                        otherwise
                                                            error('tenenv - Invalid indexing mode');
                                                    end
                                                else
                                                    out=te.planes(index(2).subs{:}).offset;
                                                end
                                            otherwise
                                                error('tenenv - Invalid parameter');
                                        end
                                    otherwise
                                        error('tenenv - Invalid indexing mode');
                                end
                            else
                                out=te.planes(index(2).subs{:});
                            end
                        otherwise
                            error('tenenv - Invalid indexing mode');
                    end
                else
                    out=te.planes;
                end
            case 'num_cilinders'
                out=te.num_cilinders;
            case 'cilinders'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            if size(index,2)>2
                                switch index(3).type
                                    case '.'
                                        switch index(3).subs
                                            case 'name'
                                                out=te.cilinders(index(2).subs{:}).name;
                                            case 'radius'
                                                if size(index,2)>3
                                                    out=subsref(te.cilinders(index(2).subs{:}).radius,index(4:size(index,2)));
                                                else
                                                    out=te.cilinders(index(2).subs{:}).radius;
                                                end
                                            case 'length'
                                                if size(index,2)>3
                                                    out=subsref(te.cilinders(index(2).subs{:}).length,index(4:size(index,2)));
                                                else
                                                    out=te.cilinders(index(2).subs{:}).length;
                                                end
                                            case 'origin'
                                                if size(index,2)>3
                                                    switch index(4).type
                                                        case '()'
                                                            if index(4).subs{:}>0 || index(4).subs{:}<4
                                                                out=subsref(te.cilinders(index(2).subs{:}).origin,index(4:size(index,2)));
                                                            else
                                                                error('tenenv - Invalid parameter');
                                                            end
                                                        otherwise
                                                            error('tenenv - Invalid indexing mode');
                                                    end
                                                else
                                                    out=te.cilinders(index(2).subs{:}).origin;
                                                end
                                            case 'orientation'
                                                if size(index,2)>3
                                                    switch index(4).type
                                                        case '()'
                                                            if index(4).subs{:}>0 || index(4).subs{:}<4
                                                                out=subsref(te.cilinders(index(2).subs{:}).orientation,index(4:size(index,2)));
                                                            else
                                                                error('tenenv - Invalid parameter');
                                                            end
                                                        otherwise
                                                            error('tenenv - Invalid indexing mode');
                                                    end
                                                else
                                                    out=te.cilinders(index(2).subs{:}).orientation;
                                                end
                                            otherwise
                                                error('tenenv - Invalid parameter');
                                        end
                                    otherwise
                                        error('tenenv - Invalid parameter');
                                end
                            else
                                error('tenenv - Invalid parameter');
                            end
                        otherwise
                            error('Invalid indexing mode');
                    end
                else
                    out=te.cilinders;
                end
            otherwise
                try
                    out=subsref(te.tenconst,index);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('tenenv - Cell array indexing not allowed for tensegrity environment objects');
end