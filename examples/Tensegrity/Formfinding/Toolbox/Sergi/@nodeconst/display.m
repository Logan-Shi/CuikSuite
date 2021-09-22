function display(nc)

display(nc.node);
display(nc.position(1));
display(nc.position(2));
display(nc.position(3));
disp(['Num. of external forces: ',num2str(nc.num_forces)]);
for i=1:1:nc.num_forces
    display(nc.forces(i,1));
    display(nc.forces(i,2));
    display(nc.forces(i,3));    
end

