function [ima_patchs, ima_normalization] = spatial_patchization(im_ini,WP)

%spatial_patchization computes the collection of patches extracted from an image  
%                 
%   INPUT:
%     im_ini             : image of interest
%     WP                  : width of the square patches to consider
%  			         
%   OUTPUT:
%     ima_patchs         : the collection of all the patches
%     ima_normalization  : number of patches to which each pixel belongs
%   
%  [ima_patchs, ima_normalization] = spatial_patchization(im_ini,WP)
%   computes the whole collecitons of  the patches of size WP x WP 
%   of an image im_ini. It also provides the number of patches to 
%   which each pixel belongs in the image.
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


[m,n] = size(im_ini);
ima_patchs=zeros(m-WP+1,n-WP+1,WP^2);
ima_normalization=zeros(m,n);

for i=1:(m-WP+1)
    for j=1:(n-WP+1)
        xrange = mod((i:i+WP-1)-1,m)+1;
        yrange = mod((j:j+WP-1)-1,n)+1;
        B = im_ini(xrange, yrange);
        ima_patchs(i,j,:) = B(:);
        ima_normalization(xrange, yrange) = ...
            ima_normalization(xrange, yrange) + ones(WP,WP);
    end
end
