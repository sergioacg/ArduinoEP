% Comparar Gráficas Reales con Simuladas

PID_Arduino
switch(m1)
    case 1
        %Control PID por Ziegler y Nichols
        load('ZN_Final.mat')
        subplot(2,1,1)
        hold on
        plot(ts,ys,'-b','linewidth',3)
        legend('Setpoint','Simulado','Real','location','southeast')
        subplot(2,1,2)
        hold on
        stairs(ts,us,'-b','linewidth',3)
    case 2
        %Control PID por Cancelamiento de polos
        load('CP_Final.mat')
        subplot(2,1,1)
        hold on
        plot(ts,ys,'-b','linewidth',3)
        legend('Setpoint','Simulado','Real','location','southeast')
        subplot(2,1,2)
        hold on
        stairs(ts,us,'-b','linewidth',3)
    case 3
        %Control PID por Asignación de Polos
        load('AP_Final.mat')
        subplot(2,1,1)
        hold on
        plot(ts,ys,'-b','linewidth',3)
        legend('Setpoint','Simulado','Real','location','southeast')
        subplot(2,1,2)
        hold on
        stairs(ts,us,'-b','linewidth',3)
end
