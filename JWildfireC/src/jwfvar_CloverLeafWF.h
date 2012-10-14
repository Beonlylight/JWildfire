/*
 JWildfireC - an external C-based fractal-flame-renderer for JWildfire
 Copyright (C) 2012 Andreas Maschke

 This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software Foundation; either version 2.1 of the
 License, or (at your option) any later version.
 
 This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License along with this software;
 if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

#include "jwf_Constants.h"
#include "jwf_Variation.h"

class CloverLeafWFFunc: public Variation {
public:
	CloverLeafWFFunc() {
		filled = 1;
		initParameterNames(1, "filled");
	}

	const char* getName() const {
		return "cloverleaf_wf";
	}

	void setParameter(char *pName, JWF_FLOAT pValue) {
		if (strcmp(pName, "filled") == 0) {
			filled = FTOI(pValue);
		}
	}

	void transform(FlameTransformationContext *pContext, XForm *pXForm, XYZPoint *pAffineTP, XYZPoint *pVarTP, JWF_FLOAT pAmount) {
    JWF_FLOAT a = pAffineTP->getPrecalcAtan();
    JWF_FLOAT r = pAffineTP->getPrecalcSqrt();

    r = (JWF_SIN(2 * a) + 0.25 * JWF_SIN(6 * a));

    if (filled == 1) {
      r *= pContext->randGen->random();
    }

    JWF_FLOAT sina, cosa;
    JWF_SINCOS(a, &sina, &cosa);
    JWF_FLOAT nx = sina * r;
    JWF_FLOAT ny = cosa * r;

    pVarTP->x += pAmount * nx;
    pVarTP->y += pAmount * ny;
		if (pContext->isPreserveZCoordinate) {
			pVarTP->z += pAmount * pAffineTP->z;
		}
	}

	CloverLeafWFFunc* makeCopy() {
		return new CloverLeafWFFunc(*this);
	}

private:
	int filled;
};

