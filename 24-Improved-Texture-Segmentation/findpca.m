clc;
clear all;
close all;

row = 450;
col = 600;
d = 25;

filename1 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-3/hw_3_answers/hw_3_prob_1_c/hw_3_prob_1_c/comb_energyfeatures.txt';
data1 = load(filename1);

data2 = data1(:,2);
X = reshape(data2, [row*col,d]); 

[residuals,reconstructed] = pcares(X,2);
