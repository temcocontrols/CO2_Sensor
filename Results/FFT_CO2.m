function value_active = FFT_CO2(x)
    delta=160e-3;
    fs=1/delta;
    x=x';
    X=1/64*fft(x,64);
    Xa=abs(X);
    value_active=max(Xa);    
end
