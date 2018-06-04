function ima_ppca = hardthresholding(ima_ppca, threshold, sigma)

%hardthresholding        Hard thresholding the PCA coefficients
%   INPUT:
%     ima_ppca    : structure of the noisy PCAs decompositions.
%     threshold   : threshold used for the hardthresholding
%     sigma	  : standard deviation of the noise
%   OUTPUT:
%     ima_ppca    : sturture of of the PCAs after hardthresholding
%
%   ima_ppca = hardthresholding(ima_ppca, threshold, sigma)
%   hard thresholding of the PCA coefficients from the ima_ppca
%   structure.
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


    coefs = ima_ppca.coefs;
    if size(coefs, 3) > 1
        isimage = 1;
        [M,N,P] = size(coefs);
        MN = M*N;
        coefs = reshape(coefs, MN, P);
    else
        isimage = 0;
        [MN,P] = size(coefs);
    end

    coefs = coefs .* (threshold < abs(coefs));

    if isimage
        ima_ppca.coefs = reshape(coefs, M, N, P);
    else
        ima_ppca.coefs = reshape(coefs, MN, P);
    end
