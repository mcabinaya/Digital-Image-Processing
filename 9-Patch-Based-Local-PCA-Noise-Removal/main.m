%% Simple example on Barbara
%
% We present here the three variations of Gaussian Patch-PCA (GP-PCA) algorithms:
% 
%
% The first one is the global approach (using PGPCA.m) meaning all the 
% patches in the images are used to compute a global PCA, followed by 
% a hard-thresholding of the coefficients.
% The second one is the local approach (using PLPCA.m) meaning that
% we use a sliding window on which the PCA is performed, before 
% hard- thresholding coefficients.
% The third one is the hierarchical or tree based approach (using PHPCA.m).
% We keep axis at some iteration and then look for axis on the complement
% of the space the span of the axis already found.
%
%
%
%
%
% Authors: \( \textbf{C-A. Deledalle} \), \(\textbf{J. Salmon} \)
% and \(\textbf{A. S. Dalalyan} \)

%   Copyright (C) 2011 GP-PCA project
%   Charles Deledalle, Joseph Salmon, Arnak S. Dalalyan
%
%   See The GNU Public License (GPL)

%---------------------------------------------------------------------
%
%   This file is part of GP-PCA.
%
%   GP-PCA is free software: you can redistribute it and/or modify
%   it under the terms of the GNU General Public License as
%   published by the Free Software Foundation, either version 3 of
%   the License, or (at your option) any later version.
%
%   GP-PCA is distributed in the hope that it will be useful,
%   but WITHOUT ANY WARRANTY; without even the implied warranty of
%   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%   GNU General Public License for more details.
%
%   You should have received a copy of the GNU General Public
%   License along with GP-PCA.  If not, see
%   <http://www.gnu.org/licenses/>.
%   Charles Deledalle, Joseph Salmon, Arnak S. Dalalyan
%
%   See The GNU Public License (GPL)



%% Initialization
%
%
clear all
close all
addpath('/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/GP-PCA_code')
sigma=25;
%randn('seed', 2);
%ima = double(imread('data/barbara.png'));
%ima_nse = ima + sigma * randn(size(ima));

filename1 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/images2/p3/House.raw';
filename2 = '/Users/abinaya/USC/Studies/DIP/Homeworks/hw-1/images2/p3/House_noisy.raw';
ima = view_raw_image_matlab(filename1,256, 256, 1);
ima_nse = view_raw_image_matlab(filename2,256, 256, 1);

figure('Position',[100 100  800 800]);
plotimage(ima_nse);
title(sprintf('Noisy: \n  PSNR %.2f', psnr(ima, ima_nse)));
set(get(gca,'Title'),'FontSize',12);


%% LOCAL VERSION: PLPCA.m
[WP factor_thr hW] = PLPCA_best_params(sigma);


threshold = factor_thr * sigma;
% Shift/Redudancy  parameter for the searching zone.
delta = hW; %< 2*hW+WP;
func_thresholding = @(ima_ppca) ...
    hardthresholding(ima_ppca, threshold, sigma);
local_time=tic;
%% Patchization step 
ima_patchs = spatial_patchization(ima_nse, WP);
%% Local PCA denoising step
ima_patchs_fil = PLPCA_denoising(ima_patchs, func_thresholding, ...
                                 hW, delta);
%% Uniform reprojection step
ima_fil_PLPCA = reprojection_UWA(ima_patchs_fil);
local_time=toc(local_time);
%% Display
figure('Position',[100 100  800 800])
plotimage(ima_fil_PLPCA);
title(sprintf('PLPCA: \n  PSNR %.2f', psnr(ima, uint8(ima_fil_PLPCA))));
set(get(gca,'Title'),'FontSize',12);
sprintf('PLPCA:\n PSNR: %.2f dB \n Computing Time: %.2f s.', ...
    psnr(ima, uint8(ima_fil_PLPCA)),local_time)
