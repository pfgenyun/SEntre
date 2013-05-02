/************************************************************
 * Copyright (c) 2010-present Peng Fei.  All rights reserved.
 ************************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistribution and use in source and binary forms must authorized by
 * Peng Fei.
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 */

/***************************************************************************
  syscall.h - SYS and NR defines
 **************************************************************************/

#ifndef SYSCALL_H
#define SYSCALL_H 

/* Copied from /usr/include/asm/unistd.h */

#if _MIPS_SIM == _MIPS_SIM_ABI32

/*
 * Linux o32 style syscalls are in the range from 4000 to 4999.
 */
#define __NR_Linux			4000
#define __NR_syscall			(__NR_Linux +   0)
#define __NR_exit			(__NR_Linux +   1)
#define __NR_fork			(__NR_Linux +   2)
#define __NR_read			(__NR_Linux +   3)
#define __NR_write			(__NR_Linux +   4)
#define __NR_open			(__NR_Linux +   5)
#define __NR_close			(__NR_Linux +   6)
#define __NR_waitpid			(__NR_Linux +   7)
#define __NR_creat			(__NR_Linux +   8)
#define __NR_link			(__NR_Linux +   9)
#define __NR_unlink			(__NR_Linux +  10)
#define __NR_execve			(__NR_Linux +  11)
#define __NR_chdir			(__NR_Linux +  12)
#define __NR_time			(__NR_Linux +  13)
#define __NR_mknod			(__NR_Linux +  14)
#define __NR_chmod			(__NR_Linux +  15)
#define __NR_lchown			(__NR_Linux +  16)
#define __NR_break			(__NR_Linux +  17)
#define __NR_unused18			(__NR_Linux +  18)
#define __NR_lseek			(__NR_Linux +  19)
#define __NR_getpid			(__NR_Linux +  20)
#define __NR_mount			(__NR_Linux +  21)
#define __NR_umount			(__NR_Linux +  22)
#define __NR_setuid			(__NR_Linux +  23)
#define __NR_getuid			(__NR_Linux +  24)
#define __NR_stime			(__NR_Linux +  25)
#define __NR_ptrace			(__NR_Linux +  26)
#define __NR_alarm			(__NR_Linux +  27)
#define __NR_unused28			(__NR_Linux +  28)
#define __NR_pause			(__NR_Linux +  29)
#define __NR_utime			(__NR_Linux +  30)
#define __NR_stty			(__NR_Linux +  31)
#define __NR_gtty			(__NR_Linux +  32)
#define __NR_access			(__NR_Linux +  33)
#define __NR_nice			(__NR_Linux +  34)
#define __NR_ftime			(__NR_Linux +  35)
#define __NR_sync			(__NR_Linux +  36)
#define __NR_kill			(__NR_Linux +  37)
#define __NR_rename			(__NR_Linux +  38)
#define __NR_mkdir			(__NR_Linux +  39)
#define __NR_rmdir			(__NR_Linux +  40)
#define __NR_dup			(__NR_Linux +  41)
#define __NR_pipe			(__NR_Linux +  42)
#define __NR_times			(__NR_Linux +  43)
#define __NR_prof			(__NR_Linux +  44)
#define __NR_brk			(__NR_Linux +  45)
#define __NR_setgid			(__NR_Linux +  46)
#define __NR_getgid			(__NR_Linux +  47)
#define __NR_signal			(__NR_Linux +  48)
#define __NR_geteuid			(__NR_Linux +  49)
#define __NR_getegid			(__NR_Linux +  50)
#define __NR_acct			(__NR_Linux +  51)
#define __NR_umount2			(__NR_Linux +  52)
#define __NR_lock			(__NR_Linux +  53)
#define __NR_ioctl			(__NR_Linux +  54)
#define __NR_fcntl			(__NR_Linux +  55)
#define __NR_mpx			(__NR_Linux +  56)
#define __NR_setpgid			(__NR_Linux +  57)
#define __NR_ulimit			(__NR_Linux +  58)
#define __NR_unused59			(__NR_Linux +  59)
#define __NR_umask			(__NR_Linux +  60)
#define __NR_chroot			(__NR_Linux +  61)
#define __NR_ustat			(__NR_Linux +  62)
#define __NR_dup2			(__NR_Linux +  63)
#define __NR_getppid			(__NR_Linux +  64)
#define __NR_getpgrp			(__NR_Linux +  65)
#define __NR_setsid			(__NR_Linux +  66)
#define __NR_sigaction			(__NR_Linux +  67)
#define __NR_sgetmask			(__NR_Linux +  68)
#define __NR_ssetmask			(__NR_Linux +  69)
#define __NR_setreuid			(__NR_Linux +  70)
#define __NR_setregid			(__NR_Linux +  71)
#define __NR_sigsuspend			(__NR_Linux +  72)
#define __NR_sigpending			(__NR_Linux +  73)
#define __NR_sethostname		(__NR_Linux +  74)
#define __NR_setrlimit			(__NR_Linux +  75)
#define __NR_getrlimit			(__NR_Linux +  76)
#define __NR_getrusage			(__NR_Linux +  77)
#define __NR_gettimeofday		(__NR_Linux +  78)
#define __NR_settimeofday		(__NR_Linux +  79)
#define __NR_getgroups			(__NR_Linux +  80)
#define __NR_setgroups			(__NR_Linux +  81)
#define __NR_reserved82			(__NR_Linux +  82)
#define __NR_symlink			(__NR_Linux +  83)
#define __NR_unused84			(__NR_Linux +  84)
#define __NR_readlink			(__NR_Linux +  85)
#define __NR_uselib			(__NR_Linux +  86)
#define __NR_swapon			(__NR_Linux +  87)
#define __NR_reboot			(__NR_Linux +  88)
#define __NR_readdir			(__NR_Linux +  89)
#define __NR_mmap			(__NR_Linux +  90)
#define __NR_munmap			(__NR_Linux +  91)
#define __NR_truncate			(__NR_Linux +  92)
#define __NR_ftruncate			(__NR_Linux +  93)
#define __NR_fchmod			(__NR_Linux +  94)
#define __NR_fchown			(__NR_Linux +  95)
#define __NR_getpriority		(__NR_Linux +  96)
#define __NR_setpriority		(__NR_Linux +  97)
#define __NR_profil			(__NR_Linux +  98)
#define __NR_statfs			(__NR_Linux +  99)
#define __NR_fstatfs			(__NR_Linux + 100)
#define __NR_ioperm			(__NR_Linux + 101)
#define __NR_socketcall			(__NR_Linux + 102)
#define __NR_syslog			(__NR_Linux + 103)
#define __NR_setitimer			(__NR_Linux + 104)
#define __NR_getitimer			(__NR_Linux + 105)
#define __NR_stat			(__NR_Linux + 106)
#define __NR_lstat			(__NR_Linux + 107)
#define __NR_fstat			(__NR_Linux + 108)
#define __NR_unused109			(__NR_Linux + 109)
#define __NR_iopl			(__NR_Linux + 110)
#define __NR_vhangup			(__NR_Linux + 111)
#define __NR_idle			(__NR_Linux + 112)
#define __NR_vm86			(__NR_Linux + 113)
#define __NR_wait4			(__NR_Linux + 114)
#define __NR_swapoff			(__NR_Linux + 115)
#define __NR_sysinfo			(__NR_Linux + 116)
#define __NR_ipc			(__NR_Linux + 117)
#define __NR_fsync			(__NR_Linux + 118)
#define __NR_sigreturn			(__NR_Linux + 119)
#define __NR_clone			(__NR_Linux + 120)
#define __NR_setdomainname		(__NR_Linux + 121)
#define __NR_uname			(__NR_Linux + 122)
#define __NR_modify_ldt			(__NR_Linux + 123)
#define __NR_adjtimex			(__NR_Linux + 124)
#define __NR_mprotect			(__NR_Linux + 125)
#define __NR_sigprocmask		(__NR_Linux + 126)
#define __NR_create_module		(__NR_Linux + 127)
#define __NR_init_module		(__NR_Linux + 128)
#define __NR_delete_module		(__NR_Linux + 129)
#define __NR_get_kernel_syms		(__NR_Linux + 130)
#define __NR_quotactl			(__NR_Linux + 131)
#define __NR_getpgid			(__NR_Linux + 132)
#define __NR_fchdir			(__NR_Linux + 133)
#define __NR_bdflush			(__NR_Linux + 134)
#define __NR_sysfs			(__NR_Linux + 135)
#define __NR_personality		(__NR_Linux + 136)
#define __NR_afs_syscall		(__NR_Linux + 137) /* Syscall for Andrew File System */
#define __NR_setfsuid			(__NR_Linux + 138)
#define __NR_setfsgid			(__NR_Linux + 139)
#define __NR__llseek			(__NR_Linux + 140)
#define __NR_getdents			(__NR_Linux + 141)
#define __NR__newselect			(__NR_Linux + 142)
#define __NR_flock			(__NR_Linux + 143)
#define __NR_msync			(__NR_Linux + 144)
#define __NR_readv			(__NR_Linux + 145)
#define __NR_writev			(__NR_Linux + 146)
#define __NR_cacheflush			(__NR_Linux + 147)
#define __NR_cachectl			(__NR_Linux + 148)
#define __NR_sysmips			(__NR_Linux + 149)
#define __NR_unused150			(__NR_Linux + 150)
#define __NR_getsid			(__NR_Linux + 151)
#define __NR_fdatasync			(__NR_Linux + 152)
#define __NR__sysctl			(__NR_Linux + 153)
#define __NR_mlock			(__NR_Linux + 154)
#define __NR_munlock			(__NR_Linux + 155)
#define __NR_mlockall			(__NR_Linux + 156)
#define __NR_munlockall			(__NR_Linux + 157)
#define __NR_sched_setparam		(__NR_Linux + 158)
#define __NR_sched_getparam		(__NR_Linux + 159)
#define __NR_sched_setscheduler		(__NR_Linux + 160)
#define __NR_sched_getscheduler		(__NR_Linux + 161)
#define __NR_sched_yield		(__NR_Linux + 162)
#define __NR_sched_get_priority_max	(__NR_Linux + 163)
#define __NR_sched_get_priority_min	(__NR_Linux + 164)
#define __NR_sched_rr_get_interval	(__NR_Linux + 165)
#define __NR_nanosleep			(__NR_Linux + 166)
#define __NR_mremap			(__NR_Linux + 167)
#define __NR_accept			(__NR_Linux + 168)
#define __NR_bind			(__NR_Linux + 169)
#define __NR_connect			(__NR_Linux + 170)
#define __NR_getpeername		(__NR_Linux + 171)
#define __NR_getsockname		(__NR_Linux + 172)
#define __NR_getsockopt			(__NR_Linux + 173)
#define __NR_listen			(__NR_Linux + 174)
#define __NR_recv			(__NR_Linux + 175)
#define __NR_recvfrom			(__NR_Linux + 176)
#define __NR_recvmsg			(__NR_Linux + 177)
#define __NR_send			(__NR_Linux + 178)
#define __NR_sendmsg			(__NR_Linux + 179)
#define __NR_sendto			(__NR_Linux + 180)
#define __NR_setsockopt			(__NR_Linux + 181)
#define __NR_shutdown			(__NR_Linux + 182)
#define __NR_socket			(__NR_Linux + 183)
#define __NR_socketpair			(__NR_Linux + 184)
#define __NR_setresuid			(__NR_Linux + 185)
#define __NR_getresuid			(__NR_Linux + 186)
#define __NR_query_module		(__NR_Linux + 187)
#define __NR_poll			(__NR_Linux + 188)
#define __NR_nfsservctl			(__NR_Linux + 189)
#define __NR_setresgid			(__NR_Linux + 190)
#define __NR_getresgid			(__NR_Linux + 191)
#define __NR_prctl			(__NR_Linux + 192)
#define __NR_rt_sigreturn		(__NR_Linux + 193)
#define __NR_rt_sigaction		(__NR_Linux + 194)
#define __NR_rt_sigprocmask		(__NR_Linux + 195)
#define __NR_rt_sigpending		(__NR_Linux + 196)
#define __NR_rt_sigtimedwait		(__NR_Linux + 197)
#define __NR_rt_sigqueueinfo		(__NR_Linux + 198)
#define __NR_rt_sigsuspend		(__NR_Linux + 199)
#define __NR_pread64			(__NR_Linux + 200)
#define __NR_pwrite64			(__NR_Linux + 201)
#define __NR_chown			(__NR_Linux + 202)
#define __NR_getcwd			(__NR_Linux + 203)
#define __NR_capget			(__NR_Linux + 204)
#define __NR_capset			(__NR_Linux + 205)
#define __NR_sigaltstack		(__NR_Linux + 206)
#define __NR_sendfile			(__NR_Linux + 207)
#define __NR_getpmsg			(__NR_Linux + 208)
#define __NR_putpmsg			(__NR_Linux + 209)
#define __NR_mmap2			(__NR_Linux + 210)
#define __NR_truncate64			(__NR_Linux + 211)
#define __NR_ftruncate64		(__NR_Linux + 212)
#define __NR_stat64			(__NR_Linux + 213)
#define __NR_lstat64			(__NR_Linux + 214)
#define __NR_fstat64			(__NR_Linux + 215)
#define __NR_pivot_root			(__NR_Linux + 216)
#define __NR_mincore			(__NR_Linux + 217)
#define __NR_madvise			(__NR_Linux + 218)
#define __NR_getdents64			(__NR_Linux + 219)
#define __NR_fcntl64			(__NR_Linux + 220)
#define __NR_reserved221		(__NR_Linux + 221)
#define __NR_gettid			(__NR_Linux + 222)
#define __NR_readahead			(__NR_Linux + 223)
#define __NR_setxattr			(__NR_Linux + 224)
#define __NR_lsetxattr			(__NR_Linux + 225)
#define __NR_fsetxattr			(__NR_Linux + 226)
#define __NR_getxattr			(__NR_Linux + 227)
#define __NR_lgetxattr			(__NR_Linux + 228)
#define __NR_fgetxattr			(__NR_Linux + 229)
#define __NR_listxattr			(__NR_Linux + 230)
#define __NR_llistxattr			(__NR_Linux + 231)
#define __NR_flistxattr			(__NR_Linux + 232)
#define __NR_removexattr		(__NR_Linux + 233)
#define __NR_lremovexattr		(__NR_Linux + 234)
#define __NR_fremovexattr		(__NR_Linux + 235)
#define __NR_tkill			(__NR_Linux + 236)
#define __NR_sendfile64			(__NR_Linux + 237)
#define __NR_futex			(__NR_Linux + 238)
#define __NR_sched_setaffinity		(__NR_Linux + 239)
#define __NR_sched_getaffinity		(__NR_Linux + 240)
#define __NR_io_setup			(__NR_Linux + 241)
#define __NR_io_destroy			(__NR_Linux + 242)
#define __NR_io_getevents		(__NR_Linux + 243)
#define __NR_io_submit			(__NR_Linux + 244)
#define __NR_io_cancel			(__NR_Linux + 245)
#define __NR_exit_group			(__NR_Linux + 246)
#define __NR_lookup_dcookie		(__NR_Linux + 247)
#define __NR_epoll_create		(__NR_Linux + 248)
#define __NR_epoll_ctl			(__NR_Linux + 249)
#define __NR_epoll_wait			(__NR_Linux + 250)
#define __NR_remap_file_pages		(__NR_Linux + 251)
#define __NR_set_tid_address		(__NR_Linux + 252)
#define __NR_restart_syscall		(__NR_Linux + 253)
#define __NR_fadvise64			(__NR_Linux + 254)
#define __NR_statfs64			(__NR_Linux + 255)
#define __NR_fstatfs64			(__NR_Linux + 256)
#define __NR_timer_create		(__NR_Linux + 257)
#define __NR_timer_settime		(__NR_Linux + 258)
#define __NR_timer_gettime		(__NR_Linux + 259)
#define __NR_timer_getoverrun		(__NR_Linux + 260)
#define __NR_timer_delete		(__NR_Linux + 261)
#define __NR_clock_settime		(__NR_Linux + 262)
#define __NR_clock_gettime		(__NR_Linux + 263)
#define __NR_clock_getres		(__NR_Linux + 264)
#define __NR_clock_nanosleep		(__NR_Linux + 265)
#define __NR_tgkill			(__NR_Linux + 266)
#define __NR_utimes			(__NR_Linux + 267)
#define __NR_mbind			(__NR_Linux + 268)
#define __NR_get_mempolicy		(__NR_Linux + 269)
#define __NR_set_mempolicy		(__NR_Linux + 270)
#define __NR_mq_open			(__NR_Linux + 271)
#define __NR_mq_unlink			(__NR_Linux + 272)
#define __NR_mq_timedsend		(__NR_Linux + 273)
#define __NR_mq_timedreceive		(__NR_Linux + 274)
#define __NR_mq_notify			(__NR_Linux + 275)
#define __NR_mq_getsetattr		(__NR_Linux + 276)
#define __NR_vserver			(__NR_Linux + 277)
#define __NR_waitid			(__NR_Linux + 278)
/* #define __NR_sys_setaltroot		(__NR_Linux + 279) */
#define __NR_add_key			(__NR_Linux + 280)
#define __NR_request_key		(__NR_Linux + 281)
#define __NR_keyctl			(__NR_Linux + 282)
#define __NR_set_thread_area		(__NR_Linux + 283)
#define __NR_inotify_init		(__NR_Linux + 284)
#define __NR_inotify_add_watch		(__NR_Linux + 285)
#define __NR_inotify_rm_watch		(__NR_Linux + 286)
#define __NR_migrate_pages		(__NR_Linux + 287)
#define __NR_openat			(__NR_Linux + 288)
#define __NR_mkdirat			(__NR_Linux + 289)
#define __NR_mknodat			(__NR_Linux + 290)
#define __NR_fchownat			(__NR_Linux + 291)
#define __NR_futimesat			(__NR_Linux + 292)
#define __NR_fstatat64			(__NR_Linux + 293)
#define __NR_unlinkat			(__NR_Linux + 294)
#define __NR_renameat			(__NR_Linux + 295)
#define __NR_linkat			(__NR_Linux + 296)
#define __NR_symlinkat			(__NR_Linux + 297)
#define __NR_readlinkat			(__NR_Linux + 298)
#define __NR_fchmodat			(__NR_Linux + 299)
#define __NR_faccessat			(__NR_Linux + 300)
#define __NR_pselect6			(__NR_Linux + 301)
#define __NR_ppoll			(__NR_Linux + 302)
#define __NR_unshare			(__NR_Linux + 303)
#define __NR_splice			(__NR_Linux + 304)
#define __NR_sync_file_range		(__NR_Linux + 305)
#define __NR_tee			(__NR_Linux + 306)
#define __NR_vmsplice			(__NR_Linux + 307)
#define __NR_move_pages			(__NR_Linux + 308)
#define __NR_set_robust_list		(__NR_Linux + 309)
#define __NR_get_robust_list		(__NR_Linux + 310)
#define __NR_kexec_load			(__NR_Linux + 311)
#define __NR_getcpu			(__NR_Linux + 312)
#define __NR_epoll_pwait		(__NR_Linux + 313)
#define __NR_ioprio_set			(__NR_Linux + 314)
#define __NR_ioprio_get			(__NR_Linux + 315)
#define __NR_utimensat			(__NR_Linux + 316)
#define __NR_signalfd			(__NR_Linux + 317)
#define __NR_timerfd			(__NR_Linux + 318)
#define __NR_eventfd			(__NR_Linux + 319)
#define __NR_fallocate			(__NR_Linux + 320)
#define __NR_timerfd_create		(__NR_Linux + 321)
#define __NR_timerfd_gettime		(__NR_Linux + 322)
#define __NR_timerfd_settime		(__NR_Linux + 323)
#define __NR_signalfd4			(__NR_Linux + 324)
#define __NR_eventfd2			(__NR_Linux + 325)
#define __NR_epoll_create1		(__NR_Linux + 326)
#define __NR_dup3			(__NR_Linux + 327)
#define __NR_pipe2			(__NR_Linux + 328)
#define __NR_inotify_init1		(__NR_Linux + 329)
#define __NR_preadv			(__NR_Linux + 330)
#define __NR_pwritev			(__NR_Linux + 331)
#define __NR_rt_tgsigqueueinfo		(__NR_Linux + 332)
#define __NR_perf_event_open		(__NR_Linux + 333)
#define __NR_accept4			(__NR_Linux + 334)
#define __NR_recvmmsg			(__NR_Linux + 335)

