%% MATLAB script to create examples of symmetric positive definite (spd) 
% linear systems of specified size.
% Specify size
size = 100;

% Specify name of example 
ex_name = sprintf('Spd_Ex_size%i_', size);

% Generate variables
A = rand(size); 
b = rand(size,1);
A_spd =0.5*(A+A') + size* eye(size);
x= A_spd\b;

% Write to file in correct format
mat_file = [ex_name 'mat.dat'];
vec_file = [ex_name 'vec.dat'];
sol_file = [ex_name 'sol.dat'];
fileID = fopen(mat_file,'w');
fprintf(fileID,'%i %i \n',size, size);
fclose(fileID);
save(mat_file,'A_spd', '-append', '-ascii');

fileID = fopen(vec_file,'w');
fprintf(fileID,'%i %i \n',size,1);
fclose(fileID);
save(vec_file,'b', '-append', '-ascii');


fileID = fopen(sol_file,'w');
fprintf(fileID,'%i %i \n',size,1);
fclose(fileID);
save(sol_file,'x', '-append', '-ascii');


