#if !defined(JP_GPIO_H)
#define JP_GPIO_H

#include "BCM2835.h"

#define GPIO_0 (0)
#define GPIO_1 (1)
#define GPIO_2 (2)
#define GPIO_3 (3)
#define GPIO_4 (4)
#define GPIO_5 (5)
#define GPIO_6 (6)
#define GPIO_7 (7)
#define GPIO_8 (8)
#define GPIO_9 (9)
#define GPIO_10 (10)
#define GPIO_11 (11)
#define GPIO_12 (12)
#define GPIO_13 (13)
#define GPIO_14 (14)
#define GPIO_15 (15)
#define GPIO_16 (16)
#define GPIO_17 (17)
#define GPIO_18 (18)
#define GPIO_19 (19)
#define GPIO_20 (20)
#define GPIO_21 (21)
#define GPIO_22 (22)
#define GPIO_23 (23)
#define GPIO_24 (24)
#define GPIO_25 (25)
#define GPIO_26 (26)
#define GPIO_27 (27)
#define GPIO_28 (28)
#define GPIO_29 (29)
#define GPIO_30 (30)
#define GPIO_31 (31)
#define GPIO_32 (32)
#define GPIO_33 (33)
#define GPIO_34 (34)
#define GPIO_35 (35)
#define GPIO_36 (36)
#define GPIO_37 (37)
#define GPIO_38 (38)
#define GPIO_39 (39)
#define GPIO_40 (40)
#define GPIO_41 (41)
#define GPIO_42 (42)
#define GPIO_43 (43)
#define GPIO_44 (44)
#define GPIO_45 (45)
#define GPIO_46 (46)
#define GPIO_47 (47)
#define GPIO_48 (48)
#define GPIO_49 (49)
#define GPIO_50 (50)
#define GPIO_51 (51)
#define GPIO_52 (52)
#define GPIO_53 (53)

#define GPIO_LED GPIO_47

#define GPIO_OUTPUT GPIO_PIN_OUTPUT
#define GPIO_INPUT GPIO_PIN_INPUT
#define GPIO_ALT5 (2)

void
SetGPIOMode(u32 pin, u32 mode);

//
// NOTE(Peacock): For some reason the GPSETx and GPCLRx registers seem to be reversed...
//
void
SetGPIO(u32 pin);

void
ClearGPIO(u32 pin);

#endif
