[b,a] = butter(2,10/100);
t = 0:1/100:10;
y = sin(t)+sin(100*t);

signal = [y',t'];
but = [a',b'];
csvwrite("butter_filter.csv", but);
csvwrite("csv_prova.csv", signal);
filt_sig = filter(b, a, y);

plot(t, y, t, filt_sig);figure(gcf)