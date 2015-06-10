% The script calculates the FFT of given sampled IR signal, calulates the
% noise level at different sampling frequency.
clc;
clear all;
close all;
f=1:10; % Modulating frequency of IR signal
k=1:20;
% fs=k.*f; %Samping frequency ; Sampling frequency should always be greater or equal to 2 times of IR signal frequency
% t=0:1/fs:1/f; % For sampling timing index
xn=0; % Noise signal , assuming white noise

for i=1:1
    for j=1:length(k)
        fs(j)=k(j).*2*f(i); %Samping frequency ; Sampling frequency should always be greater or equal to 2 times of IR signal frequency
        t=0:1/fs(j):1/f(i); % For sampling timing index
        xs=3*sin(2*pi*f(i)*t); % IR signal at modulating rfrequency
        x=xs+xn; % Total signal (original plus noise signal)
        X=1/length(x)*fft(x,size(x,2)); % Fast Fourier Transform (FFT) of IR modulated sampled signal
        Xa=abs(X); % Absolute 
%       fx=linspace(-fs(j)/2,fs(j)/2,length(X)); % FFT provides frequency spectrum only between -fs/2 to +fs/2
        XaShifted=fftshift(Xa); %  for visualizing the Fourier transform with the zero-frequency component in the middle of the spectrum 
        signalAmpatf=max(XaShifted); %Assuming the maximum amplitude is signal amplitude
        noiseVal(i,j)=abs((sum(abs(XaShifted))-2*abs(signalAmpatf))/(length(XaShifted)-2)); %
       
    end 
end
hold on
plot(fs,noiseVal(1,:));
grid on;
xlabel('Sampling Frequency (Hz)');
ylabel('Noise parameter (Unit same as given sampled signal, for eg: volt)');
title('Noise vs sampling frequency at particulat modulating IR frequency (1 Hz) at differeniont white noise assumption') ;