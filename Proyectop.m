
instrreset % reset todos los puertos serie de la PC
clear all
close all
clc

s = serial('COM9'); % cambiar este por el puerto COM en el que se encuentre el ESP32
set(s,'BaudRate',115200); % baud rate - debe coincidir con el del ESP32
fopen(s); % abre la comunicación entre Arduino y MATLAB
plot_len = 500; % tamaño de la ventana de datos en la gráfica
x_vals = linspace(0,plot_len,plot_len); % valores del eje -x
plot_var = zeros(plot_len,1); % inicializa con ceros
plot_var2 = zeros(plot_len,1); % inicializa con ceros
plot_var3 = zeros(plot_len,1); % inicializa con ceros

% configuración de figura
f1 = figure();
xlabel('Muestra')
ylabel('Amplitud')

grid('on')
hold on

loop_break = true; % 
dialogBox = uicontrol('Style', 'PushButton', 'String', 'Salir','Callback', 'loop_break = false;');
% plot zeros 
%p1 = plot(x_vals,plot_var,'linewidth',1.1); 
%p2 = plot(x_vals,plot_var2,'linewidth',1.1); 
%p3 = plot(x_vals,plot_var3,'linewidth',1.1); 
while loop_break 
        out = fscanf(s);
    if (length(out)>8)
    dat=str2num(out)
   %plot_var(1:end-1) = plot_var(2:end);
   plot_var2(1:end-1) = plot_var2(2:end);
   plot_var3(1:end-1) = plot_var3(2:end);
   %plot_var(end) =(dat(1));
   plot_var2(end) =(dat(2));
   plot_var3(end) =(dat(3));
   %set(p1,'Ydata',plot_var)
   %set(p2,'Ydata',plot_var2)
   %set(p3,'Ydata',plot_var3)
   plotCube(-dat(2), dat(3))
   drawnow
   pause(0.03)
   clf
   
   end
end
fclose(s)

