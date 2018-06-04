clc;
clear all;
close all;

filename1 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-3/hw_3_answers/hw_3_prob_1_a/hw_3_prob_1_a/energyfeature.txt';
data1 = load(filename1);

energy_1D = data1(:,2);
energy = reshape(energy_1D,[12,9]);
%energy = energy';

for i=1:9
    figure;
    hist(energy(:,i),30);
    title(['Histogram Of Energy Feature ',num2str(i)])
end
