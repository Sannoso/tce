#!/bin/bash
### TCE TESTCASE
### title: Check correct generation of predicate instructions
#tcecc --clear-plugin-cache > /dev/null

src1=data/main.c 
src2=data/crc.c
src3=data/crcTable.dat

outputprogram=out.tpef
#todo maybe make loop with function call to loop over all input adfs
function test_machine {
    echo $1
    tempdir=$(mktemp -d /tmp/tcecctestXXXXXX) 
    tcecc -O3 -a $1 -k result,test $src1 $src2 -o $tempdir/$outputprogram --temp-dir=$tempdir -d > /dev/null 
#    tcecc -O3 -a $mach1 -k result,test $src1 $src2 -o $tempdir/$outputprogram --temp-dir=$tempdir -d > /dev/null 
    #do grep on ADD
    grep "ADDrrr : InstTCE" $tempdir/GenInstrInfo.td
    #do grep on ADD with immediate
    grep "ADDrri : InstTCE" $tempdir/GenInstrInfo.td
    #do grep on AND
    grep "ANDrrr : InstTCE" $tempdir/GenInstrInfo.td
    #do grep on ANDI
    grep "ANDrri : InstTCE" $tempdir/GenInstrInfo.td
}

test_machine data/pred_fullyconnected.adf
test_machine data/pred_unguardedbus.adf
#test_machine data/pred_noLIMM_goodSIMM.adf
#test_machine data/pred_noLIMM_badSIMM.adf

