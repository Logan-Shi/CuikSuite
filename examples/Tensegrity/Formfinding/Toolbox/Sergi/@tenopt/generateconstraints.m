function to=generateconstraints(to)
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
    % objecte de restriccions
    tc=to.const;
    % obtenir la matriu de connectivitat del tensegrity
    ConnMatrix=genconnmatrix(tc.tensegrity);
    EdgeMatrix.name=[];
    for i=1:1:tc.num_edges
        row_index=getnodeindex(tc.tensegrity,tc.edges(i).origin);
        col_index=getnodeindex(tc.tensegrity,tc.edges(i).end);
        EdgeMatrix(row_index,col_index).name=tc.edges(i).name;
        EdgeMatrix(col_index,row_index).name=tc.edges(i).name;
    end
    to.num_eq=0;
    to.num_ineq=0;
    % restriccions dels nodes
    for i=1:1:tc.num_nodes
        %buscar totes les arestes a les que esta connectat
        to.eq_const(to.num_eq+1)=sym('0');
        to.eq_const(to.num_eq+2)=sym('0');
        to.eq_const(to.num_eq+3)=sym('0');
        mul=sym('1');
        for k=1:1:tc.num_nodes
            if ConnMatrix(i,k)==1
                index=getedgeindex(tc.tensegrity,EdgeMatrix(i,k).name);
                e=tc.edges(index);
                stress=sym('0');
                if strcmp(e.rest_length.type,'fixed')
                    stress=1-e.rest_length.value/e.length.var;
                else
                    stress=1-e.rest_length.var/e.length.var;
                end
                if strcmp(e.stiffness.type,'fixed')
                    stress=e.stiffness.value*stress;
                else
                    stress=e.stiffness.var*stress;
                end
                if ~strcmp(tc.nodes(i).position(1).type,'fixed')
                    if strcmp(tc.nodes(k).position(1).type,'fixed')
                        to.eq_const(to.num_eq+1)=to.eq_const(to.num_eq+1)+stress*(tc.nodes(i).position(1).var-tc.nodes(k).position(1).value);
                    else
                        to.eq_const(to.num_eq+1)=to.eq_const(to.num_eq+1)+stress*(tc.nodes(i).position(1).var-tc.nodes(k).position(1).var);
                    end
                end
                if ~strcmp(tc.nodes(i).position(2).type,'fixed')
                    if strcmp(tc.nodes(k).position(2).type,'fixed')
                        to.eq_const(to.num_eq+2)=to.eq_const(to.num_eq+2)+stress*(tc.nodes(i).position(2).var-tc.nodes(k).position(2).value);
                    else
                        to.eq_const(to.num_eq+2)=to.eq_const(to.num_eq+2)+stress*(tc.nodes(i).position(2).var-tc.nodes(k).position(2).var);
                    end
                end
                if ~strcmp(tc.nodes(i).position(3).type,'fixed')
                    if strcmp(tc.nodes(k).position(3).type,'fixed')
                        to.eq_const(to.num_eq+3)=to.eq_const(to.num_eq+3)+stress*(tc.nodes(i).position(3).var-tc.nodes(k).position(3).value);
                    else
                        to.eq_const(to.num_eq+3)=to.eq_const(to.num_eq+3)+stress*(tc.nodes(i).position(3).var-tc.nodes(k).position(3).var);
                    end
                end
                mul=mul*e.length.var;
            end
        end
        % iguarlar a les forces externes
        if tc.nodes(i).num_forces>0
            if ~strcmp(tc.nodes(i).position(1).type,'fixed')
                if strcmp(tc.nodes(i).forces(1,1).type,'fixed')
                    to.eq_const(to.num_eq+1)=simplify((to.eq_const(to.num_eq+1)-tc.nodes(i).forces(1,1).value)*mul);
                else
                    to.eq_const(to.num_eq+1)=simplify((to.eq_const(to.num_eq+1)-tc.nodes(i).forces(1,1).var)*mul);
                end
                to.num_eq=to.num_eq+1;              
            end
            if ~strcmp(tc.nodes(i).position(2).type,'fixed')
                if strcmp(tc.nodes(i).forces(1,2).type,'fixed')
                    to.eq_const(to.num_eq+1)=simplify((to.eq_const(to.num_eq+1)-tc.nodes(i).forces(1,2).value)*mul);
                else
                    to.eq_const(to.num_eq+1)=simplify((to.eq_const(to.num_eq+1)-tc.nodes(i).forces(1,2).var)*mul);
                end
                to.num_eq=to.num_eq+1;              
            end
            if ~strcmp(tc.nodes(i).position(3).type,'fixed')        
                if strcmp(tc.nodes(i).forces(1,3).type,'fixed')
                    to.eq_const(to.num_eq+1)=simplify((to.eq_const(to.num_eq+1)-tc.nodes(i).forces(1,3).value)*mul);
                else
                    to.eq_const(to.num_eq+1)=simplify((to.eq_const(to.num_eq+1)-tc.nodes(i).forces(1,3).var)*mul);
                end
                to.num_eq=to.num_eq+1;              
            end
        else
            if ~strcmp(tc.nodes(i).position(1).type,'fixed')
                to.eq_const(to.num_eq+1)=simplify(to.eq_const(to.num_eq+1)*mul);
                to.num_eq=to.num_eq+1;            
            end
            if ~strcmp(tc.nodes(i).position(2).type,'fixed')        
                to.eq_const(to.num_eq+1)=simplify(to.eq_const(to.num_eq+1)*mul);
                to.num_eq=to.num_eq+1;            
            end
            if ~strcmp(tc.nodes(i).position(3).type,'fixed')
                to.eq_const(to.num_eq+1)=simplify(to.eq_const(to.num_eq+1)*mul);        
                to.num_eq=to.num_eq+1;            
            end
        end
        if ~strcmp(tc.nodes(i).position(3).type,'fixed')
            to.num_ineq=to.num_ineq+1;
            to.ineq_const(to.num_ineq)=tc.nodes(i).position(3).var;
        end
    end
    mul=sym('1');
    module=sym('0');
    %restriccions de les arestes
    for i=1:1:tc.num_edges
        org_index=getnodeindex(tc.tensegrity,tc.edges(i).origin);
        end_index=getnodeindex(tc.tensegrity,tc.edges(i).end);
        n_o=tc.nodes(org_index);
        n_e=tc.nodes(end_index);
        e=tc.edges(i);
        to.num_eq=to.num_eq+1;
        if strcmp(n_o.position(1).type,'fixed')
            if strcmp(n_e.position(1).type,'fixed')
                to.eq_const(to.num_eq)=(n_o.position(1).value-n_e.position(1).value)*(n_o.position(1).value-n_e.position(1).value);            
            else
                to.eq_const(to.num_eq)=(n_o.position(1).value-n_e.position(1).var)*(n_o.position(1).value-n_e.position(1).var);                      
            end
        else
            if strcmp(n_e.position(1).type,'fixed')
                to.eq_const(to.num_eq)=(n_o.position(1).var-n_e.position(1).value)*(n_o.position(1).var-n_e.position(1).value);            
            else
                to.eq_const(to.num_eq)=(n_o.position(1).var-n_e.position(1).var)*(n_o.position(1).var-n_e.position(1).var);            
            end
        end
        if strcmp(n_o.position(2).type,'fixed')
            if strcmp(n_e.position(2).type,'fixed')
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+(n_o.position(2).value-n_e.position(2).value)*(n_o.position(2).value-n_e.position(2).value);            
            else
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+(n_o.position(2).value-n_e.position(2).var)*(n_o.position(2).value-n_e.position(2).var);            
            end
        else
            if strcmp(n_e.position(2).type,'fixed')
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+(n_o.position(2).var-n_e.position(2).value)*(n_o.position(2).var-n_e.position(2).value);            
            else
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+(n_o.position(2).var-n_e.position(2).var)*(n_o.position(2).var-n_e.position(2).var);            
            end
        end
        if strcmp(n_o.position(3).type,'fixed')
            if strcmp(n_e.position(3).type,'fixed')
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+(n_o.position(3).value-n_e.position(3).value)*(n_o.position(3).value-n_e.position(3).value);            
            else
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+(n_o.position(3).value-n_e.position(3).var)*(n_o.position(3).value-n_e.position(3).var);            
            end
        else
            if strcmp(n_e.position(3).type,'fixed')
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+(n_o.position(3).var-n_e.position(3).value)*(n_o.position(3).var-n_e.position(3).value);            
            else
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+(n_o.position(3).var-n_e.position(3).var)*(n_o.position(3).var-n_e.position(3).var);            
            end
        end
        to.eq_const(to.num_eq)=(e.length.var*e.length.var-to.eq_const(to.num_eq));
        % restriccions de simetria
        for j=1:1:tc.sym.num_sets
            for k=1:1:tc.sym.sets(j).num_edges
                if strcmp(e.name,tc.sym.sets(j).edges(k).name)
                    if k>1
                        ref_edge=tc.edges(tc.sym.sets(j).edges(1).name);
                        to.num_eq=to.num_eq+1;
                        if strcmp(ref_edge.rest_length.type,'fixed')
                            if strcmp(e.rest_length.type,'fixed')
                                to.eq_const(to.num_eq)=ref_edge.rest_length.value*ref_edge.rest_length.value-e.rest_length.value*e.rest_length.value;
                            else
                                to.eq_const(to.num_eq)=ref_edge.rest_length.value*ref_edge.rest_length.value-e.rest_length.var*e.rest_length.var;
                            end
                        else
                            if strcmp(e.rest_length.type,'fixed')
                                to.eq_const(to.num_eq)=ref_edge.rest_length.var*ref_edge.rest_length.var-e.rest_length.value*e.rest_length.value;
                            else
                                to.eq_const(to.num_eq)=ref_edge.rest_length.var*ref_edge.rest_length.var-e.rest_length.var*e.rest_length.var;
                            end
                        end
                    end
                end
            end
        end
        if strcmp(e.type,'cable')
            if strcmp(e.rest_length.type,'fixed')
                to.num_ineq=to.num_ineq+1;
                to.ineq_const(to.num_ineq)=(e.length.var-e.rest_length.value);
            else
                if strcmp(e.rest_length.type,'parameter')
                    to.num_ineq=to.num_ineq+1;
                    to.ineq_const(to.num_ineq)=(e.length.var-e.rest_length.var);
                else
                    to.num_ineq=to.num_ineq+1;
                    to.ineq_const(to.num_ineq)=(e.rest_length.var-e.rest_length.value(1));
                    to.num_ineq=to.num_ineq+1;
                    to.ineq_const(to.num_ineq)=(e.length.var-e.rest_length.var);
                    to.num_ineq=to.num_ineq+1;
                    to.ineq_const(to.num_ineq)=(e.rest_length.value(2)-e.length.var);
                end
            end
        else
            if strcmp(e.rest_length.type,'fixed')
                to.num_ineq=to.num_ineq+1;
                to.ineq_const(to.num_ineq)=(e.rest_length.value-e.length.var);
            else
                if strcmp(e.rest_length.type,'parameter')
                    to.num_ineq=to.num_ineq+1;
                    to.ineq_const(to.num_ineq)=(e.rest_length.var-e.length.var);
                else
                    to.num_ineq=to.num_ineq+1;
                    to.ineq_const(to.num_ineq)=(e.length.var-e.rest_length.value(1));
                    to.num_ineq=to.num_ineq+1;
                    to.ineq_const(to.num_ineq)=(e.rest_length.var-e.length.var);
                    to.num_ineq=to.num_ineq+1;
                    to.ineq_const(to.num_ineq)=(e.rest_length.value(2)-e.rest_length.var);
                end
            end
        end
        % stress module constraint
        if strcmp(e.stiffness.type,'fixed')
            if strcmp(e.rest_length.type,'fixed')
                module=module+e.stiffness.value*e.stiffness.value*(e.length.var-e.rest_length.value)*(e.length.var-e.rest_length.value)/(e.length.var*e.length.var);
            else
                module=module+e.stiffness.value*e.stiffness.value*(e.length.var-e.rest_length.var)*(e.length.var-e.rest_length.var)/(e.length.var*e.length.var);
            end
        else
            if strcmp(e.rest_length.type,'fixed')
                module=module+e.stiffness.var*e.stiffness.var*(e.length.var-e.rest_length.value)*(e.length.var-e.rest_length.value)/(e.length.var*e.length.var);
            else
                module=module+e.stiffness.var*e.stiffness.var*(e.length.var-e.rest_length.var)*(e.length.var-e.rest_length.var)/(e.length.var*e.length.var);
            end
        end 
        mul=mul*e.length.var*e.length.var;
    end
    to.ineq_const(to.num_ineq+1)=simplify((module-sym('1'))*mul);
    to.num_ineq=to.num_ineq+1;
    % restriccions del centre de massa
    if tc.cm.num_nodes>0
