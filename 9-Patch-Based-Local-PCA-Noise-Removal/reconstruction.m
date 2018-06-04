function patchs = reconstruction(coefs, dico)


%reconstruction  computes the values of the patches, knowing the 
% 		 coefficients in the basis provided by dico 
%                 
%   INPUT:
%     coefs	 : coefficients of the patches in the basis dico
%     dico       : the structure containting the basis elements 
%   OUTPUT:
%     patchs     : the patches in original domain 
%   
%patchs = reconstruction(coefs, dico)
%   compute the patchs values knowing the coefficients (coefs) of those patches in 
%   the space spanned by dicos.  
%
%see also reconstruction_ppca.m and projection.m (inverse operation)
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

    if size(coefs, 3) > 1
        isimage = 1;
        [M,N,P] = size(coefs);
        MN = M*N;
        coefs = reshape(coefs, MN, P);
    else
        isimage = 0;
        [MN,P] = size(coefs);
        P = size(dico, 1);
    end

    patchs = coefs * dico';

    if isimage
        P = size(dico, 1);
        patchs = reshape(patchs, M, N, P);
    end
