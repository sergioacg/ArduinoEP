%Graficar Control del Horno
load('SP3.mat')

%Renombra variables
rs=escalon;
us=control;
ys=salida;
ts=tiempo;

subplot(2,1,1);
plot(ts,rs,ts,ys,'linewidth',3),grid
title('Laboratorio de Temperatura')
xlabel('Tiempo (s)')
ylabel('Temperatura (C)')

subplot(2,1,2);
plot(ts,us,'linewidth',3),grid
xlabel('Tiempo (s)')
ylabel('Control (%)')