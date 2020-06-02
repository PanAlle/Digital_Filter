%Sample freq 1000Hz
%Passband 0 - 40Hz
%40dB attenuation in stopband (200 Hz - Nyquist freq)
%Max filter order 6

%Sampling freq
f_s = 1000;
%Nyquist freq
f_n = f_s/2;
%Required ripple in dB
ripple = 4;
%stopband required attenuation in dB
A_s = 40;
%Cutoff freq
f_c = 40;
%Stopband initial freq
f_st = 200;

%reutrn n, required order and Wn, cutoff freq over nyqiust freq
[n, Wn] = buttord(f_c/f_n, f_st/f_n, ripple, A_s);
%Generate filter coeffiecient
[b,a] = butter(n, Wn);
%generic sine with high freq noise
t = 0:1/100:10;
noise = sin(30*t);
y = sin(t) + noise;


signal = [y',t'];
but = [a',b'];
csvwrite("butter_filter.csv", but);
csvwrite("csv_prova.csv", signal);

filt_sig = filter(b, a, y);
%%

filename = 'csv_output.csv'
M = csvread(filename);

%tiledlayout(2,1) % Requires R2019b or later



subplot(2,1,1);
plot(t, y, t, filt_sig);figure(gcf)
title('Only Matlab filtering')

subplot(2,1,2); 
plot(t, y, M(:,2)', M(:,1)');
title('Matlab and C filtering')

