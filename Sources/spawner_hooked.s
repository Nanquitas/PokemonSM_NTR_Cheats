.arm
.align(2);
.section .rodata

.global hooked_spawner_common
.type hooked_spawner_common, %function
hooked_spawner_common:
    ldrh    r0, [r5]
    ldr     r0, =g_selected_level
    ldr     r0, [r0]
    strb    r0, [r4, #4]
    ldr     r0, =g_selected_id
    ldr     r0, [r0]
    bx      lr 

.global hooked1_spawner
.type hooked1_spawner, %function
hooked1_spawner:
    bl      hooked_spawner_common
    mov     r1, #0
    ldr     lr, =spawn_first_hook
    ldr     pc, [lr, #8]

.global hooked2_spawner
.type hooked2_spawner, %function
hooked2_spawner:
    bl      hooked_spawner_common
    bic     r0, r0, #0xF800
    ldr     lr, =spawn_second_hook
    ldr     pc, [lr, #8]

.global hooked3_spawner
.type hooked3_spawner, %function
hooked3_spawner:
    bl      hooked_spawner_common
    bic     r2, r0, #0xF800
    ldr     lr, =spawn_third_hook
    ldr     pc, [lr, #8]

