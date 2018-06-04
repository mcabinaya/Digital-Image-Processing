function [ima_patchs_fil ima_ppca_fil] = ...
        PGPCA_denoising(ima_patchs, func_thresholding)
%PGPCA_denoising  computes the denoised patches, denoised image 
%                 and tree structure using PLPCA (local PCAs)
%   
%   INPUT:
%     ima_patchs 	 : a collection of (noisy) patches
%     func_thresholding  : function that used to threshold the coefficients			
%   OUTPUT:
%     ima_patchs_fil     : structure of of the PCAs after func_thresholding
%                          reprojected in the space of patches
%     ima_ppca_fil       : structure of of the PCAs after func_thresholding
%                          but in the PCA domain
%
%   [ima_patchs_fil ima_ppca_fil] = ...
%        PGPCA_denoising(ima_patchs, func_thresholding)
%   
%
%

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


    ima_ppca = ppca(ima_patchs);
    ima_ppca_fil = func_thresholding(ima_ppca);
    ima_patchs_fil = reconstruction_ppca(ima_ppca_fil);
