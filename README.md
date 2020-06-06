# Digital_Filter
Write a generic filter in C and test it with matlab using shared csv files. 
## Implementation

So there are a couple of cvs file, 2 matlab scirpt and a c file

IN ORDER TO RUN THE FILE CORRECTLY

 1) run butter filter.m first section
 2) run C file
 3) run butter filter.m second section 

Write a generic filter in C (refer to lecture 3).
Your implementation should
• use the data type float,
• read the input data for the filter from a file,
• write the output data to a file and
• be generic either at
compile time (i.e., #define FILTER ORDER ...) or at
run time (i.e., const int filter order = ...).
Note: If necessary you can assume a maximum filter order of 16.
20/21
Task 2: Filter Application
For data sampled at 1000 Hz, design a low-pass filter with less
than 3 dB of ripple in the passband, defined from 0 to 40 Hz, and
at least 40 dB of attenuation in the stopband, defined from 200 Hz
to the Nyquist frequency. The filter order should be less than 6.
• You can use the formula from the lecture or any matlab function.
• Find a solution with the lowest filter order.
• Plot the frequency response.
• Generate a sample sine wave and a noise sine signal with the same
amplitudes. Add both signals.
• Check if your filter removes the noise form the signal.
Use the C filter from the Task 1 to remove the noise.
• Export the signal with the noise generated in Matlab to a file.
• Run your C filter.
• Import the output of the C-filter to Matlab and plot it.

 
