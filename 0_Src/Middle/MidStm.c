/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "MidStm.h"
#include "DrvStm.h"


/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/




/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/



/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Callback Function--------------------------*/
void MidRegTimerCallbackFnc(void (*pMidRegCallbackFnc)(void))
{
    DrvRegStm0CallbackFnc(pMidRegCallbackFnc);
}
