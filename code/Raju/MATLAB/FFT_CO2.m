function value_active = FFT_CO2(x)
    delta=160e-3;
    fs=1/delta;
    X=1/250*fft(x,256);
    Xa=abs(X);
    value_active=max(Xa);    
end
