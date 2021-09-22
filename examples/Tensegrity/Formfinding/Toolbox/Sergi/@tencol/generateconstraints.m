function tcol=generateconstraints(tcol)
% generates the constraint equations for the tensegrity
% this function builds the equality and inequality constraints associated
% with the tensegrity. This function must be called before calling the
% generatefunction function.
%
% to=generateconstraints(to) returns a modified version of the tenopt object
% updated with the constraint equations for the tensegrity. The result is
% stored internally to the object, but can be accessed externally by simple
% field indexing.
%
% The tensegrity optimization object must be initialized before calling
% this function. 
%
% See also: tenopt,tenconst

try
    % generar les restriccions de l'estructura
    tcol.tenopt=generateconstraints(tcol.tenopt);
    te=tcol.tenopt.const;
    tcol.num_env_ineq=0;
    tcol.num_env_eq=0;
    tcol.env_eq_const=sym('0');
    tcol.env_ineq_const=sym('0');
    % restriccions de colisió amb plans
    for i=1:1:te.num_planes
        for j=1:1:te.num_nodes
            if strcmp(te.nodes(j).position(1).type,'fixed')
                if strcmp(te.planes(i).normal(1).type,'fixed')
                    if strcmp(te.planes(i).offset(1).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=te.planes(i).normal(1).value*(te.nodes(j).position(1).value-te.planes(i).offset(1).value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=te.planes(i).normal(1).value*(te.nodes(j).position(1).value-te.planes(i).offset(1).var);
                    end
                else
                    if strcmp(te.planes(i).offset(1).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=te.planes(i).normal(1).var*(te.nodes(j).position(1).value-te.planes(i).offset(1).value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=te.planes(i).normal(1).var*(te.nodes(j).position(1).value-te.planes(i).offset(1).var);                        
                    end
                end
            else
                if strcmp(te.planes(i).normal(1).type,'fixed')
                    if strcmp(te.planes(i).offset(1).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=te.planes(i).normal(1).value*(te.nodes(j).position(1).var-te.planes(i).offset(1).value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=te.planes(i).normal(1).value*(te.nodes(j).position(1).var-te.planes(i).offset(1).var);                        
                    end
                else
                    if strcmp(te.planes(i).offset(1).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=te.planes(i).normal(1).var*(te.nodes(j).position(1).var-te.planes(i).offset(1).value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=te.planes(i).normal(1).var*(te.nodes(j).position(1).var-te.planes(i).offset(1).var);                        
                    end
                end
            end
            if strcmp(te.nodes(j).position(2).type,'fixed')
                if strcmp(te.planes(i).normal(2).type,'fixed')
                    if strcmp(te.planes(i).offset(2).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(2).value*(te.nodes(j).position(2).value-te.planes(i).offset(2).value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(2).value*(te.nodes(j).position(2).value-te.planes(i).offset(2).var);
                    end
                else
                    if strcmp(te.planes(i).offset(2).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(2).var*(te.nodes(j).position(2).value-te.planes(i).offset(2).value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(2).var*(te.nodes(j).position(2).value-te.planes(i).offset(2).var);                        
                    end
                end
            else
                if strcmp(te.planes(i).normal(2).type,'fixed')
                    if strcmp(te.planes(i).offset(2).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(2).value*(te.nodes(j).position(2).var-te.planes(i).offset(2).value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(2).value*(te.nodes(j).position(2).var-te.planes(i).offset(2).var);                        
                    end
                else
                    if strcmp(te.planes(i).offset(2).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(2).var*(te.nodes(j).position(2).var-te.planes(i).offset(2).value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(2).var*(te.nodes(j).position(2).var-te.planes(i).offset(2).var);                        
                    end
                end
            end
            if strcmp(te.nodes(j).position(3).type,'fixed')
                if strcmp(te.planes(i).normal(3).type,'fixed')
                    if strcmp(te.planes(i).offset(3).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(3).value*(te.nodes(j).position(3).value-te.planes(i).offset(3).value)-0.01;
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(3).value*(te.nodes(j).position(3).value-te.planes(i).offset(3).var)-0.01;
                    end
                else
                    if strcmp(te.planes(i).offset(3).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(3).var*(te.nodes(j).position(3).value-te.planes(i).offset(3).value)-0.01;
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(3).var*(te.nodes(j).position(3).value-te.planes(i).offset(3).var)-0.01;                        
                    end
                end
            else
                if strcmp(te.planes(i).normal(3).type,'fixed')
                    if strcmp(te.planes(i).offset(3).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(3).value*(te.nodes(j).position(3).var-te.planes(i).offset(3).value)-0.01;
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(3).value*(te.nodes(j).position(3).var-te.planes(i).offset(3).var)-0.01;                        
                    end
                else
                    if strcmp(te.planes(i).offset(3).type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(3).var*(te.nodes(j).position(3).var-te.planes(i).offset(3).value)-0.01;
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=tcol.env_ineq_const(tcol.num_env_ineq+1)+te.planes(i).normal(3).var*(te.nodes(j).position(3).var-te.planes(i).offset(3).var)-0.01;                        
                    end
                end
            end
            tcol.num_env_ineq=tcol.num_env_ineq+1;
        end
    end
    % restriccions d'autocolisió de les barres
    for i=1:1:te.num_edges
        for j=i+1:1:te.num_edges
            if strcmp(te.edges(i).type,'strut') && strcmp(te.edges(j).type,'strut')
                e1=te.edges(i);
                e2=te.edges(j);
                e1_o_index=getnodeindex(te.tenconst.tensegrity,e1.origin);
                e1_e_index=getnodeindex(te.tenconst.tensegrity,e1.end);
                n1_o=te.nodes(e1_o_index);
                n1_e=te.nodes(e1_e_index);
                e2_o_index=getnodeindex(te.tenconst.tensegrity,e2.origin);
                e2_e_index=getnodeindex(te.tenconst.tensegrity,e2.end);
                n2_o=te.nodes(e2_o_index);
                n2_e=te.nodes(e2_e_index);
                v=[sym('0'),sym('0'),sym('0')];                
                if strcmp(n1_o.position(1).type,'fixed')
                    if strcmp(n1_e.position(1).type,'fixed')
                        v(1)=n1_e.position(1).value-n1_o.position(1).value;
                    else
                        v(1)=n1_e.position(1).var-n1_o.position(1).value;
                    end
                else
                    if strcmp(n1_e.position(1).type,'fixed')
                        v(1)=n1_e.position(1).value-n1_o.position(1).var;
                    else
                        v(1)=n1_e.position(1).var-n1_o.position(1).var;
                    end
                end
                if strcmp(n1_o.position(2).type,'fixed')
                    if strcmp(n1_e.position(2).type,'fixed')
                        v(2)=n1_e.position(2).value-n1_o.position(2).value;
                    else
                        v(2)=n1_e.position(2).var-n1_o.position(2).value;
                    end
                else
                    if strcmp(n1_e.position(2).type,'fixed')
                        v(2)=n1_e.position(2).value-n1_o.position(2).var;
                    else
                        v(2)=n1_e.position(2).var-n1_o.position(2).var;
                    end
                end
                if strcmp(n1_o.position(3).type,'fixed')
                    if strcmp(n1_e.position(3).type,'fixed')
                        v(3)=n1_e.position(3).value-n1_o.position(3).value;
                    else
                        v(3)=n1_e.position(3).var-n1_o.position(3).value;
                    end
                else
                    if strcmp(n1_e.position(3).type,'fixed')
                        v(3)=n1_e.position(3).value-n1_o.position(3).var;
                    else
                        v(3)=n1_e.position(3).var-n1_o.position(3).var;
                    end
                end
                u=[sym('0'),sym('0'),sym('0')];                
                if strcmp(n2_o.position(1).type,'fixed')
                    if strcmp(n2_e.position(1).type,'fixed')
                        u(1)=n2_e.position(1).value-n2_o.position(1).value;
                    else
                        u(1)=n2_e.position(1).var-n2_o.position(1).value;
                    end
                else
                    if strcmp(n1_e.position(1).type,'fixed')
                        u(1)=n2_e.position(1).value-n2_o.position(1).var;
                    else
                        u(1)=n2_e.position(1).var-n2_o.position(1).var;
                    end
                end
                if strcmp(n2_o.position(2).type,'fixed')
                    if strcmp(n2_e.position(2).type,'fixed')
                        u(2)=n2_e.position(2).value-n2_o.position(2).value;
                    else
                        u(2)=n2_e.position(2).var-n2_o.position(2).value;
                    end
                else
                    if strcmp(n2_e.position(2).type,'fixed')
                        u(2)=n2_e.position(2).value-n2_o.position(2).var;
                    else
                        u(2)=n2_e.position(2).var-n2_o.position(2).var;
                    end
                end
                if strcmp(n2_o.position(3).type,'fixed')
                    if strcmp(n2_e.position(3).type,'fixed')
                        u(3)=n2_e.position(3).value-n2_o.position(3).value;
                    else
                        u(3)=n2_e.position(3).var-n2_o.position(3).value;
                    end
                else
                    if strcmp(n2_e.position(3).type,'fixed')
                        u(3)=n2_e.position(3).value-n2_o.position(3).var;
                    else
                        u(3)=n2_e.position(3).var-n2_o.position(3).var;
                    end
                end
                w0=[sym('0'),sym('0'),sym('0')];
                if strcmp(n1_o.position(1).type,'fixed')
                    if strcmp(n2_o.position(1).type,'fixed')
                        w0(1)=n2_o.position(1).value-n1_o.position(1).value;
                    else
                        w0(1)=n2_o.position(1).var-n1_o.position(1).value;
                    end
                else
                    if strcmp(n2_o.position(1).type,'fixed')
                        w0(1)=n2_o.position(1).value-n1_o.position(1).var;
                    else
                        w0(1)=n2_o.position(1).var-n1_o.position(1).var;
                    end
                end
                if strcmp(n1_o.position(2).type,'fixed')
                    if strcmp(n2_o.position(2).type,'fixed')
                        w0(2)=n2_o.position(2).value-n1_o.position(2).value;
                    else
                        w0(2)=n2_o.position(2).var-n1_o.position(2).value;
                    end
                else
                    if strcmp(n2_o.position(2).type,'fixed')
                        w0(2)=n2_o.position(2).value-n1_o.position(2).var;
                    else
                        w0(2)=n2_o.position(2).var-n1_o.position(2).var;
                    end
                end
                if strcmp(n1_o.position(3).type,'fixed')
                    if strcmp(n2_o.position(3).type,'fixed')
                        w0(3)=n2_o.position(3).value-n1_o.position(3).value;
                    else
                        w0(3)=n2_o.position(3).var-n1_o.position(3).value;
                    end
                else
                    if strcmp(n2_o.position(3).type,'fixed')
                        w0(3)=n2_o.position(3).value-n1_o.position(3).var;
                    else
                        w0(3)=nw_o.position(3).var-n1_o.position(3).var;
                    end
                end
                a=u*u.';
                b=u*v.';
                c=v*v.';
                d=u*w0.';
                e=v*w0.';
                dist=w0*(a*c-b*b)+((b*e-c*d)*u-(a*e-b*d)*v);
                if strcmp(e1.radius.type,'fixed')
                    if strcmp(e2.radius.type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(e1.radius.value+e2.radius.value)*(e1.radius.value+e2.radius.value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(e1.radius.value+e2.radius.var)*(e1.radius.value+e2.radius.var);
                    end
                else
                    if strcmp(e2.radius.type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(e1.radius.var+e2.radius.value)*(e1.radius.var+e2.radius.value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(e1.radius.var+e2.radius.var)*(e1.radius.var+e2.radius.var);
                    end
                end
                tcol.num_env_ineq=tcol.num_env_ineq+1;                
            end
        end
    end
    % restriccions de colisió amb els cilindres
    for i=1:1:te.num_cilinders
        for j=1:1:te.num_edges
            if strcmp(te.edges(j).type,'strut')
                e1=te.edges(j);
                e1_o_index=getnodeindex(te.tenconst.tensegrity,e1.origin);
                e1_e_index=getnodeindex(te.tenconst.tensegrity,e1.end);
                n1_o=te.nodes(e1_o_index);
                n1_e=te.nodes(e1_e_index);
                v=[sym('0'),sym('0'),sym('0')];
                if strcmp(n1_o.position(1).type,'fixed')
                    if strcmp(n1_e.position(1).type,'fixed')
                        v(1)=n1_e.position(1).value-n1_e.position(1).value;
                    else
                        v(1)=n1_e.position(1).var-n1_e.position(1).value;
                    end
                else
                    if strcmp(n1_e.position(1).type,'fixed')
                        v(1)=n1_e.position(1).value-n1_e.position(1).var;
                    else
                        v(1)=n1_e.position(1).var-n1_e.position(1).var;
                    end
                end
                if strcmp(n1_o.position(2).type,'fixed')
                    if strcmp(n1_e.position(2).type,'fixed')
                        v(2)=n1_e.position(2).value-n1_e.position(2).value;
                    else
                        v(2)=n1_e.position(2).var-n1_e.position(2).value;
                    end
                else
                    if strcmp(n1_e.position(2).type,'fixed')
                        v(2)=n1_e.position(2).value-n1_e.position(2).var;
                    else
                        v(2)=n1_e.position(2).var-n1_e.position(2).var;
                    end
                end
                if strcmp(n1_o.position(3).type,'fixed')
                    if strcmp(n1_e.position(3).type,'fixed')
                        v(3)=n1_e.position(3).value-n1_e.position(3).value;
                    else
                        v(3)=n1_e.position(3).var-n1_e.position(3).value;
                    end
                else
                    if strcmp(n1_e.position(3).type,'fixed')
                        v(3)=n1_e.position(3).value-n1_e.position(3).var;
                    else
                        v(3)=n1_e.position(3).var-n1_e.position(3).var;
                    end
                end
                u=[sym('0'),sym('0'),sym('0')];                
                if strcmp(te.cilinders(i).orientation(1).type,'fixed')
                    u(1)=te.cilinders(i).orientation(1).value;
                else
                    u(1)=te.cilinders(i).orientation(1).var;                    
                end
                if strcmp(te.cilinders(i).orientation(2).type,'fixed')
                    u(2)=te.cilinders(i).orientation(2).value;
                else
                    u(2)=te.cilinders(i).orientation(2).var;                    
                end
                if strcmp(te.cilinders(i).orientation(3).type,'fixed')
                    u(3)=te.cilinders(i).orientation(3).value;
                else
                    u(3)=te.cilinders(i).orientation(3).var;                    
                end
                w0=[sym('0'),sym('0'),sym('0')];
                if strcmp(n1_o.position(1).type,'fixed')
                    if strcmp(te.cilinders(i).origin(1).type,'fixed')
                        w0(1)=te.cilinders(i).origin(1).value-n1_o.position(1).value;
                    else
                        w0(1)=te.cilinders(i).origin(1).var-n1_o.position(1).value;
                    end
                else
                    if strcmp(te.cilinders(i).origin(1).type,'fixed')
                        w0(1)=te.cilinders(i).origin(1).value-n1_o.position(1).var;
                    else
                        w0(1)=te.cilinders(i).origin(1).var-n1_o.position(1).var;
                    end
                end
                if strcmp(n1_o.position(2).type,'fixed')
                    if strcmp(te.cilinders(i).origin(2).type,'fixed')
                        w0(2)=te.cilinders(i).origin(2).value-n1_o.position(2).value;
                    else
                        w0(2)=te.cilinders(i).origin(2).var-n1_o.position(2).value;
                    end
                else
                    if strcmp(te.cilinders(i).origin(2).type,'fixed')
                        w0(2)=te.cilinders(i).origin(2).value-n1_o.position(2).var;
                    else
                        w0(2)=te.cilinders(i).origin(2).var-n1_o.position(2).var;
                    end
                end
                if strcmp(n1_o.position(3).type,'fixed')
                    if strcmp(te.cilinders(i).origin(3).type,'fixed')
                        w0(3)=te.cilinders(i).origin(3).value-n1_o.position(3).value;
                    else
                        w0(3)=te.cilinders(i).origin(3).var-n1_o.position(3).value;
                    end
                else
                    if strcmp(te.cilinders(i).origin(3).type,'fixed')
                        w0(3)=te.cilinders(i).origin(3).value-n1_o.position(3).var;
                    else
                        w0(3)=te.cilinders(i).origin(3).var-n1_o.position(3).var;
                    end
                end
                a=u*u.';
                b=u*v.';
                c=v*v.';
                d=u*w0.';
                e=v*w0.';
                dist=w0*(a*c-b*b)+((b*e-c*d)*u-(a*e-b*d)*v);
                if strcmp(e1.radius.type,'fixed')
                    if strcmp(te.cilinders(i).radius.type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(e1.radius.value+te.cilinders(i).radius.value)*(e1.radius.value+te.cilinders(i).radius.value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(e1.radius.value+te.cilinders(i).radius.var)*(e1.radius.value+te.cilinders(i).radius.var);
                    end
                else
                    if strcmp(te.cilinders(i).radius.type,'fixed')
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(e1.radius.var+te.cilinders(i).radius.value)*(e1.radius.var+te.cilinders(i).radius.value);
                    else
                        tcol.env_ineq_const(tcol.num_env_ineq+1)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(e1.radius.var+te.cilinders(i).radius.var)*(e1.radius.var+te.cilinders(i).radius.var);
                    end
                end
                tcol.num_env_ineq=tcol.num_env_ineq+1;
            end
        end
    end
catch
    rethrow(lasterror);
end
