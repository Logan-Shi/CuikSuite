function display(v)

for i=1:1:size(v,2)
    disp(['--- variable ',v(i).name,' ---']);
    disp(['type:    ',v(i).type]);
    if size(v(i).value,1)>1
        disp(['limits:   (',num2str(v(i).value(1)),',',num2str(v(i).value(2)),')']);    
    else
        disp(['value:   ',num2str(v(i).value)]);
    end
end
