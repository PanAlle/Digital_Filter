filename = 'csv_output.csv'
M = csvread(filename);
plot(M(:,2)', M(:,1)');