clc;
clear all;
close all;

filename1 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistR.txt';
data1 = importdata(filename1);

filename2 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistG.txt';
data2 = importdata(filename2);

filename3 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistB.txt';
data3 = importdata(filename3);

filename4 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistMappingR.txt';
data4 = importdata(filename4);

filename5 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistMappingG.txt';
data5 = importdata(filename5);

filename6 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistMappingB.txt';
data6 = importdata(filename6);

filename7 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistEqualizedR.txt';
data7 = importdata(filename7);

filename8 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistEqualizedG.txt';
data8 = importdata(filename8);

filename9 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_a_methodA/hw_1_prob_2_a_methodA/Desk_HistEqualizedB.txt';
data9 = importdata(filename9);

figure; stem(data1(:,1), data1(:,2), 'r', 'LineWidth',1.5);
title('Histogram R channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data2(:,1), data2(:,2), 'g', 'LineWidth',1.5);
title('Histogram G channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data3(:,1), data3(:,2), 'b', 'LineWidth',1.5);
title('Histogram B channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');

figure; plot(data4(:,1), data4(:,2), 'r', 'LineWidth',2);
title('Transfer Function R channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Mapped Pixel values');
figure; plot(data5(:,1), data5(:,2), 'g', 'LineWidth',2);
title('Transfer Function G channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Mapped Pixel values');
figure; plot(data6(:,1), data6(:,2), 'b', 'LineWidth',2);
title('Transfer Function B channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Mapped Pixel values');


figure; stem(data7(:,1), data7(:,2), 'r', 'LineWidth',2);
title('Histogram Equalized R channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data8(:,1), data8(:,2), 'g', 'LineWidth',2);
title('Histogram Equalized G channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data9(:,1), data9(:,2), 'b', 'LineWidth',2);
title('Histogram Equalized B channel - Desk Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');