/*
 * Offset of the last Linux o32 flavoured syscall
 */
#define __NR_Linux_syscalls		335

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#define __NR_O32_Linux			4000
#define __NR_O32_Linux_syscalls		335

#if _MIPS_SIM == _MIPS_SIM_ABI64

/*
 * Linux 64-bit syscalls are in the range from 5000 to 5999.
 */
#define __NR_Linux			5000
#define __NR_read			(__NR_Linux +   0)
#define __NR_write			(__NR_Linux +   1)
#define __NR_open			(__NR_Linux +   2)
#define __NR_close			(__NR_Linux +   3)
#define __NR_stat			(__NR_Linux +   4)
#define __NR_fstat			(__NR_Linux +   5)
#define __NR_lstat			(__NR_Linux +   6)
#define __NR_poll			(__NR_Linux +   7)
#define __NR_lseek			(__NR_Linux +   8)
#define __NR_mmap			(__NR_Linux +   9)
#define __NR_mprotect			(__NR_Linux +  10)
#define __NR_munmap			(__NR_Linux +  11)
#define __NR_brk			(__NR_Linux +  12)
#define __NR_rt_sigaction		(__NR_Linux +  13)
#define __NR_rt_sigprocmask		(__NR_Linux +  14)
#define __NR_ioctl			(__NR_Linux +  15)
#define __NR_pread64			(__NR_Linux +  16)
#define __NR_pwrite64			(__NR_Linux +  17)
#define __NR_readv			(__NR_Linux +  18)
#define __NR_writev			(__NR_Linux +  19)
#define __NR_access			(__NR_Linux +  20)
#define __NR_pipe			(__NR_Linux +  21)
#define __NR__newselect			(__NR_Linux +  22)
#define __NR_sched_yield		(__NR_Linux +  23)
#define __NR_mremap			(__NR_Linux +  24)
#define __NR_msync			(__NR_Linux +  25)
#define __NR_mincore			(__NR_Linux +  26)
#define __NR_madvise			(__NR_Linux +  27)
#define __NR_shmget			(__NR_Linux +  28)
#define __NR_shmat			(__NR_Linux +  29)
#define __NR_shmctl			(__NR_Linux +  30)
#define __NR_dup			(__NR_Linux +  31)
#define __NR_dup2			(__NR_Linux +  32)
#define __NR_pause			(__NR_Linux +  33)
#define __NR_nanosleep			(__NR_Linux +  34)
#define __NR_getitimer			(__NR_Linux +  35)
#define __NR_setitimer			(__NR_Linux +  36)
#define __NR_alarm			(__NR_Linux +  37)
#define __NR_getpid			(__NR_Linux +  38)
#define __NR_sendfile			(__NR_Linux +  39)
#define __NR_socket			(__NR_Linux +  40)
#define __NR_connect			(__NR_Linux +  41)
#define __NR_accept			(__NR_Linux +  42)
#define __NR_sendto			(__NR_Linux +  43)
#define __NR_recvfrom			(__NR_Linux +  44)
#define __NR_sendmsg			(__NR_Linux +  45)
#define __NR_recvmsg			(__NR_Linux +  46)
#define __NR_shutdown			(__NR_Linux +  47)
#define __NR_bind			(__NR_Linux +  48)
#define __NR_listen			(__NR_Linux +  49)
#define __NR_getsockname		(__NR_Linux +  50)
#define __NR_getpeername		(__NR_Linux +  51)
#define __NR_socketpair			(__NR_Linux +  52)
#define __NR_setsockopt			(__NR_Linux +  53)
#define __NR_getsockopt			(__NR_Linux +  54)
#define __NR_clone			(__NR_Linux +  55)
#define __NR_fork			(__NR_Linux +  56)
#define __NR_execve			(__NR_Linux +  57)
#define __NR_exit			(__NR_Linux +  58)
#define __NR_wait4			(__NR_Linux +  59)
#define __NR_kill			(__NR_Linux +  60)
#define __NR_uname			(__NR_Linux +  61)
#define __NR_semget			(__NR_Linux +  62)
#define __NR_semop			(__NR_Linux +  63)
#define __NR_semctl			(__NR_Linux +  64)
#define __NR_shmdt			(__NR_Linux +  65)
#define __NR_msgget			(__NR_Linux +  66)
#define __NR_msgsnd			(__NR_Linux +  67)
#define __NR_msgrcv			(__NR_Linux +  68)
#define __NR_msgctl			(__NR_Linux +  69)
#define __NR_fcntl			(__NR_Linux +  70)
#define __NR_flock			(__NR_Linux +  71)
#define __NR_fsync			(__NR_Linux +  72)
#define __NR_fdatasync			(__NR_Linux +  73)
#define __NR_truncate			(__NR_Linux +  74)
#define __NR_ftruncate			(__NR_Linux +  75)
#define __NR_getdents			(__NR_Linux +  76)
#define __NR_getcwd			(__NR_Linux +  77)
#define __NR_chdir			(__NR_Linux +  78)
#define __NR_fchdir			(__NR_Linux +  79)
#define __NR_rename			(__NR_Linux +  80)
#define __NR_mkdir			(__NR_Linux +  81)
#define __NR_rmdir			(__NR_Linux +  82)
#define __NR_creat			(__NR_Linux +  83)
#define __NR_link			(__NR_Linux +  84)
#define __NR_unlink			(__NR_Linux +  85)
#define __NR_symlink			(__NR_Linux +  86)
#define __NR_readlink			(__NR_Linux +  87)
#define __NR_chmod			(__NR_Linux +  88)
#define __NR_fchmod			(__NR_Linux +  89)
#define __NR_chown			(__NR_Linux +  90)
#define __NR_fchown			(__NR_Linux +  91)
#define __NR_lchown			(__NR_Linux +  92)
#define __NR_umask			(__NR_Linux +  93)
#define __NR_gettimeofday		(__NR_Linux +  94)
#define __NR_getrlimit			(__NR_Linux +  95)
#define __NR_getrusage			(__NR_Linux +  96)
#define __NR_sysinfo			(__NR_Linux +  97)
#define __NR_times			(__NR_Linux +  98)
#define __NR_ptrace			(__NR_Linux +  99)
#define __NR_getuid			(__NR_Linux + 100)
#define __NR_syslog			(__NR_Linux + 101)
#define __NR_getgid			(__NR_Linux + 102)
#define __NR_setuid			(__NR_Linux + 103)
#define __NR_setgid			(__NR_Linux + 104)
#define __NR_geteuid			(__NR_Linux + 105)
#define __NR_getegid			(__NR_Linux + 106)
#define __NR_setpgid			(__NR_Linux + 107)
#define __NR_getppid			(__NR_Linux + 108)
#define __NR_getpgrp			(__NR_Linux + 109)
#define __NR_setsid			(__NR_Linux + 110)
#define __NR_setreuid			(__NR_Linux + 111)
#define __NR_setregid			(__NR_Linux + 112)
#define __NR_getgroups			(__NR_Linux + 113)
#define __NR_setgroups			(__NR_Linux + 114)
#define __NR_setresuid			(__NR_Linux + 115)
#define __NR_getresuid			(__NR_Linux + 116)
#define __NR_setresgid			(__NR_Linux + 117)
#define __NR_getresgid			(__NR_Linux + 118)
#define __NR_getpgid			(__NR_Linux + 119)
#define __NR_setfsuid			(__NR_Linux + 120)
#define __NR_setfsgid			(__NR_Linux + 121)
#define __NR_getsid			(__NR_Linux + 122)
#define __NR_capget			(__NR_Linux + 123)
#define __NR_capset			(__NR_Linux + 124)
#define __NR_rt_sigpending		(__NR_Linux + 125)
#define __NR_rt_sigtimedwait		(__NR_Linux + 126)
#define __NR_rt_sigqueueinfo		(__NR_Linux + 127)
#define __NR_rt_sigsuspend		(__NR_Linux + 128)
#define __NR_sigaltstack		(__NR_Linux + 129)
#define __NR_utime			(__NR_Linux + 130)
#define __NR_mknod			(__NR_Linux + 131)
#define __NR_personality		(__NR_Linux + 132)
#define __NR_ustat			(__NR_Linux + 133)
#define __NR_statfs			(__NR_Linux + 134)
#define __NR_fstatfs			(__NR_Linux + 135)
#define __NR_sysfs			(__NR_Linux + 136)
#define __NR_getpriority		(__NR_Linux + 137)
#define __NR_setpriority		(__NR_Linux + 138)
#define __NR_sched_setparam		(__NR_Linux + 139)
#define __NR_sched_getparam		(__NR_Linux + 140)
#define __NR_sched_setscheduler		(__NR_Linux + 141)
#define __NR_sched_getscheduler		(__NR_Linux + 142)
#define __NR_sched_get_priority_max	(__NR_Linux + 143)
#define __NR_sched_get_priority_min	(__NR_Linux + 144)
#define __NR_sched_rr_get_interval	(__NR_Linux + 145)
#define __NR_mlock			(__NR_Linux + 146)
#define __NR_munlock			(__NR_Linux + 147)
#define __NR_mlockall			(__NR_Linux + 148)
#define __NR_munlockall			(__NR_Linux + 149)
#define __NR_vhangup			(__NR_Linux + 150)
#define __NR_pivot_root			(__NR_Linux + 151)
#define __NR__sysctl			(__NR_Linux + 152)
#define __NR_prctl			(__NR_Linux + 153)
#define __NR_adjtimex			(__NR_Linux + 154)
#define __NR_setrlimit			(__NR_Linux + 155)
#define __NR_chroot			(__NR_Linux + 156)
#define __NR_sync			(__NR_Linux + 157)
#define __NR_acct			(__NR_Linux + 158)
#define __NR_settimeofday		(__NR_Linux + 159)
#define __NR_mount			(__NR_Linux + 160)
#define __NR_umount2			(__NR_Linux + 161)
#define __NR_swapon			(__NR_Linux + 162)
#define __NR_swapoff			(__NR_Linux + 163)
#define __NR_reboot			(__NR_Linux + 164)
#define __NR_sethostname		(__NR_Linux + 165)
#define __NR_setdomainname		(__NR_Linux + 166)
#define __NR_create_module		(__NR_Linux + 167)
#define __NR_init_module		(__NR_Linux + 168)
#define __NR_delete_module		(__NR_Linux + 169)
#define __NR_get_kernel_syms		(__NR_Linux + 170)
#define __NR_query_module		(__NR_Linux + 171)
#define __NR_quotactl			(__NR_Linux + 172)
#define __NR_nfsservctl			(__NR_Linux + 173)
#define __NR_getpmsg			(__NR_Linux + 174)
#define __NR_putpmsg			(__NR_Linux + 175)
#define __NR_afs_syscall		(__NR_Linux + 176)
#define __NR_reserved177		(__NR_Linux + 177)
#define __NR_gettid			(__NR_Linux + 178)
#define __NR_readahead			(__NR_Linux + 179)
#define __NR_setxattr			(__NR_Linux + 180)
#define __NR_lsetxattr			(__NR_Linux + 181)
#define __NR_fsetxattr			(__NR_Linux + 182)
#define __NR_getxattr			(__NR_Linux + 183)
#define __NR_lgetxattr			(__NR_Linux + 184)
#define __NR_fgetxattr			(__NR_Linux + 185)
#define __NR_listxattr			(__NR_Linux + 186)
#define __NR_llistxattr			(__NR_Linux + 187)
#define __NR_flistxattr			(__NR_Linux + 188)
#define __NR_removexattr		(__NR_Linux + 189)
#define __NR_lremovexattr		(__NR_Linux + 190)
#define __NR_fremovexattr		(__NR_Linux + 191)
#define __NR_tkill			(__NR_Linux + 192)
#define __NR_reserved193		(__NR_Linux + 193)
#define __NR_futex			(__NR_Linux + 194)
#define __NR_sched_setaffinity		(__NR_Linux + 195)
#define __NR_sched_getaffinity		(__NR_Linux + 196)
#define __NR_cacheflush			(__NR_Linux + 197)
#define __NR_cachectl			(__NR_Linux + 198)
#define __NR_sysmips			(__NR_Linux + 199)
#define __NR_io_setup			(__NR_Linux + 200)
#define __NR_io_destroy			(__NR_Linux + 201)
#define __NR_io_getevents		(__NR_Linux + 202)
#define __NR_io_submit			(__NR_Linux + 203)
#define __NR_io_cancel			(__NR_Linux + 204)
#define __NR_exit_group			(__NR_Linux + 205)
#define __NR_lookup_dcookie		(__NR_Linux + 206)
#define __NR_epoll_create		(__NR_Linux + 207)
#define __NR_epoll_ctl			(__NR_Linux + 208)
#define __NR_epoll_wait			(__NR_Linux + 209)
#define __NR_remap_file_pages		(__NR_Linux + 210)
#define __NR_rt_sigreturn		(__NR_Linux + 211)
#define __NR_set_tid_address		(__NR_Linux + 212)
#define __NR_restart_syscall		(__NR_Linux + 213)
#define __NR_semtimedop			(__NR_Linux + 214)
#define __NR_fadvise64			(__NR_Linux + 215)
#define __NR_timer_create		(__NR_Linux + 216)
#define __NR_timer_settime		(__NR_Linux + 217)
#define __NR_timer_gettime		(__NR_Linux + 218)
#define __NR_timer_getoverrun		(__NR_Linux + 219)
#define __NR_timer_delete		(__NR_Linux + 220)
#define __NR_clock_settime		(__NR_Linux + 221)
#define __NR_clock_gettime		(__NR_Linux + 222)
#define __NR_clock_getres		(__NR_Linux + 223)
#define __NR_clock_nanosleep		(__NR_Linux + 224)
#define __NR_tgkill			(__NR_Linux + 225)
#define __NR_utimes			(__NR_Linux + 226)
#define __NR_mbind			(__NR_Linux + 227)
#define __NR_get_mempolicy		(__NR_Linux + 228)
#define __NR_set_mempolicy		(__NR_Linux + 229)
#define __NR_mq_open			(__NR_Linux + 230)
#define __NR_mq_unlink			(__NR_Linux + 231)
#define __NR_mq_timedsend		(__NR_Linux + 232)
#define __NR_mq_timedreceive		(__NR_Linux + 233)
#define __NR_mq_notify			(__NR_Linux + 234)
#define __NR_mq_getsetattr		(__NR_Linux + 235)
#define __NR_vserver			(__NR_Linux + 236)
#define __NR_waitid			(__NR_Linux + 237)
/* #define __NR_sys_setaltroot		(__NR_Linux + 238) */
#define __NR_add_key			(__NR_Linux + 239)
#define __NR_request_key		(__NR_Linux + 240)
#define __NR_keyctl			(__NR_Linux + 241)
#define __NR_set_thread_area		(__NR_Linux + 242)
#define __NR_inotify_init		(__NR_Linux + 243)
#define __NR_inotify_add_watch		(__NR_Linux + 244)
#define __NR_inotify_rm_watch		(__NR_Linux + 245)
#define __NR_migrate_pages		(__NR_Linux + 246)
#define __NR_openat			(__NR_Linux + 247)
#define __NR_mkdirat			(__NR_Linux + 248)
#define __NR_mknodat			(__NR_Linux + 249)
#define __NR_fchownat			(__NR_Linux + 250)
#define __NR_futimesat			(__NR_Linux + 251)
#define __NR_newfstatat			(__NR_Linux + 252)
#define __NR_unlinkat			(__NR_Linux + 253)
#define __NR_renameat			(__NR_Linux + 254)
#define __NR_linkat			(__NR_Linux + 255)
#define __NR_symlinkat			(__NR_Linux + 256)
#define __NR_readlinkat			(__NR_Linux + 257)
#define __NR_fchmodat			(__NR_Linux + 258)
#define __NR_faccessat			(__NR_Linux + 259)
#define __NR_pselect6			(__NR_Linux + 260)
#define __NR_ppoll			(__NR_Linux + 261)
#define __NR_unshare			(__NR_Linux + 262)
#define __NR_splice			(__NR_Linux + 263)
#define __NR_sync_file_range		(__NR_Linux + 264)
#define __NR_tee			(__NR_Linux + 265)
#define __NR_vmsplice			(__NR_Linux + 266)
#define __NR_move_pages			(__NR_Linux + 267)
#define __NR_set_robust_list		(__NR_Linux + 268)
#define __NR_get_robust_list		(__NR_Linux + 269)
#define __NR_kexec_load			(__NR_Linux + 270)
#define __NR_getcpu			(__NR_Linux + 271)
#define __NR_epoll_pwait		(__NR_Linux + 272)
#define __NR_ioprio_set			(__NR_Linux + 273)
#define __NR_ioprio_get			(__NR_Linux + 274)
#define __NR_utimensat			(__NR_Linux + 275)
#define __NR_signalfd			(__NR_Linux + 276)
#define __NR_timerfd			(__NR_Linux + 277)
#define __NR_eventfd			(__NR_Linux + 278)
#define __NR_fallocate			(__NR_Linux + 279)
#define __NR_timerfd_create		(__NR_Linux + 280)
#define __NR_timerfd_gettime		(__NR_Linux + 281)
#define __NR_timerfd_settime		(__NR_Linux + 282)
#define __NR_signalfd4			(__NR_Linux + 283)
#define __NR_eventfd2			(__NR_Linux + 284)
#define __NR_epoll_create1		(__NR_Linux + 285)
#define __NR_dup3			(__NR_Linux + 286)
#define __NR_pipe2			(__NR_Linux + 287)
#define __NR_inotify_init1		(__NR_Linux + 288)
#define __NR_preadv			(__NR_Linux + 289)
#define __NR_pwritev			(__NR_Linux + 290)
#define __NR_rt_tgsigqueueinfo		(__NR_Linux + 291)
#define __NR_perf_event_open		(__NR_Linux + 292)
#define __NR_accept4			(__NR_Linux + 293)
#define __NR_recvmmsg			(__NR_Linux + 294)

