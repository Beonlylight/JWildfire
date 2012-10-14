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

class RoseWFFunc: public Variation {
public:
	RoseWFFunc() {
	  amp = 0.5;
	  waves = 4;
	  filled = 0;
		initParameterNames(3, "amp", "waves", "filled");
	}

	const char* getName() const {
		return "rose_wf";
	}

	void setParameter(char *pName, JWF_FLOAT pValue) {
		if (strcmp(pName, "amp") == 0) {
			amp = pValue;
		}
		else if (strcmp(pName, "waves") == 0) {
			waves = FTOI(pValue);
		}
		else if (strcmp(pName, "filled") == 0) {
			filled = FTOI(pValue);
		}
	}

	void transform(FlameTransformationContext *pContext, XForm *pXForm, XYZPoint *pAffineTP, XYZPoint *pVarTP, JWF_FLOAT pAmount) {
    JWF_FLOAT a = pAffineTP->getPrecalcAtan();
    JWF_FLOAT r = pAffineTP->getPrecalcSqrt();

    r = amp * JWF_COS(waves * a);

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

	RoseWFFunc* makeCopy() {
		return new RoseWFFunc(*this);
	}

private:
  JWF_FLOAT amp;
  int waves;
  int filled;
};

