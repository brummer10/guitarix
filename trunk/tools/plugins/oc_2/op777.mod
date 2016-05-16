*-----------------------------------------------------
* name : "guitarix"
* version : "0.35.0"
* author : "drgreenthumb" 
* license : "GPL v.2"
* copyright : "(c)drgreenthumb 2016"
* reference : "http://www.ecircuitcenter.com/OpModels/OpampModels.htm"
*-----------------------------------------------------
*
* Device Pins    In+ In- Vcc Vdd Vout
.SUBCKT OP777    1   2   3   4   5
*
* INPUT R
RIN   1   2   1e9
*
*  STAGE 1, POLE AT 150Hz
*   Aol=10000 (5V supply = 80dB), fu=1MHz
G1   0    10  VALUE = { 1e-2 * V(1,2)  }
R1   10   0   1e6
C1   10   0   1.06157e-9

* OUTPUT STAGE
EBUFFER 80 0  10  0    1
ROUT 80      5        100
.ENDS
