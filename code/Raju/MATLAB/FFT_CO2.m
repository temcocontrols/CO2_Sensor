 function snrdB = fft_fp(X)
% newFFT: - returns the discrete Fourier transform (DFT) of vector X,
% computed with a fast Fourier transform (FFT) algorithm. If X is a matrix,
% newFFT returns the Fourier transform of each column of the matrix

% Syntax: Y = newFFT(X,N)
%
% Inputs:
%    X          - Time domain input signal
%    N          - Number of FFT point
%
% Outputs:
%    Y      - Frequency domain N point DFT
%
% Other m-files required: 
%   Subfunctions: 
%   Upperfuncions: 
%   MAT-files required: 
%

%------------- BEGIN CODE --------------


N=64;
[m n]= size(X);

% If the length of X is greater than n, the sequence X is truncated.
if m>N
    Xmod= X(1:N,:);
% If the length of X is less than N, X is padded with trailing zeros to
% length N
elseif m<N
    Xmod =[X ;zeros(N-m,n)];
    
elseif m==N
    Xmod=X;
end

% j   = sqrt(-1);
j   = mpower(-1,0.5);
tk  = 0:(N-1);
fn  = transpose(0:(N-1))/N;
wn  = 2*pi*fn;

p= -j*wn*tk;

Wp  = exp(p); %DFT Matrix
Y   = Wp*Xmod;

delta=160e-3;
fs=1/delta;
FFT_sampled_data=1/m*Y;
absFFT_sampled_data=abs(FFT_sampled_data);
signal_value=max(absFFT_sampled_data);
noise_mean=(sum(absFFT_sampled_data)-signal_value)/(m-1);    
snrVal=signal_value/noise_mean;
snrdB=10*log10(snrVal); 

%------------- END OF CODE --------------
