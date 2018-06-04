function patchs = reconstruction_ppca(patchs_pca)

%reconstruction  computes the values of the patches, knowing the 
% 		 structure (dico+coefs) of the patch_pca 
%                 
%   INPUT:
%     patchs_pca	 : structures of the patches in the PCA basis

%   OUTPUT:
%     patchs             : the patches in original domain 
%   
%patchs = reconstruction_ppca(patchs_pca)
%   computes the patchs values knowing patchs_pca, the structure  
%   of those patches in the space spanned by dicos.  
%
%see also reconstruction.m and prejection.m (inverse operation)
%
%   Copyright (C) 2011 GP-PCA project
%   Charles Deledalle, Joseph Salmon, Arnak S. Dalalyan
%
%   See The GNU Public License (GPL)
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

    if size(patchs_pca.coefs, 3) > 1
        isimage = 1;
        [M,N,P] = size(patchs_pca.coefs);
        MN = M*N;
        coefs = reshape(patchs_pca.coefs, MN, P);
        iddico = reshape(patchs_pca.iddico, MN, 1);
    else
        isimage = 0;
        [MN,P] = size(patchs_pca.coefs);
        coefs = patchs_pca.coefs;
        iddico = patchs_pca.iddico;
    end
    P = size(patchs_pca.dicos{1}.axis, 1);
    L = length(patchs_pca.dicos);
    patchs = zeros(MN, P);
    for i = 1:L
        idx = ((iddico == i) .* (1:(MN))')';
        idx = idx(idx > 0);

        K = size(idx, 2);
        subK = min(K, 10000);
        k = 1;
        while k < K - subK
            range = (1:subK) + k;
            subcoefs = coefs(idx(range), :);
            patchs(idx(range), :) = ...
                subcoefs * patchs_pca.dicos{i}.axis' + ...
                ones(size(range, 2), 1) * patchs_pca.dicos{i}.mean;
            %repmat(patchs_pca.dicos{i}.mean, size(range, 2), 1);
            clear subcoefs;
            k = k + subK;
        end
        if k <= K
            range = (k:K);
            subcoefs = coefs(idx(range), :);
            patchs(idx(range), :) = ...
                subcoefs * patchs_pca.dicos{i}.axis' + ...
                ones(size(range, 2), 1) * patchs_pca.dicos{i}.mean;
            %repmat(patchs_pca.dicos{i}.mean, size(range, 2), 1);
            clear subcoefs;
        end
    end
    clear coefs;
    clear iddico;
    if isimage
        patchs = reshape(patchs, M, N, P);
    end
