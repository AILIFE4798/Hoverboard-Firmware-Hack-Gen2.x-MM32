#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

typedef struct {  
						int32_t  Alpha;		// Output: stationary d-axis stator variable
						int32_t  Beta;		// Output: stationary q-axis stator variable
						int32_t  Theta;		// Input: rotating angle (pu)
						int32_t  Ds;			// Input: rotating d-axis stator variable
						int32_t  Qs;			// Input: rotating q-axis stator variable
						int32_t  Sin;			// Input: Sine term
						int32_t  Cos;			// Input: Cosine term 	 
						}PARK_T;	            

/*-----------------------------------------------------------------------------
Default initalizer for the PARK object.
-----------------------------------------------------------------------------*/                     
#define PARK_DEFAULTS {   0, \
                          0, \
                          0, \
                          0, \
                          0, \
													0, \
                          0 	\
              			  }

//------------------------------------------------------------------------------
extern PARK_T park1;
extern void PARK_MACRO1(PARK_T *u1);
//------------------------------------------------------------------------------
