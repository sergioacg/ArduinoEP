function dTdt = energy_bal(time,T,Q,alpha,Ta,U)

% temperature State
m = 4e-3;               % Kg
Cp =  500;              % J/Kg K= 12 / 100^2 Area in m^2
eps = 0.9;              % Emissivity
sigma = 5.67e-8;        % Stefan-Boltzman
A = 1.2e-3;             % Area (m^2)

%% non-linear energy balance
dTdt = (1.0/(m*Cp))*(U*A*(Ta-T)...
    + eps * sigma * A * (Ta^4 - T^4)...
    + alpha * Q);
end
