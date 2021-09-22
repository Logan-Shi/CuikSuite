function display(e)

for i=1:1:size(e,2)
    disp(['--- edge ',e(i).name,' ---']);
    disp(['type:        ',e(i).type]);
    disp(['origin node: ',e(i).origin]);
    disp(['end node:    ',e(i).end]);
end