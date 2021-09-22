function to_sol=get_solution(to,parameters,solution)
try
    num_par=0;
    num_opt=0;
    to_sol=tenconst(to.const);
    [to_sol,num_var,var]=getvariables(to_sol);
    % substitute the parameter values
    for i=1:1:num_var
        if ~strcmp(var(i).type,'fixed')
            if strcmp(var(i).type,'parameter')
                num_par=num_par+1;
                var(i).type='fixed';
                var(i).value=parameters(num_par);
                to_sol=setvariable(to_sol,i,var(i));
            else
                num_opt=num_opt+1;
                var(i).type='fixed';
                var(i).value=to.solution(num_opt);
                to_sol=setvariable(to_sol,i,var(i));
            end
        end
    end
    vars=getoptvars(to);
    % substitute the variables values
    for i=1:1:to_sol.num_edges
        for j=1:1:size(vars,2)
            if ~strcmp(to_sol.edges(i).stiffness.type,'fixed') && ~strcmp(to_sol.edges(i).stiffness.type,'parameter')
                if(strcmp(vars(j).name,to_sol.edges(i).stiffness.name))
                    to_sol.edges(i).stiffness.type='fixed';
                    to_sol.edges(i).stiffness.value=solution(j);
                end
            end
            if ~strcmp(to_sol.edges(i).rest_length.type,'fixed') && ~strcmp(to_sol.edges(i).rest_length.type,'parameter')
                if(strcmp(vars(j).name,to_sol.edges(i).rest_length.name))
                    to_sol.edges(i).rest_length.type='fixed';
                    to_sol.edges(i).rest_length.value=solution(j);
                end
            end
            if ~strcmp(to_sol.edges(i).length.type,'fixed') && ~strcmp(to_sol.edges(i).length.type,'parameter')
                if(strcmp(vars(j).name,to_sol.edges(i).length.name))
                    to_sol.edges(i).length.type='fixed';
                    to_sol.edges(i).length.value=solution(j);
                end
            end
        end
    end
    for i=1:1:to_sol.num_nodes
        for j=1:1:size(vars,2)
            if ~strcmp(to_sol.nodes(i).position(1).type,'fixed') && ~strcmp(to_sol.nodes(i).position(1).type,'parameter')
                if(strcmp(vars(j).name,to_sol.nodes(i).position(1).name))
                    to_sol.nodes(i).position(1).type='fixed';
                    to_sol.nodes(i).position(1).value=solution(j);
                end
            end
            if ~strcmp(to_sol.nodes(i).position(2).type,'fixed') && ~strcmp(to_sol.nodes(i).position(2).type,'parameter')
                if(strcmp(vars(j).name,to_sol.nodes(i).position(2).name))
                    to_sol.nodes(i).position(2).type='fixed';
                    to_sol.nodes(i).position(2).value=solution(j);
                end
            end
            if ~strcmp(to_sol.nodes(i).position(3).type,'fixed') && ~strcmp(to_sol.nodes(i).position(3).type,'parameter')
                if(strcmp(vars(j).name,to_sol.nodes(i).position(3).name))
                    to_sol.nodes(i).position(3).type='fixed';
                    to_sol.nodes(i).position(3).value=solution(j);
                end
            end
        end
    end
    
catch
    rethrow(lasterror);
end
