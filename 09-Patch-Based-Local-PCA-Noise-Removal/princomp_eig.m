function [coeff, score, latent] = princomp_eig(x)
%princomp_eig  computes the PCA decomposition of the matrix x
%                 
%
%   INPUT:
%     x	 	 : input matrix
%   OUTPUT:
%     coeff      : the principal components/ new basis 
%     score      : coefficients of the representations of x in the new basis
%     latent     : eigenvalues / variances on each axis
%   
%[coeff, score, latent] = princomp_eig(x)
%   compute the pca of x where coeff are the new basis/axis elements, score
%   the coefficients of x in this new basis, and latent the variances of
%   the projection of x on each axis elements.
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


[MN P] = size(x);
meanx = mean(x, 1);
x = x - ones(MN, 1) * meanx;
[coeff latent] = eig(x' * x / (MN - 1));
%max(max(x' * x / (MN - 1)))
latent = fliplr(diag(latent));
coeff = fliplr(coeff);
%x = x + repmat(meanx, [1 P]);
score = projection(x, coeff);
