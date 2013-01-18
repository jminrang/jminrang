#ifndef	__NOTICE_H__
#define	__NOTICE_H__

#define	START	\
"Start jminrang version prototype \n\n"

#define	GDT		\
"    GDT set                .........................  [ OK ]\n"

#define	IDT		\
"    IDT set                .........................  [ OK ]\n"

#define	PIC		\
"    PIC set                .........................  [ OK ]\n"

#define	RTC		\
"    Real time clock        .........................  [ %d-%d-%d %d:%d:%d ]\n", t.year, t.mon, t.day, t.hour, t.min, t.sec

#define	CPU		\
"    CPU check              .........................  [ %s ]\n", cpu_vendor

#define	PMM		\
"    Physical memory check  .........................  [ OK ]\n"

#define	VMM		\
"    Paging initialize      .........................  [ OK ]\n"



#endif
