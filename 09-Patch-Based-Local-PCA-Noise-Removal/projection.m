function coefs = projection(patchs, dico)

%projection  computes the new coefficients when projecting 
%            the patches on the new dico elements 
%                 
%   INPUT:
%     patchs	 : collection of patches
%     dico       : the structure containting the  new basis elements 
%   OUTPUT:
%     coeff      : the coefficients of patch in the basis of dico 
%   
%coefs = projection(patchs, dico)
%   compute the projection of patchs on the space spanned by the elements
%   dicos. coefs are the coefficients in this new space.
%
%see also reconstruction_ppca.m (inverse operation)
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

    coefs = patchs * dico;

    if isimage
        coefs = reshape(coefs, M, N, P);
    end
