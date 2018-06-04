=============================================================================
================     Gaussian Patch  PCA (GP-PCA)      ======================
=============================================================================


Revision:	      05/18/2010
Author:               C-A Deledalle, J. Salmon, A. Dalalyan
Web page:             http://josephsalmon.org/code/index_codes.php?page=GPPCA

NLM-SAP is a MATLAB software implementing the denoising algorithm Gaussian
Patch PCA (GP-PCA) for images damaged by Gaussian noise
as presented in:

"Image denoising with patch based PCA: local versus global"
C.-A. Deledalle, J. Salmon, A. S. Dalalyan, BMVC 2011
PDF:http://josephsalmon.org/papers/BMVC11_DSD.pdf

GP-PCA is free software distributed under the GNU Public License
(GPL). GP-PCA should be used only for nonprofit purposes. Any
unauthorized use of this software for industrial or profit-oriented
activities is expressively prohibited.

=============================================================================
================               LICENSE                 ======================
=============================================================================

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

See LICENSE.txt

=============================================================================
================               HOW TO                  ======================
=============================================================================


The program has been written for MATLAB. Please, look at DEMO_GPPCA_online.m
to use the standard version of GP-PCA in either global (gppca.m), 
local (lppca.m) or hierarchical (hppca.m) settings.

=============================================================================
================         MAIN PROGRAM FILES            ======================
=============================================================================

The main program files are the followings:

- DEMO_GPPCA_online.m :
  	A demonstration file illustrating our three standard algorithms.

- PGPCA_denoising.m:
	A function performing the Patch Global PCA.  

- PLPCA_denoising.m :
	A function performing the Patch Local PCA. 
	It is mainly build on PLPCA.m

- PHPCA_denoising.m :
	A function performing the Patch Hierarchical PCA. 
	It is mainly build on PHPCA.m

- ppca.m :
	A  function  computing the pca for a collection of patches.

- princomp_eig.m	
	A  function  computing PCA based on eig.m (no toolbox needed).

-reconstruction_ppca.m
	A function providing the patches value from the coefficient values
	in the principal components basis. 

- hardthresholding.m :
  	A function that shrink the PCA coefficients of the patches. 

- reprojection_UWA.m :
	A function reprojecting/combining uniformly the various pixels
	estimates due to patches overlaps.

- spatial_patchization.m
	A function building the collection  of patches from an image.



=============================================================================
================             INFORMATION               ======================
=============================================================================


For any comment, suggestion or question please contact Charles-Alban
Deledalle, Joseph Salmon or Arnak S. Dalalyan.

Charles-Alban Deledalle		charles.deledalle (at) gmail.com
Joseph Salmon			joseph.salmon (at) duke.edu
Arnak S. Dalalyan 		dalalyan (at) imagine.fr
Copyright (C) 2011 GP-PCA project

See The GNU Public License (GPL) in LICENSE.txt