%        if ~strcmp(tc.cm.position(1).type,'passive')
            if strcmp(tc.cm.position(1).type,'fixed')
                to.eq_const(to.num_eq+1)=sym(tc.cm.position(1).value);
            else
                to.eq_const(to.num_eq+1)=tc.cm.position(1).var;
            end
            for i=1:1:tc.cm.num_nodes
                index=getnodeindex(tc.tensegrity,tc.cm.nodes(i).name);
                n=tc.nodes(index);
                if strcmp(n.position(1).type,'fixed')
                    to.eq_const(to.num_eq+1)=to.eq_const(to.num_eq+1)-n.position(1).value/tc.cm.num_nodes;
                else
                    to.eq_const(to.num_eq+1)=to.eq_const(to.num_eq+1)-n.position(1).var/tc.cm.num_nodes;
                end
            end        
            to.eq_const(to.num_eq+1)=10*to.eq_const(to.num_eq+1);
            to.num_eq=to.num_eq+1;
%        end
%        if ~strcmp(tc.cm.position(2).type,'passive')
            if strcmp(tc.cm.position(2).type,'fixed')
                to.eq_const(to.num_eq+1)=sym(tc.cm.position(2).value);
            else
                to.eq_const(to.num_eq+1)=tc.cm.position(2).var;
            end
            for i=1:1:tc.cm.num_nodes
                index=getnodeindex(tc.tensegrity,tc.cm.nodes(i).name);
                n=tc.nodes(index);
                if strcmp(n.position(2).type,'fixed')
                    to.eq_const(to.num_eq+1)=to.eq_const(to.num_eq+1)-n.position(2).value/tc.cm.num_nodes;
                else
                    to.eq_const(to.num_eq+1)=to.eq_const(to.num_eq+1)-n.position(2).var/tc.cm.num_nodes;
                end
            end        
            to.eq_const(to.num_eq+1)=10*to.eq_const(to.num_eq+1);
            to.num_eq=to.num_eq+1;
