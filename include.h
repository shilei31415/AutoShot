//
// Created by shilei on 19-12-26.
//

#ifndef HEROVISION_INCLUDE_H
#define HEROVISION_INCLUDE_H

#include <include/pnp.h>
#include "others/camera/MindVisionCamera.h"
#include "AutoShot/include/Armor.h"
#include "AutoShot/include/Mark.h"
#include "AutoShot/include/robot.h"
#include "AutoShot/include/TargetFind.h"
#include "AutoShot/include/trajectory.h"
#include "HeroVision.h"
#include "tools/setter/setter.h"
#include "tools/time/timer.h"
#include "others/SerialPort/SerialPort.h"
#include <cmath>

static setter g_setter;
static pnp slover(g_setter);

#endif //HEROVISION_INCLUDE_H
