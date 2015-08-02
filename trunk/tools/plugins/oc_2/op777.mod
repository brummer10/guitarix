* OP777 SPICE Macro-model Typical Values
* Description: Amplifier
* Generic Desc: 2.7/30V, BIP, OP, S SPLY, RRO, 1X
* Developed by: RM / ADSC
* Revision History: 08/10/2012 - Updated to new header style
* 1.2 (04/2009) - Corrected EVP, EVN
* 1.1 (08/2000)
* Copyright 2000, 2012 by Analog Devices
*
* Refer to http://www.analog.com/Analog_Root/static/techSupport/designTools/spiceModels/license/spice_general.html for License Statement. Use of this model
* indicates your acceptance of the terms and provisions in the License Statement.
*
* BEGIN Notes:
*
* Not Modeled:
*
* Parameters modeled include:
*
* END Notes
*
* Node Assignments
* noninverting input
* | inverting input
* | | positive supply
* | | | negative supply
* | | | | output
* | | | | |
* | | | | |
.SUBCKT OP777 1 2 99 50 45
*
* PNP INPUT STAGE
*
Q1 5 7 3 PIX
Q2 6 2 3 PIX
RC1 5 50 8000
RC2 6 50 8000
C1 5 6 0.5E-12
D1 3 8 DX
V1 99 8 DC 1.0
I1 99 3 50E-6
EOS 7 1 POLY(3) (73,98) (81,98) (22,98) 0.08E-3 1 1 1
IOS 2 1 1E-9
*
* PSRR=120dB, ZERO AT 150Hz
*
RPS1 70 0 1E+6
RPS2 71 0 1E+6
CPS1 99 70 1E-5
CPS2 50 71 1E-5
EPSY 98 72 POLY(2) (70,0) (0,71) 0 1 1
RPS3 72 73 1E+6
CPS3 72 73 1.06E-9
RPS4 73 98 1
*
* VOLTAGE NOISE REFERENCE OF 15nV/rt(Hz)
*
VN1 80 98 0
RN1 80 98 16.45E-3
HN 81 98 VN1 15
RN2 81 98 1
*
* INTERNAL VOLTAGE REFERENCE
*
EREF 98 0 POLY(2) (99,0) (50,0) 0 .5 .5
GSY 99 50 POLY(1) (99,50) 0 2.6E-6
EVP 97 98 (99,50) 0.5
EVN 51 98 (50,99) 0.5
*
*
* CMRR 110dB, ZERO AT 400Hz
*
ECM1 21 98 POLY(2) (1,98) (2,98) 0 .5 .5
RCM1 21 22 1E+6
CCM1 21 22 0.397E-9
RCM2 22 98 1
*
* GAIN STAGE
*
G1 98 30 POLY(1) (5,6) 0 28.8E-6
R1 30 98 2.02E+8
CF 45 30 50E-12
D3 30 97 DX
D4 51 30 DX
*
* OUTPUT STAGE
*
M5 45 46 99 99 POX L=1E-6 W=0.329E-3
M6 45 47 50 50 NOX L=1E-6 W=0.496E-3
EG1 99 46 POLY(1) (98,30) 0.6299 1
EG2 47 50 POLY(1) (30,98) 0.5739 1
*
* MODELS
*
.MODEL POX PMOS (LEVEL=2 KP=10E-6 VTO=-0.328 LAMBDA=0.01 KF=2.5E-23 AF=1)
.MODEL NOX NMOS (LEVEL=2 KP=10E-6 VTO=+0.328 LAMBDA=0.01 KF=2.5E-23 AF=1)
.MODEL PIX PNP (BF=2273 IS=1E-14 VAF=130)
.MODEL DX D(IS=1E-14 RS=5)
.ENDS OP777
