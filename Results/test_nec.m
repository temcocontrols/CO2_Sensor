clc;
clear all;
close all;
f1=3;
f2=5;
fs=500;
t=-5:1/fs:5;
x=5*sin(2*pi*f1*t)+7*sin(2*pi*f2*t);
% x=7*sin(2*pi*f1*t);
stem(t,x);
grid on;
X=1/length(x)*fft(x,size(x,2));
Xa=abs(X);
fx=linspace(-fs/2,fs/2,length(X));
figure;
stem(fx,fftshift(Xa));
axis([-6 6 0 5])
grid on;