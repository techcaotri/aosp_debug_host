#
# Qualcomm CHRE Implementation for Hexagon v60, based on Nanohub
#

include $(CHRE_PREFIX)/build/clean_build_template_args.mk

TARGET_NAME = qcom_hexagonv60_nanohub
TARGET_CFLAGS = -DCHRE_MESSAGE_TO_HOST_MAX_SIZE=4080
TARGET_CFLAGS += $(QCOM_HEXAGONV60_NANOHUB_CFLAGS)
TARGET_VARIANT_SRCS = $(QCOM_HEXAGONV60_NANOHUB_SRCS)
TARGET_SO_LATE_LIBS = $(QCOM_HEXAGONV60_NANOHUB_LATE_LIBS)
HEXAGON_ARCH = v60

ifneq ($(filter $(TARGET_NAME)% all, $(MAKECMDGOALS)),)
ifneq ($(IS_NANOAPP_BUILD),)
TARGET_SO_LATE_LIBS += $(CHRE_PREFIX)/build/app_support/qcom_nanohub/chre.so
TARGET_SO_LATE_LIBS += $(CHRE_PREFIX)/build/app_support/qcom_nanohub/chre_platform.so
include $(CHRE_PREFIX)/build/nanoapp/qcom_nanohub.mk
endif

include $(CHRE_PREFIX)/build/arch/hexagon.mk
include $(CHRE_PREFIX)/build/build_template.mk
endif
