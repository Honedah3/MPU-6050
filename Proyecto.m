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

x = plot(x_vals,plot_var,'linewidth',1.1); 
y = plot(x_vals,plot_var2,'linewidth',1.1);

while 1
out = fscanf(s);
    if (length(out)>8)
    dat=str2num(out);
x = fscanf(s, '%e')
y = fscanf(s, '%e')
plotCube(x, y)
drawnow
clf
end