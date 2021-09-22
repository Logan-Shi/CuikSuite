function CombineSerial(fname,o,min_force)

  f_manip=[fname '_with_contacts_with_eigens_index1.cost'];

  
  f_force=[fname '_with_contacts_with_eigens_ffc.cost'];
  fprintf('Reading force closure information  : %s\n',f_force);
  force=load(f_force);

  fprintf('Reading manipulabiity information  : %s\n',f_manip);
  manip=load(f_manip);
  
  
  if o
    f_obs  =[fname '_kin_contacts_eigens_collision.cost'];
    fprintf('\nReading collision information      : %s\n',f_obs);
    obs=load(f_obs);
    
    % Remove configurations that are in collisions
    wrongObs=(obs<0.5);
    manip(wrongObs)=0;
  else
    fprintf('Not considering collisions\n');
    wrongObs=false(size(manip));
  end
  
  % Remove configurations that are not (enough) force
  % closed 
  wrongForce=(force<min_force);
  manip(wrongForce)=0;
  
  % optimize only on the good ones
  wrong=(wrongObs|wrongForce);
  valid=(~wrong);
  
  % avoid zeros (they are just not displayed)
  manip(wrong)=1e-5;
  
  % Identify the worst and best grasps
  [mi mi_ndx]=min(manip(valid));
  fprintf('Worst grasp                        : %u\n',mi_ndx);

  [ma ma_ndx]=max(manip(valid));
  fprintf('Optimal grasp                      : %u\n',ma_ndx);
  
  % Scale the non-zeros to [1e-3 to 1]
  offset=1e-3;
  manip(valid)=(ma-manip(valid))/(ma-mi)*(offset-1)+1;
  
  % Save the result
  f_combined=[fname '_with_contacts_with_eigens_serial_combined.cost'];      
  fprintf('Writing combined result to         : %s\n',f_combined);
  save(f_combined,'manip','-ascii');
  
  exit
  
  

