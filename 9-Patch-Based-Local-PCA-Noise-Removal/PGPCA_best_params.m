function [hP factor_thr] = PGPCA_best_params(sigma)

%PGPCA_best_params        computes the parameters for PGPCA.m, 			
%  			  optimized on a small data set.
%   INPUT:
%     sigma	  : standard deviation of the noise
%   OUTPUT:
%     hP          : half size of the patch 
%     factor_thr  : factor in front of the variance term for
%		    hardthresholding the coefficients
%
%   [hP factor_thr] = PGPCA_best_params(sigma)
%   Computes the best parameters hP and factor_thr for the using
%   PGPCA_denoising.m  for some values of noise level.  
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

    switch sigma
      case 5
        hP = 7;
        factor_thr = 2.50;
      case 10
        hP = 7;
        factor_thr = 2.50;
      case 20
        hP = 7;
        factor_thr = 2.75;
      case 25
        hP = 10;
        factor_thr = 2.75;
      case 40
        hP = 12;
        factor_thr = 2.75;
    end
