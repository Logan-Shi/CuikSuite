function Ti_1i = DH(ai_1,alfai_1,di,thetai)

cti=cos(thetai);
sti=sin(thetai);
cai_1=cos(alfai_1);
sai_1=sin(alfai_1);

Ti_1i = [cti       -sti      0      ai_1; 
         sti*cai_1 cti*cai_1 -sai_1 -sai_1*di;
         sti*sai_1 cti*sai_1 cai_1  cai_1*di;
         0         0         0      1       ];
