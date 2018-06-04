function [ima_ppca tree] = PHPCA(ima_patchs, maxL, maxK, dicos)

%PHPCA            computes the structure used for denoising a collections
%		  of patches using hierarchical PCAs
%   
%   INPUT:
%     ima_patchs  : a collection of (noisy) patches
%     maxL        : maximum depth of the tree
%     maxK  	  : number of axis kept at each node of the tree
%     dicos       : ???? 
%   OUTPUT:
%     ima_ppca    : structure of of the PCAs after hardthresholding
%     tree        : tree structure ????
%
%   [ima_ppca tree] = PHPCA(ima_patchs, maxL, maxK, dicos)
%   computes a tree with the  PCA coefficients and axis by recursively
%   dividing an image in 4 zones. 
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



    if nargin < 2
        maxL = 1;
    end
    if nargin < 3
        maxK = 1;
    end
    if nargin < 4
        dicos = { };
        iddico = 1;
    else
        iddico = length(dicos) + 1;
    end

    %if size(ima_patchs, 3) == 1
    %    fprintf(2, 'hppca: ima_patchs must be an image\n');
    %    return
    %end
    [M,N,P] = size(ima_patchs);
    MN = M*N;
    ima_patchs = reshape(ima_patchs, MN, P);
    if nargin < 4
        atoms = zeros(P, 0);
        atoms(:, 1) = ones(P,1)/sqrt(P);
        atomsK = size(atoms, 2);

        coefs_residu = projection(ima_patchs, atoms);
        [pc_axis,ima_patchs_newbasis,varaxis] = ...
            princomp_eig(ima_patchs - reconstruction(coefs_residu, atoms));
        ima_patchs_newbasis = reshape(ima_patchs_newbasis, M, N, P);
        meanpatchs = ...
            mean(ima_patchs - reconstruction(coefs_residu, atoms), 1);
        clear ima_patchs;
        pc_axis = [atoms pc_axis(:,1:end-atomsK)];
        ima_patchs_newbasis = ...
            cat(3, ...
                reshape(coefs_residu, M, N, atomsK), ...
                ima_patchs_newbasis(:,:,1:end-atomsK));

        K = min(0*atomsK + maxK, P);

        clear atoms;
    else
        [pc_axis,ima_patchs_newbasis,varaxis] = ...
            princomp_eig(ima_patchs);
        ima_patchs_newbasis = reshape(ima_patchs_newbasis, M, N, P);
        meanpatchs = mean(ima_patchs, 1);
        clear ima_patchs;

        K = min(maxK, P);
    end

    if maxL == 0 || K == 0 || K == P
        ima_ppca.coefs = ima_patchs_newbasis;
        ima_ppca.iddico = iddico * ones(M,N);

        ima_ppca.dicos = dicos;
        ima_ppca.dicos{iddico}.size = P;
        ima_ppca.dicos{iddico}.axis = pc_axis;
        ima_ppca.dicos{iddico}.mean = meanpatchs;
        ima_ppca.dicos{iddico}.varaxis = varaxis;

        tree.K = K;
        tree.L = 0;
        tree.iddico = iddico;
    else
        ima_ppca.coefs = zeros(M,N,P);
        ima_ppca.coefs(:, :, 1:K) = ima_patchs_newbasis(:,:,1:K);
        ima_ppca.iddico = zeros(M,N);

        ima_patchs_newbasis = ima_patchs_newbasis(:, :, (1+K):P);
        cM = floor(M/2);
        cN = floor(N/2);

        [subima_ppca subtree] = ...
            PHPCA(ima_patchs_newbasis(1:cM, 1:cN, :), ...
                  maxL - 1, maxK, dicos);
        ima_ppca.coefs(1:cM, 1:cN, (1+K):P) = subima_ppca.coefs;
        ima_ppca.iddico(1:cM, 1:cN) = subima_ppca.iddico;
        tree.NE = subtree;
        dicos = complete_dicos(subima_ppca.dicos, ...
                               subtree, ...
                               pc_axis, ...
                               pc_axis(:,1:K), ...
                               meanpatchs,varaxis(1:K));

        clear subima_ppca;
        clear subtree;

        [subima_ppca subtree] = ...
            PHPCA(ima_patchs_newbasis((cM+1):M, 1:cN, :), ...
                  maxL - 1, maxK, dicos);
        ima_ppca.coefs((cM+1):M, 1:cN, (1+K):P) = subima_ppca.coefs;
        ima_ppca.iddico((cM+1):M, 1:cN) = subima_ppca.iddico;
        tree.NW = subtree;
        dicos = complete_dicos(subima_ppca.dicos, ...
                               subtree, ...
                               pc_axis, ...
                               pc_axis(:,1:K), ...
                               meanpatchs,varaxis(1:K));

        clear subima_ppca;
        clear subtree;

        [subima_ppca subtree] = ...
            PHPCA(ima_patchs_newbasis((cM+1):M, (cN+1):N, :), ...
                  maxL - 1, maxK, dicos);
        ima_ppca.coefs((cM+1):M, (cN+1):N, (1+K):P) = subima_ppca.coefs;
        ima_ppca.iddico((cM+1):M, (cN+1):N) = subima_ppca.iddico;
        tree.SW = subtree;
        dicos = complete_dicos(subima_ppca.dicos, ...
                               subtree, ...
                               pc_axis, ...
                               pc_axis(:,1:K), ...
                               meanpatchs,varaxis(1:K));

        clear subima_ppca;
        clear subtree;

        [subima_ppca subtree] = ...
            PHPCA(ima_patchs_newbasis(1:cM, (cN+1):N, :), ...
                  maxL - 1, maxK, dicos);
        ima_ppca.coefs(1:cM, (cN+1):N, (1+K):P) = subima_ppca.coefs;
        ima_ppca.iddico(1:cM, (cN+1):N) = subima_ppca.iddico;
        tree.SE = subtree;
        dicos = complete_dicos(subima_ppca.dicos, ...
                               subtree, ...
                               pc_axis, ...
                               pc_axis(:,1:K), ...
                               meanpatchs,varaxis(1:K));
        clear subima_ppca;
        clear subtree;

        ima_ppca.dicos = dicos;
        tree.K = K;
        tree.L = 1 + max([tree.NE.L tree.NW.L tree.SW.L tree.SE.L]);
    end
    clear ima_patch_newbasis;
    clear mean_patchs;
    clear pc_axis;
    clear varaxis;
    clear dicos;
    clear iddico;
end

function dicos = complete_dicos(dicos, tree, pc_axis, newaxis, meanpatchs,varaxis)

    if tree.L == 0
        iddico = tree.iddico;
        dico = dicos{iddico};
        S = size(dico.axis, 2);
        K = size(pc_axis, 2) - size(dico.axis, 1);
        dico.axis = cat(2, newaxis, (pc_axis * cat(1, repmat(0, K, S), dico.axis)));
        dico.mean = (pc_axis * cat(1, repmat(0, K, 1), dico.mean'))' + meanpatchs;
        dico.size = length(dico.axis);
        dico.varaxis= cat(1,varaxis, dico.varaxis);
        dicos{iddico} = dico;

        clear dico;
        clear iddico;
    else
        dicos = complete_dicos(dicos, tree.NE, pc_axis, newaxis, meanpatchs,varaxis);
        dicos = complete_dicos(dicos, tree.NW, pc_axis, newaxis, meanpatchs,varaxis);
        dicos = complete_dicos(dicos, tree.SE, pc_axis, newaxis, meanpatchs,varaxis);
        dicos = complete_dicos(dicos, tree.SW, pc_axis, newaxis, meanpatchs,varaxis);
    end

end
