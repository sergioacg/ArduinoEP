clc
clear 
close all

T0 = 24 + 273.15;       % K
Ta = 24 + 273.15;       % K
Qi=0;                  % Porcentaje
alpha = 0.014;           % W / % heater
Cp =  500;              % J/Kg K= 12 / 100^2 Area in m^2
A = 1.2e-3;             % Area (m^2)
m = 4e-3;               % Kg
U = 5.0;               % W/m^2 K
eps = 0.9;              % Emissivity
sigma = 5.67e-8;        % Stefan-Boltzman

Qi=0:5:100;

for k=1:length(Qi)
    %Equilibrio
    [Ts] = T_ss(eps,sigma,A,U,Qi(k),Ta,alpha);
   T(k)=Ts;
end

plot(Qi,T-273.15,'linewidth',2)
xlabel('Qi (%)');
ylabel('T (C)')

Qi=0;                  % Porcentaje
[Ts,TC] = T_ss(eps,sigma,A,U,Qi,Ta,alpha);
num= alpha/(m*Cp);
den=[1 (U*A+4*eps*sigma*A*Ts^3)/(m*Cp)];
G=tf(num,den)
G=tf(num/den(2),den/den(2))

du=Qi+40;
%% Comparación con modelo No Lineal
[tsim, Tnl] = ode45(@(tsim,x)energy_bal(tsim,x,du,...
        alpha,Ta,U), [0 1000], Ts);
u(1:length(tsim))=du;
Tl=lsim(G,u,tsim);

figure
plot(tsim, Tnl-273.15,tsim,Tl+T0-273.15,'--r','linewidth',2)
xlabel('t (s)');
ylabel('T (C)')
legend('Modelo No Lineal', 'Modelo lineal','Location','southeast')