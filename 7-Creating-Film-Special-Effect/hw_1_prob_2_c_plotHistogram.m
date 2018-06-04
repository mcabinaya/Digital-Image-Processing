clc;
clear all;
close all;

filename1 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/Original_mirror_invert_histR.txt';
data1 = importdata(filename1);

filename2 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/Original_mirror_invert_histG.txt';
data2 = importdata(filename2);

filename3 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/Original_mirror_invert_histB.txt';
data3 = importdata(filename3);

filename4 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/RMapping.txt';
data4 = importdata(filename4);

filename5 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/GMapping.txt';
data5 = importdata(filename5);

filename6 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/BMapping.txt';
data6 = importdata(filename6);

filename7 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/Film_histR.txt';
data7 = importdata(filename7);

filename8 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/Film_histG.txt';
data8 = importdata(filename8);

filename9 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/hw-1-answers/hw_1_prob_2_c/hw_1_prob_2_c/Film_histB.txt';
data9 = importdata(filename9);

figure; stem(data1(:,1), data1(:,2), 'r', 'LineWidth',1.5);
title('Histogram R channel - Original Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data2(:,1), data2(:,2), 'g', 'LineWidth',1.5);
title('Histogram G channel - Original Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data3(:,1), data3(:,2), 'b', 'LineWidth',1.5);
title('Histogram B channel - Original Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');

figure; plot(data4(:,1), data4(:,2), 'r', 'LineWidth',2);
title('Transfer Function R channel');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Mapped Pixel values');
figure; plot(data5(:,1), data5(:,2), 'g', 'LineWidth',2);
title('Transfer Function G channel');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Mapped Pixel values');
figure; plot(data6(:,1), data6(:,2), 'b', 'LineWidth',2);
title('Transfer Function B channel');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Mapped Pixel values');


figure; stem(data7(:,1), data7(:,2), 'r', 'LineWidth',2);
title('Histogram R channel - Film Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data8(:,1), data8(:,2), 'g', 'LineWidth',2);
title('Histogram G channel - Film Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');
figure; stem(data9(:,1), data9(:,2), 'b', 'LineWidth',2);
title('Histogram  B channel - Film Image');
xlabel('Pixel values');
xlim([-5,260]);
ylabel('Pixel Count');


