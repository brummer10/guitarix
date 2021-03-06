v 20130925 2
C 40000 40000 0 0 0 title-B.sym
C 48700 49700 1 90 0 resistor-2.sym
{
T 48350 50100 5 10 0 0 90 0 1
device=RESISTOR
T 49100 50400 5 10 1 1 180 0 1
refdes=R5
T 48800 49900 5 10 1 1 0 0 1
value=1.2k
}
C 51400 49000 1 180 0 capacitor-1.sym
{
T 51200 48300 5 10 0 0 180 0 1
device=CAPACITOR
T 50600 48900 5 10 1 1 0 0 1
refdes=C4
T 51200 48100 5 10 0 0 180 0 1
symversion=0.1
T 51500 49100 5 10 1 1 180 0 1
value=0.1u
}
C 53800 41800 1 0 1 gnd-1.sym
C 52000 41800 1 0 0 gnd-1.sym
C 53700 45300 1 0 0 npn-2.sym
{
T 54300 45800 5 10 0 0 0 0 1
device=NPN_TRANSISTOR
T 54100 45700 5 10 1 1 0 0 1
refdes=T2
T 53700 45300 5 10 0 1 0 0 1
value=Vt=26mV,Is=20.3fA,Bf=1430,Br=4
T 54300 45500 5 10 1 1 0 0 1
model-name=2N5088
}
C 55100 45300 1 0 0 npn-2.sym
{
T 55700 45800 5 10 0 0 0 0 1
device=NPN_TRANSISTOR
T 55400 45700 5 10 1 1 0 0 1
refdes=T3
T 55100 45300 5 10 0 1 0 0 1
value=Vt=26mV,Is=20.3fA,Bf=1430,Br=4
T 55700 45500 5 10 1 1 0 0 1
model-name=2N5088
}
C 49400 47000 1 270 1 resistor-variable-2.sym
{
T 49050 47300 5 10 1 1 180 6 1
refdes=P2
T 50300 47800 5 10 0 1 90 2 1
device=VARIABLE_RESISTOR
T 52000 47100 5 10 1 1 180 0 1
value=value=1000k,var=Volume,a=3
}
C 41000 48900 1 0 0 input-1.sym
{
T 41000 49200 5 10 0 0 0 0 1
device=INPUT
T 41000 48900 5 10 1 1 0 0 1
refdes=IN1
}
C 42500 49100 1 180 1 output-1.sym
{
T 42600 48800 5 10 0 0 180 6 1
device=OUTPUT
T 42700 49100 5 10 1 1 180 6 1
refdes=OUT1
}
C 55400 41800 1 0 1 gnd-1.sym
C 48500 49300 1 90 1 capacitor-2.sym
{
T 47800 49100 5 10 0 0 270 2 1
device=POLARIZED_CAPACITOR
T 48800 49000 5 10 1 1 0 6 1
refdes=C2
T 47600 49100 5 10 0 0 270 2 1
symversion=0.1
T 48700 48600 5 10 1 1 0 6 1
value=47u
}
C 45700 49700 1 90 0 resistor-2.sym
{
T 45350 50100 5 10 0 0 90 0 1
device=RESISTOR
T 45400 50400 5 10 1 1 180 0 1
refdes=R2
T 45100 50000 5 10 1 1 0 0 1
value=10k
}
C 46800 49700 1 90 0 resistor-2.sym
{
T 46450 50100 5 10 0 0 90 0 1
device=RESISTOR
T 46500 50500 5 10 1 1 180 0 1
refdes=R3
T 46200 50000 5 10 1 1 0 0 1
value=10k
}
C 51900 49200 1 270 0 capacitor-1.sym
{
T 52600 49000 5 10 0 0 270 0 1
device=CAPACITOR
T 52000 49000 5 10 1 1 180 0 1
refdes=C5
T 52800 49000 5 10 0 0 270 0 1
symversion=0.1
T 51600 48400 5 10 1 1 0 0 1
value=0.47u
}
C 50000 49000 1 180 0 capacitor-1.sym
{
T 49800 48300 5 10 0 0 180 0 1
device=CAPACITOR
T 49200 48900 5 10 1 1 0 0 1
refdes=C3
T 49800 48100 5 10 0 0 180 0 1
symversion=0.1
T 50100 49100 5 10 1 1 180 0 1
value=0.1u
}
C 52800 49200 1 270 0 capacitor-1.sym
{
T 53500 49000 5 10 0 0 270 0 1
device=CAPACITOR
T 52900 49100 5 10 1 1 180 0 1
refdes=C6
T 53700 49000 5 10 0 0 270 0 1
symversion=0.1
T 53100 48400 5 10 1 1 0 0 1
value=0.1u
}
C 54500 46900 1 270 1 resistor-variable-2.sym
{
T 54150 47600 5 10 1 1 180 6 1
refdes=P4
T 55400 47700 5 10 0 1 90 2 1
device=VARIABLE_RESISTOR
T 56400 47800 5 10 1 1 180 0 1
value=value=10k,var=Tone
}
C 54600 41800 1 0 1 gnd-1.sym
C 52400 45300 1 0 0 npn-2.sym
{
T 53000 45800 5 10 0 0 0 0 1
device=NPN_TRANSISTOR
T 52800 45800 5 10 1 1 0 0 1
refdes=T1
T 52400 45300 5 10 0 1 0 0 1
value=Vt=26mV,Is=20.3fA,Bf=1430,Br=4
T 52900 45600 5 10 1 1 0 0 1
model-name=2N5088
}
C 56100 48900 1 180 0 capacitor-1.sym
{
T 55900 48200 5 10 0 0 180 0 1
device=CAPACITOR
T 55300 48800 5 10 1 1 0 0 1
refdes=C8
T 55900 48000 5 10 0 0 180 0 1
symversion=0.1
T 56400 48900 5 10 1 1 180 0 1
value=0.01u
}
C 44700 49700 1 90 0 resistor-2.sym
{
T 44350 50100 5 10 0 0 90 0 1
device=RESISTOR
T 44400 50400 5 10 1 1 180 0 1
refdes=R1
T 44000 50000 5 10 1 1 0 0 1
value=470k
}
C 52300 46900 1 270 1 resistor-variable-2.sym
{
T 52550 47300 5 10 1 1 180 6 1
refdes=P3
T 53200 47700 5 10 0 1 90 2 1
device=VARIABLE_RESISTOR
T 54200 47000 5 10 1 1 180 0 1
value=value=40k,var=Drive
}
C 51500 41800 1 0 1 gnd-1.sym
C 54600 48900 1 180 0 capacitor-1.sym
{
T 54400 48200 5 10 0 0 180 0 1
device=CAPACITOR
T 53800 48800 5 10 1 1 0 0 1
refdes=C7
T 54400 48000 5 10 0 0 180 0 1
symversion=0.1
T 54600 48900 5 10 1 1 180 0 1
value=0.01u
}
C 48000 50600 1 180 0 resistor-2.sym
{
T 47600 50250 5 10 0 0 180 0 1
device=RESISTOR
T 47300 50700 5 10 1 1 0 0 1
refdes=R4
T 47900 50300 5 10 1 1 180 0 1
value=10k
}
C 51800 50600 1 180 0 resistor-2.sym
{
T 51400 50250 5 10 0 0 180 0 1
device=RESISTOR
T 51100 50200 5 10 1 1 0 0 1
refdes=R8
T 51700 50300 5 10 1 1 180 0 1
value=47k
}
C 49900 49600 1 90 0 resistor-2.sym
{
T 49550 50000 5 10 0 0 90 0 1
device=RESISTOR
T 49600 50400 5 10 1 1 180 0 1
refdes=R6
T 49300 49900 5 10 1 1 0 0 1
value=1M
}
C 50200 41800 1 0 1 gnd-1.sym
C 50400 49600 1 90 0 resistor-2.sym
{
T 50050 50000 5 10 0 0 90 0 1
device=RESISTOR
T 50700 50300 5 10 1 1 180 0 1
refdes=R7
T 50400 49800 5 10 1 1 0 0 1
value=100
}
C 52500 49600 1 90 0 resistor-2.sym
{
T 52150 50000 5 10 0 0 90 0 1
device=RESISTOR
T 52800 50300 5 10 1 1 180 0 1
refdes=R9
T 52600 49700 5 10 1 1 0 0 1
value=10k
}
C 50900 41800 1 0 1 gnd-1.sym
C 53400 49600 1 90 0 resistor-2.sym
{
T 53050 50000 5 10 0 0 90 0 1
device=RESISTOR
T 53800 50300 5 10 1 1 180 0 1
refdes=R10
T 53500 49700 5 10 1 1 0 0 1
value=10k
}
C 54300 49600 1 90 0 resistor-2.sym
{
T 53950 50000 5 10 0 0 90 0 1
device=RESISTOR
T 54600 50300 5 10 1 1 180 0 1
refdes=R11
T 54400 49700 5 10 1 1 0 0 1
value=10k
}
C 47700 49000 1 180 0 capacitor-1.sym
{
T 47500 48300 5 10 0 0 180 0 1
device=CAPACITOR
T 46900 48900 5 10 1 1 0 0 1
refdes=C1
T 47500 48100 5 10 0 0 180 0 1
symversion=0.1
T 47700 49000 5 10 1 1 180 0 1
value=0.1u
}
C 55200 49600 1 90 0 resistor-2.sym
{
T 54850 50000 5 10 0 0 90 0 1
device=RESISTOR
T 55600 50300 5 10 1 1 180 0 1
refdes=R13
T 55300 49700 5 10 1 1 0 0 1
value=10k
}
C 47100 47000 1 270 1 resistor-variable-2.sym
{
T 48000 47800 5 10 0 1 90 2 1
device=VARIABLE_RESISTOR
T 46850 47700 5 10 1 1 180 6 1
refdes=P1
T 49100 47800 5 10 1 1 180 0 1
value=value=4.6k,var=Bias
}
C 53100 41800 1 0 1 gnd-1.sym
C 56200 49600 1 90 0 resistor-2.sym
{
T 55850 50000 5 10 0 0 90 0 1
device=RESISTOR
T 56600 50200 5 10 1 1 180 0 1
refdes=R14
T 56300 49700 5 10 1 1 0 0 1
value=100
}
C 40600 50000 1 0 0 9V-plus-1.sym
{
T 40600 50000 5 10 0 0 0 0 1
device=POWER
T 40900 50000 5 10 1 1 0 0 1
value=9V
T 40600 50400 5 10 1 1 0 0 1
refdes=Vcc
}
C 46400 49300 1 90 1 inductor-1.sym
{
T 45900 49100 5 10 0 0 270 2 1
device=INDUCTOR
T 46200 48600 5 10 1 1 180 2 1
refdes=L1
T 45700 49100 5 10 0 0 270 2 1
symversion=0.1
T 46400 49300 5 10 0 0 270 2 1
value=0.5H
}
C 50800 46300 1 180 1 pnp-2.sym
{
T 51400 45900 5 10 0 0 180 6 1
device=PNP_TRANSISTOR
T 51400 45800 5 10 1 1 180 6 1
refdes=Tp1
T 50800 46300 5 10 0 0 180 6 1
value=Vt=26mV,Is=336.7fA,Bf=180,Br=7.16
T 51400 46100 5 10 1 1 180 6 1
model-name=BC858A
}
C 49200 45400 1 0 0 opamp-1.sym
{
T 49900 46200 5 10 0 0 0 0 1
device=OPAMP
T 49900 46000 5 10 1 1 0 0 1
refdes=U1
T 49900 46800 5 10 0 0 0 0 1
symversion=0.1
T 49200 45400 5 10 0 1 0 0 1
value=Vcc=10,Vee=-10,A=1e5
}
C 44800 48400 1 90 0 diode-3.sym
{
T 44250 48850 5 10 0 0 90 0 1
device=DIODE
T 44350 48750 5 10 1 1 90 0 1
refdes=D1
T 44800 48400 5 10 0 0 0 0 1
value=Is=10e-12,mUt=30e-3
}
C 51100 41700 1 0 0 triode.sym
{
T 53900 44500 5 10 1 1 0 0 1
refdes=U2
T 53800 44200 5 10 1 1 0 0 1
value=12ax7
T 53500 43800 5 10 0 1 0 0 1
device=TRIODE
}
C 50700 43100 1 0 0 transformer-3.sym
{
T 51100 44500 5 10 1 1 0 0 1
refdes=Trans
T 50700 44700 5 10 0 0 0 0 1
device=TRANSFORMER
T 51700 43000 5 10 0 1 0 0 1
value=w1=1000,w2=1000,w3=64,R=5400
}
C 53100 41700 1 0 0 pentode.sym
{
T 55900 44300 5 10 1 1 0 0 1
refdes=U5
T 55500 43800 5 10 0 1 0 0 1
device=PENTODE
T 56000 44000 5 10 1 1 0 0 1
value=EL84
}
C 41500 50000 1 0 0 generic-power-1.sym
{
T 41500 50300 5 10 1 1 0 0 1
refdes=Vcc1
T 42000 50300 5 10 1 1 0 0 1
value=16V
T 41500 50000 5 10 0 0 0 0 1
device=POWER
}
C 42500 50000 1 0 0 generic-power-1.sym
{
T 42600 50300 5 10 1 1 0 0 1
refdes=Vb
T 42900 50300 5 10 1 1 0 0 1
value=-16V
T 42500 50000 5 10 0 0 0 0 1
device=POWER
}
C 45200 49300 1 270 0 diode-3.sym
{
T 45750 48850 5 10 0 0 270 0 1
device=DIODE
T 45650 48950 5 10 1 1 270 0 1
refdes=D2
T 45200 49300 5 10 0 0 180 0 1
value=Is=10e-12,mUt=30e-3
}
C 48700 43200 1 0 0 transformer-1.sym
{
T 49000 44500 5 10 1 1 0 0 1
refdes=Trans
T 49000 44500 5 10 0 0 0 0 1
device=TRANSFORMER_S
T 48700 43200 5 10 0 0 0 0 1
value=w1=2000,w2=90,R=5400
}
