function patchs_ppca = ppca(patchs)

%ppca  computes the PCA of a collection of patches 
%   
%   INPUT:
%     patchs       : a collection of (noisy) patches
%   OUTPUT:
%     patchs_ppca  : structure of of the PCAs (coefficients +components)
%
%
%patchs_ppca = ppca(patchs) computes the pca structures in patch_ppca of the
% collection of patches from patchs. 
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


    if size(patchs, 3) > 1
        isimage = 1;
        [M,N,P] = size(patchs);
        MN = M*N;
        patchs = reshape(patchs, MN, P);
        
    else
        isimage = 0;
        [MN,P] = size(patchs);
    end

    cst_patchs = mean(patchs,2);
    [pc_axis,patchs_newbasis,varaxis] = ...
        princomp_eig(patchs - cst_patchs * ones(1, P));

    patchs_ppca.coefs = [ cst_patchs*sqrt(P) patchs_newbasis(:,1:end-1) ];
    patchs_ppca.iddico = ones(MN,1);
    %patchs_ppca.score_rpjct=ones(M,N);

    patchs_ppca.dicos{1}.size = P;
    patchs_ppca.dicos{1}.axis = [1/sqrt(P)*ones(P,1) pc_axis(:,1:end-1)];
    patchs_ppca.dicos{1}.mean = mean(patchs - cst_patchs * ones(1, P), 1);
    patchs_ppca.dicos{1}.varaxis = [0; varaxis(1:end-1)];

    if isimage
        patchs_ppca.iddico = reshape(patchs_ppca.iddico, M, N);
        patchs_ppca.coefs = reshape(patchs_ppca.coefs, M, N, P);
    end