/*
 * Offset of the last Linux 64-bit flavoured syscall
 */
#define __NR_Linux_syscalls		294

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 */

#define __NR_64_Linux			5000
#define __NR_64_Linux_syscalls		294

#if _MIPS_SIM == _MIPS_SIM_NABI32

/*
 * Linux N32 syscalls are in the range from 6000 to 6999.
 */
#define __NR_Linux			6000
#define __NR_read			(__NR_Linux +   0)
#define __NR_write			(__NR_Linux +   1)
#define __NR_open			(__NR_Linux +   2)
#define __NR_close			(__NR_Linux +   3)
#define __NR_stat			(__NR_Linux +   4)
#define __NR_fstat			(__NR_Linux +   5)
#define __NR_lstat			(__NR_Linux +   6)
#define __NR_poll			(__NR_Linux +   7)
#define __NR_lseek			(__NR_Linux +   8)
#define __NR_mmap			(__NR_Linux +   9)
#define __NR_mprotect			(__NR_Linux +  10)
#define __NR_munmap			(__NR_Linux +  11)
#define __NR_brk			(__NR_Linux +  12)
#define __NR_rt_sigaction		(__NR_Linux +  13)
#define __NR_rt_sigprocmask		(__NR_Linux +  14)
#define __NR_ioctl			(__NR_Linux +  15)
#define __NR_pread64			(__NR_Linux +  16)
#define __NR_pwrite64			(__NR_Linux +  17)
#define __NR_readv			(__NR_Linux +  18)
#define __NR_writev			(__NR_Linux +  19)
#define __NR_access			(__NR_Linux +  20)
#define __NR_pipe			(__NR_Linux +  21)
#define __NR__newselect			(__NR_Linux +  22)
#define __NR_sched_yield		(__NR_Linux +  23)
#define __NR_mremap			(__NR_Linux +  24)
#define __NR_msync			(__NR_Linux +  25)
#define __NR_mincore			(__NR_Linux +  26)
#define __NR_madvise			(__NR_Linux +  27)
#define __NR_shmget			(__NR_Linux +  28)
#define __NR_shmat			(__NR_Linux +  29)
#define __NR_shmctl			(__NR_Linux +  30)
#define __NR_dup			(__NR_Linux +  31)
#define __NR_dup2			(__NR_Linux +  32)
#define __NR_pause			(__NR_Linux +  33)
#define __NR_nanosleep			(__NR_Linux +  34)
#define __NR_getitimer			(__NR_Linux +  35)
#define __NR_setitimer			(__NR_Linux +  36)
#define __NR_alarm			(__NR_Linux +  37)
#define __NR_getpid			(__NR_Linux +  38)
#define __NR_sendfile			(__NR_Linux +  39)
#define __NR_socket			(__NR_Linux +  40)
#define __NR_connect			(__NR_Linux +  41)
#define __NR_accept			(__NR_Linux +  42)
#define __NR_sendto			(__NR_Linux +  43)
#define __NR_recvfrom			(__NR_Linux +  44)
#define __NR_sendmsg			(__NR_Linux +  45)
#define __NR_recvmsg			(__NR_Linux +  46)
#define __NR_shutdown			(__NR_Linux +  47)
#define __NR_bind			(__NR_Linux +  48)
#define __NR_listen			(__NR_Linux +  49)
#define __NR_getsockname		(__NR_Linux +  50)
#define __NR_getpeername		(__NR_Linux +  51)
#define __NR_socketpair			(__NR_Linux +  52)
#define __NR_setsockopt			(__NR_Linux +  53)
#define __NR_getsockopt			(__NR_Linux +  54)
#define __NR_clone			(__NR_Linux +  55)
#define __NR_fork			(__NR_Linux +  56)
#define __NR_execve			(__NR_Linux +  57)
#define __NR_exit			(__NR_Linux +  58)
#define __NR_wait4			(__NR_Linux +  59)
#define __NR_kill			(__NR_Linux +  60)
#define __NR_uname			(__NR_Linux +  61)
#define __NR_semget			(__NR_Linux +  62)
#define __NR_semop			(__NR_Linux +  63)
#define __NR_semctl			(__NR_Linux +  64)
#define __NR_shmdt			(__NR_Linux +  65)
#define __NR_msgget			(__NR_Linux +  66)
#define __NR_msgsnd			(__NR_Linux +  67)
#define __NR_msgrcv			(__NR_Linux +  68)
#define __NR_msgctl			(__NR_Linux +  69)
#define __NR_fcntl			(__NR_Linux +  70)
#define __NR_flock			(__NR_Linux +  71)
#define __NR_fsync			(__NR_Linux +  72)
#define __NR_fdatasync			(__NR_Linux +  73)
#define __NR_truncate			(__NR_Linux +  74)
#define __NR_ftruncate			(__NR_Linux +  75)
#define __NR_getdents			(__NR_Linux +  76)
#define __NR_getcwd			(__NR_Linux +  77)
#define __NR_chdir			(__NR_Linux +  78)
#define __NR_fchdir			(__NR_Linux +  79)
#define __NR_rename			(__NR_Linux +  80)
#define __NR_mkdir			(__NR_Linux +  81)
#define __NR_rmdir			(__NR_Linux +  82)
#define __NR_creat			(__NR_Linux +  83)
#define __NR_link			(__NR_Linux +  84)
#define __NR_unlink			(__NR_Linux +  85)
#define __NR_symlink			(__NR_Linux +  86)
#define __NR_readlink			(__NR_Linux +  87)
#define __NR_chmod			(__NR_Linux +  88)
#define __NR_fchmod			(__NR_Linux +  89)
#define __NR_chown			(__NR_Linux +  90)
#define __NR_fchown			(__NR_Linux +  91)
#define __NR_lchown			(__NR_Linux +  92)
#define __NR_umask			(__NR_Linux +  93)
#define __NR_gettimeofday		(__NR_Linux +  94)
#define __NR_getrlimit			(__NR_Linux +  95)
#define __NR_getrusage			(__NR_Linux +  96)
#define __NR_sysinfo			(__NR_Linux +  97)
#define __NR_times			(__NR_Linux +  98)
#define __NR_ptrace			(__NR_Linux +  99)
#define __NR_getuid			(__NR_Linux + 100)
#define __NR_syslog			(__NR_Linux + 101)
#define __NR_getgid			(__NR_Linux + 102)
#define __NR_setuid			(__NR_Linux + 103)
#define __NR_setgid			(__NR_Linux + 104)
#define __NR_geteuid			(__NR_Linux + 105)
#define __NR_getegid			(__NR_Linux + 106)
#define __NR_setpgid			(__NR_Linux + 107)
#define __NR_getppid			(__NR_Linux + 108)
#define __NR_getpgrp			(__NR_Linux + 109)
#define __NR_setsid			(__NR_Linux + 110)
#define __NR_setreuid			(__NR_Linux + 111)
#define __NR_setregid			(__NR_Linux + 112)
#define __NR_getgroups			(__NR_Linux + 113)
#define __NR_setgroups			(__NR_Linux + 114)
#define __NR_setresuid			(__NR_Linux + 115)
#define __NR_getresuid			(__NR_Linux + 116)
#define __NR_setresgid			(__NR_Linux + 117)
#define __NR_getresgid			(__NR_Linux + 118)
#define __NR_getpgid			(__NR_Linux + 119)
#define __NR_setfsuid			(__NR_Linux + 120)
#define __NR_setfsgid			(__NR_Linux + 121)
#define __NR_getsid			(__NR_Linux + 122)
#define __NR_capget			(__NR_Linux + 123)
#define __NR_capset			(__NR_Linux + 124)
#define __NR_rt_sigpending		(__NR_Linux + 125)
#define __NR_rt_sigtimedwait		(__NR_Linux + 126)
#define __NR_rt_sigqueueinfo		(__NR_Linux + 127)
#define __NR_rt_sigsuspend		(__NR_Linux + 128)
#define __NR_sigaltstack		(__NR_Linux + 129)
#define __NR_utime			(__NR_Linux + 130)
#define __NR_mknod			(__NR_Linux + 131)
#define __NR_personality		(__NR_Linux + 132)
#define __NR_ustat			(__NR_Linux + 133)
#define __NR_statfs			(__NR_Linux + 134)
#define __NR_fstatfs			(__NR_Linux + 135)
#define __NR_sysfs			(__NR_Linux + 136)
#define __NR_getpriority		(__NR_Linux + 137)
#define __NR_setpriority		(__NR_Linux + 138)
#define __NR_sched_setparam		(__NR_Linux + 139)
#define __NR_sched_getparam		(__NR_Linux + 140)
#define __NR_sched_setscheduler		(__NR_Linux + 141)
#define __NR_sched_getscheduler		(__NR_Linux + 142)
#define __NR_sched_get_priority_max	(__NR_Linux + 143)
#define __NR_sched_get_priority_min	(__NR_Linux + 144)
#define __NR_sched_rr_get_interval	(__NR_Linux + 145)
#define __NR_mlock			(__NR_Linux + 146)
#define __NR_munlock			(__NR_Linux + 147)
#define __NR_mlockall			(__NR_Linux + 148)
#define __NR_munlockall			(__NR_Linux + 149)
#define __NR_vhangup			(__NR_Linux + 150)
#define __NR_pivot_root			(__NR_Linux + 151)
#define __NR__sysctl			(__NR_Linux + 152)
#define __NR_prctl			(__NR_Linux + 153)
#define __NR_adjtimex			(__NR_Linux + 154)
#define __NR_setrlimit			(__NR_Linux + 155)
#define __NR_chroot			(__NR_Linux + 156)
#define __NR_sync			(__NR_Linux + 157)
#define __NR_acct			(__NR_Linux + 158)
#define __NR_settimeofday		(__NR_Linux + 159)
#define __NR_mount			(__NR_Linux + 160)
#define __NR_umount2			(__NR_Linux + 161)
#define __NR_swapon			(__NR_Linux + 162)
#define __NR_swapoff			(__NR_Linux + 163)
#define __NR_reboot			(__NR_Linux + 164)
#define __NR_sethostname		(__NR_Linux + 165)
#define __NR_setdomainname		(__NR_Linux + 166)
#define __NR_create_module		(__NR_Linux + 167)
#define __NR_init_module		(__NR_Linux + 168)
#define __NR_delete_module		(__NR_Linux + 169)
#define __NR_get_kernel_syms		(__NR_Linux + 170)
#define __NR_query_module		(__NR_Linux + 171)
#define __NR_quotactl			(__NR_Linux + 172)
#define __NR_nfsservctl			(__NR_Linux + 173)
#define __NR_getpmsg			(__NR_Linux + 174)
#define __NR_putpmsg			(__NR_Linux + 175)
#define __NR_afs_syscall		(__NR_Linux + 176)
#define __NR_reserved177		(__NR_Linux + 177)
#define __NR_gettid			(__NR_Linux + 178)
#define __NR_readahead			(__NR_Linux + 179)
#define __NR_setxattr			(__NR_Linux + 180)
#define __NR_lsetxattr			(__NR_Linux + 181)
#define __NR_fsetxattr			(__NR_Linux + 182)
#define __NR_getxattr			(__NR_Linux + 183)
#define __NR_lgetxattr			(__NR_Linux + 184)
#define __NR_fgetxattr			(__NR_Linux + 185)
#define __NR_listxattr			(__NR_Linux + 186)
#define __NR_llistxattr			(__NR_Linux + 187)
#define __NR_flistxattr			(__NR_Linux + 188)
#define __NR_removexattr		(__NR_Linux + 189)
#define __NR_lremovexattr		(__NR_Linux + 190)
#define __NR_fremovexattr		(__NR_Linux + 191)
#define __NR_tkill			(__NR_Linux + 192)
#define __NR_reserved193		(__NR_Linux + 193)
#define __NR_futex			(__NR_Linux + 194)
#define __NR_sched_setaffinity		(__NR_Linux + 195)
#define __NR_sched_getaffinity		(__NR_Linux + 196)
#define __NR_cacheflush			(__NR_Linux + 197)
#define __NR_cachectl			(__NR_Linux + 198)
#define __NR_sysmips			(__NR_Linux + 199)
#define __NR_io_setup			(__NR_Linux + 200)
#define __NR_io_destroy			(__NR_Linux + 201)
#define __NR_io_getevents		(__NR_Linux + 202)
#define __NR_io_submit			(__NR_Linux + 203)
#define __NR_io_cancel			(__NR_Linux + 204)
#define __NR_exit_group			(__NR_Linux + 205)
#define __NR_lookup_dcookie		(__NR_Linux + 206)
#define __NR_epoll_create		(__NR_Linux + 207)
#define __NR_epoll_ctl			(__NR_Linux + 208)
#define __NR_epoll_wait			(__NR_Linux + 209)
#define __NR_remap_file_pages		(__NR_Linux + 210)
#define __NR_rt_sigreturn		(__NR_Linux + 211)
#define __NR_fcntl64			(__NR_Linux + 212)
#define __NR_set_tid_address		(__NR_Linux + 213)
#define __NR_restart_syscall		(__NR_Linux + 214)
#define __NR_semtimedop			(__NR_Linux + 215)
#define __NR_fadvise64			(__NR_Linux + 216)
#define __NR_statfs64			(__NR_Linux + 217)
#define __NR_fstatfs64			(__NR_Linux + 218)
#define __NR_sendfile64			(__NR_Linux + 219)
#define __NR_timer_create		(__NR_Linux + 220)
#define __NR_timer_settime		(__NR_Linux + 221)
#define __NR_timer_gettime		(__NR_Linux + 222)
#define __NR_timer_getoverrun		(__NR_Linux + 223)
#define __NR_timer_delete		(__NR_Linux + 224)
#define __NR_clock_settime		(__NR_Linux + 225)
#define __NR_clock_gettime		(__NR_Linux + 226)
#define __NR_clock_getres		(__NR_Linux + 227)
#define __NR_clock_nanosleep		(__NR_Linux + 228)
#define __NR_tgkill			(__NR_Linux + 229)
#define __NR_utimes			(__NR_Linux + 230)
#define __NR_mbind			(__NR_Linux + 231)
#define __NR_get_mempolicy		(__NR_Linux + 232)
#define __NR_set_mempolicy		(__NR_Linux + 233)
#define __NR_mq_open			(__NR_Linux + 234)
#define __NR_mq_unlink			(__NR_Linux + 235)
#define __NR_mq_timedsend		(__NR_Linux + 236)
#define __NR_mq_timedreceive		(__NR_Linux + 237)
#define __NR_mq_notify			(__NR_Linux + 238)
#define __NR_mq_getsetattr		(__NR_Linux + 239)
#define __NR_vserver			(__NR_Linux + 240)
#define __NR_waitid			(__NR_Linux + 241)
/* #define __NR_sys_setaltroot		(__NR_Linux + 242) */
#define __NR_add_key			(__NR_Linux + 243)
#define __NR_request_key		(__NR_Linux + 244)
#define __NR_keyctl			(__NR_Linux + 245)
#define __NR_set_thread_area		(__NR_Linux + 246)
#define __NR_inotify_init		(__NR_Linux + 247)
#define __NR_inotify_add_watch		(__NR_Linux + 248)
#define __NR_inotify_rm_watch		(__NR_Linux + 249)
#define __NR_migrate_pages		(__NR_Linux + 250)
#define __NR_openat			(__NR_Linux + 251)
#define __NR_mkdirat			(__NR_Linux + 252)
#define __NR_mknodat			(__NR_Linux + 253)
#define __NR_fchownat			(__NR_Linux + 254)
#define __NR_futimesat			(__NR_Linux + 255)
#define __NR_newfstatat			(__NR_Linux + 256)
#define __NR_unlinkat			(__NR_Linux + 257)
#define __NR_renameat			(__NR_Linux + 258)
#define __NR_linkat			(__NR_Linux + 259)
#define __NR_symlinkat			(__NR_Linux + 260)
#define __NR_readlinkat			(__NR_Linux + 261)
#define __NR_fchmodat			(__NR_Linux + 262)
#define __NR_faccessat			(__NR_Linux + 263)
#define __NR_pselect6			(__NR_Linux + 264)
#define __NR_ppoll			(__NR_Linux + 265)
#define __NR_unshare			(__NR_Linux + 266)
#define __NR_splice			(__NR_Linux + 267)
#define __NR_sync_file_range		(__NR_Linux + 268)
#define __NR_tee			(__NR_Linux + 269)
#define __NR_vmsplice			(__NR_Linux + 270)
#define __NR_move_pages			(__NR_Linux + 271)
#define __NR_set_robust_list		(__NR_Linux + 272)
#define __NR_get_robust_list		(__NR_Linux + 273)
#define __NR_kexec_load			(__NR_Linux + 274)
#define __NR_getcpu			(__NR_Linux + 275)
#define __NR_epoll_pwait		(__NR_Linux + 276)
#define __NR_ioprio_set			(__NR_Linux + 277)
#define __NR_ioprio_get			(__NR_Linux + 278)
#define __NR_utimensat			(__NR_Linux + 279)
#define __NR_signalfd			(__NR_Linux + 280)
#define __NR_timerfd			(__NR_Linux + 281)
#define __NR_eventfd			(__NR_Linux + 282)
#define __NR_fallocate			(__NR_Linux + 283)
#define __NR_timerfd_create		(__NR_Linux + 284)
#define __NR_timerfd_gettime		(__NR_Linux + 285)
#define __NR_timerfd_settime		(__NR_Linux + 286)
#define __NR_signalfd4			(__NR_Linux + 287)
#define __NR_eventfd2			(__NR_Linux + 288)
#define __NR_epoll_create1		(__NR_Linux + 289)
#define __NR_dup3			(__NR_Linux + 290)
#define __NR_pipe2			(__NR_Linux + 291)
#define __NR_inotify_init1		(__NR_Linux + 292)
#define __NR_preadv			(__NR_Linux + 293)
#define __NR_pwritev			(__NR_Linux + 294)
#define __NR_rt_tgsigqueueinfo		(__NR_Linux + 295)
#define __NR_perf_event_open		(__NR_Linux + 296)
#define __NR_accept4			(__NR_Linux + 297)
#define __NR_recvmmsg			(__NR_Linux + 298)

