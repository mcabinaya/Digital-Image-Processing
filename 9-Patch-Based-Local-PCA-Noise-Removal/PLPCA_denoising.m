function [ima_patchs_fil subima_ppca_fil] = ...
        PLPCA_denoising(ima_patchs, func_thresholding, ...
                        hW, delta, irange, jrange)
%PLPCA_denoising  computes the denoised patches, denoised image 
%                 and tree structure using PLPCA (local PCAs)
%   
%   INPUT:
%     ima_patchs 	 : a collection of (noisy) patches
%     func_thresholding  : function that used to threshold the coefficients
%     hW  	  	 : half size of the searching zone
%     irange, jrange     : range (vertical and horizontal) on wich the PCA
%                           PCA is performed. Standard default are
%                           irange = [(1+hW):delta:(M-hW) M-hW];
%                           jrange = [(1+hW):delta:(N-hW) N-hW];
%    delta               : shift parameter, controls the overlap of 
%                          searching windows			
%   OUTPUT:
%     ima_patchs_fil     : structure of  the PCAs after func_thresholding
%                           and having dealt with overlaping inside the 
%                           searching windows
%     subima_ppca_fil    : rough structure of the PCAs after 
%                            func_thresholding. Usefull for visualization
%                           
%                           
%
%   [ima_patchs_fil subima_ppca_fil] = ...
%        PLPCA_denoising(ima_patchs, func_thresholding, ...
%                        hW, delta, irange, jrange)
%   
%
%
%   Copyright (C) 2011 GP-PCA project
%   Charles Deledalle, Joseph Salmon, Arnak S. Dalalyan
%
%   See The GNU Public License (GPL)
%
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


    ima_patchs_fil = zeros( size(ima_patchs ));    
    ima_patchs_fil_norm = zeros( [size(ima_patchs,1) size(ima_patchs,1)] );

    [M,N,P] = size(ima_patchs);
    if nargin <= 4
        irange = [(1+hW):delta:(M-hW) M-hW];
        jrange = [(1+hW):delta:(N-hW) N-hW];
    end
  
    for i = irange
        for j = jrange
            xrange = mod(i + (-hW:hW) - 1, M) + 1;
            yrange = mod(j + (-hW:hW) - 1, N) + 1;
            subima_patchs = ima_patchs(xrange, yrange, :);
            subima_ppca = ppca(subima_patchs);
            subima_ppca_fil = func_thresholding(subima_ppca);
            subima_patchs_fil = reconstruction_ppca(subima_ppca_fil);

            ima_patchs_fil(xrange, yrange,:) = ...
                ima_patchs_fil(xrange, yrange,:) + ...
                subima_patchs_fil;
            ima_patchs_fil_norm(xrange, yrange) = ...
                ima_patchs_fil_norm (xrange, yrange) + 1;
        end
    end
    for k = 1:P
        ima_patchs_fil(:,:,k) = ...
            ima_patchs_fil(:,:,k) ./ ...
            ima_patchs_fil_norm;
    end
