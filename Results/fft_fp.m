 function value_active = fft_fp(X,N)
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
% disp('Wp Float')
% disp(Wp.float)

Y   = Wp*Xmod;
Y1=1/250*fft(Y,256);
Ya=abs(Y1);
value_active=max(Ya);

%------------- END OF CODE --------------
