function [nenv,ef]=readnodeenv(ef,nenv)

if isa(ef,'envfile')
    FrictionTxt='Friction:';
    try
        [nenv.friction,ef]=readfieldreal(ef,FrictionTxt);
    catch
        rethrow(lasterror);
    end
else
    error('tenenv - Invalid tensegrity environment file');
end
