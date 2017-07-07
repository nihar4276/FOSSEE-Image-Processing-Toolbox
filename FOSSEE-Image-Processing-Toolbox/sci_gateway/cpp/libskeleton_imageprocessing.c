#ifdef __cplusplus
extern "C" {
#endif
#include <mex.h> 
#include <sci_gateway.h>
#include <api_scilab.h>
#include <MALLOC.h>
static int direct_gateway(char *fname,void F(void)) { F();return 0;};
extern Gatefunc opencv_imread;
extern Gatefunc opencv_rgb2xyz;
extern Gatefunc opencv_CascadeObjectDetector;
extern Gatefunc opencv_detectKAZEFeatures;
static GenericTable Tab[]={
  {(Myinterfun)sci_gateway_without_putlhsvar,opencv_imread,"raw_imread"},
  {(Myinterfun)sci_gateway_without_putlhsvar,opencv_rgb2xyz,"raw_rgb2xyz"},
  {(Myinterfun)sci_gateway_without_putlhsvar,opencv_CascadeObjectDetector,"raw_CascadeObjectDetector"},
  {(Myinterfun)sci_gateway_without_putlhsvar,opencv_detectKAZEFeatures,"raw_detectKAZEFeatures"},
};
 
int C2F(libskeleton_imageprocessing)()
{
  Rhs = Max(0, Rhs);
  if (*(Tab[Fin-1].f) != NULL) 
  {
     if(pvApiCtx == NULL)
     {
       pvApiCtx = (StrCtx*)MALLOC(sizeof(StrCtx));
     }
     pvApiCtx->pstName = (char*)Tab[Fin-1].name;
    (*(Tab[Fin-1].f))(Tab[Fin-1].name,Tab[Fin-1].F);
  }
  return 0;
}
#ifdef __cplusplus
}
#endif
