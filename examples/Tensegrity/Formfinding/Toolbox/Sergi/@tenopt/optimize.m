function to=optimize(to,init_value,parameters)
% optimization procedure
% this function iteratively finds the minimum of a nonlinear function using
% a penalty based newton method. The optimization parameters are specified
% in the associated optfile object. The optimization methods uses the
% init_value passed as argument to initialized the value of the
% optimization variables which can be a random value or the result of a
% previous optimization process.
%
% Also, it is possible to specify a set of parameters for the structure to
% change its behavior without having to re-compute the constraint equations
% and inequations. The length of both input vectors depend on the number of
% passive and actuated and parameter variables specified in the constraints
% file.
%
% to=optimize(to,init_value,parameters) returns a modified version of the
% tenopt object updated with the solution of the optimization process.
% After calling this function at least once, it is possible to call the
% show function to display the current tensegrity configuration.
%
% The tenopt object must be initialized before calling this function and
% the init value and parameters vectors must have the correct size for the
% problem. Use the getoptvar function to get the number of optimization 
% variables .
%
% See also tenopt, tenconst
 
%solucio antiga
num_opt=getnumoptvar(to);
old_D=eye(num_opt,num_opt);
old_sol=init_value+0.000001;
sol=init_value;
eval(['old_grad=',to.grad_file,'(old_sol,parameters);']);
eval(['grad=',to.grad_file,'(sol,parameters);']);
% pas inicial
step=1;
iteration=1;
num=0;
while (max(abs(grad))>to.tolerance) && max(abs(grad-old_grad))>0.0000000001
    p=sol-old_sol;
    q=grad.'-old_grad.';
    if p*q.'==0
    	D=old_D;
    else
        t=q*old_D*q.';
        v=p/(p*q.')-(old_D*q.').'/t;
        D=old_D+(p.'*p)/(p*q.')-(old_D*q.'*q*old_D)/(q*old_D*q.')+t*v.'*v;
    end
    steps=-D*grad;
    % calcular el step de cada variable
    eval(['valor=',to.func_file,'(sol,parameters);']);
    for m=0:1:10
        step_sol=sol+to.beta^m*to.s*steps.';
        eval(['old_valor=',to.func_file,'(step_sol,parameters);']);
        grad_valor=to.sigma*to.beta^m*to.s*grad.'*steps;
        if (valor-old_valor+grad_valor)>=0
            break;
        end
    end
    step=to.beta^m*to.s;
    old_sol=sol;
    sol=sol+step*steps.';
    if sol-old_sol==0
        break;
    end
    old_grad=grad;
    eval(['grad=',to.grad_file,'(sol,parameters);']);
    old_D=D;
    iteration=iteration+1;
end
to.solution=sol;
