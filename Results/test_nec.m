clc;
clear all;
close all;
f=6; % Modulating frequency of IR signal
k=10;
fs=k*2*f; %Samping frequency ; Sampling frequency should always be greater or equal to 2 times of IR signal frequency
t=0:1/fs:1/f; % For sampling timing index
xs=3*sin(2*pi*f*t); % IR signal at modulating rfrequency
xn=0.2; % Noise signal , assuming white noise
x=xs+xn; % Total signal (original plus noise signal)

% figure;
% stem(t,x); % Plotting of IR signal mixed with noise
% grid on;

X=1/length(x)*fft(x,size(x,2)); % Fast Fourier Transform (FFT) of IR modulated sampled signal
Xa=abs(X); % Absolute 
% fx=linspace(-fs/2,fs/2,length(X)); % FFT provides frequency spectrum only between -fs/2 to +fs/2

% figure;
XaShifted=fftshift(Xa); %  for visualizing the Fourier transform with the zero-frequency component in the middle of the spectrum 
% stem(fx,XaShifted);
% grid on;

% valatf1= XaShifted(find(fx==f))
valatf=max(XaShifted) %Assuming the maximum amplitude 

noiseVal=(sum(abs(XaShifted))-2*abs(valatf))/(length(XaShifted)-2)