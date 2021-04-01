%% Ejemplo Monitoreo de señales en tiempo Real
function varargout=monitoreo(varargin)
parar=false;
fclose('all')
global tiempo salida escalon control
fig(1)=figure('name','Monitor','menubar','none','position',[200 200 800 700],'color',[0.9 0.6 0.3]);
movegui(fig(1),'center');

%Texto del Titulo
Texto(1)=uicontrol('parent',fig(1),'style','text','string','Interfaz PIC - USB_CDC','position',[200 600 400 50],'BackgroundColor',[0.9 0.6 0.3],'fontsize',25);

%Botones para prender y apagar LEDS
led(1)=uicontrol('parent',fig(1),'style','pushbutton','string','LED 1','BackgroundColor',[0 0 1],'ForegroundColor',[1 1 1],'position',[150 400 200 100],'callback',@led1,'fontsize',15);
led(2)=uicontrol('parent',fig(1),'style','pushbutton','string','LED 2','BackgroundColor',[1 1 0],'position',[450 400 200 100],'callback',@led2,'fontsize',15);

%ports = serialportlist; %Para MATLAB 2019b en adelante
ports = seriallist;
puerta =ports(1);

popup = uicontrol('parent',fig(1),'Style', 'popup',...
           'String', ports,...
           'Position', [300 475 200 100],'fontsize',15,...
           'Callback', @puertas); 
       
axe(1)=axes('parent',fig(1),'units','pixels','position',[60 50 600 280],'xlim',[0 40],'ylim',[0 5],'xgrid','on','ygrid','on');

set(get(axe(1),'XLabel'),'String','Tiempo (Seg)');
set(get(axe(1),'YLabel'),'String','Voltaje (v)');

lin(1)=line('parent',axe(1),'xdata',[],'ydata',[],'Color','r','LineWidth',2.5);

bot(1)=uicontrol('parent',fig(1),'style','pushbutton','string','Detener','position',[680 50 100 50],'callback',@stop,'fontsize',11);


txbx(1)=uicontrol('parent',fig(1),'style','tex','string','Voltaje','position',[680 100 100 50],'fontsize',11);



%% Funcion Pare
    function varargout=stop(hObject,evendata)
        parar=true;
        fclose(SerialP);
        delete(SerialP);
        clear SerialP;
        
    end

%% Funcion LED1
    function varargout=led1(hObject,evendata)
        fwrite(SerialP,"S101$",'uchar');
    end
%% Funcion LED2
    function varargout=led2(hObject,evendata)
        fwrite(SerialP,"S102$",'uchar');
    end
%% Funcion Puerto
    function varargout=puertas(hObject,evendata)
        puerta=popup;
    end
    %% funcion Graficar
   % function varargout=grafique(hObject,evendata)
        tiempo=[0];
        salida=[0];
          
        dt=1; %Grafica cada 1 segundo
        limx=[0 40];
        limy=[0 5];
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
            voltC=char(variable(ini:fin))';
            voltios=str2num(voltC);
            
            
            set(txbx(1),'string',voltC);
            %Actualiza las variables del grafico
           
             tiempo=[tiempo tiempo(end)+dt];
             salida=[salida voltios];
 
             set(lin(1),'xdata',tiempo,'ydata',salida);
             
             pause(dt); %% espera 1 seg para cada interación
             if tiempo(end)>=limx % actualizo grafica cuando llega a su limite en tiempo real
             limx=[0 limx(2)+40];
             set(axe(1),'xlim',limx) ;
             end
             
             if salida(end)>=limy % actualizo grafica cuando llega a su limite en tiempo real
             limy=[0 limy(2)+0.1];
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
