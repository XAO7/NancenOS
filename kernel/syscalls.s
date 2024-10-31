.syntax unified
.extern __SysCall_UserMode, __SysCall_Sleep

.int __SysCall_UserMode + 1
.int __SysCall_Sleep + 1
