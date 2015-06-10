clear all;
close all;
clc;

data_active;
x=active_data;
% x=[1 2 3 4 5 6 7 8];
f=2;
N=length(x);

for i=0:N-1
    F(i+1)=0;
    for k=0:N-1
        temp = x(k+1)*exp(-2*pi*j*i*k/N);
        F(i+1)=F(i+1)+temp;        
    end
end

X=F;
fs=10;
% t=-5:1/fs:5;
plot(x);
axis([0 2 -2 2])
grid on;
X=fft(x,size(x,2));
Xa=abs(X);
fx=linspace(-fs/2,fs/2,length(X));
figure;
XaShifted=fftshift(Xa);
stem(fx,XaShifted);
valatf1= XaShifted(find(fx==f))
% axis([-3 3 0 2])
grid on;