%        end        
%        if ~strcmp(tc.cm.position(3).type,'passive')
            if strcmp(tc.cm.position(3).type,'fixed')
                to.eq_const(to.num_eq+1)=sym(tc.cm.position(3).value);
            else
                to.eq_const(to.num_eq+1)=tc.cm.position(3).var;
            end
            for i=1:1:tc.cm.num_nodes
                index=getnodeindex(tc.tensegrity,tc.cm.nodes(i).name);
                n=tc.nodes(index);
                if strcmp(n.position(3).type,'fixed')
                    to.eq_const(to.num_eq+1)=to.eq_const(to.num_eq+1)-n.position(3).value/tc.cm.num_nodes;
                else
                    to.eq_const(to.num_eq+1)=to.eq_const(to.num_eq+1)-n.position(3).var/tc.cm.num_nodes;
                end
            end        
            to.eq_const(to.num_eq+1)=10*to.eq_const(to.num_eq+1);
            to.num_eq=to.num_eq+1;
%        end        
        % restriccions de la orientació del centre de masses
        if ~strcmp(tc.cm.orientation(1).type,'passive') && ~strcmp(tc.cm.orientation(2).type,'passive') && ~strcmp(tc.cm.orientation(3).type,'passive') 
            for i=1:1:tc.cm.num_nodes
                index=getnodeindex(tc.tensegrity,tc.cm.nodes(i).name);
                n=tc.nodes(index);
                to.num_eq=to.num_eq+1;
                tmp=sym('0');
                if strcmp(n.position(1).type,'fixed')
                    if strcmp(tc.cm.position(1).type,'fixed')
                        tmp=n.position(1).value-tc.cm.position(1).value;
                    else
                        tmp=n.position(1).value-tc.cm.position(1).var;            
                    end
                else
                    if strcmp(tc.cm.position(1).type,'fixed')
                        tmp=n.position(1).var-tc.cm.position(1).value;            
                    else
                        tmp=n.position(1).var-tc.cm.position(1).var;            
                    end
                end
                if strcmp(tc.cm.orientation(1).type,'fixed')
                    tmp=tmp*tc.cm.orientation(1).value;
                else
                    tmp=tmp*tc.cm.orientation(1).var;        
                end
                to.eq_const(to.num_eq)=tmp;
                tmp=sym('0');
                if strcmp(n.position(2).type,'fixed')
                    if strcmp(tc.cm.position(2).type,'fixed')
                        tmp=n.position(2).value-tc.cm.position(2).value;
                    else
                        tmp=n.position(2).value-tc.cm.position(2).var;            
                    end
                else
                    if strcmp(tc.cm.position(2).type,'fixed')
                        tmp=n.position(2).var-tc.cm.position(2).value;            
                    else
                        tmp=n.position(2).var-tc.cm.position(2).var;            
                    end
                end
                if strcmp(tc.cm.orientation(2).type,'fixed')
                    tmp=tmp*tc.cm.orientation(2).value;
                else
                    tmp=tmp*tc.cm.orientation(2).var;        
                end
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+tmp;
                tmp=sym('0');
                if strcmp(n.position(3).type,'fixed')
                    if strcmp(tc.cm.position(3).type,'fixed')
                        tmp=n.position(3).value-tc.cm.position(3).value;
                    else
                        tmp=n.position(3).value-tc.cm.position(3).var;            
                    end
                else
                    if strcmp(tc.cm.position(3).type,'fixed')
                        tmp=n.position(3).var-tc.cm.position(3).value;            
                    else
                        tmp=n.position(3).var-tc.cm.position(3).var;            
                    end
                end
                if strcmp(tc.cm.orientation(3).type,'fixed')
                    tmp=tmp*tc.cm.orientation(3).value;
                else
                    tmp=tmp*tc.cm.orientation(3).var;        
                end
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+tmp;
            end
        end
    end
    % restriccions dels nodes coplanars
    for i=1:1:tc.num_cop_sets
        for j=1:1:tc.cop_sets(i).num_nodes
            index=getnodeindex(tc.tensegrity,tc.cop_sets(i).nodes(j).name);
            n=tc.nodes(index);
            to.num_eq=to.num_eq+1;
            tmp=sym('0');
            if strcmp(n.position(1).type,'fixed')
                if strcmp(tc.cop_sets(i).normal(1).type,'fixed')
                    tmp=n.position(1).value*tc.cop_sets(i).normal(1).value;
                else
                    tmp=n.position(1).value*tc.cop_sets(i).normal(1).var;
                end
            else
                if strcmp(tc.cop_sets(i).normal(1).type,'fixed')
                    tmp=n.position(1).var*tc.cop_sets(i).normal(1).value;      
                else
                    tmp=n.position(1).var*tc.cop_sets(i).normal(1).var;
                end
            end
            to.eq_const(to.num_eq)=tmp;
            tmp=sym('0');
            if strcmp(n.position(2).type,'fixed')
                if strcmp(tc.cop_sets(i).normal(2).type,'fixed')
                    tmp=n.position(2).value*tc.cop_sets(i).normal(2).value;
                else
                    tmp=n.position(2).value*tc.cop_sets(i).normal(2).var;
                end
            else
                if strcmp(tc.cop_sets(i).normal(2).type,'fixed')
                    tmp=n.position(2).var*tc.cop_sets(i).normal(2).value;      
                else
                    tmp=n.position(2).var*tc.cop_sets(i).normal(2).var;
                end
            end
            to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+tmp;
            tmp=sym('0');
            if strcmp(n.position(3).type,'fixed')
                if strcmp(tc.cop_sets(i).normal(3).type,'fixed')
                    tmp=n.position(3).value*tc.cop_sets(i).normal(3).value;
                else
                    tmp=n.position(3).value*tc.cop_sets(i).normal(3).var;
                end
            else
                if strcmp(tc.cop_sets(i).normal(3).type,'fixed')
                    tmp=n.position(3).var*tc.cop_sets(i).normal(3).value;      
                else
                    tmp=n.position(3).var*tc.cop_sets(i).normal(3).var;
                end
            end
            to.eq_const(to.num_eq)=to.eq_const(to.num_eq)+tmp;
            if strcmp(tc.cop_sets(i).dist.type,'fixed')
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)-tc.cop_sets(i).dist.value;
            else
                to.eq_const(to.num_eq)=to.eq_const(to.num_eq)-tc.cop_sets(i).dist.var;            
            end
        end
    end
    % restriccions de colisió
