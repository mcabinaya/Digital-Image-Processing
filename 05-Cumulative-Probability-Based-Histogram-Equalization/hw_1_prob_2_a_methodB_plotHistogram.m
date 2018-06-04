clc;
clear all;
close all;

filename1 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodB/hw_1_prob_2_a_methodB/Desk_histEqualizedR.txt';
data1 = importdata(filename1);

filename2 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodB/hw_1_prob_2_a_methodB/Desk_histEqualizedG.txt';
data2 = importdata(filename2);

filename3 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodB/hw_1_prob_2_a_methodB/Desk_histEqualizedB.txt';
data3 = importdata(filename3);

filename4 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodB/hw_1_prob_2_a_methodB/Desk_CDFEqualizedR.txt';
data4 = importdata(filename4);

filename5 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodB/hw_1_prob_2_a_methodB/Desk_CDFEqualizedG.txt';
data5 = importdata(filename5);

filename6 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodB/hw_1_prob_2_a_methodB/Desk_CDFEqualizedB.txt';
data6 = importdata(filename6);

figure; stem(data1(:,1), data1(:,2), 'r', 'LineWidth',1.2);
title('Histogram Equalized R channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data2(:,1), data2(:,2), 'g', 'LineWidth',1.2);
title('Histogram Equalized G channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data3(:,1), data3(:,2), 'b', 'LineWidth',1.2);
title('Histogram Equalized B channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');

figure; stem(data4(:,1), data4(:,2), 'r', 'LineWidth',1.2);
title('CDF Histogram Equalized R channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data5(:,1), data5(:,2), 'g', 'LineWidth',1.2);
title('CDF Histogram Equalized G channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data6(:,1), data6(:,2), 'b', 'LineWidth',1.2);
title('CDF Histogram Equalized B channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');


