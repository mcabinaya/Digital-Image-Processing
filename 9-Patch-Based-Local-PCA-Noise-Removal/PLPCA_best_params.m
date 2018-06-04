function [WP factor_thr hW] = PLPCA_best_params(sigma)

%PLPCA_best_params        computes the parameters for PLPCA.m, 			
%  			  optimized on a small data set.
%   INPUT:
%     sigma	  : standard deviation of the noise
%   OUTPUT:
%     WP          : half size of the patch 
%     factor_thr  : factor in front of the variance term for
%		    hardthresholding the coefficients
%     hW          : half size of the searching zone
%
%  [WP factor_thr hW] = PLPCA_best_params(sigma)
%   Compute the best parameters WP and factor_thr for the using
%   PLPCA_denoising.m  for some values of noise level.  
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

    [WP factor_thr] = PGPCA_best_params(sigma);
    switch sigma
      case 5
        hW = 8;
      case 10
        hW = 10;
      case 20
        hW = 11;
      case 25
        hW = 15;  
      case 40
        hW = FIXME;
    end