%     pc0x=tenvar('parameter','pc0x',0);
%     to.const=addvariable(to.const,pc0x);
%     pc0y=tenvar('parameter','pc0y',0);
%     to.const=addvariable(to.const,pc0y);
%     pc0z=tenvar('parameter','pc0z',0);
%     to.const=addvariable(to.const,pc0z);
%     pc0=[pc0x.var,pc0y.var,pc0z.var];
%     pc1x=tenvar('parameter','pc1x',0);
%     to.const=addvariable(to.const,pc1x);
%     pc1y=tenvar('parameter','pc1y',0);
%     to.const=addvariable(to.const,pc1y);
%     pc1z=tenvar('parameter','pc1z',0);
%     to.const=addvariable(to.const,pc1z);
%     pc1=[pc1x.var,pc1y.var,pc1z.var];
%     v=pc1-pc0;
%     c=v*v.';
%     rc=tenvar('parameter','rc',0);
%     to.const=addvariable(to.const,rc);
%     for i=1:1:tc.num_edges
%         if strcmp(tc.edges(i).type,'strut')
%             to.num_ineq=to.num_ineq+1;           
%             org_index=getnodeindex(tc.tensegrity,tc.edges(i).origin);
%             end_index=getnodeindex(tc.tensegrity,tc.edges(i).end);
%             n_o=tc.nodes(org_index);
%             n_e=tc.nodes(end_index);
%             e=tc.edges(i);
%             if strcmp(n_e.position(1).type,'fixed')
%                 if strcmp(n_o.position(1).type,'fixed')
%                     u(1)=n_e.position(1).value-n_o.position(1).value;
%                 else
%                     u(1)=n_e.position(1).value-n_o.position(1).var;
%                 end
%             else
%                 if strcmp(n_o.position(1).type,'fixed')
%                     u(1)=n_e.position(1).var-n_o.position(1).value;
%                 else
%                     u(1)=n_e.position(1).var-n_o.position(1).var;
%                 end
%             end
%             if strcmp(n_e.position(2).type,'fixed')
%                 if strcmp(n_o.position(2).type,'fixed')
%                     u(2)=n_e.position(2).value-n_o.position(2).value;
%                 else
%                     u(2)=n_e.position(2).value-n_o.position(2).var;
%                 end
%             else
%                 if strcmp(n_o.position(2).type,'fixed')
%                     u(2)=n_e.position(2).var-n_o.position(2).value;
%                 else
%                     u(2)=n_e.position(2).var-n_o.position(2).var;
%                 end
%             end
%             if strcmp(n_e.position(3).type,'fixed')
%                 if strcmp(n_o.position(3).type,'fixed')
%                     u(3)=n_e.position(3).value-n_o.position(3).value;
%                 else
%                     u(3)=n_e.position(3).value-n_o.position(3).var;
%                 end
%             else
%                 if strcmp(n_o.position(3).type,'fixed')
%                     u(3)=n_e.position(3).var-n_o.position(3).value;
%                 else
%                     u(3)=n_e.position(3).var-n_o.position(3).var;
%                 end
%             end
%             if strcmp(n_o.position(1).type,'fixed')
%                 w0(1)=n_o.position(1).value-pc0(1);
%             else
%                 w0(1)=n_o.position(1).var-pc0(1);
%             end
%             if strcmp(n_o.position(2).type,'fixed')
%                 w0(2)=n_o.position(2).value-pc0(2);
%             else
%                 w0(2)=n_o.position(2).var-pc0(2);
%             end
%             if strcmp(n_o.position(3).type,'fixed')
%                 w0(3)=n_o.position(3).value-pc0(3);
%             else
%                 w0(3)=n_o.position(3).var-pc0(3);
%             end
%             a=u*u.';
%             b=u*v.';
%             d=u*w0.';
%             f=v*w0.';
%             dist=w0*(a*c-b*b)+((b*f-c*d)*u-(a*f-b*d)*v);
%             rb=tenvar('parameter',['rb_',e.name],0);
%             to.const=addvariable(to.const,rb);
%             to.ineq_const(to.num_ineq)=dist*dist.'-(a*c-b*b)*(a*c-b*b)*(rc.var+rb.var)*(rc.var+rb.var);
%         end
%     end
catch
    rethrow(lasterror);
end
