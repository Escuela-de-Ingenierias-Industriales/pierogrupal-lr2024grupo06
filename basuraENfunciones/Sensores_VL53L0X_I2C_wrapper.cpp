
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#define SIMPLIFIED_RTWTYPES_COMPATIBILITY
#include "rtwtypes.h"
#undef SIMPLIFIED_RTWTYPES_COMPATIBILITY
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
# ifndef MATLAB_MEX_FILE

#include <Arduino.h>

#include <math.h>

#include <Wire.h>
#include <Wire.cpp>
#include <twi.h>
#include <twi.c>
#include <VL53L0X.h>
#include <VL53L0X.cpp>
#define XSHUT_izq 30
#define XSHUT_cen 32
#define XSHUT_der 34
#define sensor_izq_newAddress 41
#define sensor_cen_newAddress 42
#define sensor_der_newAddress 43
VL53L0X sensor_izq;
//VL53L0X sensor_cen;
VL53L0X sensor_der;

#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1
#define y_1_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void Sensores_VL53L0X_I2C_Outputs_wrapper(real_T *Sensor_izq,
			real_T *Sensor_der,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
if (xD[0]==1) {
    
    /* don't do anything for mex file generation */
    # ifndef MATLAB_MEX_FILE

    
    double media_izq=sensor_izq.readRangeContinuousMillimeters();
    //double media_cen=sensor_cen.readRangeContinuousMillimeters();
    double media_der=sensor_der.readRangeContinuousMillimeters();
    /*
    for(int iter=1;iter<10;iter++){
        media_izq=(media_izq+sensor_izq.readRangeContinuousMillimeters())/2;
        //media_cen=(media_cen+sensor_cen.readRangeContinuousMillimeters())/2;
        media_der=(media_der+sensor_der.readRangeContinuousMillimeters())/2;
    }
    */
    Sensor_izq[0] = media_izq;
    //Sensor_cen[0] = media_cen;
    Sensor_der[0] = media_der;

    # endif
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
void Sensores_VL53L0X_I2C_Update_wrapper(real_T *Sensor_izq,
			real_T *Sensor_der,
			real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
if (xD[0]!=1) {

    /* don't do anything for mex file generation */
# ifndef MATLAB_MEX_FILE
  
 // Establecemos sensor de la izq
  pinMode(XSHUT_izq, OUTPUT);
  pinMode(XSHUT_cen, OUTPUT);
  pinMode(XSHUT_der, OUTPUT);
  digitalWrite(XSHUT_izq,1);
  digitalWrite(XSHUT_cen,0);
  digitalWrite(XSHUT_der,0);
  Wire.begin();
  sensor_izq.setAddress(sensor_izq_newAddress);
  pinMode(XSHUT_izq, INPUT);
  delay(10);
  
  // Sensor del centro
  /*
  digitalWrite(XSHUT_cen,1);
  sensor_cen.setAddress(sensor_cen_newAddress);
  pinMode(XSHUT_cen, INPUT);
  delay(10);
  */

  // Sensor de la derecha
  digitalWrite(XSHUT_der,1);
  sensor_der.setAddress(sensor_der_newAddress);
  pinMode(XSHUT_der, INPUT);
  delay(10);
  
  sensor_izq.init();
  //sensor_cen.init();
  sensor_der.init();
  sensor_izq.setTimeout(5000);
  //sensor_cen.setTimeout(5000);
  sensor_der.setTimeout(5000);
  sensor_izq.startContinuous();
  //sensor_cen.startContinuous();
  sensor_der.startContinuous();
 
        # endif
    
    /* initialization done */ 
    xD[0]=1;
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}

