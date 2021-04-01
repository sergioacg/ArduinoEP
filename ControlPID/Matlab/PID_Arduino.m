clc
clear 
close all

Ts=8; %Periodo de Muestreo
m1 = menu('Control PID Arduino', 'Ziegler y Nichols', 'Cancelamiento de Polos',...
    'Asignación de Polos');
%Modelo del Proceso
k=1.04;tau=160;theta1=10;
theta = theta1 + Ts/2;

G=tf(k,[tau 1]);
G.iodelay = theta1;

%Discretización de la planta
Gd = c2d(G,Ts,'zoh');

switch(m1)
    case 1
        %Control PID por Ziegler y Nichols
        kp=(1.2*tau)/(k*theta);
        ti=2*theta;
        td=0.5*theta;
        incontrolabilidad = theta / tau
    case 2
        %Control PID por Cancelamiento de polos
        tau_d=45;                 
        kp=(tau)/(tau_d*k);         
        ti=tau;                  
        td=0;
    case 3
        %Control PID por Asignación de Polos
        % Especificaciones de Diseño
        Mp=5; %Maximo Pico
        ep=sqrt(((log(Mp/100))^2)/(pi^2+((log(Mp/100))^2))); %Fator de amortiguamiento
%         ep=1;
        Tlc=220; 
        if ep<1
            Wn=4/(ep*Tlc); 
        else if ep==1
                Wn=5.8335/Tlc;
            end
        end


        P1=2.0*ep*Wn;
        P2=Wn^2;

        kp=(P1*tau-1)/k;        
        ti=(k*kp)/(P2*tau);
        td=0;
end

% Calculo do controle PID digital
q0=kp*(1+Ts/(2*ti)+td/Ts);
q1=-kp*(1-Ts/(2*ti)+(2*td)/Ts);
q2=(kp*td)/Ts;

% Loop de Control
nit=63;
u(1:nit)=0;
r(1:nit)=0;
r(6:nit)=40;
y(1:nit)=25.5;
e=r-y;
T0 = 25.5 + 273.15;       % K
Ta = 25.5 + 273.15;       % K
Qi=0;                  % Porcentaje
alpha = 0.014;           % W / % heater
Cp =  500;              % J/Kg K= 12 / 100^2 Area in m^2
A = 1.2e-3;             % Area (m^2)
m = 4e-3;               % Kg
U = 5.0;               % W/m^2 K
eps = 0.9;              % Emissivity
sigma = 5.67e-8;        % Stefan-Boltzman
[x0,Tc] = T_ss(eps,sigma,A,U,0,Ta,alpha);
d = round(theta1/Ts);
for k=3:nit
%     %Modelo Lineal
     t = 0:Ts:(k-1)*Ts;
     y=lsim(G,u(:,1:k),t,'zoh')'+25.5;
     
    
%Modelo NO Lineal
%     t=((k-1):1:k)*Ts;
%     [tsim, Temp] = ode15s(@(tsim,x)energy_bal(tsim,x,u(k-1-d),...
%         alpha,Ta,U), t, x0);
%     x0 = Temp(end,:);    
%     y(k)=x0-273.15;
    
     %Error
     e(k)=r(k)-y(k);
     
     %PID
     u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2);
     
     if (u(k) >= 100.0)     
        u(k) = 100.0;
     end
     if (u(k) <= 0.0)
         u(k) = 0.0;
     end
     
end

t=0:Ts:(nit-1)*Ts;
figure(1)
subplot(211)
plot(t,r,'--r',t,y,'-k','linewidth',2),grid
xlabel('t(s)');
ylabel('T(C)');
legend('Setpoint','Temperatura','location','southeast')
subplot(212)
stairs(t,u,'-k','linewidth',2),grid
xlabel('t(s)');
ylabel('Q(%)');