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

sigma=10;
randn('seed', 2);
ima = double(imread('data/barbara.png'));
ima_nse = ima + sigma * randn(size(ima));

figure('Position',[100 100  800 800]);
plotimage(ima_nse);
title(sprintf('Noisy: \n  PSNR %.2f', psnr(ima, ima_nse)));
set(get(gca,'Title'),'FontSize',12);

%% GLOBAL VERSION: PGPCA.m
%
[WP factor_thr] = PGPCA_best_params(sigma);
threshold = factor_thr * sigma;
func_thresholding = @(ima_ppca) ...
    hardthresholding(ima_ppca, threshold, sigma);
global_time=tic;
%% Patchization step 
ima_patchs = spatial_patchization(ima_nse, WP);

%% Global PCA denoising step
[ima_patchs_fil ima_ppca_fil] = ...
    PGPCA_denoising(ima_patchs, func_thresholding);
%% Uniform reprojection step
ima_fil_PGPCA = reprojection_UWA(ima_patchs_fil);
global_time=toc(global_time);

%% Display
figure('Position',[100 100  800 800])
plotimage(ima_fil_PGPCA);
title(sprintf('PGPCA: \n  PSNR %.2f', psnr(ima, ima_fil_PGPCA)));
sprintf('PGPCA:\n PSNR: %.2f dB \n Computing Time: %.2f s.',...
    psnr(ima, ima_fil_PGPCA),global_time)
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
title(sprintf('PLPCA: \n  PSNR %.2f', psnr(ima, ima_fil_PLPCA)));
set(get(gca,'Title'),'FontSize',12);
sprintf('PLPCA:\n PSNR: %.2f dB \n Computing Time: %.2f s.', ...
    psnr(ima, ima_fil_PLPCA),local_time)


%% HIERARCHICAL VERSION:PHPCA.m
%
[WP factor_thr depth nb_axis_kept] = PHPCA_best_params(sigma);
threshold = factor_thr * sigma;
func_thresholding = @(ima_ppca) ...
    hardthresholding(ima_ppca, threshold, sigma);
hierarchical_time=tic;
%% Patchization step 
ima_patchs = spatial_patchization(ima_nse, WP);
%% Hierarchical PCA denoising step
[ima_patchs_fil ima_ppca_fil tree] = ...
    PHPCA_denoising(ima_patchs, func_thresholding, ...
                    depth, nb_axis_kept);
%% Uniform reprojection step
ima_fil_PHPCA = reprojection_UWA(ima_patchs_fil);
hierarchical_time=toc(hierarchical_time);

%% Display
figure('Position',[100 100  800 800])
plotimage(ima_fil_PHPCA);
title(sprintf('PHPCA: \n  PSNR %.2f', psnr(ima, ima_fil_PHPCA)));
set(get(gca,'Title'),'FontSize',12);
sprintf('PHPCA:\n PSNR: %.2f dB \n Computing Time: %.2f s.', ...
    psnr(ima, ima_fil_PHPCA),hierarchical_time)