/*
 * Offset of the last N32 flavoured syscall
 */
#define __NR_Linux_syscalls		298

#endif /* _MIPS_SIM == _MIPS_SIM_NABI32 */

#define __NR_N32_Linux			6000
#define __NR_N32_Linux_syscalls		298

/************************************************************************************/
/************************************************************************************/

/* Copied from /usr/include/bits/syscall.h */
#define SYS_64_Linux __NR_64_Linux
#define SYS_64_Linux_syscalls __NR_64_Linux_syscalls
#define SYS_Linux __NR_Linux
#define SYS_Linux_syscalls __NR_Linux_syscalls
#define SYS_N32_Linux __NR_N32_Linux
#define SYS_N32_Linux_syscalls __NR_N32_Linux_syscalls
#define SYS_O32_Linux __NR_O32_Linux
#define SYS_O32_Linux_syscalls __NR_O32_Linux_syscalls
#define SYS__llseek __NR__llseek
#define SYS__newselect __NR__newselect
#define SYS__sysctl __NR__sysctl
#define SYS_accept __NR_accept
#define SYS_accept4 __NR_accept4
#define SYS_access __NR_access
#define SYS_acct __NR_acct
#define SYS_add_key __NR_add_key
#define SYS_adjtimex __NR_adjtimex
#define SYS_afs_syscall __NR_afs_syscall
#define SYS_alarm __NR_alarm
#define SYS_bdflush __NR_bdflush
#define SYS_bind __NR_bind
#define SYS_break __NR_break
#define SYS_brk __NR_brk
#define SYS_cachectl __NR_cachectl
#define SYS_cacheflush __NR_cacheflush
#define SYS_capget __NR_capget
#define SYS_capset __NR_capset
#define SYS_chdir __NR_chdir
#define SYS_chmod __NR_chmod
#define SYS_chown __NR_chown
#define SYS_chroot __NR_chroot
#define SYS_clock_getres __NR_clock_getres
#define SYS_clock_gettime __NR_clock_gettime
#define SYS_clock_nanosleep __NR_clock_nanosleep
#define SYS_clock_settime __NR_clock_settime
#define SYS_clone __NR_clone
#define SYS_close __NR_close
#define SYS_connect __NR_connect
#define SYS_creat __NR_creat
#define SYS_create_module __NR_create_module
#define SYS_delete_module __NR_delete_module
#define SYS_dup __NR_dup
#define SYS_dup2 __NR_dup2
#define SYS_dup3 __NR_dup3
#define SYS_epoll_create __NR_epoll_create
#define SYS_epoll_create1 __NR_epoll_create1
#define SYS_epoll_ctl __NR_epoll_ctl
#define SYS_epoll_pwait __NR_epoll_pwait
#define SYS_epoll_wait __NR_epoll_wait
#define SYS_eventfd __NR_eventfd
#define SYS_eventfd2 __NR_eventfd2
#define SYS_execve __NR_execve
#define SYS_exit __NR_exit
#define SYS_exit_group __NR_exit_group
#define SYS_faccessat __NR_faccessat
#define SYS_fadvise64 __NR_fadvise64
#define SYS_fallocate __NR_fallocate
#define SYS_fchdir __NR_fchdir
#define SYS_fchmod __NR_fchmod
#define SYS_fchmodat __NR_fchmodat
#define SYS_fchown __NR_fchown
#define SYS_fchownat __NR_fchownat
#define SYS_fcntl __NR_fcntl
#define SYS_fcntl64 __NR_fcntl64
#define SYS_fdatasync __NR_fdatasync
#define SYS_fgetxattr __NR_fgetxattr
#define SYS_flistxattr __NR_flistxattr
#define SYS_flock __NR_flock
#define SYS_fork __NR_fork
#define SYS_fremovexattr __NR_fremovexattr
#define SYS_fsetxattr __NR_fsetxattr
#define SYS_fstat __NR_fstat
#define SYS_fstat64 __NR_fstat64
#define SYS_fstatat64 __NR_fstatat64
#define SYS_fstatfs __NR_fstatfs
#define SYS_fstatfs64 __NR_fstatfs64
#define SYS_fsync __NR_fsync
#define SYS_ftime __NR_ftime
#define SYS_ftruncate __NR_ftruncate
#define SYS_ftruncate64 __NR_ftruncate64
#define SYS_futex __NR_futex
#define SYS_futimesat __NR_futimesat
#define SYS_get_kernel_syms __NR_get_kernel_syms
#define SYS_get_mempolicy __NR_get_mempolicy
#define SYS_get_robust_list __NR_get_robust_list
#define SYS_getcpu __NR_getcpu
#define SYS_getcwd __NR_getcwd
#define SYS_getdents __NR_getdents
#define SYS_getdents64 __NR_getdents64
#define SYS_getegid __NR_getegid
#define SYS_geteuid __NR_geteuid
#define SYS_getgid __NR_getgid
#define SYS_getgroups __NR_getgroups
#define SYS_getitimer __NR_getitimer
#define SYS_getpeername __NR_getpeername
#define SYS_getpgid __NR_getpgid
#define SYS_getpgrp __NR_getpgrp
#define SYS_getpid __NR_getpid
#define SYS_getpmsg __NR_getpmsg
#define SYS_getppid __NR_getppid
#define SYS_getpriority __NR_getpriority
#define SYS_getresgid __NR_getresgid
#define SYS_getresuid __NR_getresuid
#define SYS_getrlimit __NR_getrlimit
#define SYS_getrusage __NR_getrusage
#define SYS_getsid __NR_getsid
#define SYS_getsockname __NR_getsockname
#define SYS_getsockopt __NR_getsockopt
#define SYS_gettid __NR_gettid
#define SYS_gettimeofday __NR_gettimeofday
#define SYS_getuid __NR_getuid
#define SYS_getxattr __NR_getxattr
#define SYS_gtty __NR_gtty
#define SYS_idle __NR_idle
#define SYS_init_module __NR_init_module
#define SYS_inotify_add_watch __NR_inotify_add_watch
#define SYS_inotify_init __NR_inotify_init
#define SYS_inotify_init1 __NR_inotify_init1
#define SYS_inotify_rm_watch __NR_inotify_rm_watch
#define SYS_io_cancel __NR_io_cancel
#define SYS_io_destroy __NR_io_destroy
#define SYS_io_getevents __NR_io_getevents
#define SYS_io_setup __NR_io_setup
#define SYS_io_submit __NR_io_submit
#define SYS_ioctl __NR_ioctl
#define SYS_ioperm __NR_ioperm
#define SYS_iopl __NR_iopl
#define SYS_ioprio_get __NR_ioprio_get
#define SYS_ioprio_set __NR_ioprio_set
#define SYS_ipc __NR_ipc
#define SYS_kexec_load __NR_kexec_load
#define SYS_keyctl __NR_keyctl
#define SYS_kill __NR_kill
#define SYS_lchown __NR_lchown
#define SYS_lgetxattr __NR_lgetxattr
#define SYS_link __NR_link
#define SYS_linkat __NR_linkat
#define SYS_listen __NR_listen
#define SYS_listxattr __NR_listxattr
#define SYS_llistxattr __NR_llistxattr
#define SYS_lock __NR_lock
#define SYS_lookup_dcookie __NR_lookup_dcookie
#define SYS_lremovexattr __NR_lremovexattr
#define SYS_lseek __NR_lseek
#define SYS_lsetxattr __NR_lsetxattr
#define SYS_lstat __NR_lstat
#define SYS_lstat64 __NR_lstat64
#define SYS_madvise __NR_madvise
#define SYS_mbind __NR_mbind
#define SYS_migrate_pages __NR_migrate_pages
#define SYS_mincore __NR_mincore
#define SYS_mkdir __NR_mkdir
#define SYS_mkdirat __NR_mkdirat
#define SYS_mknod __NR_mknod
#define SYS_mknodat __NR_mknodat
#define SYS_mlock __NR_mlock
#define SYS_mlockall __NR_mlockall
#define SYS_mmap __NR_mmap
#define SYS_mmap2 __NR_mmap2
#define SYS_modify_ldt __NR_modify_ldt
#define SYS_mount __NR_mount
#define SYS_move_pages __NR_move_pages
#define SYS_mprotect __NR_mprotect
#define SYS_mpx __NR_mpx
#define SYS_mq_getsetattr __NR_mq_getsetattr
#define SYS_mq_notify __NR_mq_notify
#define SYS_mq_open __NR_mq_open
#define SYS_mq_timedreceive __NR_mq_timedreceive
#define SYS_mq_timedsend __NR_mq_timedsend
#define SYS_mq_unlink __NR_mq_unlink
#define SYS_mremap __NR_mremap
#define SYS_msync __NR_msync
#define SYS_munlock __NR_munlock
#define SYS_munlockall __NR_munlockall
#define SYS_munmap __NR_munmap
#define SYS_nanosleep __NR_nanosleep
#define SYS_nfsservctl __NR_nfsservctl
#define SYS_nice __NR_nice
#define SYS_open __NR_open
#define SYS_openat __NR_openat
#define SYS_pause __NR_pause
#define SYS_perf_event_open __NR_perf_event_open
#define SYS_personality __NR_personality
#define SYS_pipe __NR_pipe
#define SYS_pipe2 __NR_pipe2
#define SYS_pivot_root __NR_pivot_root
#define SYS_poll __NR_poll
#define SYS_ppoll __NR_ppoll
#define SYS_prctl __NR_prctl
#define SYS_pread64 __NR_pread64
#define SYS_preadv __NR_preadv
#define SYS_prof __NR_prof
#define SYS_profil __NR_profil
#define SYS_pselect6 __NR_pselect6
#define SYS_ptrace __NR_ptrace
#define SYS_putpmsg __NR_putpmsg
#define SYS_pwrite64 __NR_pwrite64
#define SYS_pwritev __NR_pwritev
#define SYS_query_module __NR_query_module
#define SYS_quotactl __NR_quotactl
#define SYS_read __NR_read
#define SYS_readahead __NR_readahead
#define SYS_readdir __NR_readdir
#define SYS_readlink __NR_readlink
#define SYS_readlinkat __NR_readlinkat
#define SYS_readv __NR_readv
#define SYS_reboot __NR_reboot
#define SYS_recv __NR_recv
#define SYS_recvfrom __NR_recvfrom
#define SYS_recvmmsg __NR_recvmmsg
#define SYS_recvmsg __NR_recvmsg
#define SYS_remap_file_pages __NR_remap_file_pages
#define SYS_removexattr __NR_removexattr
#define SYS_rename __NR_rename
#define SYS_renameat __NR_renameat
#define SYS_request_key __NR_request_key
#define SYS_reserved221 __NR_reserved221
#define SYS_reserved82 __NR_reserved82
#define SYS_restart_syscall __NR_restart_syscall
#define SYS_rmdir __NR_rmdir
#define SYS_rt_sigaction __NR_rt_sigaction
#define SYS_rt_sigpending __NR_rt_sigpending
#define SYS_rt_sigprocmask __NR_rt_sigprocmask
#define SYS_rt_sigqueueinfo __NR_rt_sigqueueinfo
#define SYS_rt_sigreturn __NR_rt_sigreturn
#define SYS_rt_sigsuspend __NR_rt_sigsuspend
#define SYS_rt_sigtimedwait __NR_rt_sigtimedwait
#define SYS_rt_tgsigqueueinfo __NR_rt_tgsigqueueinfo
#define SYS_sched_get_priority_max __NR_sched_get_priority_max
#define SYS_sched_get_priority_min __NR_sched_get_priority_min
#define SYS_sched_getaffinity __NR_sched_getaffinity
#define SYS_sched_getparam __NR_sched_getparam
#define SYS_sched_getscheduler __NR_sched_getscheduler
#define SYS_sched_rr_get_interval __NR_sched_rr_get_interval
#define SYS_sched_setaffinity __NR_sched_setaffinity
#define SYS_sched_setparam __NR_sched_setparam
#define SYS_sched_setscheduler __NR_sched_setscheduler
#define SYS_sched_yield __NR_sched_yield
#define SYS_send __NR_send
#define SYS_sendfile __NR_sendfile
#define SYS_sendfile64 __NR_sendfile64
#define SYS_sendmsg __NR_sendmsg
#define SYS_sendto __NR_sendto
#define SYS_set_mempolicy __NR_set_mempolicy
#define SYS_set_robust_list __NR_set_robust_list
#define SYS_set_thread_area __NR_set_thread_area
#define SYS_set_tid_address __NR_set_tid_address
#define SYS_setdomainname __NR_setdomainname
#define SYS_setfsgid __NR_setfsgid
#define SYS_setfsuid __NR_setfsuid
#define SYS_setgid __NR_setgid
#define SYS_setgroups __NR_setgroups
#define SYS_sethostname __NR_sethostname
#define SYS_setitimer __NR_setitimer
#define SYS_setpgid __NR_setpgid
#define SYS_setpriority __NR_setpriority
#define SYS_setregid __NR_setregid
#define SYS_setresgid __NR_setresgid
#define SYS_setresuid __NR_setresuid
#define SYS_setreuid __NR_setreuid
#define SYS_setrlimit __NR_setrlimit
#define SYS_setsid __NR_setsid
#define SYS_setsockopt __NR_setsockopt
#define SYS_settimeofday __NR_settimeofday
#define SYS_setuid __NR_setuid
#define SYS_setxattr __NR_setxattr
#define SYS_sgetmask __NR_sgetmask
#define SYS_shutdown __NR_shutdown
#define SYS_sigaction __NR_sigaction
#define SYS_sigaltstack __NR_sigaltstack
#define SYS_signal __NR_signal
#define SYS_signalfd __NR_signalfd
#define SYS_signalfd4 __NR_signalfd4
#define SYS_sigpending __NR_sigpending
#define SYS_sigprocmask __NR_sigprocmask
#define SYS_sigreturn __NR_sigreturn
#define SYS_sigsuspend __NR_sigsuspend
#define SYS_socket __NR_socket
#define SYS_socketcall __NR_socketcall
#define SYS_socketpair __NR_socketpair
#define SYS_splice __NR_splice
#define SYS_ssetmask __NR_ssetmask
#define SYS_stat __NR_stat
#define SYS_stat64 __NR_stat64
#define SYS_statfs __NR_statfs
#define SYS_statfs64 __NR_statfs64
#define SYS_stime __NR_stime
#define SYS_stty __NR_stty
#define SYS_swapoff __NR_swapoff
#define SYS_swapon __NR_swapon
#define SYS_symlink __NR_symlink
#define SYS_symlinkat __NR_symlinkat
#define SYS_sync __NR_sync
#define SYS_sync_file_range __NR_sync_file_range
#define SYS_syscall __NR_syscall
#define SYS_sysfs __NR_sysfs
#define SYS_sysinfo __NR_sysinfo
#define SYS_syslog __NR_syslog
#define SYS_sysmips __NR_sysmips
#define SYS_tee __NR_tee
#define SYS_tgkill __NR_tgkill
#define SYS_time __NR_time
#define SYS_timer_create __NR_timer_create
#define SYS_timer_delete __NR_timer_delete
#define SYS_timer_getoverrun __NR_timer_getoverrun
#define SYS_timer_gettime __NR_timer_gettime
#define SYS_timer_settime __NR_timer_settime
#define SYS_timerfd __NR_timerfd
#define SYS_timerfd_create __NR_timerfd_create
#define SYS_timerfd_gettime __NR_timerfd_gettime
#define SYS_timerfd_settime __NR_timerfd_settime
#define SYS_times __NR_times
#define SYS_tkill __NR_tkill
#define SYS_truncate __NR_truncate
#define SYS_truncate64 __NR_truncate64
#define SYS_ulimit __NR_ulimit
#define SYS_umask __NR_umask
#define SYS_umount __NR_umount
#define SYS_umount2 __NR_umount2
#define SYS_uname __NR_uname
#define SYS_unlink __NR_unlink
#define SYS_unlinkat __NR_unlinkat
#define SYS_unshare __NR_unshare
#define SYS_unused109 __NR_unused109
#define SYS_unused150 __NR_unused150
#define SYS_unused18 __NR_unused18
#define SYS_unused28 __NR_unused28
#define SYS_unused59 __NR_unused59
#define SYS_unused84 __NR_unused84
#define SYS_uselib __NR_uselib
#define SYS_ustat __NR_ustat
#define SYS_utime __NR_utime
#define SYS_utimensat __NR_utimensat
#define SYS_utimes __NR_utimes
#define SYS_vhangup __NR_vhangup
#define SYS_vm86 __NR_vm86
#define SYS_vmsplice __NR_vmsplice
#define SYS_vserver __NR_vserver
#define SYS_wait4 __NR_wait4
#define SYS_waitid __NR_waitid
#define SYS_waitpid __NR_waitpid
#define SYS_write __NR_write
#define SYS_writev __NR_writev

#endif