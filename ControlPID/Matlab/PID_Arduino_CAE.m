%% Ejemplo Monitoreo de señales en tiempo Real
function varargout=PID_Arduino_CAE(varargin)
parar=false;
fclose('all')
global tiempo salida escalon control
fig(1)=figure('name','Monitor','menubar','none','position',[200 200 800 700],'color',[0.9 0.6 0.3])
movegui(fig(1),'center');
axe(1)=axes('parent',fig(1),'units','pixels','position',[60 380 600 280],'xlim',[0 40],'ylim',[20 50],'xgrid','on','ygrid','on')
axe(2)=axes('parent',fig(1),'units','pixels','position',[60 50 600 280],'xlim',[0 40],'ylim',[0 100],'xgrid','on','ygrid','on')

set(get(axe(1),'XLabel'),'String','Tiempo (Seg)')
set(get(axe(1),'YLabel'),'String','Temperatura (°C)')

set(get(axe(2),'XLabel'),'String','Tiempo (Seg)')
set(get(axe(2),'YLabel'),'String','Control (%)')

lin(1)=line('parent',axe(1),'xdata',[],'ydata',[],'Color','r','LineWidth',2.5);
lin(2)=line('parent',axe(1),'xdata',[],'ydata',[],'Color','k','LineWidth',2);
lin(3)=line('parent',axe(2),'xdata',[],'ydata',[],'Color','r','LineWidth',2.5);

Texto(1)=uicontrol('parent',fig(1),'style','text','string','Puerto','position',[680 630 100 50],'BackgroundColor',[0.9 0.6 0.3],'fontsize',18);
Texto(2)=uicontrol('parent',fig(1),'style','text','string','Setpoint','position',[680 280 100 50],'BackgroundColor',[0.9 0.6 0.3],'fontsize',18);
Texto(3)=uicontrol('parent',fig(1),'style','text','string','Grafico','position',[680 450 100 50],'BackgroundColor',[0.9 0.6 0.3],'fontsize',18);

bot(1)=uicontrol('parent',fig(1),'style','pushbutton','string','Detener','position',[680 50 100 50],'callback',@stop,'fontsize',11)
bot(2)=uicontrol('parent',fig(1),'style','pushbutton','string','Enviar','position',[680 200 100 50],'callback',@enviar,'fontsize',11)
bot(3)=uicontrol('parent',fig(1),'style','pushbutton','string','Salvar','position',[680 400 100 50],'callback',@salvar,'fontsize',11)

txbx(1)=uicontrol('parent',fig(1),'style','tex','string','Temp','position',[680 100 100 50],'fontsize',11)
txbx(2)=uicontrol('parent',fig(1),'style','edit','string','000','position',[680 250 100 50],'fontsize',11)


ports = serialportlist; %Para MATLAB 2019b en adelante
% ports = seriallist;
if isempty(ports)
  ports ='NONE';
end
puerta =ports(1);

popup = uicontrol('parent',fig(1),'Style', 'popup',...
           'String', ports,...
           'Position', [680 600 100 50],'fontsize',15,...
           'Callback', @puertas); 

%% Funcion Pare
    function varargout=stop(hObject,evendata)
        parar=true;
        fclose(SerialP);
        delete(SerialP);
        clear SerialP;
        
    end

%% Funcion enviar
    function varargout=enviar(hObject,evendata)
        deg1=get(txbx(2),'string');
        %Se asegura de hacer que deg1 tenga 3 caracteres
        while(strlength(deg1)<3)
            deg1=["0"+deg1];
        end
        
        deg=["S"+deg1+"$"];
        fwrite(SerialP,deg,'uchar');
    end
 %% Funcion Puerto
    function varargout=puertas(hObject,evendata)
        puerta=popup;
    end
%% Funcion Salvar
    function varargout=salvar(hObject,evendata)
        %Renombra variables
        
        rs=escalon;
        us=control;
        ys=salida;
        ts=tiempo;
        save('Datos.mat','ts','rs','ys','us')
        figure
        subplot(2,1,1);
        plot(ts,rs,ts,ys,'linewidth',3),grid
        
        title('Laboratorio de Temperatura')
        xlabel('Tiempo (s)')
        ylabel('Temperatura (C)')

        subplot(2,1,2);
        plot(ts,us,'linewidth',3),grid
        xlabel('Tiempo (s)')
        ylabel('Control (%)')
    end
    %% funcion Graficar
   % function varargout=grafique(hObject,evendata)
        tiempo=[0];
        salida=[25];
        escalon=[0];
        control=[0];
        deg1="0";
   
        dt=1;
        limx=[0 40];
        limy=[20 50];
        set(axe(1),'xlim',limx,'ylim',limy);
        
        
    %% Configura el Puerto Serial
    
    SerialP=serial(puerta);
    set(SerialP,'Baudrate',9600); % se configura la velocidad a 9600 Baudios
    set(SerialP,'StopBits',1); % se configura bit de parada a uno
    set(SerialP,'DataBits',8); % se configura que el dato es de 8 bits, debe estar entre 5 y 8
    set(SerialP,'Parity','none'); % se configura sin paridad

    fopen(SerialP);
              
     %% Grafico
     k=5;nit = 10000;
        while(~parar)
%             if get(bot(3),'value')
%                drawnow(); % necesario para que actualice el grafico
%                continue % forza a salir del while para  la proxima interacion y de esta forma nop actualizo datos
%             
%             end


            % Lectura del Dato por Puerto Serial
            variable= (fread(SerialP,30,'uchar'));
            ini=find(variable==73); %Busca el I (Primer dato)
            ini=ini(1)+1;
            fin=find(variable==70); %Busca F (ultimo dato)
            fin= fin(find(fin>ini))-1;
            fin=fin(1);
            tempC=char(variable(ini:fin))';
            temp=str2num(tempC);
            
            %Lectura de la senal de control
            ini=find(variable==67); %Busca el C (Primer dato)
            ini=ini(1)+1;
            fin=find(variable==82); %Busca R (ultimo dato)
            fin= fin(find(fin>ini))-1;
            fin=fin(1);
            Con1=char(variable(ini:fin))';
            cont=str2num(Con1);
            
            
            set(txbx(1),'string',tempC);
            %Actualiza las variables del grafico
           
             tiempo=[tiempo tiempo(end)+dt];
             salida=[salida temp];
             control=[control cont];
             escalon=[escalon str2num(deg1)];
             set(lin(1),'xdata',tiempo,'ydata',salida);
             set(lin(2),'xdata',tiempo,'ydata',escalon);
             set(lin(3),'xdata',tiempo,'ydata',control);
             pause(dt); %% espera 1 seg para cada interación
             if tiempo(end)>=limx % actualizo grafica cuando llega a su limite en tiempo real
             limx=[0 limx(2)+40];
             set(axe(1),'xlim',limx) ;
             set(axe(2),'xlim',limx); 
             end
             
             if salida(end)>=limy % actualizo grafica cuando llega a su limite en tiempo real
             limy=[20 limy(2)+5];
             set(axe(1),'ylim',limy); 
             end
             
             k=k+1;
             if(k==nit)
                 parar=true;
             end
        end
        parar=false;
        

   % end
end
