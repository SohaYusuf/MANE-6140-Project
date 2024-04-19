#include "acusim.h"
#include "udf.h"

UDF_PROTOTYPE(usrTranslation);		 /* function prototype			*/

# define Pi 3.1415926535897931

Void usrTranslation(
	UdfHd udfHd,			 /* Opaque handle for accessing data	*/
	Real* outVec,			 /* Output vector			*/
	Integer nItems,			 /* = 1					*/
	Integer vecDim)			 /* = 12					*/
	{
		udfCheckNumUsrVals(udfHd, 2);		/* check			*/
		Real* usrVals = udfGetUsrVals(udfHd);	/* user input		*/

		Real rotMat[3][3];			/* rotation matrix	*/
		Real tranMat[3][3];			/* translation matrix	*/		

		Real Amp = usrVals[0];			/* translation amplitude	*/
		Real omega = usrVals[1];		/* getting omega	*/

		Real time = udfGetTime(udfHd);		/* get time		*/

		/* Initialize rotation matrix and translation matrix to Identity matrix */
		Integer i, j;

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				rotMat[i][j] = 0.;
				tranMat[i][j] = 0.;
			}
			rotMat[i][i] = 1.;
			tranMat[i][i] = 1.;
		}

		/* Construct the transformation matrix */

		Real sinAngle = sin(omega*time);
		tranMat[1][3] = Amp * sinAngle;		/* Only y-direction translation */

		/* Build the output vector (the fourth row is not required) */
		Integer k = 0;
		for (j = 0; j < 4; j++) {
			for (i = 0; i < 3; i++) {
				outVec[k] = rotMat[i][0] * tranMat[0][j]
					+ rotMat[i][1] * tranMat[1][j]
					+ rotMat[i][2] * tranMat[2][j]
					+ rotMat[i][3] * tranMat[3][j];
				k++;
			}
		}
	} /* end of usrTranslation() */