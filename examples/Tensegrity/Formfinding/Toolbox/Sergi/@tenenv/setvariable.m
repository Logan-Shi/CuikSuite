function te=setvariable(te,index,var)
% update the information of an internal tenconst variable
% this function allows to update the information of a single variable
% indise the tenconst object by means of its index inside the variable
% list.
%
% te=setvariable(te,index,var) returns a modified version of the tenconst
% object with the information for the index variable updated to val.
%
% Both the tensegrity constraint object and the variable object must be
% initialized before calling this function, and index must be a positive
% integer and must not exceed the number of available variables (both 
% internal and user).
%
% See also tenconst,tenvar

if isa(te,'tenenv')
    if index>te.tenconst.num_var
        index=index-te.tenconst.num_var;
        for i=1:1:te.num_planes
            index=index-1;
            if index==0
                te.planes(i).normal(1)=var;
                return;
            end
            index=index-1;
            if index==0
                te.planes(i).normal(2)=var;
                return;                
            end
            index=index-1;
            if index==0
                te.planes(i).normal(3)=var;
                return;                
            end
            index=index-1;
            if index==0
                te.planes(i).offset(1)=var;
                return;                
            end
            index=index-1;
            if index==0
                te.planes(i).offset(2)=var;
                return;                
            end
            index=index-1;
            if index==0
                te.planes(i).offset(3)=var;
                return;                
            end
        end
        for i=1:1:te.num_cilinders
            index=index-1;
            if index==0
                te.cilinders(i).radius=var;
                return;
            end
            index=index-1;
            if index==0
                te.cilinders(i).length=var;
                return;
            end
            index=index-1;
            if index==0
                te.cilinders(i).origin(1)=var;
                return;
            end
            index=index-1;
            if index==0
                te.cilinders(i).origin(2)=var;
                return;
            end
            index=index-1;
            if index==0
                te.cilinders(i).origin(3)=var;
                return;
            end
            index=index-1;
            if index==0
                te.cilinders(i).orientation(1)=var;
                return;
            end
            index=index-1;
            if index==0
                te.cilinders(i).orientation(2)=var;
                return;
            end
            index=index-1;
            if index==0
                te.cilinders(i).orientation(3)=var;
                return;
            end
        end
    else
        te.tenconst=setvariable(te.tenconst,index,var);
    end
else
    error('tenconst - Invalid tensegrity constraint structure');
end
