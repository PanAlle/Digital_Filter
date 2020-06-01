%Create a sine 


t = 0:1/100:10;
singal = zeros(1,length(t));

for i = 1:10
    phase = rand*2*pi;
    ampl = rand;
    omega = 2*pi*i;
    signal = singal + ampl*sin(omega*t + phase);
end
SamplingFreq = 20*pi;
signalFFT = fft(signal(1:end-1));
signalFFT_amp = abs(signalFFT/length(signalFFT));
signalFFT_window = signalFFT_amp(1:length(signalFFT)/2+1);
signalFFT_window(2:end-1) = 2*signalFFT_window(2:end-1);
frequencies = SamplingFreq*((0:length(signalFFT)/2))/length(signalFFT);
clf;plot(frequencies, signalFFT_window)