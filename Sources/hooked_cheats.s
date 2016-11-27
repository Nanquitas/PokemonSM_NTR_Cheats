.arm
.align(2);
.section .rodata

.global hooked_always_catch
.type hooked_always_catch, %function
hooked_always_catch:
    ldrb    r0, [r0, #8]
    push    {r0, r1}
    ldr     r0, [sp, #0xC]
    ldr     r1, =0x006D839C
    cmp     r1, r0
    subeq   r0, r0, #0xF8
    streq   r0, [sp, #0xC]
    pop     {r0, r1}
    ldmfd   sp!, {r4, pc}

.global hooked_catch_trainers_pokemon
.type hooked_catch_trainers_pokemon, %function
hooked_catch_trainers_pokemon:
    mov     r3, r2
    mov     r12, r2
    push    {r0, r1}
    ldr     r0, [sp, #0x8]
    ldr     r1, =0x006D22AC
    cmp     r1, r0
    ldreq   r0, [r4, #4]
    ldreq   r0, [r0, #0xC]
    moveq   r1, #0
    streqb  r1, [r0]
    ldr     lr, =catch_trainers_pokemon_hook
    ldr     lr, [lr, #8]
    pop     {r0, r1}
    mov     pc, lr


.global hooked_wild_shiny
.type hooked_wild_shiny, %function
hooked_wild_shiny:
    mov     r6, #2
    str     r6, [r4, #0xC]
    add     r6, r4, #0x20
    ldr     r5, =wild_shiny_hook
    ldr     r5, [r5, #8]
    push    {r5}
    ldr     r5, [r1, #0x30]
    pop     {pc}

.global hooked_egg_instant_hatch
.type hooked_egg_instant_hatch, %function
hooked_egg_instant_hatch:
    ldr     r0, [sp, #0xC]
    ldr     r5, =0x006CE724
    cmp     r0, r5
    moveq   r0, #0
    movne   r0, r4
    ldmfd   sp!, {r4-r6, pc}


.global hooked_experience_modifier
.type hooked_experience_modifier, %function
hooked_experience_modifier:
    ldrh    r0, [r0, #0x22]
    bl      multiply_exp
    ldmfd   sp!, {r4, pc}

.global hooked_pc_option1
.type hooked_pc_option1, %function
hooked_pc_option1:
    ldr     lr, =g_pc_option_hook1
    ldr     lr, [lr, #8]
    push    {r1, r2, r3, lr}
    ldr     r1, =0x00636000
    ldr     r2, [r1]
    mov     r3, #0
    str     r3, [r1]
    mov     r3, #0x1300
    add     r3, r3, #0x93
    cmp     r2, r3
    moveq   r4, #0
    movne   r4, r0
    pop     {r1}
    mov     r1, r5
    pop     {r2, r3, pc}


.global hooked_pc_option2
.type hooked_pc_option2, %function
hooked_pc_option2:
    cmp     r0, #0xE
    ldrne   lr, =exit
    ldrne   pc, =0x374DD4 
    push    {r0, r1, r2, r3}
    sub     sp, sp, #0x10
    mov     r0, #0
    str     r0, [sp]
    str     r0, [sp, #4]
    str     r0, [sp, #8]
    str     r0, [sp, #0xc]
    mov     r3, r0
    mov     r2, r0
    mov     r1, #0x1300
    add     r1, r1, #0x93
    ldr     r0, =0x00636000
    str     r1, [r0]
    ldr     r0, =0x0067206C
    ldr     r0, [r0]
    mov     lr, pc
    ldr     pc, =0x38C128
    mov     r0, #2
    add     sp, sp, #0x10
    pop     {r0, r1, r2, r3}
exit:
    cmp     r0, #0
    ldr     lr, =g_pc_option_hook2
    ldr     pc, [lr, #8]

