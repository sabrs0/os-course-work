cmd_/home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o := gcc-11 -Wp,-MMD,/home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/.stub.o.d -nostdinc -I./arch/x86/include -I./arch/x86/include/generated  -I./include -I./arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -I./ubuntu/include -D__KERNEL__ -fmacro-prefix-map=./= -D__ASSEMBLY__ -fno-PIE -m64 -DCC_USING_FENTRY -g -gdwarf-5  -DMODULE  -c -o /home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o /home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.S  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --retpoline --rethunk --sls --stackval --static-call --uaccess --prefix=16   --module /home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o

source_/home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o := /home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.S

deps_/home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o := \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \

/home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o: $(deps_/home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o)

$(deps_/home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o):

/home/sersab/bmstu_ubu/4_course/os_course/os-course-work/source/../khook/x86/stub.o: $(wildcard ./tools/objtool/objtool)
