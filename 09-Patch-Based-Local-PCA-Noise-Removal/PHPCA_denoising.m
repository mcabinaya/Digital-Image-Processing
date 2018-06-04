function [ima_patchs_fil ima_ppca_fil tree] = ...
        PHPCA_denoising(ima_patchs, func_thresholding, ...
                        depth, nb_axis_kept)
%PHPCA_denoising  computes the denoised patches, denoised image 
%                 and tree structure using PHPCA (hierarchical PCAs)
%   
%   INPUT:
%     ima_patchs 	 : a collection of (noisy) patches
%     func_thresholding  : function that used to threshold the coefficients
%     depth  	  	 : maximum depth of the tree
%     nb_axis_kept       : number of axis kept at each node of the tree
%   OUTPUT:
%     ima_patchs_fil     : structure of of the PCAs after func_thresholding
%     ima_ppca_fil       : structure of of the PCAs before func_thresholding
%     tree               : tree structure 
%
%
%   [ima_patchs_fil ima_ppca_fil tree] = ...
%        PHPCA_denoising(ima_patchs, func_thresholding, ...
%                        depth, nb_axis_kept) 
%   provides the patches before and after performing a shrinkage using
%   func_thresholding, as  well as the tree structure of the axis 
%   (for potential display).
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


    [M N P] = size(ima_patchs);
    depth = round(log2(M/depth));
    [ima_ppca tree] = PHPCA(ima_patchs, depth, nb_axis_kept);
    clear ima_patchs;
    if nargout < 3
        clear tree;
    end
    ima_ppca_fil = func_thresholding(ima_ppca);
    clear ima_ppca;
    ima_patchs_fil = reconstruction_ppca(ima_ppca_fil);
    if nargout < 2
        clear ima_ppca_fil;
    end
