function [te,num,vars]=getvariables(te)

if isa(te,'tenenv')
    try
        te.num_env_var=0;
        te.env_var=tenvar();
        [te.tenconst,num,vars]=getvariables(te.tenconst);
        for i=1:1:te.num_planes
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.planes(i).normal(1);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.planes(i).normal(2);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.planes(i).normal(3);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.planes(i).offset(1);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.planes(i).offset(2);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.planes(i).offset(3);
        end
        for i=1:1:te.num_cilinders
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.cilinders(i).radius;
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.cilinders(i).length;
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.cilinders(i).origin(1);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.cilinders(i).origin(2);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.cilinders(i).origin(3);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.cilinders(i).orientation(1);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.cilinders(i).orientation(2);
            te.num_env_var=te.num_env_var+1;
            te.env_var(te.num_env_var)=te.cilinders(i).orientation(3);
        end
        % return the number and list of env_var
        num=te.num_env_var+num;
        vars=[vars te.env_var];
    catch
        rethrow(lasterror);
    end
else
    error('tenenv - Invalid tensegrity environment object');
end