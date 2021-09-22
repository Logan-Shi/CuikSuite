function to=show(to,parameters)
% shows a tensegrity structure with the current solution
% this function displays on screen the current tensegrity topology with the
% most recent stable configuration if any. 
%
% to=show(to,parameters) shows on screen the most recent tensegrity
% configuration with the parameters specified by the input argument
% parameters.
%
% The tenopt object must be initialized before calling this function and it
% must have a valid solution for the configuration of the tensegrity.
%
% See also tenopt, tenconst

% fer una copia 
try
    newplot
    num_par=0;
    num_opt=0;
    showten=tenconst(to.const);
    [showten,num_var,var]=getvariables(showten);
    for i=1:1:num_var
        if ~strcmp(var(i).type,'fixed')
            if strcmp(var(i).type,'parameter')
                num_par=num_par+1;
                var(i).type='fixed';
                var(i).value=parameters(num_par);
                showten=setvariable(showten,i,var(i));
            else
                num_opt=num_opt+1;
                var(i).type='fixed';
                var(i).value=to.solution(num_opt);
                showten=setvariable(showten,i,var(i));
            end
        end
    end
    % draw the edges
    for i=1:1:showten.num_edges
        name=showten.edges(i).origin;
        n_o=showten.nodes(name);
        name=showten.edges(i).end;
        n_e=showten.nodes(name);
        if strcmp(showten.edges(i).type,'cable')
            color='red';
            width=1;
        else
            color='blue';
            width=3;
        end
        line([n_o.position(1).value n_e.position(1).value],[n_o.position(2).value n_e.position(2).value],[n_o.position(3).value n_e.position(3).value],'Color',color,'LineWidth',width,'LineStyle','-');
        if i==1
            if n_o.position(1).value > n_e.position(1).value 
                x=[n_e.position(1).value n_o.position(1).value];
            else
                x=[n_o.position(1).value n_e.position(1).value];                
            end
            if n_o.position(2).value > n_e.position(2).value 
                y=[n_e.position(2).value n_o.position(2).value];
            else
                y=[n_o.position(2).value n_e.position(2).value];                
            end
            if n_o.position(3).value > n_e.position(3).value 
                z=[n_e.position(3).value n_o.position(3).value];
            else
                z=[n_o.position(3).value n_e.position(3).value];                
            end
        else
            if n_o.position(1).value < x(1)
                x(1)=n_o.position(1).value; 
            else
                if n_o.position(1).value > x(2)
                    x(2)=n_o.position(1).value;
                end
            end
            if n_e.position(1).value < x(1)
                x(1)=n_e.position(1).value; 
            else
                if n_e.position(1).value > x(2)
                    x(2)=n_e.position(1).value;
                end
            end
            if n_o.position(2).value < y(1)
                y(1)=n_o.position(2).value; 
            else
                if n_o.position(2).value > y(2)
                    y(2)=n_o.position(2).value;
                end
            end
            if n_e.position(2).value < y(1)
                y(1)=n_e.position(2).value; 
            else
                if n_e.position(2).value > y(2)
                    y(2)=n_e.position(2).value;
                end
            end
            if n_o.position(3).value < z(1)
                z(1)=n_o.position(3).value; 
            else
                if n_o.position(3).value > z(2)
                    z(2)=n_o.position(3).value;
                end
            end
            if n_e.position(3).value < z(1)
                z(1)=n_e.position(3).value; 
            else
                if n_e.position(3).value > z(2)
                    z(2)=n_e.position(3).value;
                end
            end
            
        end
    end
    % draw the froces
%     xlim([x(1)*1.1 x(2)*1.1]);
%     ylim([y(1)*1.1 y(2)*1.1]);
%     zlim([z(1)*1.1 z(2)*1.1]);    
    camtarget([0 0 0]);
    campos([10 10 10]);
catch
    rethrow(lasterror);
end
