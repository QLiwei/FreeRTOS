/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  RTOSDemo                               */
/*      FILE         :  reset_program.asm                      */
/*      DESCRIPTION  :  Reset Program                          */
/*      CPU SERIES   :  RX700                                  */
/*      CPU TYPE     :  RX71M                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                                
                                                                           
 
/************************************************************************/
/*    File Version: V1.01                                               */
/*    Date Generated: 04/03/2015                                        */
/************************************************************************/

    /*reset_program.asm*/

    .list
    .section .text
    .global _PowerON_Reset    /*global Start routine */
    
    .extern _HardwareSetup  /*external Sub-routine to initialise Hardware*/
    .extern _data
    .extern _mdata
    .extern _ebss
    .extern _bss
    .extern _edata
    .extern _main 
    .extern _ustack
    .extern _istack
    .extern _rvectors
    .extern _exit
    
_PowerON_Reset :
/* initialise user stack pointer */
    mvtc    #_ustack,USP

/* initialise interrupt stack pointer */
    mvtc    #_istack,ISP

#ifdef __RXv2__
/* setup exception vector */
    mvtc    #_ExceptVectors, extb    /* EXCEPTION VECTOR ADDRESS    */
#endif
/* setup intb */
    mvtc    #_rvectors_start, intb    /* INTERRUPT VECTOR ADDRESS  definition    */

/* setup FPSW */
    mvtc    #100h, fpsw    

/* load data section from ROM to RAM */

    mov     #_mdata,r2      /* src ROM address of data section in R2 */
    mov     #_data,r1       /* dest start RAM address of data section in R1 */
    mov     #_edata,r3      /* end RAM address of data section in R3 */
    sub    r1,r3            /* size of data section in R3 (R3=R3-R1) */
#ifdef __RX_ALLOW_STRING_INSNS__
    smovf                   /* block copy R3 bytes from R2 to R1 */
#else
    cmp     #0, r3
    beq     2f

1:  mov.b   [r2+], r5
    mov.b   r5, [r1+]
    sub     #1, r3
    bne     1b
2:
#endif


/* bss initialisation : zero out bss */

    mov    #00h,r2      /* load R2 reg with zero */
    mov    #_ebss, r3  /* store the end address of bss in R3 */
    mov    #_bss, r1     /* store the start address of bss in R1 */
    sub   r1,r3           /* size of bss section in R3 (R3=R3-R1) */
    sstr.b
/* call the hardware initialiser */
    mov    #_HardwareSetup,r7
    jsr    r7
    nop

/* setup PSW */
    mvtc    #10000h, psw            /* Set Ubit & Ibit for PSW */

/* change PSW PM to user-mode */
    MVFC   PSW,R1
/* DON'T CHANGE TO USER MODE    OR     #00100000h,R1 */
    PUSH.L R1
    MVFC   PC,R1
    ADD    #10,R1
    PUSH.L R1
    RTE
    NOP
    NOP
#ifdef CPPAPP
    mov    #__rx_init,r7
    jsr    r7
#endif    

/* start user program */
    mov    #_main,r7
    jsr    r7
    mov    #_exit,r7
    jsr    r7

#ifdef CPPAPP
    .global    _rx_run_preinit_array
    .type    _rx_run_preinit_array,@function
_rx_run_preinit_array:
    mov    #__preinit_array_start,r1
    mov    #__preinit_array_end,r2
    mov    #_rx_run_inilist,r7
    jsr    r7

    .global    _rx_run_init_array
    .type    _rx_run_init_array,@function
_rx_run_init_array:
    mov    #__init_array_start,r1
    mov    #__init_array_end,r2
    mov    #4, r3
    mov    #_rx_run_inilist,r7
    jsr    r7

    .global    _rx_run_fini_array
    .type    _rx_run_fini_array,@function
_rx_run_fini_array:
    mov    #__fini_array_start,r2
    mov    #__fini_array_end,r1
    mov    #-4, r3
    /* fall through */

_rx_run_inilist:
next_inilist:
    cmp    r1,r2
    beq.b    done_inilist
    mov.l    [r1],r4
    cmp    #-1, r4
    beq.b    skip_inilist
    cmp    #0, r4
    beq.b    skip_inilist
    pushm    r1-r3
    jsr    r4
    popm    r1-r3
skip_inilist:
    add    r3,r1
    mov    #next_inilist,r7
    jsr    r7
done_inilist:
    rts

    .section    .init,"ax"
    .balign 4

    .global __rx_init
__rx_init:

    .section    .fini,"ax"
    .balign 4

    .global __rx_fini
__rx_fini:
    mov    #_rx_run_fini_array,r7
    jsr    r7

        .section .sdata
        .balign 4
        .global __gp
    .weak   __gp
__gp:   

    .section .data
    .global ___dso_handle
    .weak   ___dso_handle
___dso_handle:
    .long    0

     .section        .init,"ax"
     mov    #_rx_run_preinit_array,r7
     jsr    r7
     mov    #_rx_run_init_array,r7
     jsr    r7
     rts
     
    .global __rx_init_end
__rx_init_end:

    .section        .fini,"ax"

    rts
    .global __rx_fini_end
__rx_fini_end:

#endif

/* call to exit*/
_exit:
    bra  _loop_here
_loop_here:
    bra _loop_here
    
    .text    
    .end
