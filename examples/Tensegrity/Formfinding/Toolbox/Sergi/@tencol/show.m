function tcol=show(tcol,parameters)
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
    tcol.tenopt=show(tcol.tenopt,parameters);
    hold on;
    te=tcol.tenopt.const;
    for i=1:1:te.num_planes
        z1=parameters(10)-parameters(5)/parameters(7)*(-0.5-parameters(8))-parameters(6)/parameters(7)*(-0.5-parameters(9));
        p1=[-0.5,-0.5,z1];
        z2=parameters(10)-parameters(5)/parameters(7)*(-0.5-parameters(8))-parameters(6)/parameters(7)*(0.5-parameters(9));
        p2=[-0.5,0.5,z2];
        z3=parameters(10)-parameters(5)/parameters(7)*(0.5-parameters(8))-parameters(6)/parameters(7)*(0.5-parameters(9));
        p3=[0.5,0.5,z3];
        z4=parameters(10)-parameters(5)/parameters(7)*(0.5-parameters(8))-parameters(6)/parameters(7)*(-0.5-parameters(9));
        p4=[0.5,-0.5,z4];
        fill3([p1(1) p2(1) p3(1) p4(1)],[p1(2) p2(2) p3(2) p4(2)],[p1(3) p2(3) p3(3) p4(3)],[0.5,0.5,0.5,0.5]);
        alpha(0.5);        
%        line([parameters(8) parameters(8)+parameters(5)],[parameters(9) parameters(9)+parameters(6)],[parameters(10) parameters(10)+parameters(7)],'Color','green','LineWidth',3);
    end
   hold off
    xlim([-0.6 0.6]);
    ylim([-0.6 0.6]);
    zlim([0 1]);    
    camtarget([0 0 0]);
    campos([10 0 3]);
catch
    rethrow(lasterror);
end
