function display(to)

disp(['penalty: (',num2str(to.penalty(1)),',',num2str(to.penalty(2)),')']);
disp(['penalty update function: ',func2str(to.penalty_update_h)]);
disp(['beta: ',num2str(to.beta)]);
disp(['s: ',num2str(to.s)]);
disp(['sigma: ',num2str(to.sigma)]);
disp(['tolerance: ',num2str(to.tolerance)]);