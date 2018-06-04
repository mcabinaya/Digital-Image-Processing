function ima = reprojection_UWA(ima_patchs,xg,yg)

%reprojection_UWA  compute uniform weight reprojections from  
% 		 patches to pixels values 
%                 
%   INPUT:
%     ima_patchs      : values of the collection of patches
%     xg, yg          : Initial values of the image/normalization, default are
%				 xg = zeros(M,N);
%  			         yg = zeros(M,N);
%   OUTPUT:
%     ima             : image in the original domain 
%   
%ima = reprojection_UWA(ima_patchs,xg,yg)
%   computes the pixels values knowing the values of the whole collections of  
%   the patches of an image. The reprojection is uniform.  
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

    [M, N, P] = size(ima_patchs);
    if nargin <= 2
        xg = zeros(M,N);
        yg = zeros(M,N);
    end
    p = sqrt(P);
    ima = zeros(M+p-1, N+p-1);
    norm = zeros(M+p-1, N+p-1);
    for i = 1:M
        for j = 1:N
            xrange = mod(round((i-1)+(1:p)+xg(i,j))-1,M+p-1)+1;
            yrange = mod(round((j-1)+(1:p)+yg(i,j))-1,N+p-1)+1;
            ima(xrange, yrange) = ...
                ima(xrange, yrange) + ...
                reshape(ima_patchs(i,j,:), p, p);
            norm(xrange, yrange) = ...
                norm(xrange, yrange) + ...
                1;
        end
    end
    ima = ima ./ norm;
    clear norm;
